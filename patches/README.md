# Intelli patch workflow

Historical patch contents are preserved; **none are applied to the initial
stable StarPilot baseline**. Upstream sync and GitHub builds do not replay them.

## Patch locations and state

| Location / suffix | Meaning |
| --- | --- |
| `patches/<name>.patch` | Enabled patch using paths relative to the main repository |
| `patches/opendbc/<name>.patch` | Enabled vehicle patch using paths relative to `opendbc_repo/` |
| `.patch.temp-disabled` | One of the 17 formerly enabled patches, paused for StarPilot porting |
| `.disabled` (including `.patch.OUTDATED.disabled`) | A patch that was already disabled before migration |

There are currently **17 temporarily disabled patches and six previously disabled
patches**, with no enabled patches. Both disabled suffixes are skipped by bulk
application and rejected when passed explicitly. After porting and reviewing one,
rename it to end in `.patch` to enable it. Updating a disabled patch keeps its
suffix; exporting a new patch defaults to enabled, or accepts an explicit disabled
suffix when you want to keep it inactive.

`assets/openpilot/` preserves custom artwork and audio. Original helpers and
analysis assets are in `legacy-openpilot-tooling/`, with source checksums in its
`origin.json`. Original opendbc helpers are in `tools/opendbc-patches/legacy/`.
These archived scripts are historical references, not supported commands.

## Apply and check

From the repository root (script paths also work from another directory):

```sh
./apply_patch.sh                              # All enabled patches; currently a no-op
./apply_patch.sh --check                      # Check enabled patches without changes
./apply_patch.sh example.patch                # One enabled main-repository patch
./apply_patch.sh opendbc/example.patch         # One enabled vehicle patch
./apply_patch.sh --check opendbc/example.patch
```

Bulk replay visits `patches/*.patch` first, then `patches/opendbc/*.patch`, sorting
filenames within each directory. Use filenames to establish order, or select
individual patches when dependencies need another order. Vehicle patches retain
standalone paths such as `opendbc/car/hyundai/...`; the helper adds
`opendbc_repo/` when applying them to the main repository.

Already-applied patches are skipped. Normal replay does not change the index and
stops at the first failed patch; earlier successful patches remain applied.
`--check` checks each patch independently against the current working tree. It
does not simulate the results of earlier patches in a dependent series.

Explicit `--3way` enables Git's three-way fallback, stages changes, and can leave
conflicts to resolve. `apply_patch_conflicts.sh` opts into that mode. Combining it
with `--check` still performs an ordinary, non-mutating applicability check.

`tools/opendbc-patches/apply.sh` forwards to the unified helper with vehicle-only
selection. Its no-argument/`--all` mode selects only enabled vehicle patches.

## Create from staged edits

Stage the intended source changes, then export them:

```sh
git add selfdrive/path/to/file.py
./create_patch.sh example

# Vehicle-only export, stored with standalone opendbc paths:
git add opendbc_repo/opendbc/car/hyundai/carcontroller.py
./create_patch.sh opendbc/example
```

Creation compares **HEAD to the staged index**, so unstaged edits are excluded.
It preserves new/deleted files, binary content and executable modes. Main patches
may contain application files from anywhere in the main repo, including bundled
vehicle files; `opendbc/<name>` restricts export to `opendbc_repo/` and strips that
prefix. Maintenance tools, archives and patch files are excluded.

The helpers write only the patch file. They do not sync, apply patches, change
source files, stage, commit or push. Review and stage the output patch separately.
`create_patch_manual.sh` is an alias for the same staged export. Creation refuses
to overwrite any enabled or disabled patch with the same name.

## Update a patch

Update replaces the **whole patch**, so an explicit base is required:

```sh
# For an initial port where the complete replacement is staged against HEAD:
./update_patch.sh opendbc/door_signals --base HEAD

# If the original patch's changes are already committed, use the unpatched base:
./update_patch.sh example --base <unpatched-commit>
```

The latter compares the base with the staged index, retaining committed changes
since that base as well as staged amendments. Choose the base and scope for the
complete intended patch: unrelated changes since an older base are included unless
excluded by a path selection. An incremental diff against an already-patched HEAD
would omit the original behavior, which is why update has no implicit base.
At least one source change must be staged in the selected scope.

A bare name resolves an existing enabled, temporarily disabled, or previously
disabled file and preserves its suffix. Ambiguous names require the full disabled
filename. Empty exports or errors leave existing patch contents unchanged.

Both helpers accept an optional path selection after `--`:

```sh
./create_patch.sh example -- selfdrive/path/to/file.py
./update_patch.sh opendbc/door_signals --base HEAD -- opendbc/car/hyundai/carstate.py
```

Paths are relative to the main repo for a main patch, or to `opendbc_repo/` for a
vehicle patch. Select all files belonging to an updated patch; omitted files will
not be part of its replacement. `create_patch.sh` also accepts `--base <ref>` when
an explicit older base is needed.

See [the migration guide](../docs/STARPILOT_MIGRATION.md) for upstream and deployment
workflow details. Local tooling checks use disposable Git repositories; no vehicle
patch is applied as part of those checks.
