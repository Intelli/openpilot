# EV9 Edition maintenance

This is the ongoing maintenance guide for Intelli/openpilot. See
[AGENTS.md](../AGENTS.md) for repository rules, [the patch workflow](../patches/README.md)
for command details, and [EV9 behavior](EV9_BEHAVIOR.md) for steering, engagement,
signal intent and warning policies.

## Source and routine changes

- Develop on `ev9-dev`. Stable upstream is `firestar5683/StarPilot`, branch
  **`StarPilot`**; `Dom` is not the sync target. [starpilot-upstream.json](../starpilot-upstream.json)
  records the imported commit and tree.
- Edit vehicle code under `opendbc_repo/opendbc/`; `opendbc` is a symlink there.
  Dependencies are tracked files. The standalone Intelli/opendbc checkout is
  historical reference only.
- Keep application edits and their enabled patches together. Stage the intended
  source before `./create_patch.sh <name>` or `./update_patch.sh <name>`; unstaged
  source is not exported. Updating retains the patch's original baseline and hunks.
  Review scope carefully when several patches touch the same file.
- Maintenance tooling and the documents explicitly listed in `sync-upstream.sh`
  are preserved directly. Application customizations belong in patches; do not
  preserve application paths to bypass replay.

## Upstream sync

1. Save application edits and refresh their patches before importing upstream.
   `./sync-upstream.sh --check` fetches the stable tip and previews differences.
2. `./sync-upstream.sh --allow` replaces and stages the upstream source, including
   committed local customizations. Maintenance paths and patch archives survive.
3. Run `./apply_patch.sh` to restore enabled customizations, then review and stage
   the resulting source. Sync does not replay patches; neither command commits or pushes.
4. Run focused checks and verify the patch series against the recorded baseline
   before committing the source, patches and applicable documentation together.

Replay applies `patches/*.patch` alphabetically, then `patches/opendbc/*.patch`
alphabetically. Normal replay leaves staging unchanged and stops on failure.
`--3way` explicitly permits staging and conflict markers. Current-tree
`--check` checks patches independently; it does not validate dependent replay.

## Patch ownership

Only `.patch` files directly in the two directories above are enabled. Disabled
suffixes and nested archives are never replayed. The tables identify ownership;
the filename order determines replay order.

| Application patch (`patches/`) | Scope |
| --- | --- |
| `alerts_starpilot.patch` | Compact alerts and silent braking while AOL steering continues |
| `boot_logo_ev9_edition.patch` | Boot artwork and references |
| `build_config_starpilot.patch` | Explicit editable-install import root |
| `custom_defaults_starpilot.patch` | Defaults, EV9 fingerprint, parameters and button migration |
| `custom_model_ui_starpilot.patch` | EV9 path style and independent warning highlighting |
| `customize_warnings_starpilot.patch` | Steering-warning policy and driver-input suppression |
| `drive_helpers_starpilot.patch` | Tuning broadcast, curvature, calibration, AOL and original EV9 signal-turn handling |
| `ev9_edition_starpilot.patch` | Branding and EV9-only control restriction |
| `ev9_longitudinal_status.patch` | Startup longitudinal-mode notice and display telemetry |
| `ev9_turn_lead_hesitation.patch` | Preview handoff, fixed 25.2 km/h ceiling and speed/braking fades |
| `lane_change_safeguards_starpilot.patch` | Lane-change safeguards, turn-speed split and signal intent through stops/inactivity |
| `settings_ui_starpilot.patch` | Shared flat settings layout |
| `ui_options_starpilot.patch` | Steering page and EV9 controls |

| Vehicle patch (`patches/opendbc/`) | Scope |
| --- | --- |
| `01_customize_warnings_starpilot.patch` | 0.3-second steering-saturation timer |
| `02_door_signals_starpilot.patch` | All four CAN-FD doors |
| `03_modify_baseline_starpilot.patch` | EV9 vehicle model, safety identification and flag decoding |
| `04_panda_safety_limits_starpilot.patch` | Safety limits and stock-LKAS forwarding ownership |
| `05_steering_and_ev9_limits_starpilot.patch` | Controller limits, override effort, HOD and manual handoff |
| `06_ev9_tests_starpilot.patch` | Vehicle/controller/native-safety regressions |

## Verification and deployment

Use focused tests for changed behavior. For maintenance tooling, run
`python -m pytest tools/ci/tests -q -o addopts='' --confcutdir=tools/ci/tests` in
the repository environment; these tests use disposable repositories. Verify enabled
patches replay from the recorded baseline and reproduce their affected files.
Host-native extensions and `libsafety.so` must be built separately from tracked
AGNOS binaries. Host checks do not replace a device build or on-vehicle validation.

Pushing `ev9-dev` triggers the GitHub device build, which publishes `ev9-prebuilt`;
the workflow on `master` then promotes the exact built tree to `ev9`. Install
`Intelli/ev9`. `ev9-prebuilt` is a single parentless snapshot with a `Source-Commit`
trailer; `ev9` retains history and records both `Source-Commit` and `Build-Commit`.
Tracked AGNOS binaries and `prebuilt` make source-only promotion unsafe. Parameter,
schema and native changes must ship with their rebuilt binaries.

Keep the GitHub build as the deployment gate. The build workflow is still named
`sunnypilot prebuilt action` because the `master` workflow subscribes to that name;
coordinate both before renaming it. Do not run publication scripts as local checks.
For device issues, follow [the recent-drive review workflow](RECENT_DRIVE_REVIEW.md)
to verify the recorded build and effective settings before diagnosing behavior.

## Historical material

The Sunnypilot migration is complete; original `.migrated`, `.temp-disabled` and
`.disabled` patches remain historical references. The historical custom
lane-centering, driver-monitoring and power-management patches remain deferred;
native StarPilot features are separate. The old prebuilt patch was replaced by
the maintained build tooling. Archived helper scripts are reference only.

The custom EV9 planner is retired. Its [code and notes](../patches/archive/EV9_CUSTOM_PLANNER.md)
are preserved under `patches/archive/` and excluded from replay. The former
extended-speed preview guard remains `ev9_turn_signal_edge_guard.patch.disabled`.
See [patch archive conventions](../patches/README.md#patch-locations-and-state)
for provenance and suffix rules. Current behavior belongs in the two guides above;
the [changelog](../patches/CHANGELOG.md) records earlier audits and changes.
