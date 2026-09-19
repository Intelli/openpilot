import pytest

from openpilot.common.constants import ACCELERATION_DUE_TO_GRAVITY
from openpilot.common.realtime import DT_CTRL
from openpilot.selfdrive.controls.lib.drive_helpers import clip_curvature, MAX_LATERAL_JERK


@pytest.mark.parametrize('sign', [-1, 1])
@pytest.mark.parametrize('roll', [-0.1, 0.1])
def test_ev9_low_speed_uses_symmetric_acceleration_without_roll(sign, roll):
  result, limited = clip_curvature(10, sign * 0.1, sign * 0.1, roll, ev9_angle_limit_speed_mps=40 / 3.6)
  assert result == pytest.approx(sign * 4.2 / 100)
  assert limited


@pytest.mark.parametrize('speed', [40 / 3.6, 40 / 3.6 + 0.001])
def test_threshold_includes_boundary_and_restores_stock_above(speed):
  result, limited = clip_curvature(speed, 0.1, 0.1, 0.05, ev9_angle_limit_speed_mps=40 / 3.6)
  accel = 4.2 if speed <= 40 / 3.6 else 3.0 + 0.05 * ACCELERATION_DUE_TO_GRAVITY
  assert result == pytest.approx(accel / speed**2)
  assert limited


def test_omitted_vehicle_threshold_keeps_stock_roll_and_curvature_caps():
  assert clip_curvature(1, 0.5, 0.5, 0)[0] == 0.2
  assert clip_curvature(1, 0.5, 0.5, 0, ev9_angle_limit_speed_mps=40 / 3.6) == (0.5, False)
  result, limited = clip_curvature(10, 0.1, 0.1, 0.1)
  assert result == pytest.approx((3 + 0.1 * ACCELERATION_DUE_TO_GRAVITY) / 100)
  assert limited


@pytest.mark.parametrize('threshold', [None, 40 / 3.6])
def test_jerk_comfort_factor_remains_effective(threshold):
  result, limited = clip_curvature(10, 0, 0.1, 0, jerk_factor=0.25, ev9_angle_limit_speed_mps=threshold)
  assert result == pytest.approx(MAX_LATERAL_JERK * 0.25 / 100 * DT_CTRL)
  assert not limited


def test_ev9_acceleration_comfort_limits_growth_without_false_saturation():
  result, limited = clip_curvature(10, 0.02, 0.022, 0, lat_accel_factor=0.5, ev9_angle_limit_speed_mps=40 / 3.6)
  assert result == pytest.approx(0.0205)
  assert not limited
  result, limited = clip_curvature(10, 0.021, 0.025, 0, lat_accel_factor=0.5, ev9_angle_limit_speed_mps=40 / 3.6)
  assert result == pytest.approx(0.021)
  assert not limited
  result, limited = clip_curvature(10, 0.03, 0.035, 0, lat_accel_factor=0.5, ev9_angle_limit_speed_mps=40 / 3.6)
  assert result == 0.03  # Preserve an existing curve, prohibit further growth.
  assert not limited
