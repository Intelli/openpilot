"""Exercise snapshot imports only in disposable repositories; no network required."""
import json
import os
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest  # noqa: TID251 - maintenance-script checks run without project dependencies


SCRIPT = Path(__file__).resolve().parents[3] / "sync-upstream.sh"
UPSTREAM = "https://github.com/firestar5683/StarPilot.git"


class TestStarPilotSync(unittest.TestCase):
  def setUp(self):
    self.tmp = tempfile.TemporaryDirectory()
    self.addCleanup(self.tmp.cleanup)
    self.root = Path(self.tmp.name)
    self.env = dict(os.environ, GIT_CONFIG_GLOBAL=os.devnull, GIT_CONFIG_NOSYSTEM="1", GIT_ALLOW_PROTOCOL="file",
                    GIT_AUTHOR_NAME="Fixture", GIT_AUTHOR_EMAIL="fixture@example.com",
                    GIT_COMMITTER_NAME="Fixture", GIT_COMMITTER_EMAIL="fixture@example.com")
    self.upstream = self.repo("upstream", "StarPilot")
    self.write(self.upstream, "app.txt", "stable\n")
    self.write(self.upstream, "opendbc_repo/opendbc/example.txt", "vendored\n")
    self.commit(self.upstream)
    self.bare = self.root / "upstream.git"
    self.git(self.root, "clone", "--bare", str(self.upstream), str(self.bare))
    self.local = self.repo("local", "ev9-dev")
    shutil.copyfile(SCRIPT, self.local / "sync-upstream.sh")
    self.write(self.local, "app.txt", "legacy\n")
    self.write(self.local, "obsolete.txt", "remove me\n")
    self.write(self.local, "apply_patch.sh", "legacy helper\n")
    self.write(self.local, "tools/opendbc-patches/legacy/update_patch.sh", "archived helper\n")
    self.write(self.local, "tools/patches/create.py", "patch generator\n")
    self.write(self.local, "patches/opendbc/old.patch", "deliberately invalid patch: never execute\n")
    self.commit(self.local)
    self.git(self.local, "config", f"url.{self.bare.as_uri()}.insteadOf", UPSTREAM)
    self.git(self.local, "remote", "add", "starpilot", UPSTREAM)
    self.head = self.git(self.local, "rev-parse", "HEAD").stdout.strip()
    self.remote_head = self.git(self.bare, "rev-parse", "StarPilot").stdout.strip()

  def git(self, cwd, *args):
    return subprocess.run(["git", *args], cwd=cwd, env=self.env, check=True, capture_output=True, text=True)

  def repo(self, name, branch):
    path = self.root / name
    self.git(self.root, "init", "-b", branch, str(path))
    return path

  def write(self, repo, path, text):
    dest = repo / path
    dest.parent.mkdir(parents=True, exist_ok=True)
    dest.write_text(text)

  def commit(self, repo):
    self.git(repo, "add", "-A")
    self.git(repo, "commit", "-m", "fixture")

  def sync(self, *args, success=True):
    result = subprocess.run(["bash", "sync-upstream.sh", *args], cwd=self.local, env=self.env, capture_output=True, text=True)
    self.assertEqual(result.returncode == 0, success, result.stdout + result.stderr)
    return result

  def add_submodule(self):
    sub = self.repo("sub", "main")
    self.write(sub, "opendbc/example.txt", "old submodule\n")
    self.commit(sub)
    self.git(self.local, "submodule", "add", str(sub), "opendbc_repo")
    self.commit(self.local)
    self.head = self.git(self.local, "rev-parse", "HEAD").stdout.strip()

  def assert_no_publish(self):
    self.assertEqual(self.git(self.local, "rev-parse", "HEAD").stdout.strip(), self.head)
    self.assertEqual(self.git(self.bare, "rev-parse", "StarPilot").stdout.strip(), self.remote_head)

  def test_preview_and_missing_allow_leave_source_and_index_unchanged(self):
    before = self.git(self.local, "write-tree").stdout
    self.sync("--check")
    self.sync(success=False)
    self.assertEqual((self.local / "app.txt").read_text(), "legacy\n")
    self.assertEqual(self.git(self.local, "write-tree").stdout, before)
    self.assertFalse((self.local / "starpilot-upstream.json").exists())
    self.assert_no_publish()

  def test_converts_submodule_preserves_helpers_and_does_not_apply_patches(self):
    self.add_submodule()
    self.write(self.local, "apply_patch.sh", "dirty helper\n")
    self.sync("--allow")
    self.assertEqual((self.local / "app.txt").read_text(), "stable\n")
    self.assertEqual((self.local / "opendbc_repo/opendbc/example.txt").read_text(), "vendored\n")
    self.assertFalse((self.local / "opendbc_repo/.git").exists())
    self.assertFalse((self.local / ".gitmodules").exists())
    self.assertFalse((self.local / "obsolete.txt").exists())
    self.assertEqual((self.local / "apply_patch.sh").read_text(), "dirty helper\n")
    self.assertTrue((self.local / "patches/opendbc/old.patch").exists())
    self.assertEqual((self.local / "tools/opendbc-patches/legacy/update_patch.sh").read_text(), "archived helper\n")
    self.assertEqual((self.local / "tools/patches/create.py").read_text(), "patch generator\n")
    backups = list((self.local / ".git/starpilot-backups").glob("*/opendbc_repo/opendbc/example.txt"))
    self.assertEqual(len(backups), 1)
    self.assertEqual(backups[0].read_text(), "old submodule\n")
    self.assertIn("100644", self.git(self.local, "ls-files", "--stage", "opendbc_repo/opendbc/example.txt").stdout)
    self.assertFalse(json.loads((self.local / "starpilot-upstream.json").read_text())["legacy_patches_applied"])
    self.assert_no_publish()

  def test_refuses_dirty_application(self):
    self.write(self.local, "app.txt", "unsaved\n")
    self.sync("--allow", success=False)
    self.assertEqual((self.local / "app.txt").read_text(), "unsaved\n")
    self.assert_no_publish()
    self.git(self.local, "add", "app.txt")
    self.sync("--allow", success=False)
    self.assertEqual((self.local / "app.txt").read_text(), "unsaved\n")

  def test_maintenance_docs_and_archives_survive_missing_and_colliding_upstream_files(self):
    archive = {
      "docs/MAINTENANCE.md": "ongoing maintenance workflow\n",
      "docs/EV9_BEHAVIOR.md": "current EV9 behavior\n",
      "docs/C3X_UPDATE_WORKFLOW.md": "local device update workflow\n",
      "patches/archive/ev9_custom_planner.patch": "retired planner recovery patch\n",
      "patches/archive/EV9_CUSTOM_PLANNER.md": "retired planner provenance\n",
      "patches/archive/EV9_STARTUP_TEST.md": "reverted startup experiment history\n",
    }
    for path, contents in archive.items():
      self.write(self.local, path, contents)
    self.commit(self.local)
    self.head = self.git(self.local, "rev-parse", "HEAD").stdout.strip()

    # Neither deletion by an upstream snapshot nor a same-name upstream file
    # may change preserved document/archive bytes in the working tree or index.
    for collision in (False, True):
      with self.subTest(upstream_collision=collision):
        if collision:
          self.commit(self.local)
          self.head = self.git(self.local, "rev-parse", "HEAD").stdout.strip()
          for path in archive:
            self.write(self.upstream, path, "upstream replacement\n")
          self.commit(self.upstream)
          self.git(self.upstream, "push", str(self.bare), "StarPilot")
          self.remote_head = self.git(self.bare, "rev-parse", "StarPilot").stdout.strip()
        self.sync("--allow")
        for path, contents in archive.items():
          self.assertEqual((self.local / path).read_text(), contents)
          self.assertEqual(self.git(self.local, "show", f":{path}").stdout, contents)
        self.assertEqual((self.local / "app.txt").read_text(), "stable\n")
        self.assert_no_publish()

  def test_refuses_dirty_submodule(self):
    self.add_submodule()
    self.write(self.local, "opendbc_repo/opendbc/example.txt", "unsaved submodule\n")
    self.sync("--allow", success=False)
    self.assertEqual((self.local / "opendbc_repo/opendbc/example.txt").read_text(), "unsaved submodule\n")
    self.assertTrue((self.local / "opendbc_repo/.git").exists())
    self.assert_no_publish()

  def test_refuses_untracked_source_collision(self):
    self.write(self.upstream, "untracked.txt", "upstream\n")
    self.commit(self.upstream)
    self.git(self.upstream, "push", str(self.bare), "StarPilot")
    self.remote_head = self.git(self.bare, "rev-parse", "StarPilot").stdout.strip()
    self.write(self.local, "untracked.txt", "unsaved personal\n")
    self.sync("--allow", success=False)
    self.assertEqual((self.local / "untracked.txt").read_text(), "unsaved personal\n")
    self.assert_no_publish()

  def test_refuses_ignored_collision_before_moving_submodules(self):
    self.add_submodule()
    self.write(self.upstream, "ignored.bin", "upstream\n")
    self.commit(self.upstream)
    self.git(self.upstream, "push", str(self.bare), "StarPilot")
    self.write(self.local, ".git/info/exclude", "ignored.bin\n")
    self.write(self.local, "ignored.bin", "local ignored bytes\n")
    self.sync("--allow", success=False)
    self.assertEqual((self.local / "ignored.bin").read_text(), "local ignored bytes\n")
    self.assertTrue((self.local / "opendbc_repo/.git").exists())
    self.assertFalse((self.local / ".git/starpilot-backups").exists())

  def test_import_bypasses_legacy_lfs_filters_and_hooks(self):
    self.write(self.upstream, "raw.bin", "stored raw bytes\n")
    self.commit(self.upstream)
    self.git(self.upstream, "push", str(self.bare), "StarPilot")
    # Local attributes deliberately cover both imported bytes and new metadata.
    self.write(self.local, ".git/info/attributes", "*.bin filter=lfs\nstarpilot-upstream.json filter=lfs\n")
    for name in ("process", "smudge", "clean"):
      self.git(self.local, "config", f"filter.lfs.{name}", "false")
    self.git(self.local, "config", "filter.lfs.required", "true")
    hook = self.local / ".git/hooks/post-index-change"
    hook.write_text("#!/bin/sh\ntouch old-hook-ran\n")
    hook.chmod(0o755)
    self.sync("--allow")
    self.assertEqual((self.local / "raw.bin").read_text(), "stored raw bytes\n")
    self.assertEqual(self.git(self.local, "show", ":raw.bin").stdout, "stored raw bytes\n")
    self.assertFalse((self.local / "old-hook-ran").exists())
    self.assertEqual(self.git(self.local, "config", "filter.lfs.process").stdout.strip(), "false")

  def test_preserved_and_noncolliding_untracked_files_survive(self):
    self.write(self.local, "patches/opendbc/new.patch", "new archived patch\n")
    self.write(self.local, ".git/info/exclude", "cache.bin\n")
    self.write(self.local, "cache.bin", "local cache\n")
    self.sync("--allow")
    self.assertEqual((self.local / "patches/opendbc/new.patch").read_text(), "new archived patch\n")
    self.assertEqual((self.local / "cache.bin").read_text(), "local cache\n")

  def test_subsequent_snapshot_adds_and_removes_files(self):
    self.sync("--allow")
    self.commit(self.local)
    self.head = self.git(self.local, "rev-parse", "HEAD").stdout.strip()
    (self.upstream / "app.txt").unlink()
    self.write(self.upstream, "new.txt", "next stable\n")
    self.commit(self.upstream)
    self.git(self.upstream, "push", str(self.bare), "StarPilot")
    self.remote_head = self.git(self.bare, "rev-parse", "StarPilot").stdout.strip()
    self.sync("--allow")
    self.assertFalse((self.local / "app.txt").exists())
    self.assertEqual((self.local / "new.txt").read_text(), "next stable\n")
    self.assert_no_publish()


if __name__ == "__main__":
  unittest.main()
