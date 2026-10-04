# Repository Guidelines

## Repository & Upstream
- Develop on `ev9-dev` in `https://github.com/Intelli/openpilot` at `/Volumes/2TB/Documents/GitHub/openpilot`.
- Application upstream is `https://github.com/sunnypilot/sunnypilot`, branch **`hkg-angle-steering-2025`**. Embedded vehicle upstream is `https://github.com/sunnypilot/opendbc`, the same branch name.
- Current application baseline is Sunnypilot `d021f6ca41375e58be8125801547e84939e0c503`, with embedded opendbc `28303fcd1cc457f67d405407858223e0b338df20` and its exact seven dependency pins vendored. It advances 798 upstream commits from the restoration baseline.
- Historical restoration used pre-StarPilot Intelli `5928a37ad18783068ee26b187f6a7ddb9ff9c3d3`; its customization intent is ported onto the current source, rather than replacing new upstream files.
- `sunnypilot-upstream.json` records the official application baseline and exact dependency provenance. `opendbc-upstream.json` records the independent vehicle baseline. `restored_from` identifies customized historical snapshots; enabled forward patches record their differences from official baselines.
- Target `ev9-dev` for development PRs. `master` hosts the deployment-sync trigger. `ev9-prebuilt` holds the latest GitHub build as one root commit; `ev9` receives that exact built tree while retaining deployment history.

## Project Structure & opendbc Routing
- Application source lives under `openpilot/{selfdrive,system,common,cereal,sunnypilot}/`; dependencies such as `opendbc_repo/` and `panda/`, maintenance `tools/`, and `docs/` remain at the repository root.
- Dependencies are ordinary tracked files. Gitlinks and LFS pointer files are materialized when importing snapshots; no standalone dependency checkout participates in builds. Oversized ONNX payloads are hash-verified, then stored losslessly in 45 MiB chunks with upstream-compatible manifests to stay below GitHub's 100 MiB blob limit.
- Edit vehicle code **in this repository** under `opendbc_repo/opendbc/`. The `opendbc/` symlink points there; for example `opendbc/car/hyundai/carcontroller.py` resolves into the vendored tree.
- `/Volumes/2TB/Documents/GitHub/opendbc` is historical reference only. Do not use it as an input to sync, imports or builds.
- Import application modules as `openpilot.<module>` and vehicle modules as `opendbc.<module>`, following neighboring code.

## Upstream Sync & Patches
- `./sync-upstream.sh --check [ref]` previews the application snapshot and its recursively vendored dependency pins. `./sync-upstream.sh --allow [ref]` imports and stages it.
- `./sync-upstream.sh --opendbc --check [ref]` previews vehicle-only sync; `--opendbc --allow [ref]` replaces only `opendbc_repo/` and its provenance, preserving unrelated application changes and staging.
- Both modes default to `hkg-angle-steering-2025`; explicit branch, tag or commit refs are supported. Fetching and LFS hydration use disposable temporary Git caches, not the historical standalone checkout.
- `--check` does not change source, the index, local configuration or refs. Import refuses dirty source/index paths, untracked/ignored collisions and ongoing merge/rebase operations. Maintenance edits are preserved.
- Reimporting an identical verified snapshot retains exact provenance and root ignore/ordinary-blob attribute rules; repository, commit, tree and every dependency identity must match. New baselines regenerate metadata/rules. After replay and staging, a same-baseline round trip must produce the original Git tree.
- Sync is a snapshot replacement: it removes committed customizations in its scope. It does not merge, replay patches, commit or push. Save application edits and refresh their patches first. `./update.sh` forwards the same arguments.
- Preserve only the maintenance paths explicitly listed in `tools/upstream/sync.py`, including build/sysroot tooling, CI, helpers, archives and maintenance documents. Application behavior belongs in forward patches.
- Root helpers support `patches/` (repository-relative diffs) and `patches/opendbc/` (diffs relative to `opendbc_repo/`). Vehicle application uses `--directory=opendbc_repo`.
- `./apply_patch.sh` replays enabled `.patch` files from the root directory, then the vehicle directory, alphabetically in each. Already-applied patches are skipped. `--check` checks each against the current tree without simulating dependent replay.
- Normal application leaves staging unchanged and stops on failure. `--3way`, also exposed through `apply_patch_conflicts.sh`, explicitly allows staging and conflict markers.
- `./create_patch.sh <name>` exports staged source edits as a forward patch. Use `opendbc/<name>` for vehicle-only exports. It does not sync, replay, stage, commit or push.
- `./update_patch.sh <name>` reconstructs original versions from Git blob IDs and retains committed original hunks. For shared files, it replays the enabled series in disposable indexes and transfers only amendments belonging to the requested feature; ambiguous edits or edits to another feature fail without replacing the patch. Stage new source files to include them automatically; `-- PATH...` overrides scope. `--base <ref>` explicitly replaces the baseline and bypasses feature isolation.
- Enabled patches are twelve numbered application features (`01_`–`12_`), five numbered vehicle features (`opendbc/02_`–`06_`), plus `boot_logo_ev9_edition.patch` and `sunnypilot_device_build.patch`. There are 19 enabled patches. Vehicle baseline physics (`01_`) is now supplied by upstream and archived. See `patches/README.md` for the complete inventory and ownership.
- `patches/baselines/<blob-id>` stores exact original file payloads so automatic updates work after fresh clones. Shared-file updates can add baseline payloads; stage them with the updated patch. Original consolidated restoration patches are archived under `patches/archive/sunnypilot-consolidated-20261004/`.
- StarPilot ports are preserved under `patches/archive/starpilot-20260920/`; historical archive/disabled suffixes are never applied. Legacy helper copies remain references only: their inverse-diff and automatic merge/staging behavior is not the supported workflow.
- See `docs/MAINTENANCE.md` for source and deployment, and `docs/EV9_BEHAVIOR.md` for current vehicle behavior. StarPilot upstream PR history is archival context, not the current sync target.

## GitHub Build & Publication
- Pushing `ev9-dev` runs `.github/workflows/sunnypilot-build-prebuilt.yaml` on `ubuntu-24.04-arm`, pinned to the triggering SHA.
- Keep display name `sunnypilot prebuilt action`: the `master` deployment workflow listens for it. Coordinate changes to both before renaming it.
- Maintained `scripts/laptop_device_build.sh build-image`, `setup-sysroot-agnos`, and `./build` compile the current Sunnypilot tree for AGNOS 19.7 with the `comma_arm64` target. Build/sysroot tooling is preserved by source sync; no artifact overlay or standalone opendbc repository participates.
- `release/ci/publish.sh` publishes a parentless `ev9-prebuilt` commit with a `Source-Commit` trailer, replacing only that branch through an explicit `--force-with-lease` against its fetched tip. It uses `PREBUILT_PUSH_TOKEN` in the `ev9-dev` environment.
- After success, `master` runs `tools/ci/sync_ev9_branch.sh` from `ev9-dev`. It copies the exact built tree to a new historical `ev9` commit, recording `Source-Commit` and `Build-Commit` trailers.
- Promote compiled artifacts with their source. Native/schema/default changes require rebuilt binaries, including `openpilot/common/libparams_c.so` for compiled defaults; source-only promotion and stale `prebuilt` markers are unsafe.
- The fused driving compiler uses the verified pinned QCOM small-model and driver-monitoring captures described in `docs/how-to/laptop-device-build.md`. Optional Chestnut capture is outside that bundle. Host checks do not establish native build or device inference success.
- Defaults initialize missing settings; existing device preferences remain authoritative after updates.
- Keep the GitHub build as the deployment gate. Do not add a separate test gate unless requested. Publication/sync CI scripts push remote branches; do not run them against production as local checks.

## Local Development & Verification
- For C3X updates, follow `docs/C3X_UPDATE_WORKFLOW.md`. An update request authorizes CHECK, DOWNLOAD, INSTALL and reboot through the normal updater; verify installed before/after commits. Check-only remains check-only.
- For recent device behavior, follow `docs/RECENT_DRIVE_REVIEW.md`: verify the recorded build and effective settings, and distinguish qlog evidence from full CAN/ECU confirmation. Keep private logs and signed links outside the repository.
- Python: use this checkout's `.venv` with Python 3.12, matching `pyproject.toml` (`>=3.12.3,<3.13`). Dependencies: `CC=/usr/bin/clang CXX=/usr/bin/clang++ uv sync --frozen --all-extras` on macOS.
- Imported device binaries target AGNOS. Build host-native extensions before tests that import compiled modules. See `docs/how-to/laptop-device-build.md` for the device compilation path.
- Run focused checks appropriate to the current Sunnypilot implementation. Maintenance checks use disposable repositories: `python -m pytest tools/ci/tests -q -o addopts='' --confcutdir=tools/ci/tests`; they do not build or deploy vehicle software.
- Local lint: `scripts/lint/lint.sh`.

## Style, Commits & Security
- Follow `pyproject.toml` and neighboring code: two-space Python indentation, a 160-column limit, and conventional `snake_case`, `CamelCase`, and `UPPER_SNAKE_CASE` names.
- Use concise imperative commit summaries and `.github/pull_request_template.md`, describing behavior and verification.
- Do not commit secrets, personal data, environments or caches. Hydrated imported assets are ordinary Git blobs; check GitHub size limits before adding large assets.
