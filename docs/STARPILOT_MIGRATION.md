# Stable StarPilot migration

## Baseline

This repository now carries the stable `StarPilot` branch from
[firestar5683/StarPilot](https://github.com/firestar5683/StarPilot/tree/StarPilot).
Upstream's [installation documentation](https://wiki.firestar.link/) distinguishes
the stable `firestar5683/StarPilot` install from the unstable `firestar5683/Dom`
install. We fetch only `refs/heads/StarPilot`.

The first snapshot is `c3e4ec630f41c4baa43254a90f718abd1bf764a1`.
`starpilot-upstream.json` records its commit and Git tree. The initial import
matched upstream outside the explicitly preserved maintenance files. Migrated
custom defaults and EV9 Edition changes are now recorded in enabled patches;
historical steering/tuning patches remain disabled. The baseline uses StarPilot's
own vehicle support and behavior.

`opendbc_repo/`, `panda/`, and the other bundled dependencies are ordinary files
from that same snapshot. `opendbc` links to `opendbc_repo/opendbc`. Make future
vehicle edits here; the standalone Intelli/opendbc repository is no longer a
dependency. Its local checkout and remote repository have been left available
as historical references.

## Importing another stable snapshot

From the repository root:

```sh
./sync-upstream.sh --check
./sync-upstream.sh --allow
```

The first command fetches the stable branch and shows differences against HEAD.
The second replaces application files and stages the resulting source tree and
provenance. Review and commit it on `ev9-dev` when ready. Neither command commits,
pushes, builds or applies patches. `./update.sh` accepts the same arguments.
Without `--allow`, a changed upstream commit is reported without importing it.

The script refuses application edits, an active merge/rebase, dirty submodules,
or untracked/ignored files that the import would overwrite. It preserves the
maintenance paths listed in the script. A sync replaces even previously committed
application customizations; restoring selected patches is a separate reviewed
step. Snapshot imports preserve Intelli's branch history without merging upstream
history. Only the latest upstream snapshot is fetched, limiting binary-history
downloads.

On the first conversion, old submodule checkouts are moved intact to
`.git/starpilot-backups/<timestamp>-<pid>/`, with their paths and previous main
commit recorded. Their relative `.git` pointers are usable again after restoring
the original paths. This is a local recovery copy, not part of the published repo.
The import bypasses legacy LFS filters and checkout hooks to restore upstream
bytes directly.

## Preserved work

| Location | Contents |
| --- | --- |
| Root `apply_patch*.sh`, `create_patch*.sh`, `update_patch.sh` | Unified replay and staged forward-patch export helpers |
| `patches/*.patch*` | Openpilot patches; formerly enabled patches use `.temp-disabled`, pre-existing disabled suffixes are unchanged |
| `patches/assets/openpilot/` | Custom lock artwork and audio for future patch porting |
| `patches/legacy-openpilot-tooling/` | Original patch and sync/update helpers, guidance, custom analysis assets and checksums |
| `patches/opendbc/` | Standalone opendbc patches, copied verbatim |
| `tools/opendbc-patches/legacy/` | Original standalone helpers and guidance |
| `tools/opendbc-patches/origin.json` | Standalone source commit and archive checksums |

All 17 patches that were enabled before migration now have the `.temp-disabled`
suffix. The six previously disabled patches retain their `.disabled` names.
Historical patch contents are unchanged. Enabled `custom_defaults_starpilot.patch`
and `ev9_edition_starpilot.patch` record the migrated defaults and EV9 Edition
changes. The defaults include completion of training version `0.2.0`, matching
the old custom-defaults patch. `./apply_patch.sh` skips changes already applied.
Re-enable individual reviewed patches by renaming them to end in `.patch`.

The root helpers now support both patch locations. Application discovers enabled
root patches first, then vehicle patches, and adds `opendbc_repo/` to standalone
vehicle paths. Create exports staged source. Update reconstructs original file
versions from the existing patch’s Git blob IDs and compares them with the index
(HEAD versions when nothing is staged), preserving committed original hunks and
the existing suffix. Its default scope includes existing patch paths and newly
staged source files; `-- PATH...` overrides scope and `--base <ref>` selects an
explicit baseline. Maintenance files are excluded. Empty, malformed or missing-
preimage exports leave the patch unchanged. Exporters do not sync, modify source,
stage, commit or push. Neither sync nor CI invokes these helpers.
See [the patch guide](../patches/README.md) for examples and scope selection.
Original helper copies are historical reference; do not run archived scripts.

## Build and deployment branches

1. Push a reviewed source commit to **`ev9-dev`**.
2. The GitHub build checks out that exact SHA on an ARM Ubuntu runner. It uses
   StarPilot's device container, extracts a sysroot from upstream's AGNOS image,
   and runs `./build`. The upstream build clears native build signatures and
   recreates `prebuilt` only after success.
3. The publisher commits the built output to **`ev9-prebuilt`**, recording
   `Source-Commit: <ev9-dev SHA>`. This branch contains one parentless commit for
   the latest build. The publisher replaces only this branch with an explicit
   force-with-lease against the fetched tip, so a concurrent publication is not
   overwritten. Each snapshot contains only the current build's files.
4. The existing workflow on **`master`** reacts to build success and runs the
   deployment-sync helper from `ev9-dev`. That helper copies the exact tree from
   **`ev9-prebuilt`**, including rebuilt binaries and the `prebuilt` marker, into
   a new **`ev9`** commit. It preserves `ev9` history and records both
   `Source-Commit: <ev9-dev SHA>` and `Build-Commit: <ev9-prebuilt SHA>`.

Install **`Intelli/ev9`** on the device. Its files match the published GitHub
build; `ev9-dev` is for development. The sync helper validates build provenance
and the `prebuilt` marker before promotion. Repeating a promotion with the same
tree and provenance makes no new commit; a new build/source is recorded even
when its file contents are identical.

Publishing an identical snapshot for the same source is also a no-op once
`ev9-prebuilt` has a single root commit. The first publication after switching
from the earlier history-preserving publisher replaces its history even if the
payload is unchanged. `ev9-dev` retains development history and `ev9` retains
deployment history. Old build-commit IDs may eventually be pruned from Git;
previously deployed files remain available through `ev9` history.

Do not copy the `ev9-dev` source tree directly to the install branch. Upstream
ships tracked native binaries and a `prebuilt` marker, which disables device
compilation. A source-only promotion can therefore display updated Python UI
while still loading old compiled code. In particular, `common/params_keys.h`
defaults are compiled into `common/params_pyx.so` and must be rebuilt together.

Custom defaults initialize missing settings. Existing `/data/params/d` values
win over `/cache/starpilot/params/d` cached values, which win over compiled
defaults. Installing a corrected build does not overwrite saved preferences or
a saved training-completion value. Change any retained values explicitly when
upgrading an existing installation; uninstall is not a reliable defaults reset.

The workflow file and display name remain `sunnypilot-build-prebuilt.yaml` and
`sunnypilot prebuilt action` solely because the default-branch workflow subscribes
to that name. The implementation builds StarPilot. Renaming it later requires
updating the subscription on `master` at the same time.

The existing `PREBUILT_PUSH_TOKEN` and `ev9-dev` GitHub environment remain in use.
No separate test gate was added. The build uses bundled opendbc and publishes its
own compiled output; the former Sunnypilot prebuilt download/overlay is removed.
Other inherited root workflows were retired so that upstream-owner automation
and old Sunnypilot jobs do not run in this fork.

## Verification and scope

Local integration checks cover snapshot conversion, maintenance preservation,
collision refusal, legacy LFS/hooks, deployment history, source SHA propagation,
file removals and promotion of the exact published build. They use temporary Git
repositories and never publish to GitHub.

The initial migration build succeeded on GitHub. Future deployments continue to
use the GitHub build workflow.
Local Python dependencies and compiled extensions also need to follow StarPilot's
lockfile for native development; the old Sunnypilot environment is not proof of a
working native build.
