from types import SimpleNamespace

import pytest

from opendbc.car import structs
from opendbc.car.hyundai.values import HyundaiFlags
from openpilot.selfdrive.ui.layouts.settings.starpilot.ev9_settings import ev9_settings_editable, ev9_settings_visible


def cp(model="KIA_EV9", flags=int(HyundaiFlags.CANFD_ANGLE_STEERING), angle=True):
  return SimpleNamespace(carFingerprint=model, flags=flags,
                         steerControlType=structs.CarParams.SteerControlType.angle if angle else structs.CarParams.SteerControlType.torque)


@pytest.mark.parametrize("car,started,selected,visible,editable", [
  (cp(), False, "MOCK", True, True), (cp(), True, "KIA_EV9", True, False),
  (None, False, b"KIA_EV9", True, True), (cp("MOCK"), False, "KIA_EV9", True, True),
  (None, True, "KIA_EV9", False, False), (cp("OTHER"), False, "KIA_EV9", False, False),
  (cp(flags=0), False, "KIA_EV9", False, False), (cp(angle=False), False, "KIA_EV9", False, False),
  (None, False, "OTHER", False, False),
])
def test_vehicle_and_offroad_scope(car, started, selected, visible, editable):
  assert ev9_settings_visible(car, started, selected) == visible
  assert ev9_settings_editable(car, started, selected) == editable


@pytest.fixture
def lateral_module(monkeypatch):
  # Load the real layout with display/state dependencies replaced by inert widgets.
  import importlib.util
  import sys
  from pathlib import Path

  class Row:
    def __init__(self, *args, **kwargs):
      self.__dict__.update(kwargs)

  stubs = {
    "openpilot.selfdrive.ui.lib.starpilot_state": SimpleNamespace(starpilot_state=SimpleNamespace()),
    "openpilot.system.ui.lib.application": SimpleNamespace(gui_app=SimpleNamespace(push_widget=lambda widget: None)),
    "openpilot.system.ui.lib.multilang": SimpleNamespace(tr=lambda text: text, tr_noop=lambda text: text),
    "openpilot.system.ui.widgets": SimpleNamespace(DialogResult=SimpleNamespace(CONFIRM=1)),
    "openpilot.selfdrive.ui.layouts.settings.starpilot.panel": SimpleNamespace(_SettingsPage=type("Page", (), {"SLIDER_COLOR": None})),
    "openpilot.selfdrive.ui.layouts.settings.starpilot.aethergrid": SimpleNamespace(
      DEFAULT_PANEL_STYLE=None, AetherSettingsView=Row, ParentToggle=Row, SettingRow=Row, SettingSection=Row, AetherSliderDialog=Row),
  }
  for name, module in stubs.items():
    monkeypatch.setitem(sys.modules, name, module)
  path = Path(__file__).parents[1] / "layouts/settings/starpilot/lateral.py"
  spec = importlib.util.spec_from_file_location("ev9_test_lateral", path)
  module = importlib.util.module_from_spec(spec)
  spec.loader.exec_module(module)
  return module


def test_slider_rechecks_eligibility_before_write(monkeypatch, lateral_module):
  lateral = lateral_module

  layout = lateral.StarPilotLateralLayout.__new__(lateral.StarPilotLateralLayout)
  writes = []
  layout._params = SimpleNamespace(get=lambda key: None, put_int=lambda key, value: writes.append((key, value)))
  allowed = [True]
  monkeypatch.setattr(layout, "_ev9_editable", lambda: allowed[0])
  dialogs = []
  monkeypatch.setattr(lateral, "AetherSliderDialog", lambda *args, **kwargs: (args, kwargs))
  monkeypatch.setattr(lateral.gui_app, "push_widget", dialogs.append)
  key = "HkgTuningAngleCustomLimitMaxSpeedKph"
  layout._ev9_slider(key, "EV9 Limits Speed", 40, 1, " km/h")
  args, _ = dialogs[0]
  assert args[1:5] == (10, 40, 1, 40)
  allowed[0] = False
  args[5](lateral.DialogResult.CONFIRM, 20)
  layout._ev9_set_manual(True)
  layout._ev9_slider(key, "EV9 Limits Speed", 40, 1, " km/h")
  assert writes == [] and len(dialogs) == 1
  allowed[0] = True
  args[5](lateral.DialogResult.CONFIRM, 20)
  assert writes == [(key, 20)]


def test_rows_defaults_and_legacy_manual_mode(monkeypatch, lateral_module):
  lateral = lateral_module

  layout = lateral.StarPilotLateralLayout.__new__(lateral.StarPilotLateralLayout)
  values = {}
  layout._params = SimpleNamespace(get=lambda key: values.get(key))
  monkeypatch.setattr(layout, "_ev9_editable", lambda: True)
  rows = layout._ev9_rows()
  assert len(rows) == 4
  assert not rows[0].get_state()
  assert [row.get_value() for row in rows[1:]] == ["10%", "40 km/h", "50 km/h"]
  values["HkgSharedAutonomyMode"] = "2"
  assert rows[0].get_state()


def test_mici_controls_preserve_values_and_recheck_vehicle_state(monkeypatch, lateral_module):
  import importlib.util
  import sys
  from pathlib import Path

  dialogs = []
  state = SimpleNamespace(CP=cp(), started=False)

  def make_dialog(**kwargs):
    dialog = SimpleNamespace(**kwargs)
    dialog.get_selected_option = lambda: "20%"
    dialogs.append(dialog)
    return dialog

  for name, module in {
    "openpilot.selfdrive.ui.mici.widgets.button": SimpleNamespace(BigButton=object, BigToggle=object),
    "openpilot.selfdrive.ui.mici.widgets.dialog": SimpleNamespace(BigMultiOptionDialog=make_dialog),
    "openpilot.system.ui.widgets.scroller": SimpleNamespace(NavScroller=object),
    "openpilot.selfdrive.ui.ui_state": SimpleNamespace(ui_state=state),
  }.items():
    monkeypatch.setitem(sys.modules, name, module)
  path = Path(__file__).parents[1] / "mici/layouts/settings/ev9.py"
  spec = importlib.util.spec_from_file_location("ev9_test_mici", path)
  module = importlib.util.module_from_spec(spec)
  spec.loader.exec_module(module)
  layout = module.EV9SteeringLayoutMici.__new__(module.EV9SteeringLayoutMici)
  updates = []
  monkeypatch.setattr(module, "update_starpilot_toggles", lambda: updates.append(True))
  key = "HkgTuningAngleOverrideEffortPercent"
  values = {"CarModel": "KIA_EV9", "HkgSharedAutonomyMode": "2", key: "15"}
  layout._params = SimpleNamespace(get=values.get, put_int=values.__setitem__)
  checked = []
  layout._manual = SimpleNamespace(set_checked=checked.append, set_value=lambda value: None)
  layout._controls = []
  layout._refresh()
  assert checked[-1] is True
  layout._select_value(key, 100, 10, "%")
  assert dialogs[0].default == "15%" and "15%" in dialogs[0].options
  state.started = True
  dialogs[0].right_btn_callback()
  layout._set_manual(False)
  layout._select_value(key, 100, 10, "%")
  assert values[key] == "15" and values["HkgSharedAutonomyMode"] == "2" and len(dialogs) == 1
  assert updates == []
  state.started = False
  state.CP = cp("OTHER")
  dialogs[0].right_btn_callback()
  assert values[key] == "15"
  state.CP = cp()
  dialogs[0].right_btn_callback()
  layout._set_manual(False)
  assert values[key] == 20 and values["HkgSharedAutonomyMode"] == 0
  assert len(updates) == 2
