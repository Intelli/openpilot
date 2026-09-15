#!/usr/bin/env bash
set -euo pipefail

output_dir=${1:?Usage: publish.sh OUTPUT_DIR SOURCE_SHA}
source_sha=${2:?Source SHA required}
[[ "$source_sha" =~ ^[0-9a-f]{40}$ ]]
cd "$output_dir"
test -f prebuilt

git init --initial-branch=ev9-prebuilt
git config user.name 'github-actions[bot]'
git config user.email 'github-actions[bot]@users.noreply.github.com'
git remote add origin https://github.com/Intelli/openpilot.git
previous_sha=""
if git ls-remote --exit-code --heads origin ev9-prebuilt >/dev/null; then
  git fetch --depth=1 --no-tags origin ev9-prebuilt
  previous_sha="$(git rev-parse FETCH_HEAD)"
fi
git add -f --all
build_tree="$(git write-tree)"
if [[ -n "$previous_sha" ]]; then
  previous_source="$(git log -1 --format=%B "$previous_sha" | git interpret-trailers --parse | sed -n 's/^Source-Commit: //p')"
  # Read actual commit headers: shallow history would hide parents from git log.
  previous_parents="$(git cat-file -p "$previous_sha" | sed -n '/^$/q; s/^parent //p')"
  if [[ "$build_tree" == "$(git rev-parse "$previous_sha^{tree}")" && "$previous_source" == "$source_sha" && -z "$previous_parents" ]]; then
    echo 'Deployment already matches this source and build.'
    exit 0
  fi
fi
# Keep only the latest build on this branch. ev9 retains deployment history.
build_sha="$(git commit-tree "$build_tree" -m "StarPilot deployment from ${source_sha}" -m "Source-Commit: ${source_sha}")"
git push --force-with-lease="refs/heads/ev9-prebuilt:$previous_sha" origin "$build_sha:refs/heads/ev9-prebuilt"
