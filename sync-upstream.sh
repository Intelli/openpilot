#!/usr/bin/env bash
# Import Sunnypilot snapshots; no merges, commits, deployment or patch replay.
set -euo pipefail
ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
exec python3 "$ROOT/tools/upstream/sync.py" "$@"
