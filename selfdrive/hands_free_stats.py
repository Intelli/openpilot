#!/usr/bin/env python3
import datetime
import time
from dataclasses import asdict, dataclass
from typing import Any


PARAM_KEY = "HandsFreeDriveStats"
STATS_VERSION = 1
MAX_SAMPLE_GAP_S = 0.5
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
    from openpilot.common.swaglog import cloudlog
    cloudlog.exception(f"Failed to decode hands-free drive stats: {raw}")
    return HandsFreeStats()


def persist_stats(params: Any, stats: HandsFreeStats) -> None:
  params.put(PARAM_KEY, asdict(stats))


def main() -> None:
  import cereal.messaging as messaging

  from openpilot.common.params import Params
  from openpilot.common.realtime import Ratekeeper

  params = Params()
  accumulator = HandsFreeStatsAccumulator(load_stats(params))
  services = ["carState", "carStateSP", "selfdriveState"]
  sm = messaging.SubMaster(services, frequency=10)
  rk = Ratekeeper(10, print_delay_threshold=None)
  last_persist_time = time.monotonic()

  try:
    while True:
      sm.update(0)
      now = time.monotonic()
      messages_valid = all(sm.seen[s] and sm.valid[s] and now - sm.recv_time[s] <= MAX_SAMPLE_GAP_S for s in services)
      valid = messages_valid and sm["carStateSP"].handsOnWheelValid
      since = accumulator.stats.since or datetime.datetime.now(datetime.UTC).date().isoformat()
      accumulator.update(now, sm["carState"].vEgo, sm["selfdriveState"].enabled, sm["carStateSP"].handsOnWheel,
                         valid, since)

      if now - last_persist_time >= PERSIST_INTERVAL_S:
        persist_stats(params, accumulator.stats)
        last_persist_time = now
      rk.keep_time()
  finally:
    persist_stats(params, accumulator.stats)


if __name__ == "__main__":
  main()
