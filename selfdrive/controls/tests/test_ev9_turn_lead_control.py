"""Exercise fixed-speed turn preview in real Controls, before downstream limits."""
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
  return c



def setup_case(monkeypatch, *, raw=.01, held=0., speed=5., direction=1):
  c = make_controls(monkeypatch)
  c.sm['carState'].vEgo = c.sm['carState'].vEgoRaw = speed
  c.sm['carState'].rightBlinker = direction > 0
  c.sm['carState'].leftBlinker = direction < 0
  c.sm['modelV2'].action.desiredCurvature = raw
  c.turn_hold_curvature = held
  probes, shaped = [], []

  def preview(*args):
    probes.append(args)
    return .1 * direction

  def centering(curvature, *args):
    shaped.append(curvature)
    return curvature

  monkeypatch.setattr(controlsd, '_plan_dual_probe', preview)
  c.lane_centering = SimpleNamespace(update=centering, reset=lambda: None)
  return c, probes, shaped


@pytest.mark.parametrize('sign', [-1, 1])
@pytest.mark.parametrize('speed_kph', [25.2, 25.201, 30., 35., 40.])
@pytest.mark.parametrize('limits_kph', [20., 25.2, 30., 40., 60.])
def test_preview_ceiling_preserves_model_turn_independent_of_ev9_limits(monkeypatch, sign, speed_kph, limits_kph):
  c, probes, shaped = setup_case(monkeypatch, raw=sign*.01, speed=speed_kph/3.6, direction=sign)
  c.starpilot_toggles.hkg_tuning_angle_custom_limit_max_speed_kph = limits_kph
  c.state_control()
  assert not probes
  # Inspect before downstream angle/safety limits: only supplemental preview is withdrawn.
  assert shaped[-1] == pytest.approx(sign*.01)


@pytest.mark.parametrize('sign', [-1, 1])
@pytest.mark.parametrize('limits_kph', [10., 20., 40., 60.])
@pytest.mark.parametrize('speed,expected', [(5., .085), (6., .0425), (6.999, .01), (7., .01)])
def test_preview_fades_at_fixed_boundary_in_both_directions(monkeypatch, sign, limits_kph, speed, expected):
  c, _, shaped = setup_case(monkeypatch, raw=sign*.01, speed=speed, direction=sign)
  c.starpilot_toggles.hkg_tuning_angle_custom_limit_max_speed_kph = limits_kph
  c.state_control()
  assert shaped[-1] == pytest.approx(sign*expected)


@pytest.mark.parametrize('sign', [-1, 1])
def test_retained_low_speed_hold_after_signal_cancels_is_unchanged(monkeypatch, sign):
  c, probes, shaped = setup_case(monkeypatch, raw=sign*.01, held=sign*.04, speed=1., direction=0)
  c.turn_hold_swept = .01
  c.turn_hold_handoff_t = .02
  c.state_control()
  assert not probes
  assert shaped[-1] == pytest.approx(sign*.04)
  assert c.turn_hold_curvature == pytest.approx(sign*.04)
  assert c.turn_hold_swept == pytest.approx(.01)


@pytest.mark.parametrize('speed', [0., 5.])
def test_standstill_prewind_and_low_speed_lead_remain(monkeypatch, speed):
  c, _, shaped = setup_case(monkeypatch, speed=speed)
  c.CP.steerAtStandstill = True
  monkeypatch.setattr(controlsd, 'get_plan_spatial_curvature', lambda *args: .1)
  monkeypatch.setattr(controlsd, 'get_plan_turn_onset_dist', lambda *args: 0.)
  monkeypatch.setattr(controlsd, 'get_plan_reach', lambda *args: 30.)
  c.state_control()
  assert shaped[-1] > .01


@pytest.mark.parametrize('manual', ['steeringPressed', 'manualSteeringOverride'])
def test_manual_control_bypasses_extra_assistance(monkeypatch, manual):
  c, probes, shaped = setup_case(monkeypatch)
  if manual == 'steeringPressed':
    c.sm['carState'].steeringPressed = True
  else:
    c.sm['carOutput'].actuatorsOutput.manualSteeringOverride = True
  c.state_control()
  assert not probes
  assert shaped[-1] == pytest.approx(.01)


@pytest.mark.parametrize('sign', [-1, 1])
def test_braking_before_preview_withholds_added_assistance(monkeypatch, sign):
  c, _, shaped = setup_case(monkeypatch, raw=sign*.01, direction=sign)
  c.sm['carState'].aEgo = -3.
  c.state_control()
  assert shaped[-1] == pytest.approx(sign*.01)


@pytest.mark.parametrize('raw', [.10, -.0001])
def test_model_demand_wins_or_opposes_preview(monkeypatch, raw):
  c, _, shaped = setup_case(monkeypatch, raw=raw)
  c.state_control()
  assert shaped[-1] == pytest.approx(raw)


def test_lane_change_is_not_a_turn_preview(monkeypatch):
  c, probes, shaped = setup_case(monkeypatch)
  c.sm['modelV2'].meta.laneChangeState = log.LaneChangeState.laneChangeStarting
  c.sm['modelV2'].meta.laneChangeDirection = log.LaneChangeDirection.right
  c.state_control()
  assert not probes
  assert shaped[-1] == pytest.approx(.01)


def test_non_ev9_keeps_existing_lead(monkeypatch):
  c, probes, shaped = setup_case(monkeypatch)
  c.CP.carFingerprint = 'non-EV9'
  c.state_control()
  assert probes
  assert shaped[-1] > .01
