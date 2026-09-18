"""Pure NumPy complete-body checks against observed fixed-forward-x boundaries.

The rectangle is checked exactly at each supplied pose; continuous travel between
poses is not certified. No extrapolation, road permission or obstacle inference.
"""

import math

import numpy as np


def body_inside_observed(xy, yaw, left, right, *, front, rear, half_width, left_margin, right_margin):
  """Reject a body touching/leaving the observed, vertically eroded road polygon.

  Margins contract each fixed-x boundary toward the reference road interior in y;
  they are not normal-distance offsets on a curved boundary. Callers supply body
  dimensions including any required mounting/model uncertainty expansion.
  """
  try:
    xy, yaw, left, right = (np.asarray(value, dtype=float) for value in (xy, yaw, left, right))
    scalars = (front, rear, half_width, left_margin, right_margin)
    if not all(math.isfinite(v) for v in scalars) or min(front, rear, half_width) <= 0 or min(left_margin, right_margin) < 0:
      return False
    if xy.ndim != 2 or xy.shape[1] != 2 or len(xy) == 0 or yaw.shape != (len(xy),) or not np.isfinite(np.r_[xy.ravel(), yaw]).all():
      return False
    for boundary in (left, right):
      if boundary.ndim != 2 or boundary.shape[1] != 2 or len(boundary) < 2 or not np.isfinite(boundary).all():
        return False
      if np.any(np.diff(boundary[:, 0]) <= 1e-8):
        return False
    lo, hi = max(left[0, 0], right[0, 0]), min(left[-1, 0], right[-1, 0])
    if hi - lo <= 1e-8:
      return False
    knots = np.unique(np.r_[lo, hi, left[(left[:, 0] > lo) & (left[:, 0] < hi), 0], right[(right[:, 0] > lo) & (right[:, 0] < hi), 0]])
    ly = np.interp(knots, left[:, 0], left[:, 1]) - left_margin
    ry = np.interp(knots, right[:, 0], right[:, 1]) + right_margin
    if np.any(ly - ry <= 1e-8):
      return False
    polygon = np.vstack((np.column_stack((knots, ly)), np.column_stack((knots[::-1], ry[::-1]))))
    a, b = polygon, np.roll(polygon, -1, axis=0)
    local = np.array([[-rear, -half_width], [front, -half_width], [front, half_width], [-rear, half_width]])
    for start in range(0, len(xy), 64):
      p, h = xy[start : start + 64], yaw[start : start + 64]
      c, s = np.cos(h), np.sin(h)
      corners = np.stack(
        (p[:, 0, None] + c[:, None] * local[:, 0] - s[:, None] * local[:, 1], p[:, 1, None] + s[:, None] * local[:, 0] + c[:, None] * local[:, 1]), axis=-1
      )
      # Strict corner containment includes the finite observation end-caps.
      cx, cy = corners[:, :, 0], corners[:, :, 1]
      if np.any(cx <= lo + 1e-9) or np.any(cx >= hi - 1e-9) or np.any(cy >= np.interp(cx, knots, ly) - 1e-9) or np.any(cy <= np.interp(cx, knots, ry) + 1e-9):
        return False
      # A concave boundary may enter and leave between body corners. Transform
      # every boundary segment into each body frame and intersect the CLOSED box
      # with slab clipping; any touch or intrusion rejects the entire rectangle.
      low, high = corners.min(axis=1), corners.max(axis=1)
      boxes = np.all(np.maximum(low[:, None, :], np.minimum(a, b)) <= np.minimum(high[:, None, :], np.maximum(a, b)) + 1e-9, axis=2)
      body, edge = np.nonzero(boxes)
      if not len(body):
        continue
      relative_a, relative_b = a[edge] - p[body], b[edge] - p[body]

      def to_local(q, cosine=c[body], sine=s[body]):
        return np.column_stack((cosine * q[:, 0] + sine * q[:, 1], -sine * q[:, 0] + cosine * q[:, 1]))

      q = to_local(relative_a)
      delta = to_local(relative_b) - q
      enter, leave = np.zeros(len(q)), np.ones(len(q))
      possible = np.ones(len(q), dtype=bool)
      for axis, lower, upper in ((0, -rear, front), (1, -half_width, half_width)):
        parallel = abs(delta[:, axis]) <= 1e-12
        possible &= ~(parallel & ((q[:, axis] < lower - 1e-9) | (q[:, axis] > upper + 1e-9)))
        moving = ~parallel
        ta = (lower - q[moving, axis]) / delta[moving, axis]
        tb = (upper - q[moving, axis]) / delta[moving, axis]
        enter[moving] = np.maximum(enter[moving], np.minimum(ta, tb))
        leave[moving] = np.minimum(leave[moving], np.maximum(ta, tb))
      if np.any(possible & (enter <= leave + 1e-9)):
        return False
    return True
  except (ValueError, TypeError, IndexError, OverflowError):
    return False
