"""EV9 startup prompt and mode confirmation based on live vehicle telemetry."""
import time

import pyray as rl

from openpilot.selfdrive.ui.onroad.starpilot.longitudinal_status import LongitudinalSample, LongitudinalStatus
from openpilot.selfdrive.ui.onroad.starpilot.widgets.base import LayoutWidget
from openpilot.selfdrive.ui.ui_state import ui_state
from openpilot.system.ui.lib.application import FontWeight, gui_app
from openpilot.system.ui.lib.text_measure import measure_text_cached


class LongitudinalStatusWidget(LayoutWidget):
  def __init__(self):
    super().__init__("longitudinal_status", priority=2)
    self.set_enabled(False)
    self._font = gui_app.font(FontWeight.SEMI_BOLD)
    self._status = LongitudinalStatus()
    self._label = None
    self._last_sample_key = None

  def update_status(self):
    sm = ui_state.sm
    key = (sm.frame, ui_state.started, ui_state.started_time)
    if key == self._last_sample_key:
      return
    self._last_sample_key = key

    def valid(service):
      return bool(sm.seen[service] and sm.valid[service] and sm.alive[service])

    def timestamp(service):
      return sm.logMonoTime[service] / 1e9 if sm.seen[service] else 0.0

    pandas = sm['pandaStates'] if sm.seen['pandaStates'] else ()
    vehicle = sm['starpilotCarState']
    self._label = self._status.update(LongitudinalSample(
      now=time.monotonic(), session_start=ui_state.started_time, started=ui_state.started,
      identity_ev9=bool(sm.seen['carParams'] and sm.valid['carParams'] and sm['carParams'].carFingerprint == 'KIA_EV9'),
      identity_time=timestamp('carParams'), panda_time=timestamp('pandaStates'), panda_valid=valid('pandaStates'),
      safety_models=tuple(str(p.safetyModel) for p in pandas), safety_params=tuple(p.safetyParam for p in pandas),
      panda_fault=any(bool(p.faults) for p in pandas), events_time=timestamp('onroadEvents'), events_valid=valid('onroadEvents'),
      initializing=any(str(e.name) == 'selfdriveInitializing' for e in sm['onroadEvents']),
      control_time=timestamp('carControl'), control_valid=valid('carControl'),
      vehicle_time=timestamp('starpilotCarState'), vehicle_valid=valid('starpilotCarState'),
      ready_time=vehicle.vehicleReadyTimestamp / 1e9, vehicle_ready=vehicle.vehicleReady,
    ))

  @property
  def is_visible(self):
    return self._label is not None

  @property
  def blocks_pointer(self):
    return False

  def get_size(self):
    # The right-column anchor sits 146 px from the edge.
    return 280.0, 60.0

  def _render(self, rect):
    if self._label is None:
      return
    color = rl.Color(205, 210, 208, 255)
    if self._label == 'Stock ACC':
      color = rl.Color(128, 216, 166, 255)
    elif self._label == 'Long status unavailable':
      color = rl.Color(255, 190, 90, 255)
    rl.draw_rectangle_rounded(rect, 0.25, 8, rl.Color(0, 0, 0, 190))
    # Flash the text at 2 Hz; preserve the badge's layout and background.
    if self._label == 'OP long ready' and int(time.monotonic() * 4) % 2:
      return
    font_size = 28
    size = measure_text_cached(self._font, self._label, font_size)
    if size.x > rect.width - 16:
      font_size *= (rect.width - 16) / size.x
      size = measure_text_cached(self._font, self._label, font_size)
    x = rect.x + (rect.width - size.x) / 2
    y = rect.y + (rect.height - size.y) / 2
    if self._label == 'OP long':
      # Tint the glyphs from bright lilac to violet without changing render state.
      for i, char in enumerate(self._label):
        progress = i / (len(self._label) - 1)
        color = rl.Color(round(232 - 58 * progress), round(145 - 41 * progress), 255, 255)
        rl.draw_text_ex(self._font, char, rl.Vector2(x, y), font_size, 0, color)
        x += measure_text_cached(self._font, char, font_size).x
    else:
      rl.draw_text_ex(self._font, self._label, rl.Vector2(x, y), font_size, 0, color)
