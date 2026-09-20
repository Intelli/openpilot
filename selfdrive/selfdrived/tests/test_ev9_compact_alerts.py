from types import SimpleNamespace

import pytest

from opendbc.car.hyundai.values import CAR
from openpilot.selfdrive.selfdrived.events import (
  Alert, AlertSize, AlertStatus, AudibleAlert, ET, EVENTS, EventName, Priority, VisualAlert, ev9_compact_alert,
)
from openpilot.system.hardware import HARDWARE


@pytest.mark.parametrize("duration", [0.1, 1.0])
def test_compact_callback_preserves_device_metadata_without_mutation(duration):
  original = Alert("Pay Attention", "Driver Distracted", AlertStatus.userPrompt, AlertSize.mid,
                   Priority.MID, VisualAlert.steerRequired, AudibleAlert.promptDistracted, duration, creation_delay=0.4)
  callback = ev9_compact_alert(original, "Driver Distracted", AlertStatus.userPrompt)
  compact = callback(SimpleNamespace(carFingerprint=CAR.KIA_EV9))
  assert (compact.alert_text_1, compact.alert_text_2, compact.alert_size) == ("Driver Distracted", "", AlertSize.small)
  for field in ("duration", "creation_delay", "priority", "visual_alert", "audible_alert", "alert_status"):
    assert getattr(compact, field) == getattr(original, field)
  compact.alert_type = "mutated"
  other = callback(SimpleNamespace(carFingerprint=CAR.HYUNDAI_IONIQ_5_PE))
  assert vars(other) == vars(original)
  assert other is not original
  assert original.alert_size == AlertSize.mid


@pytest.mark.parametrize("event,event_type,text,status,duration", [
  (EventName.driverDistracted2, ET.PERMANENT, "Driver Distracted", AlertStatus.userPrompt, None),
  (EventName.steerSaturated, ET.WARNING, "Turn Exceeds Steering Limit", AlertStatus.normal, 200),
])
def test_registered_events_keep_metadata_and_compact_only_ev9(event, event_type, text, status, duration):
  callback = EVENTS[event][event_type]
  compact = callback(SimpleNamespace(carFingerprint=CAR.KIA_EV9))
  other = callback(SimpleNamespace(carFingerprint=CAR.HYUNDAI_IONIQ_5_PE))
  assert (compact.alert_text_1, compact.alert_text_2, compact.alert_size, compact.alert_status) == (text, "", AlertSize.small, status)
  assert other.alert_size == AlertSize.mid
  assert other.alert_status == AlertStatus.userPrompt
  expected_duration = duration if duration is not None else (100 if HARDWARE.get_device_type() == "mici" else 10)
  assert compact.duration == other.duration == expected_duration
  for field in ("priority", "visual_alert", "audible_alert", "creation_delay"):
    assert getattr(compact, field) == getattr(other, field)
