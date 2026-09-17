from dataclasses import replace

import pytest

from openpilot.selfdrive.ui.onroad.starpilot.longitudinal_status import LongitudinalSample, LongitudinalStatus, longitudinal_status


def sample(now=20.0, **changes):
  return replace(LongitudinalSample(
    now=now, session_start=10.0, started=True, identity_ev9=True, identity_time=9.9,
    panda_time=now - 0.01, panda_valid=True, safety_models=("hyundaiCanfd",), safety_params=(36245,), panda_fault=False,
    events_time=now - 0.01, events_valid=True, initializing=False,
    control_time=now - 0.01, control_valid=True, long_active=False,
  ), **changes)


def test_runtime_configuration_and_activity_are_distinct():
  assert longitudinal_status(sample()) == "OP long ready"
  assert longitudinal_status(sample(long_active=True)) == "OP long active"
  assert longitudinal_status(sample(safety_params=(36241,))) == "Stock ACC"
  assert longitudinal_status(sample(safety_params=(36241,), long_active=True)) is None


@pytest.mark.parametrize("changes", [
  {"started": False}, {"identity_ev9": False}, {"identity_time": 0}, {"identity_time": 21},
  {"panda_valid": False}, {"panda_fault": True}, {"panda_time": 9.9}, {"panda_time": 18.9}, {"panda_time": 21.0},
  {"safety_models": ()}, {"safety_params": ()}, {"safety_models": ("elm327",)},
  {"safety_models": ("noOutput",)}, {"safety_models": ("hyundaiCanfd", "hyundaiCanfd"), "safety_params": (36245, 36245)},
  {"safety_params": (4,)}, {"safety_params": (36245 & ~256,)},
  {"events_valid": False}, {"events_time": 9.9}, {"events_time": 17.4}, {"events_time": 21.0}, {"initializing": True},
  {"control_valid": False}, {"control_time": 9.9}, {"control_time": 19.4}, {"control_time": 21.0},
])
def test_no_claim_without_current_vehicle_safety_and_control_evidence(changes):
  assert longitudinal_status(sample(**changes)) is None


def test_car_params_identity_can_precede_ui_start_but_must_be_recent():
  assert longitudinal_status(sample(identity_time=9.9)) == "OP long ready"
  assert longitudinal_status(sample(now=70, identity_time=9.9)) is None


@pytest.mark.parametrize("safety_param,label", [(36245, "OP long ready"), (36241, "Stock ACC")])
def test_thirty_seconds_begin_at_confirmation_not_onroad_transition(safety_param, label):
  notice = LongitudinalStatus()
  assert notice.update(sample(now=20, initializing=True)) is None
  assert notice.update(sample(now=30, safety_models=("elm327",))) is None
  assert notice.update(sample(now=40, safety_params=(safety_param,))) == label
  assert notice.update(sample(now=69.99, identity_time=60, safety_params=(safety_param,))) == label
  assert notice.update(sample(now=70, identity_time=60, safety_params=(safety_param,))) is None
  assert notice.update(sample(now=71, identity_time=60, safety_params=(safety_param,))) is None


def test_activity_changes_and_data_recovery_do_not_extend_notice():
  notice = LongitudinalStatus()
  assert notice.update(sample()) == "OP long ready"
  assert notice.update(sample(now=25, long_active=True)) == "OP long active"
  assert notice.update(sample(now=30, panda_valid=False)) == "Long status unavailable"
  assert notice.update(sample(now=35, identity_ev9=False)) is None
  assert notice.update(sample(now=49.99)) == "OP long ready"
  assert notice.update(sample(now=50, long_active=True)) is None
  assert notice.update(sample(now=51, initializing=True)) is None
  assert notice.update(sample(now=52, safety_params=(36241,))) is None


def test_offroad_and_new_ignition_each_reset_the_notice():
  notice = LongitudinalStatus()
  assert notice.update(sample()) == "OP long ready"
  assert notice.update(sample(now=50)) is None
  assert notice.update(sample(now=51, started=False)) is None
  assert notice.update(sample(now=60, session_start=59, identity_time=59)) == "OP long ready"
  # Reset even if rendering never observed the intervening offroad frame.
  assert notice.update(sample(now=120, session_start=119, identity_time=119)) == "OP long ready"
  assert notice.update(sample(now=150, session_start=119, identity_time=149)) is None
