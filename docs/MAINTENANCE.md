# EV9 Sunnypilot maintenance

This guide describes Intelli/openpilot on `ev9-dev`. See [repository rules](../AGENTS.md),
[the patch workflow](../patches/README.md), and [EV9 behavior](EV9_BEHAVIOR.md).

## Source and provenance

Application upstream is `sunnypilot/sunnypilot`, branch `hkg-angle-steering-2025`.
Vehicle upstream is `sunnypilot/opendbc`, branch `hkg-angle-steering-2025`.
The restored application comes from Intelli commit `5928a37ad187`, immediately
before the StarPilot migration. The archive branch tip `5655634b87` adds workflow
archival only. The restored source and seven dependency pins were imported as
ordinary tracked files, without upgrading their versions.

[sunnypilot-upstream.json](../sunnypilot-upstream.json) records application
baseline `54fb2750bab4`, dependency baselines and restoration provenance.
[opendbc-upstream.json](../opendbc-upstream.json) records vehicle baseline
`7c35b7546940`, the exact opendbc pin in that official application baseline.
The customized vehicle snapshot was `5a3f3761f586`; it is recorded as
`restored_from`, not confused with the uncustomized patch baseline.
Enabled forward patches preserve the custom source differences.

Edit vehicle code in `opendbc_repo/opendbc/`; `opendbc` is a symlink there.
The standalone Intelli/opendbc checkout is historical reference only. Sync and
builds use this repository, with no submodules or external dependency checkout.
Git LFS payloads are hydrated as ordinary Git blobs; imported LFS filter attributes
and submodule metadata are removed. Asset imports must verify payload size and hash.

## Snapshot sync

Save application edits and refresh their patches first. Preview before importing:

```sh
./sync-upstream.sh --check
./sync-upstream.sh --allow

# Independent vehicle-only sync; unrelated application edits/staging survive.
./sync-upstream.sh --opendbc --check
./sync-upstream.sh --opendbc --allow

# Either mode also accepts an explicit branch, tag or commit.
./sync-upstream.sh --check <ref>
./sync-upstream.sh --opendbc --allow <ref>
```

Application sync fetches its selected snapshot and recursively vendors the exact
commits in its gitlinks. Vehicle-only sync fetches the selected opendbc snapshot
and replaces only `opendbc_repo/` plus `opendbc-upstream.json`. The separate
vehicle manifest records overrides of the application's original dependency pin.
A later full application sync restores that application's dependency pins.

Fetches, candidate indexes and LFS hydration use disposable temporary Git caches.
`--check` materializes the complete candidate for comparison without changing
source, the repository index, refs or local config. `--allow` stages the selected
snapshot. Without `--allow`, importing a new baseline is refused.

Sync refuses dirty source/index paths in its scope, untracked or ignored file
collisions, existing gitlinks and ongoing merge/rebase/cherry-pick operations.
Local maintenance edits are preserved. Import does not merge, create commits,
replay patches or push branches. `update.sh` forwards these same arguments.

Explicit maintenance paths in `tools/upstream/sync.py` survive imports: root
helpers, patch archives, provenance, CI/publication scripts, maintained build and
sysroot tooling, `.githooks`, and maintenance documents. Upstream `.gitignore`
is adapted with local cache exclusions. Keep application behavior in patches
rather than adding application directories to the preservation list.

After importing, run `./apply_patch.sh`, review the source, stage it deliberately,
and run focused checks. Replay never commits or pushes. A new upstream source
may require refreshing patches; applicability is not guaranteed by the old
baseline's successful replay.

## Patch ownership

Only `.patch` files directly in `patches/` and `patches/opendbc/` are enabled.
Application patches replay alphabetically first, then vehicle patches.

| Patch | Scope |
| --- | --- |
| `sunnypilot_ev9_customizations.patch` | Restored application customizations relative to official Sunnypilot |
| `boot_logo_ev9_edition.patch` | Retained EV9 Edition boot artwork and Sunnypilot installation hook |
| `sunnypilot_device_build.patch` | Restored application's device-build portability changes |
| `opendbc/01_sunnypilot_ev9_customizations.patch` | Restored EV9 vehicle customizations relative to official opendbc |

Create exports staged source as a forward diff. Update reconstructs the existing
patch's original blob versions and compares them to the index, preserving
committed hunks. Both exclude maintenance files and archives. See the
[patch guide](../patches/README.md) for scope and baseline controls.

StarPilot ports and their earlier documentation remain under
`patches/archive/starpilot-20260920/`. Original historical patch files and helper
archives remain untouched references. Nested archives and disabled suffixes are
never replayed. Legacy creators used inverse diffs and automatic sync/staging;
supported root commands use reviewed forward exports instead.

## Verification and deployment

Maintenance checks run only in disposable repositories:

```sh
python -m pytest tools/ci/tests -q -o addopts='' --confcutdir=tools/ci/tests
```

Verify enabled patches against their recorded official baselines. Build host-native
extensions before tests that import compiled modules. Host checks do not replace
the AGNOS build or on-vehicle validation.

Pushing `ev9-dev` triggers the GitHub build on `ubuntu-24.04-arm`, pinned to the
source SHA. The maintained container/sysroot tooling compiles the restored
Sunnypilot application and vendored dependencies. The build publishes
`ev9-prebuilt` as a parentless snapshot with a `Source-Commit` trailer. The
`master` workflow then copies its exact tree into a historical `ev9` commit
with `Source-Commit` and `Build-Commit` trailers. Install `Intelli/ev9`.

Keep workflow name `sunnypilot prebuilt action`, which the deployment listener
uses. Keep GitHub compilation as the deployment gate; no separate test gate is
added. Never run publication scripts as local checks. Native changes and source
must ship together with rebuilt binaries. Updates preserve existing device
preferences; defaults apply to missing settings only.

Use [the recent-drive review workflow](RECENT_DRIVE_REVIEW.md) to verify recorded
builds and effective settings when diagnosing device behavior.
