import dataclasses

import numpy as np

from openpilot.selfdrive.controls.lib.ev9_path_input import CameraMount, PathGeometryConfig, build_path_input


def fixture():
  x = np.linspace(0, 20, 33)

  def line(y):
    return dict(x=np.linspace(0, 50, 33), y=np.full(33, y))

  model = dict(
    position=dict(x=x, y=np.zeros(33), t=np.linspace(0, 10, 33)),
    orientation=dict(z=np.zeros(33), t=np.linspace(0, 10, 33)),
    laneLines=[line(-5), line(-2), line(2), line(5)],
    laneLineProbs=[0.9] * 4,
    laneLineStds=[0.1] * 4,
    roadEdges=[line(-3), line(3)],
    roadEdgeStds=[0.1] * 2,
  )
  config = PathGeometryConfig(CameraMount(2.0, 0.0), True, 4.0, 1.0, 1.0)
  return model, config


def run(model, config, **kwargs):
  return build_path_input(model, config, source_time=1.0, now=1.1, model_valid=True, **kwargs)


def test_no_invented_rear_coverage_or_permission():
  model, config = fixture()
  result = run(model, config)
  assert result.available and not result.execution_authorized
  assert not result.sampled_body_covered[0]
  assert not result.preserve_reference_pose.any() and result.lateral_allowance[0] == 1.0
  assert result.boundary_source == 'inner_lanes'
  assert np.all(result.lateral_allowance <= config.max_deviation)
  assert result.left[0, 0] == 2.0


def test_road_only_is_geometry_not_lane_permission():
  model, config = fixture()
  model['laneLineProbs'] = [0.1] * 4
  result = run(model, config)
  assert result.available and result.boundary_source == 'road_edges_geometry_only'
  assert not result.execution_authorized
  model['roadEdgeStds'] = [2.0, 2.0]
  fallback = run(model, config)
  assert fallback.available and fallback.boundary_source == 'model_path'


def test_body_heading_and_front_overhang_change_coverage():
  model, config = fixture()
  base = run(model, config)
  model['orientation']['z'] = np.full(33, 0.5)
  turned = run(model, config)
  assert np.count_nonzero(turned.sampled_body_covered) < np.count_nonzero(base.sampled_body_covered)


def test_moving_camera_transform_is_not_static_translation():
  model, config = fixture()
  yaw = np.linspace(0, 0.2, 33)
  rear = np.column_stack((np.linspace(0, 20, 33), np.zeros(33)))
  camera = rear + np.column_stack((2 * np.cos(yaw), 2 * np.sin(yaw))) - [2.0, 0.0]
  model['position']['x'] = camera[:, 0]
  model['position']['y'] = -camera[:, 1]
  model['orientation']['z'] = -yaw
  result = run(model, config)
  np.testing.assert_allclose(result.xy, rear, atol=1e-12)
  np.testing.assert_allclose(result.yaw, yaw)


def test_prefix_is_explicit_and_unmatched_yaw_rejected():
  model, config = fixture()
  assert not run(model, config, horizon_distance=10.0).complete_observed_reference
  model['orientation']['t'] = np.linspace(0.01, 10.01, 33)
  assert run(model, config).reason == 'unmatched_path_heading'


def test_missing_alignment_or_nonfinite_mount_rejected():
  model, config = fixture()
  assert not run(model, dataclasses.replace(config, alignment_established=False)).available
  assert not run(model, dataclasses.replace(config, mount=CameraMount(float('nan'), 0))).available


def test_model_budget_is_not_derated_by_unknown_boundary_space():
  model, config = fixture()
  result = run(model, config)
  np.testing.assert_array_equal(result.lateral_allowance, 1.)
  assert not result.preserve_reference_pose.any()
  assert result.reliable_boundaries  # Search budget is distinct from binding observed constraints.


def test_complete_observed_left_and_right_intersection_geometry():
  for sign in (-1, 1):
    theta = np.linspace(-.4, 1.95, 65)
    center = np.column_stack((12*np.sin(theta), 12*(1-np.cos(theta))))
    normal = np.column_stack((-np.sin(theta), np.cos(theta)))
    left, right = center+3.5*normal, center-3.5*normal
    angle = np.linspace(0., np.pi/2, 33)
    xy = np.column_stack((12*np.sin(angle), 12*(1-np.cos(angle))))
    if sign < 0:
      xy[:, 1] *= -1
      left, right = right*[1, -1], left*[1, -1]
    yaw = sign*angle
    camera = xy + np.column_stack((2*np.cos(yaw), 2*np.sin(yaw))) - [2, 0]
    def line(points):
      return dict(x=points[:, 0]-2, y=-points[:, 1])
    model, config = fixture()
    model.update(position=dict(x=camera[:, 0], y=-camera[:, 1], t=np.arange(33)),
                 orientation=dict(z=-yaw, t=np.arange(33)), laneLines=[line(left), line(left), line(right), line(right)])
    result = run(model, config)
    assert result.available and result.sampled_body_covered.all()
    assert result.heading_allowance.min() > 0
    assert not result.execution_authorized
    # Observing only the first half does not grant room in the unseen exit.
    model['laneLines'] = [line(left[:35]), line(left[:35]), line(right[:35]), line(right[:35])]
    partial = run(model, config)
    assert partial.available and not partial.preserve_reference_pose[-1]
    assert partial.heading_allowance[-1] > 0 and partial.lateral_allowance[-1] == 1.0



def check_candidate(result, config, shift=0.):
  from openpilot.selfdrive.controls.lib.ev9_path_geometry import body_respects_observed
  return body_respects_observed(result.xy+[0., shift], result.yaw, result, reference_distance=result.distance,
                                front=config.front, rear=config.rear, half_width=config.half_width)


def test_missing_boundaries_leave_explicit_unverified_model_path_budget():
  model, config = fixture()
  for key in ('laneLines', 'laneLineProbs', 'laneLineStds', 'roadEdges', 'roadEdgeStds'):
    model.pop(key)
  result = run(model, config)
  assert result.available and result.boundary_source == 'model_path'
  assert not result.reliable_boundaries and not result.execution_authorized
  assert result.confidence['observed_free_space_certified'] is False
  np.testing.assert_array_equal(result.lateral_allowance, 1.)
  assert check_candidate(result, config, .9)


def test_low_confidence_wrong_branch_does_not_become_a_hard_wall():
  model, config = fixture()
  model['laneLineProbs'] = [.01]*4
  model['roadEdgeStds'] = [1.5, 2.]
  for line in model['roadEdges']:
    line['y'] = np.linspace(0., 40., 33)
  result = run(model, config)
  assert result.available and result.boundary_source == 'model_path'
  assert check_candidate(result, config, .8)


def test_reliable_boundary_conflict_remains_binding_even_for_original_path():
  model, config = fixture()
  model['laneLines'][1]['y'] = np.full(33, -.8)
  result = run(model, config)
  assert result.available and result.reliable_boundaries
  assert not check_candidate(result, config)
  assert not check_candidate(result, config, .8)


def test_sides_are_independent_and_unseen_ends_are_not_walls():
  model, config = fixture()
  model.pop('roadEdges')
  model['laneLineProbs'][2] = .01
  model['laneLines'][1]['x'] = np.linspace(4., 10., 33)-2.
  result = run(model, config)
  assert len(result.reliable_boundaries) == 1
  assert result.reliable_boundaries[0].side == 1
  assert not result.reliable_boundaries[0].applicable[0]
  assert not result.reliable_boundaries[0].applicable[-1]
  assert check_candidate(result, config)  # Full body may extend beyond observed endpoints.
  assert check_candidate(result, config, -.9)  # No invented right-hand boundary.
  assert not check_candidate(result, config, .9)  # Actual finite left curb still binds.


def test_each_side_falls_back_independently_to_reliable_road_edge():
  model, config = fixture()
  model['laneLineStds'][1] = 1.
  model['roadEdgeStds'][0] = .1
  result = run(model, config)
  assert [b.source for b in result.reliable_boundaries] == ['road_edges_geometry_only', 'inner_lanes']
  assert result.boundary_source == 'mixed_observed'



def test_nonfinite_left_std_preserves_binding_reliable_right_side():
  for source in ('lanes', 'edges'):
    model, config = fixture()
    if source == 'lanes':
      model.pop('roadEdges')
      model['laneLineStds'][1] = float('nan')
    else:
      model['laneLineProbs'] = [.01]*4
      model['roadEdgeStds'][0] = float('nan')
    result = run(model, config)
    assert result.available and len(result.reliable_boundaries) == 1
    assert result.reliable_boundaries[0].side == -1
    assert result.confidence['boundary_reliable'] == [False, True]
    assert check_candidate(result, config, .9)
    assert not check_candidate(result, config, -2.)


def test_observed_lane_room_expands_only_its_own_side_with_full_body_coverage():
  model, config = fixture()
  model['laneLines'][1]['x'] = np.linspace(-10., 50., 33)
  model['laneLines'][1]['y'] = np.full(33, -4.)
  result = run(model, config)
  np.testing.assert_allclose(result.lateral_upper, 4. - config.half_width - config.margin - 2*.1)
  np.testing.assert_array_equal(result.lateral_lower, -1.)
  # This extra room is an optimization budget; it does not certify a candidate.
  assert check_candidate(result, config, 1.5)
  assert not check_candidate(result, config, 3.)
  # A distant road edge cannot authorize leaving the current lane.
  model['laneLineProbs'][1] = .01
  model['roadEdges'][0] = model['laneLines'][1]
  road = run(model, config)
  np.testing.assert_array_equal(road.lateral_upper, 1.)


def test_lane_budget_contracts_with_uncertainty_and_never_extends_finite_ends():
  model, config = fixture()
  model['laneLines'][1]['x'] = np.linspace(4., 12., 33)-2.
  model['laneLines'][1]['y'] = np.full(33, -4.)
  certain = run(model, config)
  model['laneLineStds'][1] = .4
  uncertain = run(model, config)
  assert np.max(uncertain.lateral_upper) < np.max(certain.lateral_upper)
  assert certain.lateral_upper[0] == certain.lateral_upper[-1] == 1.
  model['laneLines'][1]['y'] = np.full(33, -.8)
  conflicting = run(model, config)
  np.testing.assert_array_equal(conflicting.lateral_upper, 1.)
  assert not check_candidate(conflicting, config)


def test_lane_budget_mirrors_with_turn_side():
  model, config = fixture()
  for index, y in [(1, -4.), (2, 4.)]:
    model['laneLines'][index]['x'] = np.linspace(-10., 50., 33)
    model['laneLines'][index]['y'] = np.full(33, y)
  result = run(model, config)
  assert np.all(result.lateral_upper > 1.)
  np.testing.assert_array_equal(result.lateral_upper, -result.lateral_lower)
