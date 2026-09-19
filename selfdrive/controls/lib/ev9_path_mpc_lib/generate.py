"""Build-time fixed-size EV9 spatial OCP; never imported by controls.

Host research build: python -m openpilot.selfdrive.controls.lib.ev9_path_mpc_lib.generate --output /private/tmp/ev9-path-mpc/build
"""
import argparse
import codecs
import os
from pathlib import Path
import platform
import subprocess
import sys

import numpy as np

N = 30  # Keep the full forecast; independent dense validation retains its spacing.


def generate(output, arch=None):
  from casadi import SX, vertcat, cos, sin

  root = Path(__file__).resolve().parents[4]
  acados = root / 'third_party/acados'
  arch = arch or ('Darwin' if platform.system() == 'Darwin' else platform.machine())
  if arch not in ('Darwin', 'aarch64', 'larch64', 'x86_64'):
    raise ValueError('unsupported acados architecture')
  os.environ['ACADOS_SOURCE_DIR'] = str(acados)
  os.environ['ACADOS_PYTHON_INTERFACE_PATH'] = str(acados / 'acados_template')
  os.environ['TERA_PATH'] = str(acados / arch / 't_renderer')
  # Vendored templates retain this Python 3.5 codec declaration; supported Python has native f-strings.
  codecs.register(lambda name: codecs.lookup('utf-8') if name == 'future_fstrings' else None)
  sys.path.insert(0, str(acados))
  from acados_template import AcadosOcp, AcadosModel, AcadosOcpSolver

  output = Path(output).resolve()
  output.mkdir(parents=True, exist_ok=True)
  ocp = AcadosOcp()
  model = AcadosModel()
  model.name = 'ev9_path'
  model.x = SX.sym('state', 4)
  model.u = SX.sym('control', 2)
  model.p = SX.sym('road', 4)
  model.xdot = SX.sym('state_derivative', 4)
  x, y, yaw, curvature = (model.x[i] for i in range(4))
  length, ref_x, ref_y, ref_yaw = (model.p[i] for i in range(4))
  model.f_expl_expr = length * model.u[1] * vertcat(cos(yaw), sin(yaw), curvature, model.u[0])
  model.f_impl_expr = model.xdot - model.f_expl_expr
  model.cost_y_expr = vertcat(model.x, model.u)
  model.cost_y_expr_e = model.x
  model.con_h_expr = -sin(ref_yaw) * (x - ref_x) + cos(ref_yaw) * (y - ref_y)
  model.con_h_expr_e = model.con_h_expr
  ocp.model = model
  ocp.dims.N = N
  ocp.parameter_values = np.array([40., 0., 0., 0.])
  ocp.cost.cost_type = ocp.cost.cost_type_e = 'NONLINEAR_LS'
  ocp.cost.W = np.diag([1., 1., 20., 1., 20., .1])
  ocp.cost.W_e = np.diag([100., 100., 100., 10.])
  ocp.cost.yref = np.zeros(6)
  ocp.cost.yref_e = np.zeros(4)
  ocp.constraints.x0 = np.zeros(4)
  ocp.constraints.idxbx = np.arange(4)
  ocp.constraints.lbx = np.array([-1e6, -1e6, -4., -.05])
  ocp.constraints.ubx = -ocp.constraints.lbx
  ocp.constraints.idxbu = np.array([0, 1])
  ocp.constraints.lbu = np.array([-.02, .7])
  ocp.constraints.ubu = np.array([.02, 1.3])
  ocp.constraints.lh = ocp.constraints.lh_e = np.array([-1.])
  ocp.constraints.uh = ocp.constraints.uh_e = np.array([1.])
  ocp.constraints.idxbx_e = np.arange(4)
  ocp.constraints.lbx_e = np.array([-100., -100., -4., -.05])
  ocp.constraints.ubx_e = -ocp.constraints.lbx_e
  options = ocp.solver_options
  options.tf = 1.
  options.qp_solver = 'PARTIAL_CONDENSING_HPIPM'
  options.qp_solver_cond_N = 10
  options.hessian_approx = 'GAUSS_NEWTON'
  options.integrator_type = 'ERK'
  options.sim_method_num_steps = 3  # At least the physical integration resolution of the former 40-node/two-step mesh.
  options.nlp_solver_type = 'SQP'
  options.nlp_solver_max_iter = 8  # Independently validate integrated candidates even at the iteration limit.
  options.qp_solver_iter_max = 50
  ocp.code_export_directory = str(output)
  ocp.acados_lib_path = str(acados / arch / 'lib')
  ocp.acados_include_path = str(acados / 'include')
  AcadosOcpSolver.generate(ocp, json_file=str(output / 'acados_ocp.json'))
  return acados, arch


def build(output):
  output = Path(output).resolve()
  acados, arch = generate(output)
  sources = sorted(str(p) for p in output.rglob('*.c') if not p.name.startswith(('main_', 'acados_sim_')))
  library = 'libev9_path_mpc.dylib' if arch == 'Darwin' else 'libev9_path_mpc.so'
  includes = [acados / 'include', acados / 'include/acados', acados / 'include/blasfeo/include', acados / 'include/hpipm/include', output]
  compiler = os.environ.get('CC', '/usr/bin/clang' if arch == 'Darwin' else 'cc')
  command = [compiler, '-O2', '-fPIC', '-shared', '-std=c99', *[f'-I{p}' for p in includes], *sources,
             str(Path(__file__).with_name('wrapper.c')), f'-L{acados / arch / "lib"}', '-lacados', '-lhpipm', '-lblasfeo', '-lm',
             f'-Wl,-rpath,{acados / arch / "lib"}', '-o', str(output / library)]
  subprocess.run(command, check=True)
  return output / library


if __name__ == '__main__':
  parser = argparse.ArgumentParser(description=__doc__)
  parser.add_argument('--output', required=True)
  parser.add_argument('--generate-only', action='store_true')
  parser.add_argument('--arch', choices=('Darwin', 'aarch64', 'larch64', 'x86_64'))
  args = parser.parse_args()
  if args.generate_only:
    generate(args.output, args.arch)
  else:
    print(build(args.output))
