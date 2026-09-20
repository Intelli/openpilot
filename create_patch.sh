#!/usr/bin/env bash
# Export staged edits as a forward patch; never sync or replay source changes.
set -euo pipefail
script_dir="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
exec python3 "$script_dir/tools/patches/create.py" create "$@"
