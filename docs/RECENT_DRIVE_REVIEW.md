# Reviewing recent device drives

Use this workflow when a user reports behavior from a recent test drive. Start
with the authenticated device's recent routes instead of requiring the user to
find a route ID. Confirm that the drive matches the report before drawing
conclusions. This is an investigation workflow, not a recurring monitor.

The experimental EV9 custom planner has been retired. For recordings made before
its removal, consult the [archived planner notes](../patches/archive/EV9_CUSTOM_PLANNER.md).
Always verify the recorded build before attributing behavior to a feature.

## Find the drive and available logs

1. Use the user's comma connect route link when supplied. Links look like
   `https://connect.comma.ai/<dongle-id>/<route-name>/<segment>`; the final segment
   number is not part of the route name. Do not infer chronological order from a
   route's boot counter or random suffix.
2. Open [comma useradmin](https://useradmin.comma.ai/) in the authenticated
   browser. A route lookup uses
   `https://useradmin.comma.ai/?onebox=<dongle-id>%7C<route-name>`.
   Connect and useradmin can require separate sign-ins. If authentication is
   missing, let the user sign in; do not read browser credential storage.
3. Follow the device link from the route to its recent-route listing. Without
   a supplied route, use the known device from the conversation or authenticated
   account, confirming the device if there are multiple candidates.
4. Inspect recent routes by **recorded start/end time**, distance and segment
   count. Upload time can be much later than driving time. Check adjacent routes
   when reinstall/calibration or an off/on cycle may have split a test. A newest
   zero-distance route may just be a parked session.
5. Record the selected route, UTC times and explicitly converted local times in
   a private investigation note. Read its build/vehicle metadata. Clarify with
   the user if the selected drive is ambiguous, continuing independent source
   review in the meantime.
6. Inspect every segment's available `qlog.zst`/`rlog.zst` links. Full rlogs may
   be absent even when the route and qlogs are visible. Download through the
   page's actual links, keeping segment numbers intact. Do not assume an array
   index equals the segment number when files are missing. Prefer rlogs for CAN
   and timing analysis; qlogs are immediately useful for state and alert triage.

### Browser automation and private files

Use the browser tool's documented API and observed page state. In Codex, initialize
computer use and read its documentation first; reacquire tabs after a reset rather
than reusing old IDs. Select links by their observed role/name. A read-only DOM
query can extract displayed download anchors named `qlog.zst` or `rlog.zst`.
Do not invent API endpoints, inspect hidden application state or extract tokens.
If browser file export is unavailable, an HTTP client can download through the
observed signed links. Refresh expired links from the page.

Keep private routes private; do not use useradmin's public-sharing controls.
Signed URLs, raw logs, device identifiers, VINs, GPS data and credentials belong
outside the repository. Use a task-specific temporary directory, such as one
created by `mktemp -d /tmp/ev9-drive-review.XXXXXX`. Never commit private evidence
or make a future investigation depend on a previous session's temporary files.

## Verify the software and settings that actually ran

- Read `initData` (`gitCommit`, `gitSrcCommit`, `gitBranch`, `dirty`, `wallTimeNanos`) and
  `carParams`. Do not assume the latest local commit ran on the device.
- Resolve the recorded deployment commit and inspect its `Source-Commit` and
  `Build-Commit` trailers. Our `ev9` deployment and `ev9-prebuilt` build should
  have identical trees; the source tree differs because the build adds compiled
  artifacts. Review the source identified by that provenance.
- If objects are missing locally, fetch the relevant repository refs read-only.
  Do not run the publication/sync CI scripts as diagnostic commands.
- Read effective route settings from nonempty
  `starpilotPlan.starpilotToggles` JSON. Empty strings mean no new settings
  snapshot, not that options were reset. Cached preferences and compiled defaults
  do not establish the effective onroad values.
- Use runtime `pandaStates` for the active safety model, parameter and alternative
  experience. Startup `carParams` or an initial ELM327 Panda state can differ
  from the final configured safety state.

## Decode locally without device-native binaries

Use this checkout's Python 3.11/3.12 environment. `cereal.log` and `zstandard`
can decode logs without importing AGNOS `msgq`, Params or CAN extensions. For
example, run from the repository root with `EV9_LOG_DIR` pointing to the private
download directory:

```python
import os
from collections import Counter
from pathlib import Path

import zstandard
from cereal import log

counts = Counter()
for path in sorted(Path(os.environ["EV9_LOG_DIR"]).glob("*-qlog.zst")):
  with path.open("rb") as compressed:
    with zstandard.ZstdDecompressor().stream_reader(compressed) as stream:
      data = stream.read()
  for event in log.Event.read_multiple_bytes(data):
    counts[event.which()] += 1
print(counts)
```

Replace the glob for rlogs as needed. Streaming decompression handles Zstandard
frames without a declared decompressed size. Process large routes one segment at
a time, selecting only relevant fields for a timeline. Sort selected records by
`logMonoTime` across segments rather than assuming filenames sort numerically.
Align different services by time, not equal list positions. For causal replay,
use the most recent preceding sample, not a future interpolated sample.

Pair the first segment's `initData.wallTimeNanos` with that event's `logMonoTime`
when converting monotonic offsets to UTC. Keep sampling precision explicit and
do not reset the relative clock at each segment boundary. Validate startup wall
time against the route's recorded time: the device clock can be incorrect before
time synchronization. If they disagree, retain monotonic offsets for causal
analysis and identify the UTC anchor as uncertain rather than assigning events
to an incorrect date.

## Build an evidence timeline

For EV9 steering/engagement reports, inspect these together:

| Service | Relevant fields |
| --- | --- |
| `carState` | Button edges, speed, gear, brake/regen, driver torque and `steeringPressed`, capacitive `handsOnWheel` with sample timestamp when available, measured angle, cruise state and fault flags |
| `liveCalibration` | `calStatus` as well as percentage; 100% alone does not establish valid calibration |
| `starpilotCarState` | AOL allowed/enabled, pause state and button state |
| `carControl` | `enabled`, `latActive`, `longActive` and requested actuators |
| `carOutput` | Controller actuator output, including the limited angle |
| `controlsState` | Angle controller active/saturated/requested/measured values and curvature |
| `selfdriveState`, `starpilotSelfdriveState` | Normal engagement and final alert type, text, size and sound |
| `onroadEvents`, `starpilotOnroadEvents` | Events before alert selection; the latter wraps its list in an `events` field |
| `pandaStates` | Runtime safety configuration, controls permission, TX/RX rejection counters and faults |
| `can`, `sendcan` | Received/requested frames, bus, address, status, counter, checksum and gain |

Some qlogs omit `modelV2` but include `drivingModelData`. In this baseline both
receive the same model `action` in `selfdrive/modeld/fill_model_msg.py`, so
`drivingModelData.action.desiredCurvature` can substitute for that model input.
Recheck this assignment after upstream changes. It is not controlsd's subsequently
modified/clamped desired curvature.

Distinguish requested state, transmitted command, permitted/forwarded CAN traffic,
and observed vehicle response. `carControl.enabled == false` does not mean AOL
steering is off. A muted output and an alert that was never generated require
different fixes. Kia's dashboard message is not automatically mirrored on C3X;
only specific parsed fault signals produce StarPilot fault events.

## State the limits and reproduce the suspected defect

- Qlogs are decimated. Determine observed rates rather than assuming full control
  frequency. A missing button edge or CAN frame does not prove it never occurred.
  Sparse CAN cannot establish continuous traffic or an ECU diagnostic code.
- Ordinary Panda telemetry does not expose every internal AOL latch. Reproduce
  its actual configuration with freshly built native safety hooks to inspect
  forwarding/permission behavior. Zero rejected-TX counts do not prove the
  receiving ECU got a continuous valid message stream.
- Build native extensions for the host before importing controller/safety tests.
  Tracked AGNOS `.so` files cannot run on macOS. Use focused tests plus a regression
  combining controller output and Panda forwarding for cross-boundary defects.
  Do not overwrite shipped binaries with host binaries or depend on a prior
  session's temporary builds.
- Recorded-input replay cannot establish how the vehicle would respond to changed
  commands. Label counterfactual or decimated replay appropriately.
- Request full uploaded rlogs when unresolved questions require exact CAN timing;
  finish independent findings from available qlogs first. ECU diagnostic data
  may still be needed to establish an OEM warning's exact cause.
- Commit synthetic regression tests and reusable instructions, not route data.

## Evaluate tuning candidates offline

1. Reproduce logged commands with the recorded build/settings before comparing
   changes. Quantify baseline error against CAN quantization. Trace the full
   path: model action, controlsd modifiers, angle conversion, vehicle filtering,
   limits, transmitted angle/gain and measured response. Upstream request
   oscillation may disappear in the vehicle filter.
2. Select contiguous valid intervals using preceding samples and explicit age
   limits. Separate driver contact, engagement transitions, speed and turn angle.
   Report coverage: long straight sections can hide poor high-angle behavior.
   Preserve each candidate's own filter/limiter state; label one-step replays
   that instead restart from recorded state. Use elapsed time for integrals.
3. Change one connected parameter at a time. Compare command lag, reversals,
   assistance loss and clipping together; lower variation can simply mean less
   steering. Preserve driver-override reductions and existing safety envelopes.
4. If fitting a vehicle-response model, hold out whole maneuvers and another
   drive, select parameters only on training data, and compare against simple
   prediction baselines. Check turn-only errors and parameter consistency.
   Supplying recorded future commands still does not validate how different
   commands would change torque, vehicle motion or future model predictions.
5. State native safety-check scope precisely. Forced permission, fixed gain or
   refreshed measurement histories test only conditional command acceptance,
   not complete Panda behavior or engagement transitions. Keep exploratory
   scripts/results private; promote only useful, small regression cases.

Validate the current fix on a matching new drive before stacking speculative
tuning changes. An unestimated `liveDelay` fallback is not a measured actuator
delay, and a fitted response model needs independent validation before it can
rank physical steering improvements.

Report the build/route reviewed, confirmed facts, separately labeled causal
inferences, remaining gaps and tests performed. For fixes, follow the
[patch workflow](../patches/README.md) and
[build/deployment provenance](STARPILOT_MIGRATION.md). A passing host replay does
not replace the GitHub device build or on-vehicle validation.
