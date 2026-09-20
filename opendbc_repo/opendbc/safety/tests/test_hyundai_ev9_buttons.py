"""EV9 OP-long main-button and pause-knob intent through real CAN hooks."""

import pytest
from cffi import FFI

from opendbc.car import structs
from opendbc.car.hyundai.values import HyundaiSafetyFlags
from opendbc.safety import ALTERNATIVE_EXPERIENCE
from opendbc.safety.tests import test_hyundai_canfd
from opendbc.safety.tests.test_hyundai_ev9 import make_case
from opendbc.safety.tests.hyundai_common import Buttons
from opendbc.safety.tests.libsafety import libsafety_py


def setup_case(ev9=True, direct=True):
  case = make_case(ev9, direct)
  case._rx(case._button_msg(Buttons.NONE, main_button=1))
  case._rx(case._button_msg(Buttons.NONE))
  case.safety.set_controls_allowed(False)
  return case


def test_main_on_engages_once_and_main_off_disengages():
  case = make_case(True, True)
  assert not case._tx(case._accel_msg(0.5))
  assert case._rx(case._button_msg(Buttons.NONE, main_button=1))
  assert case.safety.get_acc_main_on()
  assert case.safety.get_controls_allowed()
  # A new main press turns main OFF even while controls remain enabled.
  case._rx(case._button_msg(Buttons.NONE))
  case._rx(case._button_msg(Buttons.NONE, main_button=1))
  assert not case.safety.get_acc_main_on()
  assert not case.safety.get_controls_allowed()
  assert not case._tx(case._accel_msg(0.5))


def test_main_engagement_preserves_acceleration_limits():
  case = make_case(True, True)
  case._rx(case._button_msg(Buttons.NONE, main_button=1))
  for accel in (-3.5, 0, 0.5, 3.5, -3.51, 3.51):
    msg = case.packer.make_can_msg_safety("SCC_CONTROL", case.PT_BUS, {
      "MainMode_ACC": 1, "ACCMode": 1, "aReqRaw": accel, "aReqValue": accel,
    })
    assert bool(case._tx(msg)) == (-3.5 <= accel <= 3.5)


def test_main_hold_and_release_cannot_reengage_after_disengagement():
  case = make_case(True, True)
  case._rx(case._button_msg(Buttons.NONE, main_button=1))
  assert case.safety.get_controls_allowed()
  case.safety.set_controls_allowed(False)
  for main_button in (1, 1, 1, 0, 0):
    case._rx(case._button_msg(Buttons.NONE, main_button=main_button))
    assert not case.safety.get_controls_allowed()
  # A complete OFF/ON sequence is a new engagement request.
  case._rx(case._button_msg(Buttons.NONE, main_button=1))
  case._rx(case._button_msg(Buttons.NONE))
  case._rx(case._button_msg(Buttons.NONE, main_button=1))
  assert case.safety.get_controls_allowed()


@pytest.mark.parametrize('guard', ['brake_pressed', 'regen_braking', 'steering_disengage',
                                  'safety_rx_checks_invalid', 'relay_malfunction'])
def test_main_on_blocked_by_guard_cannot_engage_when_guard_clears(guard):
  case = make_case(True, True)
  case._rx(case._speed_msg(case.STANDSTILL_THRESHOLD + 1))
  ffi = FFI()
  ffi.cdef(f'extern bool {guard};')
  native = ffi.dlopen(libsafety_py.libsafety_fn)
  try:
    setattr(native, guard, True)
    case._rx(case._button_msg(Buttons.NONE, main_button=1))
    assert case.safety.get_acc_main_on()
    assert not case.safety.get_controls_allowed()
  finally:
    setattr(native, guard, False)
  for main_button in (1, 1, 0, 0):
    case._rx(case._button_msg(Buttons.NONE, main_button=main_button))
    assert not case.safety.get_controls_allowed()
    assert not case._tx(case._accel_msg(0.5))


@pytest.mark.parametrize('pedal', ['brake', 'regen', 'gas'])
def test_main_engagement_preserves_set_pedal_semantics(pedal):
  case = make_case(True, True)
  case._rx(case._speed_msg(0))
  ffi = FFI()
  ffi.cdef('extern bool regen_braking;')
  native = ffi.dlopen(libsafety_py.libsafety_fn)
  try:
    if pedal == 'regen':
      native.regen_braking = True
      # Process the rising edge before main, just like an already-held brake.
      case._rx(case._button_msg(Buttons.NONE))
    else:
      msg = case._user_brake_msg if pedal == 'brake' else case._user_gas_msg
      case._rx(msg(1))
    case._rx(case._button_msg(Buttons.NONE, main_button=1))
    assert case.safety.get_controls_allowed()
    assert case._tx(case._accel_msg(0))
    if pedal == 'gas':
      assert not case._tx(case._accel_msg(0.5))
      assert not case._tx(case._accel_msg(-0.5))
      case._rx(case._user_gas_msg(0))
      assert case._tx(case._accel_msg(0.5))
    else:
      case._rx(case._speed_msg(case.STANDSTILL_THRESHOLD + 1))
      assert not case.safety.get_controls_allowed()
      assert not case._tx(case._accel_msg(0.5))
  finally:
    native.regen_braking = False


@pytest.mark.parametrize('cancel_already_held', [False, True])
def test_cancel_wins_over_main_on_and_release(cancel_already_held):
  case = make_case(True, True)
  if cancel_already_held:
    case._rx(case._button_msg(Buttons.CANCEL))
  case._rx(case._button_msg(Buttons.CANCEL, main_button=1))
  assert case.safety.get_acc_main_on()
  assert not case.safety.get_controls_allowed()
  case._rx(case._button_msg(Buttons.NONE))
  assert not case.safety.get_controls_allowed()


@pytest.mark.parametrize('ev9,direct', [(False, True), (True, False), (False, False)])
def test_main_does_not_engage_outside_ev9_op_long(ev9, direct):
  case = make_case(ev9, direct)
  for main_button in (1, 1, 0):
    case._rx(case._button_msg(Buttons.NONE, main_button=main_button))
    assert not case.safety.get_controls_allowed()


def test_wrong_bus_main_cannot_engage():
  case = make_case(True, True)
  case._rx(case._button_msg(Buttons.NONE, main_button=1, bus=0))
  assert not case.safety.get_controls_allowed()
  assert not case.safety.get_acc_main_on()


def test_inactive_knob_release_permits_longitudinal_tx():
  case = setup_case()
  assert not case._tx(case._accel_msg(0.5))
  for _ in range(4):
    assert case._rx(case._button_msg(Buttons.CANCEL))
    assert not case.safety.get_controls_allowed()
  assert case._rx(case._button_msg(Buttons.NONE))
  assert case.safety.get_controls_allowed()
  assert case._tx(case._accel_msg(0.5))


def test_active_cancel_hold_and_release_never_reengages():
  case = setup_case()
  case._rx(case._button_msg(Buttons.SET))
  case._rx(case._button_msg(Buttons.NONE))
  assert case.safety.get_controls_allowed()
  for _ in range(4):
    case._rx(case._button_msg(Buttons.CANCEL))
    assert not case.safety.get_controls_allowed()
  case._rx(case._button_msg(Buttons.NONE))
  assert not case.safety.get_controls_allowed()
  assert not case._tx(case._accel_msg(0.5))
  # A subsequent distinct press is a new engagement request.
  case._rx(case._button_msg(Buttons.CANCEL))
  case._rx(case._button_msg(Buttons.NONE))
  assert case.safety.get_controls_allowed()


@pytest.mark.parametrize('other', [Buttons.SET, Buttons.RESUME, 3])
def test_direct_other_button_to_cancel_does_not_arm(other):
  case = setup_case()
  case._rx(case._button_msg(other))
  case._rx(case._button_msg(Buttons.CANCEL))
  assert not case.safety.get_controls_allowed()
  case._rx(case._button_msg(Buttons.NONE))
  assert not case.safety.get_controls_allowed()


@pytest.mark.parametrize('other', [Buttons.SET, Buttons.RESUME, 3])
def test_cancel_switch_to_other_button_is_not_a_release(other):
  case = setup_case()
  case._rx(case._button_msg(Buttons.CANCEL))
  case._rx(case._button_msg(other))
  assert not case.safety.get_controls_allowed()


@pytest.mark.parametrize('pedal', ['brake', 'gas'])
@pytest.mark.parametrize('clear_before_release', [False, True])
def test_pedal_during_hold_invalidates_intent(pedal, clear_before_release):
  case = setup_case()
  case._rx(case._button_msg(Buttons.CANCEL))
  msg = case._user_brake_msg if pedal == 'brake' else case._user_gas_msg
  case._rx(msg(1))
  if clear_before_release:
    case._rx(msg(0))
  case._rx(case._button_msg(Buttons.NONE))
  assert not case.safety.get_controls_allowed()


def test_main_off_during_hold_and_back_on_requires_fresh_press():
  case = setup_case()
  case._rx(case._button_msg(Buttons.CANCEL))
  case._rx(case._button_msg(Buttons.CANCEL, main_button=1))
  assert not case.safety.get_acc_main_on()
  case._rx(case._button_msg(Buttons.CANCEL))
  case._rx(case._button_msg(Buttons.CANCEL, main_button=1))
  assert case.safety.get_acc_main_on()
  case._rx(case._button_msg(Buttons.NONE))
  assert not case.safety.get_controls_allowed()


def test_reinitialization_clears_pending_press():
  case = setup_case()
  case._rx(case._button_msg(Buttons.CANCEL))
  case.safety.set_safety_hooks(structs.CarParams.SafetyModel.hyundaiCanfd, case.SAFETY_PARAM)
  case._rx(case._button_msg(Buttons.NONE))
  assert not case.safety.get_controls_allowed()


@pytest.mark.parametrize('guard', ['regen_braking', 'steering_disengage', 'safety_rx_checks_invalid', 'relay_malfunction'])
def test_interrupted_hold_does_not_survive_cleared_safety_guard(guard):
  case = setup_case()
  # These common gates have no EV9 receive signal/setter. Exercise their native
  # state explicitly, then drive the real RX hook to verify the pending intent.
  ffi = FFI()
  ffi.cdef(f'extern bool {guard};')
  native = ffi.dlopen(libsafety_py.libsafety_fn)
  case._rx(case._button_msg(Buttons.CANCEL))
  try:
    setattr(native, guard, True)
    case._rx(case._button_msg(Buttons.CANCEL))
  finally:
    setattr(native, guard, False)
  case._rx(case._button_msg(Buttons.NONE))
  assert not case.safety.get_controls_allowed()


@pytest.mark.parametrize('ev9,direct', [(False, True), (True, False), (False, False)])
def test_no_cancel_engagement_outside_ev9_op_long(ev9, direct):
  case = setup_case(ev9, direct)
  case._rx(case._button_msg(Buttons.CANCEL))
  case._rx(case._button_msg(Buttons.NONE))
  assert not case.safety.get_controls_allowed()


def test_wrong_bus_cannot_complete_pending_press():
  case = setup_case()
  case._rx(case._button_msg(Buttons.CANCEL))
  case._rx(case._button_msg(Buttons.NONE, bus=0))
  assert not case.safety.get_controls_allowed()


def test_rejected_counter_cannot_complete_pending_press():
  case = setup_case()
  press = case._button_msg(Buttons.CANCEL)
  for _ in range(10):
    case._rx(press)
  release = case._button_msg(Buttons.NONE)
  # Keep the rejected sequence's counter rather than letting the packer advance it.
  release[0].data[1] = press[0].data[1]
  assert not case._rx(release)
  assert not case.safety.get_controls_allowed()
  for _ in range(10):
    case._rx(case._button_msg(Buttons.NONE))
    assert not case.safety.get_controls_allowed()
  case._rx(case._button_msg(Buttons.CANCEL))
  case._rx(case._button_msg(Buttons.NONE))
  assert case.safety.get_controls_allowed()


@pytest.mark.parametrize("main_initially_on", [False, True])
def test_ev9_stock_acc_main_allows_aol_during_braking_without_cruise_engagement(main_initially_on):
  case = test_hyundai_canfd.TestHyundaiCanfdLKASteeringAltAngleLongEV(methodName="test_lateral_accel_limit")
  case.SAFETY_PARAM = (HyundaiSafetyFlags.CANFD_LKA_STEERING | HyundaiSafetyFlags.CANFD_LKA_STEERING_ALT |
                       HyundaiSafetyFlags.CANFD_ANGLE_STEERING | HyundaiSafetyFlags.EV_GAS | HyundaiSafetyFlags.CANFD_EV9)
  case.setUp()
  case.safety.set_alternative_experience(ALTERNATIVE_EXPERIENCE.ALWAYS_ON_LATERAL)
  case._reset_speed_measurement(case.STANDSTILL_THRESHOLD + 1)
  case._rx(case.packer.make_can_msg_safety("SCC_CONTROL", case.SCC_BUS, {"MainMode_ACC": int(main_initially_on), "ACCMode": 0}))
  case._rx(case._user_brake_msg(True))
  assert not case.safety.get_controls_allowed()

  case._rx(case._button_msg(0, main_button=1))
  # A button edge cannot invent main availability or invert the last SCC report.
  assert case.safety.get_aol_allowed() == main_initially_on
  case._rx(case._button_msg(0, main_button=0))
  # Stock SCC continues reporting main availability while ACCMode remains zero.
  case._rx(case.packer.make_can_msg_safety("SCC_CONTROL", case.SCC_BUS, {"MainMode_ACC": 1, "ACCMode": 0}))
  case._rx(case._user_brake_msg(True))
  assert not case.safety.get_controls_allowed()
  assert case.safety.get_aol_allowed()
  assert case._tx(case._angle_cmd_msg(0, enabled=True))

  case.safety.set_alternative_experience(0)
  case._rx(case._user_brake_msg(True))
  assert not case.safety.get_aol_allowed()
  assert not case._tx(case._angle_cmd_msg(0, enabled=True))
