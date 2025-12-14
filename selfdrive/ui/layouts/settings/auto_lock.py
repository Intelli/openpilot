from openpilot.common.params import Params
from openpilot.system.ui.lib.application import gui_app
from openpilot.system.ui.lib.multilang import tr
from openpilot.system.ui.widgets import Widget, DialogResult
from openpilot.system.ui.widgets.keyboard import Keyboard
from openpilot.system.ui.widgets.list_view import ListItem, ButtonAction
from openpilot.system.ui.widgets.option_dialog import MultiOptionDialog
from openpilot.system.ui.widgets.scroller_tici import Scroller


REGIONS = ["US", "CA", "EU", "CN", "AU"]


def _masked_value(value: str) -> str:
  return "•" * len(value) if value else tr("Not Set")


def _plain_value(value: str) -> str:
  return value or tr("Not Set")


class AutoLockLayout(Widget):
  def __init__(self):
    super().__init__()
    self._params = Params()
    self._keyboard_plain = Keyboard(max_text_size=120, show_password_toggle=False)
    self._keyboard_secret = Keyboard(max_text_size=120, show_password_toggle=True, password_mode=True)
    self._region_dialog: MultiOptionDialog | None = None

    # Build items
    self._username_action = self._build_action("AutoLockUsername", secret=False)
    self._password_action = self._build_action("AutoLockPassword", secret=True)
    self._pin_action = self._build_action("AutoLockPin", secret=True)
    self._region_action = ButtonAction(lambda: tr("SELECT"))
    self._region_action.set_value(self._region_value)

    items = [
      ListItem(lambda: tr("Username"), description=lambda: tr("Tap to update. Stored locally in device Params."),
               action_item=self._username_action, callback=lambda: self._edit_credential("AutoLockUsername", False)),
      ListItem(lambda: tr("Password"), description=lambda: tr("Tap to update. Stored locally in device Params."),
               action_item=self._password_action, callback=lambda: self._edit_credential("AutoLockPassword", True)),
      ListItem(lambda: tr("PIN"), description=lambda: tr("Tap to update. Stored locally in device Params."),
               action_item=self._pin_action, callback=lambda: self._edit_credential("AutoLockPin", True)),
      ListItem(lambda: tr("Region"), description=lambda: tr("Select the Kia/Hyundai account region for remote commands."),
               action_item=self._region_action, callback=self._edit_region),
    ]

    self._scroller = Scroller(items, line_separator=True, spacing=0)

  def _render(self, rect):
    self._scroller.render(rect)

  def show_event(self):
    self._scroller.show_event()

  def _build_action(self, param: str, secret: bool) -> ButtonAction:
    action = ButtonAction(lambda: tr("EDIT"))
    action.set_value(lambda p=param, s=secret: self._display_value(p, s))
    return action

  def _display_value(self, param: str, secret: bool) -> str:
    value = self._params.get(param) or ""
    return _masked_value(value) if secret else _plain_value(value)

  def _edit_credential(self, param: str, secret: bool):
    keyboard = self._keyboard_secret if secret else self._keyboard_plain
    keyboard.clear()
    keyboard.set_title(self._title_for_param(param), tr("Leave blank to clear"))
    keyboard.set_text(self._params.get(param) or "")
    gui_app.set_modal_overlay(keyboard, callback=lambda result, p=param, k=keyboard: self._on_credential_submit(result, p, k))

  def _on_credential_submit(self, result: DialogResult, param: str, keyboard: Keyboard):
    if result != DialogResult.CONFIRM:
      return
    text = keyboard.text.strip()
    if text:
      self._params.put(param, text)
    else:
      self._params.remove(param)

  def _title_for_param(self, param: str) -> str:
    titles = {
      "AutoLockUsername": tr("Enter username"),
      "AutoLockPassword": tr("Enter password"),
      "AutoLockPin": tr("Enter PIN"),
    }
    return titles.get(param, tr("Enter value"))

  def _region_value(self) -> str:
    region = (self._params.get("AutoLockRegion") or "").strip().upper()
    return region or tr("Not Set")

  def _edit_region(self):
    current = self._region_value()
    dialog = MultiOptionDialog(tr("Select Region"), REGIONS, current=current)
    self._region_dialog = dialog
    gui_app.set_modal_overlay(dialog, callback=self._on_region_submit)

  def _on_region_submit(self, result: DialogResult):
    if result != DialogResult.CONFIRM or self._region_dialog is None:
      return
    selection = self._region_dialog.selection
    if selection:
      self._params.put("AutoLockRegion", selection)
    self._region_dialog = None
