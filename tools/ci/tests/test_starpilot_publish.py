"""Exercise deployment and built-artifact promotion against an isolated local Git remote."""
import os
from pathlib import Path
import shutil
import subprocess
import sys
import tempfile
import pytest


ROOT = Path(__file__).resolve().parents[3]


class TestStarPilotPublish:
  def setup_method(self):
    self.tmp = tempfile.TemporaryDirectory()
    self.root = Path(self.tmp.name)
    self.env = dict(os.environ, GIT_CONFIG_GLOBAL=str(self.root / "gitconfig"), GIT_CONFIG_NOSYSTEM="1", GIT_TERMINAL_PROMPT="0",
                    GIT_ALLOW_PROTOCOL="file")
    self.remote = self.root / "origin.git"
    self.git("init", "--bare", str(self.remote))
    self.git("config", "--global", "user.name", "Test")
    self.git("config", "--global", "user.email", "test@example.invalid")
    self.git("config", "--global", f"url.{self.remote}.insteadOf", "https://github.com/Intelli/openpilot.git")
    self.source = self.root / "source"
    self.git("init", "--initial-branch=ev9-dev", str(self.source))
    self.git("remote", "add", "origin", str(self.remote), cwd=self.source)
    (self.source / "source.txt").write_text("baseline")
    (self.source / "common").mkdir()
    (self.source / "common/params_pyx.so").write_text("stale upstream extension")
    (self.source / "common/params_keys.h").write_text("old defaults")
    (self.source / "manager.py").write_text("old Python")
    (self.source / "obsolete-target.txt").write_text("remove on promotion")
    self.baseline = self.commit("baseline")
    self.git("push", "origin", "HEAD:ev9", cwd=self.source)
    (self.source / "source.txt").write_text("published")
    (self.source / "common/params_keys.h").write_text("EV9 defaults")
    (self.source / "manager.py").write_text("EV9 Python")
    self.published = self.commit("published")
    (self.source / "source.txt").write_text("not built yet")
    self.newer = self.commit("newer")
    self.git("push", "origin", "ev9-dev", cwd=self.source)
    self.sequence = 0

  def teardown_method(self):
    self.tmp.cleanup()

  def run_command(self, *args, cwd=None):
    return subprocess.check_output(args, cwd=cwd or self.root, env=self.env, stderr=subprocess.STDOUT, text=True).strip()

  def git(self, *args, cwd=None):
    return self.run_command("git", *args, cwd=cwd)

  def commit(self, message):
    self.git("add", "--all", cwd=self.source)
    self.git("commit", "-m", message, cwd=self.source)
    return self.git("rev-parse", "HEAD", cwd=self.source)

  def publish(self, sha, filename="payload"):
    self.sequence += 1
    output = self.root / f"output-{self.sequence}"
    output.mkdir()
    (output / "prebuilt").touch()
    (output / filename).write_text("unchanged binary")
    (output / "common").mkdir()
    (output / "common/params_pyx.so").write_text("rebuilt extension with EV9 defaults")
    for path in ("common/params_keys.h", "manager.py", "source.txt"):
      (output / path).write_text(self.git("show", f"{self.published}:{path}", cwd=self.source))
    self.run_command("bash", str(ROOT / "release/ci/publish.sh"), str(output), sha)
    return self.git("--git-dir", str(self.remote), "rev-parse", "ev9-prebuilt")

  def sync(self):
    return self.run_command("bash", str(ROOT / "tools/ci/sync_ev9_branch.sh"), cwd=self.source)

  def remote_tree(self, branch):
    return self.git("--git-dir", str(self.remote), "rev-parse", f"{branch}^{{tree}}")

  def assert_root_snapshot(self, sha):
    assert self.git("--git-dir", str(self.remote), "rev-list", "--count", sha) == "1"
    # Inspect real headers: a depth-one fetch alone can hide an existing parent.
    headers = self.git("--git-dir", str(self.remote), "cat-file", "-p", sha).split("\n\n", 1)[0]
    assert not any(line.startswith("parent ") for line in headers.splitlines())
    assert self.git("--git-dir", str(self.remote), "rev-parse", "ev9-dev") == self.newer

  def test_identical_payload_updates_provenance_and_promotes_only_built_source(self):
    first = self.publish(self.published)
    self.assert_root_snapshot(first)
    self.sync()
    first_prod = self.git("--git-dir", str(self.remote), "rev-parse", "ev9")
    assert self.remote_tree('ev9') == self.remote_tree(first)
    assert self.remote_tree('ev9') != self.remote_tree(self.published)
    assert self.git("--git-dir", str(self.remote), "rev-parse", f"{first_prod}^") == self.baseline
    assert self.git("--git-dir", str(self.remote), "show", "ev9:common/params_pyx.so") == "rebuilt extension with EV9 defaults"
    assert self.git("--git-dir", str(self.remote), "show", "ev9:common/params_keys.h") == "EV9 defaults"
    assert self.git("--git-dir", str(self.remote), "show", "ev9:manager.py") == "EV9 Python"
    assert self.git("--git-dir", str(self.remote), "show", "ev9:source.txt") == "published"
    files = self.git("--git-dir", str(self.remote), "ls-tree", "-r", "--name-only", "ev9").splitlines()
    assert "prebuilt" in files and "obsolete-target.txt" not in files
    message = self.git("--git-dir", str(self.remote), "log", "-1", "--format=%B", "ev9")
    assert f"Source-Commit: {self.published}" in message
    assert f"Build-Commit: {first}" in message
    assert self.git("--git-dir", str(self.remote), "log", "-1", "--format=%(trailers:key=Source-Commit,valueonly)", "ev9") == self.published
    assert self.git("--git-dir", str(self.remote), "log", "-1", "--format=%(trailers:key=Build-Commit,valueonly)", "ev9") == first
    assert self.remote_tree('ev9') != self.remote_tree('ev9-dev')
    second = self.publish(self.newer)
    self.assert_root_snapshot(second)
    assert first != second
    assert self.remote_tree(first) == self.remote_tree(second)
    assert self.publish(self.newer) == second
    self.sync()
    assert self.remote_tree('ev9') == self.remote_tree(second)
    assert self.git("--git-dir", str(self.remote), "rev-parse", "ev9^") == first_prod
    message = self.git("--git-dir", str(self.remote), "log", "-1", "--format=%B", "ev9")
    assert f"Source-Commit: {self.newer}" in message
    assert f"Build-Commit: {second}" in message
    head = self.git("--git-dir", str(self.remote), "rev-parse", "ev9")
    self.sync()
    assert self.git('--git-dir', str(self.remote), 'rev-parse', 'ev9') == head

  def test_publish_replaces_snapshot_removes_obsolete_files_and_preserves_ev9_history(self):
    first = self.publish(self.published, "obsolete")
    self.sync()
    first_prod = self.git("--git-dir", str(self.remote), "rev-parse", "ev9")
    second = self.publish(self.newer, "replacement")
    self.assert_root_snapshot(first)
    self.assert_root_snapshot(second)
    files = self.git('--git-dir', str(self.remote), 'ls-tree', '-r', '--name-only', second).splitlines()
    assert "obsolete" not in files and "replacement" in files and "prebuilt" in files
    self.sync()
    assert self.remote_tree("ev9") == self.remote_tree(second)
    assert self.git("--git-dir", str(self.remote), "rev-parse", "ev9^") == first_prod

  def test_sync_rejects_unknown_source(self):
    self.publish("a" * 40)
    before = self.remote_tree("ev9")
    with pytest.raises(subprocess.CalledProcessError):
      self.sync()
    assert self.remote_tree('ev9') == before

  @pytest.mark.parametrize("case", ["invalid", "missing", "nonancestor", "no_marker"])
  def test_rejects_invalid_build_without_changing_production(self, case):
    self.publish(self.published)
    self.git("fetch", "origin", "ev9-prebuilt", cwd=self.source)
    parent = self.git("rev-parse", "FETCH_HEAD", cwd=self.source)
    tree = self.git("rev-parse", f"{parent}^{{tree}}", cwd=self.source)
    source = self.published
    if case == "nonancestor":
      source = self.git("commit-tree", tree, "-m", "unrelated source", cwd=self.source)
    if case == "no_marker":
      # This source tree has no prebuilt marker, despite valid source provenance.
      tree = self.git("rev-parse", f"{self.published}^{{tree}}", cwd=self.source)
    message = "missing provenance" if case == "missing" else f"build\n\nSource-Commit: {'not-a-sha' if case == 'invalid' else source}"
    build = self.git("commit-tree", tree, "-p", parent, "-m", message, cwd=self.source)
    self.git("push", "origin", f"{build}:ev9-prebuilt", cwd=self.source)
    before = self.git("--git-dir", str(self.remote), "rev-parse", "ev9")
    with pytest.raises(subprocess.CalledProcessError):
      self.sync()
    assert self.git("--git-dir", str(self.remote), "rev-parse", "ev9") == before

  def test_same_tree_and_source_new_build_updates_build_provenance(self):
    first = self.publish(self.published)
    self.sync()
    previous_prod = self.git("--git-dir", str(self.remote), "rev-parse", "ev9")
    self.git("fetch", "origin", "ev9-prebuilt", cwd=self.source)
    tree = self.git("rev-parse", "FETCH_HEAD^{tree}", cwd=self.source)
    second = self.git("commit-tree", tree, "-p", first, "-m", f"rebuild\n\nSource-Commit: {self.published}", cwd=self.source)
    self.git("push", "origin", f"{second}:ev9-prebuilt", cwd=self.source)
    self.sync()
    assert self.git("--git-dir", str(self.remote), "rev-parse", "ev9") != previous_prod
    assert self.remote_tree("ev9") == tree
    message = self.git("--git-dir", str(self.remote), "log", "-1", "--format=%B", "ev9")
    assert f"Build-Commit: {second}" in message

  def test_identical_legacy_snapshot_is_flattened_despite_shallow_fetch(self):
    first = self.publish(self.published)
    self.git("fetch", "origin", "ev9-prebuilt", cwd=self.source)
    tree = self.remote_tree(first)
    legacy = self.git("commit-tree", tree, "-p", first, "-m", f"legacy\n\nSource-Commit: {self.published}", cwd=self.source)
    self.git("push", "origin", f"{legacy}:ev9-prebuilt", cwd=self.source)
    assert self.git("--git-dir", str(self.remote), "rev-list", "--count", "ev9-prebuilt") == "2"
    prod_before = self.git("--git-dir", str(self.remote), "rev-parse", "ev9")
    flattened = self.publish(self.published)
    assert flattened != legacy
    assert self.remote_tree(flattened) == tree
    self.assert_root_snapshot(flattened)
    assert self.publish(self.published) == flattened
    assert self.git("--git-dir", str(self.remote), "rev-parse", "ev9") == prod_before

  def test_publish_rejects_intervening_remote_change_with_explicit_lease(self):
    first = self.publish(self.published)
    self.git("fetch", "origin", "ev9-prebuilt", cwd=self.source)
    competitor = self.git("commit-tree", self.remote_tree(first), "-m", "concurrent build", cwd=self.source)
    self.git("push", "origin", f"{competitor}:refs/heads/race-fixture", cwd=self.source)
    real_git = shutil.which("git")
    wrapper_dir = self.root / "wrapper"
    wrapper_dir.mkdir()
    wrapper = wrapper_dir / "git"
    wrapper.write_text(f"#!{sys.executable}\n" + '''import os
import subprocess
import sys
from pathlib import Path

args = sys.argv[1:]
if args and args[0] == "push":
  Path(os.environ["TEST_PUSH_ARGS"]).write_text("\\n".join(args))
  subprocess.run([os.environ["TEST_REAL_GIT"], "--git-dir", os.environ["TEST_REMOTE"],
                  "update-ref", "refs/heads/ev9-prebuilt", os.environ["TEST_COMPETITOR"]], check=True)
os.execv(os.environ["TEST_REAL_GIT"], [os.environ["TEST_REAL_GIT"], *args])
''')
    wrapper.chmod(0o755)
    push_args = self.root / "push-args"
    original_env = self.env.copy()
    self.env.update(PATH=str(wrapper_dir) + os.pathsep + os.environ["PATH"], TEST_REAL_GIT=real_git,
                    TEST_REMOTE=str(self.remote), TEST_COMPETITOR=competitor, TEST_PUSH_ARGS=str(push_args))
    prod_before = self.git("--git-dir", str(self.remote), "rev-parse", "ev9")
    try:
      with pytest.raises(subprocess.CalledProcessError):
        self.publish(self.newer)
    finally:
      self.env = original_env
    args = push_args.read_text().splitlines()
    assert f"--force-with-lease=refs/heads/ev9-prebuilt:{first}" in args
    assert "--force" not in args and "--mirror" not in args and "--all" not in args
    assert self.git("--git-dir", str(self.remote), "rev-parse", "ev9-prebuilt") == competitor
    assert self.git("--git-dir", str(self.remote), "rev-parse", "ev9") == prod_before
    assert self.git("--git-dir", str(self.remote), "rev-parse", "ev9-dev") == self.newer
