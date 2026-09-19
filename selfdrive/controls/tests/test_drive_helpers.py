from types import SimpleNamespace

import pytest
from cereal import log

from openpilot.selfdrive.controls.lib.drive_helpers import get_calibrated_lateral_active, get_kona_non_scc_lateral_active, get_lateral_active


@pytest.mark.parametrize("normal_active,aol", [(False, True), (True, False), (True, True)])
@pytest.mark.parametrize("status,healthy,expected", [
  ("uncalibrated", True, False), ("invalid", True, False), ("recalibrating", True, False),
  ("calibrated", False, False), ("calibrated", True, True),
])
def test_final_ev9_calibration_gate_blocks_stale_aol_and_normal_requests(normal_active, aol, status, healthy, expected):
  class CalibrationSM(dict):
    def all_checks(self, services):
      assert services == ['liveCalibration']
      return healthy

  sm = CalibrationSM(liveCalibration=SimpleNamespace(calStatus=getattr(log.LiveCalibrationData.Status, status), calPerc=100))
  request = get_lateral_active(normal_active, normal_active, aol, False, False, False, False, True)
  assert request
  assert get_calibrated_lateral_active(request, sm) is expected


def test_final_calibration_gate_cannot_create_a_lateral_request():
  sm = SimpleNamespace(all_checks=lambda _: True)
  assert not get_calibrated_lateral_active(False, sm)


def test_get_lateral_active_requires_enabled_without_aol():
  assert not get_lateral_active(False, True, False, False, False, False, False, True)


def test_get_lateral_active_allows_aol_while_disabled():
  assert get_lateral_active(False, False, True, False, False, False, False, True)


def test_get_lateral_active_does_not_retry_after_a_latched_temporary_fault():
  assert not get_lateral_active(False, False, True, False, False, False, False, True, True)
  assert get_lateral_active(False, False, True, False, False, False, False, True, False)


def test_kona_non_scc_aol_waits_for_driver_steering_to_release():
  assert not get_kona_non_scc_lateral_active(
    False, False, True, False, False, False, False, True, True, False,
  )
  assert get_kona_non_scc_lateral_active(
    False, False, True, False, False, False, False, True, False, False,
  )
  assert get_kona_non_scc_lateral_active(
    False, False, True, False, False, False, False, True, True, True,
  )


def test_kona_non_scc_aol_gate_does_not_change_fault_or_normal_lateral_gates():
  assert not get_kona_non_scc_lateral_active(
    False, False, True, True, False, False, False, True, False, False,
  )
  assert get_kona_non_scc_lateral_active(
    True, True, False, False, False, False, False, True, True, False,
  )


def test_kona_non_scc_recovers_after_temporary_fault_clears():
  assert not get_kona_non_scc_lateral_active(
    False, False, True, True, False, False, False, True, False, True,
  )
  assert not get_kona_non_scc_lateral_active(
    False, False, True, False, False, False, False, True, True, False,
  )
  assert get_kona_non_scc_lateral_active(
    False, False, True, False, False, False, False, True, False, False,
  )


def test_get_lateral_active_honors_manual_pause_while_cruise_is_engaged():
  assert not get_lateral_active(True, True, False, False, False, False, False, False)
