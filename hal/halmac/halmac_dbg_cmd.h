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

#ifndef _HALMAC_DBG_CMD_H_
#define _HALMAC_DBG_CMD_H_

#include "halmac_api.h"
/*--------------------Define MACRO--------------------------------------*/

#define MAC_MAX_ARGC		20
#define MAC_MAX_ARGV		16

#define MACSUCCESS	0  /* Success return value */
#define MACSTATUSFAIL	-1 /* fail return value */

#define PLTFM_SNPRINTF(buf, size, fmt, ...)				\
	snprintf(buf, size, fmt, ##__VA_ARGS__)
#define PLTFM_STRCMP(s1, s2)    strcmp(s1, s2)
#define PLTFM_STRTOUL(cp, endp, base)					\
	simple_strtoul(cp, endp, base)
#define PLTFM_STRSEP(s, ct)						\
	strsep(s, ct)
#define PLTFM_STRLEN(s)							\
	strlen(s)
#define PLTFM_STRCPY(dest, src)						\
	strcpy(dest, src)
#define PLTFM_SSCANF(buf, ...) sscanf(buf, ##__VA_ARGS__)

#define	MAC_DBG_MSG(max_buff_len, used_len, buff_addr, remain_len, fmt, ...)\
	do {									\
		u32 *used_len_tmp = &(used_len);				\
		PLTFM_MUTEX_LOCK(&adapter->lock_info.fw_dbgcmd_lock);			\
		if (*used_len_tmp < max_buff_len)				\
			*used_len_tmp += PLTFM_SNPRINTF(buff_addr, remain_len, fmt, ##__VA_ARGS__);\
		PLTFM_MUTEX_UNLOCK(&adapter->lock_info.fw_dbgcmd_lock);			\
	} while (0)

/*--------------------Define Enum---------------------------------------*/
enum mac_hal_cmd_id {
	MAC_HAL_HELP = 0,
	MAC_HAL_DEMO,
	MAC_MAC_DBG_MSG_EN,
	MAC_MAC_SELF_DIAG,
	MAC_MAX_CMD_ID,
};

/*--------------------Define Struct-------------------------------------*/

struct mac_hal_cmd_info {
	char name[16];
	u16 id;
	u32 (*handler)(struct halmac_adapter *adapter, char input[][MAC_MAX_ARGV],
		       u32 input_num, char *output, u32 out_len, u32 *used);
	char description[256];
};

enum halmac_ret_status
halmac_cmd(struct halmac_adapter *adapter, char *input, u32 in_len,
	   u8 flag, char *output, u32 out_len);

#if HALMAC_FEATURE_DBGPKG
void mac_halmac_cmd_parser(struct halmac_adapter *adapter,
			   char input[][MAC_MAX_ARGV], u32 input_num, u8 flag,
			   char *output, u32 out_len);

u32 cmd_mac_help(struct halmac_adapter *adapter, char input[][MAC_MAX_ARGV], u32 input_num,
		 char *output, u32 out_len, u32 *used);

u32 cmd_mac_demo(struct halmac_adapter *adapter, char input[][MAC_MAX_ARGV], u32 input_num,
		 char *output, u32 out_len, u32 *used);

u32 cmd_mac_dbg_msg_en(struct halmac_adapter *adapter, char input[][MAC_MAX_ARGV], u32 input_num,
		       char *output, u32 out_len, u32 *used);

u32 cmd_mac_self_diag(struct halmac_adapter *adapter, char input[][MAC_MAX_ARGV], u32 input_num,
		      char *output, u32 out_len, u32 *used);

u32 is_chip_id(struct halmac_adapter *adapter, enum halmac_chip_id id);

#endif /* HALMAC_FEATURE_DBGPKG */
#endif
