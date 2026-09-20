"""Optional warning highlighting shared by the driving-screen path renderers."""
import pyray as rl

from cereal import log
from openpilot.system.ui.lib.shader_polygon import Gradient


WARNING_EVENTS = {
  "steerSaturated", "aeb", "stockAeb", "fcw", "manualRestart",
  "driverDistracted1", "driverDistracted2", "driverDistracted3",
  "driverUnresponsive1", "driverUnresponsive2", "driverUnresponsive3",
  "goatSteerSaturated", "firefoxSteerSaturated", "thisIsFineSteerSaturated",
}


def path_warning_active(sm, started_frame: int, now: float) -> bool:
  for service in ("selfdriveState", "starpilotSelfdriveState"):
    if (sm.valid.get(service, False) and sm.alive.get(service, False) and
        sm.recv_frame.get(service, -1) >= started_frame and 0 <= now - sm.recv_time.get(service, 0.0) <= 1.0):
      alert = sm[service]
      if alert.alertSize != log.SelfdriveState.AlertSize.none and str(alert.alertType).split("/", 1)[0] in WARNING_EVENTS:
        return True
  return False


class PathWarningHighlight:
  HOLD_SECONDS = 0.5
  FADE_SECONDS = 1.0

  def __init__(self):
    self.reset()

  def reset(self):
    self._started_frame = None
    self._last_update_time = None
    self._mix = 0.0
    self._hold = 0.0

  def update(self, sm, started_frame: int, enabled: bool, now: float) -> Gradient | None:
    if not enabled:
      self.reset()
      return None

    elapsed = 0.0 if self._last_update_time is None else now - self._last_update_time
    if self._started_frame != started_frame or elapsed < 0 or elapsed > 1.0:
      self.reset()
      elapsed = 0.0
    self._started_frame = started_frame
    self._last_update_time = now
    dt = elapsed

    if path_warning_active(sm, started_frame, now):
      self._mix = 1.0
      self._hold = self.HOLD_SECONDS
    else:
      held = min(self._hold, dt)
      self._hold -= held
      self._mix = max(0.0, self._mix - (dt - held) / self.FADE_SECONDS)

    if self._mix <= 0.0:
      return None
    colors = [rl.Color(r, g, b, round(a * self._mix)) for r, g, b, a in ((115, 0, 0, 209), (199, 36, 36, 173), (235, 115, 115, 140))]
    return Gradient(start=(0.0, 1.0), end=(0.0, 0.0), colors=colors, stops=[0.0, 0.5, 1.0])
