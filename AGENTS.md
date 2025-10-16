# Repository Guidelines

## Project Structure & Modules
- Core: `selfdrive/`, `system/`, `common/`, `cereal/`, `panda/`, `sunnypilot/`, `tools/`, `docs/`.
- Python import root is `openpilot/` (symlink). Import as `openpilot.<module>`.
- After clone: `git lfs pull && git submodule update --init --recursive`.

## Build, Test, and Development
- macOS setup: `tools/mac_setup.sh`.
- Build: `scons -j$(nproc)`; fast dev: `scons --minimal -j$(nproc)`; run: `python3 system/manager/build.py`.
- Lint: `scripts/lint/lint.sh` (`--fast` available).
- Tests: `pytest -n auto -m "not slow"`; HKG safety: `pytest opendbc/safety/tests/test_hyundai_canfd.py -q`.

## Coding Style & Conventions
- Python: 2-space indent, 160 cols; `snake_case`/`CamelCase`/UPPER_SNAKE`. Imports under `openpilot.*` (Ruff enforces).
- C/C++: clang/clang++ via SCons (C++17), warnings-as-errors; optional `.clang-tidy`.
- Tools: Ruff, MyPy, Codespell (see `pyproject.toml`).

## Testing Guidelines
- Place tests alongside modules in paths from `pyproject.toml:testpaths` and include a verification route when relevant.

## Architecture Overview (HKG Angle Steering)
- Branch `ev9` adds angle steering for newer Hyundai/Kia/Genesis CAN-FD cars (e.g., `KIA_EV9`).
- This branch is currently locked to EV9 deployments; `selfdrived` injects `startupNoControl` when the fingerprint is not `CAR.KIA_EV9`, leaving non-EV9 vehicles in dashcam-only mode.
- Flag-driven path: `HyundaiFlags.CANFD_ANGLE_STEERING` toggles torque vs angle control.
- Flow:
  `controlsd` → `opendbc.car.hyundai.carcontroller:CarController` (angle path) →
  `hyundaicanfd.create_steering_messages()` → EPS/ADAS; Panda safety (`opendbc/safety/modes/hyundai_canfd.h`) enforces angle/jerk limits via vehicle model.
- `controlsd`'s `clip_curvature` low-speed branch has EV9-specific safety headroom (±4.2 m/s²) gated by `HkgTuningAngleCustomLimitMaxSpeedKph`; this path only runs on EV9 angle-steering builds, and the harder limits are still enforced later by `apply_steer_angle_limits_vm` and Panda.

## Dev Workflow: Add a new HKG angle-steering car
- Define platform in `opendbc/car/hyundai/values.py` with `HyundaiCanFDPlatformConfig` + `HyundaiFlags.CANFD_ANGLE_STEERING`.
- Add fingerprints in `opendbc/car/hyundai/fingerprints.py`; ensure DBC `hyundai_canfd_generated`.
- Validate safety (angle path): `pytest opendbc/safety/tests/test_hyundai_canfd.py::TestHyundaiCanfdLKASteeringAltEVAngle -q`.
- Build, run tests, and pass `scripts/lint/lint.sh`.

## Angle Control Tuning Tips
- Optional runtime params in `CarController`: `HkgTuningAngleMinTorqueReductionGain`, `HkgTuningAngleMaxTorqueReductionGain`, `HkgTuningAngleActiveTorqueReductionGain`, `HkgTuningOverridingCycles`, `EnableHkgTuningAngleSmoothingFactor`, `HkgTuningAngleMaxAngleRate`. See `opendbc/car/hyundai/carcontroller.py`.

## Commits & Pull Requests
- Commits: concise, imperative summaries; optional scope prefix (e.g., `selfdrive: fix lateral tune`, `UI:`). Squash unrelated changes.
- PRs: use `.github/pull_request_template.md`; include description, verification steps, linked issues, and routes/screenshots when relevant. Keep PRs focused and passing lint/tests.

## Security & Configuration
- Do not commit secrets or personal data. Large/binary artifacts must use Git LFS. Follow `SECURITY.md` for disclosures.
