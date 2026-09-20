"""Verify complete EV9 controller output against native Panda safety hooks."""

import pytest

from opendbc.can import CANPacker, CANParser
from opendbc.car import Bus, gen_empty_fingerprint, structs
from opendbc.car.hyundai.carcontroller import CarController
from opendbc.car.hyundai.carstate import CarState
from opendbc.car.hyundai.interface import CarInterface
from opendbc.car.hyundai.tests.test_hyundai import get_test_toggles
from opendbc.car.hyundai.values import CAR, DBC, HyundaiFlags, HyundaiSafetyFlags
from opendbc.safety.tests import test_hyundai_canfd
from opendbc.safety.tests.libsafety import libsafety_py


def setup_controller(direct, initialized=True):
  cp = CarInterface.get_params(CAR.KIA_EV9, gen_empty_fingerprint(), [], direct, False, False, None)
  cp.openpilotLongitudinalControl = direct
  cp.flags = int(cp.flags | HyundaiFlags.CANFD_LKA_STEERING | HyundaiFlags.CANFD_LKA_STEERING_ALT)
  c = CarController(DBC[CAR.KIA_EV9], cp)
  c.long_active_ecu = direct
  if initialized:
    # Most cases exercise ongoing control after the inactive transport initialization.
    c._ev9_initialized_angle_transports.add(0xCB if direct else 0x110)
  fpcp = CarInterface.get_starpilot_params(CAR.KIA_EV9, gen_empty_fingerprint(), [], cp, get_test_toggles())
  cs = CarState(cp, fpcp)
  cs.out = structs.CarState.new_message()
  cs.out.gearShifter = structs.CarState.GearShifter.drive
  cs.out.vEgoRaw = cs.out.vEgo = 5
  # Camera command can lag the wheel during a manual handoff.
  cs.stock_lkas_msg = {"ADAS_StrAnglReqVal": -45.0, "ADAS_ACIAnglTqRedcGainVal": 0.8}
  cs.lfa_block_msg = {f"BYTE{i}": 0 for i in range(3, 32) if i != 7}
  cs.lfa_block_msg["COUNTER"] = 0
  cc = structs.CarControl.new_message()
  cc.enabled = cc.latActive = True
  toggles = get_test_toggles()
  return c, cs, cc, toggles


@pytest.mark.parametrize("direct", [False, True])
@pytest.mark.parametrize("angle", [-4.5, 4.5])
@pytest.mark.parametrize("initially_active", [False, True])
def test_first_transmitted_angle_seeds_panda_history(direct, angle, initially_active):
  c, cs, cc, toggles = setup_controller(direct, initialized=False)
  cs.out.vEgoRaw = cs.out.vEgo = 11.71
  cs.out.steeringAngleDeg = cs.mdps_steering_angle = cs.angle_steering_angle = angle
  cc.actuators.steeringAngleDeg = angle
  c.apply_angle_last = c.angle_filter.x = angle
  cc.latActive = initially_active
  safety = test_hyundai_canfd.TestHyundaiCanfdLKASteeringAltAngleLongEV(methodName="test_lateral_accel_limit")
  safety.SAFETY_PARAM |= HyundaiSafetyFlags.CANFD_EV9 | HyundaiSafetyFlags.CCNC
  if not direct:
    safety.SAFETY_PARAM &= ~HyundaiSafetyFlags.LONG
  safety.setUp()
  safety._reset_speed_measurement(round(11.71 * 3.6 / 0.03125))
  for _ in range(6):
    safety._rx(safety.packer.make_can_msg_safety("MDPS", safety.PT_BUS, {"STEERING_ANGLE": angle, "STEERING_ANGLE_2": angle}))
  safety.safety.set_desired_angle_last(0)
  safety.safety.set_controls_allowed(True)
  for frame in range(3):
    if frame:
      cc.latActive = True
      safety.safety.set_controls_allowed(True)
    safety.safety.set_timer(frame * 10_000)
    actuators, msgs = c.update(cc.as_reader(), cs, 1_000_000_000 + frame * 10_000_000, toggles)
    assert_steering_payloads(c, msgs, frame > 0)
    selected = [m for m in msgs if m[0] == (0xCB if direct else 0x110)]
    assert len(selected) == 1
    addr, data, bus = selected[0]
    assert safety._tx(libsafety_py.make_CANPacket(addr, bus, data))
    assert actuators.steeringAngleDeg == pytest.approx(c.apply_angle_last)
    assert c.apply_angle_last == pytest.approx(angle)
    assert safety.safety.get_desired_angle_last() == round(angle * 10)


def test_disengaged_ev9_initializes_continuous_inactive_angle():
  c, cs, cc, toggles = setup_controller(False, initialized=False)
  cc.latActive = cc.enabled = False
  _, msgs = c.update(cc.as_reader(), cs, 1_000_000_000, toggles)
  assert_steering_payloads(c, msgs, False)
  assert any(m[0] == 0x110 for m in msgs)
  assert c._ev9_initialized_angle_transports == {0x110}
  cc.latActive = cc.enabled = True
  _, msgs = c.update(cc.as_reader(), cs, 1_010_000_000, toggles)
  assert_steering_payloads(c, msgs, True)
  assert c._ev9_initialized_angle_transports == {0x110}


def test_inactive_stream_tracks_wheel_before_reengagement():
  c, cs, cc, toggles = setup_controller(False, initialized=False)
  cs.out.vEgoRaw = cs.out.vEgo = 11.71
  safety = test_hyundai_canfd.TestHyundaiCanfdLKASteeringAltAngleLongEV(methodName="test_lateral_accel_limit")
  safety.SAFETY_PARAM = (safety.SAFETY_PARAM | HyundaiSafetyFlags.CANFD_EV9 | HyundaiSafetyFlags.CCNC) & ~HyundaiSafetyFlags.LONG
  safety.setUp()
  safety._reset_speed_measurement(round(11.71 * 3.6 / 0.03125))
  for frame, (angle, enabled, active) in enumerate([(-4.5, True, False), (-4.5, True, True),
                                                   (20.0, False, False), (20.0, True, True), (20.0, True, True)]):
    cs.mdps_steering_angle = cs.angle_steering_angle = cs.out.steeringAngleDeg = angle
    cc.actuators.steeringAngleDeg = angle
    cc.enabled = cc.latActive = enabled
    safety.safety.set_controls_allowed(enabled)
    safety.safety.set_timer(frame * 10_000)
    for _ in range(6):
      safety._rx(safety.packer.make_can_msg_safety("MDPS", safety.PT_BUS, {"STEERING_ANGLE": angle, "STEERING_ANGLE_2": angle}))
    if frame == 3:
      assert safety.safety.get_desired_angle_last() == 200
    _, msgs = c.update(cc.as_reader(), cs, 1_000_000_000 + frame * 10_000_000, toggles)
    selected = [m for m in msgs if m[0] == 0x110]
    assert_steering_payloads(c, msgs, active)
    assert len(selected) == 1
    addr, data, bus = selected[0]
    assert safety._tx(libsafety_py.make_CANPacket(addr, bus, data))


def test_ev9_steering_stream_ownership_across_application_and_vehicle_states():
  c, cs, cc, toggles = setup_controller(False, initialized=False)
  safety = test_hyundai_canfd.TestHyundaiCanfdLKASteeringAltAngleLongEV(methodName="test_lateral_accel_limit")
  safety.SAFETY_PARAM = 3473  # Actual EV9 stock-cruise runtime configuration, including AOL-on-engage.
  safety.setUp()
  safety.safety.set_alternative_experience(32)
  safety.safety.set_controls_allowed(False)
  parser = CANParser(DBC[CAR.KIA_EV9][Bus.pt], [("LKAS_ALT", 0)], c.CAN.ACAN)
  drive, park, reverse = structs.CarState.GearShifter.drive, structs.CarState.GearShifter.park, structs.CarState.GearShifter.reverse
  # Button press/release rows model both calibration refusal and explicit OFF with stock main still available.
  phases = [
    ("cold", False, False, 0, 0, 5, drive, 5, False),
    ("main_on_refused", False, False, 1, 1, 5, drive, 5, False),
    ("calibration_wait", False, False, 0, 1, 5, drive, 5, False),
    ("aol", False, True, 0, 1, 5, drive, 5, False),
    ("main_off", False, False, 1, 1, 5, drive, 5, False),
    ("off_release", False, False, 0, 1, 5, drive, 5, False),
    ("aol_setting_off", False, False, 0, 1, 5, drive, 5, False),
    ("brake_pause", False, False, 0, 1, 5, drive, 5, True),
    ("stopped", True, True, 0, 1, 0, drive, 5, True),
    ("park", True, True, 0, 1, 0, park, 0, False),
    ("reverse", True, True, 0, 1, 2, reverse, 7, False),
    ("resume", False, True, 0, 1, 5, drive, 5, False),
  ]
  frame = 0
  for name, enabled, lat_active, main_pressed, main_available, speed, gear, raw_gear, brake in phases:
    for tick in range(25):
      now = 1_000_000_000 + frame * 10_000_000
      safety.safety.set_timer(frame * 10_000)
      safety._rx(safety._gear_msg(raw_gear))
      safety._reset_speed_measurement(round(speed * 3.6 / 0.03125))
      safety._rx(safety._button_msg(0, main_button=main_pressed if tick == 0 else 0))
      safety._rx(safety.packer.make_can_msg_safety("SCC_CONTROL", 1, {"ACCMode": 0, "MainMode_ACC": main_available}))
      safety._rx(safety.packer.make_can_msg_safety("TCS", 1, {"DriverBraking": int(brake)}))
      angle = 4.5
      for _ in range(6):
        safety._rx(safety.packer.make_can_msg_safety("MDPS", 1, {"STEERING_ANGLE": angle, "STEERING_ANGLE_2": angle}))
      cs.out.gearShifter = gear
      cs.out.vEgoRaw = cs.out.vEgo = speed
      cs.out.standstill = speed == 0
      cs.out.brakePressed = brake
      cs.mdps_steering_angle = cs.angle_steering_angle = cs.out.steeringAngleDeg = angle
      cc.enabled, cc.latActive = enabled, lat_active
      cc.actuators.steeringAngleDeg = angle
      actuators, msgs = c.update(cc.as_reader(), cs, now, toggles)
      selected = [m for m in msgs if m[0] == 0x110]
      assert len(selected) == 1, name
      active = lat_active and gear == drive and speed > 0 and frame > 0
      assert_steering_payloads(c, msgs, active)
      addr, data, bus = selected[0]
      assert safety._tx(libsafety_py.make_CANPacket(addr, bus, data)), (name, tick)
      assert safety.safety.safety_fwd_hook(2, 0x110) == -1, name
      assert safety.safety.safety_fwd_hook(2, 0x362) == -1, name
      assert safety.safety.safety_fwd_hook(2, 0x1A0) == 0, name  # Factory SCC routing is unchanged.
      if frame % 5 == 0:
        suppression = [m for m in msgs if m[0] == 0x362]
        assert len(suppression) == 1
        addr2, data2, bus2 = suppression[0]
        assert safety._tx(libsafety_py.make_CANPacket(addr2, bus2, data2))
      parser.update([(now, [selected[0]])])
      values = parser.vl["LKAS_ALT"]
      assert values["COUNTER"] == frame % 256
      checksum = parser.dbc.addr_to_msg[addr].sigs["CHECKSUM"]
      assert values["CHECKSUM"] == checksum.calc_checksum(addr, checksum, bytearray(data))
      assert values["LKA_StrSnd"] == 0
      assert values["Damping_Gain"] == 100
      assert actuators.steeringAngleDeg == pytest.approx(angle)
      if not active:
        assert values["ADAS_ACIAnglTqRedcGainVal"] == 0
        assert values["ADAS_StrAnglReqVal"] == pytest.approx(angle)
        assert c.apply_torque_base_last == 0
      frame += 1


def check_controller_sequence(direct, samples, manual, hands_on_samples=None):
  c, cs, cc, toggles = setup_controller(direct)
  toggles.hkg_shared_autonomy_mode = int(manual)
  cs.out.vEgoRaw = cs.out.vEgo = 30 / 3.6
  initial_angle = samples[0][0]
  c.apply_angle_last = c.angle_filter.x = initial_angle
  c.apply_torque_base_last = c.apply_torque_last = 0.5
  safety = test_hyundai_canfd.TestHyundaiCanfdLKASteeringAltAngleLongEV(methodName="test_lateral_accel_limit")
  safety.SAFETY_PARAM |= HyundaiSafetyFlags.CANFD_EV9 | HyundaiSafetyFlags.CCNC
  if not direct:
    safety.SAFETY_PARAM &= ~HyundaiSafetyFlags.LONG
  safety.setUp()
  safety._reset_speed_measurement(round(30 / 0.03125))
  safety.safety.set_desired_angle_last(round(initial_angle * 10))
  safety.safety.set_controls_allowed(True)
  result = []
  for frame, (angle, torque) in enumerate(samples):
    now = 1_000_000_000 + frame * 10_000_000
    cs.out.steeringAngleDeg = cs.mdps_steering_angle = cs.angle_steering_angle = angle
    cs.out.steeringTorque = torque
    cs.out.steeringPressed = abs(torque) >= 175
    hands_on = bool(manual) if hands_on_samples is None else hands_on_samples[frame]
    cs.hands_on_steering_grip = 3 if hands_on else 0
    cs.hands_on_steering_ts_nanos = now
    cc.actuators.steeringAngleDeg = angle
    for _ in range(6):
      safety._rx(safety.packer.make_can_msg_safety("MDPS", safety.PT_BUS, {"STEERING_ANGLE": angle, "STEERING_ANGLE_2": angle}))
    safety.safety.set_timer(frame * 10_000)
    _, msgs = c.update(cc.as_reader(), cs, now, toggles)
    selected = [m for m in msgs if m[0] == (0xCB if direct else 0x110)]
    assert len(selected) == 1
    addr, data, bus = selected[0]
    assert safety._tx(libsafety_py.make_CANPacket(addr, bus, data)), (frame, angle, torque)
    result.append(c.apply_torque_last)
  return result


@pytest.mark.parametrize("direct", [False, True])
@pytest.mark.parametrize("mode", [0, 1, 2])
@pytest.mark.parametrize("angle", [30, 100])
def test_gain_recovery_preserves_prompt_reduction(direct, mode, angle):
  samples = [(angle, 200)] * 3 + [(angle, 134)] * 60 + [(angle, 200)]
  gains = check_controller_sequence(direct, samples, mode, [True] * 3 + [False] * 60 + [True])
  handoff_gain = 0.0 if mode and angle < 90 else 0.1
  assert gains[0] == pytest.approx(handoff_gain)
  # Both inactive and active manual handoffs retain the base ramp, as in Sunnypilot.
  assert gains[3] == pytest.approx(0.516)
  assert gains[-2] > 0.3
  assert gains[-1] == pytest.approx(0.1)  # Effort reduction is immediate, even during the manual reentry guard.


@pytest.mark.parametrize("direct", [False, True])
def test_hands_off_torque_cycles_keep_native_gain_and_manual_takeover(direct):
  # Alternating column torque during hands-off turning must not repeatedly trigger
  # the extra 10% override cut. Exercise transmitted frames and native Panda limits.
  torques = [250, 100, -250, -100] * 10
  gains = check_controller_sequence(direct, [(100, t) for t in torques] + [(100, 250)], 0, [False] * len(torques) + [True])
  assert min(gains[:-1]) > 0.4
  assert max(b - a for a, b in zip(gains, gains[1:], strict=False)) <= 0.0040001
  assert gains[-1] == pytest.approx(0.1)  # Contact + torque still reduces effort promptly.


@pytest.mark.parametrize("raw,age", [(0, 0), (3, 0), (0, 300_000_001), (0, -1), (5, 0), (6, 0), (7, 0)])
def test_only_confirmed_hands_off_bypasses_custom_effort(raw, age):
  c, cs, cc, toggles = setup_controller(False)
  c.apply_torque_base_last = c.apply_torque_last = 0.5
  cs.out.steeringTorque = 250
  cs.out.steeringPressed = True
  cs.hands_on_steering_grip = raw
  cs.hands_on_steering_ts_nanos = 1_000_000_000 - age
  c.update(cc.as_reader(), cs, 1_000_000_000, toggles)
  expected = c.apply_torque_base_last if raw == 0 and age == 0 else 0.1
  assert c.apply_torque_last == pytest.approx(expected)
  assert cs.out.steeringPressed  # Shared vehicle/safety telemetry is not rewritten.


@pytest.mark.parametrize("direct", [False, True])
@pytest.mark.parametrize("sign", [-1, 1])
def test_manual_envelope_reentry_requires_stable_samples(direct, sign):
  angles = [90.1, 92.5, 92.5, 94.9, 94.9] + [94.9] * 10
  samples = [(angle * sign, 200) for angle in angles] + [(94.9 * sign, 134)]
  gains = check_controller_sequence(direct, samples, True, [True] * len(angles) + [False])
  assert gains[0] == pytest.approx(0.1)
  assert gains[1:13] == [0.0] * 12
  assert gains[13:15] == pytest.approx([0.1, 0.1])
  assert gains[-1] > 0.5  # Manual-follow envelope denial must not erase the independent base ramp.


@pytest.mark.parametrize("direct", [False, True])
@pytest.mark.parametrize("manual,angle,expected_active", [(False, 0, True), (True, 0, False), (True, 20, False), (True, 100, True)])
def test_actual_outgoing_handoff_native_safety(direct, manual, angle, expected_active):
  c, cs, cc, toggles = setup_controller(direct)
  toggles.hkg_shared_autonomy_mode = int(manual)
  cs.out.vEgoRaw = cs.out.vEgo = 2
  cs.out.steeringAngleDeg = cs.mdps_steering_angle = cs.angle_steering_angle = angle
  cs.out.steeringTorque = 200 if manual else 0
  cs.out.steeringPressed = manual
  cs.hands_on_steering_grip = 3
  cs.hands_on_steering_ts_nanos = 1_000_000_000
  cc.actuators.steeringAngleDeg = angle
  c.apply_angle_last = c.angle_filter.x = angle
  _, msgs = c.update(cc.as_reader(), cs, 1_000_000_000, toggles)
  selected = [m for m in msgs if m[0] == (0xCB if direct else 0x110)]
  assert_steering_payloads(c, msgs, expected_active)
  assert len(selected) == 1, [hex(m[0]) for m in msgs]
  assert (c.apply_torque_last > 0) == expected_active
  safety = test_hyundai_canfd.TestHyundaiCanfdLKASteeringAltAngleLongEV(methodName="test_lateral_accel_limit")
  safety.SAFETY_PARAM = test_hyundai_canfd.TestHyundaiCanfdLKASteeringAltAngleLongEV.SAFETY_PARAM | HyundaiSafetyFlags.CANFD_EV9 | HyundaiSafetyFlags.CCNC
  if not direct:
    safety.SAFETY_PARAM &= ~HyundaiSafetyFlags.LONG
  safety.setUp()
  safety._reset_speed_measurement(round(2 * 3.6 / 0.03125))
  for _ in range(6):
    safety._rx(safety.packer.make_can_msg_safety("MDPS", safety.PT_BUS, {"STEERING_ANGLE": angle, "STEERING_ANGLE_2": angle}))
  assert safety.safety.get_angle_meas_min() == round(angle * 10)
  safety.safety.set_desired_angle_last(round(angle * 10))
  safety.safety.set_controls_allowed(True)
  addr, data, bus = selected[0]
  assert safety._tx(libsafety_py.make_CANPacket(addr, bus, data))


@pytest.mark.parametrize("guard", ["park", "fault", "empty_envelope"])
def test_direct_manual_does_not_revive_guard(guard):
  c, cs, cc, toggles = setup_controller(True)
  c.apply_torque_base_last = c.apply_torque_last = 0.5
  toggles.hkg_shared_autonomy_mode = 1
  cs.out.steeringTorque = 200
  cs.out.steeringPressed = True
  cs.hands_on_steering_grip = 3
  cs.hands_on_steering_ts_nanos = 1_000_000_000
  if guard == "park":
    cs.out.gearShifter = structs.CarState.GearShifter.park
  elif guard == "fault":
    cs.angle_steering_fault = True
  else:
    c.apply_angle_last = 1000
  _, msgs = c.update(cc.as_reader(), cs, 1_000_000_000, toggles)
  assert_steering_payloads(c, msgs, False)
  assert not c.direct_angle_request_allowed
  assert c.apply_torque_last == 0
  assert c.apply_torque_base_last == 0
  assert not c._ev9_manual.manual_latched
  assert any(m[0] == 0xCB for m in msgs)


@pytest.mark.parametrize("direct", [False, True])
@pytest.mark.parametrize("configured_speed", [32, 100])
def test_real_output_across_controller_and_panda_speed_gates(direct, configured_speed):
  c, cs, cc, toggles = setup_controller(direct)
  toggles.hkg_tuning_angle_custom_limit_max_speed_kph = configured_speed
  safety = test_hyundai_canfd.TestHyundaiCanfdLKASteeringAltAngleLongEV(methodName="test_lateral_accel_limit")
  safety.SAFETY_PARAM = test_hyundai_canfd.TestHyundaiCanfdLKASteeringAltAngleLongEV.SAFETY_PARAM | HyundaiSafetyFlags.CANFD_EV9 | HyundaiSafetyFlags.CCNC
  if not direct:
    safety.SAFETY_PARAM &= ~HyundaiSafetyFlags.LONG
  safety.setUp()
  for frame, speed in enumerate([8.8, 8.9, 12.74, 12.79, 13, 12.74, 8.8]):
    cs.out.vEgoRaw = cs.out.vEgo = speed
    cc.actuators.steeringAngleDeg = 300
    last = c.apply_angle_last
    safety._reset_speed_measurement(round(speed * 3.6 / 0.03125))
    safety._reset_angle_measurement(0)
    safety.safety.set_desired_angle_last(round(last * 10))
    safety.safety.set_controls_allowed(True)
    safety.safety.set_timer(frame * 10_000)
    _, msgs = c.update(cc.as_reader(), cs, 1_000_000_000 + frame * 10_000_000, toggles)
    selected = [m for m in msgs if m[0] == (0xCB if direct else 0x110)]
    assert len(selected) == 1
    addr, data, bus = selected[0]
    assert safety._tx(libsafety_py.make_CANPacket(addr, bus, data)), (speed, last, c.apply_angle_last)


def test_effort_override_does_not_corrupt_base_ramp():
  c, cs, cc, toggles = setup_controller(False)
  for frame in range(150):
    c.update(cc.as_reader(), cs, 1_000_000_000 + frame * 10_000_000, toggles)
  before = c.apply_torque_base_last
  cs.out.steeringTorque = 200
  cs.out.steeringPressed = True
  c.update(cc.as_reader(), cs, 3_000_000_000, toggles)
  assert c.apply_torque_last < c.apply_torque_base_last
  assert abs(c.apply_torque_base_last - before) <= 0.016000001
  cs.out.steeringTorque = 0
  cs.out.steeringPressed = False
  c.update(cc.as_reader(), cs, 3_010_000_000, toggles)
  assert c.apply_torque_last == pytest.approx(c.apply_torque_base_last)
  for frame in range(200):
    c.update(cc.as_reader(), cs, 3_020_000_000 + frame * 10_000_000, toggles)
  assert c.apply_torque_last == pytest.approx(c.apply_torque_base_last)


def assert_steering_payloads(controller, msgs, active):
  selected = [m for m in msgs if m[0] in (0x110, 0xCB)]
  assert selected
  for addr, data, bus in selected:
    name = "LKAS_ALT" if addr == 0x110 else "ADAS_CMD_35_10ms"
    parser = CANParser(DBC[CAR.KIA_EV9][Bus.pt], [(name, 0)], bus)
    parser.update([(1_000_000_000, [(addr, data, bus)])])
    values = parser.vl[name]
    request = values["LKAS_ANGLE_ACTIVE" if addr == 0x110 else "ADAS_ActvACILvl2Sta"]
    assert request == (2 if active else 1)
    if not active:
      assert values["ADAS_StrAnglReqVal"] == pytest.approx(controller.apply_angle_last, abs=0.05)
    expected_gain = round(controller.apply_torque_last / 0.004) * 0.004 if active else 0
    assert values["ADAS_ACIAnglTqRedcGainVal"] == pytest.approx(expected_gain)


@pytest.mark.parametrize("direct", [False, True])
@pytest.mark.parametrize("gate,configured_speed", [(32 / 3.6, 32), (42 / 3.6 + 1.1, 100)])
def test_saturated_gate_drop_resets_then_recovers(direct, gate, configured_speed):
  from opendbc.car.lateral import get_max_angle_vm

  c, cs, cc, toggles = setup_controller(direct)
  toggles.hkg_tuning_angle_custom_limit_max_speed_kph = configured_speed
  c._update_ev9_angle_limits(gate - 0.02, toggles)
  before = (
    get_max_angle_vm(max(gate - 1.02, 1), c.BASELINE_VM, c._ev9_safety_params) if configured_speed == 100 else get_max_angle_vm(gate - 0.02, c.VM, c.params)
  )
  c.apply_angle_last = c.angle_filter.x = before
  cs.out.vEgoRaw = cs.out.vEgo = gate + 0.02
  cc.actuators.steeringAngleDeg = before
  _, msgs = c.update(cc.as_reader(), cs, 1_000_000_000, toggles)
  assert_steering_payloads(c, msgs, False)
  assert c.apply_angle_last == 0
  _, msgs = c.update(cc.as_reader(), cs, 1_010_000_000, toggles)
  assert_steering_payloads(c, msgs, True)


@pytest.mark.parametrize("direct", [False, True])
@pytest.mark.parametrize("sign", [-1, 1])
def test_divergent_sensor_manual_handoff_and_recovery(direct, sign):
  c, cs, cc, toggles = setup_controller(direct)
  toggles.hkg_shared_autonomy_mode = 1
  parsers = cs.get_can_parsers(c.CP)
  parser = parsers[Bus.pt]
  packer = CANPacker(DBC[CAR.KIA_EV9][Bus.pt])
  cs.update_canfd(parsers)
  mdps = packer.make_can_msg("MDPS", parser.bus, {"STEERING_ANGLE": 10 * sign, "STEERING_ANGLE_2": 20 * sign})
  parser.update([(1_000_000_000, [mdps])])
  expected_angle = (20 if direct else 10) * sign
  c.apply_angle_last = c.angle_filter.x = expected_angle
  cc.actuators.steeringAngleDeg = expected_angle

  safety = test_hyundai_canfd.TestHyundaiCanfdLKASteeringAltAngleLongEV(methodName="test_lateral_accel_limit")
  safety.SAFETY_PARAM |= HyundaiSafetyFlags.CANFD_EV9 | HyundaiSafetyFlags.CCNC
  if not direct:
    safety.SAFETY_PARAM &= ~HyundaiSafetyFlags.LONG
  safety.setUp()
  safety._reset_speed_measurement(round(2 * 3.6 / 0.03125))
  for _ in range(6):
    safety._rx(safety.packer.make_can_msg_safety("MDPS", safety.PT_BUS, {"STEERING_ANGLE": 10 * sign, "STEERING_ANGLE_2": 20 * sign}))
  assert safety.safety.get_angle_meas_min() == round(expected_angle * 10)
  safety.safety.set_desired_angle_last(round(expected_angle * 10))
  safety.safety.set_controls_allowed(True)

  # SAS changes independently; neither controller nor Panda receives another MDPS sample.
  for frame, (sas, hands_on) in enumerate([(30, True), (40, True), (40, False)]):
    now = 1_000_000_000 + frame * 10_000_000
    parser.update([(now, [packer.make_can_msg("STEERING_SENSORS", parser.bus, {"STEERING_ANGLE": sas * sign})])])
    cs.out, _ = cs.update_canfd(parsers)
    assert cs.out.steeringAngleDeg == pytest.approx(sas * sign)
    cs.out.gearShifter = structs.CarState.GearShifter.drive
    cs.out.vEgoRaw = cs.out.vEgo = 2
    cs.out.standstill = False
    cs.out.steeringTorque = 200 if hands_on else 0
    cs.out.steeringPressed = hands_on
    cs.hands_on_steering_grip = 3 if hands_on else 0
    cs.hands_on_steering_ts_nanos = now
    cs.stock_lkas_msg = {"ADAS_StrAnglReqVal": -45.0, "ADAS_ACIAnglTqRedcGainVal": 0.8}
    cs.lfa_block_msg = {f"BYTE{i}": 0 for i in range(3, 32) if i != 7}
    cs.lfa_block_msg["COUNTER"] = 0
    safety.safety.set_timer(frame * 10_000)
    actuators, msgs = c.update(cc.as_reader(), cs, now, toggles)
    assert actuators.manualSteeringOverride == hands_on
    assert_steering_payloads(c, msgs, not hands_on)
    assert c.apply_angle_last == pytest.approx(expected_angle)
    assert c._ev9_manual.manual_latched == hands_on
    selected = [m for m in msgs if m[0] == (0xCB if direct else 0x110)]
    assert len(selected) == 1
    addr, data, bus = selected[0]
    assert safety._tx(libsafety_py.make_CANPacket(addr, bus, data))
    assert safety.safety.get_controls_allowed()

  # Even a stale true input must not survive an inactive update.
  cc.actuators.manualSteeringOverride = True
  cc.latActive = False
  actuators, _ = c.update(cc.as_reader(), cs, now + 10_000_000, toggles)
  assert not actuators.manualSteeringOverride
  assert c.apply_torque_base_last == c.apply_torque_last == 0


@pytest.mark.parametrize('direct', [False, True])
@pytest.mark.parametrize('sign', [-1, 1])
@pytest.mark.parametrize('speed', [11.1, 11.2])
def test_steady_saturation_holds_valid_boundary_without_releasing(direct, sign, speed):
  from opendbc.car.lateral import get_max_angle_vm
  from opendbc.safety.tests.test_hyundai_ev9 import make_case

  c, cs, cc, toggles = setup_controller(direct)
  toggles.hkg_shared_autonomy_mode = 0
  toggles.hkg_tuning_angle_custom_limit_max_speed_kph = 40
  c._update_ev9_angle_limits(speed, toggles)
  boundary = min(c.params.ANGLE_LIMITS.STEER_ANGLE_MAX, get_max_angle_vm(speed, c.VM, c.params),
                 get_max_angle_vm(speed - 1, c.BASELINE_VM, c._ev9_safety_params))
  # Start just inside the applicable ceiling to test steady saturation, not recovery.
  if direct:
    boundary = min(boundary, 140.0)
  initial = sign * (boundary - 0.2)
  c.apply_angle_last = c.angle_filter.x = initial
  c.apply_torque_last = c.apply_torque_base_last = 0.5
  cs.out.vEgoRaw = cs.out.vEgo = speed
  cs.out.steeringAngleDeg = cs.mdps_steering_angle = cs.angle_steering_angle = sign * 90
  cs.out.steeringTorque = 0
  cs.out.steeringPressed = False
  cc.actuators.steeringAngleDeg = sign * 360
  safety = make_case(True, direct)
  safety._rx(safety._gear_msg(5))
  safety._reset_speed_measurement(round(speed * 3.6 / 0.03125))
  safety.safety.set_desired_angle_last(round(initial * 10))
  safety.safety.set_controls_allowed(True)
  for frame in range(100):
    for _ in range(6):
      safety._rx(safety.packer.make_can_msg_safety('MDPS', 1, {'STEERING_ANGLE': sign * 90, 'STEERING_ANGLE_2': sign * 90}))
    safety.safety.set_timer(frame * 10_000)
    actuators, msgs = c.update(cc.as_reader(), cs, 1_000_000_000 + frame * 10_000_000, toggles)
    assert_steering_payloads(c, msgs, True)
    assert not actuators.manualSteeringOverride
    assert c.apply_torque_last >= 0.5
    assert abs(c.apply_angle_last) <= boundary + 1e-5
    steering = [msg for msg in msgs if msg[0] == (0xCB if direct else 0x110)]
    assert len(steering) == 1
    addr, data, bus = steering[0]
    assert safety._tx(libsafety_py.make_CANPacket(addr, bus, data))
  assert c.apply_angle_last == pytest.approx(sign * boundary, abs=1e-4)


@pytest.mark.parametrize('sign', [-1, 1])
@pytest.mark.parametrize('direct', [False, True])
def test_ev9_target_saturation_stays_active_and_reverses(sign, direct):
  from opendbc.safety.tests.test_hyundai_ev9 import make_case

  c, cs, cc, toggles = setup_controller(direct)
  toggles.hkg_shared_autonomy_mode = 0
  safety = make_case(True, direct)
  safety._set_physical_angle_test_speed(5.0)
  safety.safety.set_controls_allowed(True)
  for frame in range(600):
    target_sign = sign if frame < 300 else -sign
    cc.actuators.steeringAngleDeg = target_sign * 200
    # A following wheel isolates planner saturation from manual handoff and faults.
    measured = c.apply_angle_last
    cs.out.steeringAngleDeg = cs.mdps_steering_angle = cs.angle_steering_angle = measured
    for _ in range(6):
      safety._rx(safety.packer.make_can_msg_safety('MDPS', 1, {'STEERING_ANGLE': measured, 'STEERING_ANGLE_2': measured}))
    safety.safety.set_timer(frame * 10_000)
    _, msgs = c.update(cc.as_reader(), cs, 1_000_000_000 + frame * 10_000_000, toggles)
    assert_steering_payloads(c, msgs, True)
    addr, data, bus = next(m for m in msgs if m[0] == (0xCB if direct else 0x110))
    assert safety._tx(libsafety_py.make_CANPacket(addr, bus, data))
    if direct:
      assert abs(c.apply_angle_last) <= 140.0 + 1e-6
    if frame in (299, 599):
      assert c.apply_angle_last == pytest.approx(target_sign * (140.0 if direct else 200), abs=0.01)


@pytest.mark.parametrize('sign', [-1, 1])
@pytest.mark.parametrize('manual', [False, True])
def test_ev9_target_cap_preserves_beyond_cap_measurement_and_reentry(sign, manual):
  from opendbc.safety.tests.test_hyundai_ev9 import make_case

  c, cs, cc, toggles = setup_controller(True)
  toggles.hkg_shared_autonomy_mode = int(manual)
  safety = make_case(True, True)
  safety._set_physical_angle_test_speed(5.0)
  safety.safety.set_controls_allowed(True)
  measured = sign * 200
  cs.out.steeringAngleDeg = cs.mdps_steering_angle = cs.angle_steering_angle = measured
  cc.actuators.steeringAngleDeg = sign * 240
  for frame in range(4):
    cc.latActive = frame > 0
    cs.out.steeringPressed = manual
    cs.out.steeringTorque = 200 if manual else 0
    now = 1_000_000_000 + frame * 10_000_000
    cs.hands_on_steering_grip = 3 if manual else 0
    cs.hands_on_steering_ts_nanos = now
    for _ in range(6):
      safety._rx(safety.packer.make_can_msg_safety('MDPS', 1, {'STEERING_ANGLE': measured, 'STEERING_ANGLE_2': measured}))
    safety.safety.set_timer(frame * 10_000)
    previous = c.apply_angle_last
    actuators, msgs = c.update(cc.as_reader(), cs, now, toggles)
    assert_steering_payloads(c, msgs, frame > 0)
    addr, data, bus = next(m for m in msgs if m[0] == 0xCB)
    assert safety._tx(libsafety_py.make_CANPacket(addr, bus, data))
    if frame == 0 or manual:
      assert c.apply_angle_last == pytest.approx(measured)
    else:
      assert 140.0 < abs(c.apply_angle_last) < abs(previous)
      assert abs(c.apply_angle_last - previous) <= 5 + 1e-6
    if frame > 0:
      assert actuators.manualSteeringOverride == manual
      if manual:
        assert c.apply_torque_last == pytest.approx(0.10)


@pytest.mark.parametrize('sign', [-1, 1])
@pytest.mark.parametrize('target', [139.9, 140.0, 140.1])
def test_ev9_target_cap_boundary_longitudinal_state_and_fault_recovery(sign, target):
  from opendbc.safety.tests.test_hyundai_ev9 import make_case

  c, cs, cc, toggles = setup_controller(True)
  toggles.hkg_shared_autonomy_mode = 0
  expected = sign * min(target, 140.0)
  c.apply_angle_last = c.angle_filter.x = expected
  cs.out.steeringAngleDeg = cs.mdps_steering_angle = cs.angle_steering_angle = expected
  cc.actuators.steeringAngleDeg = sign * target
  safety = make_case(True, True)
  safety._set_physical_angle_test_speed(5.0)
  safety.safety.set_desired_angle_last(round(expected * 10))
  safety.safety.set_controls_allowed(True)
  # Cap scope follows the configured transport, including AOL without longActive.
  for frame, (long_active, fault) in enumerate([(False, False), (True, False), (True, True), (False, False)]):
    cc.longActive = long_active
    cs.angle_steering_fault = fault
    for _ in range(6):
      safety._rx(safety.packer.make_can_msg_safety('MDPS', 1, {
        'STEERING_ANGLE': expected, 'STEERING_ANGLE_2': expected, 'LKA_ANGLE_FAULT': int(fault),
      }))
    safety.safety.set_timer(frame * 10_000)
    _, msgs = c.update(cc.as_reader(), cs, 1_000_000_000 + frame * 10_000_000, toggles)
    assert_steering_payloads(c, msgs, not fault)
    assert c.apply_angle_last == pytest.approx(expected)
    addr, data, bus = next(m for m in msgs if m[0] == 0xCB)
    assert safety._tx(libsafety_py.make_CANPacket(addr, bus, data))
