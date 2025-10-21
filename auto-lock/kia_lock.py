from __future__ import annotations

import logging
from typing import Any, Dict

try:
  from .kia_shared import (  # type: ignore[attr-defined]
    Region,
    KiaCredentials,
    KiaSession,
    RegionConfig,
    REGION_CONFIG,
    StampGenerator,
    KiaBaseClient,
    requests,
    Response,
    Session,
    HTTPError,
    _raise_for_status,
    _extract_error_message,
  )
except ImportError:  # pragma: no cover - script execution fallback
  from kia_shared import (  # type: ignore[no-redef]
    Region,
    KiaCredentials,
    KiaSession,
    RegionConfig,
    REGION_CONFIG,
    StampGenerator,
    KiaBaseClient,
    requests,
    Response,
    Session,
    HTTPError,
    _raise_for_status,
    _extract_error_message,
  )


logger = logging.getLogger(__name__)


class KiaAutoLockClient(KiaBaseClient):
  """Lock controller using shared infrastructure."""

  def lock(self) -> None:
    vehicle = self._ensure_vehicle()
    if self.creds.region == Region.US:
      self._lock_us(vehicle)
    elif self.creds.region == Region.CA:
      self._lock_ca(vehicle)
    elif self.creds.region == Region.EU:
      self._lock_eu(vehicle)
    elif self.creds.region == Region.AU:
      self._lock_au(vehicle)
    elif self.creds.region == Region.CN:
      self._lock_cn(vehicle)
    else:
      raise ValueError("Unsupported region")

  def _lock_us(self, vehicle: Dict[str, Any]) -> None:
    url = f"{self._env.base_url}/ac/v2/rcs/rdo/off"
    headers = {
      "access_token": self.session.access_token,
      "client_id": self._env.client_id,
      "User-Agent": "okhttp/3.12.0",
      "Content-Type": "application/x-www-form-urlencoded",
      "bluelinkservicepin": self.creds.pin,
      "gen": vehicle.get("generation", ""),
      "registrationId": vehicle.get("reg_id", ""),
      "APPCLOUD-VIN": vehicle.get("vin", ""),
      "offset": self._offset(),
    }
    data = {
      "userName": self.creds.username,
      "vin": vehicle.get("vin"),
    }
    resp = self.http.post(url, data=data, headers=headers)
    _raise_for_status(resp, "US lock")
    logger.info("Vehicle locked (US)")

  def _lock_ca(self, vehicle: Dict[str, Any]) -> None:
    p_auth = self._ca_get_preauth(vehicle)
    url = f"{self._env.base_url}/tods/api/drlck"
    headers = self._ca_headers()
    headers.update({
      "pAuth": p_auth,
      "vehicleId": vehicle.get("vehicle_id"),
    })
    body = {"pin": self.creds.pin}
    resp = self.http.post(url, json=body, headers=headers)
    _raise_for_status(resp, "CA lock")
    logger.info("Vehicle locked (CA)")

  def _lock_eu(self, vehicle: Dict[str, Any]) -> None:
    self._ensure_control_token_eu()
    url = f"{self._env.base_url}/api/v2/spa/vehicles/{vehicle['vehicle_id']}/control/door"
    headers = self._eu_vehicle_headers()
    headers["Stamp"] = self._next_stamp()
    payload = {
      "action": "close",
      "deviceId": self.session.device_id,
    }
    resp = self.http.post(url, json=payload, headers=headers)
    _raise_for_status(resp, "EU lock")
    logger.info("Vehicle locked (EU)")

  def _lock_au(self, vehicle: Dict[str, Any]) -> None:
    self._ensure_control_token_au()
    url = f"{self._env.base_url}/api/v2/spa/vehicles/{vehicle['vehicle_id']}/control/door"
    headers = self._au_vehicle_headers()
    headers["Stamp"] = self._next_stamp()
    payload = {
      "action": "close",
      "deviceId": self.session.device_id,
    }
    resp = self.http.post(url, json=payload, headers=headers)
    _raise_for_status(resp, "AU lock")
    logger.info("Vehicle locked (AU)")

  def _lock_cn(self, vehicle: Dict[str, Any]) -> None:
    self._ensure_control_token_cn()
    url = f"{self._env.base_url}/api/v2/spa/vehicles/{vehicle['vehicle_id']}/control/door"
    headers = self._cn_vehicle_headers()
    payload = {
      "action": "close",
      "deviceId": self.session.device_id,
    }
    resp = self.http.post(url, json=payload, headers=headers)
    _raise_for_status(resp, "CN lock")
    logger.info("Vehicle locked (CN)")


__all__ = [
  "Region",
  "KiaCredentials",
  "KiaSession",
  "RegionConfig",
  "REGION_CONFIG",
  "StampGenerator",
  "KiaAutoLockClient",
  "KiaBaseClient",
  "requests",
  "Response",
  "Session",
  "HTTPError",
  "_raise_for_status",
  "_extract_error_message",
]