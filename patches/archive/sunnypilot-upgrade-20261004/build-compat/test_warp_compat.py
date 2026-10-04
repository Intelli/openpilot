import importlib.util
from pathlib import Path

import pytest


SOURCE = Path(__file__).resolve().parents[3] / "selfdrive/modeld/warp_compat.py"
SPEC = importlib.util.spec_from_file_location("warp_compat", SOURCE)
warp_compat = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(warp_compat)


def test_mutating_capture_preserves_buffer_identity():
  road_buffer, wide_buffer, road_pair, wide_pair = [object() for _ in range(4)]
  result = warp_compat.unpack_warp_result((road_pair, wide_pair), road_buffer, wide_buffer)
  assert result == (road_buffer, road_pair, wide_buffer, wide_pair)


def test_explicit_capture_replaces_buffers_and_preserves_camera_order():
  old_road, old_wide, new_road, new_wide, road_pair, wide_pair = [object() for _ in range(6)]
  result = warp_compat.unpack_warp_result([new_road, road_pair, new_wide, wide_pair], old_road, old_wide)
  assert result == (new_road, road_pair, new_wide, wide_pair)


@pytest.mark.parametrize("count", [0, 1, 3, 5])
def test_unexpected_capture_arity_fails(count):
  with pytest.raises(ValueError, match="Expected 2 or 4 warp outputs"):
    warp_compat.unpack_warp_result([object() for _ in range(count)], object(), object())
