# Sunnypilot EV9 Edition behavior

The application is restored from `5928a37ad18783068ee26b187f6a7ddb9ff9c3d3`,
the last Sunnypilot source before the September 14, 2026 StarPilot migration.
Vehicle source is restored from its pinned Intelli/opendbc revision
`5a3f3761f586b8107fb8a66b449fa50806cd8f6f`, now embedded in `opendbc_repo/`.
The modern maintenance and deployment tooling is retained. StarPilot-specific
control and engagement changes are archived rather than replayed.

## Driving and engagement

The preserved Sunnypilot lane-centering implementation in
`selfdrive/controls/controlsd.py` is restored, including its lane/road-edge
selection, correction pacing and display telemetry. `AdvancedLaneCentering`
retains its original compiled default. Existing device parameters override defaults.
This source restoration does not reset preferences or prove identical behavior
to the old installed build; its selected model and effective settings also matter.

Sunnypilot MADS supplies lateral engagement and its main-cruise/unified-engagement
settings. The EV9-only control restriction, warning policy, driver-monitoring
customizations and power-management changes return with the preserved source.
The StarPilot AOL and main-button engagement implementation is not active.

## Vehicle control and safety

The embedded Hyundai controller restores the previous EV9 low-speed steering
limits, override effort, torque-reduction settings and manual-handoff logic.
All-door CAN-FD detection and the original steering-saturation timing return.
The EV9 Panda safety model and focused native-safety regressions are restored
with the corresponding controller source. They must be built and shipped together.

Application defaults and vehicle-controller fallbacks are distinct. Read the
effective `HkgTuning*` parameters before interpreting a drive. Do not substitute
the later StarPilot tuning thresholds or its direct OP-long angle cap.

## Appearance and boot

The previous EV9 UI, custom path rendering and hands-free statistics return.
The later custom boot artwork is retained at
`sunnypilot/selfdrive/assets/images/ev9_boot.jpg`. On device manager startup,
`sunnypilot/system/boot_logo.py` installs the AGNOS JPEG and, when present, PNG
variant, retaining their expected orientation and restoring root mount options.
A failure to install artwork does not stop manager startup.

## Qualification

The GitHub build compiles native components from this source and promotes its
exact output through `ev9-prebuilt` to `ev9`. It does not overlay upstream native
binaries. Qualcomm model captures are separate pinned inputs, checked against
their compatible ONNX/compiler/runtime sources. See the build manifest and
[maintenance guide](MAINTENANCE.md).

Local maintenance checks do not establish an AGNOS build or on-vehicle behavior.
The restored EV9 safety test class ran 78 tests: 66 passed, eight failed and four
were skipped. The same eight failures reproduced against the untouched saved
snapshot; they are inherited torque/request checks on its angle-steering class.
The eleven focused angle/configuration checks passed, but some are placeholder
checks and the existing suite does not qualify the low-speed threshold boundaries.
Before comparing lane centering, verify the installed source/build commits,
runtime OS, selected driving model and effective parameters. Historical StarPilot
behavior is preserved in
[`patches/archive/starpilot-20260920/EV9_BEHAVIOR.md`](../patches/archive/starpilot-20260920/EV9_BEHAVIOR.md).
