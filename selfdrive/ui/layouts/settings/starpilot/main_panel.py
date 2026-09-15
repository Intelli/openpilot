from __future__ import annotations
from collections.abc import Callable
import pyray as rl

from openpilot.system.ui.widgets import Widget
from openpilot.system.ui.lib.multilang import tr_noop
from openpilot.system.ui.lib.application import MousePos

from openpilot.selfdrive.ui.layouts.settings.starpilot.panel import StarPilotPanelType, StarPilotPanelInfo, FrameCachedParams
from openpilot.selfdrive.ui.layouts.settings.starpilot.sounds import StarPilotSoundsLayout
from openpilot.selfdrive.ui.layouts.settings.starpilot.driving_model import StarPilotDrivingModelLayout
from openpilot.selfdrive.ui.layouts.settings.starpilot.longitudinal import StarPilotLongitudinalLayout
from openpilot.selfdrive.ui.layouts.settings.starpilot.lateral import StarPilotLateralLayout
from openpilot.selfdrive.ui.layouts.settings.starpilot.maps import StarPilotMapsLayout
from openpilot.selfdrive.ui.layouts.settings.starpilot.navigation import StarPilotNavigationLayout
from openpilot.selfdrive.ui.layouts.settings.starpilot.system_settings import StarPilotSystemLayout
from openpilot.selfdrive.ui.layouts.settings.starpilot.appearance import StarPilotAppearanceLayout
from openpilot.selfdrive.ui.layouts.settings.starpilot.vehicle import StarPilotVehicleSettingsLayout

from openpilot.selfdrive.ui.layouts.settings.starpilot.aethergrid import (
  AetherSettingsView, SettingRow, SettingSection, BreadcrumbController,
)

class StarPilotLayout(Widget):
  CATEGORIES = [
    {"title": "Sounds & Alerts", "panel": "SOUNDS"},
    {"title": "Driving Model", "panel": "DRIVING_MODEL"},
    {"title": "Steering", "panel": "LATERAL"},
    {"title": "Gas / Brake", "panel": "LONGITUDINAL"},
    {"title": "Map Data", "panel": "MAPS"},
    {"title": "Navigation", "panel": "NAVIGATION"},
    {"title": "System", "panel": "SYSTEM"},
    {"title": "Appearance", "panel": "VISUALS"},
    {"title": "Vehicle Settings", "panel": "VEHICLE"},
  ]

  PANEL_TYPE_MAP = {
    "SOUNDS": StarPilotPanelType.SOUNDS,
    "SYSTEM": StarPilotPanelType.SYSTEM,
    "DRIVING_MODEL": StarPilotPanelType.DRIVING_MODEL,
    "LONGITUDINAL": StarPilotPanelType.LONGITUDINAL,
    "LATERAL": StarPilotPanelType.LATERAL,
    "MAPS": StarPilotPanelType.MAPS,
    "NAVIGATION": StarPilotPanelType.NAVIGATION,
    "VISUALS": StarPilotPanelType.VISUALS,
    "VEHICLE": StarPilotPanelType.VEHICLE,
  }

  def __init__(self):
    super().__init__()
    self._params = FrameCachedParams()

    self._current_panel = StarPilotPanelType.MAIN
    self._hub_path: list[dict] = []
    self._selected_leaf: dict | None = None
    # Compatibility fields for modal breadcrumb navigation; the root has no folders.
    self._current_category_idx: int | None = None
    self._depth_callback: Callable | None = None
    self._settings_layout = None

    StarPilotLayout.active_instance = self

    self._panel_stack: list[tuple[StarPilotPanelType, str]] = []
    self._sub_panel_callbacks: dict[str, Callable] = {}

    self._panels = {
      StarPilotPanelType.MAIN: StarPilotPanelInfo("", None),
      StarPilotPanelType.SOUNDS: StarPilotPanelInfo(tr_noop("Sounds"), StarPilotSoundsLayout()),
      StarPilotPanelType.SYSTEM: StarPilotPanelInfo(tr_noop("System Settings"), StarPilotSystemLayout()),
      StarPilotPanelType.DRIVING_MODEL: StarPilotPanelInfo(tr_noop("Driving Model"), StarPilotDrivingModelLayout()),
      StarPilotPanelType.LONGITUDINAL: StarPilotPanelInfo(tr_noop("Gas / Brake"), StarPilotLongitudinalLayout()),
      StarPilotPanelType.LATERAL: StarPilotPanelInfo(tr_noop("Steering"), StarPilotLateralLayout()),
      StarPilotPanelType.MAPS: StarPilotPanelInfo(tr_noop("Map Data"), StarPilotMapsLayout()),
      StarPilotPanelType.NAVIGATION: StarPilotPanelInfo(tr_noop("Navigation"), StarPilotNavigationLayout()),
      StarPilotPanelType.VISUALS: StarPilotPanelInfo(tr_noop("Appearance"), StarPilotAppearanceLayout()),
      StarPilotPanelType.VEHICLE: StarPilotPanelInfo(tr_noop("Vehicle Settings"), StarPilotVehicleSettingsLayout()),
    }

    self._setup_sub_panels(
      StarPilotPanelType.LONGITUDINAL,
      StarPilotPanelType.SOUNDS,
      StarPilotPanelType.SYSTEM,
      StarPilotPanelType.LATERAL,
      StarPilotPanelType.MAPS,
      StarPilotPanelType.NAVIGATION,
      StarPilotPanelType.VISUALS,
      StarPilotPanelType.VEHICLE,
    )

    self._breadcrumbs = BreadcrumbController()
    self._build_root_list()

  def set_depth_callback(self, callback: Callable):
    self._depth_callback = callback

  def set_settings_layout(self, settings_layout):
    self._settings_layout = settings_layout

  @property
  def hub_path(self) -> tuple[dict, ...]:
    return tuple(self._hub_path)

  def navigate_back(self):
    if self._panel_stack:
      self._panel_stack.pop()
      self._commit_navigation()
    elif self._current_panel != StarPilotPanelType.MAIN:
      # Every panel returns directly to the root list.
      self._set_current_panel(StarPilotPanelType.MAIN)

  def reset_to_root(self):
    """Close nested content and restore the direct settings list."""
    self._hub_path.clear()
    self._selected_leaf = None
    self._set_current_panel(StarPilotPanelType.MAIN)

  def navigate_to_hub_depth(self, depth: int):
    """Retain compatibility with modal breadcrumbs from the former folder hub."""
    self.reset_to_root()

  def _open_leaf(self, leaf: dict):
    panel_key = leaf.get("panel")
    if panel_key is None:
      return
    self._selected_leaf = leaf
    self._set_current_panel(self.PANEL_TYPE_MAP[panel_key])

  def _update_depth(self):
    # Existing panel sub-pages remain below their direct root entry.
    depth = 0
    if self._current_panel != StarPilotPanelType.MAIN:
      depth += 1
    depth += len(self._panel_stack)

    if self._depth_callback:
      self._depth_callback(depth)

  def _commit_navigation(self):
    self._update_sub_panel_visibility()
    self._update_depth()

  def _push_sub_panel(self, sub_panel_name: str):
    if sub_panel_name:
      self._panel_stack.append((self._current_panel, sub_panel_name))
    else:
      while self._panel_stack and self._panel_stack[-1][0] == self._current_panel:
        self._panel_stack.pop()
    self._commit_navigation()

  def _update_sub_panel_visibility(self):
    panel = self._panels[self._current_panel].instance
    current_sub = self._get_current_sub_panel()
    if panel and hasattr(panel, 'set_current_sub_panel'):
      panel.set_current_sub_panel(current_sub)

  def _get_current_sub_panel(self) -> str:
    if self._panel_stack and self._panel_stack[-1][0] == self._current_panel:
      return self._panel_stack[-1][1]
    return ""

  def _setup_sub_panels(self, *panel_types: StarPilotPanelType):
    for panel_type in panel_types:
      panel = self._panels[panel_type].instance
      if panel and hasattr(panel, 'set_navigate_callback'):
        panel.set_navigate_callback(self._push_sub_panel)

  def _build_root_list(self):
    rows = [SettingRow(
      id=node["panel"], type="value", title=node["title"],
      on_click=lambda item=node: self._open_leaf(item),
    ) for node in self.CATEGORIES]
    self._root_list = AetherSettingsView(self, [SettingSection("", rows)])

  def _set_current_panel(self, panel_type: StarPilotPanelType):
    if panel_type != self._current_panel:
      if self._current_panel == StarPilotPanelType.MAIN:
        self._root_list.hide_event()
      if self._current_panel != StarPilotPanelType.MAIN:
        old = self._panels[self._current_panel].instance
        old.hide_event()
        if hasattr(old, 'set_current_sub_panel'):
          old.set_current_sub_panel("")
      self._current_panel = panel_type
      self._panel_stack.clear()
      if panel_type != StarPilotPanelType.MAIN:
        self._panels[panel_type].instance.show_event()
      else:
        self._selected_leaf = None
        self._root_list.show_event()

    elif panel_type == StarPilotPanelType.MAIN:
      self._selected_leaf = None
      self._panel_stack.clear()

    self._commit_navigation()

  def _render(self, rect: rl.Rectangle):
    TOP_BAR_HEIGHT = 72
    BOTTOM_BAR_HEIGHT = 10
    content_rect = rl.Rectangle(rect.x, rect.y + TOP_BAR_HEIGHT, rect.width, rect.height - TOP_BAR_HEIGHT - BOTTOM_BAR_HEIGHT)

    # Keep a plain location bar; Back remains in the fixed outer sidebar.
    self._breadcrumbs.draw(rl.Rectangle(rect.x, rect.y, rect.width, TOP_BAR_HEIGHT))

    if self._current_panel == StarPilotPanelType.MAIN:
      self._root_list.render(content_rect)
    else:
      panel = self._panels[self._current_panel]
      if panel.instance:
        panel.instance.render(content_rect)

  def _handle_mouse_press(self, mouse_pos: MousePos):
    self._breadcrumbs.init_interaction(mouse_pos)

  def _handle_mouse_release(self, mouse_pos: MousePos):
    action = self._breadcrumbs.finish_interaction(mouse_pos)
    if action:
      self._breadcrumbs.handle_click(action)

  def _handle_mouse_event(self, mouse_event):
    self._breadcrumbs.update_interaction(mouse_event.pos)

  def show_event(self):
    super().show_event()
    self._breadcrumbs.cancel_interaction()
    if self._current_panel != StarPilotPanelType.MAIN:
      self._panels[self._current_panel].instance.show_event()
    else:
      self._root_list.show_event()

  def hide_event(self):
    super().hide_event()
    self._breadcrumbs.cancel_interaction()
    if self._current_panel != StarPilotPanelType.MAIN:
      self._panels[self._current_panel].instance.hide_event()
    else:
      self._root_list.hide_event()
