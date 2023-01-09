void cGpDataCnfHandler(void *arg)

{
  gpDataCnfDeliver();
  zb_buf_free((zb_buf_t *)arg);
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
u8 dGpStubHandleGet(void)

{
  dGpStubHandle = dGpStubHandle + 1;
  if (0xbd < dGpStubHandle)
  {
    dGpStubHandle = 0x70;
  }
  return dGpStubHandle;
}
// WARNING: Removing unreachable block (RAM,0x00027c9c)
// WARNING: Removing unreachable block (RAM,0x00027c8e)
// WARNING: Removing unreachable block (RAM,0x00027dca)
// WARNING: Removing unreachable block (RAM,0x00027d2c)
// WARNING: Removing unreachable block (RAM,0x00027dbc)
// WARNING: Removing unreachable block (RAM,0x00027ca2)
// WARNING: Removing unreachable block (RAM,0x00027cba)
// WARNING: Removing unreachable block (RAM,0x00027cc4)
// WARNING: Removing unreachable block (RAM,0x00027cfc)
// WARNING: Removing unreachable block (RAM,0x00027d06)
// WARNING: Removing unreachable block (RAM,0x00027d0e)
// WARNING: Removing unreachable block (RAM,0x00027d8c)
// WARNING: Removing unreachable block (RAM,0x00027d96)
// WARNING: Removing unreachable block (RAM,0x00027d9a)
// WARNING: Removing unreachable block (RAM,0x00027d9e)
void dGp_dataInd(void *arg)

{
  uint uVar1;

  uVar1 = gpNwkHdrParse();
  if ((uVar1 == 0) || (*(byte *)((int)arg + 0x1d) <= uVar1))
  {
    zb_buf_free((zb_buf_t *)arg);
  }
  else
  {
    gpDataFrameProcess();
  }
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void gpDataCnfDeliver(void)

{
  char *in_r0;

  if ((gpStubCb != (int *)0x0) && (*gpStubCb != 0))
  {
    if ((*in_r0 == '\x05') && (in_r0[1] == -0x42))
    {
      gpTransmitChannelTimeoutStop();
    }
    _gpTxQueueCheck();
  }
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void gpDataFrameProcess(void)

{
  u8 uVar1;
  u8 uVar2;
  u8 uVar3;
  ushort uVar4;
  undefined4 uVar5;
  zb_buf_t *in_r0;
  undefined *dest;
  int iVar6;
  undefined4 *in_r1;
  uint uVar7;
  u8 in_r2;
  uint uVar8;
  byte bVar9;
  u8 *in_r3;
  uint uVar10;
  u8 in_stack_00000000;
  undefined4 in_stack_00000004;
  u8 local_54;
  undefined auStack_44[8];
  undefined auStack_3c[24];

  memcpy(auStack_44, in_r0, 0x1e);
  uVar4 = *(ushort *)(in_r0->buf + 4);
  uVar1 = in_r0->buf[0x18];
  uVar2 = in_r0->buf[0x1a];
  uVar3 = in_r0->buf[0x1b];
  bVar9 = in_r0->buf[0x1c];
  uVar7 = (uint)bVar9;
  memset(in_r0, 0, 0x28);
  in_r0->buf[0x1c] = '\x01';
  in_r0->buf[0x1d] = uVar2;
  in_r0->buf[0x1e] = uVar3;
  in_r0->buf[0x1f] = bVar9;
  in_r0->buf[0x20] = uVar1;
  local_54 = (u8)uVar4;
  in_r0->buf[0x18] = local_54;
  in_r0->buf[0x19] = (u8)((uint)uVar4 >> 8);
  memcpy(in_r0->buf + 0x10, auStack_3c, 8);
  in_r0->buf[0x21] = in_r2;
  uVar8 = 0;
  if ((*(byte *)(in_r1 + 2) & 0x80) != 0)
  {
    uVar8 = ((uint) * (byte *)((int)in_r1 + 9) << 0x1b) >> 0x1e;
  }
  in_r0->buf[0x22] = (u8)uVar8;
  in_r0->buf[0x23] = '\0';
  in_r0->buf[0x1a] = (byte)(((uint) * (byte *)(in_r1 + 2) << 0x19) >> 0x1f);
  bVar9 = 0;
  if ((*(byte *)(in_r1 + 2) & 0x80) != 0)
  {
    bVar9 = (byte)(((uint) * (byte *)((int)in_r1 + 9) << 0x19) >> 0x1f);
  }
  in_r0->buf[0x1b] = bVar9;
  uVar5 = *in_r1;
  in_r0->buf[4] = (u8)uVar5;
  in_r0->buf[5] = (u8)((uint)uVar5 >> 8);
  in_r0->buf[6] = (u8)((uint)uVar5 >> 0x10);
  in_r0->buf[7] = (u8)((uint)uVar5 >> 0x18);
  in_r0->buf[0x24] = *(u8 *)((int)in_r1 + 10);
  uVar10 = uVar7;
  if (uVar8 != 0)
  {
    uVar10 = in_r1[1];
  }
  in_r0->buf[8] = (u8)uVar10;
  in_r0->buf[9] = (u8)(uVar10 >> 8);
  in_r0->buf[10] = (u8)(uVar10 >> 0x10);
  in_r0->buf[0xb] = (u8)(uVar10 >> 0x18);
  in_r0->buf[0x25] = *in_r3;
  in_r0->buf[0] = (u8)in_r3;
  in_r0->buf[1] = (u8)((uint)in_r3 >> 8);
  in_r0->buf[2] = (u8)((uint)in_r3 >> 0x10);
  in_r0->buf[3] = (u8)((uint)in_r3 >> 0x18);
  in_r0->buf[0x26] = in_stack_00000000;
  in_r0->buf[0xc] = (u8)in_stack_00000004;
  in_r0->buf[0xd] = (u8)((uint)in_stack_00000004 >> 8);
  in_r0->buf[0xe] = (u8)((uint)in_stack_00000004 >> 0x10);
  in_r0->buf[0xf] = (u8)((uint)in_stack_00000004 >> 0x18);
  in_r0->buf[0x27] = (byte)(((uint) * (byte *)(in_r1 + 2) << 0x1e) >> 0x1e);
  dest = (undefined *)c1();
  if (dest == (undefined *)0x0)
  {
    zb_buf_free(in_r0);
    FUN_00027bde();
    return;
  }
  iVar6 = gpDataIndSecReqEntryAdd();
  if (iVar6 == 0)
  {
    FUN_00027c10();
    return;
  }
  uVar8 = 0;
  if ((*(byte *)(in_r1 + 2) & 0x80) != 0)
  {
    uVar8 = ((uint) * (byte *)((int)in_r1 + 9) << 0x1a) >> 0x1f;
  }
  *(byte *)(iVar6 + 0x12) = *(byte *)(iVar6 + 0x12) & 0xf7 | (byte)(uVar8 << 3);
  uVar8 = 0;
  if ((*(byte *)(in_r1 + 2) & 0x80) != 0)
  {
    uVar8 = ((uint) * (byte *)((int)in_r1 + 9) << 0x1b) >> 0x1e;
  }
  *(byte *)(iVar6 + 0x12) = *(byte *)(iVar6 + 0x12) & 0xcf | (byte)(uVar8 << 4);
  if ((*(byte *)(iVar6 + 0x12) & 0x30) != 0)
  {
    uVar7 = in_r1[1];
  }
  *(char *)(iVar6 + 4) = (char)uVar7;
  *(char *)(iVar6 + 5) = (char)(uVar7 >> 8);
  *(char *)(iVar6 + 6) = (char)(uVar7 >> 0x10);
  *(char *)(iVar6 + 7) = (char)(uVar7 >> 0x18);
  memset(dest, 0, 0x11);
  dest[0xc] = in_r2;
  if (in_r2 == '\0')
  {
    uVar5 = *in_r1;
    *dest = (char)uVar5;
    dest[1] = (char)((uint)uVar5 >> 8);
    dest[2] = (char)((uint)uVar5 >> 0x10);
    dest[3] = (char)((uint)uVar5 >> 0x18);
  }
  else if (in_r2 == '\x02')
  {
    memcpy(dest, auStack_3c, 8);
    dest[0xd] = in_r0->buf[0x24];
  }
  dest[0xe] = (byte)(((uint) * (byte *)(iVar6 + 0x12) << 0x1a) >> 0x1e);
  dest[0xf] = (byte)(((uint) * (byte *)(iVar6 + 0x12) << 0x1c) >> 0x1f);
  uVar5 = *(undefined4 *)(iVar6 + 4);
  dest[8] = (char)uVar5;
  dest[9] = (char)((uint)uVar5 >> 8);
  dest[10] = (char)((uint)uVar5 >> 0x10);
  dest[0xb] = (char)((uint)uVar5 >> 0x18);
  dest[0x10] = *(undefined *)(iVar6 + 0x11);
  tl_zbTaskPost(gpSecReqSend, dest);
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void gpDataIndSecReqEntryClear(void)

{
  zb_buf_t **in_r0;

  if (*in_r0 != (zb_buf_t *)0x0)
  {
    zb_buf_free(*in_r0);
  }
  memset(in_r0, 0, 0x13);
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
// WARNING: Unknown calling convention -- yet parameter storage is locked
// WARNING: Unknown calling convention -- yet parameter storage is locked
void gpDataIndSecReqTabInit(void)

{
  int iVar1;

  iVar1 = 0;
  do
  {
    gpDataIndSecReqEntryClear();
    iVar1 = iVar1 + 1;
  } while (iVar1 != 4);
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void gpDataIndSend(void)

{
  u8 uVar1;
  u8 uVar2;
  int in_r0;

  if ((gpStubCb == 0) || (*(int *)(gpStubCb + 4) == 0))
  {
    gpDataIndSecReqEntryClear();
  }
  else
  {
    *(undefined *)(in_r0 + 0x10) = g_gpBaseCtx._5_1_;
    uVar1 = g_gpBaseCtx._4_1_;
    if (((int)g_gpBaseCtx == 0) || (uVar2 = rf_getChannel(), uVar1 == uVar2))
    {
      _gpDataIndSecReqEntryAdd();
    }
  }
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void gpDataReq(void)

{
  zb_buf_t *in_r0;

  if ((int)((uint)in_r0->buf[0x10] << 0x1f) < 0)
  {
    if (in_r0->buf[0x12] == '\0')
    {
      in_r0->buf[0x10] = in_r0->buf[0x10] & 0xdf;
    }
    else if (in_r0->buf[0x12] != '\x02')
      goto LAB_00027f8a;
    in_r0->buf[4] = 0xfe;
    in_r0->buf[5] = 0xfe;
    in_r0->buf[6] = 0xfe;
    in_r0->buf[7] = '\0';
    gpTxQueueCheck();
  }
  else
  {
  LAB_00027f8a:
    zb_buf_free(in_r0);
  }
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
byte gpNwkHdrFrameCtrlBuild(void)

{
  byte in_r0;
  uint in_r1;
  byte in_r2;
  uint in_r3;
  char in_stack_00000000;
  uint in_stack_00000004;
  uint in_stack_00000008;
  byte *in_stack_0000000c;
  byte local_28;

  local_28 = (byte)((in_r1 & 1) << 6) | in_r0 & 3 | 0xc;
  if (in_stack_0000000c != (byte *)0x0)
  {
    local_28 = 0x7f;
    *in_stack_0000000c = *in_stack_0000000c & 0xf8 | in_r2 & 7;
    *in_stack_0000000c = *in_stack_0000000c & 0xe7 | (byte)((in_r3 & 3) << 3);
    *in_stack_0000000c = *in_stack_0000000c & 0xdf | ('\x01' - (in_stack_00000000 == '\0')) * ' ';
    *in_stack_0000000c = *in_stack_0000000c & 0xbf | (byte)((in_stack_00000004 & 1) << 6);
    *in_stack_0000000c = *in_stack_0000000c & 0x7f | (byte)((in_stack_00000008 & 0xff) << 7);
  }
  return local_28;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
uint gpNwkHdrParse(void)

{
  byte bVar1;
  void *in_r0;
  undefined *in_r1;
  undefined *in;
  byte bVar2;

  *(undefined *)((int)in_r0 + 8) = *in_r1;
  in = in_r1 + 1;
  bVar1 = *(byte *)((int)in_r0 + 8);
  bVar2 = 0;
  if ((bVar1 & 0x80) != 0)
  {
    *(undefined *)((int)in_r0 + 9) = in_r1[1];
    bVar2 = *(byte *)((int)in_r0 + 9);
    if (((bVar2 & 7) != 2) && ((bVar2 & 7) != 0))
    {
      return 0;
    }
    if ((bVar2 & 0x80) != 0)
    {
      return 0;
    }
    in = in_r1 + 2;
    bVar2 = bVar2 & 7;
  }
  if (((bVar1 & 3 | bVar2) == 0) || (((bVar1 & 0x83) == 0x81 && (bVar2 == 0))))
  {
    memcpy(in_r0, in, 4);
    in = in + 4;
    bVar1 = *(byte *)((int)in_r0 + 8);
  }
  if (bVar2 == 2)
  {
    *(undefined *)((int)in_r0 + 10) = *in;
    in = in + 1;
  }
  if (((bVar1 & 0x80) != 0) && (1 < ((uint) * (byte *)((int)in_r0 + 9) << 0x1b) >> 0x1e))
  {
    memcpy((void *)((int)in_r0 + 4), in, 4);
    in = in + 4;
  }
  return (int)in - (int)in_r1 & 0xff;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void gpSecReqSend(void)

{
  u8 uVar1;
  u8 uVar2;
  u8 uVar3;
  u8 uVar4;
  undefined4 uVar5;
  zb_buf_t *in_r0;
  int iVar6;
  undefined auStack_38[20];

  if ((gpStubCb == 0) || (*(int *)(gpStubCb + 8) == 0))
  {
    zb_buf_free(in_r0);
  }
  else
  {
    memcpy(auStack_38, in_r0, 0x11);
    uVar5 = *(undefined4 *)(in_r0->buf + 8);
    uVar1 = in_r0->buf[0xc];
    uVar2 = in_r0->buf[0xd];
    uVar3 = in_r0->buf[0xe];
    uVar4 = in_r0->buf[0x10];
    iVar6 = gpDataIndDuplicateFind();
    if (iVar6 == 0)
    {
      _gpTxQueueListClear();
    }
    else
    {
      memset(in_r0, 0, 0x22);
      in_r0->buf[0xe] = uVar1;
      in_r0->buf[0xd] = uVar4;
      in_r0->buf[0xf] = uVar2;
      memcpy(in_r0, auStack_38, 8);
      in_r0->buf[0x20] = uVar3;
      in_r0->buf[8] = (u8)uVar5;
      in_r0->buf[9] = (u8)((uint)uVar5 >> 8);
      in_r0->buf[10] = (u8)((uint)uVar5 >> 0x10);
      in_r0->buf[0xb] = (u8)((uint)uVar5 >> 0x18);
      in_r0->buf[0xc] = '\0';
      tl_zbTaskPost(gpSecRsp, in_r0);
    }
  }
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void gpSecRsp(void)

{
  u8 uVar1;
  byte bVar2;
  byte **ppbVar3;
  u8 uVar4;
  zb_buf_t *in_r0;
  u8 *puVar5;
  undefined1 *arg;
  uint uVar6;
  uint uVar7;
  byte *pbStack_2c;
  undefined4 uStack_28;

  puVar5 = g_gpDataIndSecReqTab + 0x11;
  uVar6 = 0;
  while ((uVar7 = uVar6 & 0xff,
          -1 < (int)((uint)(byte)g_gpDataIndSecReqTab[uVar6 * 0x13 + 0x12] << 0x19) ||
              (*puVar5 != in_r0->buf[0xd])))
  {
    uVar6 = uVar6 + 1;
    puVar5 = puVar5 + 0x13;
    if (uVar6 == 4)
    {
      zb_buf_free(in_r0);
      return;
    }
  }
  arg = g_gpDataIndSecReqTab + uVar7 * 0x13;
  ppbVar3 = *(byte ***)(g_gpDataIndSecReqTab + uVar7 * 0x13);
  *(u8 *)((int)ppbVar3 + 0x23) = in_r0->buf[0x21];
  pbStack_2c = (byte *)0x0;
  uStack_28 = 0;
  uVar4 = *(u8 *)((int)ppbVar3 + 0x21);
  if (uVar4 == '\0')
  {
    pbStack_2c = ppbVar3[1];
    uVar1 = in_r0->buf[0xc];
  }
  else
  {
    if (uVar4 == '\x02')
    {
      memcpy(&pbStack_2c, ppbVar3 + 4, 8);
    }
    uVar1 = in_r0->buf[0xc];
  }
  if (uVar1 == '\x01')
  {
    uVar4 = gpCcmStar(uVar4, (gpdId_t)(ulonglong)CONCAT14(*(undefined *)(ppbVar3 + 9), ((uint)(byte)g_gpDataIndSecReqTab[uVar7 * 0x13 + 0x12] << 0x1a) >> 0x1e), (u8)pbStack_2c, (u8)uStack_28,
                      (byte)(((uint)(byte)g_gpDataIndSecReqTab[uVar7 * 0x13 + 0x12] << 0x1c) >> 0x1f), (u32)ppbVar3[2], *(u8 *)((int)ppbVar3 + 0x26), *ppbVar3,
                      *(bool *)((int)ppbVar3 + 0x1a), *(bool *)((int)ppbVar3 + 0x1b), (u32)ppbVar3[3],
                      in_r0->buf + 0x10);
    if (uVar4 == '\0')
    {
      bVar2 = **ppbVar3;
      *(byte *)((int)ppbVar3 + 0x25) = bVar2;
      if ((bVar2 & 0xf0) == 0xf0)
        goto LAB_0002777e;
      if (*(char *)((int)ppbVar3 + 0x22) == '\0')
      {
        *(undefined *)(ppbVar3 + 7) = 1;
      }
      else
      {
        *(undefined *)(ppbVar3 + 7) = 0;
      }
      tl_zbTaskPost(gpDataIndSend, arg);
    }
    else
    {
      *(undefined *)(ppbVar3 + 7) = 3;
      tl_zbTaskPost(gpDataIndSend, arg);
    }
  }
  else
  {
    if (uVar1 == '\0')
    {
    LAB_0002777e:
      zb_buf_free(in_r0);
      gpDataIndSecReqEntryClear();
      return;
    }
    if (uVar1 == '\x02')
    {
      *(undefined *)(ppbVar3 + 7) = 4;
      tl_zbTaskPost(gpDataIndSend, arg);
    }
    else if (uVar1 == '\x03')
    {
      uVar4 = gpCcmStar(uVar4, (gpdId_t)(ulonglong)CONCAT14(*(undefined *)(ppbVar3 + 9), ((uint)(byte)g_gpDataIndSecReqTab[uVar7 * 0x13 + 0x12] << 0x1a) >> 0x1e), (u8)pbStack_2c, (u8)uStack_28,
                        (byte)(((uint)(byte)g_gpDataIndSecReqTab[uVar7 * 0x13 + 0x12] << 0x1c) >>
                               0x1f),
                        (u32)ppbVar3[2], *(u8 *)((int)ppbVar3 + 0x26), *ppbVar3,
                        *(bool *)((int)ppbVar3 + 0x1a), *(bool *)((int)ppbVar3 + 0x1b),
                        (u32)ppbVar3[3], in_r0->buf + 0x10);
      if (uVar4 == '\0')
      {
        bVar2 = **ppbVar3;
        *(byte *)((int)ppbVar3 + 0x25) = bVar2;
        if ((bVar2 & 0xf0) == 0xf0)
          goto LAB_0002777e;
        gpDataIndSecReqEntryClear();
      }
      else
      {
        *(undefined *)(ppbVar3 + 7) = 3;
        tl_zbTaskPost(gpDataIndSend, arg);
      }
    }
  }
  zb_buf_free(in_r0);
  if (*(int *)(g_gpDataIndSecReqTab + uVar7 * 0x13) == 0)
  {
    return;
  }
  if (*(char *)((int)ppbVar3 + 0x1b) != '\0')
  {
    gp_gpdfTransSchedule();
    return;
  }
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void gpStubCbInit(void)

{
  undefined4 in_r0;

  gpTxQueueInit();
  gpDataIndSecReqTabInit();
  gpStubCb = in_r0;
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void gpTxQueueCheck(void)

{
  bool bVar1;
  bool bVar2;
  bool bVar3;
  zb_buf_t *pzVar4;
  zb_buf_t *in_r0;
  int iVar5;
  uint n;
  uint uVar6;

  pzVar4 = (zb_buf_t *)gpTxQueue;
  uVar6 = (uint)in_r0->buf[0x12];
  n = 4;
  if (uVar6 != 0)
  {
    n = ((uVar6 - 2) + ~(uVar6 - 2) + (uint)(1 < uVar6)) * 8;
  }
  if (gpTxQueue._5_1_ == '\0')
  {
    bVar1 = false;
    bVar3 = false;
  }
  else
  {
    if ((((zb_buf_t *)gpTxQueue)->buf[0x12] == uVar6) &&
        (iVar5 = memcmp(((zb_buf_t *)gpTxQueue)->buf + 8, in_r0->buf + 8, n), iVar5 == 0))
    {
      if (in_r0->buf[0x11] == '\0')
      {
        if (((uVar6 != 2) || (-1 < (int)((uint)in_r0->buf[0x10] << 0x1a))) ||
            (in_r0->buf[0x13] == pzVar4->buf[0x13]))
        {
          zb_buf_free(in_r0);
          gpTxQueueListClear();
          gpDataCnfDeliver();
          goto LAB_00027f3a;
        }
      }
      else
      {
        bVar1 = true;
        if (((uVar6 == 0) || (bVar1 = false, -1 < (int)((uint)in_r0->buf[0x10] << 0x1a))) ||
            (in_r0->buf[0x13] == pzVar4->buf[0x13]))
        {
          gpTxQueueListReplace();
          gpDataCnfDeliver();
          if (!bVar1)
          {
            bVar1 = true;
            bVar3 = true;
            goto LAB_00027e64;
          }
        LAB_00027f3a:
          bVar1 = true;
          bVar3 = true;
          bVar2 = true;
          goto LAB_00027e66;
        }
      }
    }
    bVar1 = false;
    bVar3 = true;
  }
LAB_00027e64:
  bVar2 = false;
LAB_00027e66:
  if ((!bVar1) && (!bVar2))
  {
    if (bVar3)
    {
      zb_buf_free(in_r0);
    }
    else if (in_r0->buf[0x11] == '\0')
    {
      zb_buf_free(in_r0);
    }
    else if (gpTxQueue._5_1_ == '\0')
    {
      gpTxQueue._5_1_ = '\x01';
      gpTxQueue._0_4_ = in_r0;
      gpTxQueue._4_1_ = in_r0->buf[0x16];
    }
    gpDataCnfDeliver();
  }
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void gpTxQueueFree(void)

{
  gpTxQueueInit();
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void gpTxQueueInit(void)

{
  gpTxQueueListClear();
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void gpTxQueueListClear(void)

{
  zb_buf_t **in_r0;

  if (*in_r0 != (zb_buf_t *)0x0)
  {
    zb_buf_free(*in_r0);
  }
  *(undefined *)in_r0 = 0;
  *(undefined *)((int)in_r0 + 1) = 0;
  *(undefined *)((int)in_r0 + 2) = 0;
  *(undefined *)((int)in_r0 + 3) = 0;
  *(undefined *)(in_r0 + 1) = 0;
  *(undefined *)((int)in_r0 + 5) = 0;
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void gpTxQueueListReplace(void)

{
  zb_buf_t **in_r0;
  int in_r1;

  if (*(char *)((int)in_r0 + 5) != '\0')
  {
    if (*in_r0 != (zb_buf_t *)0x0)
    {
      zb_buf_free(*in_r0);
    }
    *(char *)in_r0 = (char)in_r1;
    *(char *)((int)in_r0 + 1) = (char)((uint)in_r1 >> 8);
    *(char *)((int)in_r0 + 2) = (char)((uint)in_r1 >> 0x10);
    *(char *)((int)in_r0 + 3) = (char)((uint)in_r1 >> 0x18);
    *(undefined *)(in_r0 + 1) = *(undefined *)(in_r1 + 0x16);
  }
  return;
}
void gpTxQueueMaintenceClear(void)

{
  if ((((gpTxQueue._5_1_ != '\0') && ((int)gpTxQueue != 0)) &&
       (*(char *)((int)gpTxQueue + 0x12) == '\0')) &&
      (*(int *)((int)gpTxQueue + 8) == 0))
  {
    gpTxQueueListClear();
  }
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void gp_gpdfCreat(void)

{
  int *in_r0;
  byte *pbVar1;
  byte in_r1;
  byte *pbVar2;
  byte in_r2;
  undefined4 in_r3;
  uint uVar3;
  uint uVar4;
  undefined4 in_stack_00000000;
  byte *in_stack_00000004;

  uVar3 = (uint)(byte)(*in_stack_00000004 + 2);
  *in_stack_00000004 = *in_stack_00000004 + 2;
  if ((in_r1 & 0x80) != 0)
  {
    uVar4 = uVar3 + 1;
    uVar3 = uVar4 & 0xff;
    *in_stack_00000004 = (byte)(uVar4 * 0x1000000 >> 0x18);
    if ((in_r2 & 0x18) == 0x18)
    {
      uVar4 = uVar3 + 8;
      uVar3 = uVar4 & 0xff;
      *in_stack_00000004 = (byte)(uVar4 * 0x1000000 >> 0x18);
    }
    else if ((in_r2 & 0x18) == 0x10)
    {
      uVar4 = uVar3 + 8;
      uVar3 = uVar4 & 0xff;
      *in_stack_00000004 = (byte)(uVar4 * 0x1000000 >> 0x18);
    }
  }
  if ((in_r1 & 3) == 0)
  {
    if (*(char *)((int)in_r0 + 0x12) == '\x02')
    {
      uVar4 = uVar3 + 1;
      uVar3 = uVar4 & 0xff;
      *in_stack_00000004 = (byte)(uVar4 * 0x1000000 >> 0x18);
    }
    else
    {
      uVar4 = uVar3 + 4;
      uVar3 = uVar4 & 0xff;
      *in_stack_00000004 = (byte)(uVar4 * 0x1000000 >> 0x18);
    }
  }
  pbVar1 = (byte *)(*in_r0 - uVar3);
  *in_stack_00000004 = (char)uVar3 + *(char *)((int)in_r0 + 0x15);
  *pbVar1 = in_r1;
  pbVar2 = pbVar1 + 1;
  if ((in_r1 & 0x80) != 0)
  {
    pbVar1[1] = in_r2;
    pbVar2 = pbVar1 + 2;
  }
  if ((in_r1 & 3) == 0)
  {
    if (*(char *)((int)in_r0 + 0x12) == '\x02')
    {
      *pbVar2 = *(byte *)((int)in_r0 + 0x13);
      pbVar2 = pbVar2 + 1;
    }
    else
    {
      *pbVar2 = *(byte *)(in_r0 + 2);
      pbVar2[1] = *(byte *)((int)in_r0 + 9);
      pbVar2[2] = *(byte *)((int)in_r0 + 10);
      pbVar2[3] = *(byte *)((int)in_r0 + 0xb);
      pbVar2 = pbVar2 + 4;
    }
  }
  if (((in_r1 & 0x80) != 0) && (((in_r2 & 0x18) == 0x18 || ((in_r2 & 0x18) == 0x10))))
  {
    *pbVar2 = (byte)in_r3;
    pbVar2[1] = (byte)((uint)in_r3 >> 8);
    pbVar2[2] = (byte)((uint)in_r3 >> 0x10);
    pbVar2[3] = (byte)((uint)in_r3 >> 0x18);
    pbVar2 = pbVar2 + 4;
  }
  *pbVar2 = *(byte *)(in_r0 + 5);
  pbVar2 = pbVar2 + 1;
  if (*(byte *)((int)in_r0 + 0x15) != 0)
  {
    pbVar2 = pbVar2 + *(byte *)((int)in_r0 + 0x15);
  }
  if (((in_r1 & 0x80) != 0) && (((in_r2 & 0x18) == 0x18 || ((in_r2 & 0x18) == 0x10))))
  {
    *pbVar2 = (byte)in_stack_00000000;
    pbVar2[1] = (byte)((uint)in_stack_00000000 >> 8);
    pbVar2[2] = (byte)((uint)in_stack_00000000 >> 0x10);
    pbVar2[3] = (byte)((uint)in_stack_00000000 >> 0x18);
  }
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void gp_gpdfGenerate(void)

{
  undefined uVar1;
  byte bVar2;
  void *pvVar3;
  undefined *arg;
  u16 uVar4;
  void **in_r0;
  undefined4 uVar5;
  char in_r1;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined uStack_2d;
  byte local_2c;
  undefined local_28;

  uStack_38 = 0;
  uStack_34 = 0;
  local_28 = 0;
  local_2c = 0;
  pvVar3 = *in_r0;
  memcpy(&uStack_38, (void *)((int)pvVar3 + 8), 8);
  uVar1 = *(undefined *)((int)pvVar3 + 0x16);
  bVar2 = *(byte *)((int)pvVar3 + 0x10);
  if (in_r1 == '\x01')
  {
    FUN_00027628();
    return;
  }
  local_28 = gpNwkHdrFrameCtrlBuild();
  uStack_2d = 0;
  uVar5 = gp_gpdfCreat();
  arg = (undefined *)*in_r0;
  *arg = (char)uVar5;
  arg[1] = (char)((uint)uVar5 >> 8);
  arg[2] = (char)((uint)uVar5 >> 0x10);
  arg[3] = (char)((uint)uVar5 >> 0x18);
  arg[0x1a] = uStack_2d;
  uVar4 = g_zbInfo.nwkNib.panId;
  arg[4] = (char)g_zbInfo.nwkNib.panId;
  arg[5] = (char)(uVar4 >> 8);
  arg[6] = 0xfe;
  arg[7] = 0xfe;
  arg[0x18] = 0;
  if ((local_2c & 7) == 0)
  {
    arg[0x19] = 2;
    arg[0x10] = 0xfe;
    arg[0x11] = 0xfe;
  }
  else if ((local_2c & 7) == 2)
  {
    arg[0x19] = 3;
    memcpy(arg + 0x10, &uStack_38, 8);
  }
  arg[0x1b] = uVar1;
  arg[0x1c] = arg[0x1c] & 0xfe | (byte)(((uint)bVar2 << 0x1e) >> 0x1f);
  arg[0x1c] = arg[0x1c] & 0xfd | (byte)((((uint)bVar2 << 0x1d) >> 0x1f) << 1);
  *(undefined *)((int)*in_r0 + 0xc1) = uVar1;
  ev_timer_taskPost(cGp_dataReq, arg, 0x14);
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void gp_gpdfTransSchedule(void)

{
  int iVar1;
  int iVar2;
  char in_r1;
  uint n;
  char in_stack_00000000;
  undefined local_20[8];

  iVar1 = (int)gpTxQueue;
  n = 4;
  if (in_r1 != '\0')
  {
    if (in_r1 != '\x02')
    {
      return;
    }
    n = 8;
  }
  if ((((gpTxQueue._5_1_ != '\0') && (*(char *)((int)gpTxQueue + 0x12) == in_r1)) &&
       (iVar2 = memcmp((void *)((int)gpTxQueue + 8), local_20, n), iVar2 == 0)) &&
      (((in_r1 != '\x02' || (in_stack_00000000 == -1)) ||
        (*(char *)(iVar1 + 0x13) == in_stack_00000000))))
  {
    *(byte *)(iVar1 + 0x10) = *(byte *)(iVar1 + 0x10) & 0xfd;
    *(byte *)(iVar1 + 0x10) = *(byte *)(iVar1 + 0x10) & 0xfb;
    gp_gpdfGenerate();
    gpTxQueue._0_4_ = 0;
    gpTxQueue._4_1_ = 0;
    gpTxQueue._5_1_ = '\0';
  }
  return;
}
