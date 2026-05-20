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

#ifndef _DIAGNOSIS_AC_H_
#define _DIAGNOSIS_AC_H_

#include "halmac_api.h"

u32 diagnosis_SYSTEM_MAC_SYSTEM(struct halmac_adapter *adapter, u32 *checker_number, char *output, u32 out_len, u32 *used);
u32 diagnosis_SYSTEM_MAC_MACTOP(struct halmac_adapter *adapter, u32 *checker_number, char *output, u32 out_len, u32 *used);
u32 diagnosis_SYSTEM_MAC_TXDMA(struct halmac_adapter *adapter, u32 *checker_number, char *output, u32 out_len, u32 *used);
u32 diagnosis_SYSTEM_MAC_RXDMA(struct halmac_adapter *adapter, u32 *checker_number, char *output, u32 out_len, u32 *used);
u32 diagnosis_SYSTEM_HCI_USB(struct halmac_adapter *adapter, u32 *checker_number, char *output, u32 out_len, u32 *used);
u32 diagnosis_SYSTEM_HCI_PCIE(struct halmac_adapter *adapter, u32 *checker_number, char *output, u32 out_len, u32 *used);
u32 diagnosis_SYSTEM_MAC_PROT(struct halmac_adapter *adapter, u32 *checker_number, char *output, u32 out_len, u32 *used);
u32 diagnosis_SYSTEM_MAC_EDCA(struct halmac_adapter *adapter, u32 *checker_number, char *output, u32 out_len, u32 *used);
u32 diagnosis_SYSTEM_MAC_WMAC(struct halmac_adapter *adapter, u32 *checker_number, char *output, u32 out_len, u32 *used);
u32 diagnosis_TRX_MAC_SYSTEM(struct halmac_adapter *adapter, u32 *checker_number, char *output, u32 out_len, u32 *used);
u32 diagnosis_TRX_MAC_MACTOP(struct halmac_adapter *adapter, u32 *checker_number, char *output, u32 out_len, u32 *used);
u32 diagnosis_TRX_MAC_TXDMA(struct halmac_adapter *adapter, u32 *checker_number, char *output, u32 out_len, u32 *used);
u32 diagnosis_TRX_MAC_RXDMA(struct halmac_adapter *adapter, u32 *checker_number, char *output, u32 out_len, u32 *used);
u32 diagnosis_TRX_HCI_USB(struct halmac_adapter *adapter, u32 *checker_number, char *output, u32 out_len, u32 *used);
u32 diagnosis_TRX_HCI_PCIE(struct halmac_adapter *adapter, u32 *checker_number, char *output, u32 out_len, u32 *used);
u32 diagnosis_TRX_MAC_PROT(struct halmac_adapter *adapter, u32 *checker_number, char *output, u32 out_len, u32 *used);
u32 diagnosis_TRX_MAC_EDCA(struct halmac_adapter *adapter, u32 *checker_number, char *output, u32 out_len, u32 *used);
u32 diagnosis_TRX_MAC_WMAC(struct halmac_adapter *adapter, u32 *checker_number, char *output, u32 out_len, u32 *used);
u32 diagnosis_SYSTEM(struct halmac_adapter *adapter, u32 *total_check_number, char *output, u32 out_len, u32 *used);
u32 diagnosis_TRX(struct halmac_adapter *adapter, u32 *total_check_number, char *output, u32 out_len, u32 *used);
#endif //_DIAGNOSIS_AC_H_
