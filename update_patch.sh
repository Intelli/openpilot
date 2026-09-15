#!/usr/bin/env bash
# Replace an existing patch from staged source, preserving its enabled/disabled state.
set -euo pipefail
script_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
exec python3 "$script_dir/tools/patches/create.py" update "$@"
