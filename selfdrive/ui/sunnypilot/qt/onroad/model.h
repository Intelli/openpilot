/**
 * Copyright (c) 2021-, Haibin Wen, sunnypilot, and a number of other contributors.
 *
 * This file is part of sunnypilot and is licensed under the MIT License.
 * See the LICENSE.md file in the root directory for more details.
 */

#pragma once

#include <chrono>

#include "selfdrive/ui/qt/onroad/model.h"

class ModelRendererSP : public ModelRenderer {
public:
  ModelRendererSP() = default;
  void draw(QPainter &painter, const QRect &surface_rect);

private:
  void update_model(const cereal::ModelDataV2::Reader &model, const cereal::RadarState::LeadData::Reader &lead) override;
  void drawPath(QPainter &painter, const cereal::ModelDataV2::Reader &model, const QRect &rect) override;
  void drawLaneLines(QPainter &painter);

  QPolygonF left_blindspot_vertices;
  QPolygonF right_blindspot_vertices;
  bool centering_indicator_active = false;
  float centering_indicator_edge_sign = 0.0f;
  float centering_indicator_magnitude = 0.0f;
  cereal::ControlsState::LaneCenteringSource centering_indicator_source = cereal::ControlsState::LaneCenteringSource::NONE;
  float centering_indicator_opacity = 0.0f;
  std::chrono::steady_clock::time_point centering_indicator_last_update = std::chrono::steady_clock::now();
  std::chrono::steady_clock::time_point centering_indicator_last_signal = std::chrono::steady_clock::now();
  std::chrono::steady_clock::time_point centering_indicator_last_controls_update = std::chrono::steady_clock::now();
  cereal::ControlsState::LaneCenteringSource centering_indicator_last_nonzero_source = cereal::ControlsState::LaneCenteringSource::NONE;
  float centering_indicator_prev_magnitude = 0.0f;
  float centering_indicator_blink_intensity = 0.0f;
  float centering_indicator_blink_phase = 0.0f;
  bool centering_display_valid = false;
  float centering_display_offset_m = 0.0f;
  bool centering_adjusting_display = false;
  bool centering_edge_mode = false;
};
