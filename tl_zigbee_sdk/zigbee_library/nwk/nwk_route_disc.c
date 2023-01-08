// WARNING: Unknown calling convention -- yet parameter storage is locked
undefined4 nwkConcentDiscTimerCb(void)

{
  zb_buf_t *buf;
  int iVar1;
  undefined4 uVar2;

  if (g_zbInfo.nwkNib.concentratorDiscoveryTime == '\0')
  {
    concentratorDiscoveryTimer = 0;
    uVar2 = 0xfffffffe;
  }
  else
  {
    buf = (zb_buf_t *)c1();
    uVar2 = 0;
    if (buf != (zb_buf_t *)0x0)
    {
      iVar1 = nwkManyToOneRouteDiscEntryInitFind();
      if (iVar1 == 0)
      {
        g_routeReqId = g_routeReqId + '\x01';
        iVar1 = nwkRouteDiscEntryCreate();
        if (iVar1 == 0)
        {
          zb_buf_free(buf);
          return 0;
        }
      }
      else
      {
        *(char *)(iVar1 + 0x10) = g_routeReqId;
        g_routeReqId = g_routeReqId + '\x01';
        *(undefined *)(iVar1 + 0xe) = 10;
        *(undefined *)(iVar1 + 0xf) = 0;
      }
      nwkRouteReqConcentInitiation();
      uVar2 = 0;
    }
  }
  return uVar2;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
undefined4 nwkDiscDataPendClear(void)

{
  zb_buf_t **ppzVar1;
  undefined4 uVar2;

  ppzVar1 = (zb_buf_t **)nwkTxDataPendTabEntryRtDiscFind();
  uVar2 = 0xd3;
  if (ppzVar1 != (zb_buf_t **)0x0)
  {
    do
    {
      if (*(byte *)(ppzVar1 + 2) < 0xc0)
      {
        nwkNldeDataCnf();
      }
      else
      {
        zb_buf_free(*ppzVar1);
      }
      *(undefined *)ppzVar1 = 0;
      *(undefined *)((int)ppzVar1 + 1) = 0;
      *(undefined *)((int)ppzVar1 + 2) = 0;
      *(undefined *)((int)ppzVar1 + 3) = 0;
      nwkTxDataPendTabEntryClear();
      ppzVar1 = (zb_buf_t **)nwkTxDataPendTabEntryRtDiscFind();
    } while (ppzVar1 != (zb_buf_t **)0x0);
    uVar2 = 0;
  }
  return uVar2;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
undefined4 nwkDiscDataPendSend(void)

{
  void **ppvVar1;
  undefined4 uVar2;

  ppvVar1 = (void **)nwkTxDataPendTabEntryRtDiscFind();
  uVar2 = 0xd3;
  if (ppvVar1 != (void **)0x0)
  {
    do
    {
      *(undefined *)((int)*ppvVar1 + 0xc1) = *(undefined *)(ppvVar1 + 2);
      *(byte *)((int)ppvVar1 + 0xb) = *(byte *)((int)ppvVar1 + 0xb) & 0xbf;
      tl_zbTaskPost(nwkMsgSendCb, *ppvVar1);
      *(undefined *)ppvVar1 = 0;
      *(undefined *)((int)ppvVar1 + 1) = 0;
      *(undefined *)((int)ppvVar1 + 2) = 0;
      *(undefined *)((int)ppvVar1 + 3) = 0;
      nwkTxDataPendTabEntryClear();
      ppvVar1 = (void **)nwkTxDataPendTabEntryRtDiscFind();
    } while (ppvVar1 != (void **)0x0);
    uVar2 = 0;
  }
  return uVar2;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void nwkRouteDiscPeriodic(void)

{
  char cVar1;
  int iVar2;
  short sVar3;
  int iVar4;
  int iVar5;
  int iVar6;

  if (g_routeDiscTabCnt != '\0')
  {
    iVar6 = 0x847f34;
    iVar5 = 0;
    do
    {
      while (*(char *)(iVar6 + 5) != '\0')
      {
        if (((*(short *)(g_routeDiscTab + iVar5 * 0x16 + 0xe) != 0) &&
             (sVar3 = *(short *)(g_routeDiscTab + iVar5 * 0x16 + 0xe) + -1,
              *(short *)(g_routeDiscTab + iVar5 * 0x16 + 0xe) = sVar3, sVar3 != 0)) ||
            (iVar4 = iVar5 * 0x16, *(int *)(g_routeDiscTab + iVar4) != 0))
          break;
        if ((*(ushort *)(g_routeDiscTab + iVar4 + 0xc) & 0xfff8) != 0xfff8)
        {
          iVar2 = nwkRoutingTabEntryDstFind();
          if (iVar2 != 0)
          {
            cVar1 = *(char *)(iVar2 + 4);
            if (cVar1 == '\x01')
            {
              *(undefined *)(iVar2 + 4) = 2;
            }
            else if (cVar1 == '\x04')
            {
              if (((*(u16 *)(g_routeDiscTab + iVar4 + 8) == g_zbInfo.nwkNib.nwkAddr) &&
                   (iVar4 = nwkDiscDataPendSend(), iVar4 != 0)) &&
                  (iVar4 = c1(), iVar4 != 0))
              {
                nwkRouteDiscStatusCodeSend();
              }
            }
            else if (cVar1 == '\0')
            {
              nwkDiscDataPendSend();
            }
          }
          nwkDiscDataPendClear();
        }
        nwkRouteDiscTabEntryClear();
        iVar5 = iVar5 + 1;
        iVar6 = iVar6 + 0x16;
        if (iVar5 == 10)
        {
          return;
        }
      }
      iVar5 = iVar5 + 1;
      iVar6 = iVar6 + 0x16;
    } while (iVar5 != 10);
  }
  return;
}
// WARNING: Could not reconcile some variable overlaps
// WARNING: Unknown calling convention -- yet parameter storage is locked
undefined4 nwkRouteDiscStart(void)

{
  u8 uVar1;
  bool bVar2;
  u16 *in_r0;
  zb_buf_t *buf;
  uint uVar3;
  int iVar4;
  ev_timer_event_t *peVar5;
  char *pcVar6;
  byte bVar7;
  int iVar8;
  char cVar9;
  undefined4 uVar10;
  int iVar11;
  undefined1 *arg;
  undefined4 in_stack_ffffff9c;
  undefined4 in_stack_ffffffa0;
  nwk_hdr_t local_5c;
  undefined4 local_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  uint uStack_30;
  uint uStack_2c;
  undefined4 uStack_28;
  undefined2 local_24;
  undefined local_22;

  g_sysDiags.routeDiscInitiated = g_sysDiags.routeDiscInitiated + 1;
  buf = (zb_buf_t *)c1();
  if (buf == (zb_buf_t *)0x0)
  {
    return 0xd1;
  }
  local_5c._0_4_ = 0;
  local_5c._4_4_ = 0;
  local_5c.dstIeeeAddr._0_4_ = 0;
  local_5c.dstIeeeAddr._4_4_ = 0;
  local_5c.srcIeeeAddr._0_4_ = 0;
  local_5c.srcIeeeAddr._4_4_ = 0;
  local_5c._24_4_ = 0;
  local_5c.srcRouteSubFrame.relayList = (u8 *)0x0;
  local_3c = 0;
  uStack_38 = 0;
  uStack_34 = 0;
  uStack_30 = 0;
  uStack_2c = 0;
  uStack_28 = 0;
  local_24 = 0;
  local_22 = 0;
  if ((*(u8 *)((int)in_r0 + 3) != '\0') ||
      (uVar1 = g_zbInfo.nwkNib.concentratorRadius, *(char *)(in_r0 + 1) != '\0'))
  {
    uVar1 = *(u8 *)((int)in_r0 + 3);
  }
  uVar3 = 0;
  if (((int)((uint)ss_ib._62_1_ << 0x1c) < 0) && ((ss_ib._62_1_ & 7) != 0))
  {
    bVar2 = ss_keyPreconfigured();
    uVar3 = (uint)(bVar2 != false);
  }
  local_5c.framecontrol =
      (nwkFrameCtrl_t)(CONCAT11((byte)(local_5c._4_4_ >> 8) & 0xfd | (byte)(uVar3 << 1), (char)local_5c._4_4_) &
                           0xffc0 |
                       9);
  local_5c._4_4_ = local_5c._4_4_ & 0xffff0000 | (uint)(ushort)local_5c.framecontrol;
  local_5c._4_4_ = local_5c._4_4_ | 0x1000;
  local_5c._0_4_ = CONCAT22(g_zbInfo.nwkNib.nwkAddr, 0xfffb);
  memcpy(local_5c.srcIeeeAddr, g_zbInfo.macPib.extAddress, 8);
  if (uVar1 == '\0')
  {
    uVar1 = (u8)(((uint)g_zbInfo.nwkNib.maxDepth << 0x19) >> 0x18);
  }
  local_5c._4_4_ = CONCAT13(g_zbInfo.nwkNib.seqNum, CONCAT12(uVar1, (short)local_5c._4_4_));
  g_zbInfo.nwkNib.seqNum = g_zbInfo.nwkNib.seqNum + '\x01';
  uVar1 = getNwkHdrSize(&local_5c);
  local_5c._24_2_ = CONCAT11(uVar1, local_5c.mcaseControl);
  local_5c._24_4_ = local_5c._24_4_ & 0xffff0000 | (uint)local_5c._24_2_;
  local_3c = CONCAT31(local_3c._1_3_, 1);
  cVar9 = *(char *)(in_r0 + 1);
  if (cVar9 == '\0')
  {
    uStack_30 = uStack_30 & 0xffffff00 |
                (byte)((byte)uStack_30 & 0xe7 |
                       (byte)((2 - ((uint) * (byte *)(in_r0 + 2) + ~(uint) * (byte *)(in_r0 + 2) + 1) & 3) << 3)) &
                    0xffffffbf;
    uStack_2c = uStack_2c & 0xffffff00;
  LAB_0001cad8:
    iVar4 = nwkManyToOneRouteDiscEntryInitFind();
    cVar9 = g_routeReqId;
    if (iVar4 == 0)
    {
      g_routeReqId = g_routeReqId + '\x01';
      iVar4 = nwkRouteDiscEntryCreate();
      if (iVar4 == 0)
        goto LAB_0001cc36;
      cVar9 = *(char *)(iVar4 + 0x10);
    }
    else
    {
      *(char *)(iVar4 + 0x10) = g_routeReqId;
      g_routeReqId = g_routeReqId + '\x01';
      *(undefined *)(iVar4 + 0xe) = 10;
      *(undefined *)(iVar4 + 0xf) = 0;
    }
    uStack_30._0_2_ = CONCAT11(cVar9, (byte)uStack_30);
    uStack_30 = CONCAT22(*(undefined2 *)(iVar4 + 0xc), (undefined2)uStack_30);
    nwkRouteReqCmdSend();
    if (concentratorDiscoveryTimer != (ev_timer_event_t *)0x0)
    {
      ev_timer_taskCancel(&concentratorDiscoveryTimer);
    }
    uVar10 = 0;
    if (g_zbInfo.nwkNib.concentratorDiscoveryTime != 0)
    {
      concentratorDiscoveryTimer =
          ev_timer_taskPost(nwkConcentDiscTimerCb, (void *)(uint) * (byte *)(in_r0 + 2),
                            (uint)g_zbInfo.nwkNib.concentratorDiscoveryTime * 1000);
    }
  }
  else
  {
    if (cVar9 == '\x02')
    {
      uVar1 = zb_address_ieee_by_short(*in_r0, (addrExt_t)CONCAT44(in_stack_ffffffa0, in_stack_ffffff9c));
      if (((uVar1 == '\0') && (iVar4 = memcmp(&uStack_38, &g_zero_addr, 8), iVar4 != 0)) &&
          (iVar4 = memcmp(&uStack_38, &g_invalid_addr, 8), iVar4 != 0))
      {
        uStack_30 = uStack_30 | 0x20;
      }
      cVar9 = *(char *)(in_r0 + 1);
      uStack_30 = uStack_30 & 0xffffff00 |
                  (uint)(byte)((byte)uStack_30 & 0xbf |
                               ((cVar9 - 1U) + ~(cVar9 - 1U) + (cVar9 != '\0')) * '@');
      uStack_2c = uStack_2c & 0xffffff00;
      if (cVar9 == '\0')
        goto LAB_0001cad8;
    }
    else
    {
      uStack_30 = uStack_30 & 0xffffff00 |
                  (uint)(byte)((byte)uStack_30 & 0xbf |
                               ((cVar9 - 1U) + ~(cVar9 - 1U) + (cVar9 != '\0')) * '@');
      uStack_2c = uStack_2c & 0xffffff00;
    }
    iVar4 = nwkRoutingTabEntryDstFind();
    if (iVar4 == 0)
    {
    LAB_0001cb70:
      iVar4 = nwkRoutingTabEntryCreate();
      if (iVar4 == 0)
        goto LAB_0001cc36;
      bVar7 = *(char *)(in_r0 + 1) - 1;
      *(byte *)(iVar4 + 5) =
          *(byte *)(iVar4 + 5) & 0xf7 | (bVar7 + ~bVar7 + (*(char *)(in_r0 + 1) != '\0')) * '\b';
    }
    else
    {
      if ((int)((uint) * (byte *)(iVar4 + 5) << 0x1c) < 0)
      {
        if (*(char *)(in_r0 + 1) != '\x01')
          goto LAB_0001cb70;
      }
      else if (*(char *)(in_r0 + 1) != '\x02')
        goto LAB_0001cb70;
      if ((*(char *)(iVar4 + 4) != '\x04') && (*(char *)(iVar4 + 4) != '\0'))
      {
        *(undefined *)(iVar4 + 4) = 1;
      }
      *(byte *)(iVar4 + 5) = *(byte *)(iVar4 + 5) & 0xf;
    }
    pcVar6 = g_routeDiscTab + 0x15;
    iVar8 = 0;
    do
    {
      iVar11 = iVar8 * 0x16;
      arg = g_txDataPendTab + iVar11 + 0xbf;
      if ((*(u16 *)(g_routeDiscTab + iVar11 + 0xb) == *in_r0) && (*pcVar6 != '\0'))
      {
        if (*(int *)(g_routeDiscTab + iVar11 + 3) != 0)
        {
          zb_buf_free(buf);
          return 0;
        }
        nwkDiscDataPendClear();
        cVar9 = g_routeReqId;
        g_routeDiscTab[iVar11 + 0xf] = g_routeReqId;
        g_routeReqId = g_routeReqId + '\x01';
        g_routeDiscTab[iVar11 + 0xd] = 10;
        g_routeDiscTab[iVar11 + 0xe] = 0;
        g_routeDiscTab[iVar11 + 0x13] = 0;
        g_routeDiscTab[iVar11 + 0x10] = 0;
        g_routeDiscTab[iVar11 + 0x11] = 0xff;
        goto LAB_0001cd2c;
      }
      iVar8 = iVar8 + 1;
      pcVar6 = pcVar6 + 0x16;
    } while (iVar8 != 10);
    g_routeReqId = g_routeReqId + '\x01';
    arg = (undefined1 *)nwkRouteDiscEntryCreate();
    if (arg != (undefined1 *)0x0)
    {
      cVar9 = arg[0x10];
    LAB_0001cd2c:
      uStack_30._0_2_ = CONCAT11(cVar9, (byte)uStack_30);
      uStack_30 = CONCAT22(*(undefined2 *)(arg + 0xc), (undefined2)uStack_30);
      nwkRouteReqCmdSend();
      if (NWKC_INITIAL_RREQ_RETRIES == '\0')
      {
        return 0;
      }
      uVar1 = ev_timer_enough();
      if (uVar1 == '\0')
      {
        return 0;
      }
      iVar4 = nwkRouteDiscCachePacketCopy();
      if (iVar4 == 0)
      {
        return 0;
      }
      *arg = (char)iVar4;
      arg[1] = (char)((uint)iVar4 >> 8);
      arg[2] = (char)((uint)iVar4 >> 0x10);
      arg[3] = (char)((uint)iVar4 >> 0x18);
      peVar5 = ev_timer_taskPost(nwkRouteReqInitialRetry, arg, 0xfe);
      arg[4] = (char)peVar5;
      arg[5] = (char)((uint)peVar5 >> 8);
      arg[6] = (char)((uint)peVar5 >> 0x10);
      arg[7] = (char)((uint)peVar5 >> 0x18);
      return 0;
    }
    if (*(char *)(iVar4 + 4) == '\x01')
    {
      *(undefined *)(iVar4 + 4) = 3;
    }
  LAB_0001cc36:
    zb_buf_free(buf);
    uVar10 = 0xd1;
  }
  return uVar10;
}
// WARNING: Could not reconcile some variable overlaps
// WARNING: Unknown calling convention -- yet parameter storage is locked
void nwkRouteDiscStatusCodeSend(void)

{
  u8 uVar1;
  bool bVar2;
  void *in_r0;
  uint uVar3;
  undefined2 in_r1;
  undefined2 in_r2;
  undefined in_r3;
  undefined local_5c[4];
  undefined4 uStack_58;
  undefined4 uStack_54;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  undefined4 uStack_48;
  uint uStack_44;
  u8 *puStack_40;
  undefined local_3c[7];
  undefined uStack_35;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined2 local_24;
  undefined local_22;

  local_5c = (undefined[4])0x0;
  uStack_58 = 0;
  uStack_54 = 0;
  uStack_50 = 0;
  uStack_4c = 0;
  uStack_48 = 0;
  uStack_44 = 0;
  puStack_40 = (u8 *)0x0;
  local_3c._0_4_ = 0;
  stack0xffffffc8 = 0;
  uStack_34 = 0;
  uStack_30 = 0;
  uStack_2c = 0;
  uStack_28 = 0;
  local_24 = 0;
  local_22 = 0;
  uVar3 = 0;
  if (((int)((uint)ss_ib._62_1_ << 0x1c) < 0) && ((ss_ib._62_1_ & 7) != 0))
  {
    bVar2 = ss_keyPreconfigured();
    uVar3 = (uint)bVar2;
  }
  uStack_58 = uStack_58 & 0xffff0000 |
              (ushort)((ushort)(byte)(uStack_58._1_1_ & 0xfd | (byte)(uVar3 << 1)) << 8 |
                       (byte)uStack_58 & 0xc0 | 1 | 0x1008) &
                  0xfffff7ff;
  memcpy(&uStack_4c, g_zbInfo.macPib.extAddress, 8);
  local_5c = (undefined[4])CONCAT22(g_zbInfo.nwkNib.nwkAddr, in_r1);
  uStack_58 = CONCAT13(g_zbInfo.nwkNib.seqNum,
                       CONCAT12(g_zbInfo.nwkNib.maxDepth << 1, uStack_58._0_2_));
  g_zbInfo.nwkNib.seqNum = g_zbInfo.nwkNib.seqNum + '\x01';
  uVar1 = getNwkHdrSize((nwk_hdr_t *)local_5c);
  uStack_44._0_2_ = CONCAT11(uVar1, uStack_44._0_1_);
  uStack_44 = uStack_44 & 0xffff0000 | (uint)(ushort)uStack_44;
  local_3c._0_4_ = CONCAT31(local_3c._1_3_, 3);
  stack0xffffffc8 = CONCAT22(CONCAT11(uStack_35, in_r3), in_r2);
  tl_zbNwkSendNwkStatusCmd(in_r0, (nwk_hdr_t *)local_5c, (nwkCmd_t *)local_3c, 0xc9);
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void nwkRouteDiscTabEntryClear(void)

{
  int *in_r0;

  if ((in_r0 != (int *)0x0) && (*(char *)((int)in_r0 + 0x15) != '\0'))
  {
    if (in_r0[1] != 0)
    {
      ev_timer_taskCancel((ev_timer_event_t **)(in_r0 + 1));
    }
    if (*in_r0 != 0)
    {
      sys_exceptionPost(0x46, '4');
    }
    nwkRouteDiscTabEntryRst();
    g_routeDiscTabCnt = g_routeDiscTabCnt + -1;
  }
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void nwkRouteDiscTabEntryRst(void)

{
  void *in_r0;

  memset(in_r0, 0, 0x16);
  *(undefined *)((int)in_r0 + 0xc) = 0xfd;
  *(undefined *)((int)in_r0 + 0xd) = 0xfe;
  *(undefined *)((int)in_r0 + 10) = 0xfd;
  *(undefined *)((int)in_r0 + 0xb) = 0xfe;
  *(undefined *)((int)in_r0 + 8) = 0xfd;
  *(undefined *)((int)in_r0 + 9) = 0xfe;
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void nwkRouteDiscTabInit(void)

{
  int iVar1;

  iVar1 = 0;
  do
  {
    nwkRouteDiscTabEntryRst();
    iVar1 = iVar1 + 1;
  } while (iVar1 != 10);
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void nwkRouteRecordCmdHandler(void)

{
  zb_buf_t *in_r0;
  u16 *in_r1;
  int in_r2;

  if (*in_r1 == g_zbInfo.nwkNib.nwkAddr)
  {
    if ((int)((uint)g_zbInfo.nwkNib._45_1_ << 0x1b) < 0)
    {
      nwkRouteRecTabEntryCreat();
    }
  }
  else if (((uint) * (byte *)(in_r2 + 8) < (uint)g_zbInfo.nwkNib.maxSourceRoute) &&
           (*(char *)(in_r1 + 3) != '\0'))
  {
    memcpy((void *)(*(int *)(in_r2 + 4) + (uint) * (byte *)(in_r2 + 8) * 2), &g_zbInfo.nwkNib.nwkAddr, 2);
    *(char *)(in_r2 + 8) = *(char *)(in_r2 + 8) + '\x01';
    nwkRouteRecordCmdSend();
    return;
  }
  zb_buf_free(in_r0);
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void nwkRouteRecordCmdSend(void)

{
  zb_buf_t *in_r0;
  undefined *puVar1;
  undefined *in_r2;
  u8 in_r3;

  puVar1 = (undefined *)tl_bufInitalloc(in_r0, (in_r2[8] + '\x01') * '\x02');
  *puVar1 = *in_r2;
  puVar1[1] = in_r2[8];
  memcpy(puVar1 + 2, *(void **)(in_r2 + 4), (uint)(byte)in_r2[8] << 1);
  (in_r0->hdr).handle = in_r3;
  nwk_fwdPacket();
  return;
}
// WARNING: Could not reconcile some variable overlaps
// WARNING: Unknown calling convention -- yet parameter storage is locked
void nwkRouteRecordInitiation(void)

{
  byte bVar1;
  u8 uVar2;
  u8 uVar3;
  bool bVar4;
  u16 in_r0;
  int iVar5;
  uint uVar6;
  u16 in_r1;
  byte bVar7;
  undefined uVar8;
  undefined uVar9;
  u16 uVar10;
  byte bVar11;
  u8 uVar12;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;
  uint uStack_40;
  u8 *puStack_3c;
  undefined4 local_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  undefined2 local_20;
  undefined local_1e;

  iVar5 = c1();
  if (iVar5 != 0)
  {
    uVar8 = 0;
    uVar9 = 0;
    uVar10 = 0;
    bVar11 = 0;
    bVar1 = 0;
    uVar3 = '\0';
    uVar12 = '\0';
    uStack_50 = 0;
    uStack_4c = 0;
    uStack_48 = 0;
    uStack_44 = 0;
    uStack_40 = 0;
    puStack_3c = (u8 *)0x0;
    local_38 = 0;
    uStack_34 = 0;
    uStack_30 = 0;
    uStack_2c = 0;
    uStack_28 = 0;
    uStack_24 = 0;
    local_20 = 0;
    local_1e = 0;
    uVar6 = 0;
    if (((int)((uint)ss_ib._62_1_ << 0x1c) < 0) && ((ss_ib._62_1_ & 7) != 0))
    {
      bVar4 = ss_keyPreconfigured();
      uVar6 = (uint)(bVar4 != false);
    }
    bVar7 = bVar11 & 0xc0 | 9;
    bVar1 = bVar1 & 0xfd | (byte)(uVar6 << 1);
    uVar2 = tl_zbExtAddrByShortAddr(in_r0, (addrExt_t)(CONCAT17(uVar12, CONCAT16(uVar3, CONCAT15(bVar1, CONCAT14(bVar11, CONCAT22(uVar10, CONCAT11(uVar9, uVar8)))))) & 0xffffffc0ffffffff | 0x900000000), (u16 *)&uStack_48);
    if (uVar2 == '\0')
    {
      bVar1 = bVar1 | 0x10;
    }
    tl_zbExtAddrByShortAddr(in_r1, (addrExt_t)CONCAT17(uVar12, CONCAT16(uVar3, CONCAT15(bVar1, CONCAT14(bVar7, CONCAT22(uVar10, CONCAT11(uVar9, uVar8)))))), (u16 *)&uStack_50);
    g_zbInfo.nwkNib.seqNum = g_zbInfo.nwkNib.seqNum + '\x01';
    uVar3 = getNwkHdrSize((nwk_hdr_t *)&stack0xffffffa8);
    uStack_40._0_2_ = CONCAT11(uVar3, uStack_40._0_1_);
    uStack_40 = uStack_40 & 0xffff0000 | (uint)(ushort)uStack_40;
    local_38 = CONCAT31(local_38._1_3_, 5);
    if (g_zbInfo.nwkNib.nwkAddr == in_r0)
    {
      uStack_30 = (uint)uStack_30._1_3_ << 8;
    }
    else
    {
      uStack_30 = CONCAT31(uStack_30._1_3_, 1);
      uStack_34 = 0x8479f6;
    }
    nwkRouteRecordCmdSend();
  }
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void nwkRouteReplyCmdHandler(void)

{
  u16 shortAddr;
  undefined2 uVar1;
  zb_buf_t *in_r0;
  tl_zb_normal_neighbor_entry_t *ptVar2;
  int iVar3;
  int iVar4;
  undefined uVar5;
  int in_r1;
  byte bVar6;
  int in_r2;
  undefined uVar7;
  char cVar8;
  bool bVar9;

  shortAddr = *(u16 *)(in_r0->buf + 0x14);
  bVar6 = in_r0->buf[0x27];
  ptVar2 = nwk_neTblGetByShortAddr(shortAddr);
  if (ptVar2 != (tl_zb_normal_neighbor_entry_t *)0x0)
  {
    ptVar2->lqi = (u8)((int)((uint)bVar6 + (uint)ptVar2->lqi) >> 1);
  }
  iVar3 = nwkRoutingTabEntryDstFind();
  if (iVar3 == 0)
  {
  LAB_0001d3a6:
    zb_buf_free(in_r0);
  }
  else
  {
    uVar5 = (undefined)shortAddr;
    uVar7 = (undefined)(shortAddr >> 8);
    if (*(u16 *)(in_r2 + 0x14) == g_zbInfo.nwkNib.nwkAddr)
    {
      zb_buf_free(in_r0);
      iVar4 = nwkRouteDiscEntryFind();
      if (iVar4 == 0)
      {
        if (*(char *)(iVar3 + 4) == '\x04')
        {
          return;
        }
        if (*(char *)(iVar3 + 4) == '\0')
        {
          return;
        }
        *(undefined *)(iVar3 + 4) = 2;
        return;
      }
      cVar8 = *(char *)(iVar3 + 4);
      if (cVar8 == '\x01')
      {
        *(char *)(iVar3 + 4) = (char)((((uint) * (byte *)(iVar3 + 5) << 0x1c) >> 0x1f) << 2);
        *(undefined *)(iVar3 + 2) = uVar5;
        *(undefined *)(iVar3 + 3) = uVar7;
        *(undefined *)(iVar3 + 6) = *(undefined *)(in_r2 + 0x1a);
        *(undefined *)(iVar4 + 0x12) = *(undefined *)(in_r2 + 0x1a);
        cVar8 = *(char *)(iVar3 + 4);
        bVar9 = true;
      }
      else
      {
        if ((cVar8 != '\x04') && (cVar8 != '\0'))
        {
          return;
        }
        bVar6 = *(byte *)(in_r2 + 0x1a);
        bVar9 = false;
        if (bVar6 < *(byte *)(iVar4 + 0x12))
        {
          bVar9 = *(u16 *)(iVar3 + 2) != shortAddr;
          if (bVar9)
          {
            *(undefined *)(iVar3 + 2) = uVar5;
            *(undefined *)(iVar3 + 3) = uVar7;
            bVar6 = *(byte *)(in_r2 + 0x1a);
          }
          *(byte *)(iVar4 + 0x12) = bVar6;
          *(undefined *)(iVar3 + 6) = *(undefined *)(in_r2 + 0x1a);
          cVar8 = *(char *)(iVar3 + 4);
        }
      }
      if (cVar8 == '\0')
      {
        nwkDiscDataPendSend();
      }
    }
    else
    {
      iVar4 = nwkRouteDiscEntryFind();
      if ((iVar4 == 0) || (*(byte *)(iVar4 + 0x12) < *(byte *)(in_r2 + 0x1a)))
        goto LAB_0001d3a6;
      if (*(char *)(iVar3 + 4) == '\x01')
      {
        *(char *)(iVar3 + 4) = (char)((((uint) * (byte *)(iVar3 + 5) << 0x1c) >> 0x1f) << 2);
      }
      bVar9 = *(u16 *)(iVar3 + 2) != shortAddr;
      if (bVar9)
      {
        *(undefined *)(iVar3 + 2) = uVar5;
        *(undefined *)(iVar3 + 3) = uVar7;
      }
      *(undefined *)(iVar4 + 0x12) = *(undefined *)(in_r2 + 0x1a);
    }
    if ((bVar9) && ((int)((uint) * (byte *)(iVar3 + 5) << 0x1c) < 0))
    {
      if (*(u16 *)(in_r2 + 0x14) == g_zbInfo.nwkNib.nwkAddr)
      {
        *(undefined *)(iVar4 + 0xe) = 1;
        *(undefined *)(iVar4 + 0xf) = 0;
      }
      else
      {
        *(undefined *)(iVar4 + 0xe) = 10;
        *(undefined *)(iVar4 + 0xf) = 0;
      }
    }
    if (*(u16 *)(in_r2 + 0x14) != g_zbInfo.nwkNib.nwkAddr)
    {
      in_r0->buf[0] = *(u8 *)(in_r1 + 6);
      in_r0->buf[1] = *(u8 *)(in_r2 + 0x19);
      memcpy(in_r0->buf + 2, (void *)(in_r2 + 0x14), 2);
      memcpy(in_r0->buf + 4, (void *)(in_r2 + 0x16), 2);
      memcpy(in_r0->buf + 6, (void *)(iVar4 + 10), 2);
      in_r0->buf[8] = *(char *)(iVar4 + 0x13) + *(char *)(iVar4 + 0x12);
      tl_zbTaskPost(nwkRouteReplySendDelay, in_r0);
      if ((((int)((uint)g_zbInfo.nwkNib._45_1_ << 0x1e) < 0) &&
           (iVar3 = nwkRoutingTabEntryFind(), iVar3 == 0)) &&
          (iVar3 = nwkRoutingTabEntryCreate(), iVar3 != 0))
      {
        uVar1 = *(undefined2 *)(iVar4 + 10);
        *(char *)(iVar3 + 2) = (char)uVar1;
        *(char *)(iVar3 + 3) = (char)((ushort)uVar1 >> 8);
        *(undefined *)(iVar3 + 4) = 0;
      }
    }
  }
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void nwkRouteReplyCmdSend(void)

{
  zb_buf_t *in_r0;
  undefined *puVar1;
  undefined *out;
  char cVar2;
  undefined *in_r2;
  u8 in_r3;
  uint uVar3;

  cVar2 = '\b';
  if ((int)((uint)(byte)in_r2[0x18] << 0x1b) < 0)
  {
    cVar2 = '\x10';
  }
  puVar1 = (undefined *)
      tl_bufInitalloc(in_r0, (char)((int)((uint)(byte)in_r2[0x18] << 0x1a) >> 0x1f) * -8 + cVar2);
  *puVar1 = *in_r2;
  puVar1[1] = in_r2[0x18];
  puVar1[2] = in_r2[0x19];
  memcpy(puVar1 + 3, in_r2 + 0x14, 2);
  memcpy(puVar1 + 5, in_r2 + 0x16, 2);
  puVar1[7] = in_r2[0x1a];
  out = puVar1 + 8;
  uVar3 = (uint)(byte)in_r2[0x18];
  if ((int)(uVar3 << 0x1b) < 0)
  {
    memcpy(out, in_r2 + 4, 8);
    out = puVar1 + 0x10;
    uVar3 = (uint)(byte)in_r2[0x18];
  }
  if ((int)(uVar3 << 0x1a) < 0)
  {
    memcpy(out, in_r2 + 0xc, 8);
  }
  (in_r0->hdr).handle = in_r3;
  nwk_tx();
  return;
}
// WARNING: Could not reconcile some variable overlaps
// WARNING: Unknown calling convention -- yet parameter storage is locked
void nwkRouteReplySend(void)

{
  u8 uVar1;
  bool bVar2;
  uint uVar3;
  char in_r1;
  byte in_r2;
  undefined2 in_stack_00000004;
  nwk_hdr_t local_60;
  undefined4 local_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  ushort local_28;
  undefined local_26;

  local_60._0_4_ = 0;
  local_60._4_4_ = 0;
  local_60.dstIeeeAddr._0_4_ = 0;
  local_60.dstIeeeAddr._4_4_ = 0;
  local_60.srcIeeeAddr._0_4_ = 0;
  local_60.srcIeeeAddr._4_4_ = 0;
  local_60._24_4_ = 0;
  local_60.srcRouteSubFrame.relayList = (u8 *)0x0;
  local_40 = 0;
  uStack_3c = 0;
  uStack_38 = 0;
  uStack_34 = 0;
  uStack_30 = 0;
  uStack_2c = 0;
  local_28 = 0;
  local_26 = 0;
  uVar3 = 0;
  if (((int)((uint)ss_ib._62_1_ << 0x1c) < 0) && ((ss_ib._62_1_ & 7) != 0))
  {
    bVar2 = ss_keyPreconfigured();
    uVar3 = (uint)(bVar2 != false);
  }
  local_60._0_4_ = CONCAT22(g_zbInfo.nwkNib.nwkAddr, in_stack_00000004);
  if (in_r1 == '\0')
  {
    in_r1 = '\x01';
  }
  local_60._4_4_ =
      CONCAT13(g_zbInfo.nwkNib.seqNum,
               CONCAT12(in_r1, CONCAT11((byte)(local_60._4_4_ >> 8) & 0xfd | (byte)(uVar3 << 1),
                                        (char)local_60._4_4_))) &
          0xffffffc0 |
      9;
  g_zbInfo.nwkNib.seqNum = g_zbInfo.nwkNib.seqNum + '\x01';
  uVar1 = getNwkHdrSize(&local_60);
  local_60._24_2_ = CONCAT11(uVar1, local_60.mcaseControl);
  local_60._24_4_ = local_60._24_4_ & 0xffff0000 | (uint)local_60._24_2_;
  local_40 = CONCAT31(local_40._1_3_, 2);
  local_28 = local_28 & 0xff | (ushort)in_r2 << 8;
  nwkRouteReplyCmdSend();
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void nwkRouteReplySendDelay(void)

{
  int in_r0;
  undefined local_26[2];
  undefined local_24[2];
  undefined local_22[2];

  memcpy(local_22, (void *)(in_r0 + 2), 2);
  memcpy(local_24, (void *)(in_r0 + 4), 2);
  memcpy(local_26, (void *)(in_r0 + 6), 2);
  nwkRouteReplySend();
  return;
}
// WARNING: Could not reconcile some variable overlaps
// WARNING: Unknown calling convention -- yet parameter storage is locked
u8 nwkRouteReqCmdHandler(void)

{
  byte bVar1;
  void *out;
  undefined2 uVar2;
  byte bVar3;
  u8 uVar4;
  zb_buf_t *in_r0;
  tl_zb_normal_neighbor_entry_t *ptVar5;
  void **ppvVar6;
  undefined *arg;
  int iVar7;
  u32 uVar8;
  ev_timer_event_t *peVar9;
  void *in_r1;
  uint uVar10;
  int in_r2;
  byte bVar11;
  undefined *puVar12;
  byte bVar13;
  undefined uStack_34;
  int iStack_2c;
  undefined2 local_26;

  local_26 = *(u16 *)(in_r0->buf + 0x14);
  bVar3 = in_r0->buf[0x27];
  ptVar5 = nwk_neTblGetByShortAddr(local_26);
  if (ptVar5 != (tl_zb_normal_neighbor_entry_t *)0x0)
  {
    bVar3 = (byte)((uint)bVar3 + (uint)ptVar5->lqi >> 1);
    ptVar5->lqi = bVar3;
  }
  bVar3 = rf_lqi2cost(bVar3);
  if (NWK_COST_THRESHOLD_ONEHOP < bVar3)
    goto LAB_0001d064;
  bVar11 = g_zbInfo.nwkNib._45_1_ & 2;
  bVar13 = bVar3;
  if ((g_zbInfo.nwkNib._45_1_ & 2) == 0)
  {
    uVar10 = (uint) * (byte *)(in_r2 + 0xc);
  LAB_0001cef4:
    bVar3 = *(char *)(in_r2 + 0x10) + bVar13;
    iStack_2c = 0;
    if ((uVar10 & 0x18) == 0)
      goto LAB_0001d0b8;
  }
  else
  {
    uVar10 = (uint) * (byte *)(in_r2 + 0xc);
    if ((int)(uVar10 << 0x19) < 0)
      goto LAB_0001cef4;
    if (ptVar5 != (tl_zb_normal_neighbor_entry_t *)0x0)
    {
      bVar1 = ptVar5->outgoingCost;
      bVar13 = 7;
      if ((bVar1 != 0) && (bVar13 = bVar3, bVar3 < bVar1))
      {
        bVar13 = bVar1;
      }
      goto LAB_0001cef4;
    }
    if ((*(byte *)(in_r2 + 0xc) & 0x18) != 0)
      goto LAB_0001d064;
    bVar3 = *(char *)(in_r2 + 0x10) + 7;
    bVar13 = 7;
  LAB_0001d0b8:
    iVar7 = nwkRouteReqDstChk();
    if (iVar7 == 0)
    {
      iStack_2c = nwkRoutingTabEntryDstFind();
      if (iStack_2c != 0)
      {
        if ((int)((uint) * (byte *)(iStack_2c + 5) << 0x1c) < 0)
        {
          if ((int)((uint) * (byte *)(in_r2 + 0xc) << 0x19) < 0)
          {
          LAB_0001d0f6:
            if ((*(char *)(iStack_2c + 4) != '\x04') && (*(char *)(iStack_2c + 4) != '\0'))
            {
              *(undefined *)(iStack_2c + 4) = 1;
            }
            *(byte *)(iStack_2c + 5) = *(byte *)(iStack_2c + 5) & 0xf;
            bVar11 = g_zbInfo.nwkNib._45_1_ & 2;
            goto LAB_0001cf08;
          }
        }
        else if (-1 < (int)((uint) * (byte *)(in_r2 + 0xc) << 0x19))
          goto LAB_0001d0f6;
      }
      if (((g_zbNwkCtx._45_1_ & 0x80) == 0) ||
          (iStack_2c = nwkRoutingTabEntryCreate(), iStack_2c == 0))
        goto LAB_0001d064;
      *(byte *)(iStack_2c + 5) =
          *(byte *)(iStack_2c + 5) & 0xf7 |
          (byte)((((uint) * (byte *)(in_r2 + 0xc) << 0x19) >> 0x1f) << 3);
      bVar11 = g_zbInfo.nwkNib._45_1_ & 2;
    }
    else
    {
      bVar11 = g_zbInfo.nwkNib._45_1_ & 2;
      iStack_2c = 0;
    }
  }
LAB_0001cf08:
  puVar12 = (undefined *)0x0;
  if ((bVar11 != 0) && (-1 < (int)((uint) * (byte *)(in_r2 + 0xc) << 0x19)))
  {
    puVar12 = (undefined *)nwkRoutingTabEntryDstFind();
    if ((puVar12 == (undefined *)0x0) &&
        (puVar12 = (undefined *)nwkRoutingTabEntryCreate(), puVar12 == (undefined *)0x0))
    {
      if ((iStack_2c != 0) && (*(char *)(iStack_2c + 4) == '\x01'))
      {
        *(undefined *)(iStack_2c + 4) = 3;
      }
      goto LAB_0001d064;
    }
    puVar12[5] = puVar12[5] & 0xf;
  }
  ppvVar6 = (void **)nwkRouteDiscEntryFind();
  if (ppvVar6 == (void **)0x0)
  {
    arg = (undefined *)nwkRouteDiscEntryCreate();
    if (arg == (undefined *)0x0)
    {
      iVar7 = nwkRouteReqDstChk();
      if (iVar7 == 0)
      {
        if ((iStack_2c != 0) && (*(char *)(iStack_2c + 4) == '\x01'))
        {
          *(undefined *)(iStack_2c + 4) = 3;
        }
        if ((puVar12 != (undefined *)0x0) && (puVar12[4] == '\x01'))
        {
          puVar12[4] = 3;
        }
        goto LAB_0001d064;
      }
    }
    else
    {
      iVar7 = nwkRouteReqDstChk();
      if ((((iVar7 == 0) && (*(char *)((int)in_r1 + 6) != '\0')) &&
           (uVar4 = ev_timer_enough(), uVar4 != '\0')) &&
          (iVar7 = nwkRouteDiscCachePacketCopy(), iVar7 != 0))
      {
        uVar8 = drv_u32Rand();
        uVar10 = uVar8 & 0x7f;
        uStack_34 = (undefined)iVar7;
        *arg = uStack_34;
        arg[1] = (char)((uint)iVar7 >> 8);
        arg[2] = (char)((uint)iVar7 >> 0x10);
        arg[3] = (char)((uint)iVar7 >> 0x18);
        if (uVar10 < 2)
        {
          uVar10 = 2;
        }
        peVar9 = ev_timer_taskPost(nwkRouteReqRetry, arg, (uVar10 << 0x10) >> 0xf);
        arg[4] = (char)peVar9;
        arg[5] = (char)((uint)peVar9 >> 8);
        arg[6] = (char)((uint)peVar9 >> 0x10);
        arg[7] = (char)((uint)peVar9 >> 0x18);
      }
    }
  }
  else
  {
    if (*(byte *)((int)ppvVar6 + 0x11) <= bVar3)
      goto LAB_0001d064;
    *(byte *)((int)ppvVar6 + 0x13) = bVar13;
    *(byte *)((int)ppvVar6 + 0x11) = bVar3;
    *(undefined *)((int)ppvVar6 + 10) = (undefined)local_26;
    *(undefined *)((int)ppvVar6 + 0xb) = local_26._1_1_;
    out = *ppvVar6;
    if (out != (void *)0x0)
    {
      memcpy(out, in_r1, 0x20);
      memcpy((void *)((int)out + 0x20), (void *)(in_r2 + 4), 0xd);
    }
  }
  if (puVar12 != (undefined *)0x0)
  {
    uVar2 = *(undefined2 *)((int)in_r1 + 2);
    *puVar12 = (char)uVar2;
    puVar12[1] = (char)((ushort)uVar2 >> 8);
    puVar12[2] = (undefined)local_26;
    puVar12[3] = local_26._1_1_;
    puVar12[4] = 0;
    if ((*(byte *)(in_r2 + 0xc) & 0x18) != 0)
    {
      puVar12[5] = puVar12[5] | 2;
      puVar12[5] = puVar12[5] | 4;
      bVar11 = *(byte *)(in_r2 + 0xc) & 0x18;
      bVar3 = bVar11 - 0x10;
      puVar12[5] = puVar12[5] & 0xfe | bVar3 + ~bVar3 + (0xf < bVar11);
    }
  }
  iVar7 = nwkRouteReqDstChk();
  if (iVar7 != 0)
  {
    in_r0->buf[0] = g_zbInfo.nwkNib.maxDepth << 1;
    in_r0->buf[1] = *(u8 *)(in_r2 + 0xd);
    memcpy(in_r0->buf + 2, (void *)((int)in_r1 + 2), 2);
    memcpy(in_r0->buf + 4, (void *)(in_r2 + 0xe), 2);
    memcpy(in_r0->buf + 6, &local_26, 2);
    in_r0->buf[8] = bVar13;
    uVar4 = tl_zbTaskPost(nwkRouteReplySendDelay, in_r0);
    return uVar4;
  }
LAB_0001d064:
  uVar4 = zb_buf_free(in_r0);
  return uVar4;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
// WARNING: Unknown calling convention -- yet parameter storage is locked
// WARNING: Unknown calling convention -- yet parameter storage is locked
// WARNING: Unknown calling convention -- yet parameter storage is locked
// WARNING: Unknown calling convention -- yet parameter storage is locked
void nwkRouteReqCmdSend(void)

{
  zb_buf_t *in_r0;
  undefined *puVar1;
  undefined *in_r2;
  u8 in_r3;
  u8 size;

  size = '\x06';
  if ((int)((uint)(byte)in_r2[0xc] << 0x1a) < 0)
  {
    size = '\x0e';
  }
  puVar1 = (undefined *)tl_bufInitalloc(in_r0, size);
  *puVar1 = *in_r2;
  puVar1[1] = in_r2[0xc];
  puVar1[2] = in_r2[0xd];
  memcpy(puVar1 + 3, in_r2 + 0xe, 2);
  puVar1[5] = in_r2[0x10];
  if ((int)((uint)(byte)in_r2[0xc] << 0x1a) < 0)
  {
    memcpy(puVar1 + 6, in_r2 + 4, 8);
  }
  (in_r0->hdr).handle = in_r3;
  nwk_fwdPacket();
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
// WARNING: Could not reconcile some variable overlaps
// WARNING: Unknown calling convention -- yet parameter storage is locked
void nwkRouteReqConcentInitiation(void)

{
  u8 uVar1;
  u8 uVar2;
  bool bVar3;
  uint uVar4;
  int iVar5;
  u16 *in_r1;
  int in_r2;
  byte bVar6;
  byte bVar7;
  char cVar8;
  undefined uVar9;
  undefined uVar10;
  u16 uVar11;
  u8 uVar12;
  undefined4 uStack_48;
  undefined4 uStack_44;
  uint uStack_40;
  u8 *puStack_3c;
  undefined4 local_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  uint uStack_2c;
  uint uStack_28;
  undefined4 uStack_24;
  undefined2 local_20;
  undefined local_1e;

  bVar6 = 0;
  bVar7 = 0;
  uStack_48 = 0;
  uStack_44 = 0;
  uStack_40 = 0;
  puStack_3c = (u8 *)0x0;
  local_38 = 0;
  uStack_34 = 0;
  uStack_30 = 0;
  uStack_2c = 0;
  uStack_28 = 0;
  uStack_24 = 0;
  local_20 = 0;
  local_1e = 0;
  uVar4 = 0;
  if (((int)((uint)ss_ib._62_1_ << 0x1c) < 0) && ((ss_ib._62_1_ & 7) != 0))
  {
    bVar3 = ss_keyPreconfigured();
    uVar4 = (uint)(bVar3 != false);
  }
  bVar6 = bVar6 & 0xc0 | 9;
  bVar7 = bVar7 & 0xfd | (byte)(uVar4 << 1) | 0x10;
  uVar9 = 0xfb;
  uVar10 = 0xff;
  uVar11 = g_zbInfo.nwkNib.nwkAddr;
  memcpy(&uStack_48, g_zbInfo.macPib.extAddress, 8);
  uVar2 = g_zbInfo.nwkNib.concentratorRadius;
  if (*(char *)(in_r1 + 1) != '\0')
  {
    uVar2 = *(u8 *)((int)in_r1 + 3);
  }
  if (uVar2 == '\0')
  {
    uVar2 = (u8)(((uint)g_zbInfo.nwkNib.maxDepth << 0x19) >> 0x18);
  }
  uVar12 = g_zbInfo.nwkNib.seqNum;
  g_zbInfo.nwkNib.seqNum = g_zbInfo.nwkNib.seqNum + '\x01';
  uVar1 = getNwkHdrSize((nwk_hdr_t *)&stack0xffffffa8);
  uStack_40._0_2_ = CONCAT11(uVar1, uStack_40._0_1_);
  uStack_40 = uStack_40 & 0xffff0000 | (uint)(ushort)uStack_40;
  local_38 = CONCAT31(local_38._1_3_, 1);
  cVar8 = *(char *)(in_r1 + 1);
  if (cVar8 == '\0')
  {
    uStack_2c = (uint)(byte)((byte)uStack_2c & 0xe7 |
                             (byte)((2 - ((uint) * (byte *)(in_r1 + 2) + ~(uint) * (byte *)(in_r1 + 2) +
                                          1) &
                                     3)
                                    << 3));
  }
  else if (cVar8 == '\x02')
  {
    uVar2 = zb_address_ieee_by_short(*in_r1, (addrExt_t)
                                                 CONCAT17(uVar12, CONCAT16(uVar2, CONCAT15(bVar7, CONCAT14(bVar6, CONCAT22(
                                                                                                                      uVar11, CONCAT11(uVar10, uVar9)))))));
    if (((uVar2 == '\0') && (iVar5 = memcmp(&uStack_34, &g_zero_addr, 8), iVar5 != 0)) &&
        (iVar5 = memcmp(&uStack_34, &g_invalid_addr, 8), iVar5 != 0))
    {
      uStack_2c = (uint)((byte)uStack_2c | 0x20);
    }
    cVar8 = *(char *)(in_r1 + 1);
  }
  uStack_2c = CONCAT22(*(undefined2 *)(in_r2 + 0xc),
                       CONCAT11(*(undefined *)(in_r2 + 0x10),
                                (byte)uStack_2c & 0xbf |
                                    ((cVar8 - 1U) + ~(cVar8 - 1U) + (cVar8 != '\0')) * '@'));
  uStack_28 = uStack_28 & 0xffffff00;
  nwkRouteReqCmdSend();
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
int nwkRouteReqDstChk(void)

{
  u16 in_r0;
  tl_zb_normal_neighbor_entry_t *ptVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;

  iVar2 = 1;
  if (g_zbInfo.nwkNib.nwkAddr != in_r0)
  {
    ptVar1 = nwk_neTblGetByShortAddr(in_r0);
    iVar2 = 0;
    if (ptVar1 != (tl_zb_normal_neighbor_entry_t *)0x0)
    {
      uVar3 = (byte)ptVar1->field_0x1e & 0x7e;
      uVar4 = uVar3 - 0x14;
      iVar2 = uVar4 + ~uVar4 + (uint)(0x13 < uVar3);
    }
  }
  return iVar2;
}
// WARNING: Could not reconcile some variable overlaps
// WARNING: Unknown calling convention -- yet parameter storage is locked
undefined4 nwkRouteReqInitialRetry(void)

{
  byte bVar1;
  u8 uVar2;
  zb_buf_t **in_r0;
  void *out;
  undefined4 uVar3;
  undefined auStack_54[32];
  undefined4 local_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  uint uStack_24;
  undefined4 uStack_20;
  undefined2 local_1c;
  undefined local_1a;

  uVar2 = NWKC_INITIAL_RREQ_RETRIES;
  local_34 = 0;
  uStack_30 = 0;
  uStack_2c = 0;
  uStack_28 = 0;
  uStack_24 = 0;
  uStack_20 = 0;
  local_1c = 0;
  local_1a = 0;
  bVar1 = *(byte *)(in_r0 + 5);
  *(byte *)(in_r0 + 5) = bVar1 + 1;
  if (uVar2 < bVar1)
  {
    if (*in_r0 != (zb_buf_t *)0x0)
    {
      zb_buf_free(*in_r0);
      *(undefined *)in_r0 = 0;
      *(undefined *)((int)in_r0 + 1) = 0;
      *(undefined *)((int)in_r0 + 2) = 0;
      *(undefined *)((int)in_r0 + 3) = 0;
    }
    *(undefined *)(in_r0 + 1) = 0;
    *(undefined *)((int)in_r0 + 5) = 0;
    *(undefined *)((int)in_r0 + 6) = 0;
    *(undefined *)((int)in_r0 + 7) = 0;
    uVar3 = 0xfffffffe;
  }
  else
  {
    uVar3 = 0;
    if ((*in_r0 != (zb_buf_t *)0x0) && (out = (void *)c1(), out != (void *)0x0))
    {
      memcpy(out, *in_r0, 0xc3);
      memcpy(auStack_54, out, 0x20);
      memcpy(&uStack_30, (void *)((int)out + 0x20), 0xd);
      local_34 = CONCAT31(local_34._1_3_, 1);
      uStack_24 = uStack_24 & 0xffffff00 | (uint) * (byte *)((int)in_r0 + 0x11);
      nwkRouteReqCmdSend();
    }
  }
  return uVar3;
}
// WARNING: Could not reconcile some variable overlaps
// WARNING: Unknown calling convention -- yet parameter storage is locked
undefined4 nwkRouteReqRetry(void)

{
  byte bVar1;
  u8 uVar2;
  zb_buf_t **in_r0;
  void *out;
  undefined4 uVar3;
  undefined auStack_54[32];
  undefined4 local_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  uint uStack_24;
  undefined4 uStack_20;
  undefined2 local_1c;
  undefined local_1a;

  uVar2 = NWKC_RREQ_RETRIES;
  local_34 = 0;
  uStack_30 = 0;
  uStack_2c = 0;
  uStack_28 = 0;
  uStack_24 = 0;
  uStack_20 = 0;
  local_1c = 0;
  local_1a = 0;
  bVar1 = *(byte *)(in_r0 + 5);
  *(byte *)(in_r0 + 5) = bVar1 + 1;
  if (uVar2 < bVar1)
  {
    if (*in_r0 != (zb_buf_t *)0x0)
    {
      zb_buf_free(*in_r0);
      *(undefined *)in_r0 = 0;
      *(undefined *)((int)in_r0 + 1) = 0;
      *(undefined *)((int)in_r0 + 2) = 0;
      *(undefined *)((int)in_r0 + 3) = 0;
    }
    *(undefined *)(in_r0 + 1) = 0;
    *(undefined *)((int)in_r0 + 5) = 0;
    *(undefined *)((int)in_r0 + 6) = 0;
    *(undefined *)((int)in_r0 + 7) = 0;
    uVar3 = 0xfffffffe;
  }
  else
  {
    uVar3 = 0xfe;
    if ((*in_r0 != (zb_buf_t *)0x0) && (out = (void *)c1(), out != (void *)0x0))
    {
      memcpy(out, *in_r0, 0xc3);
      memcpy(auStack_54, out, 0x20);
      memcpy(&uStack_30, (void *)((int)out + 0x20), 0xd);
      local_34 = CONCAT31(local_34._1_3_, 1);
      uStack_24 = uStack_24 & 0xffffff00 | (uint) * (byte *)((int)in_r0 + 0x11);
      nwkRouteReqCmdSend();
    }
  }
  return uVar3;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void nwkTxDataRouteDiscStart(void)

{
  nwkRouteDiscStart();
  return;
}
void tl_zbNwkNlmeRouteDiscRequestHandler(void *arg)

{
  undefined uVar1;
  aps_group_tbl_ent_t *paVar2;
  undefined uVar3;
  u16 local_18;
  char cStack_16;

  memcpy(&local_18, arg, 5);
  if ((int)((uint)(byte)g_zbInfo.nwkNib.capabilityInfo << 0x1e) < 0)
  {
    if (cStack_16 != '\0')
    {
      if ((local_18 & 0xfff8) == 0xfff8)
      {
        uVar3 = 0xc;
        uVar1 = 0xc2;
        goto LAB_0001ce20;
      }
      if (cStack_16 == '\x02')
      {
        if (local_18 == g_zbInfo.nwkNib.nwkAddr)
          goto LAB_0001ce0a;
      }
      else if ((cStack_16 == '\x01') &&
               (paVar2 = aps_group_search_by_addr(local_18), paVar2 != (aps_group_tbl_ent_t *)0x0))
      {
      LAB_0001ce0a:
        uVar3 = 0;
        uVar1 = 0;
        goto LAB_0001ce20;
      }
    LAB_0001ce18:
      uVar1 = nwkRouteDiscStart();
      uVar3 = 0;
      goto LAB_0001ce20;
    }
    if ((int)((uint)g_zbInfo.nwkNib._45_1_ << 0x1b) < 0)
      goto LAB_0001ce18;
  }
  uVar3 = 4;
  uVar1 = 0xc2;
LAB_0001ce20:
  *(undefined *)arg = uVar1;
  *(undefined *)((int)arg + 1) = uVar3;
  tl_zbTaskPost(zdo_routeDiscCnf, arg);
  return;
}
