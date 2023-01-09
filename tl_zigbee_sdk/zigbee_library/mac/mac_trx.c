#include "includes/zb_buffer.h"

// WARNING: Unknown calling convention -- yet parameter storage is locked
void free_tx_buff(void)

{
  u32 en;

  en = drv_disable_irq();
  tx_fifo_rptr = tx_fifo_rptr + '\x01';
  drv_restore_irq(en);
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
int get_next_data(void)

{
  int iVar1;

  iVar1 = 0;
  if ((uint)tx_fifo_wptr != (uint)tx_fifo_rptr)
  {
    iVar1 = g_pTxQueue + ((uint)tx_fifo_rptr & MAC_TX_QUEUE_SIZE - 1) * 0x10;
  }
  return iVar1;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
undefined4 mac_ackWaitingTimerCb(void)

{
  if (g_macTimerEvt[8] != '\0')
  {
    tl_zbTaskPost(mac_trxTask, &DAT_00000006);
  }
  return 0xfffffffe;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
undefined4 mac_csmaStart(void)

{
  u32 uVar1;
  int iVar2;
  u32 uVar3;

  uVar1 = drv_disable_irq();
  iVar2 = rf_performCCA();
  if ((iVar2 == 4) || (g_zbInfo.macPib.maxCsmaBackoffs == '\0'))
  {
    if ((rf_busyFlag & 4) != 0)
    {
      rf_busyFlag = rf_busyFlag & 0xfb;
    }
    mac_trx_vars[4] = 2;
    rf_busyFlag = rf_busyFlag | 2;
    rf802154_tx();
    drv_restore_irq(uVar1);
    uVar1 = drv_disable_irq();
    if (g_macTimerEvt[8] == '\0')
    {
      g_macTimerEvt._0_4_ = mac_waitTxIrqCb;
      uVar3 = mac_currentTickGet();
      g_macTimerEvt._4_4_ = uVar3 + sysTimerPerUs * 10000;
      g_macTimerEvt[8] = '\x01';
    }
    else
    {
      sys_exceptionPost(0x6a, '#');
    }
    drv_restore_irq(uVar1);
  }
  else
  {
    drv_restore_irq(uVar1);
    tl_zbTaskPost(mac_trxTask, &_d);
  }
  return 0xfffffffe;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void mac_resetTx_info(void)

{
  if (mac_trx_vars[10] == '\0')
  {
    free_tx_buff();
  }
  g_macTimerEvt[8] = 0;
  mac_trx_vars._0_4_ = 0;
  mac_trx_vars._4_4_ = 0;
  mac_trx_vars._8_4_ = 0;
  return;
}

// WARNING: Unknown calling convention -- yet parameter storage is locked
void mac_sendTxCnf(void)

{
  char cVar1;
  bool bVar2;
  u8 *in_r0;

  mac_resetTx_info();
  cVar1 = *(char *)(*(int *)(in_r0 + 4) + 0xc1);
  bVar2 = false;
  if ((in_r0[2] == 0) && ((*in_r0 & 0xf0) != 0))
  {
    in_r0[2] = 0x20;
    bVar2 = true;
  }
  if (((g_zbInfo.macPib.rxOnWhenIdle == '\0') && (g_zbMacCtx.status == '\0')) &&
      ((!bVar2 || (1 < (u8)(cVar1 + 0x18U)))))
  {
    rf_setTrxState('\x03');
  }
  if (*(int *)(in_r0 + 0xc) == 0)
  {
    tl_zbMaxTxConfirmCb(*(undefined4 *)(in_r0 + 4), in_r0[2]);
  }
  else
  {
    macDataPendingListManage();
  }
  if ((!bVar2) && (tx_fifo_wptr != tx_fifo_rptr))
  {
    mac_trigger_tx((void *)0x0);
  }
  return;
}
void mac_trigger_tx(void *arg)

{
  int iVar1;

  if (((mac_trx_vars[4] == '\0') && (g_zbMacCtx.indirectData.timer == (ev_timer_event_t *)0x0)) &&
      (iVar1 = get_next_data(), iVar1 != 0))
  {
    mac_trx_vars._0_4_ = iVar1;
    mac_trxTask();
  }
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void mac_trxInit(void)

{
  // Looks like an efficient way to set 12 bytes to zero.  Does not imply
  // type for the values.
  mac_trx_vars._0_4_ = 0;
  mac_trx_vars._4_4_ = 0;
  mac_trx_vars._8_4_ = 0;
  g_pTxQueue = g_txQueue;
  rf_init();
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void mac_trxTask(void)

{
  u8 *arg;
  u8 uVar1;
  hw_timer_sts_t hVar2;
  uint in_r0;
  int iVar3;
  u32 uVar4;
  u8 bVar5;
  char cVar6;
  u32 uVar7;
  uint uVar8;
  uint uVar9;
  bool bVar10;

  arg = mac_trx_vars._0_4_;
  uVar8 = in_r0 & 0xff;
  bVar5 = mac_trx_vars[4];
  uVar9 = (uint)mac_trx_vars[4];
  if (((uVar9 == 4) || (~uVar9 + uVar9 != 0)) && (uVar8 == 0))
  {
    if (~uVar9 + uVar9 != 0)
    {
      mac_trx_vars[11] = mac_trx_vars._0_4_[3];
      mac_trx_vars[9] = (u8)(((uint)*mac_trx_vars._0_4_ << 0x1c) >> 0x1c);
      mac_trx_vars[8] = (u8)uVar8;
      rf802154_tx_ready(*(u8 **)(mac_trx_vars._0_4_ + 8), mac_trx_vars._0_4_[1]);
    }
    mac_trx_vars[6] = 0;
    mac_trx_vars[7] = g_zbInfo.macPib.minBe;
    mac_trx_vars[4] = 1;
    mac_trx_vars[5] = 0;
  }
  else
  {
    if (uVar9 != 1)
    {
      if (uVar9 == 2)
      {
        if (uVar8 != 3)
        {
          if (uVar8 != 4)
          {
            return;
          }
          mac_trx_vars[4] = 6;
          mac_trx_vars._0_4_[2] = 0x1d;
          g_sysDiags.macTxIrqTimeoutCnt = g_sysDiags.macTxIrqTimeoutCnt + '\x01';
          mac_sendTxCnf();
          return;
        }
        if (g_macTimerEvt[8] != '\x01')
        {
          return;
        }
        g_macTimerEvt[8] = 0;
        if (mac_trx_vars[9] == 0)
        {
          mac_trx_vars[4] = 6;
          mac_trx_vars._0_4_[2] = 0;
          tl_zbTaskPost(mac_sendTxCnf, arg);
          return;
        }
        mac_trx_vars[4] = (u8)uVar8;
        uVar7 = drv_disable_irq();
        if (g_macTimerEvt[8] == 0)
        {
          g_macTimerEvt._0_4_ = mac_ackWaitingTimerCb;
          uVar4 = mac_currentTickGet();
          g_macTimerEvt._4_4_ = uVar4 + sysTimerPerUs * 2000;
          g_macTimerEvt[8] = bVar5;
        }
        else
        {
          sys_exceptionPost(0x6a, '#');
        }
        drv_restore_irq(uVar7);
        return;
      }
      if (uVar9 != 3)
      {
        return;
      }
      if (uVar8 == 5)
      {
        if (g_macTimerEvt[8] != '\x02')
        {
          return;
        }
        g_macTimerEvt[8] = 0;
        if ((in_r0 << 8) >> 0x18 == 0)
        {
          *mac_trx_vars._0_4_ = *mac_trx_vars._0_4_ & 0xf;
        }
        else
        {
          *mac_trx_vars._0_4_ = *mac_trx_vars._0_4_ & 0xf | 0x10;
        }
        mac_trx_vars[4] = 6;
        arg[2] = 0;
        *(char *)(*(int *)(arg + 4) + 0xc2) = (char)(in_r0 >> 8);
        mac_sendTxCnf();
        return;
      }
      if (uVar8 != 6)
      {
        return;
      }
      if (g_zbInfo.macPib.frameRetryNum <= mac_trx_vars[8])
      {
        g_sysDiags.macTxUcastFail = g_sysDiags.macTxUcastFail + 1;
        mac_trx_vars[4] = (u8)in_r0;
        mac_trx_vars[8] = mac_trx_vars[8] + 1;
        mac_trx_vars._0_4_[2] = 0xe9;
        *(undefined *)(*(int *)(arg + 4) + 0xc2) = 0x92;
        mac_sendTxCnf();
        return;
      }
      g_sysDiags.macTxUcastRetry = g_sysDiags.macTxUcastRetry + 1;
      mac_trx_vars[8] = mac_trx_vars[8] + 1;
      goto LAB_0001432a;
    }
    if (uVar8 != 2)
    {
      return;
    }
  }
  bVar5 = mac_trx_vars[6] + 1;
  if (g_zbInfo.macPib.maxCsmaBackoffs <= mac_trx_vars[6])
  {
    cVar6 = mac_trx_vars[8] + 1;
    bVar10 = g_zbInfo.macPib.frameRetryNum <= mac_trx_vars[8];
    mac_trx_vars[6] = bVar5;
    mac_trx_vars[8] = cVar6;
    if (bVar10)
    {
      g_sysDiags.macTxCcaFail = g_sysDiags.macTxCcaFail + 1;
      mac_trx_vars[4] = 6;
      arg[2] = 0xe1;
      mac_sendTxCnf();
      return;
    }
  LAB_0001432a:
    mac_trx_vars[4] = 4;
    tl_zbTaskPost(mac_trxTask, (void *)0x0);
    return;
  }
  mac_trx_vars[6] = bVar5;
  uVar1 = rf_TrxStateGet();
  if (uVar1 != '\x01')
  {
    rf_setTrxState('\x01');
  }
  if (mac_trx_vars[6] == 1)
  {
    mac_csmaStart();
    return;
  }
  if (mac_trx_vars[7] != 0)
  {
    uVar7 = drv_u32Rand();
    iVar3 = FUN_00001628(uVar7 & 0xffff, (1 << (uint)mac_trx_vars[7]) + -1);
    uVar7 = iVar3 * 0x140;
    if (uVar7 != 0)
      goto LAB_000144ac;
  }
  uVar7 = 200;
LAB_000144ac:
  hVar2 = drv_hwTmr_set('\x03', uVar7, mac_csmaStart, arg);
  if (hVar2 != HW_TIMER_SUCC)
  {
    drv_disable_irq();
    sys_exceptionPost(0x12f, '!');
  }
  if (g_zbInfo.macPib.maxBe <= mac_trx_vars[7])
  {
    mac_trx_vars[7] = g_zbInfo.macPib.maxBe;
    return;
  }
  mac_trx_vars[7] = mac_trx_vars[7] + 1;
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
undefined4 mac_waitTxIrqCb(void)

{
  if (g_macTimerEvt[8] != '\0')
  {
    rf_busyFlag = rf_busyFlag & 0xfd;
    rf_setTrxState('\x01');
    tl_zbTaskPost(mac_trxTask, &DAT_00000004);
  }
  return 0xfffffffe;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
undefined4 tl_zbMacTx(void)

{
  undefined4 in_r0;
  u32 en;
  int in_r1;
  int in_r2;
  char in_r3;
  u8 *pbVar1;
  undefined4 uVar2;
  undefined4 in_stack_00000000;

  if (in_r2 * 0x1000000 < 0)
  {
    mac_trigger_tx((void *)0x0);
    uVar2 = 0xe5;
  }
  else
  {
    en = drv_disable_irq();
    if (((uint)tx_fifo_wptr - (uint)tx_fifo_rptr & 0xff) < (uint)MAC_TX_QUEUE_SIZE)
    {
      pbVar1 = (u8 *)(g_pTxQueue + (MAC_TX_QUEUE_SIZE - 1 & (uint)tx_fifo_wptr) * 0x10);
      tx_fifo_wptr = tx_fifo_wptr + 1;
      drv_restore_irq(en);
      uVar2 = 0x1a;
      if (pbVar1 != (u8 *)0x0)
      {
        pbVar1[4] = (u8)in_r0;
        pbVar1[5] = (u8)((uint)in_r0 >> 8);
        pbVar1[6] = (u8)((uint)in_r0 >> 0x10);
        pbVar1[7] = (u8)((uint)in_r0 >> 0x18);
        *pbVar1 = *pbVar1 & 0xf0 | 1U - (in_r3 == '\0');
        pbVar1[1] = (u8)((uint)(in_r2 * 0x1000000) >> 0x18);
        pbVar1[8] = (u8)in_r1;
        pbVar1[9] = (u8)((uint)in_r1 >> 8);
        pbVar1[10] = (u8)((uint)in_r1 >> 0x10);
        pbVar1[0xb] = (u8)((uint)in_r1 >> 0x18);
        pbVar1[3] = *(u8 *)(in_r1 + 2);
        pbVar1[0xc] = (u8)in_stack_00000000;
        pbVar1[0xd] = (u8)((uint)in_stack_00000000 >> 8);
        pbVar1[0xe] = (u8)((uint)in_stack_00000000 >> 0x10);
        pbVar1[0xf] = (u8)((uint)in_stack_00000000 >> 0x18);
        uVar2 = 0;
      }
    }
    else
    {
      drv_restore_irq(en);
      uVar2 = 0x1a;
    }
    mac_trigger_tx((void *)0x0);
  }
  return uVar2;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void zb_macTimerEventProc(void)

{
  int iVar1;
  u32 uVar2;

  iVar1 = g_macTimerEvt._4_4_;
  if ((g_macTimerEvt[8] != '\0') && (uVar2 = mac_currentTickGet(), 0x80000000 < iVar1 - uVar2))
  {
    uVar2 = drv_disable_irq();
    if (g_macTimerEvt._0_4_ != 0)
    {
      FUNBBBBH();
    }
    g_macTimerEvt[8] = '\0';
    drv_restore_irq(uVar2);
  }
  return;
}

// macPld is the MAC payload aka IEEE 802.15.4 frame.
void zb_macDataRecvHander(u8 *rxBuf, u8 *macPld, u8 len, u8 ackPkt, u32 timestamp, s8 rssi)

{
  u8 bVar1;
  zb_buf_t *buf;

  buf = (zb_buf_t *)tl_phyRxBufTozbBuf(rxBuf);
  if (ackPkt == '\0')
  {
    // The first 4 bytes of this are the address (macPld) for the MAC frame.
    buf->buf[0] = (u8)macPld;
    buf->buf[1] = (u8)((uint)macPld >> 8);
    buf->buf[2] = (u8)((uint)macPld >> 0x10);
    buf->buf[3] = (u8)((uint)macPld >> 0x18);
    buf->buf[4] = (u8)timestamp;
    buf->buf[5] = (u8)(timestamp >> 8);
    buf->buf[6] = (u8)(timestamp >> 0x10);
    buf->buf[7] = (u8)(timestamp >> 0x18);
    buf->buf[8] = rssi;
    // What is this 0xfd all about?
    buf->buf[9] = len + 0xfd;
    rf_busyFlag = rf_busyFlag & 0xfe;
    bVar1 = tl_zbUserTaskQNum();
    if (bVar1 < 0x1b)
    {
      // Passing maybe 30 bytes extra before the
      tl_zbTaskPost(mac_rxDataParse, buf);
      return;
    }
  }
  else if ((mac_trx_vars[4] == '\x03') && (mac_trx_vars[11] == macPld[2]))
  {
    mac_trxTask();
  }
  zb_buf_free(buf);
  return;
}
void zb_macDataSendHander(void)

{
  mac_trxTask();
  return;
}

void mac_rxDataParse(zb_buf_t *rxBuf)
{
  u8 len_fd;
  u8 bVar2;
  u32 timestamp;
  u8 *macPld;
  u8 uVar5;
  uint zbPldLen;
  uint uVar7;
  int iVar8;
  tl_mac_hdr_t macHdr;

  (rxBuf->hdr).rssi = rxBuf->buf[8];
  uVar5 = rf_getLqi(rxBuf->buf[8]);
  timestamp = *(undefined4 *)(rxBuf->buf + 4);
  len_fd = rxBuf->buf[9];
  macPld = *(u8 **)rxBuf->buf;
  bVar2 = *macPld;

  // At this point we have not put anything into auStack.
  zbPldLen = tl_zbMacHdrParse(&macHdr,macPld);

  if ((uVar6 < len_fd) && (g_zbMacCtx.status != '\x01')) {
    uVar7 = bVar2 & 7;
    if (g_zbMacCtx.status == '\x02') {
      iVar8 = ~uVar7 + uVar7 + (uint)(1 < g_zbMacCtx.status);
LAB_0001407e:
      if (iVar8 == 0) goto LAB_00014066;
    }
    else if (g_zbMacCtx.status == '\x03') {
      if (uVar7 != 3) goto LAB_00014066;
      uVar7 = macPld[uVar6] - 8;
      iVar8 = uVar7 + ~uVar7 + (uint)(7 < macPld[uVar6]);
      goto LAB_0001407e;
    }
    // !!Bizarre - we have switched the address of macPld and the timestamp around here!
    rxBuf->buf[0] = (u8)timestamp;
    rxBuf->buf[1] = (u8)((uint)timestamp >> 8);
    rxBuf->buf[2] = (u8)((uint)timestamp >> 0x10);
    rxBuf->buf[3] = (u8)((uint)timestamp >> 0x18);
    rxBuf->buf[4] = (u8)macPld;
    rxBuf->buf[5] = (u8)((uint)macPld >> 8);
    rxBuf->buf[6] = (u8)((uint)macPld >> 0x10);
    rxBuf->buf[7] = (u8)((uint)macPld >> 0x18);
    rxBuf->buf[8] = (u8)(macHdr.destPanAgain >> 8);
    rxBuf->buf[9] = (u8)(macHdr.destPanAgain)

    // We are the destination address so assume this is the source address.
    if (macHdr.srcIeecAddrMode == LOONG) {
      memcpy(rxBuf->buf + 10, &macHdr.srcAddr, 8);
    }
    else {
      memcpy(rxBuf->buf + 10, &macHdr.srcAddr, 2);
    }
    rxBuf->buf[18] = macHdr.srcIeeeAddrMode;
    rxBuf->buf[19] = len_fd;
    rxBuf->buf[20] = uVar5;
    uVar5 = rf_getChannel();
    rxBuf->buf[21] = uVar5;

    //PDS: From here....
    tl_zbPhyIndication(rxBuf, macHdr, zbPldLen);
  }
  else {
// Error arm
LAB_00014066:
    zb_buf_free(rxBuf);
  }
  return;
}

// macPld is the internal ZigBee header (could be start of IEEE 802.15.4).
// len is the Zigbee payload length
u8 *zb_macDataFilter(u8 *macPld, u8 len, u8 *needDrop, u8 *ackPkt)

{
  byte bVar1;
  u16 destPAN;
  bool panInvalid;
  u16 *puVar4;
  uint frameCtrl;

  frameCtrl = (uint)*macPld;
  bVar1 = macPld[1];

  // Feel like a length wrap test.  Checking for "3"?
  // Checking maximum and minimum length of a frame.
  00 => fd  Bad
  01 => fe  ...
  02 => ff  Bad
  03 => 00  Good
  ...
  81 => 7e  Good
  82 => 7f  Bad
  83 => 80  ...

  // Check frame length between 3 and 0x81 inclusive.
  if ((uint)len * 0x1000000 + 0xfd000000 >> 0x18 < 0x7f)
  {
    // Length of the frame is valid.
    if ((mac_trx_vars[4] == '\x03') && ((frameCtrl & MAC_FCF_FRAME_TYPE_MASK) == MAC_FRAME_TYPE_ACK))
    {
      if (len == 5)
      {
        // Does this mean this is an ACK packet?
        *ackPkt = '\x01';
        puVar4 = (u16 *)0x0;
      }
      else
      {
        // '\x02'
        *needDrop = RF_DROP_REASON_RF_BUSY;
        puVar4 = (u16 *)0x0;
      }
    }
    else if ((frameCtrl & MAC_FCF_FRAME_TYPE_MASK) <= MAC_FRAME_TYPE_MAX_VALID)
    {
      if ((*macPld & MAC_FCF_FRAME_TYPE_MASK) == MAC_FRAME_TYPE_BEACON)
      {
        // ??? How can frameCtrl be zero and bVar1 be anything other than zero?
        if (frameCtrl == 0)
        {
          if (bVar1 == 0xc0)
          {
            return (u8 *)0x0;
          }
          if (bVar1 == 0x80)
          {
            return (u8 *)0x0;
          }
        }
        // '\x04'
        *needDrop = RF_DROP_REASON_INVALIC_BEACON;
        puVar4 = (u16 *)0x0;
      }
      else
      {
        // Not a beacon or an ACK; must be a command.
        // Pointing at destination PAN.
        puVar4 = (u16 *)(macPld + 3);
        panInvalid = false;
        if ((frameCtrl & MAC_FCF_DST_ADDR_MODE_MASK) != 0)
        {
          // Destination addressing not zero.
          destPAN = *puVar4;
          // Now pointing to destination address.
          puVar4 = (u16 *)(macPld + 5);

          panInvalid = ((destPAN != g_zbInfo.macPib.panId) && (destPAN != 0xffff));
        }

        if ((bVar1 & MAC_FCF_INTRA_PAN_MASK) && (-1 < (int)(frameCtrl << 0x19)))
        {
          // Source address present?
          // Imcrements to source address?
          puVar4 = puVar4 + 1;
        }

        if (panInvalid)
        {
          // '\x05'
          *needDrop = RF_DROP_REASON_FILTER_PANID;
          puVar4 = (u16 *)0x0;
        }
        else if ((frameCtrl & MAC_FCF_DST_ADDR_MODE_MASK) == MAC_FCF_DST_ADDR_MODE_SHORT)
        {
          // Is the destination address a match?
          if ((*(u16 *)(macPld + 5) != 0xffff) &&
              (g_zbInfo.macPib.shortAddress != *(u16 *)(macPld + 5)))
          {
            // '\x06'
            *needDrop = RF_DROP_REASON_FILTER_DSTADDR;
          }
          puVar4 = puVar4 + 1;
        }
        else if ((frameCtrl & MAC_FCF_DST_ADDR_MODE_MASK) == MAC_FCF_DST_ADDR_MODE_LONG)
        {
          // Same check for long address.
          if ((((*(short *)(macPld + 5) != g_zbInfo.macPib.extAddress._0_2_) ||
                (*(short *)(macPld + 7) != g_zbInfo.macPib.extAddress._2_2_)) ||
               (*(short *)(macPld + 9) != g_zbInfo.macPib.extAddress._4_2_)) ||
              (*(short *)(macPld + 0xb) != g_zbInfo.macPib.extAddress._6_2_))
          {
            // '\a'
            *needDrop = RF_DROP_REASON_0A;
          }
          puVar4 = puVar4 + 4;
        }
        else if ((bVar1 & 0xc) == 0)
        {
          // '\b'
          *needDrop = RF_DROP_REASON_FILTER_LEN;
        }
      }
    }
    else
    {
      //'\x03';
      *needDrop = RF_REASON_EXPECT_ACK;
      puVar4 = (u16 *)0x0;
    }
  }
  else
  {
    // '\t'
    *needDrop = RF_DROP_REASON_INVALID_FRAME_LENGTH;

    // Statistics.
    g_sysDiags.phyLengthError = g_sysDiags.phyLengthError + 1;
    puVar4 = (u16 *)0x0;
  }
  return (u8 *)puVar4;
}
