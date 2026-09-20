"""Vehicle and offroad guards for EV9 steering settings."""
from openpilot.selfdrive.controls.lib.ev9_warnings import ev9_alert_speed_kph, ev9_angle_warnings_enabled
from openpilot.starpilot.common.ev9_tuning import read_ev9_tuning


def ev9_settings_visible(cp, started, selected_model):
  if cp is not None and getattr(cp, "carFingerprint", "MOCK") not in ("", "MOCK"):
    return ev9_angle_warnings_enabled(cp)
  if isinstance(selected_model, bytes):
    selected_model = selected_model.decode("utf-8", errors="replace")
  return not started and selected_model == "KIA_EV9"


def ev9_settings_editable(cp, started, selected_model):
  return not started and ev9_settings_visible(cp, started, selected_model)


def ev9_setting_value(params, key):
  if key == "HkgTuningEv9AlertsSpeedKph":
    return int(ev9_alert_speed_kph(params.get(key)))
  attributes = {
    "HkgSharedAutonomyMode": "hkg_shared_autonomy_mode",
    "HkgTuningAngleOverrideEffortPercent": "hkg_tuning_angle_override_effort_percent",
    "HkgTuningAngleCustomLimitMaxSpeedKph": "hkg_tuning_angle_custom_limit_max_speed_kph",
  }
  return read_ev9_tuning(params)[attributes[key]]
