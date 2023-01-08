// WARNING: Unknown calling convention -- yet parameter storage is locked
void nwk_associateJoin(void)

{
  char cVar1;
  undefined2 uVar2;
  undefined *in_r0;
  int iVar3;
  byte bVar4;

  bVar4 = g_zbNwkCtx._47_1_ & 0xf0;
  if ((g_zbNwkCtx._47_1_ & 0xf0) == 0)
  {
    iVar3 = tl_zbNwkParentChoose();
    if (iVar3 == 0)
    {
      nwk_nlmeJoinCnf();
    }
    else
    {
      g_zbNwkCtx.join._0_1_ = (undefined)iVar3;
      g_zbNwkCtx.join._1_1_ = (undefined)((uint)iVar3 >> 8);
      g_zbNwkCtx.join._2_1_ = (undefined)((uint)iVar3 >> 0x10);
      g_zbNwkCtx.join._3_1_ = (undefined)((uint)iVar3 >> 0x18);
      g_zbInfo.macPib.panId._0_1_ = (undefined) * (undefined2 *)(iVar3 + 0x12);
      g_zbInfo.macPib.panId._1_1_ = (undefined)((ushort) * (undefined2 *)(iVar3 + 0x12) >> 8);
      g_zbInfo.nwkNib.parentInfo = bVar4;
      memcpy(g_zbInfo.nwkNib.extPANId, in_r0, 8);
      g_zbInfo.nwkNib.capabilityInfo = *(capability_info_t *)(in_r0 + 0xe);
      g_zbInfo.macPib.rxOnWhenIdle = (u8)(((uint)(byte)in_r0[0xe] << 0x1c) >> 0x1f);
      memset(in_r0, 0, 0x19);
      *in_r0 = *(undefined *)(iVar3 + 0x15);
      uVar2 = *(undefined2 *)(iVar3 + 0x12);
      in_r0[2] = (char)uVar2;
      in_r0[3] = (char)((ushort)uVar2 >> 8);
      *(capability_info_t *)(in_r0 + 0xd) = g_zbInfo.nwkNib.capabilityInfo;
      cVar1 = *(char *)(iVar3 + 0x14);
      in_r0[0xc] = cVar1;
      if (cVar1 == '\x02')
      {
        uVar2 = *(undefined2 *)(iVar3 + 0x10);
        in_r0[4] = (char)uVar2;
        in_r0[5] = (char)((ushort)uVar2 >> 8);
      }
      else if (cVar1 == '\x03')
      {
        memcpy(in_r0 + 4, (void *)(iVar3 + 8), 8);
      }
      tl_zbPrimitivePost('\x02', 'E', in_r0);
    }
  }
  else
  {
    nwk_nlmeJoinCnf();
  }
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void nwk_directJoinScanCnfHandler(void)

{
  zb_nwk_status_t zVar1;
  u16 uVar2;
  zb_buf_t *in_r0;
  tl_zb_normal_neighbor_entry_t *ptVar3;
  int iVar4;
  nebTbl_t *in_stack_ffffffb8;
  nebTbl_t *in_stack_ffffffbc;
  undefined auStack_24[10];
  undefined2 local_1a;

  if (in_r0->buf[1] == '\x03')
  {
    if (in_r0->buf[0] == '\0')
    {
      ptVar3 = tl_zbNeighborTableSearchForParent();
      if (ptVar3 != (tl_zb_normal_neighbor_entry_t *)0x0)
      {
        tl_zbExtAddrByIdx(ptVar3->addrmapIdx,
                          (addrExt_t)CONCAT44(in_stack_ffffffbc, in_stack_ffffffb8));
        uVar2 = tl_zbshortAddrByIdx(ptVar3->addrmapIdx);
        iVar4 = memcmp(auStack_24, g_zbInfo.macPib.coordExtAddress, 8);
        if ((iVar4 != 0) || (g_zbInfo.macPib.coordShortAddress != uVar2))
        {
          tl_zbNeighborTableDelete(ptVar3);
          g_zbNwkCtx._46_1_ = g_zbNwkCtx._46_1_ | 0x7f;
        }
      }
      local_1a = 0;
      zVar1 = tl_zbNwkAddrMapAdd(g_zbInfo.macPib.coordShortAddress,
                                 (addrExt_t)CONCAT44(in_stack_ffffffbc, in_stack_ffffffb8),
                                 (u16 *)g_zbInfo.macPib.coordExtAddress);
      if ((zVar1 == NWK_STATUS_SUCCESS) &&
          (ptVar3 = tl_zbNeighborTableUpdate((tl_zb_normal_neighbor_entry_t *)&stack0xffffffb8, '\x01'),
           ptVar3 != (tl_zb_normal_neighbor_entry_t *)0x0))
      {
        nwk_nlmeJoinCnf();
        return;
      }
      nwk_nlmeJoinCnf();
    }
    else
    {
      nwk_nlmeJoinCnf();
    }
  }
  else
  {
    zb_buf_free(in_r0);
  }
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void nwk_nlmeJoinCnf(void)

{
  u16 uVar1;
  undefined *in_r0;
  char in_r1;

  in_r0[2] = in_r1;
  if (in_r1 == '\0')
  {
    in_r0[3] = g_zbInfo.macPib.phyChannelCur;
    uVar1 = g_zbInfo.nwkNib.nwkAddr;
    *in_r0 = (char)g_zbInfo.nwkNib.nwkAddr;
    in_r0[1] = (char)(uVar1 >> 8);
    memcpy(in_r0 + 4, g_zbInfo.nwkNib.extPANId, 8);
  }
  g_zbNwkCtx._47_1_ = g_zbNwkCtx._47_1_ & 0xf;
  tl_zbTaskPost(zdo_nlme_join_confirm, in_r0);
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void nwk_rejoinCmdSendCnf(void)

{
  zb_buf_t *in_r0;
  u32 t_ms;

  if ((g_zbNwkCtx._47_1_ & 0xf0) == 0x40)
  {
    if ((in_r0->buf[9] != ' ') && (in_r0->buf[9] != '\0'))
    {
      nwk_rejoinReq();
      return;
    }
    g_zbNwkCtx._47_1_ = g_zbNwkCtx._47_1_ & 0xf0 | 1;
    if (rejoinRespTimeoutEvt == (ev_timer_event_t *)0x0)
    {
      t_ms = FUN_00001624((uint)g_zbInfo.macPib.respWaitTime * 0x1400, 1000);
      rejoinRespTimeoutEvt = ev_timer_taskPost(tl_zbNlmeRejoinRespTimeoutCb, (void *)0x0, t_ms);
    }
  }
  zb_buf_free(in_r0);
  return;
}
// WARNING: Could not reconcile some variable overlaps
// WARNING: Unknown calling convention -- yet parameter storage is locked
void nwk_rejoinReq(void)

{
  uint uVar1;
  u8 uVar2;
  bool bVar3;
  int iVar4;
  int iVar5;
  undefined local_58[8];
  undefined4 uStack_50;
  undefined4 uStack_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;
  uint uStack_40;
  u8 *puStack_3c;
  undefined4 local_38;
  uint uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  undefined2 local_20;
  undefined local_1e;

  local_38 = 0;
  uStack_34 = 0;
  uStack_30 = 0;
  uStack_2c = 0;
  uStack_28 = 0;
  uStack_24 = 0;
  local_20 = 0;
  local_1e = 0;
  local_58._0_4_ = 0;
  local_58._4_4_ = 0;
  uStack_50 = 0;
  uStack_4c = 0;
  uStack_48 = 0;
  uStack_44 = 0;
  uStack_40 = 0;
  puStack_3c = (u8 *)0x0;
  iVar4 = tl_zbNwkParentChoose();
  if (iVar4 == 0)
  {
    nwk_nlmeJoinCnf();
  }
  else
  {
    g_zbNwkCtx.join._0_1_ = (undefined)iVar4;
    g_zbNwkCtx.join._1_1_ = (undefined)((uint)iVar4 >> 8);
    g_zbNwkCtx.join._2_1_ = (undefined)((uint)iVar4 >> 0x10);
    g_zbNwkCtx.join._3_1_ = (undefined)((uint)iVar4 >> 0x18);
    tl_zbMacChannelSet(*(u8 *)(iVar4 + 0x15));
    g_zbInfo.macPib.panId._0_1_ = *(undefined *)(iVar4 + 0x12);
    g_zbInfo.macPib.panId._1_1_ = *(undefined *)(iVar4 + 0x13);
    iVar5 = 0;
    g_zbInfo.nwkNib.panId._0_1_ = (undefined)g_zbInfo.macPib.panId;
    g_zbInfo.nwkNib.panId._1_1_ = g_zbInfo.macPib.panId._1_1_;
    if ((((int)((uint)ss_ib._62_1_ << 0x1c) < 0) && ((ss_ib._62_1_ & 7) != 0)) &&
        (bVar3 = ss_keyPreconfigured(), bVar3 != false))
    {
      iVar5 = ~(aps_ib._18_1_ & 1) + (aps_ib._18_1_ & 1) + 1;
    }
    local_38 = CONCAT31(local_38._1_3_, 6);
    uVar1 = (uint)(byte)g_zbInfo.nwkNib.capabilityInfo;
    if (g_zbInfo.nwkNib.addrAlloc == '\x02')
    {
      uVar1 = uVar1 & 0xffffff7f;
    }
    uStack_34 = uStack_34 & 0xffffff00 | uVar1;
    local_58._4_4_ = (uint)((ushort)local_58._4_4_ & 0xfe00);
    local_58._0_4_ = CONCAT22(g_zbInfo.nwkNib.nwkAddr, *(undefined2 *)(iVar4 + 0x10));
    local_58._4_4_ =
        CONCAT13(g_zbInfo.nwkNib.seqNum,
                 CONCAT12(1, (((local_58[5] & 0xfd | (byte)(iVar5 << 1)) & 0xfb | 0x10) & 0xf7) << 8 | 9));
    g_zbInfo.nwkNib.seqNum = g_zbInfo.nwkNib.seqNum + '\x01';
    memcpy(&uStack_48, g_zbInfo.macPib.extAddress, 8);
    uVar2 = getNwkHdrSize((nwk_hdr_t *)local_58);
    uStack_40._0_2_ = CONCAT11(uVar2, uStack_40._0_1_);
    uStack_40 = uStack_40 & 0xffff0000 | (uint)(ushort)uStack_40;
    tl_zbNwkSendRejoinReqCmd();
  }
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void nwk_rejoinScanCnfHandler(void)

{
  zb_buf_t *in_r0;
  u32 uVar1;
  uint uVar2;

  if (in_r0->buf[1] == '\x01')
  {
    if (in_r0->buf[0] == '\0')
    {
      uVar2 = (uint)g_zbInfo.nwkNib.nwkAddr;
      while ((uVar2 == 0 || ((uVar2 & 0xfff8) == 0xfff8)))
      {
        uVar1 = drv_u32Rand();
        g_zbInfo.macPib.shortAddress._0_1_ = (undefined)uVar1;
        g_zbInfo.macPib.shortAddress._1_1_ = (undefined)(uVar1 >> 8);
        g_zbInfo.nwkNib.nwkAddr = (u16)uVar1;
        uVar2 = uVar1 & 0xffff;
      }
      memcpy(g_zbInfo.nwkNib.ieeeAddr, g_zbInfo.macPib.extAddress, 8);
      nwk_rejoinReq();
    }
    else
    {
      nwk_nlmeJoinCnf();
    }
  }
  else
  {
    zb_buf_free(in_r0);
  }
  return;
}
void tl_zbMacMlmeAssociateConfirmHandler(void *arg)

{
  ushort shortAddr;
  anon_union_4_2_bfd4ae01_for_join aVar1;
  zb_nwk_status_t zVar2;
  zb_nwk_status_t zVar3;
  tl_zb_normal_neighbor_entry_t *ptVar4;
  nebTbl_t *in_stack_ffffffb4;
  nebTbl_t *in_stack_ffffffb8;

  aVar1.pAssocJoinParent = g_zbNwkCtx.join.pAssocJoinParent;
  if (*(char *)((int)arg + 10) == '\0')
  {
    g_zbInfo.nwkNib.updateId = (g_zbNwkCtx.join.pAssocJoinParent)->nwkUpdateId;
    g_zbInfo.nwkNib.depth =
        (byte)(((uint)(byte)(g_zbNwkCtx.join.pAssocJoinParent)->field_0x16 << 0x1c) >> 0x1c) +
        (((byte)(g_zbNwkCtx.join.pAssocJoinParent)->field_0x16 & 0xf) <
         (uint)g_zbInfo.nwkNib.maxDepth);
    g_zbInfo.nwkNib.panId._0_1_ = (undefined)(g_zbNwkCtx.join.pAssocJoinParent)->panId;
    g_zbInfo.nwkNib.panId._1_1_ = (undefined)((g_zbNwkCtx.join.pAssocJoinParent)->panId >> 8);
    memcpy(g_zbInfo.nwkNib.extPANId, g_zbNwkCtx.join.pAssocJoinParent, 8);
    shortAddr = *(ushort *)((int)arg + 8);
    g_zbInfo.macPib.shortAddress._0_1_ = (undefined)shortAddr;
    g_zbInfo.macPib.shortAddress._1_1_ = (undefined)((uint)shortAddr >> 8);
    g_zbInfo.nwkNib.nwkAddr._0_1_ = (undefined)g_zbInfo.macPib.shortAddress;
    g_zbInfo.nwkNib.nwkAddr._1_1_ = g_zbInfo.macPib.shortAddress._1_1_;
    memcpy(g_zbInfo.nwkNib.ieeeAddr, g_zbInfo.macPib.extAddress, 8);
    g_zbInfo.macPib.coordShortAddress = (aVar1.pAssocJoinParent)->shortAddr;
    memcpy(g_zbInfo.macPib.coordExtAddress, arg, 8);
    zVar2 = tl_zbNwkAddrMapAdd(shortAddr, (addrExt_t)CONCAT44(in_stack_ffffffb8, in_stack_ffffffb4),
                               (u16 *)g_zbInfo.macPib.extAddress);
    zVar3 = tl_zbNwkAddrMapAdd(g_zbInfo.macPib.coordShortAddress,
                               (addrExt_t)CONCAT44(in_stack_ffffffb8, in_stack_ffffffb4),
                               (u16 *)g_zbInfo.macPib.coordExtAddress);
    if (((zVar2 | zVar3) == 0) &&
        (ptVar4 = tl_zbNeighborTableUpdate((tl_zb_normal_neighbor_entry_t *)&stack0xffffffb4, '\x01'),
         ptVar4 != (tl_zb_normal_neighbor_entry_t *)0x0))
    {
      g_zbNwkCtx._47_1_ = g_zbNwkCtx._47_1_ & 0xf0 | 1;
      nwk_nlmeJoinCnf();
    }
    else
    {
      nwk_nlmeJoinCnf();
    }
  }
  else
  {
    memset(arg, 0, 0x10);
    *(capability_info_t *)((int)arg + 0xe) = g_zbInfo.nwkNib.capabilityInfo;
    memcpy(arg, g_zbInfo.nwkNib.extPANId, 8);
    nwk_associateJoin();
  }
  return;
}
// WARNING: Could not reconcile some variable overlaps
void tl_zbMacMlmeAssociateIndicationHandler(void *arg)

{
  int iVar1;
  undefined auStack_28[10];
  undefined2 local_1e;

  memcpy(auStack_28, arg, 8);
  local_1e = 0xfffe;
  iVar1 = tl_zbNwkJoinAccept_clone_0();
  if (iVar1 == 0x20)
  {
    zb_buf_free((zb_buf_t *)arg);
  }
  else
  {
    if (iVar1 == 0)
    {
      g_sysDiags.joinIndication = g_sysDiags.joinIndication + 1;
    }
    *(char *)((int)arg + 10) = (char)iVar1;
    *(undefined *)arg = (undefined)local_1e;
    *(undefined *)((int)arg + 1) = local_1e._1_1_;
    memcpy((void *)((int)arg + 2), auStack_28, 8);
    tl_zbPrimitivePost('\x02', 'H', arg);
  }
  return;
}
void tl_zbMacMlmeCommStatusIndicationHandler(void *arg)

{
  char cVar1;
  byte bVar2;
  byte bVar3;
  u16 uVar4;
  tl_zb_normal_neighbor_entry_t *ptVar5;
  undefined in_stack_ffffffe0;
  undefined7 in_stack_ffffffe1;
  u16 auStack_16[3];

  cVar1 = *(char *)((int)arg + 0x15);
  if (*(char *)((int)arg + 0x13) == '\x03')
  {
    ptVar5 = tl_zbNeighborTableSearchFromExtAddr(auStack_16, (addrExt_t)CONCAT71(in_stack_ffffffe1, in_stack_ffffffe0),
                                                 (u16 *)((int)arg + 0xb));
  }
  else
  {
    ptVar5 = tl_zbNeighborTableSearchFromShortAddr(*(u16 *)((int)arg + 0xb),
                                                   (addrExt_t)CONCAT71(in_stack_ffffffe1, in_stack_ffffffe0),
                                                   (u16 *)&stack0xffffffe0);
  }
  if ((ptVar5 == (tl_zb_normal_neighbor_entry_t *)0x0) ||
      ((*(char *)((int)arg + 0x14) != ' ' && (*(char *)((int)arg + 0x14) != '\0'))))
  {
    zb_buf_free((zb_buf_t *)arg);
  }
  else
  {
    tl_zbNwkBeaconPayloadUpdate();
    tl_zbExtAddrByIdx(ptVar5->addrmapIdx, (addrExt_t)CONCAT71(in_stack_ffffffe1, in_stack_ffffffe0));
    uVar4 = tl_zbshortAddrByIdx(ptVar5->addrmapIdx);
    *(char *)((int)arg + 8) = (char)uVar4;
    *(char *)((int)arg + 9) = (char)((uint)uVar4 >> 8);
    bVar2 = ptVar5->field_0x1e & 0xe;
    bVar3 = bVar2 - 2;
    *(byte *)((int)arg + 10) =
        *(byte *)((int)arg + 10) & 0xfd | (bVar3 + ~bVar3 + (1 < bVar2)) * '\x02';
    *(byte *)((int)arg + 10) =
        *(byte *)((int)arg + 10) & 0xf7 | (byte)(((byte)ptVar5->field_0x1e & 1) << 3);
    if (cVar1 == '\0')
    {
      *(undefined *)((int)arg + 0xb) = 1;
      *(undefined *)((int)arg + 0xc) = 1;
    }
    else
    {
      *(undefined *)((int)arg + 0xb) = 0;
      *(undefined *)((int)arg + 0xc) = 0;
    }
    tl_zbTaskPost(zdo_nlme_join_indication, arg);
  }
  return;
}
void tl_zbMacMlmeOrphanIndicationHandler(void *arg)

{
  tl_zb_normal_neighbor_entry_t *ptVar1;
  undefined in_stack_ffffffe4;
  undefined7 in_stack_ffffffe5;
  undefined local_12;
  undefined uStack_11;

  memcpy(&stack0xffffffe4, arg, 8);
  ptVar1 = tl_zbNeighborTableSearchFromExtAddr((u16 *)&local_12, (addrExt_t)CONCAT71(in_stack_ffffffe5, in_stack_ffffffe4),
                                               (u16 *)&stack0xffffffe4);
  if ((ptVar1 == (tl_zb_normal_neighbor_entry_t *)0x0) || ((ptVar1->field_0x1e & 0x70) != 0x10))
  {
    zb_buf_free((zb_buf_t *)arg);
  }
  else
  {
    *(undefined *)((int)arg + 8) = local_12;
    *(undefined *)((int)arg + 9) = uStack_11;
    memcpy(arg, &stack0xffffffe4, 8);
    *(undefined *)((int)arg + 10) = 1;
    tl_zbPrimitivePost('\x02', 'P', arg);
  }
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void tl_zbMcpsRejoinRespCnfHandler(void)

{
  u8 uVar1;
  zb_buf_t *in_r0;
  tl_zb_normal_neighbor_entry_t *ptVar2;
  char in_r1;
  byte bVar3;
  byte bVar4;
  undefined4 in_r2;
  undefined in_stack_ffffffd4;
  undefined7 in_stack_ffffffd5;

  if ((in_r1 == '\0') &&
      (ptVar2 = tl_zbNeighborTableSearchFromShortAddr((u16)in_r2, (addrExt_t)CONCAT71(in_stack_ffffffd5, in_stack_ffffffd4),
                                                      (u16 *)&stack0xffffffd4),
       ptVar2 != (tl_zb_normal_neighbor_entry_t *)0x0))
  {
    tl_zbNwkBeaconPayloadUpdate();
    uVar1 = in_r0->buf[0x28];
    bVar3 = ptVar2->field_0x1e & 0xe;
    bVar4 = bVar3 - 2;
    in_r0->buf[10] = in_r0->buf[10] & 0xfd | (bVar4 + ~bVar4 + (1 < bVar3)) * '\x02';
    in_r0->buf[10] = in_r0->buf[10] & 0xf7 | (byte)(((byte)ptVar2->field_0x1e & 1) << 3);
    in_r0->buf[8] = (u8)in_r2;
    in_r0->buf[9] = (u8)((uint)in_r2 >> 8);
    memcpy(in_r0, &stack0xffffffd4, 8);
    in_r0->buf[0xb] = '\x02';
    in_r0->buf[0xc] = uVar1;
    tl_zbTaskPost(zdo_nlme_join_indication, in_r0);
  }
  else
  {
    zb_buf_free(in_r0);
  }
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
// WARNING: Unknown calling convention -- yet parameter storage is locked
undefined4 tl_zbNlmeRejoinRespTimeoutCb(void)

{
  u16 uVar1;
  undefined *arg;
  void *arg_00;
  char cVar2;
  undefined4 uVar3;

  cVar2 = rejoinRespPollCnt + 1;
  if (rejoinRespPollCnt < 3)
  {
    uVar3 = 0;
    rejoinRespPollCnt = cVar2;
    if (g_zbInfo.macPib.rxOnWhenIdle == '\0')
    {
      if ((g_zbNwkCtx.join.pAssocJoinParent != (tl_zb_addition_neighbor_entry_t *)0x0) &&
          (arg = (undefined *)c1(), arg != (undefined *)0x0))
      {
        arg[10] = 2;
        uVar1 = (g_zbNwkCtx.join.pAssocJoinParent)->shortAddr;
        arg[2] = (char)uVar1;
        arg[3] = (char)(uVar1 >> 8);
        uVar1 = g_zbInfo.macPib.panId;
        *arg = (char)g_zbInfo.macPib.panId;
        arg[1] = (char)(uVar1 >> 8);
        tl_zbPrimitivePost('\x02', ']', arg);
      }
    }
  }
  else
  {
    rejoinRespPollCnt = cVar2;
    arg_00 = (void *)c1();
    uVar3 = 0;
    if (arg_00 != (void *)0x0)
    {
      tl_zbTaskPost(nwk_rejoinReq, arg_00);
      rejoinRespPollCnt = '\0';
      rejoinRespTimeoutEvt = 0;
      uVar3 = 0xfffffffe;
    }
  }
  return uVar3;
}
void tl_zbNwkNlmeDirectJoinRequestHandler(void *arg)

{
  zb_nwk_status_t zVar1;
  int iVar2;
  tl_zb_normal_neighbor_entry_t *ptVar3;
  undefined uVar4;
  nebTbl_t *in_stack_ffffffc0;
  nebTbl_t *in_stack_ffffffc4;
  undefined auStack_1c[10];
  undefined2 local_12;

  memcpy(auStack_1c, arg, 8);
  iVar2 = memcmp(arg, g_zbInfo.macPib.extAddress, 8);
  uVar4 = 0xc1;
  if (iVar2 != 0)
  {
    local_12 = 0;
    zVar1 = tl_zbNwkAddrMapAdd(*(u16 *)((int)arg + 8),
                               (addrExt_t)CONCAT44(in_stack_ffffffc4, in_stack_ffffffc0), (u16 *)arg);
    uVar4 = 199;
    if (zVar1 == NWK_STATUS_SUCCESS)
    {
      ptVar3 = nwk_neTblGetByExtAddr((addrExt_t)CONCAT44(in_stack_ffffffc4, in_stack_ffffffc0));
      uVar4 = 0xc5;
      if (ptVar3 == (tl_zb_normal_neighbor_entry_t *)0x0)
      {
        ptVar3 = tl_zbNeighborTableUpdate((tl_zb_normal_neighbor_entry_t *)&stack0xffffffc0, '\x01');
        if (ptVar3 != (tl_zb_normal_neighbor_entry_t *)0x0)
        {
          *(undefined *)arg = 0;
          *(undefined *)((int)arg + 1) = 0;
          *(undefined *)((int)arg + 2) = 0;
          *(undefined *)((int)arg + 3) = 0;
          *(undefined *)((int)arg + 4) = 0;
          *(undefined *)((int)arg + 5) = 0;
          *(undefined *)((int)arg + 6) = 0;
          *(undefined *)((int)arg + 7) = 0;
          *(undefined *)((int)arg + 8) = 0;
          *(undefined *)((int)arg + 8) = 0;
          memcpy(arg, auStack_1c, 8);
          goto LAB_00019c82;
        }
        uVar4 = 199;
      }
    }
  }
  *(undefined *)arg = 0;
  *(undefined *)((int)arg + 1) = 0;
  *(undefined *)((int)arg + 2) = 0;
  *(undefined *)((int)arg + 3) = 0;
  *(undefined *)((int)arg + 4) = 0;
  *(undefined *)((int)arg + 5) = 0;
  *(undefined *)((int)arg + 6) = 0;
  *(undefined *)((int)arg + 7) = 0;
  *(undefined *)((int)arg + 8) = 0;
  *(undefined *)((int)arg + 8) = uVar4;
LAB_00019c82:
  tl_zbTaskPost(zdo_nlme_direct_join_confirm, arg);
  return;
}
void tl_zbNwkNlmeJoinRequestHandler(void *arg)

{
  char cVar1;
  byte bVar2;
  undefined4 uVar3;
  undefined uVar4;
  undefined uVar5;
  undefined uVar6;
  undefined uVar7;
  undefined uVar8;

  cVar1 = *(char *)((int)arg + 0xc);
  if (cVar1 == '\x01')
  {
    if ((g_zbNwkCtx._47_1_ & 0xf0) != 0)
      goto LAB_00019b28;
    g_zbInfo.nwkNib.parentInfo = g_zbNwkCtx._47_1_ & 0xf0;
    memcpy(g_zbInfo.nwkNib.extPANId, arg, 8);
    g_zbInfo.nwkNib.capabilityInfo = *(capability_info_t *)((int)arg + 0xe);
    bVar2 = (byte)(((uint) * (byte *)((int)arg + 0xe) << 0x1c) >> 0x18);
    g_zbNwkCtx._47_1_ = g_zbNwkCtx._47_1_ & 0xf | 0x50;
    uVar3 = *(undefined4 *)((int)arg + 8);
    uVar7 = (undefined)uVar3;
    uVar4 = (undefined)((uint)uVar3 >> 8);
    uVar5 = (undefined)((uint)uVar3 >> 0x10);
    uVar6 = (undefined)((uint)uVar3 >> 0x18);
    g_zbNwkCtx.scanDuration = *(u8 *)((int)arg + 0xd);
    uVar8 = 3;
  }
  else
  {
    if (cVar1 == '\0')
    {
      nwk_associateJoin();
      return;
    }
    if (cVar1 != '\x02')
    {
      zb_buf_free((zb_buf_t *)arg);
      return;
    }
    if ((g_zbNwkCtx._47_1_ & 0xf0) != 0)
    {
    LAB_00019b28:
      nwk_nlmeJoinCnf();
      return;
    }
    g_zbInfo.nwkNib.parentInfo = g_zbNwkCtx._47_1_ & 0xf0;
    memcpy(g_zbInfo.nwkNib.extPANId, arg, 8);
    g_zbInfo.nwkNib.capabilityInfo = *(capability_info_t *)((int)arg + 0xe);
    bVar2 = (byte)(((uint) * (byte *)((int)arg + 0xe) << 0x1c) >> 0x18);
    g_zbNwkCtx._47_1_ = g_zbNwkCtx._47_1_ & 0xf | 0x40;
    uVar3 = *(undefined4 *)((int)arg + 8);
    uVar7 = (undefined)uVar3;
    uVar4 = (undefined)((uint)uVar3 >> 8);
    uVar5 = (undefined)((uint)uVar3 >> 0x10);
    uVar6 = (undefined)((uint)uVar3 >> 0x18);
    g_zbNwkCtx.scanDuration = *(u8 *)((int)arg + 0xd);
    uVar8 = 1;
  }
  g_zbInfo.macPib.rxOnWhenIdle = bVar2 >> 7;
  g_zbNwkCtx.scanChannels._0_1_ = uVar7;
  g_zbNwkCtx.scanChannels._1_1_ = uVar4;
  g_zbNwkCtx.scanChannels._2_1_ = uVar5;
  g_zbNwkCtx.scanChannels._3_1_ = uVar6;
  *(undefined *)((int)arg + 4) = uVar8;
  *(undefined *)arg = uVar7;
  *(undefined *)((int)arg + 1) = uVar4;
  *(undefined *)((int)arg + 2) = uVar5;
  *(undefined *)((int)arg + 3) = uVar6;
  *(u8 *)((int)arg + 5) = g_zbNwkCtx.scanDuration;
  tl_zbPrimitivePost('\x02', 'U', arg);
  return;
}
// WARNING: Could not reconcile some variable overlaps
// WARNING: Unknown calling convention -- yet parameter storage is locked
uint tl_zbNwkRejoinReqCmdHandler(void)

{
  u8 uVar1;
  byte bVar2;
  zb_buf_t *in_r0;
  int iVar3;
  int in_r1;
  uint uVar4;
  undefined local_6c[8];
  undefined4 local_64;
  undefined4 uStack_60;
  undefined4 uStack_5c;
  undefined4 uStack_58;
  uint uStack_54;
  u8 *puStack_50;
  undefined4 local_4c;
  uint uStack_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  undefined2 local_34;
  undefined local_32;
  undefined4 local_30;
  undefined4 uStack_2c;
  undefined2 local_26;

  if ((int)((uint) * (byte *)(in_r1 + 5) << 0x1b) < 0)
  {
    local_26 = *(undefined2 *)(in_r1 + 2);
    memcpy(&local_30, (void *)(in_r1 + 0x10), 8);
    iVar3 = tl_zbNwkJoinAccept_clone_0();
    if (iVar3 != 0x20)
    {
      if (iVar3 == 0)
      {
        g_sysDiags.joinIndication = g_sysDiags.joinIndication + 1;
      }
      uVar4 = (uint) * (byte *)(in_r1 + 5) << 0x1e;
      in_r0->buf[0x28] = (byte)(uVar4 >> 0x1f);
      local_4c = 0;
      uStack_48 = 0;
      uStack_44 = 0;
      uStack_40 = 0;
      uStack_3c = 0;
      uStack_38 = 0;
      local_34 = 0;
      local_32 = 0;
      local_6c._0_4_ = 0;
      local_64 = 0;
      uStack_60 = 0;
      uStack_5c = 0;
      uStack_58 = 0;
      uStack_54 = 0;
      puStack_50 = (u8 *)0x0;
      local_6c._4_4_ = (uVar4 >> 0x1f) << 9;
      local_6c[5] = (byte)(local_6c._4_4_ >> 8) | 0x10;
      local_6c._4_4_ = CONCAT11(local_6c[5], 9) | 0x800;
      memcpy(&uStack_5c, g_zbInfo.macPib.extAddress, 8);
      local_64 = uStack_2c;
      uStack_60 = local_30;
      local_6c._0_4_ = CONCAT22(g_zbInfo.macPib.shortAddress, *(undefined2 *)(in_r1 + 2));
      local_6c._4_4_ = CONCAT13(g_zbInfo.nwkNib.seqNum, CONCAT12(1, local_6c._4_2_));
      g_zbInfo.nwkNib.seqNum = g_zbInfo.nwkNib.seqNum + '\x01';
      uVar1 = getNwkHdrSize((nwk_hdr_t *)local_6c);
      uStack_54._0_2_ = CONCAT11(uVar1, uStack_54._0_1_);
      uStack_54 = uStack_54 & 0xffff0000 | (uint)(ushort)uStack_54;
      local_4c = CONCAT31(local_4c._1_3_, 7);
      uStack_48._0_3_ = CONCAT12((char)iVar3, local_26);
      uStack_48 = uStack_48 & 0xff000000 | (uint)(uint3)uStack_48;
      uVar4 = tl_zbNwkSendRejoinRespCmd();
      return uVar4;
    }
  }
  bVar2 = zb_buf_free(in_r0);
  return (uint)bVar2;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
uint tl_zbNwkRejoinRespCmdHandler(void)

{
  ushort shortAddr;
  anon_union_4_2_bfd4ae01_for_join in;
  byte bVar1;
  zb_nwk_status_t zVar2;
  zb_nwk_status_t zVar3;
  u16 uVar4;
  zb_buf_t *in_r0;
  tl_zb_normal_neighbor_entry_t *ptVar5;
  int iVar6;
  int in_r1;
  int in_r2;
  uint uVar7;
  nebTbl_t *in_stack_ffffffac;
  nebTbl_t *in_stack_ffffffb0;
  undefined auStack_30[10];
  undefined2 local_26;

  ptVar5 = tl_zbNeighborTableSearchForParent();
  in = g_zbNwkCtx.join;
  if ((g_zbNwkCtx._47_1_ & 0xf0) == 0x40)
  {
    if (((g_zbNwkCtx.join.pAssocJoinParent == (tl_zb_addition_neighbor_entry_t *)0x0) ||
         (rejoinRespTimeoutEvt + ~rejoinRespTimeoutEvt != 0)) ||
        ((g_zbNwkCtx.join.pAssocJoinParent)->shortAddr != *(u16 *)(in_r1 + 2)))
    {
      bVar1 = zb_buf_free(in_r0);
      uVar7 = (uint)bVar1;
    }
    else
    {
      rejoinRespPollCnt = 0;
      ev_timer_taskCancel((ev_timer_event_t **)&rejoinRespTimeoutEvt);
      if ((*(char *)(in_r2 + 6) == '\0') && ((*(ushort *)(in_r2 + 4) & 0xfff8) != 0xfff8))
      {
        memcpy(g_zbInfo.nwkNib.extPANId, in.pAssocJoinParent, 8);
        g_zbInfo.nwkNib.updateId = (in.pAssocJoinParent)->nwkUpdateId;
        g_zbInfo.nwkNib.depth =
            (byte)(((uint)(byte)(in.pAssocJoinParent)->field_0x16 << 0x1c) >> 0x1c) +
            (((byte)(in.pAssocJoinParent)->field_0x16 & 0xf) < (uint)g_zbInfo.nwkNib.maxDepth);
        g_zbInfo.macPib.shortAddress = *(u16 *)(in_r2 + 4);
        g_zbInfo.nwkNib.nwkAddr._0_1_ = (undefined)g_zbInfo.macPib.shortAddress;
        g_zbInfo.nwkNib.nwkAddr._1_1_ = (byte)(g_zbInfo.macPib.shortAddress >> 8);
        memcpy(g_zbInfo.nwkNib.ieeeAddr, g_zbInfo.macPib.extAddress, 8);
        g_zbInfo.macPib.coordShortAddress = *(u16 *)(in_r1 + 2);
        if ((int)((uint) * (byte *)(in_r1 + 5) << 0x1b) < 0)
        {
          memcpy(g_zbInfo.macPib.coordExtAddress, (void *)(in_r1 + 0x10), 8);
        }
        if (ptVar5 != (tl_zb_normal_neighbor_entry_t *)0x0)
        {
          tl_zbExtAddrByIdx(ptVar5->addrmapIdx,
                            (addrExt_t)CONCAT44(in_stack_ffffffb0, in_stack_ffffffac));
          uVar4 = tl_zbshortAddrByIdx(ptVar5->addrmapIdx);
          iVar6 = memcmp(auStack_30, (void *)(in_r1 + 0x10), 8);
          if ((iVar6 != 0) || (*(u16 *)(in_r1 + 2) != uVar4))
          {
            tl_zbNeighborTableDelete(ptVar5);
            g_zbNwkCtx._46_1_ = g_zbNwkCtx._46_1_ | 0x7f;
          }
        }
        local_26 = 0;
        zVar2 = tl_zbNwkAddrMapAdd(g_zbInfo.macPib.shortAddress,
                                   (addrExt_t)CONCAT44(in_stack_ffffffb0, in_stack_ffffffac),
                                   (u16 *)g_zbInfo.macPib.extAddress);
        zVar3 = tl_zbNwkAddrMapAdd(g_zbInfo.macPib.coordShortAddress,
                                   (addrExt_t)CONCAT44(in_stack_ffffffb0, in_stack_ffffffac),
                                   (u16 *)g_zbInfo.macPib.coordExtAddress);
        if (((zVar2 | zVar3) == 0) &&
            (ptVar5 = tl_zbNeighborTableUpdate((tl_zb_normal_neighbor_entry_t *)&stack0xffffffac, '\x01'),
             ptVar5 != (tl_zb_normal_neighbor_entry_t *)0x0))
        {
          uVar7 = nwk_nlmeJoinCnf();
        }
        else
        {
          uVar7 = nwk_nlmeJoinCnf();
        }
      }
      else
      {
        bVar1 = tl_zbTaskPost(nwk_rejoinReq, in_r0);
        uVar7 = (uint)bVar1;
      }
    }
  }
  else
  {
    bVar1 = zb_buf_free(in_r0);
    uVar7 = (uint)bVar1;
    if (ptVar5 != (tl_zb_normal_neighbor_entry_t *)0x0)
    {
      uVar4 = tl_zbshortAddrByIdx(ptVar5->addrmapIdx);
      uVar7 = (uint)uVar4;
      if (uVar7 != *(ushort *)(in_r1 + 2))
      {
        return uVar7;
      }
    }
    if (*(char *)(in_r2 + 6) == '\0')
    {
      shortAddr = *(ushort *)(in_r2 + 4);
      uVar7 = (uint)shortAddr;
      if ((uVar7 & 0xfff8) != 0xfff8)
      {
        g_zbInfo.nwkNib.nwkAddr._0_1_ = (undefined)shortAddr;
        g_zbInfo.nwkNib.nwkAddr._1_1_ = (byte)(uVar7 >> 8);
        g_zbInfo.macPib.shortAddress = shortAddr & 0xff | (ushort)g_zbInfo.nwkNib.nwkAddr._1_1_ << 8;
        local_26 = 0;
        tl_zbNwkAddrMapAdd(shortAddr, (addrExt_t)CONCAT44(in_stack_ffffffb0, in_stack_ffffffac),
                           (u16 *)g_zbInfo.macPib.extAddress);
        zb_info_save((void *)0x0);
        uVar7 = zdo_device_announce_send();
      }
    }
  }
  return uVar7;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void tl_zbNwkSendRejoinReqCmd(void)

{
  zb_buf_t *in_r0;
  undefined *puVar1;
  undefined *in_r2;
  u8 in_r3;

  puVar1 = (undefined *)tl_bufInitalloc(in_r0, '\x02');
  *puVar1 = *in_r2;
  puVar1[1] = in_r2[4];
  (in_r0->hdr).handle = in_r3;
  nwk_tx();
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void tl_zbNwkSendRejoinRespCmd(void)

{
  zb_buf_t *in_r0;
  undefined *puVar1;
  undefined *in_r2;
  u8 in_stack_00000000;

  puVar1 = (undefined *)tl_bufInitalloc(in_r0, '\x04');
  *puVar1 = *in_r2;
  memcpy(puVar1 + 1, in_r2 + 4, 2);
  puVar1[3] = in_r2[6];
  (in_r0->hdr).handle = in_stack_00000000;
  nwk_tx();
  return;
}
