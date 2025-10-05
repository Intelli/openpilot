#!/usr/bin/env bash
set -e

# Increase the pip timeout to handle TimeoutError
export PIP_DEFAULT_TIMEOUT=200
export UV_NO_VERIFY=1
export UV_INSTALL_SKIP_HASH_CHECK=1

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null && pwd )"
ROOT="$DIR"/../
cd "$ROOT"

if ! command -v "uv" > /dev/null 2>&1; then
  echo "installing uv..."
  curl -LsSf https://astral.sh/uv/install.sh | sh
  UV_BIN="$HOME/.local/bin"
  PATH="$UV_BIN:$PATH"
fi

echo "updating uv..."
# ok to fail, can also fail due to installing with brew
uv self update || true

UV_SYNC_FLAGS=${UV_SYNC_FLAGS:-"--frozen --all-extras"}
echo "installing python packages with uv sync $UV_SYNC_FLAGS"
# The mac setup script injects a sitecustomize module through PYTHONPATH to
# normalize platform.machine() for environment markers when running on
# Apple Silicon. Make sure we retain that behavior if PYTHONPATH is already
# set by the caller.
if [[ -n "$PYTHONPATH" ]]; then
  export PYTHONPATH="$PYTHONPATH"
fi

if [[ -n "$UV_EXCLUDE_PACKAGES" ]]; then
  echo "excluding packages: $UV_EXCLUDE_PACKAGES"
fi
uv sync $UV_SYNC_FLAGS
source .venv/bin/activate

if [[ "$(uname)" == 'Darwin' ]]; then
  touch "$ROOT"/.env
  echo "# msgq doesn't work on mac" >> "$ROOT"/.env
  echo "export ZMQ=1" >> "$ROOT"/.env
  echo "export OBJC_DISABLE_INITIALIZE_FORK_SAFETY=YES" >> "$ROOT"/.env
fi
