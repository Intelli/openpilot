import sys
import types
from unittest.mock import MagicMock
from types import SimpleNamespace

if "cereal.messaging" not in sys.modules:
  try:
    import cereal.messaging
  except ImportError:
    msg_mod = types.ModuleType("cereal.messaging")
    msg_mod.SubMaster = MagicMock
    msg_mod.PubMaster = MagicMock
    sys.modules["cereal.messaging"] = msg_mod

if "openpilot.starpilot.common.starpilot_variables" not in sys.modules:
  try:
    import openpilot.starpilot.common.starpilot_variables
  except ImportError:
    sv_mod = types.ModuleType("openpilot.starpilot.common.starpilot_variables")
    sv_mod.update_starpilot_toggles = lambda: None
    sv_mod.migrate_cancel_button_controls = lambda: None
    sv_mod.ACTIVE_THEME_PATH = "/tmp"
    sv_mod.THEME_SAVE_PATH = "/tmp"
    sv_mod.MODELS_PATH = "/tmp"
    sv_mod.EARTH_RADIUS = 6371000
    sv_mod.STARPILOT_API = ""
    sv_mod.KONIK_PATH = "/tmp"
    sys.modules["openpilot.starpilot.common.starpilot_variables"] = sv_mod

if "openpilot.common.transformations.orientation" not in sys.modules:
  try:
    import openpilot.common.transformations.orientation
  except ImportError:
    trans_mod = types.ModuleType("openpilot.common.transformations.orientation")
    trans_mod.rot_from_euler = lambda *a, **k: None
    trans_mod.euler_from_rot = lambda *a, **k: None
    sys.modules["openpilot.common.transformations.orientation"] = trans_mod

if "openpilot.starpilot.common.accel_profile" not in sys.modules:
  try:
    import openpilot.starpilot.common.accel_profile
  except ImportError:
    from collections import defaultdict
    accel_mod = types.ModuleType("openpilot.starpilot.common.accel_profile")
    accel_mod.ACCELERATION_PROFILES = defaultdict(lambda: 0)
    accel_mod.DECELERATION_PROFILES = defaultdict(lambda: 0)
    accel_mod.normalize_acceleration_profile = lambda v: v
    accel_mod.normalize_deceleration_profile = lambda v: v
    sys.modules["openpilot.starpilot.common.accel_profile"] = accel_mod

from openpilot.selfdrive.ui.layouts.settings.starpilot.main_panel import StarPilotLayout
from openpilot.selfdrive.ui.layouts.settings.starpilot.navigation import StarPilotNavigationLayout
from openpilot.selfdrive.ui.layouts.settings.starpilot.panel import StarPilotPanelType
from openpilot.selfdrive.ui.layouts.settings.starpilot.aethergrid import BreadcrumbController, gui_app


def test_root_has_nine_direct_routes_in_order():
  assert [item["title"] for item in StarPilotLayout.CATEGORIES] == [
    "Sounds & Alerts", "Driving Model", "Steering", "Gas / Brake", "Map Data",
    "Navigation", "System", "Appearance", "Vehicle Settings",
  ]
  assert all("children" not in item for item in StarPilotLayout.CATEGORIES)
  assert {StarPilotLayout.PANEL_TYPE_MAP[item["panel"]] for item in StarPilotLayout.CATEGORIES} == set(StarPilotLayout.PANEL_TYPE_MAP.values())


class _FakeList:
  def __init__(self, controller, sections):
    self.rows = sections[0].rows

  def show_event(self):
    pass

  def hide_event(self):
    pass


class _PanelSpy:
  def __init__(self, name):
    self.name = name
    self.show_count = 0
    self.hide_count = 0
    self.current_sub_panel = ""

  def show_event(self):
    self.show_count += 1

  def hide_event(self):
    self.hide_count += 1

  def set_current_sub_panel(self, sub_panel):
    self.current_sub_panel = sub_panel


def _make_layout(monkeypatch):
  import openpilot.selfdrive.ui.layouts.settings.starpilot.main_panel as main_panel

  monkeypatch.setattr(main_panel, "AetherSettingsView", _FakeList)

  layout = object.__new__(StarPilotLayout)
  layout._current_panel = StarPilotPanelType.MAIN
  layout._hub_path = []
  layout._selected_leaf = None
  layout._current_category_idx = None
  layout._panel_stack = []
  layout._depth_callback = None
  layout._panels = {}
  for panel_type in StarPilotPanelType:
    layout._panels[panel_type] = SimpleNamespace(
      name=panel_type.name,
      instance=None if panel_type == StarPilotPanelType.MAIN else _PanelSpy(panel_type.name),
    )

  depths = []
  layout.set_depth_callback(depths.append)
  StarPilotLayout.active_instance = layout
  layout._build_root_list()
  return layout, depths


def _click_title(layout, title):
  tile = next(tile for tile in layout._root_list.rows if tile.title == title)
  tile.on_click()


def test_each_root_route_opens_directly_and_back_preserves_lifecycle(monkeypatch):
  layout, depths = _make_layout(monkeypatch)
  assert len(layout._root_list.rows) == 9
  for node in layout.CATEGORIES:
    _click_title(layout, node["title"])
    panel_type = layout.PANEL_TYPE_MAP[node["panel"]]
    assert layout._current_panel == panel_type
    assert depths[-1] == 1
    assert layout.hub_path == ()
    panel = layout._panels[panel_type].instance
    assert (panel.show_count, panel.hide_count) == (1, 0)
    layout.navigate_back()
    assert layout._current_panel == StarPilotPanelType.MAIN
    assert depths[-1] == 0
    assert (panel.show_count, panel.hide_count) == (1, 1)


def test_root_driving_model_opens_directly_and_sub_panel_depth_is_additive(monkeypatch):
  layout, depths = _make_layout(monkeypatch)

  _click_title(layout, "Driving Model")
  assert layout._hub_path == []
  assert layout._current_panel == StarPilotPanelType.DRIVING_MODEL
  assert depths[-1] == 1

  layout._panel_stack.append((StarPilotPanelType.DRIVING_MODEL, "details"))
  layout._commit_navigation()
  assert depths[-1] == 2

  layout.navigate_back()
  assert layout._current_panel == StarPilotPanelType.DRIVING_MODEL
  assert layout._panel_stack == []
  assert depths[-1] == 1

  layout.navigate_back()
  assert layout._current_panel == StarPilotPanelType.MAIN
  assert depths[-1] == 0


def test_breadcrumb_path_has_no_intermediate_folders(monkeypatch):
  layout, _ = _make_layout(monkeypatch)
  monkeypatch.setattr(gui_app, "_nav_stack", [layout], raising=False)
  assert BreadcrumbController.build_path() == [("Vehicle", "action:home")]
  _click_title(layout, "Map Data")
  assert BreadcrumbController.build_path() == [("Vehicle", "action:home"), ("Map Data", "action:panel")]


def test_home_breadcrumb_clears_hub_path_panel_stack_and_active_panel(monkeypatch):
  layout, _ = _make_layout(monkeypatch)
  _click_title(layout, "Map Data")
  layout._panel_stack.append((StarPilotPanelType.MAPS, "details"))

  nav_stack = [layout, object(), object()]
  monkeypatch.setattr(gui_app, "_nav_stack", nav_stack, raising=False)
  monkeypatch.setattr(gui_app, "pop_widget", lambda: nav_stack.pop(), raising=False)
  BreadcrumbController().handle_click("action:home")

  maps_panel = layout._panels[StarPilotPanelType.MAPS].instance
  assert nav_stack == [layout]
  assert layout._hub_path == []
  assert layout._selected_leaf is None
  assert layout._panel_stack == []
  assert layout._current_panel == StarPilotPanelType.MAIN
  assert maps_panel.hide_count == 1
  assert BreadcrumbController.build_path() == [("Vehicle", "action:home")]


def test_navigation_start_is_the_summary_action_not_a_duplicate_rail_target():
  layout = object.__new__(StarPilotNavigationLayout)
  layout._draft_destination = {
    "name": "Home",
    "place_name": "Home",
    "latitude": 1.0,
    "longitude": 2.0,
  }
  layout._selected_favorite = None
  layout._favorites = []

  action_ids = [action[0] for action in layout._action_definitions()]

  assert action_ids == ["action:favorite", "action:home", "action:work"]


def test_rejected_search_invalidates_an_in_flight_request_generation():
  layout = object.__new__(StarPilotNavigationLayout)
  layout._search_generation = 3
  layout._query = "previous"
  layout._search_results = []
  layout._search_error = ""
  layout._draft_destination = None
  layout._selected_favorite = None

  layout._start_search("ab")

  assert layout._search_generation == 4
  assert layout._search_error


def test_breadcrumb_mouse_interaction_lifecycle():
  import pyray as rl
  from openpilot.system.ui.lib.application import MousePos
  controller = BreadcrumbController()
  controller._rects = {
    "action:home": rl.Rectangle(10, 10, 50, 30),
    "action:hub:1": rl.Rectangle(70, 10, 80, 30),
  }
  controller._bounds = rl.Rectangle(0, 0, 200, 50)

  # Press on Home
  controller.init_interaction(MousePos(20, 20))
  assert controller.pressed == "action:home"

  # Move within Home rect -> remains pressed
  controller.update_interaction(MousePos(25, 20))
  assert controller.pressed == "action:home"

  # Drag outside Home rect -> cancels pressed target
  controller.update_interaction(MousePos(500, 500))
  assert controller.pressed is None

  # Re-press and cancel
  controller.init_interaction(MousePos(20, 20))
  assert controller.pressed == "action:home"
  controller.cancel_interaction()
  assert controller.pressed is None


def test_breadcrumb_panel_stack_unwinds_nav_stack(monkeypatch):
  layout, _ = _make_layout(monkeypatch)
  _click_title(layout, "Map Data")
  layout._panel_stack.append((StarPilotPanelType.MAPS, "sub1"))
  layout._panel_stack.append((StarPilotPanelType.MAPS, "sub2"))

  nav_stack = [layout, object(), object()]
  monkeypatch.setattr(gui_app, "_nav_stack", nav_stack, raising=False)
  monkeypatch.setattr(gui_app, "pop_widget", lambda: nav_stack.pop(), raising=False)

  BreadcrumbController().handle_click("action:panel_stack:0")
  assert nav_stack == [layout]
  assert len(layout._panel_stack) == 1
  assert layout._panel_stack[0] == (StarPilotPanelType.MAPS, "sub1")



def test_outer_back_only_unwinds_the_visible_starpilot_panel():
  from openpilot.selfdrive.ui.layouts.settings.settings import SettingsLayout, PanelType, EXPANDED_WIDTH
  layout = object.__new__(SettingsLayout)
  starpilot = MagicMock()
  layout._panels = {PanelType.STARPILOT: SimpleNamespace(instance=starpilot)}
  layout._panel_depth = 2
  layout._close_callback = MagicMock()
  layout._current_panel = PanelType.DEVICE
  assert layout._sidebar_width == EXPANDED_WIDTH
  layout._handle_back_navigation()
  layout._close_callback.assert_called_once()
  starpilot.navigate_back.assert_not_called()
  layout._current_panel = PanelType.STARPILOT
  layout._handle_back_navigation()
  starpilot.navigate_back.assert_called_once()
