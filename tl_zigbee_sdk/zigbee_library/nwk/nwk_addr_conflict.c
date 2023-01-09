// WARNING: Could not reconcile some variable overlaps
// WARNING: Unknown calling convention -- yet parameter storage is locked
undefined4 nwk_addrConflictCb(void)

{
  ushort uVar1;
  uint uVar2;
  u8 uVar3;
  bool bVar4;
  zb_buf_t *in_r0;
  uint uVar5;
  undefined local_54[4];
  undefined4 uStack_50;
  undefined4 uStack_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  uint uStack_3c;
  u8 *puStack_38;
  undefined local_34[8];
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  undefined2 local_1c;
  undefined local_1a;

  if (conflictInfo != (ushort *)0x0)
  {
    uVar1 = *conflictInfo;
    zb_buf_clear(in_r0);
    local_54 = (undefined[4])0x0;
    uStack_50 = 0;
    uStack_4c = 0;
    uStack_48 = 0;
    uStack_44 = 0;
    uStack_40 = 0;
    uStack_3c = 0;
    puStack_38 = (u8 *)0x0;
    local_34._0_4_ = 0;
    local_34._4_4_ = 0;
    uStack_2c = 0;
    uStack_28 = 0;
    uStack_24 = 0;
    uStack_20 = 0;
    local_1c = 0;
    local_1a = 0;
    uVar5 = 0;
    if (((int)((uint)ss_ib._62_1_ << 0x1c) < 0) && ((ss_ib._62_1_ & 7) != 0))
    {
      bVar4 = ss_keyPreconfigured();
      uVar5 = (uint)(bVar4 != false);
    }
    uVar2 = (ushort)((ushort)uStack_50 & 0xff00 | (ushort)uStack_50 & 0xc0 | 1 | 0x1008) &
            0xfffff7ff;
    uStack_50._1_1_ = (byte)(uVar2 >> 8);
    uStack_50._0_2_ =
        (nwkFrameCtrl_t)CONCAT11(uStack_50._1_1_ & 0xfd | (byte)(uVar5 << 1), (char)uVar2);
    uStack_50 = uStack_50 & 0xffff0000 | (uint)(ushort)uStack_50._0_2_;
    memcpy(&uStack_44, g_zbInfo.macPib.extAddress, 8);
    local_54 = (undefined[4])CONCAT22(g_zbInfo.macPib.shortAddress, 0xfffc);
    uStack_50 = CONCAT13(g_zbInfo.nwkNib.seqNum,
                         CONCAT12(g_zbInfo.nwkNib.maxDepth << 1, uStack_50._0_2_));
    g_zbInfo.nwkNib.seqNum = g_zbInfo.nwkNib.seqNum + '\x01';
    uVar3 = getNwkHdrSize((nwk_hdr_t *)local_54);
    uStack_3c._0_2_ = CONCAT11(uVar3, uStack_3c._0_1_);
    uStack_3c = uStack_3c & 0xffff0000 | (uint)(ushort)uStack_3c;
    local_34._0_4_ = CONCAT31(local_34._1_3_, 3);
    local_34._4_4_ = local_34._4_4_ & 0xff000000 | (uint)uVar1 | 0xd0000;
    tl_zbNwkSendNwkStatusCmd(conflictInfo, (nwk_hdr_t *)local_54, (nwkCmd_t *)local_34, 0xc9);
  }
  conflictInfo = (ushort *)0x0;
  addrConflictHandleTimer = 0;
  return 0xfffffffe;
}
bool tl_zbNwkAddrConflictDetect(void *arg, u16 nwkAddr, addrExt_t ieeeAddr)

{
  tl_zb_normal_neighbor_entry_t *ptVar1;
  int iVar2;
  uint uVar3;
  void *in_r2;
  undefined in_stack_ffffffd4;
  undefined7 in_stack_ffffffd5;

  uVar3 = (uint)nwkAddr;
  if ((~uVar3 + uVar3 != 0) && (g_zbInfo.nwkNib.nwkAddr == uVar3))
  {
    return false;
  }
  if ((g_zbInfo.nwkNib.nwkAddr != uVar3) ||
      (iVar2 = memcmp(in_r2, g_zbInfo.macPib.extAddress, 8), iVar2 == 0))
  {
    ptVar1 = tl_zbNeighborTableSearchFromShortAddr(nwkAddr, (addrExt_t)CONCAT71(in_stack_ffffffd5, in_stack_ffffffd4),
                                                   (u16 *)&stack0xffffffd4);
    if (ptVar1 == (tl_zb_normal_neighbor_entry_t *)0x0)
    {
      return false;
    }
    iVar2 = memcmp(in_r2, &stack0xffffffd4, 8);
    if (iVar2 == 0)
    {
      return false;
    }
    iVar2 = memcmp(&stack0xffffffd4, &g_zero_addr, 8);
    if ((iVar2 == 0) || (~uVar3 + uVar3 != 0))
    {
      return false;
    }
  }
  tl_zbNwkAddrConflictHandle();
  g_sysDiags.nwkAddrConflict = g_sysDiags.nwkAddrConflict + '\x01';
  return true;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void tl_zbNwkAddrConflictHandle(void)

{
  u16 shortAddr;
  undefined2 *in_r0;
  u32 uVar1;
  int iVar2;
  undefined2 in_r1;
  int in_r2;
  undefined4 unaff_r8;
  undefined in_stack_ffffffe4;
  undefined in_stack_ffffffe5;

  if (addrConflictHandleTimer != (ev_timer_event_t *)0x0)
  {
    ev_timer_taskCancel(&addrConflictHandleTimer);
  }
  if (conflictInfo != (zb_buf_t *)0x0)
  {
    zb_buf_free(conflictInfo);
  }
  conflictInfo = (zb_buf_t *)in_r0;
  *in_r0 = in_r1;
  uVar1 = drv_u32Rand();
  addrConflictHandleTimer = ev_timer_taskPost(nwk_addrConflictCb, in_r0, (uVar1 & 0x3f) + 1);
  if (in_r2 == 0)
  {
    shortAddr = tl_zbNwkStochasticAddrCal();
    g_zbInfo.macPib.shortAddress._0_1_ = (undefined)shortAddr;
    g_zbInfo.macPib.shortAddress._1_1_ = (undefined)((uint)shortAddr >> 8);
    g_zbInfo.nwkNib.nwkAddr._0_1_ = (undefined)g_zbInfo.macPib.shortAddress;
    g_zbInfo.nwkNib.nwkAddr._1_1_ = g_zbInfo.macPib.shortAddress._1_1_;
    tl_zbNwkAddrMapAdd(shortAddr,
                       (addrExt_t)
                           CONCAT44(unaff_r8, (uint)CONCAT11(in_stack_ffffffe5, in_stack_ffffffe4)),
                       (u16 *)g_zbInfo.macPib.extAddress);
    zb_info_save((void *)0x0);
    zdo_device_announce_send();
  }
  else if (((*(byte *)(in_r2 + 0x1e) & 0x7f) == 0x14) && (iVar2 = c1(), iVar2 != 0))
  {
    tl_zbNwkNeighborAddrConflictHandle();
  }
  return;
}
// WARNING: Could not reconcile some variable overlaps
void tl_zbNwkAddrConflictStatusSend(u16 dstAddr, u16 statusAddr, u8 forceSeqNum)

{
  uint uVar1;
  u8 uVar2;
  bool bVar3;
  void *arg;
  uint uVar4;
  undefined local_58[4];
  undefined4 uStack_54;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;
  uint uStack_40;
  u8 *puStack_3c;
  undefined local_38[8];
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  undefined2 local_20;
  undefined local_1e;

  arg = (void *)c1();
  if (arg != (void *)0x0)
  {
    local_58 = (undefined[4])0x0;
    uStack_54 = 0;
    uStack_50 = 0;
    uStack_4c = 0;
    uStack_48 = 0;
    uStack_44 = 0;
    uStack_40 = 0;
    puStack_3c = (u8 *)0x0;
    local_38._0_4_ = 0;
    local_38._4_4_ = 0;
    uStack_30 = 0;
    uStack_2c = 0;
    uStack_28 = 0;
    uStack_24 = 0;
    local_20 = 0;
    local_1e = 0;
    uVar4 = 0;
    if (((int)((uint)ss_ib._62_1_ << 0x1c) < 0) && ((ss_ib._62_1_ & 7) != 0))
    {
      bVar3 = ss_keyPreconfigured();
      uVar4 = (uint)(bVar3 != false);
    }
    uVar1 = (ushort)((ushort)uStack_54 & 0xff00 | (ushort)uStack_54 & 0xc0 | 1 | 0x1008) &
            0xfffff7ff;
    uStack_54._1_1_ = (byte)(uVar1 >> 8);
    uStack_54._0_2_ =
        (nwkFrameCtrl_t)CONCAT11(uStack_54._1_1_ & 0xfd | (byte)(uVar4 << 1), (char)uVar1);
    uStack_54 = uStack_54 & 0xffff0000 | (uint)(ushort)uStack_54._0_2_;
    memcpy(&uStack_48, g_zbInfo.macPib.extAddress, 8);
    local_58 = (undefined[4])CONCAT22(g_zbInfo.macPib.shortAddress, dstAddr);
    uVar2 = '\0';
    if (forceSeqNum == '\0')
    {
      uVar2 = g_zbInfo.nwkNib.seqNum;
      g_zbInfo.nwkNib.seqNum = g_zbInfo.nwkNib.seqNum + '\x01';
    }
    uStack_54 = CONCAT13(uVar2, CONCAT12(g_zbInfo.nwkNib.maxDepth << 1, uStack_54._0_2_));
    uVar2 = getNwkHdrSize((nwk_hdr_t *)local_58);
    uStack_40._0_2_ = CONCAT11(uVar2, uStack_40._0_1_);
    uStack_40 = uStack_40 & 0xffff0000 | (uint)(ushort)uStack_40;
    local_38._0_4_ = CONCAT31(local_38._1_3_, 3);
    local_38._4_4_ = local_38._4_4_ & 0xff000000 | (uint)statusAddr | 0xd0000;
    tl_zbNwkSendNwkStatusCmd(arg, (nwk_hdr_t *)local_58, (nwkCmd_t *)local_38, 0xc9);
  }
  return;
}
// WARNING: Could not reconcile some variable overlaps
// WARNING: Unknown calling convention -- yet parameter storage is locked
void tl_zbNwkNeighborAddrConflictHandle(void)

{
  byte bVar1;
  ushort uVar2;
  u8 uVar3;
  bool bVar4;
  u16 uVar5;
  u16 uVar6;
  int in_r0;
  int iVar7;
  int in_r1;
  int iVar8;
  undefined4 in_stack_ffffff90;
  undefined uVar9;
  undefined4 in_stack_ffffff94;
  undefined local_68[4];
  undefined4 uStack_64;
  undefined4 local_60;
  undefined4 uStack_5c;
  undefined4 uStack_58;
  undefined4 uStack_54;
  uint uStack_50;
  u8 *puStack_4c;
  undefined4 local_48;
  uint uStack_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined2 local_30;
  undefined local_2e;
  undefined4 local_2c;
  undefined4 uStack_28;

  uVar5 = tl_zbNwkStochasticAddrCal();
  uVar6 = tl_zbshortAddrByIdx(*(u16 *)(in_r1 + 0x16));
  tl_zbExtAddrByIdx(*(u16 *)(in_r1 + 0x16), (addrExt_t)CONCAT44(in_stack_ffffff94, in_stack_ffffff90));
  local_68 = (undefined[4])0x0;
  uStack_64 = 0;
  local_60 = 0;
  uStack_5c = 0;
  uStack_58 = 0;
  uStack_54 = 0;
  uStack_50 = 0;
  puStack_4c = (u8 *)0x0;
  local_48 = 0;
  uStack_44 = 0;
  uStack_40 = 0;
  uStack_3c = 0;
  uStack_38 = 0;
  uStack_34 = 0;
  local_30 = 0;
  local_2e = 0;
  if ((int)((uint)ss_ib._62_1_ << 0x1c) < 0)
  {
    if ((ss_ib._62_1_ & 7) == 0)
    {
      iVar8 = 0;
      uVar9 = 0;
    }
    else
    {
      bVar4 = ss_keyPreconfigured();
      if (bVar4 == false)
      {
        iVar8 = 0;
        uVar9 = 0;
      }
      else
      {
        iVar8 = 1;
        uVar9 = 1;
      }
    }
  }
  else
  {
    iVar8 = 0;
    uVar9 = 0;
  }
  uStack_64 = uStack_64 & 0xffff0000 |
              (uint)(ushort)((ushort)uStack_64 & 0xff00 | (ushort)uStack_64 & 0xc0 | 1 | 8) | 0x1000;
  iVar7 = memcmp(&local_2c, &g_zero_addr, 8);
  bVar1 = ('\x01' - (iVar7 == 0)) * '\b';
  uStack_64._0_2_ =
      (nwkFrameCtrl_t)
          CONCAT11(uStack_64._1_1_ & 0xf5 | bVar1 | (byte)(iVar8 << 1), (undefined)uStack_64);
  uStack_64 = uStack_64 & 0xffff0000 | (uint)(ushort)uStack_64._0_2_;
  if ((bVar1 & 8) != 0)
  {
    local_60 = uStack_28;
    uStack_5c = local_2c;
  }
  memcpy(&uStack_58, g_zbInfo.macPib.extAddress, 8);
  local_68 = (undefined[4])CONCAT22(g_zbInfo.macPib.shortAddress, uVar6);
  uStack_64 = CONCAT13(g_zbInfo.nwkNib.seqNum,
                       CONCAT12(g_zbInfo.nwkNib.maxDepth << 1, uStack_64._0_2_));
  g_zbInfo.nwkNib.seqNum = g_zbInfo.nwkNib.seqNum + '\x01';
  uVar3 = getNwkHdrSize((nwk_hdr_t *)local_68);
  uStack_50._0_2_ = CONCAT11(uVar3, uStack_50._0_1_);
  uStack_50 = uStack_50 & 0xffff0000 | (uint)(ushort)uStack_50;
  local_48 = CONCAT31(local_48._1_3_, 7);
  uStack_44 = uStack_44 & 0xff000000 | (uint)uVar5;
  *(undefined *)(in_r0 + 0x28) = uVar9;
  tl_zbNwkSendRejoinRespCmd();
  uVar2 = *(ushort *)(in_r1 + 0x16);
  *(char *)&g_nwkAddrMap.addrMap[uVar2].shortAddr = (char)uVar5;
  *(char *)((int)&g_nwkAddrMap.addrMap[uVar2].shortAddr + 1) = (char)((uint)uVar5 >> 8);
  return;
}
void tl_zbNwkStatusAddrConflictInd(void *arg)

{
  u16 uVar1;
  tl_zb_normal_neighbor_entry_t *ptVar2;
  undefined in_stack_ffffffe8;
  undefined7 in_stack_ffffffe9;

  if ((conflictInfo != (zb_buf_t *)0x0) && (addrConflictHandleTimer != 0))
  {
    // WARNING: Load size is inaccurate
    uVar1 = *arg;
    if (*(u16 *)conflictInfo->buf != uVar1)
      goto LAB_00015af0;
    ev_timer_taskCancel((ev_timer_event_t **)&addrConflictHandleTimer);
    zb_buf_free(conflictInfo);
    conflictInfo = (zb_buf_t *)0x0;
  }
  // WARNING: Load size is inaccurate
  uVar1 = *arg;
LAB_00015af0:
  if ((g_zbInfo.macPib.shortAddress == uVar1) && (uVar1 != 0))
  {
    zb_buf_free((zb_buf_t *)arg);
    uVar1 = tl_zbNwkStochasticAddrCal();
    g_zbInfo.nwkNib.nwkAddr._0_1_ = (undefined)uVar1;
    g_zbInfo.nwkNib.nwkAddr._1_1_ = (byte)((uint)uVar1 >> 8);
    g_zbInfo.macPib.shortAddress = uVar1 & 0xff | (ushort)g_zbInfo.nwkNib.nwkAddr._1_1_ << 8;
    tl_zbNwkAddrMapAdd(uVar1, (addrExt_t)CONCAT71(in_stack_ffffffe9, in_stack_ffffffe8),
                       (u16 *)g_zbInfo.macPib.extAddress);
    zb_info_save((void *)0x0);
    zdo_device_announce_send();
  }
  else
  {
    nwkRoutingTabEntryDstDel();
    nwkRouteRecTabEntryDstDel();
    // WARNING: Load size is inaccurate
    ptVar2 = tl_zbNeighborTableSearchFromShortAddr(*arg, (addrExt_t)CONCAT71(in_stack_ffffffe9, in_stack_ffffffe8),
                                                   (u16 *)&stack0xffffffe8);
    if ((ptVar2 == (tl_zb_normal_neighbor_entry_t *)0x0) || ((ptVar2->field_0x1e & 0x7e) != 0x14))
    {
      zb_buf_free((zb_buf_t *)arg);
    }
    else
    {
      tl_zbNwkNeighborAddrConflictHandle();
    }
  }
  return;
}
