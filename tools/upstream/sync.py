#!/usr/bin/env python3
"""Stage vendored Sunnypilot snapshots using disposable Git/LFS object caches."""
import argparse
import configparser
import hashlib
import json
import os
from pathlib import Path, PurePosixPath
import posixpath
import re
import shutil
import subprocess
import sys
import tempfile
from urllib.parse import urljoin, urlparse


APPLICATION_URL = "https://github.com/sunnypilot/sunnypilot.git"
OPENDBC_URL = "https://github.com/sunnypilot/opendbc.git"
BRANCH = "hkg-angle-steering-2025"
APPLICATION_MANIFEST = "sunnypilot-upstream.json"
OPENDBC_MANIFEST = "opendbc-upstream.json"
PRESERVE = (
  "AGENTS.md", "sync-upstream.sh", "update.sh", "apply_patch.sh", "apply_patch_conflicts.sh", "fix_patch.sh",
  "create_patch.sh", "create_patch_manual.sh", "update_patch.sh", "patches", "tools/opendbc-patches", "tools/patches",
  "tools/upstream", "tools/maintenance", "tools/ci/sync_ev9_branch.sh", "tools/ci/tests", ".github/workflows",
  "release/ci/publish.sh", ".githooks", "build", "scripts/laptop_device_build.sh", "tools/laptop_device_build",
  "docs/how-to/laptop-device-build.md", "docs/MAINTENANCE.md", "docs/EV9_BEHAVIOR.md", "docs/RECENT_DRIVE_REVIEW.md",
  "docs/C3X_UPDATE_WORKFLOW.md", APPLICATION_MANIFEST, OPENDBC_MANIFEST, "starpilot-upstream.json",
)
RAW_OPTIONS = (
  "-c", "core.hooksPath=/dev/null", "-c", "core.attributesFile=/dev/null", "-c", "filter.lfs.process=",
  "-c", "filter.lfs.smudge=", "-c", "filter.lfs.clean=", "-c", "filter.lfs.required=false",
)
LFS_VERSION = b"version https://git-lfs.github.com/spec/v1\n"
BINARY_ATTRIBUTES = """# Materialized upstream assets are ordinary Git blobs, with binary diffs.
*.onnx binary
*.pkl binary
*.pkl.chunk* binary
*.jpg binary
*.png binary
*.gif binary
*.ttf binary
*.otf binary
*.wav binary
*.a binary
*.so binary
*.so.* binary
*.dylib binary
*.bin binary
*.bin.signed binary
system/hardware/tici/updater_weston binary
system/hardware/tici/updater_magic binary
"""


def under(path, parent):
  return path == parent or path.startswith(parent + "/")


def valid_path(path):
  parsed = PurePosixPath(path)
  if not path or parsed.is_absolute() or any(p.casefold() in (".", "..", ".git") for p in path.split("/")):
    raise ValueError(f"Unsafe upstream path: {path!r}")
  return path


def run(command, *, cwd=None, env=None, data=None):
  result = subprocess.run(command, cwd=cwd, env=env, input=data, capture_output=True)
  if result.returncode:
    raise ValueError(result.stderr.decode(errors="replace").strip() or f"Command failed: {command[0]}")
  return result.stdout


def git(root, *args, env=None, data=None):
  environment = dict(os.environ if env is None else env, GIT_OPTIONAL_LOCKS="0")
  return run(["git", *RAW_OPTIONS, "-C", str(root), *args], env=environment, data=data)


def tree_entries(git_call, ref):
  entries = {}
  for row in git_call("ls-tree", "-rz", ref).split(b"\0"):
    if row:
      header, encoded_path = row.split(b"\t", 1)
      mode, kind, oid = header.decode().split()
      path = valid_path(os.fsdecode(encoded_path))
      entries[path] = (mode, kind, oid)
  return entries


def relative_url(parent, child):
  if not child.startswith(("./", "../")):
    return child
  if urlparse(parent).scheme:
    return urljoin(parent.rstrip("/") + "/", child)
  if ":" in parent and not parent.startswith("/"):
    host, path = parent.split(":", 1)
    return host + ":" + posixpath.normpath(posixpath.join(path, child))
  return os.path.normpath(os.path.join(parent, child))


class Snapshot:
  def __init__(self, root, temporary):
    self.root = root
    self.cache = temporary / "objects.git"
    git(root, "init", "--bare", str(self.cache))
    self.environment = dict(os.environ, GIT_LFS_SKIP_SMUDGE="1")
    self.config = []
    # Respect the checkout's URL rewrites (also used by offline fixtures).
    aliases = subprocess.run(["git", "-C", str(root), "config", "--null", "--get-regexp", r"^url\..*\.insteadof$"], capture_output=True)
    if aliases.returncode not in (0, 1):
      raise ValueError(aliases.stderr.decode(errors="replace"))
    for row in aliases.stdout.split(b"\0"):
      if row:
        key, value = row.split(b"\n", 1)
        self.config.extend(("-c", os.fsdecode(key) + "=" + os.fsdecode(value)))
    self.downloads = {}
    self.dependencies = {}
    self.imports = {}
    self.git("config", "lfs.fetchrecentalways", "false")

  def git(self, *args, data=None):
    # Empty storage selects this bare cache's default lfs directory, overriding
    # user/global storage without an absolute path leaking into file remotes.
    return run(["git", *RAW_OPTIONS, *self.config, "-c", "lfs.storage=", "--git-dir=" + str(self.cache), *args],
               cwd=self.root, env=self.environment, data=data)

  def fetch(self, repository, ref):
    key = (repository, ref)
    if key not in self.downloads:
      remote = "source" + str(len(self.downloads))
      self.git("remote", "add", remote, repository)
      self.git("fetch", "--no-tags", "--depth=1", remote, ref)
      commit = self.git("rev-parse", "FETCH_HEAD^{commit}").decode().strip()
      tree = self.git("rev-parse", commit + "^{tree}").decode().strip()
      self.downloads[key] = (remote, commit, tree)
    return self.downloads[key]

  def blob(self, oid):
    return self.git("cat-file", "blob", oid)

  def store(self, data):
    return self.git("hash-object", "-w", "--stdin", data=data).decode().strip()

  def small_blobs(self, entries):
    objects = sorted({oid for mode, kind, oid in entries.values() if kind == "blob"})
    info = self.git("cat-file", "--batch-check", data="".join(oid + "\n" for oid in objects).encode())
    small = [row.split()[0].decode() for row in info.splitlines() if int(row.split()[2]) <= 1024]
    output = self.git("cat-file", "--batch", data="".join(oid + "\n" for oid in small).encode())
    result = {}
    offset = 0
    for oid in small:
      end = output.index(b"\n", offset)
      size = int(output[offset:end].split()[2])
      result[oid] = output[end + 1:end + 1 + size]
      offset = end + size + 2
    return result

  def materialize(self, repository, ref, prefix="", ancestors=()):
    remote, commit, tree = self.fetch(repository, ref)
    identity = (repository, commit)
    if identity in ancestors:
      raise ValueError(f"Recursive submodule reference at {prefix}")
    self.imports[prefix] = {"repository": repository, "commit": commit, "tree": tree}
    entries = tree_entries(self.git, commit)
    small = self.small_blobs(entries)
    pointers = {}
    for path, (mode, kind, oid) in entries.items():
      data = small.get(oid, b"")
      if kind == "blob" and mode != "120000" and data.startswith(LFS_VERSION):
        match = re.search(rb"\noid sha256:([0-9a-f]{64})\nsize ([0-9]+)\n?", data)
        if not match:
          raise ValueError(f"Malformed Git LFS pointer: {prefix}{path}")
        pointers[path] = (match[1].decode(), int(match[2]))
    if pointers:
      options = []
      if ".lfsconfig" in entries:
        config = configparser.RawConfigParser()
        config.read_string(self.blob(entries[".lfsconfig"][2]).decode())
        if config.has_option("lfs", "url"):
          options = ["-c", "lfs.url=" + config.get("lfs", "url")]
      self.git(*options, "lfs", "fetch", "--include=", "--exclude=", remote, commit)
      for path, (oid, size) in pointers.items():
        payload = self.cache / "lfs" / "objects" / oid[:2] / oid[2:4] / oid
        if not payload.is_file() or payload.stat().st_size != size:
          raise ValueError(f"Missing Git LFS payload: {prefix}{path}")
        digest = hashlib.sha256()
        with payload.open("rb") as source:
          for chunk in iter(lambda: source.read(1024 * 1024), b""):
            digest.update(chunk)
        if digest.hexdigest() != oid:
          raise ValueError(f"Invalid Git LFS payload: {prefix}{path}")
        stored = self.git("hash-object", "-w", "--no-filters", str(payload)).decode().strip()
        mode, kind, _ = entries[path]
        entries[path] = (mode, kind, stored)
    modules = {}
    if ".gitmodules" in entries:
      config = configparser.RawConfigParser()
      config.read_string(self.blob(entries[".gitmodules"][2]).decode())
      for section in config.sections():
        if section.startswith("submodule "):
          path = valid_path(config.get(section, "path"))
          modules[path] = relative_url(repository, config.get(section, "url"))
    result = {}
    for path, entry in entries.items():
      mode, kind, oid = entry
      destination = valid_path(prefix + path)
      if kind == "commit":
        if path not in modules:
          raise ValueError(f"No .gitmodules URL for gitlink {destination}")
        children = self.materialize(modules[path], oid, destination + "/", (*ancestors, identity))
        self.dependencies[destination] = dict(self.imports[destination + "/"], gitlink=oid)
        result.update(children)
      elif path not in (".gitmodules", ".lfsconfig"):
        if kind != "blob" or mode not in ("100644", "100755", "120000"):
          raise ValueError(f"Unsupported upstream entry {destination}: {mode} {kind}")
        # Hydrated assets stay ordinary Git blobs on future edits/commits too.
        if path == ".gitattributes" or path.endswith("/.gitattributes"):
          data = self.blob(oid).decode("utf-8", errors="surrogateescape")
          data = re.sub(r"(?<!\S)filter=lfs(?=\s|$)", "", data)
          data = re.sub(r"(?<!\S)diff=lfs(?=\s|$)", "-diff", data)
          data = re.sub(r"(?<!\S)merge=lfs(?=\s|$)", "-merge", data)
          entry = (mode, kind, self.store(data.encode("utf-8", errors="surrogateescape")))
        if destination == ".gitignore":
          data = self.blob(entry[2]).decode("utf-8", errors="surrogateescape")
          data += "\n# Local Intelli maintenance/build caches\n.comma_sysroot/\n.cache/\n.venv*/\n.host_runtime/\ncompiledmodels/\n"
          entry = (mode, kind, self.store(data.encode("utf-8", errors="surrogateescape")))
        result[destination] = entry
    return result


def preserved(path):
  return any(under(path, parent) for parent in PRESERVE)


def index_entries(root):
  entries = {}
  for row in git(root, "ls-files", "--stage", "-z").split(b"\0"):
    if row:
      header, path = row.split(b"\t", 1)
      mode, oid, stage = header.decode().split()
      if stage != "0":
        raise ValueError("Finish resolving index conflicts before syncing.")
      entries[os.fsdecode(path)] = (mode, "commit" if mode == "160000" else "blob", oid)
  return entries


def validate_layout(entries):
  for path in entries:
    parts = path.split("/")
    for length in range(1, len(parts)):
      parent = "/".join(parts[:length])
      if parent in entries:
        raise ValueError(f"Incoming file {parent} conflicts with preserved path {path}")


def safety(root, current, incoming, scope):
  dirty = set()
  for command in (("diff", "--name-only", "-z"), ("diff", "--cached", "--name-only", "-z")):
    dirty.update(os.fsdecode(path) for path in git(root, *command).split(b"\0") if path and scope(os.fsdecode(path)))
  if dirty:
    raise ValueError("Save application/index changes before syncing:\n" + "\n".join(sorted(dirty)))
  links = [path for path, entry in current.items() if scope(path) and entry[0] == "160000"]
  if links:
    raise ValueError("Convert existing gitlinks to vendored files before syncing:\n" + "\n".join(links))
  paths = set(incoming)
  directories = {"/".join(path.split("/")[:i]) for path in paths for i in range(1, len(path.split("/")))}
  conflicts = []
  for encoded in git(root, "ls-files", "--others", "-z").split(b"\0"):
    if encoded:
      path = os.fsdecode(encoded).rstrip("/")
      if not scope(path):
        continue
      parents = ["/".join(path.split("/")[:i]) for i in range(1, len(path.split("/")))]
      if path in paths or path in directories or any(parent in paths for parent in parents):
        conflicts.append(path)
  if conflicts:
    raise ValueError("Untracked or ignored files would be overwritten:\n" + "\n".join(conflicts))


def pack_objects(root, snapshot, entries):
  objects = "".join(oid + "\n" for oid in sorted({entry[2] for entry in entries.values()})).encode()
  producer = subprocess.Popen(["git", "--git-dir=" + str(snapshot.cache), "pack-objects", "--stdout"],
                              stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
  producer.stdin.write(objects)
  producer.stdin.close()
  consumer = subprocess.run(["git", *RAW_OPTIONS, "-C", str(root), "index-pack", "--stdin"],
                            stdin=producer.stdout, capture_output=True)
  producer.stdout.close()
  errors = producer.stderr.read()
  status = producer.wait()
  if status or consumer.returncode:
    raise ValueError((errors + consumer.stderr).decode(errors="replace"))


def install(root, incoming, current, candidate_index, snapshot, temporary, initial_index):
  changed = {path for path, entry in incoming.items() if current.get(path) != entry}
  removed = set(current) - set(incoming)
  stage = temporary / "stage"
  stage.mkdir()
  objects = Path(git(root, "rev-parse", "--git-path", "objects").decode().strip())
  if not objects.is_absolute():
    objects = root / objects
  environment = dict(os.environ, GIT_INDEX_FILE=str(candidate_index), GIT_OBJECT_DIRECTORY=str(snapshot.cache / "objects"),
                     GIT_ALTERNATE_OBJECT_DIRECTORIES=str(objects))
  git(root, "checkout-index", "--prefix=" + str(stage) + "/", "-z", "--stdin", env=environment,
      data=b"".join(os.fsencode(path) + b"\0" for path in sorted(changed)))
  index = Path(git(root, "rev-parse", "--git-path", "index").decode().strip())
  if not index.is_absolute():
    index = root / index
  lock = Path(str(index) + ".lock")
  backup = temporary / "backup"
  backup.mkdir()
  previous = {}
  # Fail before touching files if another Git operation already owns the index.
  with lock.open("xb") as destination:
    destination.write(candidate_index.read_bytes())
  affected = removed | changed
  touched = set()
  try:
    if index.read_bytes() != initial_index:
      raise ValueError("The index changed while preparing the snapshot; retry after saving those changes.")
    for path in sorted(affected & set(current)):
      source = root / path
      if source.is_symlink() or source.is_file():
        saved = backup / path
        saved.parent.mkdir(parents=True, exist_ok=True)
        shutil.copy2(source, saved, follow_symlinks=False)
        previous[path] = saved
      else:
        previous[path] = None
    for path in sorted(affected & set(current), key=lambda p: (-p.count("/"), p)):
      target = root / path
      if target.is_symlink() or target.is_file():
        target.unlink()
        touched.add(path)
      parent = target.parent
      while parent != root:
        try:
          parent.rmdir()
        except OSError:
          break
        parent = parent.parent
    for path in sorted(changed):
      target = root / path
      if target.is_dir():
        target.rmdir()
      target.parent.mkdir(parents=True, exist_ok=True)
      shutil.copy2(stage / path, target, follow_symlinks=False)
      touched.add(path)
    os.replace(lock, index)
  except BaseException:
    for path in sorted(touched, key=lambda p: (-p.count("/"), p)):
      target = root / path
      if target.is_symlink() or target.is_file():
        target.unlink()
      try:
        target.rmdir()
      except OSError:
        pass
      parent = target.parent
      while parent != root:
        try:
          parent.rmdir()
        except OSError:
          break
        parent = parent.parent
    for path, saved in sorted(previous.items()):
      if saved is not None and path in touched:
        target = root / path
        target.parent.mkdir(parents=True, exist_ok=True)
        shutil.copy2(saved, target, follow_symlinks=False)
    raise
  finally:
    lock.unlink(missing_ok=True)


def main():
  parser = argparse.ArgumentParser(description="Preview/stage Sunnypilot snapshots with exact vendored dependency pins.")
  parser.add_argument("--check", action="store_true", help="preview only; fetch into a disposable cache")
  parser.add_argument("--allow", action="store_true", help="allow importing a new upstream snapshot")
  parser.add_argument("--opendbc", action="store_true", help="sync only opendbc_repo from Sunnypilot opendbc")
  parser.add_argument("ref", nargs="?", default=BRANCH, help="branch, tag or commit (default: %(default)s)")
  args = parser.parse_args()
  root = Path(__file__).resolve().parents[2]
  for state in ("MERGE_HEAD", "rebase-merge", "rebase-apply", "CHERRY_PICK_HEAD", "REVERT_HEAD"):
    path = Path(git(root, "rev-parse", "--git-path", state).decode().strip())
    if not path.is_absolute():
      path = root / path
    if path.exists():
      raise ValueError("Finish the current merge/rebase/cherry-pick before syncing.")
  current = index_entries(root)
  index_path = Path(git(root, "rev-parse", "--git-path", "index").decode().strip())
  if not index_path.is_absolute():
    index_path = root / index_path
  initial_index = index_path.read_bytes()
  with tempfile.TemporaryDirectory(prefix="sunnypilot-snapshot-") as directory:
    temporary = Path(directory)
    snapshot = Snapshot(root, temporary)
    repository = OPENDBC_URL if args.opendbc else APPLICATION_URL
    source = snapshot.materialize(repository, args.ref, "opendbc_repo/" if args.opendbc else "")
    identity = snapshot.imports["opendbc_repo/" if args.opendbc else ""]
    manifest = OPENDBC_MANIFEST if args.opendbc else APPLICATION_MANIFEST
    provenance = dict(identity, branch=BRANCH, requested_ref=args.ref, legacy_patches_applied=False)
    if args.opendbc:
      provenance["source"] = "opendbc sync"
      provenance["dependencies"] = snapshot.dependencies
      source[manifest] = ("100644", "blob", snapshot.store((json.dumps(provenance, indent=2) + "\n").encode()))

      def scope(path):
        return under(path, "opendbc_repo") or path == OPENDBC_MANIFEST
    else:
      source = {path: entry for path, entry in source.items() if not preserved(path)}
      attributes = snapshot.blob(source[".gitattributes"][2]).rstrip() + b"\n\n" if ".gitattributes" in source else b""
      source[".gitattributes"] = ("100644", "blob", snapshot.store(attributes + BINARY_ATTRIBUTES.encode()))
      provenance["dependencies"] = snapshot.dependencies
      source[manifest] = ("100644", "blob", snapshot.store((json.dumps(provenance, indent=2) + "\n").encode()))
      if "opendbc_repo" in snapshot.dependencies:
        vehicle = dict(snapshot.dependencies["opendbc_repo"], branch=BRANCH, source="application pin", legacy_patches_applied=False)
        source[OPENDBC_MANIFEST] = ("100644", "blob", snapshot.store((json.dumps(vehicle, indent=2) + "\n").encode()))

      def scope(path):
        return not preserved(path) or path in (APPLICATION_MANIFEST, OPENDBC_MANIFEST)
    candidate = {path: entry for path, entry in current.items() if not scope(path)} | source
    validate_layout(candidate)
    print(f"{'opendbc' if args.opendbc else 'Sunnypilot'} snapshot: {identity['commit']}")
    print(f"Pinned dependencies: {len(snapshot.dependencies)}")
    # All preview objects/index files live outside the worktree and its Git directory.
    index = temporary / "candidate-index"
    objects = Path(git(root, "rev-parse", "--git-path", "objects").decode().strip())
    if not objects.is_absolute():
      objects = root / objects
    environment = dict(os.environ, GIT_INDEX_FILE=str(index), GIT_OBJECT_DIRECTORY=str(snapshot.cache / "objects"),
                       GIT_ALTERNATE_OBJECT_DIRECTORIES=str(objects))
    records = b"".join(f"{entry[0]} {entry[2]}\t".encode() + os.fsencode(path) + b"\0" for path, entry in sorted(candidate.items()))
    git(root, "update-index", "-z", "--index-info", env=environment, data=records)
    tree = git(root, "write-tree", env=environment).decode().strip()
    print(git(root, "diff", "--stat", "HEAD", tree, env=environment).decode(), end="")
    if args.check:
      return
    if not args.allow:
      previous = {}
      if (root / manifest).is_file():
        previous = json.loads((root / manifest).read_text())
      if previous.get("commit") != identity["commit"] or previous.get("tree") != identity["tree"]:
        raise ValueError("New upstream snapshot available. Use --allow to import it, or --check to preview.")
    safety(root, current, source, scope)
    scoped_current = {path: entry for path, entry in current.items() if scope(path)}
    pack_objects(root, snapshot, source)
    # Object transfer may be lengthy; catch edits made while it was running.
    safety(root, current, source, scope)
    install(root, source, scoped_current, index, snapshot, temporary, initial_index)
    print("Snapshot staged. No patches replayed, commits created or branches pushed.")


if __name__ == "__main__":
  try:
    main()
  except (ValueError, OSError, configparser.Error) as error:
    print(str(error), file=sys.stderr)
    sys.exit(1)
