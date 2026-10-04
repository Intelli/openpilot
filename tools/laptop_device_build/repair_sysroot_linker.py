#!/usr/bin/env python3
"""Make AGNOS loader paths usable by a sysroot linker without host libraries."""
import argparse
import os
from pathlib import Path
import struct


LOADER_PATHS = (
  'usr/lib/aarch64-linux-gnu/ld-linux-aarch64.so.1',
  'lib/aarch64-linux-gnu/ld-linux-aarch64.so.1',
  'lib/ld-linux-aarch64.so.1',
  'usr/lib/ld-linux-aarch64.so.1',
)


def resolve_in_sysroot(root: Path, relative: str) -> tuple[Path, dict[Path, Path]]:
  """Resolve device-absolute links relative to root, never the host filesystem."""
  pending = relative.split('/')
  parts: list[str] = []
  links: dict[Path, Path] = {}
  followed = 0
  while pending:
    part = pending.pop(0)
    if part in ('', '.'):
      continue
    if part == '..':
      if not parts:
        raise ValueError('Loader symlink escapes sysroot')
      parts.pop()
      continue
    path = root.joinpath(*parts, part)
    if path.is_symlink():
      followed += 1
      if followed > 40:
        raise ValueError('Loader symlink cycle in sysroot')
      target = os.readlink(path)
      if target.startswith('/'):
        links[path] = root / target.lstrip('/')
        parts = []
      pending = target.split('/') + pending
    else:
      parts.append(part)
  return root.joinpath(*parts), links


def is_arm64_loader(path: Path) -> bool:
  if not path.is_file():
    return False
  with path.open('rb') as stream:
    header = stream.read(20)
  return len(header) == 20 and header[:6] == b'\x7fELF\x02\x01' and struct.unpack('<H', header[18:20])[0] == 183


def repair_loader(root: Path) -> Path:
  root = root.resolve()
  resolved = []
  absolute_links: dict[Path, Path] = {}
  for relative in LOADER_PATHS:
    path, links = resolve_in_sysroot(root, relative)
    resolved.append(path)
    absolute_links.update(links)
  loader = next((path for path in resolved if is_arm64_loader(path)), None)
  if loader is None:
    raise ValueError(f'Missing ARM64 dynamic loader inside sysroot: {root}')

  # Preserve device targets but make normal file operations stay inside root.
  # This also handles merged-/usr images where /lib itself is an absolute link.
  for link, target in absolute_links.items():
    link.unlink()
    link.symlink_to(os.path.relpath(target, link.parent))

  for relative in LOADER_PATHS:
    alias = root / relative
    parent, _ = resolve_in_sysroot(root, str(Path(relative).parent))
    alias = parent / alias.name
    parent.mkdir(parents=True, exist_ok=True)
    if alias == loader:
      continue
    if alias.is_symlink():
      alias.unlink()
    elif alias.is_dir():
      alias.rmdir()  # Only repair the historical empty-directory extraction bug.
    elif alias.exists():
      if alias.read_bytes() != loader.read_bytes():
        raise ValueError(f'Conflicting dynamic loader inside sysroot: {alias}')
      continue
    alias.symlink_to(os.path.relpath(loader, parent))

  for relative in LOADER_PATHS:
    if not is_arm64_loader(root / relative):
      raise ValueError(f'Unusable dynamic loader path: {root / relative}')
  return loader


if __name__ == '__main__':
  parser = argparse.ArgumentParser(description=__doc__)
  parser.add_argument('sysroot', type=Path)
  args = parser.parse_args()
  try:
    repair_loader(args.sysroot)
  except (OSError, ValueError) as error:
    parser.exit(1, f'ERROR: {error}\n')
