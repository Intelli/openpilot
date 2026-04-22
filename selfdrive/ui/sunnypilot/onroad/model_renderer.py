"""
Copyright (c) 2021-, Haibin Wen, sunnypilot, and a number of other contributors.

This file is part of sunnypilot and is licensed under the MIT License.
See the LICENSE.md file in the root directory for more details.
"""
import math
import time

import pyray as rl

from openpilot.common.params import Params
from openpilot.system.ui.lib.application import FontWeight, gui_app
from openpilot.system.ui.lib.shader_polygon import draw_polygon
from openpilot.system.ui.lib.text_measure import measure_text_cached

from openpilot.selfdrive.ui.sunnypilot.onroad.chevron_metrics import ChevronMetrics
from openpilot.selfdrive.ui.sunnypilot.onroad.rainbow_path import RainbowPath

CENTERING_SIGNAL_STALE_S = 1.0
CENTERING_CENTER_BAND_M = 0.08
CENTERING_PANEL_MIN_VISIBLE_S = 0.5
CENTERING_HIGHLIGHT_FREQ_HZ = 1.0
HOD_SIGNAL_STALE_S = 0.4
HOD_TAP_GAP_S = 0.55
HOD_TAP_DISPLAY_HOLD_S = 2.0

SOURCE_NONE = 0
SOURCE_EDGE = 2


def _enum_raw(value) -> int:
  return int(getattr(value, "raw", value))


class ModelRendererSP:
  def __init__(self):
    self.rainbow_path = RainbowPath()
    self.chevron_metrics = ChevronMetrics()
    self.params = Params()

    self._title_font = gui_app.font(FontWeight.SEMI_BOLD)
    self._detail_font = gui_app.font(FontWeight.MEDIUM)
    self.advanced_lane_centering_enabled = self.params.get_bool("AdvancedLaneCentering")
    self.prev_lat_active = False

    self.centering_display_valid = False
    self.centering_display_offset_m = 0.0
    self.centering_adjusting_display = False
    self.centering_edge_mode = False
    self.centering_status_active = False
    self.centering_within_center_band = False
    self.centering_steering_direction_sign = 0.0
    self.centering_indicator_edge_sign = 0.0
    self.centering_indicator_source = SOURCE_NONE
    self.centering_indicator_last_nonzero_source = SOURCE_NONE

    self.centering_highlight_strength = 0.0
    self.centering_highlight_phase = 0.0
    self.centering_highlight_last_update = time.monotonic()

    self.centering_panel_visible_state = False
    self.centering_panel_request_active = False
    self.centering_panel_request_start = time.monotonic()
    self.centering_panel_visible = False

    self.hod_dir_status_raw = 0
    self.hod_touch = False
    self.hod_grip = False
    self.hod_strong = False
    self._hod_prev_dir_status_raw = 0
    self._hod_prev_touch = False
    self._hod_prev_strong = False
    self._hod_tap_count_pending = 0
    self._hod_tap_finalize_deadline = 0.0
    self._hod_last_tap_label = "none"
    self._hod_last_tap_time = 0.0
    self.hod_debug_available = False
    self.hod_debug_primary = "HOD unavailable"
    self.hod_debug_secondary = "Taps: none"

  def update_lane_centering_ui(self, sm) -> None:
    now = time.monotonic()
    selfdrive_state = sm["selfdriveState"]

    self.centering_status_active = False
    self.centering_display_valid = False
    self.centering_display_offset_m = 0.0
    self.centering_adjusting_display = False
    self.centering_edge_mode = False
    self.centering_indicator_source = SOURCE_NONE
    self.centering_indicator_edge_sign = 0.0
    self.centering_highlight_strength = 0.0
    self.centering_panel_visible = False
    self.centering_within_center_band = False
    self.centering_steering_direction_sign = 0.0

    panel_offset_available = False
    panel_offset_m = 0.0

    mads_enabled = False
    if sm.alive["selfdriveStateSP"]:
      mads_enabled = bool(sm["selfdriveStateSP"].mads.enabled)
    enabled = bool(selfdrive_state.enabled) or mads_enabled

    if sm.alive["carControl"]:
      lat_active = bool(sm["carControl"].latActive)
      if lat_active and not self.prev_lat_active:
        self.advanced_lane_centering_enabled = self.params.get_bool("AdvancedLaneCentering")
      self.prev_lat_active = lat_active

    if enabled and sm.alive["controlsState"]:
      controls_state = sm["controlsState"]
      controls_state_stale = abs(now - sm.recv_time["controlsState"]) > CENTERING_SIGNAL_STALE_S
      if not controls_state_stale:
        self.centering_status_active = bool(getattr(controls_state, "laneCenteringActive", False))
        self.centering_adjusting_display = bool(getattr(controls_state, "laneCenteringAdjusting", False))
        self.centering_edge_mode = bool(getattr(controls_state, "edgeClearanceActive", False))
        self.centering_display_valid = bool(getattr(controls_state, "laneCenteringValid", False))

        if self.centering_adjusting_display:
          panel_offset_available = True
          panel_offset_m = float(getattr(controls_state, "laneCenteringOffset", 0.0))
          self.centering_indicator_source = _enum_raw(getattr(controls_state, "laneCenteringSource", SOURCE_NONE))
        elif self.centering_edge_mode:
          panel_offset_available = True
          panel_offset_m = float(getattr(controls_state, "edgeClearanceOffset", 0.0))
          self.centering_indicator_source = SOURCE_EDGE
        elif self.centering_display_valid:
          panel_offset_available = True
          panel_offset_m = float(getattr(controls_state, "laneCenteringDisplayOffset", 0.0))
          self.centering_indicator_source = _enum_raw(getattr(controls_state, "laneCenteringSource", SOURCE_NONE))
        elif self.centering_status_active:
          panel_offset_available = True
          panel_offset_m = float(getattr(controls_state, "laneCenteringOffset", 0.0))
          self.centering_indicator_source = _enum_raw(getattr(controls_state, "laneCenteringSource", SOURCE_NONE))
      else:
        self.centering_indicator_last_nonzero_source = SOURCE_NONE
    else:
      self.centering_indicator_last_nonzero_source = SOURCE_NONE

    if self.centering_indicator_source == SOURCE_NONE and self.centering_indicator_last_nonzero_source != SOURCE_NONE:
      self.centering_indicator_source = self.centering_indicator_last_nonzero_source
    if self.centering_indicator_source != SOURCE_NONE:
      self.centering_indicator_last_nonzero_source = self.centering_indicator_source

    self.centering_display_valid = panel_offset_available
    self.centering_display_offset_m = panel_offset_m if panel_offset_available else 0.0
    self.centering_within_center_band = panel_offset_available and abs(panel_offset_m) <= CENTERING_CENTER_BAND_M

    if panel_offset_available:
      if panel_offset_m > 0.0:
        offset_sign = 1.0
      elif panel_offset_m < 0.0:
        offset_sign = -1.0
      else:
        offset_sign = 0.0
      self.centering_indicator_edge_sign = 0.0 if self.centering_within_center_band else offset_sign
      self.centering_steering_direction_sign = 0.0 if self.centering_within_center_band else offset_sign
      self.centering_highlight_strength = 0.0 if self.centering_within_center_band else max(0.0, min(1.0, abs(panel_offset_m) / 0.6))

    self._update_hod_debug(sm, enabled, now)

    debug_visible = self.advanced_lane_centering_enabled and self.hod_debug_available
    panel_request_now = enabled and (
      self.centering_status_active or self.centering_display_valid or panel_offset_available or debug_visible
    )
    force_panel_visible = self.centering_edge_mode or \
      (self.centering_indicator_source == SOURCE_EDGE and (self.centering_adjusting_display or panel_offset_available)) or \
      self.centering_adjusting_display or debug_visible

    if force_panel_visible:
      self.centering_panel_visible_state = True
      # Keep request state primed so we don't briefly hide when transitioning
      # from force-visible ("Adjusting") to normal panel states.
      self.centering_panel_request_active = True
      self.centering_panel_request_start = now - CENTERING_PANEL_MIN_VISIBLE_S
      self.centering_panel_visible = True
    else:
      if panel_request_now:
        if not self.centering_panel_request_active:
          self.centering_panel_request_active = True
          self.centering_panel_request_start = now
        request_duration = now - self.centering_panel_request_start
        self.centering_panel_visible_state = request_duration >= CENTERING_PANEL_MIN_VISIBLE_S
      else:
        self.centering_panel_request_active = False
        self.centering_panel_visible_state = False
      self.centering_panel_visible = self.centering_panel_visible_state

    highlight_dt = max(0.0, now - self.centering_highlight_last_update)
    self.centering_highlight_last_update = now
    if self.centering_highlight_strength <= 0.0:
      self.centering_highlight_phase = 0.0
    else:
      self.centering_highlight_phase = math.fmod(
        self.centering_highlight_phase + highlight_dt * CENTERING_HIGHLIGHT_FREQ_HZ * (2.0 * math.pi),
        2.0 * math.pi,
      )

  @staticmethod
  def _hod_state_label(status: int, touch: bool, grip: bool, strong: bool) -> str:
    if status == 0:
      return "hands off"
    if status == 1:
      return "touch soft"
    if status == 2:
      return "touch strong"
    if status == 3:
      return "grip soft"
    if status == 4:
      return "grip strong"
    if touch or grip:
      strength = "strong" if strong else "soft"
      mode = "grip" if grip else "touch"
      return f"{mode} {strength}"
    return f"reserved({status})"

  @staticmethod
  def _tap_label(count: int) -> str:
    if count <= 0:
      return "none"
    if count == 1:
      return "single"
    if count == 2:
      return "double"
    if count == 3:
      return "triple"
    return f"{count}x"

  @staticmethod
  def _is_tappable_hod_status(status: int) -> bool:
    return status in (1, 3, 4)

  def _is_hod_tap_event(self, status_raw: int, touch: bool, strong: bool) -> bool:
    prev_status = self._hod_prev_dir_status_raw
    prev_touch = self._hod_prev_touch
    prev_strong = self._hod_prev_strong

    touch_rise = (not prev_touch) and touch and prev_status == 0 and status_raw == 1
    strong_rise = (not prev_strong) and strong
    tappable_state_change = (
      self._is_tappable_hod_status(prev_status) and
      self._is_tappable_hod_status(status_raw) and
      status_raw != prev_status
    )
    tappable_contact_rise = prev_status == 0 and self._is_tappable_hod_status(status_raw)

    return touch_rise or strong_rise or tappable_state_change or tappable_contact_rise

  def _update_hod_debug(self, sm, enabled: bool, now: float) -> None:
    self.hod_debug_available = False
    self.hod_debug_primary = "HOD unavailable"
    self.hod_debug_secondary = "Taps: none"

    if not self.advanced_lane_centering_enabled:
      self._hod_prev_dir_status_raw = 0
      self._hod_prev_touch = False
      self._hod_prev_strong = False
      self._hod_tap_count_pending = 0
      self._hod_tap_finalize_deadline = 0.0
      return

    if not enabled:
      self._hod_prev_dir_status_raw = 0
      self._hod_prev_touch = False
      self._hod_prev_strong = False
      self.hod_debug_available = True
      self.hod_debug_primary = "HOD debug paused (not enabled)"
      self.hod_debug_secondary = f"Taps: {self._hod_last_tap_label}"
      return

    if not sm.alive["carStateSP"]:
      self.hod_debug_available = True
      self.hod_debug_primary = "HOD unavailable (carStateSP)"
      self.hod_debug_secondary = f"Taps: {self._hod_last_tap_label}"
      return

    car_state_sp_stale = abs(now - sm.recv_time["carStateSP"]) > HOD_SIGNAL_STALE_S
    if car_state_sp_stale:
      self.hod_debug_available = True
      self.hod_debug_primary = "HOD stale"
      self.hod_debug_secondary = f"Taps: {self._hod_last_tap_label}"
      return

    car_state_sp = sm["carStateSP"]
    self.hod_dir_status_raw = int(getattr(car_state_sp, "hodDirStatus", 0))
    self.hod_touch = bool(getattr(car_state_sp, "hodTouch", False))
    self.hod_grip = bool(getattr(car_state_sp, "hodGrip", False))
    self.hod_strong = bool(getattr(car_state_sp, "hodStrong", False))

    if self._is_hod_tap_event(self.hod_dir_status_raw, self.hod_touch, self.hod_strong):
      if self._hod_tap_count_pending > 0 and now <= self._hod_tap_finalize_deadline:
        self._hod_tap_count_pending += 1
      else:
        self._hod_tap_count_pending = 1
      self._hod_tap_finalize_deadline = now + HOD_TAP_GAP_S

    if self._hod_tap_count_pending > 0 and now > self._hod_tap_finalize_deadline:
      tap_count = self._hod_tap_count_pending
      self._hod_tap_count_pending = 0
      self._hod_tap_finalize_deadline = 0.0
      self._hod_last_tap_label = self._tap_label(tap_count)
      self._hod_last_tap_time = now

    self._hod_prev_dir_status_raw = self.hod_dir_status_raw
    self._hod_prev_touch = self.hod_touch
    self._hod_prev_strong = self.hod_strong

    active_tap_label = self._hod_last_tap_label
    if now - self._hod_last_tap_time > HOD_TAP_DISPLAY_HOLD_S:
      active_tap_label = "none"

    pending_tap_label = self._tap_label(self._hod_tap_count_pending)
    if self._hod_tap_count_pending > 0:
      tap_text = f"Taps: {active_tap_label} (pending: {pending_tap_label})"
    else:
      tap_text = f"Taps: {active_tap_label}"

    state_label = self._hod_state_label(self.hod_dir_status_raw, self.hod_touch, self.hod_grip, self.hod_strong)
    touch_bit = "1" if self.hod_touch else "0"
    grip_bit = "1" if self.hod_grip else "0"
    strong_bit = "1" if self.hod_strong else "0"

    self.hod_debug_available = True
    self.hod_debug_primary = f"HOD: {state_label} (raw:{self.hod_dir_status_raw})"
    self.hod_debug_secondary = f"{tap_text} | touch:{touch_bit} grip:{grip_bit} strong:{strong_bit}"

  def draw_lane_highlight(self, lane_lines: list) -> None:
    if self.centering_highlight_strength <= 0.0 or abs(self.centering_indicator_edge_sign) < 1e-4:
      return

    highlight_right = self.centering_indicator_edge_sign < 0.0
    highlight_idx = 2 if highlight_right else 1
    if highlight_idx < 0 or highlight_idx >= len(lane_lines):
      return
    if math.sin(self.centering_highlight_phase) <= -0.2:
      return

    points = lane_lines[highlight_idx].projected_points
    if points.size < 3:
      return

    alpha = max(0, min(255, int(round(255.0 * max(0.0, min(1.0, self.centering_highlight_strength))))))
    if alpha <= 0:
      return

    color = rl.Color(160, 90, 235, alpha) if highlight_right else rl.Color(210, 170, 255, alpha)
    draw_polygon(self._rect, points, color)

  def draw_lane_centering_panel(self, rect: rl.Rectangle) -> None:
    if not self.centering_panel_visible:
      return

    display_offset_valid = self.centering_display_valid or self.centering_status_active
    display_offset_m = self.centering_display_offset_m if display_offset_valid else 0.0
    display_offset_cm = abs(display_offset_m) * 100.0
    decimal_precision = 1 if display_offset_cm < 10.0 else 0

    use_edge_mode = self.centering_edge_mode or \
      (self.centering_indicator_source == SOURCE_EDGE and self.centering_adjusting_display)
    feature_text = "Edge" if use_edge_mode else "Lane"
    show_centered = self.centering_within_center_band and not self.centering_edge_mode

    def direction_from_sign(value: float) -> str:
      if abs(value) < 1e-4:
        return "center"
      return "right" if value > 0.0 else "left"

    primary_text = ""
    if self.advanced_lane_centering_enabled:
      correction_sign = self.centering_steering_direction_sign
      if abs(correction_sign) < 1e-4:
        if display_offset_m > 0.0:
          correction_sign = 1.0
        elif display_offset_m < 0.0:
          correction_sign = -1.0

      if not display_offset_valid and not self.centering_adjusting_display and not self.centering_edge_mode:
        primary_text = "Center Unknown"
      elif show_centered:
        primary_text = "Maintaining Center" if self.centering_adjusting_display else "Centered"
      elif use_edge_mode and (self.centering_adjusting_display or self.centering_edge_mode):
        if correction_sign > 0.0:
          primary_text = f"Adjusting Right ({feature_text})"
        elif correction_sign < 0.0:
          primary_text = f"Adjusting Left ({feature_text})"
        else:
          primary_text = f"Centering ({feature_text})"
      elif self.centering_adjusting_display:
        if correction_sign > 0.0:
          primary_text = f"Adjusting Right ({feature_text})"
        elif correction_sign < 0.0:
          primary_text = f"Adjusting Left ({feature_text})"
        else:
          primary_text = f"Centering ({feature_text})" if use_edge_mode else "Centered"
      elif display_offset_valid:
        primary_text = "Centered"
      else:
        primary_text = "Lane centering standby"

    if display_offset_valid:
      offset_value = f"{display_offset_cm:.{decimal_precision}f}"
      offset_direction = direction_from_sign(-display_offset_m)
      if offset_direction == "center":
        secondary_text = f"{offset_value} cm from center"
      else:
        secondary_text = f"{offset_value} cm {offset_direction} of center"
    else:
      secondary_text = "Offset unknown"

    debug_lines: list[str] = []
    if self.advanced_lane_centering_enabled and self.hod_debug_available:
      debug_lines = [self.hod_debug_primary, self.hod_debug_secondary]

    indicator_width = int(min(920, rect.width * 0.88))
    has_primary_text = bool(primary_text)
    indicator_height = 160 if has_primary_text else 112
    if debug_lines:
      indicator_height += 52 * len(debug_lines)
    indicator_x = int(rect.x + (rect.width - indicator_width) / 2)
    indicator_y = int(rect.y + rect.height - indicator_height - 148)
    indicator_y = max(int(rect.y + 40), indicator_y)
    indicator_rect = rl.Rectangle(indicator_x, indicator_y, indicator_width, indicator_height)

    rl.draw_rectangle_rounded(indicator_rect, 0.12, 12, rl.Color(0, 0, 0, 190))

    title_font_size = int(max(36, min(56, rect.height * 0.052)))
    detail_font_size = int(max(28, min(42, rect.height * 0.039)))
    text_color = rl.Color(255, 255, 255, 245)

    def draw_centered(font, text: str, font_size: int, y: float) -> None:
      text_size = measure_text_cached(font, text, font_size, 0)
      x = indicator_rect.x + (indicator_rect.width - text_size.x) / 2
      rl.draw_text_ex(font, text, rl.Vector2(x, y), font_size, 0, text_color)

    primary_y = indicator_rect.y + 26
    detail_y = indicator_rect.y + (indicator_height * 0.55 if has_primary_text else indicator_height * 0.33)

    if has_primary_text:
      draw_centered(self._title_font, primary_text, title_font_size, primary_y)
    draw_centered(self._detail_font, secondary_text, detail_font_size, detail_y)

    if debug_lines:
      debug_font_size = int(max(22, min(34, rect.height * 0.03)))
      debug_y = indicator_rect.y + indicator_height - 38 - (len(debug_lines) - 1) * 32
      for line in debug_lines:
        draw_centered(self._detail_font, line, debug_font_size, debug_y)
        debug_y += 32
