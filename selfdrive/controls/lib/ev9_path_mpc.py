"""Fixed-size spatial path refinement using generated acados code.

Coordinates are forward x, left y, counterclockwise yaw/curvature. This produces
geometry, never an actuator command. The caller validates path displacement and
the vehicle footprint against applicable reliable observations before publication.
"""
from ctypes import CDLL, POINTER, c_double, c_int, c_void_p
from dataclasses import dataclass
from pathlib import Path
import sys
import time

import numpy as np

from openpilot.selfdrive.controls.lib.ev9_trajectory import MAX_SAMPLES

N = 30  # Preserve the complete forecast with fewer optimization intervals.
ACADOS_SUCCESS = 0
ACADOS_MAXITER = 2
DENSE_SPACING = .05


@dataclass(frozen=True)
class PathMpcResult:
  feasible: bool
  reason: str
  xy: np.ndarray
  yaw: np.ndarray
  curvature: np.ndarray
  distance: np.ndarray
  solve_time: float
  reference_distance: np.ndarray


def _integrate_controls(initial, controls, length, subdivisions):
  """Independently integrate linear curvature with the existing Simpson rule."""
  rate = np.repeat(controls[:, 0], subdivisions)
  step = np.repeat(controls[:, 1] * length / N / subdivisions, subdivisions)
  curvature = initial[3] + np.r_[0., np.cumsum(rate * step)]
  yaw = initial[2] + np.r_[0., np.cumsum(curvature[:-1] * step + rate * step**2 / 2)]
  middle_yaw = yaw[:-1] + curvature[:-1] * step / 2 + rate * step**2 / 8
  x = initial[0] + np.r_[0., np.cumsum(step / 6 * (np.cos(yaw[:-1]) + 4*np.cos(middle_yaw) + np.cos(yaw[1:])))]
  y = initial[1] + np.r_[0., np.cumsum(step / 6 * (np.sin(yaw[:-1]) + 4*np.sin(middle_yaw) + np.sin(yaw[1:])))]
  return np.column_stack((x, y, yaw, curvature)), np.r_[0., np.cumsum(step)]


class Ev9PathMpc:
  def __init__(self, library_path=None):
    if library_path is None:
      suffix = '.dylib' if sys.platform == 'darwin' else '.so'
      library_path = Path(__file__).with_name('ev9_path_mpc_lib') / f'libev9_path_mpc{suffix}'
    self._library = CDLL(str(library_path))
    self._library.ev9_path_abi_version.restype = c_int
    if self._library.ev9_path_abi_version() != 6:
      raise RuntimeError('EV9 path MPC ABI mismatch')
    self._library.ev9_path_create.restype = c_void_p
    self._library.ev9_path_destroy.argtypes = [c_void_p]
    self._library.ev9_path_solve.argtypes = [c_void_p, c_double, *[POINTER(c_double)] * 5]
    self._library.ev9_path_solve.restype = c_int
    self._capsule = self._library.ev9_path_create()
    if not self._capsule:
      raise RuntimeError('EV9 path MPC allocation failed')

  def close(self):
    if self._capsule:
      self._library.ev9_path_destroy(self._capsule)
      self._capsule = None

  def __del__(self):
    if getattr(self, '_capsule', None):
      self.close()

  def solve(self, reference_xy, reference_yaw, initial_pose, initial_curvature, speeds, curvature_limit, curvature_rate_time,
            lateral_lower, lateral_upper, heading_deviation, preserve_reference=None, min_curvature=None):
    """Bounds are scalars or arrays matching reference points; rate is |dk/dt|.

    min_curvature defaults to -curvature_limit; asymmetric bounds and zero
    direction bounds are supported. Physical limits must be mapped from ±140-degree
    steering authority by the caller's vehicle model at each speed. A preserve
    mask fixes x/y/yaw, not merely lateral deviation. No graph building or warm
    startup is done here; every request resets the native solver state.
    """
    started = time.monotonic()

    def rejected(reason):
      return PathMpcResult(False, reason, np.empty((0, 2)), np.empty(0), np.empty(0), np.empty(0), time.monotonic() - started, np.empty(0))

    if not self._capsule:
      return rejected('closed')
    if np.asarray(initial_curvature).ndim != 0:
      return rejected('initial_curvature_shape')
    xy = np.asarray(reference_xy, dtype=float)
    yaw = np.asarray(reference_yaw, dtype=float)
    pose = np.asarray(initial_pose, dtype=float)
    if xy.ndim != 2 or xy.shape[1] != 2 or not 3 <= len(xy) <= 2048 or yaw.shape != (len(xy),) or pose.shape != (3,):
      return rejected('input_shape')
    try:
      raw = np.array([np.broadcast_to(v, (len(xy),)) for v in
                      (speeds, curvature_limit, curvature_rate_time, lateral_lower, lateral_upper, heading_deviation,
                       -np.asarray(curvature_limit) if min_curvature is None else min_curvature)])
      preserve = np.zeros(len(xy), dtype=bool) if preserve_reference is None else np.broadcast_to(preserve_reference, (len(xy),)).astype(bool)
    except ValueError:
      return rejected('bound_shape')
    if not all(np.isfinite(v).all() for v in (xy, yaw, pose, raw, np.asarray(initial_curvature))):
      return rejected('nonfinite')
    if np.any(raw[[0, 2]] <= 0) or np.any(raw[6] >= raw[1]) or np.any(raw[3] > raw[4]) or np.any(raw[5] < 0):
      return rejected('invalid_bounds')
    arc = np.r_[0., np.cumsum(np.linalg.norm(np.diff(xy, axis=0), axis=1))]
    if not np.isfinite(arc).all() or np.any(np.diff(arc) <= 1e-6) or arc[-1] < 1:
      return rejected('invalid_distance')
    # Capacity follows the published dense-plan contract, not an arbitrary
    # 100 m horizon cutoff. Keep the complete supplied forecast, never trim it
    # simply to avoid an inconvenient bend or boundary.
    if arc[-1] > ((MAX_SAMPLES - 1) // N) * N * DENSE_SPACING / 1.3:
      return rejected('path_capacity')
    subdivisions = max(1, int(np.ceil((1.3 * arc[-1] / N) / DENSE_SPACING)))
    yaw = np.unwrap(yaw)
    station = np.linspace(0., arc[-1], N + 1)
    reference = np.column_stack([np.interp(station, arc, v) for v in (*xy.T, yaw, np.gradient(yaw, arc))])
    interpolated = np.array([np.interp(station, arc, v) for v in raw])
    # Enforce each segment's most restrictive endpoint or interior raw bound,
    # then share it with both neighboring nodes. No narrow bound is skipped.
    inside = (arc[None, :] >= station[:-1, None]) & (arc[None, :] <= station[1:, None])
    caps = np.minimum(np.minimum(interpolated[1, :-1], interpolated[1, 1:]), np.min(np.where(inside, raw[1], np.inf), axis=1))
    floors = np.maximum(np.maximum(interpolated[6, :-1], interpolated[6, 1:]), np.max(np.where(inside, raw[6], -np.inf), axis=1))
    rates = np.minimum(np.minimum(interpolated[2, :-1]/interpolated[0, :-1], interpolated[2, 1:]/interpolated[0, 1:]),
                       np.min(np.where(inside, raw[2]/raw[0], np.inf), axis=1))
    caps = np.minimum(np.r_[interpolated[1, 0], caps], np.r_[caps, interpolated[1, -1]])
    floors = np.maximum(np.r_[interpolated[6, 0], floors], np.r_[floors, interpolated[6, -1]])
    rates = np.r_[rates, interpolated[2, -1]/interpolated[0, -1]]
    # Preserve intervals include their bracketing raw samples, not only points
    # falling inside a solver stage. Prefix counts avoid repeated tiny slices.
    prefix = np.r_[0, np.cumsum(preserve)]
    starts = np.maximum(0, np.searchsorted(arc, station[:-1])-1)
    ends = np.minimum(len(arc), np.searchsorted(arc, station[1:])+1)
    unknown = prefix[ends] > prefix[starts]
    mask = np.r_[False, unknown] | np.r_[unknown, False]
    if initial_curvature > raw[1, 0] + 1e-6 or initial_curvature < raw[6, 0] - 1e-6:
      return rejected('initial_curvature')
    # Stage zero fixes the measured state. Its simultaneous path constraints
    # must agree before we ask the QP to solve; adding iterations cannot resolve
    # an initial pose outside a zero-width (unobserved) reference corridor.
    initial_lateral = -np.sin(yaw[0]) * (pose[0] - xy[0, 0]) + np.cos(yaw[0]) * (pose[1] - xy[0, 1])
    if initial_lateral < raw[3, 0] - 1e-5 or initial_lateral > raw[4, 0] + 1e-5:
      return rejected('initial_lateral_bounds')
    if abs(pose[2] - yaw[0]) > raw[5, 0] + 1e-5:
      return rejected('initial_heading_bounds')
    if preserve[0] and np.any(abs(pose - np.r_[xy[0], yaw[0]]) > 1e-5):
      return rejected('initial_unobserved_pose')
    # The forecast endpoint is a preference, not a mandatory pose/curvature.
    # It may still be inside a turn that requires more than physical authority.
    # Keep its curvature target achievable; the same hard capability and path
    # bounds apply at every node, including the endpoint.
    reference[-1, 3] = np.clip(reference[-1, 3], floors[-1], caps[-1])
    limits = np.ascontiguousarray(np.column_stack([interpolated[3], interpolated[4], interpolated[5], caps, rates, mask, floors]), dtype=np.float64)
    initial = np.ascontiguousarray(np.r_[pose, initial_curvature], dtype=np.float64)
    states = np.empty((N+1, 4), dtype=np.float64)
    controls = np.empty((N, 2), dtype=np.float64)
    arrays = [reference, limits, initial, states, controls]
    status = self._library.ev9_path_solve(self._capsule, arc[-1], *[v.ctypes.data_as(POINTER(c_double)) for v in arrays])
    if status not in (ACADOS_SUCCESS, ACADOS_MAXITER) or not np.isfinite(states).all() or not np.isfinite(controls).all():
      return rejected(f'native_status_{status}')
    if np.any(controls[:, 1] < .7-1e-6) or np.any(controls[:, 1] > 1.3+1e-6):
      return rejected('segment_length_bounds')
    # Reconstruct a dynamically consistent dense path; never interpolate poses
    # independently of the optimized curvature. Exact yaw, Simpson xy integral.
    dense, distance = _integrate_controls(initial, controls, arc[-1], subdivisions)
    reference_distance = np.linspace(0., arc[-1], len(dense))
    # Converged solver nodes must agree with independent integration. At the
    # iteration limit, internal nodes may not have converged; only the integrated
    # trajectory is considered, subject to every physical/path check below and
    # the caller's displacement, footprint, intent and freshness checks.
    if status == ACADOS_SUCCESS and np.max(np.abs(dense[::subdivisions] - states)) > 1e-4:
      return rejected('dynamics_residual')
    dense_ref = np.column_stack([np.interp(reference_distance, arc, v) for v in (*xy.T, yaw)])
    # Constant bounds broadcast exactly; avoid dense arrays for scalar limits.
    dense_bounds = tuple(v[0] if np.all(v == v[0]) else np.interp(reference_distance, arc, v) for v in raw)
    lateral = -np.sin(dense_ref[:, 2]) * (dense[:, 0]-dense_ref[:, 0]) + np.cos(dense_ref[:, 2]) * (dense[:, 1]-dense_ref[:, 1])
    # Curvature and its reference-distance bounds are piecewise linear. Check
    # their combined breakpoints so a narrow bound cannot fall between samples.
    check_station = np.union1d(arc, station)
    check_curvature = np.interp(check_station, station, dense[::subdivisions, 3])
    if (np.any(check_curvature > np.interp(check_station, arc, raw[1]) + 1e-6) or
        np.any(check_curvature < np.interp(check_station, arc, raw[6]) - 1e-6) or
        np.any(dense[:, 3] > dense_bounds[1] + 1e-6) or np.any(dense[:, 3] < dense_bounds[6] - 1e-6) or
        np.any(np.abs(controls[:, 0]) > rates[:-1] + 1e-6) or
        np.any(lateral < dense_bounds[3] - 1e-5) or np.any(lateral > dense_bounds[4] + 1e-5) or
        np.any(np.abs(dense[:, 2]-dense_ref[:, 2]) > dense_bounds[5] + 1e-5)):
      return rejected('dense_bounds')
    if preserve.any():
      preserved = np.interp(reference_distance, arc, preserve.astype(float)) > 0
      if np.any(np.abs(dense[preserved, :3] - dense_ref[preserved]) > 1e-5):
        return rejected('preserved_pose')
    reason = 'candidate_requires_road_validation' if status == ACADOS_SUCCESS else 'iteration_limit_candidate_requires_road_validation'
    return PathMpcResult(True, reason, dense[:, :2], dense[:, 2], dense[:, 3], distance,
                         time.monotonic()-started, reference_distance)
