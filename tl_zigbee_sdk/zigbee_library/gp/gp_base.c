// WARNING: Unknown calling convention -- yet parameter storage is locked
uint gpAliasSrcAddrDerived(void)

{
  char in_r0;
  uint uVar1;
  uint in_r1;
  uint uVar2;
  uint uVar3;

  if (in_r0 == '\0')
  {
    uVar1 = in_r1 & 0xffff;
    uVar2 = in_r1 >> 0x10;
  }
  else
  {
    if (in_r0 != '\x02')
    {
      return 7;
    }
    uVar1 = (in_r1 >> 8 & 0xff) * 0x100 + (in_r1 & 0xff) & 0xffff;
    uVar2 = (in_r1 >> 0x18) * 0x100 + (in_r1 >> 0x10 & 0xff) & 0xffff;
  }
  uVar3 = uVar1;
  if ((0xfff5 < (uVar1 - 1 & 0xffff)) && (uVar3 = uVar2 ^ uVar1, 0xfff5 < (uVar3 - 1 & 0xffff)))
  {
    if (uVar1 == 0)
    {
      uVar3 = 7;
    }
    else
    {
      uVar3 = uVar1 - 8 & 0xffff;
    }
  }
  return uVar3;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
undefined4 gpDataIndDuplicateFind(void)

{
  int iVar1;
  byte in_r0;
  int iVar2;
  int in_r3;
  int iVar3;
  char *pcVar4;
  char in_stack_00000000;
  undefined auStack_2c[8];

  pcVar4 = g_gpDataIndSecReqTab + 0x11;
  iVar3 = 0;
  while (true)
  {
    iVar1 = iVar3 * 0x13;
    if (((((g_gpDataIndSecReqTab[iVar1 + 0x12] & 0x40) != 0) &&
          ((g_gpDataIndSecReqTab[iVar1 + 0x12] & 7) == in_r0)) &&
         (iVar2 = memcmp(auStack_2c, g_gpDataIndSecReqTab + iVar1 + 8, 8), iVar2 == 0)) &&
        ((*(int *)(g_gpDataIndSecReqTab + iVar1 + 4) == in_r3 && (*pcVar4 != in_stack_00000000))))
      break;
    iVar3 = iVar3 + 1;
    pcVar4 = pcVar4 + 0x13;
    if (iVar3 == 4)
    {
      return 0;
    }
  }
  return 1;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void gpDataIndDuplicatePeriodic(void)

{
  char cVar1;
  int iVar2;
  char *pcVar3;

  pcVar3 = g_gpDataIndSecReqTab + 0x10;
  iVar2 = 0;
  do
  {
    if ((g_gpDataIndSecReqTab[iVar2 * 0x13 + 0x12] & 0x40) != 0)
    {
      cVar1 = *pcVar3;
      if (cVar1 != -1)
      {
        if (cVar1 == '\0')
        {
          gpDataIndSecReqEntryClear();
        }
        else
        {
          *pcVar3 = cVar1 + -1;
        }
      }
    }
    iVar2 = iVar2 + 1;
    pcVar3 = pcVar3 + 0x13;
  } while (iVar2 != 4);
  return;
}
void gpDevAnnceAliasSend(u16 aliasNwkAddr)

{
  undefined auStack_14[12];

  memcpy(auStack_14, &g_invalid_addr, 8);
  zdo_devAnnce();
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
undefined gpKeyRecovery(void)

{
  char in_r0;
  int iVar1;
  char in_r1;
  void *in_r2;
  undefined in_r3;
  uint uVar2;
  char *in_stack_00000000;
  void *in_stack_00000004;

  if (in_r0 != '\0')
  {
    if ((in_r1 != '\x04') && (in_r1 != '\a'))
    {
      return 0;
    }
    iVar1 = memcmp(in_r2, g_null_securityKey, 0x10);
    if (iVar1 == 0)
    {
      return 0;
    }
    memcpy(in_stack_00000004, in_r2, 0x10);
    *in_stack_00000000 = in_r1;
    return in_r3;
  }
  if (in_r1 == '\x01')
  {
    iVar1 = memcmp(in_r2, g_null_securityKey, 0x10);
    if (iVar1 == 0)
    {
      if (zclGpAttr_gpSharedSecKeyType == '\x01')
      {
        memcpy(in_stack_00000004, zclGpAttr_gpSharedSecKey, 0x10);
      }
      else
      {
        uVar2 = ((uint)ss_ib._62_1_ << 0x1a) >> 0x1e;
        iVar1 = memcmp(ss_ib.nwkSecurMaterialSet + uVar2, g_null_securityKey, 0x10);
        if (iVar1 == 0)
        {
          return 0;
        }
        memcpy(in_stack_00000004, ss_ib.nwkSecurMaterialSet + uVar2, 0x10);
      }
    }
    else
    {
      memcpy(in_stack_00000004, in_r2, 0x10);
    }
    *in_stack_00000000 = '\x01';
    return in_r3;
  }
  if (in_r1 != '\x02')
  {
    if (in_r1 != '\x03')
    {
      return 0;
    }
    iVar1 = memcmp(in_r2, g_null_securityKey, 0x10);
    if (iVar1 == 0)
    {
      if (zclGpAttr_gpSharedSecKeyType != '\x03')
      {
        return 0;
      }
      memcpy(in_stack_00000004, zclGpAttr_gpSharedSecKey, 0x10);
    }
    else
    {
      memcpy(in_stack_00000004, in_r2, 0x10);
    }
    *in_stack_00000000 = '\x03';
    return in_r3;
  }
  iVar1 = memcmp(in_r2, g_null_securityKey, 0x10);
  if (iVar1 == 0)
  {
    if (zclGpAttr_gpSharedSecKeyType != '\x02')
    {
      return 0;
    }
    memcpy(in_stack_00000004, zclGpAttr_gpSharedSecKey, 0x10);
  }
  else
  {
    memcpy(in_stack_00000004, in_r2, 0x10);
  }
  *in_stack_00000000 = '\x02';
  return in_r3;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
bool gpSecKeyTypeMappingChk(void)

{
  byte in_r0;
  char in_r1;
  bool bVar1;

  if ((in_r1 != '\x01') || (bVar1 = true, 3 < in_r0))
  {
    if ((in_r1 == '\0') && ((in_r0 == 7 || (in_r0 == 4))))
    {
      bVar1 = true;
    }
    else
    {
      bVar1 = (byte)(in_r0 - 5) < 2;
    }
  }
  return bVar1;
}
void gpSwitchToTransmitChannel(u8 operationChannel, u8 tempMasterTxChannel)

{
  byte bVar1;

  if ((uint)g_gpBaseCtx._4_1_ != operationChannel + 0xb)
  {
    g_gpBaseCtx._4_1_ = (byte)(operationChannel + 0xb);
  }
  bVar1 = rf_getChannel();
  if (tempMasterTxChannel + 0xb != (uint)bVar1)
  {
    tl_zbMacChannelSet((u8)(tempMasterTxChannel + 0xb));
  }
  if ((ev_timer_event_t *)g_gpBaseCtx != (ev_timer_event_t *)0x0)
  {
    ev_timer_taskCancel((ev_timer_event_t **)&g_gpBaseCtx);
  }
  g_gpBaseCtx._0_4_ = ev_timer_taskPost(gpTransmitChannelTimeoutCb, (void *)0x0, (u32)&DAT_00001388);
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void gpTranimitGPDF(void)

{
  u8 uVar1;
  void **in_r0;
  zb_buf_t *p;
  void *out;

  p = (zb_buf_t *)c1();
  if (p != (zb_buf_t *)0x0)
  {
    if (*(char *)(in_r0 + 5) == -0xd)
    {
      *(undefined *)((int)in_r0 + 0x16) = 0xbe;
    }
    else
    {
      uVar1 = dGpStubHandleGet();
      *(u8 *)((int)in_r0 + 0x16) = uVar1;
    }
    memcpy(p, in_r0, 0x17);
    p->buf[0] = '\0';
    p->buf[1] = '\0';
    p->buf[2] = '\0';
    p->buf[3] = '\0';
    if (p->buf[0x15] != '\0')
    {
      out = tl_bufInitalloc(p, p->buf[0x15]);
      p->buf[0] = (u8)out;
      p->buf[1] = (u8)((uint)out >> 8);
      p->buf[2] = (u8)((uint)out >> 0x10);
      p->buf[3] = (u8)((uint)out >> 0x18);
      memcpy(out, *in_r0, (uint)p->buf[0x15]);
    }
    tl_zbTaskPost(gpDataReq, p);
  }
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
undefined4 gpTransmitChannelTimeoutCb(void)

{
  u8 uVar1;
  u8 uVar2;

  uVar1 = g_gpBaseCtx._4_1_;
  uVar2 = rf_getChannel();
  if (uVar1 != uVar2)
  {
    tl_zbMacChannelSet(g_gpBaseCtx._4_1_);
  }
  gpTxQueueMaintenceClear();
  g_gpBaseCtx._0_4_ = 0;
  return 0xfffffffe;
}
void gpTransmitChannelTimeoutStop(void)

{
  u8 uVar1;
  u8 uVar2;

  uVar1 = g_gpBaseCtx._4_1_;
  uVar2 = rf_getChannel();
  if (uVar1 != uVar2)
  {
    tl_zbMacChannelSet(g_gpBaseCtx._4_1_);
  }
  if ((int)g_gpBaseCtx != 0)
  {
    ev_timer_taskCancel((ev_timer_event_t **)&g_gpBaseCtx);
  }
  return;
}
u8 gppTunnelingDelayGet(bool rxAfterTx, u8 lqi, bool firstToForward, bool noRoute)

{
  u8 uVar1;
  char cVar2;

  uVar1 = '\x05';
  if (rxAfterTx)
  {
    uVar1 = ' ';
  }
  cVar2 = '`';
  if (lqi != '\0')
  {
    cVar2 = ' ';
  }
  if (noRoute)
  {
    uVar1 = uVar1 + 'd';
  }
  else if (!firstToForward)
  {
    uVar1 = cVar2 + uVar1;
  }
  return uVar1;
}
