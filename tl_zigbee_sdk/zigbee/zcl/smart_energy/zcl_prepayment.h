/********************************************************************************************************
 * @file    zcl_prepayment.h
 *
 * @brief   This is the header file for zcl_metering
 *
 * @author  Zigbee Group
 * @date    2021
 *
 * @par     Copyright (c) 2021, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
 *          All rights reserved.
 *
 *          Portions Copyright (c) 2023, Paul D.Smith.
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

#ifndef ZCL_PREPAYMENT_H


/*
 * Only as much support as is required for CloudSMETS is provided below.
 */

/*********************************************************************
 * CONSTANTS
 */
/**
 *  @brief	Attribute Sets
 */
#define PREPAYMENT_INFORMATION_SET								0x00
#define DEBT_ATTRIBUTE_SET										0x02
#define HISTORICAL_COST_CONSUMPTION_INFO_SET                    0x05

/**
 *  @brief	Prepayment cluster Attribute IDs
 */
//Prepayment Information Set
#define ZCL_ATTRID_CREDIT_REMAINING                          	0x0001
//Debt Attribute Set
#define ZCL_ATTRID_DEBT_LABEL1                      			0x0210
//Historical Cost Consumption Information Set
#define ZCL_ATTRID_CURRENCY										0x0503

#define ZCL_DEBT_LABEL1_MAX_LENGTH      13
/**
 *  @brief	There are no prepayment commands supported.
 */

status_t zcl_prepayment_register(u8 endpoint, u16 manuCode, u8 attrNum, const zclAttrInfo_t attrTbl[], cluster_forAppCb_t cb);

#endif	/* ZCL_PREPAYMENT_H */
