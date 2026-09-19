from types import SimpleNamespace

import numpy as np
import pytest

from openpilot.selfdrive.controls.lib.ev9_turn_assist import _forward_edge_clear, ev9_turn_assist_authority


def model_edges(width=10., std=.1):
  x = np.linspace(0., 40., 33)
  return SimpleNamespace(roadEdges=[SimpleNamespace(x=x.copy(), y=np.full(33, -width)),
                                    SimpleNamespace(x=x.copy(), y=np.full(33, width))], roadEdgeStds=[std, std])


def authority(model, curvature=.05, distance=6., **kwargs):
  options = dict(model_age=.05, blindspot=False, model_valid=True)
  return ev9_turn_assist_authority(model, curvature, distance, **(options | kwargs))


@pytest.mark.parametrize('direction', [-1., 1.])
def test_clear_observed_space_allows_assistance(direction):
  assert authority(model_edges(), direction * .05) == 1.


@pytest.mark.parametrize('direction', [-1., 1.])
def test_front_corner_is_checked_even_when_rear_axle_arc_is_clear(direction):
  # Rear axle moves less than 0.8m sideways; front corner crosses the 3m edge.
  assert authority(model_edges(width=3.), direction * .1, 4.) == 0.
  assert authority(model_edges(width=6.), direction * .1, 4.) == 1.


@pytest.mark.parametrize('direction', [-1., 1.])
def test_only_turn_side_edge_is_used(direction):
  model = model_edges()
  other = 0 if direction > 0. else 1
  model.roadEdgeStds[other] = 10.
  model.roadEdges[other].y[:] = 0.
  assert authority(model, direction * .05) == 1.
  model.roadEdges[1 - other].y[:] = direction * 1.
  assert authority(model, direction * .05) == 0.


def test_edge_cutting_across_body_is_rejected():
  model = model_edges()
  model.roadEdges[1].y = np.where(model.roadEdges[1].x < 4., 6., .5)
  assert authority(model) == 0.


def test_concave_edge_between_corners_is_rejected():
  points = np.array([[0., -2.], [2., -.5], [4., -2.], [20., -2.]])
  # Front corners at x=4 are on the permitted side; the edge enters the side
  # of the body between them and the unobserved rear corners.
  assert not _forward_edge_clear(points, np.zeros((1, 2)), np.zeros(1), -1, 4., 1., 1.)


def test_body_completely_beyond_edge_is_rejected_without_intersection():
  model = model_edges()
  model.roadEdges[1].y[:] = -10.
  assert authority(model) == 0.


def test_short_edge_is_unknown_not_an_opening():
  model = model_edges()
  model.roadEdges[1].x = np.linspace(0., 3., 33)
  assert authority(model) == 0.


@pytest.mark.parametrize('std', [-1., .5, .8, float('nan'), float('inf')])
def test_unreliable_edge_cannot_authorize_assistance(std):
  assert authority(model_edges(std=std)) == 0.


def test_confidence_fades_before_cutoff():
  values = [authority(model_edges(std=std), base_curvature=.01) for std in (.3, .35, .4, .45, .499, .5)]
  assert values[0] == 1. and values[-1] == 0.
  assert all(a > b for a, b in zip(values[:-1], values[1:], strict=True))


def test_blended_command_is_checked_not_only_raw_proposal():
  model = model_edges(width=3.5, std=.4)
  # At half authority the weaker arc has room; increasing the baseline makes
  # the actual blended command cross the edge and must be rejected.
  assert authority(model, .1, 4., base_curvature=0.) == pytest.approx(.5)
  assert authority(model, .1, 4., base_curvature=.09) == 0.


@pytest.mark.parametrize('kwargs', [dict(blindspot=True), dict(model_valid=False), dict(model_age=.201),
                                   dict(model_age=-.02), dict(model_age=float('nan'))])
def test_missing_fresh_evidence_or_blindspot_withholds_assistance(kwargs):
  assert authority(model_edges(), **kwargs) == 0.


@pytest.mark.parametrize('fault', ['no_edge', 'no_std', 'nan', 'missing_y', 'duplicate_x', 'reversed_x', 'late_start', 'oversize'])
def test_malformed_boundary_is_unknown(fault):
  model = model_edges()
  edge = model.roadEdges[1]
  if fault == 'no_edge':
    model.roadEdges = []
  elif fault == 'no_std':
    model.roadEdgeStds = []
  elif fault == 'nan':
    edge.y[5] = float('nan')
  elif fault == 'missing_y':
    edge.y = []
  elif fault == 'duplicate_x':
    edge.x[1] = edge.x[0]
  elif fault == 'reversed_x':
    edge.x = edge.x[::-1]
  elif fault == 'late_start':
    edge.x += 5.
  elif fault == 'oversize':
    edge.x = np.linspace(0., 40., 1000)
    edge.y = np.full(1000, 10.)
  assert authority(model) == 0.
