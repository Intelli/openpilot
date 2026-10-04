# Sunnypilot AGNOS 19.7 device build

This branch compiles the current Sunnypilot application and panda firmware from
source in a native ARM64 Ubuntu 24.04 / Python 3.12 container. The GitHub workflow
uses `ubuntu-24.04-arm`, checks out its triggering SHA, and builds against the
AGNOS 19.7 image selected by `openpilot/common/hardware/comma/agnos.json`.

## Full build

Docker or Podman and network access are required for the container, frozen
Python dependencies and AGNOS image. From the repository root:

```bash
scripts/laptop_device_build.sh build-image
scripts/laptop_device_build.sh setup-sysroot-agnos
./build
```

`./build 4` selects four jobs. Optional `setup-sysroot <host>` copies libraries
from a device running the matching AGNOS image. Image caches are keyed by URL;
loader repair keeps absolute device links inside the extracted sysroot.

The builder installs `uv.lock` with `uv sync --frozen --all-extras` and Python
3.12. It sets `SP_FORCE_COMMA=1`, `SP_TICI_SYSROOT=/opt/tici-sysroot`, and
`SP_USE_PINNED_MODELS=1`. The source build selects `comma_arm64` and the device
ION vision-buffer implementation even though the runner lacks device nodes.
It clears native outputs and SCons signatures, disables the SCons cache by
default, and uses `--minimal` to exclude optional desktop tools and tests.
All native application targets and signed panda H7, jungle and body firmware
are rebuilt. FFmpeg shared libraries from the frozen dependency wheel are
copied beside loggerd and loaded through `$ORIGIN/lib`; the build venv is not
part of deployment. Locationd uses a relative path to its generated filter.

`prebuilt` is created only after required native outputs pass ARM64 ELF checks,
firmware exists, model validation passes and no unresolved LFS pointers remain.
The same checks run on the packaged GitHub output. Publication and promotion
retain their existing workflow name and exact-built-tree mechanics.

## Pinned QCOM model data

The runner has no Qualcomm accelerator. Tinygrad's QCOM backend opens
`/dev/kgsl-3d0`, so it cannot capture these kernels on an ordinary ARM runner.
Only model data is supplied externally; no application executable or library
comes from a prebuilt Sunnypilot tree.

The 11 files in `tools/laptop_device_build/model_assets/` provide the fused
CD210 driving capture, driver-monitoring capture and metadata, two DM warps,
chunk manifests and input-device settings. Official model captures come from
Sunnypilot's Hugging Face dataset `sunnypilot/sunnypilot_models_v1`, pinned to
revision `25b84092909b782d51a0536bc58d3a55b3760b2d` and donor source
`a5f44653d7f43ad57fef2f546f3916ec4cbf3c56`. Both ONNX hashes and the tinygrad
commit match this imported source. Compiler helpers, camera geometry, model
constants, serialization helpers and NV12 inputs were compared byte for byte
with that donor. DM metadata was generated from the exact source ONNX/parser;
CPU selection during metadata parsing does not create a CPU inference capture.

`model_assets.json` records input hashes, capture formats, catalog hashes,
immutable download URLs and per-file hashes. Validation reads pickle opcodes
without loading captures, checks the fused capture's out-of-band buffer
framing, and requires the QCOM backend. Changed source/compiler/model bytes,
missing files or relabelled CPU captures stop the build.

```bash
python3 tools/laptop_device_build/verify_model_assets.py --require-qcom
python3 tools/laptop_device_build/verify_model_assets.py --require-qcom --install
```

The full builder verifies and installs these files automatically. The maintained
bundle survives sync; application copies are recreated before building. Packaging
excludes the maintained bundle to avoid duplicating installed model data.
Optional Chestnut hardware and its large model are not captured by this device
bundle. Replacing models requires a matching verified QCOM bundle and manifest.

## Focused targets

```bash
./build --params
./build --panda
./build --cereal
scripts/laptop_device_build.sh doctor
scripts/laptop_device_build.sh shell
```

Shortcuts build only selected targets and do not replace the full GitHub gate.
The `manager` command requires native ARM64 Python; laptop compilation does not
establish that accelerator-dependent inference can run on the laptop.

## Verification limits

The prior AGNOS 17.2 revision passed a real GitHub build and exact-tree promotion.
This AGNOS 19.7 port has passed model hash/backend/framing checks, focused build
validator tests and shell/source syntax checks. Docker/Podman is unavailable on
this host, so the new full native build remains to be verified in GitHub.
Linking, packaged library resolution and on-device inference/timing still need
that build and device verification.
