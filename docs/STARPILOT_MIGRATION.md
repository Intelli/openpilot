# Stable StarPilot migration

## Baseline

This repository now carries the stable `StarPilot` branch from
[firestar5683/StarPilot](https://github.com/firestar5683/StarPilot/tree/StarPilot).
Upstream's [installation documentation](https://wiki.firestar.link/) distinguishes
the stable `firestar5683/StarPilot` install from the unstable `firestar5683/Dom`
install. We fetch only `refs/heads/StarPilot`.

The first snapshot is `c3e4ec630f41c4baa43254a90f718abd1bf764a1`.
`starpilot-upstream.json` records its commit and Git tree. The initial import
matched upstream outside the explicitly preserved maintenance files. Migrated
custom defaults, EV9 Edition, settings UI, EV9 control/warning integration and the
six vehicle migrations are now recorded in enabled patches. Deferred features
remain disabled.

`opendbc_repo/`, `panda/`, and the other bundled dependencies are ordinary files
from that same snapshot. `opendbc` links to `opendbc_repo/opendbc`. Make future
vehicle edits here; the standalone Intelli/opendbc repository is no longer a
dependency. Its local checkout and remote repository have been left available
as historical references.

## Importing another stable snapshot

From the repository root:

```sh
./sync-upstream.sh --check
./sync-upstream.sh --allow
```

The first command fetches the stable branch and shows differences against HEAD.
The second replaces application files and stages the resulting source tree and
provenance. Review and commit it on `ev9-dev` when ready. Neither command commits,
pushes, builds or applies patches. `./update.sh` accepts the same arguments.
Without `--allow`, a changed upstream commit is reported without importing it.

The script refuses application edits, an active merge/rebase, dirty submodules,
or untracked/ignored files that the import would overwrite. It preserves the
maintenance paths listed in the script. A sync replaces even previously committed
application customizations; restoring selected patches is a separate reviewed
step. Snapshot imports preserve Intelli's branch history without merging upstream
history. Only the latest upstream snapshot is fetched, limiting binary-history
downloads.

On the first conversion, old submodule checkouts are moved intact to
`.git/starpilot-backups/<timestamp>-<pid>/`, with their paths and previous main
commit recorded. Their relative `.git` pointers are usable again after restoring
the original paths. This is a local recovery copy, not part of the published repo.
The import bypasses legacy LFS filters and checkout hooks to restore upstream
bytes directly.

## Preserved work

| Location | Contents |
| --- | --- |
| Root `apply_patch*.sh`, `create_patch*.sh`, `update_patch.sh` | Unified replay and staged forward-patch export helpers |
| `patches/*.patch*` | Application patches and unchanged `.migrated` / `.temp-disabled` archives; pre-existing disabled suffixes are unchanged |
| `patches/assets/openpilot/` | Custom lock artwork and audio for future patch porting |
| `patches/legacy-openpilot-tooling/` | Original patch and sync/update helpers, guidance, custom analysis assets and checksums |
| `patches/opendbc/` | Numbered StarPilot vehicle patches and unchanged historical originals |
| `tools/opendbc-patches/legacy/` | Original standalone helpers and guidance |
| `tools/opendbc-patches/origin.json` | Standalone source commit and archive checksums |

The 17 patches enabled before migration were initially paused with the
`.temp-disabled` suffix. After a port, its unchanged original uses `.migrated` and
a new `.patch` records the reviewed StarPilot implementation. The six previously
disabled patches retain their `.disabled` names. Only files ending in `.patch`
are enabled. `./apply_patch.sh` skips changes already applied.

### Application migration status

| Enabled patch | Scope |
| --- | --- |
| `custom_defaults_starpilot.patch` | Supported StarPilot defaults, EV9 manual fingerprint, completed training `0.2.0`, four Hkg defaults |
| `ev9_edition_starpilot.patch` | EV9 Edition branding and EV9-only control restriction; already migrated before these ports |
| `settings_ui_starpilot.patch` | Shared flat settings layout and larger, clearer controls |
| `drive_helpers_starpilot.patch` | EV9 tuning broadcast and upper-level curvature integration |
| `customize_warnings_starpilot.patch` | EV9-specific steering warning thresholds |
| `alerts_starpilot.patch` | Compact EV9 alert presentation and translucent normal banners |
| `custom_model_ui_starpilot.patch` | Ocean-blue/rainbow/warning EV9 path gradients and optional appearance control |
| `ui_options_starpilot.patch` | Flat Steering page and four relevant EV9 controls |

The original `custom_defaults`, `ev9_edition` and `prebuilt` archives now use
`.migrated` too. Their existing StarPilot replacements were reviewed rather than
reapplied. The prebuilt replacement is maintained CI tooling, preserved by sync,
so it does not need another enabled application patch. Its old Sunnypilot binary
overlay, LFS exceptions and auxiliary workflows are obsolete in this monorepo.

The custom-defaults port covers supported settings. StarPilot already enables
road-name and blind-spot visualization. Its native blind-spot/lane-change handling
is retained. Legacy auto-lock credentials, quickboot/power bookkeeping, unused
Hkg gains and smoothing knobs, and advanced lane-centering defaults are not
registered. Legacy percentage speed-limit offsets and independent lane-turn
speed have no direct equivalent in StarPilot's additive speed bands and shared
lane-change threshold; those existing StarPilot settings remain unchanged.
Terms acceptance retains StarPilot's normal flow. Existing saved preferences
are preserved, including native RainbowPath settings. The new EV9Path preference
selects the migrated effect without changing those saved path-color choices.

Three originals remain `.temp-disabled` by request: `lane_centering`,
`driver_monitoring` and `power_management`.
All previously `.disabled` archives remain unchanged.

The root helpers now support both patch locations. Application discovers enabled
root patches first, then vehicle patches, and adds `opendbc_repo/` to standalone
vehicle paths. Create exports staged source. Update reconstructs original file
versions from the existing patch’s Git blob IDs and compares them with the index
(HEAD versions when nothing is staged), preserving committed original hunks and
the existing suffix. Its default scope includes existing patch paths and newly
staged source files; `-- PATH...` overrides scope and `--base <ref>` selects an
explicit baseline. Maintenance files are excluded. Empty, malformed or missing-
preimage exports leave the patch unchanged. Exporters do not sync, modify source,
stage, commit or push. Neither sync nor CI invokes these helpers.
See [the patch guide](../patches/README.md) for examples and scope selection.
Original helper copies are historical reference; do not run archived scripts.

## EV9 vehicle migrations

All six formerly enabled opendbc patches have been ported into the bundled tree.
Replay these numbered patches in order; each builds on the preceding source:

| Patch in `patches/opendbc/` | Migrated behavior |
| --- | --- |
| `01_customize_warnings_starpilot.patch` | Steering saturation warning timer of 0.3 seconds |
| `02_door_signals_starpilot.patch` | CAN-FD door-open detection includes all four doors |
| `03_modify_baseline_starpilot.patch` | EV9 controller and Panda vehicle models; other platforms retain StarPilot's model |
| `04_panda_safety_limits_starpilot.patch` | EV9-only low-speed limits: 4.2 m/s² lateral acceleration and 4.2 m/s³ lateral jerk |
| `05_steering_and_ev9_limits_starpilot.patch` | Controller limits, override-effort tuning, HOD sensing and manual handoff |
| `06_ev9_tests_starpilot.patch` | Python behavior and native Panda CAN regression coverage |

Panda identifies EV9 using safety bit 256 together with EV-gas and angle-steering
flags. Bit 256 retains its FCEV meaning outside that context and is removed before
common gas decoding on EV9. This avoids consuming StarPilot's existing AOL flag.

The application's higher-limit threshold defaults to 40 km/h (10–40 km/h range).
The native consumer retains a 32 km/h fallback for absent broadcasts. Panda's
independent gate retains the original calculation: `max(measured_speed - 1, 1)`
at or below `42 / 3.6 + 0.1` m/s, approximately 45.96 km/h measured speed. This is
a step, not the 50 km/h gate assumed by the old test patch. Above the applicable
gate, the standard road-roll-adjusted limits apply. Controller outputs respect
both envelopes, including when a configured controller threshold exceeds Panda's.
An empty angle/rate intersection sends inactive measured-angle control.

Manual handoff requires fresh HOD touch/grip (raw 1–4, no older than 300 ms) and
driver torque. Missing, reserved and stale HOD values do not count as intent. The
legacy torque hysteresis, entry-only speed gate, one-second low-demand release,
two-second reentry guard, 0.1-second grip dwell and 90°/15° high-angle hysteresis
are preserved. High-angle hold respects gear, fault and angle/rate checks. The
request state reaches both LKAS_ALT and direct `0xCB` steering messages.
EV9 controller measurements match Panda's selected MDPS signal: `STEERING_ANGLE`
for LKAS control with stock longitudinal, and `STEERING_ANGLE_2` for direct angle
control. The public CarState angle continues to use `STEERING_SENSORS`; its offset
or timing differences must not enter inactive handoff commands. Regression tests
cover distinct sensor angles, independent SAS updates and return from handoff.

### EV9 application integration

`drive_helpers_starpilot.patch` connects persistent settings to StarPilot's toggle
broadcast and the native `EV9AngleConfig` consumer. Startup car identification
reads current persisted values over cached broadcasts; realtime consumers do no
parameter-file I/O. Settings publish before fingerprinting, while consumers gate
behavior on the actual EV9 angle-steering CarParams.

| Toggle attribute | Parameter | Application default / range |
| --- | --- | --- |
| `hkg_tuning_angle_custom_limit_max_speed_kph` | `HkgTuningAngleCustomLimitMaxSpeedKph` | 40 km/h; 10–40 |
| `hkg_tuning_angle_override_effort_percent` | `HkgTuningAngleOverrideEffortPercent` | 10%; 10–100 |
| `hkg_shared_autonomy_mode` | `HkgSharedAutonomyMode` | 0/off; 1 and legacy 2 enable handoff |

Registry defaults belong to `custom_defaults_starpilot.patch`. Existing saved
values take precedence, with malformed values falling back and values clamped to
the supported UI ranges. The legacy aliases and conservative missing-broadcast
fallback remain supported inside opendbc.

Below the configured threshold, upper-level EV9 curvature limiting uses the same
symmetric 4.2 m/s² envelope as the controller, without roll compensation or the
generic curvature cap. Existing lane-change comfort shaping remains active.
Above it, and on other cars or torque control, StarPilot behavior is unchanged.
The downstream controller/Panda intersection still limits actual steering.
`customize_warnings_starpilot.patch` restores the EV9 saturation timer's 2.5 km/h
minimum speed. The existing undershoot, turn-demand, driver-input and saturation
checks remain required. Below or at `HkgTuningEv9AlertsSpeedKph` (default 50 km/h,
range 10–50), the warning additionally requires at least 90° desired steering.
This policy applies only to EV9 angle steering, before StarPilot's existing
Switchback cooldown and sound selection. High-angle warnings remain available
at low speed. Other cars and torque controllers retain their existing behavior.
The former startup-master exception is unnecessary: normal StarPilot startup
already uses its custom startup event, while unsupported-car guards remain.
`alerts_starpilot.patch` uses compact EV9 distraction and steering-limit banners,
retaining event timing, priority and sounds. This changes presentation only; driver
monitoring logic remains unchanged. Normal EV9 banners use 50% black opacity in
both device renderers. Steering-limit warnings remain visible with Hide Alerts
enabled. Other vehicles retain their original presentation.
`ui_options_starpilot.patch` adds four controls directly under Steering → EV9
Steering: Improved Manual Control, Steering Override Effort, EV9 Limits Speed
and EV9 Alert Speed. The controls use the ranges/defaults above and fixed km/h
units for both speed thresholds. Legacy handoff mode 2 displays as enabled;
toggling on writes canonical mode 1. Actual EV9 angle CarParams are required,
with selected-EV9 fallback before initial identification while offroad. Writes
are blocked while onroad, including if a slider was opened before starting.
Cached UI parameter writes use StarPilot's existing broadcast notification.

This patch also owns the Steering page's previously migrated flat layout;
its hunks were moved out of `settings_ui_starpilot.patch` so both patches can
independently recognize already-applied changes. The previous layout remains.
The legacy lane-turn range change is omitted because StarPilot has its own
lane-change/turn controls. Path styling uses a separate EV9 Path toggle instead
of renaming the native Rainbow Path control.

### EV9 path appearance

`custom_model_ui_starpilot.patch` adds one shared gradient provider used by both
C3X and mici model renderers. Normal active steering shows animated ocean blue;
positive measured acceleration fades into the old rainbow effect (0.25 m/s² on,
0.15 m/s² off, 0.5-second fade in and 1-second fade out). Relevant steering,
collision and driver-attention alerts override the fill with red, held for
0.5 seconds after the alert and blended back over 1 second. Standard and StarPilot
alert channels are checked, including alternate steering-saturation alerts.

Fresh carControl.latActive determines steering activity, including always-on
lateral. Inactive steering uses a subdued gray fill; warning red has priority.
Invalid, stale, future-dated or previous-drive input is ignored. Animation updates
once per path draw, independently of model-message updates. Toggling off, starting
a new drive, missing geometry or a long frame gap resets the animation state.

Path geometry, Dynamic Path width, lane/road lines, outlines and adjacent blind-
spot overlays remain in StarPilot's existing rendering pipeline. The shared
helper returns colors and performs no drawing or vehicle-control changes.

EV9 Path appears under Appearance's Model & Path Visualization settings and in
the mici visuals page. It overrides Rainbow Path, Acceleration Path and the main
Path Color while enabled; their saved values are preserved and the controls
explain the override. Turning EV9 Path off restores those choices. The new key
is enabled by default in `custom_defaults_starpilot.patch`, with stock value off;
a saved EV9Path preference always takes precedence.

Regression tests live in `opendbc_repo/opendbc/car/hyundai/tests/test_ev9.py` and
`opendbc_repo/opendbc/safety/tests/test_hyundai_ev9*.py`, with corresponding updates
to existing Hyundai tests. They exercise real CAN packing/parsing, controller
output and native Panda hooks, including one-tick limit violations and stale
stock commands during manual handoff. Native safety tests require rebuilding
`libsafety.so` for the test host; the tracked AGNOS binary cannot run on macOS.

## Build and deployment branches

1. Push a reviewed source commit to **`ev9-dev`**.
2. The GitHub build checks out that exact SHA on an ARM Ubuntu runner. It uses
   StarPilot's device container, extracts a sysroot from upstream's AGNOS image,
   and runs `./build`. The upstream build clears native build signatures and
   recreates `prebuilt` only after success.
3. The publisher commits the built output to **`ev9-prebuilt`**, recording
   `Source-Commit: <ev9-dev SHA>`. This branch contains one parentless commit for
   the latest build. The publisher replaces only this branch with an explicit
   force-with-lease against the fetched tip, so a concurrent publication is not
   overwritten. Each snapshot contains only the current build's files.
4. The existing workflow on **`master`** reacts to build success and runs the
   deployment-sync helper from `ev9-dev`. That helper copies the exact tree from
   **`ev9-prebuilt`**, including rebuilt binaries and the `prebuilt` marker, into
   a new **`ev9`** commit. It preserves `ev9` history and records both
   `Source-Commit: <ev9-dev SHA>` and `Build-Commit: <ev9-prebuilt SHA>`.

Install **`Intelli/ev9`** on the device. Its files match the published GitHub
build; `ev9-dev` is for development. The sync helper validates build provenance
and the `prebuilt` marker before promotion. Repeating a promotion with the same
tree and provenance makes no new commit; a new build/source is recorded even
when its file contents are identical.

Publishing an identical snapshot for the same source is also a no-op once
`ev9-prebuilt` has a single root commit. The first publication after switching
from the earlier history-preserving publisher replaces its history even if the
payload is unchanged. `ev9-dev` retains development history and `ev9` retains
deployment history. Old build-commit IDs may eventually be pruned from Git;
previously deployed files remain available through `ev9` history.

Do not copy the `ev9-dev` source tree directly to the install branch. Upstream
ships tracked native binaries and a `prebuilt` marker, which disables device
compilation. A source-only promotion can therefore display updated Python UI
while still loading old compiled code. In particular, `common/params_keys.h`
defaults are compiled into `common/params_pyx.so` and must be rebuilt together.

Custom defaults initialize missing settings. Existing `/data/params/d` values
win over `/cache/starpilot/params/d` cached values, which win over compiled
defaults. Installing a corrected build does not overwrite saved preferences or
a saved training-completion value. Change any retained values explicitly when
upgrading an existing installation; uninstall is not a reliable defaults reset.

The workflow file and display name remain `sunnypilot-build-prebuilt.yaml` and
`sunnypilot prebuilt action` solely because the default-branch workflow subscribes
to that name. The implementation builds StarPilot. Renaming it later requires
updating the subscription on `master` at the same time.

The existing `PREBUILT_PUSH_TOKEN` and `ev9-dev` GitHub environment remain in use.
No separate test gate was added. The build uses bundled opendbc and publishes its
own compiled output; the former Sunnypilot prebuilt download/overlay is removed.
Other inherited root workflows were retired so that upstream-owner automation
and old Sunnypilot jobs do not run in this fork.

## Verification and scope

Local integration checks cover snapshot conversion, maintenance preservation,
collision refusal, legacy LFS/hooks, deployment history, source SHA propagation,
file removals and promotion of the exact published build. They use temporary Git
repositories and never publish to GitHub.

The initial migration build succeeded on GitHub. Future deployments continue to
use the GitHub build workflow.
Local Python dependencies and compiled extensions also need to follow StarPilot's
lockfile for native development; the old Sunnypilot environment is not proof of a
working native build.
