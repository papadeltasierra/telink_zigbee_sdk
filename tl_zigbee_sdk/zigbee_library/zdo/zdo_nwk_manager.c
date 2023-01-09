// WARNING: Unknown calling convention -- yet parameter storage is locked
undefined4 zdo_auth_check_timer_cb(void)

{
  undefined4 in_r0;

  tl_zbNwkAddrMapInit();
  tl_zbNeighborTableInit();
  zdo_startDeviceCnf(in_r0, 0x8d);
  g_zdo_nwk_manager._20_4_ = 0;
  g_zdo_nwk_manager._4_4_ = 0;
  return 0xfffffffe;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void zdo_manyToOneRouteDisc(void)

{
  undefined *in_r0;

  in_r0[3] = 0;
  in_r0[4] = 0;
  in_r0[2] = 0;
  *in_r0 = 0xfb;
  in_r0[1] = 0xfe;
  in_r0[3] = g_zbInfo.nwkNib.concentratorRadius;
  in_r0[4] = (byte)NWK_ROUTE_RECORD_TABLE_SIZE + ~(byte)NWK_ROUTE_RECORD_TABLE_SIZE +
             ((undefined *)0xfffffffe < in_r0 + 3);
  tl_zbPrimitivePost('\x03', 0x8f, in_r0);
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void zdo_network_formation_confirm(void)

{
  u8 uVar1;
  zb_buf_t *in_r0;
  void *arg;

  uVar1 = in_r0->buf[0];
  if (g_zdo_nwk_manager[37] == '\x01')
  {
    zdo_startDeviceCnf(in_r0, uVar1);
    if (uVar1 == '\0')
    {
      if (((int)((uint)g_zbInfo.nwkNib._45_1_ << 0x1b) < 0) &&
          (arg = (void *)c1(), arg != (void *)0x0))
      {
        tl_zbTaskPost(zdo_manyToOneRouteDisc, arg);
      }
    }
  }
  else
  {
    zb_buf_free(in_r0);
  }
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
undefined4 zdo_nlmeEdScanReq(void)

{
  undefined4 uVar1;
  int iVar2;
  undefined extraout_r1;
  uint extraout_r2;
  code *in_r3;

  uVar1 = (*in_r3)();
  if (((extraout_r2 & 0xff) != 0) && (g_zdo_nwk_manager[37] == '\0'))
  {
    iVar2 = c1();
    if (iVar2 == 0)
    {
      return 0x8a;
    }
    g_zdo_nwk_manager[37] = 7;
    g_zdo_nwk_manager[35] = (undefined)extraout_r2;
    g_zdo_nwk_manager._24_4_ = uVar1;
    g_zdo_nwk_manager[33] = extraout_r1;
    zdo_nlme_edScan(iVar2);
    return 0;
  }
  return 0x80;
}
void zdo_nlmeForgetDev(addrExt_t nodeIeeeAddr, bool rejoin)

{
  u8 uVar1;
  u16 uVar2;
  tl_zb_normal_neighbor_entry_t *entry;
  char in_r1;
  undefined in_stack_ffffffdc;
  undefined in_stack_ffffffdd;
  undefined6 in_stack_ffffffde;
  u16 local_16[3];

  local_16[0] = 0xfffe;
  if (in_r1 == '\0')
  {
    ss_devKeyPairDelete((addrExt_t)
                            CONCAT62(in_stack_ffffffde, CONCAT11(in_stack_ffffffdd, in_stack_ffffffdc)));
  }
  uVar1 = tl_zbShortAddrByExtAddr(local_16, (addrExt_t)CONCAT62(in_stack_ffffffde, CONCAT11(in_stack_ffffffdd, in_stack_ffffffdc)),
                                  (u16 *)(uint)rejoin);
  if (uVar1 == '\0')
  {
    if (in_r1 == '\0')
    {
      aps_bindingTblEntryDelByDstExtAddr();
    }
    nwkRoutingTabEntryDstDel();
    nwkRouteRecTabEntryDstDel();
    entry = nwk_neTblGetByExtAddr((addrExt_t)
                                      CONCAT62(in_stack_ffffffde, CONCAT11(in_stack_ffffffdd, in_stack_ffffffdc)));
    if (entry == (tl_zb_normal_neighbor_entry_t *)0x0)
    {
      tl_zbNwkAddrMapDelete(0);
    }
    else
    {
      uVar2 = tl_zbshortAddrByIdx(entry->addrmapIdx);
      tl_zbExtAddrByIdx(entry->addrmapIdx, (addrExt_t)CONCAT62(in_stack_ffffffde, uVar2));
      nwk_nodeAddrInfoDelete();
      tl_zbNeighborTableDelete(entry);
    }
  }
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
undefined4 zdo_nlmeLeaveReq(void)

{
  void *in;
  void *out;
  undefined4 uVar1;
  code *in_r3;

  in = (void *)(*in_r3)();
  out = (void *)c1();
  uVar1 = 0x8a;
  if (out != (void *)0x0)
  {
    memcpy(out, in, 10);
    tl_zbPrimitivePost('\x03', 0x82, out);
    uVar1 = 0;
  }
  return uVar1;
}
undefined4 zdo_nlmeNwkDiscReq(void)

{
  undefined *arg;
  undefined4 uVar1;

  arg = (undefined *)c1();
  uVar1 = 0x8a;
  if (arg != (undefined *)0x0)
  {
    g_zdo_nwk_manager[37] = 3;
    *arg = g_zdo_nwk_manager[24];
    arg[1] = g_zdo_nwk_manager[25];
    arg[2] = g_zdo_nwk_manager[26];
    arg[3] = g_zdo_nwk_manager[27];
    arg[4] = g_zdo_nwk_manager[33];
    tl_zbPrimitivePost('\x03', 's', arg);
    uVar1 = 0;
  }
  return uVar1;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
u8 zdo_nlmePermitJoinCnf(void)

{
  u8 uVar1;
  zb_buf_t *in_r0;

  uVar1 = zb_buf_free(in_r0);
  return uVar1;
}
undefined4 zdo_nlmePermitJoinReq(undefined param_1)

{
  undefined *arg;
  undefined4 uVar1;

  arg = (undefined *)c1();
  uVar1 = 0x8a;
  if (arg != (undefined *)0x0)
  {
    *arg = param_1;
    tl_zbPrimitivePost('\x03', 'w', arg);
    uVar1 = 0;
  }
  return uVar1;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
u8 zdo_nlme_direct_join_confirm(void)

{
  u8 uVar1;
  zb_buf_t *in_r0;

  uVar1 = zb_buf_free(in_r0);
  return uVar1;
}
void zdo_nlme_edScan(undefined *param_1)

{
  *param_1 = g_zdo_nwk_manager[24];
  param_1[1] = g_zdo_nwk_manager[25];
  param_1[2] = g_zdo_nwk_manager[26];
  param_1[3] = g_zdo_nwk_manager[27];
  param_1[4] = g_zdo_nwk_manager[33];
  tl_zbPrimitivePost('\x03', '{', param_1);
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void zdo_nlme_ed_scan_confirm(void)

{
  zb_buf_t *in_r0;

  if (g_zdo_nwk_manager[37] == '\a')
  {
    g_zdo_nwk_manager[35] = g_zdo_nwk_manager[35] + -1;
    if (g_zdo_nwk_manager[35] != '\0')
    {
      zdo_nlme_edScan(in_r0);
      return;
    }
    g_zdo_nwk_manager[37] = g_zdo_nwk_manager[35];
    if ((zdo_mgmt_nwk_flag & 1) != 0)
    {
      zdo_mgmt_nwk_flag = zdo_mgmt_nwk_flag & 0xfe;
      tl_zbTaskPost(zdo_nwkUpdateNotifyRespSend, in_r0);
      return;
    }
  }
  zb_buf_free(in_r0);
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void zdo_nlme_join_confirm(void)

{
  zb_buf_t *in_r0;
  u8 uVar1;

  if (g_zdo_nwk_manager[37] == '\x05')
  {
    uVar1 = in_r0->buf[2];
    (in_r0->hdr).field_0x3 = (in_r0->hdr).field_0x3 | 0x20;
    if (uVar1 == '\0')
    {
      zdo_nwkRejoinWithBackOffStop();
      if ((-1 < (int)((uint)aps_ib._18_1_ << 0x1e)) && ((ss_ib._62_1_ & 7) != 0))
      {
      LAB_00024208:
        zdo_nwkAuthTimeoutStart(in_r0);
        FUN_00024188();
        return;
      }
    LAB_000241fe:
      zdo_startDeviceCnf(in_r0, 0);
      FUN_00024188();
      return;
    }
    if (g_zdo_nwk_manager._12_4_ != 0)
    {
      g_zdo_nwk_manager[37] = 0;
      zb_buf_free(in_r0);
      return;
    }
  }
  else if (g_zdo_nwk_manager[37] == '\x06')
  {
    uVar1 = '\0';
    if (in_r0->buf[2] != '\0')
    {
      uVar1 = '`';
    }
  }
  else
  {
    if (g_zdo_nwk_manager[37] != '\x04')
    {
      zb_buf_free(in_r0);
      return;
    }
    uVar1 = in_r0->buf[2];
    if (uVar1 == '\0')
    {
      if ((-1 < (int)((uint)aps_ib._18_1_ << 0x1e)) && ((ss_ib._62_1_ & 7) != 0))
        goto LAB_00024208;
      if ((int)((uint)(byte)g_zbInfo.nwkNib.capabilityInfo << 0x1e) < 0)
      {
        zdo_nlme_start_router_req(in_r0);
        FUN_00024188();
        return;
      }
      goto LAB_000241fe;
    }
  }
  zdo_startDeviceCnf(in_r0, uVar1);
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void zdo_nlme_join_indication(void)

{
  void *in_r0;
  undefined4 local_24;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  uint uStack_14;
  undefined uStack_10;

  local_24 = 0;
  uStack_20 = 0;
  uStack_1c = 0;
  uStack_18 = 0;
  uStack_14 = (uint) * (ushort *)((int)in_r0 + 8);
  uStack_14 = uStack_14 | (uint) * (byte *)((int)in_r0 + 0xb) << 0x18;
  uStack_10 = *(undefined *)((int)in_r0 + 0xc);
  memcpy(&uStack_1c, in_r0, 8);
  memcpy(in_r0, &local_24, 0x15);
  ss_zdoChildAuthStart();
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void zdo_nlme_leave_confirm_cb(void)

{
  byte bVar1;
  zb_buf_t *in_r0;
  int iVar2;
  undefined auStack_1c[16];

  memcpy(auStack_1c, in_r0, 9);
  bVar1 = (in_r0->hdr).field_0x3;
  zb_buf_free(in_r0);
  iVar2 = memcmp(auStack_1c, &g_zero_addr, 8);
  if ((iVar2 == 0) || (iVar2 = memcmp(auStack_1c, g_zbInfo.macPib.extAddress, 8), iVar2 == 0))
  {
    zdo_nwkRejoinWithBackOffStop();
    g_zbNwkCtx._47_1_ = g_zbNwkCtx._47_1_ & 0xf0 | 2;
    tl_zbNwkLinkStatusStop();
    iVar2 = FUN_0000162c(g_zbInfo.nwkNib.passiveAckTimeout, 1000);
    ev_timer_taskPost(zdo_selfLeaveProcessCb, (void *)(((uint)bVar1 << 0x1d) >> 0x1f), iVar2 << 2);
  }
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void zdo_nlme_leave_indication_cb(void)

{
  zb_buf_t *in_r0;
  tl_zb_normal_neighbor_entry_t *ptVar1;
  int iVar2;
  undefined in_stack_ffffffd8;
  undefined7 in_stack_ffffffd9;
  char cStack_20;
  u8 local_1a;
  u8 uStack_19;

  memcpy(&stack0xffffffd8, in_r0, 9);
  ptVar1 = tl_zbNeighborTableSearchFromExtAddr((u16 *)&local_1a, (addrExt_t)CONCAT71(in_stack_ffffffd9, in_stack_ffffffd8),
                                               (u16 *)&stack0xffffffd8);
  if (((ptVar1 != (tl_zb_normal_neighbor_entry_t *)0x0) &&
       (-1 < (int)((uint)g_zbNwkCtx._45_1_ << 0x1b))) &&
      (cStack_20 == '\0'))
  {
    iVar2 = memcmp(ss_ib.trust_center_address, &g_invalid_addr, 8);
    if ((iVar2 != 0) && ((ptVar1->field_0x1e & 0x70) == 0x10))
    {
      in_r0->buf[0x12] = '\x02';
      memcpy(in_r0, ss_ib.trust_center_address, 8);
      in_r0->buf[0x10] = local_1a;
      in_r0->buf[0x11] = uStack_19;
      memcpy(in_r0->buf + 8, &stack0xffffffd8, 8);
      tl_zbTaskPost(ss_apsmeUpdateDevReq, in_r0);
      goto LAB_00023c2a;
    }
  }
  zb_buf_free(in_r0);
LAB_00023c2a:
  zdo_nlmeForgetDev((addrExt_t)CONCAT71(in_stack_ffffffd9, in_stack_ffffffd8),
                    SUB41(&stack0xffffffd8, 0));
  if ((zdoAppIndCbLst != 0) && (*(int *)(zdoAppIndCbLst + 0xc) != 0))
  {
    zdo_nlmeLeaveReq();
  }
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void zdo_nlme_network_discovery_confirm_cb(void)

{
  byte bVar1;
  u16 uVar2;
  zb_buf_t *in_r0;
  byte bVar3;

  zb_buf_free(in_r0);
  if (g_zdo_nwk_manager[37] == '\x03')
  {
    g_zdo_nwk_manager[37] = '\0';
    if (g_zdo_nwk_manager._16_4_ == 0)
    {
      g_zdo_nwk_manager[34] = '\0';
    }
    else
    {
      bVar3 = g_zdo_nwk_manager[34] + 1;
      g_zdo_nwk_manager[34] = bVar3;
      bVar1 = zdo_af_get_scan_attempts();
      if (bVar3 < bVar1)
      {
        uVar2 = zdo_af_get_nwk_time_btwn_scans();
        g_zdo_nwk_manager._0_4_ = ev_timer_taskPost(zdo_nwkDiscReqTimerCb, (void *)0x0, (uint)uVar2);
        FUN_00024274();
        return;
      }
      g_zdo_nwk_manager[34] = '\0';
      if (g_zdo_nwk_manager._16_4_ != 0)
      {
        zdoMgmtLeaveCmdProcessCb();
        FUN_00024274();
        return;
      }
    }
  }
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void zdo_nlme_start_router_confirm(void)

{
  u8 uVar1;
  zb_buf_t *in_r0;
  void *arg;

  uVar1 = in_r0->buf[0];
  if (g_zdo_nwk_manager[37] == '\x02')
  {
    zdo_startDeviceCnf(in_r0, uVar1);
    if (uVar1 == '\0')
    {
      if (((int)((uint)g_zbInfo.nwkNib._45_1_ << 0x1b) < 0) &&
          (arg = (void *)c1(), arg != (void *)0x0))
      {
        tl_zbTaskPost(zdo_manyToOneRouteDisc, arg);
      }
    }
  }
  else
  {
    zb_buf_free(in_r0);
  }
  return;
}
void zdo_nlme_start_router_req(undefined *param_1)

{
  *param_1 = 0xf;
  param_1[1] = 0xf;
  param_1[2] = 0;
  g_zdo_nwk_manager[37] = 2;
  tl_zbPrimitivePost('\x03', 'y', param_1);
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void zdo_nlme_status_indication(void)

{
  u8 uVar1;
  zb_buf_t *in_r0;

  uVar1 = in_r0->buf[2];
  if ((byte)(uVar1 - 0xb) < 2)
  {
    if ((int)((uint)g_zbInfo.nwkNib._45_1_ << 0x1b) < 0)
    {
      if (uVar1 == '\v')
      {
        nwkRouteRecTabEntryDstDel();
      }
      tl_zbTaskPost(zdo_manyToOneRouteDisc, in_r0);
      return;
    }
  }
  else
  {
    if (uVar1 == '\r')
    {
      tl_zbNwkStatusAddrConflictInd(in_r0);
      return;
    }
    if (uVar1 == '\x0f')
    {
      zb_buf_free(in_r0);
      zb_info_save((void *)0x0);
      return;
    }
  }
  zb_buf_free(in_r0);
  return;
}
void zdo_nwkAuthTimeoutStart(zb_buf_t *param_1)

{
  if (g_zdo_nwk_manager._4_4_ == (ev_timer_event_t *)0x0)
  {
    g_zdo_nwk_manager._20_4_ = param_1;
    g_zdo_nwk_manager._4_4_ =
        ev_timer_taskPost(zdo_auth_check_timer_cb, param_1, TRANSPORT_NETWORK_KEY_WAIT_TIME);
  }
  else
  {
    zb_buf_free(param_1);
  }
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
undefined4 zdo_nwkDiscReqTimerCb(void)

{
  int iVar1;
  undefined4 uVar2;

  iVar1 = zdo_nlmeNwkDiscReq();
  uVar2 = 0;
  if (iVar1 == 0)
  {
    g_zdo_nwk_manager._0_4_ = 0;
    uVar2 = 0xfffffffe;
  }
  return uVar2;
}
zdo_status_t zdo_nwkFormationStart(u32 scanChannels, u8 scanDuration)

{
  zdo_status_t zVar1;
  undefined *arg;
  int iVar2;

  zVar1 = ZDO_INVALID_REQUEST;
  if (g_zdo_nwk_manager[37] == '\0')
  {
    arg = (undefined *)c1();
    zVar1 = ZDO_INSUFFICIENT_SPACE;
    if (arg != (undefined *)0x0)
    {
      arg[6] = 0;
      *arg = (char)scanChannels;
      arg[1] = (char)(scanChannels >> 8);
      arg[2] = (char)(scanChannels >> 0x10);
      arg[3] = (char)(scanChannels >> 0x18);
      arg[8] = scanDuration;
      arg[9] = 0xf;
      arg[10] = 0xf;
      arg[7] = 0;
      g_zdo_nwk_manager[37] = '\x01';
      g_zdo_nwk_manager._24_4_ = scanChannels;
      g_zdo_nwk_manager[33] = scanDuration;
      g_zbInfo.nwkNib.capabilityInfo = (capability_info_t)af_nodeMacCapabilityGet();
      iVar2 = memcmp(aps_ib.aps_use_ext_panid, &g_zero_addr, 8);
      if (iVar2 != 0)
      {
        memcpy(g_zbInfo.nwkNib.extPANId, aps_ib.aps_use_ext_panid, 8);
      }
      tl_zbAdditionNeighborReset();
      tl_zbPrimitivePost('\x03', 'u', arg);
      zVar1 = ZDO_SUCCESS;
    }
  }
  return zVar1;
}
undefined4 zdo_nwkRejoinReqSend(void)

{
  u8 uVar1;
  void *out;
  undefined4 uVar2;
  int iVar3;

  out = (void *)c1();
  uVar2 = 0x8a;
  if (out != (void *)0x0)
  {
    g_zdo_nwk_manager[37] = 5;
    tl_zbAdditionNeighborReset();
    uVar1 = af_nodeMacCapabilityGet();
    *(undefined *)((int)out + 0xc) = 2;
    *(undefined *)((int)out + 8) = g_zdo_nwk_manager[24];
    *(undefined *)((int)out + 9) = g_zdo_nwk_manager[25];
    *(undefined *)((int)out + 10) = g_zdo_nwk_manager[26];
    *(undefined *)((int)out + 0xb) = g_zdo_nwk_manager[27];
    *(undefined *)((int)out + 0xd) = g_zdo_nwk_manager[33];
    *(u8 *)((int)out + 0xe) = uVar1;
    iVar3 = memcmp(aps_ib.aps_use_ext_panid, &g_zero_addr, 8);
    if (iVar3 == 0)
    {
      memcpy(out, g_zbInfo.nwkNib.extPANId, 8);
    }
    else
    {
      memcpy(out, aps_ib.aps_use_ext_panid, 8);
    }
    *(byte *)((int)out + 0xf) = aps_ib._18_1_ & 1 ^ 1;
    tl_zbPrimitivePost('\x03', '}', out);
    uVar2 = 0;
  }
  return uVar2;
}
zdo_status_t zdo_nwkRejoinStart(u32 scanChannels, u8 scanDuration)

{
  zdo_status_t zVar1;
  int iVar2;

  zVar1 = ZDO_INVALID_REQUEST;
  if (g_zdo_nwk_manager[37] == '\0')
  {
    iVar2 = memcmp(aps_ib.aps_use_ext_panid, &g_zero_addr, 8);
    if ((iVar2 != 0) || (iVar2 = memcmp(g_zbInfo.nwkNib.extPANId, &g_zero_addr, 8), iVar2 != 0))
    {
      g_zbNwkCtx._45_1_ = g_zbNwkCtx._45_1_ & 0xfb;
      g_zdo_nwk_manager._24_4_ = scanChannels;
      g_zdo_nwk_manager[33] = scanDuration;
      zVar1 = zdo_nwkRejoinReqSend();
    }
  }
  return zVar1;
}
void zdo_nwkRejoinWithBackOffStop(void)

{
  if (g_zdo_nwk_manager._12_4_ != 0)
  {
    ev_timer_taskCancel((ev_timer_event_t **)(g_zdo_nwk_manager + 0xc));
  }
  g_zdo_nwk_manager[32] = 0;
  g_zdo_nwk_manager._30_2_ = 0;
  g_zdo_nwk_manager._28_2_ = 0;
  return;
}
zdo_status_t zdo_nwkRouterStart(void)

{
  zdo_status_t zVar1;
  int iVar2;

  zVar1 = ZDO_INVALID_REQUEST;
  if (g_zdo_nwk_manager[37] == '\0')
  {
    iVar2 = c1();
    zVar1 = ZDO_INSUFFICIENT_SPACE;
    if (iVar2 != 0)
    {
      g_zbInfo.nwkNib.capabilityInfo = (capability_info_t)af_nodeMacCapabilityGet();
      zdo_nlme_start_router_req(iVar2);
      zVar1 = ZDO_SUCCESS;
    }
  }
  return zVar1;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void zdo_reset_confirm_cb(void)

{
  zb_buf_t *in_r0;

  if ((zdoAppIndCbLst != 0) && (*(int *)(zdoAppIndCbLst + 4) != 0))
  {
    zdo_nlmeEdScanReq();
  }
  zb_buf_free(in_r0);
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
u8 zdo_routeDiscCnf(void)

{
  u8 uVar1;
  zb_buf_t *in_r0;

  uVar1 = zb_buf_free(in_r0);
  return uVar1;
}
undefined4 zdo_selfLeaveProcessCb(int param_1)

{
  int extraout_r0;

  g_zbNwkCtx._45_1_ = g_zbNwkCtx._45_1_ & 0xfb;
  g_zdo_nwk_manager[36] = 0;
  if (param_1 != 0)
  {
    zdo_nwkRejoinStart(1 << (uint)g_zbInfo.macPib.phyChannelCur,
                       zdo_cfg_attributes.config_nwk_scan_duration);
    return 0xfffffffe;
  }
  nv_nwkFrameCountSaveToFlash(ss_ib.outgoingFrameCounter);
  nv_resetToFactoryNew();
  zb_reset();
  if (zdoTouchLinkCb == (int *)0x0)
  {
    g_zbNwkCtx._47_1_ = g_zbNwkCtx._47_1_ & 0xf0;
  }
  else
  {
    if (zdoTouchLinkCb[1] == 0)
    {
      g_zbNwkCtx._47_1_ = g_zbNwkCtx._47_1_ & 0xf0;
    }
    else
    {
      zdo_nwkRejoinWithBackOffStop();
      g_zbNwkCtx._47_1_ = g_zbNwkCtx._47_1_ & 0xf0;
      if (zdoTouchLinkCb == (int *)0x0)
        goto LAB_0002403c;
    }
    if ((*zdoTouchLinkCb != 0) && (zdo_nwkRejoinWithBackOffStop(), extraout_r0 != 0))
    {
      return 0xfffffffe;
    }
  }
LAB_0002403c:
  if ((zdoAppIndCbLst != 0) && (*(int *)(zdoAppIndCbLst + 0x10) != 0))
  {
    zdo_nwkRejoinWithBackOffStop();
  }
  return 0xfffffffe;
}
void zdo_startDeviceCnf(undefined *param_1, int param_2)

{
  u16 uVar1;

  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  param_1[4] = 0;
  param_1[5] = 0;
  *param_1 = (char)param_2;
  if (param_2 == 0)
  {
    param_1[1] = g_zbInfo.macPib.phyChannelCur;
    uVar1 = g_zbInfo.macPib.panId;
    param_1[2] = (char)g_zbInfo.macPib.panId;
    param_1[3] = (char)(uVar1 >> 8);
    uVar1 = g_zbInfo.macPib.shortAddress;
    param_1[4] = (char)g_zbInfo.macPib.shortAddress;
    param_1[5] = (char)(uVar1 >> 8);
  }
  g_zdo_nwk_manager[37] = 0;
  tl_zbTaskPost(zdo_startup_complete, param_1);
  return;
}
void zdo_startup_complete(zb_buf_t *param_1)

{
  if (param_1->buf[0] == '\0')
  {
    g_zbNwkCtx._45_1_ = g_zbNwkCtx._45_1_ | 0x14;
    ss_zdoTcInit();
    g_zbNwkCtx._45_1_ = g_zbNwkCtx._45_1_ & 0xfe;
    tl_zbNwkLinkStatusStart();
  }
  else
  {
    if ((int)((uint)g_zbNwkCtx._45_1_ << 0x1f) < 0)
    {
      g_zbNwkCtx._45_1_ = g_zbNwkCtx._45_1_ & 0xdb;
    }
    tl_zbNwkLinkStatusStop();
  }
  g_zbNwkCtx._47_1_ = g_zbNwkCtx._47_1_ & 0xf0;
  tl_zbAdditionNeighborReset();
  if ((zdoAppIndCbLst != (int *)0x0) && (*zdoAppIndCbLst != 0))
  {
    FFFFFFF();
  }
  zb_buf_free(param_1);
  return;
}
