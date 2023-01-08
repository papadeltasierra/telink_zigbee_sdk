// WARNING: Unknown calling convention -- yet parameter storage is locked
int tl_macMlmeDisassociateNotifyCmdSend(void)

{
  u8 uVar1;
  zb_buf_t *in_r0;
  undefined *puVar2;
  int iVar3;
  char in_r1;
  u16 auStack_38[4];
  u16 uStack_30;
  undefined auStack_2e[10];
  undefined auStack_24[8];
  u8 uStack_1c;

  uStack_30 = g_zbInfo.macPib.panId;
  if (in_r0->buf[0xb] == '\x01')
  {
    memcpy(auStack_38, in_r0->buf + 2, 8);
  }
  else if (in_r0->buf[0xb] == '\x02')
  {
    if (in_r0->buf[10] == '\x02')
    {
      auStack_38[0] = g_zbInfo.macPib.coordShortAddress;
    }
    else
    {
      memcpy(auStack_38, g_zbInfo.macPib.coordExtAddress, 8);
    }
  }
  memcpy(auStack_2e, g_zbInfo.macPib.extAddress, 8);
  uVar1 = tl_zbMacHdrSize((ushort)in_r0->buf[10] << 10 | 0xc063);
  tl_bufInitalloc(in_r0, uVar1 + '\x02');
  puVar2 = (undefined *)tl_zbMacHdrBuilder();
  (in_r0->hdr).handle = 0xe2;
  *puVar2 = 3;
  puVar2[1] = in_r0->buf[0xb];
  if (in_r1 == '\0')
  {
    iVar3 = tl_zbMacTx();
    if (iVar3 != 0)
    {
      iVar3 = 0xe1;
    }
  }
  else
  {
    uStack_1c = in_r0->buf[10];
    memcpy(auStack_24, auStack_38, 8);
    iVar3 = macDataPending();
  }
  return iVar3;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void tl_zbMacAssociateRequestHandler(void)

{
  u8 *p;
  u8 uVar1;
  u8 *in_r0;
  undefined *puVar2;
  int iVar3;
  undefined auStack_34[8];
  undefined2 uStack_2c;
  undefined auStack_2a[10];

  p = g_zbMacCtx.txRawDataBuf;
  if ((-1 < (int)((uint)g_zbMacCtx.txRawDataBuf[0xc3] << 0x1c)) &&
      (associationReqOrigBuffer == (u8 *)0x0))
  {
    g_zbMacCtx.txRawDataBuf[0xc3] = g_zbMacCtx.txRawDataBuf[0xc3] | 8;
    g_zbMacCtx.curChannel = *in_r0;
    associationReqOrigBuffer = in_r0;
    rf_setChannel(*in_r0);
    uStack_2c = 0xfffe;
    memcpy(auStack_34, in_r0 + 4, 8);
    memcpy(auStack_2a, g_zbInfo.macPib.extAddress, 8);
    uVar1 = tl_zbMacHdrSize((ushort)in_r0[0xc] << 10 | 0xc023);
    tl_bufInitalloc((zb_buf_t *)p, uVar1 + '\x02');
    p[0xc1] = 0xe0;
    puVar2 = (undefined *)tl_zbMacHdrBuilder();
    *puVar2 = 1;
    puVar2[1] = in_r0[0xd];
    iVar3 = tl_zbMacTx();
    if (iVar3 == 0)
    {
      return;
    }
  }
  memset(in_r0, 0, 0x16);
  in_r0[10] = 0xf2;
  tl_zbPrimitivePost('\x01', 'F', in_r0);
  associationReqOrigBuffer = (u8 *)0x0;
  return;
}
void tl_zbMacAssociateRequestStatusCheck(undefined4 param_1, byte param_2)

{
  void *pvVar1;
  u32 t_ms;
  uint uVar2;

  pvVar1 = associationReqOrigBuffer;
  uVar2 = (uint)param_2;
  if ((uVar2 == 0x20) || (~uVar2 + uVar2 + (uint)(0x1f < uVar2) != 0))
  {
    t_ms = FUN_00001624((uint)g_zbInfo.macPib.respWaitTime * 0x3c00, 1000);
    ev_timer_taskPost(tl_zbReadyToPullParentForAssoRsp, (void *)0x0, t_ms);
  }
  else
  {
    memset(associationReqOrigBuffer, 0, 0x16);
    *(byte *)((int)pvVar1 + 10) = param_2;
    tl_zbPrimitivePost('\x01', 'F', associationReqOrigBuffer);
    associationReqOrigBuffer = (void *)0x0;
  }
  return;
}
void tl_zbMacAssociateRespReceived(void)

{
  tl_zbMacIndirectDataTimerCancel();
  g_zbMacCtx.status = '\0';
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void tl_zbMacAssociateResponseHandler(void)

{
  u8 uVar1;
  zb_buf_t *in_r0;
  void *pvVar2;
  undefined *puVar3;
  int iVar4;
  undefined auStack_38[8];
  u16 uStack_30;
  undefined auStack_2e[10];
  undefined auStack_24[8];
  undefined uStack_1c;

  if ((int)((uint)g_zbNwkCtx._45_1_ << 0x1a) < 0)
  {
    zb_buf_free(in_r0);
  }
  else
  {
    uStack_30 = g_zbInfo.macPib.panId;
    memcpy(auStack_38, in_r0->buf + 2, 8);
    memcpy(auStack_2e, g_zbInfo.macPib.extAddress, 8);
    uVar1 = tl_zbMacHdrSize(0xcc63);
    pvVar2 = tl_bufInitalloc(in_r0, uVar1 + '\x04');
    puVar3 = (undefined *)tl_zbMacHdrBuilder();
    *puVar3 = 2;
    memcpy(puVar3 + 1, in_r0, 2);
    puVar3[3] = in_r0->buf[10];
    uStack_1c = 3;
    memcpy(auStack_24, in_r0->buf + 2, 8);
    in_r0->buf[0] = (u8)pvVar2;
    in_r0->buf[1] = (u8)((uint)pvVar2 >> 8);
    in_r0->buf[2] = (u8)((uint)pvVar2 >> 0x10);
    in_r0->buf[3] = (u8)((uint)pvVar2 >> 0x18);
    in_r0->buf[4] = uVar1 + '\x04';
    (in_r0->hdr).handle = 0xe1;
    iVar4 = macDataPending();
    if (iVar4 != 0)
    {
      tl_zbMacCommStatusSend();
    }
  }
  return;
}
void tl_zbMacDisassociateNotifyCmdConfirm(void *param_1, undefined param_2)

{
  *(undefined *)((int)param_1 + 0xb) = param_2;
  tl_zbPrimitivePost('\x01', 'J', param_1);
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void tl_zbMacDisassociateRequestHandler(void)

{
  u16 *in_r0;
  int iVar1;

  iVar1 = 0xe8;
  if ((g_zbInfo.macPib.panId != *in_r0) ||
      (iVar1 = tl_macMlmeDisassociateNotifyCmdSend(), iVar1 != 0))
  {
    *(char *)((int)in_r0 + 0xb) = (char)iVar1;
    tl_zbPrimitivePost('\x01', 'J', in_r0);
  }
  return;
}
undefined4 tl_zbReadyToPullParentForAssoRsp(void)

{
  void *pvVar1;
  void *out;
  code *in_r3;
  undefined local_24;
  undefined uStack_23;
  undefined auStack_22[8];
  undefined auStack_1a[8];
  undefined uStack_12;

  (*in_r3)();
  if (associationReqOrigBuffer != (void *)0x0)
  {
    out = (void *)c1();
    pvVar1 = associationReqOrigBuffer;
    if (out == (void *)0x0)
    {
      memset(associationReqOrigBuffer, 0, 0x16);
      *(undefined *)((int)pvVar1 + 10) = 0x1a;
      tl_zbPrimitivePost('\x01', 'F', associationReqOrigBuffer);
      associationReqOrigBuffer = (void *)0x0;
    }
    else
    {
      memcpy(out, associationReqOrigBuffer, 0x19);
      local_24 = 3;
      memcpy(auStack_22, g_zbInfo.macPib.extAddress, 8);
      uStack_23 = *(undefined *)((int)out + 0xc);
      memcpy(auStack_1a, (void *)((int)out + 4), 8);
      uStack_12 = 0;
      tl_zbMacMlmeDataRequestCmdSend(&local_24, out, 0xe9);
      tl_zbMacIndirectDataTimerStart(tl_zbWaitForAssociationRespTimeout, associationReqOrigBuffer);
    }
  }
  return 0xfffffffe;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
undefined4 tl_zbWaitForAssociationRespTimeout(void)

{
  void *in_r0;
  undefined4 uVar1;

  uVar1 = 0;
  if (in_r0 != (void *)0x0)
  {
    memset(in_r0, 0, 0x16);
    *(undefined *)((int)in_r0 + 10) = 0xeb;
    tl_zbPrimitivePost('\x01', 'F', in_r0);
    associationReqOrigBuffer = 0;
    g_zbMacCtx.status = '\0';
    tl_zbSwitchOffRx();
    g_zbMacCtx.indirectData.timer._0_1_ = 0;
    g_zbMacCtx.indirectData.timer._1_1_ = 0;
    g_zbMacCtx.indirectData.timer._2_1_ = 0;
    g_zbMacCtx.indirectData.timer._3_1_ = 0;
    uVar1 = 0xfffffffe;
  }
  return uVar1;
}
