"""Exercise settings callbacks and geometry without device-specific native imports."""
import ast
from pathlib import Path
from types import SimpleNamespace

import pytest


SOURCE = Path(__file__).parents[1] / "starpilot/aethergrid.py"


@pytest.fixture
def view_type():
  tree = ast.parse(SOURCE.read_text())
  original = next(n for n in tree.body if isinstance(n, ast.ClassDef) and n.name == "AetherSettingsView")
  names = {"_find_row", "_activate_target", "_active_sections", "_visible_rows", "_measure_content_height", "_uses_two_columns", "_row_height"}
  methods = [n for n in original.body if isinstance(n, ast.FunctionDef) and n.name in names]
  # Keep the product methods intact; replace only imports/base construction.
  cls = ast.ClassDef(name="IsolatedView", bases=[], keywords=[], body=methods, decorator_list=[])
  helpers = [n for n in tree.body if isinstance(n, ast.FunctionDef) and n.name in {"settings_text_lines", "_settings_text_width", "settings_row_height"}]
  module = ast.Module(body=[ast.ImportFrom(module="__future__", names=[ast.alias(name="annotations")], level=0), *helpers, cls], type_ignores=[])
  scope = {"SECTION_HEADER_HEIGHT": 44, "SECTION_HEADER_GAP": 10, "SECTION_GAP": 24}
  scope.update(
    AETHER_LIST_METRICS=SimpleNamespace(toggle_width=120, row_height=170),
    FontWeight=SimpleNamespace(NORMAL=0, MEDIUM=1, SEMI_BOLD=2),
    gui_app=SimpleNamespace(font=lambda weight: None),
    measure_text_cached=lambda font, text, size: SimpleNamespace(x=len(text) * size * 0.5),
    tr=lambda text: text,
  )
  exec(compile(ast.fix_missing_locations(module), str(SOURCE), "exec"), scope)
  return scope["IsolatedView"]


def row(name, **kwargs):
  fields = dict(id=name, title=name, subtitle="", disabled_label="", get_value=None, type="toggle",
                visible=None, enabled=None, navigate_to="", on_click=None, set_state=None, get_state=None)
  fields.update(kwargs)
  return SimpleNamespace(**fields)


def section(rows, **kwargs):
  fields = dict(rows=rows, title="", visible=None, row_height=170, column_pair="", tab_key="")
  fields.update(kwargs)
  return SimpleNamespace(**fields)


def view(view_type, sections):
  instance = view_type()
  instance._sections = sections
  instance._tab_defs = None
  instance._parent_toggle = None
  instance.TWO_COLUMN_BREAKPOINT = 1200
  return instance


def test_toggle_callback_and_disabled_row(view_type):
  state = {"value": False, "enabled": True}
  setting = row("setting", get_state=lambda: state["value"], set_state=lambda value: state.update(value=value), enabled=lambda: state["enabled"])
  instance = view(view_type, [section([setting])])
  instance._activate_target("toggle:setting")
  assert state["value"]
  state["enabled"] = False
  instance._activate_target("toggle:setting")
  assert state["value"]


def test_navigation_uses_existing_controller_callback(view_type):
  destinations = []
  instance = view(view_type, [section([row("advanced", type="value", navigate_to="advanced")])])
  instance._controller = SimpleNamespace(_navigate_to=destinations.append)
  instance._activate_target("value:advanced")
  assert destinations == ["advanced"]


def test_scrolling_measures_all_rows_and_excludes_hidden_sections(view_type):
  instance = view(view_type, [section([row(str(i)) for i in range(12)]), section([row("hidden")], visible=lambda: False)])
  assert instance._measure_content_height(1500) == 12 * 170
  assert instance._measure_content_height(1500) > 1080


def test_paired_sections_remain_full_width_on_c3(view_type):
  instance = view(view_type, [section([row("left")], column_pair="pair"), section([row("right")], column_pair="pair")])
  assert not instance._uses_two_columns(2160)
  assert instance._measure_content_height(2160) == 2 * 170 + 24


def test_long_descriptions_expand_scroll_height_without_changing_font_size(view_type):
  long_row = row("setting", subtitle="A detailed explanation with several important settings and conditions. " * 10)
  instance = view(view_type, [section([long_row])])
  short_height = instance._measure_content_height(1600)
  assert short_height > 170
  assert instance._measure_content_height(900) > short_height
  long_row.enabled = lambda: False
  long_row.disabled_label = "Unavailable"
  assert instance._measure_content_height(1600) == 170


def isolated_methods(class_name, names, scope):
  tree = ast.parse(SOURCE.read_text())
  cls = next(n for n in tree.body if isinstance(n, ast.ClassDef) and n.name == class_name)
  cls.bases = []
  cls.body = [n for n in cls.body if isinstance(n, ast.FunctionDef) and n.name in names]
  module = ast.Module(body=[ast.ImportFrom(module="__future__", names=[ast.alias(name="annotations")], level=0), cls], type_ignores=[])
  exec(compile(ast.fix_missing_locations(module), str(SOURCE), "exec"), scope)
  return scope[class_name]


def test_toggle_list_measurement_matches_rendered_variable_heights():
  rendered = []

  class Toggle:
    def __init__(self, height):
      self.height = height

    def measure_height(self, width):
      return self.height + (1600 - width) * 0.1

    def set_parent_rect(self, rect):
      self.parent = rect

    def render(self, rect):
      rendered.append(rect)

  def rect(x, y, width, height):
    return SimpleNamespace(x=x, y=y, width=width, height=height)

  grid_type = isolated_methods("TileGrid", {"_is_toggle_list", "measure_height", "_render"},
                               {"ToggleTile": Toggle, "snap_rect": lambda value: value, "rl": SimpleNamespace(Rectangle=rect)})
  grid = grid_type()
  grid.tiles = [Toggle(170), Toggle(250), Toggle(330)]
  grid._gap = 16
  grid._parent_rect = rect(0, 0, 1600, 1080)
  grid.set_rect = lambda value: None
  for width in (1600, 1200):
    rendered.clear()
    total = grid.measure_height(width)
    grid._render(rect(20, 50, width, total))
    assert len(rendered) == 3
    assert all(item.x == 20 and item.width == width for item in rendered)
    assert rendered[-1].y + rendered[-1].height == 50 + total
    assert all(b.y == a.y + a.height + 16 for a, b in zip(rendered, rendered[1:], strict=False))
    assert all(tile.parent is grid._parent_rect for tile in grid.tiles)


def test_flattened_toggle_pages_keep_every_control_in_order():
  rendered = []
  tree = ast.parse(SOURCE.read_text())
  owner = next(n.name for n in tree.body if isinstance(n, ast.ClassDef) and
               any(isinstance(m, ast.FunctionDef) and m.name == "_set_toggle_pages" for m in n.body))
  manager_type = isolated_methods(owner, {"_set_toggle_pages", "_on_page_changed"}, {})
  manager = manager_type()
  manager._page_grid = SimpleNamespace(clear=rendered.clear, add_tile=rendered.append, _tile_height=100)
  manager._make_toggle_tile = lambda definition: definition
  controls = [object() for _ in range(11)]
  manager._set_toggle_pages([controls[:4], controls[4:8], controls[8:]])
  assert rendered == controls
  assert manager._page_count == 1 and manager._current_page == 0
  assert manager._page_grid._tile_height is None
