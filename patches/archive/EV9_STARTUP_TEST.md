# Temporary EV9 startup tests

All temporary startup-test source changes were restored to the original
pre-probe versions on 2026-09-17 UTC at the user's request. This includes V1,
V2, V3 and the diagnostic badge. The sections below preserve the experiment
history and recovery instructions; no startup experiment remains armed.

## Final outcome and full rollback

The single parked READY-first attempt entered the extended diagnostic session
successfully (`50 03`) but received `7F 28 22` for communication control
`28 01 01`: NRC `0x22`, conditions not correct. No successful takeover was
recorded (`completed_at=0`), and the probe did not proceed to replacement output.
This establishes rejection of this specific attempt, not that every possible
READY-start approach is impossible. The experiment was ended without retries.

The cumulative V3 restore script ran with `--target original` while offroad and
controls were stopped. Five original source files were restored with exact
original SHA-256 hashes and permissions; five added helper files were removed.
The five helpers' bytecode caches and shared-memory badge status were archived
and removed. The entire one-use arm/claim/result directory was archived, leaving
no active trial state. The full comma reboot unloads inherited test modules.

Persistent backups remain intact under the V1, V2 and V3 backup directories.
Rejection records and removed runtime artifacts are saved under
`/data/ev9-ready-tests/20260917T050029.579054Z/runtime-20260917T050811.517225Z/`.
The V3 backup also contains `restoration.json`. Private Mac copies are under
`/tmp/ev9-ready-probe.yfWcGX/revert/`. User preferences, compiled binaries,
Panda firmware and the prebuilt marker were not changed by this rollback.

Post-reboot verification passed: a new boot, all five original hashes and modes,
all five helpers and their bytecode absent, no armed state or shared-memory test
status, original card/interface imports, UI/pandad running and card/selfdrived
stopped. The device is back to its pre-test installation.


## V3 parked READY-response test (historical; fully reverted)

The next experiment directly tests an ordinary brake + Start READY startup. It
uses a separate, single-use parked diagnostic path; the existing Hyundai READY
fallback and V2 staged-start path remain unchanged when V3 is unarmed.

V3 requires the existing Alpha opt-in, this exact installed revision and safety
configuration, fresh READY/Park/brake/zero-pedal/zero-wheel-speed signals, inactive
factory cruise and the expected diagnostic Panda mode. Conditions must hold for
one second before the attempt. Independent checksum/counter-validated CAN
monitoring continues during diagnostic IO, including intermediate unsafe samples.

The one attempt sends diagnostic session `10 03`, waits a guarded 50 ms, then
communication control `28 01 01` to ECU `0x730` on ECAN 1. Each stage has a bounded
500 ms response deadline; NRC `78` does not extend it. Raw replies and explicit
negative response codes are saved. A durable exclusive claim precedes every
possible first write, preventing repeats after a process restart. Unexpected or
missing replies produce an unknown outcome; there is no blind retry or ECU reset.

Only a matching `68 01` acknowledgement, observed factory SCC silence and a fresh
matching Panda configuration permit inactive replacement messages. V3 sends only
neutral CarControl for its entire armed session, even after general initialization.
It stops on loss of its parked conditions, factory SCC recurrence, Panda faults
or missed output deadlines. It never hands this armed session to normal driving
control. A claimed, expired, invalid or restarted trial remains locked until
explicitly disarmed/restored while offroad.

Runtime state is kept in `/data/ev9-ready-probe-v3/` with arm, claim and result
records. The arm is restricted to one boot and expires two hours after creation.
The existing shared-memory badge status path carries version 3 and
`mode=ready_parked`; logs use `ev9.ready_probe.v3`. The badge says **Hold brake in
Park**, **READY test: checking**, **READY test: accepted**, **READY test: rejected**,
**READY test: unknown**, or **READY test stopped**. Accepted reports acknowledgement
and neutral replacement startup; it is not a driving-validation result.

V3 cumulative backup: `/data/ev9-ready-tests/20260917T050029.579054Z/`.
It preserves four complete versions: original before any probe, V1 probe-only,
V2 immediately before this change (read from the actual device), and V3. Every
file has a SHA-256/mode entry; new files are explicitly absent from older versions.
The earlier V1 and V2 backup directories remain intact.

**Use this V3 restore script while V3 is installed**, rather than the older
V1/V2 scripts. While fully offroad, choose one target:

```sh
# Return to the previous staged IGN-ON V2 test and badge.
python3 -B /data/ev9-ready-tests/20260917T050029.579054Z/restore.py --target v2

# Keep only the initial timing probe.
python3 -B /data/ev9-ready-tests/20260917T050029.579054Z/restore.py --target probe

# Remove all experiments, including the initial timing probe.
python3 -B /data/ev9-ready-tests/20260917T050029.579054Z/restore.py --target original
```

Then perform a full comma reboot while offroad. Restore first archives the
single-use state directory under the backup, preserving results and disarming
the attempt. It refuses unknown source versions, modes, builds, pending updates
and running controls; partial claim/result records can be preserved for crash
recovery when a valid arm identifies the experiment. Neither restore nor an
ignition restart re-arms V3.

Private preparation and the second backup copy are in
`/tmp/ev9-ready-probe.yfWcGX/` on the Mac; the device backup is persistent.

Additional files: `selfdrive/car/ev9_ready_probe.py` and
`selfdrive/car/ev9_ready_guard.py`. V3 also changes `selfdrive/car/card.py` and the
two badge helper/widget files. The original probe, other V2 files, compiled
binaries, prebuilt marker and firmware remain unchanged.

Parked trial: from fully OFF, hold the brake and press Start once to READY. Keep
Park selected and the brake held for 30 seconds, then turn fully OFF. Do not
engage cruise or drive during this experiment. Review the logs and restore/disarm
before returning to driving. The attempt cannot automatically repeat.

Offline verification includes diagnostic response/claim tests, real CAN parser
checks, V3 session-priority and neutral-output tests, V2 regression tests, UI
classification tests and backup/restore recovery tests. Recorded CAN replay
confirmed the guard detects READY/Park/brake and latches brake release. Actual
device Python/native import preflight passed without opening live CAN sockets.
Installation passed 111 focused tests plus actual device import checks. A full
offroad reboot completed, followed by verification of the new boot, all ten
installed file hashes, updated imports, running UI/pandad and stopped
card/selfdrived. The test was then armed once for two hours. No test diagnostic
requests were sent during installation; the next parked startup supplies the
physical ECU result. The full reboot is essential because the manager caches
vehicle modules before forking card.

## V2 purpose and behavior

Attempt ECU initialization immediately after fresh EV9 CAN proves Park,
standstill and non-READY, without waiting for driver-monitoring startup. The
existing READY guard remains. This may shorten the staged IGN-ON wait; it does
not make takeover available after an ordinary READY startup.

The early attempt requires the existing Alpha longitudinal opt-in, checks READY
again before diagnostic writes, and requires the matching `68 01` response.
It runs once per card process. After successful takeover, inactive replacement
messages start only after fresh Panda configuration matches both CP and FPCP.
Normal engagement still waits for the existing readiness checks. Missing fresh
control messages use neutral output during startup.

A missed one-second safety/output deadline stops the test for that process.
An early diagnostic failure also stops the test, without publishing
`ControlsReady`. A stopped test requires turning the vehicle fully off before
retrying. It does not automatically retry or resume on a late safety response.

The temporary badge appears beneath the steering-wheel control in the BIG UI:

- **Initializing:** acquiring the ECU or waiting for safety configuration.
- **OP long acquired:** takeover and inactive output started while other startup
  checks/control telemetry are still pending.
- **OP long ready / active:** general initialization completed; fresh runtime
  control telemetry distinguishes available from actively controlling.
- **Stock ACC:** runtime configuration retained factory longitudinal control.
- **Startup test stopped:** terminal test failure; fully turn off before retrying.
- **Long status unknown:** required current-session evidence is missing or stale.

The badge uses fresh test status and runtime Panda/control data. The Alpha
setting and cached persistent car parameters do not establish takeover status.
It follows the existing HUD visibility and can be obscured by full-screen alerts.

## File inventory

| Device path relative to `/data/openpilot` | Change |
| --- | --- |
| `selfdrive/car/card.py` | Prior V1 timing probe plus early-init lifecycle and inactive startup output |
| `selfdrive/car/ev9_startup_test.py` | New eligibility, freshness, timeout and diagnostic-status helper |
| `selfdrive/selfdrived/selfdrived.py` | Prior V1 readiness timing probe, unchanged in V2 |
| `opendbc_repo/opendbc/car/hyundai/interface.py` | EV9 matching response requirement and single early attempt |
| `opendbc_repo/opendbc/car/disable_ecu.py` | Validate echoed subfunction when a response is required |
| `selfdrive/ui/onroad/starpilot/starpilot_onroad_view.py` | Register the status badge |
| `selfdrive/ui/onroad/starpilot/ev9_long_status.py` | New runtime status classifier |
| `selfdrive/ui/onroad/starpilot/widgets/ev9_long_status.py` | New badge widget |

Runtime status is written atomically at most twice per second to
`/dev/shm/ev9-startup-test-v2.json`. Diagnostic events use
`ev9.startup_test.v2` and the retained `ev9.startup_probe.v1` markers.

The prebuilt marker, native binaries, Panda firmware and user settings were not
changed. The initial deployment restarted only the offroad UI. That was insufficient:
the manager had already imported vehicle interfaces, and its Python children
inherited the old interface. Vehicle-module edits require a full device reboot
(or an equivalent complete manager reload) before testing.

## Backups and rollback

Installed deployment: `8f52e4ae5d09ddaa028f09e741976c09079dcab3`.
Source revision: `9cb4642dc1534c73959203b9e186ab6f0809e410`.

Cumulative device backup:
`/data/ev9-startup-tests/20260917T031621.588518Z/`.
It contains `original/`, `probe/`, `test/`, a manifest with SHA-256 hashes and
permissions for every version, `changes.diff`, and `restore.py`.
New files are explicitly recorded as absent from earlier versions.

The original V1 backup remains untouched:
`/data/ev9-startup-probe-backups/20260917T024442Z/`.

A second copy of the cumulative device backup and all preparation/test artifacts
is on the Mac in `/tmp/ev9-early-takeover.po4Xq7/`. The device backup is the
persistent recovery copy; the Mac's `/tmp` directory may eventually be cleaned.

With the vehicle fully off and card/selfdrived stopped, run on the device:

```sh
# Restore the original installation, including removal of the V1 timing probe.
python3 -B /data/ev9-startup-tests/20260917T031621.588518Z/restore.py --target original

# Alternatively, undo V2 and its badge, retaining only the V1 timing probe.
python3 -B /data/ev9-startup-tests/20260917T031621.588518Z/restore.py --target probe
```

Then reboot the comma while offroad to reload the restored vehicle modules and
unload the badge. Restarting the UI alone is insufficient for vehicle-module
changes because the manager forks Python processes with inherited imports.
The restore script checks the build, prebuilt marker, offroad state, stopped
control processes and every current file before writing. It refuses unrelated
edits or a newer installed build. It deletes new helper files only when their
contents match a known test version. Writes are individually atomic, with
rollback on Python exceptions; the backup also supports recovery from known
mixed versions after interrupted installation.

Use the cumulative restore script above, rather than the old V1 restore script,
while V2 is installed. Backups are retained after restoration.

## Verification and next test

- 10 eligibility/lifecycle integration tests, including stale data, neutral
  startup, once-only initialization, fallback and sticky timeout handling.
- 4 diagnostic-response tests and 15 UI-state tests.
- 4 backup/restore tests, covering both targets, new-file deletion, repeated
  restore, unknown-file protection and transaction rollback.
- Actual controller and compiled Panda safety hooks: 110 updates, 610 output
  messages accepted, zero blocked, controls disallowed throughout. Decoding
  confirmed inactive steering, zero acceleration and no cruise-button requests.
- Existing full startup logs replayed through real vehicle parsers: staged
  IGN-ON qualified about 65 ms after identification; normal READY never qualified.
- Device-runtime import preflight, native CAN conversion compatibility, installed
  checksum verification and successful offroad UI restart.

The offline checks above alone do not establish physical startup success. The
post-reboot trial below supplies parked evidence. The staged test sequence is: two Start presses without the brake, wait for **OP long
acquired** or **OP long ready**, then brake + Start to READY. Remain in Park for
20–30 seconds, then fully turn off. If the test stops, fully turn off without
proceeding. Review the full logs before attempting a drive with this prototype.

## First parked trials and runtime-loading correction

The first four V2 parked trials received successful ECU acknowledgements through
the normal initialization path. Two included READY and maintained takeover for
about 11 and 43 seconds until shutdown. The other two remained in IGN-ON.

However, the early path repeatedly crashed with an unexpected `early_takeover`
keyword because the already-running manager retained the old vehicle-interface
class. The status file then aged out between restarts, explaining the alternating
unknown/initializing display. File hashes and a fresh-interpreter import check
did not detect this inherited-module problem. These trials therefore do not
validate the intended timing improvement.

A full offroad device reboot completed on 2026-09-17 UTC. Verification confirmed
a new boot, the new interface signature through `car_helpers.interfaces`, all
eight test hashes unchanged, UI/pandad running and card/selfdrived stopped.
No control files were changed for this correction; both rollback targets remain
valid. The post-reboot parked trial below subsequently verified a single early
initialization and a stable card process.

## Successful post-reboot parked trial

The next recorded trial confirmed `early=true`, one attempt with the matching
`68 01` acknowledgement, one stable card process and no recorded crashes.
Takeover and inactive replacement traffic began about 6.2 seconds after recording
started, approximately four seconds before general readiness completed. Vehicle
identification itself took longer on this first post-reboot startup, so recording
start is not a precise substitute for the physical Start-button press.

Panda used the expected safety configuration. Before general readiness, decoded
replacement messages remained inactive with zero requested acceleration/torque.
Factory SCC ceased; accepted TX returns confirmed replacement transmission.
There were no Panda faults or safety-rejected frames before shutdown. Rejected
returns appeared only after ignition went off.

The vehicle subsequently entered READY and maintained takeover for about
38 seconds until shutdown, while stationary in Park and with controls inactive.
This validates parked early acquisition and persistence. It does not validate
engaged driving, ordinary READY-first takeover, or a READY transition while
general initialization is still pending. No further device edits were needed.
