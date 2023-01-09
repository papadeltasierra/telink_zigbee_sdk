// WARNING: Unknown calling convention -- yet parameter storage is locked
// WARNING: Unknown calling convention -- yet parameter storage is locked
// WARNING: Unknown calling convention -- yet parameter storage is locked
// WARNING: Unknown calling convention -- yet parameter storage is locked
// WARNING: Unknown calling convention -- yet parameter storage is locked
int nwkTxDataPendTabEntryAdd(void)

{
  undefined *in_r0;
  int iVar1;
  zb_buf_t *buf;
  void *in_r1;
  undefined4 in_r2;
  undefined in_r3;

  iVar1 = nwkTxDataPendTabEntryFind();
  if (iVar1 == 0)
  {
    *in_r0 = in_r3;
    in_r0[1] = (char)in_r2;
    in_r0[2] = (char)((uint)in_r2 >> 8);
    in_r0[3] = (char)((uint)in_r2 >> 0x10);
    in_r0[4] = (char)((uint)in_r2 >> 0x18);
    memcpy(in_r0 + 5, in_r1, 0x20);
    buf = (zb_buf_t *)nwkTxDataCachePacketCopy();
    if (buf != (zb_buf_t *)0x0)
    {
      iVar1 = nwkTxDataPendTabEntryCreate();
      if (iVar1 == 0)
      {
        zb_buf_free(buf);
      }
    }
  }
  return iVar1;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void nwkTxDataPendTabEntryClear(void)

{
  zb_buf_t *buf;
  zb_buf_t **in_r0;

  if ((in_r0 != (zb_buf_t **)0x0) && ((*(byte *)((int)in_r0 + 0xb) & 0x80) != 0))
  {
    buf = *in_r0;
    nwkTxDataPendTabEntryRst();
    if (buf != (zb_buf_t *)0x0)
    {
      zb_buf_free(buf);
    }
    g_txDataPendTabCnt = g_txDataPendTabCnt + -1;
  }
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void nwkTxDataPendTabEntryRst(void)

{
  undefined *in_r0;

  *in_r0 = 0;
  in_r0[1] = 0;
  in_r0[2] = 0;
  in_r0[3] = 0;
  in_r0[4] = 0;
  in_r0[5] = 0;
  in_r0[6] = 0;
  in_r0[7] = 0;
  in_r0[8] = 0;
  in_r0[9] = 0;
  in_r0[10] = 0;
  in_r0[0xb] = 0;
  in_r0[6] = 0xfd;
  in_r0[7] = 0xfe;
  in_r0[4] = 0xfd;
  in_r0[5] = 0xfe;
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void nwkTxDataPendTabInit(void)

{
  int iVar1;

  iVar1 = 0;
  do
  {
    nwkTxDataPendTabEntryRst();
    iVar1 = iVar1 + 1;
  } while (iVar1 != 0x10);
  return;
}
