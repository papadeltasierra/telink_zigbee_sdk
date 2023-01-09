// WARNING: Unknown calling convention -- yet parameter storage is locked
buf_sts_t nwkEndDevTimeoutInfoNVStore(void)

{
  nv_sts_t nVar1;
  buf_sts_t bVar2;
  int *in_r0;
  int iVar3;
  int iVar4;
  int local_34;
  undefined auStack_30[8];
  ushort local_28;
  u8 uStack_26;

  local_28 = 0;
  uStack_26 = '\0';
  nVar1 = nv_flashReadNew('\0', '\x01', 0xff, 0xc, (u8 *)&local_28);
  if (nVar1 == NV_SUCC)
  {
    iVar4 = 0;
    do
    {
      nVar1 = nv_flashReadByIndex('\x01', '\v', uStack_26, (u16)iVar4, 0xc, (u8 *)&local_34);
      if ((nVar1 == NV_SUCC) && (iVar3 = memcmp(in_r0 + 1, auStack_30, 8), iVar3 == 0))
      {
        if (*in_r0 == local_34)
          goto LAB_000182c6;
        nv_itemDeleteByIndex('\x01', '\v', uStack_26, (u16)iVar4);
      }
      iVar4 = iVar4 + 1;
    } while (iVar4 <= (int)(uint)local_28);
  }
  nv_flashWriteNew('\0', 1, '\v', 0xc, (u8 *)in_r0);
LAB_000182c6:
  bVar2 = ev_buf_free((u8 *)in_r0);
  return bVar2;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void nwkEndDevTimeoutInfoStore(void)

{
  undefined4 uVar1;
  int in_r0;
  u8 *arg;
  undefined4 unaff_r4;
  undefined4 in_lr;

  arg = ev_buf_allocate(0xc);
  if (arg != (u8 *)0x0)
  {
    tl_zbExtAddrByIdx(*(u16 *)(in_r0 + 0x16), (addrExt_t)CONCAT44(unaff_r4, in_lr));
    uVar1 = *(undefined4 *)(in_r0 + 0x10);
    *arg = (u8)uVar1;
    arg[1] = (u8)((uint)uVar1 >> 8);
    arg[2] = (u8)((uint)uVar1 >> 0x10);
    arg[3] = (u8)((uint)uVar1 >> 0x18);
    tl_zbTaskPost(nwkEndDevTimeoutInfoNVStore, arg);
  }
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
uint nwkEndDevTimeoutReqCmdHandler(void)

{
  undefined uVar1;
  undefined uVar2;
  u8 uVar3;
  bool bVar4;
  byte bVar5;
  zb_buf_t *in_r0;
  uint uVar6;
  tl_zb_normal_neighbor_entry_t *ptVar7;
  int in_r1;
  int in_r2;
  undefined uVar8;
  int iVar9;
  nwk_hdr_t local_58;
  undefined4 local_38;
  uint uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  undefined2 local_20;
  undefined local_1e;

  uStack_34 = 0;
  uStack_30 = 0;
  uStack_2c = 0;
  uStack_28 = 0;
  uStack_24 = 0;
  local_20 = 0;
  local_1e = 0;
  local_38 = 0xc;
  if ((*(byte *)(in_r2 + 4) < 0xf) && (*(char *)(in_r2 + 5) == '\0'))
  {
    ptVar7 = nwk_neTblGetByShortAddr(*(u16 *)(in_r1 + 2));
    if ((ptVar7 == (tl_zb_normal_neighbor_entry_t *)0x0) || ((ptVar7->field_0x1e & 0xe) != 4))
    {
      bVar5 = zb_buf_free(in_r0);
      return (uint)bVar5;
    }
    ptVar7->keepaliveRcvd = '\x01';
    iVar9 = 10;
    if (*(byte *)(in_r2 + 4) != 0)
    {
      iVar9 = 0x3c << (uint) * (byte *)(in_r2 + 4);
    }
    *(char *)&ptVar7->timeoutCnt = (char)iVar9;
    uVar1 = (undefined)((uint)iVar9 >> 8);
    *(undefined *)((int)&ptVar7->timeoutCnt + 1) = uVar1;
    uVar2 = (undefined)((uint)iVar9 >> 0x10);
    *(undefined *)((int)&ptVar7->timeoutCnt + 2) = uVar2;
    uVar8 = (undefined)((uint)iVar9 >> 0x18);
    *(undefined *)((int)&ptVar7->timeoutCnt + 3) = uVar8;
    *(char *)&ptVar7->devTimeout = (char)iVar9;
    *(undefined *)((int)&ptVar7->devTimeout + 1) = uVar1;
    *(undefined *)((int)&ptVar7->devTimeout + 2) = uVar2;
    *(undefined *)((int)&ptVar7->devTimeout + 3) = uVar8;
    *(undefined *)&ptVar7->endDevCfg = *(undefined *)(in_r2 + 5);
    *(undefined *)((int)&ptVar7->endDevCfg + 1) = 0;
    nwkEndDevTimeoutInfoStore();
    if ((int)((uint)g_zbInfo.nwkNib.parentInfo << 0x1e) < 0)
    {
      uStack_34 = uStack_34 & 0xffff0000 | (uint)g_zbInfo.nwkNib.parentInfo << 8;
    }
    else
    {
      uStack_34 = uStack_34 & 0xffff0000 | 0x100;
    }
  }
  else
  {
    uStack_34 = 1;
  }
  zb_buf_clear(in_r0);
  local_58._0_4_ = 0;
  local_58._4_4_ = 0;
  local_58.dstIeeeAddr._0_4_ = 0;
  local_58.dstIeeeAddr._4_4_ = 0;
  local_58.srcIeeeAddr._0_4_ = 0;
  local_58.srcIeeeAddr._4_4_ = 0;
  local_58._24_4_ = 0;
  local_58.srcRouteSubFrame.relayList = (u8 *)0x0;
  uVar6 = 0;
  if (((int)((uint)ss_ib._62_1_ << 0x1c) < 0) && ((ss_ib._62_1_ & 7) != 0))
  {
    bVar4 = ss_keyPreconfigured();
    uVar6 = (uint)bVar4;
  }
  local_58._4_4_ =
      local_58._4_4_ & 0xffff0000 |
      (uint)(CONCAT11((byte)(local_58._4_4_ >> 8) & 0xfd | (byte)(uVar6 << 1), (char)local_58._4_4_) & 0xffc0 | 0x1009) | 0x800;
  memcpy(local_58.srcIeeeAddr, g_zbInfo.macPib.extAddress, 8);
  memcpy(local_58.dstIeeeAddr, (void *)(in_r1 + 0x10), 8);
  local_58._0_4_ = CONCAT22(g_zbInfo.nwkNib.nwkAddr, *(undefined2 *)(in_r1 + 2));
  local_58._4_4_ = CONCAT13(g_zbInfo.nwkNib.seqNum, CONCAT12(1, (short)local_58._4_4_));
  g_zbInfo.nwkNib.seqNum = g_zbInfo.nwkNib.seqNum + '\x01';
  uVar3 = getNwkHdrSize(&local_58);
  local_58._24_2_ = CONCAT11(uVar3, local_58.mcaseControl);
  local_58._24_4_ = local_58._24_4_ & 0xffff0000 | (uint)local_58._24_2_;
  uVar6 = nwkEndDevTimeoutRspCmdSend();
  return uVar6;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void nwkEndDevTimeoutRspCmdSend(void)

{
  zb_buf_t *in_r0;
  undefined *puVar1;
  undefined *in_r2;
  u8 in_r3;

  puVar1 = (undefined *)tl_bufInitalloc(in_r0, '\x03');
  *puVar1 = *in_r2;
  puVar1[1] = in_r2[4];
  puVar1[2] = in_r2[5];
  (in_r0->hdr).handle = in_r3;
  nwk_fwdPacket();
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
u8 nwkEndDevTimeoutRspCnfHandler(void)

{
  u8 uVar1;
  zb_buf_t *in_r0;

  uVar1 = zb_buf_free(in_r0);
  return uVar1;
}
