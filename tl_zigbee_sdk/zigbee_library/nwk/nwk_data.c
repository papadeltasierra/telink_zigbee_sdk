// WARNING: Unknown calling convention -- yet parameter storage is locked
void nwkNldeDataCnf(void)

{
  void *in_r0;
  undefined in_r1;
  undefined in_r2;

  *(undefined *)((int)in_r0 + 5) = in_r2;
  *(undefined *)((int)in_r0 + 4) = in_r1;
  tl_zbTaskPost(aps_nwk_data_confirm_cb, in_r0);
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void nwkNldeDataInd(void)

{
  byte bVar1;
  undefined4 *in_r0;
  undefined2 *in_r1;
  int local_20;
  char cStack_1c;
  char cStack_1b;
  byte bStack_1a;
  undefined uStack_19;
  undefined2 uStack_18;
  undefined2 uStack_16;
  undefined4 uStack_14;
  undefined2 uStack_10;

  uStack_14 = 0;
  bVar1 = *(byte *)((int)in_r1 + 5) & 1;
  cStack_1b = bVar1 + ~bVar1 + '\x01';
  uStack_18 = *in_r1;
  uStack_16 = in_r1[1];
  cStack_1c = *(char *)((int)in_r0 + 0x1d) - *(byte *)((int)in_r1 + 0x19);
  local_20 = in_r0[1] + (uint) * (byte *)((int)in_r1 + 0x19);
  uStack_19 = *(undefined *)((int)in_r0 + 0x27);
  uStack_10 = *(undefined2 *)(in_r0 + 5);
  if ((int)((uint)g_zbInfo.nwkNib._45_1_ << 0x19) < 0)
  {
    uStack_14 = *in_r0;
  }
  bStack_1a = (byte)(((uint) * (byte *)((int)in_r1 + 5) << 0x1e) >> 0x1f);
  memcpy(in_r0, &local_20, 0x12);
  if (g_nwkDataIndCb != 0)
  {
    FUNCCCCA();
  }
  tl_zbTaskPost(aps_nwk_data_indication_cb, in_r0);
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void nwk_fwdPacket(void)

{
  byte bVar1;
  byte bVar2;
  u8 uVar3;
  zb_buf_t *in_r0;
  int **ppiVar4;
  int iVar5;
  tl_zb_normal_neighbor_entry_t *ptVar6;
  u8 *pBuf;
  ushort *in_r1;
  char *in_r2;
  byte bVar7;
  int iVar8;
  zb_buf_t **ppzVar9;
  uint uVar10;

  if (in_r0 == (zb_buf_t *)0x0)
  {
    sys_exceptionPost(0x29c, '\x13');
    return;
  }
  bVar1 = (in_r0->hdr).handle;
  if (*(char *)(in_r1 + 3) == '\0')
  {
    sys_exceptionPost(0x2ad, '4');
    return;
  }
  if (-1 < (int)((uint)(byte)(in_r0->hdr).field_0x3 << 0x1f))
  {
    sys_exceptionPost(0x2b2, '\x13');
    return;
  }
  if (((((*(byte *)(in_r1 + 2) & 3) == 0) && (bVar1 != 0xc1)) ||
       ((ppzVar9 = (zb_buf_t **)0x0, (*(byte *)(in_r1 + 2) & 3) == 1 && ((byte)(bVar1 + 0x3b) < 2)))) &&
      (ppzVar9 = (zb_buf_t **)nwkTxDataPendTabEntryAdd(), in_r0 == *ppzVar9))
  {
    sys_exceptionPost(0x2be, '4');
  }
  if ((*in_r1 & 0xfff8) == 0xfff8)
  {
    if (((*(byte *)(in_r1 + 2) & 3) != 1) || ((*in_r2 != '\b' && (*in_r2 != '\x01'))))
    {
      if ((in_r1[1] != g_zbInfo.nwkNib.nwkAddr) || (*(char *)(in_r1 + 3) != '\x01'))
      {
        ppiVar4 = (int **)nwkBrcTransEntryFind();
        if (ppiVar4 != (int **)0x0)
        {
          if (bVar1 != 0xc1)
          {
            *(char *)ppiVar4 = (char)ppzVar9;
            *(char *)((int)ppiVar4 + 1) = (char)((uint)ppzVar9 >> 8);
            *(char *)((int)ppiVar4 + 2) = (char)((uint)ppzVar9 >> 0x10);
            *(char *)((int)ppiVar4 + 3) = (char)((uint)ppzVar9 >> 0x18);
          }
          else
          {
          LAB_000173c6:
            ppzVar9 = (zb_buf_t **)*ppiVar4;
          }
          if ((ppzVar9 != (zb_buf_t **)0x0) && (ppiVar4[1] == (int *)0x0))
          {
            uVar3 = ev_timer_enough();
            if (uVar3 == '\0')
            {
              pBuf = (u8 *)((uint) * (byte *)((int)ppiVar4 + 0xb) * 0x1000000 |
                            (uint) * (uint3 *)(ppiVar4 + 2));
              if (pBuf != (u8 *)0x0)
              {
                ev_buf_free(pBuf);
                *(undefined *)(ppiVar4 + 2) = 0;
                *(undefined *)((int)ppiVar4 + 9) = 0;
                *(undefined *)((int)ppiVar4 + 10) = 0;
                *(undefined *)((int)ppiVar4 + 0xb) = 0;
              }
              nwkTxDataPendTabEntryClear();
              *(undefined *)ppiVar4 = 0;
              *(undefined *)((int)ppiVar4 + 1) = 0;
              *(undefined *)((int)ppiVar4 + 2) = 0;
              *(undefined *)((int)ppiVar4 + 3) = 0;
            }
            else
            {
              if ((*in_r1 == 0xffff) && (*(char *)((int)ppiVar4 + 0xf) == '\0'))
              {
                nwkBrcMsgAllEndDevStart();
              }
              nwkBrcMsgPassiveAckTimeoutStart();
            }
          }
          goto LAB_00017276;
        }
        if (bVar1 != 0xc0)
        {
          ppiVar4 = (int **)nwkBrcTransEntryCreate();
          if (ppiVar4 != (int **)0x0)
            goto LAB_000173c6;
          nwkTxDataPendTabEntryClear();
          if (bVar1 < 0xc0)
          {
            nwkNldeDataCnf();
            return;
          }
        }
        goto LAB_000172fe;
      }
      nwkTxDataPendTabEntryClear();
    }
  LAB_00017276:
    nwk_tx();
  }
  else
  {
    iVar5 = nwkRouteRecTabEntryFind();
    if ((iVar5 == 0) || (*(byte *)(in_r1 + 3) < 2))
    {
      if ((int)((uint) * (byte *)((int)in_r1 + 5) << 0x1d) < 0)
      {
        uVar10 = nwkSrcRouteReplayNextHop();
        if (*(char *)((int)in_r1 + 0x1b) == '\0')
        {
          nwk_neTblGetByShortAddr((u16)uVar10);
        }
        goto LAB_000172e6;
      }
      iVar5 = nwkVaildNeighborToFwd();
      if (iVar5 != 0)
      {
        iVar8 = nwkRoutingTabGetNextHop();
      LAB_00017408:
        if ((((iVar8 != 0) && ((*(byte *)(in_r1 + 2) & 3) == 0)) &&
             ((*(byte *)(iVar8 + 5) & 6) == 6)) &&
            ((ptVar6 = nwk_neTblGetByShortAddr(in_r1[1]), in_r1[1] == g_zbInfo.nwkNib.nwkAddr ||
                                                              ((ptVar6 != (tl_zb_normal_neighbor_entry_t *)0x0 &&
                                                                ((ptVar6->field_0x1e & 0x7e) == 0x14))))))
        {
          nwkRouteRecordInitiation();
          if (-1 < (int)((uint) * (byte *)(iVar8 + 5) << 0x1f))
          {
            *(byte *)(iVar8 + 5) = *(byte *)(iVar8 + 5) & 0xfb;
          }
        }
        if (iVar5 == 0)
        {
          if (iVar8 == 0)
            goto LAB_000172ee;
          uVar10 = (uint) * (ushort *)(iVar8 + 2);
        }
        else
        {
          uVar10 = (uint)*in_r1;
        }
        goto LAB_000172e6;
      }
      iVar8 = nwkRoutingTabGetNextHop();
      if (iVar8 != 0)
        goto LAB_00017408;
      if ((*(byte *)(in_r1 + 2) & 0xc0) == 0)
        goto LAB_000172ee;
      if (ppzVar9 != (zb_buf_t **)0x0)
      {
        iVar5 = nwkTxDataRouteDiscStart();
        if (iVar5 == 0)
        {
          zb_buf_free(in_r0);
          iVar5 = nwkRouteDiscEntryDstFind();
          *(byte *)((int)ppzVar9 + 0xb) = *(byte *)((int)ppzVar9 + 0xb) | 0x40;
          *(undefined *)((int)ppzVar9 + 10) = *(undefined *)(iVar5 + 0x10);
          return;
        }
        goto LAB_000172ee;
      }
    }
    else
    {
      *(byte *)((int)in_r1 + 5) = *(byte *)((int)in_r1 + 5) | 4;
      bVar2 = *(byte *)(iVar5 + 0x12);
      bVar7 = (byte)(((uint)bVar2 << 0x19) >> 0x19);
      *(byte *)(in_r1 + 0xd) = bVar7;
      if ((bVar2 & 0x7f) == 0)
      {
        *(byte *)((int)in_r1 + 0x1b) = bVar7;
        uVar10 = (uint)*in_r1;
      }
      else
      {
        *(byte *)((int)in_r1 + 0x1b) = (byte)(((uint) * (byte *)(iVar5 + 0x12) << 0x19) >> 0x19) - 1;
        iVar8 = iVar5 + 2;
        *(char *)(in_r1 + 0xe) = (char)iVar8;
        *(char *)((int)in_r1 + 0x1d) = (char)((uint)iVar8 >> 8);
        *(char *)(in_r1 + 0xf) = (char)((uint)iVar8 >> 0x10);
        *(char *)((int)in_r1 + 0x1f) = (char)((uint)iVar8 >> 0x18);
        uVar10 = (uint) * (ushort *)(iVar5 + (((uint) * (byte *)(iVar5 + 0x12) << 0x19) >> 0x18));
      }
    LAB_000172e6:
      if (uVar10 != 0xfffe)
        goto LAB_00017276;
    LAB_000172ee:
      if (ppzVar9 != (zb_buf_t **)0x0)
      {
        nwkTxDataPendTabEntryClear();
      }
    }
    if (bVar1 < 0xc0)
    {
      nwkNldeDataCnf();
      return;
    }
  LAB_000172fe:
    zb_buf_free(in_r0);
  }
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void nwk_tx(void)

{
  char cVar1;
  u16 uVar2;
  byte bVar3;
  void *in_r0;
  nwk_hdr_t *in_r1;
  uint in_r2;
  char in_r3;
  int iVar4;
  int in_stack_00000000;
  char in_stack_00000004;

  cVar1 = *(char *)((int)in_r0 + 0xc1);
  bVar3 = getNwkHdrSize(in_r1);
  in_r1->frameHdrLen = bVar3;
  iVar4 = in_stack_00000000 - (uint)bVar3;
  nwkHdrBuilder();
  memset(in_r0, 0, 0x26);
  *(undefined *)((int)in_r0 + 8) = 2;
  *(undefined *)((int)in_r0 + 0x13) = 2;
  *(char *)((int)in_r0 + 0xb) = (char)in_r2;
  *(char *)((int)in_r0 + 0xc) = (char)(in_r2 >> 8);
  uVar2 = g_zbInfo.macPib.panId;
  *(char *)((int)in_r0 + 9) = (char)g_zbInfo.macPib.panId;
  *(char *)((int)in_r0 + 10) = (char)(uVar2 >> 8);
  *(u8 *)((int)in_r0 + 0x14) = in_r1->frameHdrLen + in_stack_00000004;
  *(char *)((int)in_r0 + 0x15) = (char)iVar4;
  *(char *)((int)in_r0 + 0x16) = (char)((uint)iVar4 >> 8);
  *(char *)((int)in_r0 + 0x17) = (char)((uint)iVar4 >> 0x10);
  *(char *)((int)in_r0 + 0x18) = (char)((uint)iVar4 >> 0x18);
  *(char *)((int)in_r0 + 0x19) = cVar1;
  if ((in_r2 & 0xffff) != 0xffff)
  {
    *(undefined *)((int)in_r0 + 0x1a) = 1;
  }
  if (in_r3 != '\0')
  {
    *(byte *)((int)in_r0 + 0x1a) = *(byte *)((int)in_r0 + 0x1a) | 4;
  }
  if ((((int)((uint)g_zbNwkCtx._45_1_ << 0x1d) < 0) || (cVar1 == -0x3a)) || (cVar1 == -0x3d))
  {
    if (((int)((uint)(byte)(in_r1->framecontrol).field_0x1 << 0x1e) < 0) &&
        (iVar4 = ss_nwkSecureFrame(), iVar4 != 0))
    {
      g_sysDiags.nwkTxEnDecryptFail = g_sysDiags.nwkTxEnDecryptFail + 1;
      tl_zbMacMcpsDataRequestSendConfirm(in_r0, 0xd4);
    }
    else
    {
      g_sysDiags.nwkTxCnt = g_sysDiags.nwkTxCnt + 1;
      tl_zbMacMcpsDataRequestProc(in_r0);
    }
  }
  else
  {
    tl_zbMacMcpsDataRequestSendConfirm(in_r0, 0x19);
  }
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void tl_zbMacInterPanDataHandle(void)

{
  void *in_r0;

  tl_zbTaskPost(aps_interPanDataIndCb, in_r0);
  return;
}
// WARNING: Could not reconcile some variable overlaps
void tl_zbMacMcpsDataConfirmHandler(void *arg)

{
  byte bVar1;
  bool bVar2;
  u8 uVar3;
  int iVar4;
  tl_zb_normal_neighbor_entry_t *ptVar5;
  uint uVar6;
  uint uVar7;
  ushort local_54;
  byte bStack_4f;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined2 local_28;

  uStack_34 = 0;
  uStack_30 = 0;
  uStack_2c = 0;
  local_28 = 0;
  memcpy(&uStack_34, arg, 0xe);
  nwkHdrParse();
  if ((local_54 & 0xfff8) != 0xfff8)
  {
    iVar4 = nwkTxDataPendTabEntryFind();
    if (iVar4 != 0)
    {
      nwkTxDataPendTabEntryClear();
    }
    ptVar5 = nwk_neTblGetByShortAddr(uStack_2c._2_2_);
    uVar3 = NWKC_TRANSFAILURE_CNT_THRESHOLD;
    if (ptVar5 == (tl_zb_normal_neighbor_entry_t *)0x0)
    {
      bVar2 = false;
    }
    else
    {
      if ((ptVar5->field_0x1e & 0xe) == 4)
        goto LAB_00016f68;
      if (uStack_2c._1_1_ == '\0')
      {
        ptVar5->lqi = (u8)((int)((uint)ptVar5->lqi + (uint)local_28._1_1_) >> 1);
        ptVar5->transFailure = '\0';
        ptVar5->age = '\0';
        bVar2 = false;
      }
      else
      {
        bVar2 = false;
        if (((uStack_2c._1_1_ == -0x17) &&
             (bVar1 = ptVar5->transFailure, ptVar5->transFailure = bVar1 + 1, uVar3 <= bVar1)) &&
            (ptVar5->lqi = ptVar5->lqi >> 1, (int)((uint)bStack_4f << 0x1d) < 0))
        {
          ptVar5->transFailure = '\0';
          bVar2 = true;
        }
      }
    }
    iVar4 = nwkRoutingTabEntryDstActiveGet();
    if (iVar4 == 0)
    {
      if ((ptVar5 != (tl_zb_normal_neighbor_entry_t *)0x0) || (-1 < (int)((uint)bStack_4f << 0x1d)))
        goto LAB_00016f54;
    }
    else
    {
      if (uStack_2c._1_1_ == '\0')
      {
        *(byte *)(iVar4 + 5) = *(byte *)(iVar4 + 5) & 0xf;
      }
      else if ((uStack_2c._1_1_ == -0x17) &&
               (uVar6 = (uint)(*(byte *)(iVar4 + 5) >> 4),
                uVar7 = (uint)NWKC_TRANSFAILURE_CNT_THRESHOLD,
                *(byte *)(iVar4 + 5) = *(byte *)(iVar4 + 5) & 0xf | (byte)((uVar6 + 1 & 0xf) << 4),
                uVar7 <= uVar6))
      {
        *(byte *)(iVar4 + 5) = *(byte *)(iVar4 + 5) & 0xf;
        goto LAB_00016f58;
      }
    LAB_00016f54:
      if (!bVar2)
        goto LAB_00016f66;
    }
  LAB_00016f58:
    if (uStack_2c._1_1_ == -0x17)
    {
      nwkRouteMaintenance();
    }
  }
LAB_00016f66:
LAB_00016f68:
  if ((byte)uStack_2c < 0xc0)
  {
    nwkNldeDataCnf();
    return;
  }
  if (((byte)uStack_2c != 0xc0) && ((byte)uStack_2c != 0xc1))
  {
    if ((byte)uStack_2c == 0xc3)
    {
      nwk_rejoinCmdSendCnf();
      return;
    }
    if ((byte)uStack_2c == 0xc6)
    {
      nwk_leaveCmdSendCnf();
      return;
    }
    if (((byte)uStack_2c != 199) && ((byte)uStack_2c != 200))
    {
      if ((byte)uStack_2c == 0xc5)
      {
        zb_buf_free((zb_buf_t *)arg);
        if (uStack_2c._1_1_ != '\0')
        {
          return;
        }
        tl_zbNwkPanidConflictSetPanidStart();
        return;
      }
      if ((byte)uStack_2c == 0xc4)
      {
        tl_zbMcpsRejoinRespCnfHandler();
        return;
      }
      if (((byte)uStack_2c != 0xcb) && ((byte)uStack_2c == 0xce))
      {
        nwkEndDevTimeoutRspCnfHandler();
        return;
      }
    }
  }
  zb_buf_free((zb_buf_t *)arg);
  return;
}
// WARNING: Removing unreachable block (RAM,0x00017872)
// WARNING: Removing unreachable block (RAM,0x00017876)
// WARNING: Removing unreachable block (RAM,0x00017af8)
// WARNING: Removing unreachable block (RAM,0x000177b8)
// WARNING: Removing unreachable block (RAM,0x00017a06)
// WARNING: Removing unreachable block (RAM,0x00017ae8)
// WARNING: Removing unreachable block (RAM,0x00017af0)
// WARNING: Removing unreachable block (RAM,0x000177a6)
// WARNING: Removing unreachable block (RAM,0x0001773a)
// WARNING: Removing unreachable block (RAM,0x00017b58)
// WARNING: Removing unreachable block (RAM,0x00017b64)
// WARNING: Removing unreachable block (RAM,0x00017b62)
// WARNING: Removing unreachable block (RAM,0x00017b56)
// WARNING: Removing unreachable block (RAM,0x0001770a)
// WARNING: Removing unreachable block (RAM,0x00017718)
// WARNING: Removing unreachable block (RAM,0x0001772c)
// WARNING: Removing unreachable block (RAM,0x00017732)
// WARNING: Removing unreachable block (RAM,0x00017b46)
// WARNING: Removing unreachable block (RAM,0x00017b48)
// WARNING: Removing unreachable block (RAM,0x00017700)
// WARNING: Removing unreachable block (RAM,0x00017704)
// WARNING: Removing unreachable block (RAM,0x00017716)
// WARNING: Removing unreachable block (RAM,0x00017b86)
// WARNING: Removing unreachable block (RAM,0x00017734)
// WARNING: Removing unreachable block (RAM,0x0001773c)
// WARNING: Removing unreachable block (RAM,0x00017742)
// WARNING: Removing unreachable block (RAM,0x00017b84)
// WARNING: Removing unreachable block (RAM,0x00017832)
// WARNING: Removing unreachable block (RAM,0x0001785c)
// WARNING: Removing unreachable block (RAM,0x0001785e)
// WARNING: Removing unreachable block (RAM,0x0001774c)
// WARNING: Removing unreachable block (RAM,0x00017782)
// WARNING: Removing unreachable block (RAM,0x000178b6)
// WARNING: Removing unreachable block (RAM,0x000178ea)
// WARNING: Removing unreachable block (RAM,0x000179b0)
// WARNING: Removing unreachable block (RAM,0x000179d6)
// WARNING: Removing unreachable block (RAM,0x000178cc)
// WARNING: Removing unreachable block (RAM,0x000178e2)
// WARNING: Removing unreachable block (RAM,0x000178be)
// WARNING: Removing unreachable block (RAM,0x000178f8)
// WARNING: Removing unreachable block (RAM,0x00017900)
// WARNING: Removing unreachable block (RAM,0x00017914)
// WARNING: Removing unreachable block (RAM,0x0001794a)
// WARNING: Removing unreachable block (RAM,0x0001794c)
// WARNING: Removing unreachable block (RAM,0x00017952)
// WARNING: Removing unreachable block (RAM,0x00017950)
// WARNING: Removing unreachable block (RAM,0x0001797c)
// WARNING: Removing unreachable block (RAM,0x000179a2)
// WARNING: Removing unreachable block (RAM,0x000179a0)
// WARNING: Removing unreachable block (RAM,0x000178b4)
// WARNING: Removing unreachable block (RAM,0x00017784)
// WARNING: Removing unreachable block (RAM,0x0001778c)
// WARNING: Removing unreachable block (RAM,0x00017796)
// WARNING: Removing unreachable block (RAM,0x0001779c)
// WARNING: Removing unreachable block (RAM,0x000177a4)
// WARNING: Removing unreachable block (RAM,0x00017698)
// WARNING: Removing unreachable block (RAM,0x000176a0)
// WARNING: Removing unreachable block (RAM,0x000177ac)
// WARNING: Removing unreachable block (RAM,0x00017af2)
// WARNING: Removing unreachable block (RAM,0x00017afa)
// WARNING: Removing unreachable block (RAM,0x00017b04)
// WARNING: Removing unreachable block (RAM,0x00017b0e)
// WARNING: Removing unreachable block (RAM,0x00017b14)
// WARNING: Removing unreachable block (RAM,0x00017b22)
// WARNING: Removing unreachable block (RAM,0x00017b24)
// WARNING: Removing unreachable block (RAM,0x000177ba)
// WARNING: Removing unreachable block (RAM,0x000177c2)
// WARNING: Removing unreachable block (RAM,0x000177dc)
// WARNING: Removing unreachable block (RAM,0x000177da)
// WARNING: Removing unreachable block (RAM,0x00017a1c)
// WARNING: Removing unreachable block (RAM,0x00017a30)
// WARNING: Removing unreachable block (RAM,0x00017a2e)
// WARNING: Removing unreachable block (RAM,0x00017a38)
// WARNING: Removing unreachable block (RAM,0x00017a48)
// WARNING: Removing unreachable block (RAM,0x00017a4a)
// WARNING: Removing unreachable block (RAM,0x00017a56)
// WARNING: Removing unreachable block (RAM,0x000177de)
// WARNING: Removing unreachable block (RAM,0x000177f0)
// WARNING: Removing unreachable block (RAM,0x000177f8)
// WARNING: Removing unreachable block (RAM,0x00017816)
// WARNING: Removing unreachable block (RAM,0x00017822)
// WARNING: Removing unreachable block (RAM,0x00017824)
// WARNING: Removing unreachable block (RAM,0x000177ee)
// WARNING: Removing unreachable block (RAM,0x00017a58)
// WARNING: Removing unreachable block (RAM,0x00017b12)
// WARNING: Removing unreachable block (RAM,0x00017b0c)
// WARNING: Removing unreachable block (RAM,0x000177f6)
// WARNING: Removing unreachable block (RAM,0x00017878)
// WARNING: Removing unreachable block (RAM,0x0001787a)
// WARNING: Removing unreachable block (RAM,0x00017882)
// WARNING: Removing unreachable block (RAM,0x00017896)
// WARNING: Removing unreachable block (RAM,0x00017880)
// WARNING: Removing unreachable block (RAM,0x00017a68)
// WARNING: Removing unreachable block (RAM,0x00017a70)
// WARNING: Removing unreachable block (RAM,0x00017a7c)
// WARNING: Removing unreachable block (RAM,0x00017a88)
// WARNING: Removing unreachable block (RAM,0x00017a94)
// WARNING: Removing unreachable block (RAM,0x00017aa0)
// WARNING: Removing unreachable block (RAM,0x00017aac)
// WARNING: Removing unreachable block (RAM,0x00017ab8)
// WARNING: Removing unreachable block (RAM,0x00017ac4)
// WARNING: Removing unreachable block (RAM,0x00017ad0)
// WARNING: Removing unreachable block (RAM,0x00017adc)
// WARNING: Removing unreachable block (RAM,0x00017898)
// WARNING: Removing unreachable block (RAM,0x00017a66)
// WARNING: Recovered jumptable eliminated as dead code
// WARNING: Removing unreachable block (RAM,0x000176ca)
void tl_zbMacMcpsDataIndicationHandler(void *buf)

{
  uint uVar1;

  if (*(short *)((int)buf + 0x12) == -1)
  {
    uVar1 = ((uint) * *(byte **)((int)buf + 4) << 0x1a) >> 0x1c;
    if (uVar1 == 3)
    {
      tl_zbTaskPost(cGp_mcpsDataInd, buf);
      return;
    }
    if ((uVar1 != 2) || ((**(byte **)((int)buf + 4) & 3) != 3))
      goto switchD_00017a6e_caseD_0;
  }
  if ((((g_zbNwkCtx._47_1_ & 0xf) != 2) &&
       (uVar1 = nwkHdrParse(), uVar1 < *(byte *)((int)buf + 0x1d))) &&
      (((int)((uint)g_zbNwkCtx._45_1_ << 0x1d) < 0 || ((g_zbNwkCtx._47_1_ & 0xf) == 1))))
  {
    g_sysDiags.packetValidateDropCount = g_sysDiags.packetValidateDropCount + 1;
    zb_buf_free((zb_buf_t *)buf);
    return;
  }
switchD_00017a6e_caseD_0:
  zb_buf_free((zb_buf_t *)buf);
  return;
}
// WARNING: Could not reconcile some variable overlaps
// WARNING: Unknown calling convention -- yet parameter storage is locked
void tl_zbNwkInterPanDataReq(void)

{
  void *in_r0;
  void *out;
  undefined4 local_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  uint uStack_28;
  uint uStack_24;
  uint uStack_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined2 local_14;
  undefined2 local_10[4];

  local_38 = 0;
  uStack_34 = 0;
  uStack_30 = 0;
  uStack_2c = 0;
  uStack_28 = 0;
  uStack_1c = 0;
  uStack_18 = 0;
  local_14 = 0;
  local_10[0] = 0xb;
  out = (void *)(*(int *)((int)in_r0 + 0x10) + -2);
  uStack_20 = (uint)out >> 0x18;
  uStack_24 = (int)out * 0x100 | (uint)(byte)(*(char *)((int)in_r0 + 0x14) + 2);
  memcpy(out, local_10, 2);
  uStack_30 = CONCAT31(uStack_30._1_3_, 3);
  uStack_28 = uStack_28 & 0xffffff | (uint) * (byte *)((int)in_r0 + 0xb) << 0x18;
  if ((dstPanID == 0) || (deviceInfoRsp == '\0'))
  {
    uStack_30 = uStack_30 | 0xffff00;
    uStack_20._0_2_ = CONCAT11(*(undefined *)((int)in_r0 + 0xf), (undefined)uStack_20);
    uStack_20 = uStack_20 & 0xffff0000 | (uint)(ushort)uStack_20;
  }
  else
  {
    deviceInfoRsp = '\0';
    uStack_30 = uStack_30 & 0xff0000ff | (uint)dstPanID << 8;
    uStack_20._0_2_ = CONCAT11(*(undefined *)((int)in_r0 + 0xf), (undefined)uStack_20);
    uStack_20 = uStack_20 & 0xffff0000 | (uint)(ushort)uStack_20;
  }
  if (*(byte *)((int)in_r0 + 0xb) == 3)
  {
    uStack_20._0_3_ = CONCAT12(1, (ushort)uStack_20);
    uStack_20 = uStack_20 & 0xff000000 | (uint)(uint3)uStack_20;
    memcpy((void *)((int)&uStack_30 + 3), in_r0, 8);
  }
  else
  {
    uStack_30 = CONCAT13(0xfe, (undefined3)uStack_30);
    uStack_2c = CONCAT31(uStack_2c._1_3_, 0xfe);
  }
  memcpy(in_r0, &local_38, 0x26);
  tl_zbMacMcpsDataRequestProc(in_r0);
  return;
}
void tl_zbNwkNldeDataRequestHandler(void *arg)

{
  ushort uVar1;
  byte bVar2;

  if (((int)((uint)g_zbNwkCtx._45_1_ << 0x1d) < 0) && ((g_zbNwkCtx._47_1_ & 0xf) == 0))
  {
    uVar1 = *(ushort *)((int)arg + 8);
    if (*(ushort *)((int)arg + 8) == g_zbInfo.nwkNib.nwkAddr)
    {
      nwkNldeDataCnf();
    }
    else
    {
      *(undefined *)((int)arg + 0xc1) = *(undefined *)((int)arg + 0xf);
      bVar2 = *(char *)((int)arg + 0xb) - 1;
      if (*(char *)((int)arg + 0x15) == '\0')
      {
        g_zbInfo.nwkNib.seqNum = g_zbInfo.nwkNib.seqNum + '\x01';
      }
      if ((int)((uint)(~bVar2 + bVar2 + (*(char *)((int)arg + 0xb) != '\0') & 0xfd) << 0x1f) < 0)
      {
        aps_group_search_by_addr(*(u16 *)((int)arg + 8));
      }
      if ((*(char *)((int)arg + 0x19) == '\0') || ((uVar1 & 0xfff8) == 0xfff8))
      {
        nwk_fwdPacket();
      }
      else
      {
        nwk_tx();
      }
    }
  }
  else if (*(byte *)((int)arg + 0xf) < 0xc0)
  {
    nwkNldeDataCnf();
  }
  else
  {
    zb_buf_free((zb_buf_t *)arg);
  }
  return;
}
