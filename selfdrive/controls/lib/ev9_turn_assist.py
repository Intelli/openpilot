"""Road-edge veto for extended-speed EV9 turn lead, independent of trajectory mode.

This is a short constant-curvature body projection, not a drivable-space planner.
Uncertain clearance withdraws only the added assistance; the model still owns
the underlying command. Unobserved curbs/obstacles cannot be ruled out here.
"""
import math

import numpy as np

from openpilot.selfdrive.controls.lib.ev9_path_frames import static_model_points_to_rear_axle
from openpilot.selfdrive.controls.lib.ev9_path_planner import (
  MODEL_GEOMETRY, MOUNT_LATERAL_UNCERTAINTY, MOUNT_LONGITUDINAL_UNCERTAINTY,
)

MAX_MODEL_AGE = .2
EDGE_STD_FULL = .3
EDGE_STD_MAX = .5
SWEEP_STEP = .5


def _forward_edge_clear(points, xy, yaw, side, front, rear, half_width):
  """Check padded rectangles against a finite forward-x edge, without extrapolation.

  Segment/rectangle intersections cover concave edges and between-corner cuts.
  Corner side checks also reject bodies entirely beyond the edge. The caller
  pads the rectangle for uncertainty and motion between successive arc poses.
  """
  c, s = np.cos(yaw), np.sin(yaw)
  local = np.array([[-rear, -half_width], [front, -half_width], [front, half_width], [-rear, half_width]])
  corners_x = xy[:, 0, None] + c[:, None] * local[:, 0] - s[:, None] * local[:, 1]
  corners_y = xy[:, 1, None] + s[:, None] * local[:, 0] + c[:, None] * local[:, 1]
  if np.max(corners_x) > points[-1, 0]:
    return False
  observed = corners_x >= points[0, 0]
  edge_y = np.interp(corners_x, points[:, 0], points[:, 1])
  if np.any(observed & (side * (edge_y - corners_y) <= 0.)):
    return False
  relative = points[None, :, :] - xy[:, None, :]
  vertices = np.stack((c[:, None] * relative[..., 0] + s[:, None] * relative[..., 1],
                        -s[:, None] * relative[..., 0] + c[:, None] * relative[..., 1]), axis=-1)
  delta = np.diff(vertices, axis=1)
  start = vertices[:, :-1]
  parallel = abs(delta) <= 1e-12
  lower, upper = np.array([-rear, -half_width]), np.array([front, half_width])
  outside = np.any(parallel & ((start < lower) | (start > upper)), axis=-1)
  divisor = np.where(parallel, 1., delta)
  ta, tb = (lower - start) / divisor, (upper - start) / divisor
  enter = np.maximum(np.max(np.where(parallel, -np.inf, np.minimum(ta, tb)), axis=-1), 0.)
  leave = np.minimum(np.min(np.where(parallel, np.inf, np.maximum(ta, tb)), axis=-1), 1.)
  return not np.any(~outside & (enter <= leave))


def ev9_turn_assist_authority(model, curvature, preview_distance, *, base_curvature=0., model_age, blindspot, model_valid):
  """Return added-command authority, using controls' positive-RIGHT curvature.

  Check the turn-side road edge directly, never substitute a lane line. Model
  uncertainty is a heuristic, not a calibrated curb-detection probability.
  Confidence fades authority before its cutoff; clearance is checked for that
  actual blended command. The observed forward sweep includes the full body;
  the part behind the camera remains unobserved (no endpoint extrapolation).
  """
  if (blindspot or not model_valid or not all(math.isfinite(v) for v in (curvature, base_curvature, preview_distance, model_age)) or
      not -.01 <= model_age <= MAX_MODEL_AGE or not 0. < preview_distance <= 14. or curvature == 0.):
    return 0.
  try:
    index = 1 if curvature > 0. else 0
    std = float(model.roadEdgeStds[index])
    if not math.isfinite(std) or not 0. <= std < EDGE_STD_MAX:
      return 0.
    authority = min((EDGE_STD_MAX - std) / (EDGE_STD_MAX - EDGE_STD_FULL), 1.)
    authority = authority * authority * (3. - 2. * authority)
    applied = base_curvature + authority * (curvature - base_curvature)
    if applied * curvature <= 0. or abs(applied) * preview_distance >= math.pi / 2.:
      return 0.

    edge = model.roadEdges[index]
    points = np.column_stack((edge.x, edge.y))
    # Bounded model-size input and forward coverage; a truncated edge is not an opening.
    if not 2 <= len(points) <= 33 or points[0, 0] > .1 or np.any(np.diff(points[:, 0]) <= 1e-6):
      return 0.
    points = static_model_points_to_rear_axle(points, MODEL_GEOMETRY.mount)
    front = MODEL_GEOMETRY.front + MOUNT_LONGITUDINAL_UNCERTAINTY
    rear = MODEL_GEOMETRY.rear + MOUNT_LONGITUDINAL_UNCERTAINTY
    half_width = MODEL_GEOMETRY.half_width + MOUNT_LATERAL_UNCERTAINTY
    radius = math.hypot(max(front, rear), half_width)
    distance = np.linspace(0., preview_distance, math.ceil(preview_distance / SWEEP_STEP) + 1)
    k = -applied  # Geometry uses positive LEFT.
    yaw = k * distance
    xy = np.column_stack((np.sin(yaw) / k, 2. * np.sin(yaw / 2.) ** 2 / k))
    # Include between-sample motion of every body point, not only sampled corners.
    motion_margin = .5 * (distance[1] - distance[0]) * (1. + radius * abs(k))
    padding = MODEL_GEOMETRY.margin + std + motion_margin
    clear = _forward_edge_clear(points, xy, yaw, -1 if curvature > 0. else 1,
                                front + padding, rear + padding, half_width + padding)
    return authority if clear else 0.
  except (AttributeError, ValueError, TypeError, IndexError, OverflowError):
    return 0.
