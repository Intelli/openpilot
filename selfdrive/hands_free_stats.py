#!/usr/bin/env python3
import datetime
import time
from dataclasses import asdict, dataclass
from typing import Any


PARAM_KEY = "HandsFreeDriveStats"
STATS_VERSION = 1
SAMPLE_INTERVAL_S = 0.5
MAX_SAMPLE_GAP_S = 0.75
PERSIST_INTERVAL_S = 60.0


@dataclass
class HandsFreeStats:
  version: int = STATS_VERSION
  since: str = ""
  handsFreeDistanceMeters: float = 0.0
  trackedDistanceMeters: float = 0.0


class HandsFreeStatsAccumulator:
  def __init__(self, stats: HandsFreeStats | None = None):
    self.stats = stats or HandsFreeStats()
    self._last_sample_time: float | None = None
    self._last_v_ego = 0.0
    self._last_enabled = False
    self._last_hands_on = False
    self._last_valid = False

  def update(self, now: float, v_ego: float, enabled: bool, hands_on: bool, valid: bool, since: str) -> None:
    if self._last_sample_time is not None:
      dt = now - self._last_sample_time
      if self._last_valid and 0.0 < dt <= MAX_SAMPLE_GAP_S:
        distance = abs(self._last_v_ego) * dt
        self.stats.trackedDistanceMeters += distance
        if self._last_enabled and not self._last_hands_on:
          self.stats.handsFreeDistanceMeters += distance

    if valid and not self.stats.since:
      self.stats.since = since

    self._last_sample_time = now
    self._last_v_ego = v_ego
    self._last_enabled = enabled
    self._last_hands_on = hands_on
    self._last_valid = valid


def load_stats(params: Any) -> HandsFreeStats:
  raw = params.get(PARAM_KEY)
  if not isinstance(raw, dict) or raw.get("version") != STATS_VERSION:
    return HandsFreeStats()

  try:
    tracked_distance = max(0.0, float(raw.get("trackedDistanceMeters", 0.0)))
    return HandsFreeStats(
      version=STATS_VERSION,
      since=str(raw.get("since", "")),
      handsFreeDistanceMeters=min(tracked_distance, max(0.0, float(raw.get("handsFreeDistanceMeters", 0.0)))),
      trackedDistanceMeters=tracked_distance,
    )
  except (TypeError, ValueError):
    return HandsFreeStats()


def persist_stats(params: Any, stats: HandsFreeStats) -> None:
  params.put_nonblocking(PARAM_KEY, asdict(stats))


class HandsFreeStatsCollector:
  def __init__(self, params: Any):
    self.params = params
    self.accumulator = HandsFreeStatsAccumulator(load_stats(params))
    self._last_sample_time: float | None = None
    self._last_persist_time = time.monotonic()
    self._valid = False
    self._dirty = False

  def update(self, sm: Any, eligible: bool, now: float | None = None) -> None:
    now = time.monotonic() if now is None else now
    messages_valid = eligible and all(sm.seen[s] and sm.alive[s] and sm.valid[s] for s in ("carState", "carStateSP", "carControl"))
    valid = messages_valid and sm["carStateSP"].handsOnWheelValid

    # Sample at 2 Hz, but invalidate immediately to avoid counting stale data after going offroad or losing HOD data.
    sample_due = valid and (self._last_sample_time is None or now - self._last_sample_time >= SAMPLE_INTERVAL_S)
    invalidated = self._valid and not valid
    if sample_due or invalidated:
      since = self.accumulator.stats.since or datetime.datetime.now(datetime.UTC).date().isoformat()
      self.accumulator.update(now, sm["carState"].vEgo, sm["carControl"].latActive, sm["carStateSP"].handsOnWheel, valid, since)
      self._last_sample_time = now
      self._valid = valid
      self._dirty = True

    if self._dirty and (invalidated or now - self._last_persist_time >= PERSIST_INTERVAL_S):
      persist_stats(self.params, self.accumulator.stats)
      self._last_persist_time = now
      self._dirty = False
