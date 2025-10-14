/**
 * Copyright (c) 2021-, Haibin Wen, sunnypilot, and a number of other contributors.
 *
 * This file is part of sunnypilot and is licensed under the MIT License.
 * See the LICENSE.md file in the root directory for more details.
 */

#pragma once

#include <chrono>

#include "common/params.h"
#include "selfdrive/ui/qt/onroad/model.h"

class ModelRendererSP : public ModelRenderer {
public:
  ModelRendererSP() = default;
  void draw(QPainter &painter, const QRect &surface_rect);

private:
  void update_model(const cereal::ModelDataV2::Reader &model, const cereal::RadarState::LeadData::Reader &lead) override;
  void drawPath(QPainter &painter, const cereal::ModelDataV2::Reader &model, int height) override;
  void drawLaneLines(QPainter &painter);
  void drawLaneHighlight(QPainter &painter);

  // Lead status display methods
  void drawLeadStatus(QPainter &painter, int height, int width);
  void drawLeadStatusPosition(QPainter &painter, const cereal::RadarState::LeadData::Reader &lead_data,
                              const QPointF &chevron_pos, int height, int width);
  void drawBlindspot(QPainter &painter, const QRect &surface_rect, bool left_blindspot, bool right_blindspot);
  void drawRainbowPath(QPainter &painter, const QRect &surface_rect);

  QPolygonF left_blindspot_vertices;
  QPolygonF right_blindspot_vertices;

  // Lead status animation
  float lead_status_alpha = 0.0f;

  Params params;
  bool advanced_lane_centering_enabled = false;
  bool prev_lat_active = false;
  float centering_indicator_edge_sign = 0.0f;
  cereal::ControlsState::LaneCenteringSource centering_indicator_source = cereal::ControlsState::LaneCenteringSource::NONE;
  cereal::ControlsState::LaneCenteringSource centering_indicator_last_nonzero_source = cereal::ControlsState::LaneCenteringSource::NONE;
  bool centering_display_valid = false;
  float centering_display_offset_m = 0.0f;
  bool centering_adjusting_display = false;
  bool centering_edge_mode = false;
  bool centering_status_active = false;
  float centering_highlight_strength = 0.0f;
  float centering_highlight_phase = 0.0f;
  std::chrono::steady_clock::time_point centering_highlight_last_update = std::chrono::steady_clock::now();
  bool centering_panel_visible_state = false;
  bool centering_panel_request_active = false;
  std::chrono::steady_clock::time_point centering_panel_request_start = std::chrono::steady_clock::now();
};
