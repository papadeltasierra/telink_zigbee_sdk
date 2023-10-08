/********************************************************************************************************
 * @file    mac_internal.c
 *
 * @brief   This is the source file for mac_internal
 *
 * @author  Ghidra (Zigbee Group)
 * @date    2023
 *
 * @par     Copyright (c) 2021, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
 *          All rights reserved.
 *
 *          Licensed under the Apache License, Version 2.0 (the "License");
 *          you may not use this file except in compliance with the License.
 *          You may obtain a copy of the License at
 *
 *              http://www.apache.org/licenses/LICENSE-2.0
 *
 *          Unless required by applicable law or agreed to in writing, software
 *          distributed under the License is distributed on an "AS IS" BASIS,
 *          WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *          See the License for the specific language governing permissions and
 *          limitations under the License.
 *
 *******************************************************************************************************/

/**********************************************************************
 * INCLUDES
 */
#include "../common/includes/zb_common.h"
#include "compiler.h"


/**********************************************************************
 * LOCAL CONSTANTS
 *
 * These two drop reasons are used by the library code but not defined mac_phy.c.
 */
#define RF_DROP_REASON_INVALID_FRAME_LENGTH         0x09
#define RF_DROP_REASON_0A

/**
 *  @brief IEEE 802.15.4 Frame Control Field: Destination addressing modes
 * PDS:
 */
#define MAC_FCF_DST_ADDR_MODE_NONE      0x0000
#define MAC_FCF_DST_ADDR_MODE_SHORT     0x0800
#define MAC_FCF_DST_ADDR_MODE_LONG      0x0C00

/**
 *  @brief  IEEE 802.15.4 Frame Control Field: Source addressing modes
 * PDS:
 */
#define MAC_FCF_SRC_ADDR_MODE_NONE      0x0000
#define MAC_FCF_SRC_ADDR_MODE_SHORT     0x8000
#define MAC_FCF_SRC_ADDR_MODE_LONG      0xC000

/**
 *  @brief  MAC layer status values for 'tl_zb_mac_ctx_t'
 */
#define TL_ZM_MAC_CTX_STATUS_0 			0
#define TL_ZM_MAC_CTX_STATUS_1 			1
#define TL_ZM_MAC_CTX_STATUS_2 			2
#define TL_ZM_MAC_CTX_STATUS_3 			3
#define TL_ZM_MAC_CTX_STATUS_4 			4
#define TL_ZM_MAC_CTX_STATUS_5 			5

/**********************************************************************
 * LOCAL TYPEDEFS
 */

/**********************************************************************
 * Full packet structure appears to be:
 *
 * RF header [5]                    // Correct for TLSR8258.
 * IEEE, Zigbee data [V]
 * CRC [4]
 */
struct {
	u8 rfLength;                    // Not including CRC
	u8 _[3];						// Unknown
	u8 ieeePldLength;				// Payload length (V above)
} tl_rf_hdr_t;

/**********************************************************************
 * **CHECK**
 * Definition of an internal structure used to represent a MAC header.
 */
struct {
    u16 frameCtrl;                      // 0
    u8 infElPresent;                    // 2
    u8 srcIeeeAddrMode;                 // 3
    u8 framePending;                    // 4
    u8 seqNum;                          // 5
    u16 destPAN;                        // 6
    extAddr_t destAddr;                 // 8
    u16 destPanAgain;                   // 16
    extAddr_t srcAddr;                  // 18
} tl_mac_hdr_t;

/**********************************************************************
 * FALSE/TRUE enum to help Ghidra decompiling.
 */
// PDS: probably better elsewhere...
enum {
    FALSE;
    TRUE;
} bool_t;