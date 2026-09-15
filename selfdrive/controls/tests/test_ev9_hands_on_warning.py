from types import SimpleNamespace

import pytest

from cereal import car, log
from opendbc.car.hyundai.interface import CarInterface
from opendbc.car.hyundai.values import CAR
from openpilot.selfdrive.controls.lib.ev9_warnings import ev9_warning_hands_on
from openpilot.selfdrive.selfdrived import selfdrived
from openpilot.selfdrive.selfdrived.alertmanager import AlertManager
from openpilot.selfdrive.selfdrived.events import Events
from openpilot.selfdrive.selfdrived.state import StateMachine


@pytest.mark.parametrize('age,expected', [(0, True), (300_000_000, True), (300_000_001, False), (-1, False)])
def test_hod_freshness_boundary(age, expected):
  cs = car.CarState.new_message(handsOnWheel=True, handsOnWheelTimestamp=1_000_000_000)
  assert ev9_warning_hands_on(cs, 1_000_000_000 + age) == expected
  cs.steeringPressed = True
  assert ev9_warning_hands_on(cs, 1_000_000_000 + age)


def test_missing_or_invalid_touch_cannot_suppress():
  cs = car.CarState.new_message(handsOnWheel=True)
  assert not ev9_warning_hands_on(cs, 1_000_000_000)
  cs.handsOnWheel = False
  cs.handsOnWheelTimestamp = 1_000_000_000
  assert not ev9_warning_hands_on(cs, 1_000_000_000)


class SM(dict):
  frame = 300


@pytest.mark.parametrize('goat', [False, True])
@pytest.mark.parametrize('contact', ['hod', 'stale_hod', 'torque'])
def test_contact_clears_cached_banner_and_published_sound_then_rearms(monkeypatch, goat, contact):
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
  controls = log.ControlsState.new_message()
  controls.lateralControlState.init('angleState')
  controls.lateralControlState.angleState.active = True
  controls.lateralControlState.angleState.steeringAngleDesiredDeg = 120
  output = car.CarOutput.new_message()
  output.actuatorsOutput.steeringAngleDeg = 90
  d.sm = SM(controlsState=controls, carOutput=output, starpilotPlan=SimpleNamespace(forcingStop=False))
  published = {}
  d.pm = SimpleNamespace(send=lambda service, message: published.update({service: message}))
  cs = car.CarState.new_message(vEgo=2, steeringAngleDeg=80)

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

  if contact in ('hod', 'stale_hod'):
    cs.handsOnWheel = True
    cs.handsOnWheelTimestamp = now[0]
  else:
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
  if contact == 'stale_hod':
    # A stopped sensor cannot indefinitely silence the warning.
    now[0] += 300_000_000
  else:
    cs.handsOnWheel = False
  cs.steeringPressed = False
  for _ in range(29):
    alert = tick()
    assert not d.ev9_steering_warning.warning
  tick()
  assert d.ev9_steering_warning.warning


@pytest.mark.parametrize('platform', [CAR.KIA_EV9, CAR.HYUNDAI_IONIQ_5_PE])
def test_hands_on_scope_is_ev9_only(platform):
  d = selfdrived.SelfdriveD.__new__(selfdrived.SelfdriveD)
  d.CP = CarInterface.get_non_essential_params(platform)
  assert d.ev9_warning_hands_on(car.CarState.new_message(steeringPressed=True)) == (platform == CAR.KIA_EV9)
