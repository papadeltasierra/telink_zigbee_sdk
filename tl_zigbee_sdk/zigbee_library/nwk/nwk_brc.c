// WARNING: Unknown calling convention -- yet parameter storage is locked
undefined4 nwkBrcAllRelayed(void)

{
  byte bVar1;
  u16 uVar2;
  int *in_r0;
  tl_zb_normal_neighbor_entry_t *ptVar3;
  u16 *puVar4;
  byte bVar5;
  byte idx;

  bVar1 = tl_zbNeighborTableNumGet();
  if (bVar1 != 0)
  {
    idx = 0;
    do
    {
      while (true)
      {
        ptVar3 = tl_zbNeighborEntryGetFromIdx(idx);
        if (*(short *)(*in_r0 + 6) != -1)
          break;
        if ((ptVar3->field_0x1e & 0xe) != 4)
        {
        LAB_000169ba:
          uVar2 = tl_zbshortAddrByIdx(ptVar3->addrmapIdx);
          puVar4 = (u16 *)in_r0[2];
          if ((puVar4 == (u16 *)0x0) || (*(byte *)(in_r0 + 4) == 0))
          {
            return 0;
          }
          if (*puVar4 != uVar2)
          {
            bVar5 = 0;
            do
            {
              puVar4 = puVar4 + 1;
              bVar5 = bVar5 + 1;
              if (*(byte *)(in_r0 + 4) <= bVar5)
              {
                return 0;
              }
            } while (uVar2 != *puVar4);
          }
        }
      LAB_00016980:
        idx = idx + 1;
        if (bVar1 <= idx)
        {
          return 1;
        }
      }
      if (1 < (ushort)(*(short *)(*in_r0 + 6) + 4U))
        goto LAB_00016980;
      if (((ptVar3->field_0x1e & 0xe) == 0) || ((ptVar3->field_0x1e & 0xe) == 2))
        goto LAB_000169ba;
      idx = idx + 1;
    } while (idx < bVar1);
  }
  return 1;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
uint nwkBrcCheckDevMatch(void)

{
  short in_r0;
  uint uVar1;

  if (in_r0 == -3)
  {
    uVar1 = (uint)(g_zbInfo.macPib.rxOnWhenIdle != '\0');
  }
  else
  {
    uVar1 = 1;
    if ((in_r0 != -1) && (uVar1 = 0, in_r0 == -4))
    {
      uVar1 = ((uint)(byte)g_zbInfo.nwkNib.capabilityInfo << 0x1e) >> 0x1f;
    }
  }
  return uVar1;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
// WARNING: Unknown calling convention -- yet parameter storage is locked
// WARNING: Unknown calling convention -- yet parameter storage is locked
void nwkBrcMsgAddSender(void)

{
  byte bVar1;
  int in_r0;
  tl_zb_normal_neighbor_entry_t *ptVar2;
  uint uVar3;
  u16 in_r1;
  u16 *puVar4;
  uint uVar5;
  u16 *puVar6;

  ptVar2 = nwk_neTblGetByShortAddr(in_r1);
  if (((ptVar2 != (tl_zb_normal_neighbor_entry_t *)0x0) && ((ptVar2->field_0x1e & 0xf) != 4)) &&
      (puVar6 = (u16 *)((uint) * (byte *)(in_r0 + 0xb) * 0x1000000 | (uint) * (uint3 *)(in_r0 + 8)),
       puVar6 != (u16 *)0x0))
  {
    bVar1 = *(byte *)(in_r0 + 0x10);
    uVar3 = (uint)bVar1;
    if (uVar3 == 0)
    {
    LAB_00016940:
      if (uVar3 < TL_ZB_NEIGHBOR_TABLE_SIZE)
      {
        puVar6[uVar3] = in_r1;
        *(byte *)(in_r0 + 0x10) = bVar1 + 1;
      }
    }
    else if (*puVar6 != in_r1)
    {
      uVar5 = 0;
      puVar4 = puVar6;
      do
      {
        puVar4 = puVar4 + 1;
        uVar5 = uVar5 + 1 & 0xff;
        if (uVar3 <= uVar5)
          goto LAB_00016940;
      } while (*puVar4 != in_r1);
    }
  }
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
undefined4 nwkBrcMsgAllDevicesCb(void)

{
  u16 uVar1;
  int *in_r0;
  int iVar2;
  undefined auStack_3c[32];
  undefined auStack_1c[4];

  if (((in_r0 == (int *)0x0) || (*in_r0 == 0)) ||
      (pNebEntry_8462 = tl_zbNeighborTabSearchForChildEndDev(), pNebEntry_8462 == 0))
  {
    return 0xfffffffe;
  }
  uVar1 = tl_zbshortAddrByIdx(*(u16 *)(pNebEntry_8462 + 0x16));
  if (uVar1 == *(u16 *)(in_r0 + 3))
  {
    return 0;
  }
  if ((*(byte *)(pNebEntry_8462 + 0x1e) & 1) != 0)
  {
    return 0;
  }
  iVar2 = nwkTxDataCachePacketCopy();
  if (iVar2 == 0)
  {
    return 0;
  }
  memcpy(auStack_1c, (void *)(iVar2 + 1), 4);
  memcpy(auStack_3c, (void *)(iVar2 + 5), 0x20);
  tl_zbshortAddrByIdx(*(u16 *)(pNebEntry_8462 + 0x16));
  nwk_tx();
  return 0;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void nwkBrcMsgAllEndDevStart(void)

{
  void *in_r0;
  int iVar1;
  undefined4 uVar2;
  u32 t_ms;

  iVar1 = tl_zbNeighborTabSearchForChildEndDev();
  if (iVar1 != 0)
  {
    uVar2 = FUN_0000162c(g_zbInfo.nwkNib.passiveAckTimeout, TL_ZB_NEIGHBOR_TABLE_SIZE);
    t_ms = FUN_0000162c(uVar2, 1000);
    ev_timer_taskPost(nwkBrcMsgAllDevicesCb, in_r0, t_ms);
  }
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
undefined4 nwkBrcMsgPassiveAckTimeoutCb(void)

{
  int **in_r0;
  int iVar1;
  void *arg;
  byte bVar2;

  if ((*(char *)((int)in_r0 + 0x13) != '\0') && (*in_r0 != (int *)0x0))
  {
    bVar2 = *(char *)((int)in_r0 + 0xf) + 1;
    *(byte *)((int)in_r0 + 0xf) = bVar2;
    if ((bVar2 < g_zbInfo.nwkNib.maxBroadcastRetries) &&
        (((iVar1 = nwkBrcAllRelayed(), iVar1 == 0 && ((*(byte *)((int)*in_r0 + 0xb) & 0x80) != 0)) &&
          (**in_r0 != 0))))
    {
      arg = (void *)nwkTxDataCachePacketCopy();
      if (arg == (void *)0x0)
      {
        return 0;
      }
      tl_zbTaskPost(nwkMsgSendCb, arg);
      *(undefined *)(in_r0 + 1) = 0;
      *(undefined *)((int)in_r0 + 5) = 0;
      *(undefined *)((int)in_r0 + 6) = 0;
      *(undefined *)((int)in_r0 + 7) = 0;
      return 0xfffffffe;
    }
    if (in_r0[2] != (int *)0x0)
    {
      ev_buf_free((u8 *)in_r0[2]);
      *(undefined *)(in_r0 + 2) = 0;
      *(undefined *)((int)in_r0 + 9) = 0;
      *(undefined *)((int)in_r0 + 10) = 0;
      *(undefined *)((int)in_r0 + 0xb) = 0;
    }
    nwkTxDataPendTabEntryClear();
    *(undefined *)in_r0 = 0;
    *(undefined *)((int)in_r0 + 1) = 0;
    *(undefined *)((int)in_r0 + 2) = 0;
    *(undefined *)((int)in_r0 + 3) = 0;
  }
  *(undefined *)(in_r0 + 1) = 0;
  *(undefined *)((int)in_r0 + 5) = 0;
  *(undefined *)((int)in_r0 + 6) = 0;
  *(undefined *)((int)in_r0 + 7) = 0;
  return 0xfffffffe;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void nwkBrcMsgPassiveAckTimeoutStart(void)

{
  void *in_r0;
  u32 t_ms;
  ev_timer_event_t *peVar1;

  if (((in_r0 != (void *)0x0) && (*(char *)((int)in_r0 + 0x13) != '\0')) &&
      (*(int *)((int)in_r0 + 4) == 0))
  {
    t_ms = FUN_0000162c(g_zbInfo.nwkNib.passiveAckTimeout, 1000);
    peVar1 = ev_timer_taskPost(nwkBrcMsgPassiveAckTimeoutCb, in_r0, t_ms);
    *(char *)((int)in_r0 + 4) = (char)peVar1;
    *(char *)((int)in_r0 + 5) = (char)((uint)peVar1 >> 8);
    *(char *)((int)in_r0 + 6) = (char)((uint)peVar1 >> 0x10);
    *(char *)((int)in_r0 + 7) = (char)((uint)peVar1 >> 0x18);
  }
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void nwkBrcPeriodic(void)

{
  nwk_brcTransRecordEntry_t *pnVar1;
  u8 uVar2;
  byte idx;

  if ((g_brcTransTabCnt != '\0') && (NWK_BRC_TRANSTBL_SIZE != '\0'))
  {
    idx = 0;
    do
    {
      while (pnVar1 = brcTransRecordEntryGet(idx), pnVar1->used != '\0')
      {
        if ((pnVar1->expirationTime == '\0') ||
            (uVar2 = pnVar1->expirationTime + 0xff, pnVar1->expirationTime = uVar2, uVar2 == '\0'))
        {
          nwkBrcTransTabEntryClear();
          break;
        }
        idx = idx + 1;
        if (NWK_BRC_TRANSTBL_SIZE <= idx)
        {
          return;
        }
      }
      idx = idx + 1;
    } while (idx < NWK_BRC_TRANSTBL_SIZE);
  }
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
undefined4 nwkBrcTimerStart(void)

{
  u8 uVar1;
  void *in_r0;
  undefined *out;
  u32 uVar2;
  int iVar3;
  void *in_r1;
  int in_r2;
  undefined in_r3;
  undefined4 uVar4;
  undefined *puVar5;

  uVar1 = ev_timer_enough();
  uVar4 = 0x14;
  if (uVar1 != '\0')
  {
    out = (undefined *)c1();
    uVar4 = 0xd3;
    if (out != (undefined *)0x0)
    {
      memcpy(out, in_r0, 0xc3);
      *out = in_r3;
      puVar5 = out + (in_r2 - (int)in_r0 & 0xff);
      out[1] = (char)puVar5;
      out[2] = (char)((uint)puVar5 >> 8);
      out[3] = (char)((uint)puVar5 >> 0x10);
      out[4] = (char)((uint)puVar5 >> 0x18);
      memcpy(out + 5, in_r1, 0x20);
      uVar2 = drv_u32Rand();
      iVar3 = FUN_00001628(uVar2 & 0xffff, g_brcTransJitter);
      ev_timer_taskPost(nwkMsgSendCbDelay, out, iVar3 + 1);
      uVar4 = 0;
    }
  }
  return uVar4;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void nwkBrcTransJitterSet(void)

{
  undefined4 in_r0;

  g_brcTransJitter = in_r0;
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void nwkBrcTransTabEntryClear(void)

{
  int *in_r0;

  if (((in_r0 != (int *)0x0) && (*(char *)((int)in_r0 + 0x13) != '\0')) && (*in_r0 == 0))
  {
    nwkBrcTransTabEntryRst();
    g_brcTransTabCnt = g_brcTransTabCnt + -1;
  }
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void nwkBrcTransTabEntryRst(void)

{
  void *in_r0;

  if (*(u8 **)((int)in_r0 + 8) != (u8 *)0x0)
  {
    ev_buf_free(*(u8 **)((int)in_r0 + 8));
  }
  memset(in_r0, 0, 0x14);
  *(undefined *)((int)in_r0 + 0xc) = 0xfd;
  *(undefined *)((int)in_r0 + 0xd) = 0xfe;
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void nwkBrcTransTabInit(void)

{
  byte idx;

  if (NWK_BRC_TRANSTBL_SIZE != '\0')
  {
    idx = 0;
    do
    {
      brcTransRecordEntryGet(idx);
      nwkBrcTransTabEntryRst();
      idx = idx + 1;
    } while (idx < NWK_BRC_TRANSTBL_SIZE);
  }
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void nwkMsgSendCb(void)

{
  int in_r0;
  undefined auStack_34[32];
  undefined auStack_14[8];

  memcpy(auStack_14, (void *)(in_r0 + 1), 4);
  memcpy(auStack_34, (void *)(in_r0 + 5), 0x20);
  nwk_fwdPacket();
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
undefined4 nwkMsgSendCbDelay(void)

{
  nwkMsgSendCb();
  return 0xfffffffe;
}
