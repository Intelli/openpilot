"""Python startup hooks used during dependency installation on macOS arm64.

This module is injected via ``PYTHONPATH`` when we run ``uv`` to install
dependencies on Apple Silicon machines. The dependency metadata in
``pyproject.toml`` commonly relies on the ``platform_machine`` environment
marker, which expects Linux-style ``"aarch64"`` for ARM64 hardware. On macOS,
``platform.machine()`` returns ``"arm64"`` instead, which causes those markers
to evaluate incorrectly and pull in packages that should stay excluded.

By overriding ``platform.machine`` (and related helpers) to report
``"aarch64"`` when running on Apple Silicon, we ensure that environment
markers treat macOS ARM runners the same as aarch64 Linux hosts during the
installation step. The override is intentionally scoped to the short-lived
process that imports this module; runtime code continues to observe the
default ``"arm64"`` identifier.
"""

from __future__ import annotations

import os
import platform
from typing import Callable


_MACHINE_ALIASES = {
  "arm64": "aarch64",
  # Keep the canonical case we expect environment markers to reference.
}


def _patch_platform_machine(machine: str, alias: str) -> None:
  """Override platform helpers so they return *alias* instead of *machine*."""

  def machine_override() -> str:
    return alias

  platform.machine = machine_override  # type: ignore[assignment]

  try:
    original_uname = platform.uname
  except AttributeError:
    original_uname = None

  if original_uname is not None:

    def uname_override() -> platform.uname_result:
      result = original_uname()
      if getattr(result, "machine", None) == machine:
        return result._replace(machine=alias)
      return result

    platform.uname = uname_override  # type: ignore[assignment]

  if hasattr(os, "uname"):
    original_os_uname: Callable[..., os.uname_result] = os.uname  # type: ignore[assignment]

    def os_uname_override(*args, **kwargs) -> os.uname_result:
      result = original_os_uname(*args, **kwargs)
      if getattr(result, "machine", None) == machine:
        return result._replace(machine=alias)
      return result

    os.uname = os_uname_override  # type: ignore[assignment]


def _apply_alias_if_needed() -> None:
  machine = platform.machine()
  alias = _MACHINE_ALIASES.get(machine.lower())
  if alias is None or machine == alias:
    return

  _patch_platform_machine(machine, alias)


_apply_alias_if_needed()


