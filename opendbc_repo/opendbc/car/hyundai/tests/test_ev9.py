"""EV9 configuration, driver-intent and manual-control regressions."""

import itertools
from types import SimpleNamespace

import pytest

from opendbc.can import CANPacker
from opendbc.car import Bus, gen_empty_fingerprint
from opendbc.car.hyundai.carcontroller import get_baseline_safety_cp
from opendbc.car.hyundai.carstate import CarState
from opendbc.car.hyundai.ev9 import EV9AngleConfig, EV9ManualControlState, apply_override_gain, ev9_hands_on
from opendbc.car.hyundai.interface import CarInterface
from opendbc.car.hyundai.tests.test_hyundai import get_test_toggles
from opendbc.car.hyundai.values import CAR, DBC, HyundaiSafetyFlags


def test_default_config():
  config = EV9AngleConfig.from_toggles(SimpleNamespace())
  assert config.limit_speed_mps == pytest.approx(32 / 3.6)
  assert config.override_effort_scale == pytest.approx(0.1)
  assert config.shared_autonomy_mode == 0


@pytest.mark.parametrize("raw", [1, 2, 3, 4])
@pytest.mark.parametrize("age", [0, 299_999_999, 300_000_000])
def test_hod_valid_raw_fresh(raw, age):
  assert ev9_hands_on(raw, 1_000_000_000, 1_000_000_000 + age)


@pytest.mark.parametrize("raw", [None, 0, 5, -1, "garbage"])
def test_hod_invalid_raw(raw):
  assert not ev9_hands_on(raw, 1_000_000_000, 1_000_000_000)


@pytest.mark.parametrize("timestamp,now", [(0, 1), (1_000_000_000, 1_300_000_001), (1_000_000_001, 1_000_000_000)])
def test_hod_invalid_age(timestamp, now):
  assert not ev9_hands_on(1, timestamp, now)


def test_override_gain_uses_current_base_each_frame():
  assert apply_override_gain(0.8, True, 0.5) == pytest.approx(0.4)
  assert apply_override_gain(0.5, True, 0.1) == pytest.approx(0.1)
  assert apply_override_gain(0.5, False, 0.1) == pytest.approx(0.5)


def tick(state, mode=1, **overrides):
  values = dict(lat_active=True, steering_torque=200, steering_pressed=True, hands_on=True, v_ego=5, desired_angle=20, measured_angle=0, steer_threshold=150)
  values.update(overrides)
  return state.update(EV9AngleConfig(shared_autonomy_mode=mode), **values)


@pytest.mark.parametrize("mode", [1, 2])
def test_manual_latch_speed_gate_hands_release_and_reset(mode):
  state = EV9ManualControlState()
  assert not tick(state, mode, v_ego=10).manual_override
  assert tick(state, mode).manual_override
  assert tick(state, mode, v_ego=10).manual_override
  assert not tick(state, mode, hands_on=False).manual_override
  assert not tick(state, mode, lat_active=False).manual_override
  assert state == EV9ManualControlState()


@pytest.mark.parametrize("mode", [1, 2])
@pytest.mark.parametrize("sign", [-1, 1])
def test_manual_keep_active_hysteresis(mode, sign):
  state = EV9ManualControlState()
  assert not tick(state, mode, measured_angle=89.9 * sign).keep_active
  assert tick(state, mode, measured_angle=90 * sign).keep_active
  assert tick(state, mode, measured_angle=15 * sign).keep_active
  assert not tick(state, mode, measured_angle=14.9 * sign).keep_active


@pytest.mark.parametrize("mode", [1, 2])
def test_low_demand_release_and_grip_reentry_dwell(mode):
  state = EV9ManualControlState()
  assert tick(state, mode).manual_override
  for _ in range(99):
    assert tick(state, mode, steering_torque=0, steering_pressed=False, desired_angle=0).manual_override
  assert not tick(state, mode, steering_torque=0, steering_pressed=False, desired_angle=0).manual_override
  for _ in range(9):
    assert not tick(state, mode).manual_override
  # Floating-point DT_CTRL addition can require the eleventh frame for 0.1 s.
  tick(state, mode)
  assert tick(state, mode).manual_override


def test_stock_torque_hysteresis():
  state = EV9ManualControlState()
  assert not tick(state, 0, steering_torque=149).override_active
  assert tick(state, 0, steering_torque=150).override_active
  assert tick(state, 0, steering_torque=110).override_active
  assert not tick(state, 0, steering_torque=109).override_active


@pytest.mark.parametrize(
  "aliases",
  [
    ("hkg_tuning_angle_custom_limit_max_speed_kph", "hkg_tuning_angle_override_effort_percent", "hkg_shared_autonomy_mode"),
    ("HkgTuningAngleCustomLimitMaxSpeedKph", "HkgTuningAngleOverrideEffortPercent", "HkgSharedAutonomyMode"),
    ("hkgTuningAngleCustomLimitMaxSpeedKph", "hkgTuningAngleOverrideEffortPercent", "hkgSharedAutonomyMode"),
  ],
)
def test_config_aliases_clamps(aliases):
  config = EV9AngleConfig.from_toggles(dict(zip(aliases, [36, 200, 5], strict=True)))
  assert config == EV9AngleConfig(10, 1, 2)
  assert EV9AngleConfig.from_toggles(dict(zip(aliases, ["bad", float("nan"), None], strict=True))) == EV9AngleConfig()


@pytest.mark.parametrize("states", list(itertools.product((0, 1), repeat=4)))
def test_ev9_doors(states):
  toggles = get_test_toggles()
  fp = gen_empty_fingerprint()
  cp = CarInterface.get_params(CAR.KIA_EV9, fp, [], False, False, False, toggles)
  fpcp = CarInterface.get_starpilot_params(CAR.KIA_EV9, fp, [], cp, toggles)
  state = CarState(cp, fpcp)
  parsers = state.get_can_parsers(cp)
  state.update_canfd(parsers)  # Register lazily decoded CAN messages before feeding the next frame.
  signals = dict(zip(("DRIVER_DOOR", "PASSENGER_DOOR", "DRIVER_REAR_DOOR", "PASSENGER_REAR_DOOR"), states, strict=True))
  message = CANPacker(DBC[cp.carFingerprint][Bus.pt]).make_can_msg("DOORS_SEATBELTS", parsers[Bus.pt].bus, signals)
  parsers[Bus.pt].update([(1_000_000_000, [message])])
  assert state.update_canfd(parsers)[0].doorOpen == any(states)
  assert cp.steerLimitTimer == pytest.approx(0.3)


@pytest.mark.parametrize("platform", [CAR.KIA_EV9, CAR.HYUNDAI_IONIQ_5_PE, CAR.HYUNDAI_IONIQ_6, CAR.KIA_SPORTAGE_HEV_2026])
def test_interface_ev9_safety_flag_and_baseline(platform):
  cp = CarInterface.get_params(platform, gen_empty_fingerprint(), [], False, False, False, None)
  assert any(c.safetyParam & HyundaiSafetyFlags.CANFD_EV9 for c in cp.safetyConfigs) == (platform == CAR.KIA_EV9)
  baseline = get_baseline_safety_cp(platform)
  expected = CAR.KIA_EV9 if platform == CAR.KIA_EV9 else CAR.KIA_SPORTAGE_HEV_2026
  assert baseline.carFingerprint == expected
  if platform == CAR.KIA_EV9:
    assert baseline.wheelbase == pytest.approx(3.10)
    assert baseline.steerRatio == pytest.approx(16.0)


@pytest.mark.parametrize("raw", [0, 1, 2, 3, 4, 5])
def test_hod_can_decode_timestamp_and_freshness(raw):
  cp = CarInterface.get_params(CAR.KIA_EV9, gen_empty_fingerprint(), [], False, False, False, None)
  fpcp = CarInterface.get_starpilot_params(CAR.KIA_EV9, gen_empty_fingerprint(), [], cp, get_test_toggles())
  state = CarState(cp, fpcp)
  parsers = state.get_can_parsers(cp)
  parser = parsers[Bus.pt]
  name = "HOD_FD_01_100ms"
  addr = parser.dbc.name_to_msg[name].address
  assert parser.message_states[addr].ignore_alive
  state.update_canfd(parsers)
  assert not ev9_hands_on(state.hands_on_steering_grip, state.hands_on_steering_ts_nanos, 1_000_000_000)
  msg = CANPacker(DBC[CAR.KIA_EV9][Bus.pt]).make_can_msg(name, parser.bus, {"HOD_Dir_Status": raw})
  parser.update([(1_000_000_000, [msg])])
  state.update_canfd(parsers)
  assert state.hands_on_steering_grip == raw
  assert state.hands_on_steering_ts_nanos == 1_000_000_000
  assert ev9_hands_on(raw, state.hands_on_steering_ts_nanos, 1_300_000_000) == (1 <= raw <= 4)
  assert not ev9_hands_on(raw, state.hands_on_steering_ts_nanos, 1_300_000_001)


def test_hod_not_registered_for_other_platform():
  cp = CarInterface.get_params(CAR.HYUNDAI_IONIQ_5_PE, gen_empty_fingerprint(), [], False, False, False, None)
  parser = CarState(cp, None).get_can_parsers(cp)[Bus.pt]
  addr = parser.dbc.name_to_msg["HOD_FD_01_100ms"].address
  assert addr not in parser.message_states


def test_real_vehicle_threshold_and_full_effort_pressed_behavior():
  from opendbc.car.hyundai.values import CarControllerParams

  cp = CarInterface.get_non_essential_params(CAR.KIA_EV9)
  threshold = CarControllerParams(cp).STEER_THRESHOLD
  state = EV9ManualControlState()
  assert not tick(state, 0, steer_threshold=threshold, steering_torque=threshold - 1).override_active
  assert tick(state, 0, steer_threshold=threshold, steering_torque=threshold).override_active
  assert tick(state, 0, steer_threshold=threshold, steering_torque=threshold - 40).override_active
  assert not tick(state, 0, steer_threshold=threshold, steering_torque=threshold - 41).override_active
  config = EV9AngleConfig(override_effort_scale=1)
  for pressed in (False, True, False):
    result = state.update(
      config,
      lat_active=True,
      steering_torque=1000,
      steering_pressed=pressed,
      hands_on=True,
      v_ego=5,
      desired_angle=0,
      measured_angle=0,
      steer_threshold=threshold,
    )
    assert result.override_active == pressed


@pytest.mark.parametrize("sign", [-1, 1])
def test_ev9_keeps_mdps_angles_when_only_sas_updates(sign):
  fp = gen_empty_fingerprint()
  toggles = get_test_toggles()
  cp = CarInterface.get_params(CAR.KIA_EV9, fp, [], False, False, False, toggles)
  fpcp = CarInterface.get_starpilot_params(CAR.KIA_EV9, fp, [], cp, toggles)
  state = CarState(cp, fpcp)
  parsers = state.get_can_parsers(cp)
  parser = parsers[Bus.pt]
  packer = CANPacker(DBC[CAR.KIA_EV9][Bus.pt])
  state.update_canfd(parsers)
  parser.update([(1_000_000_000, [
    packer.make_can_msg("MDPS", parser.bus, {"STEERING_ANGLE": 10 * sign, "STEERING_ANGLE_2": 20 * sign}),
    packer.make_can_msg("STEERING_SENSORS", parser.bus, {"STEERING_ANGLE": 30 * sign}),
  ])])
  out, _ = state.update_canfd(parsers)
  assert out.steeringAngleDeg == pytest.approx(30 * sign)
  assert state.mdps_steering_angle == pytest.approx(10 * sign)
  assert state.angle_steering_angle == pytest.approx(20 * sign)

  parser.update([(1_010_000_000, [packer.make_can_msg("STEERING_SENSORS", parser.bus, {"STEERING_ANGLE": 40 * sign})])])
  out, _ = state.update_canfd(parsers)
  assert out.steeringAngleDeg == pytest.approx(40 * sign)
  assert state.mdps_steering_angle == pytest.approx(10 * sign)
  assert state.angle_steering_angle == pytest.approx(20 * sign)
