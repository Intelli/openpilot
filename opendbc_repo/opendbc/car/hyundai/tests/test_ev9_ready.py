"""Vehicle READY telemetry uses accepted CAN samples, not publication timestamps."""

import pytest

from opendbc.can import CANPacker
from opendbc.car import Bus, gen_empty_fingerprint
from opendbc.car.hyundai.carstate import CarState
from opendbc.car.hyundai.interface import CarInterface
from opendbc.car.hyundai.values import CAR, DBC


def setup_state(candidate=CAR.KIA_EV9):
  fingerprint = gen_empty_fingerprint()
  cp = CarInterface.get_params(candidate, fingerprint, [], False, False, False, None)
  fpcp = CarInterface.get_starpilot_params(candidate, fingerprint, [], cp, None)
  state = CarState(cp, fpcp)
  parsers = state.get_can_parsers(cp)
  packer = CANPacker(DBC[candidate][Bus.pt])
  # Register lazily accessed messages before supplying a complete valid parser batch.
  state.update_canfd(parsers)
  for parser in parsers.values():
    messages = [packer.make_can_msg(msg.name, parser.bus, {}) for msg in parser.message_states.values()]
    parser.update([(1_000_000_000, messages)])
  return state, parsers, packer


def test_ready_transition_and_timestamp_retention():
  state, parsers, packer = setup_state()
  pt = parsers[Bus.pt]
  _, status = state.update_canfd(parsers)
  assert not status.vehicleReady
  assert status.vehicleReadyTimestamp == 1_000_000_000

  msg = packer.make_can_msg("ACCELERATOR", pt.bus, {"EV9_READY": 1})
  assert msg[1][3] & 0x40  # Match the existing initialization guard's raw bit.
  pt.update([(1_010_000_000, [msg])])
  validity_count = pt.can_invalid_cnt
  _, status = state.update_canfd(parsers)
  assert pt.can_invalid_cnt == validity_count
  assert status.vehicleReady
  assert status.vehicleReadyTimestamp == 1_010_000_000

  pt.update([(1_020_000_000, [])])
  _, status = state.update_canfd(parsers)
  assert status.vehicleReady
  assert status.vehicleReadyTimestamp == 1_010_000_000

  pt.update([(1_030_000_000, [packer.make_can_msg("ACCELERATOR", pt.bus, {"EV9_READY": 0})])])
  _, status = state.update_canfd(parsers)
  assert not status.vehicleReady
  assert status.vehicleReadyTimestamp == 1_030_000_000


def test_bad_checksum_does_not_refresh_ready():
  state, parsers, packer = setup_state()
  pt = parsers[Bus.pt]
  address, data, bus = packer.make_can_msg("ACCELERATOR", pt.bus, {"EV9_READY": 1})
  corrupted = bytearray(data)
  corrupted[0] ^= 1
  pt.update([(1_010_000_000, [(address, bytes(corrupted), bus)])])
  _, status = state.update_canfd(parsers)
  assert not status.vehicleReady
  assert status.vehicleReadyTimestamp == 1_000_000_000


def test_bad_counter_invalidates_transport_without_refreshing_ready():
  state, parsers, packer = setup_state()
  pt = parsers[Bus.pt]
  msg = packer.make_can_msg("ACCELERATOR", pt.bus, {"EV9_READY": 1})
  for index in range(7):
    pt.update([(1_010_000_000 + index * 1_000_000, [msg])])
  rejected_timestamp = pt.ts_nanos["ACCELERATOR"]["EV9_READY"]
  pt.update([(1_020_000_000, [msg])])
  assert pt.ts_nanos["ACCELERATOR"]["EV9_READY"] == rejected_timestamp
  _, status = state.update_canfd(parsers)
  assert status.vehicleReadyTimestamp == rejected_timestamp
  # CarInterface/card propagate this as the publication's validity; the UI rejects it.
  assert not pt.can_valid


def test_missing_frames_never_refresh_source_timestamp():
  state, parsers, _ = setup_state()
  parsers[Bus.pt].update([(2_000_000_000, [])])
  _, status = state.update_canfd(parsers)
  # Optional parser messages can remain valid without new frames. The UI must check
  # the source timestamp independently of transport/parser validity.
  assert status.vehicleReadyTimestamp == 1_000_000_000


@pytest.mark.parametrize("candidate", [CAR.KIA_EV9, CAR.KIA_EV6])
def test_unknown_before_first_sample_and_ev9_only(candidate):
  fingerprint = gen_empty_fingerprint()
  cp = CarInterface.get_params(candidate, fingerprint, [], False, False, False, None)
  fpcp = CarInterface.get_starpilot_params(candidate, fingerprint, [], cp, None)
  state = CarState(cp, fpcp)
  _, status = state.update_canfd(state.get_can_parsers(cp))
  assert not status.vehicleReady
  assert status.vehicleReadyTimestamp == 0

  if candidate != CAR.KIA_EV9:
    state, parsers, packer = setup_state(candidate)
    pt = parsers[Bus.pt]
    pt.update([(1_010_000_000, [packer.make_can_msg("ACCELERATOR", pt.bus, {"EV9_READY": 1})])])
    _, status = state.update_canfd(parsers)
    assert not status.vehicleReady
    assert status.vehicleReadyTimestamp == 0
