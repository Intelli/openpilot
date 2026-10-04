# Archived StarPilot implementation

These files preserve the StarPilot EV9 Edition state before restoring Sunnypilot.
The exact source commit is `09c6cf07911a0b75954222f0b903347e8baa122d`, also retained
on local branch `codex/ev9-starpilot-archive-20260920`.

`application/` and `opendbc/` contain the formerly enabled StarPilot patches.
`EV9_BEHAVIOR.md`, `CHANGELOG.md` and `starpilot-upstream.json` preserve their
source and behavior context. `embedded-opendbc-maintenance/` preserves obsolete
standalone maintenance helpers from the restored vehicle snapshot; maintained
commands now live at the main repository root.

Nothing in this directory participates in normal patch replay. The boot JPEG is
retained in the active Sunnypilot tree; its former StarPilot integration is archived.
