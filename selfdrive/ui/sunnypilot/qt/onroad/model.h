/**
 * Copyright (c) 2021-, Haibin Wen, sunnypilot, and a number of other contributors.
 *
 * This file is part of sunnypilot and is licensed under the MIT License.
 * See the LICENSE.md file in the root directory for more details.
 */

#pragma once

#include "selfdrive/ui/qt/onroad/model.h"

class ModelRendererSP : public ModelRenderer {
public:
  ModelRendererSP() = default;
  void draw(QPainter &painter, const QRect &surface_rect);

private:
  void update_model(const cereal::ModelDataV2::Reader &model, const cereal::RadarState::LeadData::Reader &lead) override;
  void drawPath(QPainter &painter, const cereal::ModelDataV2::Reader &model, const QRect &rect) override;

  void drawLaneLinesAndEdges(QPainter &painter);

  QPolygonF left_blindspot_vertices;
  QPolygonF right_blindspot_vertices;
  bool centering_indicator_active = false;
  float centering_indicator_edge_sign = 0.0f;
  float centering_indicator_magnitude = 0.0f;
  cereal::ControlsState::LaneCenteringSource centering_indicator_source = cereal::ControlsState::LaneCenteringSource::NONE;
};
