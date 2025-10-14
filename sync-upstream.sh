#!/bin/bash
set -euo pipefail

DEFAULT_REF="upstream/hkg-angle-steering-2025"

EXCLUDES=(
  'AGENTS.md'
  'sync-upstream.sh'
  '.github/workflows/ev9-sync.yaml'
  'tools/ci/sync_ev9_branch.sh'
  'update.sh'
  'apply_patch.sh'
  'fix_patch.sh'
  'create_patch.sh'
  'create_patch_manual.sh'
  'update_patch.sh'
  '.gitmodules'
  'patches'
  'opendbc_repo'
)

if [[ $# -gt 1 ]]; then
  echo "Usage: $0 [commit|ref]" >&2
  return 1 2>/dev/null
  exit 1
fi

TARGET_REF="${1:-$DEFAULT_REF}"

rm -rf opendbc_repo
git fetch upstream hkg-angle-steering-2025 --prune

if ! git rev-parse --verify "${TARGET_REF}^{commit}" >/dev/null 2>&1; then
  echo "Unable to resolve '${TARGET_REF}' to a commit. Did you fetch the right branch?" >&2
  return 1 2>/dev/null
  exit 1
fi

OPENDBC_SUBMODULE_PATH="opendbc_repo"
OPENDBC_UPSTREAM_URL="https://github.com/sunnypilot/opendbc.git"
OPENDBC_TMP_REMOTE="__sync_upstream_opendbc__"

# Ensure upstream opendbc commits are available locally so the merge can fast-forward the submodule.
#git submodule update --init -- "${OPENDBC_SUBMODULE_PATH}"
#if [[ -d "${OPENDBC_SUBMODULE_PATH}" ]]; then
#  if git -C "${OPENDBC_SUBMODULE_PATH}" remote | grep -Fxq "${OPENDBC_TMP_REMOTE}"; then
#    git -C "${OPENDBC_SUBMODULE_PATH}" remote remove "${OPENDBC_TMP_REMOTE}"
#  fi
#  git -C "${OPENDBC_SUBMODULE_PATH}" remote add "${OPENDBC_TMP_REMOTE}" "${OPENDBC_UPSTREAM_URL}"
#  if ! git -C "${OPENDBC_SUBMODULE_PATH}" fetch "${OPENDBC_TMP_REMOTE}" --tags; then
#    echo "Warning: unable to fetch upstream opendbc; proceeding with existing submodule objects." >&2
#  fi
#  git -C "${OPENDBC_SUBMODULE_PATH}" remote remove "${OPENDBC_TMP_REMOTE}" >/dev/null 2>&1 || true
#fi

PRE_SYNC_REF="$(git rev-parse --verify HEAD)"

# Prefer upstream changes on overlap; excluded files get restored after.
# Ignore submodule commits during merge, they get synced separately.
if ! git -c submodule.recurse=false merge --no-edit -X theirs "${TARGET_REF}"; then
  merge_resolved=0

  if git rev-parse --verify MERGE_HEAD >/dev/null 2>&1; then
    merge_conflicts=()
    while IFS= read -r conflict_path; do
      [[ -z "${conflict_path}" ]] && continue
      merge_conflicts+=("${conflict_path}")
    done < <(git diff --name-only --diff-filter=U)

    unresolved_conflicts=()

    for path in "${merge_conflicts[@]}"; do
      if [[ "${path}" == "${OPENDBC_SUBMODULE_PATH}" ]]; then
        echo "Resetting submodule '${path}' to '${TARGET_REF}'." >&2
        if git restore --source="${TARGET_REF}" --staged --worktree --no-overlay -- "${path}"; then
          continue
        fi
      fi
      unresolved_conflicts+=("${path}")
    done

    if [[ ${#merge_conflicts[@]} -gt 0 && ${#unresolved_conflicts[@]} -eq 0 ]]; then
      if ! git diff --name-only --diff-filter=U | grep -q .; then
        if GIT_MERGE_AUTOEDIT=no git merge --continue >/dev/null 2>&1; then
          merge_resolved=1
        fi
      fi
    fi
  fi

  if [[ ${merge_resolved} -ne 1 ]]; then
    echo "Merge with '${TARGET_REF}' failed. Aborting merge; please resolve issues manually." >&2
    git merge --abort >/dev/null 2>&1 || true
    return 1 2>/dev/null
    exit 1
  fi
fi

restore_args=(
  "--source=${TARGET_REF}"
  --staged
  --worktree
  --no-overlay
  --
  .
)

for path in "${EXCLUDES[@]}"; do
  restore_args+=(":(top,exclude)${path}")
done

git restore "${restore_args[@]}"

if [[ ${#EXCLUDES[@]} -gt 0 ]]; then
  git restore --source="${PRE_SYNC_REF}" --staged --worktree -- "${EXCLUDES[@]}"
fi

# Align submodules to upstream commit.
submodules=()
while IFS= read -r submodule_path; do
  [[ -z "${submodule_path}" ]] && continue
  submodules+=("${submodule_path}")
done < <(python3 - <<'PY_SUBMODULES'
import configparser

cfg = configparser.RawConfigParser()
cfg.read('.gitmodules')
for section in cfg.sections():
    path = cfg.get(section, 'path', fallback='').strip()
    if path:
        print(path)
PY_SUBMODULES
)

if [[ ${#submodules[@]} -gt 0 ]]; then
  git submodule sync --recursive -- "${submodules[@]}"
  git submodule update --init --recursive --checkout -- "${submodules[@]}"
fi
#git restore --source="${TARGET_REF}" --staged --worktree --no-overlay .
#git clean -fd
#git commit -m "Sync upstream"
#git push origin ev9
