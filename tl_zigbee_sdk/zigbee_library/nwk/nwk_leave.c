// WARNING: Unknown calling convention -- yet parameter storage is locked
void nwkLeaveReqSend(void)

{
  u16 uVar1;
  u8 uVar2;
  bool bVar3;
  uint uVar4;
  nwk_hdr_t *in_r1;

  uVar4 = 0;
  if (((int)((uint)ss_ib._62_1_ << 0x1c) < 0) && ((ss_ib._62_1_ & 7) != 0))
  {
    bVar3 = ss_keyPreconfigured();
    uVar4 = (uint)(bVar3 != false);
  }
  *(byte *)&in_r1->framecontrol = *(byte *)&in_r1->framecontrol & 0xfc | 1;
  *(byte *)&in_r1->framecontrol = *(byte *)&in_r1->framecontrol & 0xc3 | 8;
  (in_r1->framecontrol).field_0x1 = (in_r1->framecontrol).field_0x1 & 0xfd | (byte)(uVar4 << 1);
  (in_r1->framecontrol).field_0x1 = (in_r1->framecontrol).field_0x1 | 0x10;
  memcpy(in_r1->srcIeeeAddr, g_zbInfo.macPib.extAddress, 8);
  uVar1 = g_zbInfo.nwkNib.nwkAddr;
  *(char *)&in_r1->srcAddr = (char)g_zbInfo.nwkNib.nwkAddr;
  *(char *)((int)&in_r1->srcAddr + 1) = (char)(uVar1 >> 8);
  in_r1->radius = '\x01';
  in_r1->seqNum = g_zbInfo.nwkNib.seqNum;
  g_zbInfo.nwkNib.seqNum = g_zbInfo.nwkNib.seqNum + '\x01';
  uVar2 = getNwkHdrSize(in_r1);
  in_r1->frameHdrLen = uVar2;
  tl_zbNwkSendLeaveReqCmd();
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void nwkLeaveReqStart(void)

{
  ushort in_r1;

  if ((in_r1 & 0xfff8) != 0xfff8)
  {
    zb_address_ieee_by_short(in_r1, (addrExt_t)(ulonglong)in_r1);
  }
  nwkLeaveReqSend();
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void nwk_leaveCmdSendCnf(void)

{
  u8 uVar1;
  ushort in_r1;
  undefined4 in_stack_ffffffe8;
  undefined4 in_stack_ffffffec;

  if (((in_r1 & 0xfff8) != 0xfff8) &&
      (uVar1 = zb_address_ieee_by_short(in_r1, (addrExt_t)CONCAT44(in_stack_ffffffec, in_stack_ffffffe8)),
       uVar1 != '\0'))
  {
    memcpy(&stack0xffffffe8, &g_invalid_addr, 8);
  }
  nwk_nlmeLeaveCnf();
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void nwk_nlmeLeaveCnf(void)

{
  void *in_r0;
  undefined in_r1;
  void *in_r2;

  *(undefined *)((int)in_r0 + 8) = in_r1;
  memcpy(in_r0, in_r2, 8);
  tl_zbTaskPost(zdo_nlme_leave_confirm_cb, in_r0);
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void tl_zbNwkLeaveReqCmdHandler(void)

{
  byte bVar1;
  u8 uVar2;
  zb_buf_t *in_r0;
  tl_zb_normal_neighbor_entry_t *ptVar3;
  byte bVar4;
  ushort *in_r1;
  int in_r2;
  undefined in_stack_ffffffdc;
  undefined7 in_stack_ffffffdd;

  if ((((int)((uint)g_zbNwkCtx._45_1_ << 0x1d) < 0) &&
       (1 < (int)((uint)in_r0->buf[0x1d] - (uint) * (byte *)((int)in_r1 + 0x19)))) &&
      (uVar2 = tl_zbExtAddrByShortAddr(in_r1[1], (addrExt_t)CONCAT71(in_stack_ffffffdd, in_stack_ffffffdc),
                                       (u16 *)&stack0xffffffdc),
       uVar2 != 0xff))
  {
    ptVar3 = nwk_neTblGetByShortAddr(in_r1[1]);
    bVar1 = *(byte *)(in_r2 + 4);
    bVar4 = (byte)(((uint)bVar1 << 0x1a) >> 0x1f);
    if ((((char)bVar1 < '\0') && (ptVar3 != (tl_zb_normal_neighbor_entry_t *)0x0)) &&
        ((ptVar3->field_0x1e & 0x70) == 0))
    {
      in_r0->buf[0] = '\0';
      in_r0->buf[1] = '\0';
      in_r0->buf[2] = '\0';
      in_r0->buf[3] = '\0';
      in_r0->buf[4] = '\0';
      in_r0->buf[5] = '\0';
      in_r0->buf[6] = '\0';
      in_r0->buf[7] = '\0';
      in_r0->buf[9] = bVar4;
      in_r0->buf[8] = '\x01';
      tl_zbTaskPost(tl_zbNwkNlmeLeaveRequestHandler, in_r0);
      return;
    }
    if ((-1 < (int)((uint)bVar1 << 0x19)) || ((*in_r1 & 0xfff8) == 0xfff8))
    {
      in_r0->buf[8] = bVar4;
      memcpy(in_r0, &stack0xffffffdc, 8);
      tl_zbTaskPost(zdo_nlme_leave_indication_cb, in_r0);
      return;
    }
  }
  zb_buf_free(in_r0);
  return;
}
void tl_zbNwkNlmeLeaveRequestHandler(void *arg)

{
  int iVar1;
  tl_zb_normal_neighbor_entry_t *ptVar2;
  undefined in_stack_ffffffec;
  undefined7 in_stack_ffffffed;

  memcpy(&stack0xffffffec, arg, 8);
  iVar1 = memcmp(arg, &g_zero_addr, 8);
  if ((iVar1 == 0) || (iVar1 = memcmp(arg, g_zbInfo.macPib.extAddress, 8), iVar1 == 0))
  {
    *(byte *)((int)arg + 0xc3) =
        *(byte *)((int)arg + 0xc3) & 0xfb | ('\x01' - (*(char *)((int)arg + 9) == '\0')) * '\x04';
    nwkLeaveReqStart();
  }
  else if ((int)((uint)g_zbNwkCtx._45_1_ << 0x1d) < 0)
  {
    ptVar2 = nwk_neTblGetByExtAddr((addrExt_t)CONCAT71(in_stack_ffffffed, in_stack_ffffffec));
    if (ptVar2 == (tl_zb_normal_neighbor_entry_t *)0x0)
    {
      nwk_nlmeLeaveCnf();
    }
    else if ((ptVar2->field_0x1e & 0x70) == 0x50)
    {
      nwk_nlmeLeaveCnf();
    }
    else
    {
      tl_zbshortAddrByIdx(ptVar2->addrmapIdx);
      nwkLeaveReqStart();
    }
  }
  else
  {
    nwk_nlmeLeaveCnf();
  }
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void tl_zbNwkSendLeaveReqCmd(void)

{
  zb_buf_t *in_r0;
  undefined *puVar1;
  undefined *in_r2;
  u8 in_r3;

  puVar1 = (undefined *)tl_bufInitalloc(in_r0, '\x02');
  *puVar1 = *in_r2;
  puVar1[1] = in_r2[4];
  (in_r0->hdr).handle = in_r3;
  if (in_r3 == 199)
  {
    nwk_tx();
  }
  else
  {
    nwk_fwdPacket();
  }
  return;
}
