"""Snapshot-sync integration checks use local, disposable Git/LFS repositories."""
import hashlib
import json
import os
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest  # noqa: TID251 - maintenance checks run without application dependencies


ROOT = Path(__file__).resolve().parents[3]
APPLICATION = "https://github.com/sunnypilot/sunnypilot.git"
OPENDBC = "https://github.com/sunnypilot/opendbc.git"
BRANCH = "hkg-angle-steering-2025"


class TestSunnypilotSync(unittest.TestCase):
  def setUp(self):
    self.tmp = tempfile.TemporaryDirectory()
    self.addCleanup(self.tmp.cleanup)
    self.root = Path(self.tmp.name)
    self.env = dict(os.environ, GIT_CONFIG_GLOBAL=os.devnull, GIT_CONFIG_NOSYSTEM="1", GIT_ALLOW_PROTOCOL="file",
                    GIT_AUTHOR_NAME="Fixture", GIT_AUTHOR_EMAIL="fixture@example.com",
                    GIT_COMMITTER_NAME="Fixture", GIT_COMMITTER_EMAIL="fixture@example.com")
    self.dependency = self.repo("dependency", BRANCH)
    self.write(self.dependency, "opendbc/example.txt", "pinned vehicle\n")
    self.write(self.dependency, "AGENTS.md", "dependency instructions\n")
    self.commit(self.dependency)
    self.pin = self.git(self.dependency, "rev-parse", "HEAD").stdout.strip()
    self.dependency_bare = self.bare(self.dependency)
    self.upstream = self.repo("upstream", BRANCH)
    self.write(self.upstream, "app.txt", "Sunnypilot application\n")
    self.write(self.upstream, ".gitignore", "*.o\n")
    self.write(self.upstream, "build", "upstream build: do not import\n")
    self.git(self.upstream, "submodule", "add", str(self.dependency_bare), "opendbc_repo")
    self.commit(self.upstream)
    self.application_pin = self.git(self.upstream, "rev-parse", "HEAD").stdout.strip()
    self.application_bare = self.bare(self.upstream)
    self.local = self.repo("local", "ev9-dev")
    shutil.copyfile(ROOT / "sync-upstream.sh", self.local / "sync-upstream.sh")
    shutil.copytree(ROOT / "tools/upstream", self.local / "tools/upstream")
    for path, contents in {
      "app.txt": "custom application\n", "obsolete.txt": "remove me\n",
      "opendbc_repo/opendbc/example.txt": "custom vehicle\n",
      "apply_patch.sh": "do not execute\n", "patches/opendbc/invalid.patch": "never replay\n",
      "build": "maintained build\n", "scripts/laptop_device_build.sh": "maintained container\n",
      "tools/laptop_device_build/config": "maintained sysroot\n", "docs/MAINTENANCE.md": "maintained docs\n",
      ".github/workflows/build.yaml": "maintained CI\n",
      "release/ci/docker_build_sp.sh": "maintained legacy CI entrypoint\n",
    }.items():
      self.write(self.local, path, contents)
    self.commit(self.local)
    for url, bare in ((APPLICATION, self.application_bare), (OPENDBC, self.dependency_bare)):
      self.git(self.local, "config", f"url.{bare.as_uri()}.insteadOf", url)
    self.head = self.git(self.local, "rev-parse", "HEAD").stdout.strip()

  def git(self, cwd, *args, success=True):
    result = subprocess.run(["git", *args], cwd=cwd, env=self.env, capture_output=True, text=True)
    self.assertEqual(result.returncode == 0, success, result.stdout + result.stderr)
    return result

  def repo(self, name, branch):
    path = self.root / name
    self.git(self.root, "init", "-b", branch, str(path))
    return path

  def bare(self, repository):
    path = Path(str(repository) + ".git")
    self.git(self.root, "clone", "--bare", str(repository), str(path))
    return path

  def write(self, repository, path, contents):
    target = repository / path
    target.parent.mkdir(parents=True, exist_ok=True)
    target.write_text(contents)

  def commit(self, repository):
    self.git(repository, "add", "-A")
    self.git(repository, "commit", "-m", "fixture")

  def publish(self, repository, bare):
    self.commit(repository)
    self.git(repository, "push", str(bare), BRANCH)

  def sync(self, *args, success=True):
    result = subprocess.run(["bash", "sync-upstream.sh", *args], cwd=self.local, env=self.env, capture_output=True, text=True)
    self.assertEqual(result.returncode == 0, success, result.stdout + result.stderr)
    self.assertEqual(self.git(self.local, "rev-parse", "HEAD").stdout.strip(), self.head)
    return result

  def state(self):
    return (self.git(self.local, "write-tree").stdout,
            self.git(self.local, "status", "--porcelain", "--untracked-files=all").stdout,
            self.git(self.local, "config", "--local", "--list").stdout,
            self.git(self.local, "show-ref").stdout,
            self.git(self.local, "count-objects", "-v").stdout)

  def record_restored_manifests(self, names, *, omit_gitlink=True, omit_empty_dependencies=False):
    originals = {}
    for name in names:
      metadata = json.loads((self.local / name).read_text())
      metadata.update(restored_from="1" * 40, restored_tree="2" * 40, source="restored Sunnypilot archive")
      if omit_gitlink:
        metadata.pop("gitlink", None)
        for dependency in metadata.get("dependencies", {}).values():
          dependency.pop("gitlink", None)
      if omit_empty_dependencies and not metadata.get("dependencies"):
        metadata.pop("dependencies", None)
      # Whitespace and field order are historical bytes, not just JSON semantics.
      payload = (json.dumps(metadata, indent=4, sort_keys=True) + "\n\n").encode()
      (self.local / name).write_bytes(payload)
      originals[name] = payload
    self.commit(self.local)
    self.head = self.git(self.local, "rev-parse", "HEAD").stdout.strip()
    return originals

  def publish_nested_vehicle_pin(self):
    nested = self.repo("nested-stability", "main")
    self.write(nested, "support.txt", "nested pinned source\n")
    self.commit(nested)
    self.git(self.dependency, "submodule", "add", str(self.bare(nested)), "support")
    self.publish(self.dependency, self.dependency_bare)
    vehicle_pin = self.git(self.dependency, "rev-parse", "HEAD").stdout.strip()
    self.git(self.upstream / "opendbc_repo", "fetch", str(self.dependency_bare), BRANCH)
    self.git(self.upstream / "opendbc_repo", "checkout", vehicle_pin)
    # Application and vehicle-only imports must describe the same repository.
    self.git(self.upstream, "config", "--file", ".gitmodules", "submodule.opendbc_repo.url", OPENDBC)
    self.publish(self.upstream, self.application_bare)
    return self.git(self.upstream, "rev-parse", "HEAD").stdout.strip(), vehicle_pin

  def test_preview_and_missing_permission_do_not_change_checkout_index_config_or_refs(self):
    self.write(self.local, "app.txt", "dirty source\n")
    before = self.state()
    result = self.sync("--check")
    self.assertIn(self.application_pin, result.stdout)
    self.assertIn("opendbc_repo/opendbc/example.txt", result.stdout)
    self.sync(success=False)
    self.assertEqual(self.state(), before)
    self.assertFalse((self.local / "sunnypilot-upstream.json").exists())

  def test_main_import_vendors_exact_pin_preserves_tooling_and_never_replays(self):
    self.write(self.dependency, "opendbc/example.txt", "new upstream tip\n")
    self.publish(self.dependency, self.dependency_bare)
    self.write(self.local, "apply_patch.sh", "dirty helper\n")
    self.write(self.local, ".githooks/local", "untracked local hook\n")
    self.sync("--allow")
    self.assertEqual((self.local / "app.txt").read_text(), "Sunnypilot application\n")
    self.assertEqual((self.local / "opendbc_repo/opendbc/example.txt").read_text(), "pinned vehicle\n")
    self.assertFalse((self.local / "obsolete.txt").exists())
    self.assertFalse((self.local / ".gitmodules").exists())
    self.assertFalse((self.local / "opendbc_repo/.git").exists())
    self.assertEqual((self.local / "apply_patch.sh").read_text(), "dirty helper\n")
    self.assertEqual((self.local / "build").read_text(), "maintained build\n")
    self.assertEqual((self.local / "release/ci/docker_build_sp.sh").read_text(), "maintained legacy CI entrypoint\n")
    self.assertEqual((self.local / ".githooks/local").read_text(), "untracked local hook\n")
    self.assertEqual((self.local / "patches/opendbc/invalid.patch").read_text(), "never replay\n")
    self.assertIn(".comma_sysroot/", (self.local / ".gitignore").read_text())
    self.assertEqual(self.git(self.local, "check-attr", "diff", "--", "example.onnx").stdout.strip(), "example.onnx: diff: unset")
    metadata = json.loads((self.local / "sunnypilot-upstream.json").read_text())
    self.assertEqual(metadata["commit"], self.application_pin)
    self.assertEqual(metadata["dependencies"]["opendbc_repo"]["commit"], self.pin)
    self.assertEqual(metadata["dependencies"]["opendbc_repo"]["gitlink"], self.pin)
    self.assertEqual(json.loads((self.local / "opendbc-upstream.json").read_text())["source"], "application pin")
    self.assertFalse(any(row.startswith("160000") for row in self.git(self.local, "ls-files", "--stage").stdout.splitlines()))
    self.assertEqual(self.git(self.local, "show", ":opendbc_repo/opendbc/example.txt").stdout, "pinned vehicle\n")

  def test_vehicle_only_sync_keeps_dirty_application_and_its_staging(self):
    self.write(self.local, "app.txt", "dirty application\n")
    self.git(self.local, "add", "app.txt")
    staged = self.git(self.local, "show", ":app.txt").stdout
    self.sync("--opendbc", "--allow")
    self.assertEqual((self.local / "app.txt").read_text(), "dirty application\n")
    self.assertEqual(self.git(self.local, "show", ":app.txt").stdout, staged)
    self.assertTrue((self.local / "obsolete.txt").exists())
    self.assertEqual((self.local / "opendbc_repo/opendbc/example.txt").read_text(), "pinned vehicle\n")
    self.assertFalse((self.local / "sunnypilot-upstream.json").exists())
    metadata = json.loads((self.local / "opendbc-upstream.json").read_text())
    self.assertEqual(metadata["repository"], OPENDBC)
    self.assertEqual(metadata["commit"], self.pin)

  def test_dirty_source_and_dirty_index_are_refused_before_import(self):
    for staged in (False, True):
      with self.subTest(staged=staged):
        self.write(self.local, "opendbc_repo/opendbc/example.txt", "unsaved vehicle\n")
        if staged:
          self.git(self.local, "add", "opendbc_repo/opendbc/example.txt")
        before = self.state()
        self.sync("--opendbc", "--allow", success=False)
        self.assertEqual(self.state(), before)
        self.assertEqual((self.local / "opendbc_repo/opendbc/example.txt").read_text(), "unsaved vehicle\n")

  def test_ignored_and_untracked_collisions_are_refused(self):
    self.write(self.upstream, "collision.bin", "incoming\n")
    self.publish(self.upstream, self.application_bare)
    self.write(self.local, "collision.bin", "keep private data\n")
    for ignored in (False, True):
      with self.subTest(ignored=ignored):
        if ignored:
          self.write(self.local, ".git/info/exclude", "collision.bin\n")
        before = self.state()
        self.sync("--allow", success=False)
        self.assertEqual(self.state(), before)
        self.assertEqual((self.local / "collision.bin").read_text(), "keep private data\n")

  def test_untracked_directory_contents_block_directory_to_file_replacement(self):
    self.write(self.upstream, "folder", "incoming file\n")
    self.publish(self.upstream, self.application_bare)
    self.write(self.local, "folder/private.txt", "private\n")
    self.sync("--allow", success=False)
    self.assertEqual((self.local / "folder/private.txt").read_text(), "private\n")

  def test_tracked_symlink_to_external_directory_is_replaced_without_touching_external_data(self):
    outside = self.root / "outside"
    self.write(outside, "child.txt", "external data\n")
    (self.local / "link").symlink_to(outside, target_is_directory=True)
    self.commit(self.local)
    self.head = self.git(self.local, "rev-parse", "HEAD").stdout.strip()
    self.write(self.upstream, "link/child.txt", "incoming data\n")
    self.publish(self.upstream, self.application_bare)
    self.sync("--allow")
    self.assertEqual((outside / "child.txt").read_text(), "external data\n")
    self.assertFalse((self.local / "link").is_symlink())
    self.assertEqual((self.local / "link/child.txt").read_text(), "incoming data\n")

  def test_explicit_commit_import_and_repeated_baseline_import(self):
    self.write(self.upstream, "app.txt", "new application\n")
    self.publish(self.upstream, self.application_bare)
    self.sync("--allow", self.application_pin)
    self.assertEqual((self.local / "app.txt").read_text(), "Sunnypilot application\n")
    self.commit(self.local)
    self.head = self.git(self.local, "rev-parse", "HEAD").stdout.strip()
    self.sync(self.application_pin)
    self.assertEqual(self.git(self.local, "diff", "--cached", "--stat").stdout, "")

  def test_application_repeat_preserves_restoration_provenance_and_configuration_bytes(self):
    self.sync("--allow")
    configuration = {
      ".gitignore": "# restored ignore format\n.cache/\n*.o\n",
      ".gitattributes": "# restored binary format\n*.onnx binary\n*.bin binary\n",
    }
    for name, contents in configuration.items():
      self.write(self.local, name, contents)
    originals = self.record_restored_manifests(("sunnypilot-upstream.json", "opendbc-upstream.json"))
    for request in (self.application_pin, BRANCH):
      with self.subTest(request=request):
        self.sync("--allow", request)
        self.assertEqual(self.git(self.local, "diff", "--cached", "--stat").stdout, "")
        for name, payload in originals.items():
          self.assertEqual((self.local / name).read_bytes(), payload)
        for name, contents in configuration.items():
          self.assertEqual((self.local / name).read_text(), contents)

  def test_vehicle_repeat_preserves_original_manifest_with_absent_optional_fields(self):
    self.sync("--opendbc", "--allow")
    originals = self.record_restored_manifests(("opendbc-upstream.json",), omit_empty_dependencies=True)
    for request in (self.pin, BRANCH):
      with self.subTest(request=request):
        self.sync("--opendbc", "--allow", request)
        self.assertEqual(self.git(self.local, "diff", "--cached", "--stat").stdout, "")
        self.assertEqual((self.local / "opendbc-upstream.json").read_bytes(), originals["opendbc-upstream.json"])

  def test_changed_application_dependency_pin_replaces_both_restoration_manifests(self):
    self.sync("--allow")
    self.record_restored_manifests(("sunnypilot-upstream.json", "opendbc-upstream.json"))
    self.write(self.dependency, "opendbc/example.txt", "next pinned vehicle\n")
    self.publish(self.dependency, self.dependency_bare)
    new_pin = self.git(self.dependency, "rev-parse", "HEAD").stdout.strip()
    self.git(self.upstream / "opendbc_repo", "fetch", str(self.dependency_bare), BRANCH)
    self.git(self.upstream / "opendbc_repo", "checkout", new_pin)
    self.publish(self.upstream, self.application_bare)
    self.sync("--allow")
    application = json.loads((self.local / "sunnypilot-upstream.json").read_text())
    vehicle = json.loads((self.local / "opendbc-upstream.json").read_text())
    self.assertEqual(application["commit"], self.git(self.upstream, "rev-parse", "HEAD").stdout.strip())
    self.assertEqual(application["dependencies"]["opendbc_repo"]["commit"], new_pin)
    self.assertEqual(application["dependencies"]["opendbc_repo"]["gitlink"], new_pin)
    self.assertEqual(vehicle["commit"], new_pin)
    self.assertEqual(vehicle["source"], "application pin")
    self.assertNotIn("restored_from", application)
    self.assertNotIn("restored_tree", vehicle)

  def test_changed_vehicle_identity_replaces_stale_restoration_metadata(self):
    self.sync("--opendbc", "--allow")
    self.record_restored_manifests(("opendbc-upstream.json",))
    self.write(self.dependency, "opendbc/example.txt", "new vehicle identity\n")
    self.publish(self.dependency, self.dependency_bare)
    self.sync("--opendbc", "--allow")
    metadata = json.loads((self.local / "opendbc-upstream.json").read_text())
    self.assertEqual(metadata["commit"], self.git(self.dependency, "rev-parse", "HEAD").stdout.strip())
    self.assertEqual(metadata["tree"], self.git(self.dependency, "rev-parse", "HEAD^{tree}").stdout.strip())
    self.assertNotIn("restored_from", metadata)

  def test_same_application_identity_does_not_reuse_wrong_dependency_provenance(self):
    self.sync("--allow")
    expected = json.loads((self.local / "sunnypilot-upstream.json").read_text())
    for field in ("repository", "commit", "tree", "gitlink"):
      with self.subTest(field=field):
        metadata = json.loads(json.dumps(expected))
        metadata["dependencies"]["opendbc_repo"][field] = "wrong dependency identity"
        metadata["restored_from"] = "must not retain stale provenance"
        self.write(self.local, "sunnypilot-upstream.json", json.dumps(metadata, indent=4) + "\n")
        self.commit(self.local)
        self.head = self.git(self.local, "rev-parse", "HEAD").stdout.strip()
        self.sync("--allow", self.application_pin)
        actual = json.loads((self.local / "sunnypilot-upstream.json").read_text())
        self.assertEqual(actual["dependencies"], expected["dependencies"])
        self.assertNotIn("restored_from", actual)

  def test_same_vehicle_identity_checks_nested_dependency_provenance(self):
    nested = self.repo("nested-provenance", "main")
    self.write(nested, "support.txt", "nested identity\n")
    self.commit(nested)
    self.git(self.dependency, "submodule", "add", str(self.bare(nested)), "support")
    self.publish(self.dependency, self.dependency_bare)
    self.sync("--opendbc", "--allow")
    expected = json.loads((self.local / "opendbc-upstream.json").read_text())
    for field in ("commit", "gitlink"):
      with self.subTest(field=field):
        metadata = json.loads(json.dumps(expected))
        metadata["dependencies"]["opendbc_repo/support"][field] = "wrong nested dependency identity"
        metadata["restored_tree"] = "must not retain stale provenance"
        self.write(self.local, "opendbc-upstream.json", json.dumps(metadata, indent=4) + "\n")
        self.commit(self.local)
        self.head = self.git(self.local, "rev-parse", "HEAD").stdout.strip()
        self.sync("--opendbc", "--allow")
        actual = json.loads((self.local / "opendbc-upstream.json").read_text())
        self.assertEqual(actual["dependencies"], expected["dependencies"])
        self.assertNotIn("restored_tree", actual)

  def test_main_vehicle_main_same_nested_pin_preserves_manifest_bytes(self):
    application_pin, vehicle_pin = self.publish_nested_vehicle_pin()
    self.sync("--allow", application_pin)
    vehicle = json.loads((self.local / "opendbc-upstream.json").read_text())
    self.assertIn("opendbc_repo/support", vehicle["dependencies"])
    originals = self.record_restored_manifests(("sunnypilot-upstream.json", "opendbc-upstream.json"))
    for arguments in (("--opendbc", "--allow", vehicle_pin), ("--allow", application_pin)):
      with self.subTest(arguments=arguments):
        self.sync(*arguments)
        self.assertEqual(self.git(self.local, "diff", "--cached", "--stat").stdout, "")
        for name, payload in originals.items():
          self.assertEqual((self.local / name).read_bytes(), payload)

  def test_same_snapshot_changed_dependency_path_set_replaces_stale_provenance(self):
    application_pin, vehicle_pin = self.publish_nested_vehicle_pin()
    self.sync("--allow", application_pin)
    for vehicle_only in (False, True):
      name = "opendbc-upstream.json" if vehicle_only else "sunnypilot-upstream.json"
      expected = json.loads((self.local / name).read_text())
      for change in ("missing", "extra"):
        with self.subTest(vehicle_only=vehicle_only, change=change):
          metadata = json.loads(json.dumps(expected))
          if change == "missing":
            metadata["dependencies"].pop("opendbc_repo/support")
          else:
            metadata["dependencies"]["obsolete/dependency"] = metadata["dependencies"]["opendbc_repo/support"]
          metadata["restored_from"] = "must not retain stale dependency paths"
          self.write(self.local, name, json.dumps(metadata, indent=4) + "\n")
          self.commit(self.local)
          self.head = self.git(self.local, "rev-parse", "HEAD").stdout.strip()
          arguments = ("--opendbc", "--allow", vehicle_pin) if vehicle_only else ("--allow", application_pin)
          self.sync(*arguments)
          actual = json.loads((self.local / name).read_text())
          self.assertEqual(actual["dependencies"], expected["dependencies"])
          self.assertNotIn("restored_from", actual)

  def test_next_snapshot_imports_new_upstream_ignore_and_attribute_rules(self):
    self.sync("--allow")
    self.write(self.local, ".gitignore", "# restored format\nold-local-rule\n")
    self.write(self.local, ".gitattributes", "# restored format\n*.old binary\n")
    self.record_restored_manifests(("sunnypilot-upstream.json", "opendbc-upstream.json"))
    self.write(self.upstream, ".gitignore", "new-upstream-rule\n*.o\n")
    self.write(self.upstream, ".gitattributes", "*.new -text\n")
    self.publish(self.upstream, self.application_bare)
    self.sync("--allow")
    ignore = (self.local / ".gitignore").read_text()
    attributes = (self.local / ".gitattributes").read_text()
    self.assertIn("new-upstream-rule\n", ignore)
    self.assertIn(".comma_sysroot/", ignore)
    self.assertNotIn("old-local-rule", ignore)
    self.assertIn("*.new -text\n", attributes)
    self.assertNotIn("*.old", attributes)
    self.assertNotIn("filter=lfs", attributes)

  def test_same_snapshot_does_not_retain_lfs_enabled_attributes(self):
    self.sync("--allow")
    self.write(self.local, ".gitattributes", "*.bin filter=lfs diff=lfs merge=lfs -text\n")
    self.record_restored_manifests(("sunnypilot-upstream.json", "opendbc-upstream.json"))
    self.sync("--allow", self.application_pin)
    self.assertNotIn("filter=lfs", (self.local / ".gitattributes").read_text())

  def test_existing_index_lock_refuses_import_without_overwriting_source(self):
    self.write(self.local, ".git/index.lock", "another operation\n")
    result = self.sync("--allow", success=False)
    self.assertIn("index.lock", result.stderr)
    self.assertEqual((self.local / "app.txt").read_text(), "custom application\n")
    self.assertEqual((self.local / ".git/index.lock").read_text(), "another operation\n")

  def test_failed_install_rolls_back_source_index_and_replaced_symlink(self):
    outside = self.root / "outside"
    self.write(outside, "keep.txt", "external data\n")
    (self.local / "link").symlink_to(outside, target_is_directory=True)
    script = self.local / "tools/upstream/sync.py"
    injected = '''
original_copy2 = shutil.copy2
def fail_new_file(source, destination, **kwargs):
  if "/stage/" in str(source) and str(destination).endswith("/zzz.txt"):
    raise OSError("simulated installation failure")
  return original_copy2(source, destination, **kwargs)
shutil.copy2 = fail_new_file
'''
    script.write_text(script.read_text().replace("\nAPPLICATION_URL =", injected + "\nAPPLICATION_URL ="))
    self.commit(self.local)
    self.head = self.git(self.local, "rev-parse", "HEAD").stdout.strip()
    self.write(self.upstream, "link/nested/child.txt", "incoming data\n")
    self.write(self.upstream, "zzz.txt", "fail here\n")
    self.publish(self.upstream, self.application_bare)
    before = self.git(self.local, "write-tree").stdout
    result = self.sync("--allow", success=False)
    self.assertIn("simulated installation failure", result.stderr)
    self.assertEqual(self.git(self.local, "write-tree").stdout, before)
    self.assertEqual((self.local / "app.txt").read_text(), "custom application\n")
    self.assertEqual(os.readlink(self.local / "link"), str(outside))
    self.assertEqual((outside / "keep.txt").read_text(), "external data\n")
    self.assertFalse((self.local / "sunnypilot-upstream.json").exists())
    self.assertFalse((self.local / ".git/index.lock").exists())

  def test_source_symlink_and_executable_modes_are_preserved(self):
    executable = self.upstream / "entrypoint"
    executable.write_text("#!/bin/sh\nexit 0\n")
    executable.chmod(0o755)
    (self.upstream / "opendbc").symlink_to("opendbc_repo/opendbc")
    self.publish(self.upstream, self.application_bare)
    self.sync("--allow")
    self.assertEqual(os.readlink(self.local / "opendbc"), "opendbc_repo/opendbc")
    self.assertTrue((self.local / "entrypoint").stat().st_mode & 0o111)
    self.assertIn("120000", self.git(self.local, "ls-files", "--stage", "opendbc").stdout)

  def test_relative_dependency_urls_resolve_against_the_upstream_repository(self):
    self.git(self.upstream, "config", "--file", ".gitmodules", "submodule.opendbc_repo.url", "../dependency.git")
    self.publish(self.upstream, self.application_bare)
    relative = "https://github.com/sunnypilot/dependency.git"
    self.git(self.local, "config", f"url.{self.dependency_bare.as_uri()}.insteadOf", relative)
    self.sync("--allow")
    metadata = json.loads((self.local / "sunnypilot-upstream.json").read_text())
    self.assertEqual(metadata["dependencies"]["opendbc_repo"]["repository"], relative)
    self.assertEqual((self.local / "opendbc_repo/opendbc/example.txt").read_text(), "pinned vehicle\n")

  def test_nested_dependencies_are_recursively_vendored_at_their_pins(self):
    nested = self.repo("nested", "main")
    self.write(nested, "support.txt", "nested pin\n")
    self.commit(nested)
    pin = self.git(nested, "rev-parse", "HEAD").stdout.strip()
    nested_bare = self.bare(nested)
    self.git(self.dependency, "submodule", "add", str(nested_bare), "support")
    self.publish(self.dependency, self.dependency_bare)
    self.sync("--opendbc", "--allow")
    self.assertEqual((self.local / "opendbc_repo/support/support.txt").read_text(), "nested pin\n")
    metadata = json.loads((self.local / "opendbc-upstream.json").read_text())
    self.assertEqual(metadata["dependencies"]["opendbc_repo/support"]["commit"], pin)
    self.assertFalse((self.local / "opendbc_repo/.gitmodules").exists())

  def test_next_snapshot_removes_obsolete_source_and_keeps_noncolliding_ignored_cache(self):
    self.sync("--allow")
    self.commit(self.local)
    self.head = self.git(self.local, "rev-parse", "HEAD").stdout.strip()
    self.write(self.local, ".git/info/exclude", "cache.bin\n")
    self.write(self.local, "cache.bin", "local cache\n")
    (self.upstream / "app.txt").unlink()
    self.write(self.upstream, "next.txt", "next source\n")
    self.publish(self.upstream, self.application_bare)
    self.sync("--allow")
    self.assertFalse((self.local / "app.txt").exists())
    self.assertEqual((self.local / "next.txt").read_text(), "next source\n")
    self.assertEqual((self.local / "cache.bin").read_text(), "local cache\n")

  def add_lfs_asset(self, payload, available):
    oid = hashlib.sha256(payload).hexdigest()
    self.write(self.upstream, "asset.bin", f"version https://git-lfs.github.com/spec/v1\noid sha256:{oid}\nsize {len(payload)}\n")
    self.write(self.upstream, ".gitattributes", "*.bin filter=lfs diff=lfs merge=lfs -text\n")
    # The fixture stages pointer bytes without relying on hooks or local LFS filters.
    self.git(self.upstream, "-c", "filter.lfs.clean=", "-c", "filter.lfs.process=", "-c", "filter.lfs.required=false", "add", "-A")
    self.git(self.upstream, "-c", "core.hooksPath=/dev/null", "commit", "-m", "LFS fixture")
    self.git(self.upstream, "-c", "core.hooksPath=/dev/null", "push", str(self.application_bare), BRANCH)
    if available:
      target = self.application_bare / "lfs/objects" / oid[:2] / oid[2:4] / oid
      target.parent.mkdir(parents=True, exist_ok=True)
      target.write_bytes(payload)

  def test_lfs_payloads_are_materialized_as_normal_git_blobs_without_hooks(self):
    if subprocess.run(["git", "lfs", "version"], env=self.env, capture_output=True).returncode:
      self.skipTest("git-lfs is not installed")
    payload = b"hydrated asset\0\xff\n"
    self.add_lfs_asset(payload, True)
    hook = self.local / ".git/hooks/post-index-change"
    hook.write_text("#!/bin/sh\ntouch hook-ran\n")
    hook.chmod(0o755)
    self.sync("--allow")
    self.assertEqual((self.local / "asset.bin").read_bytes(), payload)
    self.assertNotIn("filter=lfs", (self.local / ".gitattributes").read_text())
    self.assertIn("*.bin  -diff -merge -text", (self.local / ".gitattributes").read_text())
    result = subprocess.run(["git", "show", ":asset.bin"], cwd=self.local, env=self.env, capture_output=True, check=True)
    self.assertEqual(result.stdout, payload)
    self.assertFalse((self.local / "hook-ran").exists())

  def test_missing_lfs_payload_leaves_source_and_index_untouched(self):
    if subprocess.run(["git", "lfs", "version"], env=self.env, capture_output=True).returncode:
      self.skipTest("git-lfs is not installed")
    self.add_lfs_asset(b"unavailable payload\n", False)
    before = self.state()
    self.sync("--allow", success=False)
    self.assertEqual(self.state(), before)
    self.assertEqual((self.local / "app.txt").read_text(), "custom application\n")


if __name__ == "__main__":
  unittest.main()
