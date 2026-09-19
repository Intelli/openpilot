from types import SimpleNamespace

import pytest

from opendbc.car import ButtonType, structs
from opendbc.car.hyundai.values import CAR
from openpilot.selfdrive.car.cruise import VCruiseHelper, V_CRUISE_UNSET
from openpilot.selfdrive.car.ev9_cruise_buttons import EV9CruiseButtons


def setup(*, fingerprint=CAR.KIA_EV9, op_long=True, pcm_cruise=False):
  cp = structs.CarParams(brand="hyundai", carFingerprint=fingerprint, openpilotLongitudinalControl=op_long, pcmCruise=pcm_cruise)
  cs = structs.CarState(vEgo=20, canValid=True, gearShifter="drive", cruiseState={"available": True})
  return cp, cs, EV9CruiseButtons(), VCruiseHelper(cp)


def event(button, pressed):
  return structs.CarState.ButtonEvent(type=button, pressed=pressed)


def update(buttons, cp, cs, button, pressed, *, enabled=False, initialized=False):
  cs.buttonEvents = [event(button, pressed)] if button is not None else []
  buttons.update(cp, cs, enabled=enabled, cruise_initialized=initialized)
  return [(b.type.raw, b.pressed) for b in cs.buttonEvents]


@pytest.mark.parametrize("button", [ButtonType.accelCruise, ButtonType.decelCruise, ButtonType.cancel])
def test_any_knob_action_can_set_initial_speed_on_release(button):
  cp, cs, buttons, cruise = setup()
  assert update(buttons, cp, cs, button, True) == [(ButtonType.decelCruise, True)]
  assert not cs.buttonEnable
  assert update(buttons, cp, cs, button, False) == [(ButtonType.decelCruise, False)]
  assert cs.buttonEnable
  # The real resumeBlocked predicate cannot match either normalized edge.
  assert not any(b.type in (ButtonType.accelCruise, ButtonType.resumeCruise) for b in cs.buttonEvents)
  cruise.initialize_v_cruise(cs, False, False, SimpleNamespace(set_speed_limit=False))
  assert cruise.v_cruise_kph == 72


@pytest.mark.parametrize("button,expected", [(ButtonType.accelCruise, 100), (ButtonType.decelCruise, 72), (ButtonType.cancel, 72)])
def test_resume_retains_speed_but_set_and_knob_press_use_current_speed(button, expected):
  cp, cs, buttons, cruise = setup()
  cruise.v_cruise_kph = cruise.v_cruise_kph_last = 100
  for pressed in (True, False):
    update(buttons, cp, cs, button, pressed, initialized=True)
  assert cs.buttonEnable
  resume = any(b.type == ButtonType.accelCruise for b in cs.buttonEvents)
  cruise.initialize_v_cruise(cs, False, resume, SimpleNamespace(set_speed_limit=False))
  assert cruise.v_cruise_kph == expected


@pytest.mark.parametrize("button,expected", [(ButtonType.accelCruise, 73), (ButtonType.decelCruise, 71)])
def test_engaged_up_down_keep_normal_speed_adjustment(button, expected):
  cp, cs, buttons, cruise = setup()
  toggles = SimpleNamespace(cruise_increase=1, cruise_increase_long=5, set_speed_limit=False)
  cruise.initialize_v_cruise(cs, False, False, toggles)
  for pressed in (True, False):
    assert update(buttons, cp, cs, button, pressed, enabled=True, initialized=True) == [(button, pressed)]
    cruise.update_v_cruise(cs, True, True, False, toggles)
  assert cruise.v_cruise_kph == expected


def test_active_cancel_never_becomes_set_after_disengagement_during_hold():
  cp, cs, buttons, _ = setup()
  assert update(buttons, cp, cs, ButtonType.cancel, True, enabled=True) == [(ButtonType.cancel, True)]
  assert not cs.buttonEnable
  # Repeated pressed samples and a software state change cannot reinterpret the hold.
  assert update(buttons, cp, cs, ButtonType.cancel, True) == [(ButtonType.cancel, True)]
  assert update(buttons, cp, cs, ButtonType.cancel, False) == [(ButtonType.cancel, False)]
  assert not cs.buttonEnable
  # A separate subsequent physical press can engage.
  update(buttons, cp, cs, ButtonType.cancel, True)
  update(buttons, cp, cs, ButtonType.cancel, False)
  assert cs.buttonEnable


def test_initial_resume_mapping_is_stable_even_if_speed_initializes_during_hold():
  cp, cs, buttons, _ = setup()
  update(buttons, cp, cs, ButtonType.accelCruise, True)
  assert update(buttons, cp, cs, ButtonType.accelCruise, False, enabled=True, initialized=True) == [(ButtonType.decelCruise, False)]


def test_unknown_engagement_state_does_not_convert_cancel_to_set():
  cp, cs, buttons, _ = setup()
  update(buttons, cp, cs, ButtonType.cancel, True, enabled=None)
  assert update(buttons, cp, cs, ButtonType.cancel, False) == [(ButtonType.cancel, False)]
  assert not cs.buttonEnable


@pytest.mark.parametrize("button", [ButtonType.accelCruise, ButtonType.cancel])
def test_loss_of_engagement_telemetry_during_new_set_request_blocks_release(button):
  cp, cs, buttons, _ = setup()
  update(buttons, cp, cs, button, True)
  update(buttons, cp, cs, None, False, enabled=None)
  assert update(buttons, cp, cs, button, False) == [(ButtonType.decelCruise, False)]
  assert not cs.buttonEnable


def test_unpaired_cancel_release_cannot_engage():
  cp, cs, buttons, _ = setup()
  assert update(buttons, cp, cs, ButtonType.cancel, False) == [(ButtonType.cancel, False)]
  assert not cs.buttonEnable


@pytest.mark.parametrize("field,value", [
  ("brakePressed", True), ("gasPressed", True), ("regenBraking", True), ("steeringDisengage", True),
  ("canValid", False), ("canTimeout", True), ("available", False),
])
@pytest.mark.parametrize("interrupt_at_press", [False, True])
def test_interrupted_knob_press_needs_a_fresh_press(field, value, interrupt_at_press):
  cp, cs, buttons, _ = setup()
  target = cs.cruiseState if field == "available" else cs
  if not interrupt_at_press:
    update(buttons, cp, cs, ButtonType.cancel, True)
  setattr(target, field, value)
  update(buttons, cp, cs, ButtonType.cancel if interrupt_at_press else None, True)
  setattr(target, field, not value)
  update(buttons, cp, cs, ButtonType.cancel, False)
  assert not cs.buttonEnable
  update(buttons, cp, cs, ButtonType.cancel, True)
  update(buttons, cp, cs, ButtonType.cancel, False)
  assert cs.buttonEnable


@pytest.mark.parametrize("before_cancel", [True, False])
def test_direct_switch_between_cancel_and_other_knob_action_cannot_engage_cancel(before_cancel):
  cp, cs, buttons, _ = setup()
  first, second = (ButtonType.accelCruise, ButtonType.cancel) if before_cancel else (ButtonType.cancel, ButtonType.accelCruise)
  update(buttons, cp, cs, first, True)
  cs.buttonEvents = [event(first, False), event(second, True)]
  buttons.update(cp, cs, enabled=False, cruise_initialized=False)
  if before_cancel:
    update(buttons, cp, cs, second, False)
  assert not cs.buttonEnable


@pytest.mark.parametrize("config", [
  {"op_long": False, "pcm_cruise": True}, {"pcm_cruise": True}, {"fingerprint": CAR.HYUNDAI_IONIQ_5_PE},
])
@pytest.mark.parametrize("button", [ButtonType.accelCruise, ButtonType.decelCruise, ButtonType.cancel])
def test_stock_fallback_and_other_cars_remain_unchanged(config, button):
  cp, cs, buttons, _ = setup(**config)
  for pressed in (True, False):
    cs.buttonEnable = True
    assert update(buttons, cp, cs, button, pressed) == [(button, pressed)]
    assert cs.buttonEnable


def test_fallback_discards_pending_engagement_remap():
  cp, cs, buttons, _ = setup()
  update(buttons, cp, cs, ButtonType.cancel, True)
  cp.openpilotLongitudinalControl = False
  cp.pcmCruise = True
  cs.buttonEnable = False
  assert update(buttons, cp, cs, ButtonType.cancel, False) == [(ButtonType.cancel, False)]
  assert not cs.buttonEnable


def test_non_knob_events_remain_available_for_lateral_and_distance_controls():
  cp, cs, buttons, cruise = setup()
  assert cruise.v_cruise_kph == V_CRUISE_UNSET
  for button in (ButtonType.mainCruise, ButtonType.lkas, ButtonType.gapAdjustCruise):
    for pressed in (True, False):
      assert update(buttons, cp, cs, button, pressed) == [(button, pressed)]
      assert not cs.buttonEnable


@pytest.mark.parametrize("button", [ButtonType.accelCruise, ButtonType.decelCruise, ButtonType.cancel])
@pytest.mark.parametrize("main_available", [False, True])
def test_real_engagement_state_machine_and_cancel_release(button, main_available):
  from openpilot.selfdrive.car.car_specific import CarSpecificEvents
  from openpilot.selfdrive.selfdrived.events import Events
  from openpilot.selfdrive.selfdrived.state import StateMachine

  cp, cs, buttons, _ = setup()
  cs.cruiseState.available = main_available
  car_events = CarSpecificEvents(cp)
  state = StateMachine()
  enabled = False
  for pressed in (True, False):
    update(buttons, cp, cs, button, pressed, enabled=enabled)
    events = car_events.update(cs, cs, structs.CarControl(enabled=enabled))
    enabled, _ = state.update(events, Events(starpilot=True), False)
    assert enabled == (not pressed and main_available)

  if main_available:
    for pressed in (True, False):
      update(buttons, cp, cs, ButtonType.cancel, pressed, enabled=enabled)
      events = car_events.update(cs, cs, structs.CarControl(enabled=enabled))
      enabled, _ = state.update(events, Events(starpilot=True), False)
      assert not enabled


@pytest.mark.parametrize("button", [ButtonType.accelCruise, ButtonType.decelCruise, ButtonType.cancel])
def test_card_normalizes_before_speed_handling_and_publish(monkeypatch, button):
  from cereal import custom
  from openpilot.selfdrive.car import card

  cp, cs, buttons, cruise = setup()
  control = structs.CarControl()

  class SubMaster(dict):
    seen = {"carControl": True}

    def update(self, _timeout):
      pass

    def all_checks(self, _services):
      return True

  car = card.Car.__new__(card.Car)
  car.CP = cp
  car.CI = SimpleNamespace(update=lambda *_: (cs, custom.StarPilotCarState.new_message()))
  car.RI = SimpleNamespace(update=lambda _: None)
  car._inject_favorite_virtual_cruise_events = lambda _: None
  car.sm = SubMaster(carControl=control, starpilotPlan=custom.StarPilotPlan.new_message())
  car.can_sock = None
  car.can_rcv_cum_timeout_counter = 0
  car.ev9_cruise_buttons = buttons
  car.v_cruise_helper = cruise
  car.params_memory = SimpleNamespace(get_float=lambda _: 0)
  car.starpilot_toggles = SimpleNamespace(speed_limit_controller=False, set_speed_limit=False)
  car.is_metric = True
  car.experimental_mode = False
  car.CC_prev = structs.CarControl()
  car.resume_prev_button = False
  car.starpilot_card = SimpleNamespace(update=lambda _cs, fpcs, *_: fpcs)
  monkeypatch.setattr(card.messaging, "drain_sock_raw", lambda *_, **__: [])
  monkeypatch.setattr(card, "can_capnp_to_list", lambda _: [])

  for pressed in (True, False):
    cs.buttonEvents = [event(button, pressed)]
    output, _, _ = car.state_update()
    assert output.buttonEvents[0].type == ButtonType.decelCruise
    assert output.buttonEnable == (not pressed)
    assert not car.resume_prev_button

  car.CS_prev = output.as_reader()
  control.enabled = True
  cs.buttonEvents = []
  output, _, _ = car.state_update()
  assert output.vCruise == 72

  # Favorites may adjust speed, but their virtual edges must not acquire the
  # physical knob's permission to engage longitudinal control.
  control.enabled = False
  car.CC_prev = structs.CarControl(enabled=True)
  car._inject_favorite_virtual_cruise_events = lambda state: setattr(state, "buttonEvents", [event(ButtonType.accelCruise, False)])
  cs.buttonEvents = []
  output, _, _ = car.state_update()
  assert output.buttonEvents[0].type == ButtonType.accelCruise
  assert not output.buttonEnable
