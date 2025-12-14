#!/usr/bin/env bash
set -euo pipefail

if [ "$#" -lt 6 ]; then
  echo "Usage: $0 <workspace> <output_dir> <branch> <version> <repo_url> <extra_id>"
  exit 0
fi

WORKSPACE="$1"
OUTPUT_DIR="$2"
BRANCH="$3"
VERSION="$4"
REPO_URL="$5"
EXTRA_ID="$6"

echo "publish.sh placeholder"
echo "workspace: $WORKSPACE"
echo "output_dir: $OUTPUT_DIR"
echo "branch: $BRANCH"
echo "version: $VERSION"
echo "repo: $REPO_URL"
echo "extra: $EXTRA_ID"
