from __future__ import annotations

import logging
import time
from typing import Any, Dict, Optional

try:
  from .kia_shared import (  # type: ignore[attr-defined]
    KiaBaseClient,
    Region,
    _raise_for_status,
  )
except ImportError:  # pragma: no cover - script execution fallback
  from kia_shared import (  # type: ignore[no-redef]
    KiaBaseClient,
    Region,
    _raise_for_status,
  )

logger = logging.getLogger(__name__)


class KiaStatusClient(KiaBaseClient):
  def status(self) -> Dict[str, Any]:
    vehicle = self._ensure_vehicle()

    if self.creds.region == Region.US:
      return self._status_us(vehicle)
    if self.creds.region == Region.CA:
      return self._status_ca(vehicle)
    if self.creds.region == Region.EU:
      return self._status_eu(vehicle)
    if self.creds.region == Region.AU:
      return self._status_au(vehicle)
    if self.creds.region == Region.CN:
      return self._status_cn(vehicle)
    raise ValueError("Unsupported region for status polling")

  def _status_ca(self, vehicle: Dict[str, Any]) -> Dict[str, Any]:
    pre_auth = self._ca_get_preauth(vehicle)
    url = f"{self._env.base_url}/tods/api/rltmvhclsts"
    headers = self._ca_headers()
    headers.update({
      "pAuth": pre_auth,
      "vehicleId": vehicle.get("vehicle_id"),
    })
    payload: Dict[str, Any] = {"pin": self.creds.pin}
    resp = self.http.post(url, json=payload, headers=headers)
    _raise_for_status(resp, "CA status")
    data = resp.json()
    result = data.get("result", {})
    status = result.get("status", {})
    timestamp = result.get("timeStamp") or status.get("lastStatusDate") or status.get("dateTime")
    return self._normalize_status(status, timestamp)

  def _status_us(self, vehicle: Dict[str, Any]) -> Dict[str, Any]:
    url = f"{self._env.base_url}/ac/v2/rcs/rvs/vehicleStatus"
    headers = {
      "access_token": self.session.access_token,
      "client_id": self._env.client_id,
      "User-Agent": "okhttp/3.12.0",
      "payloadGenerated": time.strftime("%Y%m%d%H%M%S"),
      "vin": vehicle.get("vin"),
      "registrationId": vehicle.get("reg_id", ""),
      "gen": vehicle.get("generation", ""),
      "offset": self._offset(),
      "REFRESH": "true",
    }
    resp = self.http.get(url, headers=headers)
    _raise_for_status(resp, "US status")
    data = resp.json()
    status = data.get("vehicleStatus", {})
    timestamp = data.get("timeStamp") or status.get("dateTime") or status.get("lastStatusDate")
    return self._normalize_status(status, timestamp)

  def _status_eu(self, vehicle: Dict[str, Any]) -> Dict[str, Any]:
    self._ensure_control_token_eu()
    headers = self._eu_vehicle_headers()
    headers["Stamp"] = self._next_stamp()
    url = f"{self._env.base_url}/api/v2/spa/vehicles/{vehicle['vehicle_id']}/status"
    resp = self.http.get(url, headers=headers)
    _raise_for_status(resp, "EU status")
    body = resp.json()
    status = body.get("resMsg", {})
    timestamp = status.get("lastStatusDate") or status.get("timeStamp")
    return self._normalize_status(status, timestamp)

  def _status_au(self, vehicle: Dict[str, Any]) -> Dict[str, Any]:
    self._ensure_control_token_au()
    headers = self._au_vehicle_headers()
    headers["Stamp"] = self._next_stamp()
    url = f"{self._env.base_url}/api/v2/spa/vehicles/{vehicle['vehicle_id']}/status"
    resp = self.http.get(url, headers=headers)
    _raise_for_status(resp, "AU status")
    body = resp.json()
    status = body.get("resMsg", {})
    timestamp = status.get("lastStatusDate") or status.get("timeStamp")
    return self._normalize_status(status, timestamp)

  def _status_cn(self, vehicle: Dict[str, Any]) -> Dict[str, Any]:
    self._ensure_control_token_cn()
    headers = self._cn_vehicle_headers()
    url = f"{self._env.base_url}/api/v2/spa/vehicles/{vehicle['vehicle_id']}/status"
    resp = self.http.get(url, headers=headers)
    _raise_for_status(resp, "CN status")
    body = resp.json()
    status = body.get("resMsg", {})
    timestamp = status.get("lastStatusDate") or status.get("timeStamp")
    return self._normalize_status(status, timestamp)

  def _normalize_status(self, status: Dict[str, Any], timestamp: Optional[Any]) -> Dict[str, Any]:
    door_open = status.get("doorOpen") or {}
    tire_pressure = status.get("tirePressureLamp") or {}
    air_temp = status.get("airTemp") or {}
    ev_status = status.get("evStatus") or {}
    battery = status.get("battery") or {}

    range_km: Optional[Any] = None
    dte = status.get("dte")
    if isinstance(dte, dict):
      range_km = dte.get("value") or dte.get("total")
    if range_km is None:
      drv_distance = ev_status.get("drvDistance") if isinstance(ev_status, dict) else None
      if isinstance(drv_distance, list) and drv_distance:
        range_by_fuel = drv_distance[0].get("rangeByFuel", {})
        total_range = range_by_fuel.get("totalAvailableRange", {})
        if isinstance(total_range, dict):
          range_km = total_range.get("value")

    normalized = {
      "locked": status.get("doorLock"),
      "openDoors": {
        "frontRight": bool(door_open.get("frontRight")),
        "frontLeft": bool(door_open.get("frontLeft")),
        "backLeft": bool(door_open.get("backLeft")),
        "backRight": bool(door_open.get("backRight")),
      },
      "hoodOpen": status.get("hoodOpen"),
      "trunkOpen": status.get("trunkOpen"),
      "tirePressure": {
        "frontLeft": bool(tire_pressure.get("tirePressureWarningLampFrontLeft")),
        "frontRight": bool(tire_pressure.get("tirePressureWarningLampFrontRight")),
        "rearLeft": bool(tire_pressure.get("tirePressureWarningLampRearLeft")),
        "rearRight": bool(tire_pressure.get("tirePressureWarningLampRearRight")),
        "all": bool(tire_pressure.get("tirePressureWarningLampAll")),
      },
      "climate": {
        "active": status.get("airCtrlOn"),
        "defrost": status.get("defrost"),
        "temperatureSetpoint": air_temp.get("value"),
        "temperatureUnit": air_temp.get("unit"),
        "steeringWheelHeat": bool(status.get("steerWheelHeat")),
        "rearWindowHeat": bool(status.get("sideBackWindowHeat")),
      },
      "engine": {
        "ignition": status.get("engine"),
        "accessory": status.get("acc"),
        "rangeKm": range_km,
        "charging": ev_status.get("batteryCharge") if isinstance(ev_status, dict) else None,
        "battery12vSoc": battery.get("batSoc") if isinstance(battery, dict) else None,
        "batteryHvStatus": ev_status.get("batteryStatus") if isinstance(ev_status, dict) else None,
      },
      "timestamp": self._coerce_timestamp(timestamp, status),
    }
    return normalized

  @staticmethod
  def _coerce_timestamp(timestamp: Optional[Any], status: Dict[str, Any]) -> Optional[str]:
    if isinstance(timestamp, dict):
      for key in ("value", "utc", "iso"):
        if key in timestamp:
          return str(timestamp[key])
    if timestamp:
      return str(timestamp)
    for key in ("dateTime", "lastStatusDate", "timeStamp"):
      value = status.get(key)
      if value:
        return str(value)
    return None