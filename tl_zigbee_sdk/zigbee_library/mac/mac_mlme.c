void tl_zbMacCmdPanIdConflictNotifySendCheck(undefined4 param_1, char param_2)

{
  u16 uVar1;
  undefined *arg;

  if ((param_2 == '\0') &&
      (arg = (undefined *)c1(), uVar1 = g_zbInfo.macPib.panId, arg != (undefined *)0x0))
  {
    *arg = (char)g_zbInfo.macPib.panId;
    arg[1] = (char)(uVar1 >> 8);
    arg[2] = 0;
    arg[3] = g_zbInfo.macPib.phyChannelCur;
    arg[4] = g_zbInfo.macPib.phyPageCur;
    tl_zbPrimitivePost('\x01', '\\', arg);
  }
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
undefined4 tl_zbMacCommStatusSend(void)

{
  undefined4 *in_r0;
  undefined in_r1;
  undefined auStack_2c[2];
  undefined uStack_2a;
  undefined uStack_29;
  undefined auStack_24[10];
  undefined auStack_1a[14];

  tl_zbMacHdrParse(auStack_2c, *in_r0);
  *(undefined *)(in_r0 + 5) = in_r1;
  *(undefined *)((int)in_r0 + 0x15) = 1;
  memcpy((void *)((int)in_r0 + 2), auStack_1a, 8);
  *(undefined *)((int)in_r0 + 10) = uStack_29;
  memcpy((void *)((int)in_r0 + 0xb), auStack_24, 8);
  *(undefined *)((int)in_r0 + 0x13) = uStack_2a;
  tl_zbPrimitivePost('\x01', 'W', in_r0);
  return 0;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void tl_zbMacPollRequestHandler(void)

{
  int in_r0;
  undefined local_20;
  char cStack_1f;
  undefined auStack_1e[8];
  undefined auStack_16[8];
  undefined uStack_e;

  if (g_zbInfo.macPib.shortAddress < 0xfffe)
  {
    local_20 = 2;
    memcpy(auStack_1e, &g_zbInfo.macPib.shortAddress, 2);
    cStack_1f = *(char *)(in_r0 + 10);
  }
  else
  {
    local_20 = 3;
    memcpy(auStack_1e, g_zbInfo.macPib.extAddress, 8);
    cStack_1f = *(char *)(in_r0 + 10);
  }
  if (cStack_1f == '\x03')
  {
    memcpy(auStack_16, (void *)(in_r0 + 2), 8);
  }
  else
  {
    memcpy(auStack_16, (void *)(in_r0 + 2), 2);
  }
  uStack_e = 1;
  tl_zbMacMlmeDataRequestCmdSend(&local_20, in_r0, 0xe8);
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void tl_zbMacResetRequestHandler(void)

{
  undefined *in_r0;

  *in_r0 = 0;
  tl_zbPrimitivePost('\x01', 'R', in_r0);
  return;
}
void tl_zbMacStartReqConfirm(char *param_1, char param_2)

{
  if (param_2 == '\0')
  {
    g_zbInfo.macPib.beaconOrder = param_1[8];
    if (g_zbInfo.macPib.beaconOrder == '\x0f')
    {
      g_zbInfo.macPib.superframeOrder._0_1_ = '\x0f';
      g_zbInfo.macPib.superframeOrder._1_1_ = param_2;
    }
    else
    {
      g_zbInfo.macPib.superframeOrder._0_1_ = param_1[9];
      g_zbInfo.macPib.superframeOrder._1_1_ = '\0';
    }
    g_zbInfo.macPib.panId._0_1_ = (undefined) * (undefined2 *)(param_1 + 4);
    g_zbInfo.macPib.panId._1_1_ = (undefined)((ushort) * (undefined2 *)(param_1 + 4) >> 8);
    g_zbInfo.macPib.phyPageCur = param_1[7];
    g_zbInfo.macPib.phyChannelCur = param_1[6];
    tl_zbMacChannelSet(g_zbInfo.macPib.phyChannelCur);
    rf_setTrxState('\x01');
  }
  *param_1 = param_2;
  tl_zbPrimitivePost('\x01', '[', param_1);
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void tl_zbMacStartRequestHandler(void)

{
  int in_r0;
  int iVar1;
  ushort uVar2;
  ushort uVar3;

  uVar3 = 0xe8;
  if ((*(byte *)(in_r0 + 8) < 0x10) &&
      ((*(byte *)(in_r0 + 9) <= *(byte *)(in_r0 + 8) || (*(byte *)(in_r0 + 9) == 0xf))))
  {
    uVar3 = ~(g_zbInfo.macPib.shortAddress + 1 + ~(g_zbInfo.macPib.shortAddress + 1) +
              (ushort)(0xfffe < g_zbInfo.macPib.shortAddress)) &
            0xec;
  }
  uVar2 = 0xe8;
  if (((int)((uint)g_zbNwkCtx._45_1_ << 0x1a) < 0) || (uVar2 = uVar3, uVar3 != 0))
  {
    tl_zbMacStartReqConfirm(in_r0, uVar2);
  }
  else if (*(char *)(in_r0 + 0x17) == '\0')
  {
    tl_zbMacStartReqConfirm(in_r0, 0);
  }
  else
  {
    *(undefined *)(in_r0 + 0xc1) = 0xe6;
    iVar1 = tl_zbMacMlmeCoordRealignmentCmdSend();
    if (iVar1 != 0)
    {
      tl_zbMacStartReqConfirm(in_r0, 0xe1);
    }
  }
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void tl_zbMlmeCmdAssociateReqRecvd(void)

{
  zb_buf_t *in_r0;
  int iVar1;
  int in_r1;

  iVar1 = *(int *)(in_r0->buf + 4);
  memcpy(in_r0, (void *)(in_r1 + 0x12), 8);
  in_r0->buf[9] = in_r0->buf[0x14];
  in_r0->buf[8] = *(u8 *)(iVar1 + 1);
  if (((macAppIndCb == 0) || (*(int *)(macAppIndCb + 8) == 0)) || (iVar1 = FUNBBBBG(), iVar1 != 0))
  {
    tl_zbPrimitivePost('\x01', 'G', in_r0);
  }
  else
  {
    zb_buf_free(in_r0);
  }
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void tl_zbMlmeCmdAssociateRespRecvd(void)

{
  int iVar1;
  zb_buf_t *in_r0;
  int in_r1;

  iVar1 = *(int *)(in_r0->buf + 4);
  memset(in_r0, 0, 0x16);
  if (*(char *)(in_r1 + 3) == '\x03')
  {
    memcpy(in_r0, (void *)(in_r1 + 0x12), 8);
  }
  else
  {
    in_r0->buf[0] = '\0';
    in_r0->buf[1] = '\0';
    in_r0->buf[2] = '\0';
    in_r0->buf[3] = '\0';
    in_r0->buf[4] = '\0';
    in_r0->buf[5] = '\0';
    in_r0->buf[6] = '\0';
    in_r0->buf[7] = '\0';
  }
  if ((g_zbMacCtx.status == '\x05') && (associationReqOrigBuffer != (zb_buf_t *)0x0))
  {
    tl_zbMacAssociateRespReceived(0);
    zb_buf_free(associationReqOrigBuffer);
    associationReqOrigBuffer = (zb_buf_t *)0x0;
    memcpy(in_r0->buf + 8, (void *)(iVar1 + 1), 2);
    memcpy(&g_zbInfo.macPib.shortAddress, in_r0->buf + 8, 2);
    in_r0->buf[10] = *(u8 *)(iVar1 + 3);
    tl_zbPrimitivePost('\x01', 'F', in_r0);
    return;
  }
  zb_buf_free(in_r0);
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void tl_zbMlmeCmdBeaconReqRecvd(void)

{
  byte bVar1;
  zb_buf_t *in_r0;

  bVar1 = rf_lqi2cost(in_r0->buf[0x14]);
  if ((bVar1 < 6) && ((g_zbNwkCtx._45_1_ & 0x24) == 4))
  {
    g_zbMacCtx.beaconTriesNum = '\x03';
    tl_zbMacBeaconRequestCb();
  }
  zb_buf_free(in_r0);
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void tl_zbMlmeCmdCoordRealignRecvd(void)

{
  zb_buf_t *in_r0;
  ushort *in_r1;
  int iVar1;

  iVar1 = *(int *)(in_r0->buf + 4);
  if (((((ushort)((ushort) * (byte *)(iVar1 + 2) * 0x100 + (ushort) * (byte *)(iVar1 + 1)) ==
         g_zbInfo.macPib.panId) &&
        (g_zbInfo.macPib.phyChannelCur == *(u8 *)(iVar1 + 5))) &&
       ((ushort)((ushort) * (byte *)(iVar1 + 6) + (ushort) * (byte *)(iVar1 + 7) * 0x100) ==
        g_zbInfo.macPib.shortAddress)) &&
      (g_zbMacCtx.status == '\x03'))
  {
    iVar1 = (uint) * (byte *)(iVar1 + 4) * 0x100 + (uint) * (byte *)(iVar1 + 3);
    g_zbInfo.macPib.coordShortAddress._0_1_ = (undefined)iVar1;
    g_zbInfo.macPib.coordShortAddress._1_1_ = (undefined)((uint)iVar1 >> 8);
    if (((uint)*in_r1 << 0x10) >> 0x1e == 3)
    {
      memcpy(g_zbInfo.macPib.coordExtAddress, in_r1 + 9, 8);
    }
    else
    {
      g_zbInfo.macPib.coordExtAddress[0] = '\0';
      g_zbInfo.macPib.coordExtAddress[1] = '\0';
      g_zbInfo.macPib.coordExtAddress[2] = '\0';
      g_zbInfo.macPib.coordExtAddress[3] = '\0';
      g_zbInfo.macPib.coordExtAddress[4] = '\0';
      g_zbInfo.macPib.coordExtAddress[5] = '\0';
      g_zbInfo.macPib.coordExtAddress[6] = '\0';
      g_zbInfo.macPib.coordExtAddress[7] = '\0';
    }
    tl_zbMacOrphanScanStatusUpdate();
  }
  zb_buf_free(in_r0);
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void tl_zbMlmeCmdDataReqRecvd(void)

{
  tl_zbMacMlmeDataRequestCb();
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void tl_zbMlmeCmdOrphanNotifyRecvd(void)

{
  zb_buf_t *in_r0;
  int in_r1;

  if (*(byte *)(in_r1 + 1) >> 6 == 3)
  {
    memcpy(in_r0, (void *)(in_r1 + 0x12), 8);
    tl_zbPrimitivePost('\x01', 'O', in_r0);
  }
  else
  {
    zb_buf_free(in_r0);
  }
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void tl_zbMlmeCmdPanIdConflictNotifyRecvd(void)

{
  u16 *in_r0;

  *in_r0 = g_zbInfo.macPib.panId;
  *(undefined *)(in_r0 + 1) = 0;
  *(u8 *)((int)in_r0 + 3) = g_zbInfo.macPib.phyChannelCur;
  *(u8 *)(in_r0 + 2) = g_zbInfo.macPib.phyPageCur;
  tl_zbPrimitivePost('\x01', '\\', in_r0);
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void tl_zbPhyMlmeIndicate(void)

{
  zb_buf_t *in_r0;
  undefined1 *puVar1;
  int iVar2;
  char cVar3;

  if (g_zbMacCtx.status == '\x05')
  {
    if (**(char **)(in_r0->buf + 4) != '\x02')
      goto LAB_000139b2;
    cVar3 = '\x02';
  }
  else
  {
    cVar3 = **(char **)(in_r0->buf + 4);
  }
  puVar1 = g_zbMacMlmeEventFromPhyTbl;
  iVar2 = 0;
  do
  {
    if ((*puVar1 == cVar3) && (*(int *)(g_zbMacMlmeEventFromPhyTbl + iVar2 * 5 + 1) != 0))
    {
      tl_zbPhyMlmeIndicate_sub();
      if (iVar2 != 8)
      {
        return;
      }
      break;
    }
    iVar2 = iVar2 + 1;
    puVar1 = puVar1 + 5;
  } while (iVar2 != 8);
LAB_000139b2:
  zb_buf_free(in_r0);
  return;
}
