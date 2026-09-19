"""Small plan/state transport and capture-time pose alignment for the EV9 planner."""
from collections import deque
from dataclasses import replace
import math

from opendbc.car.vehicle_model import VehicleModel
from openpilot.selfdrive.controls.lib.ev9_trajectory import ExecutionState, MAX_STATE_AGE, wrap_angle


def decode_snapshot(message, CP, *, now, message_time, valid, require_eligible=True):
  try:
    stamp = message.sourceMonoTime / 1e9
    if not valid or stamp <= 0 or not all(0 <= now - t <= MAX_STATE_AGE for t in (stamp, message_time)):
      return None
    values = (message.steerRatio, message.tireStiffnessFront, message.tireStiffnessRear, message.angleOffsetDeg, message.roll)
    if not all(math.isfinite(v) for v in values) or min(values[:3]) <= 0:
      return None
    vm = VehicleModel(CP)
    vm.sR, vm.cF, vm.cR = values[:3]
    state = ExecutionState(stamp, (message.x, message.y, message.yaw), message.speed, message.wheelAngleDeg,
                           message.curvature, message.commandCurvature, message.delay, int(message.generation),
                           message.enabled, message.manual, message.laneChange, message.drive, message.healthy,
                           standstill=bool(getattr(message, 'standstill', message.speed == 0)), tracking_active=bool(message.active),
                           speed_limit_mps=float(getattr(message, 'speedLimitKph', 40.)) / 3.6)
    curvature = vm.calc_curvature(math.radians(state.wheel_angle_deg - message.angleOffsetDeg), state.speed, message.roll)
    # Ownership, speed and wheel authority decide whether to plan, not whether
    # a fresh healthy odometry sample can locate an earlier camera capture.
    pose_valid = not state.odometry_rejection(now)
    if not pose_valid or (require_eligible and state.rejection(now)) or not math.isclose(curvature, state.curvature, abs_tol=1e-7, rel_tol=1e-5):
      return None
    if getattr(message, 'modelCapturePoseValid', False):
      capture_time = message.modelCaptureMonoTime / 1e9
      capture_pose = (message.modelCaptureX, message.modelCaptureY, message.modelCaptureYaw)
      if all(math.isfinite(v) for v in capture_pose) and 0 <= stamp - capture_time <= .25:
        state = replace(state, model_capture_time=capture_time, model_capture_pose=capture_pose)
    return state, vm, float(message.roll), float(message.angleOffsetDeg)
  except (AttributeError, TypeError, ValueError, OverflowError, ZeroDivisionError):
    return None


class PoseHistory:
  """Align model capture coordinates to controls without a persistent world map."""
  def __init__(self):
    self.states = deque(maxlen=60)

  def reset(self):
    self.states.clear()

  def add(self, state):
    if state.odometry_rejection(state.time):
      self.reset()
      return
    if self.states and (state.generation != self.states[-1].generation or state.time < self.states[-1].time):
      self.states.clear()
    if not self.states or state.time > self.states[-1].time:
      self.states.append(state)

  def at(self, stamp, generation):
    if not self.states or generation != self.states[-1].generation or not self.states[0].time <= stamp <= self.states[-1].time:
      return None
    previous = self.states[0]
    for current in self.states:
      if stamp == current.time:
        return current.pose
      if previous.time <= stamp < current.time:
        if current.time - previous.time > MAX_STATE_AGE:
          return None
        weight = (stamp - previous.time) / (current.time - previous.time)
        return (previous.pose[0] + weight * (current.pose[0] - previous.pose[0]),
                previous.pose[1] + weight * (current.pose[1] - previous.pose[1]),
                wrap_angle(previous.pose[2] + weight * wrap_angle(current.pose[2] - previous.pose[2])))
      previous = current
    return None


def plan_message(decision, *, generation, source_time):
  source = source_time if math.isfinite(source_time) and source_time >= 0 else 0.
  out = dict(geometryAvailable=decision.geometry_available, feasible=False, executionValidated=False, reason=decision.reason,
             generation=generation, sourceMonoTime=int(source * 1e9), corridorValidUntilMonoTime=0,
             solveTime=decision.solve_time, frame='rear_axle_x_forward_y_left', boundarySource=decision.boundary_source)
  plan = decision.plan
  if plan is not None:
    out.update(feasible=True, executionValidated=plan.execution_validated, planId=plan.plan_id,
               generation=plan.generation, sourceMonoTime=int(plan.source_time * 1e9), validUntilMonoTime=int(plan.valid_until * 1e9),
               corridorRevision=plan.corridor_revision, corridorValidUntilMonoTime=int(plan.valid_until * 1e9),
               originX=plan.origin[0], originY=plan.origin[1], originYaw=plan.origin[2], speed=plan.speed,
               initialCurvature=plan.initial_curvature, initialCommandCurvature=plan.initial_command_curvature,
               minCurvature=plan.min_curvature, maxCurvature=plan.max_curvature, distance=plan.distance.tolist(),
               x=plan.xy[:, 0].tolist(), y=plan.xy[:, 1].tolist(), yaw=plan.yaw.tolist(), curvature=plan.curvature.tolist())
  return out
