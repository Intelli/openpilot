# Sunnypilot maintenance history

## October 4, 2026: latest Sunnypilot port

Imported official application `d021f6ca41375e58be8125801547e84939e0c503` and exact
embedded opendbc `28303fcd1cc457f67d405407858223e0b338df20`, advancing 798 upstream
application commits from `54fb2750bab4`. Ports move application paths under
`openpilot/` and preserve the newer parameter API, renamed control services,
model selector and MADS rendering gates.

The enabled inventory is 14 application plus five vehicle patches. Upstream now
supplies the former vehicle baseline-physics patch; its implementation is archived.
Driver-monitoring eye/blink settings already match upstream; the remaining phone
threshold customization is ported to `monitoring/policy.py`.

The build targets AGNOS 19.7 / `comma_arm64`, the fused driving compiler and
verified pinned QCOM default small-model/driver-monitoring captures. The oversized
large-model ONNX is hash-verified and imported losslessly in 45 MiB chunks;
this preserves its bytes without enabling optional Chestnut capture. Superseded
patches/helpers remain in [the upgrade archive](archive/sunnypilot-upgrade-20261004/README.md).

Focused port, model-validator and maintenance checks do not qualify the new full
native build or vehicle behavior. GitHub compilation and on-device validation remain
required before making those claims. Patch-helper staging semantics are unchanged.

## Verified StarPilot preservation

All 13 application and six vehicle StarPilot patches were compared byte-for-byte
with source commit `09c6cf07911a`. Their ordered replay from recorded baseline
`c3e4ec630f41` reproduced all 99 patched source paths exactly, including the latest
EV9 main-cruise OP-long changes. No application or vehicle source changes were
missing from the archive.

`archive/starpilot-20260920/manifest.json` catalogs payload hashes, paths,
historical originals and provenance. Exact former repository guidelines,
maintenance and patch-workflow documents are retained in its `context/` folder.
Preservation does not enable StarPilot behavior in the active Sunnypilot source.

## Separate feature patches

The application restoration is now recorded in twelve numbered feature patches,
with boot artwork and device-build compatibility retained as separate patches.
Vehicle restoration is recorded in six numbered feature patches. The former
consolidated patches are preserved byte-for-byte under
`archive/sunnypilot-consolidated-20261004/`. This changes no application or
vehicle source and enables individual feature maintenance.

Shared-file updates reconstruct the recorded series in disposable indexes,
preserve peer ownership and verify final replay before replacing a patch. Exact
preimage payloads are retained in `baselines/` so automatic updates work after
fresh clones. Historically disabled experiments remain disabled.

## Source restoration

The September 2026 StarPilot source is preserved at local branch
`codex/ev9-starpilot-archive-20260920`, commit
`09c6cf07911a0b75954222f0b903347e8baa122d`.
Its enabled application/vehicle patches and behavior notes are archived in
[`archive/starpilot-20260920/`](archive/starpilot-20260920/).

The initial restoration imported the preserved Sunnypilot application
`5928a37ad18783068ee26b187f6a7ddb9ff9c3d3` and its exact seven dependency pins.
All dependencies are ordinary tracked files; the `opendbc` symlink still resolves
to `opendbc_repo/opendbc/`. Upstream LFS inputs are materialized before import.

The modern forward patch generator/updater, explicit patch replay, collision-safe
snapshot imports and exact-built-tree publication are retained. Sunnypilot and
opendbc upstream imports have separate provenance. The custom boot artwork is
ported with a small Sunnypilot startup hook. The AGNOS build and compatible
Qualcomm model-input handling are adapted for the restored source.

Forward patches record the restored application and vehicle differences against
their actual Sunnypilot baselines, plus boot artwork and build-portability changes.
Historical inverse patches remain archived and are not normal replay inputs.
See [`README.md`](README.md), [maintenance](../docs/MAINTENANCE.md) and
[current EV9 behavior](../docs/EV9_BEHAVIOR.md) for the maintained workflow.
