from __future__ import annotations

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


class KiaAutoLockClient(KiaBaseClient):
  """New wrapper reusing shared KiaBaseClient logic for backward compatibility."""

  pass


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
