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
