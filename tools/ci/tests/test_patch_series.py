"""Shared-file feature exports must preserve ownership and real Git state."""
import os
import re
import subprocess

import pytest

from test_patch_create import repo as repo


def content(earlier='line 03', later='line 27'):
  rows = [f'line {i:02d}' for i in range(32)]
  rows[3], rows[27] = earlier, later
  return '\n'.join(rows) + '\n'


def series(repo, source='app.txt', vehicle_peer=False):
  path, git, stage, export = repo
  stage(source, content())
  git('commit', '-m', 'shared source baseline')
  stage(source, content('earlier feature'))
  export('create_patch.sh', '01_earlier', '--', source)
  git('add', 'patches')
  git('commit', '-m', 'earlier feature')
  stage(source, content('earlier feature', 'later feature'))
  later = 'opendbc/01_later' if vehicle_peer else '02_later'
  export('create_patch.sh', later, '--', source.removeprefix('opendbc_repo/') if vehicle_peer else source)
  git('add', 'patches')
  git('commit', '-m', 'later feature')
  return later


@pytest.mark.parametrize('target', ['01_earlier', '02_later'])
def test_shared_file_update_retains_only_requested_feature(repo, target):
  path, _, stage, export = repo
  series(repo)
  if target == '01_earlier':
    stage(content=content('earlier amendment', 'later feature'))
    own, peer = b'+earlier amendment\n', b'+later feature\n'
  else:
    stage(content=content('earlier feature', 'later amendment'))
    own, peer = b'+later amendment\n', b'+earlier feature\n'
  export('update_patch.sh', target)
  patch = path / f'patches/{target}.patch'
  first = patch.read_bytes()
  assert own in first and peer not in first
  export('update_patch.sh', target)
  assert patch.read_bytes() == first


@pytest.mark.parametrize('peer_change', ['amended', 'missing'])
@pytest.mark.parametrize('target', ['01_earlier', '02_later'])
def test_changing_peer_while_updating_wrong_feature_is_rejected(repo, target, peer_change):
  path, _, stage, export = repo
  series(repo)
  if target == '01_earlier':
    stage(content=content('earlier feature', 'peer amendment' if peer_change == 'amended' else 'line 27'))
  else:
    stage(content=content('peer amendment' if peer_change == 'amended' else 'line 03', 'later feature'))
  patch = path / f'patches/{target}.patch'
  original = patch.read_bytes()
  result = export('update_patch.sh', target, success=False)
  assert b'feature' in result.stderr
  assert patch.read_bytes() == original


def test_repeated_peer_line_cannot_match_an_unowned_occurrence(repo):
  path, git, stage, export = repo
  original = 'start\n' + 'same\n' * 24 + 'end\n'
  stage(content=original)
  git('commit', '-m', 'repeated source baseline')
  first = original.replace('start\n', 'earlier feature\n', 1)
  stage(content=first)
  export('create_patch.sh', '01_earlier')
  git('add', 'patches')
  git('commit', '-m', 'earlier feature')
  stage(content=first.replace('end\n', 'same\nend\n'))
  export('create_patch.sh', '02_later')
  git('add', 'patches')
  git('commit', '-m', 'later repeated-line insertion')
  patch = path / 'patches/01_earlier.patch'
  before = patch.read_bytes()
  stage(content=first.replace('end\n', 'peer amendment\nend\n'))
  export('update_patch.sh', '01_earlier', success=False)
  assert patch.read_bytes() == before


def test_insertion_at_peer_deleted_line_keeps_peer_ownership(repo):
  path, git, stage, export = repo
  stage(content=content())
  git('commit', '-m', 'shared source baseline')
  first = content('earlier feature')
  stage(content=first)
  export('create_patch.sh', '01_earlier')
  git('add', 'patches')
  git('commit', '-m', 'earlier feature')
  stage(content=first.replace('line 27\n', ''))
  export('create_patch.sh', '02_later')
  git('add', 'patches')
  git('commit', '-m', 'later deletion')
  patch = path / 'patches/01_earlier.patch'
  before = patch.read_bytes()
  stage(content=first.replace('line 27\n', 'insert at peer deletion\n'))
  export('update_patch.sh', '01_earlier', success=False)
  assert patch.read_bytes() == before


def test_missing_shared_source_does_not_remove_peer_through_wrong_patch(repo):
  path, git, _, export = repo
  series(repo)
  patch = path / 'patches/02_later.patch'
  before = patch.read_bytes()
  (path / 'app.txt').unlink()
  git('add', 'app.txt')
  export('update_patch.sh', '02_later', success=False)
  assert patch.read_bytes() == before


@pytest.mark.parametrize('vehicle_target', [False, True])
def test_root_and_vehicle_features_share_normalized_path_without_bleeding(repo, vehicle_target):
  path, _, stage, export = repo
  source = 'opendbc_repo/opendbc/car/example.py'
  later = series(repo, source, vehicle_peer=True)
  target = later if vehicle_target else '01_earlier'
  stage(source, content('earlier feature' if vehicle_target else 'earlier amendment',
                        'later amendment' if vehicle_target else 'later feature'))
  export('update_patch.sh', target)
  patch = (path / f'patches/{target}.patch').read_bytes()
  assert (b'opendbc_repo/' not in patch) == vehicle_target
  assert b'+later feature\n' not in patch and b'+earlier feature\n' not in patch
  assert (b'+later amendment\n' if vehicle_target else b'+earlier amendment\n') in patch


@pytest.mark.parametrize('vehicle_target', [False, True])
def test_shared_feature_update_includes_new_staged_source(repo, vehicle_target):
  path, _, stage, export = repo
  source = 'opendbc_repo/opendbc/car/example.py' if vehicle_target else 'app.txt'
  later = series(repo, source, vehicle_peer=vehicle_target)
  target = later if vehicle_target else '01_earlier'
  stage(source, content('earlier feature' if vehicle_target else 'earlier amendment',
                        'later amendment' if vehicle_target else 'later feature'))
  new_source = 'opendbc_repo/opendbc/car/new_feature.py' if vehicle_target else 'new_feature.py'
  stage(new_source, 'new source belongs to requested feature\n')
  if vehicle_target:
    stage('unrelated.txt', 'outside vehicle scope\n')
  export('update_patch.sh', target)
  patch = (path / f'patches/{target}.patch').read_bytes()
  assert b'+new source belongs to requested feature\n' in patch
  assert b'new file mode 100644' in patch
  assert b'+earlier feature\n' not in patch and b'+later feature\n' not in patch
  assert b'unrelated.txt' not in patch and b'outside vehicle scope' not in patch
  exported_source = 'opendbc/car/new_feature.py' if vehicle_target else new_source
  assert f'+++ b/{exported_source}\n'.encode() in patch
  assert b'opendbc_repo/' not in patch


def test_updated_peer_baseline_survives_fresh_clone(repo):
  path, git, stage, export = repo
  series(repo)
  stage(content=content('earlier amendment', 'later feature'))
  export('update_patch.sh', '01_earlier')
  # Re-exporting the later feature synthesizes a new preimage containing the
  # recorded earlier amendment, but not the later feature itself.
  export('update_patch.sh', '02_later')
  later = path / 'patches/02_later.patch'
  oid = re.search(rb'^index ([0-9a-f]{40})\.\.', later.read_bytes(), re.MULTILINE).group(1).decode()
  payload = path / f'patches/baselines/{oid}'
  assert payload.read_text() == content('earlier amendment')
  assert git('hash-object', str(payload)).decode().strip() == oid
  with pytest.raises(subprocess.CalledProcessError):
    git('cat-file', '-e', oid)
  git('add', 'app.txt', 'patches')
  git('commit', '-m', 'updated features and reachable original blobs')

  clone = path.parent / f'{path.name}-clone'
  env = dict(os.environ, GIT_CONFIG_GLOBAL=str(path / 'gitconfig'), GIT_CONFIG_NOSYSTEM='1', GIT_ALLOW_PROTOCOL='file')
  subprocess.run(['git', 'clone', '--no-local', str(path), str(clone)], env=env, check=True, capture_output=True)
  assert not (clone / '.git/objects/info/alternates').exists()
  def clone_git(*args):
    return subprocess.run(['git', *args], cwd=clone, env=env, check=True, capture_output=True).stdout
  clone_git('cat-file', '-e', oid)
  (clone / 'app.txt').write_text(content('earlier amendment', 'later second amendment'))
  clone_git('add', 'app.txt')
  index = (clone / '.git/index').read_bytes()
  worktree = clone_git('diff', '--binary', '--', '.', ':(exclude)patches')
  result = subprocess.run(['bash', 'update_patch.sh', '02_later'], cwd=clone, env=env, capture_output=True)
  assert result.returncode == 0, result.stderr.decode()
  assert (clone / '.git/index').read_bytes() == index
  assert clone_git('diff', '--binary', '--', '.', ':(exclude)patches') == worktree
  exported = (clone / 'patches/02_later.patch').read_bytes()
  assert b'+later second amendment\n' in exported
  assert b'+earlier amendment\n' not in exported
