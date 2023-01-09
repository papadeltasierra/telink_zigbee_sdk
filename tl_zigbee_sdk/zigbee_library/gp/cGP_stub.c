void cGp_dataCnf(void *arg)

{
  cGpDataCnfHandler(arg);
  return;
}
s32 cGp_dataReq(void *arg)

{
  undefined uVar1;
  undefined uVar2;
  undefined uVar3;
  undefined uVar4;
  undefined4 uVar5;
  ushort uVar6;
  undefined auStack_44[16];
  undefined auStack_34[12];
  byte bStack_28;

  memcpy(auStack_44, arg, 0x1d);
  // WARNING: Load size is inaccurate
  uVar5 = *arg;
  uVar6 = *(ushort *)((int)arg + 6);
  uVar1 = *(undefined *)((int)arg + 0x18);
  uVar2 = *(undefined *)((int)arg + 0x19);
  uVar3 = *(undefined *)((int)arg + 0x1a);
  uVar4 = *(undefined *)((int)arg + 0x1b);
  memset(arg, 0, 0x26);
  *(undefined *)((int)arg + 8) = uVar1;
  *(undefined *)((int)arg + 0x13) = uVar2;
  memcpy((void *)((int)arg + 0xb), auStack_34, 8);
  *(char *)((int)arg + 9) = (char)uVar6;
  *(char *)((int)arg + 10) = (char)((uint)uVar6 >> 8);
  *(undefined *)((int)arg + 0x19) = uVar4;
  *(char *)((int)arg + 0x15) = (char)uVar5;
  *(char *)((int)arg + 0x16) = (char)((uint)uVar5 >> 8);
  *(char *)((int)arg + 0x17) = (char)((uint)uVar5 >> 0x10);
  *(char *)((int)arg + 0x18) = (char)((uint)uVar5 >> 0x18);
  *(undefined *)((int)arg + 0x14) = uVar3;
  if ((int)((uint)bStack_28 << 0x1e) < 0)
  {
    *(byte *)((int)arg + 0x1a) = *(byte *)((int)arg + 0x1a) | 1;
  }
  if ((int)((uint)bStack_28 << 0x1f) < 0)
  {
    *(byte *)((int)arg + 0x1a) = *(byte *)((int)arg + 0x1a) | 8;
  }
  tl_zbMacMcpsDataRequestProc(arg);
  return -2;
}
void cGp_mcpsDataInd(void *arg)

{
  undefined uVar1;
  undefined uVar2;
  undefined uVar3;
  undefined uVar4;
  undefined uVar5;
  undefined uVar6;
  undefined4 uVar7;
  ushort uVar8;
  ushort uVar9;
  int iVar10;
  undefined local_60;
  undefined local_5c;
  undefined auStack_50[20];
  undefined auStack_3c[10];
  undefined auStack_32[14];

  uVar1 = *(undefined *)((int)arg + 0xc2);
  memcpy(auStack_50, arg, 0x2c);
  uVar7 = *(undefined4 *)((int)arg + 4);
  uVar8 = *(ushort *)((int)arg + 0x10);
  uVar9 = *(ushort *)((int)arg + 0x12);
  uVar5 = *(undefined *)((int)arg + 0x1c);
  uVar6 = *(undefined *)((int)arg + 0x1d);
  uVar2 = *(undefined *)((int)arg + 0x26);
  uVar3 = *(undefined *)((int)arg + 0x27);
  uVar4 = *(undefined *)((int)arg + 0x28);
  iVar10 = cgp_mcpsDataIndFilter();
  if (iVar10 == 0)
  {
    *(undefined *)((int)arg + 0x1b) = uVar3;
    *(undefined *)((int)arg + 0x1a) = uVar1;
    *(undefined *)((int)arg + 0x1c) = uVar4;
    *(undefined *)((int)arg + 0x18) = uVar5;
    local_60 = (undefined)uVar8;
    *(undefined *)((int)arg + 4) = local_60;
    *(char *)((int)arg + 5) = (char)((uint)uVar8 >> 8);
    memcpy((void *)((int)arg + 8), auStack_3c, 8);
    *(undefined *)((int)arg + 0x19) = uVar2;
    local_5c = (undefined)uVar9;
    *(undefined *)((int)arg + 6) = local_5c;
    *(char *)((int)arg + 7) = (char)((uint)uVar9 >> 8);
    memcpy((void *)((int)arg + 0x10), auStack_32, 8);
    *(undefined *)((int)arg + 0x1d) = uVar6;
    *(char *)arg = (char)uVar7;
    *(char *)((int)arg + 1) = (char)((uint)uVar7 >> 8);
    *(char *)((int)arg + 2) = (char)((uint)uVar7 >> 0x10);
    *(char *)((int)arg + 3) = (char)((uint)uVar7 >> 0x18);
    tl_zbTaskPost(dGp_dataInd, arg);
  }
  else
  {
    zb_buf_free((zb_buf_t *)arg);
  }
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
byte cgp_mcpsDataIndFilter(void)

{
  byte bVar1;
  byte bVar2;
  byte *in_r0;
  byte bVar3;

  bVar1 = *in_r0;
  bVar3 = 1;
  if (((((bVar1 & 0x3c) == 0xc) && ((bVar1 & 3) < 2)) && (bVar3 = 0, (bVar1 & 0x80) != 0)) &&
      (bVar3 = 1, (bVar1 & 3) != 1))
  {
    bVar2 = in_r0[1];
    if ((((bVar1 & 0x40) == 0) || ((bVar2 & 0x40) == 0)) &&
        ((bVar3 = bVar2 >> 7, (bVar2 & 7) != 2 && (bVar3 = 1, (bVar2 & 7) == 0))))
    {
      bVar3 = bVar2 >> 7;
    }
  }
  return bVar3;
}
