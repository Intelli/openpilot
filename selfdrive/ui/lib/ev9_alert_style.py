from cereal import log
from opendbc.car.hyundai.values import CAR


def hide_normal_alert(status, alert_type, hide_alerts):
  # Compact steering-limit warnings remain visible even with general banners hidden.
  return status == log.SelfdriveState.AlertStatus.normal and hide_alerts and alert_type.split('/')[0] != 'steerSaturated'


def alert_background_alpha(status, CP):
  if status == log.SelfdriveState.AlertStatus.normal and CP is not None and CP.carFingerprint == CAR.KIA_EV9:
    return 128
  return 255 * 0.90
