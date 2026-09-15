"""Run both actual renderer branches with real EV9 animation and inert drawing."""
import ast
from pathlib import Path
from types import SimpleNamespace

import numpy as np
import pyray as rl
import pytest

from openpilot.selfdrive.ui.onroad.starpilot.ev9_path import EV9Path, ev9_path_state
from openpilot.system.ui.lib.shader_polygon import Gradient


class Messages(dict):
  pass


@pytest.mark.parametrize("device", ["onroad", "mici/onroad"])
@pytest.mark.parametrize("native_mode", ["rainbow", "acceleration", "color"])
def test_ev9_branch_precedence_restoration_and_frame_lifecycle(device, native_mode):
  path = Path(__file__).parents[1] / device / "model_renderer.py"
  tree = ast.parse(path.read_text())
  cls = next(n for n in tree.body if isinstance(n, ast.ClassDef) and n.name == "ModelRenderer")
  method = next(n for n in cls.body if isinstance(n, ast.FunctionDef) and n.name == "_draw_path")
  draws = []
  clock = [10.0]
  state = SimpleNamespace(started_frame=1, status=1, always_on_lateral_active=False)
  custom_color = rl.Color(12, 34, 56, 255)
  namespace = dict(time=SimpleNamespace(monotonic=lambda: clock[0]), ui_state=state,
                   UIStatus=SimpleNamespace(ENGAGED=1, DISENGAGED=0), ev9_path_state=ev9_path_state,
                   draw_polygon=lambda *args, **kwargs: draws.append((args, kwargs)), rl=rl, Gradient=Gradient,
                   NO_THROTTLE_COLORS=[custom_color]*3, THROTTLE_COLORS=[custom_color]*3,
                   get_visual_color=lambda *args: custom_color,
                   with_alpha=lambda c, a: rl.Color(c.r, c.g, c.b, a))
  exec(compile(ast.Module(body=[method], type_ignores=[]), str(path), "exec"), namespace)
  values = {"EV9Path": True, "RainbowPath": native_mode == "rainbow", "AccelerationPath": native_mode == "acceleration"}
  preferences = values.copy()
  original_gradient = Gradient(start=(0, 1), end=(0, 0), colors=[custom_color]*3, stops=[0, .5, 1])
  animation = EV9Path()
  update = animation.update
  calls = []
  def counted_update(**kwargs):
    calls.append(kwargs)
    update(**kwargs)
  animation.update = counted_update
  renderer = SimpleNamespace(_params=SimpleNamespace(get_bool=lambda key, default=False: values.get(key, default)),
    _path=SimpleNamespace(projected_points=np.ones((4, 2))), _rect=None, _ev9_path=animation, _ev9_started_frame=1,
    _longitudinal_control=True, _blend_filter=SimpleNamespace(update=lambda value: None, x=1),
    _use_rainbow=values["RainbowPath"], _use_accel_path=values["AccelerationPath"], _experimental_mode=False,
    _exp_gradient=original_gradient, _path_gradient=original_gradient, _blend_colors=lambda *args: [custom_color]*3)
  sm = Messages(carState=SimpleNamespace(aEgo=.5), carControl=SimpleNamespace(latActive=True),
                selfdriveState=SimpleNamespace(alertType=""), starpilotSelfdriveState=SimpleNamespace(alertType=""),
                longitudinalPlan=SimpleNamespace(allowThrottle=True))
  sm.valid = sm.alive = dict.fromkeys(sm, True)
  sm.recv_frame = dict.fromkeys(sm, 1)
  sm.recv_time = dict.fromkeys(sm, 10)
  def draw():
    namespace["_draw_path"](renderer, sm)
  draw()
  clock[0] += .1
  draw()
  assert len(calls) == 2  # No modelUpdated event is needed for animation.
  assert animation._accel_presence > 0
  assert draws[-1][1]["gradient"] is not original_gradient
  assert values == preferences
  state.started_frame = 2
  draw()
  assert animation._accel_presence == 0 and not animation._active
  renderer._path.projected_points = np.empty((0, 2))
  count = len(draws)
  draw()
  assert len(draws) == count and animation._last_update_time is None
  renderer._path.projected_points = np.ones((4, 2))
  values["EV9Path"] = False
  draw()
  gradient = draws[-1][1]["gradient"]
  if native_mode == "rainbow":
    assert gradient is original_gradient
  else:
    assert [(c.r, c.g, c.b) for c in gradient.colors] == [(12, 34, 56)]*3
  assert {key: values[key] for key in ("RainbowPath", "AccelerationPath")} == {
    key: preferences[key] for key in ("RainbowPath", "AccelerationPath")}
