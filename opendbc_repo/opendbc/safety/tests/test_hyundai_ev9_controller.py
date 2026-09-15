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


def setup_controller(direct):
  cp = CarInterface.get_params(CAR.KIA_EV9, gen_empty_fingerprint(), [], direct, False, False, None)
  cp.openpilotLongitudinalControl = direct
  cp.flags = int(cp.flags | HyundaiFlags.CANFD_LKA_STEERING | HyundaiFlags.CANFD_LKA_STEERING_ALT)
  c = CarController(DBC[CAR.KIA_EV9], cp)
  c.long_active_ecu = direct
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
  assert c.apply_torque_last == c.apply_torque_base_last


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
    _, msgs = c.update(cc.as_reader(), cs, now, toggles)
    assert_steering_payloads(c, msgs, not hands_on)
    assert c.apply_angle_last == pytest.approx(expected_angle)
    assert c._ev9_manual.manual_latched == hands_on
    selected = [m for m in msgs if m[0] == (0xCB if direct else 0x110)]
    assert len(selected) == 1
    addr, data, bus = selected[0]
    assert safety._tx(libsafety_py.make_CANPacket(addr, bus, data))
    assert safety.safety.get_controls_allowed()
