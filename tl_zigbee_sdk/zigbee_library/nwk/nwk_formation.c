// WARNING: Unknown calling convention -- yet parameter storage is locked
uint nwk_formationScanCnfHandler(void)

{
  byte bVar1;
  byte bVar2;
  bool bVar3;
  uint uVar4;
  uint uVar5;
  byte bVar6;
  zb_buf_t *in_r0;
  uint uVar7;
  tl_zb_addition_neighbor_entry_t *ptVar8;
  u32 uVar9;
  zb_buf_t *pzVar10;
  char cVar11;
  byte bVar12;
  u8 uVar13;
  u8 uVar14;
  nwk_ctx_t *pnVar15;
  undefined2 uVar16;
  byte bVar17;

  if (in_r0->buf[1] == '\0')
  {
    if (in_r0->buf[0] == '\0')
    {
      memcpy(&g_zbNwkCtx, in_r0->buf + 8, 0x10);
      cVar11 = '\x0f';
      uVar7 = 0x800;
      pzVar10 = in_r0;
      while (true)
      {
        if (((g_zbNwkCtx.scanChannels & uVar7) != 0) && (0x3c < pzVar10->buf[8]))
        {
          g_zbNwkCtx.scanChannels = g_zbNwkCtx.scanChannels ^ uVar7;
        }
        cVar11 = cVar11 + -1;
        pzVar10 = (zb_buf_t *)(pzVar10->buf + 1);
        if (cVar11 == '\0')
          break;
        uVar7 = uVar7 << 1;
      }
      uVar7 = g_zbNwkCtx.scanChannels >> 8;
      uVar4 = g_zbNwkCtx.scanChannels >> 0x10;
      uVar5 = g_zbNwkCtx.scanChannels >> 0x18;
      if (g_zbNwkCtx.scanChannels == 0)
      {
        uVar7 = nwk_nlmeNwkFormationCn();
        return uVar7;
      }
      in_r0->buf[0] = (u8)g_zbNwkCtx.scanChannels;
      in_r0->buf[1] = (u8)uVar7;
      in_r0->buf[2] = (u8)uVar4;
      in_r0->buf[3] = (u8)uVar5;
      in_r0->buf[5] = g_zbNwkCtx.scanDuration;
      in_r0->buf[4] = '\x01';
      bVar6 = tl_zbPrimitivePost('\x02', 'U', in_r0);
      return (uint)bVar6;
    }
    goto LAB_00018752;
  }
  if (in_r0->buf[1] != '\x01')
  {
    bVar6 = zb_buf_free(in_r0);
    return (uint)bVar6;
  }
  uVar7 = (uint)g_zbInfo.nwkNib.panId;
  if ((in_r0->buf[0] != 0xea) && (in_r0->buf[0] != '\0'))
    goto LAB_00018752;
  bVar6 = tl_zbAdditionNeighborTableNumGet();
  if (bVar6 != 0)
  {
    bVar12 = 0;
    do
    {
      ptVar8 = tl_zbAdditionNeighborEntryGetFromIdx(bVar12);
      if (ptVar8 != (tl_zb_addition_neighbor_entry_t *)0x0)
      {
        g_zbNwkCtx.formationInfo.energy_detect[ptVar8->logicChannel + 5] =
            g_zbNwkCtx.formationInfo.energy_detect[ptVar8->logicChannel + 5] + '\x01';
      }
      bVar12 = bVar12 + 1;
    } while (bVar12 < bVar6);
  }
  pnVar15 = &g_zbNwkCtx;
  uVar14 = '\0';
  bVar12 = 0xff;
  bVar17 = 0xff;
  uVar13 = '\v';
  do
  {
    if (((g_zbNwkCtx.scanChannels &
          1 << (int)(pnVar15[-0x1ad58].formationInfo.channel_pan_count + 0xf)) != 0) &&
        (bVar1 = (pnVar15->formationInfo).channel_pan_count[0], bVar1 <= bVar17))
    {
      if (bVar1 == bVar17)
      {
        bVar2 = (pnVar15->formationInfo).energy_detect[0];
        if (bVar12 < bVar2)
          goto LAB_00018722;
      }
      else
      {
        bVar2 = (pnVar15->formationInfo).energy_detect[0];
      }
      bVar12 = bVar2;
      bVar17 = bVar1;
      uVar14 = uVar13;
      if (bVar1 == 0)
        goto joined_r0x00018810;
    }
  LAB_00018722:
    uVar13 = uVar13 + '\x01';
    pnVar15 = (nwk_ctx_t *)((pnVar15->formationInfo).energy_detect + 1);
  } while (uVar13 != '\x1b');
  bVar3 = false;
  uVar13 = uVar14;
  goto LAB_00018764;
joined_r0x00018810:
  while (uVar7 == 0xffff)
  {
    uVar9 = drv_u32Rand();
    uVar7 = uVar9 & 0xffff;
  }
  bVar3 = true;
LAB_00018764:
  uVar16 = (undefined2)uVar7;
  if ((byte)(uVar13 - 0xb) < 0x10)
  {
    if (!bVar3)
    {
      do
      {
        if (uVar7 == 0xffff)
        {
          uVar9 = drv_u32Rand();
          uVar7 = uVar9 & 0xffff;
        }
        bVar12 = 0;
        if (bVar6 != 0)
        {
          uVar14 = '\0';
          do
          {
            ptVar8 = tl_zbAdditionNeighborEntryGetFromIdx(uVar14);
            if (((ptVar8 != (tl_zb_addition_neighbor_entry_t *)0x0) &&
                 (ptVar8->logicChannel == uVar13)) &&
                (ptVar8->panId == uVar7))
            {
              uVar7 = uVar7 + 1 & 0xffff;
              break;
            }
            bVar12 = bVar12 + 1;
            uVar14 = uVar14 + '\x01';
          } while (bVar12 < bVar6);
        }
        uVar16 = (undefined2)uVar7;
      } while ((uVar7 == 0xffff) || (bVar6 != bVar12));
    }
    in_r0->buf[4] = (u8)uVar16;
    in_r0->buf[5] = (u8)((ushort)uVar16 >> 8);
    in_r0->buf[6] = uVar13;
    in_r0->buf[10] = '\x01';
    in_r0->buf[0x17] = '\0';
    in_r0->buf[8] = '\x0f';
    in_r0->buf[9] = '\x0f';
    in_r0->buf[0xb] = '\0';
    bVar6 = tl_zbPrimitivePost('\x02', 'Z', in_r0);
    return (uint)bVar6;
  }
LAB_00018752:
  uVar7 = nwk_nlmeNwkFormationCn();
  return uVar7;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void nwk_formationStartCnfHandler(void)

{
  u16 shortAddr;
  char *in_r0;
  int iVar1;
  undefined4 in_lr;
  undefined in_stack_ffffffe8;
  undefined in_stack_ffffffe9;

  if (*in_r0 == '\0')
  {
    g_zbInfo.macPib.rxOnWhenIdle =
        (u8)(((uint)(byte)g_zbInfo.nwkNib.capabilityInfo << 0x1c) >> 0x1f);
    g_zbInfo.nwkNib.panId = g_zbInfo.macPib.panId;
    memcpy(g_zbInfo.nwkNib.ieeeAddr, g_zbInfo.macPib.extAddress, 8);
    shortAddr = g_zbInfo.nwkNib.nwkAddr;
    g_zbInfo.macPib.shortAddress._0_1_ = (undefined)g_zbInfo.nwkNib.nwkAddr;
    g_zbInfo.macPib.shortAddress._1_1_ = (undefined)((uint)g_zbInfo.nwkNib.nwkAddr >> 8);
    iVar1 = memcmp(g_zbInfo.nwkNib.extPANId, &g_zero_addr, 8);
    if (iVar1 == 0)
    {
      memcpy(g_zbInfo.nwkNib.extPANId, g_zbInfo.macPib.extAddress, 8);
    }
    tl_zbNwkAddrMapAdd(shortAddr,
                       (addrExt_t)
                           CONCAT44(in_lr, (uint)CONCAT11(in_stack_ffffffe9, in_stack_ffffffe8)),
                       (u16 *)g_zbInfo.macPib.extAddress);
    tl_zbNwkBeaconPayloadUpdate();
  }
  nwk_nlmeNwkFormationCn();
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void tl_zbNwkBeaconPayloadUpdate(void)

{
  byte bVar1;
  int iVar2;
  int iVar3;

  memset(&g_zbInfo.macPib.beaconPayload, 0, 0xf);
  g_zbInfo.macPib.beaconPayload._1_1_ = g_zbInfo.nwkNib.stackProfile & 0xf | 0x20;
  g_zbInfo.macPib.beaconPayload._2_1_ =
      g_zbInfo.macPib.beaconPayload._2_1_ & 0x87 | (byte)((g_zbInfo.nwkNib.depth & 0xf) << 3);
  memcpy(g_zbInfo.macPib.beaconPayload.extended_panid, g_zbInfo.nwkNib.extPANId, 8);
  memset(g_zbInfo.macPib.beaconPayload.txoffset, 0xff, 3);
  g_zbInfo.macPib.beaconPayload.nwk_update_id = g_zbInfo.nwkNib.updateId;
  g_zbInfo.macPib.beaconPayload._2_1_ = g_zbInfo.macPib.beaconPayload._2_1_ | 0x7f;
  bVar1 = tl_zbNeighborTableChildEDNumGet();
  if (TL_ZB_CHILD_TABLE_SIZE <= bVar1)
  {
    g_zbInfo.macPib.beaconPayload._2_1_ = g_zbInfo.macPib.beaconPayload._2_1_ & 0x7f;
  }
  if (LONG_UPTIME_THRESHOLD <= g_secondCnt)
  {
    g_zbInfo.macPib.beaconPayload._2_1_ = g_zbInfo.macPib.beaconPayload._2_1_ | 1;
  }
  iVar2 = nwkRoutingTabEntryDstActiveGet();
  iVar3 = nwkVaildNeighborToFwd();
  if ((iVar3 != 0) || (iVar2 != 0))
  {
    g_zbInfo.macPib.beaconPayload._2_1_ = g_zbInfo.macPib.beaconPayload._2_1_ | 2;
  }
  g_zbInfo.macPib.beaconPayloadLen = '\x0f';
  return;
}
void tl_zbNwkNlmeNetworkFormationRequestHandler(void *arg)

{
  int iVar1;
  byte bVar2;
  ushort uVar3;
  undefined uVar4;
  undefined uVar5;
  undefined uVar6;

  if (((g_zbNwkCtx._47_1_ & 0xf0) == 0) && (-1 < (int)((uint)g_zbNwkCtx._45_1_ << 0x1d)))
  {
    g_zbNwkCtx._47_1_ = g_zbNwkCtx._47_1_ & 0xf | 0x10;
    // WARNING: Load size is inaccurate
    iVar1 = *arg;
    bVar2 = (byte)iVar1;
    uVar6 = (undefined)((uint)iVar1 >> 8);
    uVar4 = (undefined)((uint)iVar1 >> 0x10);
    uVar5 = (undefined)((uint)iVar1 >> 0x18);
    g_zbNwkCtx.scanDuration = *(u8 *)((int)arg + 8);
    if (*(char *)((int)arg + 6) == '\0')
    {
      g_zbInfo.nwkNib.nwkAddr._0_1_ = 0;
      g_zbInfo.nwkNib.nwkAddr._1_1_ = 0;
      uVar3 = 0;
    }
    else
    {
      uVar3 = *(ushort *)((int)arg + 4);
      g_zbInfo.nwkNib.nwkAddr._0_1_ = (undefined)uVar3;
      g_zbInfo.nwkNib.nwkAddr._1_1_ = (undefined)((uint)uVar3 >> 8);
    }
    g_zbInfo.macPib.shortAddress._0_1_ = (undefined)uVar3;
    g_zbInfo.macPib.shortAddress._1_1_ = (undefined)(uVar3 >> 8);
    g_zbNwkCtx.scanChannels._0_1_ = bVar2;
    g_zbNwkCtx.scanChannels._1_1_ = uVar6;
    g_zbNwkCtx.scanChannels._2_1_ = uVar4;
    g_zbNwkCtx.scanChannels._3_1_ = uVar5;
    *(byte *)arg = bVar2;
    *(undefined *)((int)arg + 1) = uVar6;
    *(undefined *)((int)arg + 2) = uVar4;
    *(undefined *)((int)arg + 3) = uVar5;
    *(u8 *)((int)arg + 5) = g_zbNwkCtx.scanDuration;
    bVar2 = bVar2 & bVar2 - 1;
    *(byte *)((int)arg + 4) = ~bVar2 + bVar2 + (iVar1 != 0);
    tl_zbPrimitivePost('\x02', 'U', arg);
  }
  else
  {
    nwk_nlmeNwkFormationCn();
  }
  return;
}
