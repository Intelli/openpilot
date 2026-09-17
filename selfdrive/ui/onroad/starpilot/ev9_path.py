"""Animated EV9 path colors; geometry and drawing stay in the model renderer."""
import colorsys
import math

import pyray as rl

from openpilot.system.ui.lib.shader_polygon import Gradient


def ev9_path_state(sm, started_frame: int, now: float) -> tuple[float, bool]:
  def fresh(service):
    return (sm.valid.get(service, False) and sm.alive.get(service, False) and
            sm.recv_frame.get(service, -1) >= started_frame and 0 <= now - sm.recv_time.get(service, 0.0) <= 1.0)

  acceleration = float(sm["carState"].aEgo) if fresh("carState") else 0.0
  # latActive includes always-on lateral, unlike the ACC engagement flag.
  active = bool(fresh("carState") and fresh("carControl") and sm["carControl"].latActive)
  return acceleration if math.isfinite(acceleration) else 0.0, active


def _color(h, s, l, a):
  rgb = colorsys.hls_to_rgb((h % 360) / 360, max(0, min(1, l)), max(0, min(1, s)))
  return rl.Color(*(int(c * 255) for c in rgb), int(max(0, min(1, a)) * 255))


def _blend(a, b, mix):
  return rl.Color(*(round(getattr(a, c) * (1 - mix) + getattr(b, c) * mix) for c in ("r", "g", "b", "a")))


class EV9Path:
  ACCEL_START_THRESHOLD = 0.25
  ACCEL_STOP_THRESHOLD = 0.15
  ACCEL_FADE_IN_SECONDS = 0.5
  ACCEL_FADE_OUT_SECONDS = 1.0
  OCEAN_STOPS = (
    (0.00, 206.0, 0.70, 0.32, 0.85),
    (0.35, 202.0, 0.72, 0.40, 0.75),
    (0.70, 198.0, 0.74, 0.55, 0.65),
    (1.00, 192.0, 0.60, 0.68, 0.55),
  )

  def __init__(self):
    self.reset()

  def reset(self):
    self._last_update_time = None
    self._active = False
    self._accel_presence = 0.0
    self._accel_state = False
    self._wave_phase = 0.0
    self._rainbow_phase_shift = 0.0
    self._rainbow_wave_phase = 0.0

  def update(self, *, now: float, acceleration: float, active: bool):
    elapsed = 0.0 if self._last_update_time is None else now - self._last_update_time
    if elapsed < 0 or elapsed > 1.0:
      self.reset()
      elapsed = 0.0
    self._last_update_time = now
    dt = min(elapsed, 0.1)
    self._active = active

    if active:
      acceleration = acceleration if math.isfinite(acceleration) else 0.0
      if acceleration >= self.ACCEL_START_THRESHOLD:
        self._accel_state = True
      elif acceleration <= self.ACCEL_STOP_THRESHOLD:
        self._accel_state = False
      if self._accel_state:
        self._accel_presence = min(1.0, self._accel_presence + dt / self.ACCEL_FADE_IN_SECONDS)
      else:
        self._accel_presence = max(0.0, self._accel_presence - dt / self.ACCEL_FADE_OUT_SECONDS)
      multiplier = 1.5 + self._accel_presence * 0.4 if self._accel_presence > 0 else 1.0
      self._wave_phase = (self._wave_phase + 0.35 * multiplier * dt) % math.tau
      self._rainbow_phase_shift = (self._rainbow_phase_shift + 0.10 * multiplier * dt) % 1.0
      self._rainbow_wave_phase = (self._rainbow_wave_phase + 0.8 * dt) % math.tau
    else:
      self._accel_presence = 0.0
      self._accel_state = False
      self._wave_phase = self._rainbow_phase_shift = self._rainbow_wave_phase = 0.0

  def _ocean_color(self, position):
    hue, saturation, lightness, alpha = self.OCEAN_STOPS[-1][1:]
    for left, right in zip(self.OCEAN_STOPS, self.OCEAN_STOPS[1:], strict=False):
      if position <= right[0]:
        mix = (position - left[0]) / (right[0] - left[0])
        hue, saturation, lightness, alpha = (a + (b - a) * mix for a, b in zip(left[1:], right[1:], strict=True))
        break
    presence = self._accel_presence
    wave = 0.5 * math.sin(self._wave_phase + position * 3)
    base_wave = 1.0 - presence
    return _color(hue + wave * (10 + 3 * presence) * base_wave,
                  saturation - wave * (0.05 + 0.08 * presence) * base_wave + 0.08 * presence,
                  lightness + wave * (0.08 + 0.03 * presence) * base_wave + 0.05 * presence,
                  0.45 + 0.45 * (alpha - wave * (0.04 + 0.05 * presence) * base_wave + 0.08 * presence))

  def _rainbow_color(self, position):
    primary = 0.5 * math.sin(self._rainbow_wave_phase + position * math.tau * 0.8) + 0.5
    secondary = 0.5 * math.sin(self._rainbow_wave_phase * 1.3 + position * math.tau * 0.45) + 0.5
    return _color(((position + self._rainbow_phase_shift + (primary - 0.5) * 0.25) % 1) * 360,
                  0.80 + 0.14 * self._accel_presence + (secondary - 0.5) * 0.24,
                  0.52 + 0.10 * self._accel_presence + (0.5 - primary) * 0.20,
                  0.66 + 0.18 * self._accel_presence + (secondary - 0.5) * 0.12)

  def get_gradient(self) -> Gradient:
    stops = [i / 8 for i in range(9)]
    colors = []
    for position in stops:
      base = _blend(self._ocean_color(position), self._rainbow_color(position), self._accel_presence) if self._active else \
        rl.Color(150, 150, 150, round(80 * (1 - position)))
      colors.append(base)
    return Gradient(start=(0.0, 1.0), end=(0.0, 0.0), colors=colors, stops=stops)
