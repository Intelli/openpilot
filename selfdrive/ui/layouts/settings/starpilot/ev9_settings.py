"""Vehicle and offroad guards for EV9 steering settings."""
from openpilot.selfdrive.controls.lib.ev9_warnings import ev9_angle_warnings_enabled


def ev9_settings_visible(cp, started, selected_model):
  if cp is not None and getattr(cp, "carFingerprint", "MOCK") not in ("", "MOCK"):
    return ev9_angle_warnings_enabled(cp)
  if isinstance(selected_model, bytes):
    selected_model = selected_model.decode("utf-8", errors="replace")
  return not started and selected_model == "KIA_EV9"


def ev9_settings_editable(cp, started, selected_model):
  return not started and ev9_settings_visible(cp, started, selected_model)
