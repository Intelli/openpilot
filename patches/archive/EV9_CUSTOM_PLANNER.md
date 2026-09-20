# Archived EV9 custom planner

Retired from the live codebase on 2026-09-20 at the owner's request.
This is the single archive for the custom-planner notes and documentation.
Historical implementation instructions below describe retired experiments and
must not be treated as current deployment instructions.

## Code archive and restoration

The companion [ev9_custom_planner.patch](ev9_custom_planner.patch) is a
repository-relative forward patch from the post-removal source to the exact
pre-removal working-tree implementation. It includes the runtime, native solver
source/generator, process/control integration, telemetry, tests and offline
research tools, including uncommitted work. It is based on source
`94d8673fde277999a19b581263530d8061b45d9c` plus the local work present at retirement.
Generated build products and Python caches are excluded; rebuild the native
solver and schema bindings when intentionally restoring the implementation.
The original native contract was ABI6.

The archive is deliberately nested under `patches/archive/`. Normal
`apply_patch.sh` bulk replay only visits `patches/*.patch` and
`patches/opendbc/*.patch`, and explicit selection rejects nested archives.
The old enabled `ev9_trajectory_runtime.patch` and
`ev9_trajectory_research.patch` have been consolidated into this archive.
Enabled defaults/vehicle patches no longer restore planner instrumentation.

`sync-upstream.sh` preserves the entire `patches` directory, including both
archive files, even when upstream omits them or has files with the same names.
Maintenance regression tests cover preservation and exclusion from replay.
There is no preservation exception for any live planner application path.

For an explicitly requested future restoration, first review the archive and
run `git apply --check patches/archive/ev9_custom_planner.patch` in an isolated
checkout of the removal result. A successful check is not deployment approval.
The ordinary GitHub device build remains necessary for source/schema/native
changes; no device update or setting change was performed during retirement.
A saved `EV9TrajectoryMode` value no longer has a live consumer.

Independent EV9 model/turn-lead assistance, the turn-side road-edge guard,
lane-change rules, EV9 Limits Speed, controller/manual behavior and the existing
EV9 path visualization are retained. The road-edge helper has its own compact
geometry constants/transform and does not load a planner.

## Retirement verification

- The recovery patch applies to the removal result and restores all 71 affected
  source/test files byte-for-byte to the saved pre-removal working tree. Reverse
  application returns those files to the removal result.
- All 20 remaining enabled patches replay successfully from the recorded
  StarPilot baseline `c3e4ec630f41c4baa43254a90f718abd1bf764a1`, without restoring
  planner services, ownership, the mode setting or controller telemetry.
- The maintenance suite passed: 55 tests plus 11 subtests. This includes upstream
  deletion/name-collision preservation and exclusion of the retired patch from
  default, all, check and explicit patch-helper selection.
- The independent turn-assistance helper passed 32 tests. Schema loading,
  reserved field checks, focused Python lint and source whitespace checks passed.
- Full controls integration tests could not load the checked-in AGNOS messaging
  binary on macOS; vehicle controller tests also require the missing `smbus2`
  dependency. These checks do not replace the normal device build or an onroad
  validation. These local checks did not change the device or its settings.

## Final recorded-drive findings

The reviewed September 20 test used clean deployment `23206350b7`, source
`94d8673fde`, matching native ABI6, ACTIVE mode and EV9 Limits Speed 40 km/h.
Across all ten full rlog segments: 3,357 published decisions, 17 feasible
proposals, 14 adopted plans, and 13 ownership bursts totaling **1.398 seconds**.
The longest continuous burst was **180 ms**; only one refresh retained ownership.
Nine handbacks were lease expiries, two speed mismatches and two explicit
invalid-state/capture revocations. The prior reviewed drive had no feasible
proposals or ownership.

Successful full planning took 44.3 ms median / 49.8 ms p95 against the 50 ms
budget. Some processing paths improved, and the earlier under-budget deadline
signature disappeared, but refresh continuity remained inadequate. There were
486 native/QP failures, 293 deadline decisions, 115 dense-bound failures,
133 missing-model-pose decisions and 244 invalid-execution-state decisions.
1,773 decisions skipped references already within capability. Different route
workloads prevent treating these counts as a paired solver benchmark.

At approximately 454.817–454.961 seconds elapsed, custom takeover requested an
initial unwind: wheel-angle request fell from roughly 93 to 47 degrees while
normal model demand was increasing. Outgoing CAN target fell from 88 to 71
degrees before driver pressure was detected. The candidate's near-term curvature
dip caused the request reduction; tracking feedback added further unwind.
Elsewhere, normal model, separate turn assistance, lane-change state and driver
intervention explained much of the visible steering. The custom planner did not
demonstrate sustained useful earlier turn-in through a complete 140-degree turn.

One clear signal-on path reversal came from the ordinary model: at approximately
517.16–519.02 seconds elapsed, the right signal stayed on at 23–24 km/h with
lane-change state off and no recorded driver pressure. The model forecast changed
toward left, briefly right, then left again, while the steering request unwound.
Custom ownership had ended at 515.568 seconds and remained off throughout this
reversal. The displayed path uses `modelV2.position`; it is not replaced by the
custom trajectory. A turn signal supplies turn desire, but does not lock the
model's direction. Removing the custom planner therefore does not establish
that these ordinary-model path reversals are fixed.

At the user-highlighted point, roughly 329.63 seconds into the route, the planner
was enabled but had no replacement and did not own steering. It briefly owned
steering later in that turn at 332.611–332.633 seconds (22 ms) and
334.453–334.521 seconds (68 ms), after turn-in was underway.

No sustained CAN command disruption, thermal fault or steering fault explained
the custom-induced unwind. Command/Panda-return evidence does not establish ECU
acceptance. Raw logs, route/device identifiers, GPS and signed links remain
outside the repository. Historical host simulations do not prove onroad benefit.

If this experiment is ever resumed, reproduce the recorded takeover and complete
downstream command chain offline first, inspect near-term transition/delay
modeling, then investigate planning headroom and capture-history churn. Do not
increase active-time statistics by simply relaxing the lease, body checks or
140-degree capability. Retirement authorizes none of that future work.

## Preserved historical notes

The following fenced sections preserve the original documents verbatim. Their
relative links and application paths refer to the pre-removal layout restored
by the companion patch; their dated statements may be superseded above.

<details>
<summary>docs/EV9_TEST_DRIVE_HANDOFF.md</summary>

``````markdown
# EV9 planner: next-drive handoff

Updated 2026-09-20. Read this first for current state; dated experiments elsewhere
are historical. Read `AGENTS.md` and [the drive-review workflow](RECENT_DRIVE_REVIEW.md)
before acquiring or interpreting route data.

## Source, build and device status

- Branch: `ev9-dev` in `Intelli/openpilot`.
- Committed and pushed source: **`94d8673fde277999a19b581263530d8061b45d9c`**,
  `Reduce EV9 trajectory planning work and fix result freshness`.
- [GitHub native build](https://github.com/Intelli/openpilot/actions/runs/35523918356)
  started 2026-09-20 16:49:31 UTC; observed **in progress** during this handoff.
  Recheck its result; this note does not certify completion or installation.
- Native contract is **ABI6**. Python and the rebuilt solver must match.
  A source-only overlay over the prior ABI4 library cannot run this planner.
  The normal build publishes `ev9-prebuilt`, then the deployment sync copies
  that exact built tree to `ev9`. Verify `Source-Commit` / `Build-Commit` trailers.
- The **user handles the device update and driving test**. No device update or
  setting change was performed for this revision. Last directly verified device
  build: `6ec70ba1893d9987e3ea663a0ccabaae35ea5062`, source
  `a2c43430c40f18a0b31e13ff095dfd4c5335d4e6`, ABI4.
- Last confirmed settings were `EV9TrajectoryMode=2` (ACTIVE) and
  `HkgTuningAngleCustomLimitMaxSpeedKph=40` (EV9 Limits Speed). These are historical
  observations; verify the new route's effective settings. Default mode is OFF;
  mode 1 is SHADOW. Updating does not reset existing preferences.
- Runtime and the standalone regression tests are committed. These handoff notes,
  the temporary checklist, research tools and patch-archive maintenance remain
  local workspace material. Other pre-existing dirty files were preserved.
  Do not blanket-stage them or assume every local patch matches the deployed tree.

## Intended behavior and operating scope

Refine the model's intended turn into an earlier, physically feasible path using
the EV9's full **±140° unassisted steering capability**, then track it through
the existing controller. The general direction remains model-led. This work adds
no actuator angle limiter and does not alter the generic 360° ceiling or IMC keeper.

- Planner speed ceiling uses **EV9 Limits Speed**, default/maximum 40 km/h.
  The old 0.5 m/s eligibility cutoff is removed; movement and existing lateral
  engagement rules still gate tracking. A stop clears ownership.
- Fallback path-adjustment budget is **1.0 m**. Reliable inner-lane observations
  can expand it per side when full reference-body coverage and clearance justify
  the room. Road edges alone cannot authorize expansion. Final candidate body
  and swept-boundary checks remain required for selected reliable observations.
- Missing or uncertain boundaries are neither a mandatory rejection nor proof of
  free space. Reliable finite road edges can reject a candidate crossing them;
  endpoint extrapolation does not invent walls. This is not obstacle detection.
- Physical slew profile is nominally 100°/s, with the existing controller envelope
  where tighter and the live aggregate delay. Body/mount assumptions are in
  `selfdrive/controls/lib/ev9_path_planner.py`; further details are in the
  [research/runtime notes](../tools/ev9_trajectory/README.md).
- A failed refresh may retain its still-valid incumbent. Plans keep the original
  **250 ms source lease**; tracking never renews it. The computation budget is
  **50 ms**, with current state and driver checks at adoption and during tracking.
- Separate EV9 signal/turn-lead and lane-change customizations can change normal
  steering even with this planner inactive. The EV9 turn/lane-change speed split
  uses `max(EV9 Limits Speed, Min Lane Change Speed)`; the lane-change setting
  still matters. Trace those paths separately when investigating turn intent.

## What the new commit changes

1. Keep the full forecast and 30 stages; replace repeated ERK sensitivity
   integration with an analytic curvature/yaw update and an eight-point
   Gauss–Legendre position map. The native optimizer uses DISCRETE dynamics.
2. Express the existing affine cost and corridor constraints directly as linear
   matrices. Keep their weights, interior/terminal bounds and independent dense
   physical and swept-body validation.
3. Use six outer SQP iterations and a 20-iteration inner QP budget; abort a
   proposal when an inner QP exhausts that budget. Four outer iterations lost
   useful early-turn cases and were not retained.
4. Avoid dense interpolation allocations for constant bounds and empty masks.
   Skip expensive body preparation for references already within capability,
   while retaining raw boundary history and full checks for candidate/active paths.
5. Check snapshot age with a fresh clock after worker input preparation. A timely
   solve is no longer rejected solely because its input snapshot aged while it
   computed; adoption still checks current state and the original source lease.

No schema change was needed. On cheap `reference_within_capability` frames,
`geometryAvailable=false` / `boundarySource=none` can mean geometry preparation
was skipped, rather than a failure to obtain usable geometry.

## Completed validation and its limits

| Check | Result |
| --- | --- |
| Focused/integration tests | 436 unique passing tests, including seven actual IPC tests |
| Exact current-source complete-turn simulations | 12/12 pass physical, body and exit checks |
| Recorded native cases from routes 31/35/36 | All 647 previously valid cases retained (450/55/142) |
| Independent native spatial-map check | 45 cases against 4096-substep integration; error below 1e-10 |
| Successful native CPU time on host | p95 approximately 30% lower |
| Full successful planning on host | Median 1.753→1.532 ms; p95 2.350→2.046 ms |
| Causal replay at equal imposed 0/20/40 ms compute, plus 10 ms delivery | Identical old/new adoption and ownership timestamps and reasons |
| Causal replay using measured host compute, plus 10 ms delivery | Adoptions 592→644; ownership 32.853→35.452 s; 14 lease expiries in both |
| OFF/SHADOW comparisons | No output differences |

Maximum simulated exit-heading error is 2.30° versus 1.67° previously, within the
unchanged 3° acceptance criterion. Trajectories are not identical. Recorded
proposed wheel angle peaks at 140.000260°, within existing numerical tolerance.
The causal replay uses recorded motion, latest-input conflation while busy and
current tracking feedback; it cannot establish actual vehicle response. Much of
the measured-host adoption gain occurs in a timing-sensitive calibration interval.

**ABI6 timing on C3X and sustained onroad ownership are unverified.** Older parked
C3X benchmarks in the checklist concern the preceding ABI5 experiment, not this
final solver. The 50 ms budget is not a hard preemption guarantee. Some QP,
dense-bound and deadline failures remain; no further relaxation was justified.
Temporary evidence may no longer exist. The results above and committed tests
provide durable context; reacquire private logs for new analysis as needed.

## Baseline to compare with the next drive

The last reviewed drive was route 36 on the verified ABI4 build above. Across its
full logs there were **1,883 planner proposals, zero feasible proposals and zero
active custom-trajectory states**. Principal reasons included 798 references
already within capability, 477 native status-4 failures and 222 planning deadlines.
Of those 222 deadlines, 56 reported computation at or below 50 ms: snapshot age
also mattered. A reconstructable subset of 122 deadline inputs was feasible on
the host; its recorded median computation was 93.13 ms. CPU contention was material.
These host reconstructions were never actual onroad ownership.

Do not infer that a turn was caused by the custom planner merely because the car
turned early. Original model behavior and separate turn assistance remained active.
The next review must establish whether the new source actually ran, then compare
turn-specific timing, adoption and steering behavior rather than route-wide means
dominated by straight driving.

## Next-session procedure

1. **Review and report first.** The latest handoff authorizes no further source,
   device, settings or commit changes. The user will supply a new route or ask
   for the latest uploaded drive. Discover it through authenticated useradmin by
   recorded time; do not assume the old route 36 is the new test.
2. Read `initData`, recorded build trailers, vehicle metadata and nonempty
   `starpilotPlan.starpilotToggles` JSON. Establish whether source `94d8673fde27`
   (or an identified descendant) and the matching native build ran with ACTIVE
   mode and the intended speed setting. Explain provenance gaps before attribution.
3. Prefer full rlogs across every segment. Keep raw logs, signed links, identifiers
   and GPS outside the repository. Align services by monotonic time using only
   preceding samples for causal replay; quantify gaps/decimation when using qlogs.
4. Count proposals and reasons from `ev9TrajectoryPlan`, including `feasible`,
   `executionValidated`, `solveTime`, plan ID, generation and original source/expiry
   timestamps. **A feasible proposal is not evidence of ownership.** Use matching
   `ev9TrajectoryState.active` and plan IDs to establish actual adoption intervals.
5. Measure turn-specific computation tails, source age, delivery/adoption delay,
   ownership duration, refresh cadence and handbacks. Separate native failure,
   dense/body rejection, ineligibility, expiry and current-state rejection. Check
   `modelCapturePose` validity, tracking errors and calibration continuity.
6. Reconstruct important turns with model action/path/desire and lane-change state,
   blinkers, speed/braking, driver contact, custom plan/state, controlsd curvature,
   requested/filtered steering, measured wheel angle and reliable boundaries.
   Attribute hesitation or wrong direction to the stage where it first appears.
   Distinguish model/extra assistance from actual custom ownership, and requested
   actuator output from verified CAN/ECU response.
7. Report a concise turn timeline and whether the update delivered timely,
   sustained useful ownership, earlier turn-in and appropriate use of 140°.
   Identify remaining failures with evidence and propose the smallest justified
   next change. Do not stack speculative tuning or request a series of miniature
   driving tests before using the available offline evidence.

The [temporary implementation checklist](EV9_TRAJECTORY_IMPLEMENTATION_PLAN.tmp.md)
retains prior iterations. Runtime entry points are `ev9_trajectoryd.py`,
`lib/ev9_path_input.py`, `lib/ev9_path_planner.py`, `lib/ev9_path_mpc.py`,
`lib/ev9_trajectory_control.py` and `lib/ev9_trajectory.py` under
`selfdrive/controls/`. Native generation/wrapper code is in `lib/ev9_path_mpc_lib/`;
synthetic regressions are in `selfdrive/controls/tests/test_ev9_*.py`. Follow the
host-native build instructions in `AGENTS.md`; do not load tracked AGNOS binaries
on macOS or overwrite shipped binaries with host outputs.
``````

</details>

<details>
<summary>docs/EV9_TRAJECTORY_IMPLEMENTATION_PLAN.tmp.md</summary>

``````markdown
# EV9 feasible trajectory — temporary implementation checklist

## Current status: source pushed, native build running (2026-09-20)

The canonical current context is [EV9_TEST_DRIVE_HANDOFF.md](EV9_TEST_DRIVE_HANDOFF.md).
It records the implementation, evidence, operating assumptions, deployment status
and next-drive review procedure without depending on temporary private files.

Runtime and standalone regressions are committed and pushed on ev9-dev as
**94d8673fde277999a19b581263530d8061b45d9c**. The
[GitHub native build](https://github.com/Intelli/openpilot/actions/runs/35523918356)
started at 2026-09-20 16:49:31 UTC and was observed in progress during this handoff.
Recheck completion before updating. The user handles the device update and drive;
installation of this revision has not been verified.

- [x] Replace repeated ERK integration with the discrete spatial map and eight-point
  Gaussian quadrature, retaining the full forecast and 30 stages.
- [x] Express affine costs/bounds directly; use six SQP passes and QP20 failure
  abort. Preserve independent dense physical/body validation and full ±140° use.
- [x] Reduce Python allocations and unnecessary geometry preparation; fix fresh
  snapshot checks without extending the 50 ms computation budget or 250 ms lease.
- [x] Preserve all 647 recorded native successes. Pass 436 unique tests and all
  12 complete-turn simulations. Confirm equal-timing replay ownership unchanged.
- [x] Verify reduced host CPU time. C3X timing for this final ABI6 revision remains
  unmeasured; the next drive must establish timely sustained ownership.
- [x] Refresh owned patch sections and commit the 12 runtime/test files. Preserve
  unrelated edits; keep local documentation/research/archive maintenance unstaged.
- [x] Push ev9-dev; verify the build uses the exact source SHA above.
- [x] Update the handoff, runtime notes and historical context for the next session.
- [ ] Confirm successful native build and ev9 deployment sync with matching
  source/build trailers. ABI6 source requires its matching native library.
- [ ] User updates the device and performs the test drive.
- [ ] Review the new route: recorded build/settings, actual ownership, deadlines,
  refreshes/handbacks, earlier turn-in, hesitation and steering demand/response.
- [ ] Decide whether further changes are justified by that drive. Remaining solver
  and lease failures are possible; host replay alone does not prove onroad benefit.

## Historical implementation record

Everything below is preserved evidence from earlier iterations. Statements such as
“current,” “uncommitted,” “device is now,” unchecked deployment tasks and temporary
paths refer to their original iteration; they are **not current status or new work
instructions**. In particular, the parked ABI5 benchmarks do not measure ABI6.
Use the current checklist and linked handoff above for what remains.

### Historical status: route36 latency and bounded failed solves

This section supersedes the older current-status and deployment notes below.
These changes are local and uncommitted. The installed device remains on
`6ec70ba1893d9987e3ea663a0ccabaae35ea5062`, native ABI 4, ACTIVE mode and
40 km/h EV9 Limits Speed. No installed code or settings changed this iteration.

- [x] Review route36: correct deployed build/settings, but zero feasible proposals
  and zero custom ownership. Timing and solver failures remain material.
- [x] Skip expensive body/boundary preparation for references that need no
  refinement; retain raw boundary history and perform all checks on proposals.
- [x] Separate fresh input eligibility from fresh adoption eligibility. Keep the
  50 ms computation budget, original timestamps, 250 ms model lease and current
  tracking/driver-intervention checks. Recheck input age after worker preparation.
- [x] Bound unsuccessful inner QP work at 20 iterations and abort that proposal
  on inner nonconvergence, rather than repeating it in the outer solver. Preserve
  the 30-node horizon, eight outer iterations, full integration and validation.
  Native ABI 5 requires a matching rebuilt library.
- [x] Discard simpler curve generation, continuation warm starts and relaxed
  stationarity experiments: they reduced coverage or added work without benefit.
- [x] Preserve all 647 independently validated native candidates on routes31/35/36.
  Actual-adapter replay at deterministic 20/40 ms delivery preserves all adoption
  and ownership timestamps. This is recorded-motion replay, not onroad engagement.
- [x] 368 focused/integration tests plus seven real IPC tests pass. All 12 exact
  current-source complete-turn simulations pass body/exit checks within 140 degrees.
  Focused Ruff and source diff checks pass.
- [x] Benchmark the exact final source/native build privately on the parked C3X.
  Across 1,821 route36 attempts, timely validated proposals rise 73→129 without
  added load and 11–13→45 under synthetic CPU contention. Total planner CPU work
  drops about 11%; loaded median wall time falls 9.23–9.26→5.53 ms, p99
  83.45–84.19→74.80 ms. There are still 98 deadline rejections under load and
  a 137.63 ms worst call: this is not a hard runtime bound or proof of onroad use.
- [x] Refresh and round-trip ten owned patch sections, preserving 49 unrelated
  sections and the real Git index. Private benchmarks and route data remain out
  of the repository; no benchmark processes remain on the device.
- [ ] When approved, commit/push and complete the GitHub native build, then deploy
  the matching ABI 5 source/library through the normal approved update workflow.
- [ ] Review a subsequent full drive for actual activation, deadlines and handoffs.
  Synthetic CPU load does not reproduce the full onroad scheduling workload.

Full evidence: `/private/tmp/ev9-route36-simplify/findings.md`; the source/native
hashes used on the device are in `device/final-device-verification.json` there.

### Historical status: route35 runtime correction and EV9 signal split

This section supersedes older current-status/deployment notes below.

- [x] Use max(EV9 Limits Speed, Min Lane Change Speed) for the EV9 turn/lane-change split, including navigation turn intent.
- [x] Reduce the optimizer 40→30 intervals and 20→8 SQP iterations, preserving the full forecast and integration accuracy; native ABI 4 requires a rebuild.
- [x] Remove redundant geometry allocations and avoid unnecessary nearest-reference projections; preserve physical, path and body checks.
- [x] Stop expired geometry work cooperatively instead of continuing a slow body check after the planning deadline.
- [x] 432 focused/integration tests and 12 complete-turn simulations pass; focused Ruff and diff checks pass.
- [x] Same-input parked-C3X comparison: timely validated proposals 10→35, full-planner p99 101.33→45.75 ms, maximum 439.18→112.11 ms. Some missed deadlines and solver failures remain; no hard 50 ms computation ceiling is claimed.
- [x] Recorded-motion adapter replay: latest-route active time unchanged; older-route active ticks 2,300→2,483, with one 58 ms earlier handoff. This does not establish onroad tracking benefit.
- [x] Refresh/round-trip 12 owned patch sections while preserving 49 unrelated sections and the real index.
- [x] Commit/push tested runtime and tracked regressions as `a2c43430c40f18a0b31e13ff095dfd4c5335d4e6` on `ev9-dev`. Documentation, research tools and patch archives remain local.
- [x] GitHub build and deployment sync succeeded. On user request, normal CHECK/DOWNLOAD/INSTALL updated the device on `ev9` from `4b66a79` to `6ec70ba`; exact published tree and reboot verified. Native ABI 4/30-node solver loads and passes an isolated smoke solve; startup processes healthy. Existing ACTIVE mode and 40 km/h EV9 Limits Speed preserved, with a 40 km/h turn/lane-change split.
- [ ] Review actual onroad timing, activation, handoffs and turning after that deployment; further QP/replan failures remain possible.

Full evidence: `/private/tmp/ev9-route35-lightweight/findings.md` and its source manifest. Device is now on `6ec70ba1893d9987e3ea663a0ccabaae35ea5062` with its existing ACTIVE setting. Installation evidence: `/private/tmp/ev9-install-a2c43430/result.json`. New onroad behavior is awaiting the user test drive.

### Historical status: adaptive budget, failed replans and low-speed operation

Older sections below are historical evidence, not additional current blockers.
These changes remain local and uncommitted; nothing has been installed on device.

- [x] Replace the universal one-metre adjustment cap with asymmetric room derived
  from reliable inner-lane geometry, complete body coverage and uncertainty.
  Keep one metre where lane room is unknown; road edges cannot authorize expansion.
  Preserve final swept-body checking and evaluate geometric displacement against
  the budget at the nearest reference location, not a different solver station.
- [x] Recover failures caused by insufficient fixed budget: mirrored 170-degree-
  demand turns now pass complete body/exit tests with 140-degree physical steering.
  Existing 160-degree cases remain successful. At the user's request, exit
  scoring allows three degrees with unchanged position/body requirements;
  180-degree cases with 1.644-degree residual heading now also pass. Raw measured
  outcomes are preserved. Fixed/adaptive success is 2/6 versus 6/6 under the same
  criterion, not a claim that relaxing a score changed the executed motion.
- [x] Investigate remaining QP/dense-bound failures using conditioning, consistent
  initialization and position/heading-consistency experiments. Do not retain
  variants without demonstrated complete-turn benefit. Recorded-input adoptions
  increase 429/407 to 443/420 at 20/40 ms delivery; numerical expiries remain 9/8.
- [x] Remove the planner's 0.5 m/s eligibility cutoff. Use actual speed for the
  physical vehicle model and conservative finite slew conversion while crawling.
  Keep existing lateral-engagement gates; typically steering remains inactive
  at or below 0.3 m/s when the vehicle does not allow standstill steering.
- [x] Replace arbitrary ten-metre plan length with coverage of preview plus
  lease travel, at least one metre. Do not invent a forecast or accept duplicates.
- [x] Clear tracking at standstill and reject all plans sourced at or before the
  last stopped snapshot on restart. Add mirrored native crawl/stop/restart,
  short-horizon, side-budget, larger-turn and transport regression tests.
- [x] Final validation: 549 trajectory/control tests, expanded ten-case rolling
  turn checks, seven real messaging tests, focused Ruff and diff checks.
- [ ] Remaining real-route interruptions are unresolved: not every rejected
  problem is proven impossible. Further changes must show executed-turn benefit,
  not merely additional native solver successes.
- [ ] Build and deploy only when approved, then verify device timing, logged
  activation, tracking transitions and actual behavior. This task does not
  install, enable, commit or push the changes.

Full results and current operating assumptions are in
`tools/ev9_trajectory/README.md`; private simulation/replay evidence is under
`/private/tmp/ev9-expanded-domain/`. Broader stale archive sections remain a
maintenance task; this iteration refreshes only the source/test sections it owns.


### 2026-09-19: faster planning and fewer failed refreshes — retained revision

- [x] Vectorize conservative per-stage physical bounds and exact geometric
  displacement checking. Preserve interior minima/maxima, adjacent-node sharing
  and original displacement results.
- [x] Use two native integration steps per stage. Independent dense integration
  remains authoritative; all eleven recorded integration-residual failures vanish.
- [x] Replace the arbitrary 100 m forecast cutoff with actual dense-output
  capacity (4096 samples, at most 5 cm spacing, about 156.9 m reference length).
  Keep the complete forecast and reject oversized/nonfinite lengths before solving.
- [x] Same route31 causal inputs: 186 to 201 validated proposals, all original
  proposals retained across three alternating before/after runs. Matched accepted
  plans: host median 3.87 to 2.40 ms, p95 4.93 to 3.47 ms.
- [x] Actual-adapter recorded-input replay, assumed 20/40 ms delivery: adoptions
  362/344 to 429/407; active ticks 1907/1842 to 2238/2168; failed-refresh lease
  expiries 10/9 to 9/8. OFF/SHADOW unchanged; geometry within 140 degrees.
- [x] Final production eight-case closed-loop matrix retains 8/8 success and
  identical ownership transitions to the preceding custom planner. Mirrored
  160-degree-demand, 20 km/h cases are now permanent regression tests.
- [x] Final 513 trajectory/control tests pass, including fresh native compilation;
  seven real messaging tests passed. Focused Ruff/source diff checks clean.
- [x] Remove the experimental retry. Unrestricted retry regressed two closed-loop
  turns; continuation-only retry added no sustained-tracking benefit. Keep one
  solve per request and no new retry/lease/limit configuration.
- [x] Refresh only this iteration's runtime/research archive sections and verify
  reverse/forward round trips, preserving unrelated archived sections and staging.
- [ ] Remaining failed refreshes are QP failures or dense-path bound rejections.
  They are not all proven geometrically impossible. Further seed/iteration/solver
  experiments did not establish additional benefit; no relaxed validation retained.
- [ ] C3X execution timing and vehicle behavior are unverified. A normal native
  build and approved deployment are still required; no device changes this turn.

Full findings are in `tools/ev9_trajectory/README.md`. Private evidence:
`/private/tmp/ev9-replan-improvement/final-performance.json`,
`/private/tmp/ev9-replan-improvement/rolling-ab/final-verification.json`, and
`/private/tmp/ev9-planner-adoption/final-no-retry/comparison.json`.
The pre-existing stale sections in the broader patch archives remain outside
this update; section round trips do not certify whole-archive applicability.


### 2026-09-19: worker health, feasible bends and calibration continuity

Lane-change/braking safeguards and the extra-assistance-only high-speed edge
guard were committed and pushed as `481cd8c30d`. The following planner changes
remain local and uncommitted; no device installation or activation was performed.

- [x] Exempt the solving worker's conflated receive frequency from publisher
  health checks. Event validity, liveness and source/capture age remain checked.
- [x] Vectorize the independent dense integration with the same equations and
  validation. No native ABI, iteration limit or deadline change.
- [x] Replace the fixed one-metre opposite-wheel recovery rule. Opposing bends
  already present in the model and physical recovery are allowed; the primary
  turn retains full 140-degree authority. Keep net intent, steering slew,
  one-metre path displacement and reliable full-body boundary checks.
- [x] Reanchor calibration drift only after actual adoption, to the plan's exact
  source-time configuration. Missing history/rejected plans cannot reanchor it.
- [x] 504 trajectory/control tests plus seven real messaging tests pass with
  macOS stale-worktree redirection disabled. Single bends, opposing bends,
  physical initial recovery, rolling full turns and calibration resets covered.
- [x] Same recorded route31 causal inputs: 56 to 186 validated proposals, all
  56 retained. Actual-adapter reconstructed-input replay adopts 362 plans at
  20 ms delivery and 344 at 40 ms; geometry stays within 140 degrees. No active
  generation-mismatch releases; OFF/SHADOW preserve the supplied baseline.
- [x] Mirrored rolling two-bend simulation: peak reference error improves
  12.4 to 5.0 cm in both directions, with 183 adoptions each and 140-degree
  physical steering. Endpoint error rises from 0.4 to 1.4 cm. Both policies
  fail the finite corridor's body check, so this is tracking-error evidence,
  not a demonstrated clearance improvement or complete driving validation.
- [ ] Remaining solver/refresh failures still produce lease-expiry fallbacks.
  These checks do not establish uninterrupted turning or improved vehicle motion.
  Device scheduling and road performance remain unvalidated for this revision.
- [x] Refresh and round-trip the nine owned source/test/document sections in
  the existing runtime/research archives without changing other sections.
  Full archive applicability still fails on older, previously stale sections;
  those broader maintenance updates remain separate from these runtime fixes.

Private reports are in `/private/tmp/ev9-planner-adoption/` and
`/private/tmp/ev9-planner-usefulness-profile/`. Synthetic/recorded-input results
must not be presented as successful on-device interventions.

### 140-degree compatibility and rolling continuation — historical local revision

The physical ±140° capability is a hard constraint, never a solver preference.
The previous10cm/0.01rad forecast-end matching requirement sometimes contradicted
it. The conflict was in our endpoint requirements, not a reason to increase the
vehicle's steering authority. Local implementation is retained after the tests
below. No staging, commits or device changes were made.

- [x] Make the model's terminal pose/curvature a cost target, subject to the same
  hard path, heading and physical constraints as the rest of the trajectory.
  Preserve the approved1m path displacement limit, general turn direction,
  reliable body-boundary checks and all ownership/freshness requirements.
- [x] Independently integrate the proposed curvature controls from the measured
  initial state. An optimizer iteration limit may still yield usable geometry;
  accept it only if the integrated trajectory passes all physical/path checks
  and the planner's independent displacement/body/intent/time checks. QP failures
  and nonfinite output remain rejected. Converged output additionally retains
  the optimizer-node consistency check. No iteration/timeout increase.
- [x] Check curvature at the combined raw-limit and solver-node breakpoints, so
  a narrow varying limit cannot evade validation between dense output samples.
- [x] Bump native ABI to3: status2 now guarantees initialized output arrays.
  Python rejects older libraries. Deployment must include a rebuilt native
  planner library; copying Python source onto the old device binary is inadequate.
- [x] Intersect planning capability with the existing EV9 controller's4.2m/s²
  lateral-acceleration and4.2m/s³ jerk limits at current speed. This adds no
  actuator limit or setting. It prevents a140° plan at speeds where the existing
  controller already allows less, while retaining full140° when deliverable.
- [x] Persist rolling regression coverage: finite10-second,33-point forecasts,
  actual simulated vehicle recapture, native producer/tracker and existing
  steering helpers; both turn directions and high-speed no-regression cases.
- [x] Final local suite533passes; focused Ruff and diff checks clean. Corruption
  tests cover solver nodes, physical slew, segment scale, nonfinite output,
  QP failure, narrow varying curvature limits and stale native ABI.
- [x] Final24 paired synthetic cases: baseline10successes, candidate18successes,
  eight new successes, zero lost successes;16peak-error improvements and zero
  observed regressions. Accepted proposal displacement≤0.995870m; physical
  simulated steering≤140°. Successful adopting cases have peak physical error
  ≤0.898485m from the original reference. This is synthetic controller/geometry
  evidence, not learned-perception or on-road validation.
- [x] The previously failing160°-demand10km/h turn completes continuously through
  the bend: peak error2.161→0.777m; at20km/h2.384→0.880m. Steady144° cases also
  improve. Ramp/step tests retain gains; abrupt speed change causes the expected
  single10ms speed-invalidation/re-adoption, not numerical lease collapse.
- [x] Four deliberately unachievable40km/h turns admit no replacement and remain
  identical to baseline. Four reliable-boundary-conflict cases also retain
  baseline. The intermediate40km/h regression from ignoring existing controller
  limits was corrected before retaining the revision.
- [x] Final causal route00000030 replay admits16proposals versus12in the previous
  local version, but698QP failures and80dense-bound rejections remain. Recorded
  vehicle motion is unchanged in replay; this does not prove sustained device
  use. Host p95 full-planner4.35ms, max33.32ms; device timing remains unverified.

Remaining: the user's recorded turns are not generally solved by this evidence;
real-route geometry/solver failures still need investigation. Neither every turn
nor every speed can fit the available space and1m budget. A failed solve must not
be described as a feasible140° path. Further device testing requires approval,
normal native build/deployment, and then review of actual activation/tracking.
The broader maintenance trajectory patch still needs regeneration once this
runtime revision is accepted; historical patch archives are not current source.

Private evidence: `/private/tmp/ev9-model-led-validation/final-report.json`,
`continuation-findings.md`, and
`/private/tmp/ev9-turn-planner-fixes/continuation-final.json`.
The discarded endpoint-only, cost-weight and initialization experiments remain
private diagnostics, not additional runtime implementations.


### Earlier model-led refinement and 100 cm allowance

User-approved goal: account for the EV9's full ±140° unassisted steering
capability, adjust turn timing/geometry while preserving the model's general
turn direction, and allow up to 100 cm displacement. Missing road-edge evidence
must not by itself require exact model-path matching. No commit or device change
is authorized by this follow-up; staging also remains unchanged.

- [x] Raise the model-path displacement budget from 90 cm to 100 cm. The budget
  measures geometric displacement, not progress along the same curve. It is not
  an instruction to use the whole metre, a tracking-error tolerance, or a new
  actuator limit. EV9 Limits Speed remains the shared ceiling, default/max40km/h.
- [x] Make valid model path/heading the required input and lane/road observations
  optional. Missing, malformed or weak boundaries no longer freeze the reference
  pose or globally reject a turn. No guessed lane width or free-space claim.
- [x] Select reliable constraints independently on each side: inner lane with
  probability≥.5 and std≤.5m, otherwise reliable road edge. These thresholds are
  heuristic; original uncertainty margins still apply to trusted observations.
  A bad/nonfinite value on one side does not discard the reliable opposite side.
- [x] Check the entire candidate and its swept interpolated transitions against
  reliable finite boundaries, including conflicts already present in the raw
  model path. Unknown endpoints are not extrapolated into walls. A newly reported
  reliable-boundary conflict immediately revokes the incumbent plan.
- [x] Retain same-direction curvature and terminal agreement. Compare fresh model
  path intent, not instantaneous model action curvature; an earlier turn-in may
  legitimately differ from the current action. An opposite net model turn clears
  the old trajectory even if its lease has time left or the replacement fails.
- [x] Normal completion additionally requires spatial agreement with the model
  (10cm position/1° heading); equal current steering alone cannot abandon a
  deliberately displaced path. This applies only to relinquishing ownership.
- [x] Allow a forecast ending mid-turn to finish at achievable terminal curvature
  instead of rejecting solely because its requested endpoint curvature exceeds
  ±140°. Visible feasible exit curvature is unchanged. Endpoint position/heading
  constraints remain separately checked.
- [x] Log `ev9TrajectoryPlan.boundarySource` so model-led refinement can be
  distinguished from candidates constrained by observed boundaries.
- [x] Validation: broad local trajectory/control suite515passes; real IPC7passes;
  final affected geometry/input/ownership suite121passes; focused Ruff and diff
  checks pass. Counts overlap. These are host checks, not device timing.
- [x] Causal replay of route00000030 now admits12fresh proposals (previously0),
  including9consecutive frames around+207.6–208.0s.785solver status4 rejections
  remain; the recorded vehicle never followed these new proposals. Replay does
  not establish on-road activation, changed perception, or sustained benefit.
- [x] Finite10-second/33-point rolling simulations use current provider/tracker,
  candidate-driven vehicle poses, solve delivery delay, original incumbent
  leases, causal baseline control and existing controller helpers. Across48
  initial paired cases (clear/missing/weak/wrong-branch uncertain observations),
  both policies complete16, eight candidate cases improve peak path error and
  no success is lost. Remaining32tight/fast cases fail in both arms unchanged.
  At20km/h/144° demand, max original-path error improves about79→43cm in both
  directions. This is one continuous ownership period with fresh plan updates,
  not repeated handoffs. The10km/h case's earlier proposals do not improve its
  eventual peak error.40km/h sharp cases remain infeasible; eligibility is not
  a guarantee of capability at every speed.
- [x] Speed-ramp and step tests improve the successful144° cases (about72→32cm
  and64→28cm), with one10ms invalidation at the abrupt speed jump before fresh
  adoption. Four changing-forecast cases and four reliable-wrong-branch cases
  add no observed regression; trusted conflicts yield no accepted replacement.
  All accepted proposals stay within1m and the synthetic physical wheel within
  140°. Neither the plant nor future forecasts replicate learned perception.

Remaining work/evidence limits:

- [ ] Tight finite-horizon turns still fail. One160° case has a proved endpoint
  contradiction:140° curvature requires y≥4.534m at the prescribed heading,
  versus y≤4.237m permitted by the10cm terminal box. This is distinct from the
  overall1m path budget. A private1m endpoint-box experiment failed convergence
  at both20and40SQPiterations; no accepted trajectory was demonstrated and these
  prototype native changes were NOT retained. Runtime keeps20iterations and the
  existing native ABI. More iterations alone cannot fix the original geometric
  contradiction; a better continuation formulation needs separate validation.
- [ ] On-device runtime/perception effects remain unverified for this local
  revision. No device was changed or driving requested during these checks.
- [ ] Regenerate the broader trajectory maintenance patch after this runtime
  revision is accepted. Existing runtime/research archives are historical and
  do not yet reproduce these uncommitted changes. The separate hesitation patch
  is unchanged by this follow-up.

Current private artifacts: `/private/tmp/ev9-model-led-validation/` and
`/private/tmp/ev9-turn-planner-fixes/model-led-final.json`. The detailed simulation
report records source revisions, assumptions and earlier harness corrections.
Earlier results below describe their original scope; they are not current
finite-horizon evidence and should not be combined into a single success count.


### Earlier local follow-up after route 00000030 — 2026-09-18

Uncommitted local implementation on deployed source `d6db549b6370`.
No staging, commits, device changes, or deployment are authorized without the
user's next approval. Existing unrelated working-tree edits are preserved.

- [x] Both EV9 early-turn assistance and trajectory eligibility consume the
  existing EV9 Limits Speed setting, default/max 40 km/h. Lowering the setting
  invalidates outstanding plans; UI descriptions reflect the shared scope.
- [x] EV9 preview authority varies smoothly with speed and stopping distance.
  Keep current-preview handoff, immediate opposing-intent/manual/lane-change
  vetoes, and the existing creep-speed protection. No extra temporal filter.
- [x] Refresh the separate `patches/ev9_turn_lead_hesitation.patch`, including its
  shared speed-setting helper and tests but excluding trajectory integration.
  Standalone/layered application and current-tree reverse detection pass;
  the real Git index is unchanged.
- [x] Controls publishes the exact current model capture pose from its 100 Hz
  history, avoiding worker-side sampling losses during a solve. Same-generation
  interpolation, freshness and no-extrapolation requirements remain binding.
- [x] Replace forward-x road strips with ordered observed 2D polygons, curved
  rear-history matching, whole-body clearance, and swept checks between poses.
  Heading search bounds now come from observed body clearance, not a fixed 3°.
- [x] Test reference steering slew as well as angle capability before skipping
  refinement. Preserve full ±140° and the current 90 cm displacement allowance.
- [x] Reject contradictory initial/terminal solver constraints explicitly.
  The recorded native failure had a fixed measured pose outside its zero-width
  reference corridor; more iterations could not resolve that contradiction.
- [x] Make initial replan agreement use observed clearance instead of cancelling
  wider valid paths at the old 20 cm prototype gate.
- [x] Validation: broad suite 541 passes, plus all seven real IPC cases using the
  correctly rebuilt native macOS transport; final affected planner/native/UI
  suite 57 passes after the replan correction. Focused Ruff and diff checks pass.
- [x] Four cached routes: 132,506 Controls ticks per policy, no new requests
  opposing raw model intent and no creep-speed changes above 1°. Latest-route
  early assistance begins sooner; filtered request diagnostics improve the
  specific speed/braking transitions. This is not changed-motion validation.
- [x] Rolling synthetic 90° turns with actual provider/tracker and controller
  helpers: at 10 km/h /144° original demand, max original-path error improves
  47.7→19.0 cm; at 20 km/h, 80.2→44.8 cm, in both directions. Tighter /160° and
  40 km/h cases find no replacement and remain unsuccessful in both arms. Four
  improvements, eight unchanged cases, no observed regression in this matrix.

Remaining limits are material, not hidden success criteria:

- [ ] Recorded-route planner replay still admits zero paths. In the sharp turns,
  the available road-edge pair follows a different branch from the model path;
  broad uncertainty margins further reduce usable room. Ordered 2D geometry
  does not manufacture evidence for the intended intersection branch. A usable
  observed turn-space source/association is needed before claiming benefit on
  those turns. Do not substitute an assumed lane width or remove body checks.
- [ ] Runtime timing and changed-perception performance on the device remain
  unverified for this revision. No new drive or device benchmark was requested.
- [ ] Regenerate the broader trajectory maintenance patch once this runtime
  revision is accepted; existing runtime/research archives predate these changes.

Private replay, simulation, timing and diagnostic artifacts:
`/private/tmp/ev9-turn-planner-fixes/`, `/private/tmp/ev9-lead-broader-review/`,
and `/private/tmp/ev9-second-active-review/planner-review/`.

### Earlier implementation and deployment record

Updated 2026-09-18. Development baseline:
`588897a6ceda8d07dcae2afddd01fcbea66a1512` on `ev9-dev`.

Latest testing scope approved by the user: raise the speed ceiling to 40 km/h
and the geometric path-adjustment allowance to 90 cm, then test this candidate
on device before finishing ordinary intersection-turn handling. The broader
intersection implementation remains incomplete; these larger allowances do not
remove the existing geometry and tracking restrictions.

The architecture remains one live path planner feeding one tracker and the
existing steering controller. It changes path geometry using the full ±140°
physical steering capability. It does not teach a new input to the trained model,
change the generic 360° command ceiling, add an actuator cap, or duplicate IMC.

### Implemented

- [x] Map both physical ±140° endpoints through the current learned vehicle model,
  including roll and angle offset. Keep existing manual and OP-long behavior.
- [x] Add a fixed-size compiled acados path solver with variable segment lengths,
  curvature/rate constraints, turn-direction preservation and terminal agreement.
  Runtime uses NumPy/ctypes; generation uses the existing native build infrastructure.
- [x] Connect real model path and boundary inputs, capture-time pose alignment,
  observed body-clearance checks and bounded path displacement.
- [x] Retain previously observed boundaries only behind the current observation,
  for at most eight seconds with original timestamps. Prefer the newest adequate
  observation. Never extrapolate road ahead or refresh old evidence timestamps.
- [x] Publish short-lived plans, capped by both 250 ms capture age and retained
  evidence expiry. No controls-tick renewal or worker-preparation cache.
- [x] Track the path through existing jerk, angle and vehicle controls. Invalid
  state, manual input, mode/transport changes, stale data and failed solves fall
  back to normal controls. No synthetic neutral-steering command on cancellation.
- [x] Keep routine calibration updates from clearing capture history. Material
  cumulative changes, odometry discontinuities and ownership changes still
  invalidate plans/history; every new solve receives current effective parameters.
- [x] Keep controller filter/MDPS state as diagnostic output, not mandatory exact
  reconstruction of internal control history. Use the existing aggregate delay.
- [x] Remove superseded live worker/pipeline/preparation implementations and the
  duplicate reusable research solver. Preserve the original offline optimizer
  and production-controller simulation as validation tools.
- [x] Keep mode 0 (OFF) as default; mode 1 SHADOW and mode 2 opt-in ACTIVE.
- [x] Apply the user-approved 40 km/h / 90 cm testing scope and move shared frame
  conversion into runtime code so the device does not require research tools.

### Historical device-testing profile

- Speed 0.5 m/s through 40 km/h, lateral control active in Drive, no manual
  input/lane change. This is eligibility, not guaranteed feasibility at each speed.
- Same-direction visible bends, sufficient lookahead, up to 90 cm geometric path
  adjustment only where observed space and the existing footprint checks permit.
- Full 140° angle and nominal 100°/s planning slew; no hidden 127° derating.
- Body dimensions and camera assumptions are in
  `selfdrive/controls/lib/ev9_path_planner.py`: front 3.975 m, rear 1.04 m,
  half-width 1.10 m, margin .08 m, camera 2.0 m forward, plus .30/.10 m
  longitudinal/lateral uncertainty allowances. These are explicit experimental
  assumptions; they are not measurements of the installed mount or EPS response.
- Model intent remains authoritative. Observed lane/road geometry constrains
  path changes; it does not certify traffic permission or dynamic occupancy.

### Validation and completion

- [x] Native solver constraints, independent dense body checks, frame conversion,
  state/plan freshness, manual/mode/transport cancellation and history expiry.
- [x] Fixed 64-pair production-controller/CAN matrix: candidate 64 successes,
  reference 50, 14 gains and zero losses. Body clearance improves in every pair;
  both policies use the same physical 140° maximum. Four representative gains
  are retained as native/controller regression tests.
- [x] Receding oracle-geometry helper-plant matrix: 12/12 candidate and baseline
  turns complete, including gradual and abrupt speed changes. Failures revoke
  plans and return to baseline; no result is retrospectively counted as fallback.
- [x] Actual model-provider rolling simulation with candidate-driven poses,
  33-point recaptured paths/boundaries and the bounded observation history:
  8/8 baseline/candidate completions, 2,147 fresh adoptions, median full planner
  6.6–7.2 ms / max12.6 ms on host. Fallback gaps are explicit.
- [x] Narrower real-provider rolling comparison: 8/8 complete in both arms.
  At 4 m width /144° demand, original-path max error improves15.0→4.0 cm,
  physical-body clearance38.5→52.9 cm. At3.5 m/144°, mostly rejected and no
  benefit; both arms exceed the larger uncertainty envelope there.
- [x] Fresh HEAD/OFF/SHADOW control replay: 101,165 cycles per mode across 18
  cached rlogs, exact output/warning equivalence. This is recorded-input evidence,
  not changed-motion or future-perception validation.
- [x] Current suite: 491 trajectory/control tests +94 vehicle-controller tests;
  focused Ruff, native host SCons build and generated schema C++ checks pass.
- [x] Expanded-domain rolling simulation: 16 pairs at 10/20/30/40 km/h with
  144°/160° original demand in both directions. Candidate 6 completions versus
  baseline 4, two gains and zero losses; 920 plan adoptions. At 10 km/h/160°,
  max original-path error improves 62.8 to 19.5 cm. Tight 30/40 km/h cases admit
  no replacement plans and fail in both arms; existing downstream acceleration
  limits still apply. Host full-planner maximum 10.77 ms.
- [x] Earlier narrow-profile causal live-provider replay: 500 eligible model updates, 474 capture
  poses, 83 updates using actual retained boundaries; 39 geometry-available
  frames already within capability. Zero altered-path proposals. Cached routes
  therefore do not demonstrate vehicle benefit.
- [x] Current 40 km/h / 90 cm causal replay over the same three routes:
  101,165 controls ticks, 5,449 eligible model updates, 2,814 geometry-available
  frames, one failed native solve and zero admitted path changes. No nonfinite
  outputs; maximum full-planner time 5.21 ms. The expanded eligibility still
  does not demonstrate benefit on these recordings.
- [x] Export earlier narrow-profile research/runtime patches. All 19 applicability checks pass;
  isolated layered replay reproduces 68 affected application paths, real index
  unchanged. This is a HEAD-layered replay, not a full upstream sync.

### Deferred until after this device test

- [ ] Replace the fixed 90 cm displacement cap with bounds derived from observed
  usable lane/turn space and the vehicle footprint, retaining model intent and
  preferring minimal displacement. Road edges alone must not be treated as
  permission to use another lane. The current constant increase is the user's
  explicitly approved interim testing scope.
- [ ] Replace the provisional speed window with planning constraints consistent
  with the existing speed-dependent steering, lateral-acceleration and jerk
  limits. Use the full ±140° where those existing constraints permit it, and
  handle standstill/restart and changing speed explicitly.
- [ ] Remove prototype-only geometric restrictions that obstruct ordinary turns:
  fixed 3° heading adjustment and the requirement that the entire visible
  reference fit a forward-x, below-60° representation. Support rolling turns
  using observed geometry without demanding an invented unseen exit. Retain
  intended direction/lane and appropriate terminal agreement.
- [ ] Validate the expanded live producer and tracker over normal turn speeds,
  materially earlier/wider paths, changing speed, partial visibility and manual
  takeover. Compare full executed turns and transitions with baseline. Existing
  narrow-profile and oracle-corridor results cannot stand in for these checks.
- [ ] Re-export and verify maintenance patches after the runtime changes settle.
  Existing exported patches predate the 40 km/h / 90 cm scope and frame relocation.

The 22 runtime/schema/build files were committed as `2414b5717867` and published
through the normal GitHub build and deployment sync at the user's request.
The C3X was updated through CHECK/DOWNLOAD/INSTALL from `96ba968` to `0cf0e24`
on `ev9`; its installed commit/tree match the published build and reboot was
verified. Native planner loading and both message schemas pass on device.
Persistent `EV9TrajectoryMode` is now `2` (ACTIVE), with 40 km/h and 90 cm limits.
Manager/UI/updater/offroad processes remained healthy across follow-up checks,
with no observed startup errors. The planner is correctly stopped offroad;
its onroad start condition is true for the cached EV9 configuration.
Documentation, tests, research tools and maintenance patches remain uncommitted.
Next: user device test, then review actual plan admissions/tracking and device
timing in logs. No driving performance has yet been verified on this build.

Earlier whole-intersection certification, exact MDPS/filter-history reconstruction
and slow worker readiness gates are superseded, not unfinished prerequisites.
The prior broad research results remain evidence for their stated synthetic
conditions; they do not establish on-road benefit for this narrower live profile.

See `tools/ev9_trajectory/README.md` for the current architecture and evidence.
Private logs, detailed simulation traces and build outputs remain outside Git in
`/private/tmp/ev9-trajectory-planning/` and `/private/tmp/ev9-path-mpc/`.
``````

</details>

<details>
<summary>tools/ev9_trajectory/README.md</summary>

``````markdown
# EV9 feasible paths: experimental live layer and offline evidence

The live layer refines the model's path using the EV9's full **±140° steering
capability**, then tracks that path through the existing steering controller.
It adds no actuator cap. The generic 360° ceiling, existing OP-long pre-filter
cap, IMC keeper and manual steering behavior remain unchanged.

`EV9TrajectoryMode` defaults to **0 (OFF)**. Mode 1 runs planning in SHADOW;
mode 2 requests ACTIVE when the current state and candidate pass the checks
below. This is an experimental opt-in implementation; native compilation goes
through the normal GitHub build. See the dated deployment context below.

## Current source and deployment context (2026-09-20)

The committed planner source is `94d8673fde277999a19b581263530d8061b45d9c`.
Its native contract is **ABI6**, with 30 stages, a discrete spatial map using
8-point Gauss–Legendre quadrature, six outer SQP iterations and a 20-iteration
inner QP budget that aborts on exhaustion. Planning retains full **±140°**
authority; this adds no actuator angle cap.

Validation recorded for this revision: **436 tests**, **12 bounded closed-loop
simulations**, and **647 previously successful recorded-input native cases
retained**. These are host/synthetic results, not proof of on-road improvement.
Timing for the new revision on C3X has **not been measured**. The last confirmed
installed build was `6ec70ba1893d9987e3ea663a0ccabaae35ea5062` (ABI4);
installation of the new source has not been verified. Source publication alone
does not establish what a recorded drive ran.

Use the [test-drive handoff](../../docs/EV9_TEST_DRIVE_HANDOFF.md) for current build/install status, the next
review procedure and required recorded provenance. Older dated evidence below
is historical; its solver settings, counts and deployment statements describe
that experiment rather than superseding this context.

## Live design

1. `ev9_trajectory_control.py` publishes measured SAS, the matching learned vehicle
   model, aggregate steering delay, odometry and ownership state. Controller
   filter/MDPS snapshots are diagnostics; they are not mandatory reconstruction
   inputs. Routine calibration updates must not destroy continuous pose history.
2. `ev9_trajectoryd.py` aligns each model's capture time with that pose history.
   `ev9_path_input.py` transforms the predicted camera path and observed lane/road
   boundaries into rear-axle coordinates. The model path is required; boundaries
   are optional. Missing or uncertain boundaries leave the one-metre model-path
   adjustment fallback budget available, without claiming verified free space or inventing
   lane widths. Reliable inner lanes can increase the budget independently on
   each side where the complete reference body has observed clearance. Reliable left/right observations independently constrain the body.
   A bounded history keeps actual earlier observations
   only behind the current boundary start, with original timestamps. The newest
   adequate observation is preferred; old data expires after eight seconds and
   caps the plan's expiry as well. Current geometry ahead is never extended.
3. `ev9_path_planner.py` invokes one fixed-size acados spatial optimizer from
   `ev9_path_mpc.py`. It preserves turn direction, treats the forecast endpoint
   as a preferred target, bounds path displacement and converts physical ±140°
   endpoints through the effective
   vehicle model, and checks the full candidate body and swept transitions against
   reliable finite boundaries, including conflicts already in the original path.
   Variable segment lengths allow a different feasible arc length. The existing
   controller acceleration/jerk envelope also constrains planning at higher speed.
   Iteration-limited output is usable only after independent physical integration
   and the full validation chain; optimizer nodes are never published directly.
4. `TrajectoryTracker` follows fresh plans at controls frequency. The existing
   jerk limit, angle controller and carcontroller remain downstream. Manual
   takeover, stale/invalid state, unsupported speed or a reliable-boundary conflict
   restores normal control. A failed refresh may retain its unexpired incumbent;
   a fresh opposite model-path turn cancels it immediately. Fallback does not certify that the original path is
   achievable. Plans expire within 250 ms of capture; controls ticks never renew
   an old plan.

Optimization and dense checking run in the separate existing EV9 planning
process, never in the 100 Hz controls loop. Native runtime imports NumPy/ctypes,
not CasADi/IPOPT. The former Python worker, preparation cache, separate live
pipeline and execution-renewal callbacks have been removed. Full controller
simulation remains an offline validation tool.

## Runtime scope and assumptions

- Enabled lateral control in Drive, no manual input/lane change/steering fault,
  speed **0 through EV9 Limits Speed** (default/max 40 km/h) for otherwise
  eligible planning. Tracking requires movement and no vehicle standstill flag;
  the existing lateral-engagement rules still apply (normally no engagement at
  or below 0.3 m/s when `steerAtStandstill` is false). The reference must have
  sufficient lookahead and a supported turn direction. Eligibility does not
  mean every turn is physically feasible at that speed.
- **1.0 m fallback geometric path adjustment**, expanded independently toward
  a reliable inner lane boundary when complete body coverage and clearance
  justify more room. Body dimensions, mounting allowance and boundary uncertainty
  are included. Missing/weak boundaries and road-edge-only observations cannot
  enlarge it. Final displacement uses the budget at the nearest reference
  location, and all selected reliable boundaries still constrain the swept body.
  This is room available to the optimizer, not an instruction to use it all.
- Forecasts must cover at least **max(1 m, speed × (delay + 0.25 s) + 0.1 m)**.
  No unseen turn exit is invented. Zero-length and duplicate-point forecasts
  remain invalid. Below 0.5 m/s, slew conversion uses 0.5 m/s conservatively to
  avoid unbounded spatial rates; physical steering conversion uses actual speed.
  A stop clears ownership, and plans sourced at or before the last stopped
  snapshot cannot resume it. Fresh restart proposals still pass every check.
- Physical planning slew **100°/s**, constrained by existing controller jerk
  limits where tighter, and the existing live aggregate delay. Do not
  add the controller filter delay a second time. The slew is a tested nominal
  profile, not a measured EPS guarantee.
- Body profile: 3.975 m ahead of the rear axle, 1.04 m behind, half-width 1.10 m,
  margin 0.08 m. Initial camera mount: 2.0 m forward, zero lateral offset, with
  additional body-envelope allowances of 0.30 m longitudinal and 0.10 m lateral.
  These installation/width allowances are explicit assumptions, not measured
  calibration. They are set in `ev9_path_planner.py`.
- Lane probability and boundary standard deviation select reliable observations
  per side, with road-edge fallback. The 0.5 m standard-deviation cutoff is a
  heuristic, not calibrated full-horizon confidence. Reliable boundaries retain
  an uncertainty margin; weak/missing observations do not freeze the model pose.
  Neither source proves traffic permission or obstacle absence. The model retains
  intent; plan logs distinguish model-led and observed-boundary sources.
- Dense body checking uses at most 5 cm path spacing, exact rectangle/boundary
  distances, and bounded subdivision to check the swept interpolated transitions.
  Unobserved boundary endpoints are not extended into walls.

Native ABI6 is required for the current implementation; rebuild
the library together with its Python source. Old binaries are rejected.

## Historical 2026-09-19: adaptive lane room and crawl/restart

This historical iteration replaced the universal one-metre cap with asymmetric
budgets based on observed inner-lane room. Fixed-heading body clearance provides
optimization room; it is not a certificate for a differently oriented candidate.
Heading constraints and final swept-body validation remain binding. This does
not give road edges the meaning of lane-use permission or change which reliable
boundary source is selected for each side.

Six paired closed-loop 90-degree turns at 10 km/h compare the previous fixed
budget with the new budget, using finite ten-second/33-point forecasts, observed
synthetic lane boundaries, the same physical execution model and deterministic
one-cycle delivery:

| Reference demand | Fixed-budget outcome | Adaptive-budget outcome |
| --- | --- | --- |
| 160 degrees, both directions | Full success | Same full success, about 0.777 m peak reference error |
| 170 degrees, both directions | Body/exit failure, 3.456 m peak error | Full success, 1.083 m peak error, 0.026 m exit error and 0.481-degree exit heading error |
| 180 degrees, both directions | Body/exit failure, 4.454 m peak error | Full success under the current three-degree exit criterion: body clears, 1.358 m peak error, 0.032 m exit error and 1.644-degree heading error |

At the user's request, final-heading scoring uses three degrees alongside the
unchanged 0.2 m position and full-body clearance requirements. The 180-degree
cases previously failed only the overly strict one-degree heading score; their
measured behavior has not changed. With this criterion, success increases from
2/6 fixed-budget cases to 6/6 adaptive cases. Steering stays at or below 140
degrees. The 170/180-degree cases use more than one metre of plan adjustment
and are permanent mirrored regressions.
These are prescribed synthetic observations, not changed learned perception.

Route31 actual-adapter recorded-input replay at assumed 20/40 ms delivery adds
14/13 adoptions (429/407 to 443/420), and 62/60 active ticks (2238/2168 to
2300/2228). Failed-refresh expiries remain **9/8**. OFF/SHADOW preserve the
recorded-command baseline and proposed steering remains within 140 degrees.
This is an improvement in usable opportunities, not a resolution of the recorded
interruptions. Plans are still not guaranteed for every turn or speed.

Native conditioning, initialization and heading-target experiments were not
retained: none repaired the targeted expiry windows with demonstrated complete-
turn benefit. Tangent-derived heading increased native candidate counts but
lost previously valid candidates and sometimes disagreed with learned turn
intent. Some recorded position/orientation targets are inconsistent; QP failure
alone still does not establish that no feasible path exists.

Crawl tests cover true low-speed vehicle-model conversion, finite 1–4 m
forecasts, and mirrored partial-bend stop/restart execution. Standstill returns
the baseline command, clears ownership, and rejects a plan sourced exactly at
the last stopped tick as well as older plans. Existing controls engagement gates
are preserved, including the usual 0.3 m/s threshold; this is not forced steering
at standstill. Full-turn accuracy is covered separately from these lifecycle tests.

Final validation: 549 trajectory/control tests passed, followed by the expanded
ten-case rolling-turn suite with three-degree exit scoring; seven actual
messaging tests also passed. Focused lint and source diff checks are clean.

At the time of this historical evaluation, this source had not been installed.
See the current handoff for subsequent deployment status. Recorded-input
replay and host timing cannot establish on-device scheduling or on-road behavior.
Private evidence: `/private/tmp/ev9-expanded-domain/`.

## Historical 2026-09-19: planner performance and failed-replan validation

This iteration retains three small runtime changes: vectorized conservative
stage-bound preparation and exact point-to-polyline displacement checking;
two native ERK integration steps per stage for agreement with independent dense
integration; and dense-output capacity in place of the arbitrary 100 m forecast
cutoff. Forecasts are kept in full, with at most 4096 samples and 5 cm spacing
(the then-tested 40-stage/1.3 scale contract permitted about 156.9 m of reference).
Oversized/nonfinite path lengths fail before native solving.

Physical 140-degree authority, slew/controller limits, the one-metre displacement
budget, observed full-body boundary checks, 50 ms planning deadline and 250 ms
plan lifetime remain unchanged. Native code must be rebuilt with its source.

Validation against the preceding local revision:

| Check | Before | Retained revision |
| --- | ---: | ---: |
| Validated proposals, same route31 causal inputs | 186 | 201 |
| Actual-adapter adoptions, assumed 20/40 ms delivery | 362 / 344 | 429 / 407 |
| Active controls ticks, same adapter runs | 1907 / 1842 | 2238 / 2168 |
| Failed-refresh lease expiries, same adapter runs | 10 / 9 | 9 / 8 |
| Matched accepted-path planning time, host median | 3.87 ms | 2.40 ms |
| Matched accepted-path planning time, host p95 | 4.93 ms | 3.47 ms |

All 186 original causal proposals remain accepted; the comparison was repeated
three times with alternating execution order. All 11 original dynamics-residual
failures disappear; other physical/path checks still reject unsuitable output.
The adapter has adaptive ownership history, so its adoption counts cannot be
compared timestamp-for-timestamp with the static causal protocol. OFF/SHADOW
produce zero differences from the supplied recorded-command baseline.

Eight closed-loop cases (144/160-degree reference demand, 10/20 km/h, both
turn directions) retain all eight successes, the same ownership transitions,
and steering at or below 140 degrees. Peak-error differences from the previous
custom planner are below one micrometre: this demonstrates no regression, not
new simulated tracking improvement. Permanent tests now include the sharper
20 km/h cases. The final trajectory/control suite passes 513 tests; seven actual
messaging tests also passed. Focused Ruff and source diff checks pass.

A bounded constraint-tightening retry was evaluated and removed. Unrestricted
initial retry improved replay counts but caused two sharper closed-loop turns
to lose sustained ownership and fail body/exit checks. Restricting it to active
tracking restored the simulations but added no active time or reduction in
failed-refresh expiries, so the production implementation keeps one solve.

Remaining lease-expiry failures are QP failures or dense-path bound rejections
(20 ms: five QP/four bounds; 40 ms: four/four). A QP failure is not proof that no
feasible trajectory exists. Further iteration/seed/solver experiments did not
establish a retained benefit. Do not relax physical/body checks or extend stale
plans to improve acceptance counts.

Recorded-input replay does not change vehicle motion or perception. Host timing
and reconstructed delivery/health are not C3X timing. At that evaluation, these changes were local,
uncommitted and uninstalled; that statement is historical. On-road benefit was
not established by those experiments. Private evidence is under `/private/tmp/ev9-replan-improvement/` and
`/private/tmp/ev9-planner-adoption/final-no-retry/`.

## Previous worker and continuity validation (2026-09-19)

The worker keeps message validity, liveness and explicit age checks, while
ignoring consumer receive frequency: solving conflates samples even when the
publishers are healthy. Dense independent integration is vectorized without
changing its equations, checks or the 50 ms planning deadline.

The path can contain opposing bends already requested by the model; it is not
forced into a single curvature sign by its net turn. An initially opposite
wheel can recover according to physical slew instead of a one-metre deadline.
An opposing-curvature envelope is limited by the model and measured entry,
with physical 140-degree limits, net intent, heading/displacement and observed
body checks retained. This is not exact local timing agreement with the model.

Only an actually adopted plan can reanchor estimator drift, using its exact
source calibration from bounded controls history. It does not extend plan age
or relax calibration-change thresholds.

504 trajectory/control tests and seven actual messaging tests pass. On the same
route31 causal inputs, fully validated proposals increase from 56 to 186 with
none lost. A separate actual-adapter replay with reconstructed recorded service
inputs adopts 362/344 plans at assumed 20/40 ms delivery. Proposed geometry stays
within 140 degrees; no active generation-mismatch release occurs. OFF/SHADOW
preserve the supplied recorded-command baseline. These are different protocols;
proposal and adoption counts should not be compared directly.

Remaining failed refreshes still cause lease expiry. Recorded motion is not
changed by replay, reconstructed service health is not real messaging timing,
and host solve latency is not C3X latency. These changes are local; no device
installation, activation or driving benefit is established by this validation.

## Earlier evidence

The following results describe earlier profiles and harnesses. The temporary
implementation checklist records current finite-horizon validation and limitations.


The fixed native/controller comparison covers demand 141–144°, road widths
3.5/4/4.5/5 m, both turn directions and both actual EV9 command transports:
**64/64 candidate successes versus 50/64 reference successes, 14 gains, zero
losses**. All gains concern body clearance. Minimum body-to-boundary distance
improved by 8.3–37.4 cm in every pair. Both policies reached the same physical
140° maximum. The baseline is geometric reference feedback, not the learned
model policy.

That comparison uses explicit synthetic road space, speed 2 m/s, hardware delay
0.10 s, aggregate preview 0.30 s and physical slew 100°/s. It exercises production
angle control, carcontroller and decoded CAN; it does not emulate Panda/ECU
fault response. A full-turn oracle plan is used in this matrix, so it does not
by itself establish rolling real-input admission.

Separate real-provider tests admit visible 20/30/45° synthetic bends in both
directions using either lanes or road edges, including the configured body/mount
uncertainty. Rolling replanning and varying speed are checked separately from
initial admission: all eight candidate and baseline cases complete with the
actual provider/planner/tracker and a helper physical plant. These have 2,147
fresh adoptions with explicit fallback gaps, not continuous planner ownership.
The full planner's median is 6.6–7.2 ms and maximum 12.6 ms on this host.

A separate, fixed eight-case rolling comparison uses 3.5/4 m observed corridors,
142/144° reference demand, both directions, hardware delay .10 s and aggregate
preview .30 s. Both policies complete all eight cases. At 4 m / 144°, refinement
reduces maximum error against the original path from **15.0 to 4.0 cm** and
increases minimum physical-body clearance from **38.5 to 52.9 cm**. The inflated
live body envelope also remains inside these 4 m corridors. At 3.5 m / 144°,
planning is almost always rejected and gives no benefit; both policies exceed
the larger uncertainty envelope there, despite clearing the physical body.
These results support bounded improvement, not arbitrary sharp-turn capability.

Native solves alone measured roughly 3.7–5.5 ms on the development host. Host timing is not C3X timing. An isolated SCons build compiled and loaded
the library with repository warning flags; Darwin and Linux library naming were
checked without replacing tracked AGNOS binaries.

Fresh replay of 18 cached full logs across three routes covers **101,165 control
cycles per variant**, including 58,680 autonomous cycles. OFF and SHADOW exactly
match HEAD's serialized control outputs and steering-warning presence. This is
recorded-input replay; it cannot reveal how a changed path would change future
perception or the vehicle's motion.

The final causal live-provider replay includes 500 model updates during valid
execution state, 474 with aligned capture poses. It retains earlier observed
boundaries on 83 updates; 39 have usable geometry, all already within steering
capability. It emits **zero altered-path proposals**. The cached routes therefore
still demonstrate no intervention or on-road improvement. Missing geometry was
not replaced with synthetic corridors to manufacture eligibility.

Final validation: **483 trajectory/control tests and 94 EV9 controller tests
passed**. Focused Ruff, generated schema C++ syntax and native host build checks
passed. All 19 enabled patches pass applicability checks; a layered replay from
HEAD with the original defaults/vehicle patches reversed and updated patches
applied reproduces all 68 affected application paths exactly. The real index is
unchanged. This is not a full upstream sync or an AGNOS device build.

## Offline tools

`optimizer.py` retains the slower CasADi/IPOPT full-turn research oracle;
`execution.py` runs paired trajectories through production controllers and a
synthetic physical plant. They are not imported by the live planner. The broad
research experiments and their optional steering-ratio uncertainty are separate
from the nominal/full-140° live profile.

Use Python 3.11/3.12 and this checkout's environment. Keep private routes/results
outside the repository. On macOS, tests importing Params/messaging require
host-native extensions; do not load or overwrite the tracked AGNOS binaries.

```sh
# Broad offline example: supplied 7 m corridor, 160° original demand.
.venv/bin/python -m openpilot.tools.ev9_trajectory.solve \
  --output /tmp/ev9-turn.json --plot /tmp/ev9-turn.png

SP_DISABLE_HOST_PYTEST_REDIRECT=1 .venv/bin/python -m pytest \
  tools/ev9_trajectory/tests -q -o addopts= \
  --confcutdir=tools/ev9_trajectory/tests -p no:cacheprovider
```

No installation, parameter activation, user test drive, commit or push is part
of these host checks. Current work/status is tracked in the temporary
`docs/EV9_TRAJECTORY_IMPLEMENTATION_PLAN.tmp.md`.
``````

</details>

<details>
<summary>patches/EV9_STEERING_PLANNING_REVIEW.md</summary>

``````markdown
# EV9 achievable-steering evaluation

**Historical rejected-prototype review.** For source `94d8673fde27` (ABI6),
current build/install verification and the next recorded-drive review, use the
[EV9 test-drive handoff](../docs/EV9_TEST_DRIVE_HANDOFF.md). The measurements in
this document are not current planner performance or deployment claims.

Review date: 2026-09-18. Baseline: `588897a6ceda8d07dcae2afddd01fcbea66a1512`.

This is the historical review of the rejected two-second preview. Its extra
limits and local candidate checks were removed after comparative regressions.
The later [feasible-path implementation](../tools/ev9_trajectory/README.md) uses
an actual path optimizer and tracker; that separate default-OFF layer is now
retained with bounded synthetic evidence. The findings below describe the
rejected prototype, not the current working-tree integration status.

The evaluation assumes **140° of autonomous steering authority**, as requested.
It does not establish an OEM limit. The existing direct OP-long 140° target cap,
manual/recovery behavior, 360° outer command range, Improved Manual Control keeper
and warning policy remain as they were before the experiment. Other controller
and Panda limits still apply. No additional stock-ACC or upper-level angle cap
is retained.

## What the active planning stack knows

In `selfdrive/modeld/modeld.py`, `_runner_frame_args()` supplies the model's
declared inputs. `lateral_control_params` contains speed and lateral delay;
`action_t` carries action timing; models that support `prev_action` receive the
previous model action. There is no maximum steering-angle input. Appending 140°
to these tensors would change the trained input contract, not configure it.

`controlsd` consumes the model's desired curvature and applies control shaping.
Changing the Hyundai controller's 360° ceiling cannot make that upstream model
plan a wider turn. The legacy lateral MPC is not the active source of these
model actions, so changing its constraints alone would not solve this either.

The prototype added curvature bounds and a separate two-second geometric preview.
It therefore knew about 140°, but the working-tree prototype only bounded requests
and evaluated path candidates in shadow mode. Bounded requests alone were not
accepted as evidence of better driving.

## Recorded-input A/B replay

Both variants called the real `Controls.update()`, `state_control()` and
`publish()` with identical preceding recorded inputs and recorded vehicle/settings
snapshots. Baseline modules were verified byte-for-byte against the commit above.
Actual `SelfdriveD` steering-warning logic was also evaluated. This was not a
replay of the complete engagement state machine, controller CAN stream or physical
vehicle. Recorded measurements and future model outputs stayed fixed.

Three existing routes covered OP-long with IMC off, stock ACC with IMC off, and
stock ACC with IMC on. There were **101,165 control cycles**, including **58,680
autonomous cycles**. Route identities and raw/frame-level evidence remain private.
The OP-long recording itself used an earlier 119.9° controller cap; the A/B source
baseline has the existing 140° cap. This difference is not hidden as on-road
validation of the prototype.

| Comparison | Result | Interpretation |
| --- | --- | --- |
| Autonomous commands after algebraic ±140° clipping | Only 32 of 58,680 cycles differ | Almost all added bounding is redundant under the assumed physical cap; this is not a simulated EPS response. |
| Remaining command differences | Five intervals, about 0.34 seconds total | Consistent with jerk-limiter unwind history; every interval has zero turn-hold in both variants. No tracking benefit established. |
| Inactive commands and active/manual classifications | Identical | No observed classification or inactive-passthrough improvement. |
| Executed geometric adjustments | Zero | No real-route evidence of earlier/wider turns. |
| Warning events | Additional transient warnings, including 31 added cycles on one route | Unconditionally using pre-jerk demand changes warnings even when the 140° limit is irrelevant. |

In one additional warning episode, both variants commanded about −65.5°, while
the prototype used about −118.6° as warning demand. The angle cap was not binding.
This was a regression introduced by forwarding raw demand on every cycle.

The route boundary estimates did not support the proposed path adjustment. Even
a separate, more permissive audit found no autonomous turn frame with both
inner-lane probabilities at least 0.5 and both road-edge standard deviations at
most 0.5. The prototype confidence gates were not relaxed to manufacture an
activation result.

## Independent simulation

The physical plant used the real curvature, angle-rate and filter helpers,
followed by a separate 140° physical-authority assumption. This distinguishes
physical saturation from clipping the requested angle before the filter. Extra
pre-filter clipping can slow the approach to the physical limit, while reducing
unwind delay later; fewer oversized requests is not automatically better tracking.

The 413-case EV9-parameter sweep covered steering demand from 60° to 220°,
speed from 1 to 7 m/s, delay from 0 to 0.3 seconds, both directions, calibration
and state errors, corridor width/confidence, countersteer and manual transitions.
The prototype improved maximum path error by more than 1 cm in 134 cases, worsened
it in 153 and stayed within 1 cm in 126, compared with ordinary requests into the
physically capped plant. Additional clipping alone improved 1 case and worsened
180. This segment sweep used instantaneous reference curvature. These are
synthetic sensitivity results, not measured EV9 performance.

Complete 90° turns plus an exit segment were also evaluated. A delay-aware
reference controller was included because the existing driving model already
receives delay/timing information. A comparison against only instantaneous
curvature would overstate the benefit of adding earlier steering. This reference
controller is an approximation, not a reproduction of the learned driving model.

The primary full-turn run used the recorded EV9's nominal vehicle parameters,
including steer ratio 16.0, wheelbase 3.10 m and its mass/inertia/tire stiffness.
Both variants used the same geometry and initial conditions. Results below use
maximum path error, with differences within 1 cm counted as effectively equal.

| Complete EV9-model turns: prototype versus reference | Improved | Worsened | Within 1 cm |
| --- | ---: | ---: | ---: |
| Delay-aware requests with physical 140° saturation | 1 | 40 | 5 |
| Delay-aware requests with additional pre-filter clipping | 1 | 18 | 27 |

These 46 cases included 90° turns and a 5 m exit, with vehicle-state/model
perturbations. Candidates were selected in 22 cases. In the worst regression
against the additionally clipped reference, maximum error rose from 0.069 m to
0.287 m. The two-second candidate checks did not establish whole-turn benefit.

An explicitly paired speed experiment repeated 24 of the same geometric turns
at half speed. Reference tracking error decreased in all 24, but 16 still required
more than 140° to follow the path. For example, slowing a 180°-demand turn from
3 to 1.5 m/s reduced the clipped reference's error only from 4.887 m to 4.565 m;
it achieved approximately 77° of the required 90° heading change. A feasible
100°-demand turn improved from 0.189 m to 0.029 m. This demonstrates the distinction
between response-time limitations and an impossible radius. It assumes the lower
speed is already achieved before the turn; it does not validate braking approach,
traffic interaction or a new longitudinal-control policy. No speed change is
retained from this experiment.

## Corrected preview without an added unconditional cap

A second, private-only version left ordinary requests unchanged and constrained
only selected geometric candidates. It also corrected the preview's baseline
forecast to anticipate the turn throughout its horizon. The independent plant
applied physical saturation after filtering, distinguishing stock-ACC requests
from the existing direct OP-long cap. This directly tested whether an informed
planner could help without adding a redundant ordinary-command limit.

Nine nominal execution-parity checks matched the real-helper plant within
1e-12, and an explicit over-limit ordinary request passed through unchanged.
These checks establish implementation consistency, not real-vehicle accuracy.
Each mode repeated the same 46 complete turns and 24 half-speed cases.

| Corrected preview versus unchanged reference | Candidate cases | Improved | Worsened | Within 1 cm |
| --- | ---: | ---: | ---: | ---: |
| Stock-ACC command path | 5 | 2 | 1 | 43 |
| Existing direct OP-long cap | 6 | 3 | 1 | 42 |

The two stock-ACC improvements were only 1.7 and 2.4 cm. With a 2° initial
heading error, however, maximum path error increased from 0.335 to 0.678 m:
a 34.3 cm regression despite seven locally accepted candidate frames. The
same disturbed case regressed by 28.8 cm with the existing direct cap.
Neither mode changed any half-speed result by more than 1 cm.

The correction substantially reduced unnecessary intervention, but the local
candidate checks still did not establish whole-turn benefit. It was not retained
in driving code. Further broad tuning was stopped after this counterexample;
the corrected version is not claimed to resolve the earlier manual-transition
failures. Real-route corridor coverage and learned-model feedback also remain
unvalidated.

## Retention and future acceptance criteria

Removed: the new runtime preview, extra curvature/angle caps, turn-hold bounding,
uncapped-warning override, diagnostic schemas/filter telemetry, prototype tests
and corresponding patch additions. The experiment and its reports are preserved
privately outside the repository. No vehicle update or deployment occurred.

Any replacement needs to demonstrate benefit over the existing delay-aware
command pipeline and physical saturation, not merely over a deliberately clipped
or delay-unaware baseline. It must improve complete turns and exits under realistic
vehicle-model uncertainty, preserve manual takeover/reentry, and establish usable
road/obstacle clearance. Speed coordination must distinguish a response-time
problem from a path whose radius cannot be achieved even at low speed.

For reproducibility, use full local rlogs, causal timestamp joins and recorded
vehicle/settings snapshots as described in
[the drive-review workflow](../docs/RECENT_DRIVE_REVIEW.md). Compare requested,
filtered, transmitted and physically achievable steering separately; measure
tracking and heading, not just the number of clipped requests. Keep private logs
and exploratory scripts outside the repository. A passing recorded-input replay
does not validate changed vehicle or future model responses.

After restoring the baseline, **222 focused regression tests passed**, including
native Panda/controller checks. All 17 enabled patches passed the existing
applicability check.
``````

</details>

<details>
<summary>docs/STARPILOT_MIGRATION.md: historical planner integration status</summary>

``````markdown
### Experimental trajectory integration status

`ev9_trajectory_runtime.patch` preserves the default-OFF live EV9 path refiner:
one compiled acados planner, short-lived plans, one tracker and the existing
steering chain. It uses the full ±140° physical planning authority without adding
an actuator cap. Changes remain model-led, with a one-metre fallback adjustment
budget and possible expansion from reliable inner-lane room. Selected reliable
boundaries constrain the swept body; missing boundaries do not certify free space.
Recent observations extend rear-body coverage only, never unseen road ahead.
`ev9_trajectory_research.patch` keeps the separate offline optimizer, paired
production-controller simulations, route audit and tests. Slow live workers,
prepared-solver caching and execution-renewal callbacks have been removed.

Vehicle patches `05`/`06` preserve output-only filter/MDPS/transport diagnostics.
Their absence does not invalidate otherwise fresh public SAS/vehicle-model state.
The mode default remains in `custom_defaults_starpilot.patch`. Source and native
code must pass the normal GitHub device build before installation; no default
activation or deployment occurred during host development.

An earlier narrow native/controller matrix gave 64/64 synthetic successes versus
50/64 reference successes, with no lost successes. Those historical results and
their OFF/SHADOW comparison do not describe the current validation matrix or prove
onroad benefit. The current ABI6 revision retains 647 recorded native successes;
actual onroad ownership remains to be verified on the next drive. See the
[current validation and review procedure](EV9_TEST_DRIVE_HANDOFF.md).

``````

</details>

<details>
<summary>patches/PR_TRACKER.md: former E15 status</summary>

``````markdown
**E15 — feasible-path research and experimental live layer (2026-09-18): Held / fork-only.**
`ev9_trajectory_research.patch` preserves offline optimization, controller-chain
simulation, route audits and integration tests. `ev9_trajectory_runtime.patch`
adds one compiled path refiner, observed rear-boundary history, short-lived plans
and the existing tracker/control connection. Full ±140° authority; no actuator
cap. Vehicle `05`/`06` retain optional diagnostic snapshots, distinct from E14.
The narrow native/controller matrix achieved 64/64 versus 50/64 synthetic
successes with zero losses. Real vehicle benefit and device timing remain
unvalidated; no upstream submission is being prepared. See the
[current scope and evidence](../tools/ev9_trajectory/README.md).

``````

</details>

<details>
<summary>patches/README.md: former planner archive ownership</summary>

``````markdown
`ev9_trajectory_research.patch` preserves offline optimization, production-controller
simulation, route audits and tests. `ev9_trajectory_runtime.patch` adds the
opt-in compiled path refiner, observed rear-boundary history, short-lived plans,
tracker and control integration. It permits the full ±140° planning authority
without adding an actuator cap. The obsolete live worker/preparation pipeline
has been removed. Mode registration remains in `custom_defaults_starpilot.patch`.
Vehicle `05`/`06` preserve optional output-only filter/MDPS/transport diagnostics;
missing old telemetry does not block fresh standard measured state.
See [current evidence and limitations](../tools/ev9_trajectory/README.md).

``````

</details>
