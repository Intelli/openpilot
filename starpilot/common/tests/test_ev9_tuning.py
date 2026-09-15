import json
from types import SimpleNamespace

import pytest

from opendbc.car.hyundai.ev9 import EV9AngleConfig
from openpilot.starpilot.common.ev9_tuning import read_ev9_tuning


def test_defaults_reach_native_ev9_controller():
  values = read_ev9_tuning({})
  config = EV9AngleConfig.from_toggles(SimpleNamespace(**json.loads(json.dumps(values))))
  assert config.limit_speed_mps == pytest.approx(40 / 3.6)
  assert config.override_effort_scale == 0.1
  assert config.shared_autonomy_mode == 0


@pytest.mark.parametrize('raw', [None, '', 'broken', 'nan', 'inf', '-inf'])
def test_invalid_values_use_application_defaults(raw):
  values = read_ev9_tuning(dict.fromkeys([
    'HkgTuningAngleCustomLimitMaxSpeedKph', 'HkgTuningAngleOverrideEffortPercent', 'HkgSharedAutonomyMode',
  ], raw))
  assert values == read_ev9_tuning({})


def test_persisted_values_override_stale_startup_broadcast(monkeypatch):
  from openpilot.starpilot.common import starpilot_variables as spv

  values = {'HkgTuningAngleCustomLimitMaxSpeedKph': b'25', 'HkgTuningAngleOverrideEffortPercent': '70', 'HkgSharedAutonomyMode': '2'}
  monkeypatch.setattr(spv.get_starpilot_toggles, '_params', SimpleNamespace(get=values.get, get_bool=lambda _key: False), raising=False)
  sm = {'starpilotPlan': SimpleNamespace(starpilotToggles='{"hkg_shared_autonomy_mode": 0}')}
  config = EV9AngleConfig.from_toggles(spv.get_starpilot_toggles(sm, read_persisted_force_params=True))
  assert config.limit_speed_mps == pytest.approx(25 / 3.6)
  assert config.override_effort_scale == 0.7
  assert config.shared_autonomy_mode == 2


def test_tuning_bounds_match_supported_ui_range():
  values = read_ev9_tuning({'HkgTuningAngleCustomLimitMaxSpeedKph': 100, 'HkgTuningAngleOverrideEffortPercent': -1, 'HkgSharedAutonomyMode': 9})
  assert EV9AngleConfig.from_toggles(values) == EV9AngleConfig(40 / 3.6, 0.1, 2)


def test_realtime_toggles_do_not_read_params(monkeypatch):
  from openpilot.starpilot.common import starpilot_variables as spv

  def unexpected_read(_key):
    raise AssertionError('Realtime Params read')
  monkeypatch.setattr(spv.get_starpilot_toggles, '_params', SimpleNamespace(get=unexpected_read, get_bool=unexpected_read), raising=False)
  payload = json.dumps(read_ev9_tuning({'HkgTuningAngleCustomLimitMaxSpeedKph': '30'}))
  config = EV9AngleConfig.from_toggles(spv.get_starpilot_toggles({'starpilotPlan': SimpleNamespace(starpilotToggles=payload)}))
  assert config.limit_speed_mps == pytest.approx(30 / 3.6)
