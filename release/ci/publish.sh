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

import tarfile
from io import BytesIO

BASE_URL = "https://codeload.github.com/sunnypilot/sunnypilot/tar.gz/refs/heads/hkg-angle-steering-2025-prebuilt"
print("downloading prebuilt repo archive...")
with urlopen(BASE_URL) as resp:
    data = BytesIO(resp.read())

with tarfile.open(fileobj=data, mode="r:gz") as tar:
    members = [m for m in tar.getmembers() if m.name.startswith("sunnypilot-")]
    tar.extractall(path="/tmp", members=members)

root_dir = next(Path("/tmp").glob("sunnypilot-*") )

model_src = root_dir / "selfdrive/modeld/models"
model_dest = Path("selfdrive/modeld/models")
model_dest.mkdir(parents=True, exist_ok=True)
for src in model_src.glob("*.pkl"):
    dest = model_dest / src.name
    dest.write_bytes(src.read_bytes())
    print(f"synced {src.name} -> {dest.stat().st_size} bytes")

def rsync(src, dest):
    if src.is_dir():
        os.system(f"rsync -a '{src}/' '{dest}/'")
    elif src.exists():
        dest.parent.mkdir(parents=True, exist_ok=True)
        dest.write_bytes(src.read_bytes())

import os

rsync(model_src, model_dest)
rsync(root_dir / "cereal/messaging", Path("cereal/messaging"))
rsync(root_dir / "msgq", Path("msgq"))
rsync(root_dir / "msgq_repo/msgq", Path("msgq_repo/msgq"))
rsync(root_dir / "common/params_pyx.so", Path("common/params_pyx.so"))
rsync(root_dir / "selfdrive/pandad", Path("selfdrive/pandad"))
rsync(root_dir / "selfdrive/locationd", Path("selfdrive/locationd"))
rsync(root_dir / "selfdrive/controls/lib/lateral_mpc_lib", Path("selfdrive/controls/lib/lateral_mpc_lib"))
rsync(root_dir / "selfdrive/controls/lib/longitudinal_mpc_lib", Path("selfdrive/controls/lib/longitudinal_mpc_lib"))
rsync(root_dir / "selfdrive/ui", Path("selfdrive/ui"))
rsync(root_dir / "system/loggerd", Path("system/loggerd"))
rsync(root_dir / "panda/board", Path("panda/board"))
rsync(root_dir / "compile_commands.json", Path("compile_commands.json"))

# ensure msgq pyx modules are accessible without hashed suffixes
for pattern, link_name in [("ipc_pyx*.so", "ipc_pyx.so"), ("visionipc_pyx*.so", "visionipc_pyx.so")]:
    matches = list((Path("msgq") ).glob(pattern))
    if matches:
        target = matches[0].name
        link = Path("msgq") / link_name
        if link.exists() or link.is_symlink():
            link.unlink()
        os.symlink(target, link)

print("prebuilt assets synced")
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
