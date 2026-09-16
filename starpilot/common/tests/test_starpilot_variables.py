from types import SimpleNamespace

import pytest

from openpilot.starpilot.common import starpilot_variables as spv


def test_legacy_volt_stock_acc_models_share_sng_and_auto_hold_scope():
  assert spv.LEGACY_VOLT_STOCK_ACC_CARS == {
    "CHEVROLET_VOLT",
    "CHEVROLET_VOLT_2019",
    "CHEVROLET_VOLT_ASCM",
    "CHEVROLET_VOLT_CAMERA",
  }


def test_tss2_toyota_keeps_main_aol_button_path():
  assert spv._lkas_allowed_for_aol("toyota", 0, []) is False


def test_hyundai_and_honda_keep_lkas_aol_button_path():
  assert spv._lkas_allowed_for_aol("honda", 0, []) is True
  assert spv._lkas_allowed_for_aol("hyundai", spv.HyundaiFlags.CANFD, []) is True


def test_ford_can_map_lkas_button_to_aol():
  assert spv._lkas_allowed_for_aol("ford", 0, []) is True


def test_volvo_aol_is_held_off_until_pscm_sequence_is_validated():
  assert spv.always_on_lateral_available(SimpleNamespace(brand="volvo")) is False
  assert spv.always_on_lateral_available(SimpleNamespace(brand="honda")) is True


def test_explicit_main_cruise_aol_mapping_is_not_disabled_by_longitudinal_gate():
  aol_button = spv.BUTTON_FUNCTIONS["AOL_TOGGLE"]

  # An explicit Galaxy mapping remains valid on both longitudinal paths.
  assert spv._main_cruise_aol_allowed(aol_button) is True


def test_jeep_brake_hold_scope_is_grand_cherokee_only():
  assert {str(car) for car in spv.CHRYSLER_JEEPS} == {
    "JEEP_GRAND_CHEROKEE",
    "JEEP_GRAND_CHEROKEE_2019",
  }


def test_get_starpilot_toggles_uses_last_non_empty_broadcast(monkeypatch):
  params = SimpleNamespace(get_bool=lambda _key: False)
  monkeypatch.setattr(spv.get_starpilot_toggles, "_params", params, raising=False)
  monkeypatch.delattr(spv.get_starpilot_toggles, "_last_toggles_text", raising=False)

  payload = '{"always_on_lateral": true, "vision_speed_limit_detection": true}'
  sm_with_toggles = {"starpilotPlan": SimpleNamespace(starpilotToggles=payload)}
  sm_without_toggles = {"starpilotPlan": SimpleNamespace(starpilotToggles="")}

  first = spv.get_starpilot_toggles(sm_with_toggles)
  second = spv.get_starpilot_toggles(sm_without_toggles)

  assert first.always_on_lateral is True
  assert second.always_on_lateral is True
  assert second.vision_speed_limit_detection is True


def test_get_starpilot_toggles_uses_persisted_force_torque_request(monkeypatch):
  params = SimpleNamespace(get_bool=lambda key: key == "ForceTorqueController", get=lambda _key: None)
  monkeypatch.setattr(spv.get_starpilot_toggles, "_params", params, raising=False)

  payload = '{"force_torque_controller": false}'
  toggles = spv.get_starpilot_toggles(
    {"starpilotPlan": SimpleNamespace(starpilotToggles=payload)},
    read_persisted_force_params=True,
  )

  assert toggles.force_torque_controller is True


def test_get_starpilot_toggles_realtime_path_does_not_read_persisted_force_params(monkeypatch):
  class UnexpectedParamsRead:
    def get_bool(self, key):
      raise AssertionError(f"unexpected persisted param read: {key}")

  monkeypatch.setattr(spv.get_starpilot_toggles, "_params", UnexpectedParamsRead(), raising=False)

  payload = '{"force_offroad": false, "force_onroad": true, "force_torque_controller": false}'
  toggles = spv.get_starpilot_toggles({"starpilotPlan": SimpleNamespace(starpilotToggles=payload)})

  assert toggles.force_offroad is False
  assert toggles.force_onroad is True
  assert toggles.force_torque_controller is False


def test_get_starpilot_toggles_uses_live_rivian_angle_request(monkeypatch):
  params = SimpleNamespace(get_bool=lambda key: key == "RivianAngleControl", get=lambda _key: None)
  monkeypatch.setattr(spv.get_starpilot_toggles, "_params", params, raising=False)

  payload = '{"rivian_angle_control": false}'
  toggles = spv.get_starpilot_toggles(
    {"starpilotPlan": SimpleNamespace(starpilotToggles=payload)},
    read_persisted_force_params=True,
  )

  assert toggles.rivian_angle_control is True


@pytest.mark.parametrize("broadcast_force", [False, True])
def test_startup_manual_ev9_selection_overrides_stale_broadcast_without_mutating_it(monkeypatch, broadcast_force):
  import json

  payload = json.dumps({"force_fingerprint": broadcast_force, "car_model": "MOCK", "force_torque_controller": False})
  sm = {"starpilotPlan": SimpleNamespace(starpilotToggles=payload)}
  params = SimpleNamespace(get_bool=lambda key: key == "ForceFingerprint", get=lambda key: "KIA_EV9" if key == "CarModel" else None)
  monkeypatch.setattr(spv.get_starpilot_toggles, "_params", params, raising=False)
  monkeypatch.delattr(spv.get_starpilot_toggles, "_last_toggles_text", raising=False)
  spv.process_starpilot_toggles.cache_clear()

  broadcast = spv.get_starpilot_toggles(sm)
  startup = spv.get_starpilot_toggles(sm, read_persisted_force_params=True)
  assert startup.force_fingerprint is True
  assert startup.car_model == "KIA_EV9"
  assert startup is not broadcast

  def unexpected_read(key):
    raise AssertionError(f"unexpected realtime parameter read: {key}")

  params.get = params.get_bool = unexpected_read
  realtime = spv.get_starpilot_toggles(sm)
  assert realtime.force_fingerprint is broadcast_force
  assert realtime.car_model == "MOCK"


@pytest.mark.parametrize("selected,force,expected_force,expected_model", [
  ("KIA_EV9", False, False, "STALE_MODEL"),
  (None, True, False, "STALE_MODEL"),
  ("", True, False, "STALE_MODEL"),
  ("MOCK", True, False, "STALE_MODEL"),
  (b"MOCK", True, False, "STALE_MODEL"),
  (b"KIA_EV9", True, True, "KIA_EV9"),
  *[(old, True, True, new) for old, new in spv.LEGACY_CARMODEL_MIGRATIONS.items()],
])
def test_startup_fingerprint_selection_gating_and_normalization(monkeypatch, selected, force, expected_force, expected_model):
  params = SimpleNamespace(get_bool=lambda key: force if key == "ForceFingerprint" else False,
                           get=lambda key: selected if key == "CarModel" else None)
  monkeypatch.setattr(spv.get_starpilot_toggles, "_params", params, raising=False)
  monkeypatch.delattr(spv.get_starpilot_toggles, "_last_toggles_text", raising=False)
  payload = '{"force_fingerprint": true, "car_model": "STALE_MODEL"}'
  toggles = spv.get_starpilot_toggles({"starpilotPlan": SimpleNamespace(starpilotToggles=payload)}, read_persisted_force_params=True)
  assert toggles.force_fingerprint is expected_force
  assert toggles.car_model == expected_model


def test_startup_refreshes_persisted_selection_with_inherited_last_broadcast(monkeypatch):
  values = {"CarModel": "KIA_EV9", "ForceFingerprint": True}
  params = SimpleNamespace(get_bool=lambda key: bool(values.get(key, False)), get=lambda key: values.get(key))
  monkeypatch.setattr(spv.get_starpilot_toggles, "_params", params, raising=False)
  payload = '{"force_fingerprint": false, "car_model": "MOCK"}'
  monkeypatch.setattr(spv.get_starpilot_toggles, "_last_toggles_text", payload, raising=False)
  # The default SubMaster remains empty in a forked card process. No update() is called.
  assert not spv.get_starpilot_toggles.__defaults__[0]["starpilotPlan"].starpilotToggles
  first = spv.get_starpilot_toggles(read_persisted_force_params=True)
  assert first.force_fingerprint is True
  assert first.car_model == "KIA_EV9"

  values["CarModel"] = "HYUNDAI_IONIQ_6"
  second = spv.get_starpilot_toggles(read_persisted_force_params=True)
  assert second.force_fingerprint is True
  assert second.car_model == "HYUNDAI_IONIQ_6"
  assert first.car_model == "KIA_EV9"

  values["ForceFingerprint"] = False
  third = spv.get_starpilot_toggles(read_persisted_force_params=True)
  assert third.force_fingerprint is False
  assert third.car_model == "MOCK"
  assert second.force_fingerprint is True


def test_startup_without_broadcast_refreshes_cached_fallback_selection(monkeypatch):
  fallback = SimpleNamespace(force_fingerprint=False, car_model="MOCK")
  monkeypatch.setattr(spv, "StarPilotVariables", lambda: SimpleNamespace(starpilot_toggles=fallback))
  monkeypatch.delattr(spv.get_starpilot_toggles, "_last_toggles_text", raising=False)
  params = SimpleNamespace(get_bool=lambda key: key == "ForceFingerprint", get=lambda key: "KIA_EV9" if key == "CarModel" else None)
  monkeypatch.setattr(spv.get_starpilot_toggles, "_params", params, raising=False)
  spv.process_starpilot_toggles.cache_clear()
  try:
    # Simulate the fallback object cached by manager before a child starts.
    assert spv.process_starpilot_toggles("") is fallback
    startup = spv.get_starpilot_toggles(read_persisted_force_params=True)
    assert startup.force_fingerprint is True
    assert startup.car_model == "KIA_EV9"
    assert fallback.force_fingerprint is False
    assert fallback.car_model == "MOCK"
  finally:
    spv.process_starpilot_toggles.cache_clear()


@pytest.mark.parametrize("candidate", [None, "MOCK"])
def test_startup_manual_ev9_selection_reaches_real_car_interface(monkeypatch, candidate):
  from opendbc.car import car_helpers, gen_empty_fingerprint, structs
  from opendbc.car.hyundai.values import CAR, HyundaiFlags, HyundaiSafetyFlags
  from opendbc.car.vin import VIN_UNKNOWN

  params = SimpleNamespace(get_bool=lambda key: key == "ForceFingerprint", get=lambda key: "KIA_EV9" if key == "CarModel" else None,
                           put_nonblocking=lambda _key, _value: None)
  monkeypatch.setattr(spv.get_starpilot_toggles, "_params", params, raising=False)
  payload = '{"force_fingerprint": false, "car_model": "MOCK", "disable_openpilot_long": false}'
  toggles = spv.get_starpilot_toggles({"starpilotPlan": SimpleNamespace(starpilotToggles=payload)}, read_persisted_force_params=True)
  monkeypatch.setattr(car_helpers, "fingerprint", lambda *_args: (
    candidate, gen_empty_fingerprint(), VIN_UNKNOWN, [], structs.CarParams.FingerprintSource.can, True,
  ))
  interface = car_helpers.get_car(None, None, None, False, False, params, starpilot_toggles=toggles)
  assert interface.CP.carFingerprint == CAR.KIA_EV9
  assert interface.CP.steerControlType == structs.CarParams.SteerControlType.angle
  assert interface.CP.flags & HyundaiFlags.CANFD_ANGLE_STEERING
  safety_param = interface.CP.safetyConfigs[-1].safetyParam
  for flag in (HyundaiSafetyFlags.CANFD_EV9, HyundaiSafetyFlags.CANFD_ANGLE_STEERING, HyundaiSafetyFlags.EV_GAS):
    assert safety_param & flag
  assert interface.CC.BASELINE_VM.l == pytest.approx(3.10)
  assert interface.CC.BASELINE_VM.sR == pytest.approx(16.0)


def test_startup_uses_compiled_ev9_defaults_without_saved_selection(monkeypatch, tmp_path):
  params = spv.Params(str(tmp_path), return_defaults=True)
  raw_params = spv.Params(str(tmp_path))
  assert raw_params.get("ForceFingerprint") is None
  assert raw_params.get("CarModel") is None
  monkeypatch.setattr(spv.get_starpilot_toggles, "_params", params, raising=False)
  payload = '{"force_fingerprint": false, "car_model": "MOCK"}'
  toggles = spv.get_starpilot_toggles({"starpilotPlan": SimpleNamespace(starpilotToggles=payload)}, read_persisted_force_params=True)
  assert toggles.force_fingerprint is True
  assert toggles.car_model == "KIA_EV9"
  assert raw_params.get("ForceFingerprint") is None
  assert raw_params.get("CarModel") is None


class _FakeParams:
  def __init__(self, floats=None, ints=None, bools=None):
    self.floats = dict(floats or {})
    self.ints = dict(ints or {})
    self.bools = dict(bools or {})

  def get_float(self, key):
    return float(self.floats.get(key, 0.0))

  def get_int(self, key):
    return int(self.ints.get(key, 0))

  def get_bool(self, key):
    return bool(self.bools.get(key, False))

  def get(self, key):
    if key in self.floats:
      return self.floats[key]
    if key in self.ints:
      return self.ints[key]
    return self.bools.get(key)

  def put_float(self, key, value):
    self.floats[key] = float(value)

  def put_int(self, key, value):
    self.ints[key] = int(value)

  def put_bool(self, key, value):
    self.bools[key] = bool(value)

  def remove(self, key):
    self.floats.pop(key, None)
    self.ints.pop(key, None)
    self.bools.pop(key, None)


def test_ford_lkas_default_migrates_from_experimental_to_aol_toggle():
  params = _FakeParams(ints={"LKASButtonControl": spv.BUTTON_FUNCTIONS["EXPERIMENTAL_MODE"]})

  assert spv.migrate_ford_lkas_button_default("ford", params) is True
  assert params.get_int("LKASButtonControl") == spv.BUTTON_FUNCTIONS["AOL_TOGGLE"]
  assert params.get_bool(spv.FORD_LKAS_MIGRATION_KEY) is True

  params.put_int("LKASButtonControl", spv.BUTTON_FUNCTIONS["EXPERIMENTAL_MODE"])
  assert spv.migrate_ford_lkas_button_default("ford", params) is False
  assert params.get_int("LKASButtonControl") == spv.BUTTON_FUNCTIONS["EXPERIMENTAL_MODE"]


def test_ev9_main_aol_migration_is_once_only():
  params = _FakeParams(ints={"LKASButtonControl": 9, "MainCruiseButtonControl": 0}, bools={"AlwaysOnLateral": True})
  assert spv.migrate_ev9_main_cruise_aol(spv.HYUNDAI_CAR.KIA_EV9, params)
  assert params.get_int("MainCruiseButtonControl") == 9
  params.put_int("MainCruiseButtonControl", 0)
  assert not spv.migrate_ev9_main_cruise_aol(spv.HYUNDAI_CAR.KIA_EV9, params)
  assert params.get_int("MainCruiseButtonControl") == 0


@pytest.mark.parametrize(("model", "aol", "lkas", "main"), [
  ("OTHER_CAR", True, 9, 0), ("KIA_EV9", False, 9, 0), ("KIA_EV9", True, 5, 0), ("KIA_EV9", True, 9, 10),
])
def test_ev9_main_aol_migration_preserves_other_choices(model, aol, lkas, main):
  params = _FakeParams(ints={"LKASButtonControl": lkas, "MainCruiseButtonControl": main}, bools={"AlwaysOnLateral": aol})
  spv.migrate_ev9_main_cruise_aol(model, params)
  assert params.get_int("MainCruiseButtonControl") == main


def test_ford_lkas_default_migration_preserves_custom_mapping():
  params = _FakeParams(ints={"LKASButtonControl": spv.BUTTON_FUNCTIONS["BOOKMARK"]})

  assert spv.migrate_ford_lkas_button_default("ford", params) is True
  assert params.get_int("LKASButtonControl") == spv.BUTTON_FUNCTIONS["BOOKMARK"]


def test_ford_lkas_default_migration_ignores_other_brands():
  params = _FakeParams(ints={"LKASButtonControl": spv.BUTTON_FUNCTIONS["EXPERIMENTAL_MODE"]})

  assert spv.migrate_ford_lkas_button_default("honda", params) is False
  assert params.get_int("LKASButtonControl") == spv.BUTTON_FUNCTIONS["EXPERIMENTAL_MODE"]
  assert params.get_bool(spv.FORD_LKAS_MIGRATION_KEY) is False


def test_sync_reboot_marker_uses_manager_guard(tmp_path):
  params = _FakeParams()
  marker = tmp_path / "cache" / "use_HD"

  assert spv.sync_reboot_marker(marker, True, params) is True
  assert marker.is_file()
  assert params.get_bool("DoReboot") is True

  params.put_bool("DoReboot", False)
  assert spv.sync_reboot_marker(marker, True, params) is False
  assert params.get_bool("DoReboot") is False

  assert spv.sync_reboot_marker(marker, False, params) is True
  assert not marker.exists()
  assert params.get_bool("DoReboot") is True


def test_sync_stock_param_does_not_stomp_existing_custom_value_when_stock_missing():
  params = _FakeParams({"SteerDelay": 0.35, "SteerDelayStock": 0.0})
  variables = object.__new__(spv.StarPilotVariables)
  variables.params = params

  variables._sync_stock_param("SteerDelay", "SteerDelayStock", 0.10)

  assert params.get_float("SteerDelay") == 0.35
  assert params.get_float("SteerDelayStock") == 0.10


def test_steer_delay_mode_migration_converts_untouched_stock_value_to_full_auto_delay():
  params = _FakeParams({"SteerDelay": 0.11, "SteerDelayStock": 0.11})
  variables = object.__new__(spv.StarPilotVariables)
  variables.params = params
  variables.params_raw = params

  variables._migrate_steer_delay_mode(0.11)

  assert params.get_bool("UseAutoSteerDelay") is True
  assert params.get_float("SteerDelay") == 0.31
  assert params.get_bool(spv.STEER_DELAY_MODE_MIGRATION_KEY) is True


def test_steer_delay_mode_migration_preserves_existing_manual_full_delay():
  params = _FakeParams({"SteerDelay": 0.35, "SteerDelayStock": 0.11})
  variables = object.__new__(spv.StarPilotVariables)
  variables.params = params
  variables.params_raw = params

  variables._migrate_steer_delay_mode(0.11)

  assert params.get_bool("UseAutoSteerDelay") is False
  assert params.get_float("SteerDelay") == 0.35
  assert params.get_bool(spv.STEER_DELAY_MODE_MIGRATION_KEY) is True


def test_cancel_button_migration_copies_distance_actions_once():
  params = _FakeParams(
    ints={
      "DistanceButtonControl": 8,
      "LongDistanceButtonControl": 4,
      "VeryLongDistanceButtonControl": 7,
    },
    bools={"RemapCancelToDistance": True},
  )

  assert spv.migrate_cancel_button_controls(params) is True
  assert params.get_int("CancelButtonControl") == 8
  assert params.get_int("LongCancelButtonControl") == 4
  assert params.get_int("VeryLongCancelButtonControl") == 7
  assert params.get_bool(spv.CANCEL_BUTTON_MIGRATION_KEY) is True

  params.put_int("DistanceButtonControl", 1)
  params.put_int("CancelButtonControl", 3)

  assert spv.migrate_cancel_button_controls(params) is False
  assert params.get_int("CancelButtonControl") == 3


def test_runtime_values_ignore_legacy_tuning_level_metadata():
  params = _FakeParams(ints={"LKASButtonControl": spv.BUTTON_FUNCTIONS["AOL_TOGGLE"]})
  variables = object.__new__(spv.StarPilotVariables)
  variables.params = params
  variables.default_values = {"LKASButtonControl": str(spv.BUTTON_FUNCTIONS["EXPERIMENTAL_MODE"])}

  assert variables.get_value("LKASButtonControl", cast=int) == spv.BUTTON_FUNCTIONS["AOL_TOGGLE"]
  assert variables.get_button_function("LKASButtonControl") == spv.BUTTON_FUNCTIONS["AOL_TOGGLE"]


def test_missing_bounded_value_uses_explicit_default():
  variables = object.__new__(spv.StarPilotVariables)
  variables.params = _FakeParams()
  variables.default_values = {}

  value = variables.get_value("LaneChangeCloseGapSeconds", cast=float, default=1.0, min=0.5, max=3.0)

  assert value == 1.0


@pytest.mark.parametrize("speed_mph", [0, 10, 100])
def test_aol_brake_slider_value_round_trips_and_converts_to_mps(monkeypatch, tmp_path, speed_mph):
  params_cls = spv.Params

  def isolated_params(_path=None, memory=False, return_defaults=False):
    return params_cls(str(tmp_path / ("memory" if memory else "params")), return_defaults=return_defaults)

  monkeypatch.setattr(spv, "Params", isolated_params)
  params = isolated_params()
  params.put_bool("AlwaysOnLateral", True)
  params.put_int("PauseAOLOnBrake", speed_mph)
  assert params.get_int("PauseAOLOnBrake") == speed_mph

  variables = spv.StarPilotVariables()
  assert variables.starpilot_toggles.always_on_lateral_pause_speed == pytest.approx(speed_mph * spv.CV.MPH_TO_MS)


def test_disabled_conditional_experimental_toggles_are_off(monkeypatch, tmp_path):
  params_cls = spv.Params

  def isolated_params(_path=None, memory=False, return_defaults=False):
    return params_cls(str(tmp_path / ("memory" if memory else "params")), return_defaults=return_defaults)

  monkeypatch.setattr(spv, "Params", isolated_params)
  params = isolated_params()
  params.put_bool("ConditionalExperimental", True)
  params.put_bool("CEStopLights", False)
  params.put_float("CEModelStopTime", 0.0)

  variables = spv.StarPilotVariables()
  toggles = variables.starpilot_toggles

  assert variables.params_raw.get_float("CEModelStopTime") == 0.0
  assert toggles.conditional_experimental_mode is False
  assert toggles.conditional_curves is False
  assert toggles.conditional_curves_lead is False
  assert toggles.conditional_lead is False
  assert toggles.conditional_open_road is False
  assert toggles.conditional_slower_lead is False
  assert toggles.conditional_stopped_lead is False
  assert toggles.conditional_limit == 0.0
  assert toggles.conditional_limit_lead == 0.0
  assert toggles.conditional_model_stop_time == 0.0
  assert toggles.conditional_signal == 0.0
  assert toggles.conditional_signal_lane_detection is False


def test_big_ui_exposes_developer_toggles_without_persisting_developer_ui(monkeypatch, tmp_path):
  params_cls = spv.Params

  def isolated_params(_path=None, memory=False, return_defaults=False):
    return params_cls(str(tmp_path / ("memory" if memory else "params")), return_defaults=return_defaults)

  monkeypatch.setattr(spv, "Params", isolated_params)
  monkeypatch.setattr(spv.HARDWARE, "get_device_type", lambda: "tici")
  monkeypatch.delenv("BIG", raising=False)

  variables = spv.StarPilotVariables()

  assert variables.starpilot_toggles.developer_ui is True
  assert variables.params_raw.get_bool("DeveloperUI") is False


def test_device_shutdown_hours_convert_directly_to_seconds():
  assert spv.device_shutdown_seconds(1) == 60 * 60
  assert spv.device_shutdown_seconds(6) == 6 * 60 * 60
  assert spv.device_shutdown_seconds(0) == 60 * 60
  assert spv.device_shutdown_seconds(31) == 30 * 60 * 60


def test_compiled_terms_and_shutdown_defaults_preserve_saved_preferences(tmp_path):
  from openpilot.system.version import terms_version

  params = spv.Params(str(tmp_path), return_defaults=True)
  raw_params = spv.Params(str(tmp_path))
  assert raw_params.get("HasAcceptedTerms") is None
  assert raw_params.get("DeviceShutdown") is None
  assert params.get("HasAcceptedTerms") == terms_version == "2"
  assert params.get_int("DeviceShutdown") == spv.DEVICE_SHUTDOWN_DEFAULT_HOURS == 2
  assert spv.device_shutdown_seconds(params.get_int("DeviceShutdown")) == 2 * 3600

  raw_params.put("HasAcceptedTerms", "0")
  raw_params.put_int("DeviceShutdown", 6)
  assert params.get("HasAcceptedTerms") == "0"
  assert spv.device_shutdown_seconds(params.get_int("DeviceShutdown")) == 6 * 3600


@pytest.mark.parametrize("metric", [False, True])
@pytest.mark.parametrize("saved_speed", [None, 25])
def test_lane_change_threshold_stays_in_mph_when_display_units_change(monkeypatch, tmp_path, metric, saved_speed):
  from openpilot.common.constants import CV

  params_cls = spv.Params

  def isolated_params(_path=None, memory=False, return_defaults=False):
    return params_cls(str(tmp_path / ("memory" if memory else "params")), return_defaults=return_defaults)

  monkeypatch.setattr(spv, "Params", isolated_params)
  monkeypatch.setattr(spv, "HD_PATH", tmp_path / "use_HD")
  monkeypatch.setattr(spv, "KONIK_PATH", tmp_path / "use_konik")
  params = isolated_params()
  params.put_bool("IsMetric", metric)
  params.put_bool("LaneChanges", True)
  if saved_speed is not None:
    params.put_float("MinimumLaneChangeSpeed", saved_speed)
  variables = spv.StarPilotVariables()

  for display_metric in (metric, not metric, metric):
    params.put_bool("IsMetric", display_metric)
    variables.update()
    assert variables.starpilot_toggles.is_metric is display_metric
    assert variables.starpilot_toggles.minimum_lane_change_speed == pytest.approx((saved_speed or 20) * CV.MPH_TO_MS)
    assert variables.starpilot_toggles.device_shutdown_time == 2 * 3600


def test_favorite_button_flags_map_to_three_slots():
  toggle = SimpleNamespace()

  spv.StarPilotVariables.set_favorite_button_flags(toggle, "lkas", spv.BUTTON_FUNCTIONS["FAVORITE_2"])

  assert toggle.favorite_1_via_lkas is False
  assert toggle.favorite_2_via_lkas is True
  assert toggle.favorite_3_via_lkas is False


def test_set_speed_limit_available_on_openpilot_longitudinal():
  assert spv.set_speed_limit_available(openpilot_longitudinal=True, has_cc_long=False, pcm_cruise_speed=True) is True


def test_set_speed_limit_available_on_gm_helper_path():
  assert spv.set_speed_limit_available(openpilot_longitudinal=False, has_cc_long=True, pcm_cruise_speed=True) is True


def test_set_speed_limit_available_on_redneck_helper_path():
  assert spv.set_speed_limit_available(openpilot_longitudinal=False, has_cc_long=False, pcm_cruise_speed=False) is True


def test_set_speed_limit_unavailable_on_stock_pcm_without_helper():
  assert spv.set_speed_limit_available(openpilot_longitudinal=False, has_cc_long=False, pcm_cruise_speed=True) is False


def test_speed_limit_controller_available_on_openpilot_longitudinal_or_redneck():
  assert spv.speed_limit_controller_available(openpilot_longitudinal=True, redneck_cruise=False) is True
  assert spv.speed_limit_controller_available(openpilot_longitudinal=False, redneck_cruise=True) is True


def test_toyota_pcm_cruise_uses_hardware_reverse_instead_of_software_intervals():
  assert spv.software_cruise_intervals_available(True, "toyota", True, True, True) is False
  assert spv.reverse_cruise_available(True, "toyota", True) is True


def test_non_toyota_software_cruise_keeps_custom_intervals():
  assert spv.software_cruise_intervals_available(True, "hyundai", False, True, True) is True
  assert spv.reverse_cruise_available(True, "hyundai", False) is False
  assert spv.speed_limit_controller_available(openpilot_longitudinal=False, redneck_cruise=False) is False
