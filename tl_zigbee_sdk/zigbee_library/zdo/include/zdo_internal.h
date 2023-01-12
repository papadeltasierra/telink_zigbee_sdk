* INCLUDES
 */
#include "../common/includes/zb_common.h"
#include "compiler.h"


/**********************************************************************
 * LOCAL CONSTANTS
 *
 */


/**********************************************************************
 * LOCAL TYPEDEFS
 */
enum {
    mainQueue,
    nwkFromMacTblQueue,
    nwkTaskQueue,
    nwkFromHighTblQueue
} tl_zb_taskList_e;

/**********************************************************************
 * GLOBAL VARIABLES
 */
typedef (void *)(*tl_zbEventHandler_t)(void *);
struct {
    u8 primitive;
    tl_zbEventHandler_t eventHandler;
} g_zbNwkEventTbl_t;

// These tables are almost certainly different for the end-device library.

// The IDs below are the Network layer primitive id e.g. NWK_NLME_LEAVE_REQ

g_zbNwkEventTbl_t g_zbNwkEventFromHighTbl[] =
{
    { 0x70, tl_zbNwkNldeDataRequestHandler },
    { 0x73, tl_zbNwkNlmeNwkDiscRequestHandler },
    { 0x75, tl_zbNwkNlmeNetworkFormationRequestHandler },
    { 0x77, tl_zbNwkNlmePermitJoiningRequestHandler },
    { 0x79, tl_zbNwkNlmeStartRouterRequestHandler },
    { 0x7b, tl_zbNwkNlmeEDScanRequestHandler },
    { 0x7d, tl_zbNwkNlmeJoinRequestHandler },
    { 0x80, tl_zbNwkNlmeDirectJoinRequestHandler },
    { 0x82, tl_zbNwkNlmeLeaveRequestHandler },
    { 0x85, tl_zbNwkNlmeResetRequestHandler },
    { 0x8f, tl_zbNwkNlmeRouteDiscRequestHandler }
};
#define ZB_NWK_EVENT_FROM_HIGH_TBL_SIZE \
    (sizeof(g_zbNwkEventFromHighTbl)/sizeof(g_zbNwkEventTbl_t))

// The IDs below are the MAC primitive IDs e.g. MAC_MLME_POLL_IND

g_zbNwkEventTbl_t g_zbNwkEventFromMacTbl[] =
{
    { 0x41, tl_zbMacMcpsDataConfirmHandler },
    { 0x42, tl_zbMacMcpsDataIndicationHandler },
    { 0x46, tl_zbMacMlmeAssociateConfirmHandler },
    { 0x47, tl_zbMacMlmeAssociateIndicationHandler },
    { 0x4c, tl_zbMacMlmeBeaconNotifyIndicationHandler },
    { 0x4f, tl_zbMacMlmeOrphanIndicationHandler },
    { 0x52, tl_zbMacMlmeResetConfirmHandler },
    { 0x56, tl_zbMacMlmeScanConfirmHandler },
    { 0x57, tl_zbMacMlmeCommStatusIndicationHandler },
    { 0x5b, tl_zbMacMlmeStartConfirmHandler },
    { 0x5c, tl_zbMacMlmeSyncLossIndicationHandler },
    { 0x63, tl_zbMacMlmePollIndicationHandler}
};

#define ZB_NWK_EVENT_FROM_MAC_TBL_SIZE \
    (sizeof(g_zbNwkEventFromMacTbl)/sizeof(g_zbNwkEventTbl_t))
