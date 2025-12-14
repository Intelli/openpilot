# Kia Auto-Lock Python Helper

This folder contains the Python implementation for issuing remote lock commands and polling vehicle status across supported Kia/Hyundai regions. The primary entry points are `kia_lock.py` (locking) and `kia_status.py` (status polling), both powered by the shared helpers in `kia_shared.py`.

## Components

- **`kia_shared.py`**: Core shared implementation (HTTP session, region metadata, token handling). Both lock and status clients import from here.
- **`kia_lock.py`**: Implements `KiaAutoLockClient` using the shared helpers. Replaces the old bespoke implementation (previously `kia_lock_old.py`).
- **`kia_status.py`**: Defines `KiaStatusClient` for real-time vehicle status queries with normalized outputs.
- **`lock_cli.py`**: CLI harness for manual locking tests (requires Python 3.8+).
- **`status_cli.py`**: CLI harness for manual status polling with pretty-printed JSON output.

## Dependencies

- **Optional**: `requests` (`pip install requests`). The module automatically falls back to built-in `urllib` if `requests` is unavailable (e.g., on C3X hardware).

## Programmatic Usage

To poll live vehicle data instead of issuing commands:

```python
from openpilot.auto_lock.kia_status import KiaStatusClient, KiaCredentials, Region

creds = KiaCredentials(
  username="user@example.com",
  password="your-account-password",
  pin="1234",
  region=Region.CA,
  vin="KNXXX...",
)

client = KiaStatusClient(creds)
status = client.status()
```

The returned dictionary contains normalized keys (door locks, climate state, battery information, timestamps) regardless of region.

```python
from openpilot.auto_lock.kia_lock import KiaAutoLockClient, KiaCredentials, Region

creds = KiaCredentials(
  username="user@example.com",
  password="your-account-password",
  pin="1234",
  region=Region.CA,
  vin="KNXXX...",  # Optional if only one vehicle
  vehicle_id=None,
  language="en",   # Optional, primarily for EU region
)

client = KiaAutoLockClient(creds)
client.lock()
```

### Integration Tips

- **Credential Sourcing**: Avoid hardcoding secrets. Prefer reading from secure storage, environment variables, or OpenPilot parameter servers.
- **Error Handling**: Wrap `client.lock()` in try/except and surface `RuntimeError` messages to the UI or logs. The client surfaces server error codes for troubleshooting.
- **Session Reuse**: Reuse a single `KiaAutoLockClient` instance if multiple commands are needed; tokens are cached internally.
- **VIN/Vehicle Selection**: Either supply `vin` or `vehicle_id` when multiple vehicles exist on the account. For single-vehicle accounts, both may be left `None`.
- **Threading**: The client is not explicitly thread-safe. Serialize access when integrating with background services.

## CLI Testing

Use the CLI script during development or on-device testing:

```bash
python3 openpilot/auto_lock/lock_cli.py "username" "password" "pin" CA \
  "<vin-or-empty>" "<vehicle-id-or-empty>" --language en --verbose
```

- **Region Choices**: `US`, `CA`, `EU`, `CN`, `AU`.
- **VIN/Vehicle ID**: Omit these parameters when the account has one vehicle. Provide at least one when multiple vehicles exist (Canada `vehicle_id` is required for command authorization).
- **Language**: Optional, primarily for EU (e.g., `--language fr`).
- **Verbose Mode**: Adds debug logging to help diagnose authentication issues.

### Status CLI

```bash
python3 openpilot/auto_lock/status_cli.py "username" "password" "pin" CA \
  "<vin-or-empty>" "<vehicle-id-or-empty>" --language en --verbose
```

- **Output**: Prints normalized status JSON for quick inspection.
- **Verbose Mode**: Includes the same detailed login logs as the lock CLI when troubleshooting authentication flows.

## Adding New Regions or Updates

- **Check Bluelinky Reference**: When behavior deviates (headers, payload keys, stamps), consult the `bluelinky` Node.js repository for region specifics.
- **Maintain Fallback Compatibility**: Ensure new HTTP flows still function without `requests` by staying within the `Session` abstraction in `kia_shared.py`.
- **Testing**: Run `lock_cli.py` and `status_cli.py` per region to confirm successful login and locking/status retrieval before integrating changes into higher-level workflows.

## Calling from OpenPilot Services

- **Import Path**: Reference modules as `openpilot.auto_lock.kia_lock` to leverage the repository’s import root.
- **Service Hooks**: For example, within a background manager:

```python
from openpilot.auto_lock.kia_lock import KiaAutoLockClient, KiaCredentials, Region

def lock_vehicle(creds_dict):
  creds = KiaCredentials(**creds_dict)
  client = KiaAutoLockClient(creds)
  try:
    client.lock()
  except RuntimeError as err:
    handle_error(str(err))
```

- **Scheduling**: Integrate with existing timers or event triggers (e.g., lock on ignition off). Ensure you respect rate limits and user consent.

## Troubleshooting Cheatsheet

- **CA 7901 Error**: Ensure `from`, `language`, and `offset` are included in the payload (already handled). Double-check remote services are active.
- **401/Invalid PIN**: Confirm the remote services PIN (not radio PIN) and handle the raised exception gracefully.
- **Multiple Vehicles**: Provide `vehicle_id` if the account manages more than one vehicle; the client selects the first by default otherwise.
- **Missing `requests`**: The fallback HTTP client is automatic; no extra configuration needed on C3X.

## Contributing

- **Keep Files Lean**: `kia_lock.py` is large; prefer adding helpers over inlining large code blocks to avoid lint issues.
- **Log Carefully**: Debug logs may leak sensitive server payloads. Mask or remove before enabling in production.
