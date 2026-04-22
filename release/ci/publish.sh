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
echo "#define SUNNYPILOT_VERSION \"$VERSION\"" > ${OUTPUT_DIR}/sunnypilot/common/version.h

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
import shutil
import tempfile
import os

BASE_URL = "https://codeload.github.com/sunnypilot/sunnypilot/tar.gz/refs/heads/hkg-angle-steering-2025-prebuilt"
print("downloading prebuilt repo archive...")
with urlopen(BASE_URL) as resp:
    data = BytesIO(resp.read())

with tempfile.TemporaryDirectory() as tmpdir:
    tmp_path = Path(tmpdir)
    with tarfile.open(fileobj=data, mode="r:gz") as tar:
        members = [m for m in tar.getmembers() if m.name.startswith("sunnypilot-")]
        tar.extractall(path=tmp_path, members=members)

    root_dir = next(tmp_path.glob("sunnypilot-*/"))

    print(f"extracted prebuilt archive to {root_dir}")

    DISALLOWED_SUFFIXES = {
        ".py",
        ".pyi",
        ".pyx",
        ".pxd",
        ".pxi",
        ".c",
        ".cc",
        ".cxx",
        ".h",
        ".hpp",
        ".hh",
    }

    def should_copy_file(path: Path) -> bool:
        return path.suffix not in DISALLOWED_SUFFIXES

    # When set to 1, we keep locally built artifacts and only fill in gaps.
    # When set to 0, upstream prebuilts always overwrite local build outputs.
    DISABLE_UPSTREAM_OVERWRITES = 0

    FORCE_UPSTREAM_OVERWRITES = {
        "selfdrive/modeld/models",
        "sunnypilot/modeld",
        "sunnypilot/modeld_v2",
        "sunnypilot/modeld/models",
        "opendbc_repo/opendbc/dbc/generator",
    }
    PROTECTED_FILES = {
        Path("common/params_pyx.so"),
        Path("common/transformations/transformations.so"),
    }

    def copy_entry(rel_path: str):
        src = root_dir / rel_path
        dest = Path(rel_path)
        if not src.exists():
            print(f"warning: missing {rel_path} in prebuilt archive")
            return
        if src.is_dir():
            overwrite = rel_path in FORCE_UPSTREAM_OVERWRITES
            for root, _, files in os.walk(src):
                rel_root = Path(root).relative_to(src)
                (dest / rel_root).mkdir(parents=True, exist_ok=True)
                for file in files:
                    src_file = Path(root) / file
                    if not should_copy_file(src_file):
                        continue
                    dest_file = dest / rel_root / file
                    dest_file.parent.mkdir(parents=True, exist_ok=True)
                    rel_target = Path(rel_path) / rel_root / file
                    if rel_target in PROTECTED_FILES:
                        continue
                    if DISABLE_UPSTREAM_OVERWRITES and dest_file.exists() and not overwrite:
                        continue
                    shutil.copy2(src_file, dest_file)
        else:
            overwrite = rel_path in FORCE_UPSTREAM_OVERWRITES
            if not should_copy_file(src):
                return
            dest.parent.mkdir(parents=True, exist_ok=True)
            if Path(rel_path) in PROTECTED_FILES:
                return
            if DISABLE_UPSTREAM_OVERWRITES and dest.exists() and not overwrite:
                return
            shutil.copy2(src, dest)

    FILES_TO_COPY = [
        "common/params_pyx.so",
        "common/transformations/transformations.so",
        "selfdrive/ui/ui",
        "sunnypilot/modeld/libthneed.so",
        "sunnypilot/modeld/runners/thneedmodel_pyx.cpp",
        "sunnypilot/modeld/runners/thneedmodel_pyx.so",
        "compile_commands.json",
        "system/camerad/camerad",
    ]

    for rel in FILES_TO_COPY:
        copy_entry(rel)

    DIRS_TO_COPY = [
        "cereal/messaging",
        "msgq",
        "msgq_repo/msgq",
        "selfdrive/modeld/models",
        "selfdrive/pandad",
        "selfdrive/locationd",
        "selfdrive/controls/lib/lateral_mpc_lib",
        "selfdrive/controls/lib/longitudinal_mpc_lib",
        "system/loggerd",
        "panda/board",
        "sunnypilot/modeld",
        "sunnypilot/modeld_v2",
        "sunnypilot/selfdrive/locationd",
        "rednose_repo/rednose/helpers",
    ]

    for rel in DIRS_TO_COPY:
        copy_entry(rel)

    def ensure_unhashed(lib_dir: Path, pattern: str, target: str):
        matches = sorted(lib_dir.glob(pattern))
        if matches:
            dest = lib_dir / target
            dest.write_bytes(matches[0].read_bytes())

    ensure_unhashed(Path("msgq"), "ipc_pyx*.so", "ipc_pyx.so")
    ensure_unhashed(Path("msgq"), "visionipc_pyx*.so", "visionipc_pyx.so")
    ensure_unhashed(Path("msgq_repo/msgq"), "ipc_pyx*.so", "ipc_pyx.so")
    ensure_unhashed(Path("msgq_repo/msgq"), "visionipc_pyx*.so", "visionipc_pyx.so")

    # copy only compiled UI translation files so Python sources remain untouched
    ui_translations_src = root_dir / "selfdrive/ui/translations"
    if ui_translations_src.exists():
        dest_dir = Path("selfdrive/ui/translations")
        dest_dir.mkdir(parents=True, exist_ok=True)
        for src in ui_translations_src.glob("*.qm"):
            copy_entry(f"selfdrive/ui/translations/{src.name}")


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
SP_VERSION=$(awk -F\" '{print $2}' $SOURCE_DIR/sunnypilot/common/version.h)

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
