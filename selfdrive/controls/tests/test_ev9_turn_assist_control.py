"""Exercise the edge-admission seam in real Controls, before downstream limits."""
from collections import defaultdict
from types import SimpleNamespace

import cereal.messaging as messaging
from cereal import log

import pytest

from openpilot.selfdrive.controls import controlsd
from opendbc.car.hyundai.interface import CarInterface
from opendbc.car.hyundai.values import CAR
from opendbc.car.vehicle_model import VehicleModel
from openpilot.selfdrive.controls.controlsd import Controls
from openpilot.selfdrive.controls.lib.lane_centering import LaneCenteringController
from openpilot.selfdrive.controls.lib.latcontrol_angle import LatControlAngle


class SubMaster(dict):
  def __init__(self):
    services = (
      'carState',
      'carOutput',
      'liveParameters',
      'liveDelay',
      'modelV2',
      'selfdriveState',
      'liveCalibration',
      'longitudinalPlan',
      'starpilotCarState',
      'starpilotPlan',
      'radarState',
      'lateralManeuverPlan',
    )
    super().__init__((service, getattr(messaging.new_message(service), service)) for service in services)
    self['onroadEvents'] = []
    self.valid = defaultdict(lambda: True, lateralManeuverPlan=False)
    self.logMonoTime = defaultdict(lambda: 10_000_000_000)

  def all_checks(self, services):
    return all(self.valid[service] for service in services)


def make_controls(monkeypatch):
  monkeypatch.setattr(controlsd, 'REPLAY', True)
  c = Controls.__new__(Controls)
  c.CP = CarInterface.get_non_essential_params(CAR.KIA_EV9)
  c.CP.openpilotLongitudinalControl = False
  c.CI = CarInterface
  c.sm = SubMaster()
  c.sm['carState'].vEgo = c.sm['carState'].vEgoRaw = 5.0
  c.sm['selfdriveState'].enabled = c.sm['selfdriveState'].active = True
  c.sm['liveCalibration'].calStatus = log.LiveCalibrationData.Status.calibrated
  c.sm['starpilotPlan'].lateralCheck = True
  c.sm['liveParameters'].stiffnessFactor = 1.0
  c.sm['liveParameters'].steerRatio = c.CP.steerRatio
  c.sm['liveDelay'].lateralDelay = 0.2
  c.starpilot_toggles = SimpleNamespace(
    max_desired_acceleration=2.0,
    lane_centering=False,
    lane_center_offset=0.0,
    lane_centering_e2e_authority=0.0,
    lane_centering_pause_on_signal=True,
    lane_change_pace=10,
    hkg_tuning_angle_custom_limit_max_speed_kph=40,
  )
  for field in (
    'curvature',
    'desired_curvature',
    'lc_smooth_release',
    'lc_entry_sign',
    'lc_arrest_jerk_factor',
    'turn_hold_curvature',
    'turn_hold_standstill_t',
    'turn_hold_swept',
    'turn_hold_handoff_t',
    'turn_blinker_swept',
    'twitch_guard_remaining',
  ):
    setattr(c, field, 0.0)
  c.turn_hold_done = c.steer_limited_by_safety = c.ecu_disable_failed = False
  c.ecu_disable_failed_checked = True
  c.calibrated_pose = None
  c.VM = VehicleModel(c.CP)
  c.LaC = LatControlAngle(c.CP, None, 0.01)
  c.LoC = SimpleNamespace(long_control_state=0, reset=lambda: None, update=lambda *args, **kwargs: 0.0)
  c.lane_centering = LaneCenteringController()
  c.ev9_trajectory = None
  return c



def setup_case(monkeypatch, *, raw=.01, held=.04, speed=1., weight=0.):
  c = make_controls(monkeypatch)
  c.sm['carState'].vEgo = c.sm['carState'].vEgoRaw = speed
  c.sm['modelV2'].action.desiredCurvature = raw
  c.turn_hold_curvature = held
  calls, shaped = [], []

  def authority(*args, **kwargs):
    calls.append((args, kwargs))
    return weight

  def centering(curvature, *args):
    shaped.append(curvature)
    return curvature

  monkeypatch.setattr(controlsd, 'ev9_turn_assist_authority', authority, raising=False)
  c.lane_centering = SimpleNamespace(update=centering, reset=lambda: None)
  return c, calls, shaped


@pytest.mark.parametrize('sign', [-1, 1])
@pytest.mark.parametrize('weight', [0., .5, 1.])
def test_retained_hold_after_signal_cancels_is_checked(monkeypatch, sign, weight):
  c, calls, shaped = setup_case(monkeypatch, raw=sign*.01, held=sign*.04, weight=weight)
  c.turn_hold_swept = .01
  c.turn_hold_standstill_t = .2
  c.turn_hold_handoff_t = .02
  c.state_control()
  assert len(calls) == 1
  assert shaped[-1] == pytest.approx(sign*(.01+.03*weight))
  if weight < 1.:
    assert c.turn_hold_curvature == c.turn_hold_swept == c.turn_hold_handoff_t == c.turn_hold_standstill_t == 0.
  else:
    assert c.turn_hold_curvature == pytest.approx(sign*.04)


@pytest.mark.parametrize('sign', [-1, 1])
@pytest.mark.parametrize('same_side', [False, True])
def test_blindspot_uses_actual_assist_direction_without_signal(monkeypatch, sign, same_side):
  c, calls, _ = setup_case(monkeypatch, raw=sign*.01, held=sign*.04)
  c.sm['carState'].rightBlindspot = (sign > 0) == same_side
  c.sm['carState'].leftBlindspot = (sign < 0) == same_side
  c.state_control()
  assert calls[0][1]['blindspot'] is same_side


@pytest.mark.parametrize('raw,held', [(.05, .04), (-.05, -.04), (.01, 0.)])
def test_raw_model_is_not_reduced(monkeypatch, raw, held):
  c, calls, shaped = setup_case(monkeypatch, raw=raw, held=held)
  c.state_control()
  assert not calls
  assert shaped[-1] == pytest.approx(raw)


@pytest.mark.parametrize('manual', ['steeringPressed', 'manualSteeringOverride'])
def test_manual_control_keeps_existing_shaping(monkeypatch, manual):
  c, calls, shaped = setup_case(monkeypatch)
  if manual == 'steeringPressed':
    c.sm['carState'].steeringPressed = True
  else:
    c.sm['carOutput'].actuatorsOutput.manualSteeringOverride = True
  c.state_control()
  assert not calls
  assert shaped[-1] == pytest.approx(.04)


def test_non_ev9_keeps_existing_shaping(monkeypatch):
  c, calls, shaped = setup_case(monkeypatch)
  c.CP.carFingerprint = 'non-EV9'
  c.state_control()
  assert not calls
  assert shaped[-1] == pytest.approx(.04)


@pytest.mark.parametrize('speed', [0., 5.])
def test_spatial_prewind_and_moving_lead_are_checked(monkeypatch, speed):
  c, calls, shaped = setup_case(monkeypatch, held=0., speed=speed)
  c.sm['carState'].rightBlinker = True
  c.CP.steerAtStandstill = True  # Exercise pre-wind with lateral control explicitly permitted.
  monkeypatch.setattr(controlsd, 'get_plan_spatial_curvature', lambda *args: .1)
  monkeypatch.setattr(controlsd, 'get_plan_turn_onset_dist', lambda *args: 0.)
  monkeypatch.setattr(controlsd, 'get_plan_reach', lambda *args: 30.)
  monkeypatch.setattr(controlsd, '_plan_dual_probe', lambda *args: .1)
  c.state_control()
  assert len(calls) == 1
  assert shaped[-1] == pytest.approx(.01)
  assert c.turn_hold_curvature == 0.


def test_opposing_raw_demand_does_not_bypass_guard(monkeypatch):
  # Below the existing hold's opposite-release threshold, it can still supply
  # an opposing floor. Blocking extra assistance must restore the raw action.
  c, calls, shaped = setup_case(monkeypatch, raw=-.0001)
  c.state_control()
  assert len(calls) == 1
  assert shaped[-1] == pytest.approx(-.0001)
  assert calls[0][1]['base_curvature'] == pytest.approx(-.0001)


def test_model_validity_is_forwarded(monkeypatch):
  c, calls, _ = setup_case(monkeypatch)
  c.sm.valid['modelV2'] = False
  c.state_control()
  assert calls[0][1]['model_valid'] is False
