# Sunnypilot device build

The GitHub workflow runs an ARM64 Ubuntu 24.04 container, resolves the restored
Sunnypilot `uv.lock` with Python 3.12, extracts the AGNOS image selected by
`system/hardware/tici/agnos.json`, and rebuilds native application targets and
signed panda firmware. `SP_FORCE_ARCH=larch64` and `SP_TICI_SYSROOT` select the
device architecture and sysroot explicitly. `--minimal` excludes optional tests
and desktop tools; it still builds the device runtime.

`model_assets.json` pins ONNX inputs, tinygrad runtime sources and model data
hashes. The preserved bundle contains QCOM captures only, stored under
`model_assets/` so upstream sync does not delete them. Before SCons runs,
`verify_model_assets.py --require-qcom --install` verifies and copies the
allowlisted data into the application model directories. It never copies native
libraries or executables. Altered source/compiler inputs, CPU captures, missing
chunks and changed asset bytes stop the build.

Driving captures and metadata come from the official PMV2 catalog entry for
`62bf6fb072880905a4c490f0f4f4a6b3c23346ec`, compiled with the preserved tinygrad
pin `3501a714785ff370cffb966a45d5f9cdf6c9ea7a`. Their ONNX hashes match the
restored source. Driver-monitoring captures and eight warps come from official
Sunnypilot prebuilt commit `d69599e89a5cd28ad773415d4c89952735bbb52d`, whose
tinygrad runtime matches that pin. Each original URL/hash is recorded in the
manifest. Metadata semantics, frame geometry and warp math match the preserved
source. Road warp captures return updated buffers explicitly; a caller adapter
accepts both this interface and the original in-place interface.

`verify_build.py` checks required ARM64 ELF outputs, signed firmware, installed
model data and unresolved LFS pointers before creating `prebuilt`, and again on
the packaged deployment. The preserved model storage is excluded from the
deployment because the installed application copies already contain the same
verified data. Publication and exact-tree promotion remain separate existing
scripts.

Local syntax/unit/model-data checks do not establish successful AGNOS native
compilation or device inference timing. The GitHub device build remains the
deployment gate; device behavior and performance still need verification after
that build.
