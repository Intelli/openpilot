from __future__ import annotations

import copy
import logging
import sys
import time
from dataclasses import dataclass
from importlib import util
from pathlib import Path
from typing import Any, Dict, Optional

import cereal.messaging as messaging
from cereal import log
from openpilot.common.params import Params

logger = logging.getLogger(__name__)
debug_logger = logging.getLogger(f"{__name__}.debug")

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
    self.sm = messaging.SubMaster(["carState", "pandaStates", "deviceState", "can"])

    self.car_active: bool = False
    self.off_since: Optional[float] = None

    self.lock_attempted_at: Optional[float] = None
    self._lock_client = None
    self._lock_client_creds: Optional[_Creds] = None
    self._status_client = None
    self._status_client_creds: Optional[_Creds] = None
    self._kia_lock_module = None
    self._kia_status_module = None
    self._kia_shared_module = None
    self._status_monitor_active = False
    self._status_monitor_started_at: Optional[float] = None
    self._next_status_poll_at: Optional[float] = None
    self._door_seen_open_locally = False
    self._door_seen_open_remotely = False
    self.door_open = False
    self.last_door_open_time: Optional[float] = None
    self.last_door_close_time: Optional[float] = None
    self.door_open_after_off_time: Optional[float] = None
    self.door_close_after_off_time: Optional[float] = None

    self._missing_creds_logged_at: Optional[float] = None
    self._network_type = None
    self._awaiting_ignition_cycle = False
    self.seatbelt_unlatched: bool = False
    self._last_seatbelt_state: Optional[bool] = None
    self._last_status_snapshot: Optional[Dict[str, Any]] = None
    self._status_poll_logged: bool = False
    self._monitor_creds: Optional[_Creds] = None

  def run(self) -> None:
    while True:
      self.sm.update(int(POLL_INTERVAL_S * 1000))
      now = _now()

      if self.off_since is None and not self.car_active:
        if self._panda_ignition_active():
          self.car_active = True
        else:
          self._handle_panda_state(now)

      if self.sm.updated["carState"]:
        self._handle_car_state(now)
      if self.sm.updated["pandaStates"]:
        self._handle_panda_state(now)
      if self.sm.updated["deviceState"]:
        self._handle_device_state()
      if self.sm.updated["can"]:
        self._handle_can_messages(now)

      self._evaluate(now)

  def _handle_car_state(self, now: float) -> None:
    cs = self.sm["carState"]
    seatbelt_unlatched = bool(getattr(cs, "seatbeltUnlatched", False))

    if self._last_seatbelt_state is None or seatbelt_unlatched != self._last_seatbelt_state:
      logger.debug("Driver seatbelt unlatched: %s", seatbelt_unlatched)
      self._last_seatbelt_state = seatbelt_unlatched
    self.seatbelt_unlatched = seatbelt_unlatched

    door_open = bool(getattr(cs, "doorOpen", False))
    if self.door_open != door_open:
      logger.debug("Door open: %s", door_open)
    if door_open:
      if not self._door_seen_open_locally:
        logger.debug("Local door open detected")
      self.last_door_open_time = now
      if not self.car_active and self.off_since is not None:
        if self.door_open_after_off_time is None:
          logger.debug("Door opened after ignition off (local)")
        self.door_open_after_off_time = now
      self._door_seen_open_locally = True
    else:
      self.last_door_close_time = now
      if not self.car_active and self.off_since is not None:
        if self._door_seen_open_locally:
          if self.door_close_after_off_time is None:
            logger.debug("Door closed after ignition off (local)")
          self.door_close_after_off_time = now
    self.door_open = door_open

  def _handle_can_messages(self, now: float) -> None:
    if self.car_active or self.off_since is None:
      return

    can_event = self.sm["can"]
    can_msgs = getattr(can_event, "can", [])
    if not can_msgs:
      return

    for can_msg in can_msgs:
      data_bytes = bytes(can_msg.dat)
      debug_logger.debug(
        "CAN frame t_off=%.3f bus=%d addr=0x%03X len=%d data=%s",
        now - self.off_since,
        can_msg.src,
        can_msg.address,
        len(data_bytes),
        data_bytes.hex(),
      )

  def _panda_ignition_state(self) -> tuple[bool, bool]:
    panda_states = self.sm["pandaStates"]
    ignition_line_active = any(bool(panda_state.ignitionLine) for panda_state in panda_states)
    ignition_can_active = any(bool(panda_state.ignitionCan) for panda_state in panda_states)
    return ignition_line_active, ignition_can_active

  def _panda_ignition_active(self) -> bool:
    ignition_line_active, ignition_can_active = self._panda_ignition_state()
    return ignition_line_active or ignition_can_active

  def _handle_panda_state(self, now: float) -> None:
    ignition_line_active, ignition_can_active = self._panda_ignition_state()
    ignition_on = ignition_line_active or ignition_can_active

    if ignition_on:
      if not self.car_active:
        logger.debug("Ignition became active")
        debug_logger.debug("Ignition active (line=%s, can=%s)", ignition_line_active, ignition_can_active)
      self.off_since = None
      self.car_active = True
      self._awaiting_ignition_cycle = False
      self._stop_status_monitor(reset_wait=False)
      self._door_seen_open_locally = False
      self._door_seen_open_remotely = False
      self.door_open_after_off_time = None
      self.door_close_after_off_time = None
    else:
      if self.car_active:
        logger.debug("Ignition became inactive")
        debug_logger.debug("Ignition inactive (line=%s, can=%s)", ignition_line_active, ignition_can_active)
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

    creds = self._monitor_creds
    if creds is None:
      creds = self._load_credentials(now)
      if creds is None:
        return
      self._monitor_creds = creds

    if not self._status_monitor_active:
      self._start_status_monitor(now)

    self._process_status_monitor(now, creds)

  def _load_credentials(self, now: float) -> Optional[_Creds]:
    username = self.params.get("AutoLockUsername", block=False) or ""
    password = self.params.get("AutoLockPassword", block=False) or ""
    pin = self.params.get("AutoLockPin", block=False) or ""
    region_raw = self.params.get("AutoLockRegion", block=False) or ""

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
    if self._status_poll_logged:
      logger.debug("Auto-lock remote status polling stopped")
    self._status_monitor_active = False
    self._status_monitor_started_at = None
    self._next_status_poll_at = None
    self._door_seen_open_remotely = False
    self._last_status_snapshot = None
    self._status_poll_logged = False
    self._monitor_creds = None
    if reset_wait:
      self._awaiting_ignition_cycle = True

  def _start_status_monitor(self, now: float) -> None:
    self._status_monitor_active = True
    self._status_monitor_started_at = now
    self._next_status_poll_at = now
    self._door_seen_open_remotely = False
    self._status_poll_logged = False
    logger.debug("Auto-lock status monitor started")
    off_since = self.off_since if self.off_since is not None else now
    debug_logger.debug("Status monitor started t_off=%.3f", now - off_since)

  def _process_status_monitor(self, now: float, creds: _Creds) -> None:
    if not self._status_monitor_active or self._status_monitor_started_at is None:
      return

    elapsed = now - self._status_monitor_started_at

    if elapsed >= STATUS_MONITOR_TIMEOUT_S:
      logger.info("Auto-lock polling timed out after %.0f seconds; forcing lock command", STATUS_MONITOR_TIMEOUT_S)
      off_since = self.off_since if self.off_since is not None else now
      debug_logger.debug("Status monitor timeout reached t_off=%.3f", now - off_since)
      self._force_lock(now, creds)
      return

    if self._next_status_poll_at is None:
      self._next_status_poll_at = now

    if now < self._next_status_poll_at:
      return

    self._poll_status(now, creds)

    if self._status_monitor_active:
      interval = self._status_poll_interval(elapsed)
      self._next_status_poll_at = now + interval

  def _status_poll_interval(self, elapsed: float) -> float:
    for cutoff, interval in STATUS_POLL_SCHEDULE:
      if elapsed < cutoff:
        return interval
    return STATUS_POLL_SCHEDULE[-1][1]

  def _force_lock(self, now: float, creds: _Creds) -> None:
    logger.info("Auto-lock timeout reached; forcing lock command")
    off_since = self.off_since if self.off_since is not None else now
    debug_logger.debug("Force lock triggered at t_off=%.3f", now - off_since)
    if creds is None:
      logger.error("Forced auto-lock aborted: credentials unavailable")
      debug_logger.debug("Force lock aborted due to missing credentials")
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
        debug_logger.debug("Force lock aborted due to missing lock client")
        self._reset_cycle_state()
      return

    action_desc = "Triggering auto-lock"
    if force:
      action_desc += " (forced timeout)"
    network_type = getattr(self, "_network_type", None)
    network_label = getattr(network_type, "name", str(network_type)) if network_type is not None else "unknown"
    logger.info("%s | networkType=%s", action_desc, network_label)
    off_since = self.off_since if self.off_since is not None else now
    debug_logger.debug("Lock attempt force=%s t_off=%.3f", force, now - off_since)

    self.lock_attempted_at = now
    try:
      lock_client.lock()
      success_desc = "Auto-lock command sent"
      if force:
        success_desc += " (forced)"
      logger.info(success_desc)
      debug_logger.debug("Lock command dispatched force=%s", force)
    except Exception as err:  # pylint: disable=broad-except
      failure_desc = "Auto-lock command failed"
      if force:
        failure_desc += " (forced)"
      logger.error("%s: %s", failure_desc, err)
      debug_logger.debug("Lock command failure force=%s error=%s", force, err)
    finally:
      self._reset_cycle_state()

  def _poll_status(self, now: float, creds: _Creds) -> None:
    status_client = self._ensure_status_client(creds)
    if status_client is None:
      return

    try:
      if not self._status_poll_logged:
        logger.debug("Auto-lock remote status polling started")
        self._status_poll_logged = True
      logger.debug("Polling remote status via KiaStatusClient (region=%s)", creds.region)
      status: Dict[str, Any] = status_client.status()
    except Exception as err:  # pylint: disable=broad-except
      logger.error("Auto-lock status polling failed: %s", err)
      debug_logger.debug("Status polling error=%s", err)
      return

    self._log_status_update(status)

    locked_value = status.get("locked")
    engine = status.get("engine") or {}
    open_doors = status.get("openDoors") or {}
    debug_logger.debug(
      "Status response locked=%s ignition=%s accessory=%s hood=%s trunk=%s doors=%s timestamp=%s",
      locked_value,
      engine.get("ignition"),
      engine.get("accessory"),
      status.get("hoodOpen"),
      status.get("trunkOpen"),
      open_doors,
      status.get("timestamp"),
    )
    if locked_value is True:
      logger.info("Remote status indicates vehicle already locked; stopping auto-lock monitor")
      debug_logger.debug("Remote status reported locked; monitor stopping")
      self._stop_status_monitor(reset_wait=True)
      return

    ignition_on = bool(engine.get("ignition"))
    accessory_on = bool(engine.get("accessory"))

    door_open = any(bool(open_doors.get(name)) for name in ("frontRight", "frontLeft", "backLeft", "backRight"))
    hood_open = bool(status.get("hoodOpen"))
    trunk_open = bool(status.get("trunkOpen"))

    door_seen_open = self._door_seen_open_locally or self._door_seen_open_remotely
    if door_open and not door_seen_open:
      logger.debug("Remote door open detected")
      debug_logger.debug("Remote door open detected doors=%s", open_doors)
    if door_open:
      self._door_seen_open_remotely = True
      if self.door_open_after_off_time is None:
        self.door_open_after_off_time = now
      self.lock_attempted_at = None
      return

    if hood_open or trunk_open:
      return

    if locked_value is not False:
      return

    if door_seen_open and self.door_close_after_off_time is None and not self.door_open:
      logger.debug("Doors closed after ignition off (joint detection)")
      self.door_close_after_off_time = now

    if not door_seen_open:
      return

    if ignition_on or accessory_on:
      return

    if self.door_close_after_off_time is None:
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

      KiaStatusClient = getattr(module, "KiaStatusClient", None)
      Region = getattr(module, "Region", None)
      KiaCredentials = getattr(module, "KiaCredentials", None)

      if KiaCredentials is None or Region is None:
        shared_module = self._get_kia_shared_module()
        if shared_module is not None:
          if KiaCredentials is None:
            KiaCredentials = getattr(shared_module, "KiaCredentials", None)
          if Region is None:
            Region = getattr(shared_module, "Region", None)

      if KiaCredentials is None or Region is None:
        lock_module = self._get_kia_lock_module()
        if lock_module is not None:
          if KiaCredentials is None:
            KiaCredentials = getattr(lock_module, "KiaCredentials", None)
          if Region is None:
            Region = getattr(lock_module, "Region", None)

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
      module_dir = module_path.parent
      if str(module_dir) not in sys.path:
        sys.path.insert(0, str(module_dir))
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
      module_dir = module_path.parent
      if str(module_dir) not in sys.path:
        sys.path.insert(0, str(module_dir))
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

  def _get_kia_shared_module(self):
    if self._kia_shared_module is None:
      module_path = Path(__file__).resolve().parents[2] / "auto-lock" / "kia_shared.py"
      module_dir = module_path.parent
      if str(module_dir) not in sys.path:
        sys.path.insert(0, str(module_dir))
      spec = util.spec_from_file_location("auto_lock_kia_shared", module_path)
      if spec is None or spec.loader is None:
        logger.error("Unable to locate kia_shared.py at %s", module_path)
        return None
      module = util.module_from_spec(spec)
      try:
        spec.loader.exec_module(module)
      except Exception as err:  # pylint: disable=broad-except
        logger.error("Failed to load kia_shared.py: %s", err)
        return None
      self._kia_shared_module = module
    return self._kia_shared_module

  def _handle_device_state(self) -> None:
    self._network_type = self.sm["deviceState"].networkType

  def _reset_cycle_state(self) -> None:
    self.last_door_open_time = None
    self.last_door_close_time = None
    self.door_open_after_off_time = None
    self.door_close_after_off_time = None
    self.door_open = False
    self._door_seen_open_locally = False
    self._door_seen_open_remotely = False
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
    file_handler.setLevel(logging.DEBUG)
    logger.addHandler(file_handler)
    logger.setLevel(logging.DEBUG)

    debug_logfile = log_dir / "autolock.debug.log"
    try:
      debug_logfile.unlink()
    except FileNotFoundError:
      pass
    except OSError as err:
      logger.warning("Unable to remove existing debug log file %s: %s", debug_logfile, err)

    debug_formatter = logging.Formatter("%(asctime)s %(levelname)s %(name)s: %(message)s")
    for handler in list(debug_logger.handlers):
      handler.close()
      debug_logger.removeHandler(handler)
    debug_handler = logging.FileHandler(debug_logfile, mode="w", encoding="utf-8")
    debug_handler.setFormatter(debug_formatter)
    debug_handler.setLevel(logging.DEBUG)
    debug_logger.addHandler(debug_handler)
    debug_logger.setLevel(logging.DEBUG)
    debug_logger.propagate = False

    kia_status_logger = logging.getLogger("auto_lock_kia_status")
    if not any(isinstance(handler, logging.FileHandler) and handler.baseFilename == str(logfile) for handler in kia_status_logger.handlers):
      kia_status_logger.addHandler(file_handler)
    kia_status_logger.setLevel(logging.DEBUG)

    kia_shared_logger = logging.getLogger("auto_lock_kia_shared")
    if not any(isinstance(handler, logging.FileHandler) and handler.baseFilename == str(logfile) for handler in kia_shared_logger.handlers):
      kia_shared_logger.addHandler(file_handler)
    kia_shared_logger.setLevel(logging.DEBUG)
  monitor = AutoLockMonitor()
  monitor.run()


if __name__ == "__main__":
  main()
