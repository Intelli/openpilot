"""Observed ordered 2D corridor geometry; no extrapolation or obstacle inference."""
import math
from dataclasses import dataclass

import numpy as np


def _cross(a, b):
  return a[..., 0] * b[..., 1] - a[..., 1] * b[..., 0]


def observed_polygon(left, right):
  """Validate one unambiguous strip, with finite observation end caps.

  Both boundaries run in travel order; left followed by reversed right must
  form a simple clockwise polygon. Boundary crossings/touches are unknown.
  """
  lines = [np.asarray(line, dtype=float) for line in (left, right)]
  for line in lines:
    if line.ndim != 2 or line.shape[1] != 2 or len(line) < 2 or not np.isfinite(line).all():
      raise ValueError('invalid_boundary')
    if np.any(np.linalg.norm(np.diff(line, axis=0), axis=1) <= 1e-8):
      raise ValueError('duplicate_boundary_point')
  polygon = np.vstack((lines[0], lines[1][::-1]))
  a, b = polygon, np.roll(polygon, -1, axis=0)
  if np.sum(_cross(a, b)) >= -1e-8 or np.any(np.linalg.norm(b-a, axis=1) <= 1e-8):
    raise ValueError('reversed_or_missing_boundaries')
  # Bounding boxes prune disjoint pairs before orientation arithmetic.
  for i in range(len(a)):
    j = np.arange(i+2, len(a))
    if i == 0:
      j = j[j != len(a)-1]
    overlap = np.all(np.maximum(np.minimum(a[i], b[i]), np.minimum(a[j], b[j])) <=
                     np.minimum(np.maximum(a[i], b[i]), np.maximum(a[j], b[j])) + 1e-9, axis=1)
    j = j[overlap]
    if not len(j):
      continue
    c, d = _cross(b[i]-a[i], a[j]-a[i]), _cross(b[i]-a[i], b[j]-a[i])
    e, f = _cross(b[j]-a[j], a[i]-a[j]), _cross(b[j]-a[j], b[i]-a[j])
    if np.any((c*d <= 1e-18) & (e*f <= 1e-18)):
      raise ValueError('crossed_or_ambiguous_boundaries')
  return polygon


def _inside(points, polygon):
  a, b = polygon, np.roll(polygon, -1, axis=0)
  x, y = points[..., 0, None], points[..., 1, None]
  dy = b[:, 1]-a[:, 1]
  crossing = (a[:, 1] > y) != (b[:, 1] > y)
  at_x = a[:, 0] + (y-a[:, 1]) * (b[:, 0]-a[:, 0]) / np.where(abs(dy) > 1e-15, dy, 1.)
  return np.sum(crossing & (x < at_x), axis=-1) % 2 == 1


def _clearance(xy, yaw, polygon, margins, front, rear, half_width, *, side=0, reference_xy=None):
  """Exact rectangle-to-segment distance, negative for a non-contained body."""
  a, b = (polygon[:-1], polygon[1:]) if side else (polygon, np.roll(polygon, -1, axis=0))
  delta = b-a
  local = np.array([[-rear, -half_width], [front, -half_width], [front, half_width], [-rear, half_width]])
  output = np.empty(len(xy))
  for start in range(0, len(xy), 32):
    p, h = xy[start:start+32], yaw[start:start+32]
    c, s = np.cos(h), np.sin(h)
    corners = np.stack((p[:, 0, None] + c[:, None]*local[:, 0] - s[:, None]*local[:, 1],
                        p[:, 1, None] + s[:, None]*local[:, 0] + c[:, None]*local[:, 1]), axis=-1)
    q = corners[:, :, None, :] - a
    t = np.clip(np.sum(q*delta, axis=-1)/np.sum(delta**2, axis=-1), 0., 1.)
    corner_distance = np.linalg.norm(q-t[..., None]*delta, axis=-1).min(axis=1)
    relative = polygon[None, :, :]-p[:, None, :]
    vertices = np.stack((c[:, None]*relative[..., 0]+s[:, None]*relative[..., 1],
                         -s[:, None]*relative[..., 0]+c[:, None]*relative[..., 1]), axis=-1)
    vertex_distance = np.linalg.norm(np.maximum(np.maximum(np.array([-rear, -half_width])-vertices,
                                                           vertices-np.array([front, half_width])), 0.), axis=-1)
    endpoint_distance = np.minimum(vertex_distance[:, :-1], vertex_distance[:, 1:]) if side else np.minimum(
      vertex_distance, np.roll(vertex_distance, -1, axis=1))
    distance = np.minimum(corner_distance, endpoint_distance)
    d = np.diff(vertices, axis=1) if side else np.roll(vertices, -1, axis=1)-vertices
    if side:
      vertices = vertices[:, :-1]
    enter, leave = np.zeros(distance.shape), np.ones(distance.shape)
    possible = np.ones(distance.shape, dtype=bool)
    for axis, lower, upper in ((0, -rear, front), (1, -half_width, half_width)):
      parallel = abs(d[..., axis]) <= 1e-12
      possible &= ~(parallel & ((vertices[..., axis] < lower) | (vertices[..., axis] > upper)))
      divisor = np.where(parallel, 1., d[..., axis])
      ta, tb = (lower-vertices[..., axis])/divisor, (upper-vertices[..., axis])/divisor
      enter = np.maximum(enter, np.where(parallel, -np.inf, np.minimum(ta, tb)))
      leave = np.minimum(leave, np.where(parallel, np.inf, np.maximum(ta, tb)))
    distance[possible & (enter <= leave)] = 0.
    gap = np.min(distance-margins, axis=1)
    if side:
      reference = reference_xy[start:start+len(p)]
      _, applicable = boundary_association(reference, polygon)
      # Signed nearest-edge distances at EACH corner avoid extending one
      # concave segment's half-plane across its adjacent observed segment.
      signed = signed_boundary_distance(corners.reshape(-1, 2), polygon, side).reshape(len(p), 4).min(axis=1)
      gap = np.minimum(gap, np.where(applicable, signed-float(margins), np.inf))
    else:
      gap[~np.all(_inside(corners, polygon), axis=1)] = -np.inf
    output[start:start+len(p)] = gap
  return output


def body_clearance_observed(xy, yaw, left, right, *, front, rear, half_width, left_margin, right_margin):
  """Per-pose complete-body clearance to observed edges, with normal margins.

  Positive clearance certifies arbitrary translations of smaller magnitude at
  fixed heading. Finite end caps have zero extra margin but remain impassable.
  """
  xy, yaw = np.asarray(xy, dtype=float), np.asarray(yaw, dtype=float)
  if xy.ndim != 2 or xy.shape[1] != 2 or yaw.shape != (len(xy),) or not np.isfinite(np.r_[xy.ravel(), yaw]).all():
    raise ValueError('invalid_pose')
  if not all(math.isfinite(v) for v in (front, rear, half_width, left_margin, right_margin)):
    raise ValueError('invalid_dimensions')
  if min(front, rear, half_width) <= 0 or min(left_margin, right_margin) < 0:
    raise ValueError('invalid_dimensions')
  polygon = observed_polygon(left, right)
  margins = np.r_[np.full(len(left)-1, left_margin), 0., np.full(len(right)-1, right_margin), 0.]
  return _clearance(xy, yaw, polygon, margins, front, rear, half_width)


def body_inside_observed(xy, yaw, left, right, *, front, rear, half_width, left_margin, right_margin):
  """Certify supplied poses AND their linear-position/shortest-yaw transitions.

  A distance bound on rigid-body motion certifies each segment; uncertain
  segments are bisected, never accepted from finite sampling alone. Callers
  must supply contiguous trajectory runs, not concatenate separated changes.
  """
  try:
    xy, yaw = np.asarray(xy, dtype=float), np.asarray(yaw, dtype=float)
    clearance = body_clearance_observed(xy, yaw, left, right, front=front, rear=rear, half_width=half_width,
                                        left_margin=left_margin, right_margin=right_margin)
    if not len(clearance) or np.any(clearance <= 1e-9):
      return False
    polygon = observed_polygon(left, right)
    margins = np.r_[np.full(len(left)-1, left_margin), 0., np.full(len(right)-1, right_margin), 0.]
    radius = math.hypot(max(front, rear), half_width)
    p, q, h, k = xy[:-1], xy[1:], yaw[:-1], yaw[1:]
    ca, cb = clearance[:-1], clearance[1:]
    for _ in range(16):
      angle = (k-h+np.pi) % (2*np.pi)-np.pi
      motion = np.linalg.norm(q-p, axis=1) + radius*abs(angle)
      uncertain = np.maximum(ca, cb) <= motion + 1e-9
      if not np.any(uncertain):
        return True
      if np.count_nonzero(uncertain) > 4096:
        return False
      p, q, h, angle, ca, cb = (v[uncertain] for v in (p, q, h, angle, ca, cb))
      midpoint, heading = (p+q)/2, h+angle/2
      middle = _clearance(midpoint, heading, polygon, margins, front, rear, half_width)
      if np.any(middle <= 1e-9):
        return False
      p, q = np.vstack((p, midpoint)), np.vstack((midpoint, q))
      h, k = np.r_[h, heading], np.r_[heading, h+angle]
      ca, cb = np.r_[ca, middle], np.r_[middle, cb]
    return False
  except (ValueError, TypeError, IndexError, OverflowError):
    return False


@dataclass(frozen=True)
class ObservedBoundary:
  """Optional reliable finite evidence, not a complete drivable-space polygon."""
  points: np.ndarray
  side: int  # +1 left / -1 right, in forward observation order
  margin: float
  source: str
  std: float
  confidence: float  # Explicit heuristic score; not a calibrated probability.
  applicable: np.ndarray  # Associated at each original reference station.


def boundary_association(reference_xy, points):
  """Nearest finite segment, with no tangent/side extrapolation past endpoints."""
  delta = np.diff(points, axis=0)
  relative = np.asarray(reference_xy)[:, None]-points[:-1]
  fraction = np.sum(relative*delta, axis=2)/np.sum(delta**2, axis=1)
  distance = np.linalg.norm(relative-np.clip(fraction, 0., 1.)[..., None]*delta, axis=2)
  index = np.argmin(distance, axis=1)
  selected = fraction[np.arange(len(index)), index]
  return index, ((selected >= 0.) | (index > 0)) & ((selected <= 1.) | (index < len(delta)-1))


def signed_boundary_distance(points, boundary, side):
  delta = np.diff(boundary, axis=0)
  index, applicable = boundary_association(points, boundary)
  edge = delta[index]
  fraction = np.sum((points-boundary[index])*edge, axis=1)/np.sum(edge**2, axis=1)
  closest = boundary[index]+np.clip(fraction, 0., 1.)[:, None]*edge
  tangent = edge/np.linalg.norm(edge, axis=1)[:, None]
  previous = (fraction < 0.) & (index > 0)
  following = (fraction > 1.) & (index < len(delta)-1)
  for mask, adjacent in ((previous, np.maximum(index-1, 0)), (following, np.minimum(index+1, len(delta)-1))):
    neighbor = delta[adjacent]/np.linalg.norm(delta[adjacent], axis=1)[:, None]
    tangent[mask] += neighbor[mask]
  tangent /= np.maximum(np.linalg.norm(tangent, axis=1)[:, None], 1e-15)
  return np.where(applicable, -side*_cross(tangent, points-closest), np.inf)


def reliable_body_clearance(xy, yaw, boundaries, *, reference_xy, front, rear, half_width):
  """Clearance to reliable finite segments and applicable side constraints."""
  xy, yaw, reference_xy = (np.asarray(value, dtype=float) for value in (xy, yaw, reference_xy))
  if (xy.ndim != 2 or xy.shape[1] != 2 or reference_xy.shape != xy.shape or yaw.shape != (len(xy),) or
      not np.isfinite(np.r_[xy.ravel(), yaw, reference_xy.ravel()]).all()):
    raise ValueError('invalid_pose')
  if not all(math.isfinite(v) and v > 0 for v in (front, rear, half_width)):
    raise ValueError('invalid_body')
  clearance = np.full(len(xy), np.inf)
  for boundary in boundaries:
    points = np.asarray(boundary.points, dtype=float)
    if (boundary.side not in (-1, 1) or not math.isfinite(boundary.margin) or boundary.margin < 0 or
        points.ndim != 2 or points.shape[1] != 2 or len(points) < 2 or not np.isfinite(points).all() or
        np.any(np.linalg.norm(np.diff(points, axis=0), axis=1) <= 1e-8)):
      raise ValueError('invalid_boundary')
    clearance = np.minimum(clearance, _clearance(xy, yaw, points, boundary.margin, front, rear, half_width,
                                                side=boundary.side, reference_xy=reference_xy))
  return clearance


def body_respects_observed(xy, yaw, geometry, *, reference_distance, front, rear, half_width):
  """Check only supplied reliable evidence, including the swept finite segments.

  True with no reliable boundaries means model-path refinement is unverified
  against boundaries; it is deliberately NOT a free-space certification.
  """
  try:
    xy, yaw, station = (np.asarray(value, dtype=float) for value in (xy, yaw, reference_distance))
    if station.shape != (len(xy),) or not np.isfinite(station).all() or np.any(np.diff(station) < 0):
      return False
    if not len(station) or station[0] < geometry.distance[0]-1e-8 or station[-1] > geometry.distance[-1]+1e-8:
      return False
    reference = np.column_stack([np.interp(station, geometry.distance, axis) for axis in geometry.xy.T])
    boundaries = geometry.reliable_boundaries
    def clearance(p, h, ref):
      return reliable_body_clearance(p, h, boundaries, reference_xy=ref, front=front, rear=rear, half_width=half_width)
    gap = clearance(xy, yaw, reference)
    if np.any(gap <= 1e-9):
      return False
    p, q, h, k, r, t = xy[:-1], xy[1:], yaw[:-1], yaw[1:], reference[:-1], reference[1:]
    ca, cb = gap[:-1], gap[1:]
    radius = math.hypot(max(front, rear), half_width)
    for _ in range(16):
      angle = (k-h+np.pi) % (2*np.pi)-np.pi
      motion = np.linalg.norm(q-p, axis=1)+radius*abs(angle)
      uncertain = np.maximum(ca, cb) <= motion+1e-9
      if not np.any(uncertain):
        return True
      if np.count_nonzero(uncertain) > 4096:
        return False
      p, q, h, angle, r, t, ca, cb = (v[uncertain] for v in (p, q, h, angle, r, t, ca, cb))
      mid, heading, ref = (p+q)/2, h+angle/2, (r+t)/2
      cm = clearance(mid, heading, ref)
      if np.any(cm <= 1e-9):
        return False
      p, q, h, k = np.vstack((p, mid)), np.vstack((mid, q)), np.r_[h, heading], np.r_[heading, h+angle]
      r, t, ca, cb = np.vstack((r, ref)), np.vstack((ref, t)), np.r_[ca, cm], np.r_[cm, cb]
    return False
  except (ValueError, TypeError, IndexError, AttributeError):
    return False
