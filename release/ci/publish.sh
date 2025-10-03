#!/usr/bin/env bash

set -e

DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" >/dev/null && pwd)"
cd $DIR

# Take parameters as arguments
SOURCE_DIR=$1
OUTPUT_DIR=$2
DEV_BRANCH=$3
VERSION=$4
GIT_ORIGIN=$5
EXTRA_VERSION_IDENTIFIER=$6

# Check parameters
if [ -z "$SOURCE_DIR" ] || [ -z "$OUTPUT_DIR" ]; then
    echo "Error: No source or output directory provided."
    exit 1
fi

if [ -z "$DEV_BRANCH" ] || [ -z "$VERSION" ]; then
    echo "Error: No dev branch or version provided."
    exit 1
fi

if [ -z "$GIT_ORIGIN" ]; then
    echo "Error: No GIT_ORIGIN provided"
    exit 1
fi

# "Tagging"
echo "#define COMMA_VERSION \"$VERSION\"" > ${OUTPUT_DIR}/common/version.h

## set git identity
#source $DIR/identity.sh
#export GIT_SSH_COMMAND="ssh -i /data/gitkey"

echo "[-] Setting up repo T=$SECONDS"
cd $OUTPUT_DIR
git init
git lfs install --local
git lfs track "*.pkl"
git config lfs.skipSmudge 1
git config lfs.fetchrecentrefsdays 3650
git config lfs.fetchrecentcommitsdays 3650
git config lfs.url https://gitlab.com/sunnypilot/public/sunnypilot-new-lfs.git/info/lfs
git config lfs.https://gitlab.com/sunnypilot/public/sunnypilot-new-lfs.git.locksverify false

# allow PKL artifacts to be stored directly in git to avoid LFS push failures
sed -i '/^\*\.pkl filter=lfs/d' .gitattributes

echo "[-] Syncing upstream models T=$SECONDS"
python3 - <<'PY'
from urllib.request import urlopen
from pathlib import Path

MODELS = [
  "dmonitoring_model_tinygrad.pkl",
  "driving_policy_tinygrad.pkl",
  "driving_vision_tinygrad.pkl",
  "driving_policy_metadata.pkl",
  "driving_vision_metadata.pkl",
]
BASE = "https://raw.githubusercontent.com/sunnypilot/sunnypilot/staging/selfdrive/modeld/models/{}"
root = Path("selfdrive/modeld/models")
root.mkdir(parents=True, exist_ok=True)
for name in MODELS:
    url = BASE.format(name)
    dest = root / name
    with urlopen(url) as resp, open(dest, "wb") as out:
        out.write(resp.read())
    print(f"synced {name} -> {dest.stat().st_size} bytes")
PY

# set git username/password
#source /data/identity.sh

git rm -rf $OUTPUT_DIR/.git || true # Doing cleanup, but it might fail if the .git doesn't exist or not allowed to delete
git remote remove origin || true # ensure cleanup
git remote add origin $GIT_ORIGIN
#git push origin -d $DEV_BRANCH || true # Ensuring we delete the remote branch if it exists as we are wiping it out
git fetch origin $DEV_BRANCH || (git checkout -b $DEV_BRANCH && git commit --allow-empty -m "sunnypilot v$VERSION release" && git push -u origin $DEV_BRANCH)

echo "[-] committing version $VERSION T=$SECONDS"
git add -f .

# include source commit hash and build date in commit
GIT_HASH=$(git --git-dir=$SOURCE_DIR/.git rev-parse HEAD)
DATETIME=$(date '+%Y-%m-%dT%H:%M:%S')
SP_VERSION=$(awk -F\" '{print $2}' $SOURCE_DIR/common/version.h)

# Commit with detailed message
git commit -a -m "sunnypilot v$VERSION
version: sunnypilot v$SP_VERSION (${EXTRA_VERSION_IDENTIFIER})
date: $DATETIME
master commit: $GIT_HASH
"
git branch --set-upstream-to=origin/$DEV_BRANCH
git branch -m $DEV_BRANCH

# Push!
echo "[-] pushing T=$SECONDS"
git push -f origin $DEV_BRANCH
