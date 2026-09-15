# Archived Intelli opendbc patches

The main repository now carries StarPilot's `opendbc_repo/` source directly.
`patches/opendbc/` preserves the standalone Intelli/opendbc patches verbatim;
they have **not** been applied during migration. Their `opendbc/...` paths are
relative to the former standalone repository, so replay must add `opendbc_repo/`.

## Explicit replay

From the main repository, inspect a patch and check its applicability first:

```sh
tools/opendbc-patches/apply.sh --check door_signals.patch
```

Only when intentionally restoring that behavior:

```sh
tools/opendbc-patches/apply.sh door_signals.patch
```

An explicit `--all` selects the six `.patch` files in filename order. The
`.patch.disabled` file is retained as reference and is never selected. With no
argument the helper exits without applying anything. It never fetches, syncs,
stages, commits or pushes. Ordinary `git apply` failures stop replay for manual
review; earlier patches may already have applied. `--check --all` checks each
patch against the current tree independently, not the result of earlier patches.
An already-applied patch is detected by a reverse applicability check and skipped.

These historical patches were written for Sunnypilot-derived Intelli code. Check
their intent against StarPilot's existing implementation before restoring them.

## Original helper archive

`origin.json` records the original commit, source URLs and SHA-256 checksums.
`legacy/AGENTS.md` preserves the original standalone repository guidance as history.

`legacy/` preserves these seven original standalone scripts byte-for-byte:
`apply_patch.sh`, `apply_patch_conflicts.sh`, `create_patch.sh`,
`create_patch_manual.sh`, `fix_patch.sh`, `sync-upstream.sh`, and `update_patch.sh`.
They are historical source, **not supported commands in the new repository**.
In particular, the old sync targets Sunnypilot's HKG branch, and create/update
helpers invoke sync, stage changes and generate inverse HEAD-relative diffs.
Running them from their new location would use the wrong repository/path context.

Use the wrapper above for explicit replay. Maintain patch files manually after
reviewing the desired diff; do not run archived inverse-generation helpers.
No upstream-sync or deployment workflow invokes these patches or scripts.
