from __future__ import annotations

try:
  from .kia_lock import (  # type: ignore[attr-defined]
    Region,
    KiaCredentials,
    KiaSession,
    RegionConfig,
    REGION_CONFIG,
    StampGenerator,
    KiaAutoLockClient,
    requests,
    Response,
    Session,
    HTTPError,
    _raise_for_status,
    _extract_error_message,
  )
except ImportError:  # pragma: no cover - script execution fallback
  from kia_lock import (  # type: ignore[no-redef]
    Region,
    KiaCredentials,
    KiaSession,
    RegionConfig,
    REGION_CONFIG,
    StampGenerator,
    KiaAutoLockClient,
    requests,
    Response,
    Session,
    HTTPError,
    _raise_for_status,
    _extract_error_message,
  )


class KiaBaseClient(KiaAutoLockClient):
  pass


__all__ = [
  "Region",
  "KiaCredentials",
  "KiaSession",
  "RegionConfig",
  "REGION_CONFIG",
  "StampGenerator",
  "KiaBaseClient",
  "KiaAutoLockClient",
  "Session",
  "Response",
  "requests",
  "HTTPError",
  "_raise_for_status",
  "_extract_error_message",
]
