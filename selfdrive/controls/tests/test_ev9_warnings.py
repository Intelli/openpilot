from types import SimpleNamespace

import pytest

from opendbc.car import structs
from opendbc.car.hyundai.values import CAR, HyundaiFlags
from openpilot.selfdrive.controls.lib.ev9_warnings import ev9_alert_speed_kph, steering_saturation_warning_allowed
from openpilot.selfdrive.controls.lib.latcontrol_angle import LatControlAngle


def make_cp(platform=CAR.KIA_EV9, angle_flag=True, angle_controller=True):
  return SimpleNamespace(carFingerprint=platform, flags=int(HyundaiFlags.CANFD_ANGLE_STEERING) if angle_flag else 0,
                         steerControlType=structs.CarParams.SteerControlType.angle if angle_controller else structs.CarParams.SteerControlType.torque,
                         steerLimitTimer=0.3, brand="hyundai")


@pytest.mark.parametrize("speed,angle,allowed", [(49.9, 0, False), (50, 0, False), (50.1, 0, True),
                                               (0, 89.9, False), (0, 90, True), (0, -90, True), (0, -119.9, True)])
def test_speed_and_angle_boundaries(speed, angle, allowed):
  assert steering_saturation_warning_allowed(make_cp(), SimpleNamespace(steeringAngleDesiredDeg=angle), speed / 3.6,
                                            SimpleNamespace()) == allowed


@pytest.mark.parametrize("cp", [make_cp(CAR.HYUNDAI_IONIQ_5_PE), make_cp(angle_flag=False), make_cp(angle_controller=False)])
def test_other_control_paths_unchanged(cp):
  assert steering_saturation_warning_allowed(cp, SimpleNamespace(steeringAngleDesiredDeg=0), 0, SimpleNamespace())
  assert LatControlAngle(cp, None, 0.01).sat_check_min_speed == 5


def test_missing_angle_telemetry_keeps_existing_warning():
  assert steering_saturation_warning_allowed(make_cp(), SimpleNamespace(), 0, SimpleNamespace())


@pytest.mark.parametrize("value,expected", [(None, 50), ("bad", 50), (float("nan"), 50), (float("inf"), 50), (9, 10), (51, 50), ("25", 25)])
def test_numeric_validation(value, expected):
  assert ev9_alert_speed_kph(value) == expected


def test_configured_warning_speed():
  toggles = SimpleNamespace(hkg_tuning_ev9_alerts_speed_kph=25)
  assert not steering_saturation_warning_allowed(make_cp(), SimpleNamespace(steeringAngleDesiredDeg=0), 25 / 3.6, toggles)
  assert steering_saturation_warning_allowed(make_cp(), SimpleNamespace(steeringAngleDesiredDeg=0), 25.1 / 3.6, toggles)


@pytest.mark.parametrize("speed,expected", [(2.49 / 3.6, False), (2.5 / 3.6, False), (2.51 / 3.6, True)])
def test_actual_angle_controller_saturation_timer(speed, expected):
  controller = LatControlAngle(make_cp(), None, 0.01)
  cs = SimpleNamespace(vEgo=speed, steeringPressed=False)
  for _ in range(31):
    saturated = controller._check_saturation(True, cs, False, False)
  assert bool(saturated) == expected
