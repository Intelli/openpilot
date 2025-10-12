#!/usr/bin/env python3
import os
import re
import datetime
import subprocess
import psutil
import shutil
import signal
import fcntl
import tempfile
import threading
from collections import defaultdict
from pathlib import Path

from openpilot.common.basedir import BASEDIR
from openpilot.common.params import Params
from openpilot.common.time_helpers import system_time_valid
from openpilot.common.markdown import parse_markdown
from openpilot.common.swaglog import cloudlog
from openpilot.selfdrive.selfdrived.alertmanager import set_offroad_alert
from openpilot.system.hardware import AGNOS, HARDWARE
from openpilot.system.version import get_build_metadata, SP_BRANCH_MIGRATIONS

LOCK_FILE = os.getenv("UPDATER_LOCK_FILE", "/tmp/safe_staging_overlay.lock")
STAGING_ROOT = os.getenv("UPDATER_STAGING_ROOT", "/data/safe_staging")

FINALIZED = os.path.join(STAGING_ROOT, "finalized")
FINALIZED_MARKER = os.path.join(FINALIZED, ".update_ready")
STAGED_BRANCH_PARAM = "UpdaterStagedBranch"
STAGED_COMMIT_PARAM = "UpdaterStagedCommit"
OVERLAY_CONSISTENT = Path(os.path.join(FINALIZED, ".overlay_consistent"))
OVERLAY_INIT = Path(os.path.join(BASEDIR, ".overlay_init"))

# do not allow to engage after this many hours onroad and this many routes
HOURS_NO_CONNECTIVITY_MAX = 27
ROUTES_NO_CONNECTIVITY_MAX = 84
# send an offroad prompt after this many hours onroad and this many routes
HOURS_NO_CONNECTIVITY_PROMPT = 23
ROUTES_NO_CONNECTIVITY_PROMPT = 80


class UserRequest:
  NONE = 0
  CHECK = 1
  FETCH = 2

class WaitTimeHelper:
  def __init__(self):
    self.ready_event = threading.Event()
    self.user_request = UserRequest.NONE
    signal.signal(signal.SIGHUP, self.update_now)
    signal.signal(signal.SIGUSR1, self.check_now)

  def update_now(self, signum: int, frame) -> None:
    cloudlog.info("caught SIGHUP, attempting to downloading update")
    self.user_request = UserRequest.FETCH
    self.ready_event.set()

  def check_now(self, signum: int, frame) -> None:
    cloudlog.info("caught SIGUSR1, checking for updates")
    self.user_request = UserRequest.CHECK
    self.ready_event.set()

  def sleep(self, t: float) -> None:
    self.ready_event.wait(timeout=t)

def write_time_to_param(params, param) -> None:
  t = datetime.datetime.now(datetime.UTC).replace(tzinfo=None)
  params.put(param, t)

def run(cmd: list[str], cwd: str = None) -> str:
  return subprocess.check_output(cmd, cwd=cwd, stderr=subprocess.STDOUT, encoding='utf8')


def set_update_ready(ready: bool) -> None:
  if ready:
    Path(FINALIZED_MARKER).touch()
    OVERLAY_CONSISTENT.touch()
  else:
    Path(FINALIZED_MARKER).unlink(missing_ok=True)
    OVERLAY_CONSISTENT.unlink(missing_ok=True)
  os.sync()


def ensure_staging_root() -> None:
  os.makedirs(STAGING_ROOT, exist_ok=True)


def clear_staged_metadata(params: Params | None = None) -> None:
  p = params or Params()
  for key in (STAGED_BRANCH_PARAM, STAGED_COMMIT_PARAM):
    try:
      p.remove(key)
    except Exception:
      pass


def invalidate_staged_update(params: Params | None = None) -> None:
  set_update_ready(False)
  clear_staged_metadata(params)
  OVERLAY_INIT.unlink(missing_ok=True)

def parse_release_notes(basedir: str) -> bytes:
  try:
    with open(os.path.join(basedir, "RELEASES.md"), "rb") as f:
      r = f.read().split(b'\n\n', 1)[0]  # Slice latest release notes
    try:
      return bytes(parse_markdown(r.decode("utf-8")), encoding="utf-8")
    except Exception:
      return r + b"\n"
  except FileNotFoundError:
    pass
  except Exception:
    cloudlog.exception("failed to parse release notes")
  return b""

def get_remote_url(path: str) -> str:
  return run(["git", "config", "--get", "remote.origin.url"], path).strip()


def compute_git_diff(branch: str) -> str:
  try:
    return run(["git", "diff", "--stat", "HEAD", f"origin/{branch}"], BASEDIR)
  except subprocess.CalledProcessError:
    cloudlog.exception("failed to compute git diff")
  return ""


def finalize_update(checkout_path: str) -> None:
  params = Params()
  quickboot_enabled = params.get_bool("UsePrebuiltToggle")
  if quickboot_enabled:
    params.put_bool("QuickBootPendingRebuild", True)

  cloudlog.info("finalizing downloaded update")
  set_update_ready(False)
  ensure_staging_root()

  if os.path.exists(FINALIZED):
    shutil.rmtree(FINALIZED)
  shutil.copytree(checkout_path, FINALIZED, symlinks=True)

  run(["git", "reset", "--hard"], FINALIZED)
  run(["git", "submodule", "foreach", "--recursive", "git", "reset", "--hard"], FINALIZED)

  if quickboot_enabled:
    prebuilt_path = Path(FINALIZED) / "prebuilt"
    prebuilt_path.unlink(missing_ok=True)
    live_prebuilt = Path(BASEDIR) / "prebuilt"
    live_prebuilt.unlink(missing_ok=True)

  set_update_ready(True)
  cloudlog.info("download finalized")


def handle_agnos_update(checkout_path: str) -> None:
  from openpilot.system.hardware.tici.agnos import flash_agnos_update, get_target_slot_number

  cur_version = HARDWARE.get_os_version()
  updated_version = run(["bash", "-c", r"unset AGNOS_VERSION && source launch_env.sh && \
                          echo -n $AGNOS_VERSION"], checkout_path).strip()

  cloudlog.info(f"AGNOS version check: {cur_version} vs {updated_version}")
  if cur_version == updated_version:
    return

  set_update_ready(False)

  cloudlog.info(f"Beginning background installation for AGNOS {updated_version}")
  set_offroad_alert("Offroad_NeosUpdate", True)

  manifest_path = os.path.join(checkout_path, "system/hardware/tici/agnos.json")
  target_slot_number = get_target_slot_number()
  flash_agnos_update(manifest_path, target_slot_number, cloudlog)
  set_offroad_alert("Offroad_NeosUpdate", False)



class Updater:
  def __init__(self):
    self.params = Params()
    self.branches = defaultdict(str)
    self._has_internet: bool = False

  @property
  def has_internet(self) -> bool:
    return self._has_internet

  @property
  def target_branch(self) -> str:
    b: str | None = self.params.get("UpdaterTargetBranch")
    if b is None:
      b = self.get_branch(BASEDIR)
    b = SP_BRANCH_MIGRATIONS.get((HARDWARE.get_device_type(), b), b)
    return b

  @property
  def update_ready(self) -> bool:
    if Path(FINALIZED_MARKER).is_file() and os.path.isdir(FINALIZED):
      staged_branch = self.params.get(STAGED_BRANCH_PARAM)
      staged_commit = self.params.get(STAGED_COMMIT_PARAM)
      if staged_branch is None or staged_commit is None:
        return False

      finalized_commit = self.get_commit_hash(FINALIZED)
      base_commit = self.get_commit_hash(BASEDIR)
      if finalized_commit == "" or base_commit == "":
        return False

      branch_matches = staged_branch == self.target_branch == self.get_branch(FINALIZED)
      return branch_matches and finalized_commit == staged_commit and staged_commit != base_commit
    return False

  @property
  def update_available(self) -> bool:
    remote_commit = self.branches.get(self.target_branch)
    if remote_commit is None:
      return False

    local_commit = self.get_commit_hash(BASEDIR)
    if local_commit == "":
      return False
    return remote_commit != local_commit
    return False

  def get_branch(self, path: str) -> str:
    try:
      return run(["git", "rev-parse", "--abbrev-ref", "HEAD"], path).rstrip()
    except Exception:
      return ""

  def get_commit_hash(self, path: str = BASEDIR) -> str:
    try:
      return run(["git", "rev-parse", "HEAD"], path).rstrip()
    except Exception:
      return ""

  def set_params(self, update_success: bool, failed_count: int, exception: str | None) -> None:
    self.params.put("UpdateFailedCount", failed_count)
    self.params.put("UpdaterTargetBranch", self.target_branch)

    self.params.put_bool("UpdaterFetchAvailable", self.update_available)
    if len(self.branches):
      self.params.put("UpdaterAvailableBranches", ','.join(self.branches.keys()))

    last_uptime_onroad = self.params.get("UptimeOnroad", return_default=True)
    last_route_count = self.params.get("RouteCount", return_default=True)
    if update_success:
      self.params.put("LastUpdateTime", datetime.datetime.now(datetime.UTC).replace(tzinfo=None))
      self.params.put("LastUpdateUptimeOnroad", last_uptime_onroad)
      self.params.put("LastUpdateRouteCount", last_route_count)
    else:
      last_uptime_onroad = self.params.get("LastUpdateUptimeOnroad", return_default=True)
      last_route_count = self.params.get("LastUpdateRouteCount", return_default=True)

    if exception is None:
      self.params.remove("LastUpdateException")
    else:
      self.params.put("LastUpdateException", exception)

    # Write out current and new version info
    def get_description(basedir: str) -> str:
      if not os.path.exists(basedir):
        return ""

      version = ""
      branch = ""
      commit = ""
      commit_date = ""
      try:
        branch = self.get_branch(basedir)
        commit = self.get_commit_hash(basedir)[:7]
        with open(os.path.join(basedir, "common", "version.h")) as f:
          version = f.read().split('"')[1]

        commit_unix_ts = run(["git", "show", "-s", "--format=%ct", "HEAD"], basedir).rstrip()
        dt = datetime.datetime.fromtimestamp(int(commit_unix_ts))
        commit_date = dt.strftime("%b %d")
      except Exception:
        cloudlog.exception("updater.get_description")
      return f"{version} / {branch} / {commit} / {commit_date}"
    self.params.put("UpdaterCurrentDescription", get_description(BASEDIR))
    self.params.put("UpdaterCurrentReleaseNotes", parse_release_notes(BASEDIR))
    self.params.put("UpdaterNewDescription", get_description(FINALIZED))
    self.params.put("UpdaterNewReleaseNotes", parse_release_notes(FINALIZED))
    self.params.put_bool("UpdateAvailable", self.update_ready)
    self.params.put("GitDiff", compute_git_diff(self.target_branch))

    # Handle user prompt
    for alert in ("Offroad_UpdateFailed", "Offroad_ConnectivityNeeded", "Offroad_ConnectivityNeededPrompt"):
      set_offroad_alert(alert, False)

    dt_uptime_onroad = (self.params.get("UptimeOnroad", return_default=True) - last_uptime_onroad) / (60*60)
    dt_route_count = self.params.get("RouteCount", return_default=True) - last_route_count
    build_metadata = get_build_metadata()
    if failed_count > 15 and exception is not None and self.has_internet:
      if build_metadata.tested_channel:
        extra_text = "Ensure the software is correctly installed. Uninstall and re-install if this error persists."
      else:
        extra_text = exception
      set_offroad_alert("Offroad_UpdateFailed", True, extra_text=extra_text)
    elif failed_count > 0:
      if dt_uptime_onroad > HOURS_NO_CONNECTIVITY_MAX and dt_route_count > ROUTES_NO_CONNECTIVITY_MAX:
        set_offroad_alert("Offroad_ConnectivityNeeded", True)
      elif dt_uptime_onroad > HOURS_NO_CONNECTIVITY_PROMPT and dt_route_count > ROUTES_NO_CONNECTIVITY_PROMPT:
        remaining = max(HOURS_NO_CONNECTIVITY_MAX - dt_uptime_onroad, 1)
        set_offroad_alert("Offroad_ConnectivityNeededPrompt", True, extra_text=f"{remaining} hour{'' if remaining == 1 else 's'}.")

  def check_for_update(self) -> None:
    cloudlog.info("checking for updates")

    excluded_branches = ('release2', 'release2-staging')

    try:
      run(["git", "ls-remote", "origin", "HEAD"], BASEDIR)
      self._has_internet = True
    except subprocess.CalledProcessError:
      self._has_internet = False

    output = run(["git", "ls-remote", "--heads", "origin"], BASEDIR)

    self.branches = defaultdict(lambda: None)
    for line in output.split('\n'):
      ls_remotes_re = r'(?P<commit_sha>\b[0-9a-f]{5,40}\b)(\s+)(refs\/heads\/)(?P<branch_name>.*$)'
      x = re.fullmatch(ls_remotes_re, line.strip())
      if x is not None and x.group('branch_name') not in excluded_branches:
        self.branches[x.group('branch_name')] = x.group('commit_sha')

    cur_branch = self.get_branch(BASEDIR)
    cur_commit = self.get_commit_hash(BASEDIR)
    new_branch = self.target_branch
    new_commit = self.branches[new_branch]
    if (cur_branch, cur_commit) != (new_branch, new_commit):
      cloudlog.info(f"update available, {cur_branch} ({str(cur_commit)[:7]}) -> {new_branch} ({str(new_commit)[:7]})")
    else:
      cloudlog.info(f"up to date on {cur_branch} ({str(cur_commit)[:7]})")

  def fetch_update(self) -> None:
    cloudlog.info("starting staged update download")
    self.params.put("UpdaterState", "downloading...")
    set_update_ready(False)
    self.params.put_bool("UpdateAvailable", False)
    ensure_staging_root()

    remote_url = get_remote_url(BASEDIR)
    branch = self.target_branch

    with tempfile.TemporaryDirectory(prefix="update_", dir=STAGING_ROOT) as tmpdir:
      OVERLAY_INIT.touch()
      clone_cmd = [
        "git", "clone", "--progress",
        remote_url,
        "--branch", branch,
        "--depth", "1",
        "--recurse-submodules",
        tmpdir,
      ]
      clone_output = run(clone_cmd)
      cloudlog.info("git clone success: %s", clone_output)

      run(["git", "submodule", "update", "--init", "--recursive"], tmpdir)

      cloned_commit = self.get_commit_hash(tmpdir)
      self.params.put(STAGED_BRANCH_PARAM, branch)
      self.params.put(STAGED_COMMIT_PARAM, cloned_commit)

      if AGNOS:
        handle_agnos_update(tmpdir)

      self.params.put("UpdaterState", "finalizing update...")
      finalize_update(tmpdir)

    cloudlog.info("update download finalized")


def main() -> None:
  params = Params()

  if params.get_bool("DisableUpdates"):
    cloudlog.warning("updates are disabled by the DisableUpdates param")
    exit(0)

  with open(LOCK_FILE, 'w') as ov_lock_fd:
    try:
      fcntl.flock(ov_lock_fd, fcntl.LOCK_EX | fcntl.LOCK_NB)
    except OSError as e:
      raise RuntimeError("couldn't get overlay lock; is another instance running?") from e

    # Set low io priority
    proc = psutil.Process()
    if psutil.LINUX:
      proc.ionice(psutil.IOPRIO_CLASS_BE, value=7)

    # Check if we just performed an update
    if Path(os.path.join(STAGING_ROOT, "old_openpilot")).is_dir():
      cloudlog.event("update installed")

    if not params.get("InstallDate"):
      t = datetime.datetime.now(datetime.UTC).replace(tzinfo=None)
      params.put("InstallDate", t)

    updater = Updater()
    update_failed_count = 0
    wait_helper = WaitTimeHelper()

    ensure_staging_root()

    # invalidate any stale staged update from previous runs
    invalidate_staged_update(params)

    params.put("UpdaterState", "idle")

    first_run = True
    while True:
      wait_helper.ready_event.clear()

      exception = None
      try:
        updater.set_params(False, update_failed_count, exception)

        if not system_time_valid() or first_run:
          first_run = False
          wait_helper.sleep(60)
          continue

        update_failed_count += 1

        params.put("UpdaterState", "checking...")
        updater.check_for_update()

        last_fetch = params.get("UpdaterLastFetchTime")
        timed_out = last_fetch is None or (datetime.datetime.now(datetime.UTC).replace(tzinfo=None) - last_fetch > datetime.timedelta(days=3))
        user_requested_fetch = wait_helper.user_request == UserRequest.FETCH
        if params.get_bool("NetworkMetered") and not timed_out and not user_requested_fetch:
          cloudlog.info("skipping fetch, connection metered")
        elif wait_helper.user_request == UserRequest.CHECK:
          cloudlog.info("skipping fetch, only checking")
        else:
          updater.fetch_update()
          write_time_to_param(params, "UpdaterLastFetchTime")
        update_failed_count = 0
      except subprocess.CalledProcessError as e:
        cloudlog.event(
          "update process failed",
          cmd=e.cmd,
          output=e.output,
          returncode=e.returncode
        )
        exception = f"command failed: {e.cmd}\n{e.output}"
        invalidate_staged_update(params)
      except Exception as e:
        cloudlog.exception("uncaught updated exception, shouldn't happen")
        exception = str(e)
        invalidate_staged_update(params)

      try:
        params.put("UpdaterState", "idle")
        update_successful = (update_failed_count == 0)
        updater.set_params(update_successful, update_failed_count, exception)
      except Exception:
        cloudlog.exception("uncaught updated exception while setting params, shouldn't happen")

      wait_helper.user_request = UserRequest.NONE
      wait_helper.sleep(5*60 if update_failed_count > 0 else 1.5*60*60)


if __name__ == "__main__":
  main()
