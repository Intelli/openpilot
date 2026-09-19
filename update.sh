#!/usr/bin/env bash
# Compatibility entry point: opendbc now updates with the whole StarPilot tree.
set -euo pipefail
script_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
exec "$script_dir/sync-upstream.sh" "$@"
