"""
Copyright (c) 2021-, Haibin Wen, sunnypilot, and a number of other contributors.

This file is part of sunnypilot and is licensed under the MIT License.
See the LICENSE.md file in the root directory for more details.
"""
from openpilot.common.params import Params
from openpilot.system.ui.lib.application import gui_app
from openpilot.system.ui.lib.multilang import tr
from openpilot.system.ui.sunnypilot.widgets.input_dialog import InputDialogSP
from openpilot.system.ui.sunnypilot.widgets.list_view import button_item_sp
from openpilot.system.ui.widgets import DialogResult, Widget
from openpilot.system.ui.widgets.option_dialog import MultiOptionDialog
from openpilot.system.ui.widgets.scroller_tici import LineSeparator, Scroller

AUTO_LOCK_REGIONS = ["US", "CA", "EU", "CN", "AU"]

AUTO_LOCK_USERNAME_PARAM = "AutoLockUsername"
AUTO_LOCK_PASSWORD_PARAM = "AutoLockPassword"
AUTO_LOCK_PIN_PARAM = "AutoLockPin"
AUTO_LOCK_REGION_PARAM = "AutoLockRegion"


class AutoLockLayout(Widget):
  def __init__(self):
    super().__init__()
    self._params = Params()
    self._region_dialog: MultiOptionDialog | None = None
    self._initialize_items()
    self._scroller = Scroller(self._items, line_separator=True, spacing=0)

  def _initialize_items(self):
    description = tr("Tap to update. Stored locally in device Params.")

    self._username_btn = button_item_sp(
      title=tr("Username"),
      button_text=tr("EDIT"),
      description=description,
      callback=lambda: self._edit_credential(tr("Enter Username"), AUTO_LOCK_USERNAME_PARAM, False),
    )
    self._password_btn = button_item_sp(
      title=tr("Password"),
      button_text=tr("EDIT"),
      description=description,
      callback=lambda: self._edit_credential(tr("Enter Password"), AUTO_LOCK_PASSWORD_PARAM, True),
    )
    self._pin_btn = button_item_sp(
      title=tr("PIN"),
      button_text=tr("EDIT"),
      description=description,
      callback=lambda: self._edit_credential(tr("Enter PIN"), AUTO_LOCK_PIN_PARAM, True),
    )
    self._region_btn = button_item_sp(
      title=tr("Region"),
      button_text=tr("SELECT"),
      description=tr("Select the Kia/Hyundai account region for remote commands."),
      callback=self._edit_region,
    )

    self._items = [
      self._username_btn,
      LineSeparator(),
      self._password_btn,
      LineSeparator(),
      self._pin_btn,
      LineSeparator(),
      self._region_btn,
    ]

  def _edit_credential(self, title: str, param_key: str, password_mode: bool):
    current_value = self._params.get(param_key) or ""
    dialog = InputDialogSP(
      title=title,
      sub_title=tr("Leave blank to clear"),
      current_text=current_value,
      callback=lambda result, text: self._save_credential(result, param_key, text),
      password_mode=password_mode,
    )
    dialog.show()

  def _save_credential(self, result: DialogResult, param_key: str, value: str):
    if result != DialogResult.CONFIRM:
      return

    cleaned = value.strip()
    if cleaned:
      self._params.put(param_key, cleaned)
    else:
      self._params.remove(param_key)

  def _edit_region(self):
    current_region = (self._params.get(AUTO_LOCK_REGION_PARAM) or "").strip().upper()
    if current_region not in AUTO_LOCK_REGIONS:
      current_region = ""

    self._region_dialog = MultiOptionDialog(
      tr("Select Region"),
      AUTO_LOCK_REGIONS,
      current=current_region,
      callback=self._save_region,
    )
    gui_app.push_widget(self._region_dialog)

  def _save_region(self, result: DialogResult):
    if result == DialogResult.CONFIRM and self._region_dialog is not None:
      selection = self._region_dialog.selection.strip().upper()
      if selection in AUTO_LOCK_REGIONS:
        self._params.put(AUTO_LOCK_REGION_PARAM, selection)
    self._region_dialog = None

  @staticmethod
  def _masked_or_not_set(value: str) -> str:
    return tr("Not Set") if not value else "*" * len(value)

  @staticmethod
  def _plain_or_not_set(value: str) -> str:
    return tr("Not Set") if not value else value

  def _update_state(self):
    super()._update_state()

    username = self._params.get(AUTO_LOCK_USERNAME_PARAM) or ""
    password = self._params.get(AUTO_LOCK_PASSWORD_PARAM) or ""
    pin = self._params.get(AUTO_LOCK_PIN_PARAM) or ""
    region = (self._params.get(AUTO_LOCK_REGION_PARAM) or "").strip().upper()
    if region not in AUTO_LOCK_REGIONS:
      region = ""

    self._username_btn.action_item.set_value(self._plain_or_not_set(username))
    self._password_btn.action_item.set_value(self._masked_or_not_set(password))
    self._pin_btn.action_item.set_value(self._masked_or_not_set(pin))
    self._region_btn.action_item.set_value(self._plain_or_not_set(region))

  def _render(self, rect):
    self._scroller.render(rect)

  def show_event(self):
    super().show_event()
    self._scroller.show_event()
