// WARNING: Unknown calling convention -- yet parameter storage is locked
void nwk_discoveryScanCnfHandler(void)

{
  zb_buf_t *in_r0;

  if (in_r0->buf[1] == '\x01')
  {
    nwk_nlmeNwkDiscCnf();
  }
  else
  {
    zb_buf_free(in_r0);
  }
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void nwk_nlmeNwkDiscCnf(void)

{
  void *in_r0;
  undefined in_r1;

  *(undefined *)((int)in_r0 + 0x80) = in_r1;
  g_zbNwkCtx._47_1_ = g_zbNwkCtx._47_1_ & 0xf;
  tl_zbTaskPost(zdo_nlme_network_discovery_confirm_cb, in_r0);
  return;
}
// WARNING: Could not reconcile some variable overlaps
void tl_zbMacMlmeBeaconNotifyIndicationHandler(void *arg)

{
  byte bVar1;
  char *pcVar2;
  u16 uVar3;
  tl_zb_normal_neighbor_entry_t *ptVar4;
  int iVar5;
  byte bVar6;
  byte bVar7;
  uint uVar8;
  uint uVar9;
  char *pcStack_48;
  undefined auStack_44[16];
  uint uStack_34;
  uint local_30;
  uint local_2c;
  undefined uStack_28;
  byte bStack_27;

  pcVar2 = *(char **)((int)arg + 0x28);
  memcpy(&uStack_28, (void *)((int)arg + 6), 2);
  bVar7 = *(byte *)((int)arg + 6);
  bVar1 = *(byte *)((int)arg + 7);
  uVar9 = (uint)bVar1;
  if ((((pcVar2 == (char *)0x0) || (*pcVar2 != '\0')) || ((pcVar2[1] & 0xf0U) != 0x20)) ||
      (((pcVar2[0xb] != -1 || (pcVar2[0xc] != -1)) || (pcVar2[0xd] != -1))))
    goto LAB_00017ef6;
  bVar6 = g_zbNwkCtx._47_1_ & 0xf0;
  if (bVar6 == 0x30)
  {
    if (((TL_ZB_ASSOCJOIN_PERMIT_PANID != 0xffff) &&
         (TL_ZB_ASSOCJOIN_PERMIT_PANID != *(u16 *)((int)arg + 4))) ||
        ((TL_ZB_ASSOCJOIN_FILTER_PANID != 0xffff &&
          (TL_ZB_ASSOCJOIN_FILTER_PANID == *(u16 *)((int)arg + 4)))))
      goto LAB_00017ef6;
    if ((bStack_27 & 0x80) != 0)
      goto LAB_0001801c;
  }
  else if ((bVar6 == 0x10) ||
           ((bVar6 == 0x40 && (iVar5 = memcmp(pcVar2 + 3, g_zbInfo.nwkNib.extPANId, 8), iVar5 == 0))))
  {
  LAB_0001801c:
    pcStack_48 = pcVar2 + 3;
    auStack_44._0_4_ = 0;
    auStack_44._4_4_ = 0;
    auStack_44._8_4_ = 0;
    auStack_44._12_4_ = 0;
    uStack_34 = 0;
    bVar6 = (byte)(((byte)pcVar2[2] >> 2 & 1) << 2);
    local_2c._0_3_ =
        CONCAT12(pcVar2[0xe], (ushort) * (byte *)((int)arg + 0x1f) << 8 | (ushort)(bVar7 >> 4) << 2);
    local_2c = (uint)(uint3)local_2c;
    uVar8 = 0;
    if (((byte)pcVar2[1] & 0xf) == (uint)g_zbInfo.nwkNib.stackProfile)
    {
      uVar8 = (uint)(bVar6 != 0);
    }
    local_30 = CONCAT13(bVar6 | bVar1 >> 7 | (byte)(((byte)pcVar2[1] & 0xf) << 4) |
                            ((byte)pcVar2[2] >> 7) << 3 | (byte)(uVar8 << 1),
                        (uint3) * (byte *)((int)arg + 0x1c) << 8 |
                            (uint3)(byte)((byte)((bVar7 & 0xf) << 4) | (byte)pcVar2[2] >> 3 & 0xf) << 0x10);
    memcpy(auStack_44, pcStack_48, 8);
    uStack_34 = uStack_34 & 0xffff | (uint) * (ushort *)((int)arg + 4) << 0x10;
    bVar7 = *(byte *)((int)arg + 0x10);
    local_30 = local_30 & 0xffffff00 | (uint)bVar7;
    if (bVar7 == 2)
    {
      memcpy(auStack_44 + 0x10, (void *)((int)arg + 8), 2);
    }
    else if (bVar7 == 3)
    {
      memcpy(auStack_44 + 8, (void *)((int)arg + 8), 8);
    }
    bVar7 = (byte)(((uVar9 << 0x19) >> 0x1f) << 6);
    bStack_27 = (byte)((uVar9 << 0x1c) >> 0x1c) | (byte)(((uVar9 << 0x1b) >> 0x1f) << 4) |
                (byte)(((uVar9 << 0x1a) >> 0x1f) << 5) | bVar7 | bVar1 & 0x80;
    local_2c = local_2c & 0xffffff00 | (uint)(byte)((byte)local_2c & 0xfc | ~bVar7 + bVar7);
    tl_zbAdditionNeighborTableUpdate((tl_zb_addition_neighbor_entry_t *)auStack_44);
    goto LAB_00017ef6;
  }
  uVar9 = (uint)g_zbNwkCtx._45_1_;
  if ((uVar9 & 0x24) == 4)
  {
    bVar7 = g_zbNwkCtx._46_1_ & 0xf;
    if (bVar7 < 8)
    {
      uVar3 = *(u16 *)((int)arg + 4);
      iVar5 = 0;
      do
      {
        if (g_zbNwkCtx.known_panids[iVar5] == uVar3)
          break;
        if (g_zbNwkCtx.known_panids[iVar5] == 0)
        {
          *(char *)(g_zbNwkCtx.known_panids + iVar5) = (char)uVar3;
          *(char *)((int)g_zbNwkCtx.known_panids + iVar5 * 2 + 1) = (char)(uVar3 >> 8);
          g_zbNwkCtx._46_1_ = g_zbNwkCtx._46_1_ & 0xf0 | bVar7 + 1 & 0xf;
          break;
        }
        iVar5 = iVar5 + 1;
      } while (iVar5 != 8);
      if ((int)(uVar9 << 0x19) < 0)
        goto LAB_00017ef6;
      iVar5 = tl_zbNwkPanidConflictDetect();
      if (iVar5 != 0)
      {
        g_zbNwkCtx._45_1_ = g_zbNwkCtx._45_1_ | 0x40;
        g_sysDiags.panIdConflict = g_sysDiags.panIdConflict + '\x01';
        tl_zbNwkPanidConflictProcess();
        return;
      }
    }
    if ((((*(char *)((int)arg + 0x10) == '\x02') &&
          (ptVar4 = nwk_neTblGetByShortAddr(*(u16 *)((int)arg + 8)),
           ptVar4 != (tl_zb_normal_neighbor_entry_t *)0x0)) &&
         (*(u16 *)((int)arg + 4) == g_zbInfo.nwkNib.panId)) &&
        (iVar5 = memcmp(pcVar2 + 3, g_zbInfo.nwkNib.extPANId, 8), iVar5 == 0))
    {
      ptVar4->depth = (byte)(((uint)(byte)pcVar2[2] << 0x19) >> 0x1c);
    }
  }
LAB_00017ef6:
  zb_buf_free((zb_buf_t *)arg);
  return;
}
void tl_zbNwkNlmeNwkDiscRequestHandler(void *arg)

{
  undefined4 uVar1;
  undefined uVar2;
  undefined uVar3;
  undefined uVar4;

  if ((g_zbNwkCtx._47_1_ & 0xf0) == 0)
  {
    // WARNING: Load size is inaccurate
    if ((*arg & 0x7fff800) == 0)
    {
      nwk_nlmeNwkDiscCnf();
    }
    else
    {
      g_zbNwkCtx._47_1_ = g_zbNwkCtx._47_1_ & 0xf | 0x30;
      // WARNING: Load size is inaccurate
      uVar1 = *arg;
      uVar2 = (undefined)((uint)uVar1 >> 8);
      uVar3 = (undefined)((uint)uVar1 >> 0x10);
      uVar4 = (undefined)((uint)uVar1 >> 0x18);
      g_zbNwkCtx.scanDuration = *(u8 *)((int)arg + 4);
      g_zbNwkCtx.scanChannels._0_1_ = (char)uVar1;
      g_zbNwkCtx.scanChannels._1_1_ = uVar2;
      g_zbNwkCtx.scanChannels._2_1_ = uVar3;
      g_zbNwkCtx.scanChannels._3_1_ = uVar4;
      *(undefined *)((int)arg + 4) = 1;
      *(char *)arg = (char)uVar1;
      *(undefined *)((int)arg + 1) = uVar2;
      *(undefined *)((int)arg + 2) = uVar3;
      *(undefined *)((int)arg + 3) = uVar4;
      *(u8 *)((int)arg + 5) = g_zbNwkCtx.scanDuration;
      tl_zbPrimitivePost('\x02', 'U', arg);
    }
  }
  else
  {
    nwk_nlmeNwkDiscCnf();
  }
  return;
}
