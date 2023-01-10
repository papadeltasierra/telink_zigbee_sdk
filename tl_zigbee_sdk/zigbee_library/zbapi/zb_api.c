u8 zb_apsmeRequestKeyReq(ss_apsmeRequestKeyReq_t *pRequestKeyReq)

{
  u8 uVar1;
  void *out;

  out = (void *)c1();
  uVar1 = '\n';
  if (out != (void *)0x0)
  {
    memcpy(out, pRequestKeyReq, 0x12);
    tl_zbTaskPost(ss_apsmeRequestKeyReq, out);
    uVar1 = '\0';
  }
  return uVar1;
}
u8 zb_apsmeSwitchKeyReq(ss_apsmeSwitchKeyReq_t *pSwitchKeyReq)

{
  u8 uVar1;
  void *out;

  out = (void *)c1();
  uVar1 = '\n';
  if (out != (void *)0x0)
  {
    memcpy(out, pSwitchKeyReq, 9);
    tl_zbTaskPost(ss_apsmeSwitchKeyReq, out);
    uVar1 = '\0';
  }
  return uVar1;
}
u8 zb_assocJoinReq(void)

{
  return '2';
}
bool zb_getMacAssocPermit(void)

{
  return (bool)g_zbInfo.macPib.associationPermit;
}
bool zb_isDeviceFactoryNew(void)

{
  return (bool)(g_zbNwkCtx._45_1_ & 1);
}
bool zb_isDeviceJoinedNwk(void)

{
  // This explains compiler field '_45_1_'
  //  union {
  //    struct {
  //      u8  is_factory_new:1;	/*!< Device is factory new */
	//      u8  permit_join:1; 		/*!< True if permit join is in progress */
	//      u8  joined:1;      		/*!< Non-zero if we are joined into the network */
	//      u8  router_started:1; 	/*!< not used */
	//      u8  is_tc:1;            /*!< True if we are Trust Center */
	//      u8  joined_pro:1;
	//      u8	panIdConflict:1;	/*!< if we find panID conflict */
	//      u8	joinAccept:1;
  //    },
  //    u8 _45_1_;
  //  };
  // ...
  // }nwk_ctx_t;
  return SUB41(((uint)g_zbNwkCtx._45_1_ << 0x1d) >> 0x1f, 0);
}
u8 zb_nlmeLeaveReq(nlme_leave_req_t *pLeaveReq)

{
  u8 uVar1;

  uVar1 = (*(code *)&zdo_nlmeLeaveReq)();
  return uVar1;
}
u8 zb_nlmePermitJoiningRequest(u8 permitDuration)

{
  u8 uVar1;

  uVar1 = zdo_nlmePermitJoinReq(permitDuration);
  return uVar1;
}
u8 zb_nwkDiscovery(u32 scanChannels, u8 scanDuration, nwkDiscoveryUserCb_t cb)

{
  return '2';
}
u8 zb_nwkFormation(u32 scanChannels, u8 scanDuration)

{
  zdo_status_t zVar1;

  zVar1 = zdo_nwkFormationStart(scanChannels, scanDuration);
  return zVar1;
}
u8 zb_routerStart(void)

{
  zdo_status_t zVar1;

  zVar1 = zdo_nwkRouterStart();
  return zVar1;
}
u8 zb_tcUpdateNwkKey(ss_tcUpdateNwkKey_t *pTcUpdateNwkKey)

{
  u8 uVar1;
  void *dest;

  dest = (void *)c1();
  uVar1 = '\n';
  if (dest != (void *)0x0)
  {
    memset(dest, 0, 0x25);
    memcpy(dest, pTcUpdateNwkKey, 8);
    memcpy((void *)((int)dest + 9), pTcUpdateNwkKey->key, 0x10);
    *(undefined *)((int)dest + 8) = 1;
    *(u8 *)((int)dest + 0x1a) = ss_ib.activeKeySeqNum + '\x01';
    *(undefined *)((int)dest + 0x19) = 0;
    *(undefined *)((int)dest + 0x24) = 1;
    *(undefined *)((int)dest + 0x23) = 0;
    ss_tcTransportKeyTimerStart();
    uVar1 = '\0';
  }
  return uVar1;
}
zdo_status_t zb_zdoBindUnbindReq(bool isBinding, zdo_bind_req_t *pReq, u8 *seqNo, zdo_callback indCb)

{
  u8 uVar1;
  zdo_status_t zVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  u16 local_22;

  uVar4 = 0;
  uVar5 = 0;
  iVar3 = memcmp(pReq, g_zbInfo.macPib.extAddress, 8);
  if (iVar3 == 0)
  {
    zVar2 = zdo_apsmeBindUnBind();
  }
  else
  {
    uVar1 = tl_zbShortAddrByExtAddr(&local_22, (addrExt_t)CONCAT44(uVar5, uVar4), (u16 *)pReq);
    zVar2 = ZDO_DEVICE_NOT_FOUND;
    if (uVar1 != 0xff)
    {
      uVar4 = 0xf;
      if (pReq->dst_addr_mode == LONG_EXADDR_DSTENDPOINT)
      {
        uVar4 = 0x16;
      }
      zVar2 = zdp_data_send(pReq, uVar4, &stack0xffffffc0);
      *seqNo = '\0';
    }
  }
  return zVar2;
}
void zb_zdoCbRegister(zdo_appIndCb_t *cb)

{
  zdo_zdpCbTblRegister(cb);
  return;
}
zdo_status_t zb_zdoNwkAddrReq(u16 dstNwkAddr, zdo_nwk_addr_req_t *pReq, u8 *seqNo, zdo_callback indCb)

{
  zdo_status_t zVar1;
  undefined4 local_2c;
  undefined4 uStack_28;
  uint uStack_24;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  zdo_callback p_Stack_18;
  u8 local_14;

  local_2c = 0;
  uStack_28 = 0;
  uStack_20 = 0;
  uStack_1c = 0;
  local_14 = '\0';
  uStack_24 = (uint)dstNwkAddr;
  p_Stack_18 = indCb;
  zVar1 = zdp_data_send(pReq, 0xb, &local_2c);
  *seqNo = local_14;
  return zVar1;
}
u8 zb_zdoSendDevAnnance(void)

{
  zdo_device_announce_send();
  return '\0';
}
void zb_zdoSendParentAnnce(void)

{
  zdo_apsParentAnnceTimerStart();
  return;
}

zdo_status_t
zb_mgmtPermitJoinReq(u16 dstNwkAddr, u8 permitJoinDuration, u8 tcSignificance, u8 *seqNo, zdo_callback indCb)

{
  zdo_status_t zVar1;
  undefined4 local_34;
  undefined4 uStack_30;
  uint uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  zdo_callback p_Stack_20;
  u8 local_1c;
  u8 local_18;
  u8 uStack_17;

  if (g_zbInfo.nwkNib.nwkAddr == dstNwkAddr)
  {
    zVar1 = zdo_nlmePermitJoinReq(permitJoinDuration);
  }
  else
  {
    if ((dstNwkAddr & 0xfff8) == 0xfff8)
    {
      zdo_nlmePermitJoinReq(permitJoinDuration);
      p_Stack_20 = ll_reset;
    }
    else
    {
      p_Stack_20 = indCb;
    }
    uStack_24 = 0x36;
    uStack_2c = (uint)dstNwkAddr;
    local_1c = '\0';
    uStack_28 = 0;
    uStack_30 = 0;
    local_34 = 0;
    local_18 = permitJoinDuration;
    uStack_17 = tcSignificance;
    zVar1 = zdp_data_send(&local_18, 3, &local_34);
    *seqNo = local_1c;
  }
  return zVar1;
}