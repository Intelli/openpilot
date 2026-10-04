"""AGNOS loader repair must satisfy linker scripts without resolving host links."""
import importlib.util
import os
from pathlib import Path
import struct
import subprocess
from types import SimpleNamespace

import pytest


ROOT = Path(__file__).resolve().parents[3]
spec = importlib.util.spec_from_file_location('sysroot_loader', ROOT / 'tools/laptop_device_build/repair_sysroot_linker.py')
loader_repair = importlib.util.module_from_spec(spec)
spec.loader.exec_module(loader_repair)


def elf(machine=183):
  header = bytearray(64)
  header[:6] = b'\x7fELF\x02\x01'
  header[18:20] = struct.pack('<H', machine)
  return bytes(header)


def device_loader(root):
  path = root / 'usr/lib/aarch64-linux-gnu/ld-linux-aarch64.so.1'
  path.parent.mkdir(parents=True)
  path.write_bytes(elf())
  return path


def check_loader_paths(root):
  for relative in loader_repair.LOADER_PATHS:
    path = root / relative
    assert path.read_bytes() == elf()
    assert path.resolve().is_relative_to(root)
    if path.is_symlink():
      assert not os.readlink(path).startswith('/')


def test_glibc_conventional_loader_alias_and_shell_repair(tmp_path):
  device_loader(tmp_path)
  # rdump historically left an empty directory where this alias should be.
  (tmp_path / 'lib/aarch64-linux-gnu/ld-linux-aarch64.so.1').mkdir(parents=True)
  subprocess.run(['bash', '-c', 'source "$1"; SYSROOT_DIR="$2"; repair_sysroot_linker',
                  'test', str(ROOT / 'scripts/laptop_device_build.sh'), str(tmp_path)], check=True)
  check_loader_paths(tmp_path)
  before = {p: os.readlink(tmp_path / p) for p in loader_repair.LOADER_PATHS if (tmp_path / p).is_symlink()}
  loader_repair.repair_loader(tmp_path)
  assert before == {p: os.readlink(tmp_path / p) for p in before}


def test_device_absolute_loader_links_resolve_inside_sysroot(tmp_path):
  actual = device_loader(tmp_path)
  (tmp_path / 'lib/aarch64-linux-gnu').mkdir(parents=True)
  (tmp_path / 'lib/aarch64-linux-gnu/ld-linux-aarch64.so.1').symlink_to('/usr/lib/aarch64-linux-gnu/ld-linux-aarch64.so.1')
  (tmp_path / 'lib/ld-linux-aarch64.so.1').symlink_to('/lib/aarch64-linux-gnu/ld-linux-aarch64.so.1')
  assert loader_repair.repair_loader(tmp_path) == actual
  check_loader_paths(tmp_path)


def test_merged_usr_absolute_directory_link_stays_inside_sysroot(tmp_path):
  actual = device_loader(tmp_path)
  (tmp_path / 'lib').symlink_to('/usr/lib')
  assert loader_repair.repair_loader(tmp_path) == actual
  assert os.readlink(tmp_path / 'lib') == 'usr/lib'
  check_loader_paths(tmp_path)


@pytest.mark.parametrize('machine', [None, 62])
def test_missing_or_host_loader_cannot_supply_device_sysroot(tmp_path, machine):
  # Even an absolute target that exists on the host must not be read there.
  (tmp_path / 'lib').mkdir()
  (tmp_path / 'lib/ld-linux-aarch64.so.1').symlink_to('/bin/sh')
  if machine is not None:
    device_loader(tmp_path).write_bytes(elf(machine))
  with pytest.raises(ValueError, match='Missing ARM64 dynamic loader inside sysroot'):
    loader_repair.repair_loader(tmp_path)
  assert os.readlink(tmp_path / 'lib/ld-linux-aarch64.so.1') == '/bin/sh'


def test_loader_symlink_cycle_rejected(tmp_path):
  device_loader(tmp_path)
  (tmp_path / 'lib').mkdir()
  (tmp_path / 'lib/ld-linux-aarch64.so.1').symlink_to('ld-linux-aarch64.so.1')
  with pytest.raises(ValueError, match='symlink cycle'):
    loader_repair.repair_loader(tmp_path)


def test_agnos_extraction_repairs_loader_before_success(tmp_path, monkeypatch):
  builder = ROOT / 'tools/laptop_device_build'
  monkeypatch.syspath_prepend(str(builder))
  extract_spec = importlib.util.spec_from_file_location('test_agnos_extract', builder / 'extract_sysroot_from_agnos.py')
  extractor = importlib.util.module_from_spec(extract_spec)
  extract_spec.loader.exec_module(extractor)
  output = tmp_path / 'sysroot'
  args = SimpleNamespace(manifest='unused.json', output_dir=str(output), cache_dir=str(tmp_path / 'cache'),
                         url='https://example.test/agnos17.img', force_download=False)
  monkeypatch.setattr(extractor, 'parse_args', lambda: args)
  monkeypatch.setattr(extractor.shutil, 'which', lambda _: '/usr/bin/debugfs')
  monkeypatch.setattr(extractor, 'download_and_prepare_image', lambda *args: tmp_path / 'image')
  monkeypatch.setattr(extractor, 'ensure_debugfs_readable_image', lambda path, _: path)
  monkeypatch.setattr(extractor, 'populate_optional_host_includes', lambda _: None)

  def extract(_image, _source, destination):
    destination.mkdir(parents=True, exist_ok=True)
    (destination / 'extracted.txt').write_text('device content')
    if destination == output / 'usr/lib/aarch64-linux-gnu':
      (destination / 'ld-linux-aarch64.so.1').write_bytes(elf())
  monkeypatch.setattr(extractor, 'run_debugfs', extract)
  assert extractor.main() == 0
  check_loader_paths(output)
