from __future__ import annotations

import logging
import time
from dataclasses import dataclass
from typing import Optional

import cereal.messaging as messaging
from openpilot.auto_lock.kia_lock import KiaAutoLockClient, KiaCredentials, Region
from openpilot.common.params import Params

logger = logging.getLogger(__name__)

DOOR_RECENT_WINDOW_S = 300.0
OFF_STABLE_TIME_S = 1.0
LOCK_RETRY_COOLDOWN_S = 120.0
POLL_INTERVAL_S = 0.1


def _now() -> float:
  return time.monotonic()


def _get_region(value: Optional[str]) -> Optional[Region]:
  if not value:
    return None
  try:
    return Region(value.strip().upper())
  except ValueError:
    return None


@dataclass(frozen=True)
class _Creds:
  username: str
  password: str
  pin: str
  region: Region
  vin: Optional[str]
  vehicle_id: Optional[str]
  language: Optional[str]


class AutoLockMonitor:
  def __init__(self) -> None:
    self.params = Params()
    self.sm = messaging.SubMaster(["carState", "pandaState"])

    self.door_open: bool = False
    self.last_door_open_time: Optional[float] = None
    self.last_door_close_time: Optional[float] = None
    self.car_active: bool = False
    self.off_since: Optional[float] = None

    self.lock_attempted_at: Optional[float] = None
    self._client: Optional[KiaAutoLockClient] = None
    self._client_creds: Optional[_Creds] = None

    self._missing_creds_logged_at: Optional[float] = None

  def run(self) -> None:
    while True:
      self.sm.update(int(POLL_INTERVAL_S * 1000))
      now = _now()

      if self.sm.updated["carState"]:
        self._handle_car_state(now)
      if self.sm.updated["pandaState"]:
        self._handle_panda_state(now)

      self._evaluate(now)

  def _handle_car_state(self, now: float) -> None:
    cs = self.sm["carState"]
    door_open = bool(cs.doorOpen)

    if door_open:
      self.last_door_open_time = now
      if not self.door_open:
        logger.debug("Door transitioned open")
      self.lock_attempted_at = None
    elif self.door_open and not door_open:
      self.last_door_close_time = now
      logger.debug("Door transitioned closed")

    self.door_open = door_open

  def _handle_panda_state(self, now: float) -> None:
    ps = self.sm["pandaState"]
    panda_states = ps.pandaStates
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
    else:
      if self.car_active:
        logger.debug("Ignition became inactive")
        self.off_since = now
      elif self.off_since is None:
        self.off_since = now
      self.car_active = False

  def _evaluate(self, now: float) -> None:
    if self.car_active:
      return

    if self.off_since is None or (now - self.off_since) < OFF_STABLE_TIME_S:
      return

    doors_recent = self.last_door_open_time is not None and (now - self.last_door_open_time) <= DOOR_RECENT_WINDOW_S
    doors_closed = not self.door_open and self.last_door_close_time is not None
    door_cycle_complete = (
      self.last_door_open_time is not None
      and self.last_door_close_time is not None
      and self.last_door_close_time >= self.last_door_open_time
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

    logger.info("Triggering auto-lock")
    self.lock_attempted_at = now
    try:
      client.lock()
      logger.info("Auto-lock command sent")
    except Exception as err:  # pylint: disable=broad-except
      logger.error("Auto-lock command failed: %s", err)

  def _load_credentials(self, now: float) -> Optional[_Creds]:
    username = self.params.get("AutoLockUsername", encoding="utf-8", block=False) or ""
    password = self.params.get("AutoLockPassword", encoding="utf-8", block=False) or ""
    pin = self.params.get("AutoLockPin", encoding="utf-8", block=False) or ""
    region_raw = self.params.get("AutoLockRegion", encoding="utf-8", block=False) or ""

    username = username.strip()
    password = password.strip()
    pin = pin.strip()
    region = _get_region(region_raw)

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

  def _ensure_client(self, creds: _Creds) -> Optional[KiaAutoLockClient]:
    if self._client_creds != creds:
      logger.debug("Refreshing KiaAutoLockClient session")
      try:
        kia_creds = KiaCredentials(
          username=creds.username,
          password=creds.password,
          pin=creds.pin,
          region=creds.region,
          vin=creds.vin,
          vehicle_id=creds.vehicle_id,
          language=creds.language,
        )
      except Exception as err:  # pylint: disable=broad-except
        logger.error("Failed to build Kia credentials: %s", err)
        return None

      self._client = KiaAutoLockClient(kia_creds)
      self._client_creds = creds

    return self._client


def main() -> None:
  logging.basicConfig(level=logging.INFO)
  monitor = AutoLockMonitor()
  monitor.run()


if __name__ == "__main__":
  main()
