// WARNING: Unknown calling convention -- yet parameter storage is locked
uint nwkReportCmdHandler(void)

{
  byte *pbVar1;
  byte bVar2;
  zb_buf_t *in_r0;
  u32 uVar3;
  int in_r1;
  uint uVar4;
  uint uVar5;

  if (((int)((uint)g_zbNwkCtx._45_1_ << 0x19) < 0) || ((*(byte *)(in_r1 + 0x10) & 0xe0) != 0))
  {
    bVar2 = zb_buf_free(in_r0);
    uVar4 = (uint)bVar2;
  }
  else
  {
    g_zbNwkCtx._45_1_ = g_zbNwkCtx._45_1_ | 0x40;
  LAB_0001b8ee:
    do
    {
      while (true)
      {
        uVar3 = drv_u32Rand();
        uVar4 = uVar3 & 0xffff;
        if ((g_zbNwkCtx._46_1_ & 0xf) == 0)
          break;
        if (g_zbNwkCtx.known_panids[0] != uVar4)
        {
          uVar5 = 0;
          do
          {
            uVar5 = uVar5 + 1 & 0xff;
            if ((g_zbNwkCtx._46_1_ & 0xf) <= uVar5)
              goto LAB_0001b932;
          } while (g_zbNwkCtx.known_panids[uVar5] != uVar4);
        }
      }
    LAB_0001b932:
      if ((*(byte *)(in_r1 + 0x10) & 0x1f) != 0)
      {
        pbVar1 = *(byte **)(in_r1 + 0xc);
        if (uVar4 != (uint)pbVar1[1] * 0x100 + (uint)*pbVar1)
        {
          uVar5 = 0;
          do
          {
            uVar5 = uVar5 + 1 & 0xff;
            if ((*(byte *)(in_r1 + 0x10) & 0x1f) <= uVar5)
              goto LAB_0001b980;
          } while (uVar4 != (uint)pbVar1[uVar5 * 2] + (uint)pbVar1[uVar5 * 2 + 1] * 0x100);
        }
        goto LAB_0001b8ee;
      }
    LAB_0001b980:
    } while (uVar4 == 0);
    g_zbInfo.nwkNib.updateId = g_zbInfo.nwkNib.updateId + '\x01';
    uVar4 = tl_zbNwkUpdateForPanidConflict();
  }
  return uVar4;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void nwkReportCmdSend(void)

{
  zb_buf_t *in_r0;
  undefined *puVar1;
  undefined *in_r2;
  u8 in_r3;

  puVar1 = (undefined *)
      tl_bufInitalloc(in_r0, (u8)((((uint)(byte)in_r2[0x10] << 0x1b) >> 2) + 0xa000000 >> 0x18));
  *puVar1 = *in_r2;
  puVar1[1] = in_r2[0x10];
  memcpy(puVar1 + 2, in_r2 + 4, 8);
  memcpy(puVar1 + 10, *(void **)(in_r2 + 0xc), ((uint)(byte)in_r2[0x10] << 0x1b) >> 0x1a);
  (in_r0->hdr).handle = in_r3;
  nwk_fwdPacket();
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void nwkUpdateCmdHandler(void)

{
  u16 uVar1;
  zb_buf_t *in_r0;
  int iVar2;
  int in_r1;
  int in_r2;

  if ((((-1 < (int)((uint)g_zbNwkCtx._46_1_ << 0x1a)) && ((*(byte *)(in_r2 + 0xe) & 0xe0) == 0)) &&
       (iVar2 = memcmp((void *)(in_r2 + 4), g_zbInfo.nwkNib.extPANId, 8), iVar2 == 0)) &&
      (((uVar1 = zdo_af_get_accept_nwk_update_pan_id(), uVar1 == 0 ||
                                                            (uVar1 = zdo_af_get_accept_nwk_update_pan_id(), uVar1 == 0xffff)) ||
        (uVar1 = zdo_af_get_accept_nwk_update_pan_id(), uVar1 == *(u16 *)(in_r2 + 0xc)))))
  {
    g_zbNwkCtx._46_1_ = g_zbNwkCtx._46_1_ | 0x20;
    g_zbNwkCtx._45_1_ = g_zbNwkCtx._45_1_ | 0x40;
    g_zbNwkCtx.new_panid._0_1_ = (undefined) * (undefined2 *)(in_r2 + 0xc);
    g_zbNwkCtx.new_panid._1_1_ = (undefined)((ushort) * (undefined2 *)(in_r2 + 0xc) >> 8);
    tl_zbNwkPanidConflictSetPanidStart();
    if (*(u16 *)(in_r1 + 2) == g_zbInfo.nwkNib.managerAddr)
    {
      g_zbInfo.nwkNib.updateId = *(u8 *)(in_r2 + 0xf);
    }
  }
  zb_buf_free(in_r0);
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void nwkUpdateCmdSend(void)

{
  zb_buf_t *in_r0;
  undefined *puVar1;
  undefined *in_r2;
  u8 in_r3;

  puVar1 = (undefined *)tl_bufInitalloc(in_r0, '\r');
  *puVar1 = *in_r2;
  puVar1[1] = in_r2[0xe];
  memcpy(puVar1 + 2, in_r2 + 4, 8);
  puVar1[10] = in_r2[0xf];
  memcpy(puVar1 + 0xb, in_r2 + 0xc, 2);
  (in_r0->hdr).handle = in_r3;
  nwk_fwdPacket();
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void nwk_panIdConflictCnfHandler(void)

{
  void *in_r0;

  g_zbInfo.nwkNib.panId = g_zbInfo.macPib.panId;
  tl_zbNwkBeaconPayloadUpdate();
  g_zbNwkCtx._47_1_ = g_zbNwkCtx._47_1_ & 0xf;
  g_zbNwkCtx._45_1_ = g_zbNwkCtx._45_1_ & 0xbf;
  g_zbNwkCtx._46_1_ = g_zbNwkCtx._46_1_ & 0xd0;
  memset(g_zbNwkCtx.known_panids, 0, 0x10);
  tl_zbNwkNlmeNwkStatusInd(in_r0, g_zbInfo.nwkNib.managerAddr, 0xf);
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void tl_zbNwkNetworkUpdateCmdHandler(void)

{
  zb_buf_t *in_r0;
  int iVar1;
  ushort *in_r1;

  if (((*in_r1 & 0xfff8) == 0xfff8) && (*(char *)(in_r1 + 3) != '\0'))
  {
    nwkBrcTransJitterSet();
    iVar1 = nwkBrcTimerStart();
    if (iVar1 != 0)
    {
      iVar1 = nwkBrcTransEntryFind();
      if (iVar1 != 0)
      {
        nwkBrcTransTabEntryClear();
      }
      zb_buf_free(in_r0);
      return;
    }
  }
  nwkUpdateCmdHandler();
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
undefined4 tl_zbNwkPanidConflictDetect(void)

{
  u16 in_r0;
  int iVar1;
  void *in_r1;
  undefined4 uVar2;

  uVar2 = 0;
  if ((g_zbInfo.nwkNib.panId == in_r0) &&
      ((iVar1 = memcmp(in_r1, &g_zero_addr, 8), iVar1 == 0 ||
                                                    (iVar1 = memcmp(in_r1, g_zbInfo.nwkNib.extPANId, 8), iVar1 != 0))))
  {
    g_sysDiags.panIdConflictCheck = g_sysDiags.panIdConflictCheck + 1;
    if (g_panIdConflictDected._0_4_ == (ev_timer_event_t *)0x0)
    {
      memcpy(g_panIdConflictDected + 4, in_r1, 8);
      g_panIdConflictDected[12] = 2;
      g_panIdConflictDected._0_4_ =
          ev_timer_taskPost(tl_zbNwkPanidConflictDoubleCheck, (void *)0x0, 0x14);
      uVar2 = 0;
    }
    else
    {
      iVar1 = memcmp(in_r1, g_panIdConflictDected + 4, 8);
      uVar2 = 0;
      if (iVar1 == 0)
      {
        ev_timer_taskCancel((ev_timer_event_t **)g_panIdConflictDected);
        uVar2 = 1;
      }
    }
  }
  return uVar2;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
undefined4 tl_zbNwkPanidConflictDoubleCheck(void)

{
  undefined4 uVar1;
  int iVar2;

  tl_zbMacMlmeBeaconRequestCmdSend();
  iVar2 = (g_panIdConflictDected[12] - 1) * 0x1000000;
  g_panIdConflictDected[12] = (char)((uint)iVar2 >> 0x18);
  if (iVar2 < 1)
  {
    g_panIdConflictDected._0_4_ = 0;
    uVar1 = 0xfffffffe;
  }
  else
  {
    uVar1 = 2000;
  }
  return uVar1;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void tl_zbNwkPanidConflictProcess(void)

{
  u32 uVar1;
  uint uVar2;
  uint uVar3;

  if (g_zbInfo.nwkNib.managerAddr == g_zbInfo.nwkNib.nwkAddr)
  {
    do
    {
      while (true)
      {
        uVar1 = drv_u32Rand();
        uVar2 = uVar1 & 0xffff;
        if ((g_zbNwkCtx._46_1_ & 0xf) == 0)
          break;
        if (g_zbNwkCtx.known_panids[0] != uVar2)
        {
          uVar3 = 0;
          do
          {
            uVar3 = uVar3 + 1 & 0xff;
            if ((g_zbNwkCtx._46_1_ & 0xf) <= uVar3)
              goto LAB_0001b89e;
          } while (g_zbNwkCtx.known_panids[uVar3] != uVar2);
        }
      }
    LAB_0001b89e:
    } while (uVar2 == 0);
    g_zbInfo.nwkNib.updateId = g_zbInfo.nwkNib.updateId + '\x01';
    tl_zbNwkUpdateForPanidConflict();
  }
  else
  {
    tl_zbNwkReportForPanidConflict();
  }
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
undefined4 tl_zbNwkPanidConflictSetPanidCb(void)

{
  u16 uVar1;
  device_type_t dVar2;
  void *arg;
  char cVar3;

  arg = (void *)c1();
  uVar1 = g_zbNwkCtx.new_panid;
  if (arg != (void *)0x0)
  {
    *(char *)((int)arg + 4) = (char)g_zbNwkCtx.new_panid;
    cVar3 = (uVar1 >> 7 & 1) != 0;
    *(char *)((int)arg + 5) = (char)(uVar1 >> 8);
    *(u8 *)((int)arg + 6) = g_zbMacCtx.curChannel;
    *(undefined *)((int)arg + 8) = 0xf;
    dVar2 = af_nodeDevTypeGet();
    *(device_type_t *)((int)arg + 10) = ~dVar2 + dVar2 + cVar3;
    *(undefined *)((int)arg + 9) = 0xf;
    *(undefined *)((int)arg + 0xb) = 0;
    *(undefined *)((int)arg + 0x17) = 0;
    g_zbNwkCtx._47_1_ = g_zbNwkCtx._47_1_ & 0xf | 0x60;
    tl_zbPrimitivePost('\x02', 'Z', arg);
    g_sysDiags.panIdModified = g_sysDiags.panIdModified + '\x01';
  }
  panidConflictTimerEvt = 0;
  return 0xfffffffe;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void tl_zbNwkPanidConflictSetPanidStart(void)

{
  if (panidConflictTimerEvt == (ev_timer_event_t *)0x0)
  {
    panidConflictTimerEvt =
        ev_timer_taskPost(tl_zbNwkPanidConflictSetPanidCb, (void *)0x0,
                          g_zbInfo.nwkNib.nwkBroadcastDeliveryTime);
  }
  return;
}
// WARNING: Could not reconcile some variable overlaps
// WARNING: Unknown calling convention -- yet parameter storage is locked
void tl_zbNwkReportForPanidConflict(void)

{
  u8 uVar1;
  bool bVar2;
  uint uVar3;
  byte bVar4;
  u8 uVar5;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;
  uint uStack_40;
  u8 *puStack_3c;
  undefined4 local_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  uint uStack_28;
  undefined4 uStack_24;
  undefined2 local_20;
  undefined local_1e;

  bVar4 = 0;
  uVar1 = '\0';
  uVar5 = '\0';
  uStack_50 = 0;
  uStack_4c = 0;
  uStack_48 = 0;
  uStack_44 = 0;
  uStack_40 = 0;
  puStack_3c = (u8 *)0x0;
  local_38 = 0;
  uStack_34 = 0;
  uStack_30 = 0;
  uStack_2c = 0;
  uStack_28 = 0;
  uStack_24 = 0;
  local_20 = 0;
  local_1e = 0;
  uVar3 = 0;
  if (((int)((uint)ss_ib._62_1_ << 0x1c) < 0) && ((ss_ib._62_1_ & 7) != 0))
  {
    bVar2 = ss_keyPreconfigured();
    uVar3 = (uint)(bVar2 != false);
  }
  tl_zbExtAddrByShortAddr(g_zbInfo.nwkNib.managerAddr,
                          (addrExt_t)(CONCAT17(uVar5, CONCAT16(uVar1, CONCAT15(bVar4 & 0xf5 | 0x10 | (byte)(uVar3 << 1),
                                                                               CONCAT14(9, CONCAT22(g_zbInfo.nwkNib.nwkAddr,
                                                                                                    g_zbInfo.nwkNib.managerAddr))))) |
                                      0x4000000000),
                          (u16 *)&uStack_50);
  memcpy(&uStack_48, g_zbInfo.macPib.extAddress, 8);
  g_zbInfo.nwkNib.seqNum = g_zbInfo.nwkNib.seqNum + '\x01';
  uVar1 = getNwkHdrSize((nwk_hdr_t *)&stack0xffffffa8);
  uStack_40._0_2_ = CONCAT11(uVar1, uStack_40._0_1_);
  uStack_40 = uStack_40 & 0xffff0000 | (uint)(ushort)uStack_40;
  local_38 = CONCAT31(local_38._1_3_, 9);
  uStack_28 = uStack_28 & 0xffffff00 | g_zbNwkCtx._46_1_ & 0xf;
  memcpy(&uStack_34, g_zbInfo.nwkNib.extPANId, 8);
  uStack_2c = 0x847e47;
  nwkReportCmdSend();
  return;
}
// WARNING: Could not reconcile some variable overlaps
// WARNING: Unknown calling convention -- yet parameter storage is locked
uint tl_zbNwkUpdateForPanidConflict(void)

{
  uint uVar1;
  u8 uVar2;
  byte bVar3;
  bool bVar4;
  zb_buf_t *in_r0;
  uint uVar5;
  int iVar6;
  uint in_r1;
  undefined local_58[4];
  undefined4 uStack_54;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;
  uint uStack_40;
  u8 *puStack_3c;
  undefined4 local_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  undefined2 local_20;
  undefined local_1e;

  g_zbNwkCtx.new_panid._0_1_ = (undefined)in_r1;
  g_zbNwkCtx.new_panid._1_1_ = (undefined)(in_r1 >> 8);
  local_58 = (undefined[4])0x0;
  uStack_54 = 0;
  uStack_50 = 0;
  uStack_4c = 0;
  uStack_48 = 0;
  uStack_44 = 0;
  uStack_40 = 0;
  puStack_3c = (u8 *)0x0;
  local_38 = 0;
  uStack_34 = 0;
  uStack_30 = 0;
  uStack_2c = 0;
  uStack_28 = 0;
  uStack_24 = 0;
  local_20 = 0;
  local_1e = 0;
  uVar5 = 0;
  if (((int)((uint)ss_ib._62_1_ << 0x1c) < 0) && ((ss_ib._62_1_ & 7) != 0))
  {
    bVar4 = ss_keyPreconfigured();
    uVar5 = (uint)bVar4;
  }
  uVar1 = ((ushort)uStack_54 & 0xff00 | 0x1049) & 0xfffff7ff;
  uStack_54._1_1_ = (byte)(uVar1 >> 8);
  uStack_54._0_2_ =
      (nwkFrameCtrl_t)CONCAT11(uStack_54._1_1_ & 0xfd | (byte)(uVar5 << 1), (char)uVar1);
  uStack_54 = uStack_54 & 0xffff0000 | (uint)(ushort)uStack_54._0_2_;
  memcpy(&uStack_48, g_zbInfo.macPib.extAddress, 8);
  local_58 = (undefined[4])CONCAT22(g_zbInfo.nwkNib.nwkAddr, 0xfffe);
  uStack_54 = CONCAT13(g_zbInfo.nwkNib.seqNum,
                       CONCAT12(g_zbInfo.nwkNib.maxDepth << 1, uStack_54._0_2_));
  g_zbInfo.nwkNib.seqNum = g_zbInfo.nwkNib.seqNum + '\x01';
  uVar2 = getNwkHdrSize((nwk_hdr_t *)local_58);
  uStack_40._0_2_ = CONCAT11(uVar2, uStack_40._0_1_);
  uStack_40 = uStack_40 & 0xffff0000 | (uint)(ushort)uStack_40;
  local_38 = CONCAT31(local_38._1_3_, 10);
  uStack_2c._0_3_ = CONCAT12(1, (short)uStack_2c);
  uStack_2c = uStack_2c & 0xff000000 | (uint)(uint3)uStack_2c;
  memcpy(&uStack_34, g_zbInfo.nwkNib.extPANId, 8);
  uStack_2c._2_2_ =
      (ushort)(uStack_2c >> 0x10) & 0xff |
      (ushort)(((uint)g_zbInfo.nwkNib.updateId << 0x18) >> 0x10);
  uStack_2c = in_r1 & 0xffff | (uint)uStack_2c._2_2_ << 0x10;
  if (((zdoAppIndCbLst == 0) || (*(int *)(zdoAppIndCbLst + 0x14) == 0)) ||
      (iVar6 = tl_zbNwkPanidConflictDetect(), iVar6 == 1))
  {
    uVar5 = nwkUpdateCmdSend();
  }
  else
  {
    bVar3 = zb_buf_free(in_r0);
    uVar5 = (uint)bVar3;
  }
  return uVar5;
}
