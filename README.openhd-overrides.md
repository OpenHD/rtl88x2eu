# OpenHD Override Flow for rtl88x2eu

The rtl88x2eu driver exposes three module parameters that OpenHD can use to
force the radio configuration even when regulatory or userspace requests would
select different values:

- `openhd_override_channel`
- `openhd_override_channel_width`
- `openhd_override_tx_power_mbm`

This document explains what each override changes inside the driver and the
steps the driver performs when a new value is supplied.

## 1. Channel override

1. Userspace writes the desired primary channel number to the
   `openhd_override_channel` module parameter (for example with
   `echo 149 > /sys/module/88x2eu/parameters/openhd_override_channel`).
2. The module parameter is stored in the driver's global registry copy inside
   `os_dep/linux/os_intfs.c`.
3. Whenever cfg80211 asks the driver to configure a monitor channel (through
   `cfg80211_rtw_set_monitor_channel`), the helper
   `rtw_apply_openhd_monitor_overrides` refreshes the cached registry copy with
   the latest module parameter value and then replaces the target channel with
   the OpenHD override.
4. The monitor-mode configuration command (`rtw_set_chbw_cmd`) finally programs
   the hardware with the overridden channel, so the adapter tunes directly to
   the OpenHD request even if cfg80211 asked for something else.

## 2. Channel-width override

1. Userspace writes a desired channel width to the
   `openhd_override_channel_width` module parameter. The value should match the
   driver's internal width constants (20/40/80/160 MHz, etc.).
2. The module parameter is cached in the registry state when the driver loads
   and refreshed every time OpenHD applies overrides.
3. `rtw_apply_openhd_monitor_overrides` swaps the width selected by cfg80211
   with the override. If a narrower width (20 MHz or below) is requested, the
   primary-channel offset is automatically cleared so the firmware uses a pure
   primary channel.
4. The final width is visible in the diagnostic log message emitted by the
   helper before the configuration command runs, which makes it easier to
   confirm which width the radio will use.
5. The `rtw_set_chbw_cmd` call uses the overridden width and programs the PHY
   accordingly.

## 3. TX-power override

1. Userspace writes a power level (in milli-dBm) to
   `openhd_override_tx_power_mbm`.
2. During each cfg80211 `set_tx_power` call the driver checks the module
   parameter and validates the requested level with
   `phy_is_txpwr_user_mbm_valid` so that only power values supported by the
   chipset are accepted.
3. When the override is valid the driver clears the regulatory limit, sets the
   target power level to the override value, and logs the exact override that
   will be enforced.
4. The driver schedules `rtw_update_txpwr_level_all_hwband` to run in the
   command thread so the hardware immediately adopts the new power level.
5. Subsequent `get_tx_power` calls and log lines reflect the OpenHD override so
   users can verify the applied power.

Together these three paths ensure that channel, bandwidth, and transmit power
are all driven by OpenHD without relying on cfg80211 or regulatory negotiation.
