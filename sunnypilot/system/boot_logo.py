"""Install the EV9 artwork for AGNOS boot without changing driving settings."""
from io import BytesIO
from pathlib import Path
import subprocess
import tempfile

from PIL import Image


ARTWORK = Path(__file__).resolve().parents[1] / "selfdrive/assets/images/ev9_boot.jpg"


def logo_images(source: Path, landscape_jpeg: bool) -> dict[str, bytes]:
  with Image.open(source) as image:
    image = image.convert("RGB")
    landscape = image if image.width >= image.height else image.transpose(Image.Transpose.ROTATE_90)
    portrait = landscape.transpose(Image.Transpose.ROTATE_270)
    jpeg, png = BytesIO(), BytesIO()
    (landscape if landscape_jpeg else portrait).save(jpeg, format="JPEG", quality=95)
    landscape.save(png, format="PNG")
  return {"bg.jpg": jpeg.getvalue(), "bg.png": png.getvalue()}


def install_boot_logo(destination: Path = Path("/usr/comma")) -> bool:
  try:
    magic = destination / "magic.py"
    landscape_jpeg = magic.is_file() and "/usr/comma/bg.jpg" in magic.read_text()
    images = logo_images(ARTWORK, landscape_jpeg)
    updates = {name: data for name, data in images.items()
               if (name == "bg.jpg" or (destination / name).is_file()) and
               (not (destination / name).is_file() or (destination / name).read_bytes() != data)}
    if not updates:
      return True
    mount_options = subprocess.check_output(["findmnt", "-n", "-o", "OPTIONS", "/"], text=True).strip()
    if not mount_options:
      raise RuntimeError("Unable to determine root mount options")
    with tempfile.TemporaryDirectory(prefix="ev9-boot-logo-") as temporary:
      for name, data in updates.items():
        (Path(temporary) / name).write_bytes(data)
      subprocess.run(["sudo", "mount", "-o", "remount,rw", "/"], check=True)
      try:
        for name in updates:
          subprocess.run(["sudo", "cp", str(Path(temporary) / name), str(destination / name)], check=True)
      finally:
        subprocess.run(["sudo", "mount", "-o", f"remount,{mount_options}", "/"], check=True)
    return True
  except (OSError, ValueError, RuntimeError, subprocess.SubprocessError) as error:
    print(f"EV9 boot artwork could not be installed: {error}")
    return False
