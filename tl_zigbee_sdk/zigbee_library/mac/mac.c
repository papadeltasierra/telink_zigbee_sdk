
void mac_pibNvInit(char param_1)

{
  u32 uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;

  if (param_1 != '\0')
  {
    memcpy(&g_zbInfo, &macPibDefault, 0x4c);
    generateIEEEAddr();
    uVar1 = drv_u32Rand();
    g_zbInfo.macPib.seqNum = (u8)uVar1;
    uVar1 = drv_u32Rand();
    uVar3 = (uint)g_zbInfo.macPib.maxBe;
    uVar2 = (uint)g_zbInfo.macPib.minBe;
    if (uVar3 < uVar2)
    {
      uVar7 = 0;
      uVar3 = uVar2;
      g_zbInfo.macPib.maxBe = g_zbInfo.macPib.minBe;
    }
    else
    {
      uVar7 = uVar3 - uVar2;
    }
    uVar5 = (uint)g_zbInfo.macPib.maxCsmaBackoffs;
    if ((int)uVar5 < (int)uVar7)
    {
      uVar7 = uVar5;
    }
    uVar7 = uVar7 & 0xff;
    iVar4 = 0;
    if (uVar7 != 0)
    {
      iVar6 = 0;
      do
      {
        iVar4 = iVar4 + (1 << iVar6 + uVar2);
        iVar6 = iVar6 + 1;
      } while (iVar6 < (int)uVar7);
    }
    iVar4 = (((1 << uVar3) + -1) * (uVar5 - uVar7) + 1 + iVar4) * 0x1280000;
    g_zbInfo.macPib.frameTotalWaitTime._0_1_ = (undefined)((uint)iVar4 >> 0x10);
    g_zbInfo.macPib.frameTotalWaitTime._1_1_ = (undefined)((uint)iVar4 >> 0x18);
    g_zbInfo.macPib.beaconSeqNum = (u8)uVar1;
  }
  tl_zbMacChannelSet(g_zbInfo.macPib.phyChannelCur);
  return;
}
void tl_zbMacChannelSet(u8 chan)

{
  g_zbMacCtx.curChannel = chan;
  rf_setChannel(chan);
  return;
}
void tl_zbMacInit(u8 coldReset)

{
  mac_pibNvInit(coldReset);
  mac_trxInit();
  g_zbInfo.macPib.associationPermit = 0;
  g_zbMacCtx.txRawDataBuf = (u8 *)c1();
  return;
}
void tl_zbMacReset(void)

{
  mac_pibNvInit(1);
  g_zbInfo.macPib.associationPermit = 0;
  return;
}
void tl_zbMacTaskProc(void)

{
  tl_zb_task_t *ptVar1;
  int iVar2;
  undefined1 *puVar3;
  tl_zb_task_t tStack_1c;

  ptVar1 = tl_zbTaskQPop('\x02', &tStack_1c);
  if ((ptVar1 != (tl_zb_task_t *)0x0) && (tStack_1c.data != (void *)0x0))
  {
    puVar3 = g_zbMacEventFromNwkTbl;
    iVar2 = 0;
    do
    {
      if ((*puVar3 == *(char *)((int)tStack_1c.data + 0xc0)) &&
          (*(int *)(g_zbMacEventFromNwkTbl + iVar2 * 5 + 1) != 0))
      {
        tl_zbReadyToPullParentForAssoRsp();
        break;
      }
      iVar2 = iVar2 + 1;
      puVar3 = puVar3 + 5;
    } while (iVar2 != 8);
  }
  zb_macTimerEventProc();
  return;
}
void tl_zbMaxTxConfirmCb(u8 *param_1, undefined param_2)

{
  u8 uVar1;

  uVar1 = param_1[0xc1];
  if (param_1 == g_zbMacCtx.txRawDataBuf)
  {
    param_1[0xc3] = param_1[0xc3] & 0xf7;
  }
  if (uVar1 == 0xe0)
  {
    tl_zbMacAssociateRequestStatusCheck(param_1, param_2);
  }
  else if (uVar1 == 0xe1)
  {
    tl_zbMacCommStatusSend();
  }
  else if (uVar1 == 0xe2)
  {
    tl_zbMacDisassociateNotifyCmdConfirm();
  }
  else if ((byte)(uVar1 + 0x18) < 2)
  {
    tl_zbMacDataRequestStatusCheck();
  }
  else if (uVar1 == 0xe6)
  {
    tl_zbMacStartReqConfirm();
  }
  else if ((uVar1 != 0xea) && (uVar1 != 0xe4))
  {
    if (uVar1 == 0xe7)
    {
      tl_zbMacCmdPanIdConflictNotifySendCheck();
    }
    else if (uVar1 == 0xe3)
    {
      tl_zbMacMlmeBeaconSendConfirm();
    }
    else if (uVar1 == 0xe5)
    {
      tl_zbMacOrphanResponseStatusCheck();
    }
    else
    {
      tl_zbMacMcpsDataRequestSendConfirm();
    }
  }
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void tl_zbPhyIndication(void)

{
  byte bVar1;
  u8 uVar2;
  u8 uVar3;
  u8 uVar4;
  bool bVar5;
  zb_buf_t *in_r0;
  int iVar6;
  int in_r1;
  char *pcVar7;
  uint in_r2;
  uint length;
  uint uVar8;
  char *pcVar9;
  uint uVar10;
  byte bVar11;

  uVar10 = in_r2 & 0xff;
  bVar1 = **(byte **)(in_r0->buf + 4);
  bVar11 = bVar1 & 7;
  if (*(char *)(in_r1 + 2) == '\x02')
  {
    if (*(short *)(in_r1 + 8) == -1)
    {
      g_sysDiags.macRxBcast = g_sysDiags.macRxBcast + 1;
    }
    else
    {
      g_sysDiags.macRxUcast = g_sysDiags.macRxUcast + 1;
    }
  }
  if (macAppIndCb == (int *)0x0)
  {
  LAB_00011fde:
    pcVar7 = (char *)(*(int *)(in_r0->buf + 4) + uVar10);
    in_r0->buf[4] = (u8)pcVar7;
    in_r0->buf[5] = (u8)((uint)pcVar7 >> 8);
    in_r0->buf[6] = (u8)((uint)pcVar7 >> 0x10);
    in_r0->buf[7] = (u8)((uint)pcVar7 >> 0x18);
    if (bVar11 == 1)
    {
      tl_zbPhyMldeIndication();
      return;
    }
    if ((bVar1 & 7) != 0)
    {
      if (bVar11 == 3)
      {
      LAB_0001200e:
        tl_zbPhyMlmeIndicate();
        return;
      }
      goto LAB_00011fd2;
    }
  }
  else
  {
    if ((bVar1 & 7) != 0)
    {
      if (bVar11 == 3)
      {
        if (*macAppIndCb == 0)
        {
          iVar6 = *(int *)(in_r0->buf + 4) + uVar10;
          in_r0->buf[4] = (u8)iVar6;
          in_r0->buf[5] = (u8)((uint)iVar6 >> 8);
          in_r0->buf[6] = (u8)((uint)iVar6 >> 0x10);
          in_r0->buf[7] = (u8)((uint)iVar6 >> 0x18);
        }
        else
        {
          pcVar7 = (char *)(*(int *)(in_r0->buf + 4) + uVar10);
          if (*pcVar7 == '\a')
          {
            iVar6 = FUNBBBBF();
            if (iVar6 == 0)
              goto LAB_00011fd2;
            pcVar7 = (char *)(*(int *)(in_r0->buf + 4) + uVar10);
          }
          in_r0->buf[4] = (u8)pcVar7;
          in_r0->buf[5] = (u8)((uint)pcVar7 >> 8);
          in_r0->buf[6] = (u8)((uint)pcVar7 >> 0x10);
          in_r0->buf[7] = (u8)((uint)pcVar7 >> 0x18);
        }
        goto LAB_0001200e;
      }
      goto LAB_00011fde;
    }
    if (macAppIndCb[1] == 0)
      goto LAB_00011fde;
    iVar6 = FUNBBBBF();
    if (iVar6 == 0)
      goto LAB_00011fd2;
    pcVar7 = (char *)(*(int *)(in_r0->buf + 4) + uVar10);
    in_r0->buf[4] = (u8)pcVar7;
    in_r0->buf[5] = (u8)((uint)pcVar7 >> 8);
    in_r0->buf[6] = (u8)((uint)pcVar7 >> 0x10);
    in_r0->buf[7] = (u8)((uint)pcVar7 >> 0x18);
  }
  uVar10 = in_r0->buf[0x13] - uVar10;
  length = uVar10 & 0xff;
  in_r0->buf[0x13] = (u8)(uVar10 * 0x1000000 >> 0x18);
  if (g_zbInfo.macPib.autoReq == '\0')
  {
    uVar2 = in_r0->buf[0x14];
    uVar3 = in_r0->buf[0x15];
    if ((((*pcVar7 != -1) || ((pcVar7[1] & 0xfU) != 0xf)) || (pcVar7[2] != '\0')) || (length < 5))
      goto LAB_00011fd2;
    bVar1 = pcVar7[3];
    uVar10 = 4;
    if ((bVar1 & 7) != 0)
    {
      uVar10 = (bVar1 & 7) * 0x2000000 + 0x4000000 >> 0x18;
    }
    uVar8 = ((uint)bVar1 << 0x19) >> 0x1d;
    if (uVar8 != 0)
    {
      uVar10 = uVar8 * 8 + uVar10;
    }
    if (length < uVar10 + 0xf)
      goto LAB_00011fd2;
    uVar8 = length;
    if (length < 0x1e)
    {
      uVar8 = 0x1e;
    }
    if ((char *)0xc0 < pcVar7 + (length - (int)in_r0) + uVar8)
      goto LAB_00011fd2;
    pcVar9 = pcVar7 + uVar8;
    memcpy(pcVar9, pcVar7, length);
    memcpy(in_r0->buf + 6, pcVar9, 2);
    uVar4 = pcVar9[2];
    in_r0->buf[0x1e] = uVar4;
    if ((uVar4 != '\0') || ((in_r0->buf[6] & 0xf) != 0xf))
      goto LAB_00011fd2;
    memcpy(in_r0->buf + 4, (void *)(in_r1 + 0x10), 2);
    in_r0->buf[0x10] = *(u8 *)(in_r1 + 3);
    in_r0->buf[0x1f] = uVar2;
    in_r0->buf[0x1c] = uVar3;
    memcpy(in_r0->buf + 8, (void *)(in_r1 + 0x12), 8);
    in_r0->buf[0x2c] = *(u8 *)(in_r1 + 5);
    in_r0->buf[0x24] = '\0';
    in_r0->buf[0x25] = '\0';
    in_r0->buf[0x26] = '\0';
    in_r0->buf[0x27] = '\0';
    in_r0->buf[0x2e] = '\x0f';
    pcVar9 = pcVar9 + uVar10;
    in_r0->buf[0x28] = (u8)pcVar9;
    in_r0->buf[0x29] = (u8)((uint)pcVar9 >> 8);
    in_r0->buf[0x2a] = (u8)((uint)pcVar9 >> 0x10);
    in_r0->buf[0x2b] = (u8)((uint)pcVar9 >> 0x18);
    tl_zbPrimitivePost('\x01', 'L', in_r0);
    if (g_zbMacCtx.status == '\x02')
    {
      tl_zbMacActiveScanListAdd();
    }
    bVar5 = false;
    if (g_zbInfo.macPib.autoReq == '\0')
    {
      return;
    }
  }
  else
  {
    bVar5 = true;
  }
  if (g_zbMacCtx.status == '\x02')
  {
    tl_zbMacActiveScanListAdd();
  }
  if (!bVar5)
  {
    return;
  }
LAB_00011fd2:
  zb_buf_free(in_r0);
  return;
}
