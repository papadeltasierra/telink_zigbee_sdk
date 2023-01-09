// WARNING: Unknown calling convention -- yet parameter storage is locked
void aps_command_handle(void)

{
  char cVar1;
  zb_buf_t *in_r0;

  if (*(u16 *)(in_r0->buf + 0x14) != g_zbInfo.macPib.shortAddress)
  {
    cVar1 = **(char **)(in_r0->buf + 0xc);
    if (cVar1 == '\b')
    {
      ss_apsRequestKeyCmdHandle();
      return;
    }
    if (cVar1 == '\x0f')
    {
      ss_apsVerifyKeyCmdHandle();
      return;
    }
    if (cVar1 == '\x06')
    {
      ss_apsUpdateDeviceCmdHandle();
      return;
    }
  }
  zb_buf_free(in_r0);
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void aps_get_counter_value(void)

{
  aps_counter_value = aps_counter_value + '\x01';
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
byte aps_get_handle(void)

{
  byte bVar1;

  bVar1 = aps_handle;
  aps_handle = aps_handle + 1;
  return bVar1 & 0x3f;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
uint aps_hdr_parse(void)

{
  byte bVar1;
  byte *in_r0;
  int iVar2;
  byte *pbVar3;
  void *in_r1;
  byte *pbVar4;
  uint uVar5;
  uint uVar6;

  memset(in_r1, 0, 0xf);
  bVar1 = *in_r0;
  uVar6 = (uint)bVar1;
  *(byte *)((int)in_r1 + 1) = bVar1;
  uVar5 = uVar6 & 3;
  if (uVar5 == 3)
  {
    iVar2 = (uint)in_r0[2] * 0x100 + (uint)in_r0[1];
    *(char *)((int)in_r1 + 8) = (char)iVar2;
    *(char *)((int)in_r1 + 9) = (char)((uint)iVar2 >> 8);
    iVar2 = (uint)in_r0[4] * 0x100 + (uint)in_r0[3];
    *(char *)((int)in_r1 + 10) = (char)iVar2;
    *(char *)((int)in_r1 + 0xb) = (char)((uint)iVar2 >> 8);
    pbVar3 = in_r0 + 5;
  }
  else if (((int)(uVar6 << 0x1b) < 0) || (uVar5 == 1))
  {
    *(byte *)((int)in_r1 + 2) = in_r0[1];
    pbVar3 = in_r0 + 2;
  }
  else
  {
    if (((uVar6 & 0xc) == 8) || ((bVar1 & 0xc) == 0))
    {
      *(byte *)((int)in_r1 + 6) = in_r0[1];
      pbVar4 = in_r0 + 2;
    }
    else
    {
      iVar2 = (uint)in_r0[2] * 0x100 + (uint)in_r0[1];
      *(char *)((int)in_r1 + 6) = (char)iVar2;
      *(char *)((int)in_r1 + 7) = (char)((uint)iVar2 >> 8);
      pbVar4 = in_r0 + 3;
    }
    iVar2 = (uint)pbVar4[1] * 0x100 + (uint)*pbVar4;
    *(char *)((int)in_r1 + 8) = (char)iVar2;
    *(char *)((int)in_r1 + 9) = (char)((uint)iVar2 >> 8);
    iVar2 = (uint)pbVar4[3] * 0x100 + (uint)pbVar4[2];
    *(char *)((int)in_r1 + 10) = (char)iVar2;
    *(char *)((int)in_r1 + 0xb) = (char)((uint)iVar2 >> 8);
    *(byte *)((int)in_r1 + 3) = pbVar4[4];
    *(byte *)((int)in_r1 + 2) = pbVar4[5];
    pbVar3 = pbVar4 + 6;
    if ((int)(uVar6 * 0x1000000) < 0)
    {
      *(byte *)((int)in_r1 + 0xc) = pbVar4[6];
      *(byte *)((int)in_r1 + 0xd) = pbVar4[7];
      pbVar3 = pbVar4 + 8;
      if (uVar5 == 2)
      {
        *(byte *)((int)in_r1 + 0xe) = pbVar4[8];
        pbVar3 = pbVar4 + 9;
      }
    }
  }
  return (int)pbVar3 - (int)in_r0 & 0xff;
}
void aps_init(void)

{
  u32 uVar1;

  uVar1 = drv_u32Rand();
  aps_handle = 0;
  aps_counter_value = (char)uVar1;
  aps_me_init();
  return;
}
