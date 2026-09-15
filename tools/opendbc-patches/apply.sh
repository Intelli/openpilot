#!/usr/bin/env bash
# Explicit opt-in replay of archived opendbc patches into the main repository.
set -euo pipefail

script_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
repo_root="$(git -C "$script_dir" rev-parse --show-toplevel)"
patch_dir="$repo_root/patches/opendbc"
check_only=0
if [[ ${1:-} == --check ]]; then
  check_only=1
  shift
fi
if [[ $# -ne 1 ]]; then
  echo "Usage: $0 [--check] <patch-name.patch|--all>" >&2
  echo "No patches run by default. --all selects only patches/opendbc/*.patch." >&2
  exit 2
fi
cd "$repo_root"
if [[ ! -d opendbc_repo/opendbc ]]; then
  echo "Expected the bundled opendbc_repo/opendbc source tree." >&2
  exit 1
fi

if [[ $1 == --all ]]; then
  shopt -s nullglob
  patches=("$patch_dir"/*.patch)
  shopt -u nullglob
else
  # Accept a basename only; all inputs stay in the archived patch directory.
  if [[ $1 == */* || $1 == .* || $1 != *.patch ]]; then
    echo "Pass a .patch basename from patches/opendbc (disabled files are excluded)." >&2
    exit 2
  fi
  patches=("$patch_dir/$1")
fi
if [[ ${#patches[@]} -eq 0 ]]; then
  echo "No active archived patches found." >&2
  exit 1
fi

# Check mode evaluates each patch against the current tree without applying any.
# Replay mode checks and applies sequentially; failures leave earlier patches in place.
for patch in "${patches[@]}"; do
  [[ -f "$patch" ]] || { echo "Missing patch: $patch" >&2; exit 1; }
  if git apply --directory=opendbc_repo --reverse --check "$patch" 2>/dev/null; then
    echo "Already applied: $(basename "$patch")"
    continue
  fi
  git apply --directory=opendbc_repo --check "$patch"
  if [[ $check_only -eq 1 ]]; then
    echo "Applicable: $(basename "$patch")"
  else
    git apply --directory=opendbc_repo "$patch"
    echo "Applied: $(basename "$patch")"
  fi
done
