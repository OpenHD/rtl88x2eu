#!/usr/bin/env python3

import importlib.machinery
import importlib.util
import unittest
from pathlib import Path


TOOL = Path(__file__).with_name("openhd-efuse-flash")
LOADER = importlib.machinery.SourceFileLoader("openhd_efuse_flash", str(TOOL))
SPEC = importlib.util.spec_from_loader(LOADER.name, LOADER)
FLASHER = importlib.util.module_from_spec(SPEC)
LOADER.exec_module(FLASHER)


class FlasherTests(unittest.TestCase):
    def test_driver_mac_validation(self):
        self.assertTrue(FLASHER.driver_accepts_mac(bytes.fromhex("00e04c123456")))
        self.assertFalse(FLASHER.driver_accepts_mac(bytes.fromhex("02e04c123456")))
        self.assertFalse(FLASHER.driver_accepts_mac(bytes.fromhex("01e04c123456")))
        self.assertFalse(FLASHER.driver_accepts_mac(b"\xff" * 6))

    def test_blank_card_flow_reserves_before_write(self):
        mac = bytes.fromhex("00e04c123456")
        events = []
        read_count = 0

        def fake_ioctl(_interface, command):
            nonlocal read_count
            events.append(command)
            if command == "mp_start":
                return "m  p  _  s  t  a  r  t     o  k"
            if command.startswith("efuse_get rmap"):
                read_count += 1
                value = b"\xff" * 6 if read_count == 1 else mac
                return " ".join(f"0  x  {byte:02X}" for byte in value)
            if command == "efuse_get ableraw":
                return "[ available raw size ] = 1 0 9 0 bytes"
            if command.startswith("efuse_file "):
                return "efuse file file_read OK"
            if command.startswith("efuse_mask "):
                return "efuse mask file read OK"
            if command.startswith("efuse_set wlwfake"):
                return "wlwfake OK"
            if command.startswith("efuse_get wlrfkrmap"):
                return " ".join(f"0  x  {byte:02X}" for byte in mac)
            if command == "efuse_set wlfk2map":
                return "WiFi write map compare OK"
            raise AssertionError(command)

        original_ioctl = FLASHER.ioctl_command
        FLASHER.ioctl_command = fake_ioctl
        reserved = []
        try:
            result = FLASHER.provision(
                "wlan1",
                Path("/map"),
                Path("/mask"),
                mac,
                True,
                lambda value: (reserved.append(value), events.append("RESERVED")),
            )
        finally:
            FLASHER.ioctl_command = original_ioctl

        self.assertEqual(result, (mac, True))
        self.assertEqual(reserved, [mac])
        self.assertLess(events.index("RESERVED"), events.index("efuse_set wlfk2map"))


if __name__ == "__main__":
    unittest.main()
