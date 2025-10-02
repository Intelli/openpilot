#!/usr/bin/env bash
set -euo pipefail

NAME=opendbc
SUBPATH=opendbc_repo
REMOTE=origin
BRANCH=hkg-angle-steering
URL=https://github.com/sunnypilot/opendbc.git

# 0) Keep local submodule config in sync with .gitmodules
git submodule sync --recursive

# 1) Ensure .gitmodules has the right settings (tracked in the repo)
git submodule set-url    "$SUBPATH" "$URL"
git submodule set-branch -b "$BRANCH" "$SUBPATH"
git add .gitmodules

# 2) Ensure the submodule is present
git submodule update --init "$SUBPATH"

# 3) Fetch & checkout the exact remote tip (no merges; detach at origin/BRANCH)
git -C "$SUBPATH" remote set-url "$REMOTE" "$URL"
git -C "$SUBPATH" fetch "$REMOTE" "$BRANCH"
git -C "$SUBPATH" checkout --detach "$REMOTE/$BRANCH"

# 4) Record the new pointer in the superproject, if it actually changed
git add "$SUBPATH" .gitmodules
if ! git diff --cached --quiet; then
  NEW_SHA="$(git -C "$SUBPATH" rev-parse --short=12 HEAD)"
  git commit -m "Bump opendbc to ${NEW_SHA} (${BRANCH})"
  git push
else
  echo "No change in submodule pointer; already at latest ${BRANCH}."
fi

