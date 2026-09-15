"""EV9 steering-warning scope and speed policy."""
import math

from opendbc.car import structs
from opendbc.car.hyundai.values import CAR, HyundaiFlags


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
  return speed_mps > threshold or abs(lateral_state.steeringAngleDesiredDeg) >= 90.0
