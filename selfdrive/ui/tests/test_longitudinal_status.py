from dataclasses import replace

import pytest

from openpilot.selfdrive.ui.onroad.starpilot.longitudinal_status import LongitudinalSample, LongitudinalStatus, longitudinal_status


def sample(now=20.0, **changes):
  return replace(LongitudinalSample(
    now=now, session_start=10.0, started=True, identity_ev9=True, identity_time=9.9,
    panda_time=now - 0.01, panda_valid=True, safety_models=("hyundaiCanfd",), safety_params=(36245,), panda_fault=False,
    events_time=now - 0.01, events_valid=True, initializing=False,
    control_time=now - 0.01, control_valid=True,
    vehicle_time=now - 0.01, vehicle_valid=True, ready_time=now - 0.01, vehicle_ready=False,
  ), **changes)


def test_runtime_configuration_and_vehicle_power_state():
  assert longitudinal_status(sample()) == "OP long ready"
  assert longitudinal_status(sample(vehicle_ready=True)) == "OP long"
  assert longitudinal_status(sample(safety_params=(36241,))) == "Stock ACC"
  assert longitudinal_status(sample(safety_params=(36241,), vehicle_ready=True)) == "Stock ACC"


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


@pytest.mark.parametrize("changes", [
  {"vehicle_valid": False}, {"vehicle_time": 0}, {"vehicle_time": 9.9}, {"vehicle_time": 19.4}, {"vehicle_time": 21},
  {"ready_time": 0}, {"ready_time": 9.9}, {"ready_time": 19.4}, {"ready_time": 21},
])
@pytest.mark.parametrize("ready", [False, True])
def test_op_prompt_and_confirmation_require_fresh_ready_evidence(changes, ready):
  assert longitudinal_status(sample(vehicle_ready=ready, **changes)) is None
  # Stock mode is established by Panda; no READY inference is needed for that label.
  assert longitudinal_status(sample(safety_params=(36241,), vehicle_ready=ready, **changes)) == "Stock ACC"


def test_car_params_identity_can_precede_ui_start_but_must_be_recent():
  assert longitudinal_status(sample(identity_time=9.9)) == "OP long ready"
  assert longitudinal_status(sample(now=70, identity_time=9.9)) is None


@pytest.mark.parametrize("safety_param,label", [(36245, "OP long"), (36241, "Stock ACC")])
def test_thirty_seconds_begin_at_confirmation_not_onroad_transition(safety_param, label):
  notice = LongitudinalStatus()
  assert notice.update(sample(now=20, initializing=True)) == "Please wait..."
  assert notice.update(sample(now=60, identity_time=59, safety_models=("elm327",))) == "Please wait..."
  assert notice.update(sample(now=70, identity_time=69, safety_params=(safety_param,), vehicle_ready=True)) == label
  assert notice.update(sample(now=99.99, identity_time=90, safety_params=(safety_param,), vehicle_ready=True)) == label
  assert notice.update(sample(now=100, identity_time=90, safety_params=(safety_param,), vehicle_ready=True)) is None
  assert notice.update(sample(now=101, identity_time=90, safety_params=(safety_param,), vehicle_ready=True)) is None


@pytest.mark.parametrize("changes", [
  {"started": False}, {"identity_ev9": False}, {"identity_time": 0}, {"identity_time": 21}, {"identity_time": -40},
])
def test_startup_wait_requires_recent_ev9_identity(changes):
  assert LongitudinalStatus().update(sample(initializing=True, **changes)) is None


def test_prompt_waits_for_brake_start_then_confirmation_gets_thirty_seconds():
  notice = LongitudinalStatus()
  assert notice.update(sample(now=11, initializing=True)) == "Please wait..."
  assert notice.update(sample()) == "OP long ready"
  assert notice.update(sample(now=80, identity_time=79)) == "OP long ready"
  assert notice.update(sample(now=90, identity_time=89, vehicle_ready=True)) == "OP long"
  assert notice.update(sample(now=119.99, identity_time=119, vehicle_ready=True)) == "OP long"
  assert notice.update(sample(now=120, identity_time=119, vehicle_ready=True)) is None


def test_missing_evidence_never_keeps_green_or_restarts_final_window():
  notice = LongitudinalStatus()
  assert notice.update(sample(vehicle_ready=True)) == "OP long"
  assert notice.update(sample(now=25, ready_time=20, vehicle_ready=True)) == "Long status unavailable"
  assert notice.update(sample(now=30, panda_valid=False, vehicle_ready=True)) == "Long status unavailable"
  assert notice.update(sample(now=35, identity_ev9=False, vehicle_ready=True)) is None
  assert notice.update(sample(now=49.99, vehicle_ready=True)) == "OP long"
  assert notice.update(sample(now=50, vehicle_ready=True)) is None
  assert notice.update(sample(now=51, initializing=True, vehicle_ready=True)) is None
  assert notice.update(sample(now=52, safety_params=(36241,), vehicle_ready=True)) is None


def test_ready_fluctuations_do_not_restart_final_window():
  notice = LongitudinalStatus()
  assert notice.update(sample(vehicle_ready=True)) == "OP long"
  assert notice.update(sample(now=30)) == "OP long ready"
  assert notice.update(sample(now=40, vehicle_ready=True)) == "OP long"
  assert notice.update(sample(now=50, vehicle_ready=True)) is None


def test_stock_confirmation_reappears_when_vehicle_starts_after_initial_window():
  notice = LongitudinalStatus()
  assert notice.update(sample(safety_params=(36241,))) == "Stock ACC"
  assert notice.update(sample(now=50, safety_params=(36241,))) is None
  assert notice.update(sample(now=60, identity_time=59, safety_params=(36241,), vehicle_ready=True)) == "Stock ACC"
  assert notice.update(sample(now=90, identity_time=89, safety_params=(36241,), vehicle_ready=True)) is None


def test_offroad_and_new_ignition_each_reset_the_notice():
  notice = LongitudinalStatus()
  assert notice.update(sample(vehicle_ready=True)) == "OP long"
  assert notice.update(sample(now=50, vehicle_ready=True)) is None
  assert notice.update(sample(now=51, started=False)) is None
  assert notice.update(sample(now=60, session_start=59, identity_time=59)) == "OP long ready"
  # Reset even if rendering never observed the intervening offroad frame.
  assert notice.update(sample(now=120, session_start=119, identity_time=119, initializing=True)) == "Please wait..."
  assert notice.update(sample(now=121, session_start=119, identity_time=119, vehicle_ready=True)) == "OP long"
  assert notice.update(sample(now=151, session_start=119, identity_time=149, vehicle_ready=True)) is None
