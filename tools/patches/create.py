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
  'docs/STARPILOT_MIGRATION.md', 'starpilot-upstream.json',
)
SUFFIXES = ('.patch', '.patch.temp-disabled', '.patch.disabled', '.patch.OUTDATED.disabled')


def git(*args: str) -> bytes:
  result = subprocess.run(['git', '-C', str(ROOT), *args], capture_output=True)
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
  parser.add_argument('--base', help='Unpatched Git revision to compare with the index. Create defaults to HEAD; update requires this.')
  args = parser.parse_args(argv)
  if args.command == 'update' and args.base is None:
    parser.error('update requires --base REF: replacing a patch with only incremental edits could drop its original changes. ' +
                 'Use --base HEAD when the full replacement is staged against HEAD.')
  output, vehicle = patch_destination(args.name, args.command == 'update')
  if git('ls-files', '--unmerged', '-z'):
    raise ValueError('Resolve staged merge conflicts before exporting a patch.')
  selected = source_paths(paths, vehicle)
  if not git('diff', '--cached', '--name-only', '--no-renames', '-z', 'HEAD', '--', *selected):
    raise ValueError('No staged source changes in the selected scope. Stage the intended edits first.')
  base = git('rev-parse', '--verify', '--end-of-options', (args.base or 'HEAD') + '^{tree}').decode().strip()
  options = ['--cached', '--binary', '--full-index', '--no-renames', '--no-ext-diff', '--no-textconv', '--no-color',
             '--src-prefix=a/', '--dst-prefix=b/']
  if vehicle:
    options.append('--relative=opendbc_repo')
  patch = git('diff', *options, base, '--', *selected)
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
  print(f"{'Updated' if args.command == 'update' else 'Created'} {output.relative_to(ROOT)} from the staged index (base {args.base or 'HEAD'}).")
  print('Source files and staging are unchanged. Review and stage the patch file separately.')


if __name__ == '__main__':
  try:
    main()
  except (ValueError, OSError) as error:
    sys.exit(f'Error: {error}')
