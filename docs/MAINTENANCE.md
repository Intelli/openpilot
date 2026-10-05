# EV9 Sunnypilot maintenance

This guide describes Intelli/openpilot on `ev9-dev`. See [repository rules](../AGENTS.md),
[the patch workflow](../patches/README.md), and [EV9 behavior](EV9_BEHAVIOR.md).

## Source and provenance

Application upstream is `sunnypilot/sunnypilot`, branch `hkg-angle-steering-2025`.
Vehicle upstream is `sunnypilot/opendbc`, branch `hkg-angle-steering-2025`.
The current official application baseline is `d021f6ca41375e58be8125801547e84939e0c503`,
with embedded opendbc `28303fcd1cc457f67d405407858223e0b338df20`, recorded in
[sunnypilot-upstream.json](../sunnypilot-upstream.json) and
[opendbc-upstream.json](../opendbc-upstream.json). Application code now lives under
`openpilot/{selfdrive,common,cereal,system,sunnypilot}/`. Dependencies remain vendored
at their exact application pins.

The October 4 upgrade advances 798 upstream commits from official application
`54fb2750bab4`. Before that upgrade, restoration used pre-StarPilot Intelli
`5928a37ad187` and customized vehicle snapshot `5a3f3761f586`; its official vehicle
baseline was `7c35b7546940`. Archive tip `5655634b87` added workflow archival only.
These identify historical restoration, not the current imported baseline. Enabled
patches now port the customization intent onto the newer upstream source.

Edit vehicle code in `opendbc_repo/opendbc/`; `opendbc` is a symlink there.
The standalone Intelli/opendbc checkout is historical reference only. Sync and
builds use this repository, with no submodules or external dependency checkout.
Git LFS payloads are hydrated as ordinary Git blobs; imported LFS filter attributes
and submodule metadata are removed. Asset imports verify payload size and SHA-256. The roughly 730 MiB large driving
ONNX is stored losslessly as 45 MiB chunks and an upstream-compatible manifest,
avoiding GitHub's 100 MiB blob limit; this storage transformation does not select
the optional large-model backend.

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

Reimporting the same verified snapshot retains exact provenance JSON, including
restoration history, and the existing root ignore/ordinary-blob attribute rules.
Repository, commit, tree and every dependency pin must match; an explicit ref
spelling alone does not change provenance. New snapshots regenerate metadata and
import upstream ignore/attribute rules with the local vendoring adaptations.
Active LFS attributes are never retained. The Intelli Docker image/registry helper
`release/ci/docker_build_sp.sh` is preserved as maintenance tooling.

The obsolete standalone opendbc deployment workflow is archived under
`patches/archive/sunnypilot-consolidated-20261004/legacy-opendbc-ev9-sync.yaml`.
It does not participate in the embedded dependency or current GitHub deployment.

After importing, run `./apply_patch.sh`, review the source, stage it deliberately,
and run focused checks. Replay never commits or pushes. A new upstream source
may require refreshing patches; applicability is not guaranteed by the old
baseline's successful replay.

For a same-baseline round trip, import the recorded commit, replay the enabled
patches, and stage the source. The resulting Git tree must equal the starting
tree. Normal replay leaves the index unchanged until that final staging step.

## Patch ownership

Only `.patch` files directly in `patches/` and `patches/opendbc/` are enabled.
Application patches replay alphabetically first, then vehicle patches.

| Patch series | Scope |
| --- | --- |
| Application `01_`–`12_` | Separate defaults, driving helpers, lane centering, UI, alerts, warnings, statistics, branding, monitoring, power and asset features |
| `boot_logo_ev9_edition.patch` | Retained EV9 Edition boot artwork and Sunnypilot installation hook |
| `sunnypilot_device_build.patch` | Current native build portability and fused-model compilation |
| Vehicle `opendbc/02_`–`06_` | Separate safety, steering, door, warning and regression-test features |

There are 14 application and five vehicle patches, 19 enabled in total. Vehicle
baseline physics formerly in `01_modify_baseline.patch` is now upstream; its old
implementation is archived rather than replayed. Driver-monitoring patch `10_`
only changes the phone threshold; upstream already supplies the eye/blink thresholds.

Create exports staged source as a forward diff. Update reconstructs the existing
patch's original blob versions, preserving committed hunks. For shared files,
it reconstructs the enabled series and isolates the requested feature's amendments
from the final index. Changes to other features or ambiguous transfers fail safely.
Exact preimages are retained in `patches/baselines/`; stage newly generated
baseline files with an updated patch. Both helpers exclude maintenance files and archives. See the
[patch guide](../patches/README.md) for scope and baseline controls.

The former two consolidated restoration patches remain unchanged under
`patches/archive/sunnypilot-consolidated-20261004/`. Splitting them changed patch
organization only at restoration time. Superseded patches and build-compatibility
helpers from the later upgrade are documented in
[the upgrade archive](../patches/archive/sunnypilot-upgrade-20261004/README.md).

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
source SHA. The maintained container/sysroot tooling compiles the current
Sunnypilot application and vendored dependencies for AGNOS 19.7 / `comma_arm64`.
The fused compiler uses verified pinned QCOM captures for the official default
small model and driver monitoring; it does not overlay upstream native binaries.
See [the device-build guide](how-to/laptop-device-build.md) for exact model provenance
and verification limits. The new full native build still requires GitHub validation
and device inference remains to be checked. The build publishes
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
