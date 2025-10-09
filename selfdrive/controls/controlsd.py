#!/usr/bin/env python3
import math
import threading
import time
from numbers import Number

from cereal import car, log
import cereal.messaging as messaging
from openpilot.common.constants import CV
from openpilot.common.params import Params
from openpilot.common.realtime import config_realtime_process, Priority, Ratekeeper, DT_CTRL
from openpilot.common.swaglog import cloudlog

from opendbc.car.car_helpers import interfaces
from opendbc.car.hyundai.values import CAR as HYUNDAI_CAR
from opendbc.car.vehicle_model import VehicleModel
from openpilot.selfdrive.controls.lib.drive_helpers import clip_curvature
from openpilot.selfdrive.controls.lib.latcontrol import LatControl
from openpilot.selfdrive.controls.lib.latcontrol_pid import LatControlPID
from openpilot.selfdrive.controls.lib.latcontrol_angle import LatControlAngle, STEER_ANGLE_SATURATION_THRESHOLD
from openpilot.selfdrive.controls.lib.latcontrol_torque import LatControlTorque
from openpilot.selfdrive.controls.lib.longcontrol import LongControl
from openpilot.selfdrive.locationd.helpers import PoseCalibrator, Pose

from openpilot.sunnypilot.livedelay.helpers import get_lat_delay
from openpilot.sunnypilot.modeld.modeld_base import ModelStateBase
from openpilot.sunnypilot.selfdrive.controls.controlsd_ext import ControlsExt

State = log.SelfdriveState.OpenpilotState
LaneChangeState = log.LaneChangeState
LaneChangeDirection = log.LaneChangeDirection
LaneCenteringSourceEnum = log.ControlsState.LaneCenteringSource

ACTUATOR_FIELDS = tuple(car.CarControl.Actuators.schema.fields.keys())

CENTERING_LOOKAHEAD_M = 10.0
CENTERING_MAX_OFFSET_M = 0.5
CENTERING_MIN_OFFSET_M = 0.03
CENTERING_LANE_WIDTH_MIN_M = 2.4
CENTERING_LANE_WIDTH_MAX_M = 5.0
CENTERING_PROB_ENTER_THRESHOLD = 0.6
CENTERING_PROB_EXIT_THRESHOLD = 0.5
CENTERING_MIN_SPEED_MS = 1.0
CENTERING_MAX_CURVATURE_DELTA = 0.01
CENTERING_MIN_DISPLAY_DELTA = 5e-5
CENTERING_RATE_LIMIT_M_PER_S = 0.1
CENTERING_MIN_EDGE_DISTANCE_M = 0.3048  # 1 ft
CENTERING_EDGE_STD_MAX_ENTER = 1.0
CENTERING_EDGE_STD_MAX_EXIT = 1.2
CENTERING_EDGE_STD_SAMPLES = 10
CENTERING_EDGE_MIN_CORRECTION_M = 0.01

LANE_CENTERING_SOURCE_MAP = {
  None: LaneCenteringSourceEnum.none,
  "lane": LaneCenteringSourceEnum.lane,
  "edge": LaneCenteringSourceEnum.edge,
}


class Controls(ControlsExt, ModelStateBase):
  def __init__(self) -> None:
    self.params = Params()
    cloudlog.info("controlsd is waiting for CarParams")
    self.CP = messaging.log_from_bytes(self.params.get("CarParams", block=True), car.CarParams)
    cloudlog.info("controlsd got CarParams")

    # Initialize sunnypilot controlsd extension and base model state
    ControlsExt.__init__(self, self.CP, self.params)
    ModelStateBase.__init__(self)

    self.CI = interfaces[self.CP.carFingerprint](self.CP, self.CP_SP)

    self.sm = messaging.SubMaster(['liveParameters', 'liveTorqueParameters', 'modelV2', 'selfdriveState',
                                   'liveCalibration', 'livePose', 'longitudinalPlan', 'carState', 'carOutput',
                                   'driverMonitoringState', 'onroadEvents', 'driverAssistance', 'liveDelay'] + self.sm_services_ext,
                                  poll='selfdriveState')
    self.pm = messaging.PubMaster(['carControl', 'controlsState'] + self.pm_services_ext)

    self.steer_limited_by_safety = False
    self.curvature = 0.0
    self.desired_curvature = 0.0
    self.centering_correction = 0.0
    self.centering_active = False
    self.centering_offset_m = 0.0
    self.centering_source: str | None = None
    self._lanes_reliable = False
    self._edges_reliable = False

    self.pose_calibrator = PoseCalibrator()
    self.calibrated_pose: Pose | None = None

    self.LoC = LongControl(self.CP)
    self.VM = VehicleModel(self.CP)
    self.LaC: LatControl
    if self.CP.steerControlType == car.CarParams.SteerControlType.angle:
      self.LaC = LatControlAngle(self.CP, self.CP_SP, self.CI)
    elif self.CP.lateralTuning.which() == 'pid':
      self.LaC = LatControlPID(self.CP, self.CP_SP, self.CI)
    elif self.CP.lateralTuning.which() == 'torque':
      self.LaC = LatControlTorque(self.CP, self.CP_SP, self.CI)

  def update(self):
    self.sm.update(15)
    if self.sm.updated["liveCalibration"]:
      self.pose_calibrator.feed_live_calib(self.sm['liveCalibration'])
    if self.sm.updated["livePose"]:
      device_pose = Pose.from_live_pose(self.sm['livePose'])
      self.calibrated_pose = self.pose_calibrator.build_calibrated_pose(device_pose)

  def state_control(self):
    CS = self.sm['carState']

    # Update VehicleModel
    lp = self.sm['liveParameters']
    x = max(lp.stiffnessFactor, 0.1)
    sr = max(lp.steerRatio, 0.1)
    self.VM.update_params(x, sr)

    steer_angle_without_offset = math.radians(CS.steeringAngleDeg - lp.angleOffsetDeg)
    self.curvature = -self.VM.calc_curvature(steer_angle_without_offset, CS.vEgo, lp.roll)

    # Update Torque Params
    if self.CP.lateralTuning.which() == 'torque':
      torque_params = self.sm['liveTorqueParameters']
      if self.sm.all_checks(['liveTorqueParameters']) and torque_params.useParams:
        self.LaC.update_live_torque_params(torque_params.latAccelFactorFiltered, torque_params.latAccelOffsetFiltered,
                                           torque_params.frictionCoefficientFiltered)

        self.LaC.extension.update_limits()

      self.LaC.extension.update_model_v2(self.sm['modelV2'])

      self.lat_delay = get_lat_delay(self.params, self.sm["liveDelay"].lateralDelay)
      self.LaC.extension.update_lateral_lag(self.lat_delay)

    long_plan = self.sm['longitudinalPlan']
    model_v2 = self.sm['modelV2']

    CC = car.CarControl.new_message()
    CC.enabled = self.sm['selfdriveState'].enabled

    # Check which actuators can be enabled
    standstill = abs(CS.vEgo) <= max(self.CP.minSteerSpeed, 0.3) or CS.standstill

    # Get which state to use for active lateral control
    _lat_active = self.get_lat_active(self.sm)

    CC.latActive = _lat_active and not CS.steerFaultTemporary and not CS.steerFaultPermanent and \
                   (not standstill or self.CP.steerAtStandstill)
    CC.longActive = CC.enabled and not any(e.overrideLongitudinal for e in self.sm['onroadEvents']) and \
                    (self.CP.openpilotLongitudinalControl or not self.CP_SP.pcmCruiseSpeed)

    actuators = CC.actuators
    actuators.longControlState = self.LoC.long_control_state

    # Enable blinkers while lane changing
    if model_v2.meta.laneChangeState != LaneChangeState.off:
      CC.leftBlinker = model_v2.meta.laneChangeDirection == LaneChangeDirection.left
      CC.rightBlinker = model_v2.meta.laneChangeDirection == LaneChangeDirection.right

    if not CC.latActive:
      self.LaC.reset()
    if not CC.longActive:
      self.LoC.reset()

    # accel PID loop
    pid_accel_limits = self.CI.get_pid_accel_limits(self.CP, CS.vEgo, CS.vCruise * CV.KPH_TO_MS)
    actuators.accel = float(self.LoC.update(CC.longActive, CS, long_plan.aTarget, long_plan.shouldStop, pid_accel_limits))

    # Steering PID loop and lateral MPC
    # Reset desired curvature to current to avoid violating the limits on engage
    base_desired_curvature = model_v2.action.desiredCurvature if CC.latActive else self.curvature

    target_offset_m = 0.0
    centering_available = False
    self.centering_source = None
    if CC.latActive and self._lane_centering_enabled():
      target_offset_m, centering_available = self._calculate_centering_target_offset(model_v2, CS.vEgo)

    if not CC.latActive:
      self.centering_offset_m = 0.0
    else:
      rate_step = CENTERING_RATE_LIMIT_M_PER_S * DT_CTRL
      offset_error = target_offset_m - self.centering_offset_m
      if offset_error > rate_step:
        offset_error = rate_step
      elif offset_error < -rate_step:
        offset_error = -rate_step
      self.centering_offset_m += offset_error
      self.centering_offset_m = max(-CENTERING_MAX_OFFSET_M, min(self.centering_offset_m, CENTERING_MAX_OFFSET_M))

      reset_threshold = CENTERING_EDGE_MIN_CORRECTION_M if self.centering_source == "edge" else CENTERING_MIN_OFFSET_M
      if not centering_available and abs(self.centering_offset_m) < reset_threshold and abs(target_offset_m) < reset_threshold:
        self.centering_offset_m = 0.0

    min_offset_for_curvature = CENTERING_EDGE_MIN_CORRECTION_M if self.centering_source == "edge" else CENTERING_MIN_OFFSET_M
    centering_delta = self._offset_to_curvature(self.centering_offset_m, min_offset_for_curvature) if centering_available else 0.0
    new_desired_curvature = base_desired_curvature + centering_delta
    self.desired_curvature, curvature_limited = clip_curvature(CS.vEgo, self.desired_curvature, new_desired_curvature, lp.roll)

    if CC.latActive:
      self.centering_correction = self.desired_curvature - base_desired_curvature
      active_offset_threshold = CENTERING_EDGE_MIN_CORRECTION_M if self.centering_source == "edge" else CENTERING_MIN_OFFSET_M
      self.centering_active = abs(self.centering_offset_m) > active_offset_threshold and \
                              abs(self.centering_correction) > CENTERING_MIN_DISPLAY_DELTA
      if not self.centering_active:
        self.centering_correction = 0.0
    else:
      self.centering_offset_m = 0.0
      self.centering_correction = 0.0
      self.centering_active = False
      self.centering_source = None

    actuators.curvature = self.desired_curvature
    steer, steeringAngleDeg, lac_log = self.LaC.update(CC.latActive, CS, self.VM, lp,
                                                       self.steer_limited_by_safety, self.desired_curvature,
                                                       self.calibrated_pose, curvature_limited)  # TODO what if not available
    actuators.torque = float(steer)
    actuators.steeringAngleDeg = float(steeringAngleDeg)
    # Ensure no NaNs/Infs
    for p in ACTUATOR_FIELDS:
      attr = getattr(actuators, p)
      if not isinstance(attr, Number):
        continue

      if not math.isfinite(attr):
        cloudlog.error(f"actuators.{p} not finite {actuators.to_dict()}")
        setattr(actuators, p, 0.0)

    return CC, lac_log

  def _lane_centering_enabled(self) -> bool:
    return self.CP.carFingerprint == HYUNDAI_CAR.KIA_EV9 and \
           self.CP.steerControlType == car.CarParams.SteerControlType.angle

  def _lane_y_at_distance(self, lane_line, distance_m: float) -> float | None:
    xs = lane_line.x
    ys = lane_line.y
    if len(xs) == 0 or len(ys) == 0:
      return None

    accum = 0.0
    count = 0
    for x_val, y_val in zip(xs, ys):
      if x_val > distance_m:
        break
      accum += y_val
      count += 1

    if count == 0:
      return float(ys[0])

    return accum / count

  def _calculate_centering_target_offset(self, model_v2, v_ego: float) -> tuple[float, bool]:
    self.centering_source = None
    lanes_available, lane_offset = self._calculate_lane_offset(model_v2, v_ego)
    if lanes_available:
      if lane_offset is not None:
        self.centering_source = "lane"
        return lane_offset, True
      return 0.0, False

    edge_offset = self._calculate_edge_offset(model_v2, v_ego)
    if edge_offset is not None:
      self.centering_source = "edge"
      return edge_offset, True

    return 0.0, False

  def _calculate_lane_offset(self, model_v2, v_ego: float) -> tuple[bool, float | None]:
    if v_ego < CENTERING_MIN_SPEED_MS:
      return False, None

    if len(model_v2.laneLines) < 3 or len(model_v2.laneLineProbs) < 3:
      self._lanes_reliable = False
      return False, None

    left_prob = model_v2.laneLineProbs[1]
    right_prob = model_v2.laneLineProbs[2]
    prob_threshold = CENTERING_PROB_ENTER_THRESHOLD if not self._lanes_reliable else CENTERING_PROB_EXIT_THRESHOLD
    if left_prob < prob_threshold or right_prob < prob_threshold:
      self._lanes_reliable = False
      return False, None

    left_y_raw = self._lane_y_at_distance(model_v2.laneLines[1], CENTERING_LOOKAHEAD_M)
    right_y_raw = self._lane_y_at_distance(model_v2.laneLines[2], CENTERING_LOOKAHEAD_M)
    left_y, right_y = self._extract_signed_boundaries(left_y_raw, right_y_raw)
    if left_y is None or right_y is None:
      self._lanes_reliable = False
      return False, None

    lane_width = left_y - right_y
    if lane_width < CENTERING_LANE_WIDTH_MIN_M or lane_width > CENTERING_LANE_WIDTH_MAX_M:
      self._lanes_reliable = False
      return False, None

    center_offset = 0.5 * (left_y + right_y)
    if abs(center_offset) < CENTERING_MIN_OFFSET_M:
      self._lanes_reliable = True
      return True, None

    limited_offset = max(-CENTERING_MAX_OFFSET_M, min(center_offset, CENTERING_MAX_OFFSET_M))
    self._lanes_reliable = True
    return True, limited_offset

  def _calculate_edge_offset(self, model_v2, v_ego: float) -> float | None:
    if v_ego < CENTERING_MIN_SPEED_MS:
      self._edges_reliable = False
      return None

    if len(model_v2.roadEdges) < 2:
      self._edges_reliable = False
      return None

    left_y_raw = self._lane_y_at_distance(model_v2.roadEdges[0], CENTERING_LOOKAHEAD_M)
    right_y_raw = self._lane_y_at_distance(model_v2.roadEdges[1], CENTERING_LOOKAHEAD_M)

    left_y, right_y = self._extract_signed_boundaries(left_y_raw, right_y_raw)
    if left_y is None and right_y is None:
      self._edges_reliable = False
      return None

    edge_std = self._edge_std_average(model_v2.roadEdgeStds)
    std_threshold = CENTERING_EDGE_STD_MAX_ENTER if not self._edges_reliable else CENTERING_EDGE_STD_MAX_EXIT
    if edge_std is not None and edge_std > std_threshold:
      self._edges_reliable = False
      return None

    constraints_min = -CENTERING_MAX_OFFSET_M
    constraints_max = CENTERING_MAX_OFFSET_M

    if left_y is not None:
      constraints_max = min(constraints_max, left_y - CENTERING_MIN_EDGE_DISTANCE_M)
    if right_y is not None:
      constraints_min = max(constraints_min, CENTERING_MIN_EDGE_DISTANCE_M + right_y)

    if constraints_min > constraints_max:
      self._edges_reliable = False
      return None

    candidates: list[float] = []
    if left_y is not None:
      candidates.append(left_y)
    if right_y is not None:
      candidates.append(right_y)

    close_candidates = [y for y in candidates if abs(y) < CENTERING_MIN_EDGE_DISTANCE_M]
    if not close_candidates:
      self._edges_reliable = True
      return None

    if len(close_candidates) >= 2 and left_y is not None and right_y is not None:
      self._edges_reliable = False
      return None

    closest_y = min(close_candidates, key=lambda y: abs(y))
    needed_shift = CENTERING_MIN_EDGE_DISTANCE_M - abs(closest_y)
    correction = -math.copysign(needed_shift, closest_y)

    if correction < constraints_min or correction > constraints_max:
      # No feasible correction that preserves minimum distance to both edges
      self._edges_reliable = False
      return None

    if abs(correction) < CENTERING_EDGE_MIN_CORRECTION_M:
      self._edges_reliable = True
      return None

    self._edges_reliable = True
    return correction

  def _edge_std_average(self, stds: list[float]) -> float | None:
    if not stds:
      return None
    total = 0.0
    count = 0
    for value in stds:
      if not isinstance(value, (int, float)):
        continue
      total += float(value)
      count += 1
      if count >= CENTERING_EDGE_STD_SAMPLES:
        break
    if count == 0:
      return None
    return total / count

  def _extract_signed_boundaries(self, first: float | None, second: float | None) -> tuple[float | None, float | None]:
    positives = [v for v in (first, second) if v is not None and v > 0.0]
    negatives = [v for v in (first, second) if v is not None and v < 0.0]

    left_val = max(positives) if positives else None
    right_val = min(negatives) if negatives else None

    if left_val is None and right_val is not None:
      right_val = min((v for v in (first, second) if v is not None), default=None)
    if right_val is None and left_val is not None:
      left_val = max((v for v in (first, second) if v is not None), default=None)

    return left_val, right_val

  def _offset_to_curvature(self, offset_m: float, min_offset: float) -> float:
    if abs(offset_m) < min_offset:
      return 0.0

    curvature_delta = (2.0 * offset_m) / (CENTERING_LOOKAHEAD_M ** 2)
    if curvature_delta > CENTERING_MAX_CURVATURE_DELTA:
      curvature_delta = CENTERING_MAX_CURVATURE_DELTA
    elif curvature_delta < -CENTERING_MAX_CURVATURE_DELTA:
      curvature_delta = -CENTERING_MAX_CURVATURE_DELTA

    if abs(curvature_delta) < CENTERING_MIN_DISPLAY_DELTA:
      return 0.0

    return curvature_delta

  def publish(self, CC, lac_log):
    CS = self.sm['carState']

    if not self.centering_active:
      self.centering_correction = 0.0

    # Orientation and angle rates can be useful for carcontroller
    # Only calibrated (car) frame is relevant for the carcontroller
    CC.currentCurvature = self.curvature
    if self.calibrated_pose is not None:
      CC.orientationNED = self.calibrated_pose.orientation.xyz.tolist()
      CC.angularVelocity = self.calibrated_pose.angular_velocity.xyz.tolist()

    CC.cruiseControl.override = CC.enabled and not CC.longActive and (self.CP.openpilotLongitudinalControl or not self.CP_SP.pcmCruiseSpeed)
    CC.cruiseControl.cancel = CS.cruiseState.enabled and (not CC.enabled or not self.CP.pcmCruise)
    CC.cruiseControl.resume = CC.enabled and CS.cruiseState.standstill and not self.sm['longitudinalPlan'].shouldStop

    hudControl = CC.hudControl
    hudControl.setSpeed = float(CS.vCruiseCluster * CV.KPH_TO_MS)
    hudControl.speedVisible = CC.enabled
    hudControl.lanesVisible = CC.enabled
    hudControl.leadVisible = self.sm['longitudinalPlan'].hasLead
    hudControl.leadDistanceBars = self.sm['selfdriveState'].personality.raw + 1
    hudControl.visualAlert = self.sm['selfdriveState'].alertHudVisual

    hudControl.rightLaneVisible = True
    hudControl.leftLaneVisible = True
    if self.sm.valid['driverAssistance']:
      hudControl.leftLaneDepart = self.sm['driverAssistance'].leftLaneDeparture
      hudControl.rightLaneDepart = self.sm['driverAssistance'].rightLaneDeparture

    if self.sm['selfdriveState'].active:
      CO = self.sm['carOutput']
      if self.CP.steerControlType == car.CarParams.SteerControlType.angle:
        self.steer_limited_by_safety = abs(CC.actuators.steeringAngleDeg - CO.actuatorsOutput.steeringAngleDeg) > \
                                              STEER_ANGLE_SATURATION_THRESHOLD
      else:
        self.steer_limited_by_safety = abs(CC.actuators.torque - CO.actuatorsOutput.torque) > 1e-2

    # TODO: both controlsState and carControl valids should be set by
    #       sm.all_checks(), but this creates a circular dependency

    # controlsState
    dat = messaging.new_message('controlsState')
    dat.valid = CS.canValid
    cs = dat.controlsState

    cs.curvature = self.curvature
    cs.longitudinalPlanMonoTime = self.sm.logMonoTime['longitudinalPlan']
    cs.lateralPlanMonoTime = self.sm.logMonoTime['modelV2']
    cs.desiredCurvature = self.desired_curvature
    cs.laneCenteringActive = bool(self.centering_active)
    cs.laneCenteringOffset = float(self.centering_offset_m if self.centering_active else 0.0)
    cs.laneCenteringSource = LANE_CENTERING_SOURCE_MAP.get(self.centering_source, LaneCenteringSourceEnum.none)
    cs.longControlState = self.LoC.long_control_state
    cs.upAccelCmd = float(self.LoC.pid.p)
    cs.uiAccelCmd = float(self.LoC.pid.i)
    cs.ufAccelCmd = float(self.LoC.pid.f)
    cs.forceDecel = bool((self.sm['driverMonitoringState'].awarenessStatus < 0.) or
                         (self.sm['selfdriveState'].state == State.softDisabling))

    lat_tuning = self.CP.lateralTuning.which()
    if self.CP.steerControlType == car.CarParams.SteerControlType.angle:
      cs.lateralControlState.angleState = lac_log
    elif lat_tuning == 'pid':
      cs.lateralControlState.pidState = lac_log
    elif lat_tuning == 'torque':
      cs.lateralControlState.torqueState = lac_log

    self.pm.send('controlsState', dat)

    # carControl
    cc_send = messaging.new_message('carControl')
    cc_send.valid = CS.canValid
    cc_send.carControl = CC
    self.pm.send('carControl', cc_send)

  def params_thread(self, evt):
    while not evt.is_set():
      self.get_params_sp()

      time.sleep(0.1)

  def run(self):
    rk = Ratekeeper(100, print_delay_threshold=None)
    e = threading.Event()
    t = threading.Thread(target=self.params_thread, args=(e,))
    try:
      t.start()
      while True:
        self.update()
        CC, lac_log = self.state_control()
        self.publish(CC, lac_log)
        self.run_ext(self.sm, self.pm)
        rk.monitor_time()
    finally:
      e.set()
      t.join()


def main():
  config_realtime_process(4, Priority.CTRL_HIGH)
  controls = Controls()
  controls.run()


if __name__ == "__main__":
  main()
