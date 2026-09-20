import importlib
from types import SimpleNamespace

import numpy as np
import pytest

from cereal import custom, log
from openpilot.common.params import Params
from openpilot.selfdrive.ui.lib.ui_param_cache import UIParamCache
from openpilot.selfdrive.ui.onroad.starpilot.path_warning import PathWarningHighlight, path_warning_active
from openpilot.system.ui.lib.shader_polygon import Gradient
import pyray as rl


class Messages(dict):
  def __init__(self):
    super().__init__(selfdriveState=log.SelfdriveState.new_message(alertType="fcw/permanent", alertSize="full"),
                     starpilotSelfdriveState=custom.StarPilotSelfdriveState.new_message(),
                     longitudinalPlan=SimpleNamespace(allowThrottle=True),
                     carState=SimpleNamespace(aEgo=0.8), carControl=SimpleNamespace(latActive=True))
    self.valid = dict.fromkeys(self, True)
    self.alive = dict.fromkeys(self, True)
    self.recv_frame = dict.fromkeys(self, 100)
    self.recv_time = dict.fromkeys(self, 10.0)


def test_selected_alerts_only_including_starpilot_and_normal_status():
  sm = Messages()
  assert path_warning_active(sm, 100, 10.5)
  sm["selfdriveState"].alertType = "driverDistracted1/permanent"
  sm["selfdriveState"].alertStatus = "normal"
  assert path_warning_active(sm, 100, 10.5)
  sm["selfdriveState"].alertType = "laneChange/warning"
  assert not path_warning_active(sm, 100, 10.5)
  sm["starpilotSelfdriveState"].alertType = "goatSteerSaturated/warning"
  sm["starpilotSelfdriveState"].alertSize = "mid"
  assert path_warning_active(sm, 100, 10.5)


@pytest.mark.parametrize("condition", ["invalid", "dead", "previous_drive", "stale", "future", "hidden"])
def test_unusable_alert_does_not_highlight(condition):
  sm = Messages()
  if condition == "invalid":
    sm.valid["selfdriveState"] = False
  elif condition == "dead":
    sm.alive["selfdriveState"] = False
  elif condition == "previous_drive":
    sm.recv_frame["selfdriveState"] = 99
  elif condition in ("stale", "future"):
    sm.recv_time["selfdriveState"] = 9.0 if condition == "stale" else 11.0
  else:
    sm["selfdriveState"].alertSize = "none"
  assert not path_warning_active(sm, 100, 10.5)


def test_warning_holds_then_fades_and_resets_on_disable_session_or_time_gap():
  sm, highlight = Messages(), PathWarningHighlight()
  red = highlight.update(sm, 100, True, 10.0)
  sm["selfdriveState"].alertType = ""
  # Slow rendering must not stretch the half-second hold or one-second fade.
  assert highlight.update(sm, 100, True, 10.25).colors[0].a == red.colors[0].a
  assert highlight.update(sm, 100, True, 10.5).colors[0].a == red.colors[0].a
  fading = highlight.update(sm, 100, True, 11.0)
  assert fading.colors[0].a == round(red.colors[0].a / 2)
  assert highlight.update(sm, 100, True, 11.5) is None

  for enabled, started_frame, now in ((False, 100, 10.1), (True, 101, 10.1), (True, 100, 12.0), (True, 100, 9.0)):
    highlight.reset()
    sm["selfdriveState"].alertType = "fcw/permanent"
    assert highlight.update(sm, 100, True, 10.0) is not None
    sm["selfdriveState"].alertType = ""
    assert highlight.update(sm, started_frame, enabled, now) is None


@pytest.mark.parametrize("module", ["openpilot.selfdrive.ui.onroad.model_renderer", "openpilot.selfdrive.ui.mici.onroad.model_renderer"])
def test_renderers_overlay_existing_styles_and_respect_settings(monkeypatch, tmp_path, module):
  renderer_module = importlib.import_module(module)
  params = Params(str(tmp_path))
  ui = SimpleNamespace(ui_params=UIParamCache(params), started_frame=100,
                       status=renderer_module.UIStatus.ENGAGED, always_on_lateral_active=True)
  monkeypatch.setattr(renderer_module, "ui_state", ui)
  monkeypatch.setattr(renderer_module.time, "monotonic", lambda: 10.0)
  draws = []
  monkeypatch.setattr(renderer_module, "draw_polygon", lambda rect, points, color=None, gradient=None: draws.append((points, color, gradient)))
  renderer = renderer_module.ModelRenderer()
  renderer._path.projected_points = np.array([[0, 100], [40, 0], [60, 0], [100, 100]], dtype=np.float32)
  renderer._exp_gradient = Gradient((0, 1), (0, 0), [rl.Color(*rl.BLUE), rl.Color(*rl.GREEN)], [0, 1])
  sm = Messages()
  ui.ui_params.put("PathColor", "#123456")
  for ev9, rainbow, acceleration, experimental in ((True, True, True, False), (False, False, False, False),
                                                 (False, False, True, False), (False, False, True, True), (False, True, True, False)):
    ui.ui_params.put_bool("EV9Path", ev9)
    ui.ui_params.put_bool("RainbowPath", rainbow)
    ui.ui_params.put_bool("AccelerationPath", acceleration)
    renderer._use_rainbow, renderer._use_accel_path = rainbow, acceleration
    renderer._experimental_mode = experimental
    for enabled, model_ui, expected_draws in ((False, True, 1), (True, True, 2), (True, False, 1)):
      ui.ui_params.put_bool("PathWarningHighlight", enabled)
      ui.ui_params.put_bool("ModelUI", model_ui)
      draws.clear()
      renderer._draw_path(sm)
      assert len(draws) == expected_draws
      base_colors = [(c.r, c.g, c.b, c.a) for c in draws[0][2].colors]
      if not enabled:
        original_colors = base_colors
      assert base_colors == original_colors
      if expected_draws == 2:
        assert draws[-1][0] is renderer._path.projected_points
        assert draws[-1][2].colors[0].r > draws[-1][2].colors[0].g
    assert params.get_bool("RainbowPath") == rainbow and params.get_bool("AccelerationPath") == acceleration
  assert params.get("PathColor") == "#123456"
  # EV9 animation advances each draw, and resets between drives and without a path.
  ui.ui_params.put_bool("EV9Path", True)
  sm["selfdriveState"].alertType = ""
  renderer._draw_path(sm)
  monkeypatch.setattr(renderer_module.time, "monotonic", lambda: 10.1)
  renderer._draw_path(sm)
  assert renderer._ev9_path._accel_presence > 0
  ui.started_frame = 101
  renderer._draw_path(sm)
  assert renderer._ev9_path._accel_presence == 0 and not renderer._ev9_path._active
  renderer._path.projected_points = np.empty((0, 2), dtype=np.float32)
  draws.clear()
  renderer._draw_path(sm)
  assert not draws
  assert renderer._ev9_path._last_update_time is None
  assert renderer._path_warning_highlight._last_update_time is None
