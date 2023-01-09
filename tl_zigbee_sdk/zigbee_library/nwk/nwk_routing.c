// WARNING: Unknown calling convention -- yet parameter storage is locked
void nwkRouteMaintenance(void)

{
  u16 *in_r0;
  int iVar1;
  undefined4 in_r1;
  u8 *puVar2;
  uint uVar3;
  uint uVar4;

  if ((int)((uint) * (byte *)((int)in_r0 + 5) << 0x1d) < 0)
  {
    nwkRouteRecTabEntryDstDel();
  }
  else if (ROUTING_TABLE_SIZE != 0)
  {
    puVar2 = &g_routingTab[0].status;
    uVar3 = 0;
    uVar4 = 0;
    do
    {
      if ((*puVar2 == '\0') && (*in_r0 == g_routingTab[uVar3].dstAddr))
      {
        g_routingTab[uVar4 >> 0x10].status = '\x03';
        if ((int)((uint)(byte)g_routingTab[uVar4 >> 0x10].field_0x5 << 0x1e) < 0)
        {
          g_zbNwkCtx.manyToOneRepair.senderAddr._0_1_ = (undefined)in_r0[1];
          g_zbNwkCtx.manyToOneRepair.senderAddr._1_1_ = (undefined)((uint)in_r0[1] >> 8);
          g_zbNwkCtx.manyToOneRepair.lastSendFailAddr._0_1_ = (undefined)in_r1;
          g_zbNwkCtx.manyToOneRepair.lastSendFailAddr._1_1_ = (char)((uint)in_r1 >> 8);
        }
        iVar1 = c1();
        if (iVar1 == 0)
        {
          return;
        }
        nwkRouteRepair();
        return;
      }
      uVar3 = uVar3 + 1;
      puVar2 = puVar2 + 8;
      uVar4 = uVar3 * 0x10000;
    } while ((uVar3 & 0xffff) < (uint)ROUTING_TABLE_SIZE);
  }
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
// WARNING: Unknown calling convention -- yet parameter storage is locked
// WARNING: Unknown calling convention -- yet parameter storage is locked
// WARNING: Unknown calling convention -- yet parameter storage is locked
// WARNING: Unknown calling convention -- yet parameter storage is locked
// WARNING: Unknown calling convention -- yet parameter storage is locked
// WARNING: Unknown calling convention -- yet parameter storage is locked
// WARNING: Unknown calling convention -- yet parameter storage is locked
void nwkRouteRecTabEntryDstDel(void)

{
  byte bVar1;
  u16 in_r0;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;

  uVar2 = (uint)NWK_ROUTE_RECORD_TABLE_SIZE;
  if (uVar2 != 0)
  {
    uVar3 = (uint)g_zbInfo.nwkNib.maxSourceRoute;
    uVar5 = 0;
    do
    {
      bVar1 = g_routeRecTab[uVar5].field_0x12;
      if ((char)bVar1 < '\0')
      {
        if (g_routeRecTab[uVar5].nwkAddr != in_r0)
        {
          if ((bVar1 & 0x7f) == 0)
            goto LAB_0001de54;
          if (in_r0 != g_routeRecTab[uVar5].path[0])
          {
            uVar4 = 0;
            do
            {
              uVar4 = uVar4 + 1 & 0xff;
              if ((bVar1 & 0x7f) <= uVar4)
                goto LAB_0001de54;
            } while (in_r0 != g_routeRecTab[uVar5].path[uVar4]);
          }
        }
        *(undefined *)&g_routeRecTab[uVar5].nwkAddr = 0xfd;
        *(undefined *)((int)&g_routeRecTab[uVar5].nwkAddr + 1) = 0xfe;
        if (uVar3 != 0)
        {
          uVar4 = 0;
          do
          {
            *(undefined *)(g_routeRecTab[uVar5].path + uVar4) = 0xfd;
            *(undefined *)((int)g_routeRecTab[uVar5].path + uVar4 * 2 + 1) = 0xfe;
            uVar4 = uVar4 + 1;
          } while ((uVar4 & 0xff) < uVar3);
        }
        g_routeRecTab[uVar5].field_0x12 = g_routeRecTab[uVar5].field_0x12 & 0x80;
        g_routeRecTab[uVar5].field_0x12 = g_routeRecTab[uVar5].field_0x12 & 0x7f;
        g_routeRecTab[uVar5].forgetCnt = '\0';
      }
    LAB_0001de54:
      uVar5 = uVar5 + 1 & 0xffff;
    } while (uVar5 < uVar2);
  }
  return;
}
// WARNING: Could not reconcile some variable overlaps
// WARNING: Unknown calling convention -- yet parameter storage is locked
void nwkRouteRepair(void)

{
  uint uVar1;
  u8 uVar2;
  bool bVar3;
  void *in_r0;
  uint uVar4;
  undefined2 in_r1;
  undefined2 in_r2;
  undefined in_r3;
  undefined local_54[4];
  undefined4 uStack_50;
  undefined4 uStack_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  uint uStack_3c;
  u8 *puStack_38;
  undefined local_34[8];
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  undefined2 local_1c;
  undefined local_1a;

  local_54 = (undefined[4])0x0;
  uStack_50 = 0;
  uStack_4c = 0;
  uStack_48 = 0;
  uStack_44 = 0;
  uStack_40 = 0;
  uStack_3c = 0;
  puStack_38 = (u8 *)0x0;
  uStack_2c = 0;
  uStack_28 = 0;
  uStack_24 = 0;
  uStack_20 = 0;
  local_1c = 0;
  local_1a = 0;
  local_34._0_4_ = 3;
  local_34._4_4_ = (uint)CONCAT12(in_r3, in_r2);
  uVar4 = 0;
  if (((int)((uint)ss_ib._62_1_ << 0x1c) < 0) && ((ss_ib._62_1_ & 7) != 0))
  {
    bVar3 = ss_keyPreconfigured();
    uVar4 = (uint)bVar3;
  }
  uVar1 = (ushort)((ushort)uStack_50 & 0xff00 | (ushort)uStack_50 & 0xc0 | 1 | 0x1008) & 0xfffff7ff;
  uStack_50._1_1_ = (byte)(uVar1 >> 8);
  uStack_50._0_2_ =
      (nwkFrameCtrl_t)CONCAT11(uStack_50._1_1_ & 0xfd | (byte)(uVar4 << 1), (char)uVar1);
  uStack_50 = uStack_50 & 0xffff0000 | (uint)(ushort)uStack_50._0_2_;
  memcpy(&uStack_44, g_zbInfo.macPib.extAddress, 8);
  local_54 = (undefined[4])CONCAT22(g_zbInfo.nwkNib.nwkAddr, in_r1);
  uStack_50 = CONCAT13(g_zbInfo.nwkNib.seqNum,
                       CONCAT12(g_zbInfo.nwkNib.maxDepth << 1, uStack_50._0_2_));
  g_zbInfo.nwkNib.seqNum = g_zbInfo.nwkNib.seqNum + '\x01';
  uVar2 = getNwkHdrSize((nwk_hdr_t *)local_54);
  uStack_3c._0_2_ = CONCAT11(uVar2, uStack_3c._0_1_);
  uStack_3c = uStack_3c & 0xffff0000 | (uint)(ushort)uStack_3c;
  tl_zbNwkSendNwkStatusCmd(in_r0, (nwk_hdr_t *)local_54, (nwkCmd_t *)local_34, 0xc9);
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void nwkRoutingTabEntryClear(void)

{
  undefined *in_r0;

  in_r0[5] = 0;
  in_r0[6] = 0;
  in_r0[7] = 0;
  *in_r0 = 0xfd;
  in_r0[1] = 0xfe;
  in_r0[2] = 0xfd;
  in_r0[3] = 0xfe;
  in_r0[4] = 3;
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
// WARNING: Unknown calling convention -- yet parameter storage is locked
void nwkRoutingTabEntryDstDel(void)

{
  u16 in_r0;
  uint uVar1;

  if (ROUTING_TABLE_SIZE != 0)
  {
    uVar1 = 0;
    do
    {
      while ((g_routingTab[uVar1].dstAddr == in_r0 || (g_routingTab[uVar1].nextHopAddr == in_r0)))
      {
        nwkRoutingTabEntryClear();
        uVar1 = uVar1 + 1 & 0xffff;
        if (ROUTING_TABLE_SIZE <= uVar1)
        {
          return;
        }
      }
      uVar1 = uVar1 + 1 & 0xffff;
    } while (uVar1 < ROUTING_TABLE_SIZE);
  }
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void nwkRoutingTabInit(void)

{
  uint uVar1;
  uint uVar2;
  ushort uVar3;
  uint uVar4;
  uint uVar5;
  u8 *puVar6;

  if (ROUTING_TABLE_SIZE != 0)
  {
    uVar3 = 0;
    do
    {
      nwkRoutingTabEntryClear();
      uVar3 = uVar3 + 1;
    } while (uVar3 < ROUTING_TABLE_SIZE);
  }
  uVar1 = (uint)NWK_ROUTE_RECORD_TABLE_SIZE;
  if (uVar1 != 0)
  {
    uVar4 = (uint)g_zbInfo.nwkNib.maxSourceRoute;
    puVar6 = &g_routeRecTab[0].forgetCnt;
    uVar5 = 0;
    do
    {
      g_brcTransTab[uVar5 + 0xb].used = 0xfd;
      *(undefined *)&g_routeRecTab[uVar5].nwkAddr = 0xfe;
      if (uVar4 != 0)
      {
        uVar2 = 0;
        do
        {
          *(undefined *)((int)g_routeRecTab[uVar5].path + uVar2 * 2 + -1) = 0xfd;
          *(undefined *)(g_routeRecTab[uVar5].path + uVar2) = 0xfe;
          uVar2 = uVar2 + 1;
        } while ((uVar2 & 0xff) < uVar4);
      }
      *(byte *)((int)g_routeRecTab[uVar5].path + 0xf) =
          *(byte *)((int)g_routeRecTab[uVar5].path + 0xf) & 0x80;
      *(byte *)((int)g_routeRecTab[uVar5].path + 0xf) =
          *(byte *)((int)g_routeRecTab[uVar5].path + 0xf) & 0x7f;
      *puVar6 = '\0';
      uVar5 = uVar5 + 1;
      puVar6 = puVar6 + 0x14;
    } while ((uVar5 & 0xffff) < uVar1);
  }
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void nwkRoutingTabPeriodic(void)

{
  u8 *puVar1;
  u8 *puVar2;
  uint uVar3;
  short sVar4;
  uint uVar5;

  uVar5 = (uint)ROUTING_TABLE_SIZE;
  if (uVar5 != 0)
  {
    sVar4 = 0;
    puVar2 = &g_routingTab[0].status;
    do
    {
      if (*puVar2 == '\0')
      {
        sVar4 = sVar4 + 1;
      }
      puVar2 = puVar2 + 8;
    } while (puVar2 != &g_routingTab[1].status + ((uVar5 - 1) * 0x10000 >> 0xd));
    if (sVar4 != 0)
    {
      uVar3 = 0;
      puVar2 = &g_routingTab[0].status;
      puVar1 = &g_routingTab[1].status;
      while (true)
      {
        if (((*puVar2 == '\0') && (-1 < (int)((uint)(byte)g_routingTab[uVar3].field_0x5 << 0x1e))) && (puVar2[3] != 0xff))
        {
          puVar2[3] = puVar2[3] + '\x01';
        }
        uVar3 = uVar3 + 1;
        if (uVar5 <= (uVar3 & 0xffff))
          break;
        puVar2 = puVar1;
        puVar1 = puVar1 + 8;
      }
    }
  }
  uVar5 = (uint)NWK_ROUTE_RECORD_TABLE_SIZE;
  if (uVar5 != 0)
  {
    uVar3 = 0;
    sVar4 = 0;
    do
    {
      if ((char)g_routeRecTab[uVar3].field_0x12 < '\0')
      {
        sVar4 = sVar4 + 1;
      }
      uVar3 = uVar3 + 1;
    } while ((uVar3 & 0xffff) < uVar5);
    if (sVar4 != 0)
    {
      puVar2 = &g_routeRecTab[0].forgetCnt;
      uVar3 = 0;
      do
      {
        if (((char)g_routeRecTab[uVar3].field_0x12 < '\0') && (*puVar2 != 0xff))
        {
          *puVar2 = *puVar2 + '\x01';
        }
        uVar3 = uVar3 + 1;
        puVar2 = puVar2 + 0x14;
      } while ((uVar3 & 0xffff) < uVar5);
    }
  }
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
byte nwkSourceRoutePacketRelayFilter(void)

{
  byte bVar1;
  u16 *in_r0;
  int iVar2;

  bVar1 = 0xc1;
  if (((in_r0[1] != g_zbInfo.nwkNib.nwkAddr) && (bVar1 = 0, g_zbInfo.nwkNib.nwkAddr != *in_r0)) &&
      (*(char *)(in_r0 + 0xd) != '\0'))
  {
    iVar2 = (uint) * (byte *)((int)in_r0 + 0x1b) * 2;
    bVar1 = ~(g_zbInfo.nwkNib.nwkAddr !=
              (u16)((ushort) * (byte *)(*(int *)(in_r0 + 0xe) + iVar2 + 1) * 0x100 +
                    (ushort) * (byte *)(*(int *)(in_r0 + 0xe) + iVar2))) &
            0xc1;
  }
  return bVar1;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
u16 nwkSrcRouteReplayNextHop(void)

{
  u16 *in_r0;
  tl_zb_normal_neighbor_entry_t *ptVar1;
  byte bVar2;
  int iVar3;
  u16 uVar4;

  if ((in_r0[1] == g_zbInfo.nwkNib.nwkAddr) || (-1 < (int)((uint) * (byte *)((int)in_r0 + 5) << 0x1d)))
  {
    uVar4 = 0xfffe;
  }
  else
  {
    if (*(char *)((int)in_r0 + 0x1b) == '\0')
    {
      uVar4 = *in_r0;
    }
    else
    {
      ptVar1 = nwk_neTblGetByShortAddr(*in_r0);
      if ((ptVar1 == (tl_zb_normal_neighbor_entry_t *)0x0) || ((ptVar1->field_0x1e & 0x7e) != 0x14))
      {
        bVar2 = *(char *)((int)in_r0 + 0x1b) - 1;
        *(byte *)((int)in_r0 + 0x1b) = bVar2;
        iVar3 = (uint)bVar2 * 2;
        uVar4 = (ushort) * (byte *)(*(int *)(in_r0 + 0xe) + iVar3 + 1) * 0x100 +
                (ushort) * (byte *)(*(int *)(in_r0 + 0xe) + iVar3);
      }
      else
      {
        uVar4 = *in_r0;
      }
    }
    nwkSrcRouteRequiredClear();
  }
  return uVar4;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void nwkSrcRouteRequiredClear(void)

{
  u16 in_r0;
  int iVar1;
  uint uVar2;

  if (ROUTING_TABLE_SIZE != 0)
  {
    if (in_r0 == g_routingTab[0].dstAddr)
    {
      uVar2 = 0;
    }
    else
    {
      iVar1 = 0;
      uVar2 = 0;
      do
      {
        uVar2 = uVar2 + 1 & 0xffff;
        if (ROUTING_TABLE_SIZE <= uVar2)
        {
          return;
        }
        iVar1 = iVar1 + 1;
      } while (in_r0 != g_routingTab[iVar1].dstAddr);
    }
    if (-1 < (int)((uint)(byte)g_routingTab[uVar2].field_0x5 << 0x1f))
    {
      g_routingTab[uVar2].field_0x5 = g_routingTab[uVar2].field_0x5 & 0xfb;
    }
  }
  return;
}
