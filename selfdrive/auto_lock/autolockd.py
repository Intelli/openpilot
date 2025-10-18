from __future__ import annotations

import logging
import time
from dataclasses import dataclass
from importlib import util
from pathlib import Path
from typing import Optional

import cereal.messaging as messaging
from cereal import log
from openpilot.common.params import Params

logger = logging.getLogger(__name__)

USE_CUSTOM_LOGFILE = True

OFF_STABLE_TIME_S = 1.0
LOCK_RETRY_COOLDOWN_S = 120.0
POLL_INTERVAL_S = 0.5


def _now() -> float:
  return time.monotonic()


def _normalize_region(value: Optional[str]) -> Optional[str]:
  if not value:
    return None
  return value.strip().upper() or None


@dataclass(frozen=True)
class _Creds:
  username: str
  password: str
  pin: str
  region: str
  vin: Optional[str]
  vehicle_id: Optional[str]
  language: Optional[str]


class AutoLockMonitor:
  def __init__(self) -> None:
    self.params = Params()
    self.sm = messaging.SubMaster(["carState", "pandaStates", "deviceState", "driverMonitoringState"])

    self.door_open: bool = False
    self.last_door_open_time: Optional[float] = None
    self.last_door_close_time: Optional[float] = None
    self.car_active: bool = False
    self.off_since: Optional[float] = None

    self.lock_attempted_at: Optional[float] = None
    self._client = None
    self._client_creds: Optional[_Creds] = None
    self._kia_lock_module = None

    self._missing_creds_logged_at: Optional[float] = None
    self._network_type = None
    self._awaiting_ignition_cycle = False
    self.door_open_after_off_time: Optional[float] = None
    self.door_close_after_off_time: Optional[float] = None
    self.seatbelt_unlatched: bool = False
    self._last_seatbelt_state: Optional[bool] = None
    self._last_driver_monitor_state: Optional[tuple] = None
    self.driver_present: bool = False
    self.car_voltage: Optional[float] = None
    self._last_logged_voltage: Optional[float] = None
    self.panda_power_save: Optional[bool] = None


  def run(self) -> None:
    while True:
      self.sm.update(int(POLL_INTERVAL_S * 1000))
      now = _now()

      if self.sm.updated["carState"]:
        self._handle_car_state(now)
      if self.sm.updated["pandaStates"]:
        self._handle_panda_state(now)
      if self.sm.updated["deviceState"]:
        self._handle_device_state()
      if self.sm.updated["driverMonitoringState"]:
        self._handle_driver_monitoring()

      self._evaluate(now)

  def _handle_car_state(self, now: float) -> None:
    cs = self.sm["carState"]
    door_open = bool(cs.doorOpen)
    seatbelt_unlatched = bool(getattr(cs, "seatbeltsAllUnlatched", getattr(cs, "seatbeltUnlatched", False)))

    if self._last_seatbelt_state is None or seatbelt_unlatched != self._last_seatbelt_state:
      logger.debug("Seatbelts all unlatched: %s", seatbelt_unlatched)
      self._last_seatbelt_state = seatbelt_unlatched
    self.seatbelt_unlatched = seatbelt_unlatched

    if door_open:
      if not self.door_open:
        logger.debug("Door transitioned open")
      self.last_door_open_time = now
      if self.off_since is not None:
        self.door_open_after_off_time = self.door_open_after_off_time or now
        if self.door_open_after_off_time == now:
          logger.debug("Door open recorded after ignition off at %.2f", now - self.off_since)
      self.lock_attempted_at = None
    elif self.door_open and not door_open:
      self.last_door_close_time = now
      logger.debug("Door transitioned closed")
      if self.off_since is not None:
        self.door_close_after_off_time = now
        logger.debug("Door close recorded after ignition off at %.2f", now - self.off_since)

    self.door_open = door_open

  def _handle_panda_state(self, now: float) -> None:
    panda_states = self.sm["pandaStates"]
    ignition_on = False
    for panda_state in panda_states:
      if panda_state.ignitionLine or panda_state.ignitionCan:
        ignition_on = True
        break

    if panda_states:
      voltage_raw = float(panda_states[0].voltage)
      voltage_v = voltage_raw / 1000.0 if voltage_raw > 1000.0 else voltage_raw
      if self._last_logged_voltage is None or abs(voltage_v - self._last_logged_voltage) >= 0.05:
        # logger.debug("Vehicle bus voltage: %.2f V", voltage_v)
        self._last_logged_voltage = voltage_v
      self.car_voltage = voltage_v

      power_save = bool(panda_states[0].powerSaveEnabled)
      if self.panda_power_save is None or power_save != self.panda_power_save:
        logger.debug("Panda power-save mode: %s", power_save)
      self.panda_power_save = power_save

    if ignition_on:
      if not self.car_active:
        logger.debug("Ignition became active")
      self.off_since = None
      self.car_active = True
      self._awaiting_ignition_cycle = False
    else:
      if self.car_active:
        logger.debug("Ignition became inactive")
        self.off_since = now
        self.door_open_after_off_time = now if self.door_open else None
        self.door_close_after_off_time = None
      elif self.off_since is None:
        self.off_since = now
      self.car_active = False

  def _evaluate(self, now: float) -> None:
    if self.car_active:
      return

    if self._awaiting_ignition_cycle:
      return

    if self.off_since is None:
      return

    if not self.seatbelt_unlatched:
      logger.debug("Skipping auto-lock: seatbelts still latched")
      return

    if (now - self.off_since) < OFF_STABLE_TIME_S:
      return

    doors_recent = self.door_open_after_off_time is not None
    doors_closed = (
      not self.door_open
      and self.door_close_after_off_time is not None
    )
    door_cycle_complete = (
      doors_recent
      and self.door_open_after_off_time >= self.off_since
      and (
        self.door_close_after_off_time is None
        or self.door_close_after_off_time >= self.off_since
      )
    )
    cooldown_ok = self.lock_attempted_at is None or (now - self.lock_attempted_at) >= LOCK_RETRY_COOLDOWN_S

    if not all([doors_recent, doors_closed, door_cycle_complete, cooldown_ok]):
      return

    creds = self._load_credentials(now)
    if creds is None:
      return

    client = self._ensure_client(creds)
    if client is None:
      return

    if not self._connectivity_available():
      logger.info("Skipping auto-lock: no network connectivity")
      return

    logger.info("Triggering auto-lock")
    self.lock_attempted_at = now
    try:
      client.lock()
      logger.info("Auto-lock command sent")
    except Exception as err:  # pylint: disable=broad-except
      logger.error("Auto-lock command failed: %s", err)
    finally:
      self._reset_cycle_state()

  def _load_credentials(self, now: float) -> Optional[_Creds]:
    username = self.params.get("AutoLockUsername", encoding="utf-8", block=False) or ""
    password = self.params.get("AutoLockPassword", encoding="utf-8", block=False) or ""
    pin = self.params.get("AutoLockPin", encoding="utf-8", block=False) or ""
    region_raw = self.params.get("AutoLockRegion", encoding="utf-8", block=False) or ""

    username = username.strip()
    password = password.strip()
    pin = pin.strip()
    region = _normalize_region(region_raw)

    if not username or not password or not pin or region is None:
      if self._missing_creds_logged_at is None or (now - self._missing_creds_logged_at) >= 300.0:
        logger.debug("Auto-lock credentials incomplete; skipping")
        self._missing_creds_logged_at = now
      return None

    language = "en"
    vin = None
    vehicle_id = None
    creds = _Creds(username, password, pin, region, vin, vehicle_id, language)
    self._missing_creds_logged_at = None
    return creds

  def _ensure_client(self, creds: _Creds):
    if self._client_creds != creds:
      module = self._get_kia_lock_module()
      if module is None:
        return None

      KiaCredentials = getattr(module, "KiaCredentials", None)
      KiaAutoLockClient = getattr(module, "KiaAutoLockClient", None)
      Region = getattr(module, "Region", None)
      if KiaCredentials is None or KiaAutoLockClient is None or Region is None:
        logger.error("Kia lock module missing required classes")
        return None

      logger.debug("Refreshing KiaAutoLockClient session")
      try:
        region_enum = Region[creds.region]
        kia_creds = KiaCredentials(
          username=creds.username,
          password=creds.password,
          pin=creds.pin,
          region=region_enum,
          vin=creds.vin,
          vehicle_id=creds.vehicle_id,
          language=creds.language,
        )
      except Exception as err:  # pylint: disable=broad-except
        logger.error("Failed to build Kia credentials: %s", err)
        return None

      try:
        self._client = KiaAutoLockClient(kia_creds)
      except Exception as err:  # pylint: disable=broad-except
        logger.error("Failed to initialise KiaAutoLockClient: %s", err)
        return None
      self._client_creds = creds

    return self._client

  def _get_kia_lock_module(self):
    if self._kia_lock_module is None:
      module_path = Path(__file__).resolve().parents[2] / "auto-lock" / "kia_lock.py"
      spec = util.spec_from_file_location("auto_lock_kia_lock", module_path)
      if spec is None or spec.loader is None:
        logger.error("Unable to locate kia_lock.py at %s", module_path)
        return None
      module = util.module_from_spec(spec)
      try:
        spec.loader.exec_module(module)
      except Exception as err:  # pylint: disable=broad-except
        logger.error("Failed to load kia_lock.py: %s", err)
        return None
      self._kia_lock_module = module
    return self._kia_lock_module

  def _handle_device_state(self) -> None:
    ds = self.sm["deviceState"]
    self._network_type = ds.networkType

  def _handle_driver_monitoring(self) -> None:
    dms = self.sm["driverMonitoringState"]
    face_detected = bool(getattr(dms, "faceDetected", False))
    aware = not bool(getattr(dms, "isDistracted", False))
    awareness_status = float(getattr(dms, "awarenessStatus", 0.0) or 0.0)
    awareness_active = float(getattr(dms, "awarenessActive", 0.0) or 0.0)
    awareness_passive = float(getattr(dms, "awarenessPassive", 0.0) or 0.0)
    distractions = int(getattr(dms, "distractedType", 0) or 0)
    hi_std_count = int(getattr(dms, "hiStdCount", 0) or 0)

    driver_present = face_detected or awareness_status > 0.0

    new_state = (
      face_detected,
      aware,
      driver_present,
      round(awareness_status, 3),
      round(awareness_active, 3),
      round(awareness_passive, 3),
      distractions,
      hi_std_count,
    )

    if self._last_driver_monitor_state != new_state:
      logger.debug(
        "Driver monitoring: present=%s face=%s aware=%s aware_status=%.3f (act=%.3f pas=%.3f) distracted_type=0x%X hi_std=%d",
        driver_present,
        face_detected,
        aware,
        awareness_status,
        awareness_active,
        awareness_passive,
        distractions,
        hi_std_count,
      )
      self._last_driver_monitor_state = new_state

    self.driver_present = driver_present

  def _connectivity_available(self) -> bool:
    network_type = getattr(self, "_network_type", None)
    if network_type is None:
      return False
    allowed_networks = {
      log.DeviceState.NetworkType.wifi,
      log.DeviceState.NetworkType.cell2G,
      log.DeviceState.NetworkType.cell3G,
      log.DeviceState.NetworkType.cell4G,
      log.DeviceState.NetworkType.cell5G,
      log.DeviceState.NetworkType.ethernet,
    }
    return network_type in allowed_networks or network_type == log.DeviceState.NetworkType.none

  def _reset_cycle_state(self) -> None:
    self.last_door_open_time = None
    self.last_door_close_time = None
    self.door_open_after_off_time = None
    self.door_close_after_off_time = None
    self.off_since = None
    self._awaiting_ignition_cycle = True


def main() -> None:
  logging.basicConfig(level=logging.INFO)
  if USE_CUSTOM_LOGFILE:
    log_dir = Path("/data/openpilot/auto-lock")
    log_dir.mkdir(parents=True, exist_ok=True)
    logfile = log_dir / "autolock.log"
    try:
      logfile.unlink()
    except FileNotFoundError:
      pass
    except OSError as err:
      logger.warning("Unable to remove existing log file %s: %s", logfile, err)
    file_handler = logging.FileHandler(logfile, mode="w", encoding="utf-8")
    file_handler.setFormatter(logging.Formatter("%(asctime)s %(levelname)s %(name)s: %(message)s"))
    logger.addHandler(file_handler)
    logger.setLevel(logging.DEBUG)
  monitor = AutoLockMonitor()
  monitor.run()


if __name__ == "__main__":
  main()
