"""Observed geometry for bounded path refinement; never grants steering permission.

Coordinates are rear-axle x-forward/y-left. Physical mounting/alignment and body
size are explicit caller inputs. Road edges constrain geometry, not lane rights.
Unknown stations require preserving BOTH reference position and heading; even
that is not a claim the original path is safe or executable.
"""

from dataclasses import dataclass, field
import math

import numpy as np

from openpilot.selfdrive.controls.lib.ev9_path_frames import CameraMount, model_path_to_rear_axle, static_model_points_to_rear_axle


@dataclass(frozen=True)
class PathGeometryConfig:
  mount: CameraMount
  alignment_established: bool
  front: float
  rear: float
  half_width: float
  margin: float = 0.1
  max_deviation: float = 0.90  # An optimization limit, never evidence of available space.
  lane_probability: float = 0.5
  uncertainty_multiplier: float = 2.0  # Rejection margin, not a calibrated probability guarantee.


@dataclass
class PathInput:
  available: bool
  reason: str
  xy: np.ndarray = field(default_factory=lambda: np.empty((0, 2)))
  yaw: np.ndarray = field(default_factory=lambda: np.empty(0))
  distance: np.ndarray = field(default_factory=lambda: np.empty(0))
  left: np.ndarray = field(default_factory=lambda: np.empty((0, 2)))
  right: np.ndarray = field(default_factory=lambda: np.empty((0, 2)))
  sampled_body_covered: np.ndarray = field(default_factory=lambda: np.empty(0, dtype=bool))
  lateral_allowance: np.ndarray = field(default_factory=lambda: np.empty(0))
  preserve_reference_pose: np.ndarray = field(default_factory=lambda: np.empty(0, dtype=bool))
  boundary_source: str = 'none'
  confidence: dict = field(default_factory=dict)
  source_time: float = 0.0
  complete_observed_reference: bool = False
  execution_authorized: bool = field(default=False, init=False)


def _get(value, key):
  return value[key] if isinstance(value, dict) else getattr(value, key)


def _array(value, key):
  result = np.asarray(_get(value, key), dtype=float)
  if result.ndim != 1 or not np.isfinite(result).all():
    raise ValueError('invalid_array')
  return result


def _boundary(line, mount):
  x, y = _array(line, 'x'), _array(line, 'y')
  if len(x) < 3 or x.shape != y.shape or np.any(np.diff(x) <= 1e-5):
    raise ValueError('invalid_boundary')
  return static_model_points_to_rear_axle(np.column_stack((x, y)), mount)


def build_path_input(model, config, *, source_time, now, model_valid, horizon_distance=None, boundary_history=None, capture_pose=None, generation=0):
  """Build a geometry proposal from the complete observed path or explicit prefix.

  Lane probability selects lane versus road geometry, not an execution gate.
  Boundary standard deviations contract observed widths; no guessed lane width.
  A requested prefix is labelled incomplete and cannot prove turn completion.
  Bounds hold for the sampled rectangle at REFERENCE heading. Consumers must
  independently validate the entire changed swept footprint and terminal state.
  """

  def reject(reason):
    if boundary_history is not None:
      boundary_history.reset()
    return PathInput(False, reason)

  values = [
    source_time,
    now,
    config.front,
    config.rear,
    config.half_width,
    config.margin,
    config.max_deviation,
    config.lane_probability,
    config.uncertainty_multiplier,
  ]
  if (
    not all(math.isfinite(v) for v in values)
    or min(config.front, config.rear, config.half_width) <= 0
    or min(config.margin, config.max_deviation, config.uncertainty_multiplier) < 0
    or not 0 <= config.lane_probability <= 1
  ):
    return reject('invalid_configuration')
  if not config.alignment_established:
    return reject('unestablished_frame_alignment')
  if not model_valid or not 0 <= now - source_time <= 0.25:
    return reject('invalid_or_stale_model')
  try:
    position, orientation = _get(model, 'position'), _get(model, 'orientation')
    x, y, t = (_array(position, key) for key in ('x', 'y', 't'))
    heading, heading_t = _array(orientation, 'z'), _array(orientation, 't')
    if len(x) < 4 or x.shape != y.shape or x.shape != t.shape or heading.shape != x.shape or not np.array_equal(t, heading_t):
      return reject('unmatched_path_heading')
    if np.any(np.diff(t) <= 0):
      return reject('invalid_path_time')
    xy, yaw = model_path_to_rear_axle(np.column_stack((x, y)), heading, config.mount)
    distance = np.r_[0.0, np.cumsum(np.linalg.norm(np.diff(xy, axis=0), axis=1))]
    if np.any(np.diff(distance) <= 1e-5) or distance[-1] < 3:
      return reject('insufficient_reference')
    complete = True
    if horizon_distance is not None:
      if not math.isfinite(horizon_distance) or not 3 <= horizon_distance <= distance[-1]:
        return reject('invalid_requested_horizon')
      complete = horizon_distance == distance[-1]
      end = int(np.searchsorted(distance, horizon_distance, side='right'))
      xy, yaw, distance = xy[:end], yaw[:end], distance[:end]
      if len(xy) < 4:
        return reject('insufficient_reference')
    # Fixed-forward-x boundaries cannot represent a branch wrapping behind camera.
    if np.any(np.diff(xy[:, 0]) <= 1e-5) or np.max(abs(yaw)) >= math.pi / 3:
      return reject('unsupported_turn_geometry')
    probs, lane_std = _array(model, 'laneLineProbs'), _array(model, 'laneLineStds')
    if probs.shape != (4,) or lane_std.shape != (4,) or np.any(probs < 0) or np.any(probs > 1) or np.any(lane_std < 0):
      return reject('invalid_lane_metadata')
    use_lanes = min(probs[1:3]) >= config.lane_probability
    if use_lanes:
      pair = list(_get(model, 'laneLines'))[1:3]
      std = lane_std[1:3]
      source = 'inner_lanes'
    else:
      pair = _get(model, 'roadEdges')
      std = _array(model, 'roadEdgeStds')
      if len(pair) != 2 or std.shape != (2,) or np.any(std < 0):
        return reject('invalid_road_metadata')
      source = 'road_edges_geometry_only'
    left, right = [_boundary(line, config.mount) for line in pair]
  except (KeyError, AttributeError, IndexError, TypeError, ValueError):
    return reject('invalid_or_missing_geometry')
  erosion = config.margin + config.uncertainty_multiplier * np.asarray(std)
  if boundary_history is not None:
    if capture_pose is None or np.asarray(capture_pose).shape != (3,) or not np.isfinite(capture_pose).all():
      return reject('missing_capture_pose')
    left, right, erosion = boundary_history.extend(left, right, erosion, pose=capture_pose, stamp=source_time,
                                                  now=now, generation=generation, source=source,
                                                  rear_extent=math.hypot(config.rear, config.half_width) + config.max_deviation +
                                                  config.front * math.sin(math.radians(3)))
  lo, hi = max(left[0, 0], right[0, 0]), min(left[-1, 0], right[-1, 0])
  knots = np.unique(np.r_[left[:, 0], right[:, 0]])
  knots = knots[(knots >= lo) & (knots <= hi)]
  if len(knots) < 2 or np.any(np.interp(knots, left[:, 0], left[:, 1]) <= np.interp(knots, right[:, 0], right[:, 1])):
    return reject('crossed_or_missing_boundaries')
  # Model scalar std is only the first predicted point: this erosion is a
  # descriptive conservative heuristic, NOT full-horizon confidence validation.
  local = np.array([(a, b) for a in np.linspace(-config.rear, config.front, 12) for b in np.linspace(-config.half_width, config.half_width, 7)])
  c, s = np.cos(yaw)[:, None], np.sin(yaw)[:, None]
  bx = xy[:, 0, None] + c * local[:, 0] - s * local[:, 1]
  by = xy[:, 1, None] + s * local[:, 0] + c * local[:, 1]
  left_gap = np.interp(bx, left[:, 0], left[:, 1]) - by - erosion[0]
  right_gap = by - np.interp(bx, right[:, 0], right[:, 1]) - erosion[1]
  longitudinal_gap = np.minimum(bx - lo, hi - bx).min(axis=1)
  clearance = np.minimum(left_gap, right_gap).min(axis=1)
  covered = (longitudinal_gap >= 0) & (clearance > 0)
  slope = max(np.max(abs(np.diff(b[:, 1]) / np.diff(b[:, 0]))) for b in [left, right])
  normal_motion = np.abs(np.cos(yaw)) + slope * np.abs(np.sin(yaw))
  allowance = np.minimum(config.max_deviation, np.maximum(clearance, 0) / np.maximum(normal_motion, 1e-8))
  allowance = np.minimum(allowance, np.maximum(longitudinal_gap, 0) / np.maximum(abs(np.sin(yaw)), 1e-8))
  allowance[~covered] = 0.0
  try:
    reference_std = _array(position, 'yStd')[: len(xy)]
    path_std_max = float(max(reference_std)) if len(reference_std) else None
  except (KeyError, AttributeError, TypeError, ValueError):
    path_std_max = None
  return PathInput(
    bool(np.any(allowance > 0)),
    'observed_geometry_only' if np.any(allowance > 0) else 'no_observed_body_deviation_room',
    xy,
    yaw,
    distance,
    left,
    right,
    covered,
    allowance,
    allowance <= 0,
    source,
    dict(lane_probability=float(min(probs[1:3])), boundary_std=std.tolist(), uncertainty_margin=erosion.tolist(), model_path_y_std_max=path_std_max),
    source_time,
    complete,
  )
