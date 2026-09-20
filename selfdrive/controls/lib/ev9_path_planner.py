"""Rolling EV9 model-path refiner; the existing controller still drives the car.

The model owns driving intent. This layer adjusts timing and geometry within a
bounded distance of that path, using reliable observed boundaries when available.
Model-led adjustments without boundaries are not independent free-space proof.
"""
from dataclasses import dataclass, replace
import math
import time

import numpy as np

from opendbc.car.hyundai.ev9 import EV9_HIGH_LATERAL_LIMIT
from openpilot.selfdrive.controls.lib.drive_helpers import MIN_SPEED
from openpilot.selfdrive.controls.lib.ev9_path_geometry import body_respects_observed
from openpilot.selfdrive.controls.lib.ev9_path_frames import CameraMount
from openpilot.selfdrive.controls.lib.ev9_path_history import RearBoundaryHistory
from openpilot.selfdrive.controls.lib.ev9_path_input import PathGeometryConfig, build_path_input
from openpilot.selfdrive.controls.lib.ev9_trajectory import (
  MAX_PLAN_AGE, STEERING_CAPABILITY_DEG, TrajectoryMode, TrajectoryPlan, parse_mode, required_plan_distance, wrap_angle,
)


# Explicit initial experimental profile, not an inferred physical calibration.
# Mount sensitivity is included in the body envelope below. No angle derating.
MODEL_GEOMETRY = PathGeometryConfig(CameraMount(2.0, 0.0), True, 3.975, 1.04, 1.1, margin=.08, max_deviation=1.0)
MOUNT_LONGITUDINAL_UNCERTAINTY = .30
MOUNT_LATERAL_UNCERTAINTY = .10
PLANNING_ANGLE_RATE = 100.0
MIN_SPATIAL_RATE_SPEED = .5  # Finite, conservative slew conversion while crawling or stopped.
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


def remaining_path(xy, yaw, distance, pose):
  """Trim only the already-traversed prefix, never the inconvenient turn exit."""
  segment = np.diff(xy, axis=0)
  length = np.linalg.norm(segment, axis=1)
  fraction = np.clip(np.sum((np.asarray(pose[:2]) - xy[:-1]) * segment, axis=1) / length**2, 0., 1.)
  projections = xy[:-1] + fraction[:, None] * segment
  nearest = int(np.argmin(np.linalg.norm(projections - pose[:2], axis=1)))
  start = distance[nearest] + fraction[nearest] * length[nearest]
  station = np.r_[start, distance[distance > start + 1e-5]]
  xy = np.column_stack([np.interp(station, distance, v) for v in xy.T])
  yaw = np.interp(station, distance, np.unwrap(yaw))
  return xy, yaw, station - start, station


def remaining_reference(geometry, pose):
  xy, yaw, distance, station = remaining_path(geometry.xy, geometry.yaw, geometry.distance, pose)
  lower = np.interp(station, geometry.distance, geometry.lateral_lower)
  upper = np.interp(station, geometry.distance, geometry.lateral_upper)
  heading_allowance = np.interp(station, geometry.distance, geometry.heading_allowance)
  preserve = np.interp(station, geometry.distance, geometry.preserve_reference_pose.astype(float)) > 0
  return xy, yaw, distance, lower, upper, heading_allowance, preserve


def within_path_budget(points, reference, distance, lower, upper):
  """Geometric displacement uses the room at the nearest reference station.

  Optimized progress may differ from reference progress; it cannot borrow room
  from a wider part of the lane elsewhere in the solver horizon.
  """
  if not all(np.isfinite(value).all() for value in (points, reference, distance, lower, upper)):
    return False
  # A nearby point on the reference proves the nearest point is at least as
  # close. Use only the smallest budget on either side, so this cheap proof
  # cannot borrow room from another station. Project the unresolved poses only.
  station = np.linspace(distance[0], distance[-1], len(points))
  sampled = np.column_stack([np.interp(station, distance, axis) for axis in reference.T])
  minimum = min(float(np.min(upper)), -float(np.max(lower)))
  unresolved = ~(np.sum((points - sampled)**2, axis=1) <= (max(0., minimum) + 1e-5)**2)
  if minimum < 0 or np.any(np.diff(distance) <= 0) or np.any(np.all(np.diff(reference, axis=0) == 0, axis=1)):
    unresolved[:] = True
  points = points[unresolved]
  if not len(points):
    return True
  segment_x, segment_y = np.diff(reference, axis=0).T
  delta_x = points[:, 0, None] - reference[None, :-1, 0]
  delta_y = points[:, 1, None] - reference[None, :-1, 1]
  fraction = np.clip((delta_x * segment_x + delta_y * segment_y) / (segment_x**2 + segment_y**2), 0., 1.)
  squared = (delta_x - fraction * segment_x)**2 + (delta_y - fraction * segment_y)**2
  index = np.argmin(squared, axis=1)
  rows = np.arange(len(points))
  station = distance[index] + fraction[rows, index] * np.diff(distance)[index]
  side = segment_x[index] * delta_y[rows, index] - segment_y[index] * delta_x[rows, index]
  budget = np.where(side >= 0., np.interp(station, distance, upper), -np.interp(station, distance, lower))
  return bool(np.all(squared[rows, index] <= (budget + 1e-5)**2))


def reference_capability(xy, yaw, distance, state, vm, roll, angle_offset_deg):
  min_curvature, max_curvature = sorted(vm.calc_curvature(math.radians(a - angle_offset_deg), state.speed, roll)
                                      for a in (-STEERING_CAPABILITY_DEG, STEERING_CAPABILITY_DEG))
  rate = abs(vm.curvature_factor(state.speed) / vm.sR * math.radians(PLANNING_ANGLE_RATE))
  # The existing EV9 controller also enforces lateral acceleration and jerk.
  # Account for those limits in geometry rather than planning steering that
  # downstream controls will clip. The full 140 degrees remains available
  # whenever these existing speed-dependent limits permit it.
  controller_bound = EV9_HIGH_LATERAL_LIMIT / max(state.speed, MIN_SPEED)**2
  min_curvature, max_curvature = max(min_curvature, -controller_bound), min(max_curvature, controller_bound)
  rate = min(rate, controller_bound)
  if not np.isfinite([min_curvature, max_curvature, rate]).all() or not min_curvature < 0 < max_curvature or rate <= 0:
    raise ValueError('invalid_vehicle_model')
  reference_curvature = np.gradient(yaw, distance)
  turn = yaw[-1] - yaw[0]
  over_limit = (reference_curvature < min_curvature - 1e-6) | (reference_curvature > max_curvature + 1e-6)
  # Staying below 140 degrees does not make a late turn-in executable. The
  # reference must also respect the same steering slew used by the solver.
  over_rate = abs(np.diff(reference_curvature)) * state.speed > rate * np.diff(distance) + 1e-6
  requires_change = over_limit | np.r_[over_rate, False] | np.r_[False, over_rate]
  return min_curvature, max_curvature, rate, reference_curvature, turn, requires_change


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

    # Input freshness is checked at entry; the tracker checks its current state
    # again at adoption. Computation never restamps or extends the model lease.
    def check_budget():
      elapsed = self.clock() - started
      finished = now + elapsed
      if elapsed < 0 or elapsed > SOLVE_BUDGET or not 0 <= finished - model_time <= MAX_PLAN_AGE:
        raise TimeoutError("planning_deadline")

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
    initial_pose = relative_pose(state.pose, model_pose)

    capability = None

    def precheck(xy, yaw, distance):
      nonlocal capability
      if state.tracking_active:
        return None
      xy, yaw, distance, _ = remaining_path(xy, yaw, distance, initial_pose)
      if len(distance) < 5 or distance[-1] < required_plan_distance(state.speed, state.delay):
        return 'insufficient_remaining_reference'
      # Only skip when the later initial-state check necessarily passes even
      # without additional lane room. Otherwise preserve its exact rejection.
      heading = min(np.pi/2, config.max_deviation/math.hypot(max(config.front, config.rear), config.half_width))
      if (np.linalg.norm(xy[0] - initial_pose[:2]) > max(.2, config.max_deviation) or
          abs(wrap_angle(yaw[0] - initial_pose[2])) > max(math.radians(3), heading)):
        return None
      try:
        capability = reference_capability(xy, yaw, distance, state, vm, roll, angle_offset_deg)
        _, _, _, _, turn, requires_change = capability
      except ValueError:
        return None
      if not requires_change.any():
        return 'reference_within_capability'
      if abs(turn) < math.radians(5):
        return 'unsupported_turn_intent'
      return None

    try:
      check_budget()
      geometry = build_path_input(model, config, source_time=model_time, now=now, model_valid=model_valid,
                                  boundary_history=self.boundary_history, capture_pose=model_pose, generation=state.generation,
                                  check_budget=check_budget, precheck=precheck)
    except TimeoutError:
      return reject('planning_deadline')
    if not geometry.available:
      return reject(geometry.reason)
    xy, yaw, distance, lateral_lower, lateral_upper, heading_allowance, preserve = remaining_reference(geometry, initial_pose)
    if len(distance) < 5 or distance[-1] < required_plan_distance(state.speed, state.delay):
      return reject('insufficient_remaining_reference')
    # A continuing refined path may be deliberately farther from the model than
    # the old 15 cm prototype allowed. Use observed clearance here as in the
    # solve; otherwise a valid wider turn cancels itself as the car follows it.
    initial_lateral = np.array([-math.sin(yaw[0]), math.cos(yaw[0])]) @ (np.asarray(initial_pose[:2]) - xy[0])
    initial_room = lateral_upper[0] if initial_lateral >= 0 else -lateral_lower[0]
    if (np.linalg.norm(xy[0] - initial_pose[:2]) > max(.2, initial_room) or
        abs(wrap_angle(yaw[0] - initial_pose[2])) > max(math.radians(3), heading_allowance[0])):
      return reject('model_state_mismatch')
    try:
      min_curvature, max_curvature, rate, reference_curvature, turn, requires_change = (
        capability if capability is not None else reference_capability(xy, yaw, distance, state, vm, roll, angle_offset_deg))
    except ValueError:
      return reject('invalid_vehicle_model')
    if not requires_change.any():
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
      spatial_agreement = (np.linalg.norm(xy[0] - initial_pose[:2]) <= .1 and
                           abs(wrap_angle(yaw[0] - initial_pose[2])) <= math.radians(1))
      if (abs(turn) < math.radians(5) and spatial_agreement and math.isfinite(baseline) and
          abs(baseline - state.command_curvature) <= rate * .05):
        return reject('tracking_complete')
    if np.any(requires_change & preserve):
      return reject('over_limit_without_observed_room')
    if abs(turn) < math.radians(5) and not state.tracking_active:
      return reject('unsupported_turn_intent')
    direction = math.copysign(1., turn) if abs(turn) >= math.radians(5) else 0.
    # A forecast can bend both ways despite its net turn direction. Permit
    # those opposing bends and physical recovery from an opposite initial wheel,
    # without inventing stronger countersteer than either already requires.
    # The turn itself retains full physical authority; spatial/heading bounds
    # preserve the local model shape. There is no arbitrary recovery distance.
    lower = max(min_curvature, min(0., state.curvature, float(np.min(reference_curvature)))) if direction > 0 else min_curvature
    upper = min(max_curvature, max(0., state.curvature, float(np.max(reference_curvature)))) if direction < 0 else max_curvature
    if self.solver is None:
      if self.native_unavailable:
        return reject('native_planner_unavailable')
      try:
        from openpilot.selfdrive.controls.lib.ev9_path_mpc import Ev9PathMpc
        self.solver = Ev9PathMpc()
      except (OSError, RuntimeError):
        self.native_unavailable = True
        return reject('native_planner_unavailable')
    try:
      check_budget()
    except TimeoutError:
      return reject('planning_deadline')
    result = self.solver.solve(xy, yaw, initial_pose, state.curvature, max(state.speed, MIN_SPATIAL_RATE_SPEED), upper, rate,
                               lateral_lower, lateral_upper, heading_allowance, preserve_reference=preserve, min_curvature=lower)
    if not result.feasible:
      return reject(result.reason)
    if direction * (result.yaw[-1] - result.yaw[0]) < -1e-6:
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
    if not within_path_budget(result.xy, xy, distance, lateral_lower, lateral_upper):
      return reject('excessive_path_displacement')
    # Missing edges do not become invented walls or verified free space.
    # Applicable reliable observations constrain the full candidate, including
    # conflicts already present in the original model path.
    original_station = result.reference_distance + geometry.distance[-1] - distance[-1]
    try:
      check_budget()
      if not body_respects_observed(result.xy, result.yaw, geometry, reference_distance=original_station,
                                    front=config.front, rear=config.rear, half_width=config.half_width, check_budget=check_budget):
        return reject('observed_boundary_conflict')
    except TimeoutError:
      return reject('planning_deadline')
    elapsed = self.clock() - started
    finished = now + elapsed
    if elapsed < 0 or elapsed > SOLVE_BUDGET or not 0 <= finished - model_time <= MAX_PLAN_AGE:
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
