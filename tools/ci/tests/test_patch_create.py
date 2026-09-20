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
    # The patch output may itself be tracked; only application/tool source must stay unchanged.
    tracked = git("diff", "--binary", "--", ".", ":(exclude)patches")
    result = command("bash", script, *args, check=False)
    assert (result.returncode == 0) == success, result.stdout.decode() + result.stderr.decode()
    assert (tmp_path / ".git/index").read_bytes() == index
    assert git("diff", "--binary", "--", ".", ":(exclude)patches") == tracked
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


@pytest.mark.parametrize("case", ["missing_metadata", "invalid_base", "no_staged", "empty_selection"])
def test_failed_update_preserves_existing_patch(repo, case):
  path, _, stage, export = repo
  (path / "patches").mkdir()
  target = path / "patches/example.patch.disabled"
  target.write_bytes(b"original patch bytes\n")
  if case != "no_staged":
    stage()
  args = [] if case == "missing_metadata" else ["--base", "not-a-ref" if case == "invalid_base" else "HEAD"]
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
  (path / "docs").mkdir()
  for name in ("MAINTENANCE.md", "EV9_BEHAVIOR.md"):
    stage(f"docs/{name}", "maintenance reference\n")
  export("create_patch_manual.sh", "example", "--", "app.txt", "patches", "docs")
  patch = (path / "patches/example.patch").read_text()
  assert "+staged" in patch
  assert "metadata" not in patch and "vehicle edit" not in patch
  assert "docs/" not in patch


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


@pytest.mark.parametrize("vehicle", [False, True])
@pytest.mark.parametrize("committed", [False, True])
def test_update_infers_base_and_keeps_original_hunks(repo, vehicle, committed):
  path, git, stage, export = repo
  name = "opendbc/example" if vehicle else "example"
  source = "opendbc_repo/opendbc/car/example.py" if vehicle else "app.txt"
  base = git("rev-parse", "HEAD").decode().strip()
  stage(source, "first customization\n")
  export("create_patch.sh", name)
  git("add", "patches")
  git("commit", "-m", "first patch")
  stage("unrelated.txt", "unrelated committed history\n")
  git("commit", "-m", "unrelated source")
  stage(source, "first customization\nsecond customization\n")
  if committed:
    git("commit", "-m", "amend source before exporting patch")
  (path / source).write_text("unstaged content must not leak\n")
  export("update_patch.sh", name)
  options = ["--relative=opendbc_repo"] if vehicle else []
  expected = git("diff", "--cached", "--binary", "--full-index", "--no-renames", *options, base, "--", source)
  assert (path / f"patches/{name}.patch").read_bytes() == expected
  # Repeating with no further changes must preserve the full patch.
  export("update_patch.sh", name)
  assert (path / f"patches/{name}.patch").read_bytes() == expected


def test_update_includes_newly_staged_files_and_excludes_maintenance(repo):
  path, git, stage, export = repo
  base = git("rev-parse", "HEAD").decode().strip()
  stage(content="original customization\n")
  export("create_patch.sh", "example.patch.temp-disabled")
  git("add", "patches")
  git("commit", "-m", "first patch")
  stage("extra source.txt", "newly included customization\n")
  stage("AGENTS.md", "maintenance\n")
  (path / "docs").mkdir()
  for name in ("MAINTENANCE.md", "EV9_BEHAVIOR.md"):
    stage(f"docs/{name}", "maintenance reference\n")
  export("update_patch.sh", "example")
  expected = git("diff", "--cached", "--binary", "--full-index", "--no-renames", base, "--", "app.txt", "extra source.txt")
  assert (path / "patches/example.patch.temp-disabled").read_bytes() == expected
  assert not (path / "patches/example.patch").exists()


@pytest.mark.parametrize("vehicle", [False, True])
def test_update_infers_binary_add_delete_rename_and_executable_changes(repo, vehicle):
  path, git, stage, export = repo
  prefix = "opendbc_repo/" if vehicle else ""
  name = "opendbc/example" if vehicle else "example"
  binary = prefix + "binary.dat"
  old = prefix + "old name.txt"
  new = prefix + "new name.txt"
  deleted = prefix + "deleted.txt"
  added = prefix + "added\tspace\nfile.sh"
  (path / binary).write_bytes(bytes(range(256)))
  stage(old, "rename me\n")
  stage(deleted, "delete me\n")
  git("add", binary)
  git("commit", "-m", "binary and rename baseline")
  base = git("rev-parse", "HEAD").decode().strip()
  (path / binary).write_bytes(bytes(range(256)) * 2)
  (path / old).rename(path / new)
  (path / deleted).unlink()
  stage(added, "#!/bin/sh\necho first\n")
  (path / added).chmod(0o755)
  git("add", "-A")
  export("create_patch.sh", name)
  git("add", "patches")
  git("commit", "-m", "first compound patch")
  (path / binary).write_bytes(bytes(range(256)) * 3)
  stage(new, "rename me and amend\n")
  stage(added, "#!/bin/sh\necho second\n")
  git("add", binary)
  export("update_patch.sh", name)
  options = ["--relative=opendbc_repo"] if vehicle else []
  expected = git("diff", "--cached", "--binary", "--full-index", "--no-renames", *options, base, "--", binary, old, new, deleted, added)
  assert (path / f"patches/{name}.patch").read_bytes() == expected


def test_update_mode_only_patch_does_not_swallow_staged_content(repo):
  path, git, stage, export = repo
  base = git("rev-parse", "HEAD").decode().strip()
  (path / "app.txt").chmod(0o755)
  git("add", "app.txt")
  export("create_patch.sh", "example")
  git("add", "patches")
  git("commit", "-m", "executable mode patch")
  stage(content="content amendment\n")
  export("update_patch.sh", "example")
  expected = git("diff", "--cached", "--binary", "--full-index", "--no-renames", base, "--", "app.txt")
  assert (path / "patches/example.patch").read_bytes() == expected


def test_update_with_unavailable_original_blob_preserves_patch(repo):
  path, git, stage, export = repo
  stage()
  export("create_patch.sh", "example")
  target = path / "patches/example.patch"
  original = git("rev-parse", "HEAD:app.txt").strip()
  missing_blob_patch = target.read_bytes().replace(original, b"f" * len(original))
  target.write_bytes(missing_blob_patch)
  result = export("update_patch.sh", "example", success=False)
  assert b"--base REF" in result.stderr
  assert target.read_bytes() == missing_blob_patch


def test_update_automatic_scope_can_be_explicitly_limited(repo):
  path, git, stage, export = repo
  base = git("rev-parse", "HEAD").decode().strip()
  stage(content="first customization\n")
  export("create_patch.sh", "example")
  git("add", "patches")
  git("commit", "-m", "first patch")
  stage(content="second customization\n")
  stage("unrelated.txt", "excluded staged file\n")
  export("update_patch.sh", "example", "--", "app.txt")
  expected = git("diff", "--cached", "--binary", "--full-index", "--no-renames", base, "--", "app.txt")
  assert (path / "patches/example.patch").read_bytes() == expected
