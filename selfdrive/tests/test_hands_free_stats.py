import pytest

from openpilot.selfdrive.hands_free_stats import HandsFreeStats, HandsFreeStatsAccumulator, load_stats, persist_stats


class FakeParams:
  def __init__(self, value=None):
    self.value = value

  def get(self, _key):
    return self.value

  def put(self, _key, value):
    self.value = value


def test_accumulates_only_valid_hod_distance():
  accumulator = HandsFreeStatsAccumulator()
  accumulator.update(0.0, 10.0, True, False, True, "2026-06-06")
  accumulator.update(0.1, 10.0, True, True, True, "2026-06-06")
  accumulator.update(0.2, 10.0, False, False, True, "2026-06-06")
  accumulator.update(0.3, 10.0, True, False, False, "2026-06-06")
  accumulator.update(0.4, 10.0, True, False, True, "2026-06-06")
  accumulator.update(1.0, 10.0, True, False, True, "2026-06-06")

  assert accumulator.stats.trackedDistanceMeters == pytest.approx(3.0)
  assert accumulator.stats.handsFreeDistanceMeters == pytest.approx(1.0)
  assert accumulator.stats.since == "2026-06-06"


def test_load_and_persist_stats():
  params = FakeParams()
  stats = HandsFreeStats(since="2026-06-06", handsFreeDistanceMeters=123.4, trackedDistanceMeters=234.5)
  persist_stats(params, stats)

  assert load_stats(params) == stats


@pytest.mark.parametrize("value", [None, {}, {"version": 999}, {"version": 1, "trackedDistanceMeters": "bad"}])
def test_invalid_persisted_stats_reset(value):
  assert load_stats(FakeParams(value)) == HandsFreeStats()


def test_loaded_hands_free_distance_is_bounded_by_tracked_distance():
  stats = load_stats(FakeParams({"version": 1, "handsFreeDistanceMeters": 20.0, "trackedDistanceMeters": 10.0}))
  assert stats.handsFreeDistanceMeters == stats.trackedDistanceMeters == 10.0
