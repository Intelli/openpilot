# StarPilot maintenance and EV9 behavior

## Source and workflow

- Develop on `ev9-dev`. Stable upstream is `firestar5683/StarPilot`, branch
  **`StarPilot`**; `Dom` is not the sync target. [starpilot-upstream.json](../starpilot-upstream.json)
  records the imported commit/tree.
- Edit vehicle code under `opendbc_repo/opendbc/` (`opendbc` is a symlink).
  Dependencies are tracked files. The standalone Intelli/opendbc checkout is
  historical reference only.
- Save application edits before `./sync-upstream.sh --check` / `--allow`.
  `--allow` replaces and stages the upstream source, including previously
  committed customizations. It never replays patches, commits or pushes.
- Restore customizations with `./apply_patch.sh`, then review source and patches
  together. Replay root patches alphabetically, then numbered vehicle patches.
  See [the patch workflow](../patches/README.md) for export/update commands and
  [AGENTS.md](../AGENTS.md) for development and build instructions.
- This guide, the patch archive and maintenance tooling are preserved by sync.
  Application changes belong in patches, not the sync preservation list.

## Patch ownership

Only files ending in `.patch` are enabled. Historical `.migrated`,
`.temp-disabled` and `.disabled` originals remain unchanged and unapplied.
Lane centering, driver monitoring and power management remain deferred.
The old prebuilt patch was replaced by maintained build tooling.
Archived helpers under `patches/legacy-openpilot-tooling/` and
`tools/opendbc-patches/legacy/` are reference only; do not run them.

| Root patch (`patches/`) | Current scope |
| --- | --- |
| `build_config_starpilot.patch` | Explicit editable-install import root; prevents Hatchling from walking uv's temporary cache |
| `custom_defaults_starpilot.patch` | Supported defaults, EV9 fingerprint, parameter registration and button migration |
| `ev9_edition_starpilot.patch` | Branding and EV9-only control restriction |
| `boot_logo_ev9_edition.patch` | Boot artwork and references |
| `settings_ui_starpilot.patch` | Shared flat settings layout |
| `drive_helpers_starpilot.patch` | EV9 tuning broadcast, curvature integration, calibration and always-on lateral (AOL) state |
| `customize_warnings_starpilot.patch` | Steering-warning policy and driver-input suppression |
| `alerts_starpilot.patch` | Compact alerts and silent braking while AOL steering continues |
| `custom_model_ui_starpilot.patch` | EV9 path colors and appearance toggle |
| `ui_options_starpilot.patch` | Flat Steering page and EV9 controls |

## EV9 vehicle migrations

| Vehicle patch (`patches/opendbc/`) | Current scope |
| --- | --- |
| `01_customize_warnings_starpilot.patch` | 0.3-second steering-saturation timer |
| `02_door_signals_starpilot.patch` | All four CAN-FD doors |
| `03_modify_baseline_starpilot.patch` | EV9 vehicle model, safety identification and flag decoding |
| `04_panda_safety_limits_starpilot.patch` | EV9 numeric safety limits and stock-LKAS forwarding ownership |
| `05_steering_and_ev9_limits_starpilot.patch` | Controller limits, override effort, HOD and manual handoff |
| `06_ev9_tests_starpilot.patch` | Vehicle/controller/native-safety regression tests |

### Limits and steering ownership

- Preserve the historical EV9 steering envelopes; longitudinal acceleration uses
  StarPilot defaults. Low-speed lateral acceleration/jerk limits are 4.2 m/s²
  and 4.2 m/s³. Upper-level curvature uses the matching symmetric envelope below
  the configured threshold; controller and Panda checks still apply.
- The application threshold defaults to 40 km/h; the vehicle consumer falls back
  to 32 km/h without a broadcast. Panda independently uses
  `max(measured_speed - 1, 1) <= 42 / 3.6 + 0.1` (m/s), approximately 45.96 km/h
  measured speed. Above the applicable gate, standard limits apply.
- Ordinary clipping keeps steering active at the nearest valid command. An empty
  angle/rate intersection requires inactive control, as in Sunnypilot. A blanket
  hold at the last angle would bypass these checks.
- EV9 stock-LKAS traffic stays continuous while inactive, with measured angle and
  zero gain. Panda blocks duplicate factory steering traffic independently of
  the AOL latch; active commands still require permission and valid limits.
  Use the MDPS angle selected by Panda: `STEERING_ANGLE` for stock-LKAS and
  `STEERING_ANGLE_2` for direct angle control, not the public SAS angle.
- EV9 safety identification uses bit 256 with EV-gas and angle-steering flags.
  EV9 alias bits must be removed before common flag decoding; bit 128 also
  selects LKAS_ALT and must not accidentally enable the common LKAS latch.
- With Improved Manual Control off (mode 0), torque-override release immediately
  restores the current base assistance. Fresh HOD no-contact bypasses only the
  custom override-effort cut; native torque-dependent gain reduction still applies.
  Contact or unavailable HOD retains torque-only override behavior. This deliberately
  differs from Sunnypilot mode 0 to avoid hands-off gain cycling. Modes 1/2 retain
  their touch-plus-torque handoff, dwell and reentry guards, preserve independent
  base assistance during manual handoff, and restore it immediately on release.
  Inactive manual commands still transmit zero gain; disengagement and invalid
  overall angle envelopes reset the base assistance.
  HOD samples expire after 300 ms; reserved statuses publish a zero timestamp.
  Global `steeringPressed` and Panda inputs remain unchanged.

### Settings and engagement

| Parameter | Application default / supported range |
| --- | --- |
| `HkgTuningAngleCustomLimitMaxSpeedKph` | 40 km/h / 10–40 |
| `HkgTuningAngleOverrideEffortPercent` | 10% / 10–100 |
| `HkgSharedAutonomyMode` | 0/off; 1/on; legacy 2 also enables handoff |
| `HkgTuningEv9AlertsSpeedKph` | 50 km/h / 10–50 |

The four EV9 controls are offroad-only: Steering → EV9 Steering on C3/C3X,
Settings → Vehicle → EV9 Steering on C4, and Galaxy → Lateral (Steering).
EV9 Path is also available in both device UIs and Galaxy → Visual (Display & UI).
Runtime consumers use the toggle broadcast, not parameter-file I/O. Persisted
startup identity/settings take precedence over cached broadcasts. Active
`/data/params/d` values override `/cache/starpilot/params/d` and compiled defaults;
updates initialize missing values and do not reset saved preferences.

The top-left Driving Assist/main-cruise button controls AOL through StarPilot's
button assignments and keeps its factory cruise behavior with stock ACC. The one-time EV9
migration assigns it only when AOL is enabled, LKAS already toggles AOL and
main/cruise has no assignment; explicit assignments are preserved.
With OP longitudinal actually enabled, each main press sets AOL to the resulting
cruise readiness: main ON requests AOL ON and main OFF requests AOL OFF. This
avoids inverting AOL after independent LKAS presses or a refused calibration
request. SET/RES engages longitudinal without overriding an explicit steering OFF,
including LKAS OFF while cruise is only armed. Calibration and cruise faults can
refuse activation; later recovery alone does not enable AOL. Runtime fallback to
stock ACC restores the stock-mode button behavior.
`PauseAOLOnBrake=0` keeps lateral steering active when braking. A normal cruise
transition while healthy AOL steering continues has no disengagement sound,
banner or HUD cue; faults and full disengagement retain their alerts.

AOL requires healthy, completed calibration. A refused activation or loss of
calibration discards the session and requires a fresh accepted request. Delayed
stock-cruise engagement cannot undo an explicit button OFF. Stock SCC availability
supplies main permission without requiring actual cruise engagement.

EV9 Force Turn Desires follows the signal through predicted-stop conditions, as
in Sunnypilot. It requires active lateral control, movement, one signal, speed
below the configured lane-change threshold and no same-side blind-spot detection.

### Steering warnings

Two paths feed the EV9 steering-limit alert:

1. **Historical controller saturation:** retain the controller's saturation timer,
   turning/acceleration-undershoot checks, and absolute requested angle ≥90° **or** speed
   above the configured alert threshold. Saturation can mature before eligibility;
   eligibility does not start another 0.3-second wait.
2. **Additional tracking shortfall:** absolute request ≥119.9° and directional measured-angle
   or command shortfall >2.5° for 0.3 seconds. Clearing hysteresis uses 114.9°/1°.
   Speed alone cannot qualify this additional path.

Torque input suppresses both through the legacy two-second holdoff, clearing
visible/audible warnings, unless fresh valid HOD explicitly reports no contact.
The angle controller's saturation timer uses the same qualified input. Capacitive
touch alone does not suppress warnings; unknown/stale HOD falls back to torque.
Timers recover during the holdoff without arming hysteresis. Inactive steering,
standstill, unhealthy inputs and actual manual handoff reset the warning.
`manualSteeringOverride` telemetry distinguishes handoff from normal angle clipping.
StarPilot's sound selection and Switchback cooldown remain in use. These warning
thresholds do not impose a universal 90° steering-command limit.

### Path appearance

EV9 Path uses animated blue, acceleration rainbow and alert-red fills in both
device renderers; it preserves saved native path-color choices when disabled.
Geometry and adjacent blind-spot overlays remain native StarPilot behavior.
Blind-spot red can appear without an alert and is independent of the EV9 alert fill.

## Build, deployment and verification

Use `ev9-dev` → GitHub device build → `ev9-prebuilt` → `ev9`. Install `Intelli/ev9`.
`ev9-prebuilt` holds one parentless built snapshot with a `Source-Commit` trailer;
`ev9` preserves deployment history and records `Source-Commit` and `Build-Commit`.
Promote the exact built tree: tracked AGNOS binaries and `prebuilt` make source-only
promotion unsafe. Parameter/schema/native changes must ship with rebuilt binaries.

The build workflow retains the name `sunnypilot prebuilt action` because the
workflow on `master` subscribes to it; coordinate both when renaming. The GitHub
build remains the deployment gate. Do not run publishing scripts as local checks.

Use focused tests for changed behavior. Host-native extensions and `libsafety.so`
must be built separately from tracked AGNOS binaries. Verify enabled patches replay
from the recorded baseline and reproduce their affected source files; current-tree
`./apply_patch.sh --check` alone does not simulate dependent replay.
For device issues, follow [the recent-drive review workflow](RECENT_DRIVE_REVIEW.md)
to verify the recorded build/settings and inspect full-rate logs when needed.
Host checks do not replace the GitHub device build or on-vehicle validation.
