"""Exercise actual cosmetic callbacks without constructing a display."""
import ast
from pathlib import Path
from types import SimpleNamespace


def test_path_options_and_pending_color_dialog_preserve_values():
  path = Path(__file__).parents[1] / "layouts/settings/starpilot/appearance.py"
  tree = ast.parse(path.read_text())
  layout = next(n for n in tree.body if isinstance(n, ast.ClassDef) and n.name == "StarPilotAppearanceLayout")
  methods = [n for n in layout.body if isinstance(n, ast.FunctionDef) and n.name in ("_set_path_option", "_show_color_selector")]
  dialogs = []
  values = {"EV9Path": False, "RainbowPath": True, "AccelerationPath": False, "PathColor": "#123456"}
  params = SimpleNamespace(get_bool=lambda k: values.get(k, False), get=lambda k, **kw: values.get(k),
                           put_bool=values.__setitem__, put=values.__setitem__, remove=lambda k: values.pop(k, None))
  def dialog(*args, **kwargs):
    return SimpleNamespace(selection="#abcdef", callback=kwargs["callback"])
  namespace = dict(DialogResult=SimpleNamespace(CONFIRM=1), MultiOptionDialog=dialog, COLOR_PRESETS=[],
                   tr=lambda text: text, gui_app=SimpleNamespace(push_widget=dialogs.append))
  exec(compile(ast.Module(body=methods, type_ignores=[]), str(path), "exec"), namespace)
  owner = SimpleNamespace(_params=params)
  namespace["_show_color_selector"](owner, "PathColor")
  values["EV9Path"] = True
  dialogs[0].callback(1)
  namespace["_set_path_option"](owner, "RainbowPath", False)
  namespace["_set_path_option"](owner, "AccelerationPath", True)
  namespace["_show_color_selector"](owner, "PathColor")
  assert len(dialogs) == 1
  assert values == {"EV9Path": True, "RainbowPath": True, "AccelerationPath": False, "PathColor": "#123456"}
  values["EV9Path"] = False
  dialogs[0].callback(1)
  assert values["PathColor"] == "#abcdef"
