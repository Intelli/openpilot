# Intelli patch workflow

Historical patch contents are preserved; **none are applied to the initial
stable StarPilot baseline**. Upstream sync and GitHub builds do not replay them.

## Patch locations and state

| Location / suffix | Meaning |
| --- | --- |
| `patches/<name>.patch` | Enabled patch using paths relative to the main repository |
| `patches/opendbc/<name>.patch` | Enabled vehicle patch using paths relative to `opendbc_repo/` |
| `.patch.temp-disabled` | One of the 17 formerly enabled patches, paused for StarPilot porting |
| `.patch.migrated` | Unchanged historical original whose supported port is recorded in an enabled patch or replacement build tooling |
| `.disabled` (including `.patch.OUTDATED.disabled`) | A patch that was already disabled before migration |

The 17 formerly enabled patches started as temporarily disabled archives. Migrated
originals now use `.migrated`; the six previously disabled patches keep their
original suffixes. All archive suffixes are skipped by application. Port source,
export a new enabled patch, then rename the historical original to `.migrated`.
Keep the original contents intact. Updating a disabled patch keeps its suffix;
exporting a new patch defaults to enabled, or accepts an explicit disabled suffix
when you want to keep it inactive.

The six migrated vehicle patches use prefixes `01_` through `06_` to preserve their
dependency order. The eight enabled root patches contain custom defaults, EV9 Edition branding,
settings UI, EV9 control configuration/curvature, warning policy, compact alerts,
EV9 settings controls, and the EV9 animated path effect. Only lane centering,
driver monitoring and power management remain `.temp-disabled` by request. The old prebuilt
patch is archived as `.migrated` because the StarPilot build/publish tooling has
already replaced its Sunnypilot implementation; it is not replayed.
See the migration guide for deliberate adaptations and omitted legacy defaults.

`assets/openpilot/` preserves custom artwork and audio. Original helpers and
analysis assets are in `legacy-openpilot-tooling/`, with source checksums in its
`origin.json`. Original opendbc helpers are in `tools/opendbc-patches/legacy/`.
These archived scripts are historical references, not supported commands.

## Apply and check

From the repository root (script paths also work from another directory):

```sh
./apply_patch.sh                              # All enabled patches; skips already-applied changes
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

Update retains the original patch baseline without needing a commit reference:

```sh
./update_patch.sh example
./update_patch.sh opendbc/door_signals

# Explicitly rebase, or recover when original Git objects are unavailable:
./update_patch.sh example --base <unpatched-commit>
```

By default, the helper reads original file versions from the existing patch's
embedded Git blob IDs, without guessing commits, and compares them with the Git
index. With nothing staged, the index contains HEAD versions. This preserves
committed original hunks and captures committed changes to existing patch paths;
unstaged edits are excluded.

The index must contain the complete intended result. Updating does not apply
missing historical hunks for you; port or apply a patch before regenerating it.

Default scope is the existing patch's files plus newly staged source files,
excluding maintenance files. Stage new files before committing if they should be
included automatically. A path selection after `--` replaces this scope.
Explicit `--base <ref>` instead uses an ordinary base-to-index diff and its scope;
select paths to avoid including unrelated changes since an older base. Update
does not require staged changes, but the resulting patch must be nonempty.
Malformed patches or unavailable preimage objects fail without overwriting the
existing patch; use an explicit base when those original objects are unavailable.
Patches that only change file permissions have no blob IDs: their original
content comes from HEAD. Use `--base` to include already-committed content
amendments to those files.

A bare name resolves an existing enabled, temporarily disabled, or previously
disabled file and preserves its suffix. Ambiguous names require the full disabled
filename. Empty exports or errors leave existing patch contents unchanged.

Both helpers accept an optional path selection after `--`:

```sh
./create_patch.sh example -- selfdrive/path/to/file.py
./update_patch.sh opendbc/door_signals -- opendbc/car/hyundai/carstate.py
```

Paths are relative to the main repo for a main patch, or to `opendbc_repo/` for a
vehicle patch. Select all files belonging to an updated patch; omitted files will
not be part of its replacement. `create_patch.sh` also accepts `--base <ref>` when
an explicit older base is needed.

See [the migration guide](../docs/STARPILOT_MIGRATION.md) for upstream and deployment
workflow details. Local tooling checks use disposable Git repositories; no vehicle
patch is applied as part of those checks.
