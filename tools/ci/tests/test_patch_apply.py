"""Patch replay checks use only disposable Git repositories."""
import os
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest  # noqa: TID251 - standalone maintenance checks need no project dependencies


SOURCE = Path(__file__).resolve().parents[3]


class TestPatchApply(unittest.TestCase):
  def setUp(self):
    self.tmp = tempfile.TemporaryDirectory()
    self.addCleanup(self.tmp.cleanup)
    self.root = Path(self.tmp.name)
    self.env = dict(os.environ, GIT_CONFIG_GLOBAL=os.devnull, GIT_CONFIG_NOSYSTEM="1",
                    GIT_AUTHOR_NAME="Fixture", GIT_AUTHOR_EMAIL="fixture@example.com",
                    GIT_COMMITTER_NAME="Fixture", GIT_COMMITTER_EMAIL="fixture@example.com")
    for name in ("apply_patch.sh", "apply_patch_conflicts.sh", "tools/opendbc-patches/apply.sh"):
      dest = self.root / name
      dest.parent.mkdir(parents=True, exist_ok=True)
      shutil.copyfile(SOURCE / name, dest)
    self.write("app.txt", "before\n")
    self.write("opendbc_repo/opendbc/car.txt", "before\n")
    self.git("init", "-q")
    self.git("add", ".")
    self.git("commit", "-qm", "fixture")
    self.head = self.git("rev-parse", "HEAD").stdout
    self.index = self.git("write-tree").stdout

  def write(self, path, value):
    dest = self.root / path
    dest.parent.mkdir(parents=True, exist_ok=True)
    dest.write_text(value)
    return dest

  def git(self, *args):
    return subprocess.run(["git", *args], cwd=self.root, env=self.env, text=True, capture_output=True, check=True)

  def patch(self, name, path="app.txt", before="before", after="after"):
    return self.write("patches/" + name, f"diff --git a/{path} b/{path}\n--- a/{path}\n+++ b/{path}\n@@ -1 +1 @@\n-{before}\n+{after}\n")

  def apply(self, *args, script="apply_patch.sh", ok=True):
    result = subprocess.run(["bash", str(self.root / script), *args], cwd=self.root, env=self.env, text=True, capture_output=True)
    self.assertEqual(result.returncode == 0, ok, result.stdout + result.stderr)
    self.assertEqual(self.git("rev-parse", "HEAD").stdout, self.head)
    return result

  def assert_index_unchanged(self):
    self.assertEqual(self.git("write-tree").stdout, self.index)

  def test_missing_or_disabled_only_is_noop(self):
    self.apply()
    self.patch("old.patch.disabled")
    self.patch("opendbc/old.patch.disabled", "opendbc/car.txt")
    self.patch("temporary.patch.temp-disabled")
    self.patch("opendbc/temporary.patch.temp-disabled", "opendbc/car.txt")
    self.apply()
    self.apply("--all", script="tools/opendbc-patches/apply.sh")
    self.apply("old.patch.disabled", ok=False)
    self.apply("opendbc/old.patch.disabled", ok=False)
    self.apply("temporary.patch.temp-disabled", ok=False)
    self.apply("opendbc/temporary.patch.temp-disabled", ok=False)
    self.assertEqual((self.root / "app.txt").read_text(), "before\n")
    self.assert_index_unchanged()

  def test_discovery_root_then_vehicle_alphabetical(self):
    self.patch("b.patch", before="middle", after="root done")
    self.patch("a.patch", after="middle")
    self.patch("opendbc/a.patch", "opendbc/car.txt", after="vehicle done")
    result = self.apply()
    self.assertLess(result.stdout.index("patches/a.patch"), result.stdout.index("patches/b.patch"))
    self.assertLess(result.stdout.index("patches/b.patch"), result.stdout.index("patches/opendbc/a.patch"))
    self.assertEqual((self.root / "app.txt").read_text(), "root done\n")
    self.assertEqual((self.root / "opendbc_repo/opendbc/car.txt").read_text(), "vehicle done\n")
    self.assert_index_unchanged()

  def test_retired_planner_archive_is_skipped_and_cannot_be_selected(self):
    archive = self.patch("archive/ev9_custom_planner.patch", after="retired planner")
    self.write("patches/archive/EV9_CUSTOM_PLANNER.md", "Recovery only; not an enabled patch.\n")
    # Prove the archive could change application code if accidentally replayed.
    self.git("apply", "--check", str(archive))
    self.patch("opendbc/active.patch", "opendbc/car.txt", after="active vehicle change")
    for args in ((), ("--all",), ("--check",)):
      self.apply(*args)
      self.assertEqual((self.root / "app.txt").read_text(), "before\n")
      self.assert_index_unchanged()
    self.assertEqual((self.root / "opendbc_repo/opendbc/car.txt").read_text(), "active vehicle change\n")

    for script in ("apply_patch.sh", "apply_patch_conflicts.sh", "tools/opendbc-patches/apply.sh"):
      for name in ("archive/ev9_custom_planner.patch", "patches/archive/ev9_custom_planner.patch", str(archive)):
        with self.subTest(script=script, name=name):
          result = self.apply(name, script=script, ok=False)
          self.assertIn("Patch must be an enabled file directly in", result.stderr)
          self.assertEqual((self.root / "app.txt").read_text(), "before\n")
          self.assert_index_unchanged()

  def test_named_spaces_check_and_idempotence(self):
    patch = self.patch("with spaces.patch")
    self.apply("--check", str(patch))
    self.assertEqual((self.root / "app.txt").read_text(), "before\n")
    self.apply("patches/with spaces.patch")
    self.assertIn("Already applied", self.apply("with spaces.patch").stdout)
    self.assert_index_unchanged()

  def test_vehicle_alias_and_wrapper_scope(self):
    self.patch("root.patch")
    self.patch("opendbc/vehicle name.patch", "opendbc/car.txt")
    self.apply("--check", "opendbc/vehicle name.patch")
    self.apply("--all", script="tools/opendbc-patches/apply.sh")
    self.assertEqual((self.root / "app.txt").read_text(), "before\n")
    self.assertEqual((self.root / "opendbc_repo/opendbc/car.txt").read_text(), "after\n")
    self.apply("patches/opendbc/vehicle name.patch")
    self.assert_index_unchanged()

  def test_normal_conflict_does_not_modify_or_stage(self):
    self.patch("conflict.patch")
    self.write("app.txt", "user changes\n")
    self.apply("conflict.patch", ok=False)
    self.assertEqual((self.root / "app.txt").read_text(), "user changes\n")
    self.assert_index_unchanged()

  def test_explicit_three_way_preserves_conflicts(self):
    self.write("app.txt", "patch changes\n")
    patch = self.git("diff", "--full-index", "--", "app.txt").stdout
    self.write("patches/conflict.patch", patch)
    self.write("app.txt", "committed other changes\n")
    self.git("add", "app.txt")
    self.git("commit", "-qm", "other")
    self.head = self.git("rev-parse", "HEAD").stdout
    self.index = self.git("write-tree").stdout
    self.apply("--check", "conflict.patch", script="apply_patch_conflicts.sh", ok=False)
    self.assert_index_unchanged()
    self.apply("conflict.patch", script="apply_patch_conflicts.sh", ok=False)
    self.assertTrue(self.git("ls-files", "-u").stdout)
    self.assertIn("<<<<<<<", (self.root / "app.txt").read_text())


if __name__ == "__main__":
  unittest.main()
