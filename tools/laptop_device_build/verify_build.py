#!/usr/bin/env python3
"""Check required Sunnypilot device outputs before setting prebuilt."""
import argparse
import struct
from pathlib import Path

from verify_model_assets import verify_assets


NATIVE_OUTPUTS = (
  'openpilot/common/libparams_c.so',
  'rednose_repo/rednose/helpers/ekf_sym_pyx.so',
  'msgq_repo/msgq/ipc_pyx.so',
  'msgq_repo/msgq/visionipc/visionipc_pyx.so',
  'openpilot/cereal/messaging/bridge',
  'openpilot/selfdrive/pandad/pandad',
  'openpilot/system/camerad/camerad',
  'openpilot/system/loggerd/loggerd',
  'openpilot/system/loggerd/encoderd',
  'openpilot/system/loggerd/bootlog',
  'openpilot/system/loggerd/lib/libavcodec.so.61',
  'openpilot/system/loggerd/lib/libavformat.so.61',
  'openpilot/system/loggerd/lib/libavutil.so.59',
  'openpilot/system/loggerd/lib/libswresample.so.5',
  'openpilot/selfdrive/locationd/models/generated/libcar.so',
  'openpilot/selfdrive/locationd/models/generated/libpose.so',
  'openpilot/sunnypilot/selfdrive/locationd/models/generated/liblive.so',
  'openpilot/sunnypilot/selfdrive/locationd/locationd',
  'openpilot/selfdrive/controls/lib/longitudinal_mpc_lib/c_generated_code/acados_ocp_solver_pyx.so',
  'openpilot/selfdrive/controls/lib/longitudinal_mpc_lib/c_generated_code/libacados_ocp_solver_long.so',
)
FIRMWARE_OUTPUTS = ('panda_h7', 'panda_jungle_h7', 'body_h7')


def verify_elf(path: Path) -> None:
  with path.open('rb') as stream:
    header = stream.read(20)
  if len(header) != 20 or header[:6] != b'\x7fELF\x02\x01' or struct.unpack('<H', header[18:20])[0] != 183:
    raise ValueError(f'Expected ARM64 ELF artifact: {path}')


def verify_build(root: Path) -> None:
  verify_assets(root, require_qcom=True, installed=True)
  for name in NATIVE_OUTPUTS:
    verify_elf(root / name)
  for variant in FIRMWARE_OUTPUTS:
    path = root / f'panda/board/obj/{variant}.bin.signed'
    if not path.is_file() or path.stat().st_size < 128:
      raise ValueError(f'Missing signed firmware: {path}')
  # A release contains real inputs, never unresolved LFS pointers.
  for directory in ('openpilot', 'panda', 'opendbc_repo', 'msgq_repo', 'rednose_repo', 'tinygrad_repo'):
    for path in (root / directory).rglob('*'):
      if path.is_file() and not path.is_symlink():
        with path.open('rb') as stream:
          if stream.read(43).startswith(b'version https://git-lfs.github.com/spec/v1'):
            raise ValueError(f'Unresolved LFS pointer: {path}')


if __name__ == '__main__':
  parser = argparse.ArgumentParser(description=__doc__)
  parser.add_argument('root', type=Path)
  args = parser.parse_args()
  try:
    verify_build(args.root)
  except (OSError, ValueError, KeyError) as exc:
    parser.exit(1, f'{exc}\n')
  print('Verified native ARM64 application outputs, signed panda firmware and pinned QCOM model data')
