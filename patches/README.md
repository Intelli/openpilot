# Historical Intelli patches

These files preserve work from the former Sunnypilot-based Intelli repositories.
**None are applied to the initial stable StarPilot baseline.** Upstream sync and
GitHub builds do not replay them.

- Root `.patch` and `.disabled` files are the original openpilot patch series.
- `opendbc/` contains the standalone vehicle/safety patch series.
- `assets/openpilot/` keeps custom lock artwork and sounds outside runtime paths.
- `legacy-openpilot-tooling/` keeps the previous sync/update scripts, guidance and
  custom analysis assets for reference.

Review each patch against StarPilot before deciding whether to port it. Root
patch helpers retain their historical manual behavior, including bulk replay and
inverse patch generation. For the copied opendbc patches, see
[`tools/opendbc-patches/README.md`](../tools/opendbc-patches/README.md).

See [the migration guide](../docs/STARPILOT_MIGRATION.md) for the new single-repo
workflow and preserved file locations.
