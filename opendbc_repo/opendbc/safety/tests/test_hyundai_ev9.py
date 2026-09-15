"""EV9-specific model and low-speed envelope checks against native Panda hooks."""
import math

import pytest

from opendbc.car import gen_empty_fingerprint, structs
from opendbc.car.hyundai.interface import CarInterface
from opendbc.car.hyundai.values import CAR, HyundaiSafetyFlags
from opendbc.safety.tests import test_hyundai_canfd as hyundai_tests


def make_case(ev9, direct=False, ev_gas=True):
  case = hyundai_tests.TestHyundaiCanfdLKASteeringAltAngleLongEV(methodName='test_lateral_accel_limit')
  case.SAFETY_PARAM = hyundai_tests.TestHyundaiCanfdLKASteeringAltAngleLongEV.SAFETY_PARAM | HyundaiSafetyFlags.CCNC
  if not direct:
    case.SAFETY_PARAM &= ~HyundaiSafetyFlags.LONG
  if ev9:
    case.SAFETY_PARAM |= HyundaiSafetyFlags.CANFD_EV9
  if not ev_gas:
    case.SAFETY_PARAM &= ~HyundaiSafetyFlags.EV_GAS
  case.setUp()
  return case


def send_angle(case, angle, direct):
  if not direct:
    return case._tx(case._angle_cmd_msg(angle, True))
  return case._tx(case.packer.make_can_msg_safety('ADAS_CMD_35_10ms', 1, {
    'ADAS_ActvACILvl2Sta': 2, 'ADAS_StrAnglReqVal': angle, 'ADAS_ACIAnglTqRedcGainVal': 1.0,
  }))


@pytest.mark.parametrize('ev9', [False, True])
@pytest.mark.parametrize('direct', [False, True])
@pytest.mark.parametrize('physical_speed', [10.0, 12.74, 12.79, 21.0])
@pytest.mark.parametrize('kind', ['accel', 'jerk'])
@pytest.mark.parametrize('sign', [-1, 1])
def test_actual_quantized_bounds(ev9, direct, physical_speed, kind, sign):
  for beyond in (False, True):
    case = make_case(ev9, direct)
    speed = case._set_physical_angle_test_speed(physical_speed)
    limit = 4.2 if ev9 and speed <= 42 / 3.6 + 0.1 else 3.0 + 9.81 * 0.06
    slip, ratio, wheelbase = (-0.0005410588125765342, 16, 3.10) if ev9 else (-0.0006085930193026732, 13.7, 2.756)
    factor = 1 / (1 - slip * speed**2) / wheelbase
    angle = limit / speed**2 * ratio / factor * 180 / math.pi
    if kind == 'jerk':
      angle /= 100
    bound = int(angle * 10 + 1)
    assert bound < 3600  # Every case exercises both acceptance and rejection.
    raw = sign * (bound + int(beyond))
    case.safety.set_controls_allowed(True)
    case.safety.set_desired_angle_last(raw if kind == 'accel' else 0)
    assert bool(send_angle(case, raw / 10, direct)) == (not beyond), (ev9, direct, speed, kind, sign, raw)


@pytest.mark.parametrize('platform', [CAR.KIA_EV9, CAR.HYUNDAI_IONIQ_5_PE, CAR.HYUNDAI_IONIQ_6, CAR.KIA_SPORTAGE_HEV_2026])
def test_interface_identity_only_ev9(platform):
  cp = CarInterface.get_params(platform, gen_empty_fingerprint(), [], False, False, False, None)
  assert any(c.safetyParam & HyundaiSafetyFlags.CANFD_EV9 for c in cp.safetyConfigs) == (platform == CAR.KIA_EV9)


def test_ev9_flag_preserves_ev_gas_and_aol_behavior():
  case = make_case(True)
  assert not case.safety.get_aol_allowed()
  for pressed in (False, True, False):
    case._rx(case._user_gas_msg(int(pressed)))
    assert bool(case.safety.get_gas_pressed_prev()) == pressed
  case.safety.set_alternative_experience(32)
  case._rx(case.packer.make_can_msg_safety('SCC_CONTROL', 1, {'MainMode_ACC': 1, 'ACCMode': 0}))
  assert case.safety.get_aol_allowed()
  assert not case.safety.get_controls_allowed()


@pytest.mark.parametrize('ev_gas', [False, True])
def test_identity_requires_ev_gas(ev_gas):
  # At highway speed, an angle between Sportage and EV9 bounds isolates model selection.
  case = make_case(True, ev_gas=ev_gas)
  case._set_physical_angle_test_speed(21.0)
  case.safety.set_controls_allowed(True)
  angle = 30.0
  case.safety.set_desired_angle_last(int(angle * 10))
  assert bool(send_angle(case, angle, False)) == ev_gas


def test_ev9_identity_does_not_enable_angle_mode():
  case = make_case(True)
  param = case.SAFETY_PARAM & ~HyundaiSafetyFlags.CANFD_ANGLE_STEERING
  case.safety.set_safety_hooks(structs.CarParams.SafetyModel.hyundaiCanfd, param)
  case.safety.init_tests()
  case._set_physical_angle_test_speed(21.0)
  case._rx(case._gear_msg(5))
  case.safety.set_controls_allowed(True)
  assert not send_angle(case, 30.0, True)


@pytest.mark.parametrize('ev9', [False, True])
@pytest.mark.parametrize('direct', [False, True])
def test_ev9_lkas_alt_flag_does_not_latch_main_button(ev9, direct):
  case = make_case(ev9, direct)
  case.safety.set_alternative_experience(32)
  case.safety.set_controls_allowed(False)
  case._rx(case._button_msg(0, main_button=1))
  assert case.safety.get_acc_main_on() == (not ev9 or direct)
  assert case.safety.get_lkas_on() == (not ev9)  # Other platforms retain their existing common flag behavior.
  case._rx(case._button_msg(0, main_button=0))
  case._rx(case._button_msg(0, main_button=1))
  assert not case.safety.get_acc_main_on()
  assert case.safety.get_aol_allowed() == (not ev9)


@pytest.mark.parametrize('controls,aol', [(False, False), (True, False), (False, True)])
@pytest.mark.parametrize('moving', [False, True])
@pytest.mark.parametrize('gear', [0, 5, 7])
def test_ev9_inactive_ownership_does_not_grant_actuation(controls, aol, moving, gear):
  case = make_case(True)
  case.safety.set_alternative_experience(32)
  case._rx(case._gear_msg(gear))
  case._reset_speed_measurement(round(5 * 3.6 / 0.03125) if moving else 0)
  if aol:
    case._rx(case.packer.make_can_msg_safety('SCC_CONTROL', 1, {'MainMode_ACC': 1, 'ACCMode': 0}))
  case.safety.set_controls_allowed(controls)
  for _ in range(6):
    case._rx(case.packer.make_can_msg_safety('MDPS', 1, {'STEERING_ANGLE': 4.5, 'STEERING_ANGLE_2': 4.5}))
  assert case.safety.safety_fwd_hook(2, 0x110) == -1
  assert case.safety.safety_fwd_hook(2, 0x362) == -1
  assert case._tx(case._angle_cmd_msg(4.5, False))
  assert not case._tx(case._angle_cmd_msg(5.0, False))  # Measured-angle checks still apply to inactive ownership.
  assert not case._tx(case._angle_cmd_msg(4.5, False, gain_raw=1))
  case.safety.set_desired_angle_last(45)
  assert bool(case._tx(case._angle_cmd_msg(4.5, True))) == ((controls or aol) and moving and gear == 5)


@pytest.mark.parametrize('main_available', [False, True])
@pytest.mark.parametrize('brake', [False, True])
def test_ev9_stock_scc_main_authority_survives_refused_request_rearm(main_available, brake):
  case = make_case(True)
  case.safety.set_alternative_experience(32)
  case._rx(case._gear_msg(5))
  case._reset_speed_measurement(round(5 * 3.6 / 0.03125))
  for _ in range(6):
    case._rx(case.packer.make_can_msg_safety('MDPS', 1, {'STEERING_ANGLE': 4.5}))
  case._rx(case.packer.make_can_msg_safety('SCC_CONTROL', 1, {'MainMode_ACC': int(main_available), 'ACCMode': 0}))  # ACCMode remains zero throughout.
  for press, active in [(1, False), (0, False), (1, True), (0, True)]:
    case._rx(case._user_brake_msg(brake))
    case._rx(case._button_msg(0, main_button=press))
    # Check before the next SCC frame as well as afterwards: no transient XOR permission dip.
    for refresh in (False, True):
      if refresh:
        case._rx(case.packer.make_can_msg_safety('SCC_CONTROL', 1, {'MainMode_ACC': int(main_available), 'ACCMode': 0}))
      assert not case.safety.get_controls_allowed()
      assert not case.safety.get_lkas_on()
      assert case.safety.get_acc_main_on() == main_available
      assert case.safety.get_aol_allowed() == main_available
      case.safety.set_desired_angle_last(45)
      assert bool(case._tx(case._angle_cmd_msg(4.5, active))) == (not active or main_available)
  case._rx(case.packer.make_can_msg_safety('SCC_CONTROL', 1, {'MainMode_ACC': 0, 'ACCMode': 0}))
  assert not case.safety.get_aol_allowed()
  assert not case._tx(case._angle_cmd_msg(4.5, True))
