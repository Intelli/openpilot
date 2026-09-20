#!/usr/bin/env bash
# Promote the successfully published device build, including its compiled artifacts.
set -euo pipefail

if [[ -n "${CI:-}" ]]; then
  git config --global --add safe.directory "$(pwd)"
fi

git fetch --no-tags origin \
  +refs/heads/ev9:refs/remotes/origin/ev9 \
  +refs/heads/ev9-dev:refs/remotes/origin/ev9-dev \
  +refs/heads/ev9-prebuilt:refs/remotes/origin/ev9-prebuilt

build_sha="$(git rev-parse origin/ev9-prebuilt)"
source_sha="$(git log -1 --format=%B "$build_sha" | git interpret-trailers --parse | sed -n 's/^Source-Commit: //p')"
if [[ ! "$source_sha" =~ ^[0-9a-f]{40}$ ]]; then
  echo 'ev9-prebuilt has no valid Source-Commit trailer; publish a StarPilot build first.' >&2
  exit 1
fi
git cat-file -e "$source_sha^{commit}"
git merge-base --is-ancestor "$source_sha" origin/ev9-dev || {
  echo 'Published source is not part of ev9-dev history.' >&2
  exit 1
}
if [[ "$(git cat-file -t "$build_sha:prebuilt" 2>/dev/null || true)" != blob ]]; then
  echo 'Published build has no prebuilt marker; refusing to promote it.' >&2
  exit 1
fi

prod_sha="$(git rev-parse origin/ev9)"
build_tree="$(git rev-parse "$build_sha^{tree}")"
previous_source="$(git log -1 --format=%B "$prod_sha" | git interpret-trailers --parse | sed -n 's/^Source-Commit: //p')"
previous_build="$(git log -1 --format=%B "$prod_sha" | git interpret-trailers --parse | sed -n 's/^Build-Commit: //p')"
if [[ "$build_tree" == "$(git rev-parse "$prod_sha^{tree}")" && "$previous_source" == "$source_sha" && "$previous_build" == "$build_sha" ]]; then
  echo 'ev9 already matches the published build.'
  exit 0
fi

export GIT_AUTHOR_NAME="${SYNC_AUTHOR_NAME:-GitHub Actions}"
export GIT_AUTHOR_EMAIL="${SYNC_AUTHOR_EMAIL:-github-actions[bot]@users.noreply.github.com}"
export GIT_COMMITTER_NAME="$GIT_AUTHOR_NAME"
export GIT_COMMITTER_EMAIL="$GIT_AUTHOR_EMAIL"
new_commit="$(git commit-tree "$build_tree" -p "$prod_sha" \
  -m "deploy: StarPilot build @ ${source_sha:0:12}" \
  -m "Source-Commit: $source_sha
Build-Commit: $build_sha")"
git push origin "$new_commit:refs/heads/ev9"
echo "ev9 now matches published build $build_sha from source $source_sha"
