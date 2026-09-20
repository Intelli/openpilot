# Repository Guidelines

## Repositories & Branches
- This checkout: `https://github.com/Intelli/openpilot`, at `/Volumes/2TB/Documents/GitHub/openpilot`.
- Companion checkout: `https://github.com/Intelli/opendbc`, at `/Volumes/2TB/Documents/GitHub/opendbc`; read its `AGENTS.md` before editing there.
- Develop in `ev9-dev` in both repositories. Target `ev9-dev` for development PRs; `master` is GitHub's default branch, not this project's development target.
- `ev9` contains automatically synced source, and openpilot's `ev9-prebuilt` contains deployment output. Make source changes on `ev9-dev`.

## Project Structure & Modules
- Core: `selfdrive/`, `system/`, `common/`, `cereal/`, `panda/`, `sunnypilot/`, `tools/`, `docs/`.
- Import as `openpilot.<module>`; the `openpilot/` package contains links to source directories such as `common/`.
- After clone: `git lfs pull && git submodule update --init --recursive`.

## opendbc Edit Routing
- Make opendbc source changes in the standalone repository, including requests expressed through this checkout's `opendbc/` symlink or `opendbc_repo/` submodule.
- This checkout's `opendbc/` resolves to `opendbc_repo/opendbc/`. The standalone repository also has a nested `opendbc/` package.
- Example: `/Volumes/2TB/Documents/GitHub/openpilot/opendbc/car/hyundai/carcontroller.py` → `/Volumes/2TB/Documents/GitHub/opendbc/opendbc/car/hyundai/carcontroller.py`.
- Openpilot imports its own pinned submodule checkout, not the standalone working tree. Editing the standalone repository does not update openpilot's imports or builds.

## Build & Source Sync on GitHub
- Pushing opendbc `ev9-dev` triggers its `ev9-sync.yaml`, which copies the complete tracked source tree into a new commit on opendbc `ev9`, preserving separate branch history.
- After that sync succeeds, update openpilot's `opendbc_repo` to the resulting opendbc `ev9` commit and commit the submodule pointer on openpilot `ev9-dev`.
- `.gitmodules` names opendbc's `ev9` branch, but normal submodule checkout still uses the committed SHA; there is no automatic cross-repository pointer update.
- Pushing openpilot `ev9-dev` triggers `.github/workflows/sunnypilot-build-prebuilt.yaml`, which builds and publishes `ev9-prebuilt` under the current deployment configuration.
- Successful completion triggers [the source-sync workflow on `master`](https://github.com/Intelli/openpilot/blob/master/.github/workflows/ev9-sync.yaml), copying openpilot `ev9-dev` into `ev9`. That workflow is absent from the local `ev9-dev` checkout.
- Retain the existing GitHub build as the deployment gate; do not add a separate test gate unless requested. Local checks should still match the change being made.
- The build checkout and sync scripts currently resolve branch heads rather than consistently pinning the triggering SHA; account for this when tracing overlapping runs.
- `release/ci/publish.sh` overlays selected upstream artifacts from sunnypilot's `hkg-angle-steering-2025-prebuilt` onto the build output, including UI and Panda board binaries. Review that overlay when changing compiled components; a successful local build does not guarantee its binaries are the ones published.
- Sync and publish scripts push remote branches. They are deployment tooling, not local setup commands.

## Build, Test, and Development
- Run these commands from the openpilot repository root unless otherwise stated.
- Python: `>=3.12.3,<3.13`; use the version pinned in `.python-version` and this checkout's `.venv`, not the system Python.
- macOS setup: `./tools/op.sh setup`; activate the environment with `source .venv/bin/activate` in the shell that will run subsequent commands.
- Dependencies only: `uv sync --frozen --all-extras`. This preserves the checked-in lockfile.
- Build: `scons -j$(nproc)`; fast dev: `scons --minimal -j$(nproc)`; manager build entry point: `python3 system/manager/build.py`.
- Lint: `scripts/lint/lint.sh` (`--fast` available).
- Tests: `pytest -n auto -m "not slow"`.
- Run HKG safety checks from the standalone opendbc root using its environment: `source .venv/bin/activate`, then `python -m unittest opendbc.safety.tests.test_hyundai_canfd.TestHyundaiCanfdLKASteeringAltEVAngleEV9 -q`.

## Coding Style & Conventions
- Python: 2-space indent, 160 cols; `snake_case`/`CamelCase`/UPPER_SNAKE`. Imports under `openpilot.*` (Ruff enforces).
- C/C++: clang/clang++ via SCons (C++17), warnings-as-errors; optional `.clang-tidy`.
- Tools: Ruff, ty, Codespell (see `pyproject.toml` and `scripts/lint/lint.sh`).

## Testing Guidelines
- Place tests alongside modules in paths from `pyproject.toml:testpaths` and include a verification route when relevant.

## Architecture Overview (HKG Angle Steering)
- Branch `ev9-dev` adds angle steering for newer Hyundai/Kia/Genesis CAN-FD cars (e.g., `KIA_EV9`), with source synced to `ev9` for deployment.
- This branch is currently locked to EV9 deployments; `selfdrived` injects `startupNoControl` when the fingerprint is not `CAR.KIA_EV9`, leaving non-EV9 vehicles in dashcam-only mode.
- Flag-driven path: `HyundaiFlags.CANFD_ANGLE_STEERING` toggles torque vs angle control.
- Flow:
  `controlsd` → `opendbc.car.hyundai.carcontroller:CarController` (angle path) →
  `hyundaicanfd.create_steering_messages()` → EPS/ADAS; Panda safety (`opendbc/safety/modes/hyundai_canfd.h`) enforces angle/jerk limits via vehicle model.
- `controlsd`'s `clip_curvature` low-speed branch has EV9-specific safety headroom (±4.2 m/s²) gated by `HkgTuningAngleCustomLimitMaxSpeedKph`; this path only runs on EV9 angle-steering builds, and the harder limits are still enforced later by `apply_steer_angle_limits_vm` and Panda.

## Dev Workflow: Add a new HKG angle-steering car
- In the standalone opendbc repository, define the platform in `opendbc/car/hyundai/values.py` with `HyundaiCanFDPlatformConfig` + `HyundaiFlags.CANFD_ANGLE_STEERING`.
- Add fingerprints in that repository's `opendbc/car/hyundai/fingerprints.py`; ensure DBC `hyundai_canfd_generated`.
- Run the targeted EV9 safety command above for EV9 regression coverage, and add/run appropriate safety tests for the new platform.
- Follow the opendbc sync and openpilot submodule update sequence above to integrate the change.
- Build, run tests, and pass `scripts/lint/lint.sh`.

## Angle Control Tuning Tips
- Optional runtime params in `CarController`: `HkgTuningAngleMinTorqueReductionGain`, `HkgTuningAngleMaxTorqueReductionGain`, `HkgTuningAngleActiveTorqueReductionGain`, `HkgTuningOverridingCycles`, `EnableHkgTuningAngleSmoothingFactor`, `HkgTuningAngleMaxAngleRate`. See `opendbc/car/hyundai/carcontroller.py`.

## Commits & Pull Requests
- Commits: concise, imperative summaries; optional scope prefix (e.g., `selfdrive: fix lateral tune`, `UI:`). Squash unrelated changes.
- PRs: use `.github/pull_request_template.md`; include description, verification steps, linked issues, and routes/screenshots when relevant. Keep PRs focused and passing lint/tests.

## Security & Configuration
- Do not commit secrets or personal data. Large/binary artifacts must use Git LFS. Follow `SECURITY.md` for disclosures.
