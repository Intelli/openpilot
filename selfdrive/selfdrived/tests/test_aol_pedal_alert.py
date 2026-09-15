from types import SimpleNamespace

import pytest

from cereal import car, log
from openpilot.selfdrive.selfdrived.events import AudibleAlert, ET, EventName, Events
from openpilot.selfdrive.selfdrived.state import State, StateMachine
from openpilot.selfdrive.selfdrived.alertmanager import AlertManager


class AlertSM(dict):
  healthy = True

  def all_checks(self, services):
    return self.healthy


def brake_alert(*, normal_enabled=True, pedal="brake", guard=None, pcm_disable=False):
  cs = SimpleNamespace(brakePressed=pedal == "brake", regenBraking=pedal == "regen", steerFaultTemporary=False,
                       steerFaultPermanent=False, standstill=False, vEgo=15.0, canValid=True, canTimeout=False, gearShifter=car.CarState.GearShifter.drive)
  cp = SimpleNamespace(minSteerSpeed=0.0, steerAtStandstill=False)
  toggles = SimpleNamespace(always_on_lateral_pause_speed=0.0)
  sm = AlertSM({
    "starpilotCarState": SimpleNamespace(alwaysOnLateralEnabled=True, pauseLateral=False),
    "carControl": SimpleNamespace(latActive=True),
    "starpilotPlan": SimpleNamespace(lateralCheck=True),
    "liveCalibration": SimpleNamespace(calStatus=log.LiveCalibrationData.Status.calibrated),
  })
  if guard == "temporary_fault":
    cs.steerFaultTemporary = True
  elif guard == "permanent_fault":
    cs.steerFaultPermanent = True
  elif guard == "aol_off":
    sm["starpilotCarState"].alwaysOnLateralEnabled = False
  elif guard == "paused":
    sm["starpilotCarState"].pauseLateral = True
  elif guard == "lat_inactive":
    sm["carControl"].latActive = False
  elif guard == "lateral_blocked":
    sm["starpilotPlan"].lateralCheck = False
  elif guard == "uncalibrated":
    sm["liveCalibration"].calStatus = log.LiveCalibrationData.Status.uncalibrated
  elif guard == "standstill":
    cs.standstill = True
  elif guard == "near_stop":
    cs.vEgo = 0.2
  elif guard == "can_invalid":
    cs.canValid = False
  elif guard == "can_timeout":
    cs.canTimeout = True
  elif guard == "brake_pause":
    toggles.always_on_lateral_pause_speed = 20.0
  elif guard == "unhealthy_service":
    sm.healthy = False
  elif guard == "reverse":
    cs.gearShifter = car.CarState.GearShifter.reverse
  events = Events()
  events.add(EventName.pedalPressed)
  if pcm_disable:
    events.add(EventName.pcmDisable)
  machine = StateMachine()
  machine.state = State.enabled if normal_enabled else State.disabled
  enabled, active = machine.update(events, Events(starpilot=True), sm["starpilotCarState"].alwaysOnLateralEnabled)
  assert not enabled and not active
  return events.create_alerts(machine.current_alert_types, [cp, cs, sm, False, 0, None, toggles]), sm


@pytest.mark.parametrize("pedal", ["brake", "regen"])
def test_brake_partial_disengagement_has_distinct_sound_and_clear_text(pedal):
  alerts, sm = brake_alert(pedal=pedal)
  alert, = alerts
  assert alert.event_type == ET.USER_DISABLE
  assert alert.audible_alert == AudibleAlert.prompt
  assert alert.duration == 20
  assert (alert.alert_text_1, alert.alert_text_2) == ("Cruise off", "Steering remains active")
  assert sm["carControl"].latActive


@pytest.mark.parametrize("guard", [
  "temporary_fault", "permanent_fault", "aol_off", "paused", "lat_inactive", "lateral_blocked", "uncalibrated", "standstill", "near_stop",
  "can_invalid", "can_timeout", "brake_pause", "unhealthy_service", "reverse",
])
def test_brake_full_disengagement_never_claims_steering_remains_active(guard):
  alerts, _ = brake_alert(guard=guard)
  alert, = alerts
  assert alert.audible_alert == AudibleAlert.disengage
  assert alert.alert_text_2 == ""


def test_pedal_alert_without_brake_or_regen_keeps_standard_disengagement():
  alerts, _ = brake_alert(pedal="gas")
  assert alerts[0].audible_alert == AudibleAlert.disengage


def test_brake_during_aol_only_does_not_repeat_cruise_disengagement():
  alerts, _ = brake_alert(normal_enabled=False)
  assert alerts == []


def test_simultaneous_pcm_and_pedal_disable_cannot_restore_standard_chime():
  alerts, _ = brake_alert(pcm_disable=True)
  assert len(alerts) == 2
  manager = AlertManager()
  manager.add_many(0, alerts)
  manager.process_alerts(0, set())
  assert manager.current_alert.audible_alert == AudibleAlert.prompt
  assert manager.current_alert.alert_text_2 == "Steering remains active"


def test_partial_disengagement_does_not_override_immediate_fault_alert():
  alerts, _ = brake_alert()
  events = Events()
  events.add(EventName.steerUnavailable)
  alerts += events.create_alerts([ET.IMMEDIATE_DISABLE])
  manager = AlertManager()
  manager.add_many(0, alerts)
  manager.process_alerts(0, set())
  assert manager.current_alert.event_type == ET.IMMEDIATE_DISABLE
  assert manager.current_alert.alert_text_2 != "Steering remains active"
