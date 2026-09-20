#!/usr/bin/env python3
"""Opt-in EV9 model-path refinement, separate from the 100 Hz controls loop."""
import time

from cereal import car, messaging
from openpilot.common.params import Params
from openpilot.selfdrive.controls.lib.ev9_path_planner import ModelPathPlanner, PathPlanningDecision
from openpilot.selfdrive.controls.lib.ev9_trajectory import TrajectoryMode, parse_mode
from openpilot.selfdrive.controls.lib.ev9_trajectory_io import PoseHistory, decode_snapshot, plan_message


def run(cp, params, sm, pm, *, planner=None, clock=time.monotonic):
  planner = planner if planner is not None else ModelPathPlanner()
  history = PoseHistory()
  last_status = None
  try:
    while True:
      sm.update(20)
      now = clock()
      mode = parse_mode(params.get('EV9TrajectoryMode'))
      snapshot = decode_snapshot(sm['ev9TrajectoryState'], cp, now=now,
                                 message_time=sm.logMonoTime['ev9TrajectoryState'] / 1e9,
                                 valid=sm.all_checks(['ev9TrajectoryState']), require_eligible=False)
      state, vm, roll, offset = snapshot if snapshot is not None else (None, None, 0., 0.)
      if state is not None:
        history.add(state)
      else:
        history.reset()
      if mode == TrajectoryMode.OFF:
        planner.reset()
        last_status = None
        continue
      # Parameter reads and snapshot decoding can be descheduled. Judge input
      # freshness at solve entry, not at the earlier subscription wakeup.
      now = clock()
      if state is None or state.rejection(now):
        planner.reset()
        decision = PathPlanningDecision('invalid_execution_state')
      elif sm.updated['modelV2']:
        model = sm['modelV2']
        model_time = model.timestampEof / 1e9
        capture_pose = state.model_capture_pose if state.model_capture_time == model_time else None
        if capture_pose is None:
          capture_pose = history.at(model_time, state.generation)
        decision = planner.update(model, state, vm, model_time=model_time,
                                  model_pose=capture_pose, now=now, mode=mode,
                                  model_valid=sm.all_checks(['modelV2']), roll=roll, angle_offset_deg=offset)
      else:
        # Never renew an old plan on a controls tick. Its original capture-time
        # expiry remains binding even when new model messages stop arriving.
        continue
      generation = state.generation if state is not None else int(sm['ev9TrajectoryState'].generation)
      result = plan_message(decision, generation=generation, source_time=state.time if state is not None else now)
      status = (decision.reason, result.get('planId', 0), generation)
      if decision.reason == 'invalid_execution_state' and status == last_status:
        continue
      msg = messaging.new_message('ev9TrajectoryPlan', valid=True)
      msg.ev9TrajectoryPlan = result
      pm.send('ev9TrajectoryPlan', msg)
      last_status = status
  finally:
    planner.close()


def create_submaster():
  # Solver work conflates incoming samples: this consumer's receive frequency
  # does not measure publisher health. Keep Event validity and liveness checks;
  # decode_snapshot and the planner separately enforce source/capture freshness.
  services = ['modelV2', 'ev9TrajectoryState']
  return messaging.SubMaster(services, poll='ev9TrajectoryState', ignore_avg_freq=services)


def main():
  params = Params()
  cp = messaging.log_from_bytes(params.get('CarParams', block=True), car.CarParams)
  from opendbc.car.hyundai.values import CAR, HyundaiFlags
  if cp.carFingerprint != CAR.KIA_EV9 or not cp.flags & HyundaiFlags.CANFD_ANGLE_STEERING:
    return
  # Collect pose history at controls frequency; solve only on new model frames.
  sm = create_submaster()
  pm = messaging.PubMaster(['ev9TrajectoryPlan'])
  run(cp, params, sm, pm)


if __name__ == '__main__':
  main()
