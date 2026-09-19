#!/usr/bin/env bash
# Compatibility alias: patch creation now always uses staged edits.
set -euo pipefail
script_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
exec "$script_dir/create_patch.sh" "$@"
