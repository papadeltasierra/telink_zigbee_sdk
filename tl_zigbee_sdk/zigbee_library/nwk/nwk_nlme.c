// WARNING: Unknown calling convention -- yet parameter storage is locked
void nwk_edScanCnfHandler(void)

{
  void *in_r0;

  g_zbNwkCtx._47_1_ = g_zbNwkCtx._47_1_ & 0xf;
  tl_zbTaskPost(zdo_nlme_ed_scan_confirm, in_r0);
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void nwk_nlmeStartRouterCnf(void)

{
  undefined *in_r0;
  undefined in_r1;

  *in_r0 = in_r1;
  g_zbNwkCtx._47_1_ = g_zbNwkCtx._47_1_ & 0xf;
  tl_zbTaskPost(zdo_nlme_start_router_confirm, in_r0);
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void nwk_startRouterCnfHandler(void)

{
  u16 shortAddr;
  char *in_r0;
  int iVar1;
  undefined4 in_lr;
  undefined in_stack_ffffffe8;
  undefined in_stack_ffffffe9;

  if (*in_r0 == '\0')
  {
    g_zbInfo.macPib.rxOnWhenIdle =
        (u8)(((uint)(byte)g_zbInfo.nwkNib.capabilityInfo << 0x1c) >> 0x1f);
    g_zbInfo.nwkNib.panId = g_zbInfo.macPib.panId;
    memcpy(g_zbInfo.nwkNib.ieeeAddr, g_zbInfo.macPib.extAddress, 8);
    shortAddr = g_zbInfo.nwkNib.nwkAddr;
    g_zbInfo.macPib.shortAddress._0_1_ = (undefined)g_zbInfo.nwkNib.nwkAddr;
    g_zbInfo.macPib.shortAddress._1_1_ = (undefined)((uint)g_zbInfo.nwkNib.nwkAddr >> 8);
    iVar1 = memcmp(g_zbInfo.nwkNib.extPANId, &g_zero_addr, 8);
    if (iVar1 == 0)
    {
      memcpy(g_zbInfo.nwkNib.extPANId, g_zbInfo.macPib.extAddress, 8);
    }
    tl_zbNwkAddrMapAdd(shortAddr,
                       (addrExt_t)
                           CONCAT44(in_lr, (uint)CONCAT11(in_stack_ffffffe9, in_stack_ffffffe8)),
                       (u16 *)g_zbInfo.macPib.extAddress);
    tl_zbNwkBeaconPayloadUpdate();
  }
  nwk_nlmeStartRouterCnf();
  return;
}
void tl_zbMacMlmePollIndicationHandler(void *arg)

{
  u32 uVar1;
  tl_zb_normal_neighbor_entry_t *ptVar2;

  // WARNING: Load size is inaccurate
  if ((((int)((uint)g_zbNwkCtx._45_1_ << 0x1d) < 0) &&
       (-1 < (int)((uint)g_zbInfo.nwkNib.parentInfo << 0x1e))) &&
      (*arg == '\x02'))
  {
    ptVar2 = nwk_neTblGetByShortAddr(*(u16 *)((int)arg + 1));
    if (ptVar2 == (tl_zb_normal_neighbor_entry_t *)0x0)
    {
      if (unknowEndDevAddr_8528 == -2)
      {
        unknowEndDevAddr_8528 = *(u16 *)((int)arg + 1);
        if ((unknowEndDevAddr_8528 & 0xfff8) != 0xfff8)
        {
          zb_address_ieee_by_short(unknowEndDevAddr_8528, (addrExt_t)(ulonglong)unknowEndDevAddr_8528);
        }
        nwkLeaveReqSend();
        return;
      }
      if (unknowEndDevAddr_8528 == *(short *)((int)arg + 1))
      {
        unknowEndDevAddr_8528 = -3;
      }
    }
    else
    {
      uVar1 = ptVar2->devTimeout;
      if (uVar1 != 0)
      {
        *(char *)&ptVar2->timeoutCnt = (char)uVar1;
        *(char *)((int)&ptVar2->timeoutCnt + 1) = (char)(uVar1 >> 8);
        *(char *)((int)&ptVar2->timeoutCnt + 2) = (char)(uVar1 >> 0x10);
        *(char *)((int)&ptVar2->timeoutCnt + 3) = (char)(uVar1 >> 0x18);
        ptVar2->keepaliveRcvd = '\x01';
      }
    }
  }
  zb_buf_free((zb_buf_t *)arg);
  return;
}
void tl_zbMacMlmeResetConfirmHandler(void *arg)

{
  undefined uVar1;

  // WARNING: Load size is inaccurate
  uVar1 = *arg;
  tl_zbNwkNibInit();
  tl_zbNeighborTableInit();
  memset(&g_zbNwkCtx, 0, 0x4f);
  g_zbNwkCtx._46_1_ = g_zbNwkCtx._46_1_ | 0x10;
  *(undefined *)arg = uVar1;
  tl_zbTaskPost(zdo_reset_confirm_cb, arg);
  return;
}
void tl_zbMacMlmeSyncLossIndicationHandler(void *arg)

{
  zb_buf_free((zb_buf_t *)arg);
  return;
}
void tl_zbNwkNlmeEDScanRequestHandler(void *arg)

{
  undefined4 uVar1;

  // WARNING: Load size is inaccurate
  uVar1 = *arg;
  *(char *)arg = (char)uVar1;
  *(char *)((int)arg + 1) = (char)((uint)uVar1 >> 8);
  *(char *)((int)arg + 2) = (char)((uint)uVar1 >> 0x10);
  *(char *)((int)arg + 3) = (char)((uint)uVar1 >> 0x18);
  *(undefined *)((int)arg + 5) = *(undefined *)((int)arg + 4);
  *(undefined *)((int)arg + 4) = 0;
  g_zbNwkCtx._47_1_ = g_zbNwkCtx._47_1_ & 0xf | 0x70;
  tl_zbPrimitivePost('\x02', 'U', arg);
  return;
}
void tl_zbNwkNlmeNwkStatusInd(void *arg, u16 nwkAddr, nwk_statusCode_t status)

{
  *(nwk_statusCode_t *)((int)arg + 2) = status;
  *(u16 *)arg = nwkAddr;
  tl_zbTaskPost(zdo_nlme_status_indication, arg);
  return;
}
void tl_zbNwkNlmeResetRequestHandler(void *arg)

{
  byte bVar1;

  if (((g_zbNwkCtx._47_1_ & 0xf0) == 0) &&
      (bVar1 = g_zbNwkCtx._45_1_ & 4, (g_zbNwkCtx._45_1_ & 4) == 0))
  {
    // WARNING: Load size is inaccurate
    if (*arg == '\0')
    {
      *(undefined *)arg = 1;
      tl_zbPrimitivePost('\x02', 'Q', arg);
    }
    else
    {
      tl_zbAdditionNeighborReset();
      *(byte *)arg = bVar1;
      tl_zbTaskPost(zdo_reset_confirm_cb, arg);
    }
  }
  else
  {
    *(undefined *)arg = 0;
    tl_zbTaskPost(zdo_reset_confirm_cb, arg);
  }
  return;
}
void tl_zbNwkNlmeStartRouterRequestHandler(void *arg)

{
  byte bVar1;

  bVar1 = g_zbNwkCtx._47_1_ & 0xf0;
  if ((g_zbNwkCtx._47_1_ & 0xf0) == 0)
  {
    g_zbNwkCtx._47_1_ = g_zbNwkCtx._47_1_ & 0xf | 0x20;
    // WARNING: Load size is inaccurate
    *(u16 *)((int)arg + 4) = g_zbInfo.macPib.panId;
    *(u8 *)((int)arg + 6) = g_zbInfo.macPib.phyChannelCur;
    *(byte *)((int)arg + 7) = bVar1;
    *(undefined *)((int)arg + 10) = 1;
    *(byte *)((int)arg + 0x17) = bVar1;
    *(undefined *)((int)arg + 8) = *arg;
    *(undefined *)((int)arg + 9) = *(undefined *)((int)arg + 1);
    *(undefined *)((int)arg + 0xb) = *(undefined *)((int)arg + 2);
    tl_zbPrimitivePost('\x02', 'Z', arg);
  }
  else
  {
    nwk_nlmeStartRouterCnf();
  }
  return;
}
