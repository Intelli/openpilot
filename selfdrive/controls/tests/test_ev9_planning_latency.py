"""A fresh solve snapshot and a fresh adoption state have different lifetimes."""
from dataclasses import replace
import math
import os
from types import SimpleNamespace

import numpy as np
import pytest

from opendbc.car.vehicle_model import VehicleModel
from openpilot.selfdrive.controls.lib.ev9_path_mpc import Ev9PathMpc
from openpilot.selfdrive.controls.lib.ev9_path_planner import ModelPathPlanner
from openpilot.selfdrive.controls.lib.ev9_trajectory import ExecutionState, TrajectoryMode, TrajectoryTracker
from openpilot.selfdrive.controls.lib.ev9_trajectory_control import decode_plan
from openpilot.selfdrive.controls.lib.ev9_trajectory_io import plan_message


@pytest.fixture(scope='module')
def native(tmp_path_factory):
  library = os.environ.get('EV9_PATH_MPC_LIBRARY')
  if library is None:
    from openpilot.selfdrive.controls.lib.ev9_path_mpc_lib.generate import build
    library = build(tmp_path_factory.mktemp('latency-mpc'))
  solver = Ev9PathMpc(library)
  yield solver
  solver.close()


def turn():
  vm = VehicleModel(SimpleNamespace(mass=2800., rotationalInertia=6311.7, wheelbase=3.1, centerToFront=1.24,
                                   steerRatioRear=0., tireStiffnessFront=368002.7, tireStiffnessRear=387824.9, steerRatio=16.))
  arc = np.linspace(0., 45., 301)
  curvature = abs(vm.calc_curvature(math.radians(144.), 2., 0.)) * np.clip(np.minimum((arc-12.)/4., (35.-arc)/4.), 0., 1.)
  step = np.diff(arc)
  yaw = np.r_[0., np.cumsum((curvature[1:]+curvature[:-1])*step/2)]
  middle = (yaw[1:]+yaw[:-1])/2
  xy = np.vstack(([0., 0.], np.cumsum(np.column_stack((np.cos(middle), np.sin(middle)))*step[:, None], axis=0)))
  camera = xy + 2*np.column_stack((np.cos(yaw), np.sin(yaw))) - [2., 0.]
  model = dict(position=dict(x=camera[:, 0], y=-camera[:, 1], t=arc/2), orientation=dict(z=-yaw, t=arc/2))
  return model, vm


def delayed_plan(native, *, initial_age=.03, compute=.04, model_age=.08):
  model, vm = turn()
  start = 10.+initial_age
  clock = [start]

  class TimedSolver:
    def solve(self, *args, **kwargs):
      result = native.solve(*args, **kwargs)
      clock[0] += compute
      return result

  state = ExecutionState(10., (0., 0., 0.), 2., 0., 0., 0., .3, generation=3)
  planner = ModelPathPlanner(solver=TimedSolver(), clock=lambda: clock[0])
  result = planner.update(model, state, vm, model_time=10.-model_age, model_pose=(0., 0., 0.), now=start,
                          mode=TrajectoryMode.ACTIVE, model_valid=True, roll=0., angle_offset_deg=0.)
  return result, state, clock[0]


def adopt(plan, state, now, **changes):
  tracker = TrajectoryTracker()
  tracker.update(replace(state, time=9.99), .0123, mode=TrajectoryMode.ACTIVE)
  current = replace(state, **(dict(time=now, pose=(state.speed*(now-state.time), 0., 0.)) | changes))
  return tracker.update(current, .0123, mode=TrajectoryMode.ACTIVE, proposal=plan,
                        corridor_revision=plan.corridor_revision, corridor_valid_until=plan.valid_until, model_turn_direction=1)


def test_timely_compute_uses_fresh_adoption_state_without_restamping(native):
  result, state, now = delayed_plan(native)
  assert result.plan is not None, result.reason
  assert now-state.time > .05 and result.solve_time < .05
  message = plan_message(result, generation=state.generation, source_time=state.time)
  plan = decode_plan(SimpleNamespace(**message))
  assert plan.source_time == 10.
  assert plan.valid_until == pytest.approx(10.-.08+.25)
  decision = adopt(plan, state, now)
  assert decision.active and decision.plan_id == plan.plan_id


@pytest.mark.parametrize('changes,reason', [
  ({'manual': True}, 'driver_or_baseline_ownership'),
  ({'enabled': False}, 'driver_or_baseline_ownership'),
  ({'lane_change': True}, 'driver_or_baseline_ownership'),
  ({'healthy': False}, 'driver_or_baseline_ownership'),
  ({'generation': 4}, 'state_or_frame_mismatch'),
  ({'speed': 3.}, 'speed_mismatch'),
  ({'curvature': .02}, 'initial_state_mismatch'),
  ({'command_curvature': .02}, 'initial_state_mismatch'),
  ({'pose': (.14, .3, 0.)}, 'initial_state_mismatch'),
  ({'pose': (.14, 0., math.radians(4))}, 'initial_state_mismatch'),
  ({'standstill': True}, 'standstill'),
])
def test_delayed_plan_is_revalidated_against_actual_current_state(native, changes, reason):
  result, state, now = delayed_plan(native)
  assert result.plan is not None, result.reason
  decision = adopt(result.plan, state, now, **changes)
  assert not decision.active and decision.reason == reason
  assert decision.curvature == .0123


@pytest.mark.parametrize('kwargs,reason', [
  ({'initial_age': .06}, 'invalid_execution_state'),
  ({'compute': .051}, 'planning_deadline'),
  ({'model_age': .19}, 'planning_deadline'),
])
def test_stale_input_compute_overrun_and_old_model_remain_rejected(native, kwargs, reason):
  result, _, _ = delayed_plan(native, **kwargs)
  assert result.plan is None and result.reason == reason


def test_delayed_plan_cannot_cross_a_driver_intervention_or_extend_lease(native):
  result, state, now = delayed_plan(native)
  assert result.plan is not None, result.reason
  plan = result.plan
  tracker = TrajectoryTracker()
  tracker.update(replace(state, time=9.99), .0123, mode=TrajectoryMode.ACTIVE)
  tracker.update(replace(state, time=10.04, manual=True), .0123, mode=TrajectoryMode.ACTIVE)
  current = replace(state, time=now, pose=(.14, 0., 0.))
  decision = tracker.update(current, .0123, mode=TrajectoryMode.ACTIVE, proposal=plan,
                            corridor_revision=plan.corridor_revision, corridor_valid_until=plan.valid_until)
  assert not decision.active and decision.reason == 'superseded_plan'
  assert not adopt(plan, state, plan.valid_until+.001).active
