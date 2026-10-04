# Sunnypilot AGNOS 17.2 device build

This branch builds the restored Sunnypilot application for the comma device
(`larch64`) in an ARM64 Ubuntu 24.04 container, using Python 3.12 and an AGNOS
17.2 sysroot. The GitHub workflow uses `ubuntu-24.04-arm` and checks out the
triggering source SHA. It compiles native application targets and panda firmware
from that source; it does not overlay upstream native binaries.

## Prerequisites

- Docker or Podman with a native ARM64 container runtime, or ARM64 emulation.
- Internet access for the frozen Python dependencies, container and AGNOS image.
- `uv` for the optional host environment setup.
- `rsync` and SSH only when copying a sysroot from a device already running the
  matching AGNOS 17.2 image.

The source manifest at `system/hardware/tici/agnos.json` selects the sysroot
image. Do not substitute a newer StarPilot device sysroot. Image download caches
are keyed by URL so a prior AGNOS 19.6 cache cannot supply the older image.

## Setup and full device build

From the repository root:

```bash
scripts/laptop_device_build.sh build-image
scripts/laptop_device_build.sh setup-sysroot-agnos
./build
```

`./build 4` selects four parallel jobs. The equivalent full-build command is
`scripts/laptop_device_build.sh build 4`.

The builder resolves `uv.lock` with `uv sync --frozen --all-extras` and the
container's Python 3.12 interpreter. It sets `SP_FORCE_ARCH=larch64`,
`SP_FORCE_TICI=1`, `SP_TICI_SYSROOT=/opt/tici-sysroot` and
`SP_USE_PINNED_MODELS=1`. It removes native application outputs and the SCons
signature database before compiling, disables the SCons cache by default and
uses `--minimal` to exclude optional tests and desktop tools. All device runtime
native targets and signed panda H7, jungle and body firmware remain included.

`prebuilt` is created only after required native outputs have been verified as
ARM64 ELF files, firmware is present, model data passes validation and LFS
pointers are absent. The same checks run on the packaged GitHub deployment.
Publication creates `ev9-prebuilt`; the existing promotion script copies its
exact tree to `ev9` with source/build provenance and deployment history.

## Pinned QCOM model data

ARM64 CI has no Qualcomm accelerator for capturing device model kernels. The
19 pinned files under `tools/laptop_device_build/model_assets/` supply the
required QCOM driving, driver-monitoring and warp captures. They are model data
only, with no external native executable/library overlay. `model_assets.json`
records their source URLs, hashes, ONNX inputs and tinygrad runtime identity.

```bash
python3 tools/laptop_device_build/verify_model_assets.py --require-qcom
python3 tools/laptop_device_build/verify_model_assets.py --require-qcom --install
```

The full builder verifies and installs these files automatically. Missing or
changed files, changed ONNX/compiler inputs, or CPU captures stop the build.
The maintained bundle survives upstream sync, while the application copies are
recreated before compilation. The maintained storage is excluded from deployment
to avoid duplicating the installed data.

The driving pair comes from the official PMV2 catalog entry whose ONNX hashes
match this source. Driver monitoring and eight warps come from pinned official
Sunnypilot prebuilt commit `d69599e89a5cd28ad773415d4c89952735bbb52d` with matching
tinygrad runtime sources. Metadata semantics, warp math and frame geometry were
checked against the restored source. A caller adapter accepts both the original
in-place warp interface and the donor's explicit updated-buffer returns.

## Focused targets and inspection

```bash
./build --params
./build --panda
./build --cereal
scripts/laptop_device_build.sh doctor
scripts/laptop_device_build.sh shell
```

These shortcuts compile only their requested native targets. They do not replace
the full GitHub device build as a deployment gate. Plain host `scons` is not
automatically routed into this container. Use `./build` for the device target.

The preserved `manager` command requires an ARM64 Python runtime. The selected
QCOM model captures require the device accelerator for inference; building on
a laptop does not establish that the on-device processes can run there.

## Verification limits

Model hash/backend/compiler checks, caller adapter tests, build validation tests
and script syntax checks passed locally. The full native AGNOS build has not
been run locally because Docker/Podman is unavailable in this checkout's host
environment. Successful GitHub compilation and subsequent on-device inference,
timing and behavior remain to be verified.
