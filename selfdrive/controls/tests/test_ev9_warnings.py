import math
from types import SimpleNamespace

import pytest

from opendbc.car import structs
from opendbc.car.hyundai.values import CAR, HyundaiFlags
from openpilot.selfdrive.controls.lib.ev9_warnings import ev9_alert_speed_kph
from openpilot.selfdrive.controls.lib.latcontrol_angle import LatControlAngle


def make_cp(platform=CAR.KIA_EV9, angle_flag=True, angle_controller=True):
  return SimpleNamespace(carFingerprint=platform, flags=int(HyundaiFlags.CANFD_ANGLE_STEERING) if angle_flag else 0,
                         steerControlType=structs.CarParams.SteerControlType.angle if angle_controller else structs.CarParams.SteerControlType.torque,
                         steerLimitTimer=0.3, brand="hyundai")


@pytest.mark.parametrize("cp", [make_cp(CAR.HYUNDAI_IONIQ_5_PE), make_cp(angle_flag=False), make_cp(angle_controller=False)])
def test_other_control_paths_unchanged(cp):
  assert LatControlAngle(cp, None, 0.01).sat_check_min_speed == 5


@pytest.mark.parametrize("value,expected", [(None, 50), ("bad", 50), (float("nan"), 50), (float("inf"), 50), (9, 10), (51, 50), ("25", 25)])
def test_numeric_validation(value, expected):
  assert ev9_alert_speed_kph(value) == expected


@pytest.mark.parametrize("speed,expected", [(2.49 / 3.6, False), (2.5 / 3.6, False), (2.51 / 3.6, True)])
def test_actual_angle_controller_saturation_timer(speed, expected):
  controller = LatControlAngle(make_cp(), None, 0.01)
  cs = SimpleNamespace(vEgo=speed, steeringPressed=False)
  for _ in range(31):
    saturated = controller._check_saturation(True, cs, False, False)
  assert bool(saturated) == expected


@pytest.mark.parametrize("platform", [CAR.KIA_EV9, CAR.HYUNDAI_IONIQ_5_PE])
@pytest.mark.parametrize("requested,measured,expected", [(90, 87.5, False), (90, 87.49, True), (89.99, 80, False)])
@pytest.mark.parametrize("sign", [-1, 1])
def test_high_angle_tracking_boundaries_are_ev9_only(platform, requested, measured, expected, sign):
  controller = LatControlAngle(make_cp(platform), None, 0.01)
  cs = SimpleNamespace(vEgo=10, steeringPressed=False, steeringAngleDeg=sign * measured)
  vm = SimpleNamespace(get_steer_from_curvature=lambda *args: math.radians(sign * requested))
  for _ in range(31):
    _, _, angle_log = controller.update(True, cs, vm, SimpleNamespace(roll=0, angleOffsetDeg=0),
                                       False, 0.04, False, 0, None, None, SimpleNamespace())
  assert angle_log.saturated == (expected and platform == CAR.KIA_EV9)
