"""EV9 angle-control configuration and manual handoff; no persistent parameter I/O."""
from collections.abc import Mapping
from dataclasses import dataclass
import math

from opendbc.car import DT_CTRL

EV9_PANDA_LIMIT_SPEED_MPS = 42.0 / 3.6 + 0.1
EV9_HIGH_LATERAL_LIMIT = 4.2
_MISSING = object()


def _read(source, *names):
  for name in names:
    value = source.get(name, _MISSING) if isinstance(source, Mapping) else getattr(source, name, _MISSING)
    if value is not _MISSING:
      return value
  return _MISSING


def _number(value, default):
  try:
    result = float(value)
    return result if math.isfinite(result) else default
  except (TypeError, ValueError, OverflowError):
    return default


@dataclass(frozen=True)
class EV9AngleConfig:
  limit_speed_mps: float = 32.0 / 3.6
  override_effort_scale: float = 0.1
  shared_autonomy_mode: int = 0

  @classmethod
  def from_toggles(cls, toggles):
    """Consume broadcast attributes or a mapping, with former Hkg parameter aliases.

    Missing values retain the historical defaults. The openpilot parameter registry
    and broadcast producer are separate integration points; this never reads Params.
    """
    speed = _number(_read(toggles, 'hkg_tuning_angle_custom_limit_max_speed_kph',
                          'HkgTuningAngleCustomLimitMaxSpeedKph', 'hkgTuningAngleCustomLimitMaxSpeedKph'), 32.0)
    effort = _number(_read(toggles, 'hkg_tuning_angle_override_effort_percent',
                           'HkgTuningAngleOverrideEffortPercent', 'hkgTuningAngleOverrideEffortPercent'), 10.0)
    mode = _read(toggles, 'hkg_shared_autonomy_mode', 'HkgSharedAutonomyMode', 'hkgSharedAutonomyMode')
    if mode is _MISSING:
      enabled = _read(toggles, 'hkg_shared_autonomy_enabled', 'HkgSharedAutonomyEnabled', 'hkgSharedAutonomyEnabled')
      mode = 1 if _number(enabled, 0.0) != 0.0 else 0
    return cls((speed if speed > 0 else 32.0) / 3.6, min(100.0, max(10.0, effort)) / 100.0,
               min(2, max(0, int(_number(mode, 0.0)))))


def ev9_hands_on(raw, timestamp, now_nanos) -> bool:
  """HOD 1/2 = touch, 3/4 = grip; reserved, missing and stale samples are not intent."""
  return raw in (1, 2, 3, 4) and timestamp > 0 and 0 <= now_nanos - timestamp <= 300_000_000


def apply_override_gain(base_gain: float, override_active: bool, effort_scale: float) -> float:
  if not override_active:
    return base_gain
  scale = min(1.0, max(0.1, effort_scale))
  return min(1.0, max(0.10, round(base_gain * scale / 0.004) * 0.004))


@dataclass(frozen=True)
class EV9ManualControlOutput:
  override_active: bool = False
  manual_override: bool = False
  keep_active: bool = False


@dataclass
class EV9ManualControlState:
  override_active: bool = False
  torque_override_active: bool = False
  manual_latched: bool = False
  low_demand_timer: float = 0.0
  reentry_guard_timer: float = 0.0
  grip_dwell_timer: float = 0.0
  keep_active_latched: bool = False

  def reset(self):
    self.override_active = False
    self.torque_override_active = False
    self.manual_latched = False
    self.low_demand_timer = 0.0
    self.reentry_guard_timer = 0.0
    self.grip_dwell_timer = 0.0
    self.keep_active_latched = False

  def update(self, config: EV9AngleConfig, *, lat_active, steering_torque, steering_pressed, hands_on,
             v_ego, desired_angle, measured_angle, steer_threshold) -> EV9ManualControlOutput:
    if not lat_active:
      self.reset()
      return EV9ManualControlOutput()

    torque = abs(steering_torque)
    exit_threshold = max(0.0, steer_threshold - 40.0)
    if config.shared_autonomy_mode == 0:
      previous_override = self.override_active
      self.reset()
      self.override_active = bool(steering_pressed) if config.override_effort_scale >= 0.999 else \
        torque >= (exit_threshold if previous_override else steer_threshold)
      return EV9ManualControlOutput(override_active=self.override_active)

    self.override_active = False
    self.torque_override_active = torque >= exit_threshold if self.torque_override_active else bool(hands_on and torque >= steer_threshold)
    override_active = self.torque_override_active
    self.reentry_guard_timer = max(0.0, self.reentry_guard_timer - DT_CTRL)
    self.grip_dwell_timer = self.grip_dwell_timer + DT_CTRL if hands_on else 0.0
    reentry_allowed = self.reentry_guard_timer <= 0.0 or self.grip_dwell_timer >= 0.1
    if not self.manual_latched:
      # Preserve the historical speed gate on entry only, not an automatic release.
      self.manual_latched = bool(v_ego <= config.limit_speed_mps and hands_on and self.torque_override_active and reentry_allowed)
      self.low_demand_timer = 0.0

    if self.manual_latched:
      low_demand = not steering_pressed and abs(desired_angle - measured_angle) <= 1.0
      self.low_demand_timer = self.low_demand_timer + DT_CTRL if low_demand else 0.0
      if not hands_on or self.low_demand_timer >= 1.0:
        self.manual_latched = False
        self.torque_override_active = False
        self.low_demand_timer = 0.0
        self.reentry_guard_timer = 2.0
        self.grip_dwell_timer = 0.0

    if self.manual_latched:
      self.keep_active_latched = abs(measured_angle) >= (15.0 if self.keep_active_latched else 90.0)
    else:
      self.keep_active_latched = False
    return EV9ManualControlOutput(override_active, self.manual_latched, self.keep_active_latched)
