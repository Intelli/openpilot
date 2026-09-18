"""Small, rolling EV9 path refiner; the existing controller still drives the car.

The model owns driving intent. This layer can make a small same-direction path
adjustment where observed geometry supports the changed body poses. It does not
infer an intersection, choose another lane, or simulate the CAN controller live.
"""
from dataclasses import dataclass, replace
import math
import time

import numpy as np

from openpilot.selfdrive.controls.lib.ev9_path_geometry import body_inside_observed
from openpilot.selfdrive.controls.lib.ev9_path_frames import CameraMount
from openpilot.selfdrive.controls.lib.ev9_path_history import RearBoundaryHistory
from openpilot.selfdrive.controls.lib.ev9_path_input import PathGeometryConfig, build_path_input
from openpilot.selfdrive.controls.lib.ev9_trajectory import MAX_PLAN_AGE, STEERING_CAPABILITY_DEG, TrajectoryMode, TrajectoryPlan, parse_mode, wrap_angle


# Explicit initial experimental profile, not an inferred physical calibration.
# Mount sensitivity is included in the body envelope below. No angle derating.
MODEL_GEOMETRY = PathGeometryConfig(CameraMount(2.0, 0.0), True, 3.975, 1.04, 1.1, margin=.08, max_deviation=.90)
MOUNT_LONGITUDINAL_UNCERTAINTY = .30
MOUNT_LATERAL_UNCERTAINTY = .10
PLANNING_ANGLE_RATE = 100.0
SOLVE_BUDGET = .05


@dataclass(frozen=True)
class PathPlanningDecision:
  reason: str
  plan: TrajectoryPlan | None = None
  geometry_available: bool = False
  solve_time: float = 0.0
  boundary_source: str = 'none'


def relative_pose(pose, origin):
  dx, dy = pose[0] - origin[0], pose[1] - origin[1]
  c, s = math.cos(origin[2]), math.sin(origin[2])
  return (c * dx + s * dy, -s * dx + c * dy, wrap_angle(pose[2] - origin[2]))


def remaining_reference(geometry, pose):
  """Trim only the already-traversed prefix, never the inconvenient turn exit."""
  segment = np.diff(geometry.xy, axis=0)
  length = np.linalg.norm(segment, axis=1)
  fraction = np.clip(np.sum((np.asarray(pose[:2]) - geometry.xy[:-1]) * segment, axis=1) / length**2, 0., 1.)
  projections = geometry.xy[:-1] + fraction[:, None] * segment
  nearest = int(np.argmin(np.linalg.norm(projections - pose[:2], axis=1)))
  start = geometry.distance[nearest] + fraction[nearest] * length[nearest]
  station = np.r_[start, geometry.distance[geometry.distance > start + 1e-5]]
  xy = np.column_stack([np.interp(station, geometry.distance, v) for v in geometry.xy.T])
  yaw = np.interp(station, geometry.distance, np.unwrap(geometry.yaw))
  allowance = np.interp(station, geometry.distance, geometry.lateral_allowance)
  preserve = np.interp(station, geometry.distance, geometry.preserve_reference_pose.astype(float)) > 0
  return xy, yaw, station - start, allowance, preserve


class ModelPathPlanner:
  def __init__(self, *, geometry=MODEL_GEOMETRY, solver=None, clock=time.monotonic,
               mount_longitudinal_uncertainty=MOUNT_LONGITUDINAL_UNCERTAINTY,
               mount_lateral_uncertainty=MOUNT_LATERAL_UNCERTAINTY):
    self.geometry = geometry
    self.solver = solver
    self.clock = clock
    self.mount_longitudinal_uncertainty = mount_longitudinal_uncertainty
    self.mount_lateral_uncertainty = mount_lateral_uncertainty
    self.last_plan_id = 0
    self.boundary_history = RearBoundaryHistory()
    self.native_unavailable = False

  def reset(self):
    self.boundary_history.reset()

  def update(self, model, state, vm, *, model_time, model_pose, now, mode, model_valid, roll, angle_offset_deg):
    started = self.clock()
    geometry = None

    def reject(reason):
      return PathPlanningDecision(reason, geometry_available=bool(geometry is not None and geometry.available),
                                  solve_time=max(0., self.clock() - started),
                                  boundary_source=geometry.boundary_source if geometry is not None else 'none')

    if parse_mode(mode) == TrajectoryMode.OFF:
      self.boundary_history.reset()
      return reject('off')
    if state is None or state.rejection(now):
      self.boundary_history.reset()
      return reject('invalid_execution_state')
    if model_pose is None or not np.isfinite([*model_pose, roll, angle_offset_deg]).all():
      self.boundary_history.reset()
      return reject('missing_model_pose')
    uncertainty = (self.mount_longitudinal_uncertainty, self.mount_lateral_uncertainty)
    if not np.isfinite(uncertainty).all() or min(uncertainty) < 0:
      return reject('invalid_mount_uncertainty')
    # The body uncertainty concerns the static camera origin, not steering power.
    config = replace(self.geometry, front=self.geometry.front + self.mount_longitudinal_uncertainty,
                     rear=self.geometry.rear + self.mount_longitudinal_uncertainty,
                     half_width=self.geometry.half_width + self.mount_lateral_uncertainty)
    geometry = build_path_input(model, config, source_time=model_time, now=now, model_valid=model_valid,
                                boundary_history=self.boundary_history, capture_pose=model_pose, generation=state.generation)
    if not geometry.available:
      return reject(geometry.reason)
    initial_pose = relative_pose(state.pose, model_pose)
    xy, yaw, distance, allowance, preserve = remaining_reference(geometry, initial_pose)
    if len(distance) < 5 or distance[-1] < 10:
      return reject('insufficient_remaining_reference')
    if np.linalg.norm(xy[0] - initial_pose[:2]) > .2 or abs(wrap_angle(yaw[0] - initial_pose[2])) > math.radians(3):
      return reject('model_state_mismatch')
    min_curvature, max_curvature = sorted(vm.calc_curvature(math.radians(a - angle_offset_deg), state.speed, roll)
                                        for a in (-STEERING_CAPABILITY_DEG, STEERING_CAPABILITY_DEG))
    rate = abs(vm.curvature_factor(state.speed) / vm.sR * math.radians(PLANNING_ANGLE_RATE))
    if not np.isfinite([min_curvature, max_curvature, rate]).all() or not min_curvature < 0 < max_curvature or rate <= 0:
      return reject('invalid_vehicle_model')
    reference_curvature = np.gradient(yaw, distance)
    turn = yaw[-1] - yaw[0]
    over_limit = (reference_curvature < min_curvature - 1e-6) | (reference_curvature > max_curvature + 1e-6)
    if not over_limit.any():
      if not state.tracking_active:
        return reject('reference_within_capability')
      # Finish through a fresh feasible reference instead of abandoning a turn
      # merely because the next model frame falls below the capability threshold.
      # Yield normally once the model action and the applied command agree to
      # within one model frame of the same planned steering slew.
      try:
        action = model['action']['desiredCurvature'] if isinstance(model, dict) else model.action.desiredCurvature
        baseline = -float(action)
      except (KeyError, AttributeError, TypeError, ValueError):
        return reject('invalid_or_missing_geometry')
      if abs(turn) < math.radians(5) and math.isfinite(baseline) and abs(baseline - state.command_curvature) <= rate * .05:
        return reject('tracking_complete')
    if np.any(over_limit & preserve):
      return reject('over_limit_without_observed_room')
    if abs(turn) < math.radians(5) and not state.tracking_active:
      return reject('unsupported_turn_intent')
    direction = math.copysign(1., turn) if abs(turn) >= math.radians(5) else 0.
    # Preserve turn direction; an already opposite initial wheel may recover
    # within one metre. Independent checking below uses actual solved distance.
    opposite = min(0., direction * state.curvature)
    recovery = opposite * np.maximum(1. - distance, 0.)
    lower = np.maximum(min_curvature, recovery) if direction > 0 else np.full(len(distance), min_curvature)
    upper = np.minimum(max_curvature, -recovery) if direction < 0 else np.full(len(distance), max_curvature)
    if self.solver is None:
      if self.native_unavailable:
        return reject('native_planner_unavailable')
      try:
        from openpilot.selfdrive.controls.lib.ev9_path_mpc import Ev9PathMpc
        self.solver = Ev9PathMpc()
      except (OSError, RuntimeError):
        self.native_unavailable = True
        return reject('native_planner_unavailable')
    result = self.solver.solve(xy, yaw, initial_pose, state.curvature, state.speed, upper, rate,
                               -allowance, allowance, math.radians(3), preserve_reference=preserve, min_curvature=lower)
    if not result.feasible:
      return reject(result.reason)
    if np.any(direction * result.curvature < opposite * np.maximum(1. - result.distance, 0.) - 1e-6):
      return reject('opposite_turn_recovery')
    reference_xy = np.column_stack([np.interp(result.reference_distance, distance, v) for v in xy.T])
    reference_yaw = np.interp(result.reference_distance, distance, yaw)
    changed = (np.linalg.norm(result.xy - reference_xy, axis=1) > 1e-5) | (abs(result.yaw - reference_yaw) > 1e-5)
    unknown = np.interp(result.reference_distance, distance, preserve.astype(float)) > 0
    if np.any(changed & unknown):
      return reject('changed_unobserved_pose')
    if not changed.any() and not state.tracking_active:
      return reject('no_path_adjustment')
    # Measure geometric path displacement, not a difference in progress along
    # the same path. A different feasible arc length is an intended outcome.
    segments = np.diff(xy, axis=0)
    relative = result.xy[:, None, :] - xy[None, :-1, :]
    fraction = np.clip(np.sum(relative * segments, axis=2) / np.sum(segments**2, axis=1), 0., 1.)
    nearest = np.min(np.linalg.norm(relative - fraction[:, :, None] * segments, axis=2), axis=1)
    if np.max(nearest) > config.max_deviation + 1e-5:
      return reject('excessive_path_displacement')
    erosion = geometry.confidence['uncertainty_margin']
    if changed.any() and not body_inside_observed(result.xy[changed], result.yaw[changed], geometry.left, geometry.right,
                                                 front=config.front, rear=config.rear, half_width=config.half_width,
                                                 left_margin=erosion[0], right_margin=erosion[1]):
      return reject('changed_body_outside_observed_space')
    elapsed = self.clock() - started
    finished = now + elapsed
    if elapsed < 0 or elapsed > SOLVE_BUDGET or state.rejection(finished) or not 0 <= finished - model_time <= MAX_PLAN_AGE:
      return reject('planning_deadline')
    plan_id = max(self.last_plan_id + 1, int(state.time * 1e9))
    # A plan cannot extend the lifetime of rear points retained from an older
    # capture. Current-only bounds impose no tighter limit than the model lease.
    boundary_expiry = min((float(np.min(times)) + self.boundary_history.max_age
                           for times in self.boundary_history.point_times if len(times)), default=math.inf)
    valid_until = min(min(state.time, model_time) + MAX_PLAN_AGE, boundary_expiry)
    plan = TrajectoryPlan(plan_id, state.generation, state.time, valid_until,
                          model_pose, state.speed, state.curvature, state.command_curvature, min_curvature, max_curvature,
                          result.distance, result.xy, result.yaw, result.curvature, plan_id, execution_validated=True)
    reason = plan.rejection(state, finished)
    if reason:
      return reject(reason)
    self.last_plan_id = plan_id
    return PathPlanningDecision('refined_model_path', plan, True, elapsed, geometry.boundary_source)

  def close(self):
    if self.solver is not None:
      self.solver.close()
