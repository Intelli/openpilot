from __future__ import annotations

from typing import Callable

from openpilot.common.params import Params
from openpilot.system.ui.lib.application import gui_app
from openpilot.system.ui.lib.multilang import tr
from openpilot.system.ui.widgets import Widget, DialogResult
from openpilot.system.ui.widgets.keyboard import Keyboard
from openpilot.system.ui.widgets.list_view import ListItem, ButtonAction
from openpilot.system.ui.widgets.scroller_tici import Scroller


def _clamp(val: int, min_val: int, max_val: int) -> int:
  return max(min_val, min(max_val, val))


class NumericItem:
  def __init__(self, title: str, param: str, description: str, min_val: int, max_val: int, suffix: str = "", default: int | None = None):
    self.title = title
    self.param = param
    self.description = description
    self.min_val = min_val
    self.max_val = max_val
    self.suffix = suffix
    self.default = default


class LateralTuningLayout(Widget):
  ITEMS = [
    NumericItem(
      title=tr("Override Steering Effort"),
      param="HkgTuningAngleMinTorqueReductionGain",
      description=tr("Sets the steering effort percentage used when the driver is overriding lateral control. Higher values increase resistance and make the wheel feel stiffer."),
      min_val=1,
      max_val=60,
      suffix="%",
    ),
    NumericItem(
      title=tr("Max Torque Reduction"),
      param="HkgTuningAngleMaxTorqueReductionGain",
      description=tr("Sets the maximum torque reduction percentage."),
      min_val=1,
      max_val=100,
      suffix="%",
    ),
    NumericItem(
      title=tr("Active Torque Reduction"),
      param="HkgTuningAngleActiveTorqueReductionGain",
      description=tr("Sets the active torque reduction percentage while steering is engaged."),
      min_val=1,
      max_val=100,
      suffix="%",
    ),
    NumericItem(
      title=tr("EV9 Limit Speed"),
      param="HkgTuningAngleCustomLimitMaxSpeedKph",
      description=tr("Modify EV9 steering limits only below this speed (km/h)."),
      min_val=10,
      max_val=40,
      suffix=tr(" km/h"),
      default=32,
    ),
    NumericItem(
      title=tr("EV9 Alert Speed"),
      param="HkgTuningEv9AlertsSpeedKph",
      description=tr("Modify EV9 steering alerts only below this speed (km/h)."),
      min_val=10,
      max_val=50,
      suffix=tr(" km/h"),
      default=40,
    ),
    NumericItem(
      title=tr("Lane Turn Max Speed"),
      param="LaneTurnValue",
      description=tr("Set the maximum speed for lane turn desires (mph)."),
      min_val=5,
      max_val=25,
      suffix=tr(" mph"),
      default=25,
    ),
  ]

  def __init__(self):
    super().__init__()
    self._params = Params()
    self._keyboard = Keyboard(max_text_size=6, min_text_size=1)
    self._items: list[tuple[NumericItem, ButtonAction]] = []

    list_items: list[Widget] = []
    for cfg in self.ITEMS:
      action = ButtonAction(lambda: tr("EDIT"))
      action.set_value(self._make_value_fn(cfg))
      list_items.append(ListItem(lambda c=cfg: c.title, description=lambda c=cfg: c.description, action_item=action,
                                 callback=self._make_edit_fn(cfg, action)))
      self._items.append((cfg, action))

    self._scroller = Scroller(list_items, line_separator=True, spacing=0)

  def _render(self, rect):
    self._scroller.render(rect)

  def show_event(self):
    self._scroller.show_event()

  def _make_value_fn(self, cfg: NumericItem) -> Callable[[], str]:
    def value() -> str:
      raw = self._params.get(cfg.param)
      if raw is None or raw == "":
        if cfg.default is not None:
          return f"{cfg.default}{cfg.suffix}"
        return tr("Not Set")
      try:
        val = int(raw)
      except Exception:
        return raw
      val = _clamp(val, cfg.min_val, cfg.max_val)
      return f"{val}{cfg.suffix}"
    return value

  def _make_edit_fn(self, cfg: NumericItem, action: ButtonAction):
    def edit():
      self._keyboard.clear()
      self._keyboard.set_title(cfg.title, cfg.description)
      current = self._params.get(cfg.param)
      if current:
        self._keyboard.set_text(str(current))
      gui_app.set_modal_overlay(self._keyboard, callback=lambda result: self._on_submit(result, cfg, action))
    return edit

  def _on_submit(self, result: DialogResult, cfg: NumericItem, action: ButtonAction):
    if result != DialogResult.CONFIRM:
      return
    text = self._keyboard.text.strip()
    if not text:
      if cfg.default is not None:
        self._params.put(cfg.param, str(cfg.default))
      else:
        self._params.remove(cfg.param)
      return
    try:
      val = int(float(text))
    except Exception:
      return
    val = _clamp(val, cfg.min_val, cfg.max_val)
    self._params.put(cfg.param, str(val))
    action.set_value(self._make_value_fn(cfg))
