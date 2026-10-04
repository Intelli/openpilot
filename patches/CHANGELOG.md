# Sunnypilot restoration

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

The working source restores the preserved Sunnypilot application
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
