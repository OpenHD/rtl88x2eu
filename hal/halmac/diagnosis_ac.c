/******************************************************************************
 *
 * Copyright(c) 2018 - 2019 Realtek Corporation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 ******************************************************************************/

#include "halmac_dbg_cmd.h"
#include "diagnosis_ac.h"
#if HALMAC_FEATURE_DBGPKG
#if HALMAC_SELF_DIAG
extern u32 halmac_diag_lvl;
u32 diagnosis_SYSTEM_HCI_PCIE(struct halmac_adapter *adapter, u32 *check_number, char *output, u32 out_len, u32 *used)
{
	struct halmac_api *api = (struct halmac_api *)adapter->halmac_api;
	u32 ret = 0;
	u32 reg1 = 0, reg2 = 0, cnt = 0;
	*check_number = 0;

		return cnt;
}

u32 diagnosis_SYSTEM_HCI_USB(struct halmac_adapter *adapter, u32 *check_number, char *output, u32 out_len, u32 *used)
{
	struct halmac_api *api = (struct halmac_api *)adapter->halmac_api;
	u32 ret = 0;
	u32 reg1 = 0, reg2 = 0, cnt = 0;
	*check_number = 0;

		return cnt;
}

u32 diagnosis_SYSTEM_MAC_EDCA(struct halmac_adapter *adapter, u32 *check_number, char *output, u32 out_len, u32 *used)
{
	struct halmac_api *api = (struct halmac_api *)adapter->halmac_api;
	u32 ret = 0;
	u32 reg1 = 0, reg2 = 0, cnt = 0;
	*check_number = 0;

		return cnt;
}

u32 diagnosis_SYSTEM_MAC_MACTOP(struct halmac_adapter *adapter, u32 *check_number, char *output, u32 out_len, u32 *used)
{
	struct halmac_api *api = (struct halmac_api *)adapter->halmac_api;
	u32 ret = 0;
	u32 reg1 = 0, reg2 = 0, cnt = 0;
	*check_number = 0;

		return cnt;
}

u32 diagnosis_SYSTEM_MAC_PROT(struct halmac_adapter *adapter, u32 *check_number, char *output, u32 out_len, u32 *used)
{
	struct halmac_api *api = (struct halmac_api *)adapter->halmac_api;
	u32 ret = 0;
	u32 reg1 = 0, reg2 = 0, cnt = 0;
	*check_number = 0;

		return cnt;
}

u32 diagnosis_SYSTEM_MAC_RXDMA(struct halmac_adapter *adapter, u32 *check_number, char *output, u32 out_len, u32 *used)
{
	struct halmac_api *api = (struct halmac_api *)adapter->halmac_api;
	u32 ret = 0;
	u32 reg1 = 0, reg2 = 0, cnt = 0;
	*check_number = 0;

		return cnt;
}

u32 diagnosis_SYSTEM_MAC_SYSTEM(struct halmac_adapter *adapter, u32 *check_number, char *output, u32 out_len, u32 *used)
{
	struct halmac_api *api = (struct halmac_api *)adapter->halmac_api;
	u32 ret = 0;
	u32 reg1 = 0, reg2 = 0, cnt = 0;
	*check_number = 0;

#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x2);
		if ((reg1 & 0x03) != 0x03) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 2 => %x,\n+-- ERROR:BB disabled\n\n", __func__, reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x3);
		if ((reg1 & 0x04) != 0x04) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 3 => %x,\n+-- ERROR:MCU core disable\n\n", __func__, reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x6);
		if ((reg1 & 0x02) != 0x02) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 6 => %x,\n+-- ERROR:Power is not ready from LPS , ROF , suspend mode\n\n", __func__, reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x6);
		if ((reg1 & 0x01) != 0x01) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 6 => %x,\n+-- ERROR:WLON circuit reset not ready\n\n", __func__, reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0xA);
		if ((reg1 & 0x20) != 0x20) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: A => %x,\n+-- ERROR:WLAN efuse autoload failed\n\n", __func__, reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x1C);
		if ((reg1 & 0x20) != 0x00) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 1C => %x,\n+-- ERROR:Cannot write Reg 0x1C[6]\n\n", __func__, reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x1C);
		if ((reg1 & 0x10) != 0x00) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 1C => %x,\n+-- ERROR:Cannot write Reg 0x40~0x43\n\n", __func__, reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x1C);
		if ((reg1 & 0x08) != 0x00) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 1C => %x,\n+-- ERROR:Cannot write Reg 0x8~0xB\n\n", __func__, reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x1C);
		if ((reg1 & 0x04) != 0x00) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 1C => %x,\n+-- ERROR:Cannot write Reg 0x4~0x7\n\n", __func__, reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x1C);
		if ((reg1 & 0x02) != 0x00) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 1C => %x,\n+-- ERROR:Cannot write Reg 0x0~0x3\n\n", __func__, reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x1C);
		if ((reg1 & 0x01) != 0x00) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 1C => %x,\n+-- ERROR:Cannot write Reg 0x0~0xFF\n\n", __func__, reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x1D);
		if ((reg1 & 0x01) != 0x01) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 1D => %x,\n+-- ERROR:WLMCU IO interface control disabled\n\n", __func__, reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x1F);
		if ((reg1 & 0x07) != 0x07) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 1F => %x,\n+-- ERROR:RF disabled\n\n", __func__, reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x57);
		if ((reg1 & 0x20) != 0x00) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 57 => %x,\n+-- ERROR:SPS OCP alarm interrupt\n\n", __func__, reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R16(0x80);
		if ((reg1 & 0x8000) != 0x8000) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 80 => %x,\n+-- ERROR:Download firmware failed\n\n", __func__, reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x90);
		if ((reg1 & 0x01) != 0x00) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 90 => %x,\n+-- ERROR:PMC stay in  wait XTAL ready \n\n", __func__, reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0xF3);
		if ((reg1 & 0xf0) != 0x00) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: F3 => %x,\n+-- ERROR:Not in normal mode\n\n", __func__, reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0xF2);
		if ((reg1 & 0x10) != 0x00) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: F2 => %x,\n+-- ERROR:Test Mode\n\n", __func__, reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0xF0);
		if ((reg1 & 0x40) != 0x00) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: F0 => %x,\n+-- ERROR:SPS OCP shutdown Chip\n\n", __func__, reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0xF0);
		if ((reg1 & 0x01) != 0x01) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: F0 => %x,\n+-- ERROR:XTAL clock not stable\n\n", __func__, reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
		return cnt;
}

u32 diagnosis_SYSTEM_MAC_TXDMA(struct halmac_adapter *adapter, u32 *check_number, char *output, u32 out_len, u32 *used)
{
	struct halmac_api *api = (struct halmac_api *)adapter->halmac_api;
	u32 ret = 0;
	u32 reg1 = 0, reg2 = 0, cnt = 0;
	*check_number = 0;

		return cnt;
}

u32 diagnosis_SYSTEM_MAC_WMAC(struct halmac_adapter *adapter, u32 *check_number, char *output, u32 out_len, u32 *used)
{
	struct halmac_api *api = (struct halmac_api *)adapter->halmac_api;
	u32 ret = 0;
	u32 reg1 = 0, reg2 = 0, cnt = 0;
	*check_number = 0;

#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x1082);
		if ((reg1 & 0x01) != 0x01) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 1082 => %x,\n+-- ERROR:Reset WLAN platform\n\n", __func__, reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x1170);
		if ((reg1 & 0x01) != 0x00) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 1170 => %x,\n+-- ERROR:IO wrapper error\n\n", __func__, reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
		return cnt;
}

u32 diagnosis_TRX_HCI_PCIE(struct halmac_adapter *adapter, u32 *check_number, char *output, u32 out_len, u32 *used)
{
	struct halmac_api *api = (struct halmac_api *)adapter->halmac_api;
	u32 ret = 0;
	u32 reg1 = 0, reg2 = 0, cnt = 0;
	*check_number = 0;

#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x300);
		if ((reg1 & 0x01) != 0x00) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 300 => %x,\n+-- ERROR:(For PCIE only) Stop HI0Q DMA\n\n", __func__, reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x300);
		if ((reg1 & 0x02) != 0x00) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 300 => %x,\n+-- ERROR:(For PCIE only) Stop HI1Q DMA\n\n", __func__, reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x300);
		if ((reg1 & 0x04) != 0x00) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 300 => %x,\n+-- ERROR:(For PCIE only) Stop HI2Q DMA\n\n", __func__, reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x300);
		if ((reg1 & 0x08) != 0x00) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 300 => %x,\n+-- ERROR:(For PCIE only) Stop HI3Q DMA\n\n", __func__, reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x300);
		if ((reg1 & 0x10) != 0x00) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 300 => %x,\n+-- ERROR:(For PCIE only) Stop HI4Q DMA\n\n", __func__, reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x300);
		if ((reg1 & 0x20) != 0x00) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 300 => %x,\n+-- ERROR:(For PCIE only) Stop HI5Q DMA\n\n", __func__, reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x300);
		if ((reg1 & 0x40) != 0x00) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 300 => %x,\n+-- ERROR:(For PCIE only) Stop HI6Q DMA\n\n", __func__, reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x300);
		if ((reg1 & 0x80) != 0x00) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 300 => %x,\n+-- ERROR:(For PCIE only) Stop HI7Q DMA\n\n", __func__, reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x301);
		if ((reg1 & 0x01) != 0x00) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 301 => %x,\n+-- ERROR:(For PCIE only) RX DMA STOP\n\n", __func__, reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x301);
		if ((reg1 & 0x02) != 0x00) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 301 => %x,\n+-- ERROR:(For PCIE only) BKQ DMA STOP\n\n", __func__, reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x301);
		if ((reg1 & 0x04) != 0x00) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 301 => %x,\n+-- ERROR:(For PCIE only) BEQ DMA STOP\n\n", __func__, reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x301);
		if ((reg1 & 0x08) != 0x00) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 301 => %x,\n+-- ERROR:(For PCIE only) VIQ DMA STOP\n\n", __func__, reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x301);
		if ((reg1 & 0x10) != 0x00) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 301 => %x,\n+-- ERROR:(For PCIE only) VOQ DMA STOP\n\n", __func__, reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x301);
		if ((reg1 & 0x20) != 0x00) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 301 => %x,\n+-- ERROR:(For PCIE only) MGQ DMA STOP\n\n", __func__, reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x301);
		if ((reg1 & 0x40) != 0x00) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 301 => %x,\n+-- ERROR:(For PCIE only) BCNQ DMA STOP\n\n", __func__, reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x3A0);
		reg2 = HALMAC_REG_R8(0x3A2);
		if (((reg1 & 0xff) != (reg2 & 0xff)) && (halmac_diag_lvl > 0))
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 3A0 => %x/%x,\n+-- INFO:(For PCIE only) VOQ TXBD index dismatch\n\n", __func__, reg1, reg2);

	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x3A1);
		reg2 = HALMAC_REG_R8(0x3A3);
		if (((reg1 & 0x0f) != (reg2 & 0x0f)) && (halmac_diag_lvl > 0))
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 3A1 => %x/%x,\n+-- INFO:(For PCIE only) VOQ TXBD index dismatch\n\n", __func__, reg1, reg2);

	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x3A4);
		reg2 = HALMAC_REG_R8(0x3A6);
		if (((reg1 & 0xff) != (reg2 & 0xff)) && (halmac_diag_lvl > 0))
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 3A4 => %x/%x,\n+-- INFO:(For PCIE only) VIQ TXBD index dismatch\n\n", __func__, reg1, reg2);

	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x3A5);
		reg2 = HALMAC_REG_R8(0x3A7);
		if (((reg1 & 0x0f) != (reg2 & 0x0f)) && (halmac_diag_lvl > 0))
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 3A5 => %x/%x,\n+-- INFO:(For PCIE only) VIQ TXBD index dismatch\n\n", __func__, reg1, reg2);

	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x3A8);
		reg2 = HALMAC_REG_R8(0x3AA);
		if (((reg1 & 0xff) != (reg2 & 0xff)) && (halmac_diag_lvl > 0))
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 3A8 => %x/%x,\n+-- INFO:(For PCIE only) BEQ TXBD index dismatch\n\n", __func__, reg1, reg2);

	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x3A9);
		reg2 = HALMAC_REG_R8(0x3AB);
		if (((reg1 & 0x0f) != (reg2 & 0x0f)) && (halmac_diag_lvl > 0))
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 3A9 => %x/%x,\n+-- INFO:(For PCIE only) BEQ TXBD index dismatch\n\n", __func__, reg1, reg2);

	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x3AC);
		reg2 = HALMAC_REG_R8(0x3AE);
		if (((reg1 & 0xff) != (reg2 & 0xff)) && (halmac_diag_lvl > 0))
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 3AC => %x/%x,\n+-- INFO:(For PCIE only) BKQ TXBD index dismatch\n\n", __func__, reg1, reg2);

	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x3AD);
		reg2 = HALMAC_REG_R8(0x3AF);
		if (((reg1 & 0x0f) != (reg2 & 0x0f)) && (halmac_diag_lvl > 0))
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 3AD => %x/%x,\n+-- INFO:(For PCIE only) BKQ TXBD index dismatch\n\n", __func__, reg1, reg2);

	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x3B0);
		reg2 = HALMAC_REG_R8(0x3B2);
		if (((reg1 & 0xff) != (reg2 & 0xff)) && (halmac_diag_lvl > 0))
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 3B0 => %x/%x,\n+-- INFO:(For PCIE only) MGQ TXBD index dismatch\n\n", __func__, reg1, reg2);

	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x3B1);
		reg2 = HALMAC_REG_R8(0x3B3);
		if (((reg1 & 0x0f) != (reg2 & 0x0f)) && (halmac_diag_lvl > 0))
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 3B1 => %x/%x,\n+-- INFO:(For PCIE only) MGQ TXBD index dismatch\n\n", __func__, reg1, reg2);

	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x3B4);
		reg2 = HALMAC_REG_R8(0x3B6);
		if (((reg1 & 0xff) != (reg2 & 0xff)) && (halmac_diag_lvl > 0))
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 3B4 => %x/%x,\n+-- INFO:(For PCIE only) RXQ RXBD index dismatch\n\n", __func__, reg1, reg2);

	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x3B5);
		reg2 = HALMAC_REG_R8(0x3B7);
		if (((reg1 & 0x0f) != (reg2 & 0x0f)) && (halmac_diag_lvl > 0))
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 3B5 => %x/%x,\n+-- INFO:(For PCIE only) RXQ RXBD index dismatch\n\n", __func__, reg1, reg2);

	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x3B8);
		reg2 = HALMAC_REG_R8(0x3BA);
		if (((reg1 & 0xff) != (reg2 & 0xff)) && (halmac_diag_lvl > 0))
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 3B8 => %x/%x,\n+-- INFO:(For PCIE only) HI0Q TXBD index dismatch\n\n", __func__, reg1, reg2);

	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x3B9);
		reg2 = HALMAC_REG_R8(0x3BB);
		if (((reg1 & 0x0f) != (reg2 & 0x0f)) && (halmac_diag_lvl > 0))
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 3B9 => %x/%x,\n+-- INFO:(For PCIE only) HI0Q TXBD index dismatch\n\n", __func__, reg1, reg2);

	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x3BC);
		reg2 = HALMAC_REG_R8(0x3BE);
		if (((reg1 & 0xff) != (reg2 & 0xff)) && (halmac_diag_lvl > 0))
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 3BC => %x/%x,\n+-- INFO:(For PCIE only) HI1Q TXBD index dismatch\n\n", __func__, reg1, reg2);

	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x3BD);
		reg2 = HALMAC_REG_R8(0x3BF);
		if (((reg1 & 0x0f) != (reg2 & 0x0f)) && (halmac_diag_lvl > 0))
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 3BD => %x/%x,\n+-- INFO:(For PCIE only) HI1Q TXBD index dismatch\n\n", __func__, reg1, reg2);

	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x3C0);
		reg2 = HALMAC_REG_R8(0x3C2);
		if (((reg1 & 0xff) != (reg2 & 0xff)) && (halmac_diag_lvl > 0))
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 3C0 => %x/%x,\n+-- INFO:(For PCIE only) HI2Q TXBD index dismatch\n\n", __func__, reg1, reg2);

	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x3C1);
		reg2 = HALMAC_REG_R8(0x3C3);
		if (((reg1 & 0x0f) != (reg2 & 0x0f)) && (halmac_diag_lvl > 0))
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 3C1 => %x/%x,\n+-- INFO:(For PCIE only) HI2Q TXBD index dismatch\n\n", __func__, reg1, reg2);

	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x3C4);
		reg2 = HALMAC_REG_R8(0x3C6);
		if (((reg1 & 0xff) != (reg2 & 0xff)) && (halmac_diag_lvl > 0))
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 3C4 => %x/%x,\n+-- INFO:(For PCIE only) HI3Q TXBD index dismatch\n\n", __func__, reg1, reg2);

	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x3C5);
		reg2 = HALMAC_REG_R8(0x3C7);
		if (((reg1 & 0x0f) != (reg2 & 0x0f)) && (halmac_diag_lvl > 0))
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 3C5 => %x/%x,\n+-- INFO:(For PCIE only) HI3Q TXBD index dismatch\n\n", __func__, reg1, reg2);

	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x3C8);
		reg2 = HALMAC_REG_R8(0x3CA);
		if (((reg1 & 0xff) != (reg2 & 0xff)) && (halmac_diag_lvl > 0))
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 3C8 => %x/%x,\n+-- INFO:(For PCIE only) HI4Q TXBD index dismatch\n\n", __func__, reg1, reg2);

	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x3C9);
		reg2 = HALMAC_REG_R8(0x3CB);
		if (((reg1 & 0x0f) != (reg2 & 0x0f)) && (halmac_diag_lvl > 0))
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 3C9 => %x/%x,\n+-- INFO:(For PCIE only) HI4Q TXBD index dismatch\n\n", __func__, reg1, reg2);

	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x3CC);
		reg2 = HALMAC_REG_R8(0x3CE);
		if (((reg1 & 0xff) != (reg2 & 0xff)) && (halmac_diag_lvl > 0))
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 3CC => %x/%x,\n+-- INFO:(For PCIE only) HI5Q TXBD index dismatch\n\n", __func__, reg1, reg2);

	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x3CD);
		reg2 = HALMAC_REG_R8(0x3CF);
		if (((reg1 & 0x0f) != (reg2 & 0x0f)) && (halmac_diag_lvl > 0))
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 3CD => %x/%x,\n+-- INFO:(For PCIE only) HI5Q TXBD index dismatch\n\n", __func__, reg1, reg2);

	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x3D0);
		reg2 = HALMAC_REG_R8(0x3D2);
		if (((reg1 & 0xff) != (reg2 & 0xff)) && (halmac_diag_lvl > 0))
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 3D0 => %x/%x,\n+-- INFO:(For PCIE only) HI6Q TXBD index dismatch\n\n", __func__, reg1, reg2);

	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x3D1);
		reg2 = HALMAC_REG_R8(0x3D3);
		if (((reg1 & 0x0f) != (reg2 & 0x0f)) && (halmac_diag_lvl > 0))
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 3D1 => %x/%x,\n+-- INFO:(For PCIE only) HI6Q TXBD index dismatch\n\n", __func__, reg1, reg2);

	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x3D4);
		reg2 = HALMAC_REG_R8(0x3D6);
		if (((reg1 & 0xff) != (reg2 & 0xff)) && (halmac_diag_lvl > 0))
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 3D4 => %x/%x,\n+-- INFO:(For PCIE only) HI7Q TXBD index dismatch\n\n", __func__, reg1, reg2);

	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x3D5);
		reg2 = HALMAC_REG_R8(0x3D7);
		if (((reg1 & 0x0f) != (reg2 & 0x0f)) && (halmac_diag_lvl > 0))
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 3D5 => %x/%x,\n+-- INFO:(For PCIE only) HI7Q TXBD index dismatch\n\n", __func__, reg1, reg2);

	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R32(0x3F0);
		if ((reg1 & 0x4000000) != 0x4000000) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 3F0 => %x,\n+-- ERROR:Turn on PCIE TRX stuck interrupt\n\n", __func__, reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x3F3);
		if ((reg1 & 0x02) != 0x00) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 3F3 => %x,\n+-- ERROR:(For PCIE only) PCIE RX stuck\n\n", __func__, reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x3F3);
		if ((reg1 & 0x01) != 0x00) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 3F3 => %x,\n+-- ERROR:(For PCIE only) PCIE TX stuck\n\n", __func__, reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x3FE);
		if ((reg1 & 0x08) != 0x00) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 3FE => %x,\n+-- ERROR:(For PCIE only) PCIE page_over_err\n\n", __func__, reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x3FE);
		if ((reg1 & 0x04) != 0x00) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 3FE => %x,\n+-- ERROR:(For PCIE only) PCIE arb_err\n\n", __func__, reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x3FE);
		if ((reg1 & 0x02) != 0x00) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 3FE => %x,\n+-- ERROR:(For PCIE only) PCIE prefetch_err\n\n", __func__, reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x3FE);
		if ((reg1 & 0x01) != 0x00) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 3FE => %x,\n+-- ERROR:(For PCIE only) PCIE txqsel_err\n\n", __func__, reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
		return cnt;
}

u32 diagnosis_TRX_HCI_USB(struct halmac_adapter *adapter, u32 *check_number, char *output, u32 out_len, u32 *used)
{
	struct halmac_api *api = (struct halmac_api *)adapter->halmac_api;
	u32 ret = 0;
	u32 reg1 = 0, reg2 = 0, cnt = 0;
	*check_number = 0;

#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x288);
		if ((reg1 & 0x02) != 0x00) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 288 => %x,\n+-- ERROR:(For USB only) USB RXAGGEN error due to RX length overflow\n\n", __func__, reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
		return cnt;
}

u32 diagnosis_TRX_MAC_EDCA(struct halmac_adapter *adapter, u32 *check_number, char *output, u32 out_len, u32 *used)
{
	struct halmac_api *api = (struct halmac_api *)adapter->halmac_api;
	u32 ret = 0;
	u32 reg1 = 0, reg2 = 0, cnt = 0;
	*check_number = 0;

#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x521);
		if ((reg1 & 0x80) != 0x00) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 521 => %x,\n+-- ERROR:Disable EDCCA\n\n", __func__, reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x521);
		if ((reg1 & 0x40) != 0x00) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 521 => %x,\n+-- ERROR:Disable CCA\n\n", __func__, reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x522);
		if ((reg1 & 0x80) != 0x00) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 522 => %x,\n+-- ERROR:BCN/HI/MGT queues all stop\n\n", __func__, reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x522);
		if ((reg1 & 0x40) != 0x00) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 522 => %x,\n+-- ERROR:Stop BCNQ Queue\n\n", __func__, reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x522);
		if ((reg1 & 0x20) != 0x00) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 522 => %x,\n+-- ERROR:Stop High Queue\n\n", __func__, reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x522);
		if ((reg1 & 0x10) != 0x00) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 522 => %x,\n+-- ERROR:Stop Management Queue\n\n", __func__, reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x522);
		if ((reg1 & 0x08) != 0x00) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 522 => %x,\n+-- ERROR:Stop BK Queue\n\n", __func__, reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x522);
		if ((reg1 & 0x04) != 0x00) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 522 => %x,\n+-- ERROR:Stop BE Queue\n\n", __func__, reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x522);
		if ((reg1 & 0x02) != 0x00) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 522 => %x,\n+-- ERROR:Stop VI Queue\n\n", __func__, reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x522);
		if ((reg1 & 0x01) != 0x00) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 522 => %x,\n+-- ERROR:Stop VO Queue\n\n", __func__, reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x523);
		if ((reg1 & 0x80) != 0x00) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 523 => %x,\n+-- ERROR:Disable BT CCA\n\n", __func__, reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x550);
		if ((reg1 & 0x08) != 0x08) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 550 => %x,\n+-- ERROR:port 0 function en should be 1 to enable address (MACID0) reg and other sub-functions\n\n", __func__, reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R32(0x700);
		if (reg1 != 0) {
			reg1 = HALMAC_REG_R8(0x551);
			if (((reg1 & 0x08) != 0x08) && (halmac_diag_lvl > 0))
				MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 551 => %x,\n+-- INFO:port 1 function en should be 1 to enable address (MACID1) reg and other sub-functions\n\n", __func__, reg1);

		}
	}
#endif // End of IC compile flag
		return cnt;
}

u32 diagnosis_TRX_MAC_MACTOP(struct halmac_adapter *adapter, u32 *check_number, char *output, u32 out_len, u32 *used)
{
	struct halmac_api *api = (struct halmac_api *)adapter->halmac_api;
	u32 ret = 0;
	u32 reg1 = 0, reg2 = 0, cnt = 0;
	*check_number = 0;

#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x100);
		if ((reg1 & 0xff) != 0xff) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 100 => %x,\n+-- ERROR:Invalid MAC configuration\n\n", __func__, reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
		return cnt;
}

u32 diagnosis_TRX_MAC_PROT(struct halmac_adapter *adapter, u32 *check_number, char *output, u32 out_len, u32 *used)
{
	struct halmac_api *api = (struct halmac_api *)adapter->halmac_api;
	u32 ret = 0;
	u32 reg1 = 0, reg2 = 0, cnt = 0;
	*check_number = 0;

#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x41A);
		if (((reg1 & 0x01) != 0x01) && (halmac_diag_lvl > 0))
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 41A => %x,\n+-- INFO:AC0 queue is not empty\n\n", __func__, reg1);

	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x41A);
		if (((reg1 & 0x02) != 0x02) && (halmac_diag_lvl > 0))
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 41A => %x,\n+-- INFO:AC1 queue is not empty\n\n", __func__, reg1);

	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x41A);
		if (((reg1 & 0x04) != 0x04) && (halmac_diag_lvl > 0))
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 41A => %x,\n+-- INFO:AC2 queue is not empty\n\n", __func__, reg1);

	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x41A);
		if (((reg1 & 0x08) != 0x08) && (halmac_diag_lvl > 0))
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 41A => %x,\n+-- INFO:AC3 queue is not empty\n\n", __func__, reg1);

	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x41A);
		if (((reg1 & 0x10) != 0x10) && (halmac_diag_lvl > 0))
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 41A => %x,\n+-- INFO:AC4 queue is not empty\n\n", __func__, reg1);

	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x41A);
		if (((reg1 & 0x20) != 0x20) && (halmac_diag_lvl > 0))
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 41A => %x,\n+-- INFO:AC5 queue is not empty\n\n", __func__, reg1);

	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x41A);
		if (((reg1 & 0x40) != 0x40) && (halmac_diag_lvl > 0))
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 41A => %x,\n+-- INFO:AC6 queue is not empty\n\n", __func__, reg1);

	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x41A);
		if (((reg1 & 0x80) != 0x80) && (halmac_diag_lvl > 0))
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 41A => %x,\n+-- INFO:AC7 queue is not empty\n\n", __func__, reg1);

	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x41B);
		if (((reg1 & 0x01) != 0x01) && (halmac_diag_lvl > 0))
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 41B => %x,\n+-- INFO:MGQ queue poll by cpu queue is not empty\n\n", __func__, reg1);

	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x41B);
		if (((reg1 & 0x02) != 0x02) && (halmac_diag_lvl > 0))
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 41B => %x,\n+-- INFO:MGQ queue is not empty\n\n", __func__, reg1);

	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x41B);
		if (((reg1 & 0x04) != 0x04) && (halmac_diag_lvl > 0))
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 41B => %x,\n+-- INFO:High queue is not empty\n\n", __func__, reg1);

	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x41B);
		if (((reg1 & 0x08) != 0x08) && (halmac_diag_lvl > 0))
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 41B => %x,\n+-- INFO:Beacon queue is not empty\n\n", __func__, reg1);

	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R16(0x420);
		if (((reg1 & 0xff00) != 0xff00) && (halmac_diag_lvl > 0))
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 420 => %x,\n+-- INFO:1: HW will report tx_status 0: no report BIT0: BK Queue BIT1: BE Queue BIT2: VI Queue BIT3: VO Queue BIT4: MGT Queue BIT5: HI Queue BIT6: BCN Queue BIT7: CPU_MGT Queue\n\n", __func__, reg1);

	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x426);
		if ((reg1 & 0x20) != 0x00) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 426 => %x,\n+-- ERROR:Turning on BA parser may cause TX DMA error\n\n", __func__, reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x45C);
		if (((reg1 & 0x01) != 0x00) && (halmac_diag_lvl > 0))
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 45C => %x,\n+-- INFO:AC0 queue is stop\n\n", __func__, reg1);

	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x45C);
		if (((reg1 & 0x02) != 0x00) && (halmac_diag_lvl > 0))
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 45C => %x,\n+-- INFO:AC1 queue is stop\n\n", __func__, reg1);

	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x45C);
		if (((reg1 & 0x04) != 0x00) && (halmac_diag_lvl > 0))
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 45C => %x,\n+-- INFO:AC2 queue is stop\n\n", __func__, reg1);

	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x45C);
		if (((reg1 & 0x08) != 0x00) && (halmac_diag_lvl > 0))
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 45C => %x,\n+-- INFO:AC3 queue is stop\n\n", __func__, reg1);

	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x45C);
		if (((reg1 & 0x10) != 0x00) && (halmac_diag_lvl > 0))
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 45C => %x,\n+-- INFO:AC4 queue is stop\n\n", __func__, reg1);

	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x45C);
		if (((reg1 & 0x20) != 0x00) && (halmac_diag_lvl > 0))
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 45C => %x,\n+-- INFO:AC5 queue is stop\n\n", __func__, reg1);

	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x45C);
		if (((reg1 & 0x40) != 0x00) && (halmac_diag_lvl > 0))
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 45C => %x,\n+-- INFO:AC6 queue is stop\n\n", __func__, reg1);

	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x45C);
		if (((reg1 & 0x80) != 0x00) && (halmac_diag_lvl > 0))
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 45C => %x,\n+-- INFO:AC7 queue is stop\n\n", __func__, reg1);

	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x4E2);
		if ((reg1 & 0x80) != 0x00) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 4E2 => %x,\n+-- ERROR:In rate fallback process, but rate table is invalid\n\n", __func__, reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x4E2);
		if ((reg1 & 0x40) != 0x00) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 4E2 => %x,\n+-- ERROR:PTCL wait FTM T2R_REQ timeout\n\n", __func__, reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x4E2);
		if ((reg1 & 0x20) != 0x00) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 4E2 => %x,\n+-- ERROR:TX time over 2 sec\n\n", __func__, reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x4E2);
		if ((reg1 & 0x10) != 0x00) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 4E2 => %x,\n+-- ERROR:packet report current page is NULL\n\n", __func__, reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x4E2);
		if ((reg1 & 0x08) != 0x00) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 4E2 => %x,\n+-- ERROR:packet contention error, cause by current page is NULL\n\n", __func__, reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x4E2);
		if ((reg1 & 0x04) != 0x00) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 4E2 => %x,\n+-- ERROR:packet assign to queue, but start page is NULL\n\n", __func__, reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x4E2);
		if ((reg1 & 0x02) != 0x00) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 4E2 => %x,\n+-- ERROR:packet queue total page overflow || current page is NULL but packet queue total page not empty == overflow\n\n", __func__, reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x4E2);
		if ((reg1 & 0x01) != 0x00) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 4E2 => %x,\n+-- ERROR:packet assign queue error by queue_index = 0\n\n", __func__, reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
		return cnt;
}

u32 diagnosis_TRX_MAC_RXDMA(struct halmac_adapter *adapter, u32 *check_number, char *output, u32 out_len, u32 *used)
{
	struct halmac_api *api = (struct halmac_api *)adapter->halmac_api;
	u32 ret = 0;
	u32 reg1 = 0, reg2 = 0, cnt = 0;
	*check_number = 0;

#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x286);
		if ((reg1 & 0x04) != 0x00) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 286 => %x,\n+-- ERROR:RX DMA pause\n\n", __func__, reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x288);
		if ((reg1 & 0x80) != 0x00) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 288 => %x,\n+-- ERROR:C2H packet overflow\n\n", __func__, reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x288);
		if ((reg1 & 0x40) != 0x00) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 288 => %x,\n+-- ERROR:RX aggregation config error\n\n", __func__, reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x288);
		if ((reg1 & 0x20) != 0x00) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 288 => %x,\n+-- ERROR:FW release poll error\n\n", __func__, reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x288);
		if ((reg1 & 0x10) != 0x00) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 288 => %x,\n+-- ERROR:RX data overflow\n\n", __func__, reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x288);
		if ((reg1 & 0x08) != 0x00) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 288 => %x,\n+-- ERROR:RX Sync FIFO underflow\n\n", __func__, reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x288);
		if ((reg1 & 0x04) != 0x00) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 288 => %x,\n+-- ERROR:RX Sync FIFO overflow\n\n", __func__, reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x288);
		if ((reg1 & 0x01) != 0x00) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 288 => %x,\n+-- ERROR:There is more than 255 RX packets in FF\n\n", __func__, reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
		return cnt;
}

u32 diagnosis_TRX_MAC_SYSTEM(struct halmac_adapter *adapter, u32 *check_number, char *output, u32 out_len, u32 *used)
{
	struct halmac_api *api = (struct halmac_api *)adapter->halmac_api;
	u32 ret = 0;
	u32 reg1 = 0, reg2 = 0, cnt = 0;
	*check_number = 0;

#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0xB7);
		if ((reg1 & 0x04) != 0x00) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: B7 => %x,\n+-- ERROR:Transmit Beacon0 Error\n\n", __func__, reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0xB6);
		if ((reg1 & 0x01) != 0x00) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: B6 => %x,\n+-- ERROR:Beacon Queue DMA error0\n\n", __func__, reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0xBD);
		if ((reg1 & 0x02) != 0x00) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: BD => %x,\n+-- ERROR:TX packet buffer overflow\n\n", __func__, reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0xBD);
		if ((reg1 & 0x01) != 0x00) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: BD => %x,\n+-- ERROR:RX packet buffer overflow\n\n", __func__, reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
		return cnt;
}

u32 diagnosis_TRX_MAC_TXDMA(struct halmac_adapter *adapter, u32 *check_number, char *output, u32 out_len, u32 *used)
{
	struct halmac_api *api = (struct halmac_api *)adapter->halmac_api;
	u32 ret = 0;
	u32 reg1 = 0, reg2 = 0, cnt = 0;
	*check_number = 0;

#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x230);
		reg2 = HALMAC_REG_R8(0x232);
		if ((reg1 & 0xff) != (reg2 & 0xff)) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 230 => %x/%x,\n+-- ERROR:Reserved HPQ page number not equal to available HPQ page number\n\n", __func__, reg1, reg2);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x231);
		reg2 = HALMAC_REG_R8(0x233);
		if ((reg1 & 0x0f) != (reg2 & 0x0f)) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 231 => %x/%x,\n+-- ERROR:Reserved HPQ page number not equal to available HPQ page number\n\n", __func__, reg1, reg2);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x234);
		reg2 = HALMAC_REG_R8(0x236);
		if (((reg1 & 0xff) != (reg2 & 0xff)) && (halmac_diag_lvl > 0))
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 234 => %x/%x,\n+-- INFO:Reserved LPQ page number not equal to available LPQ page number\n\n", __func__, reg1, reg2);

	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x235);
		reg2 = HALMAC_REG_R8(0x237);
		if ((reg1 & 0x0f) != (reg2 & 0x0f)) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 235 => %x/%x,\n+-- ERROR:Reserved LPQ page number not equal to available LPQ page number\n\n", __func__, reg1, reg2);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x238);
		reg2 = HALMAC_REG_R8(0x23A);
		if ((reg1 & 0xff) != (reg2 & 0xff)) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 238 => %x/%x,\n+-- ERROR:Reserved NPQ page number not equal to available NPQ page number\n\n", __func__, reg1, reg2);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x239);
		reg2 = HALMAC_REG_R8(0x23B);
		if ((reg1 & 0x0f) != (reg2 & 0x0f)) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 239 => %x/%x,\n+-- ERROR:Reserved NPQ page number not equal to available NPQ page number\n\n", __func__, reg1, reg2);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x23C);
		reg2 = HALMAC_REG_R8(0x23E);
		if ((reg1 & 0xff) != (reg2 & 0xff)) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 23C => %x/%x,\n+-- ERROR:Reserved EXQ page number not equal to available EXQ page number\n\n", __func__, reg1, reg2);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x23D);
		reg2 = HALMAC_REG_R8(0x23F);
		if ((reg1 & 0x0f) != (reg2 & 0x0f)) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 23D => %x/%x,\n+-- ERROR:Reserved EXQ page number not equal to available EXQ page number\n\n", __func__, reg1, reg2);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x240);
		reg2 = HALMAC_REG_R8(0x242);
		if ((reg1 & 0xff) != (reg2 & 0xff)) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 240 => %x/%x,\n+-- ERROR:Reserved PUBQ page number not equal to available PUBQ page number\n\n", __func__, reg1, reg2);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x241);
		reg2 = HALMAC_REG_R8(0x243);
		if ((reg1 & 0x0f) != (reg2 & 0x0f)) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 241 => %x/%x,\n+-- ERROR:Reserved PUBQ page number not equal to available PUBQ page number\n\n", __func__, reg1, reg2);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x212);
		if ((reg1 & 0x04) != 0x00) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 212 => %x,\n+-- ERROR:Tx packet buffer request error\n\n", __func__, reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x212);
		if ((reg1 & 0x02) != 0x00) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 212 => %x,\n+-- ERROR:High priority queue TXOQT underflow\n\n", __func__, reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x212);
		if ((reg1 & 0x01) != 0x00) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 212 => %x,\n+-- ERROR:High priority queue TXOQT overflow\n\n", __func__, reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x211);
		if ((reg1 & 0x80) != 0x00) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 211 => %x,\n+-- ERROR:Payload checksum error\n\n", __func__, reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x211);
		if ((reg1 & 0x40) != 0x00) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 211 => %x,\n+-- ERROR:Payload is under the packet length of TX descriptor\n\n", __func__, reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x211);
		if ((reg1 & 0x20) != 0x00) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 211 => %x,\n+-- ERROR:Payload is over the packet length of TX descriptor\n\n", __func__, reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x211);
		if ((reg1 & 0x10) != 0x00) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 211 => %x,\n+-- ERROR:TX descriptor checksum error\n\n", __func__, reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x211);
		if ((reg1 & 0x08) != 0x00) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 211 => %x,\n+-- ERROR:An unknown QSEL of TX descriptor is detected\n\n", __func__, reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x211);
		if ((reg1 & 0x04) != 0x00) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 211 => %x,\n+-- ERROR:TX endpoint is mismatched with the QSEL of descriptor\n\n", __func__, reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x211);
		if ((reg1 & 0x02) != 0x00) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 211 => %x,\n+-- ERROR:TX offset is mismatched\n\n", __func__, reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x211);
		if ((reg1 & 0x01) != 0x00) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 211 => %x,\n+-- ERROR:TXOQT underflow\n\n", __func__, reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x210);
		if ((reg1 & 0x80) != 0x00) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 210 => %x,\n+-- ERROR:TXOQT overflow\n\n", __func__, reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x210);
		if ((reg1 & 0x40) != 0x00) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 210 => %x,\n+-- ERROR:TXDMA Sync FIFO underflow\n\n", __func__, reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x210);
		if ((reg1 & 0x20) != 0x00) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 210 => %x,\n+-- ERROR:TXDMA Sync FIFO overflow\n\n", __func__, reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x210);
		if ((reg1 & 0x10) != 0x00) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 210 => %x,\n+-- ERROR:TXDMA reads as NULL page\n\n", __func__, reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x210);
		if ((reg1 & 0x08) != 0x00) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 210 => %x,\n+-- ERROR:Total pages included PTCL un-return pages are under the total reserved pages minus the page threshold\n\n", __func__, reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x210);
		if ((reg1 & 0x04) != 0x00) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 210 => %x,\n+-- ERROR:Total pages included PTCL un-return pages are over the total reserved pages\n\n", __func__, reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x210);
		if ((reg1 & 0x02) != 0x00) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 210 => %x,\n+-- ERROR:TXFF page underflow in TDE page controller\n\n", __func__, reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x210);
		if ((reg1 & 0x01) != 0x00) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 210 => %x,\n+-- ERROR:TXFF page overflow in TDE page controller\n\n", __func__, reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x202);
		if ((reg1 & 0xff) == 0x00) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 202 => %x,\n+-- ERROR:No HPQ and EXQ free spaces\n\n", __func__, reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R8(0x200);
		if ((reg1 & 0xff) == 0x00) {
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 200 => %x,\n+-- ERROR:No NPQ and LPQ free spaces\n\n", __func__, reg1);
			cnt += 1;
		}
	}
#endif // End of IC compile flag
		return cnt;
}

u32 diagnosis_TRX_MAC_WMAC(struct halmac_adapter *adapter, u32 *check_number, char *output, u32 out_len, u32 *used)
{
	struct halmac_api *api = (struct halmac_api *)adapter->halmac_api;
	u32 ret = 0;
	u32 reg1 = 0, reg2 = 0, cnt = 0;
	*check_number = 0;

#if (HALMAC_8822E_SUPPORT)
	if (is_chip_id(adapter, HALMAC_CHIP_ID_8822E)) {
		*check_number += 1;
		reg1 = HALMAC_REG_R32(0x1118);
		reg2 = HALMAC_REG_R32(0x111C);
		if ((reg1 & 0x3ffff) != (reg2 & 0x3ffff)) {
			if (halmac_diag_lvl > 0)
				MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 1118 => %x/%x,\n+-- INFO:RX FIFO R/W pointer mismatch\n\n", __func__, reg1, reg2);
			PLTFM_DELAY_US(100*1000);
			reg2 = HALMAC_REG_R32(0x1118);
			if ((reg1 & 0x3ffff) == (reg2 & 0x3ffff)) {
				MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "func: %s, Reg: 1118 => %x,\n+-- RX FIFO R/W pointer mismatch\n\n", __func__, reg1);
				cnt += 1;
			}
		}
	}
#endif // End of IC compile flag
		return cnt;
}

u32 diagnosis_SYSTEM(struct halmac_adapter *adapter, u32 *total_check_number, char *output, u32 out_len, u32 *used)
{
	u32 cnt = 0;
	u32 check_number = 0;

#if HALMAC_PCIE_SUPPORT
	if (adapter->intf == HALMAC_INTERFACE_PCIE) {
		check_number = 0;
		cnt += diagnosis_SYSTEM_HCI_PCIE(adapter, &check_number, output, out_len, used);
		*total_check_number += check_number;
	}
#endif
#if HALMAC_USB_SUPPORT
	if (adapter->intf == HALMAC_INTERFACE_USB) {
		check_number = 0;
		cnt += diagnosis_SYSTEM_HCI_USB(adapter, &check_number, output, out_len, used);
		*total_check_number += check_number;
	}
#endif
	check_number = 0;
	cnt += diagnosis_SYSTEM_MAC_EDCA(adapter, &check_number, output, out_len, used);
	*total_check_number += check_number;
	check_number = 0;
	cnt += diagnosis_SYSTEM_MAC_MACTOP(adapter, &check_number, output, out_len, used);
	*total_check_number += check_number;
	check_number = 0;
	cnt += diagnosis_SYSTEM_MAC_PROT(adapter, &check_number, output, out_len, used);
	*total_check_number += check_number;
	check_number = 0;
	cnt += diagnosis_SYSTEM_MAC_RXDMA(adapter, &check_number, output, out_len, used);
	*total_check_number += check_number;
	check_number = 0;
	cnt += diagnosis_SYSTEM_MAC_SYSTEM(adapter, &check_number, output, out_len, used);
	*total_check_number += check_number;
	check_number = 0;
	cnt += diagnosis_SYSTEM_MAC_TXDMA(adapter, &check_number, output, out_len, used);
	*total_check_number += check_number;
	check_number = 0;
	cnt += diagnosis_SYSTEM_MAC_WMAC(adapter, &check_number, output, out_len, used);
	*total_check_number += check_number;
	if (cnt > 0) {
		MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "###############################\n");
		MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "####SYSTEM Error counter:%d####\n", cnt);
		MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "###############################\n\n");
	}

	return cnt;
}

u32 diagnosis_TRX(struct halmac_adapter *adapter, u32 *total_check_number, char *output, u32 out_len, u32 *used)
{
	u32 cnt = 0;
	u32 check_number = 0;

#if HALMAC_PCIE_SUPPORT
	if (adapter->intf == HALMAC_INTERFACE_PCIE) {
		check_number = 0;
		cnt += diagnosis_TRX_HCI_PCIE(adapter, &check_number, output, out_len, used);
		*total_check_number += check_number;
	}
#endif
#if HALMAC_USB_SUPPORT
	if (adapter->intf == HALMAC_INTERFACE_USB) {
		check_number = 0;
		cnt += diagnosis_TRX_HCI_USB(adapter, &check_number, output, out_len, used);
		*total_check_number += check_number;
	}
#endif
	check_number = 0;
	cnt += diagnosis_TRX_MAC_EDCA(adapter, &check_number, output, out_len, used);
	*total_check_number += check_number;
	check_number = 0;
	cnt += diagnosis_TRX_MAC_MACTOP(adapter, &check_number, output, out_len, used);
	*total_check_number += check_number;
	check_number = 0;
	cnt += diagnosis_TRX_MAC_PROT(adapter, &check_number, output, out_len, used);
	*total_check_number += check_number;
	check_number = 0;
	cnt += diagnosis_TRX_MAC_RXDMA(adapter, &check_number, output, out_len, used);
	*total_check_number += check_number;
	check_number = 0;
	cnt += diagnosis_TRX_MAC_SYSTEM(adapter, &check_number, output, out_len, used);
	*total_check_number += check_number;
	check_number = 0;
	cnt += diagnosis_TRX_MAC_TXDMA(adapter, &check_number, output, out_len, used);
	*total_check_number += check_number;
	check_number = 0;
	cnt += diagnosis_TRX_MAC_WMAC(adapter, &check_number, output, out_len, used);
	*total_check_number += check_number;
	if (cnt > 0) {
		MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "############################\n");
		MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "####TRX Error counter:%d####\n", cnt);
		MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "############################\n\n");
	}

	return cnt;
}

#endif //HALMAC_SELF_DIAG
#endif //HALMAC_FEATURE_DBGPKG
