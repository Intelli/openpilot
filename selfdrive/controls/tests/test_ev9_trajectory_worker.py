"""Worker reception rate is distinct from source validity and timestamp age."""
import pytest
from cereal import messaging

from opendbc.car.hyundai.interface import CarInterface
from opendbc.car.hyundai.values import CAR
from opendbc.car.vehicle_model import VehicleModel
from openpilot.selfdrive.controls.ev9_trajectoryd import create_submaster
from openpilot.selfdrive.controls.lib.ev9_trajectory_io import decode_snapshot


@pytest.fixture
def subscribers(monkeypatch):
  monkeypatch.setenv('SIMULATION', '0')
  monkeypatch.setattr(messaging, 'sub_sock', lambda *args, **kwargs: object())
  return messaging.SubMaster(['modelV2', 'ev9TrajectoryState'], poll='ev9TrajectoryState'), create_submaster()


def messages(now, valid=True):
  result = []
  for service in ('ev9TrajectoryState', 'modelV2'):
    msg = messaging.new_message(service, valid=valid)
    msg.logMonoTime = round(now*1e9)
    result.append(msg)
  return result


def test_solver_conflation_does_not_invalidate_fresh_publisher(subscribers):
  baseline, worker = subscribers
  # Model/state publishers remain current; solver consumes only the newest
  # messages every 60 ms. Exercise real SubMaster and FrequencyTracker logic.
  for i in range(250):
    now = 10.+i*.06
    msgs = messages(now)
    for sm in subscribers:
      sm.update_msgs(now, msgs)
  assert baseline.all_alive() and baseline.all_valid()
  assert not baseline.freq_ok['ev9TrajectoryState']
  assert not baseline.all_checks()
  assert not worker.freq_ok['ev9TrajectoryState']
  assert worker.all_checks()
  assert worker.logMonoTime['ev9TrajectoryState'] == round(now*1e9)


@pytest.mark.parametrize('service', ['modelV2', 'ev9TrajectoryState'])
def test_worker_still_rejects_invalid_events_and_dead_publishers(subscribers, service):
  _, worker = subscribers
  worker.update_msgs(10., messages(10.))
  invalid = messaging.new_message(service, valid=False)
  invalid.logMonoTime = 10_010_000_000
  worker.update_msgs(10.01, [invalid])
  assert not worker.all_checks([service])
  worker.update_msgs(10.02, messages(10.02))
  assert worker.all_checks([service])
  worker.update_msgs(11., [])
  assert not worker.all_checks([service])


def test_frequency_exemption_does_not_relax_snapshot_freshness():
  cp = CarInterface.get_non_essential_params(CAR.KIA_EV9)
  vm = VehicleModel(cp)
  msg = messaging.new_message('ev9TrajectoryState').ev9TrajectoryState
  msg.sourceMonoTime = 10_000_000_000
  msg.steerRatio, msg.tireStiffnessFront, msg.tireStiffnessRear = vm.sR, vm.cF, vm.cR
  msg.speed = 2.
  msg.enabled = msg.drive = msg.healthy = True
  msg.delay = .3
  assert decode_snapshot(msg, cp, now=10.01, message_time=10., valid=True) is not None
  assert decode_snapshot(msg, cp, now=10.06, message_time=10.06, valid=True) is None
  assert decode_snapshot(msg, cp, now=10.01, message_time=9.9, valid=True) is None
  assert decode_snapshot(msg, cp, now=10.01, message_time=10., valid=False) is None


def test_worker_rechecks_freshness_after_preparation_delay():
  from types import SimpleNamespace
  from openpilot.selfdrive.controls.ev9_trajectoryd import run

  cp = CarInterface.get_non_essential_params(CAR.KIA_EV9)
  vm = VehicleModel(cp)
  msg = messaging.new_message('ev9TrajectoryState').ev9TrajectoryState
  msg.sourceMonoTime = 10_000_000_000
  msg.steerRatio, msg.tireStiffnessFront, msg.tireStiffnessRear = vm.sR, vm.cF, vm.cR
  msg.speed, msg.delay = 2., .3
  msg.enabled = msg.drive = msg.healthy = True
  now, sent = [10.], []

  class Subscriber(dict):
    def __init__(self):
      super().__init__(ev9TrajectoryState=msg, modelV2=SimpleNamespace(timestampEof=10_000_000_000))
      self.updated = dict(modelV2=True)
      self.logMonoTime = dict(ev9TrajectoryState=10_000_000_000)
      self.calls = 0

    def update(self, timeout):
      if self.calls:
        raise StopIteration
      self.calls += 1

    def all_checks(self, services):
      return True

  class Planner:
    def reset(self):
      pass

    def close(self):
      pass

    def update(self, *args, **kwargs):
      raise AssertionError('started planning from a stale execution snapshot')

  def read_mode(key):
    now[0] += .06
    return '2'

  pm = SimpleNamespace(send=lambda _, event: sent.append(event.ev9TrajectoryPlan.to_dict()))
  with pytest.raises(StopIteration):
    run(cp, SimpleNamespace(get=read_mode), Subscriber(), pm, planner=Planner(), clock=lambda: now[0])
  assert len(sent) == 1 and sent[0]['reason'] == 'invalid_execution_state'
  assert not sent[0]['feasible']
