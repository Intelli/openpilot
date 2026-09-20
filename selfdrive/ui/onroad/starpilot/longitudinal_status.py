"""EV9 startup mode and vehicle READY notice, independent of cruise engagement."""
from dataclasses import dataclass


# HyundaiSafetyFlags: the EV9 alias is meaningful only with EV and angle steering.
EV9_SAFETY_IDENTITY = 1 | 256 | 1024
LONGITUDINAL_FLAG = 4
NOTICE_SECONDS = 30.0


@dataclass(frozen=True)
class LongitudinalSample:
  now: float
  session_start: float
  started: bool
  identity_ev9: bool
  identity_time: float
  panda_time: float
  panda_valid: bool
  safety_models: tuple[str, ...]
  safety_params: tuple[int, ...]
  panda_fault: bool
  events_time: float
  events_valid: bool
  initializing: bool
  control_time: float
  control_valid: bool
  vehicle_time: float
  vehicle_valid: bool
  ready_time: float
  vehicle_ready: bool


def _fresh(timestamp: float, sample: LongitudinalSample, maximum_age: float) -> bool:
  return timestamp > 0 and timestamp >= sample.session_start and 0 <= sample.now - timestamp <= maximum_age


def _identified_ev9(sample: LongitudinalSample) -> bool:
  # carParams publishes every 50 seconds and may arrive just before the UI starts.
  return sample.identity_ev9 and sample.identity_time > 0 and 0 <= sample.now - sample.identity_time <= 55.0


def _ready_state(sample: LongitudinalSample) -> bool | None:
  # A fresh publication can contain an old CAN value. Check both timestamps.
  if not sample.vehicle_valid or not _fresh(sample.vehicle_time, sample, 0.5) or not _fresh(sample.ready_time, sample, 0.5):
    return None
  return sample.vehicle_ready


def longitudinal_status(sample: LongitudinalSample) -> str | None:
  """Identify the configured controller and power state; not an ECU-health certification."""
  # Use carParams only for identity. Current-session Panda configuration determines mode,
  # including fallback, which can differ from the initial/cached carParams.
  if not sample.started or not _identified_ev9(sample):
    return None
  if (not sample.panda_valid or sample.panda_fault or not _fresh(sample.panda_time, sample, 1.0) or
      sample.safety_models != ("hyundaiCanfd",) or len(sample.safety_params) != 1):
    return None
  safety_param = sample.safety_params[0]
  if safety_param & EV9_SAFETY_IDENTITY != EV9_SAFETY_IDENTITY:
    return None
  if (not sample.events_valid or not _fresh(sample.events_time, sample, 2.5) or sample.initializing or
      not sample.control_valid or not _fresh(sample.control_time, sample, 0.5)):
    return None
  if not safety_param & LONGITUDINAL_FLAG:
    return "Stock ACC"
  ready = _ready_state(sample)
  if ready is None:
    return None
  return "OP long" if ready else "OP long ready"


class LongitudinalStatus:
  def __init__(self):
    self._session_start: float | None = None
    self._show_until: float | None = None
    self._ready_seen = False

  def update(self, sample: LongitudinalSample) -> str | None:
    if not sample.started:
      self._session_start = self._show_until = None
      self._ready_seen = False
      return None
    if sample.session_start != self._session_start:
      self._session_start = sample.session_start
      self._show_until = None
      self._ready_seen = False

    status = longitudinal_status(sample)
    if self._show_until is None and status is None:
      # Show initialization without claiming a mode or consuming its notice window.
      return "Please wait..." if _identified_ev9(sample) else None
    if self._show_until is None and status is not None:
      self._show_until = sample.now + NOTICE_SECONDS
    # Keep the pre-READY prompt available while the driver completes startup.
    # Give the final mode its own 30 seconds, once per ignition session.
    if status is not None and not self._ready_seen:
      if status == "OP long ready" or _ready_state(sample) is True:
        self._show_until = sample.now + NOTICE_SECONDS
      self._ready_seen = _ready_state(sample) is True
    if not sample.identity_ev9 or self._show_until is None or sample.now >= self._show_until:
      return None
    return status or "Long status unavailable"
