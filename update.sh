#!/usr/bin/env bash
# Compatibility entry point for Sunnypilot and scoped embedded opendbc imports.
set -euo pipefail
script_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
exec "$script_dir/sync-upstream.sh" "$@"
