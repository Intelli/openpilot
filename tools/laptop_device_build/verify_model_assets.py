#!/usr/bin/env python3
"""Validate pinned model data without executing or unpickling it."""
import argparse
import hashlib
import json
import pickletools
import re
import shutil
from pathlib import Path


def compiler_digest(root: Path) -> str:
  digest = hashlib.sha256()
  for path in sorted((root / 'tinygrad_repo/tinygrad').rglob('*.py')):
    digest.update(path.relative_to(root).as_posix().encode() + b'\0')
    digest.update(path.read_bytes() + b'\0')
  return digest.hexdigest()


def verify_assets(root: Path, require_qcom: bool = False, install: bool = False, installed: bool = False) -> dict:
  manifest = json.loads((root / 'tools/laptop_device_build/model_assets.json').read_text())
  asset_root = root if installed else root / 'tools/laptop_device_build/model_assets'
  if compiler_digest(root) != manifest['tinygrad_runtime_sha256']:
    raise ValueError('Pinned models do not match the tinygrad runtime/compiler sources')
  for group in ('source_inputs', 'assets'):
    for name, expected in manifest[group].items():
      if group == 'assets':
        allowed_data = re.fullmatch(r'.+\.pkl(?:\.chunk(?:manifest|\d{2}of\d{2}))?', Path(name).name) is not None
        allowed_data = allowed_data or name == 'selfdrive/modeld/models/tg_compiled_flags.json'
        if not allowed_data or not name.startswith(('selfdrive/modeld/models/', 'sunnypilot/modeld_v2/models/')) or '..' in Path(name).parts:
          raise ValueError(f'Unexpected model asset destination: {name}')
      path = (asset_root if group == 'assets' else root) / name
      if not path.is_file() or hashlib.sha256(path.read_bytes()).hexdigest() != expected:
        raise ValueError(f'Missing or modified pinned model input: {name}')

  backend = manifest['backend']
  flags = json.loads((asset_root / 'selfdrive/modeld/models/tg_compiled_flags.json').read_text())
  if flags['DEV'].split()[0] != backend:
    raise ValueError('Model backend flags disagree with the pinned asset manifest')
  for name in manifest['assets']:
    if name.endswith('_tinygrad.pkl'):
      data = (asset_root / name).read_bytes()
    elif name.endswith('_tinygrad.pkl.chunkmanifest'):
      count = int((asset_root / name).read_text())
      stem = name.removesuffix('.chunkmanifest')
      data = b''.join((asset_root / f'{stem}.chunk{i:02d}of{count:02d}').read_bytes() for i in range(1, count + 1))
    else:
      continue
    devices = {arg for _, arg, _ in pickletools.genops(data) if isinstance(arg, str) and arg in ('CPU', 'QCOM', 'CUDA', 'GPU')}
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
