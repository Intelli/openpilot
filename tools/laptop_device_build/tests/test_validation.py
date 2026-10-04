import hashlib
import importlib.util
import json
import pickle
import struct
import sys
from pathlib import Path

import pytest

BUILDER = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(BUILDER))
from verify_build import verify_elf
import verify_build as build_validation
from verify_model_assets import compiler_digest, verify_assets


@pytest.fixture
def model_root(tmp_path):
  runtime = tmp_path / 'tinygrad_repo/tinygrad'
  runtime.mkdir(parents=True)
  (runtime / '__init__.py').write_text('runtime = 1\n')
  asset_root = tmp_path / 'tools/laptop_device_build/model_assets'
  model_dir = asset_root / 'selfdrive/modeld/models'
  model_dir.mkdir(parents=True)
  (model_dir / 'tg_compiled_flags.json').write_text('{"DEV": "QCOM"}')
  (model_dir / 'driving_policy_tinygrad.pkl').write_bytes(pickle.dumps(('QCOM', 42)))
  manifest = {
    'backend': 'QCOM',
    'tinygrad_runtime_sha256': compiler_digest(tmp_path),
    'source_inputs': {},
    'assets': {p.relative_to(asset_root).as_posix(): hashlib.sha256(p.read_bytes()).hexdigest() for p in model_dir.iterdir()},
  }
  manifest_path = tmp_path / 'tools/laptop_device_build/model_assets.json'
  manifest_path.write_text(json.dumps(manifest))
  return tmp_path


def test_install_copies_verified_qcom_data(model_root):
  verify_assets(model_root, require_qcom=True, install=True)
  verify_assets(model_root, require_qcom=True, installed=True)
  assert (model_root / 'selfdrive/modeld/models/driving_policy_tinygrad.pkl').read_bytes() == pickle.dumps(('QCOM', 42))


def test_tampered_capture_fails_before_install(model_root):
  stored = model_root / 'tools/laptop_device_build/model_assets/selfdrive/modeld/models/driving_policy_tinygrad.pkl'
  stored.write_bytes(b'modified')
  with pytest.raises(ValueError, match='Missing or modified'):
    verify_assets(model_root, require_qcom=True, install=True)
  assert not (model_root / 'selfdrive/modeld/models').exists()


def test_changed_compiler_rejects_model_capture(model_root):
  (model_root / 'tinygrad_repo/tinygrad/__init__.py').write_text('runtime = 2\n')
  with pytest.raises(ValueError, match='runtime/compiler'):
    verify_assets(model_root)


def test_relabelled_cpu_capture_is_rejected(model_root):
  stored = model_root / 'tools/laptop_device_build/model_assets/selfdrive/modeld/models/driving_policy_tinygrad.pkl'
  stored.write_bytes(pickle.dumps(('CPU', 42)))
  path = model_root / 'tools/laptop_device_build/model_assets.json'
  manifest = json.loads(path.read_text())
  manifest['assets']['selfdrive/modeld/models/driving_policy_tinygrad.pkl'] = hashlib.sha256(stored.read_bytes()).hexdigest()
  path.write_text(json.dumps(manifest))
  with pytest.raises(ValueError, match='capture backend'):
    verify_assets(model_root, require_qcom=True)


def test_installed_capture_tampering_is_rejected(model_root):
  verify_assets(model_root, install=True)
  (model_root / 'selfdrive/modeld/models/driving_policy_tinygrad.pkl').write_bytes(b'modified')
  with pytest.raises(ValueError, match='Missing or modified'):
    verify_assets(model_root, installed=True)


@pytest.mark.parametrize('machine,valid', [(183, True), (62, False), (40, False)])
def test_runtime_native_artifact_must_be_arm64(tmp_path, machine, valid):
  artifact = tmp_path / 'extension.so'
  artifact.write_bytes(b'\x7fELF\x02\x01' + b'\0' * 12 + struct.pack('<H', machine))
  if valid:
    verify_elf(artifact)
  else:
    with pytest.raises(ValueError, match='ARM64 ELF'):
      verify_elf(artifact)


def test_sysroot_cache_cannot_reuse_other_agnos_image(tmp_path, monkeypatch):
  spec = importlib.util.spec_from_file_location('extract_sysroot', BUILDER / 'extract_sysroot_from_agnos.py')
  extractor = importlib.util.module_from_spec(spec)
  spec.loader.exec_module(extractor)
  downloads = []
  def download(url, destination):
    downloads.append(url)
    destination.write_bytes(url.encode())
  monkeypatch.setattr(extractor, 'download', download)
  old = extractor.download_and_prepare_image('https://example.test/agnos17.img', tmp_path, False)
  new = extractor.download_and_prepare_image('https://example.test/agnos19.img', tmp_path, False)
  assert old != new
  assert old.read_bytes() == b'https://example.test/agnos17.img'
  assert new.read_bytes() == b'https://example.test/agnos19.img'
  assert len(downloads) == 2


def test_missing_bootlog_rejects_device_build(tmp_path, monkeypatch):
  monkeypatch.setattr(build_validation, 'verify_assets', lambda *args, **kwargs: None)
  header = bytearray(64)
  header[:6] = b'\x7fELF\x02\x01'
  header[18:20] = struct.pack('<H', 183)
  for name in build_validation.NATIVE_OUTPUTS:
    if name == 'system/loggerd/bootlog':
      continue
    path = tmp_path / name
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_bytes(header)
  for variant in build_validation.FIRMWARE_OUTPUTS:
    path = tmp_path / f'panda/board/obj/{variant}.bin.signed'
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_bytes(b'\0' * 128)
  with pytest.raises(FileNotFoundError, match='bootlog'):
    build_validation.verify_build(tmp_path)
  (tmp_path / 'system/loggerd/bootlog').write_bytes(header)
  build_validation.verify_build(tmp_path)
