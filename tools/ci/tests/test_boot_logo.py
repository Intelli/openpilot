"""Boot artwork installation is idempotent and restores a remounted root on failure."""
import builtins
import importlib.util
from io import BytesIO
from pathlib import Path
import shutil
import subprocess

from PIL import Image
import pytest


ROOT = Path(__file__).resolve().parents[3]
spec = importlib.util.spec_from_file_location("ev9_boot_logo", ROOT / "openpilot/sunnypilot/system/boot_logo.py")
boot_logo = importlib.util.module_from_spec(spec)
spec.loader.exec_module(boot_logo)


def test_logo_orientation_matches_magic_and_weston():
  for landscape_jpeg in (False, True):
    images = boot_logo.logo_images(boot_logo.ARTWORK, landscape_jpeg)
    with Image.open(BytesIO(images["bg.jpg"])) as jpeg, Image.open(BytesIO(images["bg.png"])) as png:
      assert (jpeg.width >= jpeg.height) == landscape_jpeg
      assert png.width >= png.height


@pytest.mark.parametrize("copy_fails", [False, True])
def test_install_restores_mount_and_skips_matching_artwork(tmp_path, monkeypatch, copy_fails):
  (tmp_path / "bg.png").write_bytes(b"old png")
  (tmp_path / "magic.py").write_text("'/usr/comma/bg.jpg'")
  monkeypatch.setattr(boot_logo.subprocess, "check_output", lambda *args, **kwargs: "ro,relatime\n")
  commands = []

  def run(command, **kwargs):
    commands.append(command)
    if command[1] == "cp":
      if copy_fails:
        raise subprocess.CalledProcessError(1, command)
      shutil.copyfile(command[2], command[3])

  monkeypatch.setattr(boot_logo.subprocess, "run", run)
  assert boot_logo.install_boot_logo(tmp_path) == (not copy_fails)
  assert commands[-1] == ["sudo", "mount", "-o", "remount,ro,relatime", "/"]
  if not copy_fails:
    commands.clear()
    assert boot_logo.install_boot_logo(tmp_path)
    assert commands == []


def test_missing_image_library_does_not_stop_manager(tmp_path, monkeypatch):
  original_import = builtins.__import__

  def without_pillow(name, *args, **kwargs):
    if name == "PIL":
      raise ImportError("Pillow is unavailable")
    return original_import(name, *args, **kwargs)

  monkeypatch.setattr(builtins, "__import__", without_pillow)
  spec.loader.exec_module(boot_logo)
  assert not boot_logo.install_boot_logo(tmp_path)
