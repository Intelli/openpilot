# Archived StarPilot implementation

These files preserve the StarPilot EV9 Edition state before restoring Sunnypilot.
The exact source commit is `09c6cf07911a0b75954222f0b903347e8baa122d`, also retained
on local branch `codex/ev9-starpilot-archive-20260920`.

`application/` and `opendbc/` contain the formerly enabled StarPilot patches.
All **13 application and six vehicle patches** match their originals at the
source commit byte-for-byte. [manifest.json](manifest.json) records their original
paths, archived paths, Git blob IDs, SHA-256 hashes and changed source paths. It
also catalogs the 24 preserved historical/disabled originals.
The retired [EV9 custom planner](../ev9_custom_planner.patch) and its
[notes](../EV9_CUSTOM_PLANNER.md) remain in their existing archive locations and
are included in the catalog as well.

The full ordered series was replayed from stable StarPilot baseline
`c3e4ec630f41c4baa43254a90f718abd1bf764a1` in a disposable index. All 99 patched
paths exactly matched the archived source. No application or vehicle changes
were missing; the remaining differences were maintenance tooling and documents.
This is source-preservation verification, not build or device qualification.

The latest EV9 main-cruise OP-long engagement changes are included in
[`drive_helpers_starpilot.patch`](application/drive_helpers_starpilot.patch),
vehicle [safety patch 04](opendbc/04_panda_safety_limits_starpilot.patch) and
[tests patch 06](opendbc/06_ev9_tests_starpilot.patch). Turn-lead assistance,
lane-change safeguards, steering/manual-handoff changes, startup status,
defaults, warnings, alerts, settings, EV9 UI and boot artwork are retained too.

`context/` contains exact historical snapshots of the
[repository guidelines](context/REPOSITORY_GUIDELINES.md),
[maintenance guide](context/MAINTENANCE.md) and
[patch workflow](context/PATCH_WORKFLOW.md). Their paths and instructions describe
the former StarPilot layout; use the current repository guidelines for active work.

`EV9_BEHAVIOR.md`, `CHANGELOG.md` and `starpilot-upstream.json` preserve their
source and behavior context. `embedded-opendbc-maintenance/` preserves obsolete
standalone maintenance helpers from the restored vehicle snapshot; maintained
commands now live at the main repository root.

Nothing in this directory participates in normal patch replay. The boot JPEG is
retained in the active Sunnypilot tree; its former StarPilot integration is archived.
Port selected changes to Sunnypilot deliberately and create new enabled forward
patches. Do not move these historical StarPilot patches into the active directories
as a way to enable them.
