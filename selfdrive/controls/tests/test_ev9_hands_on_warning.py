from types import SimpleNamespace

import pytest

from cereal import car, log
from opendbc.car.hyundai.interface import CarInterface
from opendbc.car.hyundai.values import CAR
from openpilot.selfdrive.controls.lib.ev9_warnings import ev9_driver_steering_pressed
from openpilot.selfdrive.selfdrived import selfdrived
from openpilot.selfdrive.selfdrived.alertmanager import AlertManager
from openpilot.selfdrive.selfdrived.events import Events
from openpilot.selfdrive.selfdrived.state import StateMachine


class SM(dict):
  frame = 300


@pytest.mark.parametrize('timestamp,contact,expected', [
  (1_000_000_000, False, False), (1_000_000_000, True, True),
  (699_999_999, False, True), (1_000_000_001, False, True), (0, False, True),
])
def test_only_fresh_explicit_no_contact_rejects_torque_input(timestamp, contact, expected):
  cs = car.CarState.new_message(steeringPressed=True, handsOnWheel=contact, handsOnWheelTimestamp=timestamp)
  assert ev9_driver_steering_pressed(cs, 1_000_000_000) == expected


def test_replay_uses_recorded_car_state_time_for_contact_freshness(monkeypatch):
  monkeypatch.setattr(selfdrived, 'REPLAY', True)
  d = selfdrived.SelfdriveD.__new__(selfdrived.SelfdriveD)
  d.CP = CarInterface.get_non_essential_params(CAR.KIA_EV9)
  d.car_state_mono_time = 1_000_000_000
  cs = car.CarState.new_message(steeringPressed=True, handsOnWheel=False, handsOnWheelTimestamp=1_000_000_000)
  assert not d.steering_pressed_for_warning(cs)
  d.car_state_mono_time += 300_000_001
  assert d.steering_pressed_for_warning(cs)


@pytest.mark.parametrize('frames_since_input,expected', [(0, True), (199, True), (200, False)])
def test_legacy_two_second_driver_input_boundary(frames_since_input, expected):
  d = selfdrived.SelfdriveD.__new__(selfdrived.SelfdriveD)
  d.CP = CarInterface.get_non_essential_params(CAR.KIA_EV9)
  d.last_steering_pressed_frame = 300
  d.sm = SM()
  d.sm.frame = 300 + frames_since_input
  cs = car.CarState.new_message(handsOnWheel=True, handsOnWheelTimestamp=1_000_000_000)
  assert d.ev9_warning_suppressed_by_driver(cs) == expected
  cs.steeringPressed = True
  assert d.ev9_warning_suppressed_by_driver(cs)


@pytest.mark.parametrize('goat', [False, True])
@pytest.mark.parametrize('controller_saturated', [False, True])
def test_torque_clears_cached_banner_and_sound_for_two_seconds(monkeypatch, goat, controller_saturated):
  now = [1_000_000_000]
  monkeypatch.setattr(selfdrived.time, 'monotonic_ns', lambda: now[0])
  d = selfdrived.SelfdriveD.__new__(selfdrived.SelfdriveD)
  d.CP = CarInterface.get_non_essential_params(CAR.KIA_EV9)
  d.events, d.starpilot_events = Events(), Events(starpilot=True)
  d.events_prev, d.starpilot_events_prev = [], []
  d.AM, d.starpilot_AM = AlertManager(), AlertManager()
  d.state_machine = StateMachine()
  d.personality = log.LongitudinalPersonality.standard
  d.is_metric = True
  d.experimental_mode = False
  d.forcing_stop_chime_played = False
  d.last_steering_pressed_frame = 0
  d.last_steer_saturated_alert_time = 0
  d.starpilot_toggles = SimpleNamespace(goat_scream_alert=goat, hkg_tuning_ev9_alerts_speed_kph=50)
  controls = log.ControlsState.new_message(curvature=0.015)
  controls.lateralControlState.init('angleState')
  controls.lateralControlState.angleState.active = True
  controls.lateralControlState.angleState.saturated = controller_saturated
  requested = 30 if controller_saturated else 120
  controls.lateralControlState.angleState.steeringAngleDesiredDeg = requested
  output = car.CarOutput.new_message()
  output.actuatorsOutput.steeringAngleDeg = requested if controller_saturated else 90
  d.sm = SM(controlsState=controls, carOutput=output, starpilotPlan=SimpleNamespace(forcingStop=False),
            modelV2=SimpleNamespace(action=SimpleNamespace(desiredCurvature=0.04)))
  published = {}
  d.pm = SimpleNamespace(send=lambda service, message: published.update({service: message}))
  cs = car.CarState.new_message(vEgo=20 if controller_saturated else 10,
                                steeringAngleDeg=requested if controller_saturated else 80)

  def tick(extra_event=None):
    d.sm.frame += 1
    now[0] += 10_000_000
    d.events.clear()
    d.starpilot_events.clear()
    d.update_steering_saturation_events(cs)
    if extra_event is not None:
      d.events.add(extra_event)
    d.enabled, d.active = d.state_machine.update(d.events, d.starpilot_events, True)
    d.update_alerts(cs)
    d.publish_selfdriveState(cs)
    return published['starpilotSelfdriveState'].starpilotSelfdriveState if goat else published['selfdriveState'].selfdriveState

  for _ in range(30):
    alert = tick()
  assert alert.alertType.endswith('SteerSaturated/warning') if goat else alert.alertType == 'steerSaturated/warning'
  assert alert.alertSound.raw != 0

  # EPS torque pulses with fresh explicit no-contact must not clear the alert or restart the holdoff.
  for frame in range(30):
    cs.steeringPressed = frame % 2 == 0
    cs.handsOnWheelTimestamp = now[0]
    assert tick().alertSound.raw != 0
    assert d.ev9_steering_warning.warning
    assert d.last_steering_pressed_frame == 0
  cs.steeringPressed = False

  # Fresh capacitive contact alone must not suppress the warning.
  cs.handsOnWheel = True
  cs.handsOnWheelTimestamp = now[0]
  assert tick().alertSound.raw != 0
  assert d.ev9_steering_warning.warning

  cs.steeringPressed = True
  alert = tick()
  assert alert.alertType == ''
  assert alert.alertSound.raw == 0
  assert not d.ev9_steering_warning.warning
  assert 'steerSaturated/warning' not in d.AM.alerts
  assert 'goatSteerSaturated/warning' not in d.starpilot_AM.alerts

  # Driver-monitoring alerts are not removed by the steering-warning filter.
  tick(log.OnroadEvent.EventName.driverDistracted2)
  assert published['selfdriveState'].selfdriveState.alertType == 'driverDistracted2/permanent'
  cs.steeringPressed = False
  last_input_frame = d.sm.frame
  for _ in range(199):
    tick()
    assert not d.ev9_steering_warning.warning
    assert 'steerSaturated/warning' not in d.AM.alerts
    assert 'goatSteerSaturated/warning' not in d.starpilot_AM.alerts
  tick()
  assert d.sm.frame - last_input_frame == 200
  assert d.ev9_steering_warning.warning


@pytest.mark.parametrize('platform', [CAR.KIA_EV9, CAR.HYUNDAI_IONIQ_5_PE])
def test_driver_suppression_scope_is_ev9_only(platform):
  d = selfdrived.SelfdriveD.__new__(selfdrived.SelfdriveD)
  d.CP = CarInterface.get_non_essential_params(platform)
  assert d.ev9_warning_suppressed_by_driver(car.CarState.new_message(steeringPressed=True)) == (platform == CAR.KIA_EV9)
