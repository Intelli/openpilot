# Sunnypilot upgrade archive — October 4, 2026

The active application advances from official `54fb2750bab46111cda1fbf2fd2267ad7c2d5e03`
to `d021f6ca41375e58be8125801547e84939e0c503` (798 upstream commits). Its exact
opendbc pin advances from `7c35b75469408ef8bf14e78737a3e0ad83e15d61` to
`28303fcd1cc457f67d405407858223e0b338df20`. Current provenance is recorded in the
root application and vehicle manifests.

This directory preserves superseded implementations for reference:

| Directory | Archived content |
| --- | --- |
| `application/` | Previous power-management feature patch |
| `opendbc/` | Previous six vehicle feature patches, including baseline physics now supplied upstream |
| `build-compat/` | Previous device-build patch, warp compatibility helper and its tests |

None of these nested archive files is an enabled replay input. The active series
contains 14 application and five vehicle patches. Vehicle `01_modify_baseline.patch`
has no enabled replacement because upstream now supplies its physics; the remaining
vehicle filenames keep `02_`–`06_` ordering.

Application ports use the new `openpilot/` layout and current parameter/service
APIs without replacing new upstream files wholesale. Driver monitoring now uses
`policy.py`: eye/blink thresholds already match upstream, leaving only the phone
threshold in enabled patch `10_`. Native builds now target AGNOS 19.7 / `comma_arm64`
and the fused compiler with verified pinned QCOM small-model/DM captures.

Historical restoration remains documented in
[the consolidated archive](../sunnypilot-consolidated-20261004/) and
[the changelog](../../CHANGELOG.md). This archive records provenance, not successful
full native compilation or device qualification of the upgrade.
