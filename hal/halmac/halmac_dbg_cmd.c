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
u32 halmac_diag_lvl = 0;
static const struct mac_hal_cmd_info mac_hal_cmd_i[] = {
	{"-h", MAC_HAL_HELP, cmd_mac_help, "help"},
	/*@do not move this element to other position*/
	{"demo", MAC_HAL_DEMO, cmd_mac_demo, "demo"},

	/*for MAC Debug Command Usage*/
	{"dbg_msg_en", MAC_MAC_DBG_MSG_EN, cmd_mac_dbg_msg_en, "set foreground/background dump"},
	{"self_diag", MAC_MAC_SELF_DIAG, cmd_mac_self_diag, "self diag"},

	/*for FW Debug Command Usage*/

	/*for QC Command Usage*/

        /* QC & Test Usage*/

        /*@do not move this element to other position*/
};

u32 cmd_mac_help(struct halmac_adapter *adapter, char input[][MAC_MAX_ARGV], u32 input_num,
		 char *output, u32 out_len, u32 *used)
{
	u32 hal_cmd_ary_size = sizeof(mac_hal_cmd_i) / sizeof(struct mac_hal_cmd_info);
	u32 i;

	//PLTFM_MSG_TRACE("HAL cmd ==>\n");
	MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "HAL cmd ==>\n");
	for (i = 0; i < hal_cmd_ary_size - 1; i++) {
		//PLTFM_MSG_TRACE("	 %-5d: %s\n",
		MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "	 %-5d: %s\n",
			    i, mac_hal_cmd_i[i + 1].name);
		MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "\t\tNote: %s\n\n",
			    mac_hal_cmd_i[i + 1].description);
	}
	return MACSUCCESS;
}

u32 cmd_mac_demo(struct halmac_adapter *adapter, char input[][MAC_MAX_ARGV], u32 input_num,
		 char *output, u32 out_len, u32 *used)
{
	u32 directory = 0;
	char char_temp;
	char *ptmp;
	/*@echo demo 10 0x3a z abcde >halmac_cmd*/
	//PLTFM_MSG_TRACE("HAL cmd ==>\n");
	directory = PLTFM_STRTOUL(input[1], &ptmp, 10);
	MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "Decimal value = %d\n",
		    directory);
	directory = PLTFM_STRTOUL(input[2], &ptmp, 16);
	MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "Hex value = 0x%x\n",
		    directory);
	PLTFM_SSCANF(input[3], "%c", &char_temp);
	MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "Char = %c\n",
		    char_temp);
	MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used, "String = %s\n",
		    input[4]);

	return MACSUCCESS;
}

u32 cmd_mac_self_diag(struct halmac_adapter *adapter, char input[][MAC_MAX_ARGV], u32 input_num,
		 char *output, u32 out_len, u32 *used)
{
	u32 total_err = 0;
#if HALMAC_SELF_DIAG
	char *ptmp;
	u32 ret = 0, diag_level = 0, check_number = 0;

	if (input_num > 1) {
		diag_level = PLTFM_STRTOUL(input[1], &ptmp, 16);
		halmac_diag_lvl = diag_level;
	} else {
		halmac_diag_lvl = 0;
	}

	ret = diagnosis_SYSTEM(adapter, &check_number, output, out_len, used);
	MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used,
		    "SYSTEM Status Pass Rate %d/%d\n", check_number - ret, check_number);
	total_err += ret;

	//MAC TRX Status check
	check_number = 0;
	ret = diagnosis_TRX(adapter, &check_number, output, out_len, used);

	MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used,
		    "TRX Status Pass Rate %d/%d\n", check_number - ret, check_number);
	total_err += ret;

	MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used,
		    "self diagnosis done total err num %d\n", total_err);
#endif
	return total_err;
}

u32 cmd_mac_dbg_msg_en(struct halmac_adapter *adapter, char input[][MAC_MAX_ARGV], u32 input_num,
		 char *output, u32 out_len, u32 *used)
{
	char *ptmp;
	if (input_num != 3) {
		MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used,
			    "\ninvalid argument\n");
		return MACSTATUSFAIL;
	}

	adapter->fw_dbgcmd.dbg_console_log_en = PLTFM_STRTOUL(input[1], &ptmp, 16) ? 1 : 0;
	adapter->fw_dbgcmd.dbg_bg_log_en = PLTFM_STRTOUL(input[2], &ptmp, 16) ? 1 : 0;

	return MACSUCCESS;
}

void mac_halmac_cmd_parser(struct halmac_adapter *adapter,
			   char input[][MAC_MAX_ARGV], u32 input_num, u8 flag,
			   char *output, u32 out_len)
{
	u32 hal_cmd_ary_size = sizeof(mac_hal_cmd_i) / sizeof(struct mac_hal_cmd_info);
	u32 i = 0;
	u32 *used;
	u8 bg_log_en = 0;

	if (output) {
		adapter->fw_dbgcmd.buf = output;
		adapter->fw_dbgcmd.out_len = out_len;
		adapter->fw_dbgcmd.used = 0;
	} else {
		PLTFM_MSG_TRACE("%s invalid argument\n", __func__);
		return;
	}

	used = &adapter->fw_dbgcmd.used;
	//struct mac_ax_fwstatus_payload data;

	if (hal_cmd_ary_size == 0)
		return;

	if (flag == 0) {
		MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used,
			 "GET, nothing to print\n");
		return;
	}

	/* Parsing Cmd ID */
	if (input_num) {
		bg_log_en = adapter->fw_dbgcmd.dbg_bg_log_en;
		if (!bg_log_en)
			PLTFM_MSG_WARN("[WARN] LOG/WARN disabled due to mac cmd\n");
		adapter->fw_dbgcmd.dbg_console_log_on = adapter->fw_dbgcmd.dbg_console_log_en;
		adapter->fw_dbgcmd.dbg_bg_log_on = adapter->fw_dbgcmd.dbg_bg_log_en;
		for (i = 0; i < hal_cmd_ary_size; i++) {
			//PLTFM_MSG_TRACE("input string : %s\n, input_num = %d",
			//		input[0], input_num);
			if (PLTFM_STRCMP(mac_hal_cmd_i[i].name, input[0]) == 0) {
				//PLTFM_MSG_TRACE("enter hal dbg %s\n", mac_hal_cmd_i[i].name);
				//MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used,
				//"enter hal dbg %s\n", mac_hal_cmd_i[i].name);
				if (mac_hal_cmd_i[i].handler(adapter, input, input_num,
							     output, out_len, used)) {
					//PLTFM_MSG_TRACE("%s command process error\n",
					MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used,
						    mac_hal_cmd_i[i].name);
				}
				PLTFM_DELAY_US(1000*200);
				break;
			}
		}
		adapter->fw_dbgcmd.dbg_console_log_on = 0;
		adapter->fw_dbgcmd.dbg_bg_log_on = 1;
		if (!bg_log_en)
			PLTFM_MSG_WARN("[WARN] LOG/WARN enabled after mac cmd\n");
		if (i == hal_cmd_ary_size) {
			//PLTFM_MSG_TRACE("HAL command not found!\n");
			MAC_DBG_MSG(out_len, *used, output + *used, out_len - *used,
				    "HAL command not found!\n");
			return;
		}
	}
	PLTFM_MSG_TRACE("-----------------------%s function return\n", __func__);
}

/**
 * halmac_cmd() - halmac command
 * @adapter : the adapter of halmac
 * @input : command string input
 * @in_len : command string input length
 * @flag : 1->enable 0->disable
 * @output : output message string
 * @out_len : output message string buffer size
 * Author : Jwsyu
 * Return : enum halmac_ret_status
 * More details of status code can be found in prototype document
 */
enum halmac_ret_status
halmac_cmd(struct halmac_adapter *adapter, char *input, u32 in_len, u8 flag,
	   char *output, u32 out_len)
{
	char *token;
	u32 argc = 0;
	static char argv[MAC_MAX_ARGC][MAC_MAX_ARGV];

	do {
		token = PLTFM_STRSEP(&input, ", ");
		if (token) {
			if (PLTFM_STRLEN(token) <= MAC_MAX_ARGV)
				PLTFM_STRCPY(argv[argc], token);

			argc++;
		} else {
			break;
		}
	} while (argc < MAC_MAX_ARGC);

	if (argc == 1)
		argv[0][PLTFM_STRLEN(argv[0]) - 1] = '\0';

	mac_halmac_cmd_parser(adapter, argv, argc, flag, output, out_len);

	return HALMAC_RET_SUCCESS;
}

u32 is_chip_id(struct halmac_adapter *adapter, enum halmac_chip_id id)
{
        return (id == adapter->chip_id ? 1 : 0);
}

#else

enum halmac_ret_status
halmac_cmd(struct halmac_adapter *adapter, char *input, u32 in_len, u8 flag,
	   char *output, u32 out_len)
{
	PLTFM_MSG_WARN("[WARN] HALMAC_FEATURE_DBGPKG disabled\n");
	return HALMAC_RET_NOT_SUPPORT;
}

#endif

