#!/usr/bin/env python3
from __future__ import annotations

import argparse
import logging
import sys

from kia_lock import KiaAutoLockClient, KiaCredentials, Region


def parse_args() -> argparse.Namespace:
  parser = argparse.ArgumentParser(description="Lock a Kia vehicle via KiaAutoLockClient (new shared implementation)")
  parser.add_argument("username", help="Account username")
  parser.add_argument("password", help="Account password")
  parser.add_argument("pin", help="Remote services PIN")
  parser.add_argument("region", choices=[r.value for r in Region], help="Region code (US/CA/EU/CN/AU)")
  parser.add_argument("vin", nargs="?", help="Vehicle VIN (optional if account has single vehicle)")
  parser.add_argument("vehicle_id", nargs="?", help="Vehicle identifier if VIN not provided")
  parser.add_argument("--language", default=None, help="Optional language code for EU region")
  parser.add_argument("--verbose", action="store_true", help="Enable debug logging")
  return parser.parse_args()


def main() -> int:
  args = parse_args()

  logging.basicConfig(level=logging.DEBUG if args.verbose else logging.INFO)

  region = Region(args.region.upper())
  creds = KiaCredentials(
    username=args.username,
    password=args.password,
    pin=args.pin,
    region=region,
    vin=args.vin,
    vehicle_id=args.vehicle_id,
    language=args.language,
  )

  client = KiaAutoLockClient(creds)

  try:
    client.lock()
  except Exception as err:  # pylint: disable=broad-except
    logging.exception("Lock command failed: %s", err)
    return 1

  logging.info("Lock command succeeded")
  return 0


if __name__ == "__main__":
  sys.exit(main())
