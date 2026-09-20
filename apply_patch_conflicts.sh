#!/usr/bin/env bash
# Explicit conflict-preserving mode: stages changes and can leave merge conflicts.
set -euo pipefail
ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
exec bash "$ROOT/apply_patch.sh" --3way "$@"
