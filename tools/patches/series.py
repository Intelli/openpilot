"""Keep feature ownership when updating patches that share source files."""
import copy
import os
from pathlib import Path
import re
import shutil
import tempfile


HUNK = re.compile(rb'^@@ -(\d+)(?:,(\d+))? \+(\d+)(?:,(\d+))? @@', re.MULTILINE)
PREIMAGE = re.compile(rb'^index ([0-9a-f]{40,64})\.\.', re.MULTILINE)


def lines(data):
  parts = data.split(b'\n')
  return [part + b'\n' for part in parts[:-1]] + ([parts[-1]] if parts[-1] else [])


def hunks(diff):
  for match in HUNK.finditer(diff):
    old, old_count, new, new_count = (int(value) if value is not None else 1 for value in match.groups())
    yield (old - 1 if old_count else old), old_count, (new - 1 if new_count else new), new_count


def literal_glob(path):
  return ''.join('\\' + char if char in '\\*?[' else char for char in path)


def cache_preimages(root, git, patch, env):
  directory = root / 'patches/baselines'
  if directory.is_symlink():
    raise ValueError('Patch baseline directory must not be a symlink.')
  directory.mkdir(parents=True, exist_ok=True)
  for encoded in sorted(set(PREIMAGE.findall(patch))):
    oid = encoded.decode()
    if not int(oid, 16):
      continue
    payload = git('cat-file', 'blob', oid, env=env)
    target = directory / oid
    if os.path.lexists(target):
      if target.is_symlink() or not target.is_file() or target.read_bytes() != payload:
        raise ValueError(f'Invalid cached patch baseline: {target.relative_to(root)}')
      continue
    with tempfile.NamedTemporaryFile(dir=directory, prefix='.', delete=False) as handle:
      temporary = Path(handle.name)
      handle.write(payload)
    try:
      temporary.chmod(0o644)
      os.link(temporary, target)
    finally:
      temporary.unlink(missing_ok=True)


def update_series(root, git, output, vehicle, scope, peers):
  """Transfer only unrecorded, owned edits from the final series to one feature."""
  with tempfile.TemporaryDirectory(prefix='update-patch-series-') as directory:
    temp = Path(directory)
    objects = temp / 'objects'
    (objects / 'info').mkdir(parents=True)
    original_objects = git('rev-parse', '--path-format=absolute', '--git-path', 'objects').decode().strip()
    (objects / 'info/alternates').write_text(original_objects + '\n')
    env = dict(os.environ, GIT_OBJECT_DIRECTORY=str(objects), GIT_INDEX_FILE=str(temp / 'index'))
    desired_env = dict(env, GIT_INDEX_FILE=str(temp / 'desired-index'))
    real_index = git('rev-parse', '--path-format=absolute', '--git-path', 'index').decode().strip()
    shutil.copy2(real_index, desired_env['GIT_INDEX_FILE'])
    desired = git('write-tree', env=desired_env).decode().strip()

    def tree():
      return git('write-tree', env=env).decode().strip()

    def entries(ref):
      result = {}
      for row in git('ls-tree', '-rz', ref, env=env).split(b'\0'):
        if row:
          header, name = row.split(b'\t', 1)
          mode, kind, oid = header.decode().split()
          result[os.fsdecode(name)] = (mode, oid)
      return result

    def data(entry):
      return git('cat-file', 'blob', entry[1], env=env) if entry else b''

    def diff(before, after, paths, zero=False):
      return git('diff', '--binary', '--full-index', '--no-renames', '--no-ext-diff', '--no-textconv', '--no-color',
                 *(['--unified=0'] if zero else []), '--src-prefix=a/', '--dst-prefix=b/', before, after, '--',
                 *(':(top,literal)' + path for path in sorted(paths)), env=env)

    def apply(peer, replacement=None):
      path, is_vehicle, owned = peer
      included = scope if replacement is not None else owned & scope
      if not included:
        return
      git('apply', '--cached', '--whitespace=nowarn', *(['--directory=opendbc_repo'] if is_vehicle else []),
          *('--include=' + literal_glob(name) for name in sorted(included)), str(replacement or path), env=env)

    git('read-tree', 'HEAD', env=env)
    originals, seen = {}, set()
    for ordinal, (path, is_vehicle, owned) in enumerate(peers):
      first = (owned & scope) - seen
      if not first:
        continue
      ancestor_env = dict(env, GIT_INDEX_FILE=str(temp / f'ancestor-{ordinal}'))
      git('apply', '--numstat', '--build-fake-ancestor=' + ancestor_env['GIT_INDEX_FILE'],
          *(['--directory=opendbc_repo'] if is_vehicle else []), str(path), env=env)
      for row in git('ls-files', '--stage', '-z', env=ancestor_env).split(b'\0'):
        if row:
          header, encoded = row.split(b'\t', 1)
          name = os.fsdecode(encoded)
          if name in first:
            originals[name] = row + b'\0'
      seen |= first
    git('update-index', '--force-remove', '-z', '--stdin', stdin=b''.join(os.fsencode(p) + b'\0' for p in sorted(seen)), env=env)
    git('update-index', '-z', '--index-info', stdin=b''.join(originals.values()), env=env)
    baseline = tree()
    initial = entries(baseline)
    tokens = {name: [(None, i) for i in range(len(lines(data(initial.get(name)))))] for name in scope}
    boundaries = {name: [set() for _ in range(len(tokens[name]) + 1)] for name in scope}
    whole_owners = {name: set() for name in scope}
    requested_before = requested_after = None
    requested_tokens = None
    serial = 0
    for peer in peers:
      before = tree()
      before_entries = entries(before)
      apply(peer)
      after = tree()
      after_entries = entries(after)
      owner = str(peer[0].relative_to(root))
      for name in peer[2] & scope:
        old, new = before_entries.get(name), after_entries.get(name)
        change = diff(before, after, {name}, zero=True)
        if not change:
          continue
        if b'GIT binary patch\n' in change or (old and new and old[0] != new[0]) or any(e and e[0] == '120000' for e in (old, new)):
          whole_owners[name].add(owner)
        for start, count, _, added in reversed(list(hunks(change))):
          old_bounds = boundaries[name][start:start + count + 1]
          deleted = set().union(*old_bounds)
          if count and not added:
            deleted.add(owner)
          labels = [(owner, serial + i) for i in range(added)]
          serial += added
          tokens[name][start:start + count] = labels
          boundaries[name][start:start + count + 1] = [deleted] + [set() for _ in range(added)]
      if peer[0] == output:
        requested_before, requested_after = before, after
        requested_tokens = copy.deepcopy(tokens)
    if requested_before is None:
      raise ValueError('Requested patch is not in the enabled series.')
    expected = tree()
    expected_entries, desired_entries = entries(expected), entries(desired)
    git('read-tree', requested_after, env=env)
    target_entries = entries(requested_after)
    owner = str(output.relative_to(root))
    for name in sorted(scope):
      change = diff(expected, desired, {name}, zero=True)
      if not change:
        continue
      old, new = expected_entries.get(name), desired_entries.get(name)
      if whole_owners[name] - {owner}:
        raise ValueError(f'Amendment shares binary/mode ownership with another feature: {name}')
      binary_or_mode = b'GIT binary patch\n' in change or (old and new and old[0] != new[0])
      target_data = lines(data(target_entries.get(name)))
      expected_data, desired_data = lines(data(old)), lines(data(new))
      positions = {token: i for i, token in enumerate(requested_tokens[name])}
      for start, count, new_start, added in reversed(list(hunks(change))):
        owners = {token[0] for token in tokens[name][start:start + count] if token[0] is not None}
        owners |= set().union(*boundaries[name][start:start + count + 1])
        if not count and 0 < start < len(tokens[name]) and tokens[name][start - 1][0] == tokens[name][start][0]:
          if tokens[name][start][0] is not None:
            owners.add(tokens[name][start][0])
        if owners - {owner}:
          raise ValueError(f'Amendment touches another feature in {name}; update the owning patch first.')
        if count:
          mapped = [positions.get(token) for token in tokens[name][start:start + count]]
          if not mapped or mapped[0] is None or mapped != list(range(mapped[0], mapped[0] + count)):
            raise ValueError(f'Cannot isolate amendment from later feature changes in {name}.')
          target_start = mapped[0]
        else:
          previous = positions.get(tokens[name][start - 1]) if start else -1
          following = positions.get(tokens[name][start]) if start < len(tokens[name]) else len(requested_tokens[name])
          if previous is None or following is None or previous + 1 != following:
            raise ValueError(f'Ambiguous insertion between feature patches in {name}.')
          target_start = following
        if target_data[target_start:target_start + count] != expected_data[start:start + count]:
          raise ValueError(f'Amendment preimage differs from the selected feature in {name}.')
        target_data[target_start:target_start + count] = desired_data[new_start:new_start + added]
      if binary_or_mode:
        peer_owners = {token[0] for token in tokens[name] if token[0] is not None} | whole_owners[name]
        if peer_owners - {owner}:
          raise ValueError(f'Cannot isolate binary/mode amendment in shared feature file: {name}')
        payload = data(new)
      else:
        payload = b''.join(target_data)
      git('update-index', '--force-remove', '--', name, env=env)
      if new is not None:
        oid = git('hash-object', '-w', '--stdin', stdin=payload, env=env).decode().strip()
        git('update-index', '-z', '--index-info', stdin=f'{new[0]} {oid}\t'.encode() + os.fsencode(name) + b'\0', env=env)
    amended = tree()
    patch = diff(requested_before, amended, scope)
    if vehicle:
      patch = git('diff', '--binary', '--full-index', '--no-renames', '--no-ext-diff', '--no-textconv', '--no-color',
                  '--relative=opendbc_repo', '--src-prefix=a/', '--dst-prefix=b/', requested_before, amended, '--',
                  *(':(top,literal)' + path for path in sorted(scope)), env=env)
    candidate = temp / 'candidate.patch'
    candidate.write_bytes(patch)
    git('read-tree', baseline, env=env)
    for peer in peers:
      apply(peer, candidate if peer[0] == output else None)
    if diff(tree(), desired, scope):
      raise ValueError('Updated feature does not reproduce the staged source when replayed with its peers.')
    cache_preimages(root, git, patch, env)
    return patch
