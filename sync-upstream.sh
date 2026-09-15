#!/usr/bin/env bash
# Import the stable StarPilot tree, retaining local maintenance tools only.
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$ROOT"
REMOTE=starpilot
UPSTREAM_URL=https://github.com/firestar5683/StarPilot.git
UPSTREAM_BRANCH=StarPilot
ALLOW=0
CHECK=0
for arg in "$@"; do
  case "$arg" in
    --allow) ALLOW=1 ;;
    --check) CHECK=1 ;;
    --help|-h)
      echo "Usage: $0 [--check | --allow]"
      echo "Fetch stable StarPilot; --check previews changes, --allow stages the upstream snapshot."
      exit 0 ;;
    *) echo "Unknown argument: $arg" >&2; exit 2 ;;
  esac
done

# These are maintenance files, not custom vehicle/application behavior.
# Do not preserve .gitmodules or opendbc_repo: StarPilot vendors its dependencies.
PRESERVE=(
  AGENTS.md sync-upstream.sh update.sh
  apply_patch.sh apply_patch_conflicts.sh fix_patch.sh
  create_patch.sh create_patch_manual.sh update_patch.sh
  patches tools/opendbc-patches
  tools/ci/sync_ev9_branch.sh tools/ci/tests
  .github/workflows release/ci/publish.sh
  docs/STARPILOT_MIGRATION.md starpilot-upstream.json
)
PATHS=(.)
for path in "${PRESERVE[@]}"; do
  PATHS+=(":(top,exclude)$path")
done

if git rev-parse --verify MERGE_HEAD >/dev/null 2>&1 ||
   [[ -d "$(git rev-parse --git-path rebase-merge)" || -d "$(git rev-parse --git-path rebase-apply)" ]]; then
  echo 'Finish the current merge/rebase before syncing.' >&2
  exit 1
fi
if [[ $CHECK -eq 0 ]] && { ! git diff --quiet -- "${PATHS[@]}" || ! git diff --cached --quiet -- "${PATHS[@]}"; }; then
  echo 'Commit or stash application changes first. Only preserved maintenance files may be dirty.' >&2
  exit 1
fi

if git remote get-url "$REMOTE" >/dev/null 2>&1; then
  [[ "$(git config --get "remote.$REMOTE.url")" == "$UPSTREAM_URL" ]] || {
    echo "Remote $REMOTE must point to $UPSTREAM_URL" >&2; exit 1;
  }
else
  git remote add "$REMOTE" "$UPSTREAM_URL"
fi
# Fetch just the stable snapshot, including shipped binaries, not years of binary history.
git fetch --no-tags --depth=1 "$REMOTE" "+refs/heads/$UPSTREAM_BRANCH:refs/remotes/$REMOTE/$UPSTREAM_BRANCH"
TARGET="$(git rev-parse "refs/remotes/$REMOTE/$UPSTREAM_BRANCH")"
TREE="$(git rev-parse "$TARGET^{tree}")"
echo "Stable StarPilot: $TARGET"

if [[ $CHECK -eq 1 ]]; then
  git diff --stat HEAD "$TARGET" -- "${PATHS[@]}"
  exit 0
fi

PREVIOUS=""
if [[ -f starpilot-upstream.json ]]; then
  PREVIOUS="$(python3 -c 'import json; print(json.load(open("starpilot-upstream.json"))["commit"])')"
fi
if [[ $ALLOW -ne 1 && "$TARGET" != "$PREVIOUS" ]]; then
  echo 'New upstream snapshot available. Use --allow to import it, or --check to preview.' >&2
  exit 1
fi

# git restore can overwrite untracked and ignored files. Check file/directory
# collisions first; old gitlink contents will be moved intact into the backup.
python3 - "$TARGET" "${PRESERVE[@]}" <<'PY'
import subprocess
import sys

target, *preserved = sys.argv[1:]

def git_paths(*args):
  return subprocess.check_output(['git', *args]).decode('utf-8', 'surrogateescape').split('\0')[:-1]

def under(path, root):
  return path == root or path.startswith(root + '/')

gitlinks = [entry.split('\t', 1)[1] for entry in git_paths('ls-files', '--stage', '-z') if entry.startswith('160000 ')]
incoming = {p for p in git_paths('ls-tree', '-r', '--name-only', '-z', target) if not any(under(p, root) for root in preserved)}
incoming_dirs = {p[:i] for p in incoming for i, char in enumerate(p) if char == '/'}
conflicts = []
for path in git_paths('ls-files', '--others', '-z'):
  path = path.rstrip('/')  # Git reports untracked nested repositories as directories.
  if any(under(path, root) for root in preserved + gitlinks):
    continue
  ancestors = [path[:i] for i, char in enumerate(path) if char == '/']
  if path in incoming or path in incoming_dirs or any(parent in incoming for parent in ancestors):
    conflicts.append(path)
if conflicts:
  sys.exit('Untracked or ignored files would be overwritten; move them before syncing:\n' + '\n'.join(conflicts))
PY

# Move old submodules aside before their gitlinks become ordinary files.
# Keep the files and Git metadata recoverable; never delete the standalone repo.
BACKUP="$(git rev-parse --absolute-git-dir)/starpilot-backups/$(date -u +%Y%m%dT%H%M%SZ)-$$"
SUBMODULES=()
SUBMODULE_COUNT=0
while IFS= read -r path; do
  if [[ -n "$path" ]]; then
    SUBMODULES+=("$path")
    SUBMODULE_COUNT=$((SUBMODULE_COUNT + 1))
  fi
done < <(git ls-files --stage | awk '$1 == "160000" {sub(/^[^\t]*\t/, ""); print}')
for path in "${SUBMODULES[@]-}"; do
  [[ -n "$path" ]] || continue
  if [[ -e "$path/.git" ]] && [[ -n "$(git -C "$path" status --porcelain)" ]]; then
    echo "Submodule $path has local changes; save them before syncing." >&2
    exit 1
  fi
done
if [[ $SUBMODULE_COUNT -gt 0 ]]; then
  mkdir -p "$BACKUP"
  git rev-parse HEAD > "$BACKUP/previous-head"
  for path in "${SUBMODULES[@]}"; do
    if [[ -e "$path" ]]; then
      mkdir -p "$BACKUP/$(dirname "$path")"
      mv "$path" "$BACKUP/$path"
      printf '%s\n' "$path" >> "$BACKUP/submodule-paths"
    fi
  done
  echo "Previous submodule checkouts saved in $BACKUP"
fi

# Import stored bytes directly, without the previous fork's LFS filters/hooks.
RAW_GIT=(git -c filter.lfs.process= -c filter.lfs.smudge= -c filter.lfs.clean=
  -c filter.lfs.required=false -c core.hooksPath=/dev/null)
"${RAW_GIT[@]}" -c submodule.recurse=false restore --source="$TARGET" --staged --worktree --no-overlay -- "${PATHS[@]}"
python3 - "$TARGET" "$TREE" <<'PY'
import json
from pathlib import Path
import sys

Path('starpilot-upstream.json').write_text(json.dumps({
  'repository': 'https://github.com/firestar5683/StarPilot',
  'branch': 'StarPilot',
  'commit': sys.argv[1],
  'tree': sys.argv[2],
  'legacy_patches_applied': False,
}, indent=2) + '\n')
PY
"${RAW_GIT[@]}" add starpilot-upstream.json
echo 'Stable StarPilot staged. No legacy patches applied and no commits or pushes made.'
