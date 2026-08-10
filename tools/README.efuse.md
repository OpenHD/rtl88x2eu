# OpenHD eFuse provisioning tool

`openhd-efuse-flash` provisions one RTL8812EU/RTL8822EU-family USB card with
the OpenHD Wi-Fi map and a persistent MAC address:

```sh
sudo openhd-efuse-flash wlan1
```

The command takes an exclusive lock, reloads `88x2eu_ohd` in MP mode, checks
the existing hardware MAC and raw eFuse capacity, stages the map and official
RTL8822E USB mask, asks for an irreversible-write confirmation, writes the
eFuse, verifies the hardware readback, records the allocated MAC, and reloads
the driver in normal mode. A card that already has a driver-valid permanent
MAC is reported without another write.

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
