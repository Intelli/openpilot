"""Explicit model-camera to rear-axle geometry; no inferred installation defaults.

The calibrated model frame is camera-origin, x-forward/y-right. The optimizer
uses the current rear axle, x-forward/y-left. A moving camera path and a static
road boundary need DIFFERENT transformations. These helpers do not establish
mounting calibration, body clearance, road permission or obstacle absence.
"""
from dataclasses import dataclass

import numpy as np


@dataclass(frozen=True)
class CameraMount:
  """Physical camera position relative to the rear axle, metres, y-left.

  Caller must establish yaw/roll alignment and handle any virtual camera warp
  before using this planar transform. The CameraOffset UI parameter is not a
  measurement of this physical mounting position.
  """
  forward: float
  left: float

  def vector(self):
    value = np.array([self.forward, self.left], dtype=float)
    if not np.isfinite(value).all():
      raise ValueError('invalid_camera_mount')
    return value


def _points(value):
  points = np.asarray(value, dtype=float)
  if points.ndim != 2 or points.shape[1] != 2 or len(points) < 2 or not np.isfinite(points).all():
    raise ValueError('invalid_points')
  return points


def static_model_points_to_rear_axle(points, mount):
  """Static boundary points observed from the current camera; never extrapolate."""
  return _points(points) * [1., -1.] + mount.vector()


def model_path_to_rear_axle(camera_positions, body_yaw_right, mount):
  """Camera motion -> rear-axle motion, using body yaw at each matching instant.

  Positions and yaw must be relative to the CURRENT camera pose/aligned body
  heading, not independently recentered at the first prediction. With positive-
  left yaw, rear(t) = camera(t) + d - R(yaw(t))*d.
  Translating the entire trajectory by d would retain the camera's larger turn
  radius. Path tangent is not body yaw when the camera is ahead of the axle.
  """
  positions = _points(camera_positions) * [1., -1.]
  yaw = -np.asarray(body_yaw_right, dtype=float)
  if yaw.shape != (len(positions),) or not np.isfinite(yaw).all():
    raise ValueError('invalid_matching_body_yaw')
  d = mount.vector()
  c, s = np.cos(yaw), np.sin(yaw)
  rotated = np.column_stack((c * d[0] - s * d[1], s * d[0] + c * d[1]))
  return positions + d - rotated, yaw
