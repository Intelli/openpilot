def unpack_warp_result(result, image_buffer, big_image_buffer):
  """Normalize captures that mutate buffers or return updated buffers explicitly."""
  if len(result) == 2:
    return image_buffer, result[0], big_image_buffer, result[1]
  if len(result) == 4:
    return tuple(result)
  raise ValueError(f"Expected 2 or 4 warp outputs, received {len(result)}")
