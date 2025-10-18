from __future__ import annotations

import copy
import logging
import time
from dataclasses import dataclass
from importlib import util
from pathlib import Path
from typing import Any, Dict, Optional

import cereal.messaging as messaging
from cereal import log
from openpilot.common.params import Params

logger = logging.getLogger(__name__)

USE_CUSTOM_LOGFILE = True

OFF_STABLE_TIME_S = 1.0
LOCK_RETRY_COOLDOWN_S = 120.0
POLL_INTERVAL_S = 1.0
STATUS_MONITOR_TIMEOUT_S = 300.0
STATUS_POLL_SCHEDULE = (
  (15.0, 1.5),
  (60.0, 3.0),
  (150.0, 6.0),
  (STATUS_MONITOR_TIMEOUT_S, 10.0),
)


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
    self.sm = messaging.SubMaster(["carState", "pandaStates", "deviceState"])

    self.car_active: bool = False
    self.off_since: Optional[float] = None

    self.lock_attempted_at: Optional[float] = None
    self._lock_client = None
    self._lock_client_creds: Optional[_Creds] = None
    self._status_client = None
    self._status_client_creds: Optional[_Creds] = None
    self._kia_lock_module = None
    self._kia_status_module = None
    self._status_monitor_active = False
    self._status_monitor_started_at: Optional[float] = None
    self._next_status_poll_at: Optional[float] = None
    self._door_seen_open_remotely = False

    self._missing_creds_logged_at: Optional[float] = None
    self._network_type = None
    self._awaiting_ignition_cycle = False
    self.seatbelt_unlatched: bool = False
    self._last_seatbelt_state: Optional[bool] = None
    self._last_status_snapshot: Optional[Dict[str, Any]] = None

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

      self._evaluate(now)

  def _handle_car_state(self, _: float) -> None:
    cs = self.sm["carState"]
    seatbelt_unlatched = bool(getattr(cs, "seatbeltUnlatched", False))

    if self._last_seatbelt_state is None or seatbelt_unlatched != self._last_seatbelt_state:
      logger.debug("Driver seatbelt unlatched: %s", seatbelt_unlatched)
      self._last_seatbelt_state = seatbelt_unlatched
    self.seatbelt_unlatched = seatbelt_unlatched

  def _handle_panda_state(self, now: float) -> None:
    panda_states = self.sm["pandaStates"]
    ignition_on = False
    for panda_state in panda_states:
      if panda_state.ignitionLine or panda_state.ignitionCan:
        ignition_on = True
        break

    if ignition_on:
      if not self.car_active:
        logger.debug("Ignition became active")
      self.off_since = None
      self.car_active = True
      self._awaiting_ignition_cycle = False
      self._stop_status_monitor(reset_wait=False)
    else:
      if self.car_active:
        logger.debug("Ignition became inactive")
        self.off_since = now
        self.lock_attempted_at = None
        self._stop_status_monitor(reset_wait=False)
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

    if (now - self.off_since) < OFF_STABLE_TIME_S:
      return

    if not self._status_monitor_active:
      self._start_status_monitor(now)

    self._process_status_monitor(now)

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

  def _ensure_lock_client(self, creds: _Creds):
    if self._lock_client_creds != creds:
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
        self._lock_client = KiaAutoLockClient(kia_creds)
      except Exception as err:  # pylint: disable=broad-except
        logger.error("Failed to initialise KiaAutoLockClient: %s", err)
        return None
      self._lock_client_creds = creds

    return self._lock_client

  def _stop_status_monitor(self, *, reset_wait: bool) -> None:
    if self._status_monitor_active:
      logger.debug("Auto-lock status monitor stopped (reset=%s)", reset_wait)
    self._status_monitor_active = False
    self._status_monitor_started_at = None
    self._next_status_poll_at = None
    self._door_seen_open_remotely = False
    self._last_status_snapshot = None
    if reset_wait:
      self._awaiting_ignition_cycle = True

  def _start_status_monitor(self, now: float) -> None:
    self._status_monitor_active = True
    self._status_monitor_started_at = now
    self._next_status_poll_at = now
    self._door_seen_open_remotely = False
    logger.debug("Auto-lock status monitor started")

  def _process_status_monitor(self, now: float) -> None:
    if not self._status_monitor_active or self._status_monitor_started_at is None:
      return

    elapsed = now - self._status_monitor_started_at

    if elapsed >= STATUS_MONITOR_TIMEOUT_S:
      logger.info("Auto-lock polling timed out after %.0f seconds; forcing lock command", STATUS_MONITOR_TIMEOUT_S)
      self._force_lock(now)
      return

    if self._next_status_poll_at is None:
      self._next_status_poll_at = now

    if now < self._next_status_poll_at:
      return

    self._poll_status(now)

    if self._status_monitor_active:
      interval = self._status_poll_interval(elapsed)
      self._next_status_poll_at = now + interval

  def _status_poll_interval(self, elapsed: float) -> float:
    for cutoff, interval in STATUS_POLL_SCHEDULE:
      if elapsed < cutoff:
        return interval
    return STATUS_POLL_SCHEDULE[-1][1]

  def _force_lock(self, now: float) -> None:
    logger.info("Auto-lock timeout reached; forcing lock command")
    creds = self._load_credentials(now)
    if creds is None:
      logger.error("Forced auto-lock aborted: credentials unavailable")
      self._reset_cycle_state()
      return
    self._try_lock(now, creds, force=True)

  def _try_lock(self, now: float, creds: _Creds, *, force: bool) -> None:
    if not force and self.lock_attempted_at is not None and (now - self.lock_attempted_at) < LOCK_RETRY_COOLDOWN_S:
      return

    lock_client = self._ensure_lock_client(creds)
    if lock_client is None:
      if force:
        logger.error("Forced auto-lock aborted: unable to initialise lock client")
        self._reset_cycle_state()
      return

    action_desc = "Triggering auto-lock"
    if force:
      action_desc += " (forced timeout)"
    logger.info(action_desc)

    self.lock_attempted_at = now
    try:
      lock_client.lock()
      success_desc = "Auto-lock command sent"
      if force:
        success_desc += " (forced)"
      logger.info(success_desc)
    except Exception as err:  # pylint: disable=broad-except
      failure_desc = "Auto-lock command failed"
      if force:
        failure_desc += " (forced)"
      logger.error("%s: %s", failure_desc, err)
    finally:
      self._reset_cycle_state()

  def _poll_status(self, now: float) -> None:
    if not self._connectivity_available():
      return

    creds = self._load_credentials(now)
    if creds is None:
      return

    status_client = self._ensure_status_client(creds)
    if status_client is None:
      return

    try:
      status: Dict[str, Any] = status_client.status()
    except Exception as err:  # pylint: disable=broad-except
      logger.error("Auto-lock status polling failed: %s", err)
      return

    self._log_status_update(status)

    locked_value = status.get("locked")
    if locked_value is True:
      logger.info("Remote status indicates vehicle already locked; stopping auto-lock monitor")
      self._stop_status_monitor(reset_wait=True)
      return

    engine = status.get("engine") or {}
    ignition_on = bool(engine.get("ignition"))
    accessory_on = bool(engine.get("accessory"))

    open_doors = status.get("openDoors") or {}
    door_open = any(bool(open_doors.get(name)) for name in ("frontRight", "frontLeft", "backLeft", "backRight"))
    hood_open = bool(status.get("hoodOpen"))
    trunk_open = bool(status.get("trunkOpen"))

    if door_open and not self._door_seen_open_remotely:
      logger.debug("Remote door open detected")
    if door_open:
      self._door_seen_open_remotely = True
      self.lock_attempted_at = None
      return

    if hood_open or trunk_open:
      return

    if locked_value is not False:
      return

    if not self._door_seen_open_remotely:
      return

    if ignition_on or accessory_on:
      return

    self._try_lock(now, creds, force=False)

  def _log_status_update(self, status: Dict[str, Any]) -> None:
    if self._last_status_snapshot is None:
      logger.debug("Initial remote status payload: %s", status)
    else:
      changes = self._diff_status(self._last_status_snapshot, status)
      if changes:
        formatted = ", ".join(f"{path}: {change['old']} -> {change['new']}" for path, change in sorted(changes.items()))
        logger.debug("Remote status changes: %s", formatted)
    self._last_status_snapshot = copy.deepcopy(status)

  @staticmethod
  def _diff_status(previous: Dict[str, Any], current: Dict[str, Any]) -> Dict[str, Dict[str, Any]]:
    changes: Dict[str, Dict[str, Any]] = {}

    def recurse(prev: Any, curr: Any, path: tuple[str, ...]) -> None:
      if isinstance(prev, dict) and isinstance(curr, dict):
        keys = set(prev.keys()) | set(curr.keys())
        for key in sorted(keys):
          recurse(prev.get(key), curr.get(key), path + (str(key),))
        return

      if prev != curr:
        key = ".".join(path) if path else "(root)"
        changes[key] = {"old": prev, "new": curr}

    recurse(previous, current, tuple())
    return changes

  def _ensure_status_client(self, creds: _Creds):
    if self._status_client_creds != creds:
      module = self._get_kia_status_module()
      if module is None:
        return None

      KiaCredentials = getattr(module, "KiaCredentials", None)
      KiaStatusClient = getattr(module, "KiaStatusClient", None)
      Region = getattr(module, "Region", None)
      if KiaCredentials is None or KiaStatusClient is None or Region is None:
        logger.error("Kia status module missing required classes")
        return None

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
        logger.error("Failed to build Kia status credentials: %s", err)
        return None

      try:
        self._status_client = KiaStatusClient(kia_creds)
      except Exception as err:  # pylint: disable=broad-except
        logger.error("Failed to initialise KiaStatusClient: %s", err)
        return None
      self._status_client_creds = creds

    return self._status_client

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

  def _get_kia_status_module(self):
    if self._kia_status_module is None:
      module_path = Path(__file__).resolve().parents[2] / "auto-lock" / "kia_status.py"
      spec = util.spec_from_file_location("auto_lock_kia_status", module_path)
      if spec is None or spec.loader is None:
        logger.error("Unable to locate kia_status.py at %s", module_path)
        return None
      module = util.module_from_spec(spec)
      try:
        spec.loader.exec_module(module)
      except Exception as err:  # pylint: disable=broad-except
        logger.error("Failed to load kia_status.py: %s", err)
        return None
      self._kia_status_module = module
    return self._kia_status_module

  def _handle_device_state(self) -> None:
    ds = self.sm["deviceState"]
    self._network_type = ds.networkType

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
    self._stop_status_monitor(reset_wait=True)


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
