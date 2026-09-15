import math
from types import SimpleNamespace

import pytest

from cereal import car, log
from opendbc.car.hyundai.interface import CarInterface
from opendbc.car.hyundai.values import CAR
from openpilot.selfdrive.controls.lib.ev9_warnings import EV9SteeringWarning
from openpilot.selfdrive.controls.lib.latcontrol_angle import LatControlAngle
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


@pytest.mark.parametrize('speed_kph,threshold_kph,requested,expected', [
  (49.9, 50, 30, False), (50, 50, 30, False), (50.1, 50, 30, True),
  (2.5, 50, 89.9, False), (2.5, 50, 90, True), (2.5, 50, -90, True),
  (25, 25, 30, False), (25.1, 25, 30, True),
])
def test_active_warning_speed_and_angle_boundaries(speed_kph, threshold_kph, requested, expected):
  state = EV9SteeringWarning()
  measured = requested - (20 if requested > 0 else -20)
  for frame in range(30):
    result = sample(state, frame, speed=speed_kph / 3.6, requested=requested, measured=measured,
                    output=requested, threshold_kph=threshold_kph)
  assert result == expected


def test_long_gap_resets_pending_warning():
  state = EV9SteeringWarning()
  for frame in range(25):
    sample(state, frame)
  assert not sample(state, 100)
  assert not sample(state, 101)


def test_recent_driver_input_does_not_arm_warning_hysteresis():
  state = EV9SteeringWarning()
  for frame in range(200):
    assert not sample(state, frame, recent_steer_pressed=True, controller_saturated=True)
  assert not sample(state, 200, requested=88, measured=86, controller_saturated=True)
  assert sample(state, 201, controller_saturated=True)


class SM(dict):
  frame = 0


@pytest.mark.parametrize('source,gate,desired_curvature,model_valid,expected', [
  ('clipping', 'angle', 0.04, True, True),
  ('curvature', 'speed', 0.04, True, True),
  ('curvature', 'initial', 0.04, True, True),
  ('curvature', 'initial', 0.005, True, False),  # Not turning enough for the legacy path.
  ('curvature', 'initial', 0.015, True, False),  # Already achieving the requested curvature.
  ('curvature', 'initial', 0.04, False, False),
])
def test_controller_saturation_uses_existing_timer_and_legacy_gates(source, gate, desired_curvature, model_valid, expected):
  d = SelfdriveD.__new__(SelfdriveD)
  d.CP = CarInterface.get_non_essential_params(CAR.KIA_EV9)
  d.events, d.starpilot_events = Events(), Events(starpilot=True)
  d.last_steering_pressed_frame = 0
  d.starpilot_toggles = SimpleNamespace(hkg_tuning_ev9_alerts_speed_kph=50)
  controller = LatControlAngle(d.CP, None, 0.01)
  cs = car.CarState.new_message(vEgo=10)
  controls = log.ControlsState.new_message(curvature=0.015)
  controls.lateralControlState.init('angleState')
  output = car.CarOutput.new_message()
  d.sm = SM(controlsState=controls, carOutput=output, modelV2=SimpleNamespace(action=SimpleNamespace(desiredCurvature=desired_curvature)))
  d.sm.valid = {'modelV2': model_valid}

  def tick(frame, requested):
    cs.steeringAngleDeg = requested
    output.actuatorsOutput.steeringAngleDeg = requested - (5 if source == 'clipping' else 0)
    vm = SimpleNamespace(get_steer_from_curvature=lambda *args: math.radians(requested))
    _, _, angle_log = controller.update(True, cs, vm, SimpleNamespace(roll=0, angleOffsetDeg=0),
                                       source == 'clipping', desired_curvature, source == 'curvature', 0, None, None, SimpleNamespace())
    controls.lateralControlState.angleState = angle_log
    d.sm.frame = 300 + frame
    d.events.clear()
    d.update_steering_saturation_events(cs)
    return log.OnroadEvent.EventName.steerSaturated in d.events.names

  requested = 100 if gate == 'initial' else 80
  for frame in range(29):
    assert not tick(frame, requested)
  assert tick(29, requested) == (expected and gate == 'initial')
  assert controls.lateralControlState.angleState.saturated
  if gate != 'initial':
    # An already-saturated controller must warn on even one eligible sample, without another 0.3-second wait.
    if gate == 'speed':
      cs.vEgo = 51 / 3.6
    assert tick(30, 90 if gate == 'angle' else requested) == expected
    cs.vEgo = 10
    assert not tick(31, 80)


@pytest.mark.parametrize('sign,pressed,manual_mode,healthy,manual_override', [
  pytest.param(1, False, 0, True, False, id='left'),
  pytest.param(-1, False, 0, True, False, id='right'),
  pytest.param(1, True, 0, True, False, id='driver-contact'),
  pytest.param(1, False, 0, False, False, id='unhealthy-input'),
  pytest.param(1, False, 1, True, True, id='actual-manual-handoff'),
  pytest.param(1, False, 1, True, False, id='manual-option-without-handoff'),
  pytest.param(1, False, 2, True, False, id='legacy-manual-option-without-handoff'),
])
def test_slow_turn_generates_visible_audible_event_respects_driver_contact(sign, pressed, manual_mode, healthy, manual_override):
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
  for frame in range(300, 340):
    d.sm.frame = frame
    d.events.clear()
    d.update_steering_saturation_events(cs)
  assert (log.OnroadEvent.EventName.steerSaturated in d.events.names) == (not manual_override and healthy and not pressed)
  if not manual_override and healthy and not pressed:
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
