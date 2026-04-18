"""
Copyright (c) 2021-, Haibin Wen, sunnypilot, and a number of other contributors.

This file is part of sunnypilot and is licensed under the MIT License.
See the LICENSE.md file in the root directory for more details.
"""
from openpilot.selfdrive.ui.sunnypilot.layouts.settings.vehicle.brands.base import BrandSettings
from openpilot.selfdrive.ui.ui_state import ui_state
from openpilot.system.ui.lib.multilang import tr
from openpilot.system.ui.sunnypilot.widgets.list_view import multiple_button_item_sp, option_item_sp
from opendbc.car.hyundai.values import CAR, UNSUPPORTED_LONGITUDINAL_CAR, HyundaiFlags


class HyundaiSettings(BrandSettings):
  def __init__(self):
    super().__init__()
    self.alpha_long_available = False
    self.has_angle_steering = False

    tuning_texts = [tr("Off"), tr("Dynamic"), tr("Predictive")]
    self.longitudinal_tuning_item = multiple_button_item_sp(tr("Custom Longitudinal Tuning"), "", tuning_texts,
                                                            button_width=300, callback=self._on_tuning_selected,
                                                            param="HyundaiLongitudinalTuning", inline=False)
    shared_autonomy_texts = [tr("Stock"), tr("Partial"), tr("Disabled")]
    self.shared_autonomy_mode_item = multiple_button_item_sp(
      title=tr("Shared Autonomy"),
      description="",
      buttons=shared_autonomy_texts,
      button_width=300,
      callback=self._on_shared_autonomy_mode_selected,
      param="HkgSharedAutonomyMode",
      inline=False,
    )
    self.angle_override_effort_item = option_item_sp(
      title=tr("Steering Override Effort"),
      param="HkgTuningAngleOverrideEffortPercent",
      min_value=10,
      max_value=100,
      value_change_step=10,
      description="",
      label_callback=lambda value: f"{value}%",
    )
    self.angle_custom_limit_speed_item = option_item_sp(
      title=tr("Speed (EV9 Limits)"),
      param="HkgTuningAngleCustomLimitMaxSpeedKph",
      min_value=10,
      max_value=40,
      value_change_step=1,
      description="",
      label_callback=lambda value: f"{value} km/h",
    )
    self.ev9_alerts_speed_item = option_item_sp(
      title=tr("Speed (EV9 Alerts)"),
      param="HkgTuningEv9AlertsSpeedKph",
      min_value=10,
      max_value=50,
      value_change_step=1,
      description="",
      label_callback=lambda value: f"{value} km/h",
    )
    self.items = [self.longitudinal_tuning_item, self.shared_autonomy_mode_item, self.angle_override_effort_item,
                  self.angle_custom_limit_speed_item, self.ev9_alerts_speed_item]

  @staticmethod
  def _on_tuning_selected(index):
    ui_state.params.put("HyundaiLongitudinalTuning", index)

  @staticmethod
  def _on_shared_autonomy_mode_selected(index):
    ui_state.params.put("HkgSharedAutonomyMode", index)

  def update_settings(self):
    self.alpha_long_available = False
    self.has_angle_steering = False
    bundle = ui_state.params.get("CarPlatformBundle")
    if bundle:
      platform = bundle.get("platform")
      config = CAR[platform].config
      self.alpha_long_available = CAR[platform] not in set().union(*UNSUPPORTED_LONGITUDINAL_CAR.values())
      self.has_angle_steering = bool(config.flags & HyundaiFlags.CANFD_ANGLE_STEERING)
    elif ui_state.CP is not None:
      self.alpha_long_available = ui_state.CP.alphaLongitudinalAvailable
      self.has_angle_steering = bool(ui_state.CP.flags & HyundaiFlags.CANFD_ANGLE_STEERING)

    tuning_param = int(ui_state.params.get("HyundaiLongitudinalTuning") or "0")
    long_enabled = ui_state.has_longitudinal_control

    long_tuning_descs = [
      tr("Your vehicle will use the Default longitudinal tuning."),
      tr("Your vehicle will use the Dynamic longitudinal tuning."),
      tr("Your vehicle will use the Predictive longitudinal tuning."),
    ]
    long_tuning_desc = long_tuning_descs[tuning_param] if tuning_param < len(long_tuning_descs) else long_tuning_descs[0]

    longitudinal_tuning_disabled = not ui_state.is_offroad() or not long_enabled
    if longitudinal_tuning_disabled:
      if not ui_state.is_offroad():
        long_tuning_desc = tr("This feature is unavailable while the car is onroad.")
      elif not long_enabled:
        long_tuning_desc = tr("This feature is unavailable because sunnypilot Longitudinal Control (Alpha) is not enabled.")

    self.longitudinal_tuning_item.action_item.set_enabled(not longitudinal_tuning_disabled)
    self.longitudinal_tuning_item.set_description(long_tuning_desc)
    self.longitudinal_tuning_item.show_description(True)
    self.longitudinal_tuning_item.action_item.set_selected_button(tuning_param)
    self.longitudinal_tuning_item.set_visible(self.alpha_long_available)

    shared_autonomy_mode = int(ui_state.params.get("HkgSharedAutonomyMode") or "2")
    shared_autonomy_mode = max(0, min(shared_autonomy_mode, 2))
    shared_autonomy_stock_mode = shared_autonomy_mode == 0
    shared_autonomy_descs = [
      tr("Stock: openpilot can continue lateral control while you manually steer. Steering Override Effort applies in this mode."),
      tr("Partial: openpilot sends no lateral actuation while strong manual steering override is detected, then resumes immediately on release."),
      tr("Disabled: openpilot sends no lateral actuation while any manual steering intent is detected " +
         "(including hands-on steering detection when available), then resumes immediately on release."),
    ]
    shared_autonomy_base_desc = shared_autonomy_descs[shared_autonomy_mode]
    if not self.has_angle_steering:
      shared_autonomy_desc = tr("This feature is only available on angle-steering Hyundai/Kia/Genesis platforms.")
    elif not ui_state.is_offroad():
      unavailable_desc = tr("Enable \"Always Offroad\" in Device panel, or turn vehicle off to adjust this setting.")
      shared_autonomy_desc = f"<b>{unavailable_desc}</b><br><br>{shared_autonomy_base_desc}"
    else:
      shared_autonomy_desc = shared_autonomy_base_desc

    self.shared_autonomy_mode_item.action_item.set_enabled(self.has_angle_steering and ui_state.is_offroad())
    self.shared_autonomy_mode_item.set_description(shared_autonomy_desc)
    self.shared_autonomy_mode_item.show_description(True)
    self.shared_autonomy_mode_item.action_item.set_selected_button(shared_autonomy_mode)
    self.shared_autonomy_mode_item.set_visible(self.has_angle_steering)

    angle_override_base_desc = tr("Adjust steering effort required to manually override lateral control on angle-steering platforms. " +
                                  "Lower values make override easier. 100% keeps stock behavior.")
    if not self.has_angle_steering:
      angle_override_desc = tr("This feature is only available on angle-steering Hyundai/Kia/Genesis platforms.")
    elif not shared_autonomy_stock_mode:
      unavailable_desc = tr("Set Shared Autonomy to \"Stock\" to use this setting.")
      angle_override_desc = f"<b>{unavailable_desc}</b><br><br>{angle_override_base_desc}"
    elif not ui_state.is_offroad():
      angle_override_desc = tr("Enable \"Always Offroad\" in Device panel, or turn vehicle off to adjust this setting.")
      angle_override_desc = f"<b>{angle_override_desc}</b><br><br>{angle_override_base_desc}"
    else:
      angle_override_desc = angle_override_base_desc

    self.angle_override_effort_item.action_item.set_enabled(self.has_angle_steering and ui_state.is_offroad() and shared_autonomy_stock_mode)
    self.angle_override_effort_item.set_description(angle_override_desc)
    self.angle_override_effort_item.show_description(True)
    self.angle_override_effort_item.set_visible(self.has_angle_steering)

    ev9_limits_speed_desc = tr("Modify EV9 steering limits only below this speed.")
    if not self.has_angle_steering:
      ev9_limits_speed_desc = tr("This feature is only available on angle-steering Hyundai/Kia/Genesis platforms.")
    elif not ui_state.is_offroad():
      unavailable_desc = tr("Enable \"Always Offroad\" in Device panel, or turn vehicle off to adjust this setting.")
      ev9_limits_speed_desc = f"<b>{unavailable_desc}</b><br><br>{ev9_limits_speed_desc}"
    self.angle_custom_limit_speed_item.action_item.set_enabled(self.has_angle_steering and ui_state.is_offroad())
    self.angle_custom_limit_speed_item.set_description(ev9_limits_speed_desc)
    self.angle_custom_limit_speed_item.show_description(True)
    self.angle_custom_limit_speed_item.set_visible(self.has_angle_steering)

    ev9_alerts_speed_desc = tr("Modify EV9 steering alerts only below this speed.")
    if not self.has_angle_steering:
      ev9_alerts_speed_desc = tr("This feature is only available on angle-steering Hyundai/Kia/Genesis platforms.")
    elif not ui_state.is_offroad():
      unavailable_desc = tr("Enable \"Always Offroad\" in Device panel, or turn vehicle off to adjust this setting.")
      ev9_alerts_speed_desc = f"<b>{unavailable_desc}</b><br><br>{ev9_alerts_speed_desc}"
    self.ev9_alerts_speed_item.action_item.set_enabled(self.has_angle_steering and ui_state.is_offroad())
    self.ev9_alerts_speed_item.set_description(ev9_alerts_speed_desc)
    self.ev9_alerts_speed_item.show_description(True)
    self.ev9_alerts_speed_item.set_visible(self.has_angle_steering)
