#!/usr/bin/env python3
import math
import time
import threading
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
CENTERING_MIN_OFFSET_M = 0.015
CENTERING_LANE_WIDTH_MIN_M = 2.4
CENTERING_LANE_WIDTH_MAX_M = 5.0
CENTERING_PROB_ENTER_THRESHOLD = 0.6
CENTERING_PROB_EXIT_THRESHOLD = 0.5
CENTERING_MIN_SPEED_MS = 1.0
CENTERING_MAX_CURVATURE_DELTA = 0.01
CENTERING_MIN_DISPLAY_DELTA = 1e-6
CENTERING_RATE_LIMIT_M_PER_S = 0.08
CENTERING_CURVATURE_MIN_OFFSET_M = 0.008
CENTERING_CURVATURE_GAIN = 0.55
CENTERING_EDGE_STD_MAX_ENTER = 1.0
CENTERING_EDGE_STD_MAX_EXIT = 1.2
CENTERING_EDGE_STD_SAMPLES = 10
CENTERING_DISTANCE_RATIO_MAX = 3.0
CENTERING_DEADBAND_ENTER_M = 0.045
CENTERING_DEADBAND_EXIT_M = 0.02
CENTERING_SIGN_FLIP_MIN_M = 0.12
CENTERING_TARGET_FILTER_TC = 0.6
CENTERING_EDGE_MARGIN_M = 0.14
CENTERING_SOFT_GAIN_MIN = 0.3
CENTERING_SOFT_GAIN_THRESHOLD_M = 0.08
CENTERING_POST_CROSS_SLACK_M = 0.025
CENTERING_SLACK_DECAY_RATE_M_PER_S = 0.02
CENTERING_CURVE_ATTENUATION_START = 0.0025
CENTERING_CURVE_ATTENUATION_FULL = 0.0075
CENTERING_CURVE_MIN_SCALE = 0.35
CENTERING_STATUS_HOLD_S = 1.0
EDGE_CLEARANCE_MIN_M = 0.381

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
    self._centering_last_source: str | None = None
    self._lane_reliability: dict[int, bool] = {}
    self._edges_reliable = False
    self._centering_lock_sign = 0
    self._centering_target_filtered = 0.0
    self._centering_cross_slack = 0.0
    self._advanced_centering_enabled = self.params.get_bool("AdvancedLaneCentering")
    self._prev_lat_active = False
    self._centering_tracking_ready = False
    self._centering_status_hold = 0.0
    self._centering_source_hold = 0.0
    self.edge_clearance_active = False
    self.edge_clearance_offset_m = 0.0

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

    target_mode: str | None = None
    target_offset_m = 0.0
    centering_available = False
    centering_source: str | None = None
    tracking_ready = False
    edge_clearance_active = False
    advanced_centering_enabled = self._advanced_centering_enabled
    centering_released = not advanced_centering_enabled
    if CC.latActive and not self._prev_lat_active:
      self._advanced_centering_enabled = self.params.get_bool("AdvancedLaneCentering")
    if CC.latActive and self._lane_centering_enabled() and advanced_centering_enabled:
      self._centering_tracking_ready = False
      lane_offset_raw, centering_available, centering_source, edge_offset_raw, edge_active = self._calculate_centering_target_offset(model_v2, CS.vEgo)
      tracking_ready = self._centering_tracking_ready
      if centering_available:
        target_mode = "lane"
        filtered_target = self._filter_centering_target(lane_offset_raw)
        target_offset_m, centering_available, centering_released = self._apply_offset_hysteresis(filtered_target, True)
      elif edge_active:
        target_mode = "edge"
        filtered_target = self._filter_centering_target(edge_offset_raw)
        target_offset_m, centering_available, _ = self._apply_offset_hysteresis(filtered_target, True)
        edge_clearance_active = centering_available
        centering_released = False
      else:
        filtered_target = 0.0
        self._centering_target_filtered = 0.0

    if not CC.latActive:
      self.centering_offset_m = 0.0
      self._centering_lock_sign = 0
      self._centering_target_filtered = 0.0
      self.centering_source = None
      self._centering_last_source = None
      self._centering_status_hold = 0.0
      self._centering_source_hold = 0.0
      self._centering_tracking_ready = False
      self.edge_clearance_active = False
      self.edge_clearance_offset_m = 0.0
    else:
      if centering_released:
        self.centering_offset_m = 0.0
        self._centering_target_filtered = 0.0
      rate_step = CENTERING_RATE_LIMIT_M_PER_S * DT_CTRL
      offset_error = target_offset_m - self.centering_offset_m
      if offset_error > rate_step:
        offset_error = rate_step
      elif offset_error < -rate_step:
        offset_error = -rate_step
      self.centering_offset_m += offset_error
      self.centering_offset_m = max(-CENTERING_MAX_OFFSET_M, min(self.centering_offset_m, CENTERING_MAX_OFFSET_M))

      reset_threshold = CENTERING_MIN_OFFSET_M
      if not centering_available and abs(self.centering_offset_m) < reset_threshold and abs(target_offset_m) < reset_threshold:
        self.centering_offset_m = 0.0

    min_offset_for_curvature = CENTERING_CURVATURE_MIN_OFFSET_M
    centering_delta = self._offset_to_curvature(self.centering_offset_m, min_offset_for_curvature, base_desired_curvature) if centering_available else 0.0
    new_desired_curvature = base_desired_curvature + centering_delta
    self.desired_curvature, curvature_limited = clip_curvature(CS.vEgo, self.desired_curvature, new_desired_curvature, lp.roll)

    if CC.latActive:
      self.centering_correction = self.desired_curvature - base_desired_curvature
      offset_mag = abs(self.centering_offset_m)
      correction_mag = abs(self.centering_correction)

      if advanced_centering_enabled and self._lane_centering_enabled() and target_mode == "lane":
        if tracking_ready:
          self._centering_status_hold = CENTERING_STATUS_HOLD_S
          self._centering_source_hold = CENTERING_STATUS_HOLD_S
        else:
          self._centering_status_hold = max(0.0, self._centering_status_hold - DT_CTRL)
          self._centering_source_hold = max(0.0, self._centering_source_hold - DT_CTRL)

        engaged = tracking_ready or centering_available or \
                  offset_mag > (CENTERING_MIN_OFFSET_M / 2) or \
                  correction_mag > CENTERING_MIN_DISPLAY_DELTA or \
                  self._centering_status_hold > 0.0

        self.centering_active = engaged

        if centering_source is not None:
          self.centering_source = centering_source
          self._centering_last_source = centering_source
        elif self._centering_source_hold > 0.0 and self._centering_last_source is not None:
          self.centering_source = self._centering_last_source
        else:
          if self._centering_source_hold <= 0.0:
            self._centering_last_source = None
          self.centering_source = None

        if not engaged and self._centering_status_hold <= 0.0:
          self.centering_correction = 0.0
        self.edge_clearance_active = False
        self.edge_clearance_offset_m = 0.0
      else:
        if target_mode == "edge" and edge_clearance_active:
          self.centering_active = False
          self.centering_source = None
          self._centering_last_source = None
          self._centering_status_hold = 0.0
          self._centering_source_hold = 0.0
          self.edge_clearance_active = True
          self.edge_clearance_offset_m = self.centering_offset_m
        else:
          self.centering_active = False
          self.centering_correction = 0.0
          self.centering_source = None
          self._centering_last_source = None
          self._centering_status_hold = 0.0
          self._centering_source_hold = 0.0
          self.edge_clearance_active = False
          self.edge_clearance_offset_m = 0.0
    else:
      self.centering_offset_m = 0.0
      self.centering_correction = 0.0
      self.centering_active = False
      self.centering_source = None
      self._centering_last_source = None
      self._centering_lock_sign = 0
      self._centering_status_hold = 0.0
      self._centering_source_hold = 0.0
      self._centering_tracking_ready = False
      self.edge_clearance_active = False
      self.edge_clearance_offset_m = 0.0

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

    self._prev_lat_active = CC.latActive

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

  def _calculate_centering_target_offset(self, model_v2, v_ego: float) -> tuple[float, bool, str | None, float, bool]:
    if v_ego < CENTERING_MIN_SPEED_MS:
      self._lane_reliability.clear()
      self._edges_reliable = False
      self._centering_tracking_ready = False
      return 0.0, False, None, 0.0, False

    left_candidates, right_candidates, left_edge_dist, right_edge_dist = self._collect_boundary_candidates(model_v2)

    left_boundary, left_source = self._select_closest_boundary(left_candidates, "left")
    right_boundary, right_source = self._select_closest_boundary(right_candidates, "right")

    edge_offset, edge_active = self._edge_clearance_target(left_edge_dist, right_edge_dist)

    if left_boundary is None or right_boundary is None:
      self._centering_tracking_ready = False
      return 0.0, False, None, edge_offset, edge_active

    lane_width = left_boundary - right_boundary
    if lane_width < CENTERING_LANE_WIDTH_MIN_M or lane_width > CENTERING_LANE_WIDTH_MAX_M:
      self._centering_tracking_ready = False
      return 0.0, False, None, edge_offset, edge_active

    left_distance = max(left_boundary, CENTERING_MIN_OFFSET_M)
    right_distance = max(abs(right_boundary), CENTERING_MIN_OFFSET_M)
    ratio = max(left_distance, right_distance) / max(min(left_distance, right_distance), CENTERING_MIN_OFFSET_M)
    if ratio > CENTERING_DISTANCE_RATIO_MAX:
      self._centering_tracking_ready = False
      return 0.0, False, None, edge_offset, edge_active

    center_offset = 0.5 * (left_boundary + right_boundary)
    center_offset = max(-CENTERING_MAX_OFFSET_M, min(center_offset, CENTERING_MAX_OFFSET_M))

    self._centering_tracking_ready = True

    if abs(center_offset) < CENTERING_MIN_OFFSET_M:
      return 0.0, False, None, edge_offset, edge_active

    left_distance = left_boundary
    right_distance = abs(right_boundary)
    if left_distance <= right_distance:
      primary_source = left_source
      secondary_source = right_source
    else:
      primary_source = right_source
      secondary_source = left_source

    source = primary_source or secondary_source

    return center_offset, True, source, 0.0, False

  def _apply_offset_hysteresis(self, target_offset_m: float, available: bool) -> tuple[float, bool, bool]:
    if not available:
      self._centering_lock_sign = 0
      self._centering_cross_slack = 0.0
      return 0.0, False, False

    magnitude = abs(target_offset_m)
    if self._centering_cross_slack > 0.0:
      decay = CENTERING_SLACK_DECAY_RATE_M_PER_S * DT_CTRL
      self._centering_cross_slack = max(0.0, self._centering_cross_slack - decay)
    if magnitude < CENTERING_DEADBAND_EXIT_M:
      if self._centering_lock_sign != 0:
        self._centering_lock_sign = 0
      self._centering_cross_slack = 0.0
      return 0.0, False, False

    desired_sign = 1 if target_offset_m > 0.0 else -1

    if self._centering_lock_sign == 0:
      threshold = CENTERING_DEADBAND_ENTER_M + self._centering_cross_slack
      if magnitude < threshold:
        return 0.0, False, False
      self._centering_lock_sign = desired_sign
      self._centering_cross_slack = 0.0
    else:
      if desired_sign != self._centering_lock_sign:
        self._centering_lock_sign = 0
        self._centering_cross_slack = CENTERING_POST_CROSS_SLACK_M
        return 0.0, False, True

    locked_offset = self._centering_lock_sign * magnitude
    return locked_offset, True, False

  def _filter_centering_target(self, target_offset_m: float) -> float:
    alpha = DT_CTRL / (CENTERING_TARGET_FILTER_TC + DT_CTRL)
    self._centering_target_filtered += alpha * (target_offset_m - self._centering_target_filtered)
    if abs(target_offset_m) < CENTERING_MIN_OFFSET_M / 2 and abs(self._centering_target_filtered) < CENTERING_MIN_OFFSET_M / 2:
      self._centering_target_filtered = 0.0
    return self._centering_target_filtered

  def _collect_boundary_candidates(self, model_v2) -> tuple[list[tuple[str, float]], list[tuple[str, float]], float | None, float | None]:
    left_candidates: list[tuple[str, float]] = []
    right_candidates: list[tuple[str, float]] = []
    left_edge_distance: float | None = None
    right_edge_distance: float | None = None

    lane_lines = model_v2.laneLines
    lane_probs = model_v2.laneLineProbs
    lane_count = min(len(lane_lines), len(lane_probs))
    if lane_count == 0:
      self._lane_reliability.clear()
    else:
      for idx in range(lane_count):
        lane_val, lane_ok = self._lane_boundary(idx, lane_lines[idx], lane_probs[idx])
        if lane_ok and lane_val is not None:
          if lane_val > 0.0:
            left_candidates.append(("lane", float(lane_val)))
          elif lane_val < 0.0:
            right_candidates.append(("lane", float(lane_val)))

    if len(model_v2.roadEdges) < 2:
      self._edges_reliable = False
    else:
      edge_std = self._edge_std_average(model_v2.roadEdgeStds)
      std_threshold = CENTERING_EDGE_STD_MAX_EXIT if self._edges_reliable else CENTERING_EDGE_STD_MAX_ENTER
      if edge_std is not None and edge_std > std_threshold:
        self._edges_reliable = False
      else:
        self._edges_reliable = True
        for edge_reader in model_v2.roadEdges:
          edge_val, edge_ok = self._edge_boundary(edge_reader)
          if edge_ok and edge_val is not None:
            if edge_val > 0.0:
              if left_edge_distance is None or edge_val < left_edge_distance:
                left_edge_distance = float(edge_val)
            elif edge_val < 0.0:
              if right_edge_distance is None or abs(edge_val) < abs(right_edge_distance):
                right_edge_distance = float(edge_val)

    return left_candidates, right_candidates, left_edge_distance, right_edge_distance

  def _lane_boundary(self, index: int, lane_line, probability: float) -> tuple[float | None, bool]:
    reliable = self._lane_reliability.get(index, False)
    threshold = CENTERING_PROB_EXIT_THRESHOLD if reliable else CENTERING_PROB_ENTER_THRESHOLD
    if probability < threshold:
      self._lane_reliability[index] = False
      return None, False

    y_val = self._lane_y_at_distance(lane_line, CENTERING_LOOKAHEAD_M)
    if y_val is None:
      self._lane_reliability[index] = False
      return None, False

    if abs(y_val) < CENTERING_MIN_OFFSET_M:
      self._lane_reliability[index] = reliable
      return None, False

    self._lane_reliability[index] = True
    return float(y_val), True

  def _edge_boundary(self, road_edge) -> tuple[float | None, bool]:
    if not self._edges_reliable:
      return None, False

    y_val = self._lane_y_at_distance(road_edge, CENTERING_LOOKAHEAD_M)
    if y_val is None or abs(y_val) < CENTERING_MIN_OFFSET_M:
      return None, False

    return float(y_val), True

  def _edge_clearance_target(self, left_edge: float | None, right_edge: float | None) -> tuple[float, bool]:
    left_violation = 0.0
    right_violation = 0.0
    if left_edge is not None and left_edge > 0.0 and left_edge < EDGE_CLEARANCE_MIN_M:
      left_violation = EDGE_CLEARANCE_MIN_M - left_edge
    if right_edge is not None and right_edge < 0.0 and abs(right_edge) < EDGE_CLEARANCE_MIN_M:
      right_violation = EDGE_CLEARANCE_MIN_M - abs(right_edge)

    if left_violation <= 0.0 and right_violation <= 0.0:
      return 0.0, False

    if left_violation >= right_violation:
      offset = -max(left_violation, CENTERING_MIN_OFFSET_M)
    else:
      offset = max(right_violation, CENTERING_MIN_OFFSET_M)

    offset = max(-CENTERING_MAX_OFFSET_M, min(offset, CENTERING_MAX_OFFSET_M))
    return offset, True

  def _select_closest_boundary(self, candidates: list[tuple[str, float]], side: str) -> tuple[float | None, str | None]:
    closest_value: float | None = None
    closest_source: str | None = None

    for source, value in candidates:
      if side == "left" and value <= 0.0:
        continue
      if side == "right" and value >= 0.0:
        continue

      if closest_value is None or abs(value) < abs(closest_value):
        closest_value = value
        closest_source = source
      elif closest_value is not None and math.isclose(abs(value), abs(closest_value), rel_tol=0.0, abs_tol=1e-4):
        if closest_source != "lane" and source == "lane":
          closest_value = value
          closest_source = source

    if closest_value is None:
      return None, None

    return closest_value, closest_source

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

  def _offset_to_curvature(self, offset_m: float, min_offset: float, base_curvature: float) -> float:
    offset_abs = abs(offset_m)
    if offset_abs < min_offset:
      return 0.0

    ratio = min(1.0, offset_abs / CENTERING_SOFT_GAIN_THRESHOLD_M) if CENTERING_SOFT_GAIN_THRESHOLD_M > 0.0 else 1.0
    gain = CENTERING_SOFT_GAIN_MIN + (CENTERING_CURVATURE_GAIN - CENTERING_SOFT_GAIN_MIN) * (ratio ** 1.5)

    curvature_delta = gain * (2.0 * offset_m) / (CENTERING_LOOKAHEAD_M ** 2)

    curve_mag = abs(base_curvature)
    if curve_mag > CENTERING_CURVE_ATTENUATION_START:
      atten_span = max(1e-6, CENTERING_CURVE_ATTENUATION_FULL - CENTERING_CURVE_ATTENUATION_START)
      attenuation_ratio = min(1.0, (curve_mag - CENTERING_CURVE_ATTENUATION_START) / atten_span)
      curve_scale = 1.0 - attenuation_ratio * (1.0 - CENTERING_CURVE_MIN_SCALE)
      curve_scale = max(CENTERING_CURVE_MIN_SCALE, curve_scale)
      curvature_delta *= curve_scale

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
    cs.laneCenteringOffset = float(self.centering_offset_m)
    cs.laneCenteringSource = LANE_CENTERING_SOURCE_MAP.get(self.centering_source, LaneCenteringSourceEnum.none)
    cs.edgeClearanceActive = bool(self.edge_clearance_active)
    cs.edgeClearanceOffset = float(self.edge_clearance_offset_m)
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
