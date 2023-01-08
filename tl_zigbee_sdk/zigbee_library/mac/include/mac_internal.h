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
#define RF_DROP_REASON_0A					        0x0a

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
