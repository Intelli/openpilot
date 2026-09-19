#!/usr/bin/env bash
# Compatibility entry point: named vehicle patch or --all, using the shared runner.
set -euo pipefail
ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
exec bash "$ROOT/apply_patch.sh" --opendbc-only "$@"
