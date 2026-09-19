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
    best_extent = 0.
    records = [record for record in reversed(self.records) if 0 <= now-record[0] <= self.max_age]
    transformed_records = [tuple(self.transform(line, record[1], pose) for line in record[2]) for record in records]
    matches = self._matches(transformed_records, current)
    for record, transformed, match in zip(records, transformed_records, matches, strict=True):
      observed, _, _, old_margin, _ = record
      discrepancy, counts, reversed_overlap = match
      prefixes = [line[:count] for line, count in zip(transformed, counts, strict=True)] if len(counts) == 2 else []
      if reversed_overlap:
        self.reset()
        result, margin = current, np.asarray(erosion).copy()
        times = tuple(np.full(len(line), stamp) for line in current)
        break
      if len(prefixes) != 2:
        continue
      if max(discrepancy) > self.overlap_tolerance:
        self.reset()
        result, margin = current, np.asarray(erosion).copy()
        times = tuple(np.full(len(line), stamp) for line in current)
        break
      candidate = tuple(np.vstack((prefix, new)) for prefix, new in zip(prefixes, current, strict=True))
      # Adequacy concerns rear coverage in CURRENT vehicle coordinates only;
      # matching and extension themselves do not assume forward-x boundaries.
      extent = min(
        float(np.linalg.norm(new[0]-prefix[0])) if len(prefix) else 0. for prefix, new in zip(prefixes, current, strict=True))
      adequate = max(line[0, 0] for line in candidate) <= -rear_extent
      if adequate or extent > best_extent:
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

  def _matches(self, observations, current):
    """Batch equal-sized recorded boundaries; inspect every observation in order.

    This retains the same newest-adequate selection without hundreds of small
    NumPy calls when none of the retained observations covers the rear body.
    """
    result = [[[], [], False] for _ in observations]
    for side, new in enumerate(current):
      new_arc = np.r_[0., np.cumsum(np.linalg.norm(np.diff(new, axis=0), axis=1))]
      sample = np.unique(np.r_[0., min(2., new_arc[-1]), new_arc[new_arc <= 2.]])
      points = np.column_stack([np.interp(sample, new_arc, new[:, axis]) for axis in (0, 1)])
      groups = {}
      for index, pair in enumerate(observations):
        groups.setdefault(len(pair[side]), []).append(index)
      for indices in (group[start:start+32] for group in groups.values() for start in range(0, len(group), 32)):
        old = np.asarray([observations[index][side] for index in indices])
        segment = np.diff(old, axis=1)
        lengths = np.linalg.norm(segment, axis=2)
        arc = np.column_stack((np.zeros(len(old)), np.cumsum(lengths, axis=1)))
        relative = points[None, :, None, :] - old[:, None, :-1, :]
        fraction = np.clip(np.sum(relative*segment[:, None], axis=3)/np.sum(segment**2, axis=2)[:, None], 0., 1.)
        distances = np.linalg.norm(relative-fraction[..., None]*segment[:, None], axis=3)
        nearest = np.argmin(distances, axis=2)
        projected = arc[:, None, :-1] + fraction*lengths[:, None]
        progress = np.take_along_axis(projected, nearest[..., None], axis=2)[..., 0]
        error = np.take_along_axis(distances, nearest[..., None], axis=2)[..., 0].max(axis=1)
        reversed_overlap = np.any(np.diff(progress, axis=1) <= 1e-5, axis=1)
        complete = progress[:, -1]-progress[:, 0] >= .8*sample[-1]
        ambiguous = np.any((distances <= self.overlap_tolerance) & (abs(projected-progress[..., None]) > 2.), axis=(1, 2))
        counts = np.sum(arc < progress[:, :1]-1e-5, axis=1)
        for row, index in enumerate(indices):
          if len(result[index][1]) != side or result[index][2]:
            continue
          if reversed_overlap[row]:
            result[index][2] = True
          elif complete[row] and not ambiguous[row]:
            result[index][0].append(float(error[row]))
            result[index][1].append(int(counts[row]))
    return result
