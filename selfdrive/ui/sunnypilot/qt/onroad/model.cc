/**
 * Copyright (c) 2021-, Haibin Wen, sunnypilot, and a number of other contributors.
 *
 * This file is part of sunnypilot and is licensed under the MIT License.
 * See the LICENSE.md file in the root directory for more details.
 */

#include "selfdrive/ui/sunnypilot/qt/onroad/model.h"

#include <algorithm>
#include <array>
#include <chrono>
#include <cmath>
#include <iterator>
#include <QString>

#include "common/timing.h"

constexpr float CENTERING_DISPLAY_MAX_OFFSET_CM = 50.0f;
constexpr float CENTERING_INDICATOR_MIN_OPACITY = 1e-3f;
constexpr float CENTERING_SIGNAL_STALE_S = 1.0f;
constexpr float CENTERING_INDICATOR_RAMP_UP_S = 0.18f;
constexpr float CENTERING_INDICATOR_RAMP_DOWN_S = 0.7f;
constexpr float CENTERING_LANE_HIGHLIGHT_MIN_M = 0.06f;
constexpr float CENTERING_LANE_HIGHLIGHT_FULL_M = 0.25f;
constexpr float CENTERING_LANE_PULSE_FREQ_HZ = 3.0f;

void ModelRendererSP::draw(QPainter &painter, const QRect &surface_rect) {
  auto *s = uiState();
  auto &sm = *(s->sm);

  if (sm.rcv_frame("liveCalibration") < s->scene.started_frame ||
      sm.rcv_frame("modelV2") < s->scene.started_frame) {
    return;
  }
  clip_region = surface_rect.adjusted(-CLIP_MARGIN, -CLIP_MARGIN, CLIP_MARGIN, CLIP_MARGIN);
  experimental_mode = sm["selfdriveState"].getSelfdriveState().getExperimentalMode();
  longitudinal_control = sm["carParams"].getCarParams().getOpenpilotLongitudinalControl();
  path_offset_z = sm["liveCalibration"].getLiveCalibration().getHeight()[0];

  painter.save();

  const auto &model = sm["modelV2"].getModelV2();
  const auto &radar_state = sm["radarState"].getRadarState();
  const auto &lead_one = radar_state.getLeadOne();
  const auto &selfdrive_state = sm["selfdriveState"].getSelfdriveState();

  const auto now = std::chrono::steady_clock::now();
  const float frame_dt = std::chrono::duration<float>(now - centering_indicator_last_update).count();
  centering_indicator_last_update = now;

  bool centering_signal = false;
  bool edge_clearance_signal = false;
  float centering_offset_m = 0.0f;
  float edge_clearance_offset_m = 0.0f;
  cereal::ControlsState::LaneCenteringSource centering_source = cereal::ControlsState::LaneCenteringSource::NONE;
  bool controls_state_stale = true;
  bool centering_valid_now = false;
  float display_offset_now = 0.0f;
  bool centering_adjusting_now = false;

  if (sm.alive("controlsState")) {
    const auto &controls_state = sm["controlsState"].getControlsState();
    centering_offset_m = controls_state.getLaneCenteringOffset();
    centering_source = controls_state.getLaneCenteringSource();
    edge_clearance_offset_m = controls_state.getEdgeClearanceOffset();
    centering_valid_now = controls_state.getLaneCenteringValid();
    display_offset_now = controls_state.getLaneCenteringDisplayOffset();
    centering_adjusting_now = controls_state.getLaneCenteringAdjusting();
    centering_signal = selfdrive_state.getEnabled() && centering_adjusting_now;
    edge_clearance_signal = selfdrive_state.getEnabled() && controls_state.getEdgeClearanceActive();
    const int64_t controls_mono_time = sm.rcv_time("controlsState");
    const double age = std::abs((double)(nanos_since_boot() - controls_mono_time)) / 1e9;
    controls_state_stale = age > CENTERING_SIGNAL_STALE_S;

    if (!controls_state_stale) {
      centering_indicator_last_controls_update = now;
      centering_display_valid = centering_valid_now;
      centering_display_offset_m = centering_valid_now ? display_offset_now : 0.0f;
    }

    const bool guard_signal = centering_signal || edge_clearance_signal;
    if (guard_signal) {
      const float display_offset = centering_signal ? centering_offset_m : edge_clearance_offset_m;
      const auto display_source = centering_signal ? centering_source : cereal::ControlsState::LaneCenteringSource::EDGE;

      centering_indicator_last_signal = now;
      centering_indicator_magnitude = std::abs(display_offset);
      centering_indicator_edge_sign = display_offset > 0.0f ? 1.0f : (display_offset < 0.0f ? -1.0f : 0.0f);
      centering_indicator_source = display_source;
      if (centering_indicator_source != cereal::ControlsState::LaneCenteringSource::NONE) {
        centering_indicator_last_nonzero_source = centering_indicator_source;
      }
    }
  } else {
    centering_display_valid = false;
    centering_display_offset_m = 0.0f;
  }

  if (controls_state_stale || !selfdrive_state.getEnabled()) {
    centering_adjusting_display = false;
    centering_edge_mode = false;
    if (controls_state_stale) {
      centering_display_valid = false;
      centering_display_offset_m = 0.0f;
    }
  } else {
    centering_adjusting_display = centering_signal;
    centering_edge_mode = edge_clearance_signal;
  }

  const bool any_signal = centering_signal || edge_clearance_signal;
  if (any_signal) {
    centering_indicator_active = true;
  } else if (controls_state_stale || !selfdrive_state.getEnabled()) {
    centering_indicator_active = false;
  }

  const float target_opacity = centering_indicator_active ? 1.0f : 0.0f;
  const float ramp = centering_indicator_active ? CENTERING_INDICATOR_RAMP_UP_S : CENTERING_INDICATOR_RAMP_DOWN_S;
  if (ramp > 1e-3f && frame_dt > 0.0f) {
    const float step = frame_dt / ramp;
    if (target_opacity > centering_indicator_opacity) {
      centering_indicator_opacity = std::min(target_opacity, centering_indicator_opacity + step);
    } else {
      centering_indicator_opacity = std::max(target_opacity, centering_indicator_opacity - step);
    }
  } else {
    centering_indicator_opacity = target_opacity;
  }

  if (centering_indicator_opacity <= CENTERING_INDICATOR_MIN_OPACITY) {
    centering_indicator_opacity = 0.0f;
  }

  if (centering_indicator_opacity <= 0.0f) {
    centering_indicator_blink_intensity = 0.0f;
    centering_indicator_edge_sign = 0.0f;
    centering_indicator_prev_magnitude = 0.0f;
    centering_indicator_source = cereal::ControlsState::LaneCenteringSource::NONE;
  } else {
    const float prev_mag = centering_indicator_prev_magnitude;
    centering_indicator_prev_magnitude = centering_indicator_magnitude;

    float highlight_progress = 0.0f;
    if (centering_indicator_magnitude > CENTERING_LANE_HIGHLIGHT_MIN_M && centering_indicator_edge_sign != 0.0f) {
      const float span = std::max(CENTERING_LANE_HIGHLIGHT_FULL_M - CENTERING_LANE_HIGHLIGHT_MIN_M, 1e-3f);
      const float normalized = (centering_indicator_magnitude - CENTERING_LANE_HIGHLIGHT_MIN_M) / span;
      highlight_progress = std::clamp(normalized, 0.0f, 1.0f);
      const bool reducing = (prev_mag - centering_indicator_magnitude) > 1e-3f;
      if (!reducing) {
        highlight_progress *= 0.35f;
      }
    }

    const float target_blink = centering_indicator_active ? highlight_progress : 0.0f;
    const float rise = frame_dt / 0.12f;
    const float fall = frame_dt / 0.4f;
    if (target_blink > centering_indicator_blink_intensity) {
      centering_indicator_blink_intensity = std::min(target_blink, centering_indicator_blink_intensity + rise);
    } else {
      centering_indicator_blink_intensity = std::max(target_blink, centering_indicator_blink_intensity - fall);
    }

    centering_indicator_blink_phase = std::fmod(centering_indicator_blink_phase + frame_dt * CENTERING_LANE_PULSE_FREQ_HZ * float(2.0 * M_PI), float(2.0 * M_PI));

    if (centering_indicator_source == cereal::ControlsState::LaneCenteringSource::NONE &&
        centering_indicator_last_nonzero_source != cereal::ControlsState::LaneCenteringSource::NONE &&
        centering_indicator_active) {
      centering_indicator_source = centering_indicator_last_nonzero_source;
    }
  }

  update_model(model, lead_one);
  drawLaneLines(painter);
  drawPath(painter, model, surface_rect);

  if (longitudinal_control && sm.alive("radarState")) {
    update_leads(radar_state, model.getPosition());
    const auto &lead_two = radar_state.getLeadTwo();
    if (lead_one.getStatus()) {
      drawLead(painter, lead_one, lead_vertices[0], surface_rect);
    }
    if (lead_two.getStatus() && (std::abs(lead_one.getDRel() - lead_two.getDRel()) > 3.0)) {
      drawLead(painter, lead_two, lead_vertices[1], surface_rect);
    }
  }
  drawLeadStatus(painter, surface_rect.height(), surface_rect.width());

  const bool panel_visible = selfdrive_state.getEnabled() && (centering_display_valid || centering_indicator_opacity > 0.0f || centering_adjusting_display || centering_edge_mode);
  if (panel_visible) {
    painter.save();
    float panel_opacity = centering_indicator_opacity;
    if (!centering_adjusting_display && !centering_edge_mode) {
      panel_opacity = centering_display_valid ? 1.0f : 0.6f;
    } else {
      panel_opacity = std::max(centering_indicator_opacity, 0.75f);
    }
    painter.setOpacity(std::clamp(panel_opacity, 0.0f, 1.0f));

    const bool use_edge_mode = centering_edge_mode || (centering_indicator_source == cereal::ControlsState::LaneCenteringSource::EDGE && centering_adjusting_display);
    const QString feature_text = use_edge_mode ? QStringLiteral("road edge") : QStringLiteral("lane line");

    const float display_offset_m = centering_display_valid ? centering_display_offset_m : 0.0f;
    const float display_offset_cm = std::abs(display_offset_m) * 100.0f;
    const bool offset_small = display_offset_cm < 1.0f;
    const int decimal_precision = display_offset_cm < 10.0f ? 1 : 0;

    auto direction_from_sign = [](float value) {
      if (std::abs(value) < 1e-4f) {
        return QStringLiteral("center");
      }
      return value > 0.0f ? QStringLiteral("right") : QStringLiteral("left");
    };

    QString primary_text;
    if (!centering_display_valid && !centering_adjusting_display && !centering_edge_mode) {
      primary_text = QStringLiteral("Lane centering: offset unknown");
    } else if (use_edge_mode && (centering_adjusting_display || centering_edge_mode)) {
      const float edge_sign = centering_indicator_edge_sign != 0.0f ? centering_indicator_edge_sign : (display_offset_m >= 0.0f ? 1.0f : -1.0f);
      if (edge_sign > 0.0f) {
        primary_text = QStringLiteral("Maintaining clearance from right %1").arg(feature_text);
      } else if (edge_sign < 0.0f) {
        primary_text = QStringLiteral("Maintaining clearance from left %1").arg(feature_text);
      } else {
        primary_text = QStringLiteral("Maintaining road edge clearance");
      }
    } else if (centering_adjusting_display) {
      const float sign = centering_indicator_edge_sign != 0.0f ? centering_indicator_edge_sign : (display_offset_m >= 0.0f ? 1.0f : -1.0f);
      if (sign > 0.0f) {
        primary_text = QStringLiteral("Adjusting left from right %1").arg(feature_text);
      } else if (sign < 0.0f) {
        primary_text = QStringLiteral("Adjusting right from left %1").arg(feature_text);
      } else {
        primary_text = QStringLiteral("Centering using %1").arg(feature_text);
      }
    } else if (centering_display_valid) {
      if (offset_small) {
        primary_text = QStringLiteral("Lane centered");
      } else {
        primary_text = QStringLiteral("Vehicle %1 of center").arg(direction_from_sign(display_offset_m));
      }
    } else {
      primary_text = QStringLiteral("Lane centering standby");
    }

    QString secondary_text;
    if (centering_display_valid) {
      if (offset_small) {
        secondary_text = QStringLiteral("Offset: < 1 cm from center");
      } else {
        secondary_text = QStringLiteral("Offset: %1 cm %2 of center")
                            .arg(QString::number(display_offset_cm, 'f', decimal_precision))
                            .arg(direction_from_sign(display_offset_m));
      }
    } else {
      secondary_text = QStringLiteral("Offset: unknown");
    }

    const int indicator_width = 720;
    const int indicator_height = 160;
    QRect indicator_rect(QPoint(surface_rect.center().x() - indicator_width / 2,
                                surface_rect.bottom() - indicator_height - 148),
                         QSize(indicator_width, indicator_height));

    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(0, 0, 0, 190));
    painter.drawRoundedRect(indicator_rect, 36, 36);

    painter.setPen(QColor(255, 255, 255, 245));
    QFont title_font = InterFont(56, QFont::DemiBold);
    QFont detail_font = InterFont(42, QFont::Medium);

    painter.setFont(title_font);
    QRect title_rect = indicator_rect.adjusted(32, 26, -32, -indicator_height / 2);
    painter.drawText(title_rect, Qt::AlignCenter | Qt::TextWordWrap, primary_text);

    painter.setFont(detail_font);
    painter.drawText(indicator_rect.adjusted(32, indicator_height / 2 - 2, -32, -26), Qt::AlignCenter, secondary_text);

    painter.restore();
  }

  painter.restore();
}

void ModelRendererSP::drawLaneLines(QPainter &painter) {
  ModelRenderer::drawLaneLines(painter);

  if (centering_indicator_blink_intensity <= 0.0f || std::abs(centering_indicator_edge_sign) < 1e-4f) {
    return;
  }

  const int highlight_idx = centering_indicator_edge_sign > 0.0f ? 2 : 1;
  if (highlight_idx < 0 || highlight_idx >= static_cast<int>(std::size(lane_line_vertices))) {
    return;
  }

  const float blink_wave = 0.5f * (1.0f + std::sin(centering_indicator_blink_phase));
  const float alpha_float = 210.0f * centering_indicator_blink_intensity * blink_wave;
  if (alpha_float <= 1.0f) {
    return;
  }

  const int alpha = std::clamp(static_cast<int>(std::lround(alpha_float)), 0, 255);
  painter.save();
  painter.setBrush(QColor(178, 102, 255, alpha));
  painter.drawPolygon(lane_line_vertices[highlight_idx]);
  painter.restore();
}

void ModelRendererSP::update_model(const cereal::ModelDataV2::Reader &model, const cereal::RadarState::LeadData::Reader &lead) {
  ModelRenderer::update_model(model, lead);
  const auto &model_position = model.getPosition();
  const auto &lane_lines = model.getLaneLines();
  float max_distance = std::clamp(*(model_position.getX().end() - 1), MIN_DRAW_DISTANCE, MAX_DRAW_DISTANCE);
  int max_idx = get_path_length_idx(lane_lines[0], max_distance);
  // update blindspot vertices
  float max_distance_barrier = 100;
  int max_idx_barrier = std::min(max_idx, get_path_length_idx(lane_lines[0], max_distance_barrier));
  mapLineToPolygon(model.getLaneLines()[1], 0.2, -0.05, &left_blindspot_vertices, max_idx_barrier);
  mapLineToPolygon(model.getLaneLines()[2], 0.2, -0.05, &right_blindspot_vertices, max_idx_barrier);
}

void ModelRendererSP::drawPath(QPainter &painter, const cereal::ModelDataV2::Reader &model, const QRect &surface_rect) {
  auto *s = uiState();
  auto &sm = *(s->sm);
  bool blindspot = Params().getBool("BlindSpot");

  if (blindspot) {
    bool left_blindspot = sm["carState"].getCarState().getLeftBlindspot();
    bool right_blindspot = sm["carState"].getCarState().getRightBlindspot();

    //painter.setBrush(QColor::fromRgbF(1.0, 0.0, 0.0, 0.4));  // Red with alpha for blind spot

    if (left_blindspot && !left_blindspot_vertices.isEmpty()) {
      QLinearGradient gradient(0, 0, surface_rect.width(), 0); // Horizontal gradient from left to right
      gradient.setColorAt(0.0, QColor(255, 165, 0, 102)); // Orange with alpha
      gradient.setColorAt(1.0, QColor(255, 255, 0, 102)); // Yellow with alpha
      painter.setBrush(gradient);
      painter.drawPolygon(left_blindspot_vertices);
    }

    if (right_blindspot && !right_blindspot_vertices.isEmpty()) {
      QLinearGradient gradient(surface_rect.width(), 0, 0, 0); // Horizontal gradient from right to left
      gradient.setColorAt(0.0, QColor(255, 165, 0, 102)); // Orange with alpha
      gradient.setColorAt(1.0, QColor(255, 255, 0, 102)); // Yellow with alpha
      painter.setBrush(gradient);
      painter.drawPolygon(right_blindspot_vertices);
    }
  }

  bool rainbow = Params().getBool("RainbowMode");
  bool disable_accel_effect = !rainbow;
  float a_ego = sm["carState"].getCarState().getAEgo();
  constexpr float accel_start_threshold = 0.25f;
  constexpr float accel_stop_threshold = 0.15f;
  constexpr float accel_fade_in_seconds = 0.5f;
  constexpr float accel_fade_out_seconds = 1.0f;
  static float accel_presence = 0.0f;
  static bool accel_state = false;
  static auto last_accel_update = std::chrono::steady_clock::now();
  static float rainbow_presence = 0.0f;
  if (!accel_state && a_ego >= accel_start_threshold) {
    accel_state = true;
  } else if (accel_state && a_ego <= accel_stop_threshold) {
    accel_state = false;
  }
  //float v_ego = sm["carState"].getCarState().getVEgo();

  const auto &selfdrive_state = sm["selfdriveState"].getSelfdriveState();
  const QString alert_type = QString::fromUtf8(selfdrive_state.getAlertType().cStr());
  static const std::array<QString, 7> hazard_prefixes = {
      QStringLiteral("steerSaturated"),
      QStringLiteral("aeb"),
      QStringLiteral("stockAeb"),
      QStringLiteral("fcw"),
      QStringLiteral("driverDistracted"),
      QStringLiteral("driverUnresponsive"),
      QStringLiteral("manualRestart"),
  };
  const bool hazard_active = !alert_type.isEmpty() &&
      std::any_of(hazard_prefixes.begin(), hazard_prefixes.end(), [&](const QString &prefix) { return alert_type.startsWith(prefix); });

  static float hazard_mix = 0.0f;
  static auto last_hazard_update = std::chrono::steady_clock::now();
  static float hazard_hold = 0.0f;
  auto now = std::chrono::steady_clock::now();
  float dt = std::chrono::duration<float>(now - last_hazard_update).count();
  last_hazard_update = now;

  static auto last_frame_time = std::chrono::steady_clock::now();
  float frame_dt = std::chrono::duration<float>(now - last_frame_time).count();
  last_frame_time = now;

  constexpr float rainbow_transition_seconds = 0.5f;
  float target_rainbow_presence = (hazard_mix <= 0.0f) ? 1.0f : 0.0f;
  if (frame_dt > 0.0f) {
    float transition_step = frame_dt / std::max(rainbow_transition_seconds, 1e-3f);
    if (target_rainbow_presence > rainbow_presence) {
      rainbow_presence = std::min(target_rainbow_presence, rainbow_presence + transition_step);
    } else if (rainbow_presence > target_rainbow_presence) {
      rainbow_presence = std::max(target_rainbow_presence, rainbow_presence - transition_step);
    }
  }

  constexpr float hazard_hold_seconds = 0.5f;
  constexpr float hazard_fade_seconds = 1.0f;
  if (hazard_active) {
    hazard_mix = 1.0f;
    hazard_hold = hazard_hold_seconds;
  } else if (hazard_mix > 0.0f && dt > 0.0f) {
    if (hazard_hold > 0.0f) {
      hazard_hold = std::max(0.0f, hazard_hold - dt);
    } else {
      hazard_mix = std::max(0.0f, hazard_mix - dt / hazard_fade_seconds);
    }
  }

  float accel_dt = std::chrono::duration<float>(now - last_accel_update).count();
  last_accel_update = now;
  if (accel_dt > 0.0f) {
    float target_presence = accel_state ? 1.0f : 0.0f;
    if (target_presence > accel_presence) {
      accel_presence = std::min(target_presence, accel_presence + accel_dt / accel_fade_in_seconds);
    } else if (accel_presence > target_presence) {
      accel_presence = std::max(target_presence, accel_presence - accel_dt / accel_fade_out_seconds);
    }
  }

  float base_wave_speed = 0.35f;
  float base_scroll_speed = 0.10f;
  float base_speed_multiplier = 1.0f;
  if (disable_accel_effect) {
    base_speed_multiplier += 0.6f * std::clamp(accel_presence, 0.0f, 1.0f);
  }

  if (hazard_mix > 0.0f) {
    ModelRenderer::drawPath(painter, model, surface_rect.height());

    QLinearGradient hazard_bg(0, surface_rect.height(), 0, 0);
    hazard_bg.setColorAt(0.0f, QColor::fromRgbF(0.45f, 0.0f, 0.0f, 0.82f * hazard_mix));
    hazard_bg.setColorAt(0.5f, QColor::fromRgbF(0.78f, 0.14f, 0.14f, 0.68f * hazard_mix));
    hazard_bg.setColorAt(1.0f, QColor::fromRgbF(0.92f, 0.45f, 0.45f, 0.55f * hazard_mix));
    painter.setBrush(hazard_bg);
    painter.drawPolygon(track_vertices);
    return;
  }

  const bool show_rainbow = true;
  if (rainbow_presence <= 0.0f) {
    ModelRenderer::drawPath(painter, model, surface_rect.height());
    return;
  }

  if (rainbow_presence < 1.0f) {
    painter.save();
    painter.setOpacity(1.0f - rainbow_presence);
    ModelRenderer::drawPath(painter, model, surface_rect.height());
    painter.restore();
  }

  if (show_rainbow) { // Kia EV9 "Ocean Blue" inspired gradient with subtle motion

    struct GradientStop {
      float position;
      float hue_deg;
      float saturation;
      float lightness;
      float alpha;
    };

    static constexpr std::array<GradientStop, 4> ocean_stops = {{
        {0.00f, 206.0f, 0.70f, 0.32f, 0.85f},
        {0.35f, 202.0f, 0.72f, 0.40f, 0.75f},
        {0.70f, 198.0f, 0.74f, 0.55f, 0.65f},
        {1.00f, 192.0f, 0.60f, 0.68f, 0.55f},
    }};

    static constexpr std::array<GradientStop, 4> warning_stops = {{
        {0.00f, 358.0f, 0.78f, 0.30f, 0.93f},
        {0.35f, 5.0f, 0.82f, 0.39f, 0.82f},
        {0.70f, 12.0f, 0.85f, 0.52f, 0.72f},
        {1.00f, 18.0f, 0.76f, 0.65f, 0.62f},
    }};

    auto lerp = [](float a, float b, float t) { return a + (b - a) * t; };
    auto clamp01 = [](float v) { return std::clamp(v, 0.0f, 1.0f); };

    auto sample_stops = [&](const std::array<GradientStop, 4> &stops, float position) {
      if (position <= stops.front().position) return stops.front();
      if (position >= stops.back().position) return stops.back();

      const GradientStop *left = &stops.front();
      const GradientStop *right = &stops.back();
      for (size_t i = 1; i < stops.size(); ++i) {
        if (position <= stops[i].position) {
          left = &stops[i - 1];
          right = &stops[i];
          break;
        }
      }

      float span = std::max(1e-4f, right->position - left->position);
      float t = clamp01((position - left->position) / span);

      return GradientStop{
          position,
          lerp(left->hue_deg, right->hue_deg, t),
          lerp(left->saturation, right->saturation, t),
          lerp(left->lightness, right->lightness, t),
          lerp(left->alpha, right->alpha, t),
      };
    };

    auto blend_colors = [&](const QColor &a, const QColor &b, float t) {
      float mix = clamp01(t);
      float r = lerp(a.redF(), b.redF(), mix);
      float g = lerp(a.greenF(), b.greenF(), mix);
      float bl = lerp(a.blueF(), b.blueF(), mix);
      float alpha = clamp01(lerp(a.alphaF(), b.alphaF(), mix));
      return QColor::fromRgbF(clamp01(r), clamp01(g), clamp01(bl), alpha);
    };

    auto wrap_unit = [](float v) {
      float wrapped = std::fmod(v, 1.0f);
      return wrapped < 0.0f ? wrapped + 1.0f : wrapped;
    };

    float accel_visibility = disable_accel_effect ? 0.0f : accel_presence;
    float rainbow_speed_multiplier = (!disable_accel_effect && accel_visibility > 0.0f) ? 1.5f + accel_visibility * 0.4f : 1.0f;
    float animation_speed = base_wave_speed * base_speed_multiplier * rainbow_speed_multiplier;
    float rainbow_scroll_speed = base_scroll_speed * base_speed_multiplier * rainbow_speed_multiplier;
    float lightness_boost = 0.05f * accel_visibility;
    float saturation_boost = 0.08f * accel_visibility;
    float alpha_boost = 0.08f * accel_visibility;

    constexpr float kTau = 6.283185307f;
    static constexpr std::array<float, 9> sample_positions = {{
        0.00f, 0.125f, 0.25f, 0.375f, 0.50f, 0.625f, 0.75f, 0.875f, 1.00f,
    }};

    static float wave_phase = 0.0f;
    static float rainbow_phase_shift = 0.0f;
    static float rainbow_wave_phase = 0.0f;

    if (frame_dt > 0.0f) {
      wave_phase = std::fmod(wave_phase + animation_speed * frame_dt, kTau);
      rainbow_phase_shift = wrap_unit(rainbow_phase_shift + rainbow_scroll_speed * frame_dt);
      rainbow_wave_phase = std::fmod(rainbow_wave_phase + 0.8f * frame_dt, kTau);
    }

    QLinearGradient bg(0, surface_rect.height(), 0, 0);

    for (float position : sample_positions) {
      const auto ocean = sample_stops(ocean_stops, position);
      const auto warning = sample_stops(warning_stops, position);

      float wave = 0.5f * std::sin(wave_phase + position * 3.0f) + 0.5f;

      float base_hue_mod = lerp(10.0f, 6.0f, hazard_mix);
      float base_lightness_mod = lerp(0.08f, 0.05f, hazard_mix);
      float base_saturation_mod = lerp(0.05f, 0.04f, hazard_mix);
      float base_alpha_mod = lerp(0.04f, 0.05f, hazard_mix);

      float hue_mod = base_hue_mod + 3.0f * accel_visibility;
      float lightness_mod = base_lightness_mod + 0.03f * accel_visibility;
      float saturation_mod = base_saturation_mod + 0.08f * accel_visibility;
      float alpha_mod = base_alpha_mod + 0.05f * accel_visibility;

      float wave_offset = wave - 0.5f;
      float base_wave_strength = accel_visibility > 0.0f ? 0.0f : 1.0f;

      float base_hue = std::fmod(lerp(ocean.hue_deg, warning.hue_deg, hazard_mix) + wave_offset * hue_mod * base_wave_strength + 360.0f, 360.0f);
      float base_lightness = clamp01(lerp(ocean.lightness, warning.lightness, hazard_mix) + wave_offset * lightness_mod * base_wave_strength + lightness_boost);
      float base_saturation = clamp01(lerp(ocean.saturation, warning.saturation, hazard_mix) - wave_offset * saturation_mod * base_wave_strength + saturation_boost);
      float base_alpha = clamp01(lerp(ocean.alpha, warning.alpha, hazard_mix) - wave_offset * alpha_mod * base_wave_strength + alpha_boost);

      QColor base_color = QColor::fromHslF(base_hue / 360.0f, base_saturation, base_lightness, clamp01(0.45f + 0.45f * base_alpha));

      float rainbow_phase = wrap_unit(position + rainbow_phase_shift);
      float rainbow_wave_primary = 0.5f * std::sin(rainbow_wave_phase + position * (kTau * 0.8f)) + 0.5f;
      float rainbow_wave_secondary = 0.5f * std::sin(rainbow_wave_phase * 1.3f + position * (kTau * 0.45f)) + 0.5f;
      float hue_cycle = wrap_unit(rainbow_phase + (rainbow_wave_primary - 0.5f) * 0.25f);
      float rainbow_hue = hue_cycle * 360.0f;
      float rainbow_saturation = clamp01(0.80f + 0.14f * accel_visibility + (rainbow_wave_secondary - 0.5f) * 0.24f);
      float rainbow_lightness = clamp01(0.52f + accel_visibility * 0.10f + (0.5f - rainbow_wave_primary) * 0.20f);
      float rainbow_alpha = clamp01(0.66f + 0.18f * accel_visibility + (rainbow_wave_secondary - 0.5f) * 0.12f);

      QColor rainbow_color = QColor::fromHslF(rainbow_hue / 360.0f, rainbow_saturation, rainbow_lightness, rainbow_alpha);
      QColor final_color = blend_colors(base_color, rainbow_color, accel_visibility);

      bg.setColorAt(position, final_color);
    }

    painter.setBrush(bg);
    painter.drawPolygon(track_vertices);
  }
}

