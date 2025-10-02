#!/bin/bash
set -euo pipefail

DEFAULT_REF="upstream/hkg-angle-steering-2025"

EXCLUDES=(
  'AGENTS.md'
  'sync-upstream.sh'
  # 'update.sh'   # optional; file will be removed—leaving this commented is fine
  'apply_patch.sh'
  'create_patch.sh'
  'create_patch_manual.sh'
  'update_patch.sh'
  '.gitmodules'
  'patches'
  'opendbc_repo'
)

if [[ $# -gt 1 ]]; then
  echo "Usage: $0 [commit|ref]" >&2
  exit 1
fi

TARGET_REF="${1:-$DEFAULT_REF}"

# Ensure we have the upstream ref locally
git fetch upstream hkg-angle-steering-2025 --prune

if ! git rev-parse --verify "${TARGET_REF}^{commit}" >/dev/null 2>&1; then
  echo "Unable to resolve '${TARGET_REF}' to a commit. Did you fetch the right branch?" >&2
  exit 1
fi

# --- opendbc tracking config (we now do this here, not in update.sh) ---
OPENDBC_PATH="opendbc_repo"
OPENDBC_URL="https://github.com/sunnypilot/opendbc.git"
OPENDBC_BRANCH="hkg-angle-steering-2025"
OPENDBC_REMOTE="origin"

PRE_SYNC_REF="$(git rev-parse --verify HEAD)"

# Prefer upstream changes on overlap; excluded files get restored after.
# Ignore submodule commits during merge, they get synced separately.
if ! git -c submodule.recurse=false merge --no-edit -X theirs "${TARGET_REF}"; then
  echo "Merge with '${TARGET_REF}' failed. Aborting merge; please resolve issues manually." >&2
  git merge --abort >/dev/null 2>&1 || true
  exit 1
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

# Align (other) submodules to the merged superproject commit.
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

# --- Force opendbc_repo to the sunnypilot/opendbc branch tip we track ---
# Keep our .gitmodules + opendbc pointer independent of upstream tree.
git submodule set-url    "${OPENDBC_PATH}" "${OPENDBC_URL}"
git submodule set-branch -b "${OPENDBC_BRANCH}" "${OPENDBC_PATH}"
git submodule sync -- "${OPENDBC_PATH}"

git submodule update --init "${OPENDBC_PATH}"

git -C "${OPENDBC_PATH}" remote set-url "${OPENDBC_REMOTE}" "${OPENDBC_URL}"
git -C "${OPENDBC_PATH}" fetch "${OPENDBC_REMOTE}" "refs/heads/${OPENDBC_BRANCH}:refs/remotes/${OPENDBC_REMOTE}/${OPENDBC_BRANCH}"
git -C "${OPENDBC_PATH}" checkout --detach "${OPENDBC_REMOTE}/${OPENDBC_BRANCH}"

git add "${OPENDBC_PATH}" .gitmodules
if ! git diff --cached --quiet -- "${OPENDBC_PATH}" .gitmodules; then
  NEW_SHA="$(git -C "${OPENDBC_PATH}" rev-parse --short=12 HEAD)"
  git commit -m "Sync opendbc to ${NEW_SHA} (${OPENDBC_BRANCH})"
fi

echo "Upstream sync complete. Current HEAD: $(git rev-parse --short HEAD)"

