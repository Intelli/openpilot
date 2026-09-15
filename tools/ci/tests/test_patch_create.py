"""Patch export must use the staged index without altering it or source files."""
import os
from pathlib import Path
import shutil
import subprocess

import pytest


ROOT = Path(__file__).resolve().parents[3]


@pytest.fixture
def repo(tmp_path):
  for name in ("create_patch.sh", "create_patch_manual.sh", "update_patch.sh"):
    shutil.copy2(ROOT / name, tmp_path / name)
  shutil.copytree(ROOT / "tools/patches", tmp_path / "tools/patches")
  env = dict(os.environ, GIT_CONFIG_GLOBAL=str(tmp_path / "gitconfig"), GIT_CONFIG_NOSYSTEM="1", GIT_ALLOW_PROTOCOL="file")

  def command(*args, check=True):
    return subprocess.run(args, cwd=tmp_path, env=env, check=check, capture_output=True)

  def git(*args):
    return command("git", *args).stdout

  git("init", "--initial-branch=main")
  git("config", "user.name", "Test")
  git("config", "user.email", "test@example.invalid")
  (tmp_path / "app.txt").write_text("original\n")
  (tmp_path / "opendbc_repo/opendbc/car").mkdir(parents=True)
  (tmp_path / "opendbc_repo/opendbc/car/example.py").write_text("original\n")
  git("add", ".")
  git("commit", "-m", "baseline")

  def stage(path="app.txt", content="staged\n"):
    (tmp_path / path).write_text(content)
    git("add", path)

  def export(script, *args, success=True):
    index = (tmp_path / ".git/index").read_bytes()
    tracked = git("diff", "--binary")
    result = command("bash", script, *args, check=False)
    assert (result.returncode == 0) == success, result.stdout.decode() + result.stderr.decode()
    assert (tmp_path / ".git/index").read_bytes() == index
    assert git("diff", "--binary") == tracked
    return result

  return tmp_path, git, stage, export


def test_create_exports_staged_content_only(repo):
  path, _, stage, export = repo
  stage()
  (path / "app.txt").write_text("unstaged\n")
  export("create_patch.sh", "example")
  patch = (path / "patches/example.patch").read_text()
  assert "+staged" in patch and "+unstaged" not in patch


def test_update_explicit_base_keeps_committed_and_staged_hunks(repo):
  path, git, stage, export = repo
  base = git("rev-parse", "HEAD").decode().strip()
  stage(content="committed\n")
  git("commit", "-m", "first customization")
  (path / "patches").mkdir()
  (path / "patches/example.patch.temp-disabled").write_bytes(git("diff", base, "HEAD", "--", "app.txt"))
  stage("opendbc_repo/opendbc/car/example.py", "second staged change\n")
  export("update_patch.sh", "example", "--base", base)
  patch = (path / "patches/example.patch.temp-disabled").read_text()
  assert "+committed" in patch and "+second staged change" in patch
  assert not (path / "patches/example.patch").exists()


@pytest.mark.parametrize("case", ["missing_base", "invalid_base", "no_staged", "empty_selection"])
def test_failed_update_preserves_existing_patch(repo, case):
  path, _, stage, export = repo
  (path / "patches").mkdir()
  target = path / "patches/example.patch.disabled"
  target.write_bytes(b"original patch bytes\n")
  if case != "no_staged":
    stage()
  args = [] if case == "missing_base" else ["--base", "not-a-ref" if case == "invalid_base" else "HEAD"]
  if case == "empty_selection":
    args += ["--", "opendbc_repo/opendbc/car/example.py"]
  export("update_patch.sh", "example", *args, success=False)
  assert target.read_bytes() == b"original patch bytes\n"


@pytest.mark.parametrize("suffix", [".patch", ".patch.disabled", ".patch.temp-disabled", ".patch.OUTDATED.disabled"])
def test_update_resolves_suffix_and_create_refuses_collision(repo, suffix):
  path, _, stage, export = repo
  (path / "patches").mkdir()
  target = path / f"patches/example{suffix}"
  target.write_text("old")
  stage()
  export("create_patch.sh", "example", success=False)
  assert target.read_text() == "old"
  export("update_patch.sh", "example", "--base", "HEAD")
  assert "+staged" in target.read_text()
  assert len(list((path / "patches").iterdir())) == 1


def test_update_rejects_ambiguous_name(repo):
  path, _, stage, export = repo
  (path / "patches").mkdir()
  for suffix in (".patch", ".patch.disabled"):
    (path / f"patches/example{suffix}").write_text("old")
  stage()
  export("update_patch.sh", "example", "--base", "HEAD", success=False)
  assert all(p.read_text() == "old" for p in (path / "patches").iterdir())


def test_vehicle_binary_patch_uses_standalone_paths_and_roundtrips(repo):
  path, git, stage, export = repo
  payload = bytes(range(256)) * 3
  binary = path / "opendbc_repo/opendbc/car/new.bin"
  binary.write_bytes(payload)
  git("add", "opendbc_repo/opendbc/car/new.bin")
  stage()
  export("create_patch.sh", "opendbc/example", "--", "opendbc/car/new.bin")
  patch = path / "patches/opendbc/example.patch"
  assert b"GIT binary patch" in patch.read_bytes()
  assert b"a/app.txt" not in patch.read_bytes()
  assert b"opendbc_repo/" not in patch.read_bytes()
  standalone = path / "standalone"
  standalone.mkdir()
  subprocess.run(["git", "init", str(standalone)], check=True, capture_output=True)
  result = subprocess.run(["git", "apply", str(patch)], cwd=standalone, capture_output=True)
  assert result.returncode == 0, result.stderr
  assert (standalone / "opendbc/car/new.bin").read_bytes() == payload


def test_manual_alias_filters_paths_and_excludes_maintenance(repo):
  path, git, stage, export = repo
  stage()
  stage("opendbc_repo/opendbc/car/example.py", "vehicle edit\n")
  (path / "patches").mkdir()
  (path / "patches/metadata.patch.disabled").write_text("metadata")
  git("add", "patches")
  export("create_patch_manual.sh", "example", "--", "app.txt", "patches")
  patch = (path / "patches/example.patch").read_text()
  assert "+staged" in patch
  assert "metadata" not in patch and "vehicle edit" not in patch


@pytest.mark.parametrize("name", ["../escape", "/tmp/escape", "opendbc/../../escape"])
def test_rejects_name_traversal(repo, name):
  _, _, stage, export = repo
  stage()
  export("create_patch.sh", name, success=False)


def test_rejects_patch_directory_symlink_escape(repo):
  path, _, stage, export = repo
  outside = path.parent / f"{path.name}-outside"
  outside.mkdir()
  (path / "patches").symlink_to(outside, target_is_directory=True)
  stage()
  export("create_patch.sh", "example", success=False)
  assert not list(outside.iterdir())


def test_export_preserves_deletion_and_executable_mode(repo):
  path, git, _, export = repo
  (path / "app.txt").unlink()
  git("add", "app.txt")
  script = path / "new-script.sh"
  script.write_text("#!/bin/sh\necho example\n")
  script.chmod(0o755)
  git("add", "new-script.sh")
  export("create_patch.sh", "example")
  patch = (path / "patches/example.patch").read_text()
  assert "deleted file mode 100644" in patch
  assert "new file mode 100755" in patch
