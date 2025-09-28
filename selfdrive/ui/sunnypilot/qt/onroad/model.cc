/**
 * Copyright (c) 2021-, Haibin Wen, sunnypilot, and a number of other contributors.
 *
 * This file is part of sunnypilot and is licensed under the MIT License.
 * See the LICENSE.md file in the root directory for more details.
 */

#include "selfdrive/ui/sunnypilot/qt/onroad/model.h"


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
  //float v_ego = sm["carState"].getCarState().getVEgo();

  if (rainbow) {
    // Kia EV9 "Ocean Blue" inspired gradient with subtle motion
    float time_offset = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::steady_clock::now().time_since_epoch()).count() / 1000.0f;
    float animation_speed = 1.2f;

    struct GradientStop {
      float position;
      float hue_deg;
      float saturation;
      float lightness;
      float alpha;
    };

    const GradientStop stops[] = {
      {0.00f, 206.0f, 0.70f, 0.32f, 0.85f},
      {0.35f, 202.0f, 0.72f, 0.40f, 0.75f},
      {0.70f, 198.0f, 0.74f, 0.55f, 0.65f},
      {1.00f, 192.0f, 0.60f, 0.68f, 0.55f},
    };

    QLinearGradient bg(0, surface_rect.height(), 0, 0);

    for (const auto &stop : stops) {
      float wave = 0.5f * std::sin(animation_speed * time_offset + stop.position * 3.0f) + 0.5f;
      float hue = std::fmod(stop.hue_deg + (wave - 0.5f) * 10.0f + 360.0f, 360.0f);
      float lightness = std::clamp(stop.lightness + (wave - 0.5f) * 0.08f, 0.0f, 1.0f);
      float saturation = std::clamp(stop.saturation + (0.5f - wave) * 0.05f, 0.0f, 1.0f);
      float alpha = std::clamp(stop.alpha + (0.5f - wave) * 0.04f, 0.4f, 0.9f);

      QColor color = QColor::fromHslF(hue / 360.0f, saturation, lightness, alpha);
      bg.setColorAt(stop.position, color);
    }

    painter.setBrush(bg);
    painter.drawPolygon(track_vertices);
  } else {
    // Normal path rendering
    ModelRenderer::drawPath(painter, model, surface_rect.height());
  }
}
