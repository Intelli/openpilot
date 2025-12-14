import time
import threading
import subprocess
from datetime import datetime, timedelta

from openpilot.common.params import Params
from openpilot.system.hardware import HARDWARE
from openpilot.common.swaglog import cloudlog
from openpilot.system.statsd import statlog

CAR_VOLTAGE_LOW_PASS_K = 0.011 # LPF gain for 45s tau (dt/tau / (dt/tau + 1))

# While driving, a battery charges completely in about 30-60 minutes
CAR_BATTERY_CAPACITY_uWh = 30e6
CAR_CHARGING_RATE_W = 45

VBATT_PAUSE_CHARGING = 11.8           # Lower limit on the LPF car battery voltage
MAX_TIME_OFFROAD_S = 30*3600
MIN_ON_TIME_S = 3600
DELAY_SHUTDOWN_TIME_S = 300 # Wait at least DELAY_SHUTDOWN_TIME_S seconds after offroad_time to shutdown.
VOLTAGE_SHUTDOWN_MIN_OFFROAD_TIME_S = 60

class PowerMonitoring:
  def __init__(self):
    self.params = Params()
    self.last_measurement_time = None           # Used for integration delta
    self.last_save_time = 0                     # Used for saving current value in a param
    self.power_used_uWh = 0                     # Integrated power usage in uWh since going into offroad
    self.next_pulsed_measurement_time = None
    self.car_voltage_mV = 12e3                  # Low-passed version of peripheralState voltage
    self.car_voltage_instant_mV = 12e3          # Last value of peripheralState voltage
    self.integration_lock = threading.Lock()
    self._last_login_check = 0.0
    self._remote_logged_in = False

    car_battery_capacity_uWh = self.params.get("CarBatteryCapacity") or 0

    # Reset capacity if it's low
    self.car_battery_capacity_uWh = max((CAR_BATTERY_CAPACITY_uWh / 10), car_battery_capacity_uWh)

  # Calculation tick
  def calculate(self, voltage: int | None, ignition: bool):
    try:
      now = time.monotonic()

      # If peripheralState is None, we're probably not in a car, so we don't care
      if voltage is None:
        with self.integration_lock:
          self.last_measurement_time = None
          self.next_pulsed_measurement_time = None
          self.power_used_uWh = 0
        return

      # Low-pass battery voltage
      self.car_voltage_instant_mV = voltage
      self.car_voltage_mV = ((voltage * CAR_VOLTAGE_LOW_PASS_K) + (self.car_voltage_mV * (1 - CAR_VOLTAGE_LOW_PASS_K)))
      statlog.gauge("car_voltage", self.car_voltage_mV / 1e3)

      # Cap the car battery power and save it in a param every 10-ish seconds
      self.car_battery_capacity_uWh = max(self.car_battery_capacity_uWh, 0)
      self.car_battery_capacity_uWh = min(self.car_battery_capacity_uWh, CAR_BATTERY_CAPACITY_uWh)
      if now - self.last_save_time >= 10:
        self.params.put_nonblocking("CarBatteryCapacity", int(self.car_battery_capacity_uWh))
        self.last_save_time = now

      # First measurement, set integration time
      with self.integration_lock:
        if self.last_measurement_time is None:
          self.last_measurement_time = now
          return

      if ignition:
        # If there is ignition, we integrate the charging rate of the car
        with self.integration_lock:
          self.power_used_uWh = 0
          integration_time_h = (now - self.last_measurement_time) / 3600
          if integration_time_h < 0:
            raise ValueError(f"Negative integration time: {integration_time_h}h")
          self.car_battery_capacity_uWh += (CAR_CHARGING_RATE_W * 1e6 * integration_time_h)
          self.last_measurement_time = now
      else:
        # Get current power draw somehow
        current_power = HARDWARE.get_current_power_draw()

        # Do the integration
        self._perform_integration(now, current_power)
    except Exception:
      cloudlog.exception("Power monitoring calculation failed")

  def _perform_integration(self, t: float, current_power: float) -> None:
    with self.integration_lock:
      try:
        if self.last_measurement_time:
          integration_time_h = (t - self.last_measurement_time) / 3600
          power_used = (current_power * 1000000) * integration_time_h
          if power_used < 0:
            raise ValueError(f"Negative power used! Integration time: {integration_time_h} h Current Power: {power_used} uWh")
          self.power_used_uWh += power_used
          self.car_battery_capacity_uWh -= power_used
          self.last_measurement_time = t
      except Exception:
        cloudlog.exception("Integration failed")

  # Get the power usage
  def get_power_used(self) -> int:
    return int(self.power_used_uWh)

  def get_car_battery_capacity(self) -> int:
    return int(self.car_battery_capacity_uWh)

  def max_time_offroad_exceeded(self, offroad_time: float) -> bool:
    return 0 < MAX_TIME_OFFROAD_S <= offroad_time

  def _remote_user_logged_in(self) -> bool:
    now = time.monotonic()
    if (now - self._last_login_check) < 60.0:
      return self._remote_logged_in

    remote_logged_in = False
    try:
      result = subprocess.run(["last"], capture_output=True, text=True, check=False)
      for line in result.stdout.splitlines():
        if "still logged in" not in line:
          continue
        parts = line.split()
        if not parts:
          continue
        user = parts[0]
        terminal = parts[1] if len(parts) > 1 else ""
        host = parts[2] if len(parts) > 2 else ""
        if user in {"reboot", "shutdown", "runlevel", "wtmp"}:
          continue
        if terminal.startswith("pts/") or (host and any(ch in host for ch in (".", ":"))):
          try:
            still_idx = parts.index("still")
            date_str = " ".join(parts[3:still_idx])
            login_time = datetime.strptime(date_str, "%a %b %d %H:%M")
            now_dt = datetime.now()
            login_time = login_time.replace(year=now_dt.year)
            if login_time > now_dt + timedelta(days=1):
              login_time = login_time.replace(year=now_dt.year - 1)
            if (now_dt - login_time) > timedelta(hours=24):
              continue
          except Exception:
            remote_logged_in = True
            break
          remote_logged_in = True
          break
    except Exception:
      remote_logged_in = False

    self._remote_logged_in = remote_logged_in
    self._last_login_check = now
    return remote_logged_in

  # See if we need to shutdown
  def should_shutdown(self, ignition: bool, in_car: bool, offroad_timestamp: float | None, started_seen: bool):
    if offroad_timestamp is None:
      return False

    now = time.monotonic()
    should_shutdown = False
    offroad_time = (now - offroad_timestamp)
    low_voltage_shutdown = (self.car_voltage_mV < (VBATT_PAUSE_CHARGING * 1e3) and
                            offroad_time > VOLTAGE_SHUTDOWN_MIN_OFFROAD_TIME_S)
    max_time_exceeded = self.max_time_offroad_exceeded(offroad_time)
    if max_time_exceeded and self._remote_user_logged_in():
      max_time_exceeded = False
    should_shutdown |= max_time_exceeded
    should_shutdown |= low_voltage_shutdown
    should_shutdown |= (self.car_battery_capacity_uWh <= 0)
    should_shutdown &= not ignition
    should_shutdown &= (not self.params.get_bool("DisablePowerDown"))
    should_shutdown &= in_car
    should_shutdown &= offroad_time > DELAY_SHUTDOWN_TIME_S
    should_shutdown |= self.params.get_bool("ForcePowerDown")
    should_shutdown &= started_seen or (now > MIN_ON_TIME_S)
    return should_shutdown
