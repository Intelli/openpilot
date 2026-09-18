"""Fixed-size spatial path refinement using generated acados code.

Coordinates are forward x, left y, counterclockwise yaw/curvature. This produces
geometry, never an actuator command. The caller must independently validate the
entire vehicle footprint against observed road bounds before publishing a plan.
"""
from ctypes import CDLL, POINTER, c_double, c_int, c_void_p
from dataclasses import dataclass
from pathlib import Path
import sys
import time

import numpy as np

N = 40


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


class Ev9PathMpc:
  def __init__(self, library_path=None):
    if library_path is None:
      suffix = '.dylib' if sys.platform == 'darwin' else '.so'
      library_path = Path(__file__).with_name('ev9_path_mpc_lib') / f'libev9_path_mpc{suffix}'
    self._library = CDLL(str(library_path))
    self._library.ev9_path_abi_version.restype = c_int
    if self._library.ev9_path_abi_version() != 2:
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
    if np.any(np.diff(arc) <= 1e-6) or not 1 <= arc[-1] <= 100:
      return rejected('invalid_distance')
    yaw = np.unwrap(yaw)
    station = np.linspace(0., arc[-1], N + 1)
    reference = np.column_stack([np.interp(station, arc, v) for v in (*xy.T, yaw, np.gradient(yaw, arc))])
    interpolated = np.array([np.interp(station, arc, v) for v in raw])
    # Enforce the most restrictive physical limit across each complete segment.
    caps, floors = interpolated[1].copy(), interpolated[6].copy()
    rates = interpolated[2] / interpolated[0]
    mask = np.zeros(N + 1, dtype=bool)
    for i in range(N):
      inside = (arc >= station[i]) & (arc <= station[i+1])
      minimum = min(interpolated[1, i], interpolated[1, i+1], np.min(raw[1, inside], initial=np.inf))
      caps[i:i+2] = np.minimum(caps[i:i+2], minimum)
      maximum = max(interpolated[6, i], interpolated[6, i+1], np.max(raw[6, inside], initial=-np.inf))
      floors[i:i+2] = np.maximum(floors[i:i+2], maximum)
      rates[i] = min(rates[i], rates[i+1], np.min(raw[2, inside] / raw[0, inside], initial=np.inf))
      unknown = preserve[inside].any() or preserve[max(0, np.searchsorted(arc, station[i])-1):min(len(arc), np.searchsorted(arc, station[i+1])+1)].any()
      if unknown:
        mask[i:i+2] = True
    if initial_curvature > raw[1, 0] + 1e-6 or initial_curvature < raw[6, 0] - 1e-6:
      return rejected('initial_curvature')
    limits = np.ascontiguousarray(np.column_stack([interpolated[3], interpolated[4], interpolated[5], caps, rates, mask, floors]), dtype=np.float64)
    initial = np.ascontiguousarray(np.r_[pose, initial_curvature], dtype=np.float64)
    states = np.empty((N+1, 4), dtype=np.float64)
    controls = np.empty((N, 2), dtype=np.float64)
    arrays = [reference, limits, initial, states, controls]
    status = self._library.ev9_path_solve(self._capsule, arc[-1], *[v.ctypes.data_as(POINTER(c_double)) for v in arrays])
    if status or not np.isfinite(states).all() or not np.isfinite(controls).all():
      return rejected(f'native_status_{status}')
    if np.any(controls[:, 1] < .7-1e-6) or np.any(controls[:, 1] > 1.3+1e-6):
      return rejected('segment_length_bounds')
    # Reconstruct a dynamically consistent dense path; never interpolate poses
    # independently of the optimized curvature. Exact yaw, Simpson xy integral.
    subdivisions = max(1, int(np.ceil((1.3 * arc[-1] / N) / .05)))
    dense = np.empty((N * subdivisions + 1, 4))
    dense[0] = initial
    j = 0
    distances = [0.]
    for rate, scale in controls:
      step = arc[-1] / N / subdivisions * scale
      for _ in range(subdivisions):
        x, y, psi, k = dense[j]
        middle_yaw = psi + k * step / 2 + rate * step**2 / 8
        end_yaw = psi + k * step + rate * step**2 / 2
        dense[j+1] = (x + step / 6 * (np.cos(psi) + 4*np.cos(middle_yaw) + np.cos(end_yaw)),
                      y + step / 6 * (np.sin(psi) + 4*np.sin(middle_yaw) + np.sin(end_yaw)), end_yaw, k + rate * step)
        j += 1
        distances.append(distances[-1] + step)
    distance = np.array(distances)
    reference_distance = np.linspace(0., arc[-1], len(dense))
    if np.max(np.abs(dense[::subdivisions] - states)) > 1e-4:
      return rejected('dynamics_residual')
    dense_ref = np.column_stack([np.interp(reference_distance, arc, v) for v in (*xy.T, yaw)])
    dense_bounds = np.array([np.interp(reference_distance, arc, v) for v in raw])
    lateral = -np.sin(dense_ref[:, 2]) * (dense[:, 0]-dense_ref[:, 0]) + np.cos(dense_ref[:, 2]) * (dense[:, 1]-dense_ref[:, 1])
    if (np.any(dense[:, 3] > dense_bounds[1] + 1e-6) or np.any(dense[:, 3] < dense_bounds[6] - 1e-6) or
        np.any(np.abs(controls[:, 0]) > rates[:-1] + 1e-6) or
        np.any(lateral < dense_bounds[3] - 1e-5) or np.any(lateral > dense_bounds[4] + 1e-5) or
        np.any(np.abs(dense[:, 2]-dense_ref[:, 2]) > dense_bounds[5] + 1e-5)):
      return rejected('dense_bounds')
    preserved = np.interp(reference_distance, arc, preserve.astype(float)) > 0
    if np.any(np.abs(dense[preserved, :3] - dense_ref[preserved]) > 1e-5):
      return rejected('preserved_pose')
    if (np.any(np.abs(dense[-1, :2] - xy[-1]) > .10001) or abs(dense[-1, 2]-yaw[-1]) > .01001 or
        abs(dense[-1, 3]-reference[-1, 3]) > .00201):
      return rejected('terminal_agreement')
    return PathMpcResult(True, 'candidate_requires_road_validation', dense[:, :2], dense[:, 2], dense[:, 3], distance,
                         time.monotonic()-started, reference_distance)
