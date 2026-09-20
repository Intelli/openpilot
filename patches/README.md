# Intelli patch workflow

The custom EV9 planner is retired. Its implementation and tests are preserved in
[`archive/ev9_custom_planner.patch`](archive/ev9_custom_planner.patch), and all
planner notes are consolidated in [`archive/EV9_CUSTOM_PLANNER.md`](archive/EV9_CUSTOM_PLANNER.md).
Both files survive upstream sync; neither is part of normal patch replay.

For the cumulative behavior changes from stock StarPilot, see the
[EV9 Edition changelog](CHANGELOG.md).

Historical patch contents are preserved; **none are applied to the initial
stable StarPilot baseline**. Upstream sync and GitHub builds do not replay them.

## Patch locations and state

| Location / suffix | Meaning |
| --- | --- |
| `patches/<name>.patch` | Enabled patch using paths relative to the main repository |
| `patches/opendbc/<name>.patch` | Enabled vehicle patch using paths relative to `opendbc_repo/` |
| `patches/archive/` | Retired code and notes; preserved by sync and excluded from patch replay |
| `.patch.temp-disabled` | One of the 17 formerly enabled patches, paused for StarPilot porting |
| `.patch.migrated` | Unchanged historical original whose supported port is recorded in an enabled patch or replacement build tooling |
| `.disabled` (including `.patch.OUTDATED.disabled`) | A patch that was already disabled before migration |

The 17 formerly enabled patches started as temporarily disabled archives. Migrated
originals now use `.migrated`; the six previously disabled patches keep their
original suffixes. All archive suffixes are skipped by application. Port source,
export a new enabled patch, then rename the historical original to `.migrated`.
Keep the original contents intact. Updating a disabled patch keeps its suffix;
exporting a new patch defaults to enabled, or accepts an explicit disabled suffix
when you want to keep it inactive.

The six migrated vehicle patches use prefixes `01_` through `06_` to preserve their
dependency order. The established root patches contain build configuration, custom defaults, EV9 Edition branding and boot artwork,
settings UI, EV9 control configuration/curvature, warning policy, compact alerts,
EV9 settings controls, the EV9 animated path effect, and the startup longitudinal-status notice. Only lane centering,
driver monitoring and power management remain `.temp-disabled` by request. The old prebuilt
patch is archived as `.migrated` because the StarPilot build/publish tooling has
already replaced its Sunnypilot implementation; it is not replayed.
See the migration guide for current EV9 behavior and patch ownership.

`ev9_turn_lead_hesitation.patch` separately preserves the EV9 angle-control
turn-lead fix and its focused tests: current preview assistance no longer fades
with wheel catchup, and opposing model demand vetoes that assistance. It also
retains smooth speed and stopping-distance envelopes with a fixed preview
ceiling of 7 m/s (25.2 km/h), independent of EV9 Limits Speed, and focused tests. It works
without the retired custom planner and excludes its messaging, tracking and
handoff changes. When refreshing it, retain only these turn-lead
changes and tests: exporting all later `controlsd.py` changes from its original
base would also pull in unrelated planner changes.

The extended-speed road-edge guard is retired in
`ev9_turn_signal_edge_guard.patch.disabled`; normal replay does not restore it.
Restoring the preview ceiling does not change the current EV9 turn-desire rules:
predicted stops do not veto signal turn desires while moving, and their speed
split remains the greater of EV9 Limits Speed and Minimum Lane Change Speed.
Actual standstill still prevents a turn desire.

`ui_options_starpilot.patch` exposes the four EV9 steering controls on C3/C3X,
C4 and Galaxy, plus EV9 Path in Galaxy. The device path controls/renderers remain
in `custom_model_ui_starpilot.patch`.

`ev9_longitudinal_status.patch` adds a C3/C3X startup notice: flashing **OP long
ready** while waiting for brake + Start, then bright purple-gradient **OP long** for 30 seconds
after vehicle READY. **Stock ACC** stays solid green. It includes display-only EV9
READY telemetry and tests; it does not change takeover or emergency braking behavior.

`drive_helpers_starpilot.patch` also normalizes the EV9 OP-long cruise knob:
up/down/in engage when inactive; up resumes a saved speed when available, while
down/in follow normal SET initialization. While engaged, up/down adjust speed
and in cancels. Vehicle patch `04` includes the matching native permission checks,
with regressions in `06`. Stock ACC and other vehicles keep their existing controls.

Steering/AOL follow-ups are incorporated into the existing custom-defaults,
alerts, warning and drive-helper patches and vehicle patches `03`–`06`. They cover
valid calibration and rejected-request handling, AOL feedback and button state,
brake-pause units and silent brake transitions while steering continues, sustained
EV9 steering-limit warnings with a contact-qualified torque-input holdoff, hands-off assistance stability,
and signal-driven EV9 turn desires through predicted stops,
and continuous inactive LKAS traffic with
matching Panda forwarding. Actual manual handoff is reported through an appended
actuator telemetry field; capacitive hands-on state includes its sample timestamp.
Vehicle patch `05` also caps the EV9 direct OP-long autonomous angle target at
±140° before filtering. Cap binding keeps assistance active, with existing
manual-following and smooth-reentry exceptions; Panda limits and inactive
measured-angle handling remain unchanged. See the migration guide for scope
and verification. Recent-device investigation
is documented in [the drive-review workflow](../docs/RECENT_DRIVE_REVIEW.md).

`assets/openpilot/` preserves custom artwork and audio. Original helpers and
analysis assets are in `legacy-openpilot-tooling/`, with source checksums in its
`origin.json`. Original opendbc helpers are in `tools/opendbc-patches/legacy/`.
These archived scripts are historical references, not supported commands.

## Apply and check

From the repository root (script paths also work from another directory):

```sh
./apply_patch.sh                              # All enabled patches; skips already-applied changes
./apply_patch.sh --check                      # Check enabled patches without changes
./apply_patch.sh example.patch                # One enabled main-repository patch
./apply_patch.sh opendbc/example.patch         # One enabled vehicle patch
./apply_patch.sh --check opendbc/example.patch
```

Bulk replay visits `patches/*.patch` first, then `patches/opendbc/*.patch`, sorting
filenames within each directory. Use filenames to establish order, or select
individual patches when dependencies need another order. Vehicle patches retain
standalone paths such as `opendbc/car/hyundai/...`; the helper adds
`opendbc_repo/` when applying them to the main repository.

Already-applied patches are skipped. Normal replay does not change the index and
stops at the first failed patch; earlier successful patches remain applied.
`--check` checks each patch independently against the current working tree. It
does not simulate the results of earlier patches in a dependent series.

Explicit `--3way` enables Git's three-way fallback, stages changes, and can leave
conflicts to resolve. `apply_patch_conflicts.sh` opts into that mode. Combining it
with `--check` still performs an ordinary, non-mutating applicability check.

`tools/opendbc-patches/apply.sh` forwards to the unified helper with vehicle-only
selection. Its no-argument/`--all` mode selects only enabled vehicle patches.

## Create from staged edits

Stage the intended source changes, then export them:

```sh
git add selfdrive/path/to/file.py
./create_patch.sh example

# Vehicle-only export, stored with standalone opendbc paths:
git add opendbc_repo/opendbc/car/hyundai/carcontroller.py
./create_patch.sh opendbc/example
```

Creation compares **HEAD to the staged index**, so unstaged edits are excluded.
It preserves new/deleted files, binary content and executable modes. Main patches
may contain application files from anywhere in the main repo, including bundled
vehicle files; `opendbc/<name>` restricts export to `opendbc_repo/` and strips that
prefix. Maintenance tools, archives and patch files are excluded.

The helpers write only the patch file. They do not sync, apply patches, change
source files, stage, commit or push. Review and stage the output patch separately.
`create_patch_manual.sh` is an alias for the same staged export. Creation refuses
to overwrite any enabled or disabled patch with the same name.

## Update a patch

Update retains the original patch baseline without needing a commit reference:

```sh
./update_patch.sh example
./update_patch.sh opendbc/door_signals

# Explicitly rebase, or recover when original Git objects are unavailable:
./update_patch.sh example --base <unpatched-commit>
```

By default, the helper reads original file versions from the existing patch's
embedded Git blob IDs, without guessing commits, and compares them with the Git
index. With nothing staged, the index contains HEAD versions. This preserves
committed original hunks and captures committed changes to existing patch paths;
unstaged edits are excluded.

The index must contain the complete intended result. Updating does not apply
missing historical hunks for you; port or apply a patch before regenerating it.

Default scope is the existing patch's files plus newly staged source files,
excluding maintenance files. Stage new files before committing if they should be
included automatically. A path selection after `--` replaces this scope.
Explicit `--base <ref>` instead uses an ordinary base-to-index diff and its scope;
select paths to avoid including unrelated changes since an older base. Update
does not require staged changes, but the resulting patch must be nonempty.
Malformed patches or unavailable preimage objects fail without overwriting the
existing patch; use an explicit base when those original objects are unavailable.
Patches that only change file permissions have no blob IDs: their original
content comes from HEAD. Use `--base` to include already-committed content
amendments to those files.

A bare name resolves an existing enabled, temporarily disabled, or previously
disabled file and preserves its suffix. Ambiguous names require the full disabled
filename. Empty exports or errors leave existing patch contents unchanged.

Both helpers accept an optional path selection after `--`:

```sh
./create_patch.sh example -- selfdrive/path/to/file.py
./update_patch.sh opendbc/door_signals -- opendbc/car/hyundai/carstate.py
```

Paths are relative to the main repo for a main patch, or to `opendbc_repo/` for a
vehicle patch. Select all files belonging to an updated patch; omitted files will
not be part of its replacement. `create_patch.sh` also accepts `--base <ref>` when
an explicit older base is needed.

See [the migration guide](../docs/STARPILOT_MIGRATION.md) for upstream and deployment
workflow details. Local tooling checks use disposable Git repositories; no vehicle
patch is applied as part of those checks.
