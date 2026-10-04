# Sunnypilot EV9 Edition behavior

Current official baselines are application
`d021f6ca41375e58be8125801547e84939e0c503` and embedded opendbc
`28303fcd1cc457f67d405407858223e0b338df20`. The October 4 upgrade advances 798
upstream application commits from the restoration baseline. Intelli features are
ported onto this newer source through 14 application and five vehicle patches.

Historical restoration used pre-StarPilot Intelli application `5928a37ad187`
and vehicle snapshot `5a3f3761f586`. Those identify feature provenance, rather than
the current imported source. StarPilot control and engagement implementations
remain archived.

## Driving and engagement

Lane-centering customization in `openpilot/selfdrive/controls/controlsd.py`
retains lane/road-edge selection, correction pacing and display telemetry while
preserving newer upstream control paths and renamed services. Its experimental
`AdvancedLaneCentering` setting defaults to off. Existing device preferences
remain authoritative; an update does not reset them.

The custom curvature helper allows the EV9 low-speed lateral envelope while
retaining the normal higher-speed limit and jerk limiting. Sunnypilot MADS supplies
lateral engagement and its main-cruise/unified-engagement settings. The EV9-only
startup restriction and custom steering warning policy remain; the archived
StarPilot AOL/main-button engagement implementation is not replayed.

Driver monitoring uses the newer `openpilot/selfdrive/monitoring/policy.py`.
Upstream already supplies eye threshold 0.65 and blink threshold 0.865; enabled
patch `10_driver_monitoring.patch` retains only the phone threshold change to 0.68.
It preserves the newer upstream monitoring logic.

## Vehicle control and safety

The embedded Hyundai controller retains EV9 low-speed steering limits, override
effort, torque-reduction settings and manual-handoff logic. All-door CAN-FD detection
and the 0.3-second steering-saturation timer remain. The vehicle baseline-physics
change formerly in `01_modify_baseline.patch` is now provided by upstream and is
archived. EV9-specific Panda lateral limits remain in enabled patch `02_`; controller
and safety source must be built and shipped together.

The EV9 controller uses the preserved Sunnypilot acceleration/jerk envelope:
4.2 m/s² and 4.2 m/s³ at or below `HkgTuningAngleCustomLimitMaxSpeedKph`
(40 km/h by default), then 3.5886 m/s² and 3.5886 m/s³ above it. The
application retains its separate higher-speed 3.0 m/s² limit with road-bank
compensation. These limits depend on speed and do not impose a fixed 45° cap.

Custom override effort defaults to 10%. On EV9, the custom reduction and manual
handoff require both driver torque and confirmed HOD contact (status 1–4, with an
actual signal timestamp no more than 300 ms old). Hands-off, missing, reserved,
stale or future-dated HOD readings bypass custom override and release its latches
immediately. Native Sunnypilot torque-dependent assistance and its rate history
continue unchanged; the effort-reduction floor cannot increase that native gain. At 100%
effort the custom gain reduction is disabled. Angle requests, filtering and
controller/Panda envelopes are unchanged by this contact guard.

Application defaults and vehicle-controller fallbacks are distinct. Read effective
`HkgTuning*` and `HkgSharedAutonomyMode` parameters before interpreting a drive.
Retaining feature intent across this upstream upgrade does not establish identical
vehicle behavior; the selected model and effective settings also matter.

## Appearance, statistics and power

EV9 path coloring and the lane-centering overlay retain the newer upstream MADS
rendering gates and path-width filtering. Model settings retain the new small/big
model selector and camera-offset control alongside the custom centering and EV9
vehicle options. EV9 hands-free statistics continue recording and displaying
tracked and hands-free distance; custom engagement audio and branding remain.
Retained auto-lock icons do not enable the disabled auto-lock implementation.

Offroad power, screen and model-manager changes are adapted to the newer source.
Idle state uses the current `IsOffroad` setting; the removed `IsOnroad` parameter
must not block model-catalog refresh or override Panda's device-state and ignition guards.
Boot artwork lives at `openpilot/sunnypilot/selfdrive/assets/images/ev9_boot.jpg`.
On manager startup, `openpilot/sunnypilot/system/boot_logo.py` installs the AGNOS
JPEG and, when present, PNG variant, preserving orientation and root mount options.
Artwork installation failure does not stop manager startup.

## Qualification

The maintained build targets AGNOS 19.7 / `comma_arm64`, compiles native source
and promotes its exact output through `ev9-prebuilt` to `ev9`. It uses the newer
fused driving compiler and verified pinned QCOM captures for the official default
small model and driver monitoring. Optional Chestnut capture is outside this bundle.
The large upstream ONNX is retained losslessly in hash-verified 45 MiB chunks;
its storage format does not select that model at runtime.

Focused source, patch-replay, model-input and maintenance checks do not establish
an AGNOS build or on-vehicle behavior. Full native compilation still requires the
GitHub build; packaged linking and device inference/timing remain to be verified.
Before comparing lane centering, verify installed source/build commits, runtime OS,
selected model and effective parameters. See [the device-build guide](how-to/laptop-device-build.md)
and [maintenance](MAINTENANCE.md). Historical StarPilot behavior is preserved in
[its archive](../patches/archive/starpilot-20260920/EV9_BEHAVIOR.md).
