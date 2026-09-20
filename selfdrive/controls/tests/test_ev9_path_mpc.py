"""Standalone native MPC checks; generated host artifacts stay in pytest temp paths."""
from types import SimpleNamespace

import numpy as np
import pytest

from openpilot.selfdrive.controls.lib.ev9_path_mpc import Ev9PathMpc, N


@pytest.fixture(scope='module')
def native(tmp_path_factory):
  from openpilot.selfdrive.controls.lib.ev9_path_mpc_lib.generate import build
  solver = Ev9PathMpc(build(tmp_path_factory.mktemp('ev9-mpc')))
  yield solver
  solver.close()


def request():
  x = np.linspace(0., 10., 81)
  return dict(reference_xy=np.column_stack((x, np.zeros_like(x))), reference_yaw=np.zeros_like(x),
              initial_pose=np.zeros(3), initial_curvature=0., speeds=2., curvature_limit=.05,
              min_curvature=-.05, curvature_rate_time=.02, lateral_lower=-1., lateral_upper=1., heading_deviation=.2)


@pytest.mark.parametrize('preserve', [False, True])
def test_native_scalar_and_expanded_bounds_agree(native, preserve):
  args = request()
  args['preserve_reference'] = preserve
  scalar = native.solve(**args)
  for key in ['speeds', 'curvature_limit', 'min_curvature', 'curvature_rate_time', 'lateral_lower', 'lateral_upper', 'heading_deviation']:
    args[key] = np.full(81, args[key])
  args['preserve_reference'] = np.full(81, preserve)
  expanded = native.solve(**args)
  assert scalar.feasible and expanded.feasible
  for name in ['xy', 'yaw', 'curvature', 'distance', 'reference_distance']:
    np.testing.assert_array_equal(getattr(scalar, name), getattr(expanded, name))


@pytest.fixture
def straight_iteration_limit():
  # A known straight native candidate isolates the independent postchecks from
  # optimizer convergence. Its node states are deliberately not authoritative.
  def solve(capsule, length, reference, limits, initial, states, controls):
    np.ctypeslib.as_array(states, shape=((N+1)*4,))[:] = 0.
    control = np.ctypeslib.as_array(controls, shape=(N*2,)).reshape(N, 2)
    control[:, 0], control[:, 1] = 0., 1.
    return 2
  solver = Ev9PathMpc.__new__(Ev9PathMpc)
  solver._capsule = 1
  solver._library = SimpleNamespace(ev9_path_solve=solve, ev9_path_destroy=lambda capsule: None)
  return solver


@pytest.mark.parametrize('key,value', [('lateral_upper', -.5), ('lateral_lower', .5), ('curvature_limit', -.001), ('min_curvature', .001)])
def test_single_interior_bound_is_not_treated_as_constant(straight_iteration_limit, key, value):
  args = request()
  assert straight_iteration_limit.solve(**args).feasible
  args[key] = np.full(81, args[key])
  args[key][37] = value
  result = straight_iteration_limit.solve(**args)
  assert not result.feasible and result.reason == 'dense_bounds'


def test_single_preserved_interior_pose_still_checked(straight_iteration_limit):
  args = request()
  args['reference_xy'][37, 1] = .02
  assert straight_iteration_limit.solve(**args).feasible
  args['preserve_reference'] = np.zeros(81, dtype=bool)
  args['preserve_reference'][37] = True
  result = straight_iteration_limit.solve(**args)
  assert not result.feasible and result.reason == 'preserved_pose'
