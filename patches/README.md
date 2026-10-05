# Intelli patch workflow

Supported root commands retain the familiar apply/create/update workflow while
exporting forward diffs and keeping sync, staging and publication explicit.
See [maintenance](../docs/MAINTENANCE.md) and [EV9 behavior](../docs/EV9_BEHAVIOR.md)
for source provenance and current behavior.

## Patch locations and state

| Location / suffix | Meaning |
| --- | --- |
| `patches/<name>.patch` | Enabled patch with main-repository paths |
| `patches/opendbc/<name>.patch` | Enabled vehicle patch with paths relative to `opendbc_repo/` |
| `patches/archive/` | Historical implementations and notes; excluded from replay |
| `patches/baselines/<blob-id>` | Exact original file bytes retained for automatic updates after fresh clones |
| `.patch.migrated`, `.patch.temp-disabled`, `.disabled` | Preserved historical originals; never replayed |

Current enabled application patches replay in this order:

| Patch | Feature ownership |
| --- | --- |
| `01_custom_defaults.patch` | Compiled parameter defaults and custom parameter keys |
| `02_drive_helpers.patch` | Steering-limit configuration, schema and interface helpers |
| `03_lane_centering.patch` | Lane/road-edge correction and telemetry |
| `04_custom_model_ui.patch` | Path/model rendering, centering overlays and rainbow path |
| `05_ui_options.patch` | Model, vehicle and visual settings |
| `06_alerts.patch` | Compact alert text and translucent alert presentation |
| `07_customize_warnings.patch` | Steering saturation warning policy |
| `08_hands_free_stats.patch` | Statistics recording, UI, trips and tests |
| `09_ev9_edition.patch` | EV9 branding and vehicle-only startup restriction |
| `10_driver_monitoring.patch` | Phone threshold 0.68; eye/blink thresholds already match upstream |
| `11_power_management.patch` | Offroad power, screen and model-manager behavior |
| `12_custom_assets.patch` | Custom engagement audio and preserved auto-lock icons |
| `boot_logo_ev9_edition.patch` | Boot artwork and its Sunnypilot installation hook |
| `sunnypilot_device_build.patch` | AGNOS 19.7 / `comma_arm64` native build and fused-model compatibility |

There are 14 enabled application patches. Then five vehicle patches replay, with
paths relative to `opendbc_repo/` (19 enabled patches in total):

| Patch | Feature ownership |
| --- | --- |
| `opendbc/02_panda_safety_limits.patch` | EV9 lateral safety thresholds |
| `opendbc/03_steering_and_ev9_limits.patch` | EV9 controller, tuning/interface and steering/HOD signals |
| `opendbc/04_door_signals.patch` | All-door detection |
| `opendbc/05_customize_warnings.patch` | Steering-saturation timer |
| `opendbc/06_ev9_tests.patch` | EV9 vehicle and native-safety regressions |

The former consolidated patches are archived unchanged under
`archive/sunnypilot-consolidated-20261004/`. Original `.migrated` and
`.temp-disabled` files remain historical references; these newly generated forward
patches replace their replay role. Asset retention does not enable the disabled
auto-lock implementation.

Current official baselines are application `d021f6ca41375e58be8125801547e84939e0c503`
and its opendbc pin `28303fcd1cc457f67d405407858223e0b338df20`. Application patch
paths now start with `openpilot/`. The upgrade advanced 798 upstream commits from
`54fb2750bab4`; ports preserve new upstream behavior while retaining custom features.
Vehicle `01_modify_baseline.patch` is archived because current upstream supplies
its EV9 baseline physics. Superseded implementations and helpers are described in
[the upgrade archive](archive/sunnypilot-upgrade-20261004/README.md).

Historical restoration used Intelli `5928a37ad187`, customized vehicle snapshot
`5a3f3761f586`, and its original dependency pins. Those identify restoration history,
rather than the current official baselines.

StarPilot implementations are retained under `archive/starpilot-20260920/`,
including their documentation. They are not applied to current Sunnypilot.
Its [catalog](archive/starpilot-20260920/manifest.json) records all 13 application
and six vehicle patches, hashes and original context. Their complete replay was
verified against the recorded StarPilot baseline and matches the preserved source.
Other archived experiments and original patch suffixes remain historical references.
The [changelog](CHANGELOG.md) describes restoration and earlier work.

`assets/openpilot/` retains custom artwork/audio. `legacy-openpilot-tooling/` and
`tools/opendbc-patches/legacy/` preserve original helpers with provenance/checksums.
Do not run those copies: their creators automatically sync/stage and generate
inverse diffs. Supported root helpers produce forward exports without those side effects.

## Sync and replay

`./sync-upstream.sh --check [ref]` previews the application and its exact dependency
pins. `--allow` stages the imported snapshot. Add `--opendbc` for vehicle-only sync.
Both default to Sunnypilot's `hkg-angle-steering-2025`; no historical standalone
checkout participates. Sync removes custom source in its scope while preserving
maintenance files and patch archives. It does not replay patches, merge, commit or push.

Same-baseline imports retain provenance bytes and existing root ignore/attribute
rules only after checking the official snapshot and all dependency pins. Combined
with replay and final staging, the recorded baselines produce an identical Git
tree. New upstream snapshots still regenerate provenance and import new rules.
The historical standalone opendbc deployment workflow is retained only as
`archive/sunnypilot-consolidated-20261004/legacy-opendbc-ev9-sync.yaml`.

Save edits and update patch records before sync. Import, then run the application
helper below, review and stage the result. New upstream snapshots can require ports;
current-tree `--check` is not a simulated replay of a dependent patch series.

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
git add openpilot/selfdrive/path/to/file.py
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

The helpers export patches without syncing, replaying into application source,
staging, committing or pushing. Shared-file updates also retain any newly required
preimage payloads in `patches/baselines/`. Review and stage the patch and baseline
files together.
`create_patch_manual.sh` is an alias for the same staged export. Creation refuses
to overwrite any enabled or disabled patch with the same name.

## Update a patch

Update retains the original patch baseline without needing a commit reference:

```sh
./update_patch.sh example
./update_patch.sh opendbc/04_door_signals

# Explicitly rebase, or recover when original Git objects are unavailable:
./update_patch.sh example --base <unpatched-commit>
```

By default, the helper reads original file versions from the existing patch's
embedded Git blob IDs, without guessing commits, and compares them with the Git
index. With nothing staged, the index contains HEAD versions. This preserves
committed original hunks and captures committed changes to existing patch paths;
unstaged edits are excluded.

Some features share a source file: warnings and EV9 startup branding share
`openpilot/selfdrive/selfdrived/selfdrived.py`; steering signals and doors share
`opendbc_repo/opendbc/car/hyundai/carstate.py`. For an enabled patch with peers
in its selected files, the helper reconstructs and replays the series in temporary
indexes, finds changes beyond the recorded series, and transfers only the requested
feature's amendments. Other features remain separate. It checks line ownership,
rejects edits to another feature or ambiguous insertions, and verifies that the
updated series reproduces the intended index before replacing the patch.

Update the owning feature first when an edit changes another patch's lines. Stage
only the intended amendment, or use `-- PATH...` to narrow the export. A disabled
peer cannot be reconstructed as part of the enabled series; rebase the remaining
dependent patch deliberately when changing series membership. Existing defaults,
controller and other whole-file features use the original automatic update path
when no enabled peer shares their selected source.

Mode-only patches sharing a file with content patches can lack an unambiguous
original content baseline. Automatic series reconstruction rejects those cases;
use an explicit baseline and an isolated intended index when rebasing them.

`baselines/<blob-id>` files are exact preimages, with filenames equal to their Git
blob IDs. Committing these payloads keeps the required Git objects available in
fresh or shallow clones. Shared-file updates can add a new baseline payload;
commit it with the updated patch.

The index must contain the complete intended result. Updating does not apply
missing historical hunks for you; port or apply a patch before regenerating it.

Default scope is the existing patch's files plus newly staged source files,
excluding maintenance files. Stage new files before committing if they should be
included automatically. A path selection after `--` replaces this scope.
Explicit `--base <ref>` instead uses an ordinary base-to-index diff and its scope;
it bypasses feature isolation. Select paths and isolate the intended feature in
the index to avoid including other features since an older base. Update
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
./create_patch.sh example -- openpilot/selfdrive/path/to/file.py
./update_patch.sh opendbc/04_door_signals -- opendbc/car/hyundai/carstate.py
```

Paths are relative to the main repo for a main patch, or to `opendbc_repo/` for a
vehicle patch. Select all files belonging to an updated patch; omitted files will
not be part of its replacement. `create_patch.sh` also accepts `--base <ref>` when
an explicit older base is needed.

See [the maintenance guide](../docs/MAINTENANCE.md) for upstream and deployment
workflow details. Local tooling checks use disposable Git repositories; no vehicle
patch is applied as part of those checks.
