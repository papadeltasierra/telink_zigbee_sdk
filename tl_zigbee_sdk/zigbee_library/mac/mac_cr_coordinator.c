// WARNING: Unknown calling convention -- yet parameter storage is locked
void tl_zbMacBeaconRequestCb(void)

{
  if ((((byte)g_zbInfo.nwkNib.capabilityInfo & 2) != 0) &&
      (g_zbInfo.macPib.beaconPayloadLen != '\0'))
  {
    tl_zbNwkBeaconPayloadUpdate();
    tl_zbMacMlmeBeaconCmdSend();
    g_zbMacCtx.beaconTriesNum = g_zbMacCtx.beaconTriesNum + 0xff;
  }
  return;
}
undefined4 tl_zbMacMlmeBeaconCmdSend(byte *param_1)

{
  u8 *p;
  u8 uVar1;
  void *dest;
  byte *pbVar2;
  u32 uVar3;
  byte bVar4;
  undefined4 uStack_28;
  undefined4 uStack_24;
  undefined2 local_20;

  uStack_24 = 0;
  local_20 = 0;
  uStack_28 = (uint)g_zbInfo.macPib.panId;
  bVar4 = *param_1;
  if (bVar4 == 3)
  {
    memcpy((void *)((int)&uStack_28 + 2), g_zbInfo.macPib.extAddress, 8);
  }
  else
  {
    memcpy((void *)((int)&uStack_28 + 2), &g_zbInfo.macPib.shortAddress, 2);
  }
  uVar1 = tl_zbMacHdrSize((ushort)param_1[2] << 4 | (ushort)bVar4 << 0xe);
  p = g_zbMacCtx.txRawDataBuf;
  if (-1 < (int)((uint)g_zbMacCtx.txRawDataBuf[0xc3] << 0x1c))
  {
    bVar4 = uVar1 + g_zbInfo.macPib.beaconPayloadLen + '\x04';
    g_zbMacCtx.txRawDataBuf[0xc3] = g_zbMacCtx.txRawDataBuf[0xc3] | 8;
    dest = tl_bufInitalloc((zb_buf_t *)p, bVar4);
    *p = (u8)dest;
    p[1] = (u8)((uint)dest >> 8);
    p[2] = (u8)((uint)dest >> 0x10);
    p[3] = (u8)((uint)dest >> 0x18);
    p[4] = bVar4;
    memset(dest, 0, (uint)bVar4);
    pbVar2 = (byte *)tl_zbMacHdrBuilder();
    *pbVar2 = param_1[4] & 0xf | param_1[5] << 4;
    bVar4 = g_zbInfo.macPib.associationPermit << 7 | 0xf | (byte)((param_1[3] & 1) << 4);
    pbVar2[1] = bVar4;
    if (aps_ib.aps_designated_coordinator == '\x01')
    {
      pbVar2[1] = bVar4 | 0x40;
    }
    memcpy(pbVar2 + 4, &g_zbInfo.macPib.beaconPayload, (uint)g_zbInfo.macPib.beaconPayloadLen);
    uVar3 = drv_u32Rand();
    ev_timer_taskPost(tl_zbMacPacketDelaySend, (void *)0x0, (uVar3 & 0x14) + 1);
  }
  return 0;
}
void tl_zbMacMlmeBeaconSendConfirm(undefined4 param_1, char param_2)

{
  if ((param_2 != '\0') && (g_zbMacCtx.beaconTriesNum != '\0'))
  {
    tl_zbMacBeaconRequestCb();
  }
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void tl_zbMacMlmeCoordRealignmentCmdSend(void)

{
  char in_r0;
  u8 uVar1;
  void *out;
  void *in_r1;
  undefined2 in_r2;
  zb_buf_t *in_r3;
  undefined4 local_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  undefined2 local_34;
  undefined local_30;
  undefined auStack_2f[2];
  undefined auStack_2d[2];
  u8 uStack_2b;
  undefined2 local_2a;
  u8 uStack_28;
  undefined2 local_26;

  local_26 = 0xfffe;
  uStack_40 = 0;
  uStack_38 = 0;
  local_34 = 0;
  uStack_3c = (uint)g_zbInfo.macPib.panId;
  local_44 = 0xfffe;
  memcpy((void *)((int)&uStack_3c + 2), g_zbInfo.macPib.extAddress, 8);
  if (in_r0 == '\0')
  {
    memcpy(&local_44, in_r1, 8);
    uVar1 = tl_zbMacHdrSize(0xcc23);
    local_30 = 8;
    memcpy(auStack_2f, in_r3->buf + 4, 2);
    memcpy(auStack_2d, &g_zbInfo.macPib.shortAddress, 2);
    uStack_2b = in_r3->buf[6];
    local_2a = in_r2;
  }
  else
  {
    uVar1 = tl_zbMacHdrSize(0xc803);
    local_30 = 8;
    memcpy(auStack_2f, in_r3->buf + 4, 2);
    memcpy(auStack_2d, &g_zbInfo.macPib.shortAddress, 2);
    uStack_2b = in_r3->buf[6];
    local_2a = 0xfffe;
  }
  uStack_28 = in_r3->buf[7];
  tl_bufInitalloc(in_r3, uVar1 + '\t');
  out = (void *)tl_zbMacHdrBuilder();
  memcpy(out, &local_30, 9);
  tl_zbMacTx();
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void tl_zbMacOrphanResponseHandler(void)

{
  u16 uVar1;
  void *in_r0;
  int iVar2;
  undefined4 local_1c;
  undefined4 uStack_18;
  undefined2 local_14;
  undefined local_12;

  local_1c = 0;
  uStack_18 = 0;
  local_14 = 0;
  local_12 = 0;
  memcpy(&local_1c, in_r0, 0xb);
  uVar1 = g_zbInfo.macPib.panId;
  *(char *)((int)in_r0 + 4) = (char)g_zbInfo.macPib.panId;
  *(char *)((int)in_r0 + 5) = (char)(uVar1 >> 8);
  *(u8 *)((int)in_r0 + 6) = g_zbMacCtx.curChannel;
  *(undefined *)((int)in_r0 + 7) = 0;
  *(undefined *)((int)in_r0 + 0xc1) = 0xe5;
  iVar2 = tl_zbMacMlmeCoordRealignmentCmdSend();
  if (iVar2 != 0)
  {
    tl_zbMacOrphanResponseStatusCheck(in_r0, 0xf1);
  }
  return;
}
void tl_zbMacOrphanResponseStatusCheck(zb_buf_t *param_1, char param_2)

{
  undefined auStack_1c[8];
  undefined auStack_14[8];

  memcpy(auStack_1c, param_1, 0xb);
  if (param_2 == '\0')
  {
    param_1->buf[0x14] = '\0';
    param_1->buf[0x15] = '\0';
    memcpy(param_1->buf + 2, auStack_1c, 8);
    param_1->buf[10] = '\x03';
    memcpy(param_1->buf + 0xb, auStack_14, 2);
    param_1->buf[0x13] = '\x02';
    tl_zbPrimitivePost('\x01', 'W', param_1);
  }
  else
  {
    zb_buf_free(param_1);
  }
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
int tl_zbMacPacketDelaySend(void)

{
  int iVar1;

  g_zbMacCtx.txRawDataBuf[0xc1] = 0xe3;
  iVar1 = tl_zbMacTx();
  return -(uint)(iVar1 == 0);
}