#!/usr/bin/env python3
"""Validate pinned model data without executing or unpickling it."""
import argparse
import hashlib
import json
import pickletools
import re
import shutil
import struct
from pathlib import Path


def compiler_digest(root: Path) -> str:
  digest = hashlib.sha256()
  for path in sorted((root / 'tinygrad_repo/tinygrad').rglob('*.py')):
    digest.update(path.relative_to(root).as_posix().encode() + b'\0')
    digest.update(path.read_bytes() + b'\0')
  return digest.hexdigest()


def capture_devices(data: bytes, serialization: str) -> set[str]:
  """Inspect pickle opcodes and OOB framing without importing or executing captures."""
  if serialization == 'oob':
    if len(data) < 8:
      raise ValueError('Truncated out-of-band model capture')
    opcode_size = struct.unpack('<q', data[:8])[0]
    if not 0 < opcode_size <= min(16 * 1024 * 1024, len(data) - 8):
      raise ValueError('Invalid out-of-band model opcode length')
    opcodes = data[8:8 + opcode_size]
    offset = 8 + opcode_size
    buffers = 0
    while offset < len(data):
      if len(data) - offset < 8:
        raise ValueError('Truncated out-of-band model buffer length')
      size = struct.unpack('<q', data[offset:offset + 8])[0]
      offset += 8
      if size < 0 or size > len(data) - offset:
        raise ValueError('Invalid out-of-band model buffer length')
      offset += size
      buffers += 1
  elif serialization == 'pickle':
    opcodes = data
    buffers = 0
  else:
    raise ValueError(f'Unknown model serialization: {serialization}')
  operations = list(pickletools.genops(opcodes))
  if not operations or operations[-1][0].name != 'STOP' or operations[-1][2] + 1 != len(opcodes):
    raise ValueError('Trailing data in model pickle opcodes')
  if sum(op.name == 'NEXT_BUFFER' for op, _, _ in operations) != buffers:
    raise ValueError('Out-of-band model buffer count differs from pickle opcodes')
  return {arg for _, arg, _ in operations if isinstance(arg, str) and arg in ('CPU', 'QCOM', 'CUDA', 'GPU')}


def verify_assets(root: Path, require_qcom: bool = False, install: bool = False, installed: bool = False) -> dict:
  manifest = json.loads((root / 'tools/laptop_device_build/model_assets.json').read_text())
  asset_root = root if installed else root / 'tools/laptop_device_build/model_assets'
  if compiler_digest(root) != manifest['tinygrad_runtime_sha256']:
    raise ValueError('Pinned models do not match the tinygrad runtime/compiler sources')
  for group in ('source_inputs', 'assets'):
    for name, expected in manifest[group].items():
      if group == 'assets':
        allowed_data = re.fullmatch(r'.+\.pkl(?:\.chunk(?:manifest|\d{2}of\d{2}))?', Path(name).name) is not None
        allowed_data = allowed_data or name == 'openpilot/selfdrive/modeld/models/tg_input_devices.json'
        if not allowed_data or not name.startswith('openpilot/selfdrive/modeld/models/') or '..' in Path(name).parts:
          raise ValueError(f'Unexpected model asset destination: {name}')
      path = (asset_root if group == 'assets' else root) / name
      if not path.is_file() or hashlib.sha256(path.read_bytes()).hexdigest() != expected:
        raise ValueError(f'Missing or modified pinned model input: {name}')

  backend = manifest['backend']
  devices = json.loads((asset_root / 'openpilot/selfdrive/modeld/models/tg_input_devices.json').read_text())
  if devices['openpilot.selfdrive.modeld.dmonitoringmodeld']['default']['DEV'] != backend:
    raise ValueError('Model backend flags disagree with the pinned asset manifest')
  for name in manifest['assets']:
    if name.endswith('_tinygrad.pkl'):
      data = (asset_root / name).read_bytes()
      stem = name
    elif name.endswith('_tinygrad.pkl.chunkmanifest'):
      count = int((asset_root / name).read_text())
      if not 0 < count <= 32:
        raise ValueError(f'Invalid model chunk count: {name}')
      stem = name.removesuffix('.chunkmanifest')
      data = b''.join((asset_root / f'{stem}.chunk{i:02d}of{count:02d}').read_bytes() for i in range(1, count + 1))
    else:
      continue
    if stem in manifest.get('capture_sha256', {}) and hashlib.sha256(data).hexdigest() != manifest['capture_sha256'][stem]:
      raise ValueError(f'Combined model capture differs from the pinned catalog: {stem}')
    devices = capture_devices(data, manifest['formats'][stem])
    if devices != {backend}:
      raise ValueError(f'Model capture backend differs from manifest: {name}: {devices}')
  if require_qcom and backend != 'QCOM':
    raise ValueError('Pinned prior Sunnypilot assets contain CPU kernels. Device CI requires a compatible QCOM bundle; publication is blocked.')
  if install:
    for name in manifest['assets']:
      destination = root / name
      destination.parent.mkdir(parents=True, exist_ok=True)
      shutil.copyfile(asset_root / name, destination)
  return manifest


if __name__ == '__main__':
  parser = argparse.ArgumentParser(description=__doc__)
  parser.add_argument('--require-qcom', action='store_true')
  parser.add_argument('--install', action='store_true', help='Copy verified model data into application model directories')
  parser.add_argument('--installed', action='store_true', help='Verify the installed application copies instead of the preserved bundle')
  args = parser.parse_args()
  root = Path(__file__).resolve().parents[2]
  try:
    manifest = verify_assets(root, args.require_qcom, args.install, args.installed)
  except (ValueError, OSError, KeyError) as exc:
    parser.exit(1, f'{exc}\n')
  print(f"Verified {len(manifest['assets'])} model assets; backend={manifest['backend']}; donor={manifest['donor_commit']}")
