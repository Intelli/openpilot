import importlib.util
import sys
from pathlib import Path
from types import ModuleType, SimpleNamespace

import pytest


def load_widget(monkeypatch):
  def stub(name, **attributes):
    module = ModuleType(name)
    module.__dict__.update(attributes)
    monkeypatch.setitem(sys.modules, name, module)

  stub('pyray')
  stub('openpilot.selfdrive.ui.onroad.starpilot.widgets.base', LayoutWidget=object)
  stub('openpilot.selfdrive.ui.ui_state', ui_state=None)
  stub('openpilot.system.ui.lib.application', FontWeight=None, gui_app=None)
  stub('openpilot.system.ui.lib.text_measure', measure_text_cached=None)
  path = Path(__file__).parents[1] / 'onroad/starpilot/widgets/longitudinal_status.py'
  spec = importlib.util.spec_from_file_location('tested_longitudinal_widget', path)
  module = importlib.util.module_from_spec(spec)
  spec.loader.exec_module(module)
  return module


class SubMaster(dict):
  def __init__(self):
    super().__init__(carParams=SimpleNamespace(carFingerprint='KIA_EV9'),
                     pandaStates=[SimpleNamespace(safetyModel='hyundaiCanfd', safetyParam=36245, faults=[])],
                     onroadEvents=[], carControl=SimpleNamespace(longActive=False),
                     starpilotCarState=SimpleNamespace(vehicleReady=False, vehicleReadyTimestamp=99_000_000_000))
    self.frame = 1
    self.seen = dict.fromkeys(self, True)
    self.valid = dict.fromkeys(self, True)
    self.alive = dict.fromkeys(self, True)
    self.logMonoTime = dict.fromkeys(self, 99_000_000_000)


def test_live_samples_filtered_and_updated_even_when_hidden(monkeypatch):
  module = load_widget(monkeypatch)
  sm = SubMaster()
  module.ui_state = SimpleNamespace(sm=sm, started=True, started_time=90.0)
  samples = []
  widget = object.__new__(module.LongitudinalStatusWidget)
  widget._status = SimpleNamespace(update=lambda sample: samples.append(sample))
  widget._last_sample_key = None
  widget._label = None
  widget.update_status()
  widget.update_status()
  assert len(samples) == 1
  assert samples[-1].identity_ev9
  assert samples[-1].safety_params == (36245,)
  assert samples[-1].panda_valid and samples[-1].events_valid and samples[-1].control_valid
  assert samples[-1].vehicle_valid and samples[-1].ready_time == 99.0 and not samples[-1].vehicle_ready
  assert not widget.is_visible

  sm.frame += 1
  sm.seen['carParams'] = False
  sm.alive['pandaStates'] = False
  sm.valid['onroadEvents'] = False
  sm.seen['carControl'] = False
  sm.valid['starpilotCarState'] = False
  sm['pandaStates'][0].faults = ['relayMalfunction']
  widget.update_status()
  sample = samples[-1]
  assert not sample.identity_ev9 and sample.identity_time == 0
  assert not sample.panda_valid and sample.panda_fault
  assert not sample.events_valid and not sample.control_valid and sample.control_time == 0
  assert not sample.vehicle_valid

  # Transitions reset classifier state even if rendering is suppressed and sm.frame is unchanged.
  module.ui_state.started = False
  widget.update_status()
  assert not samples[-1].started
  module.ui_state.started = True
  module.ui_state.started_time = 101.0
  widget.update_status()
  assert samples[-1].session_start == 101.0
  assert len(samples) == 4


def test_live_widget_notice_expires_without_rendering_and_returns_next_startup(monkeypatch):
  module = load_widget(monkeypatch)
  sm = SubMaster()
  module.ui_state = SimpleNamespace(sm=sm, started=True, started_time=90.0)
  widget = object.__new__(module.LongitudinalStatusWidget)
  widget._status = module.LongitudinalStatus()
  widget._last_sample_key = None
  widget._label = None

  def update(now):
    monkeypatch.setattr(module.time, 'monotonic', lambda: now)
    sm.frame += 1
    sm.logMonoTime = dict.fromkeys(sm, int((now - 0.01) * 1e9))
    sm['starpilotCarState'].vehicleReadyTimestamp = int((now - 0.01) * 1e9)
    widget.update_status()
    return widget._label

  assert update(100) == 'OP long ready'
  sm['carControl'].longActive = True
  assert update(105) == 'OP long ready'
  sm['starpilotCarState'].vehicleReady = True
  assert update(106) == 'OP long'
  sm['carControl'].longActive = False
  assert update(107) == 'OP long'
  sm.alive['pandaStates'] = False
  assert update(110) == 'Long status unavailable'
  sm.alive['pandaStates'] = True
  assert update(135.99) == 'OP long'
  assert update(136) is None
  assert update(140) is None

  # The onroad view may not render a frame during the intervening offroad period.
  module.ui_state.started_time = 150.0
  sm['pandaStates'][0].safetyParam = 36241
  sm['carControl'].longActive = False
  assert update(160) == 'Stock ACC'


@pytest.mark.parametrize('label', ['OP long', 'Stock ACC', 'OP long ready', 'Long status unavailable'])
def test_larger_text_and_flashing_only_for_startup_prompt(monkeypatch, label):
  module = load_widget(monkeypatch)
  drawn = []
  backgrounds = []
  module.rl.Color = lambda *rgba: rgba
  module.rl.Vector2 = lambda x, y: (x, y)
  module.rl.draw_rectangle_rounded = lambda *args: backgrounds.append(args)
  module.rl.draw_text_ex = lambda *args: drawn.append(args)
  module.measure_text_cached = lambda font, text, size: SimpleNamespace(x=len(text) * size * 0.5, y=size)
  widget = object.__new__(module.LongitudinalStatusWidget)
  widget._font = object()
  widget._label = label
  width, height = widget.get_size()
  rect = SimpleNamespace(x=0, y=0, width=width, height=height)

  for now in (100, 100.26, 100.5):
    monkeypatch.setattr(module.time, 'monotonic', lambda now=now: now)
    widget._render(rect)
  assert len(backgrounds) == 3
  assert len(drawn) == (2 if label == 'OP long ready' else 3)
  assert all(22 < call[3] <= 28 for call in drawn)
  expected_color = ((128, 216, 166, 255) if label in ('OP long', 'Stock ACC') else
                    (255, 190, 90, 255) if label == 'Long status unavailable' else (205, 210, 208, 255))
  assert all(call[5] == expected_color for call in drawn)
