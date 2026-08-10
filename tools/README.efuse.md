# OpenHD eFuse provisioning tool

The native C++ `openhd-efuse-flash` utility provisions one
RTL8812EU/RTL8822EU-family USB card with the OpenHD Wi-Fi map and a persistent
MAC address:

```sh
sudo openhd-efuse-flash wlan1
```

The command takes an exclusive lock, reloads `88x2eu_ohd` in MP mode, checks
the existing hardware MAC and raw eFuse capacity, stages the map and official
RTL8822E USB mask, asks for an irreversible-write confirmation, writes the
eFuse, verifies the hardware readback, records the allocated MAC, and reloads
the driver in normal mode. A card that already has a driver-valid permanent
MAC is reported without another write.

Connect exactly one supported Realtek card while provisioning. The utility
tracks the card through its sysfs driver association, so it remains on the
correct device if Linux renumbers `wlan0` and `wlan1` during module reloads.

For unattended operation, add `--yes`. Production lines with more than one
flashing host should allocate MAC addresses centrally and supply one with
`--mac 00:E0:4C:xx:xx:xx`; the local registry and lock prevent duplicates and
concurrent writes on one host, but cannot coordinate independent hosts.

The map and mask are installed as root-only files under `/etc/wifi`. This
prevents non-root users from reading them, but cannot protect the data from a
machine administrator. The map also remains visible in this public Git
repository and its history. Genuine confidentiality requires keeping the map
and flashing fixture under trusted control.

Do not interrupt power during the irreversible write.

## Debian package

Build a package for the current Debian architecture with:

```sh
make openhd-efuse-deb
```

Install the resulting package from `dist/`, then provision one connected card:

```sh
sudo apt install ./openhd-efuse-flasher_1.0.2_armhf.deb
sudo openhd-efuse-flash
```

Without `--mac`, the utility generates a random address in the `00:E0:4C`
range and rejects addresses already recorded on that host. The package stores
the map and mask as root-only configuration files. Anyone who can obtain and
extract the package can still recover those files; client-side packaging
cannot make a locally used provisioning map secret.

Newly provisioned cards receive the fixed USB serial string `673643`. The
utility verifies both the generated MAC and this serial directly from hardware
after the write. Cards that already have a valid permanent MAC are left
unchanged.

To update only the USB serial on an already-provisioned card, without changing
its MAC or other logical-map fields, run:

```sh
sudo openhd-efuse-flash --serial-only
```

This direct eFuse update is also irreversible. It requires typing `SERIAL`
before writing unless `--yes` is supplied, and verifies the resulting serial
from hardware before reporting success.

## RF test mode

Run the separate, time-bounded RF single-tone test with:

```sh
sudo openhd-efuse-flash wlan1 --rf-test
```

On an interactive terminal, a `whiptail` menu selects 20 or 40 MHz. For
automation, use `--bandwidth 20` or `--bandwidth 40` and optionally
`--duration SECONDS` (10 seconds by default, 300 maximum). The test uses
channel 36, maximum power index 63 on paths A and B, and stops automatically.
For 20 MHz the center frequency is 5180 MHz. For 40 MHz, 5180 MHz is the
primary frequency and the bonded-channel center is 5190 MHz.

This is a continuous RF test signal, not normal Wi-Fi traffic. Use it only in
a shielded test setup and where the transmission is permitted. Press Ctrl-C
to stop it early. The tool stops MP transmission and restores normal driver
mode during cleanup.

Build only the utility with:

```sh
make openhd-efuse-tool
```
