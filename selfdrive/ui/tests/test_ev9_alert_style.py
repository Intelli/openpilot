from types import SimpleNamespace

import pytest

from cereal import log
from opendbc.car.hyundai.values import CAR
from openpilot.selfdrive.ui.lib.ev9_alert_style import alert_background_alpha, hide_normal_alert

AlertStatus = log.SelfdriveState.AlertStatus


@pytest.mark.parametrize('hidden', [False, True])
def test_compact_steering_warning_remains_visible(hidden):
  assert not hide_normal_alert(AlertStatus.normal, 'steerSaturated/warning', hidden)
  assert hide_normal_alert(AlertStatus.normal, 'laneChange/warning', hidden) == hidden
  assert not hide_normal_alert(AlertStatus.userPrompt, 'driverDistracted2/permanent', hidden)
  assert not hide_normal_alert(AlertStatus.critical, 'controlsMismatch/immediateDisable', hidden)


def test_half_opacity_only_for_normal_ev9_alerts():
  ev9 = SimpleNamespace(carFingerprint=CAR.KIA_EV9)
  assert alert_background_alpha(AlertStatus.normal, ev9) == 128
  assert alert_background_alpha(AlertStatus.userPrompt, ev9) == 255 * 0.90
  assert alert_background_alpha(AlertStatus.critical, ev9) == 255 * 0.90
  assert alert_background_alpha(AlertStatus.normal, None) == 255 * 0.90
  assert alert_background_alpha(AlertStatus.normal, SimpleNamespace(carFingerprint=CAR.HYUNDAI_IONIQ_5)) == 255 * 0.90
