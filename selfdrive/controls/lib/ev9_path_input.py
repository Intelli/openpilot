"""Observed geometry for bounded path refinement; never grants steering permission.

Coordinates are rear-axle x-forward/y-left. Physical mounting/alignment and body
size are explicit caller inputs. Road edges constrain geometry, not lane rights.
Missing/uncertain boundaries leave the model-path budget available. This is
not a claim that the resulting path is observed free space.
"""

from dataclasses import dataclass, field
import math

import numpy as np

from openpilot.selfdrive.controls.lib.ev9_path_geometry import ObservedBoundary, boundary_association, reliable_body_clearance
from openpilot.selfdrive.controls.lib.ev9_path_frames import CameraMount, model_path_to_rear_axle, static_model_points_to_rear_axle
from openpilot.selfdrive.controls.lib.ev9_trajectory import MIN_TRAJECTORY_DISTANCE


@dataclass(frozen=True)
class PathGeometryConfig:
  mount: CameraMount
  alignment_established: bool
  front: float
  rear: float
  half_width: float
  margin: float = 0.1
  max_deviation: float = 1.0  # Model-led fallback; reliable inner lanes may supply additional room.
  lane_probability: float = 0.5
  uncertainty_multiplier: float = 2.0  # Rejection margin, not a calibrated probability guarantee.
  boundary_std_max: float = .5  # Heuristic reliability cutoff, metres; not a calibrated confidence guarantee.


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
  heading_allowance: np.ndarray = field(default_factory=lambda: np.empty(0))
  reliable_boundaries: tuple[ObservedBoundary, ...] = ()
  lateral_lower: np.ndarray = field(default_factory=lambda: np.empty(0))
  lateral_upper: np.ndarray = field(default_factory=lambda: np.empty(0))


def _get(value, key):
  return value[key] if isinstance(value, dict) else getattr(value, key)


def _array(value, key):
  result = np.asarray(_get(value, key), dtype=float)
  if result.ndim != 1 or not np.isfinite(result).all():
    raise ValueError('invalid_array')
  return result


def _boundary(line, mount):
  x, y = _array(line, 'x'), _array(line, 'y')
  if len(x) < 3 or x.shape != y.shape or np.any(np.hypot(np.diff(x), np.diff(y)) <= 1e-5):
    raise ValueError('invalid_boundary')
  return static_model_points_to_rear_axle(np.column_stack((x, y)), mount)


def build_path_input(model, config, *, source_time, now, model_valid, horizon_distance=None, boundary_history=None, capture_pose=None, generation=0):
  """Build a geometry proposal from the complete observed path or explicit prefix.

  Lane probability selects lane versus road geometry, not an execution gate.
  Boundary standard deviations contract observed widths; no guessed lane width.
  A requested prefix is labelled incomplete and cannot prove turn completion.
  The path budget is not observed free space. Consumers must independently
  validate reliable boundary constraints against the entire swept footprint.
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
    config.boundary_std_max,
  ]
  if (
    not all(math.isfinite(v) for v in values)
    or min(config.front, config.rear, config.half_width) <= 0
    or min(config.margin, config.max_deviation, config.uncertainty_multiplier) < 0
    or config.boundary_std_max <= 0
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
    if np.any(np.diff(distance) <= 1e-5) or distance[-1] < MIN_TRAJECTORY_DISTANCE:
      return reject('insufficient_reference')
    complete = True
    if horizon_distance is not None:
      if not math.isfinite(horizon_distance) or not MIN_TRAJECTORY_DISTANCE <= horizon_distance <= distance[-1]:
        return reject('invalid_requested_horizon')
      complete = horizon_distance == distance[-1]
      end = int(np.searchsorted(distance, horizon_distance, side='right'))
      xy, yaw, distance = xy[:end], yaw[:end], distance[:end]
      if len(xy) < 4:
        return reject('insufficient_reference')
  except (KeyError, AttributeError, IndexError, TypeError, ValueError):
    return reject('invalid_or_missing_geometry')

  def optional_array(key, length):
    try:
      # Metadata belongs to independent sides: one nonfinite value must not
      # erase another side's finite observation. Selection checks each value.
      values = np.asarray(_get(model, key), dtype=float)
      return values if values.shape == (length,) else np.full(length, np.nan)
    except (KeyError, AttributeError, TypeError, ValueError):
      return np.full(length, np.nan)

  probs, lane_std, edge_std = optional_array('laneLineProbs', 4), optional_array('laneLineStds', 4), optional_array('roadEdgeStds', 2)
  lines, sources, stds, reliable = [], [], [], []
  for side in range(2):
    options = [('inner_lanes', 'laneLines', side+1, lane_std[side+1],
                bool(np.isfinite(probs[side+1]) and config.lane_probability <= probs[side+1] <= 1.)),
               ('road_edges_geometry_only', 'roadEdges', side, edge_std[side], True)]
    selected = None
    for source, key, index, std, eligible in options:
      if not eligible:
        continue
      try:
        points = _boundary(_get(model, key)[index], config.mount)
      except (KeyError, AttributeError, IndexError, TypeError, ValueError):
        continue
      trusted = bool(np.isfinite(std) and 0 <= std <= config.boundary_std_max)
      if selected is None or trusted:
        selected = (points, source, float(std), trusted)
      if trusted:
        break
    points, source, std, trusted = selected if selected is not None else (np.empty((0, 2)), 'missing', math.nan, False)
    lines.append(points)
    sources.append(source)
    stds.append(std)
    reliable.append(trusted)
  erosion = np.array([config.margin+config.uncertainty_multiplier*std if trusted else 0. for std, trusted in zip(stds, reliable, strict=True)])
  if boundary_history is not None:
    if all(reliable):
      if capture_pose is None or np.asarray(capture_pose).shape != (3,) or not np.isfinite(capture_pose).all():
        return reject('missing_capture_pose')
      left, right, erosion = boundary_history.extend(*lines, erosion, pose=capture_pose, stamp=source_time,
                                                    now=now, generation=generation, source='/'.join(sources),
                                                    rear_extent=math.hypot(config.rear, config.half_width)+config.max_deviation+
                                                    config.front*np.sin(min(np.pi/2, config.max_deviation/config.front)))
      lines = [left, right]
    else:
      # Do not carry a formerly reliable side through a changed source/pair.
      boundary_history.reset()
  boundaries = []
  body_applicability = np.zeros((2, len(xy)), dtype=bool)
  local = np.array([[-config.rear, -config.half_width], [config.front, -config.half_width],
                    [config.front, config.half_width], [-config.rear, config.half_width]])
  c, sn = np.cos(yaw)[:, None], np.sin(yaw)[:, None]
  corners = np.stack((xy[:, 0, None]+c*local[:, 0]-sn*local[:, 1], xy[:, 1, None]+sn*local[:, 0]+c*local[:, 1]), axis=-1)
  applicability = np.zeros((2, len(xy)), dtype=bool)
  confidence = np.zeros((2, len(xy)))
  side_clearance = np.full((2, len(xy)), np.inf)
  for index in range(2):
    if reliable[index]:
      _, applicability[index] = boundary_association(xy, lines[index])
      _, corner_applicability = boundary_association(corners.reshape(-1, 2), lines[index])
      body_applicability[index] = corner_applicability.reshape(len(xy), 4).all(axis=1)
      score = 1.-stds[index]/(2*config.boundary_std_max)
      confidence[index] = applicability[index]*score
      boundaries.append(ObservedBoundary(lines[index], 1 if index == 0 else -1, float(erosion[index]), sources[index],
                                         stds[index], score, applicability[index]))
      side_clearance[index] = reliable_body_clearance(xy, yaw, boundaries[-1:], reference_xy=xy,
                                                       front=config.front, rear=config.rear, half_width=config.half_width)
  clearance = np.min(side_clearance, axis=0)
  # Unknown space does not freeze the model pose. Reliable constraints remain
  # binding in the final validator, including when the original path conflicts.
  room = np.full((2, len(xy)), config.max_deviation)
  for index in range(2):
    # Only an observed inner lane can justify expanding toward that side.
    # A road edge says nothing about the intervening lane's traffic direction.
    # Complete body coverage and positive margin are required; finite ends and
    # unknown space retain the original model-led budget. This is optimization
    # room at reference heading, not a substitute for final swept-body checking.
    if reliable[index] and sources[index] == 'inner_lanes':
      observed = body_applicability[index] & np.isfinite(side_clearance[index])
      room[index] = np.where(observed, np.maximum(room[index], side_clearance[index]), room[index])
  allowance = np.max(room, axis=0)
  radius = math.hypot(max(config.front, config.rear), config.half_width)
  heading_allowance = np.full(len(xy), min(np.pi/2, config.max_deviation/radius))
  try:
    reference_std = _array(position, 'yStd')[:len(xy)]
    path_std_max = float(max(reference_std)) if len(reference_std) else None
  except (KeyError, AttributeError, TypeError, ValueError):
    path_std_max = None
  source = 'model_path' if not boundaries else (boundaries[0].source if len({b.source for b in boundaries}) == 1 else 'mixed_observed')
  return PathInput(
    True, 'model_path_with_optional_boundaries', xy, yaw, distance, *lines,
    np.all(body_applicability, axis=0) & (clearance > 0), allowance, np.zeros(len(xy), dtype=bool), source,
    dict(lane_probability=float(np.nanmin(probs[1:3])) if np.isfinite(probs[1:3]).any() else None,
         boundary_std=[v if math.isfinite(v) else None for v in stds], uncertainty_margin=erosion.tolist(),
         model_path_y_std_max=path_std_max, boundary_sources=sources, boundary_reliable=reliable,
         boundary_applicability=applicability.tolist(), boundary_confidence=confidence.tolist(),
         boundary_confidence_policy='heuristic scalar std <= boundary_std_max; not full-horizon free-space confidence',
         boundary_std_max=config.boundary_std_max, observed_free_space_certified=False),
    source_time, complete, heading_allowance=heading_allowance, reliable_boundaries=tuple(boundaries),
    lateral_lower=-room[1], lateral_upper=room[0],
  )
