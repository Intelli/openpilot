# EV9 Edition changes from stock StarPilot

This records an earlier audit of the **enabled patches** against stable
StarPilot commit `c3e4ec630f41c4baa43254a90f718abd1bf764a1`, recorded in
[starpilot-upstream.json](../starpilot-upstream.json). The reviewed EV9 source is
`f1b6e566dc`, plus the two-hour shutdown default and C4/Galaxy settings support
(including the Lane Change Smoothing default of 10), and the EV9 startup
longitudinal-status notice, EV9 OP-long cruise-knob engagement, and the EV9
OP-long autonomous steering target cap.

That audit covered **17 enabled patches: 11 application patches and 6 vehicle patches**,
and 96 source files, including tests and artwork. It verified their replay against
the recorded baseline. Repository maintenance changes are listed separately below.
Later changes, including preview assistance and signal intent through stops, can
supersede this snapshot. Use [maintenance](../docs/MAINTENANCE.md) for the current
patch inventory and [EV9 behavior](../docs/EV9_BEHAVIOR.md) for current policies.

## 1. Defaults and configuration

Owner: [custom_defaults_starpilot.patch](custom_defaults_starpilot.patch).
Existing saved preferences take precedence. These changes initialize missing
settings; they do not overwrite a device's saved settings on update. Parameter
defaults require rebuilding the native Params extension before deployment.

### Changed defaults

| Setting / parameter | Stock baseline | EV9 Edition |
| --- | --- | --- |
| Vehicle make / model / display name | `mock` / `MOCK` / empty | `Kia` / `KIA_EV9` / `Kia EV9 2025-26` |
| Force selected fingerprint (`ForceFingerprint`) | Off | On |
| Metric units (`IsMetric`) | No explicit default | On |
| Offroad shutdown (`DeviceShutdown`) | 6 hours | 2 hours; invalid-value fallback also becomes 2 hours |
| Lane Change Smoothing | 5 | **10 — Stock**, removing the optional extra lane-change smoothing by default |
| Automatic lane-change delay (`LaneChangeTime`) | 1.0 second | 0.05 second |
| Automatic lane changes without a steering nudge (`NudgelessLaneChange`) | Off | On |
| Force Turn Desires (`TurnDesires`) | Off | On |
| Green-light alert | Off | On |
| Lead-departure alert | Off | On |
| Rainbow path | Off | On |
| Signal metrics | Off | On |
| Stopped timer | Off | On |
| Completed training version marker | `0` | `0.2.0` |
| Accepted terms version marker | `0` | `2` |

### Added settings

| Parameter | Default | Supported UI / broadcast range |
| --- | --- | --- |
| `HkgTuningAngleCustomLimitMaxSpeedKph` | 40 km/h | 10–40 km/h |
| `HkgTuningAngleOverrideEffortPercent` | 10% | 10–100% |
| `HkgSharedAutonomyMode` | 0 / off | Off or on; historical mode 2 also enables manual handoff |
| `HkgTuningEv9AlertsSpeedKph` | 50 km/h | 10–50 km/h |
| `EV9Path` | On | Appearance toggle |

Also adds `EV9MainCruiseAOLMigrated`, an internal one-time migration marker.
The four EV9 steering controls are editable offroad under **Steering → EV9 Steering**
on C3/C3X, **Settings → Vehicle → EV9 Steering** on C4/mici, and **Lateral (Steering)**
in Galaxy. EV9 Path is available in both device UIs and Galaxy's **Visual (Display & UI)**
section. Vehicle code receives validated tuning values through the
runtime settings broadcast rather than reading parameter files in the control loop.

Other configuration fixes:

- A real vehicle selected as the default can still use forced fingerprinting;
  only missing or mock selections disable that override.
- Minimum Lane Change Speed is interpreted in **mph**, matching the existing UI,
  regardless of the general metric/imperial preference.
- `PauseAOLOnBrake` changes from a boolean to an integer speed setting. Its default
  remains zero; the runtime converts its mph value to m/s correctly.
- Persisted startup EV9 identity/settings take priority over stale cached toggle
  data. Settings refresh preserves the configured EV9 identity.

## 2. Engagement, buttons and braking

Owners: [drive_helpers_starpilot.patch](drive_helpers_starpilot.patch),
[custom_defaults_starpilot.patch](custom_defaults_starpilot.patch),
[alerts_starpilot.patch](alerts_starpilot.patch), vehicle patches 03–05.

- **Driving Assist button:** conditionally adds the EV9 AOL assignment to the
  top-left main-cruise/Driving Assist button. Migration
  requires AOL enabled, LKAS already assigned to AOL, and no main-button assignment;
  the existing LKAS assignment and explicit custom mappings are preserved. The
  Driving Assist button keeps its factory cruise behavior with stock ACC. With
  OP longitudinal actually enabled, main ON requests AOL ON and main OFF requests
  AOL OFF, using fault-free cruise readiness and the existing calibration gates.
  Independent LKAS presses or a refused request cannot invert the next main action.
- **OP-long cruise knob:** on the EV9 with OP longitudinal active as the selected
  control system, up, down or a knob press can request engagement on release.
  Up resumes a saved speed, or sets the current speed on first engagement; down
  and a knob press use the normal SET speed initialization. While engaged, up/down
  retain their speed adjustments and a knob press cancels immediately. A held
  cancel cannot re-engage on release. Stock ACC, other vehicles, main arming,
  existing engagement checks and speed-limit preferences retain their behavior.
  The native EV9 safety hook accepts a complete inactive-origin knob press only;
  pedal, main-off or safety interruptions require a fresh press.
- **Independent lateral control:** explicit button OFF remains OFF even if stock
  cruise engagement arrives afterward. A refused activation during calibration
  cannot silently become active through a later cruise-state update. In OP-long
  mode, LKAS OFF while cruise is armed also stays OFF through SET/RES engagement.
- **Calibration:** EV9 lateral actuation requires healthy, current, completed
  calibration. Shared AOL session handling clears refused/lost-calibration requests
  and requires fresh rearming. Parts of this AOL lifecycle fix apply beyond the EV9.
- **Live AOL settings:** switching AOL off clears its current session. Switching
  it back on requires fresh activation and cannot grant safety permission that was
  absent at startup.
- **Stock cruise permission:** EV9 Panda handling uses received SCC main
  availability independently of whether cruise is actually engaged, avoiding
  conflicting temporary button-state changes.
- **Brake feedback:** braking or regenerative braking that disables cruise while
  healthy AOL steering continues no longer produces a disengagement banner, sound
  or HUD alert. This applies to shared AOL behavior, with calibration, CAN, gear,
  steering-fault, lateral-readiness and brake-pause checks. Full disengagement,
  no-entry and fault alerts retain their normal behavior.
- **Lateral-only saturation tracking:** request/output limiting is checked while
  lateral steering is active, including AOL without normal cruise engagement.
  Inactive operation clears stale limiting state.

Always-on lateral and the zero brake-pause default already existed in stock
StarPilot. The patches correct their EV9 integration and feedback.

## 3. EV9 steering, manual control and Panda safety

Owners: vehicle patches [03](opendbc/03_modify_baseline_starpilot.patch),
[04](opendbc/04_panda_safety_limits_starpilot.patch),
[05](opendbc/05_steering_and_ev9_limits_starpilot.patch), and
[drive_helpers_starpilot.patch](drive_helpers_starpilot.patch).

### Geometry and limits

- Uses **EV9 reference geometry** in controller/Panda angle checks instead of the
  shared Sportage reference: steer ratio 13.7 → 16.0, wheelbase 2.756 → 3.10 m,
  with the corresponding EV9 slip factor.
- Adds context-qualified EV9 safety identification and masks overlapping flag bits
  before common Hyundai decoding. EV9 flags no longer accidentally select FCEV
  gas handling or unrelated main-button/LKAS latch behavior.
- Raises the low-speed controller envelope from approximately 3.59 to **4.2 m/s²
  lateral acceleration and 4.2 m/s³ lateral jerk**, with a configurable speed gate.
  Panda's EV9 low-speed envelope similarly rises from approximately 3.59 to 4.2 in
  those respective units.
- At the application curvature layer, low-speed EV9 requests use a symmetric
  **4.2 m/s²** envelope instead of 3.0 m/s² plus roll compensation. The generic
  `0.2 m⁻¹` curvature cap is omitted in this region; vehicle and Panda limits still apply.
- The application/controller threshold defaults to **40 km/h**. The vehicle
  consumer retains a **32 km/h** fallback if tuning data is missing. Panda has an
  independent historical gate: `max(minimum measured speed − 1 m/s, 1 m/s)` must
  be no greater than `42 km/h + 0.1 m/s` (about 45.96 km/h before that tolerance).
  Above the relevant gates, standard limits apply.
- Intersects vehicle angle/rate bounds with the Panda-compatible envelope.
  Ordinary clipping keeps steering active at a valid bounded request; an empty
  intersection requires an inactive command.
- Caps the EV9 direct OP-long autonomous angle target at **±140°** before
  filtering, including lateral-only operation. Larger requests hold the bounded
  target without a new disengagement rule. Existing manual wheel following and
  smooth reentry may exceed that target cap; inactive commands retain measured
  angle. Stock ACC steering and other vehicles are unchanged. The cap is a test
  boundary, not an established hardware maximum or proven EPS-fault fix.

The absolute **360° software angle ceiling**, native vehicle angle filtering,
base torque-reduction law and longitudinal acceleration limits are unchanged.
The separate 119.9° warning threshold still controls warning eligibility. Upstream
curvature-rate limiting and any enabled lane-change smoothing still apply.

### Driver override and Improved Manual Control

- Adds configurable override effort, scaling assistance from an independently
  maintained base level, with a minimum active gain of 0.10.
- With Improved Manual Control **off**, fresh confirmed hands-off detection avoids
  repeated custom low-effort cuts from column-torque oscillation. Native
  torque-dependent reduction remains active; unknown contact falls back to the
  torque-based override behavior.
- With Improved Manual Control **on**, contact plus driver torque can enter manual
  handoff below the configured entry speed. That speed gate controls entry rather
  than forcing handoff to end when speed rises.
- During handoff, follows the measured wheel angle and normally sends inactive,
  zero-gain commands. At high measured angles it can retain a low-gain active
  wheel-following command, subject to both angle/rate envelopes. The keeper enters
  at 90° and releases below 15°.
- Releases manual handoff on hands-off detection or one second of low steering
  demand. Retains torque hysteresis, a two-second reentry guard and a 100 ms contact
  dwell override of that guard. Rejected wheel-following samples require 100 ms of
  safe samples before active wheel following resumes.
- Preserves independent base assistance during manual handoff and restores it
  immediately when override clears. Genuine disengagement or invalid overall
  angle bounds reset that history.
- Parses optional capacitive hands-on-wheel data with a **300 ms freshness limit**.
  Reserved/stale readings are not accepted as fresh hands-off evidence. Adds contact
  timestamps and `manualSteeringOverride` telemetry; global `steeringPressed` remains intact.

### Steering message continuity

- Maintains one continuous EV9 stock-LKAS message stream, including while inactive,
  and blocks duplicate factory LKAS forwarding independently of the AOL latch.
  Active requests still require Panda permission.
- Inactive messages follow the correct MDPS measurement with zero assistance;
  inactive EV9 message encoding uses the supplied angle, no steering sound and
  damping value 100.
- Initializes outgoing angle/filter history from the first transmitted command,
  avoiding disagreement between stored state and the actual inactive command.
- Uses the MDPS sensor appropriate to the transport rather than assuming the
  public steering-angle signal is identical. Reports the actual outgoing EV9 angle
  in actuator telemetry.

## 4. Turn intent, door detection and steering warnings

### Turn intent and doors

- **EV9 Force Turn Desires:** a signal can continue selecting turn intent through
  a predicted stop. It still requires active lateral steering, movement, exactly
  one signal, speed below the lane-change threshold, and no detected blind-spot
  object on the requested side. Owner: [drive_helpers](drive_helpers_starpilot.patch).
- **All four doors:** Hyundai CAN-FD door-open detection includes passenger and
  rear doors instead of only the driver's door. Owner:
  [vehicle patch 02](opendbc/02_door_signals_starpilot.patch).

### Steering-warning qualification

Owners: [customize_warnings_starpilot.patch](customize_warnings_starpilot.patch),
[vehicle patch 01](opendbc/01_customize_warnings_starpilot.patch).

- Hyundai's steering saturation timer changes from **0.4 to 0.3 seconds**. This
  interface-level change applies to Hyundai vehicles generally.
- EV9 angle-controller saturation checking starts above **2.5 km/h**, rather than
  5 m/s (18 km/h). At requests of at least 90°, a measured tracking error above
  2.5° can indicate saturation even when the transmitted command was not clipped.
- Inactive angle controllers reset their saturation state; that cleanup is shared.
- Adds two EV9 paths to the steering-limit notification:
  1. **Qualified controller saturation:** retains saturation persistence and the
     turning/lateral-acceleration-undershoot checks. Eligibility requires an
     absolute requested angle of at least 90° or speed above the configurable
     alert-speed threshold (default 50 km/h). Angle retention uses 85°. Saturation
     can mature before angle eligibility, without starting another 0.3-second wait.
  2. **Additional tracking warning:** absolute request at least **119.9°**, plus
     directional measured-angle or outgoing-command shortfall above **2.5°** for
     **0.3 seconds**. Its independent retention thresholds are 114.9° and 1°.
     Speed alone cannot activate this path.
- Requires active, moving, healthy lateral control and excludes actual manual
  handoff. Invalid timing/data clears the warning state.
- Driver torque suppresses warnings with the historical **two-second holdoff**,
  except when fresh valid HOD explicitly reports no contact. Capacitive touch alone
  without torque does not suppress warnings; unknown/stale HOD falls back to torque.
  The angle-controller saturation timer uses the same qualified driver-input signal.
- Clears cached steering-limit banners and sounds promptly during driver override,
  including the optional Goat variant, without clearing unrelated fault or
  driver-monitoring alerts. EV9 steering-warning audio can stop before its first
  sample finishes. Existing sound selection and Switchback cooldown remain in use.

### Alert presentation

Owner: [alerts_starpilot.patch](alerts_starpilot.patch).

- EV9 steering saturation becomes a compact, single-line **“Turn Exceeds Steering
  Limit”** banner with normal status; EV9 distraction becomes **“Driver Distracted”**
  with user-prompt status. Existing priorities, HUD cues, sounds and durations remain.
- EV9 normal-status alert backgrounds use approximately **50% opacity**, instead
  of 90%, in both device renderers. Critical/user-prompt opacity is unchanged.
- The standard renderer keeps `steerSaturated` visible even when Hide Alerts is on;
  this visibility exemption is shared, not EV9-only.

## 5. Interface, branding and path appearance

### EV9 Edition identity and supported vehicle

Owners: [ev9_edition_starpilot.patch](ev9_edition_starpilot.patch),
[boot_logo_ev9_edition.patch](boot_logo_ev9_edition.patch).

- Brands the standard home screen as **StarPilot – EV9 Edition**. The mici home
  screen gains a separate edition subtitle and smaller main title. The numeric
  progress spinner also displays EV9 Edition.
- Supplies EV9 Edition boot artwork and selects it for the StarPilot logo/default
  fallback. Explicit custom logos and the stock-logo choice remain supported.
- **Restricts driving control to the EV9:** other vehicles receive startup-no-control
  handling, and normal engagement, lateral control, longitudinal control and AOL
  actuation are forced off. Replay and simulation are exempt. This is a functional
  restriction in the edition patch, not only a branding change.

### EV9 startup longitudinal status

Owner: [ev9_longitudinal_status.patch](ev9_longitudinal_status.patch).

- Flashes **OP long ready** at 2 Hz beneath the steering wheel on C3/C3X when
  initialization confirms OP longitudinal mode while the vehicle is still in
  IGN-ON, prompting the driver to complete brake + Start. The prompt stays visible
  while fresh evidence confirms this state.
- Shows steady **OP long** in a bright lilac-to-violet text gradient once vehicle READY is detected, for 30 seconds.
  **Stock ACC** stays solid green; its initial 30-second notice restarts once when
  READY is first confirmed. Text increases from 22 to 28 px, fitting to the badge
  width for longer messages. Cruise engagement does not change the notice.
- Uses fresh, current-session Panda configuration, initialization events and
  control telemetry, plus EV9's existing power READY bit decoded continuously
  from checksum/counter-accepted CAN. The UI checks both the publication time and
  original READY sample time. Saved Alpha settings and cached car parameters do
  not establish the displayed control mode.
- Displays **Long status unavailable** if evidence goes stale during the notice.
  Data recovery and repeated READY transitions do not extend the final 30-second
  window; a new ignition session resets it. Existing alert/road-view visibility
  takes precedence.
- Reports configuration and vehicle power state, not independently verified ECU
  or AEB health. Adds display telemetry/schema fields only; no vehicle-control,
  diagnostic, parameter, firmware or safety changes.

### Standard C3/C3X settings

Owners: [settings_ui_starpilot.patch](settings_ui_starpilot.patch),
[ui_options_starpilot.patch](ui_options_starpilot.patch).

- Renames the StarPilot settings tab to **Vehicle**, retains a permanent sidebar,
  and removes sidebar collapse and edge-swipe navigation.
- Replaces glowing tile grids, multiple columns and horizontally paged toggles
  with larger black/gray scrolling lists, green accents, larger controls and
  wrapping descriptions.
- Removes intermediate Driving Controls and Navigation & Maps folders. Conditional
  Drive Mode and Curve Speed Controller become directly accessible under Gas / Brake.
  The underlying feature controls remain available.
- Steering opens directly into AOL and lane-change controls; Advanced Lateral
  Tuning retains its submenu. Adds the four offroad-only EV9 controls described in
  section 1, with recognized-EV9 gating and a saved-EV9 fallback before recognition.
  Dialog callbacks also prevent writes while driving.
- Enlarges model browsing, map-region selection and navigation controls. Fixes
  pinned map status/actions versus the scrolling region list, including remove-map
  button hit testing. Stacks sound-volume controls above utility toggles and enables
  scrolling in System/Vehicle views.
- Clarifies Minimum Lane Change Speed as mph in the Galaxy settings schema.

The shared C3/C3X layout changes are not vehicle-gated. C4/mici retains its native
settings layout and text sizes, with an added EV9 Steering page. Galaxy exposes
all five new user-facing settings on either device and checks EV9/offroad eligibility
when saving steering settings.

### EV9 Path

Owner: [custom_model_ui_starpilot.patch](custom_model_ui_starpilot.patch);
default enabled by [custom_defaults_starpilot.patch](custom_defaults_starpilot.patch).

- Adds an EV9 Path option to both C3/C3X and mici settings/renderers. The option
  itself has no vehicle-fingerprint gate.
- Draws animated blue while lateral control is active, acceleration-responsive
  rainbow coloring, and gray when inactive. AOL counts as active even without cruise.
- Uses red for selected steering-limit, collision/AEB and driver-attention/restart
  alerts, including themed steering-limit variants, with a brief hold and fade.
- Rejects stale or previous-session telemetry when deciding active/hazard colors.
- While enabled, supersedes ordinary path-color, rainbow and acceleration-color
  options. Their saved preferences remain available when EV9 Path is switched off.
- Changes path appearance, not predicted trajectory geometry. Adjacent blind-spot
  overlays remain the native StarPilot visualization and can be red without an alert.

## 6. Build configuration and verification coverage

Owner: [build_config_starpilot.patch](build_config_starpilot.patch).

- Explicitly sets Hatchling's editable-install import directory to the repository
  root. This prevents package discovery from walking uv's temporary build cache
  and failing on directories deleted during dependency setup.
- Adds focused regressions alongside the runtime/UI patches for defaults,
  engagement/calibration, braking feedback, turn intent, warning suppression/audio,
  curvature limits, path rendering and settings behavior.
- [Vehicle patch 06](opendbc/06_ev9_tests_starpilot.patch) contains tests rather than
  production tuning: EV9 configuration, door/HOD decoding, manual handoff/recovery,
  transport initialization, both steering transports, native Panda limits and
  forwarding/button permissions. Existing generic Hyundai test expectations are
  adjusted for the scoped EV9 behavior and changed warning timer.

## 7. Features retained from stock; inactive archives

These enabled patches **do not replace** StarPilot's driving model, native vehicle
angle filter, base gain law, lane-centering algorithm, post-stop suppression,
low-speed turn hold or turn-initiation lead. Those remain upstream behavior.
Lane-change smoothing remains available; only its default changes to 10.
Longitudinal acceleration limits retain StarPilot values.

Historical patch files are references and are not replayed:

- Deferred `.temp-disabled`: custom lane centering, driver monitoring and power management.
- Previously disabled: auto lock, custom audio, ICBM fixes, quickboot and both
  application/vehicle tap-detection debug patches.
- `.migrated`: preserved Sunnypilot originals. Their enabled StarPilot replacements
  are the implemented changes described here. The old prebuilt patch is represented
  by maintained build/deployment tooling instead of an enabled patch.

## 8. Repository maintenance changes outside the patches

These are preserved directly by upstream sync, rather than encoded in an enabled
application/vehicle patch:

- Stable-branch StarPilot snapshot import with a recorded commit/tree; bundled
  opendbc is edited inside this repository. Sync preserves maintenance tooling and
  archives, replaces application source, and never automatically reapplies patches.
- Unified forward-patch apply/create/update tools, support for bundled vehicle
  paths, explicit three-way application, and disposable-repository maintenance tests.
- EV9 GitHub build workflow replacing upstream build/publication workflows: build
  the triggering `ev9-dev` source for AGNOS using StarPilot's device build tooling.
- Publish only the latest built tree as the parentless `ev9-prebuilt` snapshot with
  source provenance, then promote that exact tree to `ev9` while retaining deployment
  history. The existing master-branch trigger coordinates that promotion.
- Repository guidance, maintenance references, and a documented private-log investigation
  and recorded-input replay workflow.

See [README.md](README.md) for patch operations and
[MAINTENANCE.md](../docs/MAINTENANCE.md) for maintenance details.
This file lives under `patches/` so upstream sync preserves it automatically.

## Enabled patch index

| Patch | Main changelog sections |
| --- | --- |
| [alerts_starpilot.patch](alerts_starpilot.patch) | 2, 4: brake feedback and alert presentation |
| [boot_logo_ev9_edition.patch](boot_logo_ev9_edition.patch) | 5: boot artwork |
| [build_config_starpilot.patch](build_config_starpilot.patch) | 6: editable-install build fix |
| [custom_defaults_starpilot.patch](custom_defaults_starpilot.patch) | 1: defaults and parameter corrections |
| [custom_model_ui_starpilot.patch](custom_model_ui_starpilot.patch) | 5: animated EV9 path |
| [customize_warnings_starpilot.patch](customize_warnings_starpilot.patch) | 4: warning qualification and sound clearing |
| [drive_helpers_starpilot.patch](drive_helpers_starpilot.patch) | 1–4: configuration, AOL, curvature and turn intent |
| [ev9_edition_starpilot.patch](ev9_edition_starpilot.patch) | 5: branding and EV9 control restriction |
| [ev9_longitudinal_status.patch](ev9_longitudinal_status.patch) | 5: 30-second startup control-mode notice |
| [settings_ui_starpilot.patch](settings_ui_starpilot.patch) | 5: shared settings layout |
| [ui_options_starpilot.patch](ui_options_starpilot.patch) | 1, 5: Steering page and EV9 controls on C3/C3X, C4 and Galaxy |
| [opendbc/01_customize_warnings_starpilot.patch](opendbc/01_customize_warnings_starpilot.patch) | 4: Hyundai saturation timer |
| [opendbc/02_door_signals_starpilot.patch](opendbc/02_door_signals_starpilot.patch) | 4: CAN-FD doors |
| [opendbc/03_modify_baseline_starpilot.patch](opendbc/03_modify_baseline_starpilot.patch) | 2–3: EV9 geometry, identity and permission |
| [opendbc/04_panda_safety_limits_starpilot.patch](opendbc/04_panda_safety_limits_starpilot.patch) | 3: Panda envelope and ownership |
| [opendbc/05_steering_and_ev9_limits_starpilot.patch](opendbc/05_steering_and_ev9_limits_starpilot.patch) | 3: controller, handoff and telemetry |
| [opendbc/06_ev9_tests_starpilot.patch](opendbc/06_ev9_tests_starpilot.patch) | 6: vehicle and native safety tests |
