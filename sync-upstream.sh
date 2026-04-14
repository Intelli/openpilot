#!/bin/bash
set -euo pipefail

DEFAULT_REF="upstream/hkg-angle-steering-2025"

# Files/dirs we always keep from our pre-sync state (local tooling, patches, etc.)
# NOTE: Do NOT exclude .gitmodules or any submodule paths if you want submodules to always follow upstream.
EXCLUDES=(
  'AGENTS.md'
  'sync-upstream.sh'
  'tools/ci/sync_ev9_branch.sh'
  'update.sh'
  'apply_patch.sh'
  'apply_patch_conflicts.sh'
  'fix_patch.sh'
  'create_patch.sh'
  'create_patch_manual.sh'
  'update_patch.sh'
  '.gitmodules'
  'opendbc_repo'
  'patches'
  'auto-lock/lock-closed-white.png'
  'auto-lock/lock-closed-white.svg'
)

usage() {
  echo "Usage: $0 [--allow] [commit|ref]" >&2
  return 1 2>/dev/null
  exit 1
}

is_excluded() {
  local p="$1"
  local e
  for e in "${EXCLUDES[@]}"; do
    if [[ "$p" == "$e" || "$p" == "$e/"* ]]; then
      return 0
    fi
  done
  return 1
}

# Resolve a conflicted path in favor of the upstream tree ($TARGET_REF),
# including submodules (gitlinks) without needing the submodule commit objects locally.
take_upstream_path() {
  local path="$1"

  # What does upstream have at this path?
  # For a submodule, ls-tree returns one line with mode 160000 and a SHA.
  # For a file, it returns mode 100xxx and a blob SHA.
  # If upstream deleted it, output is empty.
  local entry mode sha
  entry="$(git ls-tree "${TARGET_REF}" -- "${path}" 2>/dev/null | head -n1 || true)"

  if [[ -z "${entry}" ]]; then
    # Upstream deleted it -> accept deletion
    git rm -f --cached -- "${path}" >/dev/null 2>&1 || true
    rm -rf -- "${path}" >/dev/null 2>&1 || true
    return 0
  fi

  mode="$(echo "${entry}" | awk '{print $1}')"
  sha="$(echo "${entry}" | awk '{print $3}')"

  if [[ "${mode}" == "160000" ]]; then
    # Submodule gitlink: set index directly to upstream SHA (no worktree touch).
    git update-index --cacheinfo 160000 "${sha}" "${path}"
  else
    # Regular file: take upstream content
    git restore --source="${TARGET_REF}" --staged --worktree --no-overlay -- "${path}"
  fi
}

# Resolve a conflicted path in favor of our pre-sync tree ($PRE_SYNC_REF)
take_ours_path() {
  local path="$1"
  local entry mode sha

  entry="$(git ls-tree "${PRE_SYNC_REF}" -- "${path}" 2>/dev/null | head -n1 || true)"
  if [[ -z "${entry}" ]]; then
    # Didn't exist pre-sync -> remove it
    git rm -f --cached -- "${path}" >/dev/null 2>&1 || true
    rm -rf -- "${path}" >/dev/null 2>&1 || true
    return 0
  fi

  mode="$(echo "${entry}" | awk '{print $1}')"
  sha="$(echo "${entry}" | awk '{print $3}')"

  if [[ "${mode}" == "160000" ]]; then
    # Submodule gitlink: restore index directly to pre-sync SHA.
    git update-index --cacheinfo 160000 "${sha}" "${path}"
    return 0
  fi

  if git cat-file -e "${PRE_SYNC_REF}:${path}" >/dev/null 2>&1; then
    git restore --source="${PRE_SYNC_REF}" --staged --worktree --no-overlay -- "${path}"
  else
    # Didn't exist pre-sync -> remove it
    git rm -f --cached -- "${path}" >/dev/null 2>&1 || true
    rm -rf -- "${path}" >/dev/null 2>&1 || true
  fi
}

ALLOW_UPSTREAM=0
POSITIONAL_ARGS=()
while [[ $# -gt 0 ]]; do
  case "$1" in
    --allow)
      ALLOW_UPSTREAM=1
      shift
      ;;
    -*)
      echo "Unknown option: $1" >&2
      usage
      ;;
    *)
      POSITIONAL_ARGS+=("$1")
      shift
      ;;
  esac
done

if [[ ${#POSITIONAL_ARGS[@]} -gt 1 ]]; then
  usage
fi

if [[ ${#POSITIONAL_ARGS[@]} -gt 0 ]]; then
  TARGET_REF="${POSITIONAL_ARGS[0]}"
else
  TARGET_REF="$DEFAULT_REF"
fi

# Fetch upstream branch so TARGET_REF resolves (default case).
git fetch upstream hkg-angle-steering-2025 --prune

if ! git rev-parse --verify "${TARGET_REF}^{commit}" >/dev/null 2>&1; then
  echo "Unable to resolve '${TARGET_REF}' to a commit. Did you fetch the right branch?" >&2
  return 1 2>/dev/null
  exit 1
fi

# Save our current HEAD for restoring excluded paths later.
PRE_SYNC_REF="$(git rev-parse --verify HEAD)"

# Safety check: upstream contains commits not present in HEAD (unless --allow).
if ! git merge-base --is-ancestor "${TARGET_REF}" HEAD; then
  if [[ ${ALLOW_UPSTREAM} -ne 1 ]]; then
    echo "Upstream '${TARGET_REF}' contains commits not present in HEAD. Re-run with --allow to continue." >&2
    return 1 2>/dev/null
    exit 1
  fi
fi

# Merge (prefer upstream content on overlap). We will auto-resolve:
# - ALL submodule conflicts by taking upstream gitlinks
# - ALL other conflicts by taking upstream, except EXCLUDES which keep ours
if ! git -c submodule.recurse=false merge --no-edit -X theirs "${TARGET_REF}"; then
  merge_resolved=0

  if git rev-parse --verify MERGE_HEAD >/dev/null 2>&1; then
    merge_conflicts=()
    while IFS= read -r conflict_path; do
      [[ -z "${conflict_path}" ]] && continue
      merge_conflicts+=("${conflict_path}")
    done < <(git diff --name-only --diff-filter=U)

    for path in "${merge_conflicts[@]}"; do
      if is_excluded "${path}"; then
        echo "Keeping ours for excluded path '${path}'." >&2
        take_ours_path "${path}"
      else
        echo "Taking upstream for '${path}'." >&2
        take_upstream_path "${path}"
      fi
    done

    if ! git diff --name-only --diff-filter=U | grep -q .; then
      if GIT_MERGE_AUTOEDIT=no git merge --continue >/dev/null 2>&1; then
        merge_resolved=1
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

# Force working tree to match upstream for everything except EXCLUDES.
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

# Restore excluded paths back to our pre-sync versions.
if [[ ${#EXCLUDES[@]} -gt 0 ]]; then
  git restore --source="${PRE_SYNC_REF}" --staged --worktree -- "${EXCLUDES[@]}" || true
fi

# git restore above can miss submodule gitlinks in some merge/no-conflict flows.
# Force excluded submodule pointers back to their pre-sync SHAs.
if [[ ${#EXCLUDES[@]} -gt 0 ]]; then
  for path in "${EXCLUDES[@]}"; do
    entry="$(git ls-tree "${PRE_SYNC_REF}" -- "${path}" 2>/dev/null | head -n1 || true)"
    [[ -z "${entry}" ]] && continue

    mode="$(echo "${entry}" | awk '{print $1}')"
    sha="$(echo "${entry}" | awk '{print $3}')"
    if [[ "${mode}" == "160000" ]]; then
      git update-index --cacheinfo 160000 "${sha}" "${path}"
    fi
  done
fi

# Align submodules to the SHAs recorded in the (now-upstream) superproject.
submodules=()
if [[ -f .gitmodules ]]; then
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
fi

if [[ ${#submodules[@]} -gt 0 ]]; then
  git submodule sync --recursive -- "${submodules[@]}"
  git submodule update --init --recursive --checkout -- "${submodules[@]}"
fi

# Uncomment if you want the script to auto-commit:
# git commit -m "Sync upstream"
