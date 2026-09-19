"""Actual isolated msgq round trip: publisher envelopes, daemon, and ownership.

Only geometry and time are deterministic fixtures. Validity/frequency checks and
both publisher/subscriber paths are real. macOS uses its native ZMQ transport.
"""
import math
from pathlib import Path
import shutil
import sys
import time
from types import SimpleNamespace
import uuid

import numpy as np
import pytest

from cereal import messaging
from cereal.services import SERVICE_LIST
from opendbc.car.vehicle_model import VehicleModel
from openpilot.selfdrive.controls.ev9_trajectoryd import run
from openpilot.selfdrive.controls.lib.ev9_path_planner import PathPlanningDecision
from openpilot.selfdrive.controls.lib.ev9_trajectory import TrajectoryPlan
from openpilot.selfdrive.controls.lib.ev9_trajectory_control import EV9TrajectoryControl


@pytest.fixture
def isolated_bus(monkeypatch):
  namespace = 'ev9_message_test_' + uuid.uuid4().hex
  monkeypatch.setenv('OPENPILOT_PREFIX', namespace)
  monkeypatch.setenv('OPENPILOT_ZMQ_NAMESPACE', namespace)
  monkeypatch.delenv('CEREAL_FAKE', raising=False)
  monkeypatch.delenv('SIMULATION', raising=False)
  monkeypatch.delenv('REPLAY', raising=False)
  directory = Path('/dev/shm') / ('msgq_' + namespace)
  if sys.platform != 'darwin':
    directory.mkdir()
  messaging.reset_context()
  yield
  messaging.reset_context()
  if directory.exists():
    shutil.rmtree(directory)


@pytest.mark.parametrize('failure', ['manual', 'invalid_state_envelope', 'stale_input', 'stale_plan', 'rejected_refresh', 'malformed_geometry', 'speed_limit'])
def test_real_state_daemon_plan_control_round_trip(isolated_bus, monkeypatch, failure):
  cp = SimpleNamespace(mass=2800., rotationalInertia=6311.7, wheelbase=3.1, centerToFront=1.24, steerRatioRear=0.,
                       tireStiffnessFront=368002.7, tireStiffnessRear=387824.9, steerRatio=16., openpilotLongitudinalControl=False)
  vm = VehicleModel(cp)
  params = SimpleNamespace(get=lambda _: b'2')
  control = EV9TrajectoryControl(cp, params)
  services = ['carState', 'carOutput', 'modelV2', 'liveParameters', 'liveDelay', 'selfdriveState']
  upstream = messaging.PubMaster(services)
  state_pm = messaging.PubMaster(['ev9TrajectoryState'])
  plan_pm = messaging.PubMaster(['ev9TrajectoryPlan'])
  control_sm = messaging.SubMaster(services + ['ev9TrajectoryPlan'], poll='carState')
  now = [100.]
  tick = [-1]
  observed = []
  real_sleep = time.sleep

  class StatePublisher:
    def send(self, service, message):
      if failure == 'invalid_state_envelope' and tick[0] >= 120:
        message.valid = False
      if tick[0] < 120:
        assert message.valid
      state_pm.send(service, message)

  class PlanPublisher:
    def send(self, service, message):
      if failure != 'stale_plan' or tick[0] < 120:
        plan_pm.send(service, message)

  class Planner:
    calls = 0
    closed = False

    def reset(self):
      pass

    def close(self):
      self.closed = True

    def update(self, model, state, model_vm, **kwargs):
      assert kwargs['model_valid']
      assert kwargs['model_pose'] is not None
      self.calls += 1
      if failure == 'malformed_geometry' and tick[0] >= 120:
        return PathPlanningDecision('invalid_lane_metadata')
      if failure == 'rejected_refresh' and tick[0] >= 120:
        return PathPlanningDecision('native_status_4')
      distance = np.linspace(0., 20., 401)
      origin = kwargs['model_pose']
      offset = state.pose[0] - origin[0]
      xy = np.column_stack((distance + offset, np.zeros(len(distance))))
      plan = TrajectoryPlan(int(state.time * 1e9), state.generation, state.time, state.time + .25, origin,
                            state.speed, 0., state.command_curvature, -.04, .04, distance, xy,
                            np.zeros(len(distance)), np.zeros(len(distance)), int(state.time * 1e9), True)
      return PathPlanningDecision('fixture_feasible', plan, True)

  class DaemonSubscriber(messaging.SubMaster):
    def update(self, timeout=20):
      tick[0] += 1
      if tick[0] == 165:
        raise StopIteration
      now[0] = 100. + tick[0] * .01
      for service in services:
        cadence = max(1, round(100 / SERVICE_LIST[service].frequency))
        if tick[0] % cadence:
          continue
        message = messaging.new_message(service, valid=True)
        data = getattr(message, service)
        if service == 'carState':
          data.vEgo = data.vEgoRaw = 4. if failure == 'speed_limit' else 2.
          data.canValid = True
          data.gearShifter = 'drive'
          data.steeringPressed = failure == 'manual' and tick[0] >= 120
          if failure == 'stale_input' and tick[0] >= 120:
            message.logMonoTime = int((now[0] - 1.) * 1e9)
        elif service == 'modelV2':
          data.timestampEof = int(now[0] * 1e9)
        elif service == 'liveParameters':
          data.valid = True
          data.steerRatio = cp.steerRatio
          data.stiffnessFactor = 1.
        elif service == 'liveDelay':
          data.lateralDelay = .3
        upstream.send(service, message)
      real_sleep(.002)  # Let the real transport deliver; no validity injection.
      control_sm.update(20)
      limit = 10 if failure == 'speed_limit' and tick[0] >= 120 else 40
      toggles = SimpleNamespace(hkg_tuning_angle_custom_limit_max_speed_kph=limit)
      decision = control.update(control_sm, control_sm['carState'], True, vm, control_sm['liveParameters'], 0., .0123, toggles=toggles)
      observed.append((tick[0], decision.active, decision.reason, decision.curvature,
                       control_sm.valid['ev9TrajectoryPlan'], control_sm.all_checks(['ev9TrajectoryPlan'])))
      control.publish(StatePublisher(), messaging)
      real_sleep(.002)
      super().update(timeout)
      if 80 <= tick[0] < 120:
        assert self.valid['ev9TrajectoryState'], (self.seen, self.updated, control.mode, control_sm.valid, control_sm.alive, control_sm.freq_ok)
        assert self.all_checks(['ev9TrajectoryState'])

  daemon_sm = DaemonSubscriber(['modelV2', 'ev9TrajectoryState'], poll='ev9TrajectoryState')
  planner = Planner()
  real_sleep(.15)  # ZMQ subscription handshake; isolated namespace only.
  monkeypatch.setattr(time, 'monotonic', lambda: now[0])
  with pytest.raises(StopIteration):
    run(cp, params, daemon_sm, PlanPublisher(), planner=planner, clock=lambda: now[0])
  assert planner.closed and planner.calls > 5
  steady = [row for row in observed if 80 <= row[0] < 120]
  assert any(row[1] for row in steady), steady
  assert any(row[4] and row[5] for row in steady), steady
  release_tick = 121 if failure in ('malformed_geometry', 'speed_limit') else 141 if failure == 'rejected_refresh' else 151
  released = [row for row in observed if row[0] >= release_tick]
  assert all(not row[1] and math.isclose(row[3], .0123) for row in released), released
  if failure == 'rejected_refresh':
    retained = [row for row in observed if 121 <= row[0] <= 135]
    assert all(row[1] for row in retained), retained
  if failure == 'invalid_state_envelope':
    assert not daemon_sm.valid['ev9TrajectoryState']
    assert not daemon_sm.all_checks(['ev9TrajectoryState'])
