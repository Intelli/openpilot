from types import SimpleNamespace

import pytest

from cereal import car, log
from opendbc.car.hyundai.interface import CarInterface
from opendbc.car.hyundai.values import CAR
from openpilot.selfdrive.controls.lib.ev9_warnings import EV9SteeringWarning
from openpilot.selfdrive.selfdrived.events import Events, ET
from openpilot.selfdrive.selfdrived.selfdrived import SelfdriveD


def sample(state, frame, **overrides):
  args = dict(now=frame * 0.01, active=True, speed=2, requested=100, measured=80, output=100, threshold_kph=50)
  args.update(overrides)
  return state.update(**args)


def test_persistence_and_hysteresis():
  state = EV9SteeringWarning()
  for frame in range(29):
    assert not sample(state, frame)
  assert sample(state, 29)
  assert sample(state, 30, requested=88, measured=86, output=88)
  assert not sample(state, 31, requested=88, measured=87, output=88)
  assert not sample(state, 32)


@pytest.mark.parametrize('changes', [dict(active=False), dict(speed=0), dict(requested=89), dict(measured=105),
                                    dict(manual_following=True), dict(requested=float('nan'))])
def test_ineligible_or_following_driver_does_not_warn(changes):
  state = EV9SteeringWarning()
  for frame in range(40):
    assert not sample(state, frame, **changes)


def test_configured_speed_policy_and_command_clip():
  state = EV9SteeringWarning()
  for frame in range(40):
    result = sample(state, frame, speed=8, threshold_kph=25, requested=30, measured=30, output=20)
  assert result
  assert not sample(state, 40, active=False)


def test_long_gap_resets_pending_warning():
  state = EV9SteeringWarning()
  for frame in range(25):
    sample(state, frame)
  assert not sample(state, 100)
  assert not sample(state, 101)


class SM(dict):
  frame = 0


@pytest.mark.parametrize('manual_override', [False, True])
@pytest.mark.parametrize('healthy', [False, True])
@pytest.mark.parametrize('sign', [-1, 1])
@pytest.mark.parametrize('pressed', [False, True])
@pytest.mark.parametrize('manual_mode', [0, 1, 2])
def test_slow_turn_generates_visible_audible_event_while_driver_assists(sign, pressed, manual_mode, healthy, manual_override):
  d = SelfdriveD.__new__(SelfdriveD)
  d.CP = CarInterface.get_non_essential_params(CAR.KIA_EV9)
  d.events = Events()
  d.starpilot_events = Events(starpilot=True)
  d.last_steering_pressed_frame = 0
  d.starpilot_toggles = SimpleNamespace(hkg_shared_autonomy_mode=manual_mode, hkg_tuning_ev9_alerts_speed_kph=50)
  cs = car.CarState.new_message(vEgo=2, steeringAngleDeg=sign * 80, steeringPressed=pressed)
  controls = log.ControlsState.new_message()
  controls.lateralControlState.init('angleState')
  controls.lateralControlState.angleState.active = True
  controls.lateralControlState.angleState.steeringAngleDesiredDeg = sign * 100
  output = car.CarOutput.new_message()
  output.actuatorsOutput.steeringAngleDeg = sign * 80
  output.actuatorsOutput.manualSteeringOverride = manual_override
  d.sm = SM(controlsState=controls, carOutput=output)
  d.sm.valid = {"controlsState": healthy, "carOutput": healthy}
  for frame in range(100, 140):
    d.sm.frame = frame
    d.events.clear()
    d.update_steering_saturation_events(cs)
  assert (log.OnroadEvent.EventName.steerSaturated in d.events.names) == (not manual_override and healthy)
  if not manual_override and healthy:
    alerts = d.events.create_alerts([ET.WARNING], [d.CP])
    assert len(alerts) == 1
    assert alerts[0].alert_text_1 == 'Turn Exceeds Steering Limit'
    assert alerts[0].audible_alert == log.SelfdriveState.AudibleAlert.promptRepeat
    assert alerts[0].alert_size == log.SelfdriveState.AlertSize.small


@pytest.mark.parametrize('sign', [-1, 1])
@pytest.mark.parametrize('requested,measured,output,expected', [
  (90, 87.5, 90, False),
  (90, 87.49, 90, True),
  (90, 95, 90, False),  # Driver has already turned farther than requested.
  (90, 90, 87.49, True),  # Command clipping remains visible while the driver helps.
])
def test_directional_tracking_and_clipping_boundaries(sign, requested, measured, output, expected):
  state = EV9SteeringWarning()
  for frame in range(40):
    result = sample(state, frame, requested=sign * requested, measured=sign * measured, output=sign * output)
  assert result == expected


def test_bad_clock_recovers_without_carrying_persistence():
  state = EV9SteeringWarning()
  assert not sample(state, 0, now=float('nan'))
  for frame in range(29):
    assert not sample(state, frame)
  assert sample(state, 29)


@pytest.mark.parametrize('pressed,speed,expected', [(False, 10, True), (True, 10, False), (False, 2, False)])
def test_other_hyundai_retains_generic_takeover_gates(pressed, speed, expected):
  d = SelfdriveD.__new__(SelfdriveD)
  d.CP = CarInterface.get_non_essential_params(CAR.HYUNDAI_IONIQ_5_PE)
  d.events, d.starpilot_events = Events(), Events(starpilot=True)
  d.last_steering_pressed_frame = 0
  d.starpilot_toggles = SimpleNamespace(goat_scream_alert=False)
  cs = car.CarState.new_message(vEgo=speed, steeringAngleDeg=80, steeringPressed=pressed)
  controls = log.ControlsState.new_message(curvature=0.015)
  controls.lateralControlState.init('angleState')
  controls.lateralControlState.angleState.active = True
  controls.lateralControlState.angleState.saturated = True
  controls.lateralControlState.angleState.steeringAngleDesiredDeg = 100
  d.sm = SM(controlsState=controls, modelV2=SimpleNamespace(action=SimpleNamespace(desiredCurvature=0.04)))
  d.sm.frame = 1000
  d.update_steering_saturation_events(cs)
  assert (log.OnroadEvent.EventName.steerSaturated in d.events.names) == expected


def test_existing_sound_selection_and_cooldown_are_preserved(monkeypatch):
  from openpilot.selfdrive.selfdrived import selfdrived
  d = SelfdriveD.__new__(SelfdriveD)
  d.events, d.starpilot_events = Events(), Events(starpilot=True)
  d.starpilot_toggles = SimpleNamespace(goat_scream_alert=True)
  d.last_steer_saturated_alert_time = 10
  monkeypatch.setattr(selfdrived.time, 'monotonic', lambda: 11)
  d.add_steering_saturation_event(True, 2)
  assert not d.events.names and not d.starpilot_events.names
  monkeypatch.setattr(selfdrived.time, 'monotonic', lambda: 12)
  d.add_steering_saturation_event(True, 2)
  assert selfdrived.StarPilotEventName.goatSteerSaturated in d.starpilot_events.names
  assert not d.events.names


@pytest.mark.parametrize('control_type', ['pidState', 'debugState'])
def test_startup_or_debug_control_state_resets_ev9_warning(control_type):
  d = SelfdriveD.__new__(SelfdriveD)
  d.CP = CarInterface.get_non_essential_params(CAR.KIA_EV9)
  d.events, d.starpilot_events = Events(), Events(starpilot=True)
  d.last_steering_pressed_frame = 0
  d.starpilot_toggles = SimpleNamespace()
  d.ev9_steering_warning = EV9SteeringWarning(elapsed=1, warning=True)
  controls = log.ControlsState.new_message()
  controls.lateralControlState.init(control_type)
  d.sm = SM(controlsState=controls, carOutput=car.CarOutput.new_message())
  d.update_steering_saturation_events(car.CarState.new_message(vEgo=10))
  assert not d.ev9_steering_warning.warning
  assert not d.events.names
