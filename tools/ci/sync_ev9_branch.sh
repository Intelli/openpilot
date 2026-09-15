#!/usr/bin/env bash
# Promote the source commit recorded by the successfully published device build.
set -euo pipefail

if [[ -n "${CI:-}" ]]; then
  git config --global --add safe.directory "$(pwd)"
fi

git fetch --no-tags origin \
  +refs/heads/ev9:refs/remotes/origin/ev9 \
  +refs/heads/ev9-dev:refs/remotes/origin/ev9-dev \
  +refs/heads/ev9-prebuilt:refs/remotes/origin/ev9-prebuilt

source_sha="$(git log -1 --format=%B origin/ev9-prebuilt | git interpret-trailers --parse | sed -n 's/^Source-Commit: //p')"
if [[ ! "$source_sha" =~ ^[0-9a-f]{40}$ ]]; then
  echo 'ev9-prebuilt has no valid Source-Commit trailer; publish a StarPilot build first.' >&2
  exit 1
fi
git cat-file -e "$source_sha^{commit}"
git merge-base --is-ancestor "$source_sha" origin/ev9-dev || {
  echo 'Published source is not part of ev9-dev history.' >&2
  exit 1
}

prod_sha="$(git rev-parse origin/ev9)"
source_tree="$(git rev-parse "$source_sha^{tree}")"
if [[ "$source_tree" == "$(git rev-parse "$prod_sha^{tree}")" ]]; then
  echo 'ev9 already matches the published source.'
  exit 0
fi

export GIT_AUTHOR_NAME="${SYNC_AUTHOR_NAME:-GitHub Actions}"
export GIT_AUTHOR_EMAIL="${SYNC_AUTHOR_EMAIL:-github-actions[bot]@users.noreply.github.com}"
export GIT_COMMITTER_NAME="$GIT_AUTHOR_NAME"
export GIT_COMMITTER_EMAIL="$GIT_AUTHOR_EMAIL"
new_commit="$(git commit-tree "$source_tree" -p "$prod_sha" \
  -m "sync: StarPilot source @ ${source_sha:0:12}" \
  -m "Source-Commit: $source_sha")"
git push origin "$new_commit:refs/heads/ev9"
echo "ev9 now matches published source $source_sha"
