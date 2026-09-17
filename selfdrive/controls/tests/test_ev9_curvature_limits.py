"""EV9 uses the standard StarPilot curvature envelope at every speed."""
import pytest

from openpilot.common.constants import ACCELERATION_DUE_TO_GRAVITY
from openpilot.common.realtime import DT_CTRL
from openpilot.selfdrive.controls.lib.drive_helpers import clip_curvature, MAX_LATERAL_JERK


@pytest.mark.parametrize('sign', [-1, 1])
@pytest.mark.parametrize('roll', [-0.1, 0.1])
@pytest.mark.parametrize('speed', [5, 10, 40 / 3.6, 40 / 3.6 + 0.001, 20])
def test_standard_acceleration_with_roll_at_all_speeds(sign, roll, speed):
  result, limited = clip_curvature(speed, sign * 0.2, sign * 0.2, roll)
  assert result == pytest.approx((sign * 3.0 + roll * ACCELERATION_DUE_TO_GRAVITY) / speed**2)
  assert limited


@pytest.mark.parametrize('sign', [-1, 1])
def test_low_speed_keeps_standard_curvature_cap(sign):
  result, limited = clip_curvature(1, sign * 0.5, sign * 0.5, 0)
  assert result == sign * 0.2
  assert limited


def test_jerk_comfort_factor_remains_effective():
  result, limited = clip_curvature(10, 0, 0.1, 0, jerk_factor=0.25)
  assert result == pytest.approx(MAX_LATERAL_JERK * 0.25 / 100 * DT_CTRL)
  assert not limited


def test_acceleration_comfort_preserves_existing_curve_without_false_saturation():
  result, limited = clip_curvature(10, 0.014, 0.022, 0, lat_accel_factor=0.5)
  assert result == pytest.approx(0.0145)
  assert not limited
  result, limited = clip_curvature(10, 0.021, 0.025, 0, lat_accel_factor=0.5)
  assert result == pytest.approx(0.021)
  assert not limited
  result, limited = clip_curvature(10, 0.03, 0.035, 0, lat_accel_factor=0.5)
  assert result == 0.03  # Preserve an existing curve, prohibit further growth.
  assert limited  # The request exceeds the standard unshaped envelope.
