import pytest

from opendbc.car.hyundai.values import HyundaiSafetyFlags
from opendbc.safety import ALTERNATIVE_EXPERIENCE
from opendbc.safety.tests import test_hyundai_canfd


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
  if not main_initially_on:
    assert case.safety.get_aol_allowed()
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
