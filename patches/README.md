# Intelli patch workflow

Supported root commands retain the familiar apply/create/update workflow while
exporting forward diffs and keeping sync, staging and publication explicit.
See [maintenance](../docs/MAINTENANCE.md) and [EV9 behavior](../docs/EV9_BEHAVIOR.md)
for source provenance and current behavior.

## Patch locations and state

| Location / suffix | Meaning |
| --- | --- |
| `patches/<name>.patch` | Enabled patch with main-repository paths |
| `patches/opendbc/<name>.patch` | Enabled vehicle patch with paths relative to `opendbc_repo/` |
| `patches/archive/` | Historical implementations and notes; excluded from replay |
| `.patch.migrated`, `.patch.temp-disabled`, `.disabled` | Preserved historical originals; never replayed |

Current enabled patches are:

- `sunnypilot_ev9_customizations.patch`: restored application changes relative to
  the official Sunnypilot baseline in `sunnypilot-upstream.json`.
- `boot_logo_ev9_edition.patch`: custom boot image and its Sunnypilot installation hook.
- `sunnypilot_device_build.patch`: device-build portability changes.
- `opendbc/01_sunnypilot_ev9_customizations.patch`: restored vehicle changes relative
  to official opendbc `7c35b7546940`, recorded in `opendbc-upstream.json`.

The application was restored from Intelli `5928a37ad187`, with customized vehicle
snapshot `5a3f3761f586` and the original dependency pins. Those customized snapshots
are restoration provenance; the enabled forward patches use official baselines.
The current vehicle baseline is the exact pin of the official application baseline,
not a guessed merge-base of deployment history.

StarPilot implementations are retained under `archive/starpilot-20260920/`,
including their documentation. They are not applied to restored Sunnypilot.
Other archived experiments and original patch suffixes remain historical references.
The [changelog](CHANGELOG.md) describes restoration and earlier work.

`assets/openpilot/` retains custom artwork/audio. `legacy-openpilot-tooling/` and
`tools/opendbc-patches/legacy/` preserve original helpers with provenance/checksums.
Do not run those copies: their creators automatically sync/stage and generate
inverse diffs. Supported root helpers produce forward exports without those side effects.

## Sync and replay

`./sync-upstream.sh --check [ref]` previews the application and its exact dependency
pins. `--allow` stages the imported snapshot. Add `--opendbc` for vehicle-only sync.
Both default to Sunnypilot's `hkg-angle-steering-2025`; no historical standalone
checkout participates. Sync removes custom source in its scope while preserving
maintenance files and patch archives. It does not replay patches, merge, commit or push.

Save edits and update patch records before sync. Import, then run the application
helper below, review and stage the result. New upstream snapshots can require ports;
current-tree `--check` is not a simulated replay of a dependent patch series.

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

See [the maintenance guide](../docs/MAINTENANCE.md) for upstream and deployment
workflow details. Local tooling checks use disposable Git repositories; no vehicle
patch is applied as part of those checks.
