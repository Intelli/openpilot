"""Native trajectory build and execution contract, independent of replay tools."""
from ctypes import POINTER, byref, c_char_p, c_double, c_int, c_void_p
import math
from types import SimpleNamespace

import numpy as np
import pytest

from openpilot.selfdrive.controls.lib.ev9_path_mpc import DENSE_SPACING, Ev9PathMpc, N
from openpilot.selfdrive.controls.lib.ev9_trajectory import MAX_SAMPLES


@pytest.fixture(scope='module')
def native(tmp_path_factory):
  from openpilot.selfdrive.controls.lib.ev9_path_mpc_lib.generate import build
  solver = Ev9PathMpc(build(tmp_path_factory.mktemp('path-native')))
  yield solver
  solver.close()


def request(sign=1):
  radius = 25.
  angle = np.linspace(0., .6, 81)
  return dict(reference_xy=np.column_stack((radius*np.sin(angle), sign*radius*(1.-np.cos(angle)))),
              reference_yaw=sign*angle, initial_pose=(0., 0., 0.), initial_curvature=sign/radius,
              speeds=3., curvature_limit=.06, min_curvature=-.06, curvature_rate_time=.02,
              lateral_lower=-1., lateral_upper=1., heading_deviation=.2)


def discrete_step(native, state, control, length):
  function = native._library.ev9_path_dyn_disc_phi_fun
  work = native._library.ev9_path_dyn_disc_phi_fun_work
  sizes = [c_int() for _ in range(4)]
  assert work(*[byref(size) for size in sizes]) == 0
  pointer = POINTER(c_double)
  inputs = [np.ascontiguousarray(value, dtype=np.float64) for value in (state, control, [length, 0., 0., 0.])]
  output = np.empty(4)
  arguments, results = (pointer*sizes[0].value)(), (pointer*sizes[1].value)()
  for index, value in enumerate(inputs):
    arguments[index] = value.ctypes.data_as(pointer)
  results[0] = output.ctypes.data_as(pointer)
  integer_work = (c_int*max(1, sizes[2].value))()
  real_work = (c_double*max(1, sizes[3].value))()
  function.argtypes = [POINTER(pointer), POINTER(pointer), POINTER(c_int), pointer, c_void_p]
  function.restype = c_int
  assert function(arguments, results, integer_work, real_work, None) == 0
  return output


@pytest.mark.parametrize('length', [1., 45., ((MAX_SAMPLES-1)//N)*N*DENSE_SPACING/1.3])
@pytest.mark.parametrize('scale', [.7, 1., 1.3])
@pytest.mark.parametrize('curvatures', [(-.08, -.08), (-.08, .08), (.08, -.08), (.08, .08), (0., 0.)])
def test_discrete_dynamics_match_independent_dense_quadrature(native, length, scale, curvatures):
  distance = length/N*scale
  initial, final = curvatures
  rate = (final-initial)/distance
  yaw = 2.7
  state = np.array([3., -7., yaw, initial])
  actual = discrete_step(native, state, [rate, scale], length)
  def heading(station):
    return yaw+initial*station+rate*station**2/2
  station = np.linspace(0., distance, 4097)
  def simpson(values):
    return distance/4096/3*(values[0]+values[-1]+4*values[1:-1:2].sum()+2*values[2:-1:2].sum())
  expected = [state[0]+simpson(np.cos(heading(station))), state[1]+simpson(np.sin(heading(station))), heading(distance), final]
  np.testing.assert_allclose(actual, expected, rtol=0., atol=1e-10)


@pytest.mark.parametrize('sign', [-1, 1])
def test_native_reuses_only_current_reference_and_boundary_constraints(native, sign):
  args = request(sign)
  original = native.solve(**args)
  assert original.feasible, original.reason
  blocked = native.solve(**dict(args, lateral_lower=.5, lateral_upper=.6))
  assert not blocked.feasible and not len(blocked.xy)
  opposite = native.solve(**request(-sign))
  assert opposite.feasible, opposite.reason
  repeated = native.solve(**args)
  assert repeated.feasible, repeated.reason
  np.testing.assert_allclose(repeated.xy, original.xy, rtol=0., atol=1e-8)


@pytest.mark.parametrize('version', [2, 3, 4, 5])
def test_older_native_library_is_rejected(monkeypatch, version):
  from openpilot.selfdrive.controls.lib import ev9_path_mpc
  monkeypatch.setattr(ev9_path_mpc, 'CDLL', lambda _: SimpleNamespace(ev9_path_abi_version=lambda: version))
  with pytest.raises(RuntimeError, match='ABI mismatch'):
    Ev9PathMpc('older-library')


def test_exhausted_inner_qp_stops_without_candidate(native, tmp_path, monkeypatch):
  from openpilot.selfdrive.controls.lib.ev9_path_mpc_lib.generate import build
  from acados_template import AcadosOcpSolver
  generate = AcadosOcpSolver.generate

  def limited_generate(ocp, *args, **kwargs):
    ocp.solver_options.qp_solver_iter_max = 1
    return generate(ocp, *args, **kwargs)

  monkeypatch.setattr(AcadosOcpSolver, 'generate', staticmethod(limited_generate))
  solver = Ev9PathMpc(build(tmp_path/'exhausted-qp'))
  try:
    result = solver.solve(**dict(request(), initial_curvature=0.))
    assert not result.feasible and result.reason == 'native_status_4'
    assert not len(result.xy)
    config = solver._library.ev9_path_acados_get_nlp_config
    internal_solver = solver._library.ev9_path_acados_get_nlp_solver
    for getter in (config, internal_solver):
      getter.argtypes, getter.restype = [c_void_p], c_void_p
    get = solver._library.ocp_nlp_get
    get.argtypes, get.restype = [c_void_p, c_void_p, c_char_p, c_void_p], None
    iterations = c_int()
    get(config(solver._capsule), internal_solver(solver._capsule), b'sqp_iter', byref(iterations))
    assert iterations.value == 1
  finally:
    solver.close()


@pytest.mark.parametrize('sign', [-1, 1])
def test_linear_corridor_preserves_rotated_translated_trajectory(native, sign):
  args = request(sign)
  original = native.solve(**args)
  assert original.feasible, original.reason
  angle = .8
  rotation = np.array([[math.cos(angle), -math.sin(angle)], [math.sin(angle), math.cos(angle)]])
  offset = np.array([12., -21.])
  rotated = native.solve(**dict(args, reference_xy=args['reference_xy']@rotation.T+offset,
                               reference_yaw=args['reference_yaw']+angle, initial_pose=(*offset, angle)))
  assert rotated.feasible, rotated.reason
  np.testing.assert_allclose(rotated.xy, original.xy@rotation.T+offset, rtol=0., atol=1e-5)
  np.testing.assert_allclose(rotated.curvature, original.curvature, rtol=0., atol=1e-6)
