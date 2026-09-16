from openpilot.selfdrive.ui.layouts.settings.starpilot.ev9_settings import ev9_setting_value, ev9_settings_editable, ev9_settings_visible
from openpilot.selfdrive.ui.lib.ui_param_cache import shared_ui_params
from openpilot.selfdrive.ui.mici.widgets.button import BigButton, BigToggle
from openpilot.selfdrive.ui.mici.widgets.dialog import BigMultiOptionDialog
from openpilot.selfdrive.ui.ui_state import ui_state
from openpilot.starpilot.common.starpilot_variables import update_starpilot_toggles
from openpilot.system.ui.lib.application import gui_app
from openpilot.system.ui.widgets.scroller import NavScroller


class EV9SteeringLayoutMici(NavScroller):
  def __init__(self):
    super().__init__()
    self._params = shared_ui_params()
    self._manual = BigToggle("improved manual control", toggle_callback=self._set_manual)
    self._manual.set_enabled(self._editable)
    self._controls = []
    for key, title, maximum, step, unit in (
      ("HkgTuningAngleOverrideEffortPercent", "steering override effort", 100, 10, "%"),
      ("HkgTuningAngleCustomLimitMaxSpeedKph", "EV9 limits speed", 40, 1, " km/h"),
      ("HkgTuningEv9AlertsSpeedKph", "EV9 alert speed", 50, 1, " km/h"),
    ):
      button = BigButton(title)
      button.set_enabled(self._editable)
      button.set_click_callback(lambda k=key, m=maximum, s=step, u=unit: self._select_value(k, m, s, u))
      self._controls.append((key, unit, button))
    self._scroller.add_widgets([self._manual, *(button for _, _, button in self._controls)])

  def visible(self):
    return ev9_settings_visible(ui_state.CP, ui_state.started, self._params.get("CarModel"))

  def _editable(self):
    return ev9_settings_editable(ui_state.CP, ui_state.started, self._params.get("CarModel"))

  def _set_manual(self, enabled):
    if self._editable():
      self._params.put_int("HkgSharedAutonomyMode", int(enabled))
      update_starpilot_toggles()
    self._refresh()

  def _select_value(self, key, maximum, step, unit):
    if not self._editable():
      return
    current = ev9_setting_value(self._params, key)
    # Preserve an existing in-range value even if it falls between UI steps.
    values = sorted(set(range(10, maximum + 1, step)) | {current})
    options = {f"{value}{unit}": value for value in values}

    def on_confirm():
      if self._editable():
        self._params.put_int(key, options[dialog.get_selected_option()])
        update_starpilot_toggles()
      self._refresh()

    dialog = BigMultiOptionDialog(options=list(options), default=f"{current}{unit}", right_btn_callback=on_confirm)
    gui_app.push_widget(dialog)

  def _refresh(self):
    self._manual.set_checked(ev9_setting_value(self._params, "HkgSharedAutonomyMode") != 0)
    self._manual.set_value("hands-on handoff" if self._editable() else "turn vehicle off to adjust")
    for key, unit, button in self._controls:
      button.set_value(f"{ev9_setting_value(self._params, key)}{unit}")

  def show_event(self):
    super().show_event()
    self._refresh()

  def _update_state(self):
    super()._update_state()
    self._refresh()
