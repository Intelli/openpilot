# Sunnypilot device builder

The maintained ARM64 container/sysroot builder targets AGNOS 19.7 and the
`comma_arm64` application under `openpilot/`. See
[the device build guide](../../docs/how-to/laptop-device-build.md) for setup,
full native compilation, pinned QCOM model provenance and verification limits.

`verify_model_assets.py` inspects model hashes and pickle/OOB framing without
loading captures. `verify_build.py` checks required ARM64 application outputs,
packaged FFmpeg libraries, firmware and installed model data before publication.
No external native application artifacts participate in the build.
