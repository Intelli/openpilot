"""Exercise deployment and source promotion against an isolated local Git remote."""
import os
from pathlib import Path
import subprocess
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
    self.commit("baseline")
    self.git("push", "origin", "HEAD:ev9", cwd=self.source)
    (self.source / "source.txt").write_text("published")
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
    self.run_command("bash", str(ROOT / "release/ci/publish.sh"), str(output), sha)
    return self.git("--git-dir", str(self.remote), "rev-parse", "ev9-prebuilt")

  def sync(self):
    return self.run_command("bash", str(ROOT / "tools/ci/sync_ev9_branch.sh"), cwd=self.source)

  def remote_tree(self, branch):
    return self.git("--git-dir", str(self.remote), "rev-parse", f"{branch}^{{tree}}")

  def test_identical_payload_updates_provenance_and_promotes_only_built_source(self):
    first = self.publish(self.published)
    self.sync()
    assert self.remote_tree('ev9') == self.remote_tree(self.published)
    assert self.remote_tree('ev9') != self.remote_tree('ev9-dev')
    second = self.publish(self.newer)
    assert first != second
    assert self.remote_tree(first) == self.remote_tree(second)
    assert self.publish(self.newer) == second
    self.sync()
    assert self.remote_tree('ev9') == self.remote_tree('ev9-dev')
    head = self.git("--git-dir", str(self.remote), "rev-parse", "ev9")
    self.sync()
    assert self.git('--git-dir', str(self.remote), 'rev-parse', 'ev9') == head

  def test_publish_removes_obsolete_files_and_preserves_history(self):
    first = self.publish(self.published, "obsolete")
    second = self.publish(self.newer, "replacement")
    assert self.git('--git-dir', str(self.remote), 'rev-parse', f'{second}^') == first
    assert self.git('--git-dir', str(self.remote), 'ls-tree', '--name-only', second) == 'prebuilt\nreplacement'

  def test_sync_rejects_unknown_source(self):
    self.publish("a" * 40)
    before = self.remote_tree("ev9")
    with pytest.raises(subprocess.CalledProcessError):
      self.sync()
    assert self.remote_tree('ev9') == before
