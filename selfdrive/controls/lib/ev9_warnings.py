"""EV9 steering-warning scope and speed policy."""
import math
from dataclasses import dataclass

from opendbc.car import structs
from opendbc.car.hyundai.values import CAR, HyundaiFlags

EV9_HIGH_ANGLE_WARNING_DEG = 90.0
EV9_WARNING_CLEAR_ANGLE_DEG = 85.0
EV9_WARNING_TRACKING_GAP_DEG = 2.5
EV9_WARNING_CLEAR_GAP_DEG = 1.0
EV9_WARNING_PERSISTENCE_SECONDS = 0.3


def ev9_angle_warnings_enabled(CP) -> bool:
  return (CP.carFingerprint == CAR.KIA_EV9 and
          bool(CP.flags & HyundaiFlags.CANFD_ANGLE_STEERING) and
          CP.steerControlType == structs.CarParams.SteerControlType.angle)


def ev9_alert_speed_kph(value) -> float:
  try:
    speed = float(value)
  except (TypeError, ValueError, OverflowError):
    return 50.0
  return min(50.0, max(10.0, speed)) if math.isfinite(speed) else 50.0


def steering_saturation_warning_allowed(CP, lateral_state, speed_mps, toggles) -> bool:
  if not ev9_angle_warnings_enabled(CP) or not hasattr(lateral_state, "steeringAngleDesiredDeg"):
    return True
  threshold = ev9_alert_speed_kph(getattr(toggles, "hkg_tuning_ev9_alerts_speed_kph", 50.0)) / 3.6
  return speed_mps > threshold or abs(lateral_state.steeringAngleDesiredDeg) >= EV9_HIGH_ANGLE_WARNING_DEG


@dataclass
class EV9SteeringWarning:
  """Debounce insufficient steering independently of the generic hands-off warning."""
  elapsed: float = 0.0
  warning: bool = False
  last_time: float | None = None

  def update(self, *, now, active, speed, requested, measured, output, threshold_kph, manual_following=False):
    dt = 0.01 if self.last_time is None else now - self.last_time
    self.last_time = now
    if not all(math.isfinite(value) for value in (now, speed, requested, measured, dt)) or dt < 0 or dt > 0.2:
      self.elapsed, self.warning = 0.0, False
      self.last_time = now if math.isfinite(now) else None
      return False
    angle_threshold = EV9_WARNING_CLEAR_ANGLE_DEG if self.warning else EV9_HIGH_ANGLE_WARNING_DEG
    eligible = abs(requested) >= angle_threshold or speed > ev9_alert_speed_kph(threshold_kph) / 3.6
    direction = 1.0 if requested >= 0 else -1.0
    tracking_shortfall = direction * (requested - measured)
    command_shortfall = direction * (requested - output) if output is not None and math.isfinite(output) else 0.0
    gap_threshold = EV9_WARNING_CLEAR_GAP_DEG if self.warning else EV9_WARNING_TRACKING_GAP_DEG
    insufficient = max(tracking_shortfall, command_shortfall) > gap_threshold
    if not active or speed <= 0.3 or manual_following or not eligible or not insufficient:
      self.elapsed, self.warning = 0.0, False
      return False
    self.elapsed += max(dt, 0.0)
    self.warning |= self.elapsed >= EV9_WARNING_PERSISTENCE_SECONDS - 1e-6
    return self.warning
