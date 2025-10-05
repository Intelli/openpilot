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
  float a_ego = sm["carState"].getCarState().getAEgo();
  constexpr float accel_start_threshold = 0.24f;
  constexpr float accel_stop_threshold = 0.14f;
  constexpr float accel_fade_in_seconds = 0.5f;
  constexpr float accel_fade_out_seconds = 1.0f;
  static float accel_presence = 0.0f;
  static bool accel_state = false;
  static auto last_accel_update = std::chrono::steady_clock::now();
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

  if (rainbow) { // Kia EV9 "Ocean Blue" inspired gradient with subtle motion

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

    float accel_visibility = accel_presence;
    float rainbow_speed_multiplier = accel_visibility > 0.0f ? 1.5f : 1.0f;
    float animation_speed = base_wave_speed * rainbow_speed_multiplier;
    float rainbow_scroll_speed = base_scroll_speed * rainbow_speed_multiplier;
    float lightness_boost = 0.05f * accel_visibility;
    float saturation_boost = 0.08f * accel_visibility;
    float alpha_boost = 0.08f * accel_visibility;

    constexpr float kTau = 6.283185307f;
    auto smooth_cycle = [&wrap_unit](float phase) {
      float wrapped = wrap_unit(phase);
      return 0.5f - 0.5f * std::cos(wrapped * kTau);
    };
    auto seam_cycle = [&wrap_unit](float phase) {
      float wrapped = wrap_unit(phase + 0.5f);
      return 0.5f - 0.5f * std::cos(wrapped * kTau);
    };
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
      float rainbow_wave = 0.5f * std::sin(rainbow_wave_phase + position * (kTau * 0.6f)) + 0.5f;
      float trimmed_phase = smooth_cycle(rainbow_phase);
      float rainbow_hue = 160.0f + trimmed_phase * 120.0f;
      float rainbow_saturation = clamp01(0.78f + 0.10f * accel_visibility + 0.08f * (rainbow_wave - 0.5f));
      float rainbow_lightness = clamp01(0.50f + 0.08f * accel_visibility + 0.10f * (0.5f - rainbow_wave));
      float rainbow_alpha = clamp01(0.68f + 0.15f * accel_visibility + 0.08f * (0.5f - rainbow_wave));

      QColor rainbow_color = QColor::fromHslF(rainbow_hue / 360.0f, rainbow_saturation, rainbow_lightness, rainbow_alpha);
      float white_mix = std::pow(seam_cycle(rainbow_phase), 2.0f);
      if (white_mix > 0.0f) {
        float white_alpha = clamp01(0.50f + 0.25f * accel_visibility);
        QColor white_color = QColor::fromRgbF(1.0f, 1.0f, 1.0f, white_alpha);
        rainbow_color = blend_colors(rainbow_color, white_color, clamp01(white_mix));
      }
      QColor final_color = blend_colors(base_color, rainbow_color, accel_visibility);

      bg.setColorAt(position, final_color);
    }

    painter.setBrush(bg);
    painter.drawPolygon(track_vertices);
  } else {
    ModelRenderer::drawPath(painter, model, surface_rect.height());
  }
}
