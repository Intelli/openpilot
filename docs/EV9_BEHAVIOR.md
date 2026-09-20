# EV9 behavior reference

This describes the maintained branch, not necessarily the build or saved settings
on a device. Verify those using [the drive-review workflow](RECENT_DRIVE_REVIEW.md).
For source, patch ownership and deployment, see [maintenance](MAINTENANCE.md).
The retired custom planner is documented only in [its archive](../patches/archive/EV9_CUSTOM_PLANNER.md).

## Limits and steering ownership

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
- EV9 direct OP-long steering caps the autonomous angle target at **±140°**
  before filtering, including lateral-only operation. Greater turn demand holds
  the bounded target without an added disengagement or boundary cooldown.
  Existing driver override, manual wheel following and rate-limited reentry
  remain in place, so those transitions can transmit angles beyond the target
  cap. Inactive commands still follow the measured wheel within the existing
  360° range. Stock ACC steering and other vehicles do not use this target cap.
  This is a conservative test boundary, not a confirmed EV9 hardware limit or
  a verified fix for EPS faults.
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

## Settings and engagement

| Parameter | Application default / supported range |
| --- | --- |
| `HkgTuningAngleCustomLimitMaxSpeedKph` | 40 km/h / 10–40 |
| `HkgTuningAngleOverrideEffortPercent` | 10% / 10–100 |
| `HkgSharedAutonomyMode` | 0/off; 1/on; legacy 2 also enables handoff |
| `HkgTuningEv9AlertsSpeedKph` | 50 km/h / 10–50 |

The four EV9 controls are offroad-only: Steering → EV9 Steering on C3/C3X,
Settings → Vehicle → EV9 Steering on C4, and Galaxy → Lateral (Steering).
EV9 Path and Path Warning Highlighting are available in both device UIs and
Galaxy → Visual (Display & UI). Both default on in this branch.
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

EV9 Force Turn Desires follows the signal through predicted stops, actual
standstill and inactive lateral control, matching Sunnypilot's signal-intent
eligibility. It requires one signal, speed below the greater of EV9 Limits Speed
and Minimum Lane Change Speed, and no same-side blind-spot detection. Signal
cancellation, hazards, a blocked requested side or disabling the setting clears
the turn intent. A continuously held signal no longer creates a fresh model
turn pulse solely because the car stops and restarts; a signal first selected
while stopped can establish intent immediately. This does not lock the model's
path or enable steering while stopped. Steering activation, navigation desires
and other vehicles retain their existing gates. The follow-up is preserved in
`patches/lane_change_safeguards_starpilot.patch`.

EV9 preview assistance has a separate fixed ceiling of 7 m/s (25.2 km/h),
independent of EV9 Limits Speed. It retains the current-preview handoff to model
demand, opposing-model and manual vetoes, and smooth speed/braking fades.
Restoring this ceiling does not change the signal turn-desire rules above.
The road-edge guard for the former extended speed range is retired in
`patches/ev9_turn_signal_edge_guard.patch.disabled` and excluded from replay.

## Steering warnings

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

## Path appearance

EV9 Path provides animated blue and acceleration rainbow in both renderers,
preserving saved native path-color choices when disabled. Path Warning Highlighting
is a separate default-on Model UI option and works over any base style. Its helper
and renderer overlay match the parked upstream PR; only the EV9 default is on.
Selected fresh, current-drive alerts with nonzero size trigger a red overlay,
which holds for 0.5 seconds then fades for 1 second. It replaces the old EV9 color
blend, so its appearance needs device validation before upstream publication.
Geometry and adjacent blind-spot overlays remain native StarPilot behavior.
Blind-spot red can appear without an alert and is independent of warning highlighting.
