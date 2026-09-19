"""EV9 trajectory contracts and tracking, independent of messaging and the solver.

Geometry uses a rear-axle origin, metres, and positive-left yaw/curvature.
Only the returned command uses controlsd's positive-right curvature convention.
The source checks bounded changes against observed body clearance and the
experimental execution profile. Short-lived plans cannot renew themselves.
"""
from dataclasses import dataclass
from enum import IntEnum
import math

import numpy as np


STEERING_CAPABILITY_DEG = 140.0
MIN_TRAJECTORY_SPEED = 0.5
MAX_TRAJECTORY_SPEED = 40.0 / 3.6
MAX_PLAN_AGE = 0.25
MAX_STATE_AGE = 0.05
MAX_SAMPLES = 4096


class TrajectoryMode(IntEnum):
  OFF = 0
  SHADOW = 1
  ACTIVE = 2


def parse_mode(value):
  try:
    return TrajectoryMode(int(value or 0))
  except (ValueError, TypeError):
    return TrajectoryMode.OFF


def wrap_angle(angle):
  return math.atan2(math.sin(angle), math.cos(angle))


def path_turn_direction(yaw):
  """Net spatial intent in left-positive coordinates; straight is not a reversal."""
  values = np.asarray(yaw, dtype=float)
  if values.ndim != 1 or len(values) < 2 or not np.isfinite(values).all():
    return 0
  turn = float(np.unwrap(values)[-1] - values[0])
  return int(math.copysign(1, turn)) if abs(turn) >= math.radians(5) else 0


@dataclass(frozen=True)
class ExecutionState:
  time: float
  pose: tuple[float, float, float]
  speed: float
  wheel_angle_deg: float
  curvature: float  # geometric, positive left
  command_curvature: float  # geometric, positive left, after existing jerk limits
  delay: float  # aggregate command-to-motion delay; do not add filter RC again
  generation: int = 0
  enabled: bool = True
  manual: bool = False
  lane_change: bool = False
  drive: bool = True
  healthy: bool = True
  # Optional controller snapshot, distinct from prior requested command_curvature.
  # Planning/tracking uses SAS/VM and aggregate delay; missing diagnostic controller
  # internals alone does not invalidate the ordinary measured vehicle state.
  angle_filter_state_deg: float = 0.0
  angle_state_valid: bool = False
  angle_state_mono_time: int = 0  # controller snapshot time, not individual MDPS sample time
  direct_angle_control: bool = False
  selected_mdps_angle_deg: float = 0.0  # separate sensor reference; mapping to calibrated SAS must be validated
  tracking_active: bool = False
  speed_limit_mps: float = MAX_TRAJECTORY_SPEED
  model_capture_time: float = 0.0
  model_capture_pose: tuple[float, float, float] | None = None

  def odometry_rejection(self, now):
    if not all(math.isfinite(v) for v in (self.time, *self.pose, self.speed, self.curvature, now)):
      return 'invalid_odometry'
    if not self.healthy or not self.drive or self.speed < 0 or not 0 <= now - self.time <= MAX_STATE_AGE:
      return 'invalid_odometry'
    return ''


  def rejection(self, now):
    values = (self.time, *self.pose, self.speed, self.wheel_angle_deg, self.curvature, self.command_curvature, self.delay, self.speed_limit_mps, now)
    if not all(math.isfinite(x) for x in values):
      return 'invalid_state'
    if not 0 <= now - self.time <= MAX_STATE_AGE:
      return 'stale_state'
    if not self.enabled or self.manual or self.lane_change or not self.drive or not self.healthy:
      return 'driver_or_baseline_ownership'
    if (not MIN_TRAJECTORY_SPEED <= self.speed <= min(self.speed_limit_mps, MAX_TRAJECTORY_SPEED) or
        abs(self.wheel_angle_deg) > STEERING_CAPABILITY_DEG or not 0 <= self.delay <= 1.0):
      return 'unsupported_state'
    return ''


@dataclass(frozen=True)
class TrajectoryPlan:
  plan_id: int
  generation: int
  source_time: float
  valid_until: float
  origin: tuple[float, float, float]  # rear-axle pose in the same odometry frame as ExecutionState
  speed: float
  initial_curvature: float
  initial_command_curvature: float
  min_curvature: float
  max_curvature: float
  distance: np.ndarray
  xy: np.ndarray
  yaw: np.ndarray
  curvature: np.ndarray
  corridor_revision: int
  execution_validated: bool = False
  frame: str = 'rear_axle_x_forward_y_left'

  def rejection(self, state, now, *, adopting=True):
    if self.frame != 'rear_axle_x_forward_y_left' or self.generation != state.generation:
      return 'state_or_frame_mismatch'
    values = (self.source_time, self.valid_until, *self.origin, self.speed, self.initial_curvature,
              self.initial_command_curvature, self.min_curvature, self.max_curvature)
    if not all(math.isfinite(v) for v in values):
      return 'invalid_plan'
    if (now < self.source_time or (adopting and now - self.source_time > MAX_PLAN_AGE) or
        not now <= self.valid_until <= self.source_time + 120.0):
      return 'expired_plan'
    if not self.execution_validated:
      return 'execution_not_validated'
    n = len(self.distance)
    if (not 5 <= n <= MAX_SAMPLES or self.distance.shape != (n,) or self.xy.shape != (n, 2) or
        self.yaw.shape != (n,) or self.curvature.shape != (n,)):
      return 'invalid_plan'
    if not all(np.isfinite(a).all() for a in (self.distance, self.xy, self.yaw, self.curvature)):
      return 'invalid_plan'
    if abs(self.distance[0]) > 1e-6 or np.any(np.diff(self.distance) <= 0) or self.distance[-1] < 10:
      return 'invalid_plan'
    if not self.min_curvature < 0 < self.max_curvature or np.min(self.curvature) < self.min_curvature - 1e-6 or \
       np.max(self.curvature) > self.max_curvature + 1e-6:
      return 'invalid_capability'
    if (not math.isfinite(state.speed_limit_mps) or abs(state.speed - self.speed) > 0.25 or
        not MIN_TRAJECTORY_SPEED <= self.speed <= min(state.speed_limit_mps, MAX_TRAJECTORY_SPEED)):
      return 'speed_mismatch'
    return ''


@dataclass(frozen=True)
class TrackingDecision:
  curvature: float  # controlsd convention; baseline when inactive
  active: bool
  reason: str
  plan_id: int = 0
  lateral_error: float = 0.0
  heading_error: float = 0.0


class TrajectoryTracker:
  """Adopt fresh full trajectories; cancellation never synthesizes neutral steering.

  The caller supplies the already-shaped baseline request. OFF and SHADOW return
  that exact value and cannot acquire steering ownership. A fresh corridor lease
  and generation are checked on every tick, including between model messages.
  """
  def __init__(self):
    self.plan = None
    self.progress = 0
    self.last_plan_id = 0
    self.last_source_time = -math.inf
    self.reject_before = -math.inf
    self.last_mode = TrajectoryMode.OFF
    self.corridor_valid_until = 0.0

  def reset(self, now):
    self.plan = None
    self.progress = 0
    self.corridor_valid_until = 0.0
    self.reject_before = max(self.reject_before, now)

  @staticmethod
  def local_pose(state, plan):
    dx, dy = state.pose[0] - plan.origin[0], state.pose[1] - plan.origin[1]
    c, s = math.cos(plan.origin[2]), math.sin(plan.origin[2])
    return np.array([c * dx + s * dy, -s * dx + c * dy]), wrap_angle(state.pose[2] - plan.origin[2])

  def update(self, state, baseline_curvature, *, mode, proposal=None, corridor_revision=0, corridor_valid_until=0.0, revoke=False, model_turn_direction=0):
    now = state.time
    mode = parse_mode(mode)
    if mode != self.last_mode:
      self.reset(now)
      self.last_mode = mode
    if mode != TrajectoryMode.ACTIVE:
      self.plan = None
      return TrackingDecision(baseline_curvature, False, 'off' if mode == TrajectoryMode.OFF else 'shadow')
    reason = state.rejection(now)
    if reason:
      self.reset(now)
      return TrackingDecision(baseline_curvature, False, reason)
    if revoke:
      self.reset(now)
      return TrackingDecision(baseline_curvature, False, 'corridor_unavailable')
    intent_changed = self.plan is not None and model_turn_direction * path_turn_direction(self.plan.yaw) < 0
    if intent_changed:
      # A fresh compatible replacement may still adopt this tick. Do not let an
      # unsuccessful solve keep driving the old turn merely because its lease lives.
      self.plan, self.progress, self.corridor_valid_until = None, 0, 0.0
    fresh_corridor = math.isfinite(corridor_valid_until) and now <= corridor_valid_until <= now + MAX_PLAN_AGE
    if proposal is not None:
      reason = proposal.rejection(state, now)
      if model_turn_direction * path_turn_direction(proposal.yaw) < 0:
        reason = 'model_intent_changed'
      if not fresh_corridor:
        reason = 'corridor_unavailable'
      if not reason and (proposal.source_time < self.reject_before or proposal.source_time < self.last_source_time or
                         proposal.plan_id <= self.last_plan_id or proposal.corridor_revision != corridor_revision):
        reason = 'superseded_plan'
      if not reason:
        xy, yaw = self.local_pose(state, proposal)
        nearest = int(np.argmin(np.sum((proposal.xy - xy)**2, axis=1)))
        if (proposal.distance[nearest] > state.speed * MAX_PLAN_AGE + 0.25 or
            np.linalg.norm(xy - proposal.xy[nearest]) > 0.20 or
            abs(wrap_angle(yaw - proposal.yaw[nearest])) > math.radians(3) or
            abs(state.curvature - proposal.curvature[nearest]) > 0.005 or
            abs(state.command_curvature - proposal.initial_command_curvature) > 0.01):
          reason = 'initial_state_mismatch'
        else:
          self.plan, self.progress = proposal, nearest
          self.corridor_valid_until = min(corridor_valid_until, proposal.valid_until)
          self.last_plan_id, self.last_source_time = proposal.plan_id, proposal.source_time
      if reason and self.plan is None:
        return TrackingDecision(baseline_curvature, False, reason)
    if self.plan is None:
      if intent_changed:
        self.reset(now)
      return TrackingDecision(baseline_curvature, False, 'model_intent_changed' if intent_changed else 'no_replacement')
    plan = self.plan
    # A replacement's revision/lease belongs to that replacement. Failed adoption
    # must not revoke a still-valid incumbent or renew it from unrelated evidence.
    if corridor_revision == plan.corridor_revision:
      if not fresh_corridor:
        self.reset(now)
        return TrackingDecision(baseline_curvature, False, 'corridor_unavailable')
      self.corridor_valid_until = min(corridor_valid_until, plan.valid_until)
    if now > self.corridor_valid_until:
      self.reset(now)
      return TrackingDecision(baseline_curvature, False, 'corridor_unavailable')
    reason = plan.rejection(state, now, adopting=False)
    if reason:
      self.reset(now)
      return TrackingDecision(baseline_curvature, False, reason)
    xy, yaw = self.local_pose(state, plan)
    # Bound search by physical progress since adoption, including a refreshed
    # corridor after a model-frame gap; avoid arbitrary sample-count windows.
    max_progress = min(plan.distance[-1], state.speed * (now - plan.source_time) + 1.0)
    lo = max(0, self.progress - 4)
    hi = max(lo + 1, int(np.searchsorted(plan.distance, max_progress, side='right')))
    self.progress = lo + int(np.argmin(np.sum((plan.xy[lo:hi] - xy)**2, axis=1)))
    i = self.progress
    h = plan.yaw[i]
    lateral = float((xy - plan.xy[i]) @ np.array([-math.sin(h), math.cos(h)]))
    heading = wrap_angle(yaw - h)
    if np.linalg.norm(xy - plan.xy[i]) > 0.30 or abs(lateral) > 0.25 or abs(heading) > math.radians(5):
      self.reset(now)
      return TrackingDecision(baseline_curvature, False, 'tracking_error')
    preview = state.speed * state.delay
    if plan.distance[i] + preview >= plan.distance[-1] - 0.1:
      self.reset(now)
      return TrackingDecision(baseline_curvature, False, 'complete')
    geometric = float(np.interp(plan.distance[i] + preview, plan.distance, plan.curvature)) - 0.08 * lateral - 0.5 * heading
    # The capability constrains path geometry, not the feedback request. The
    # existing command chain and physical plant govern execution; predicted
    # execution must include saturation. Rejecting a correction merely because
    # its request exceeds 140 is another artificial output restriction and can
    # abandon an otherwise trackable full-authority turn.
    return TrackingDecision(-geometric, True, 'tracking', plan.plan_id, lateral, heading)


class EgoMotion:
  """Short-lived local odometry for plan-frame alignment, invalidated on gaps.

  Inputs must already describe the rear axle. This is not an estimator of the
  unknown installation offset between the camera/device and the rear axle.
  """
  def __init__(self):
    self.pose = (0.0, 0.0, 0.0)
    self.time = None
    self.generation = 0

  def update(self, now, speed, yaw_rate):
    if not all(math.isfinite(v) for v in (now, speed, yaw_rate)) or self.time is None or not 0 < now - self.time <= 0.05:
      self.pose = (0.0, 0.0, 0.0)
      self.generation += 1
    else:
      dt = now - self.time
      x, y, yaw = self.pose
      heading = yaw + yaw_rate * dt / 2
      self.pose = (x + speed * math.cos(heading) * dt, y + speed * math.sin(heading) * dt, wrap_angle(yaw + yaw_rate * dt))
    self.time = now
    return self.pose
