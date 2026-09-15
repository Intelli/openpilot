import math
from types import SimpleNamespace

import cereal.messaging as messaging
import pytest

from cereal import car, custom, log
from opendbc.car.tesla.interface import CarInterface
from opendbc.car.tesla.values import CAR, TeslaSafetyFlags
from opendbc.car.hyundai.interface import CarInterface as HyundaiInterface
from opendbc.car.hyundai.values import CAR as HYUNDAI_CAR
from openpilot.selfdrive.controls import controlsd
from openpilot.selfdrive.controls.controlsd import Controls
from openpilot.selfdrive.controls.lib.latcontrol_angle import LatControlAngle
from openpilot.selfdrive.selfdrived.alertmanager import AlertManager
from openpilot.selfdrive.selfdrived.events import Events
from openpilot.selfdrive.selfdrived.selfdrived import SelfdriveD
from openpilot.selfdrive.selfdrived.state import StateMachine


REQUESTED_ANGLE = -14.5
OUTPUT_ANGLE = -9.0
SAMPLE_TIME_NANOS = 1_000_000_000
FRESH_TIME_NANOS = SAMPLE_TIME_NANOS + 20_000_000
STALE_TIME_NANOS = SAMPLE_TIME_NANOS + 100_000_001
HOST_TIME_NANOS = 9_000_000_000
CAR_STATE_TIME_NANOS = 7_000_000_000


class CapturePubMaster:
  def __init__(self):
    self.sent = {}

  def send(self, service, message):
    self.sent[service] = message


class PublishSubMaster:
  def __init__(self, car_output, starpilot_car_control, selfdrive_time_nanos, output_healthy=True):
    car_state = car.CarState.new_message()
    car_state.canValid = True

    long_plan = log.LongitudinalPlan.new_message()
    long_plan.speeds = []

    selfdrive_state = log.SelfdriveState.new_message()
    selfdrive_state.active = True

    self.messages = {
      "carState": car_state.as_reader(),
      "longitudinalPlan": long_plan.as_reader(),
      "starpilotCarState": custom.StarPilotCarState.new_message().as_reader(),
      "selfdriveState": selfdrive_state.as_reader(),
      "carOutput": car_output.as_reader(),
      "starpilotCarControl": starpilot_car_control.as_reader(),
      "driverAssistance": log.DriverAssistance.new_message().as_reader(),
      "driverMonitoringState": log.DriverMonitoringState.new_message().as_reader(),
    }
    self.valid = {"carOutput": output_healthy, "driverAssistance": False}
    self.alive = {"carOutput": output_healthy}
    self.freq_ok = {"carOutput": output_healthy}
    self.logMonoTime = {
      "selfdriveState": selfdrive_time_nanos,
      "carState": CAR_STATE_TIME_NANOS,
      "longitudinalPlan": 0,
      "modelV2": 0,
    }

  def __getitem__(self, service):
    return self.messages[service]


def make_car_params():
  cp = CarInterface.get_non_essential_params(CAR.TESLA_MODEL_3)
  cp.safetyConfigs[0].safetyParam |= TeslaSafetyFlags.COOP_STEERING.value
  return cp.as_reader()


def make_car_output(real_limit_error=0.0):
  output = car.CarOutput.new_message()
  output.actuatorsOutput.steeringAngleDeg = OUTPUT_ANGLE
  return output


def make_starpilot_car_control(real_limit_error=0.0):
  message = messaging.new_message("starpilotCarControl", valid=True)
  info = message.starpilotCarControl.steeringLimitInfo
  info.valid = True
  info.monoTime = SAMPLE_TIME_NANOS
  info.cooperativeOffsetDeg = 5.5
  info.modelLimitErrorDeg = real_limit_error
  info.combinedLimitErrorDeg = real_limit_error
  return message


def make_controls(car_output, starpilot_car_control, selfdrive_time_nanos, output_healthy=True):
  controls = Controls.__new__(Controls)
  controls.CP = make_car_params()
  controls.sm = PublishSubMaster(car_output, starpilot_car_control, selfdrive_time_nanos, output_healthy)
  controls.pm = CapturePubMaster()
  controls.curvature = 0.0
  controls.calibrated_pose = None
  controls.desired_curvature = 0.0
  controls.LoC = SimpleNamespace(
    long_control_state=car.CarControl.Actuators.LongControlState.off,
    pid=SimpleNamespace(p=0.0, i=0.0, f=0.0),
  )
  controls.LaC = SimpleNamespace()
  controls.starpilot_toggles = SimpleNamespace()
  controls.steer_limited_by_safety = False
  return controls


def run_publish(monkeypatch, replay, selfdrive_time_nanos, host_time_nanos=HOST_TIME_NANOS,
                output_healthy=True, real_limit_error=0.0):
  monkeypatch.setattr(controlsd, "REPLAY", replay, raising=False)
  monkeypatch.setattr(controlsd.time, "monotonic_ns", lambda: host_time_nanos)
  controls = make_controls(
    make_car_output(real_limit_error), make_starpilot_car_control(real_limit_error), selfdrive_time_nanos, output_healthy,
  )
  cc = car.CarControl.new_message()
  cc.enabled = True
  cc.latActive = True
  cc.actuators.steeringAngleDeg = REQUESTED_ANGLE
  lac_log = log.ControlsState.LateralAngleState.new_message()

  controls.publish(cc, lac_log)
  return controls


def test_replay_uses_current_poll_timestamp_for_fresh_diagnostics(monkeypatch):
  controls = run_publish(monkeypatch, True, FRESH_TIME_NANOS)

  assert not controls.steer_limited_by_safety


def test_replay_stale_diagnostics_still_use_legacy_fallback(monkeypatch):
  controls = run_publish(monkeypatch, True, STALE_TIME_NANOS)

  assert controls.steer_limited_by_safety


@pytest.mark.parametrize(("selfdrive_time_nanos", "expected_limited"), (
  (SAMPLE_TIME_NANOS + 100_000_000, False),
  (SAMPLE_TIME_NANOS + 100_000_001, True),
  (SAMPLE_TIME_NANOS - 1, True),
  (0, True),
))
def test_replay_publish_preserves_diagnostic_age_boundaries(monkeypatch, selfdrive_time_nanos, expected_limited):
  controls = run_publish(monkeypatch, True, selfdrive_time_nanos)

  assert controls.steer_limited_by_safety is expected_limited


def test_live_uses_monotonic_clock_instead_of_message_clock(monkeypatch):
  controls = run_publish(monkeypatch, False, FRESH_TIME_NANOS, host_time_nanos=STALE_TIME_NANOS)

  assert controls.steer_limited_by_safety


def test_unhealthy_car_output_still_uses_legacy_fallback(monkeypatch):
  controls = run_publish(monkeypatch, True, FRESH_TIME_NANOS, output_healthy=False)

  assert controls.steer_limited_by_safety


def test_replay_genuine_limiter_error_remains_visible(monkeypatch):
  controls = run_publish(monkeypatch, True, FRESH_TIME_NANOS, real_limit_error=3.0)

  assert controls.steer_limited_by_safety


@pytest.mark.parametrize("normal_active", [False, True])
@pytest.mark.parametrize("angle_control", [False, True])
def test_lateral_inactive_clears_previous_limit_feedback(normal_active, angle_control):
  controls = make_controls(make_car_output(), make_starpilot_car_control(), FRESH_TIME_NANOS)
  cp = controls.CP.as_builder()
  if not angle_control:
    cp.steerControlType = car.CarParams.SteerControlType.torque
    cp.lateralTuning.init("torque")
  controls.CP = cp.as_reader()
  state = log.SelfdriveState.new_message()
  state.active = normal_active
  controls.sm.messages["selfdriveState"] = state.as_reader()
  controls.steer_limited_by_safety = True
  cc = car.CarControl.new_message()
  cc.enabled = normal_active
  cc.latActive = False
  cc.actuators.steeringAngleDeg = REQUESTED_ANGLE
  lac_log = (log.ControlsState.LateralAngleState if angle_control else log.ControlsState.LateralTorqueState).new_message()

  controls.publish(cc, lac_log)

  assert not controls.steer_limited_by_safety


@pytest.mark.parametrize("sign", [-1, 1])
@pytest.mark.parametrize("requested,output,measured,pressed,speed,active,expected", [
  (120, 90, 90, False, 10, True, True),  # Controller command clipping during AOL.
  (120, 120, 90, False, 10, True, True),  # EPS undertracking without command clipping.
  (120, 120, 120, False, 10, True, False),
  (89, 89, 45, False, 10, True, False),
  (120, 90, 90, True, 10, True, False),
  (120, 90, 90, False, 0.5, True, True),
  (120, 90, 90, False, 10, False, False),
])
def test_ev9_aol_feedback_reaches_visible_audible_alert(sign, requested, output, measured, pressed, speed, active, expected):
  cp = HyundaiInterface.get_non_essential_params(HYUNDAI_CAR.KIA_EV9)
  car_output = make_car_output()
  car_output.actuatorsOutput.steeringAngleDeg = sign * output
  controls = make_controls(car_output, make_starpilot_car_control(), FRESH_TIME_NANOS)
  controls.CP = cp.as_reader()
  controls.sm.messages["selfdriveState"] = log.SelfdriveState.new_message().as_reader()
  cs = car.CarState.new_message()
  cs.canValid = True
  cs.vEgo = speed
  cs.steeringAngleDeg = sign * measured
  cs.steeringPressed = pressed
  controls.sm.messages["carState"] = cs.as_reader()
  controls.LaC = LatControlAngle(cp, None, 0.01)
  controls.curvature = sign * 0.015
  controls.starpilot_toggles = SimpleNamespace(goat_scream_alert=False)
  model = log.ModelDataV2.new_message()
  model.action.desiredCurvature = sign * 0.04
  controls.sm.messages["modelV2"] = model.as_reader()
  cc = car.CarControl.new_message()
  cc.enabled = False
  cc.latActive = active
  cc.actuators.steeringAngleDeg = sign * requested

  selfdrive = SelfdriveD.__new__(SelfdriveD)
  selfdrive.CP = cp.as_reader()
  selfdrive.sm = controls.sm
  selfdrive.starpilot_toggles = controls.starpilot_toggles
  selfdrive.events = Events()
  selfdrive.starpilot_events = Events(starpilot=True)
  selfdrive.state_machine = StateMachine()
  selfdrive.AM = AlertManager()
  selfdrive.starpilot_AM = AlertManager()
  selfdrive.personality = log.LongitudinalPersonality.standard
  selfdrive.is_metric = True
  selfdrive.last_steering_pressed_frame = 0
  selfdrive.last_steer_saturated_alert_time = 0.0
  vm = SimpleNamespace(get_steer_from_curvature=lambda *args: math.radians(sign * requested))

  for frame in range(300, 400):
    controls.sm.frame = frame
    _, _, lac_log = controls.LaC.update(active, cs, vm, SimpleNamespace(roll=0.0, angleOffsetDeg=0.0),
                                      controls.steer_limited_by_safety, 0.04, False, 0, None, model, controls.starpilot_toggles)
    controls.publish(cc, lac_log)
    controls.sm.messages["controlsState"] = controls.pm.sent["controlsState"].controlsState.as_reader()
    selfdrive.events.clear()
    selfdrive.starpilot_events.clear()
    selfdrive.update_steering_saturation_events(cs)
    selfdrive.enabled, selfdrive.active = selfdrive.state_machine.update(selfdrive.events, selfdrive.starpilot_events, active)
    selfdrive.update_alerts(cs)

  assert not selfdrive.enabled and not selfdrive.active
  assert not controls.sm["selfdriveState"].active
  assert (log.OnroadEvent.EventName.steerSaturated in selfdrive.events.names) is expected
  if expected:
    assert selfdrive.AM.current_alert.alert_text_1 == "Turn Exceeds Steering Limit"
    assert selfdrive.AM.current_alert.audible_alert == log.SelfdriveState.AudibleAlert.promptRepeat
  else:
    assert selfdrive.AM.current_alert.alert_text_1 == ""
    assert selfdrive.AM.current_alert.audible_alert == log.SelfdriveState.AudibleAlert.none

  # Deactivation clears both the feedback and its timer, rather than carrying an old warning into the next session.
  cc.latActive = False
  _, _, lac_log = controls.LaC.update(False, cs, vm, SimpleNamespace(roll=0.0, angleOffsetDeg=0.0),
                                    True, 0.04, True, 0, None, model, controls.starpilot_toggles)
  controls.publish(cc, lac_log)
  assert not controls.steer_limited_by_safety
  assert not lac_log.saturated
  assert controls.LaC.sat_time == 0
