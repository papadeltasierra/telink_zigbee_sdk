/********************************************************************************************************
 * @file    zcl_price.h
 *
 * @brief   This is the header file for zcl_price
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

#ifndef ZCL_PRICE_H
#define ZCL_PRICE_H


/*
 * Only as much support as is required for CloudSMETS is provided below.
 */

/*********************************************************************
 * CONSTANTS
 */
/**
 *  @brief	Attribute Sets
 */
#define TIER_LABEL_DELIVERED									0x00

/**
 *  @brief	SE price Attribute IDs
 */
//Reading Information Set
#define ZCL_ATTRID_TIER1_PRICE_LABEL                        	0x0000

/**
 *  @brief	SE price command IDs
 */
//Server commands
// Commands received.
#define ZCL_CMD_GET_CURRENT_PRICE                               0x00

// Commands generated.
#define ZCL_CMD_PUBLISH_PRICE									0x00

/**
 *  @brief	Format of the Get Current Price command
 */

enum {
    CMD_OPT_REQUESTOR_RX_ON_IDLE = 0x01
} zcl_commandOptions_t;

typedef struct
{
    u8          commandOptions;
} zcl_price_getCurrentPriceCmd_t;

/**
 *  @brief	Format of the Publish Price command
 */
#define ZCL_RATE_LABEL_MAX_LENGTH       13

enum {
    UOM_KWH_OR_KW               = 0x00,
    UOM_M3_OR_M3_PH             = 0x01,
    UOM_FT3_OR_FT3_PH           = 0x02,
    UOM_CCF_OR_CCF_PH           = 0x03,
    UOM_USGAL_OR_USGAL_PH       = 0x04,
    UOM_IMPGAL_OR_IMPGAL_PH     = 0x05,
    UMM_BTU_OR_BUT_PH           = 0x06,
    UOM_LITER_OR_LITER_PH       = 0x07,
    UOM_KPA_GUAGE               = 0x08,
    UOM_KPA_ABSOLUTE            = 0x09,
    UOM_MCF_OR_MCF_PH           = 0x0A,
    UOM_UNITLESS                = 0x0B,
    UOM_MJ_OR_MW                = 0x0C,
    UOM_KVAR_OR_KVARH           = 0x0D
} zcl_unitsOfMeasure_t;

enum {
    PTDPT_NO_TIER_RELATED       = 0x00,
    PTDPT_TIER1_PRICE_LABEL     = 0x01,
    PTDPT_TIER2_PRICE_LABEL     = 0x02,
    PTDPT_TIER3_PRICE_LABEL     = 0x03,
    PTDPT_TIER4_PRICE_LABEL     = 0x04,
    PTDPT_TIER5_PRICE_LABEL     = 0x05,
    PTDPT_TIER6_PRICE_LABEL     = 0x06,
    PTDPT_TIER7_PRICE_LABEL     = 0x07,
    PTDPT_TIER8_PRICE_LABEL     = 0x08,
    PTDPT_TIER9_PRICE_LABEL     = 0x09,
    PTDPT_TIER10_PRICE_LABEL    = 0x0A,
    PTDPT_TIER11_PRICE_LABEL    = 0x0B,
    PTDPT_TIER12_PRICE_LABEL    = 0x0C,
    PTDPT_TIER13_PRICE_LABEL    = 0x0D,
    PTDPT_TIER14_PRICE_LABEL    = 0x0E,
    PTDPT_DEL_EXTND_PRICE_TIER  = 0x0F
} zcl_priceTailingDigitAndPriceTier_t;

enum {
    REG_TIERS_NO_TIER_RELATED                       = 0x0,
    REG_TIERS_ACC_CURRENTTIER1SUMMATIONDELIVERED    = 0x1,
    REG_TIERS_ACC_CURRENTTIER2SUMMATIONDELIVERED    = 0x2,
    REG_TIERS_ACC_CURRENTTIER3SUMMATIONDELIVERED    = 0x3,
    REG_TIERS_ACC_CURRENTTIER4SUMMATIONDELIVERED    = 0x4,
    REG_TIERS_ACC_CURRENTTIER5SUMMATIONDELIVERED    = 0x5,
    REG_TIERS_ACC_CURRENTTIER6SUMMATIONDELIVERED    = 0x6,
    REG_TIERS_ACC_CURRENTTIER7SUMMATIONDELIVERED    = 0x7,
    REG_TIERS_ACC_CURRENTTIER8SUMMATIONDELIVERED    = 0x8,
    REG_TIERS_ACC_CURRENTTIER9SUMMATIONDELIVERED    = 0x9,
    REG_TIERS_ACC_CURRENTTIER10SUMMATIONDELIVERED   = 0xA,
    REG_TIERS_ACC_CURRENTTIER11SUMMATIONDELIVERED   = 0xB,
    REG_TIERS_ACC_CURRENTTIER12SUMMATIONDELIVERED   = 0xC,
    REG_TIERS_ACC_CURRENTTIER13SUMMATIONDELIVERED   = 0xD,
    REG_TIERS_ACC_CURRENTTIER14SUMMATIONDELIVERED   = 0xE,
    REG_TIERS_DEP_EXTND_REGISTER_TIER               = 0xF
} zcl_registerTiers_t;

typedef struct {
    u8 priceTiers: 4;
    u8 registerTiers: 4;
} zcl_numPriceTiersAndRegisterTiers_t;

enum {
    ALT_COST_UNIT_KG_CO2    = 0x01
} zcl_alternativeCostUnit_t;

typedef struct {
    u8 righOfDecimal: 4;
    u8 reserved: 4;
} zcl_trailingDigit_t;

#define ZCL_TRAILING_DIGIT_UNUSED 0xFF

typedef struct {
    u8 priceAckRequired: 1;
    u8 totalTiersExceeds15: 1;
    u8 reserved: 6;
} zcl_priceControl_t;

#define PRICE_CONTROL_ACKNOWLEDGEMENT_NOT_REQUIRED  0
#define PRICE_CONTROL_ACKNOWLEDGEMENT_REQUIRED      1
#define TOTAL_TIERS_DOES_NOT_EXCEED_15              0
#define TOTAL_TIERS_EXCEEDS_15                      1

enum {
    GEN_TIER_ACC_CURRENTTIER1SUMMATIONRECEIVED      = 0x01,
    GEN_TIER_ACC_CURRENTTIER2SUMMATIONRECEIVED      = 0x02,
    GEN_TIER_ACC_CURRENTTIER3SUMMATIONRECEIVED      = 0x03,
    GEN_TIER_ACC_CURRENTTIER4SUMMATIONRECEIVED      = 0x04,
    GEN_TIER_ACC_CURRENTTIER5SUMMATIONRECEIVED      = 0x05,
    GEN_TIER_ACC_CURRENTTIER6SUMMATIONRECEIVED      = 0x06,
    GEN_TIER_ACC_CURRENTTIER7SUMMATIONRECEIVED      = 0x07,
    GEN_TIER_ACC_CURRENTTIER8SUMMATIONRECEIVED      = 0x08,
    GEN_TIER_ACC_CURRENTTIER9SUMMATIONRECEIVED      = 0x09,
    GEN_TIER_ACC_CURRENTTIER10SUMMATIONRECEIVED     = 0x0A,
    GEN_TIER_ACC_CURRENTTIER11SUMMATIONRECEIVED     = 0x0B,
    GEN_TIER_ACC_CURRENTTIER12SUMMATIONRECEIVED     = 0x0C,
    GEN_TIER_ACC_CURRENTTIER13SUMMATIONRECEIVED     = 0x0D,
    GEN_TIER_ACC_CURRENTTIER14SUMMATIONRECEIVED     = 0x0E,
    GEN_TIER_ACC_CURRENTTIER15SUMMATIONRECEIVED     = 0x0F,
    GEN_TIER_ACC_CURRENTTIER16SUMMATIONRECEIVED     = 0x10,
    GEN_TIER_ACC_CURRENTTIER17SUMMATIONRECEIVED     = 0x11,
    GEN_TIER_ACC_CURRENTTIER18SUMMATIONRECEIVED     = 0x12,
    GEN_TIER_ACC_CURRENTTIER19SUMMATIONRECEIVED     = 0x13,
    GEN_TIER_ACC_CURRENTTIER20SUMMATIONRECEIVED     = 0x14,
    GEN_TIER_ACC_CURRENTTIER21SUMMATIONRECEIVED     = 0x15,
    GEN_TIER_ACC_CURRENTTIER22SUMMATIONRECEIVED     = 0x16,
    GEN_TIER_ACC_CURRENTTIER23SUMMATIONRECEIVED     = 0x17,
    GEN_TIER_ACC_CURRENTTIER24SUMMATIONRECEIVED     = 0x18,
    GEN_TIER_ACC_CURRENTTIER25SUMMATIONRECEIVED     = 0x19,
    GEN_TIER_ACC_CURRENTTIER26SUMMATIONRECEIVED     = 0x1A,
    GEN_TIER_ACC_CURRENTTIER27SUMMATIONRECEIVED     = 0x1B,
    GEN_TIER_ACC_CURRENTTIER28SUMMATIONRECEIVED     = 0x1C,
    GEN_TIER_ACC_CURRENTTIER29SUMMATIONRECEIVED     = 0x1D,
    GEN_TIER_ACC_CURRENTTIER30SUMMATIONRECEIVED     = 0x1E,
    GEN_TIER_ACC_CURRENTTIER31SUMMATIONRECEIVED     = 0x1F,
    GEN_TIER_ACC_CURRENTTIER32SUMMATIONRECEIVED     = 0x20,
    GEN_TIER_ACC_CURRENTTIER33SUMMATIONRECEIVED     = 0x21,
    GEN_TIER_ACC_CURRENTTIER34SUMMATIONRECEIVED     = 0x22,
    GEN_TIER_ACC_CURRENTTIER35SUMMATIONRECEIVED     = 0x23,
    GEN_TIER_ACC_CURRENTTIER36SUMMATIONRECEIVED     = 0x24,
    GEN_TIER_ACC_CURRENTTIER37SUMMATIONRECEIVED     = 0x25,
    GEN_TIER_ACC_CURRENTTIER38SUMMATIONRECEIVED     = 0x26,
    GEN_TIER_ACC_CURRENTTIER39SUMMATIONRECEIVED     = 0x27,
    GEN_TIER_ACC_CURRENTTIER40SUMMATIONRECEIVED     = 0x28,
    GEN_TIER_ACC_CURRENTTIER41SUMMATIONRECEIVED     = 0x29,
    GEN_TIER_ACC_CURRENTTIER42SUMMATIONRECEIVED     = 0x2A,
    GEN_TIER_ACC_CURRENTTIER43SUMMATIONRECEIVED     = 0x2B,
    GEN_TIER_ACC_CURRENTTIER44SUMMATIONRECEIVED     = 0x2C,
    GEN_TIER_ACC_CURRENTTIER45SUMMATIONRECEIVED     = 0x2D,
    GEN_TIER_ACC_CURRENTTIER46SUMMATIONRECEIVED     = 0x2E,
    GEN_TIER_ACC_CURRENTTIER47SUMMATIONRECEIVED     = 0x2F,
    GEN_TIER_ACC_CURRENTTIER48SUMMATIONRECEIVED     = 0x30
} zcl_generationTier_t;

enum {
    EXTND_PRICE_TIER_PRICE_TIER_SUBFIELD  = 0x00,
    EXTND_PRICE_TIER_TIER_16_PRICE_LABEL  = 0X01,
    EXTND_PRICE_TIER_TIER_17_PRICE_LABEL  = 0X02,
    EXTND_PRICE_TIER_TIER_18_PRICE_LABEL  = 0X03,
    EXTND_PRICE_TIER_TIER_19_PRICE_LABEL  = 0X04,
    EXTND_PRICE_TIER_TIER_20_PRICE_LABEL  = 0X05,
    EXTND_PRICE_TIER_TIER_21_PRICE_LABEL  = 0X06,
    EXTND_PRICE_TIER_TIER_22_PRICE_LABEL  = 0X07,
    EXTND_PRICE_TIER_TIER_23_PRICE_LABEL  = 0X08,
    EXTND_PRICE_TIER_TIER_24_PRICE_LABEL  = 0X09,
    EXTND_PRICE_TIER_TIER_25_PRICE_LABEL  = 0X0A,
    EXTND_PRICE_TIER_TIER_26_PRICE_LABEL  = 0X0B,
    EXTND_PRICE_TIER_TIER_27_PRICE_LABEL  = 0X0C,
    EXTND_PRICE_TIER_TIER_28_PRICE_LABEL  = 0X0D,
    EXTND_PRICE_TIER_TIER_29_PRICE_LABEL  = 0X0E,
    EXTND_PRICE_TIER_TIER_30_PRICE_LABEL  = 0X0F,
    EXTND_PRICE_TIER_TIER_31_PRICE_LABEL  = 0X10,
    EXTND_PRICE_TIER_TIER_32_PRICE_LABEL  = 0X11,
    EXTND_PRICE_TIER_TIER_33_PRICE_LABEL  = 0X12,
    EXTND_PRICE_TIER_TIER_34_PRICE_LABEL  = 0X13,
    EXTND_PRICE_TIER_TIER_35_PRICE_LABEL  = 0X14,
    EXTND_PRICE_TIER_TIER_36_PRICE_LABEL  = 0X15,
    EXTND_PRICE_TIER_TIER_37_PRICE_LABEL  = 0X16,
    EXTND_PRICE_TIER_TIER_38_PRICE_LABEL  = 0X17,
    EXTND_PRICE_TIER_TIER_39_PRICE_LABEL  = 0X18,
    EXTND_PRICE_TIER_TIER_40_PRICE_LABEL  = 0X19,
    EXTND_PRICE_TIER_TIER_41_PRICE_LABEL  = 0X1A,
    EXTND_PRICE_TIER_TIER_42_PRICE_LABEL  = 0X1B,
    EXTND_PRICE_TIER_TIER_43_PRICE_LABEL  = 0X1C,
    EXTND_PRICE_TIER_TIER_44_PRICE_LABEL  = 0X1D,
    EXTND_PRICE_TIER_TIER_45_PRICE_LABEL  = 0X1E,
    EXTND_PRICE_TIER_TIER_46_PRICE_LABEL  = 0X1F,
    EXTND_PRICE_TIER_TIER_47_PRICE_LABEL  = 0X20,
    EXTND_PRICE_TIER_TIER_48_PRICE_LABEL  = 0X21
} zcl_extendedPriceTier_t;

/*
 * The Extended number of price tiers is either none of a number indicated by
 * the value of the field.  So a value of 6 indicates that the standard number
 * of tiers (15) is available plus another 6 so tiers 16-21 also exist.
 */
#define EXTND_NUM_PRICE_TIERS_NONE      0
#define EXTND_NUM_PRICE_TIERS_MIN       1
#define EXTND_NUM_PRICE_TIERS_MAX       33

enum {
    EXTND_REGISTER_TIER_REGISTER_TIER_SUBFIELD             = 0X00,
    EXTND_REGISTER_TIER_CURRENT_TIER16_SUMMATION_DELIVERED = 0X01,
    EXTND_REGISTER_TIER_CURRENT_TIER17_SUMMATION_DELIVERED = 0X02,
    EXTND_REGISTER_TIER_CURRENT_TIER18_SUMMATION_DELIVERED = 0X03,
    EXTND_REGISTER_TIER_CURRENT_TIER19_SUMMATION_DELIVERED = 0X04,
    EXTND_REGISTER_TIER_CURRENT_TIER20_SUMMATION_DELIVERED = 0X05,
    EXTND_REGISTER_TIER_CURRENT_TIER21_SUMMATION_DELIVERED = 0X06,
    EXTND_REGISTER_TIER_CURRENT_TIER22_SUMMATION_DELIVERED = 0X07,
    EXTND_REGISTER_TIER_CURRENT_TIER23_SUMMATION_DELIVERED = 0X08,
    EXTND_REGISTER_TIER_CURRENT_TIER24_SUMMATION_DELIVERED = 0X09,
    EXTND_REGISTER_TIER_CURRENT_TIER25_SUMMATION_DELIVERED = 0X0A,
    EXTND_REGISTER_TIER_CURRENT_TIER26_SUMMATION_DELIVERED = 0X0B,
    EXTND_REGISTER_TIER_CURRENT_TIER27_SUMMATION_DELIVERED = 0X0C,
    EXTND_REGISTER_TIER_CURRENT_TIER28_SUMMATION_DELIVERED = 0X0D,
    EXTND_REGISTER_TIER_CURRENT_TIER29_SUMMATION_DELIVERED = 0X0E,
    EXTND_REGISTER_TIER_CURRENT_TIER30_SUMMATION_DELIVERED = 0X0F,
    EXTND_REGISTER_TIER_CURRENT_TIER31_SUMMATION_DELIVERED = 0X10,
    EXTND_REGISTER_TIER_CURRENT_TIER32_SUMMATION_DELIVERED = 0X11,
    EXTND_REGISTER_TIER_CURRENT_TIER33_SUMMATION_DELIVERED = 0X12,
    EXTND_REGISTER_TIER_CURRENT_TIER34_SUMMATION_DELIVERED = 0X13,
    EXTND_REGISTER_TIER_CURRENT_TIER35_SUMMATION_DELIVERED = 0X14,
    EXTND_REGISTER_TIER_CURRENT_TIER36_SUMMATION_DELIVERED = 0X15,
    EXTND_REGISTER_TIER_CURRENT_TIER37_SUMMATION_DELIVERED = 0X16,
    EXTND_REGISTER_TIER_CURRENT_TIER38_SUMMATION_DELIVERED = 0X17,
    EXTND_REGISTER_TIER_CURRENT_TIER39_SUMMATION_DELIVERED = 0X18,
    EXTND_REGISTER_TIER_CURRENT_TIER40_SUMMATION_DELIVERED = 0X19,
    EXTND_REGISTER_TIER_CURRENT_TIER41_SUMMATION_DELIVERED = 0X1A,
    EXTND_REGISTER_TIER_CURRENT_TIER42_SUMMATION_DELIVERED = 0X1B,
    EXTND_REGISTER_TIER_CURRENT_TIER43_SUMMATION_DELIVERED = 0X1C,
    EXTND_REGISTER_TIER_CURRENT_TIER44_SUMMATION_DELIVERED = 0X1D,
    EXTND_REGISTER_TIER_CURRENT_TIER45_SUMMATION_DELIVERED = 0X1E,
    EXTND_REGISTER_TIER_CURRENT_TIER46_SUMMATION_DELIVERED = 0X1F,
    EXTND_REGISTER_TIER_CURRENT_TIER47_SUMMATION_DELIVERED = 0X20,
    EXTND_REGISTER_TIER_CURRENT_TIER48_SUMMATION_DELIVERED = 0X21
} zcl_extendedRegisterTier_t;

/* D.4.2.4.1 */
typedef struct {
    u32         providerId;
    u8          rateLabel[ZCL_RATE_LABEL_MAX_LENGTH];
	u32         issuerEventId;
    UTCTime     currentTime;
    u8          unitsOfMeasure;
    u16         currency;
    u8          priceTrailingDigitAndPriceTier;
    u8          numPriceTiersAndRegisterTier;
    UTCTime     startTime;
    u16         durationInMins;
    u32         price;
    u8          priceRatio;
    u32         generationPrice;
    u8          generationpriceRatio;
    u32         alternateCostDelivered;
    u8          alternateCostUnit;
    u8          alternateCostTrailingDigit;
    u8          numBlockThresholds;
    u8          priceControl;
    u8          numGenerationTiers;
    u8          generationTier;
    u8          extendedNumPriceTiers;
    u8          extendedPriceTiers;
    u8          extendedRegisterTier;
} zcl_price_publishPriceCmd_t;


status_t zcl_price_register(u8 endpoint, u16 manuCode, u8 attrNum, const zclAttrInfo_t attrTbl[], cluster_forAppCb_t cb);

/* Commands received */
status_t zcl_price_getCurrentPrice(u8 srcEp, epInfo_t *pDstEpInfo, u8 disableDefaultRsp, u8 seqNo, zcl_price_getCurrentPriceCmd_t *pReq);
#define zcl_price_getCurrentPriceCmd(a,b,c,d)	(zcl_price_getCurrentPrice((a), (b), (c), ZCL_SEQ_NUM, (d)))

/* Commands sent */
status_t zcl_price_publishPrice(u8 srcEp, epInfo_t *pDstEpInfo, u8 disableDefaultRsp, u8 seqNo, zcl_price_publishPriceCmd_t *pReq);
#define zcl_price_publishPriceCmd(a,b,c,d)	(zcl_price_publishPrice((a), (b), (c), ZCL_SEQ_NUM, (d)))

#endif	/* ZCL_PRICE_H */