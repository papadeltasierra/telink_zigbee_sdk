// WARNING: Unknown calling convention -- yet parameter storage is locked
uint tl_zbMacHdrParse(ushort *param_1, ushort *param_2)

{
  ushort uVar1;
  uint uVar2;
  uint uVar3;
  void *in;

  uVar1 = *param_2;
  uVar2 = (uint)uVar1;
  memset(param_1, 0, 0x1a);
  *param_1 = uVar1;
  *(undefined *)((int)param_1 + 5) = *(undefined *)(param_2 + 1);
  in = (void *)((int)param_2 + 3);
  *(byte *)(param_1 + 1) = (byte)((uVar2 << 0x14) >> 0x1e);
  uVar3 = (uVar2 << 0x10) >> 0x1e;
  *(byte *)((int)param_1 + 3) = (byte)(uVar2 >> 8) >> 6;
  *(byte *)(param_1 + 2) = (byte)((uVar2 << 0x19) >> 0x1f);
  if ((uVar2 << 0x14) >> 0x1e != 0)
  {
    memcpy(param_1 + 3, in, 2);
    if (*(char *)(param_1 + 1) == '\x02')
    {
      memcpy(param_1 + 4, (void *)((int)param_2 + 5), 2);
      in = (void *)((int)param_2 + 7);
      uVar3 = (uint) * (byte *)((int)param_1 + 3);
    }
    else
    {
      memcpy(param_1 + 4, (void *)((int)param_2 + 5), 8);
      in = (void *)((int)param_2 + 0xd);
      uVar3 = (uint) * (byte *)((int)param_1 + 3);
    }
  }
  if (uVar3 == 0)
    goto LAB_000129d6;
  if (*(char *)(param_1 + 2) == '\0')
  {
    memcpy(param_1 + 8, in, 2);
    in = (void *)((int)in + 2);
    if (*(char *)((int)param_1 + 3) == '\x02')
      goto LAB_00012a1a;
  }
  else if (uVar3 == 2)
  {
  LAB_00012a1a:
    memcpy(param_1 + 9, in, 2);
    in = (void *)((int)in + 2);
    goto LAB_000129d6;
  }
  memcpy(param_1 + 9, in, 8);
  in = (void *)((int)in + 8);
LAB_000129d6:
  return (int)in - (int)param_2 & 0xff;
}
u8 tl_zbMacHdrSize(u16 frameCtrl)

{
  u8 uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;

  uVar2 = (uint)frameCtrl;
  uVar3 = (uVar2 << 0x14) >> 0x1e;
  uVar4 = (uVar2 << 0x10) >> 0x1e;
  uVar1 = '\x03';
  if ((uVar3 != 0) && (uVar1 = '\a', uVar3 == 3))
  {
    uVar1 = '\r';
  }
  if (uVar4 != 0)
  {
    if (uVar4 == 3)
    {
      uVar1 = uVar1 + '\b';
    }
    else
    {
      uVar1 = uVar1 + '\x02';
    }
    if (-1 < (int)(uVar2 << 0x19))
    {
      uVar1 = uVar1 + '\x02';
    }
  }
  return uVar1;
}
