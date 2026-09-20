import math
import types

from cereal import car

import pytest

from openpilot.common.realtime import DT_CTRL
from openpilot.selfdrive.controls.controlsd import (
  TWITCH_GUARD_DURATION,
  TWITCH_GUARD_FLOOR,
  TWITCH_GUARD_MAX_SPEED,
  get_control_lateral_smooth_seconds,
  limit_curvature_to_plan,
  turn_lead_allowed,
  update_twitch_guard,
)


LateralControlMode = car.CarControl.Actuators.LateralControlMode


def _plan(xs, ys):
  return types.SimpleNamespace(position=types.SimpleNamespace(x=xs, y=ys))


def _arc_plan(radius, n=200):
  return _plan([radius * math.sin(i / n) for i in range(n)],
               [radius * (1.0 - math.cos(i / n)) for i in range(n)])


STRAIGHT_PLAN = _plan([i * 0.5 for i in range(200)], [0.0] * 200)
STANDSTILL_STUB_PLAN = _plan([0.0, 0.3], [0.0, 0.0])
TURN_PLAN = _arc_plan(30.0)
GENTLE_BEND_PLAN = _arc_plan(143.0)


def test_turn_lead_is_suppressed_only_during_applied_angle_control():
  assert not turn_lead_allowed("rivian", LateralControlMode.angle)
  assert turn_lead_allowed("rivian", LateralControlMode.torque)
  assert turn_lead_allowed("rivian", LateralControlMode.torqueRecovering)
  assert turn_lead_allowed("rivian", LateralControlMode.inactive)
  assert turn_lead_allowed("ford", LateralControlMode.angle)


@pytest.mark.parametrize("v_ego", [0.0, 5.0, 30.0])
def test_non_rivian_control_smoothing_matches_starpilot(v_ego):
  assert get_control_lateral_smooth_seconds("toyota", v_ego, 0.0) == 0.1


@pytest.mark.parametrize(("v_ego", "expected"), [
  (0.0, 0.4),
  (5.0, 0.2),
  (30.0, 0.0),
])
def test_subaru_control_smoothing_uses_vehicle_schedule(v_ego, expected):
  assert get_control_lateral_smooth_seconds("subaru", v_ego, 0.4) == pytest.approx(expected)


@pytest.mark.parametrize(("v_ego", "expected"), [
  (0.0, 0.4),
  (5.0, 0.2),
  (30.0, 0.0),
])
def test_rivian_control_smoothing_remains_speed_scheduled(v_ego, expected):
  assert get_control_lateral_smooth_seconds("rivian", v_ego, 0.4) == pytest.approx(expected)


@pytest.mark.parametrize("curvature", [0.0155, -0.0155])
def test_twitch_against_a_straight_plan_is_clamped_to_the_floor(curvature):
  guarded = limit_curvature_to_plan(STRAIGHT_PLAN, curvature, 1.2)
  assert abs(guarded) == pytest.approx(TWITCH_GUARD_FLOOR)
  assert math.copysign(1.0, guarded) == math.copysign(1.0, curvature)


def test_command_already_below_the_floor_is_untouched():
  assert limit_curvature_to_plan(STRAIGHT_PLAN, 0.0015, 1.2) == pytest.approx(0.0015)


@pytest.mark.parametrize("v_ego", [TWITCH_GUARD_MAX_SPEED, 6.0, 30.0])
def test_guard_is_inactive_above_its_speed_band(v_ego):
  assert limit_curvature_to_plan(STRAIGHT_PLAN, 0.0155, v_ego) == pytest.approx(0.0155)


def test_guard_fades_out_across_the_speed_band():
  full = limit_curvature_to_plan(STRAIGHT_PLAN, 0.0155, 1.2)
  half = limit_curvature_to_plan(STRAIGHT_PLAN, 0.0155, 3.5)
  assert full < half < 0.0155


@pytest.mark.parametrize("ratio", [0.8, 1.0, 2.0, 3.0])
def test_real_turns_tracking_their_own_plan_are_untouched(ratio):
  action = (1.0 / 30.0) * ratio
  assert limit_curvature_to_plan(TURN_PLAN, action, 1.2) == pytest.approx(action)


def test_a_barely_bending_plan_does_not_license_a_large_command():
  guarded = limit_curvature_to_plan(GENTLE_BEND_PLAN, 0.0155, 1.2)
  assert TWITCH_GUARD_FLOOR < guarded < 0.008


@pytest.mark.parametrize("plan", [STANDSTILL_STUB_PLAN, _plan([], [])])
def test_guard_stands_down_when_the_plan_is_too_short_to_judge(plan):
  assert limit_curvature_to_plan(plan, 0.0155, 0.4) == pytest.approx(0.0155)


def test_zero_command_stays_zero():
  assert limit_curvature_to_plan(STRAIGHT_PLAN, 0.0, 1.2) == 0.0


@pytest.mark.parametrize("bad_plan", [
  _plan([0.0, math.nan, 20.0], [0.0, 0.0, 0.0]),
  _plan([0.0, math.inf, 20.0], [0.0, 0.0, 0.0]),
  _plan([0.0, 20.0], [0.0]),
])
def test_invalid_plan_data_leaves_curvature_untouched(bad_plan):
  assert limit_curvature_to_plan(bad_plan, 0.0155, 1.2) == pytest.approx(0.0155)


@pytest.mark.parametrize("value", [math.nan, math.inf, -math.inf])
def test_nonfinite_guard_inputs_disarm(value):
  assert update_twitch_guard(value, 1.0, False) == 0.0
  assert update_twitch_guard(TWITCH_GUARD_DURATION, value, False) == 0.0


def test_twitch_guard_arms_at_standstill_or_creep_speed():
  assert update_twitch_guard(0.0, 0.0, True) == TWITCH_GUARD_DURATION
  assert update_twitch_guard(0.0, 0.3, False) == TWITCH_GUARD_DURATION


def test_twitch_guard_decays_after_pullaway_and_expires():
  remaining = update_twitch_guard(0.0, 0.0, True)
  remaining = update_twitch_guard(remaining, 1.0, False)
  assert remaining == pytest.approx(TWITCH_GUARD_DURATION - DT_CTRL)

  for _ in range(int(TWITCH_GUARD_DURATION / DT_CTRL) + 1):
    remaining = update_twitch_guard(remaining, 1.0, False)
  assert remaining == 0.0


def test_twitch_guard_does_not_arm_while_moving():
  assert update_twitch_guard(0.0, 1.0, False) == 0.0


@pytest.mark.parametrize('direction', [-1., 1.])
def test_ev9_angle_lead_uses_current_preview_until_model_catches_up(direction):
  from opendbc.car.hyundai.values import CAR
  from openpilot.selfdrive.controls.controlsd import turn_lead_engagement_weight
  for measured in (0., .01, .02, .03):
    weight = turn_lead_engagement_weight(CAR.KIA_EV9, car.CarParams.SteerControlType.angle,
                                         direction * measured, direction * .003, direction * .02, direction)
    assert weight == 1.
  # No retained floor: smaller current preview immediately reduces its contribution;
  # stronger model demand wins the production max-magnitude handoff.
  for preview, raw, expected in ((.0127, .003, .0127), (.004, .003, .004), (.004, .02, .02)):
    weight = turn_lead_engagement_weight(CAR.KIA_EV9, car.CarParams.SteerControlType.angle,
                                         direction * .02, direction * raw, direction * preview, direction)
    assert max(raw, preview * weight) == expected


@pytest.mark.parametrize('direction', [-1., 1.])
def test_ev9_angle_lead_never_adds_against_raw_model_correction(direction):
  from opendbc.car.hyundai.values import CAR
  from openpilot.selfdrive.controls.controlsd import turn_lead_engagement_weight
  for raw in (-1e-8, -.001, -.02):
    assert turn_lead_engagement_weight(CAR.KIA_EV9, car.CarParams.SteerControlType.angle,
                                       0., direction * raw, direction * .02, direction) == 0.


@pytest.mark.parametrize('fingerprint,control_type', [('other', car.CarParams.SteerControlType.angle),
                                                       ('other', car.CarParams.SteerControlType.torque)])
def test_other_vehicle_turn_lead_fade_remains_identical(fingerprint, control_type):
  from openpilot.selfdrive.controls.controlsd import turn_lead_engagement_weight, TURN_LEAD_ENGAGED_FRAC
  for measured in (-.03, -.015, 0., .015, .03):
    expected = min(max((1. - abs(measured) / .02) / (1. - TURN_LEAD_ENGAGED_FRAC), 0.), 1.)
    assert turn_lead_engagement_weight(fingerprint, control_type, measured, -.001, .02, 1.) == expected


def test_ev9_lead_configured_speed_boundary_is_continuous():
  from openpilot.selfdrive.controls.controlsd import ev9_turn_lead_authority
  ceiling = 40. / 3.6
  assert ev9_turn_lead_authority(32. / 3.6, 0., 10., ceiling) == 1.
  assert ev9_turn_lead_authority(ceiling, 0., 10., ceiling) == 0.
  assert ev9_turn_lead_authority(ceiling - .001, 0., 10., ceiling) < 1e-5
  assert ev9_turn_lead_authority(ceiling - 1., 0., 10., ceiling) == .5
  assert ev9_turn_lead_authority(7., 0., 9.1, ceiling) == 1.
  # A low configured ceiling must not bypass the historical creep exclusion.
  assert ev9_turn_lead_authority(2.5, 0., 4., 10. / 3.6) == 0.
  assert ev9_turn_lead_authority(3., 0., 4., ceiling) == 0.


def test_ev9_lead_stop_projection_fades_without_deceleration_switch():
  from openpilot.selfdrive.controls.controlsd import ev9_turn_lead_authority
  # At 6 m/s and an 8 m preview: stop before the bend => no initiation.
  assert ev9_turn_lead_authority(6., -3., 8., 40./3.6) == 0.
  assert ev9_turn_lead_authority(6., -2.25, 8., 40./3.6) == 0.
  assert ev9_turn_lead_authority(6., -1.8, 8., 40./3.6) == .5
  assert ev9_turn_lead_authority(6., -1.5, 8., 40./3.6) == 1.
  assert ev9_turn_lead_authority(6., -.501, 8., 40./3.6) == ev9_turn_lead_authority(6., -.499, 8., 40./3.6)
