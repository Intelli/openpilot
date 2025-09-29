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
  constexpr float hard_accel_threshold = 2.5f;  // m/s^2 threshold to trigger the effect
  constexpr float hard_accel_span = 2.0f;
  constexpr float hard_accel_fade_seconds = 1.0f;
  static float hard_accel_mix = 0.0f;
  static auto last_hard_accel_update = std::chrono::steady_clock::now();
  float target_hard_accel_mix = std::clamp((a_ego - hard_accel_threshold) / hard_accel_span, 0.0f, 1.0f);
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

  constexpr float hazard_hold_seconds = 1.0f;
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

  float hard_accel_dt = std::chrono::duration<float>(now - last_hard_accel_update).count();
  last_hard_accel_update = now;
  if (target_hard_accel_mix > 0.0f) {
    hard_accel_mix = target_hard_accel_mix;
  } else if (hard_accel_mix > 0.0f && hard_accel_dt > 0.0f) {
    hard_accel_mix = std::max(0.0f, hard_accel_mix - hard_accel_dt / hard_accel_fade_seconds);
  }

  if (rainbow) {
    // Kia EV9 "Ocean Blue" inspired gradient with subtle motion

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

    float time_offset = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::steady_clock::now().time_since_epoch()).count() / 1000.0f;
    float accel_influence = hard_accel_mix * (1.0f - hazard_mix);
    float animation_speed = lerp(1.2f, 2.6f, accel_influence);
    float lightness_boost = lerp(0.0f, 0.08f, accel_influence);
    float saturation_boost = lerp(0.0f, 0.12f, accel_influence);
    float alpha_boost = lerp(0.0f, 0.10f, accel_influence);

    QLinearGradient bg(0, surface_rect.height(), 0, 0);

    for (size_t i = 0; i < ocean_stops.size(); ++i) {
      const auto &ocean = ocean_stops[i];
      const auto &warning = warning_stops[i];

      float wave = 0.5f * std::sin(animation_speed * time_offset + ocean.position * 3.0f) + 0.5f;

      float base_hue_mod = lerp(10.0f, 6.0f, hazard_mix);
      float base_lightness_mod = lerp(0.08f, 0.05f, hazard_mix);
      float base_saturation_mod = lerp(0.05f, 0.04f, hazard_mix);
      float base_alpha_mod = lerp(0.04f, 0.05f, hazard_mix);

      float hue_mod = base_hue_mod + lerp(0.0f, 8.0f, accel_influence);
      float lightness_mod = base_lightness_mod + lerp(0.0f, 0.04f, accel_influence);
      float saturation_mod = base_saturation_mod + lerp(0.0f, 0.10f, accel_influence);
      float alpha_mod = base_alpha_mod + lerp(0.0f, 0.05f, accel_influence);

      float hue = std::fmod(lerp(ocean.hue_deg, warning.hue_deg, hazard_mix) + (wave - 0.5f) * hue_mod + 360.0f, 360.0f);
      float lightness = std::clamp(lerp(ocean.lightness, warning.lightness, hazard_mix) + (wave - 0.5f) * lightness_mod + lightness_boost, 0.0f, 1.0f);
      float saturation = std::clamp(lerp(ocean.saturation, warning.saturation, hazard_mix) + (0.5f - wave) * saturation_mod + saturation_boost, 0.0f, 1.0f);
      float alpha = std::clamp(lerp(ocean.alpha, warning.alpha, hazard_mix) + (0.5f - wave) * alpha_mod + alpha_boost, 0.4f, 0.95f);

      QColor color = QColor::fromHslF(hue / 360.0f, saturation, lightness, alpha);
      bg.setColorAt(ocean.position, color);
    }

    painter.setBrush(bg);
    painter.drawPolygon(track_vertices);
  } else {
    // Normal path rendering with hazard fade overlay
    ModelRenderer::drawPath(painter, model, surface_rect.height());

    if (hazard_mix > 0.0f) {
      QLinearGradient hazard_bg(0, surface_rect.height(), 0, 0);
      hazard_bg.setColorAt(0.0f, QColor::fromRgbF(0.45f, 0.0f, 0.0f, 0.82f * hazard_mix));
      hazard_bg.setColorAt(0.5f, QColor::fromRgbF(0.78f, 0.14f, 0.14f, 0.68f * hazard_mix));
      hazard_bg.setColorAt(1.0f, QColor::fromRgbF(0.92f, 0.45f, 0.45f, 0.55f * hazard_mix));
      painter.setBrush(hazard_bg);
      painter.drawPolygon(track_vertices);
    }
  }
}
