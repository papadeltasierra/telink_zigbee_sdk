/********************************************************************************************************
 * @file    zcl_price.c
 *
 * @brief   This is the source file for zcl_price
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

/**********************************************************************
 * INCLUDES
 */
#include "../zcl_include.h"


#ifdef ZCL_PRICE
/**********************************************************************
 * LOCAL CONSTANTS
 */


/**********************************************************************
 * LOCAL TYPES
 */


/**********************************************************************
 * LOCAL VARIABLES
 */


/**********************************************************************
 * LOCAL FUNCTIONS
 */
static status_t zcl_price_cmdHandler(zclIncoming_t *pInMsg);


_CODE_ZCL_ status_t zcl_price_register(u8 endpoint, u16 manuCode, u8 attrNum, const zclAttrInfo_t attrTbl[], cluster_forAppCb_t cb)
{
	return zcl_registerCluster(endpoint, ZCL_CLUSTER_SE_PRICE, manuCode, attrNum, attrTbl, zcl_price_cmdHandler, cb);
}


_CODE_ZCL_ status_t zcl_price_getCurrentPrice(u8 srcEp, epInfo_t *pDstEpInfo, u8 disableDefaultRsp, u8 seqNo, zcl_price_getCurrentPriceCmd_t *pReq)
{
	u8 buf[1];
	u8 *pBuf = buf;

	*pBuf++ = pReq->commandOptions;

	return zcl_sendCmd(srcEp, pDstEpInfo, ZCL_CLUSTER_SE_PRICE, ZCL_CMD_GET_CURRENT_PRICE, TRUE,
					ZCL_FRAME_CLIENT_SERVER_DIR, disableDefaultRsp, 0, seqNo, (u8)(pBuf - buf), buf);
}

_CODE_ZCL_ status_t zcl_price_publishPrice(u8 srcEp, epInfo_t *pDstEpInfo, u8 disableDefaultRsp, u8 seqNo, zcl_price_publishPriceCmd_t *pReq)
{
	u8 buf[60];
	u8 *pBuf = buf;

    *pBuf++ = U32_BYTE0(pReq->providerId);
    *pBuf++ = U32_BYTE1(pReq->providerId);
    *pBuf++ = U32_BYTE2(pReq->providerId);
    *pBuf++ = U32_BYTE3(pReq->providerId);
    memcpy(pBuf, pReq->rateLabel,  pReq->rateLabel[0]);
    pBuf += ZCL_RATE_LABEL_MAX_LENGTH;
	*pBuf++ = U32_BYTE0(pReq->issuerEventId);
	*pBuf++ = U32_BYTE1(pReq->issuerEventId);
	*pBuf++ = U32_BYTE2(pReq->issuerEventId);
	*pBuf++ = U32_BYTE3(pReq->issuerEventId);
    *pBuf++ = U32_BYTE0(pReq->currentTime);
    *pBuf++ = U32_BYTE1(pReq->currentTime);
    *pBuf++ = U32_BYTE2(pReq->currentTime);
    *pBuf++ = U32_BYTE3(pReq->currentTime);
    *pBuf++ = pReq->unitsOfMeasure;
    *pBuf++ = U16_BYTE0(pReq->currency);
    *pBuf++ = U16_BYTE1(pReq->currency);
    *pBuf++ = pReq->priceTrailingDigitAndPriceTier;
    *pBuf++ = pReq->numPriceTiersAndRegisterTier;
    *pBuf++ = U32_BYTE0(pReq->startTime);
    *pBuf++ = U32_BYTE1(pReq->startTime);
    *pBuf++ = U32_BYTE2(pReq->startTime);
    *pBuf++ = U32_BYTE3(pReq->startTime);
    *pBuf++ = U16_BYTE0(pReq->durationInMins);
    *pBuf++ = U16_BYTE1(pReq->durationInMins);
    *pBuf++ = U32_BYTE0(pReq->price);
    *pBuf++ = U32_BYTE1(pReq->price);
    *pBuf++ = U32_BYTE2(pReq->price);
    *pBuf++ = U32_BYTE3(pReq->price);
    *pBuf++ = pReq->priceRatio;
    *pBuf++ = U32_BYTE0(pReq->generationPrice);
    *pBuf++ = U32_BYTE1(pReq->generationPrice);
    *pBuf++ = U32_BYTE2(pReq->generationPrice);
    *pBuf++ = U32_BYTE3(pReq->generationPrice);
    *pBuf++ = pReq->generationpriceRatio;
    *pBuf++ = U32_BYTE0(pReq->alternateCostDelivered);
    *pBuf++ = U32_BYTE1(pReq->alternateCostDelivered);
    *pBuf++ = U32_BYTE2(pReq->alternateCostDelivered);
    *pBuf++ = U32_BYTE3(pReq->alternateCostDelivered);
    *pBuf++ = pReq->alternateCostUnit;
    *pBuf++ = pReq->alternateCostTrailingDigit;
    *pBuf++ = pReq->numBlockThresholds;
    *pBuf++ = pReq->priceControl;
    *pBuf++ = pReq->numGenerationTiers;
    *pBuf++ = pReq->generationTier;
    *pBuf++ = pReq->extendedNumPriceTiers;
    *pBuf++ = pReq->extendedPriceTiers;
    *pBuf++ = pReq->extendedRegisterTier;

	return zcl_sendCmd(srcEp, pDstEpInfo, ZCL_CLUSTER_SE_PRICE, ZCL_CMD_PUBLISH_PRICE, TRUE,
					ZCL_FRAME_SERVER_CLIENT_DIR, disableDefaultRsp, 0, seqNo, (u8)(pBuf - buf), buf);
}

_CODE_ZCL_ static status_t zcl_price_getCurrentPricePrc(zclIncoming_t *pInMsg)
{
	u8 status = ZCL_STA_SUCCESS;

	u8 *pData = pInMsg->pData;

    if(pInMsg->clusterAppCb){
	    zcl_price_getCurrentPriceCmd_t getCurrentPriceCmd;
	    getCurrentPriceCmd.commandOptions = *pData++;

    	status = pInMsg->clusterAppCb(&(pInMsg->addrInfo), pInMsg->hdr.cmd, &getCurrentPriceCmd);
    }else{
		status = ZCL_STA_FAILURE;
	}

    return status;
}

_CODE_ZCL_ static status_t zcl_price_publishPricePrc(zclIncoming_t *pInMsg)
{
	u8 status = ZCL_STA_SUCCESS;

	u8 *pData = pInMsg->pData;

    if(pInMsg->clusterAppCb){
	    zcl_price_publishPriceCmd_t publishPriceCmd;

        publishPriceCmd.providerId = BUILD_U32(pData[0], pData[1], pData[2], pData[3]);
	    pData += 4;
        publishPriceCmd.rateLabel[0] = *pData;
        memcpy(&publishPriceCmd.rateLabel[1],  &pData[1], pData[0]);
        pData += pData[0];
        pData++;
        publishPriceCmd.issuerEventId = BUILD_U32(pData[0], pData[1], pData[2], pData[3]);
	    pData += 4;
        publishPriceCmd.currentTime = BUILD_U32(pData[0], pData[1], pData[2], pData[3]);
	    pData += 4;
        publishPriceCmd.unitsOfMeasure = *pData++;
        publishPriceCmd.currency = BUILD_U16(pData[0], pData[1]);
	    pData += 2;
        publishPriceCmd.priceTrailingDigitAndPriceTier = *pData++;
        publishPriceCmd.numPriceTiersAndRegisterTier = *pData++;
        publishPriceCmd.startTime = BUILD_U32(pData[0], pData[1], pData[2], pData[3]);
	    pData += 4;
        publishPriceCmd.durationInMins = BUILD_U16(pData[0], pData[1]);
	    pData += 2;
        publishPriceCmd.price = BUILD_U32(pData[0], pData[1], pData[2], pData[3]);
	    pData += 4;
        publishPriceCmd.priceRatio = *pData++;
        publishPriceCmd.generationPrice = BUILD_U32(pData[0], pData[1], pData[2], pData[3]);
	    pData += 4;
        publishPriceCmd.generationpriceRatio = *pData++;
        publishPriceCmd.alternateCostDelivered = BUILD_U32(pData[0], pData[1], pData[2], pData[3]);
	    pData += 4;
        publishPriceCmd.alternateCostUnit = *pData++;
        publishPriceCmd.alternateCostTrailingDigit = *pData++;
        publishPriceCmd.numBlockThresholds = *pData++;
        publishPriceCmd.priceControl = *pData++;
        publishPriceCmd.numGenerationTiers = *pData++;
        publishPriceCmd.generationTier = *pData++;
        publishPriceCmd.extendedNumPriceTiers = *pData++;
        publishPriceCmd.extendedPriceTiers = *pData++;
        publishPriceCmd.extendedRegisterTier = *pData++;

    	status = pInMsg->clusterAppCb(&(pInMsg->addrInfo), pInMsg->hdr.cmd, &publishPriceCmd);
    }else{
		status = ZCL_STA_FAILURE;
	}

    return status;
}

_CODE_ZCL_ static status_t zcl_price_clientCmdHandler(zclIncoming_t *pInMsg)
{
	u8 status = ZCL_STA_SUCCESS;

	switch(pInMsg->hdr.cmd){
		case ZCL_CMD_PUBLISH_PRICE:
			status = zcl_price_publishPricePrc(pInMsg);
			break;
		default:
			status = ZCL_STA_UNSUP_CLUSTER_COMMAND;
			break;
	}

	return status;
}

_CODE_ZCL_ static status_t zcl_price_serverCmdHandler(zclIncoming_t *pInMsg)
{
	u8 status = ZCL_STA_SUCCESS;

	switch(pInMsg->hdr.cmd){
		case ZCL_CMD_GET_CURRENT_PRICE:
			status = zcl_price_getCurrentPricePrc(pInMsg);
			break;
		default:
			status = ZCL_STA_UNSUP_CLUSTER_COMMAND;
			break;
	}

	return status;
}

_CODE_ZCL_ static status_t zcl_price_cmdHandler(zclIncoming_t *pInMsg)
{
	if(pInMsg->hdr.frmCtrl.bf.dir == ZCL_FRAME_CLIENT_SERVER_DIR){
		return zcl_price_clientCmdHandler(pInMsg);
	}else{
		return zcl_price_serverCmdHandler(pInMsg);
	}
}

#endif  /* ZCL_PRICE */
