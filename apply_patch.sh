#!/usr/bin/env bash
# Replay enabled root and vehicle patches; no sync, commits or pushes.
set -euo pipefail
ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$ROOT"
exec python3 - "$@" <<'PYTHON'
import argparse
from pathlib import Path
import subprocess

parser = argparse.ArgumentParser(description="Apply enabled root patches, then opendbc patches, in filename order.")
parser.add_argument("--check", action="store_true", help="check ordinary applicability against the current tree without changes")
parser.add_argument("--3way", dest="three_way", action="store_true", help="explicit three-way apply; stages changes and may leave conflicts")
parser.add_argument("--opendbc-only", action="store_true", help="select only patches/opendbc")
parser.add_argument("--all", action="store_true", help="explicitly select all enabled patches")
parser.add_argument("patch", nargs="?", help="root name/path or opendbc/name.patch; disabled files must be renamed first")
args = parser.parse_args()
root = Path.cwd()
patch_root = root / "patches"
vehicle_root = patch_root / "opendbc"
if args.all and args.patch:
  parser.error("--all cannot be combined with a patch name")
if args.patch:
  given = Path(args.patch)
  if not args.patch.endswith(".patch"):
    parser.error("Only enabled .patch files may be selected; rename .disabled or .temp-disabled files first")
  if given.is_absolute():
    selected = given
  elif given.parts[0] == "patches":
    selected = root / given
  elif given.parts[0] == "opendbc":
    selected = patch_root / given
  else:
    selected = (vehicle_root if args.opendbc_only else patch_root) / given
  selected = selected.resolve()
  allowed = [vehicle_root] if args.opendbc_only else [patch_root, vehicle_root]
  if selected.parent not in allowed or selected.suffix != ".patch" or not selected.is_file():
    parser.error("Patch must be an enabled file directly in patches/ or patches/opendbc/")
  patches = [selected]
else:
  folders = [vehicle_root] if args.opendbc_only else [patch_root, vehicle_root]
  patches = [p for folder in folders for p in sorted(folder.glob("*.patch")) if p.is_file() and not p.is_symlink()]

if not patches:
  print("No enabled patches; nothing to apply.")
for patch in patches:
  prefix = ["--directory=opendbc_repo"] if patch.parent == vehicle_root else []
  cmd = ["git", "apply", *prefix]
  if subprocess.run([*cmd, "--reverse", "--check", str(patch)], capture_output=True).returncode == 0:
    print(f"Already applied: {patch.relative_to(root)}", flush=True)
    continue
  mode = ["--3way"] if args.three_way and not args.check else []
  # Normal apply checks first and never falls back to a mutating conflict mode.
  result = subprocess.run([*cmd, *mode, "--check", str(patch)])
  if result.returncode and not (args.three_way and not args.check):
    raise SystemExit(result.returncode)
  if args.check:
    print(f"Applicable: {patch.relative_to(root)}", flush=True)
    continue
  result = subprocess.run([*cmd, *mode, str(patch)])
  if result.returncode:
    raise SystemExit(result.returncode)
  print(f"Applied: {patch.relative_to(root)}", flush=True)
PYTHON
