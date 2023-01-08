// WARNING: Unknown calling convention -- yet parameter storage is locked
void tl_zbMacActiveScanListAdd(void)

{
  g_macScanParam[17] = g_macScanParam[17] + '\x01';
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
undefined4 tl_zbMacMlmeBeaconRequestCmdSend(void)

{
  u8 *p;
  undefined *puVar1;
  undefined4 uVar2;

  p = g_zbMacCtx.txRawDataBuf;
  uVar2 = 0;
  if (-1 < (int)((uint)g_zbMacCtx.txRawDataBuf[0xc3] << 0x1c))
  {
    g_zbMacCtx.txRawDataBuf[0xc3] = g_zbMacCtx.txRawDataBuf[0xc3] | 8;
    p[0xc1] = 0xe4;
    tl_bufInitalloc((zb_buf_t *)p, '\b');
    puVar1 = (undefined *)tl_zbMacHdrBuilder();
    *puVar1 = 7;
    uVar2 = tl_zbMacTx();
  }
  return uVar2;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void tl_zbMacOrphanScanStatusUpdate(void)

{
  g_macScanParam[16] = 1;
  return;
}
// WARNING: Removing unreachable block (RAM,0x00013e88)
// WARNING: Removing unreachable block (RAM,0x00013f1c)
// WARNING: Removing unreachable block (RAM,0x00013f2a)
// WARNING: Removing unreachable block (RAM,0x00013f20)
// WARNING: Removing unreachable block (RAM,0x00013f26)
// WARNING: Removing unreachable block (RAM,0x00013eca)
// WARNING: Removing unreachable block (RAM,0x00013ece)
// WARNING: Removing unreachable block (RAM,0x00013eda)
// WARNING: Removing unreachable block (RAM,0x00013ee0)
// WARNING: Removing unreachable block (RAM,0x00013f30)
// WARNING: Removing unreachable block (RAM,0x00013ee6)
// WARNING: Removing unreachable block (RAM,0x00013ee8)
// WARNING: Unknown calling convention -- yet parameter storage is locked
void tl_zbMacScanRequestHandler(void)

{
  undefined *in_r0;
  undefined uVar1;

  uVar1 = 0xfc;
  if (7 < (byte)in_r0[5])
  {
    uVar1 = 0xe8;
  }
  *in_r0 = uVar1;
  in_r0[1] = in_r0[4];
  tl_zbPrimitivePost('\x01', 'V', in_r0);
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
undefined4 tl_zbMacScanRunning(void)

{
  u8 *p;
  byte bVar1;
  u8 uVar2;
  undefined4 uVar3;
  undefined *puVar4;
  uint uVar5;
  uint uVar6;
  undefined4 uStack_28;
  int iStack_24;
  undefined2 local_20;

  bVar1 = g_macScanParam[17];
  puVar4 = g_macScanParam._4_4_;
  uVar6 = (uint)g_macScanParam[12];
  if ((chan_8321 < 0x1b) && (g_macScanParam[16] == '\0'))
  {
    iStack_24 = ~uVar6 + uVar6 + 1;
    if ((iStack_24 != 0) && (edChan_8323 != 0xff))
    {
      uVar5 = (uint)g_macScanParam[17];
      uVar2 = rf_stopED();
      puVar4[uVar5 + 8] = uVar2;
      g_macScanParam[17] = bVar1 + 1;
      if (0x1a < chan_8321)
      {
        return 0;
      }
    }
    do
    {
      if ((g_macScanParam._8_4_ & 1 << chan_8321) != 0)
      {
        tl_zbMacChannelSet((u8)chan_8321);
        p = g_zbMacCtx.txRawDataBuf;
        g_macScanParam[13] = (undefined)chan_8321;
        if (iStack_24 == 0)
        {
          if (uVar6 == 3)
          {
            local_20 = 0;
            if (-1 < (int)((uint)g_zbMacCtx.txRawDataBuf[0xc3] << 0x1c))
            {
              g_zbMacCtx.txRawDataBuf[0xc3] = g_zbMacCtx.txRawDataBuf[0xc3] | 8;
              uStack_28 = 0xfffe;
              memcpy((void *)((int)&uStack_28 + 2), g_zbInfo.macPib.extAddress, 8);
              uVar2 = tl_zbMacHdrSize(0xc803);
              p[0xc1] = 0xea;
              tl_bufInitalloc((zb_buf_t *)p, uVar2 + '\x01');
              puVar4 = (undefined *)tl_zbMacHdrBuilder();
              *puVar4 = 6;
              tl_zbMacTx();
            }
          }
          else if (uVar6 == 1)
          {
            tl_zbMacMlmeBeaconRequestCmdSend();
          }
          g_macScanParam._8_4_ = g_macScanParam._8_4_ & ~(1 << chan_8321);
          return 0;
        }
        rf_startED();
        edChan_8323 = chan_8321;
        g_macScanParam._8_4_ = g_macScanParam._8_4_ & ~(1 << chan_8321);
        return 0;
      }
      chan_8321 = chan_8321 + 1;
    } while (chan_8321 != 0x1b);
    chan_8321 = 0x1b;
    uVar3 = 0;
  }
  else
  {
    chan_8321 = 0xb;
    edChan_8323 = 0xff;
    g_macScanParam._4_4_[1] = g_macScanParam[12];
    *puVar4 = 0xea;
    puVar4[3] = g_macScanParam[17];
    if ((uVar6 == 0) || ((g_macScanParam[17] != 0 || (g_macScanParam[16] != '\0'))))
    {
      *puVar4 = 0;
    }
    tl_zbPrimitivePost('\x01', 'V', puVar4);
    g_zbMacCtx.status = '\0';
    tl_zbMacChannelSet(g_macScanParam[14]);
    rf_setTrxState(g_macScanParam[18]);
    g_macScanParam._0_4_ = 0;
    uVar3 = 0xfffffffe;
  }
  return uVar3;
}
