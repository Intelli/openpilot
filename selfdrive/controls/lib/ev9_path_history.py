"""Short-lived observed rear boundary memory, not a road map or occupancy claim."""
from collections import deque

import numpy as np


class RearBoundaryHistory:
  def __init__(self, max_age=8., overlap_tolerance=.20):
    self.max_age = max_age
    self.overlap_tolerance = overlap_tolerance
    self.reset()

  def reset(self):
    self.records = deque(maxlen=161)
    self.generation = None
    self.point_times = (np.empty(0), np.empty(0))

  @staticmethod
  def transform(points, source, target):
    angle = source[2] - target[2]
    c, s = np.cos(angle), np.sin(angle)
    ct, st = np.cos(target[2]), np.sin(target[2])
    offset = (np.asarray(source[:2]) - target[:2]) @ np.array([[ct, -st], [st, ct]])
    return points @ np.array([[c, s], [-s, c]]) + offset

  def extend(self, left, right, erosion, *, pose, stamp, now, generation, source, rear_extent=0.):
    """Prepend actual old points only; never store merged or restamped history.

    The join must agree over the first two metres of current observation. The
    maximum observed join discrepancy is added to the retained erosion. This is
    geometric consistency, not a guarantee that a previously empty area is empty.
    """
    current = (left, right)
    if (self.generation != generation or (self.records and
        (stamp < self.records[-1][0] or source != self.records[-1][4]))):
      self.reset()
    self.generation = generation
    while self.records and now - self.records[0][0] > self.max_age:
      self.records.popleft()
    result = current
    times = tuple(np.full(len(line), stamp) for line in current)
    margin = np.asarray(erosion).copy()
    best_extent = max(line[0, 0] for line in current)
    for observed, origin, lines, old_margin, _ in reversed(self.records):
      if not 0 <= now - observed <= self.max_age:
        continue
      transformed = tuple(self.transform(line, origin, pose) for line in lines)
      if any(np.any(np.diff(line[:, 0]) <= 1e-5) for line in transformed):
        self.reset()
        result, margin = current, np.asarray(erosion).copy()
        times = tuple(np.full(len(line), stamp) for line in current)
        break
      discrepancy = []
      prefixes = []
      for old, new in zip(transformed, current, strict=True):
        start = new[0, 0]
        end = min(new[-1, 0], old[-1, 0], start + 2.)
        if old[0, 0] > start or end <= start:
          break
        knots = np.unique(np.r_[start, end, old[:, 0], new[:, 0]])
        knots = knots[(knots >= start) & (knots <= end)]
        discrepancy.append(float(np.max(abs(np.interp(knots, old[:, 0], old[:, 1]) - np.interp(knots, new[:, 0], new[:, 1])))))
        prefixes.append(old[old[:, 0] < start - 1e-5])
      if len(prefixes) != 2:
        continue
      if max(discrepancy) > self.overlap_tolerance:
        self.reset()
        result, margin = current, np.asarray(erosion).copy()
        times = tuple(np.full(len(line), stamp) for line in current)
        break
      candidate = tuple(np.vstack((prefix, new)) for prefix, new in zip(prefixes, current, strict=True))
      extent = max(line[0, 0] for line in candidate)
      adequate = extent <= -rear_extent
      if adequate or extent < best_extent:
        result = candidate
        times = tuple(np.r_[np.full(len(prefix), observed), np.full(len(new), stamp)] for prefix, new in zip(prefixes, current, strict=True))
        margin = np.maximum(erosion, old_margin) + np.asarray(discrepancy)
        best_extent = extent
      # Prefer the newest observation covering the complete rear envelope. If
      # none does, retain the greatest observed extent without filling any gaps.
      if adequate:
        break
    self.generation = generation
    if not self.records or stamp > self.records[-1][0]:
      self.records.append((stamp, tuple(pose), tuple(line.copy() for line in current), np.asarray(erosion).copy(), source))
    self.point_times = times
    return *result, margin
