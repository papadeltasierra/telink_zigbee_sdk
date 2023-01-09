// WARNING: Unknown calling convention -- yet parameter storage is locked
undefined4 macDataPending(void)

{
  u8 uVar1;
  undefined4 in_r0;
  int iVar2;
  u8 *dest;
  undefined4 uVar3;
  undefined local_24[12];

  iVar2 = listLength((list_t)&macPendingQueue_list);
  uVar3 = 0xf1;
  if ((iVar2 < (int)(uint)ZB_MAC_PENDING_TRANS_QUEUE_SIZE) &&
      (dest = ev_buf_allocate(0x15), dest != (u8 *)0x0))
  {
    memset(dest, 0, 0x15);
    listAdd((list_t)&macPendingQueue_list, dest);
    dest[4] = (u8)in_r0;
    dest[5] = (u8)((uint)in_r0 >> 8);
    dest[6] = (u8)((uint)in_r0 >> 0x10);
    dest[7] = (u8)((uint)in_r0 >> 0x18);
    memcpy(dest + 8, local_24, 9);
    uVar1 = FUN_00001624((uint)g_zbInfo.macPib.transactionPersistenceTime * 0x3c00, 1000000);
    dest[0x11] = uVar1;
    dest[0x12] = ZB_MAC_EXT_EXPEIRY_CNT;
    dest[0x13] = '\x01';
    uVar3 = 0;
  }
  return uVar3;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void macDataPendingListManage(void)

{
  void *in_r0;
  undefined in_r1;
  undefined uVar1;

  uVar1 = in_r1;
  if ((in_r0 != (void *)0x0) && (uVar1 = 0xf0, *(char *)((int)in_r0 + 0x13) != '\x04'))
  {
    uVar1 = in_r1;
  }
  *(undefined *)((int)in_r0 + 0x14) = uVar1;
  tl_zbTaskPost(macDataPendingListProc, in_r0);
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void macDataPendingListProc(void)

{
  u8 uVar1;
  u8 *in_r0;

  uVar1 = in_r0[0x14];
  if (((uVar1 == ' ') || (uVar1 == '\0')) || (uVar1 == '\x04'))
  {
    tl_zbMaxTxConfirmCb(*(undefined4 *)(in_r0 + 4));
    listRemove((list_t)&macPendingQueue_list, in_r0);
    ev_buf_free(in_r0);
  }
  else
  {
    in_r0[0x13] = '\x01';
  }
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void macIndirPeriodic(void)

{
  int iVar1;
  undefined4 *pBuf;

  iVar1 = listLength((list_t)&macPendingQueue_list);
  if (iVar1 != 0)
  {
    for (pBuf = (undefined4 *)listHead((list_t)&macPendingQueue_list); pBuf != (undefined4 *)0x0;
         pBuf = (undefined4 *)*pBuf)
    {
      if (*(char *)((int)pBuf + 0x11) == '\0')
      {
        if (*(char *)((int)pBuf + 0x12) == '\0')
        {
          if (1 < (byte)(*(char *)((int)pBuf + 0x13) - 3U))
          {
            if (pBuf[1] != 0)
            {
              tl_zbMaxTxConfirmCb(pBuf[1], 0xf0);
            }
            listRemove((list_t)&macPendingQueue_list, pBuf);
            ev_buf_free((u8 *)pBuf);
            return;
          }
          *(undefined *)((int)pBuf + 0x13) = 4;
          return;
        }
        *(char *)((int)pBuf + 0x12) = *(char *)((int)pBuf + 0x12) + -1;
      }
      else
      {
        *(char *)((int)pBuf + 0x11) = *(char *)((int)pBuf + 0x11) + -1;
      }
    }
  }
  return;
}
void tl_zbMacDataRequestStatusCheck(zb_buf_t *param_1, uint param_2)

{
  u8 uVar1;
  int iVar2;

  param_2 = param_2 & 0xff;
  iVar2 = (param_2 - 0x20) + ~(param_2 - 0x20) + (uint)(0x1f < param_2);
  if ((iVar2 == 0) && (param_2 != 0))
  {
    tl_zbMacMlmeDataRequestConfirm();
  }
  else
  {
    uVar1 = (param_1->hdr).handle;
    if (uVar1 == 0xe8)
    {
      if (iVar2 == 0)
      {
        param_1->buf[0] = 0xeb;
        tl_zbPrimitivePost('\x01', '^', param_1);
      }
      else
      {
        param_1->buf[0] = ' ';
        tl_zbPrimitivePost('\x01', '^', param_1);
        tl_zbMacIndirectDataTimerStart(tl_zbWaitForPendingDataTimeout, 0);
      }
    }
    else if (uVar1 == 0xe9)
    {
      zb_buf_free(param_1);
    }
  }
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void tl_zbMacIndirectDataTimerCancel(void)

{
  if (g_zbMacCtx.indirectData.timer != (ev_timer_event_t *)0x0)
  {
    ev_timer_taskCancel(&g_zbMacCtx.indirectData.timer);
  }
  tl_zbSwitchOffRx();
  return;
}
void tl_zbMacIndirectDataTimerStart(ev_timer_callback_t param_1, void *param_2)

{
  u32 t_ms;

  if (g_zbMacCtx.indirectData.timer != (ev_timer_event_t *)0x0)
  {
    ev_timer_taskCancel(&g_zbMacCtx.indirectData.timer);
  }
  t_ms = FUN_00001624((uint)g_zbInfo.macPib.frameTotalWaitTime << 4, 1000);
  g_zbMacCtx.indirectData.timer = ev_timer_taskPost(param_1, param_2, t_ms);
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void tl_zbMacMlmeDataRequestCb(void)

{
  byte **ppbVar1;
  byte *pbVar2;
  char cVar3;
  undefined *in_r0;
  int iVar4;
  undefined4 *puVar5;
  undefined *m1;
  undefined auStack_24[12];

  m1 = in_r0 + 10;
  cVar3 = tl_zbMacPendingDataSearch();
  iVar4 = listLength((list_t)&macPendingQueue_list);
  if (iVar4 != 0)
  {
    for (puVar5 = (undefined4 *)listHead((list_t)&macPendingQueue_list); puVar5 != (undefined4 *)0x0; puVar5 = (undefined4 *)*puVar5)
    {
      ppbVar1 = (byte **)puVar5[1];
      if (((ppbVar1 != (byte **)0x0) && (*(char *)((int)puVar5 + 0x13) == '\x02')) &&
          (*(char *)(puVar5 + 4) == in_r0[0x12]))
      {
        if (*(char *)(puVar5 + 4) == '\x03')
        {
          iVar4 = memcmp(m1, puVar5 + 2, 8);
        }
        else
        {
          iVar4 = memcmp(m1, puVar5 + 2, 2);
        }
        if (iVar4 == 0)
        {
          pbVar2 = *ppbVar1;
          if ('\x01' < cVar3)
          {
            *pbVar2 = *pbVar2 | 0x10;
          }
          iVar4 = tl_zbMacTx();
          if (iVar4 == 0)
          {
            *(undefined *)((int)puVar5 + 0x13) = 3;
          }
          else
          {
            *(undefined *)((int)puVar5 + 0x13) = 1;
          }
          break;
        }
      }
    }
  }
  memcpy(auStack_24, m1, 9);
  *in_r0 = in_r0[0x12];
  memcpy(in_r0 + 1, auStack_24, 8);
  tl_zbPrimitivePost('\x01', 'c', in_r0);
  return;
}
int tl_zbMacMlmeDataRequestCmdSend(byte *param_1, zb_buf_t *param_2, u8 param_3)

{
  u8 uVar1;
  undefined *puVar2;
  int iVar3;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  undefined2 local_20;

  uStack_30 = 0;
  uStack_2c = 0;
  uStack_28 = 0;
  uStack_24 = 0;
  local_20 = 0;
  memcpy(&uStack_30, param_1 + 10, 8);
  memcpy((void *)((int)&uStack_28 + 2), param_1 + 2, 8);
  uVar1 = tl_zbMacHdrSize((ushort)param_1[1] << 10 | (ushort)*param_1 << 0xe | 99);
  tl_bufInitalloc(param_2, uVar1 + '\x01');
  puVar2 = (undefined *)tl_zbMacHdrBuilder();
  *puVar2 = 4;
  (param_2->hdr).handle = param_3;
  iVar3 = tl_zbMacTx();
  if (iVar3 == 0)
  {
    if (param_3 == 0xe9)
    {
      g_zbMacCtx.status = '\x05';
    }
  }
  else
  {
    tl_zbMacMlmeDataRequestConfirm();
  }
  return iVar3;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void tl_zbMacMlmeDataRequestConfirm(void)

{
  zb_buf_t *in_r0;
  u8 in_r1;

  if ((in_r0->hdr).handle == 0xe9)
  {
    zb_buf_free(in_r0);
  }
  else
  {
    in_r0->buf[0] = in_r1;
    tl_zbPrimitivePost('\x01', '^', in_r0);
  }
  return;
}
u8 tl_zbMacPendingDataCheck(u8 addrMode, u8 *addr, u8 send)

{
  int iVar1;
  undefined4 *puVar2;

  iVar1 = listLength((list_t)&macPendingQueue_list);
  if (iVar1 != 0)
  {
    for (puVar2 = (undefined4 *)listHead((list_t)&macPendingQueue_list); puVar2 != (undefined4 *)0x0; puVar2 = (undefined4 *)*puVar2)
    {
      if ((puVar2[1] != 0) && (*(u8 *)(puVar2 + 4) == addrMode))
      {
        if (addrMode == '\x03')
        {
          iVar1 = 0;
          while (addr[iVar1] == *(u8 *)((int)puVar2 + iVar1 + 8))
          {
            iVar1 = iVar1 + 1;
            if (iVar1 == 8)
              goto LAB_000010f2;
          }
        }
        else if (*(short *)(puVar2 + 2) == (ushort)((ushort)addr[1] * 0x100 + (ushort)*addr))
        {
        LAB_000010f2:
          if (send == '\0')
          {
            return 0xed;
          }
          if (1 < (byte)(*(char *)((int)puVar2 + 0x13) - 1U))
          {
            return 0xed;
          }
          *(undefined *)((int)puVar2 + 0x13) = 2;
          return '\0';
        }
      }
    }
  }
  return 0xed;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
int tl_zbMacPendingDataSearch(void)

{
  char in_r0;
  int iVar1;
  undefined4 *puVar2;
  void *in_r1;
  char cVar3;

  iVar1 = listLength((list_t)&macPendingQueue_list);
  cVar3 = '\0';
  if (iVar1 != 0)
  {
    for (puVar2 = (undefined4 *)listHead((list_t)&macPendingQueue_list); puVar2 != (undefined4 *)0x0; puVar2 = (undefined4 *)*puVar2)
    {
      if ((puVar2[1] != 0) && (*(char *)(puVar2 + 4) == in_r0))
      {
        if (in_r0 == '\x03')
        {
          iVar1 = memcmp(in_r1, puVar2 + 2, 8);
        }
        else
        {
          iVar1 = memcmp(in_r1, puVar2 + 2, 2);
        }
        if (iVar1 == 0)
        {
          cVar3 = cVar3 + '\x01';
        }
      }
    }
  }
  return (int)cVar3;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void tl_zbSwitchOffRx(void)

{
  if (g_zbInfo.macPib.rxOnWhenIdle == '\0')
  {
    rf_setTrxState('\x03');
  }
  tl_zbTaskPost(mac_trigger_tx, (void *)0x0);
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
undefined4 tl_zbWaitForPendingDataTimeout(void)

{
  tl_zbSwitchOffRx();
  g_zbMacCtx.indirectData.timer._0_1_ = 0;
  g_zbMacCtx.indirectData.timer._1_1_ = 0;
  g_zbMacCtx.indirectData.timer._2_1_ = 0;
  g_zbMacCtx.indirectData.timer._3_1_ = 0;
  return 0xfffffffe;
}
