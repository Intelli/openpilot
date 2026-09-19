"""Automatic initiation safeguards; real DesireHelper with in-memory settings."""
from types import SimpleNamespace

import pytest
from cereal import log

from openpilot.selfdrive.controls.lib import desire_helper

State = log.LaneChangeState


@pytest.fixture
def case(monkeypatch):
  monkeypatch.setattr(desire_helper, 'Params', lambda **kwargs: SimpleNamespace(get=lambda key: None))
  helper = desire_helper.DesireHelper()
  cs = SimpleNamespace(vEgo=40/3.6, leftBlinker=True, rightBlinker=False, standstill=False, brakePressed=False,
                       steeringPressed=False, steeringTorque=0., leftBlindspot=False, rightBlindspot=False,
                       cruiseState=SimpleNamespace(enabled=True))
  toggles = SimpleNamespace(minimum_lane_change_speed=20*.44704, lane_changes=True, nudgeless=True,
                            lane_change_delay=.05, lane_detection_width=2.5, one_lane_change=True, use_turn_desires=True)
  plan = SimpleNamespace(laneWidthLeft=3.5, laneWidthRight=3.5)

  def step(active=True, probability=1.):
    helper.update(cs, active, probability, plan, toggles)
    return helper.lane_change_state

  return helper, cs, toggles, step


def test_braking_blocks_initial_automatic_attempt_after_release(case):
  helper, cs, _, step = case
  assert step() == State.preLaneChange
  cs.brakePressed = True
  assert step() == State.preLaneChange
  cs.brakePressed = False
  for _ in range(40):
    assert step() == State.preLaneChange
  assert helper.lane_change_brake_latched
  cs.steeringPressed, cs.steeringTorque = True, 200.
  assert step() == State.laneChangeStarting  # Explicit nudge remains available.


def test_brake_on_arming_tick_only_is_not_waiting_latch(case):
  helper, cs, _, step = case
  cs.brakePressed = True
  step()
  cs.brakePressed = False
  step()
  assert step() == State.laneChangeStarting
  assert not helper.lane_change_brake_latched


@pytest.mark.parametrize('delay', [.05, .5, 1., 2., 3.])
def test_blindspot_clear_wait_matches_legacy_timer(case, delay):
  helper, cs, toggles, step = case
  toggles.lane_change_delay = delay
  step()
  cs.leftBlindspot = True
  for _ in range(80):
    assert step() == State.preLaneChange
  expected = -1. if delay == .05 else delay-1.
  assert helper.lane_change_wait_timer == pytest.approx(expected)
  cs.leftBlindspot = False
  for _ in range(30):
    expected += desire_helper.DT_MDL
    state = step()
    assert (state == State.laneChangeStarting) == (expected > delay)
    if state == State.laneChangeStarting:
      break
  else:
    pytest.fail('No automatic start after legacy clearance delay')


def test_nudge_bypasses_clearance_delay_but_not_occupied_blindspot(case):
  _, cs, _, step = case
  step()
  cs.leftBlindspot = True
  cs.steeringPressed, cs.steeringTorque = True, 200.
  assert step() == State.preLaneChange
  cs.leftBlindspot = False
  assert step() == State.laneChangeStarting


@pytest.mark.parametrize('reset', ['signal', 'inactive', 'disabled', 'below_speed', 'timeout'])
def test_cycle_reset_clears_latch_and_wait_without_held_signal_rearm(case, reset):
  helper, cs, toggles, step = case
  step()
  cs.brakePressed = True
  step()
  if reset == 'signal':
    cs.leftBlinker = False
  elif reset == 'disabled':
    toggles.lane_changes = False
  elif reset == 'below_speed':
    cs.vEgo = 1.
  elif reset == 'timeout':
    helper.lane_change_timer = 11.
  assert step(active=reset != 'inactive') == State.off
  assert not helper.lane_change_brake_latched
  assert helper.lane_change_wait_timer == 0.
  cs.brakePressed = False
  cs.vEgo = 40/3.6
  toggles.lane_changes = True
  if reset != 'signal':
    assert step() == State.off
    cs.leftBlinker = False
    step()
  cs.leftBlinker = True
  assert step() == State.preLaneChange
  step()
  assert step() == State.laneChangeStarting


def test_brake_does_not_cancel_started_maneuver(case):
  helper, cs, _, step = case
  step()
  step()
  assert step() == State.laneChangeStarting
  cs.brakePressed = True
  assert step() == State.laneChangeStarting
  assert not helper.lane_change_brake_latched


def test_opposite_side_blindspot_does_not_delay(case):
  _, cs, _, step = case
  cs.rightBlindspot = True
  step()
  step()
  assert step() == State.laneChangeStarting


def test_completed_cycle_keeps_existing_one_lane_policy(case):
  helper, cs, _, step = case
  step()
  cs.brakePressed = True
  step()
  cs.steeringPressed, cs.steeringTorque = True, 200.
  assert step() == State.laneChangeStarting
  cs.brakePressed = cs.steeringPressed = False
  for _ in range(40):
    step(probability=0.)
  assert helper.lane_change_state == State.off
  assert not helper.lane_change_brake_latched
  assert helper.lane_change_completed
  assert step() == State.off  # Held signal cannot rearm after completion.


def test_right_direction_brake_and_blindspot_guards(case):
  _, cs, _, step = case
  cs.leftBlinker, cs.rightBlinker = False, True
  step()
  cs.brakePressed = cs.rightBlindspot = True
  step()
  cs.brakePressed = False
  cs.steeringPressed, cs.steeringTorque = True, -200.
  assert step() == State.preLaneChange
  cs.rightBlindspot = False
  assert step() == State.laneChangeStarting
