# Bundled opendbc patches

Vehicle source is tracked directly in the main repository under `opendbc_repo/`.
Patch files in `patches/opendbc/` use standalone paths such as
`opendbc/car/hyundai/carcontroller.py`. The unified root helper adds
`opendbc_repo/` when applying them.

The six formerly enabled patches now end in `.patch.temp-disabled`; the existing
`tap_detection_debug.patch.disabled` keeps its original name. All are inactive,
and their contents are unchanged. `origin.json` records original paths, source
commit/URLs and SHA-256 checksums, with updated archive locations.

## Supported helpers

Use the main helpers:

```sh
./apply_patch.sh --check opendbc/example.patch
./apply_patch.sh opendbc/example.patch
./create_patch.sh opendbc/example
./update_patch.sh opendbc/example
```

Create requires staged source. Update reads original file versions from the
existing patch’s Git blob IDs and compares them with the index, or HEAD versions
when nothing is staged. It keeps committed original hunks and any disabled suffix.
Default update scope includes existing patch paths and newly staged source files;
stage new files before committing to include them automatically. Both accept
`-- PATH...`, relative to `opendbc_repo/`, to override scope; maintenance files are
excluded. Optional `--base <ref>` uses an explicit baseline and ordinary
base-to-index diff scope. Empty, malformed or missing-preimage exports leave the
patch unchanged. See [the patch guide](../../patches/README.md) for details.

`tools/opendbc-patches/apply.sh` is a compatibility wrapper for the unified
application helper. A basename selects one enabled vehicle patch; no arguments or
`--all` selects all enabled vehicle patches. With the current archive, that mode
succeeds without applying anything. `--check` performs ordinary applicability
checks without changing files, independently for each patch. Disabled filenames
are rejected even when explicitly selected. No helper fetches, syncs, commits or
pushes; ordinary apply also leaves staging unchanged.

## Original helper archive

`legacy/` preserves the original standalone helpers and `AGENTS.md` byte-for-byte.
They are historical source, **not supported commands** in the main repository.
They still contain the old Sunnypilot sync and inverse-patch generation logic.
Do not run them in their archive location. Use the root helpers described above.
