from types import SimpleNamespace

import pytest

from openpilot.selfdrive.ui.onroad.starpilot.ev9_path import EV9Path, ev9_path_state


def colors(path):
  gradient = path.get_gradient()
  assert len(gradient.colors) == len(gradient.stops)
  assert gradient.stops == sorted(gradient.stops)
  return [(c.r, c.g, c.b, c.a) for c in gradient.colors]


def tick(path, now, *, acceleration=0.0, active=True, hazard=False):
  path.update(now=now, acceleration=acceleration, active=active, hazard=hazard)


def test_inactive_and_reset_clear_animation():
  path = EV9Path()
  tick(path, 10, active=False)
  gray = colors(path)
  assert all(r == g == b for r, g, b, _ in gray)
  for frame in range(11):
    tick(path, 11 + frame * 0.1, acceleration=1)
  assert colors(path) != gray
  tick(path, 13, active=False)
  assert colors(path) == gray
  path.reset()
  assert colors(path) == colors(EV9Path())


def test_hazard_priority_even_when_inactive_and_smooth_release():
  path = EV9Path()
  tick(path, 10, active=False)
  gray = colors(path)
  tick(path, 10.1, active=False, hazard=True)
  red = colors(path)
  assert any(r > g and r > b for r, g, b, _ in red)
  for frame in range(1, 5):
    tick(path, 10.1 + frame * 0.1, active=False)
    assert colors(path) == red
  for frame in range(5, 11):
    tick(path, 10.1 + frame * 0.1, active=False)
  assert colors(path) not in (red, gray)
  for frame in range(11, 18):
    tick(path, 10.1 + frame * 0.1, active=False)
  assert colors(path) == gray
  tick(path, 12, active=False, hazard=True)
  assert colors(path) == red


def test_long_gap_resets_and_does_not_advance_animation():
  path = EV9Path()
  tick(path, 10, acceleration=1)
  for frame in range(1, 8):
    tick(path, 10 + frame * 0.1, acceleration=1)
  tick(path, 12, acceleration=1)
  fresh = EV9Path()
  tick(fresh, 12, acceleration=1)
  assert colors(path) == colors(fresh)


class Messages(dict):
  def __init__(self):
    super().__init__(carState=SimpleNamespace(aEgo=0.8), carControl=SimpleNamespace(latActive=True),
                     selfdriveState=SimpleNamespace(alertType=''), starpilotSelfdriveState=SimpleNamespace(alertType=''))
    self.valid = dict.fromkeys(self, True)
    self.alive = dict.fromkeys(self, True)
    self.recv_frame = dict.fromkeys(self, 100)
    self.recv_time = dict.fromkeys(self, 10.0)


def state(sm):
  return ev9_path_state(sm, 100, 10.5)


def test_lateral_activity_comes_from_car_control_including_aol():
  sm = Messages()
  sm['selfdriveState'].enabled = False
  assert state(sm) == (0.8, True, False)
  sm['carControl'].latActive = False
  assert state(sm) == (0.8, False, False)


@pytest.mark.parametrize('service', ['carState', 'carControl', 'selfdriveState', 'starpilotSelfdriveState'])
@pytest.mark.parametrize('condition', ['invalid', 'dead', 'previous_session', 'stale', 'future'])
def test_stale_or_invalid_messages_cannot_affect_path(service, condition):
  sm = Messages()
  sm['selfdriveState'].alertType = 'fcw/permanent' if service == 'selfdriveState' else ''
  sm['starpilotSelfdriveState'].alertType = 'goatSteerSaturated/warning' if service == 'starpilotSelfdriveState' else ''
  if condition == 'invalid':
    sm.valid[service] = False
  elif condition == 'dead':
    sm.alive[service] = False
  elif condition == 'previous_session':
    sm.recv_frame[service] = 99
  elif condition == 'stale':
    sm.recv_time[service] = 9.49
  else:
    sm.recv_time[service] = 10.6
  acceleration, active, hazard = state(sm)
  if service == 'carState':
    assert acceleration == 0
  if service == 'carControl':
    assert not active
  assert not hazard


@pytest.mark.parametrize('prefix', ['steerSaturated', 'aeb', 'stockAeb', 'fcw', 'driverDistracted', 'driverDistracted2',
                                    'driverUnresponsive', 'manualRestart'])
def test_ordinary_hazards(prefix):
  sm = Messages()
  sm['selfdriveState'].alertType = prefix + '/warning'
  assert state(sm)[2]


@pytest.mark.parametrize('prefix', ['goatSteerSaturated', 'firefoxSteerSaturated', 'thisIsFineSteerSaturated'])
def test_starpilot_hazards(prefix):
  sm = Messages()
  sm['starpilotSelfdriveState'].alertType = prefix + '/warning'
  assert state(sm)[2]


@pytest.mark.parametrize('alert', ['', 'laneChange/warning', 'startup/permanent'])
def test_ordinary_informational_alerts_do_not_trigger_hazard(alert):
  sm = Messages()
  sm['selfdriveState'].alertType = alert
  sm['starpilotSelfdriveState'].alertType = alert
  assert not state(sm)[2]


def test_acceleration_hysteresis_and_fade_timing():
  path = EV9Path()
  tick(path, 10, acceleration=0.24)
  assert not path._accel_state
  tick(path, 10.1, acceleration=0.26)
  assert path._accel_state
  assert path._accel_presence == pytest.approx(0.2)
  for frame in range(2, 6):
    tick(path, 10 + frame * 0.1, acceleration=0.20)
  assert path._accel_state
  assert path._accel_presence == pytest.approx(1)
  tick(path, 10.6, acceleration=0.14)
  assert not path._accel_state
  assert path._accel_presence == pytest.approx(0.9)
  for frame in range(7, 16):
    tick(path, 10 + frame * 0.1, acceleration=0.20)
  assert not path._accel_state
  assert path._accel_presence == pytest.approx(0, abs=1e-12)


def test_frame_delta_is_bounded_and_inactive_resets_acceleration():
  path = EV9Path()
  tick(path, 10, acceleration=1)
  tick(path, 10.8, acceleration=1)
  assert path._accel_presence == pytest.approx(0.2)
  tick(path, 10.8, acceleration=1)
  assert path._accel_presence == pytest.approx(0.2)
  tick(path, 10.9, active=False)
  assert path._accel_presence == 0 and not path._accel_state
  assert path._wave_phase == path._rainbow_phase_shift == path._rainbow_wave_phase == 0


def test_reset_clears_hazard_and_all_animation():
  path = EV9Path()
  tick(path, 10, acceleration=1, hazard=True)
  tick(path, 10.1, acceleration=1, hazard=True)
  path.reset()
  assert path._last_update_time is None
  assert path._accel_presence == path._hazard_mix == path._hazard_hold == 0
  assert path._wave_phase == path._rainbow_phase_shift == path._rainbow_wave_phase == 0
  assert not path._accel_state
