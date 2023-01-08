void tl_zbMacMcpsDataRequestProc(void *arg)

{
  byte bVar1;
  byte bVar2;
  ushort uVar3;
  uint uVar4;
  int iVar5;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined2 local_2c;
  undefined auStack_28[8];
  undefined uStack_20;

  uStack_3c = 0;
  uStack_38 = 0;
  uStack_30 = 0;
  local_2c = 0;
  uVar4 = (uint) * (byte *)((int)arg + 0x13);
  if (uVar4 == 2)
  {
    if (*(short *)((int)arg + 0xb) == -1)
    {
      g_sysDiags.macTxBcast = g_sysDiags.macTxBcast + 1;
      uVar4 = (uint) * (byte *)((int)arg + 0x13);
    }
    else
    {
      g_sysDiags.macTxUcast = g_sysDiags.macTxUcast + 1;
      uVar4 = (uint) * (byte *)((int)arg + 0x13);
    }
  }
  uStack_34 = (uint)g_zbInfo.macPib.panId;
  bVar1 = *(byte *)((int)arg + 8);
  uVar3 = 0;
  if ((bVar1 != 0) && (uVar4 != 0))
  {
    uVar3 = *(ushort *)((int)arg + 9) - g_zbInfo.macPib.panId;
    uVar3 = (uVar3 + ~uVar3 + (ushort)(g_zbInfo.macPib.panId <= *(ushort *)((int)arg + 9))) * 0x40;
  }
  bVar2 = *(byte *)((int)arg + 0x1a);
  memcpy(&uStack_3c, (void *)((int)arg + 0xb), 8);
  if (bVar1 == 2)
  {
    uStack_34 = uStack_34 & 0xffff | (uint)g_zbInfo.macPib.shortAddress << 0x10;
  }
  else if (bVar1 == 3)
  {
    memcpy((void *)((int)&uStack_34 + 2), g_zbInfo.macPib.extAddress, 8);
  }
  bVar2 = tl_zbMacHdrSize(uVar3 | (ushort)bVar1 << 0xe | 1 | (ushort)((bVar2 & 1) << 5) |
                          (ushort)(uVar4 << 10));
  *(undefined *)((int)arg + 0xc1) = *(undefined *)((int)arg + 0x19);
  bVar1 = *(byte *)((int)arg + 0x14);
  iVar5 = *(int *)((int)arg + 0x15) - (uint)bVar2;
  tl_zbMacHdrBuilder();
  *(byte *)((int)arg + 0xc3) = *(byte *)((int)arg + 0xc3) | 2;
  if ((*(byte *)((int)arg + 0x1a) & 4) == 0)
  {
    iVar5 = tl_zbMacTx();
  }
  else
  {
    *(char *)arg = (char)iVar5;
    *(char *)((int)arg + 1) = (char)((uint)iVar5 >> 8);
    *(char *)((int)arg + 2) = (char)((uint)iVar5 >> 0x10);
    *(char *)((int)arg + 3) = (char)((uint)iVar5 >> 0x18);
    *(char *)((int)arg + 4) = (char)(((uint)bVar2 + (uint)bVar1) * 0x1000000 >> 0x18);
    uStack_20 = *(undefined *)((int)arg + 0x13);
    memcpy(auStack_28, (void *)((int)arg + 0xb), 8);
    iVar5 = macDataPending();
  }
  if (iVar5 != 0)
  {
    tl_zbMacMcpsDataRequestSendConfirm(arg);
  }
  return;
}
void tl_zbMacMcpsDataRequestSendConfirm(undefined *param_1, undefined param_2)

{
  char cVar1;
  undefined4 uVar2;
  u8 uVar3;
  undefined2 uVar4;

  cVar1 = param_1[0x19];
  if (param_1[0x13] == '\x02')
  {
    uVar4 = *(undefined2 *)(param_1 + 0xb);
  }
  else
  {
    uVar4 = 0xfffe;
  }
  param_1[0xc3] = param_1[0xc3] & 0xfd;
  if ((byte)(cVar1 + 0x90U) < 0x50)
  {
    param_1[1] = cVar1;
    *param_1 = param_2;
    tl_zbTaskPost(cGp_dataCnf, param_1);
  }
  else
  {
    param_1[8] = cVar1;
    param_1[9] = param_2;
    param_1[10] = (char)uVar4;
    param_1[0xb] = (char)((ushort)uVar4 >> 8);
    uVar2 = *(undefined4 *)(param_1 + 0x15);
    param_1[4] = (char)uVar2;
    param_1[5] = (char)((uint)uVar2 >> 8);
    param_1[6] = (char)((uint)uVar2 >> 0x10);
    param_1[7] = (char)((uint)uVar2 >> 0x18);
    param_1[0xc] = param_1[0xc2];
    uVar3 = rf_getLqi(param_1[0xc2]);
    param_1[0xd] = uVar3;
    tl_zbPrimitivePost('\x01', 'A', param_1);
  }
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void tl_zbPhyMldeIndication(void)

{
  undefined uVar1;
  undefined4 uVar2;
  undefined2 uVar3;
  void *in_r0;
  byte *in_r1;
  char in_r2;

  uVar1 = *(undefined *)((int)in_r0 + 0x14);
  uVar2 = *(undefined4 *)((int)in_r0 + 4);
  *(char *)((int)in_r0 + 4) = (char)uVar2;
  *(char *)((int)in_r0 + 5) = (char)((uint)uVar2 >> 8);
  *(char *)((int)in_r0 + 6) = (char)((uint)uVar2 >> 0x10);
  *(char *)((int)in_r0 + 7) = (char)((uint)uVar2 >> 0x18);
  *(char *)((int)in_r0 + 0x1d) = *(char *)((int)in_r0 + 0x13) - in_r2;
  *(byte *)((int)in_r0 + 0x26) = in_r1[2];
  memcpy((void *)((int)in_r0 + 0x1e), in_r1 + 8, 8);
  uVar3 = *(undefined2 *)(in_r1 + 6);
  *(char *)((int)in_r0 + 0x12) = (char)uVar3;
  *(char *)((int)in_r0 + 0x13) = (char)((ushort)uVar3 >> 8);
  *(byte *)((int)in_r0 + 0x1c) = in_r1[3];
  memcpy((void *)((int)in_r0 + 0x14), in_r1 + 0x12, 8);
  if (in_r1[4] == 0)
  {
    uVar3 = *(undefined2 *)(in_r1 + 0x10);
    *(char *)((int)in_r0 + 0x10) = (char)uVar3;
    *(char *)((int)in_r0 + 0x11) = (char)((ushort)uVar3 >> 8);
  }
  *(byte *)((int)in_r0 + 0x28) = in_r1[5];
  *(undefined *)((int)in_r0 + 0x27) = uVar1;
  if ((g_zbInfo.macPib.rxOnWhenIdle == '\0') && ((int)((uint)*in_r1 << 0x1b) < 0))
  {
    *(byte *)((int)in_r0 + 0xc3) = *(byte *)((int)in_r0 + 0xc3) | 0x10;
  }
  tl_zbPrimitivePost('\x01', 'B', in_r0);
  return;
}
