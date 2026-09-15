# Repository Guidelines

## Repository & Upstream
- Develop in `ev9-dev` in `https://github.com/Intelli/openpilot` at `/Volumes/2TB/Documents/GitHub/openpilot`.
- Stable upstream is `https://github.com/firestar5683/StarPilot`, branch **`StarPilot`**. `Dom` is upstream development and is not our sync target.
- `starpilot-upstream.json` records the imported commit/tree. Application source currently matches that snapshot; historical Intelli patches are retained but **not applied**.
- Target `ev9-dev` for development PRs. `master` is GitHub's default branch and hosts the source-sync trigger. `ev9` is generated source; `ev9-prebuilt` is generated deployment output.

## Project Structure & opendbc Routing
- Core: `selfdrive/`, `system/`, `common/`, `cereal/`, `starpilot/`, `panda/`, `tools/`, `docs/`.
- StarPilot vendors its dependencies as ordinary tracked files. This tree has no Git submodules or LFS attributes.
- Edit vehicle code **in this repository** under `opendbc_repo/opendbc/`. The `opendbc/` symlink points there.
- Example: `opendbc/car/hyundai/carcontroller.py` resolves to `opendbc_repo/opendbc/car/hyundai/carcontroller.py` in this checkout.
- `/Volumes/2TB/Documents/GitHub/opendbc` is a historical reference only. It is not an input to this repository's sync, imports or build.
- Import application modules as `openpilot.<module>` and vehicle modules as `opendbc.<module>`, following neighboring code.

## Upstream Sync & Historical Patches
- `./sync-upstream.sh --check` fetches the stable tip and previews source differences against HEAD.
- `./sync-upstream.sh --allow` imports and stages the stable source tree, preserving maintenance tooling and patch archives. It makes no commits or pushes.
- `./update.sh` is a compatibility alias for that sync, with the same arguments.
- Save application changes before syncing. Sync is a tree replacement: it removes committed local application customizations. It never replays patches.
- Preserve the explicit maintenance paths listed in `sync-upstream.sh`; do not add application paths to that list to hide a customization from upstream sync.
- Original openpilot patch helpers remain at the root, with patches in `patches/`. Copied opendbc patches are in `patches/opendbc/`; original opendbc helpers are archived in `tools/opendbc-patches/legacy/`.
- Do not run legacy patch or inverse-generation helpers automatically. Porting individual patches is separate work and requires reviewing StarPilot's existing behavior first.
- `tools/opendbc-patches/apply.sh --check <name.patch>` can check one archived vehicle patch using the new path prefix. See its README before explicit replay.
- See `docs/STARPILOT_MIGRATION.md` for provenance, archive layout and migration details.

## GitHub Build & Publication
- Pushing `ev9-dev` runs `.github/workflows/sunnypilot-build-prebuilt.yaml` on `ubuntu-24.04-arm`, pinned to the triggering SHA.
- The workflow retains the display name `sunnypilot prebuilt action` because the existing `.github/workflows/ev9-sync.yaml` on `master` listens for it. Coordinate changes to both before renaming it.
- Build uses StarPilot's `scripts/laptop_device_build.sh build-image`, `setup-sysroot-agnos`, then `./build`. No standalone opendbc checkout or Sunnypilot artifact overlay participates.
- `release/ci/publish.sh` publishes the built tree to `ev9-prebuilt` with a `Source-Commit` trailer. It uses the existing `PREBUILT_PUSH_TOKEN` in the `ev9-dev` environment.
- After success, the workflow on `master` runs `tools/ci/sync_ev9_branch.sh`. It copies the source tree recorded by the published build into a new commit on `ev9`, preserving that branch's history.
- Keep the GitHub build as the deployment gate. Do not add a separate test gate unless requested. Sync/publish CI scripts push remote branches; do not run them against production as local checks.

## Local Development & Verification
- Python: use 3.11 or 3.12, matching `pyproject.toml` (`>=3.11,<3.13`), with this checkout's `.venv`.
- macOS setup: `./tools/mac_setup.sh`. Dependencies only: `CC=/usr/bin/clang CXX=/usr/bin/clang++ uv sync --frozen --all-extras`; activate with `source .venv/bin/activate`.
- The imported device binaries target AGNOS. Build native extensions for macOS before running tests that import compiled modules. See upstream `docs/how-to/laptop-device-build.md` for the device build path.
- Local build: `scons -j$(sysctl -n hw.ncpu)` on macOS, or `scons -j$(nproc)` on Linux. Lint: `scripts/lint/lint.sh`.
- Run focused checks appropriate to a change; do not assume old Intelli EV9 test classes or tuning parameters still exist in stock StarPilot.
- Maintenance integration tests use disposable Git repositories: `python -m pytest tools/ci/tests -q -o addopts='' --confcutdir=tools/ci/tests`. They do not build or deploy vehicle software.

## Style, Commits & Security
- Follow `pyproject.toml` and neighboring code: Python uses two-space indentation and a 160-column limit; `snake_case`, `CamelCase`, and `UPPER_SNAKE_CASE` as appropriate.
- Use concise imperative commit summaries. Use `.github/pull_request_template.md` and describe the behavior change and relevant verification.
- Do not commit secrets, personal data, local environments or build caches. Preserve upstream's existing binary storage format; check GitHub size limits before adding new large assets.
