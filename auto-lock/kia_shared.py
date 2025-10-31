from __future__ import annotations

import base64
import json
import logging
import time
import uuid
from dataclasses import dataclass, field
from enum import Enum
from typing import Any, Dict, Optional
from urllib.parse import parse_qs, urlparse
import re

try:
  import requests
  from requests import Response, Session
except ImportError:  # pragma: no cover - fallback for embedded environments
  requests = None  # type: ignore[assignment]
  Response = Any  # type: ignore[misc,assignment]
  Session = Any  # type: ignore[misc,assignment]
  HTTPError = Exception  # Placeholder, overwritten below
else:
  HTTPError = requests.HTTPError


if requests is None:  # pragma: no cover
  import http.cookiejar
  import urllib.error
  import urllib.parse
  import urllib.request

  HTTPError = urllib.error.HTTPError

  class _SimpleResponse:
    def __init__(self, url: str, status: int, headers: Dict[str, str], content: bytes, reason: Optional[str] = None) -> None:
      self.url = url
      self.status_code = status
      self.headers = headers
      self._content = content
      self.reason = reason or ""

    @property
    def text(self) -> str:
      return self._content.decode("utf-8", errors="replace")

    def json(self) -> Any:
      return json.loads(self.text)

    def raise_for_status(self) -> None:
      if 400 <= self.status_code:
        raise HTTPError(self.url, self.status_code, self.reason, None, None)

    @property
    def content(self) -> bytes:
      return self._content

  class _NoRedirect(urllib.request.HTTPErrorProcessor):
    def http_response(self, request, response):  # type: ignore[override]
      return response

    https_response = http_response  # type: ignore[assignment]

  class _CookieFacade:
    def __init__(self, jar: http.cookiejar.CookieJar) -> None:
      self._jar = jar

    def clear(self) -> None:
      try:
        self._jar.clear()
      except ValueError:
        for domain in list(self._jar._cookies.keys()):  # type: ignore[attr-defined]
          self._jar.clear(domain)  # type: ignore[arg-type]

  class _UrllibSession:
    def __init__(self) -> None:
      self.headers: Dict[str, str] = {}
      self._cookie_jar = http.cookiejar.CookieJar()
      self.cookies = _CookieFacade(self._cookie_jar)
      self._default_opener = urllib.request.build_opener(urllib.request.HTTPCookieProcessor(self._cookie_jar))

    def _build_opener(self, allow_redirects: bool):
      if allow_redirects:
        return self._default_opener
      return urllib.request.build_opener(urllib.request.HTTPCookieProcessor(self._cookie_jar), _NoRedirect())

    def request(self, method: str, url: str, *, headers: Optional[Dict[str, str]] = None, data: Any = None, json: Any = None,
                allow_redirects: bool = True) -> _SimpleResponse:
      req_headers = dict(self.headers)
      if headers:
        req_headers.update(headers)

      body: Optional[bytes] = None
      if json is not None:
        body = json_dumps(json)
        req_headers.setdefault("Content-Type", "application/json")
      elif data is not None:
        if isinstance(data, dict):
          body = urllib.parse.urlencode({k: v for k, v in data.items() if v is not None}).encode()
          req_headers.setdefault("Content-Type", "application/x-www-form-urlencoded")
        elif isinstance(data, str):
          body = data.encode()
        elif isinstance(data, bytes):
          body = data
        else:
          raise TypeError("Unsupported data type for request body")

      clean_headers = {k: str(v) for k, v in req_headers.items() if v is not None}
      req = urllib.request.Request(url, data=body, headers=clean_headers, method=method.upper())
      opener = self._build_opener(allow_redirects)
      try:
        resp = opener.open(req)
        content = resp.read()
        status = resp.getcode()
        final_url = resp.geturl()
        headers_dict = dict(resp.headers.items())
        return _SimpleResponse(final_url, status, headers_dict, content, resp.reason)
      except urllib.error.HTTPError as err:
        content = err.read()
        headers_dict = dict(err.headers.items()) if err.headers else {}
        return _SimpleResponse(err.geturl(), err.code, headers_dict, content, err.reason)

    def get(self, url: str, **kwargs: Any) -> _SimpleResponse:
      kwargs.setdefault("allow_redirects", True)
      return self.request("GET", url, **kwargs)

    def post(self, url: str, **kwargs: Any) -> _SimpleResponse:
      kwargs.setdefault("allow_redirects", True)
      return self.request("POST", url, **kwargs)

    def put(self, url: str, **kwargs: Any) -> _SimpleResponse:
      kwargs.setdefault("allow_redirects", True)
      return self.request("PUT", url, **kwargs)

    def close(self) -> None:
      pass

  Session = _UrllibSession  # type: ignore[assignment]
  Response = _SimpleResponse  # type: ignore[assignment]

  def json_dumps(payload: Any) -> bytes:
    return json.dumps(payload).encode()

else:
  def json_dumps(payload: Any) -> bytes:
    return json.dumps(payload).encode()


logger = logging.getLogger(__name__)


class Region(Enum):
  US = "US"
  CA = "CA"
  EU = "EU"
  CN = "CN"
  AU = "AU"


@dataclass
class KiaCredentials:
  username: str
  password: str
  pin: str
  region: Region
  vin: Optional[str] = None
  vehicle_id: Optional[str] = None
  language: Optional[str] = None


@dataclass
class KiaSession:
  access_token: Optional[str] = None
  refresh_token: Optional[str] = None
  control_token: Optional[str] = None
  access_token_expires_at: float = 0.0
  control_token_expires_at: float = 0.0
  device_id: str = field(default_factory=lambda: uuid.uuid4().hex)

  def has_valid_access_token(self) -> bool:
    return bool(self.access_token) and time.time() < self.access_token_expires_at - 10

  def has_valid_control_token(self) -> bool:
    return bool(self.control_token) and time.time() < self.control_token_expires_at - 10


@dataclass
class RegionConfig:
  base_url: str
  client_id: str
  client_secret: Optional[str] = None
  app_id: Optional[str] = None
  basic_token: Optional[str] = None
  auth_host: Optional[str] = None
  token_exchange_url: Optional[str] = None
  stamp_cfb: Optional[str] = None
  origin: Optional[str] = None
  provider_device_id: Optional[str] = None
  push_reg_id: Optional[str] = None


REGION_CONFIG: Dict[Region, RegionConfig] = {
  Region.US: RegionConfig(
    base_url="https://api.owners.kia.com/apigw/v1",
    client_id="MWAMOBILE",
    client_secret="98er-w34rf-ibf3-3f6h",
  ),
  Region.CA: RegionConfig(
    base_url="https://kiaconnect.ca",
    client_id="",
    origin="SPA",
  ),
  Region.EU: RegionConfig(
    base_url="https://prd.eu-ccapi.kia.com:8080",
    client_id="fdc85c00-0a2f-4c64-bcb4-2cfb1500730a",
    app_id="a2b8469b-30a3-4361-8e13-6fceea8fbe74",
    basic_token="Basic ZmRjODVjMDAtMGEyZi00YzY0LWJjYjQtMmNmYjE1MDA3MzBhOnNlY3JldA==",
    auth_host="idpconnect-eu.kia.com",
    token_exchange_url="https://idpconnect-eu.kia.com/auth/api/v2/user/oauth2/token",
    stamp_cfb="wLTVxwidmH8CfJYBWSnHD6E0huk0ozdiuygB4hLkM5XCgzAL1Dk5sE36d/bx5PFMQeU=",
  ),
  Region.AU: RegionConfig(
    base_url="https://au-apigw.ccs.kia.com.au:8082",
    client_id="8acb778a-b918-4a8d-8624-73a0beb64289",
    app_id="4ad4dcde-be23-48a8-bc1c-91b94f5c06f8",
    basic_token="Basic OGFjYjc3OGEtYjkxOC00YThkLTg2MjQtNzNhMGJlYjY0Mjg5OjdTY01NbTZmRVlYZGlFUEN4YVBhUW1nZVlkbFVyZndvaDRBZlhHT3pZSVMyQ3U5VA==",
    stamp_cfb="IDbMgWBXgic4MAyMgf5PFFRAdGX5O3IyC3uvN3scCs0gDpTFDuyvBorlAH9JMM2/hys=",
  ),
  Region.CN: RegionConfig(
    base_url="https://prd.cn-ccapi.kia.com",
    client_id="9d5df92a-06ae-435f-b459-8304f2efcc67",
    app_id="eea8762c-adfc-4ee4-8d7a-6e2452ddf342",
    basic_token="Basic OWQ1ZGY5MmEtMDZhZS00MzVmLWI0NTktODMwNGYyZWZjYzY3OnRzWGRrVWcwOEF2MlpaelhPZ1d6Snl4VVQ2eWVTbk5OUWtYWFBSZEtXRUFOd2wxcA==",
    provider_device_id="32dedba78045415b92db816e805ed47b",
    push_reg_id="ogc+GB5gom7zDEQjPhb3lP+bjjM=DG2rQ9Zuq0otwOU7n9y08LKjYpo=",
  ),
}


class StampGenerator:
  def __init__(self, cfb_b64: str, app_id: str) -> None:
    self._cfb = base64.b64decode(cfb_b64)
    self._app_id = app_id

  def __call__(self) -> str:
    payload = f"{self._app_id}:{int(time.time() * 1000)}".encode()
    if len(payload) < len(self._cfb):
      payload = payload.ljust(len(self._cfb), b"0")
    elif len(payload) > len(self._cfb):
      payload = payload[:len(self._cfb)]
    stamp = bytes(x ^ y for x, y in zip(self._cfb, payload))
    return base64.b64encode(stamp).decode()


class KiaBaseClient:
  _STD_HEADERS = {
    "User-Agent": "Mozilla/5.0 (iPhone; CPU iPhone OS 13_5 like Mac OS X)"
  }

  def __init__(self, creds: KiaCredentials, http: Optional[Session] = None) -> None:
    self.creds = creds
    if http is not None:
      self.http = http
    elif requests is not None:
      self.http = requests.Session()
    else:
      self.http = Session()
    self.http.headers.update(self._STD_HEADERS)
    if creds.region == Region.CA:
      self.http.headers.setdefault("from", REGION_CONFIG[Region.CA].origin or "SPA")
      self.http.headers.setdefault("language", "1")
      self.http.headers.setdefault("offset", self._offset())
    self.session = KiaSession()
    self._env = REGION_CONFIG[creds.region]
    self._stamp = StampGenerator(self._env.stamp_cfb, self._env.app_id) if self._env.stamp_cfb and self._env.app_id else None
    self._vehicle: Optional[Dict[str, Any]] = None
    self._vehicles: Optional[Any] = None
    self._vehicles_fetched_at: float = 0.0

  def _ensure_vehicle(self) -> Dict[str, Any]:
    if not self.session.has_valid_access_token():
      self._login()
    elif self.creds.region in {Region.US, Region.EU, Region.AU, Region.CN} and time.time() > self.session.access_token_expires_at - 120:
      self._refresh_access_token()
    if self._vehicle and time.time() - self._vehicles_fetched_at < 300:
      return self._vehicle
    fetchers = {
      Region.US: self._fetch_vehicles_us,
      Region.CA: self._fetch_vehicles_ca,
      Region.EU: self._fetch_vehicles_eu,
      Region.AU: self._fetch_vehicles_au,
      Region.CN: self._fetch_vehicles_cn,
    }
    vehicles = fetchers[self.creds.region]()
    self._vehicles = vehicles
    self._vehicles_fetched_at = time.time()
    self._vehicle = self._select_vehicle(vehicles)
    if not self._vehicle:
      raise RuntimeError("No vehicles available for selected account")
    return self._vehicle

  def _select_vehicle(self, vehicles: Any) -> Dict[str, Any]:
    vin = (self.creds.vin or "").lower()
    vehicle_id = self.creds.vehicle_id
    for vehicle in vehicles:
      if vin and vehicle.get("vin", "").lower() == vin:
        return vehicle
      if vehicle_id and str(vehicle.get("vehicle_id")) == str(vehicle_id):
        return vehicle
    return vehicles[0] if vehicles else {}

  def _login(self) -> None:
    handlers = {
      Region.US: self._login_us,
      Region.CA: self._login_ca,
      Region.EU: self._login_eu,
      Region.AU: self._login_au,
      Region.CN: self._login_cn,
    }
    handlers[self.creds.region]()

  def _refresh_access_token(self) -> None:
    handlers = {
      Region.US: self._refresh_us,
      Region.CA: self._login_ca,
      Region.EU: self._refresh_eu,
      Region.AU: self._refresh_au,
      Region.CN: self._refresh_cn,
    }
    handlers[self.creds.region]()

  def _login_us(self) -> None:
    url = f"{self._env.base_url}/v2/ac/oauth/token"
    payload = {
      "username": self.creds.username,
      "password": self.creds.password,
    }
    headers = {
      "client_id": self._env.client_id,
      "client_secret": self._env.client_secret,
      "Content-Type": "application/json",
    }
    resp = self.http.post(url, json=payload, headers=headers)
    _raise_for_status(resp, "US login")
    data = resp.json()
    if resp.status_code != 200:
      raise RuntimeError(f"US login failed: {data}")
    self.session.access_token = data.get("access_token")
    self.session.refresh_token = data.get("refresh_token")
    expires_in = int(data.get("expires_in", 1800))
    self.session.access_token_expires_at = time.time() + expires_in
    logger.debug("US login successful; expires in %s", expires_in)

  def _refresh_us(self) -> None:
    if not self.session.refresh_token:
      self._login_us()
      return
    url = f"{self._env.base_url}/v2/ac/oauth/token/refresh"
    payload = {"refresh_token": self.session.refresh_token}
    headers = {
      "client_id": self._env.client_id,
      "client_secret": self._env.client_secret,
      "Content-Type": "application/json",
    }
    resp = self.http.post(url, json=payload, headers=headers)
    _raise_for_status(resp, "US refresh")
    data = resp.json()
    if resp.status_code != 200:
      raise RuntimeError(f"US token refresh failed: {data}")
    self.session.access_token = data.get("access_token")
    self.session.refresh_token = data.get("refresh_token", self.session.refresh_token)
    expires_in = int(data.get("expires_in", 1800))
    self.session.access_token_expires_at = time.time() + expires_in
    logger.debug("US token refresh successful; expires in %s", expires_in)

  def _login_ca(self) -> None:
    url = f"{self._env.base_url}/tods/api/lgn"
    payload = {
      "loginId": self.creds.username,
      "password": self.creds.password,
    }
    headers = self._ca_headers()
    resp = self.http.post(url, json=payload, headers=headers)
    _raise_for_status(resp, "CA login")
    body = resp.json()
    if not isinstance(body, dict):
      raise RuntimeError(f"CA login failed: unexpected response {body}")
    header = body.get("responseHeader", {})
    code = header.get("responseCode")
    desc = header.get("responseDesc")
    if code not in (0, "0"):
      raise RuntimeError(f"CA login failed (code {code}): {desc}")
    data = body.get("result", {})
    access_token = data.get("accessToken")
    refresh_token = data.get("refreshToken")
    if not access_token:
      raise RuntimeError("CA login failed: missing access token in response")
    self.session.access_token = access_token
    self.session.refresh_token = refresh_token
    expires_in = int(data.get("expireIn", 900))
    self.session.access_token_expires_at = time.time() + expires_in
    logger.debug("CA login successful; expires in %s", expires_in)

  def _fetch_vehicles_us(self) -> Any:
    url = f"{self._env.base_url}/ac/v2/enrollment/details/{self.creds.username}"
    headers = {
      "access_token": self.session.access_token,
      "client_id": self._env.client_id,
      "User-Agent": "okhttp/3.12.0",
      "payloadGenerated": time.strftime("%Y%m%d%H%M%S"),
      "includeNonConnectedVehicles": "Y",
    }
    resp = self.http.get(url, headers=headers)
    _raise_for_status(resp, "US vehicle list")
    vehicles = []
    for entry in resp.json().get("enrolledVehicleDetails", []):
      details = entry.get("vehicleDetails", {})
      vehicles.append({
        "vin": details.get("vin"),
        "vehicle_id": details.get("vehicleId") or details.get("vehicleId", details.get("vehicleId")),
        "reg_id": details.get("regid"),
        "generation": details.get("vehicleGeneration"),
      })
    if not vehicles:
      raise RuntimeError("No US vehicles found")
    return vehicles

  def _fetch_vehicles_ca(self) -> Any:
    url = f"{self._env.base_url}/tods/api/vhcllst"
    headers = self._ca_headers()
    resp = self.http.post(url, json={}, headers=headers)
    _raise_for_status(resp, "CA vehicle list")
    data = resp.json().get("result", {}).get("vehicles", [])
    vehicles = []
    for item in data:
      vehicles.append({
        "vin": item.get("vin"),
        "vehicle_id": item.get("vehicleId"),
        "reg_id": item.get("regid"),
      })
    if not vehicles:
      raise RuntimeError("No CA vehicles found")
    return vehicles

  def _fetch_vehicles_eu(self) -> Any:
    url = f"{self._env.base_url}/api/v1/spa/vehicles"
    headers = self._eu_default_headers()
    headers["Stamp"] = self._next_stamp()
    resp = self.http.get(url, headers=headers)
    _raise_for_status(resp, "EU vehicle list")
    vehicles = []
    for item in resp.json().get("resMsg", {}).get("vehicles", []):
      vehicle_id = item.get("vehicleId")
      profile = self._fetch_vehicle_profile(vehicle_id)
      vin = profile.get("vinInfo", [{}])[0].get("basic", {}).get("vin")
      vehicles.append({
        "vin": vin,
        "vehicle_id": vehicle_id,
      })
    if not vehicles:
      raise RuntimeError("No EU vehicles found")
    return vehicles

  def _fetch_vehicles_au(self) -> Any:
    url = f"{self._env.base_url}/api/v1/spa/vehicles"
    headers = self._au_default_headers()
    headers["Stamp"] = self._next_stamp()
    resp = self.http.get(url, headers=headers)
    _raise_for_status(resp, "AU vehicle list")
    vehicles = []
    for item in resp.json().get("resMsg", {}).get("vehicles", []):
      vehicle_id = item.get("vehicleId")
      profile = self._fetch_vehicle_profile(vehicle_id)
      vin = profile.get("vinInfo", [{}])[0].get("basic", {}).get("vin")
      vehicles.append({
        "vin": vin,
        "vehicle_id": vehicle_id,
      })
    if not vehicles:
      raise RuntimeError("No AU vehicles found")
    return vehicles

  def _fetch_vehicles_cn(self) -> Any:
    url = f"{self._env.base_url}/api/v1/spa/vehicles"
    headers = self._cn_default_headers()
    resp = self.http.get(url, headers=headers)
    _raise_for_status(resp, "CN vehicle list")
    vehicles = []
    for item in resp.json().get("resMsg", {}).get("vehicles", []):
      vehicle_id = item.get("vehicleId")
      profile = self._fetch_vehicle_profile(vehicle_id, region=Region.CN)
      vin = profile.get("vinInfo", [{}])[0].get("basic", {}).get("vin")
      vehicles.append({
        "vin": vin,
        "vehicle_id": vehicle_id,
      })
    if not vehicles:
      raise RuntimeError("No CN vehicles found")
    return vehicles

  def _fetch_vehicle_profile(self, vehicle_id: str, region: Optional[Region] = None) -> Dict[str, Any]:
    region = region or self.creds.region
    url = f"{self._env.base_url}/api/v1/spa/vehicles/{vehicle_id}/profile"
    if region == Region.EU:
      headers = self._eu_default_headers()
      headers["Stamp"] = self._next_stamp()
    elif region == Region.AU:
      headers = self._au_default_headers()
      headers["Stamp"] = self._next_stamp()
    else:
      headers = self._cn_default_headers()
    resp = self.http.get(url, headers=headers)
    _raise_for_status(resp, "Vehicle profile")
    return resp.json().get("resMsg", {})

  def _login_eu(self) -> None:
    self.http.cookies.clear()
    language = self.creds.language or "en"
    auth_url = (
      f"https://{self._env.auth_host}/auth/api/v2/user/oauth2/authorize"
      f"?response_type=code&client_id={self._env.client_id}"
      f"&redirect_uri={self._env.base_url}/api/v1/user/oauth2/redirect&lang={language}&state=ccsp"
    )
    auth_resp = self.http.get(auth_url, allow_redirects=True)
    _raise_for_status(auth_resp, "EU auth redirect")
    connector = self._extract_connector_session_key(auth_resp.url)
    signin_url = f"https://{self._env.auth_host}/auth/account/signin"
    form = {
      "client_id": self._env.client_id,
      "encryptedPassword": "false",
      "orgHmgSid": "",
      "password": self.creds.password,
      "redirect_uri": f"{self._env.base_url}/api/v1/user/oauth2/redirect",
      "state": "ccsp",
      "username": self.creds.username,
      "remember_me": "false",
      "connector_session_key": connector,
      "_csrf": "",
    }
    signin_headers = {
      "content-type": "application/x-www-form-urlencoded",
      "origin": f"https://{self._env.auth_host}",
    }
    resp = self.http.post(signin_url, data=form, headers=signin_headers, allow_redirects=False)
    if resp.status_code != 302:
      raise RuntimeError(f"EU signin failed: {resp.text}")
    location = resp.headers.get("Location")
    if not location:
      raise RuntimeError("EU signin missing redirect location")
    code = self._extract_code(location)
    self._register_device_eu()
    self._exchange_code_for_token_eu(code)

  def _register_device_eu(self) -> None:
    url = f"{self._env.base_url}/api/v1/spa/notifications/register"
    headers = self._eu_default_headers()
    headers.update({
      "ccsp-service-id": self._env.client_id,
      "ccsp-application-id": self._env.app_id,
      "Stamp": self._next_stamp(),
    })
    payload = {
      "pushRegId": uuid.uuid4().hex,
      "pushType": "APNS",
      "uuid": self.session.device_id,
    }
    resp = self.http.post(url, json=payload, headers=headers)
    _raise_for_status(resp, "EU notification register")
    res = resp.json().get("resMsg", {})
    self.session.device_id = res.get("deviceId", self.session.device_id)

  def _exchange_code_for_token_eu(self, code: str) -> None:
    data = {
      "grant_type": "authorization_code",
      "code": code,
      "redirect_uri": f"{self._env.base_url}/api/v1/user/oauth2/redirect",
      "client_id": self._env.client_id,
      "client_secret": "secret",
    }
    headers = {"Content-Type": "application/x-www-form-urlencoded"}
    resp = self.http.post(self._env.token_exchange_url, data=data, headers=headers)
    _raise_for_status(resp, "EU token exchange")
    payload = resp.json()
    if resp.status_code != 200:
      raise RuntimeError(f"EU token exchange failed: {payload}")
    self.session.access_token = f"Bearer {payload.get('access_token')}"
    self.session.refresh_token = payload.get("refresh_token")
    self.session.access_token_expires_at = time.time() + float(payload.get("expires_in", 1800))
    logger.debug("EU token exchange successful; expires in %s", payload.get("expires_in", 1800))

  def _refresh_eu(self) -> None:
    if not self.session.refresh_token:
      self._login_eu()
      return
    url = self._env.base_url + "/api/v1/user/oauth2/token"
    form = {
      "grant_type": "refresh_token",
      "refresh_token": self.session.refresh_token,
      "redirect_uri": "https://www.getpostman.com/oauth2/callback",
    }
    headers = {
      "Authorization": self._env.basic_token,
      "Content-Type": "application/x-www-form-urlencoded",
      "Stamp": self._next_stamp(),
      "Host": self._env.base_url.replace("https://", ""),
      "User-Agent": "okhttp/3.10.0",
    }
    resp = self.http.post(url, data=form, headers=headers)
    _raise_for_status(resp, "EU refresh")
    payload = resp.json()
    if resp.status_code != 200:
      raise RuntimeError(f"EU refresh failed: {payload}")
    self.session.access_token = f"Bearer {payload.get('access_token')}"
    self.session.access_token_expires_at = time.time() + float(payload.get("expires_in", 1800))
    logger.debug("EU token refresh successful; expires in %s", payload.get("expires_in", 1800))

  def _ensure_control_token_eu(self) -> None:
    if self.session.has_valid_control_token():
      return
    url = f"{self._env.base_url}/api/v1/user/pin"
    headers = self._eu_default_headers()
    headers["Stamp"] = self._next_stamp()
    payload = {"deviceId": self.session.device_id, "pin": self.creds.pin}
    resp = self.http.put(url, json=payload, headers=headers)
    _raise_for_status(resp, "EU enter pin")
    body = resp.json()
    control_token = body.get("controlToken") or body.get("resMsg", {}).get("controlToken")
    if not control_token:
      raise RuntimeError(f"EU control token missing: {body}")
    self.session.control_token = f"Bearer {control_token}"
    expires = body.get("expiresTime") or body.get("resMsg", {}).get("expiresTime", 600)
    self.session.control_token_expires_at = time.time() + float(expires)
    logger.debug("EU control token acquired; expires in %s", expires)

  def _login_au(self) -> None:
    self.http.cookies.clear()
    session_url = f"{self._env.base_url}/api/v1/user/oauth2/authorize?response_type=code&client_id={self._env.client_id}&redirect_uri={self._env.base_url}/api/v1/user/oauth2/redirect&lang=en"
    self.http.get(session_url)
    auth_url = f"{self._env.base_url}/api/v1/user/signin"
    payload = {"email": self.creds.username, "password": self.creds.password, "mobileNum": ""}
    resp = self.http.post(auth_url, json=payload)
    _raise_for_status(resp, "AU signin")
    redirect = resp.json().get("redirectUrl")
    if not redirect:
      raise RuntimeError("AU signin missing redirectUrl")
    code = self._extract_code(redirect)
    self._register_device_au()
    self._exchange_code_for_token_au(code)

  def _register_device_au(self) -> None:
    url = f"{self._env.base_url}/api/v1/spa/notifications/register"
    headers = self._au_default_headers()
    headers.update({
      "ccsp-service-id": self._env.client_id,
      "ccsp-application-id": self._env.app_id,
      "Stamp": self._next_stamp(),
    })
    payload = {
      "pushRegId": uuid.uuid4().hex,
      "pushType": "GCM",
      "uuid": self.session.device_id,
    }
    resp = self.http.post(url, json=payload, headers=headers)
    _raise_for_status(resp, "AU notification register")
    res = resp.json().get("resMsg", {})
    self.session.device_id = res.get("deviceId", self.session.device_id)

  def _exchange_code_for_token_au(self, code: str) -> None:
    url = f"{self._env.base_url}/api/v1/user/oauth2/token"
    data = {
      "grant_type": "authorization_code",
      "redirect_uri": f"{self._env.base_url}/api/v1/user/oauth2/redirect",
      "code": code,
    }
    headers = {
      "Authorization": self._env.basic_token,
      "Content-Type": "application/x-www-form-urlencoded",
      "Stamp": self._next_stamp(),
    }
    resp = self.http.post(url, data=data, headers=headers)
    _raise_for_status(resp, "AU token exchange")
    payload = resp.json()
    if resp.status_code != 200:
      raise RuntimeError(f"AU token exchange failed: {payload}")
    self.session.access_token = f"Bearer {payload.get('access_token')}"
    self.session.refresh_token = payload.get("refresh_token")
    self.session.access_token_expires_at = time.time() + float(payload.get("expires_in", 1800))
    logger.debug("AU token exchange successful; expires in %s", payload.get("expires_in", 1800))

  def _refresh_au(self) -> None:
    if not self.session.refresh_token:
      self._login_au()
      return
    url = f"{self._env.base_url}/api/v1/user/oauth2/token"
    data = {
      "grant_type": "refresh_token",
      "refresh_token": self.session.refresh_token,
      "redirect_uri": "https://www.getpostman.com/oauth2/callback",
    }
    headers = {
      "Authorization": self._env.basic_token,
      "Content-Type": "application/x-www-form-urlencoded",
      "Stamp": self._next_stamp(),
    }
    resp = self.http.post(url, data=data, headers=headers)
    _raise_for_status(resp, "AU refresh")
    payload = resp.json()
    if resp.status_code != 200:
      raise RuntimeError(f"AU refresh failed: {payload}")
    self.session.access_token = f"Bearer {payload.get('access_token')}"
    self.session.access_token_expires_at = time.time() + float(payload.get("expires_in", 1800))
    logger.debug("AU token refresh successful; expires in %s", payload.get("expires_in", 1800))

  def _ensure_control_token_au(self) -> None:
    if self.session.has_valid_control_token():
      return
    url = f"{self._env.base_url}/api/v1/user/pin"
    headers = self._au_default_headers()
    headers["Stamp"] = self._next_stamp()
    payload = {"deviceId": self.session.device_id, "pin": self.creds.pin}
    resp = self.http.put(url, json=payload, headers=headers)
    _raise_for_status(resp, "AU enter pin")
    body = resp.json()
    control_token = body.get("controlToken") or body.get("resMsg", {}).get("controlToken")
    if not control_token:
      raise RuntimeError(f"AU control token missing: {body}")
    self.session.control_token = f"Bearer {control_token}"
    expires = body.get("expiresTime") or body.get("resMsg", {}).get("expiresTime", 600)
    self.session.control_token_expires_at = time.time() + float(expires)

  def _login_cn(self) -> None:
    self.http.cookies.clear()
    self._init_cn_session()
    auth_url = f"{self._env.base_url}/api/v1/user/signin"
    payload = {"email": self.creds.username, "password": self.creds.password}
    resp = self.http.post(auth_url, json=payload)
    _raise_for_status(resp, "CN signin")
    redirect = resp.json().get("redirectUrl")
    if not redirect:
      raise RuntimeError("CN signin missing redirectUrl")
    code = self._extract_code(redirect)
    self._register_device_cn()
    self._exchange_code_for_token_cn(code)

  def _init_cn_session(self) -> None:
    self.http.get(f"{self._env.base_url}/api/v1/user/oauth2/authorize?response_type=code&client_id={self._env.client_id}&redirect_uri={self._env.base_url}:443/api/v1/user/oauth2/redirect&state=test")
    headers = {"Content-Type": "application/json"}
    self.http.post(f"{self._env.base_url}/api/v1/user/language", data='{"lang":"zh"}', headers=headers)

  def _register_device_cn(self) -> None:
    url = f"{self._env.base_url}/api/v1/spa/notifications/register"
    headers = self._cn_default_headers()
    payload = {
      "pushRegId": self._env.push_reg_id,
      "providerDeviceId": self._env.provider_device_id,
      "pushType": "GCM",
      "uuid": self.session.device_id,
    }
    resp = self.http.post(url, json=payload, headers=headers)
    _raise_for_status(resp, "CN notification register")
    res = resp.json().get("resMsg", {})
    self.session.device_id = res.get("deviceId", self.session.device_id)

  def _exchange_code_for_token_cn(self, code: str) -> None:
    url = f"{self._env.base_url}/api/v1/user/oauth2/token"
    data = {
      "grant_type": "authorization_code",
      "redirect_uri": f"{self._env.base_url}:443/api/v1/user/oauth2/redirect",
      "code": code,
    }
    headers = {
      "Authorization": self._env.basic_token,
      "Content-Type": "application/x-www-form-urlencoded",
    }
    resp = self.http.post(url, data=data, headers=headers)
    _raise_for_status(resp, "CN token exchange")
    payload = resp.json()
    if resp.status_code != 200:
      raise RuntimeError(f"CN token exchange failed: {payload}")
    self.session.access_token = f"Bearer {payload.get('access_token')}"
    self.session.refresh_token = payload.get("refresh_token")
    self.session.access_token_expires_at = time.time() + float(payload.get("expires_in", 1800))

  def _refresh_cn(self) -> None:
    if not self.session.refresh_token:
      self._login_cn()
      return
    url = f"{self._env.base_url}/api/v1/user/oauth2/token"
    data = {
      "grant_type": "refresh_token",
      "refresh_token": self.session.refresh_token,
      "redirect_uri": "https://www.getpostman.com/oauth2/callback",
    }
    headers = {
      "Authorization": self._env.basic_token,
      "Content-Type": "application/x-www-form-urlencoded",
    }
    resp = self.http.post(url, data=data, headers=headers)
    _raise_for_status(resp, "CN refresh")
    payload = resp.json()
    if resp.status_code != 200:
      raise RuntimeError(f"CN refresh failed: {payload}")
    self.session.access_token = f"Bearer {payload.get('access_token')}"
    self.session.access_token_expires_at = time.time() + float(payload.get("expires_in", 1800))
    logger.debug("CN token refresh successful; expires in %s", payload.get("expires_in", 1800))

  def _ensure_control_token_cn(self) -> None:
    if self.session.has_valid_control_token():
      return
    url = f"{self._env.base_url}/api/v1/user/pin?token="
    headers = self._cn_default_headers()
    payload = {"deviceId": self.session.device_id, "pin": self.creds.pin}
    resp = self.http.put(url, json=payload, headers=headers)
    _raise_for_status(resp, "CN enter pin")
    body = resp.json()
    control_token = body.get("controlToken") or body.get("resMsg", {}).get("controlToken")
    if not control_token:
      raise RuntimeError(f"CN control token missing: {body}")
    self.session.control_token = f"Bearer {control_token}"
    expires = body.get("expiresTime") or body.get("resMsg", {}).get("expiresTime", 600)
    self.session.control_token_expires_at = time.time() + float(expires)

  def _ca_get_preauth(self, vehicle: Dict[str, Any]) -> str:
    url = f"{self._env.base_url}/tods/api/vrfypin"
    headers = self._ca_headers()
    headers["vehicleId"] = vehicle.get("vehicle_id")
    payload = {"pin": self.creds.pin}
    resp = self.http.post(url, json=payload, headers=headers)
    _raise_for_status(resp, "CA verify pin")
    result = resp.json().get("result", {})
    return result.get("pAuth")

  def _extract_connector_session_key(self, url: str) -> str:
    patterns = [r"connector_session_key%3D([0-9a-fA-F-]{36})", r"connector_session_key=([0-9a-fA-F-]{36})"]
    for pattern in patterns:
      match = re.search(pattern, url)
      if match:
        return match.group(1)
    raise RuntimeError(f"connector_session_key not found in {url}")

  def _extract_code(self, location: str) -> str:
    parsed = urlparse(location)
    query = parse_qs(parsed.query)
    code = query.get("code", [None])[0]
    if not code:
      raise RuntimeError(f"Authorization code missing in {location}")
    return code

  def _next_stamp(self) -> str:
    if not self._stamp:
      raise RuntimeError("Stamp generator not configured for region")
    return self._stamp()

  def _offset(self) -> str:
    return f"{-(time.localtime().tm_gmtoff) / 3600:.0f}"

  def _ca_headers(self) -> Dict[str, str]:
    origin_value = self._env.origin or "SPA"
    headers = {
      "from": origin_value,
      "language": "1",
      "offset": self._offset(),
      "Content-Type": "application/json",
      "Origin": self._env.base_url,
      "Referer": f"{self._env.base_url}/login",
    }
    if self.session.access_token:
      headers["accessToken"] = self.session.access_token
    return headers

  def _eu_default_headers(self) -> Dict[str, str]:
    return {
      "Authorization": self.session.access_token,
      "ccsp-device-id": self.session.device_id,
      "ccsp-application-id": self._env.app_id,
      "Content-Type": "application/json",
      "offset": self._offset(),
    }

  def _eu_vehicle_headers(self) -> Dict[str, str]:
    headers = self._eu_default_headers()
    headers["Authorization"] = self.session.control_token
    return headers

  def _au_default_headers(self) -> Dict[str, str]:
    return {
      "Authorization": self.session.access_token,
      "ccsp-device-id": self.session.device_id,
      "ccsp-application-id": self._env.app_id,
      "Content-Type": "application/json",
      "offset": self._offset(),
    }

  def _au_vehicle_headers(self) -> Dict[str, str]:
    headers = self._au_default_headers()
    headers["Authorization"] = self.session.control_token
    return headers

  def _cn_default_headers(self) -> Dict[str, str]:
    return {
      "Authorization": self.session.access_token,
      "Content-Type": "application/json",
      "ccsp-device-id": "2e062595-28e0-4bcb-a75a-1b395cde337c",
      "ccsp-application-id": self._env.app_id,
      "User-Agent": "okhttp/4.4.0",
      "offset": self._offset(),
    }

  def _cn_vehicle_headers(self) -> Dict[str, str]:
    headers = self._cn_default_headers()
    headers["Authorization"] = self.session.control_token
    headers["AuthorizationCCSP"] = self.session.control_token
    return headers


def _raise_for_status(resp: Response, context: str) -> None:
  try:
    resp.raise_for_status()
  except HTTPError as err:
    message = _extract_error_message(resp)
    raise RuntimeError(f"{context} failed: {message}") from err


def _extract_error_message(resp: Response) -> str:
  try:
    body = resp.json()
  except ValueError:
    body = resp.text
  return json.dumps(body, ensure_ascii=False) if isinstance(body, (dict, list)) else str(body)


__all__ = [
  "Region",
  "KiaCredentials",
  "KiaSession",
  "RegionConfig",
  "REGION_CONFIG",
  "StampGenerator",
  "KiaBaseClient",
  "Session",
  "Response",
  "requests",
  "HTTPError",
  "_raise_for_status",
  "_extract_error_message",
  "json_dumps",
]