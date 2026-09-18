"""Messaging adapter for EV9 trajectory ownership; never runs optimization."""
import math
import os
import time

import numpy as np

from openpilot.selfdrive.controls.lib.ev9_trajectory import (
  EgoMotion, ExecutionState, TrackingDecision, TrajectoryMode, TrajectoryPlan, TrajectoryTracker, parse_mode,
)


def decode_plan(message):
  """Untrusted/old schema contents cannot become a steering command."""
  try:
    return TrajectoryPlan(
      int(message.planId), int(message.generation), message.sourceMonoTime / 1e9, message.validUntilMonoTime / 1e9,
      (message.originX, message.originY, message.originYaw), message.speed, message.initialCurvature,
      message.initialCommandCurvature, message.minCurvature, message.maxCurvature,
      np.asarray(message.distance), np.column_stack((message.x, message.y)), np.asarray(message.yaw), np.asarray(message.curvature),
      int(message.corridorRevision), bool(message.executionValidated), str(message.frame),
    )
  except (AttributeError, ValueError, TypeError, OverflowError):
    return None


def material_configuration_change(current, anchor):
  """Bound cumulative estimator drift relative to the last frame reset.

  These are frame invalidation thresholds, not steering authority reductions.
  Routine estimator refreshes must retain enough odometry for camera capture time.
  """
  if not all(math.isfinite(value) for value in (*current[:5], *anchor[:5])):
    return True
  return (abs(current[0] - anchor[0]) > .25 or
          any(abs(current[i] - anchor[i]) > .03 * abs(anchor[i]) for i in (1, 2)) or
          abs(current[3] - anchor[3]) > .5 or abs(current[4] - anchor[4]) > .01 or current[5] != anchor[5])


class EV9TrajectoryControl:
  def __init__(self, CP, params):
    self.params = params
    self.mode = parse_mode(params.get('EV9TrajectoryMode'))
    self.tracker = TrajectoryTracker()
    self.motion = EgoMotion()
    self.last_parameter_read = -math.inf
    self.last_message = 0
    self.last_mode = self.mode
    self.last_parameters = None
    self.last_transport = bool(CP.openpilotLongitudinalControl)
    self.decision = TrackingDecision(0.0, False, 'off')
    self.state = None
    self.vehicle_configuration = None
    self.was_active = False
    self.ownership_changed = False

  def update(self, sm, CS, lat_active, VM, lp, previous_curvature, baseline_curvature):
    now = sm.logMonoTime['selfdriveState'] / 1e9 if 'REPLAY' in os.environ else time.monotonic()
    if now - self.last_parameter_read >= 1.0 or now < self.last_parameter_read:
      self.mode = parse_mode(self.params.get('EV9TrajectoryMode'))
      self.last_parameter_read = now
    output = sm['carOutput'].actuatorsOutput
    snapshot_ns = int(getattr(output, 'ev9AngleStateMonoTime', 0))
    snapshot_time = snapshot_ns / 1e9
    filter_angle = float(getattr(output, 'ev9AngleFilterStateDeg', 0.0))
    mdps_angle = float(getattr(output, 'ev9MeasuredAngleDeg', 0.0))
    direct_angle_control = bool(getattr(output, 'ev9DirectAngleControl', False))
    angle_state_valid = bool(getattr(output, 'ev9AngleStateValid', False)) and snapshot_time > 0
    angle_state_valid = angle_state_valid and math.isfinite(filter_angle) and math.isfinite(mdps_angle)
    angle_state_valid = angle_state_valid and 0 <= now - snapshot_time <= .05
    angle_state_valid = angle_state_valid and bool(sm.all_checks(['carOutput'])) and 0 <= now - sm.logMonoTime['carOutput'] / 1e9 <= .05
    # paramsd learns the VM/offset from public SAS, not the controller-selected MDPS signal.
    # Planning uses the same calibrated SAS/VM and aggregate response delay as
    # controls. MDPS/filter telemetry is diagnostic, not a second vehicle model
    # or a mandatory reconstruction of the controller's hidden command history.
    wheel_angle = float(CS.steeringAngleDeg)
    # The curvature-based odometry has a rear-axle kinematic interpretation.
    # Transforming model-space geometry into this frame remains the planner's job.
    measured_curvature = float(VM.calc_curvature(math.radians(wheel_angle - lp.angleOffsetDeg), CS.vEgo, lp.roll))
    previous_generation = self.motion.generation
    pose = self.motion.update(now, CS.vEgo, measured_curvature * CS.vEgo)
    if angle_state_valid:
      self.last_transport = direct_angle_control
    configuration = (VM.sR, VM.cF, VM.cR, lp.angleOffsetDeg, lp.roll, self.last_transport)
    odometry_reset = self.motion.generation != previous_generation
    configuration_reset = self.last_parameters is not None and (
      material_configuration_change(configuration, self.last_parameters) or self.mode != self.last_mode)
    if configuration_reset and not odometry_reset:
      self.motion.generation += 1
    # Retain the anchor between resets so many small changes cannot evade the bounds.
    if self.last_parameters is None or odometry_reset or configuration_reset:
      self.last_parameters = configuration
    self.last_mode = self.mode
    self.vehicle_configuration = (VM.sR, VM.cF, VM.cR, lp.angleOffsetDeg, lp.roll)
    healthy = bool(sm.all_checks(['carState', 'carOutput', 'modelV2', 'liveParameters', 'liveDelay'])) and bool(lp.valid)
    healthy = healthy and all(0 <= now - sm.logMonoTime[service] / 1e9 <= age for service, age in
                              [('carState', .05), ('carOutput', .05), ('modelV2', .25), ('liveParameters', 1.5), ('liveDelay', 1.5)])
    healthy = healthy and not (CS.steerFaultTemporary or CS.steerFaultPermanent)
    self.state = ExecutionState(
      now, pose, float(CS.vEgo), wheel_angle,
      measured_curvature,
      -previous_curvature, float(sm['liveDelay'].lateralDelay), self.motion.generation,
      bool(lat_active), bool(CS.steeringPressed or output.manualSteeringOverride),
      str(sm['modelV2'].meta.laneChangeState) != 'off', str(CS.gearShifter) == 'drive', healthy,
      angle_filter_state_deg=filter_angle if math.isfinite(filter_angle) else 0.0,
      angle_state_valid=angle_state_valid, angle_state_mono_time=snapshot_ns, direct_angle_control=direct_angle_control,
      selected_mdps_angle_deg=mdps_angle if math.isfinite(mdps_angle) else 0.0,
    )
    proposal = None
    revoke = False
    lease, revision = 0.0, 0
    message = sm['ev9TrajectoryPlan']
    stamp = sm.logMonoTime['ev9TrajectoryPlan']
    # Missing plan messages are optional to baseline controls. A stale publisher
    # cannot extend a corridor lease or leave the tracker in control.
    if sm.valid['ev9TrajectoryPlan'] and 0 <= now - stamp / 1e9 <= 0.25:
      lease = message.corridorValidUntilMonoTime / 1e9
      revision = int(message.corridorRevision)
      if stamp != self.last_message:
        self.last_message = stamp
        proposal = decode_plan(message) if message.feasible else None
        revoke = not message.feasible and message.reason in (
          'invalid_execution_state', 'invalid_or_stale_model', 'invalid_or_missing_geometry',
          'invalid_configuration', 'unestablished_frame_alignment', 'unmatched_path_heading', 'invalid_path_time',
          'invalid_lane_metadata', 'invalid_road_metadata', 'missing_model_pose', 'missing_capture_pose',
          'invalid_mount_uncertainty', 'invalid_vehicle_model',
          'crossed_or_missing_boundaries', 'changed_body_outside_observed_space', 'no_observed_body_deviation_room',
          'tracking_complete',
        )
    self.decision = self.tracker.update(
      self.state, baseline_curvature, mode=self.mode, proposal=proposal,
      corridor_revision=revision, corridor_valid_until=lease, revoke=revoke,
    )
    self.ownership_changed = self.was_active != self.decision.active
    self.was_active = self.decision.active
    return self.decision

  def publish(self, pm, messaging):
    if self.state is None or self.mode == TrajectoryMode.OFF:
      return
    data = messaging.new_message('ev9TrajectoryState', valid=True)
    s, out = self.state, data.ev9TrajectoryState
    out.mode, out.generation = int(self.mode), s.generation
    out.sourceMonoTime = int(s.time * 1e9)
    out.x, out.y, out.yaw = s.pose
    out.speed, out.wheelAngleDeg = s.speed, s.wheel_angle_deg
    out.curvature, out.commandCurvature, out.delay = s.curvature, s.command_curvature, s.delay
    out.enabled, out.manual, out.healthy = s.enabled, s.manual, s.healthy
    out.laneChange, out.drive = s.lane_change, s.drive
    out.active, out.reason, out.planId = self.decision.active, self.decision.reason, self.decision.plan_id
    out.lateralError, out.headingError = self.decision.lateral_error, self.decision.heading_error
    out.selectedMdpsAngleDeg = s.selected_mdps_angle_deg
    out.angleFilterStateDeg, out.angleStateValid = s.angle_filter_state_deg, s.angle_state_valid
    out.angleStateMonoTime, out.directAngleControl = s.angle_state_mono_time, s.direct_angle_control
    out.steerRatio, out.tireStiffnessFront, out.tireStiffnessRear, out.angleOffsetDeg, out.roll = self.vehicle_configuration
    pm.send('ev9TrajectoryState', data)
