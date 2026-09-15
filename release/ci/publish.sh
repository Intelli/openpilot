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
if git ls-remote --exit-code --heads origin ev9-prebuilt >/dev/null; then
  git fetch --depth=1 origin ev9-prebuilt
  git reset --soft FETCH_HEAD
fi
git add -f --all
if git diff --cached --quiet && git rev-parse --verify HEAD >/dev/null 2>&1; then
  previous_source=$(git log -1 --format=%B | git interpret-trailers --parse | sed -n 's/^Source-Commit: //p')
  if [[ "$previous_source" == "$source_sha" ]]; then
    echo 'Deployment already matches this source and build.'
    exit 0
  fi
fi
git commit --allow-empty -m "StarPilot deployment from ${source_sha}" -m "Source-Commit: ${source_sha}"
git push origin HEAD:refs/heads/ev9-prebuilt
