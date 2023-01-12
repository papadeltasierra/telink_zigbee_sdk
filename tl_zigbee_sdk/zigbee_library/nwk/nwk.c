u8 getNwkHdrSize(nwk_hdr_t *pNwkHdr)

{
  u8 uVar1;
  uint uVar2;

  uVar2 = (uint)(byte)(pNwkHdr->framecontrol).field_0x1;
  uVar1 = '\b';
  if ((int)(uVar2 << 0x1c) < 0)
  {
    uVar1 = '\x10';
  }
  if ((int)(uVar2 << 0x1b) < 0)
  {
    uVar1 = uVar1 + '\b';
  }
  if ((int)(uVar2 << 0x1f) < 0)
  {
    uVar1 = uVar1 + '\x01';
  }
  if ((int)(uVar2 << 0x1d) < 0)
  {
    uVar1 = uVar1 + (pNwkHdr->srcRouteSubFrame).relayCnt * '\x02' + '\x02';
  }
  if ((int)(uVar2 << 0x1e) < 0)
  {
    uVar1 = uVar1 + '\x0e';
  }
  return uVar1;
}
u8 is_device_factory_new(void)

{
  return g_zbNwkCtx._45_1_ & 1;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
uint nwkHdrParse(void)

{
  byte bVar1;
  undefined *in_r0;
  uint uVar2;
  void *in_r1;
  int iVar3;
  byte *pbVar4;

  memcpy(in_r0 + 4, in_r1, 2);
  uVar2 = 2;
  if ((in_r0[4] & 3) != 3)
  {
    iVar3 = (uint) * (byte *)((int)in_r1 + 3) * 0x100 + (uint) * (byte *)((int)in_r1 + 2);
    *in_r0 = (char)iVar3;
    in_r0[1] = (char)((uint)iVar3 >> 8);
    iVar3 = (uint) * (byte *)((int)in_r1 + 5) * 0x100 + (uint) * (byte *)((int)in_r1 + 4);
    in_r0[2] = (char)iVar3;
    in_r0[3] = (char)((uint)iVar3 >> 8);
    in_r0[6] = *(undefined *)((int)in_r1 + 6);
    in_r0[7] = *(undefined *)((int)in_r1 + 7);
    pbVar4 = (byte *)((int)in_r1 + 8);
    uVar2 = (uint)(byte)in_r0[5];
    if ((int)(uVar2 << 0x1c) < 0)
    {
      memcpy(in_r0 + 8, pbVar4, 8);
      pbVar4 = (byte *)((int)in_r1 + 0x10);
      uVar2 = (uint)(byte)in_r0[5];
    }
    if ((int)(uVar2 << 0x1b) < 0)
    {
      memcpy(in_r0 + 0x10, pbVar4, 8);
      pbVar4 = pbVar4 + 8;
      uVar2 = (uint)(byte)in_r0[5];
    }
    if ((int)(uVar2 << 0x1f) < 0)
    {
      in_r0[0x18] = *pbVar4;
      pbVar4 = pbVar4 + 1;
    }
    if ((int)(uVar2 << 0x1d) < 0)
    {
      bVar1 = *pbVar4;
      in_r0[0x1a] = bVar1;
      in_r0[0x1b] = pbVar4[1];
      pbVar4 = pbVar4 + 2;
      in_r0[0x1c] = (char)pbVar4;
      in_r0[0x1d] = (char)((uint)pbVar4 >> 8);
      in_r0[0x1e] = (char)((uint)pbVar4 >> 0x10);
      in_r0[0x1f] = (char)((uint)pbVar4 >> 0x18);
      pbVar4 = pbVar4 + (uint)bVar1 * 2;
    }
    if ((int)(uVar2 << 0x1e) < 0)
    {
      pbVar4 = pbVar4 + 0xe;
    }
    uVar2 = (int)pbVar4 - (int)in_r1 & 0xff;
  }
  return uVar2;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void nwkLinkStatusCmdSend(void)

{
  zb_buf_t *in_r0;
  undefined *puVar1;
  undefined *in_r2;
  u8 in_r3;

  puVar1 = (undefined *)tl_bufInitalloc(in_r0, (in_r2[8] & 0x1f) * '\x03' + '\x02');
  *puVar1 = *in_r2;
  puVar1[1] = in_r2[8];
  if ((in_r2[8] & 0x1f) != 0)
  {
    memcpy(puVar1 + 2, *(void **)(in_r2 + 4), ((byte)in_r2[8] & 0x1f) * 3);
  }
  (in_r0->hdr).handle = in_r3;
  nwk_fwdPacket();
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
uint nwk_linkStEntryBuild(void)

{
  ushort uVar1;
  byte bVar2;
  u16 uVar3;
  ushort *in_r0;
  tl_zb_normal_neighbor_entry_t *ptVar4;
  uint in_r1;
  ushort *puVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  ushort *puVar9;
  uint uVar10;
  ushort *puVar11;
  byte bVar12;
  uint uVar13;
  uint uVar14;
  ushort *in;

  uVar10 = 0;
  puVar11 = in_r0;
  for (bVar12 = 0; bVar2 = tl_zbNeighborTableNumGet(), bVar12 < bVar2; bVar12 = bVar12 + 1)
  {
    ptVar4 = tl_zbNeighborEntryGetFromIdx(bVar12);
    if (((ptVar4 != (tl_zb_normal_neighbor_entry_t *)0x0) && (ptVar4->lqi != '\0')) &&
        (((ptVar4->field_0x1e & 0xe) == 0 || ((ptVar4->field_0x1e & 0xe) == 2))))
    {
      uVar3 = tl_zbshortAddrByIdx(ptVar4->addrmapIdx);
      bVar2 = rf_lqi2cost(ptVar4->lqi);
      *(byte *)puVar11 = (byte)uVar3;
      *(byte *)((int)puVar11 + 1) = (byte)((uint)uVar3 >> 8);
      *(byte *)(puVar11 + 1) = 0;
      *(byte *)(puVar11 + 1) = (bVar2 & 7) + (ptVar4->outgoingCost & 7) * '\x10';
      uVar10 = uVar10 + 1 & 0xff;
      if ((in_r1 & 0xff) <= uVar10)
        break;
      puVar11 = (ushort *)((int)puVar11 + 3);
    }
  }
  if (1 < uVar10)
  {
    uVar8 = 1;
    puVar11 = in_r0;
    uVar14 = 0;
    if (1 < uVar10)
    {
      do
      {
        uVar6 = uVar8;
        uVar8 = uVar6;
        puVar9 = puVar11;
        uVar13 = uVar14;
        in = (ushort *)0x0;
        do
        {
          while (true)
          {
            uVar7 = uVar8;
            puVar5 = (ushort *)((int)in_r0 + uVar7 * 3);
            if ((*(byte *)((int)puVar9 + 1) <= *(byte *)((int)puVar5 + 1)) &&
                ((*(byte *)((int)puVar5 + 1) != *(byte *)((int)puVar9 + 1) ||
                  (*(byte *)puVar9 <= *(byte *)puVar5))))
              break;
            uVar8 = uVar7 + 1 & 0xff;
            puVar9 = puVar5;
            uVar13 = uVar7;
            in = puVar5;
            if (uVar10 <= uVar8)
              goto LAB_00014b9a;
          }
          uVar8 = uVar7 + 1 & 0xff;
        } while (uVar8 < uVar10);
      LAB_00014b9a:
        if ((in != (ushort *)0x0) && (uVar13 != uVar14))
        {
          uVar1 = *puVar11;
          bVar12 = *(byte *)(puVar11 + 1);
          uVar8 = (uint)bVar12;
          memcpy(puVar11, in, 3);
          *(byte *)in = (byte)uVar1;
          *(byte *)((int)in + 1) = (byte)((uint)uVar1 >> 8);
          *(byte *)(in + 1) = *(byte *)(in + 1) & 0xf8 | (byte)((uVar8 << 0x1d) >> 0x1d);
          *(byte *)(in + 1) = *(byte *)(in + 1) & 0xf7 | (byte)(((uVar8 << 0x1c) >> 0x1f) << 3);
          *(byte *)(in + 1) = *(byte *)(in + 1) & 0x8f | (byte)(((uVar8 << 0x19) >> 0x1d) << 4);
          *(byte *)(in + 1) = *(byte *)(in + 1) & 0x7f | bVar12 & 0x80;
        }
        puVar11 = (ushort *)((int)puVar11 + 3);
        uVar8 = uVar6 + 1 & 0xff;
        uVar14 = uVar6;
      } while (uVar8 < uVar10);
    }
  }
  return uVar10;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void nwk_linkStPeriodic(void)

{
  u32 uVar1;

  if ((linkStExpiry != '\0') && (linkStExpiry = linkStExpiry + -1, linkStExpiry == '\0'))
  {
    uVar1 = drv_u32Rand();
    linkStTimer = ev_timer_taskPost(tl_zbNwkLinkStatusTimerEvtCb, (void *)0x0, (uVar1 & 0x7f) + 5);
  }
  return;
}
void tl_zbMacMlmeScanConfirmHandler(void *arg)

{
  switch (g_zbNwkCtx._47_1_ >> 4)
  {
  default:
    zb_buf_free((zb_buf_t *)arg);
    break;
  case 1:
    nwk_formationScanCnfHandler();
    break;
  case 3:
    nwk_discoveryScanCnfHandler();
    break;
  case 4:
    nwk_rejoinScanCnfHandler();
    break;
  case 5:
    nwk_directJoinScanCnfHandler();
    break;
  case 7:
    nwk_edScanCnfHandler();
  }
  return;
}
void tl_zbMacMlmeStartConfirmHandler(void *arg)

{
  byte bVar1;

  bVar1 = g_zbNwkCtx._47_1_ >> 4;
  if (bVar1 == 2)
  {
    nwk_startRouterCnfHandler();
  }
  else if (bVar1 == 6)
  {
    nwk_panIdConflictCnfHandler();
  }
  else if (bVar1 == 1)
  {
    nwk_formationStartCnfHandler();
  }
  else
  {
    zb_buf_free((zb_buf_t *)arg);
  }
  return;
}
void tl_zbNwkInit(u8 coldReset)

{
  u32 uVar1;

  memset(&g_zbNwkCtx, 0, 0x4f);
  g_zbNwkCtx._46_1_ = g_zbNwkCtx._46_1_ | 0x10;
  tl_zbNwkAddrMapInit();
  tl_zbNwkNibInit();
  tl_zbNeighborTableInit();
  nwkTxDataPendTabInit();
  nwkBrcTransTabInit();
  nwkRouteDiscTabInit();
  nwkRoutingTabInit();
  uVar1 = drv_u32Rand();
  g_zbInfo.nwkNib.seqNum = (u8)uVar1;
  if (g_zbInfo.macPib.maxBe != 0)
  {
    g_zbInfo.nwkNib.passiveAckTimeout =
        ((0x140 << (uint)g_zbInfo.macPib.maxBe) + -0x140) * (uint)g_zbInfo.macPib.maxCsmaBackoffs;
  }
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void tl_zbNwkLinkStatusCmdHandler(void)

{
  byte bVar1;
  u16 *puVar2;
  u16 uVar3;
  zb_buf_t *in_r0;
  tl_zb_normal_neighbor_entry_t *ptVar4;
  int iVar5;
  short sVar6;
  int in_r1;
  int in_r2;
  uint uVar7;
  u16 *puVar8;
  uint uVar9;
  nebTbl_t *in_stack_ffffffbc;
  nebTbl_t *in_stack_ffffffc0;

  if ((byte)(in_r0->buf[0x1d] - *(char *)(in_r1 + 0x19)) !=
      (byte)((*(byte *)(in_r2 + 8) & 0x1f) * '\x03' + '\x02'))
    goto LAB_00014f9a;
  bVar1 = in_r0->buf[0x27];
  ptVar4 = nwk_neTblGetByShortAddr(*(u16 *)(in_r1 + 2));
  if (ptVar4 == (tl_zb_normal_neighbor_entry_t *)0x0)
  {
    if ((((int)((uint) * (byte *)(in_r1 + 5) << 0x1b) < 0) && (in_r0->buf[0x1c] == '\x02')) &&
        (*(u16 *)(in_r0->buf + 0x14) == *(u16 *)(in_r1 + 2)))
    {
      tl_zbNwkAddrMapAdd(*(u16 *)(in_r1 + 2),
                         (addrExt_t)CONCAT44(in_stack_ffffffc0, in_stack_ffffffbc),
                         (u16 *)(in_r1 + 0x10));
    }
    iVar5 = FUNBBBBK();
    if (iVar5 != 0)
      goto LAB_00014f9a;
    sVar6 = 0;
    if ((*(short *)(in_r1 + 2) == 0) &&
        (sVar6 = *(short *)(in_r1 + 2), (*(byte *)(in_r2 + 8) & 0x1f) != 0))
    {
      puVar2 = *(u16 **)(in_r2 + 4);
      sVar6 = 1;
      if (*puVar2 != g_zbInfo.nwkNib.nwkAddr)
      {
        uVar9 = 0;
        do
        {
          uVar9 = uVar9 + 1 & 0xff;
          if ((*(byte *)(in_r2 + 8) & 0x1f) <= uVar9)
          {
            sVar6 = 0;
            goto LAB_00015152;
          }
        } while (CONCAT11(*(undefined *)((int)puVar2 + uVar9 * 3 + 1),
                          *(undefined *)(uVar9 * 3 + (int)puVar2)) != g_zbInfo.nwkNib.nwkAddr);
        sVar6 = 1;
      }
    }
  LAB_00015152:
    ptVar4 = tl_zbNeighborTableUpdate((tl_zb_normal_neighbor_entry_t *)&stack0xffffffbc, (u8)sVar6);
    if (ptVar4 == (tl_zb_normal_neighbor_entry_t *)0x0)
      goto LAB_00014f9a;
  }
  else
  {
    ptVar4->age = '\0';
    ptVar4->lqi = (u8)((int)((uint)bVar1 + (uint)ptVar4->lqi) >> 1);
    ptVar4->field_0x1e =
        ptVar4->field_0x1e & 0xf1 | ('\x01' - (*(short *)(in_r1 + 2) == 0)) * '\x02';
  }
  uVar7 = (uint) * (byte *)(in_r2 + 8);
  uVar9 = 0;
  if ((*(byte *)(in_r2 + 8) & 0x1f) == 0)
  {
  LAB_00015048:
    if ((uVar7 & 0x1f) != uVar9)
      goto LAB_00014f9a;
  }
  else
  {
    puVar2 = *(u16 **)(in_r2 + 4);
    uVar3 = *puVar2;
    puVar8 = puVar2;
    while (uVar3 != g_zbInfo.nwkNib.nwkAddr)
    {
      uVar9 = uVar9 + 1 & 0xff;
      if ((uVar7 & 0x1f) <= uVar9)
        goto LAB_00015048;
      puVar8 = (u16 *)((int)puVar2 + uVar9 * 3);
      uVar3 = *puVar8;
    }
    ptVar4->outgoingCost = (byte)(((uint) * (byte *)(puVar8 + 1) << 0x1d) >> 0x1d);
    uVar7 = (uint) * (byte *)(in_r2 + 8);
    if ((uVar7 & 0x1f) != uVar9)
      goto LAB_00014f9a;
  }
  if ((uVar7 & 0x60) == 0x60)
  {
    ptVar4->outgoingCost = '\0';
  }
LAB_00014f9a:
  zb_buf_free(in_r0);
  return;
}
void tl_zbNwkLinkStatusStart(void)

{
  tl_zbNwkSendLinkStatus();
  if (g_zbInfo.nwkNib.linkStatusPeriod != '\0')
  {
    linkStExpiry = g_zbInfo.nwkNib.linkStatusPeriod;
  }
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void tl_zbNwkLinkStatusStop(void)

{
  if (linkStExpiry != '\0')
  {
    linkStExpiry = '\0';
  }
  if (linkStTimer != 0)
  {
    ev_timer_taskCancel((ev_timer_event_t **)&linkStTimer);
  }
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
undefined4 tl_zbNwkLinkStatusTimerEvtCb(void)

{
  if ((int)((uint)g_zbNwkCtx._45_1_ << 0x1d) < 0)
  {
    T_DBG_linkStatus = T_DBG_linkStatus + '\x01';
    tl_zbNwkNeighborTabAging();
    tl_zbNwkLinkStatusStart();
  }
  linkStTimer = 0;
  return 0xfffffffe;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void tl_zbNwkNeighborTabAging(void)

{
  byte bVar1;
  tl_zb_normal_neighbor_entry_t *ptVar2;
  byte bVar3;
  byte idx;

  bVar1 = tl_zbNeighborTableNumGet();
  if (bVar1 != 0)
  {
    idx = 0;
    do
    {
      ptVar2 = tl_zbNeighborEntryGetFromIdx(idx);
      if ((((ptVar2 != (tl_zb_normal_neighbor_entry_t *)0x0) && ((ptVar2->field_0x1e & 0xe) != 4)) && (g_zbInfo.nwkNib.addrAlloc != '\0')) &&
          (bVar3 = ptVar2->age + 1, ptVar2->age = bVar3, g_zbInfo.nwkNib.routerAgeLimit <= bVar3))
      {
        ptVar2->outgoingCost = '\0';
        ptVar2->lqi = '\0';
        ptVar2->age = '\0';
        ptVar2->transFailure = '\0';
        g_sysDiags.neighborStale = g_sysDiags.neighborStale + 1;
      }
      idx = idx + 1;
    } while (idx < bVar1);
  }
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void tl_zbNwkNibInit(void)

{
  char in_r0;
  device_type_t dVar1;

  if (in_r0 == '\0')
  {
    g_zbNwkCtx._45_1_ = g_zbNwkCtx._45_1_ & 0xfe;
    dVar1 = af_nodeDevTypeGet();
    if (dVar1 == DEVICE_TYPE_COORDINATOR)
    {
      g_zbNwkCtx._45_1_ = g_zbNwkCtx._45_1_ | 0x10;
    }
  }
  else
  {
    memcpy(&g_zbInfo.nwkNib, &nwkNibDefault, 0x3c);
    g_zbInfo.nwkNib.extPANId[0] = '\0';
    g_zbInfo.nwkNib.extPANId[1] = '\0';
    g_zbInfo.nwkNib.extPANId[2] = '\0';
    g_zbInfo.nwkNib.extPANId[3] = '\0';
    g_zbInfo.nwkNib.extPANId[4] = '\0';
    g_zbInfo.nwkNib.extPANId[5] = '\0';
    g_zbInfo.nwkNib.extPANId[6] = '\0';
    g_zbInfo.nwkNib.extPANId[7] = '\0';
    g_zbNwkCtx._45_1_ = g_zbNwkCtx._45_1_ | 1;
  }
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
uint tl_zbNwkReportCmdHandler(void)

{
  byte bVar1;
  zb_buf_t *in_r0;
  uint uVar2;
  u16 *in_r1;

  if (*in_r1 == g_zbInfo.nwkNib.nwkAddr)
  {
    uVar2 = nwkReportCmdHandler();
  }
  else if (*(char *)(in_r1 + 3) == '\0')
  {
    bVar1 = zb_buf_free(in_r0);
    uVar2 = (uint)bVar1;
  }
  else
  {
    uVar2 = nwkReportCmdSend();
  }
  return uVar2;
}
// WARNING: Could not reconcile some variable overlaps
void tl_zbNwkSendLinkStatus(void)

{
  byte bVar1;
  uint uVar2;
  byte bVar3;
  u8 uVar4;
  bool bVar5;
  char cVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  u8 *puVar11;
  u8 *puVar12;
  uint local_68;
  u8 *puStack_64;
  undefined local_60[4];
  undefined4 uStack_5c;
  undefined4 uStack_58;
  undefined4 uStack_54;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  uint uStack_48;
  u8 *puStack_44;
  undefined4 local_40;
  u8 *puStack_3c;
  uint uStack_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined2 local_28;
  undefined local_26;
  uint extraout_r0;

  bVar3 = tl_zbNeighborTableRouterValidNumGet();
  extraout_r0 = (uint)bVar3;
  puStack_64 = (u8 *)0x0;
  if (extraout_r0 == 0)
  {
  LAB_00014cee:
    local_68 = 1;
    uVar10 = 0;
  }
  else
  {
    uVar9 = ev_buf_getFreeMaxSize();
    uVar10 = extraout_r0;
    if (uVar9 < extraout_r0 * 3)
    {
      uVar10 = FUN_0000162c(uVar9, 3);
      uVar10 = uVar10 & 0xff;
    }
    puStack_64 = ev_buf_allocate((u16)(uVar10 * 0x30000 >> 0x10));
    if (puStack_64 == (u8 *)0x0)
    {
      sys_exceptionPost(0x162, '5');
      return;
    }
    uVar10 = nwk_linkStEntryBuild();
    if (uVar10 == 0)
      goto LAB_00014cee;
    uVar9 = FUN_0000162c(uVar10, 0x1a);
    cVar6 = FUN_00001628(uVar10, 0x1a);
    local_68 = (uVar9 & 0xff) + (uint)(cVar6 != '\0') & 0xff;
    if (local_68 == 0)
      goto LAB_00014e46;
  }
  uVar9 = 0;
  puVar12 = puStack_64;
  while (iVar7 = c1(), iVar7 != 0)
  {
    local_60 = (undefined[4])0x0;
    uStack_5c = 0;
    uStack_58 = 0;
    uStack_54 = 0;
    uStack_50 = 0;
    uStack_4c = 0;
    uStack_48 = 0;
    puStack_44 = (u8 *)0x0;
    uVar8 = 0;
    if (((ss_ib._62_1_ & 8) != 0) && (uVar8 = 0, (ss_ib._62_1_ & 7) != 0))
    {
      bVar5 = ss_keyPreconfigured();
      uVar8 = (uint)(bVar5 != false);
    }
    uVar2 = (ushort)((ushort)uStack_5c & 0xff00 | (ushort)uStack_5c & 0xc0 | 1 | 0x1008) &
            0xfffff7ff;
    uStack_5c._1_1_ = (byte)(uVar2 >> 8);
    uStack_5c._0_2_ =
        (nwkFrameCtrl_t)CONCAT11(uStack_5c._1_1_ & 0xfd | (byte)(uVar8 << 1), (char)uVar2);
    uStack_5c = uStack_5c & 0xffff0000 | (uint)(ushort)uStack_5c._0_2_;
    memcpy(&uStack_50, g_zbInfo.macPib.extAddress, 8);
    local_60 = (undefined[4])CONCAT22(g_zbInfo.nwkNib.nwkAddr, 0xfffb);
    uStack_5c = CONCAT13(g_zbInfo.nwkNib.seqNum, CONCAT12(1, uStack_5c._0_2_));
    g_zbInfo.nwkNib.seqNum = g_zbInfo.nwkNib.seqNum + '\x01';
    uVar4 = getNwkHdrSize((nwk_hdr_t *)local_60);
    uStack_48._0_2_ = CONCAT11(uVar4, uStack_48._0_1_);
    uStack_48 = uStack_48 & 0xffff0000 | (uint)(ushort)uStack_48;
    uVar8 = uVar10;
    if (0x1a < (uVar10 & 0xff))
    {
      uVar8 = 0x1a;
    }
    uStack_34 = 0;
    uStack_30 = 0;
    uStack_2c = 0;
    local_28 = 0;
    local_26 = 0;
    local_40 = 8;
    uStack_38._0_1_ = (byte)uVar8 & 0x1f;
    bVar3 = (byte)uVar9;
    bVar1 = bVar3 - (char)(local_68 - 1);
    uStack_38 = (uint)(byte)((bVar1 + ~bVar1 + (local_68 - 1 <= uVar9)) * '@' |
                             (~bVar3 + bVar3) * ' ' & 0xbf | (byte)uStack_38);
    puVar11 = puVar12;
    if (puVar12 != (u8 *)0x0)
    {
      puVar11 = puVar12 + (uVar8 & 0xff) * 3;
    }
    puStack_3c = puVar12;
    nwkLinkStatusCmdSend();
    uVar9 = uVar9 + 1 & 0xff;
    if (local_68 <= uVar9)
      break;
    uVar10 = uVar10 - (uVar8 & 0xff) & 0xff;
    puVar12 = puVar11;
  }
  if (puStack_64 == (u8 *)0x0)
  {
    return;
  }
LAB_00014e46:
  ev_buf_free(puStack_64);
  return;
}
void tl_zbNwkSendNwkStatusCmd(void *arg, nwk_hdr_t *pNwkHdr, nwkCmd_t *pNwkStatus, u8 handle)

{
  u16 uVar1;
  nwk_cmdId_t *pnVar2;
  int iVar3;

  if ((pNwkStatus->field2_0x4).rreq.dstIeeeAddr[2] == '\f')
  {
    if ((pNwkHdr->srcAddr != g_zbInfo.nwkNib.nwkAddr) &&
        (iVar3 = nwkRoutingTabEntryDstFind(), iVar3 != 0))
    {
      if ((*(u16 *)(iVar3 + 2) !=
           CONCAT11(g_zbNwkCtx.manyToOneRepair.senderAddr._1_1_,
                    (undefined)g_zbNwkCtx.manyToOneRepair.senderAddr)) &&
          (*(u16 *)(iVar3 + 2) != pNwkHdr->srcAddr))
        goto LAB_00015214;
      nwkRoutingTabEntryClear();
    }
    iVar3 = nwkVaildNeighborToFwd();
    if ((iVar3 == 0) || (pNwkHdr->srcAddr == g_zbInfo.nwkNib.nwkAddr))
    {
      do
      {
        iVar3 = tl_zbNeighborTabSearchForRouter();
        if (iVar3 == 0)
          break;
        uVar1 = tl_zbshortAddrByIdx(*(u16 *)(iVar3 + 0x16));
      } while (((uint)CONCAT11(g_zbNwkCtx.manyToOneRepair.senderAddr._1_1_,
                               (undefined)g_zbNwkCtx.manyToOneRepair.senderAddr) == (uint)uVar1) ||
               ((uint)(g_zbNwkCtx._72_4_ << 8) >> 0x10 == (uint)uVar1));
    }
    pnVar2 = (nwk_cmdId_t *)tl_bufInitalloc((zb_buf_t *)arg, '\x04');
    *pnVar2 = pNwkStatus->cmdId;
    pnVar2[1] = (pNwkStatus->field2_0x4).rreq.dstIeeeAddr[2];
    memcpy(pnVar2 + 2, &pNwkStatus->field2_0x4, 2);
    *(u8 *)((int)arg + 0xc1) = handle;
    nwk_tx();
  }
  else
  {
  LAB_00015214:
    pnVar2 = (nwk_cmdId_t *)tl_bufInitalloc((zb_buf_t *)arg, '\x04');
    *pnVar2 = pNwkStatus->cmdId;
    pnVar2[1] = (pNwkStatus->field2_0x4).rreq.dstIeeeAddr[2];
    memcpy(pnVar2 + 2, &pNwkStatus->field2_0x4, 2);
    *(u8 *)((int)arg + 0xc1) = handle;
    nwk_fwdPacket();
  }
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void tl_zbNwkStatusCmdHandler(void)

{
  byte bVar1;
  zb_buf_t *in_r0;
  tl_zb_normal_neighbor_entry_t *ptVar2;
  int iVar3;
  ushort uVar4;
  nwk_hdr_t *in_r1;
  nwkCmd_t *in_r2;
  u16 uVar5;

  bVar1 = (in_r2->field2_0x4).rreq.dstIeeeAddr[2];
  if (bVar1 == 0)
  {
  LAB_00015376:
    uVar4 = in_r1->dstAddr;
    uVar5 = g_zbInfo.nwkNib.nwkAddr;
  }
  else if (bVar1 < 3)
  {
    ptVar2 = nwk_neTblGetByShortAddr(*(u16 *)&in_r2->field2_0x4);
    if ((*(u16 *)&in_r2->field2_0x4 == g_zbInfo.nwkNib.nwkAddr) ||
        ((ptVar2 != (tl_zb_normal_neighbor_entry_t *)0x0 && ((ptVar2->field_0x1e & 0x7e) == 0x14))))
    {
      iVar3 = nwkRoutingTabEntryDstActiveGet();
      if (iVar3 != 0)
      {
        *(undefined *)(iVar3 + 4) = 3;
      }
      uVar4 = in_r1->dstAddr;
      uVar5 = g_zbInfo.nwkNib.nwkAddr;
    }
    else
    {
      uVar4 = in_r1->dstAddr;
      uVar5 = g_zbInfo.nwkNib.nwkAddr;
    }
  }
  else
  {
    if (bVar1 != 0xc)
      goto LAB_00015376;
    uVar4 = in_r1->dstAddr;
    uVar5 = uVar4;
    if ((uVar4 != g_zbInfo.nwkNib.nwkAddr) &&
        (uVar5 = g_zbInfo.nwkNib.nwkAddr, in_r1->radius != '\0'))
    {
      g_zbNwkCtx.manyToOneRepair.senderAddr._0_1_ = (undefined) * (undefined2 *)(in_r0->buf + 0x14);
      g_zbNwkCtx.manyToOneRepair.senderAddr._1_1_ =
          (undefined)((ushort) * (undefined2 *)(in_r0->buf + 0x14) >> 8);
      uVar4 = in_r1->dstAddr;
    }
  }
  if ((uVar4 & 0xfff8) == 0xfff8)
  {
    if (*(u16 *)&in_r2->field2_0x4 == uVar5)
      goto LAB_000153c2;
    if (in_r1->radius == '\0')
    {
      tl_zbNwkNlmeNwkStatusInd(in_r0, *(u16 *)&in_r2->field2_0x4, (in_r2->field2_0x4).rreq.dstIeeeAddr[2]);
      return;
    }
    iVar3 = nwkBrcTimerStart();
    if (iVar3 != 0)
    {
      iVar3 = nwkBrcTransEntryFind();
      if (iVar3 != 0)
      {
        nwkBrcTransTabEntryClear();
      }
      goto LAB_000153c2;
    }
    uVar4 = in_r1->dstAddr;
    uVar5 = g_zbInfo.nwkNib.nwkAddr;
    if ((uVar4 & 0xfff8) == 0xfff8)
      goto LAB_000154d0;
  }
  if (uVar4 == uVar5)
  {
  LAB_000154d0:
    tl_zbNwkNlmeNwkStatusInd(in_r0, *(u16 *)&in_r2->field2_0x4, (in_r2->field2_0x4).rreq.dstIeeeAddr[2]);
    return;
  }
  if (in_r1->radius != '\0')
  {
    tl_zbNwkSendNwkStatusCmd(in_r0, in_r1, in_r2, 0xc9);
    return;
  }
LAB_000153c2:
  zb_buf_free(in_r0);
  return;
}

// WARNING: Unknown calling convention -- yet parameter storage is locked
// Perhaps "tl_zbNwkTaskRun()" might be a good name?  Or "start listening" or similar.
byte FUNBBBBJ(void)

{
  code *in_r3;

  (*in_r3)();
  return g_zbNwkCtx._45_1_ & 1;
}

void tl_zbNwkTaskProc(void)
{
  tl_zb_task_t *ptVar1;
  int iVar2;
  g_zbNwkEventTbl_t *pgVar3;
  tl_zb_task_t tStack_20;

  ptVar1 = tl_zbTaskQPop(nwkFromHighTblQueue,&tStack_20);
  if ((ptVar1 != (tl_zb_task_t *)0x0) && (iVar2 = 0, tStack_20.data != (void *)0x0)) {
    pgVar3 = &g_zbNwkEventFromHighTbl;
    do {
      if ((pgVar3->primitive == *(u8 *)((int)tStack_20.data + 0xc0)) &&
         ((g_zbNwkEventFromHighTbl[iVar2].eventHandler != NULL)) {
        g_zbNwkEventFromHighTbl[iVar2].eventHandler(tStack_20.data);
        break;
      }
      iVar2 = iVar2 + 1;
      pgVar3 = pgVar3 + 1;
    } while (iVar2 != ZB_NWK_EVENT_FROM_HIGH_TBL_SIZE);
  }
  ptVar1 = tl_zbTaskQPop(nwkFromMacTblQueue,&tStack_20);
  if ((ptVar1 != (tl_zb_task_t *)0x0) && (tStack_20.data != (void *)0x0)) {
    pgVar3 = &g_zbNwkEventFromMacTbl;
    iVar2 = 0;
    do {
      if ((pgVar3->primitive == *(u8 *)((int)tStack_20.data + 0xc0)) &&
         ((g_zbNwkEventFromMacTbl[iVar2].eventHandle != NULL)) {
        g_zbNwkEventFromMacTbl[iVar2].eventHandler(tStack_20.data);
        return;
      }
      iVar2 = iVar2 + 1;
      pgVar3 = pgVar3 + 1;
    } while (iVar2 != ZB_NWK_EVENT_FROM_MAC_TBL_SIZE);
  }
  return;
}
