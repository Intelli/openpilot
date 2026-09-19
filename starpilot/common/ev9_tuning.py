import math


def read_ev9_tuning(params):
  """Read off the realtime path; broadcast these values even before fingerprinting."""
  settings = (
    ("HkgTuningAngleCustomLimitMaxSpeedKph", "hkg_tuning_angle_custom_limit_max_speed_kph", 40, 10, 40),
    ("HkgTuningAngleOverrideEffortPercent", "hkg_tuning_angle_override_effort_percent", 10, 10, 100),
    ("HkgSharedAutonomyMode", "hkg_shared_autonomy_mode", 0, 0, 2),
  )
  values = {}
  for key, attribute, default, minimum, maximum in settings:
    try:
      value = float(params.get(key))
      if not math.isfinite(value):
        value = default
    except (TypeError, ValueError):
      value = default
    values[attribute] = int(max(minimum, min(value, maximum)))
  return values


def ev9_limit_speed_mps(toggles):
  """Shared configured EV9 envelope; missing/invalid values use the 40 km/h default."""
  key = 'hkg_tuning_angle_custom_limit_max_speed_kph'
  try:
    value = float(toggles.get(key, 40) if isinstance(toggles, dict) else getattr(toggles, key, 40))
    if not math.isfinite(value):
      value = 40.
  except (TypeError, ValueError, OverflowError):
    value = 40.
  return max(10., min(value, 40.)) / 3.6
