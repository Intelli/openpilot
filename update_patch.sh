#!/usr/bin/env bash
# Update from staged/committed source using the existing patch's base; --base optionally overrides it.
set -euo pipefail
script_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
exec python3 "$script_dir/tools/patches/create.py" update "$@"
