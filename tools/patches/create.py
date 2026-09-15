#!/usr/bin/env python3
"""Export forward patches from the staged index without changing source files."""
import argparse
import os
from pathlib import Path, PurePosixPath
import stat
import subprocess
import sys
import tempfile


ROOT = Path(__file__).resolve().parents[2]
# Keep maintenance and archived patches out of application patch exports.
MAINTENANCE = (
  'AGENTS.md', 'sync-upstream.sh', 'update.sh', 'apply_patch.sh', 'apply_patch_conflicts.sh', 'fix_patch.sh',
  'create_patch.sh', 'create_patch_manual.sh', 'update_patch.sh', 'patches', 'tools/patches', 'tools/opendbc-patches',
  'tools/ci/sync_ev9_branch.sh', 'tools/ci/tests', '.github/workflows', 'release/ci/publish.sh',
  'docs/STARPILOT_MIGRATION.md', 'docs/RECENT_DRIVE_REVIEW.md', 'starpilot-upstream.json',
)
SUFFIXES = ('.patch', '.patch.temp-disabled', '.patch.disabled', '.patch.OUTDATED.disabled')


def git(*args: str, stdin: bytes | None = None, env: dict | None = None) -> bytes:
  result = subprocess.run(['git', '-C', str(ROOT), *args], input=stdin, env=env, capture_output=True)
  if result.returncode:
    raise ValueError(result.stderr.decode(errors='replace').strip() or 'Git command failed.')
  return result.stdout


def relative_path(value: str) -> PurePosixPath:
  path = PurePosixPath(value)
  if path.is_absolute() or '..' in path.parts or value.startswith(('-', ':')):
    raise ValueError(f'Expected a relative path without traversal: {value}')
  return path


def patch_destination(name: str, update: bool) -> tuple[Path, bool]:
  path = relative_path(name)
  if path.parts and path.parts[0] == 'patches':
    path = PurePosixPath(*path.parts[1:])
  vehicle = len(path.parts) == 2 and path.parts[0] == 'opendbc'
  if not path.parts or (len(path.parts) != 1 and not vehicle) or path.name.startswith('.'):
    raise ValueError('Use a patch name or opendbc/<name>; nested archive paths are not patch destinations.')
  filename = path.name
  suffix = next((s for s in SUFFIXES if filename.endswith(s)), None)
  if suffix:
    stem = filename[:-len(suffix)]
  else:
    if '.patch.' in filename:
      raise ValueError(f'Unrecognized patch suffix: {filename}')
    stem, suffix = filename, '.patch'
  if not stem:
    raise ValueError('Patch name is empty.')
  directory = ROOT / 'patches' / ('opendbc' if vehicle else '')
  if directory.is_symlink() or (ROOT / 'patches').is_symlink():
    raise ValueError('Patch directories must not be symlinks.')
  existing = [directory / (stem + s) for s in SUFFIXES if os.path.lexists(directory / (stem + s))]
  if any(p.is_symlink() or not p.is_file() for p in existing):
    raise ValueError('Patch destinations must be regular files, not symlinks or directories.')
  if not update:
    if existing:
      raise ValueError(f'Patch already exists: {existing[0].relative_to(ROOT)}. Use update_patch.sh or a different name.')
    return directory / (stem + suffix), vehicle
  explicit_disabled = suffix != '.patch'
  if explicit_disabled:
    selected = directory / (stem + suffix)
    if selected not in existing:
      raise ValueError(f'No patch exists at {selected.relative_to(ROOT)}.')
    return selected, vehicle
  if len(existing) != 1:
    raise ValueError('Expected exactly one existing patch; specify its full disabled suffix if the name is ambiguous.')
  return existing[0], vehicle


def source_paths(paths: list[str], vehicle: bool) -> list[str]:
  selected = []
  for value in paths:
    path = relative_path(value)
    selected.append(':(top,literal)' + str(PurePosixPath('opendbc_repo', path) if vehicle else path))
  if not selected:
    selected = ['opendbc_repo' if vehicle else '.']
  return selected + [':(top,exclude)' + path for path in MAINTENANCE]


def diff_options(vehicle: bool) -> list[str]:
  options = ['--cached', '--binary', '--full-index', '--no-renames', '--no-ext-diff', '--no-textconv', '--no-color',
             '--src-prefix=a/', '--dst-prefix=b/']
  if vehicle:
    options.append('--relative=opendbc_repo')
  return options


def patch_paths(output: Path, vehicle: bool) -> list[str]:
  # git apply's numstat reports rename destinations only; reverse includes sources.
  paths = set()
  for direction in ([], ['--reverse']):
    stats = git('apply', '--numstat', '-z', *direction, *(['--directory=opendbc_repo'] if vehicle else []), str(output))
    for record in stats.split(b'\0'):
      if record:
        name = os.fsdecode(record.split(b'\t', 2)[2])
        path = PurePosixPath(name)
        if path.is_absolute() or '..' in path.parts:
          raise ValueError(f'Unsafe patch path: {name}')
        paths.add(name)
  if not paths:
    raise ValueError('The existing patch contains no file changes.')
  return sorted(paths)


def automatic_update(output: Path, vehicle: bool, paths: list[str]) -> bytes:
  try:
    existing = patch_paths(output, vehicle)
    selected = source_paths(paths, vehicle)
    if not paths:
      staged = git('diff', '--cached', '--name-only', '--no-renames', '-z', 'HEAD', '--', *selected)
      scope = sorted(set(existing) | {os.fsdecode(p) for p in staged.split(b'\0') if p})
      selected = [':(top,literal)' + p for p in scope] + [':(top,exclude)' + p for p in MAINTENANCE]

    with tempfile.TemporaryDirectory(prefix='update-patch-') as directory:
      temp = Path(directory)
      objects = temp / 'objects'
      objects.mkdir()
      original_objects = git('rev-parse', '--path-format=absolute', '--git-path', 'objects').decode().strip()
      # Keep generated trees out of the repository's object store as well as its index.
      (objects / 'info').mkdir()
      (objects / 'info/alternates').write_text(original_objects + '\n')
      env = dict(os.environ, GIT_OBJECT_DIRECTORY=str(objects))
      base_env = dict(env, GIT_INDEX_FILE=str(temp / 'base-index'))
      ancestor_env = dict(env, GIT_INDEX_FILE=str(temp / 'ancestor-index'))
      git('read-tree', 'HEAD', env=base_env)
      # Mode-only patches read content from this HEAD index, never staged amendments.
      git('apply', '--numstat', '--build-fake-ancestor=' + ancestor_env['GIT_INDEX_FILE'],
          *(['--directory=opendbc_repo'] if vehicle else []), str(output), env=base_env)
      originals = git('ls-files', '--stage', '-z', env=ancestor_env)
      # Added paths must be absent from the base; deleted paths must be restored.
      git('update-index', '--force-remove', '-z', '--stdin',
          stdin=b''.join(os.fsencode(p) + b'\0' for p in existing), env=base_env)
      git('update-index', '-z', '--index-info', stdin=originals, env=base_env)
      base = git('write-tree', env=base_env).decode().strip()
      return git('diff', *diff_options(vehicle), base, '--', *selected, env=env)
  except ValueError as error:
    raise ValueError('Cannot reconstruct the original patch base; existing patch left unchanged. ' +
                     f'Use --base REF to select an unpatched revision explicitly. Details: {error}') from error


def main() -> None:
  argv = sys.argv[1:]
  paths = []
  if '--' in argv:
    divider = argv.index('--')
    argv, paths = argv[:divider], argv[divider + 1:]
  parser = argparse.ArgumentParser(
    description='Write a forward binary-capable patch from staged source. No sync, replay, staging, commits or pushes.',
    epilog='Optional -- PATH... limits files (repo-relative for root patches; relative to opendbc_repo for vehicle patches).',
  )
  parser.add_argument('command', choices=('create', 'update'))
  parser.add_argument('name', help='NAME[.patch] or opendbc/NAME[.patch]; disabled suffixes are preserved')
  parser.add_argument('--base', help='Override the unpatched base. Create defaults to HEAD; update uses original versions from the existing patch.')
  args = parser.parse_args(argv)
  output, vehicle = patch_destination(args.name, args.command == 'update')
  if git('ls-files', '--unmerged', '-z'):
    raise ValueError('Resolve staged merge conflicts before exporting a patch.')
  selected = source_paths(paths, vehicle)
  if args.command == 'create' and not git('diff', '--cached', '--name-only', '--no-renames', '-z', 'HEAD', '--', *selected):
    raise ValueError('No staged source changes in the selected scope. Stage the intended edits first.')
  if args.command == 'update' and args.base is None:
    patch = automatic_update(output, vehicle, paths)
    base_label = 'original versions recorded in the existing patch'
  else:
    base_label = args.base or 'HEAD'
    base = git('rev-parse', '--verify', '--end-of-options', base_label + '^{tree}').decode().strip()
    patch = git('diff', *diff_options(vehicle), base, '--', *selected)
  if not patch:
    raise ValueError('The staged source matches the selected base; existing patch left unchanged.')
  output.parent.mkdir(parents=True, exist_ok=True)
  mode = stat.S_IMODE(output.stat().st_mode) if output.exists() else 0o644
  with tempfile.NamedTemporaryFile(dir=output.parent, prefix='.' + output.name + '.', delete=False) as handle:
    temporary = Path(handle.name)
    handle.write(patch)
  try:
    temporary.chmod(mode)
    if args.command == 'create':
      # Exclusive creation: do not overwrite a patch created while Git was reading.
      os.link(temporary, output)
    else:
      os.replace(temporary, output)
  finally:
    temporary.unlink(missing_ok=True)
  print(f"{'Updated' if args.command == 'update' else 'Created'} {output.relative_to(ROOT)} from the staged index (base: {base_label}).")
  print('Source files and staging are unchanged. Review and stage the patch file separately.')


if __name__ == '__main__':
  try:
    main()
  except (ValueError, OSError) as error:
    sys.exit(f'Error: {error}')
