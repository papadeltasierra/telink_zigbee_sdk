// WARNING: Unknown calling convention -- yet parameter storage is locked
void apsParentAnncePeriodic(void)

{
  if ((aps_ib.aps_parent_announce_timer != '\0') &&
      (aps_ib.aps_parent_announce_timer = aps_ib.aps_parent_announce_timer + 0xff,
       aps_ib.aps_parent_announce_timer == '\0'))
  {
    zdo_parent_announce_send();
  }
  return;
}
undefined4 zdoMgmtLeaveCmdProcessCb(void)

{
  void *arg;
  code *in_r3;

  arg = (void *)(*in_r3)();
  tl_zbPrimitivePost('\x03', 0x82, arg);
  return 0xfffffffe;
}
// WARNING: Could not reconcile some variable overlaps
void zdo_SysServerDiscoveryIndiate(void *buf)

{
  u8 uVar1;
  byte bVar2;
  byte bVar3;
  u8 *puVar4;
  undefined local_44[12];
  undefined4 uStack_38;
  uint uStack_34;
  zdo_callback p_Stack_30;
  u8 local_2c;
  node_descriptor_t nStack_28;

  puVar4 = *(u8 **)((int)buf + 0xc);
  uVar1 = *puVar4;
  bVar2 = puVar4[2];
  bVar3 = puVar4[1];
  af_nodeDescriptorCopy(&nStack_28);
  nStack_28.server_mask = (ushort)bVar2 * 0x100 + (ushort)bVar3 & nStack_28.server_mask;
  if (nStack_28.server_mask == 0)
  {
    zb_buf_free((zb_buf_t *)buf);
  }
  else
  {
    local_44._0_4_ = (u8 *)0x0;
    local_44._4_4_ = (zb_buf_t *)0x0;
    local_44._8_4_ = 0;
    uStack_38 = 0;
    p_Stack_30 = ll_reset;
    local_2c = '\0';
    uStack_34 = 0x40000;
    local_44._0_4_ = (u8 *)tl_bufInitalloc((zb_buf_t *)buf, '\x04');
    *local_44._0_4_ = uVar1;
    local_44._0_4_[1] = '\0';
    local_44._0_4_[2] = (u8)nStack_28.server_mask;
    local_44._0_4_[3] = (u8)(nStack_28.server_mask >> 8);
    p_Stack_30 = ll_reset;
    uStack_34 = (uint)((uint3)uStack_34 & 0xff0000 | 0x8015);
    local_44._8_4_ = local_44._8_4_ & 0xffff0000 | (uint) * (ushort *)((int)buf + 0x14);
    local_44._4_4_ = (zb_buf_t *)buf;
    zdo_send_req((zdo_zdp_req_t *)local_44);
    zb_buf_free(local_44._4_4_);
  }
  return;
}
// WARNING: Could not reconcile some variable overlaps
void zdo_activeEpIndicate(void *buf)

{
  u16 uVar1;
  u8 uVar2;
  device_type_t dVar3;
  u8 *puVar4;
  af_endpoint_descriptor_t *paVar5;
  u8 uVar6;
  uint uVar7;
  int iVar8;
  u8 *puVar9;
  undefined local_3c[12];
  undefined4 uStack_30;
  uint uStack_2c;
  zdo_callback p_Stack_28;
  u8 local_24;

  puVar4 = *(u8 **)((int)buf + 0xc);
  uVar6 = *puVar4;
  if ((*(ushort *)((int)buf + 2) & 0xfff8) == 0xfff8)
  {
    zb_buf_free((zb_buf_t *)buf);
  }
  else
  {
    uVar7 = (uint)puVar4[2] * 0x100 + (uint)puVar4[1];
    iVar8 = uVar7 * 0x10000;
    local_3c._0_4_ = (u8 *)0x0;
    local_3c._4_4_ = (zb_buf_t *)0x0;
    local_3c._8_4_ = 0;
    uStack_30 = 0;
    uStack_2c = 0;
    p_Stack_28 = ll_reset;
    local_24 = '\0';
    uVar2 = af_availableEpNumGet();
    puVar4 = (u8 *)tl_bufInitalloc((zb_buf_t *)buf, uVar2 + '\x05');
    *puVar4 = uVar6;
    uVar1 = g_zbInfo.macPib.shortAddress;
    uVar6 = (u8)((uint)iVar8 >> 0x18);
    local_3c._0_4_ = puVar4;
    if ((uint)g_zbInfo.macPib.shortAddress == (uVar7 & 0xffff))
    {
      puVar4[1] = '\0';
      puVar4[2] = (u8)uVar1;
      puVar4[3] = uVar6;
      puVar4[4] = uVar2;
      puVar9 = puVar4 + 5;
      paVar5 = af_epDescriptorGet();
      if (uVar2 != '\0')
      {
        puVar4 = puVar9;
        do
        {
          *puVar4 = paVar5->ep;
          puVar4 = puVar4 + 1;
          paVar5 = paVar5 + 1;
        } while (puVar4 != puVar4 + (byte)(uVar2 - 2) + 6);
        puVar9 = puVar9 + (byte)(uVar2 - 2) + 1;
      }
    }
    else
    {
      dVar3 = af_nodeDevTypeGet();
      uVar2 = 0x80;
      if (dVar3 != DEVICE_TYPE_END_DEVICE)
      {
        uVar2 = 0x81;
      }
      puVar4[1] = uVar2;
      puVar4[2] = (u8)((uint)iVar8 >> 0x10);
      puVar4[3] = uVar6;
      puVar4[4] = '\0';
      puVar9 = puVar4 + 5;
    }
    p_Stack_28 = ll_reset;
    uStack_2c = (uint)CONCAT12((char)puVar9 - (char)local_3c._0_4_, 0x8005);
    local_3c._8_4_ = local_3c._8_4_ & 0xffff0000 | (uint) * (ushort *)((int)buf + 0x14);
    local_3c._4_4_ = (zb_buf_t *)buf;
    zdo_send_req((zdo_zdp_req_t *)local_3c);
    zb_buf_free(local_3c._4_4_);
  }
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void zdo_apsParentAnnceTimerStart(void)

{
  char cVar1;
  u32 uVar2;

  uVar2 = drv_u32Rand();
  cVar1 = FUN_00001628(uVar2 & 0xff, 10);
  aps_ib.aps_parent_announce_timer = cVar1 + '\n';
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
byte zdo_apsmeBindUnBind(void)

{
  u8 ep;
  char in_r0;
  byte bVar1;
  int iVar2;
  void *in_r1;
  byte bVar3;
  char cVar4;

  iVar2 = memcmp(in_r1, g_zbInfo.macPib.extAddress, 8);
  if (iVar2 != 0)
  {
    return 0x84;
  }
  ep = *(u8 *)((int)in_r1 + 8);
  bVar1 = *(byte *)((int)in_r1 + 0xb);
  if (bVar1 == 1)
  {
    bVar3 = 0x82;
    if (0xfd < (byte)(ep - 1))
      goto LAB_00025cee;
  }
  else
  {
    if ((((0xfd < (byte)(ep - 1)) || (*(char *)((int)in_r1 + 0x14) == '\0')) || (bVar1 == 2)) ||
        (bVar1 == 0))
    {
      bVar3 = 0x82;
      goto LAB_00025cee;
    }
    bVar3 = 0x82;
    if (3 < bVar1)
      goto LAB_00025cee;
  }
  cVar4 = '\0';
  bVar1 = af_clusterMatchedLocal((ushort) * (byte *)((int)in_r1 + 9) + (ushort) * (byte *)((int)in_r1 + 10) * 0x100,
                                 ep);
  bVar3 = ~(bVar1 + ~bVar1 + cVar4) & 0x88;
LAB_00025cee:
  if (in_r0 == '\0')
  {
    if (((bVar3 == 0) && (iVar2 = aps_me_unbind_req(), iVar2 != 0)) && (bVar3 = 0x84, iVar2 == 0xa4))
    {
      bVar3 = 0x88;
    }
  }
  else if (bVar3 == 0)
  {
    iVar2 = aps_me_bind_req();
    if ((iVar2 != 0) && (bVar3 = 0x84, iVar2 == 0xae))
    {
      bVar3 = 0x8c;
    }
  }
  else
  {
    bVar3 = 0x82;
  }
  return bVar3;
}
// WARNING: Could not reconcile some variable overlaps
void zdo_bindOrUnbindIndicate(void *buf)

{
  u8 uVar1;
  u8 uVar2;
  undefined local_48[12];
  undefined4 uStack_3c;
  uint uStack_38;
  zdo_callback p_Stack_34;
  u8 local_30;
  undefined auStack_2c[28];

  uVar1 = **(u8 **)((int)buf + 0xc);
  memcpy(auStack_2c, *(u8 **)((int)buf + 0xc) + 1, *(ushort *)((int)buf + 10) - 1);
  local_48._0_4_ = (u8 *)0x0;
  local_48._4_4_ = (zb_buf_t *)0x0;
  local_48._8_4_ = 0;
  uStack_3c = 0;
  uStack_38 = 0;
  p_Stack_34 = ll_reset;
  local_30 = '\0';
  if (*(short *)((int)buf + 8) == 0x21)
  {
    uStack_38 = 0x8021;
  }
  else if (*(short *)((int)buf + 8) == 0x22)
  {
    uStack_38 = 0x8022;
  }
  uVar2 = zdo_apsmeBindUnBind();
  uStack_38._0_3_ = CONCAT12(2, (u16)uStack_38);
  uStack_38 = uStack_38 & 0xff000000 | (uint)(uint3)uStack_38;
  local_48._0_4_ = (u8 *)tl_bufInitalloc((zb_buf_t *)buf, '\x02');
  *local_48._0_4_ = uVar1;
  local_48._0_4_[1] = uVar2;
  p_Stack_34 = ll_reset;
  uStack_38 = uStack_38 & 0xffffff;
  local_48._8_4_ = local_48._8_4_ & 0xffff0000 | (uint) * (ushort *)((int)buf + 0x14);
  local_48._4_4_ = (zb_buf_t *)buf;
  zdo_send_req((zdo_zdp_req_t *)local_48);
  zb_buf_free(local_48._4_4_);
  return;
}
// WARNING: Could not reconcile some variable overlaps
// WARNING: Unknown calling convention -- yet parameter storage is locked
void zdo_bind_toggle_action(void)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  uint uStack_24;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  byte local_18;

  uStack_2c = 0;
  uStack_28 = 0;
  uStack_20 = 0;
  uStack_1c = 0;
  local_18 = 0;
  uVar2 = 0;
  uVar3 = 0;
  if (ed_binding_ctx[7] == '\0')
  {
    uStack_24 = (uint)ed_binding_ctx[14];
    tl_zbExtAddrByShortAddr(ed_binding_ctx._12_2_, (addrExt_t)0x0, (u16 *)&uStack_2c);
    tl_zbExtAddrByShortAddr(ed_binding_ctx._4_2_, (addrExt_t)CONCAT44(uVar3, uVar2), (u16 *)&uStack_20);
    local_18 = ed_binding_ctx[6];
  }
  else
  {
    uStack_24 = (uint)ed_binding_ctx[6];
    tl_zbExtAddrByShortAddr(ed_binding_ctx._4_2_, (addrExt_t)0x0, (u16 *)&uStack_2c);
    tl_zbExtAddrByShortAddr(ed_binding_ctx._12_2_, (addrExt_t)CONCAT44(uVar3, uVar2), (u16 *)&uStack_20);
    local_18 = ed_binding_ctx[14];
  }
  uStack_24._0_3_ =
      CONCAT12((char)((ushort)ed_binding_ctx._16_2_ >> 8),
               CONCAT11((char)ed_binding_ctx._16_2_, (undefined)uStack_24));
  uStack_24 = (uint3)uStack_24 | 0x3000000;
  iVar1 = zdo_bind_unbind_req();
  if (iVar1 == 0x8a)
  {
    tl_zbTaskPost(zdo_bind_toggle_action, (void *)0x0);
  }
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void zdo_bind_toggle_cb(void)

{
  zdo_bind_unbind_after_toggle_clone_0();
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
undefined4 zdo_bind_unbind_req(void)

{
  byte bVar1;
  u8 uVar2;
  u8 uVar3;
  void *in_r0;
  zb_buf_t *p;
  u8 *puVar4;
  zdo_zdp_req_t *in_r1;
  byte in_r2;
  uint length;
  undefined4 uVar5;

  p = (zb_buf_t *)c1();
  uVar5 = 0x8a;
  if (p != (zb_buf_t *)0x0)
  {
    *(char *)&in_r1->buff_addr = (char)p;
    *(char *)((int)&in_r1->buff_addr + 1) = (char)((uint)p >> 8);
    *(char *)((int)&in_r1->buff_addr + 2) = (char)((uint)p >> 0x10);
    *(char *)((int)&in_r1->buff_addr + 3) = (char)((uint)p >> 0x18);
    puVar4 = (u8 *)tl_bufInitalloc(p, '\x15');
    *(char *)&in_r1->zdu = (char)puVar4;
    *(char *)((int)&in_r1->zdu + 1) = (char)((uint)puVar4 >> 8);
    *(char *)((int)&in_r1->zdu + 2) = (char)((uint)puVar4 >> 0x10);
    *(char *)((int)&in_r1->zdu + 3) = (char)((uint)puVar4 >> 0x18);
    uVar2 = zdp_txSeqNo;
    uVar3 = zdp_txSeqNo + '\x01';
    in_r1->zdpSeqNum = zdp_txSeqNo;
    zdp_txSeqNo = uVar3;
    *puVar4 = uVar2;
    if (*(char *)((int)in_r0 + 0xb) == '\x03')
    {
      in_r1->zduLen = '\x15';
      length = 0x15;
    }
    else
    {
      in_r1->zduLen = '\x0e';
      length = 0xe;
    }
    memcpy(puVar4 + 1, in_r0, length);
    bVar1 = in_r1->zduLen;
    in_r1->zduLen = bVar1 + 1;
    *(byte *)&in_r1->cluster_id = in_r2 + ~in_r2 + (0xfffffffe < bVar1) + '!';
    *(undefined *)((int)&in_r1->cluster_id + 1) = 0;
    zdo_send_req(in_r1);
    zb_buf_free((zb_buf_t *)in_r1->buff_addr);
    uVar5 = 0;
  }
  return uVar5;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
undefined4 zdo_change_channel_cb(void)

{
  u8 in_r0;

  tl_zbMacChannelSet(in_r0);
  g_zbInfo.nwkNib.txTotal._0_1_ = 0;
  g_zbInfo.nwkNib.txTotal._1_1_ = 0;
  g_zbInfo.nwkNib.txFail._0_1_ = 0;
  g_zbInfo.nwkNib.txFail._1_1_ = 0;
  g_zbInfo.macPib.phyChannelCur = in_r0;
  tl_zbTaskPost(zb_info_save, (void *)0x0);
  return 0xfffffffe;
}
// WARNING: Could not reconcile some variable overlaps
void zdo_descriptorsIndicate(void *buf)

{
  byte ep;
  u8 *puVar1;
  char cVar2;
  device_type_t dVar3;
  u8 uVar4;
  u8 *puVar5;
  af_simple_descriptor_t *sd;
  u8 uVar6;
  short sVar7;
  uint uVar8;
  int iVar9;
  char cVar10;
  undefined local_40[12];
  undefined4 uStack_34;
  uint uStack_30;
  zdo_callback p_Stack_2c;
  u8 local_28;

  puVar1 = *(u8 **)((int)buf + 0xc);
  uVar4 = *puVar1;
  if ((*(ushort *)((int)buf + 2) & 0xfff8) == 0xfff8)
  {
    zb_buf_free((zb_buf_t *)buf);
    return;
  }
  uVar8 = (uint)puVar1[2] * 0x100 + (uint)puVar1[1];
  iVar9 = uVar8 * 0x10000;
  uVar8 = uVar8 & 0xffff;
  local_40._0_4_ = (u8 *)0x0;
  local_40._4_4_ = (zb_buf_t *)0x0;
  local_40._8_4_ = 0;
  uStack_34 = 0;
  uStack_30 = 0;
  p_Stack_2c = ll_reset;
  local_28 = '\0';
  puVar5 = (u8 *)tl_bufInitalloc((zb_buf_t *)buf, '4');
  *puVar5 = uVar4;
  cVar2 = (char)puVar5;
  cVar10 = cVar2 + '\x01';
  local_40._0_4_ = puVar5;
  if (g_zbInfo.nwkNib.nwkAddr == uVar8)
  {
    sVar7 = *(short *)((int)buf + 8);
    uVar4 = (u8)g_zbInfo.nwkNib.nwkAddr;
    uVar6 = (u8)((uint)iVar9 >> 0x18);
    if (sVar7 == 2)
    {
      puVar5[1] = '\0';
      puVar5[2] = uVar4;
      puVar5[3] = uVar6;
      af_nodeDescriptorCopy((node_descriptor_t *)(puVar5 + 4));
      cVar10 = cVar2 + '\x11';
      sVar7 = *(short *)((int)buf + 8);
    }
    else if (sVar7 == 3)
    {
      puVar5[1] = '\0';
      puVar5[2] = uVar4;
      puVar5[3] = uVar6;
      af_powerDescriptorCopy((power_descriptor_t *)(puVar5 + 4));
      cVar10 = cVar2 + '\x06';
      sVar7 = *(short *)((int)buf + 8);
    }
    else if (sVar7 == 4)
    {
      ep = puVar1[3];
      uVar6 = (u8)(g_zbInfo.nwkNib.nwkAddr >> 8);
      if ((ep == 0) || ((ep != 0xf2 && (0xf0 < ep))))
      {
        puVar5[1] = 0x82;
        puVar5[2] = uVar4;
        puVar5[3] = uVar6;
        puVar5[4] = '\0';
      }
      else
      {
        sd = af_simpleDescGet(ep);
        if (sd != (af_simple_descriptor_t *)0x0)
        {
          puVar5[1] = '\0';
          puVar5[2] = uVar4;
          puVar5[3] = uVar6;
          uVar4 = af_simpleDescriptorCopy(puVar5 + 5, sd);
          cVar10 = (char)(puVar5 + 5) + uVar4;
          puVar5[4] = uVar4;
          sVar7 = *(short *)((int)buf + 8);
          goto LAB_00025306;
        }
        puVar5[1] = 0x83;
        puVar5[2] = uVar4;
        puVar5[3] = uVar6;
        puVar5[4] = '\0';
      }
      cVar10 = cVar2 + '\x05';
      sVar7 = *(short *)((int)buf + 8);
    }
  }
  else
  {
    dVar3 = af_nodeDevTypeGet();
    if (dVar3 == DEVICE_TYPE_END_DEVICE)
    {
      puVar5[1] = 0x80;
    }
    else
    {
      puVar5[1] = 0x81;
    }
    puVar5[2] = (u8)((uint)iVar9 >> 0x10);
    puVar5[3] = (u8)(uVar8 >> 8);
    cVar10 = cVar2 + '\x04';
    sVar7 = *(short *)((int)buf + 8);
    if (sVar7 == 4)
    {
      puVar5[4] = '\0';
      cVar10 = cVar2 + '\x05';
      sVar7 = *(short *)((int)buf + 8);
    }
  }
LAB_00025306:
  p_Stack_2c = ll_reset;
  uStack_30 = (uint)(uint3)(CONCAT12(cVar10 - (char)local_40._0_4_, sVar7) | 0x8000);
  local_40._8_4_ = local_40._8_4_ & 0xffff0000 | (uint) * (ushort *)((int)buf + 0x14);
  local_40._4_4_ = (zb_buf_t *)buf;
  zdo_send_req((zdo_zdp_req_t *)local_40);
  zb_buf_free(local_40._4_4_);
  return;
}
void zdo_deviceAnnounceIndicate(void *buf)

{
  bool bVar1;
  u16 uVar2;
  int iVar3;
  tl_zb_normal_neighbor_entry_t *entry;
  undefined in_stack_ffffffcc;
  undefined in_stack_ffffffcd;
  undefined2 in_stack_ffffffce;
  undefined4 in_stack_ffffffd0;
  u16 local_28;
  u16 auStack_26[7];

  memcpy(&local_28, (void *)(*(int *)((int)buf + 0xc) + 1), 0xb);
  bVar1 = tl_zbNwkAddrConflictDetect(buf, local_28,
                                     (addrExt_t)
                                         CONCAT44(in_stack_ffffffd0,
                                                  CONCAT22(in_stack_ffffffce,
                                                           CONCAT11(in_stack_ffffffcd, in_stack_ffffffcc))));
  if (bVar1 != true)
  {
    if ((g_gpDeviceAnnounceCheckCb == ll_reset) || (iVar3 = zdo_dAI_sub(), iVar3 == 0))
    {
      entry = nwk_neTblGetByExtAddr((addrExt_t)
                                        CONCAT44(in_stack_ffffffd0,
                                                 CONCAT22(in_stack_ffffffce,
                                                          CONCAT11(in_stack_ffffffcd, in_stack_ffffffcc))));
      if (((entry != (tl_zb_normal_neighbor_entry_t *)0x0) && ((entry->field_0x1e & 0xe) == 4)) &&
          (*(u16 *)((int)buf + 0x1c) != local_28))
      {
        in_stack_ffffffce = 0;
        in_stack_ffffffd0 = 0;
        uVar2 = tl_zbshortAddrByIdx(entry->addrmapIdx);
        in_stack_ffffffcc = (undefined)uVar2;
        in_stack_ffffffcd = (undefined)(uVar2 >> 8);
        tl_zbExtAddrByIdx(entry->addrmapIdx,
                          (addrExt_t)CONCAT44(in_stack_ffffffd0, CONCAT22(in_stack_ffffffce, uVar2)));
        nwk_nodeAddrInfoDelete();
        tl_zbNeighborTableDelete(entry);
      }
      tl_zbNwkAddrMapAdd(local_28, (addrExt_t)CONCAT44(in_stack_ffffffd0, CONCAT22(in_stack_ffffffce, CONCAT11(in_stack_ffffffcd, in_stack_ffffffcc))),
                         auStack_26);
      nwkRoutingTabEntryDstDel();
      nwkRouteRecTabEntryDstDel();
      if ((int)((uint)g_zbInfo.nwkNib._45_1_ << 0x1b) < 0)
      {
        tl_zbTaskPost(zdo_manyToOneRouteDisc, buf);
      }
      else
      {
        zb_buf_free((zb_buf_t *)buf);
      }
      if ((zdoAppIndCbLst != 0) && (*(int *)(zdoAppIndCbLst + 8) != 0))
      {
        zdo_dAI_sub();
      }
    }
    else
    {
      zb_buf_free((zb_buf_t *)buf);
    }
  }
  return;
}
// WARNING: Could not reconcile some variable overlaps
// WARNING: Unknown calling convention -- yet parameter storage is locked
// WARNING: Unknown calling convention -- yet parameter storage is locked
void zdo_device_announce_send(void)

{
  af_nodeMacCapabilityGet();
  zdo_devAnnce();
  return;
}
void zdo_endDeviceBindIndicate(void *buf)

{
  undefined uVar1;
  undefined uVar2;
  int iVar3;
  int iVar4;

  iVar3 = *(int *)((int)buf + 0xc);
  if ((byte)(*(char *)(iVar3 + 9) - 1U) < 0xfe)
  {
    if (ed_binding_ctx._0_4_ == (void *)0x0)
    {
      if (zdo_bind_timer_event != (ev_timer_event_t *)0x0)
      {
        ev_timer_taskCancel(&zdo_bind_timer_event);
      }
      zdo_bind_timer_event = ev_timer_taskPost(zdo_end_device_bind_timeout_cb, buf, 20000);
      ed_binding_ctx._0_4_ = buf;
      return;
    }
    if (zdo_bind_timer_event != (ev_timer_event_t *)0x0)
    {
      ev_timer_taskCancel(&zdo_bind_timer_event);
    }
    iVar4 = (int)ed_binding_ctx._0_4_;
    uVar1 = *(undefined *)(iVar3 + 0xb);
    uVar2 = *(undefined *)(*(int *)((int)ed_binding_ctx._0_4_ + 0xc) + 0xb);
    if (*(short *)(*(int *)((int)ed_binding_ctx._0_4_ + 0xc) + 0xc) == *(short *)(iVar3 + 0xc))
    {
      ed_binding_ctx._48_2_ = ed_binding_ctx._48_2_ & 0xff00;
      zdo_cluster_list_match_process_clone_1();
      ed_binding_ctx._4_4_ = ed_binding_ctx._4_4_ & 0xffffff | (uint)ed_binding_ctx[48] << 0x18;
      zdo_cluster_list_match_process_clone_1();
      ed_binding_ctx._12_4_ =
          ed_binding_ctx._12_4_ & 0xffffff |
          (uint)(byte)(ed_binding_ctx[48] - ed_binding_ctx[7]) << 0x18;
      if (ed_binding_ctx[48] != '\0')
      {
        ed_binding_ctx._4_3_ = CONCAT12(uVar2, *(undefined2 *)(iVar4 + 0x14));
        ed_binding_ctx._4_4_ = ed_binding_ctx._4_4_ & 0xff000000 | (uint)ed_binding_ctx._4_3_;
        ed_binding_ctx._12_4_ =
            CONCAT13(ed_binding_ctx[48] - ed_binding_ctx[7],
                     CONCAT12(uVar1, *(undefined2 *)((int)buf + 0x14)));
        tl_zbTaskPost(zdo_bind_toggle_action, (void *)0x0);
        zdo_end_device_bind_resp_send();
        zdo_end_device_bind_resp_send();
        return;
      }
    }
  }
  zdo_end_device_bind_resp_send();
  zdo_end_device_bind_resp_send();
  ed_binding_ctx._48_2_ = 0;
  ed_binding_ctx._44_4_ = 0;
  ed_binding_ctx._40_4_ = 0;
  ed_binding_ctx._36_4_ = 0;
  ed_binding_ctx._32_4_ = 0;
  ed_binding_ctx._28_4_ = 0;
  ed_binding_ctx._24_4_ = 0;
  ed_binding_ctx._20_4_ = 0;
  ed_binding_ctx._16_4_ = 0;
  ed_binding_ctx._12_4_ = 0;
  ed_binding_ctx._8_4_ = 0;
  ed_binding_ctx._4_4_ = 0;
  ed_binding_ctx._0_4_ = (void *)0x0;
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void zdo_end_device_bind_cb(void)

{
  zdo_bind_unbind_after_toggle_clone_0();
  return;
}
// WARNING: Could not reconcile some variable overlaps
// WARNING: Unknown calling convention -- yet parameter storage is locked
void zdo_end_device_bind_resp_send(void)

{
  zb_buf_t *in_r0;
  u8 in_r1;
  u8 in_r2;
  ushort in_r3;
  undefined local_38[12];
  undefined4 uStack_2c;
  uint uStack_28;
  zdo_callback p_Stack_24;
  u8 local_20;

  local_38._0_4_ = (u8 *)0x0;
  local_38._4_4_ = (zb_buf_t *)0x0;
  local_38._8_4_ = 0;
  uStack_2c = 0;
  p_Stack_24 = ll_reset;
  local_20 = '\0';
  uStack_28 = 0x20000;
  local_38._0_4_ = (u8 *)tl_bufInitalloc(in_r0, '\x02');
  *local_38._0_4_ = in_r2;
  local_38._0_4_[1] = in_r1;
  p_Stack_24 = ll_reset;
  uStack_28 = (uint)((uint3)uStack_28 & 0xff0000 | 0x8020);
  local_38._8_4_ = local_38._8_4_ & 0xffff0000 | (uint)in_r3;
  local_38._4_4_ = in_r0;
  zdo_send_req((zdo_zdp_req_t *)local_38);
  zb_buf_free(local_38._4_4_);
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
undefined4 zdo_end_device_bind_timeout_cb(void)

{
  zdo_end_device_bind_resp_send();
  ed_binding_ctx._0_4_ = 0;
  ed_binding_ctx._4_4_ = 0;
  ed_binding_ctx._8_4_ = 0;
  ed_binding_ctx._12_4_ = 0;
  ed_binding_ctx._16_4_ = 0;
  ed_binding_ctx._20_4_ = 0;
  ed_binding_ctx._24_4_ = 0;
  ed_binding_ctx._28_4_ = 0;
  ed_binding_ctx._32_4_ = 0;
  ed_binding_ctx._36_4_ = 0;
  ed_binding_ctx._40_4_ = 0;
  ed_binding_ctx._44_4_ = 0;
  ed_binding_ctx._48_2_ = 0;
  zdo_bind_timer_event = 0;
  return 0xfffffffe;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void zdo_end_device_unbind_cb(void)

{
  zdo_bind_unbind_after_toggle_clone_0();
  return;
}
void zdo_ieeeAddrIndicate(void *buf)

{
  ev_timer_taskPost(zdo_ieeeAddrReqDelayCb, buf, 200);
  return;
}
// WARNING: Could not reconcile some variable overlaps
undefined4 zdo_ieeeAddrReqDelayCb(zb_buf_t *param_1)

{
  u8 uVar1;
  byte bVar2;
  byte bVar3;
  device_type_t dVar4;
  byte bVar5;
  u16 uVar6;
  tl_zb_normal_neighbor_entry_t *ptVar7;
  u8 *puVar8;
  int iVar9;
  u8 size;
  uint uVar10;
  uint uVar11;
  char cVar12;
  u8 *puVar13;
  u8 uVar14;
  undefined4 in_stack_ffffffac;
  uint uVar15;
  undefined4 in_stack_ffffffb0;
  uint uVar16;
  undefined auStack_4c[12];
  undefined4 uStack_40;
  uint uStack_3c;
  zdo_callback p_Stack_38;
  u8 local_34;
  u16 auStack_30[6];
  uint extraout_r0;

  puVar8 = *(u8 **)(param_1->buf + 0xc);
  uVar1 = *puVar8;
  uVar6 = *(u16 *)(puVar8 + 1);
  bVar2 = puVar8[3];
  bVar3 = puVar8[4];
  uVar10 = (uint)bVar3;
  auStack_4c._0_4_ = (u8 *)0x0;
  auStack_4c._4_4_ = (zb_buf_t *)0x0;
  auStack_4c._8_4_ = 0;
  uStack_40 = 0;
  uStack_3c = 0;
  p_Stack_38 = ll_reset;
  local_34 = '\0';
  memcpy(auStack_30, &g_invalid_addr, 8);
  ptVar7 = nwk_neTblGetByShortAddr(uVar6);
  if ((g_zbInfo.nwkNib.nwkAddr == uVar6) ||
      ((ptVar7 != (tl_zb_normal_neighbor_entry_t *)0x0 && ((ptVar7->field_0x1e & 0xe) == 4))))
  {
    if (1 < bVar2)
    {
      uVar14 = 0x80;
      if ((*(ushort *)(param_1->buf + 2) & 0xfff8) == 0xfff8)
        goto LAB_00024754;
    LAB_0002471e:
      tl_zbExtAddrByShortAddr(uVar6, (addrExt_t)CONCAT44(in_stack_ffffffb0, in_stack_ffffffac), auStack_30);
      size = '\x1a';
      uVar15 = 0;
      uVar16 = 0;
      goto LAB_00024674;
    }
    uVar14 = '\0';
    if (bVar2 != 0)
      goto LAB_0002473e;
  LAB_00024666:
    if (uVar14 == '\0')
    {
      tl_zbExtAddrByShortAddr(uVar6, (addrExt_t)CONCAT44(in_stack_ffffffb0, in_stack_ffffffac), auStack_30);
      size = '\x1a';
      uVar15 = 0;
      uVar16 = 0;
      goto LAB_00024674;
    }
  }
  else
  {
    uVar14 = 0x81;
    if ((*(ushort *)(param_1->buf + 2) & 0xfff8) == 0xfff8)
    {
    LAB_00024754:
      zb_buf_free(param_1);
      return 0xfffffffe;
    }
    if (bVar2 == 0)
      goto LAB_00024666;
  LAB_0002473e:
    if (bVar2 != 1)
      goto LAB_0002471e;
    if (uVar14 != '\0')
    {
      size = '\x1a';
      uVar15 = 0;
      uVar16 = 0;
      goto LAB_00024674;
    }
    memcpy(auStack_30, g_zbInfo.macPib.extAddress, 8);
    uVar6 = g_zbInfo.macPib.shortAddress;
    dVar4 = af_nodeDevTypeGet();
    if ((dVar4 == DEVICE_TYPE_COORDINATOR) ||
        (dVar4 = af_nodeDevTypeGet(), dVar4 == DEVICE_TYPE_ROUTER))
    {
      bVar5 = tl_zbNeighborTableChildEDNumGet();
      extraout_r0 = (uint)bVar5;
      uVar16 = extraout_r0;
      if (extraout_r0 == 0)
      {
        size = '\x1a';
        uVar15 = 0;
      }
      else if (uVar10 < extraout_r0)
      {
        uVar15 = extraout_r0 - uVar10 & 0xff;
        if (uVar15 * 2 < 0x1f)
        {
          size = (char)(uVar15 * 2) + '\x1a';
        }
        else
        {
          size = '9';
          uVar15 = 0xf;
        }
      }
      else
      {
        size = '\x1a';
        uVar15 = 0;
      }
      goto LAB_00024674;
    }
  }
  size = '\x1a';
  uVar15 = 0;
  uVar16 = 0;
LAB_00024674:
  puVar8 = (u8 *)tl_bufInitalloc(param_1, size);
  *puVar8 = uVar1;
  puVar8[1] = uVar14;
  auStack_4c._0_4_ = puVar8;
  memcpy(puVar8 + 2, auStack_30, 8);
  puVar8[10] = (u8)uVar6;
  puVar8[0xb] = (u8)(uVar6 >> 8);
  cVar12 = (char)puVar8 + '\f';
  dVar4 = af_nodeDevTypeGet();
  if ((((dVar4 == DEVICE_TYPE_COORDINATOR) ||
        (dVar4 = af_nodeDevTypeGet(), dVar4 == DEVICE_TYPE_ROUTER)) &&
       (uVar14 == '\0')) &&
      (bVar2 == 1))
  {
    if (uVar16 == 0)
    {
      puVar8[0xc] = '\0';
      cVar12 = (char)puVar8 + '\r';
    }
    else
    {
      puVar8[0xd] = bVar3;
      puVar13 = puVar8 + 0xe;
      iVar9 = tl_zbNeighborTabSearchForChildEndDev();
      uVar16 = 0;
      if (iVar9 != 0)
      {
        uVar11 = 0;
        do
        {
          uVar11 = uVar11 + 1 & 0xff;
          if (uVar10 <= uVar11)
          {
            uVar6 = tl_zbshortAddrByIdx(*(u16 *)(iVar9 + 0x16));
            *puVar13 = (u8)uVar6;
            uVar6 = tl_zbshortAddrByIdx(*(u16 *)(iVar9 + 0x16));
            puVar13[1] = (u8)((uint)uVar6 >> 8);
            puVar13 = puVar13 + 2;
            uVar16 = uVar16 + 1 & 0xff;
          }
        } while ((uVar16 < uVar15) && (iVar9 = tl_zbNeighborTabSearchForChildEndDev(), iVar9 != 0));
      }
      cVar12 = (char)puVar13;
      puVar8[0xc] = (u8)uVar16;
    }
  }
  p_Stack_38 = ll_reset;
  uStack_3c = (uint)CONCAT12(cVar12 - (char)auStack_4c._0_4_, 0x8001);
  auStack_4c._8_4_ = auStack_4c._8_4_ & 0xffff0000 | (uint) * (ushort *)(param_1->buf + 0x14);
  auStack_4c._4_4_ = param_1;
  zdo_send_req((zdo_zdp_req_t *)auStack_4c);
  zb_buf_free(auStack_4c._4_4_);
  return 0xfffffffe;
}
// WARNING: Could not reconcile some variable overlaps
void zdo_matchDescriptorIndicate(void *buf)

{
  undefined *puVar1;
  af_simple_descriptor_t *paVar2;
  device_type_t dVar3;
  byte bVar4;
  byte *pbVar5;
  af_endpoint_descriptor_t *paVar6;
  u16 *puVar7;
  int iVar8;
  int iVar9;
  byte *pbVar10;
  u8 *puVar11;
  uint uVar12;
  uint uVar13;
  uint uVar14;
  uint uVar15;
  u8 uVar16;
  u16 uVar17;
  uint uVar18;
  ushort uVar19;
  byte bVar20;
  byte bVar21;
  uint local_a8;
  undefined4 *puStack_98;
  int iStack_84;
  u16 uStack_76;
  undefined4 uStack_74;
  undefined4 uStack_70;
  undefined4 uStack_6c;
  undefined4 uStack_68;
  undefined4 uStack_64;
  undefined4 uStack_60;
  undefined4 uStack_5c;
  undefined4 uStack_58;
  undefined2 local_54;
  undefined auStack_50[12];
  undefined4 uStack_44;
  uint local_40;
  zdo_callback p_Stack_3c;
  u8 local_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined local_28;

  puVar1 = *(undefined **)((int)buf + 0xc);
  uStack_34._0_1_ = *puVar1;
  uStack_70 = 0;
  uStack_6c = 0;
  uStack_68 = 0;
  uStack_64 = 0;
  uStack_60 = 0;
  uStack_5c = 0;
  uStack_58 = 0;
  local_54 = 0;
  // WARNING: Load size is inaccurate
  iStack_84 = 0;
  if (*buf == '\x02')
  {
    uVar14 = *(ushort *)((int)buf + 2) & 0xfff8;
    uVar15 = uVar14 - 0xfff8;
    iStack_84 = ~uVar15 + uVar15 + (uint)(0xfff7 < uVar14);
  }
  uVar19 = (ushort)(byte)puVar1[2] * 0x100 + (ushort)(byte)puVar1[1];
  uVar17 = (ushort)(byte)puVar1[4] * 0x100 + (ushort)(byte)puVar1[3];
  bVar4 = puVar1[5];
  uVar14 = (uint)bVar4;
  uStack_74 = (uint)bVar4;
  uStack_76 = uVar17;
  if (0x10 < uVar14)
    goto LAB_00025708;
  pbVar10 = puVar1 + 6;
  if (uVar14 != 0)
  {
    uVar15 = 0;
    pbVar5 = pbVar10;
    do
    {
      (&uStack_76)[uVar15 + 2] = (ushort)pbVar5[1] * 0x100 + (ushort)*pbVar5;
      pbVar5 = pbVar5 + 2;
      uVar15 = uVar15 + 1;
    } while ((uVar15 & 0xff) < uVar14);
    pbVar10 = pbVar10 + ((uVar14 - 1) * 0x1000000 >> 0x17) + 2;
  }
  bVar20 = *pbVar10;
  uStack_74 = (uint)CONCAT11(bVar20, bVar4);
  uVar15 = uVar14 + bVar20;
  if (0x10 < uVar15)
    goto LAB_00025708;
  if ((uVar14 < uVar15) && (uVar14 < 0x10))
  {
    pbVar10 = pbVar10 + 1;
    uVar12 = uVar14;
    do
    {
      (&uStack_76)[uVar12 + 2] = (ushort)pbVar10[1] * 0x100 + (ushort)*pbVar10;
      pbVar10 = pbVar10 + 2;
      uVar12 = uVar12 + 1 & 0xff;
      if (uVar15 <= uVar12)
        break;
    } while (uVar12 < 0x10);
  }
  auStack_50._0_4_ = (u8 *)0x0;
  auStack_50._4_4_ = (zb_buf_t *)0x0;
  uStack_44 = 0;
  local_40 = 0;
  p_Stack_3c = ll_reset;
  local_38 = '\0';
  auStack_50._8_4_ = (uint) * (ushort *)((int)buf + 0x14);
  uStack_34 = 0;
  uStack_30 = 0;
  uStack_2c = 0;
  local_28 = 0;
  if ((g_zbInfo.macPib.shortAddress != uVar19) && ((uVar19 & 0xfff8) != 0xfff8))
  {
    dVar3 = af_nodeDevTypeGet();
    if (dVar3 == DEVICE_TYPE_END_DEVICE)
    {
      uVar16 = '\x05';
    }
    else
    {
      uVar16 = '\x05';
    }
    goto LAB_000256c0;
  }
  if ((uVar14 != 0) || (local_a8 = 0, bVar20 != 0))
  {
    bVar4 = af_availableEpNumGet();
    paVar6 = af_epDescriptorGet();
    if (bVar4 != 0)
    {
      uVar12 = uStack_74 & 0xff;
      uVar15 = uStack_74 >> 8 & 0xff;
      local_a8 = uStack_30 & 0xff;
      bVar20 = 0;
      uVar14 = 0;
    LAB_00025788:
      paVar2 = paVar6->correspond_simple_desc;
      if ((paVar2->app_profile_id == uVar17) || (uVar17 == 0xffff))
      {
        if (uVar12 != 0)
        {
          puVar7 = paVar2->app_in_cluster_lst;
          if (paVar2->app_in_cluster_count != 0)
          {
            bVar21 = 0;
            do
            {
              uVar18 = (uint) * (byte *)((int)puVar7 + 1) * 0x100 + (uint) * (byte *)puVar7 & 0xffff;
              puVar7 = puVar7 + 1;
              if (uVar18 == uStack_74 >> 0x10)
                goto LAB_0002589c;
              uVar13 = 0;
              iVar9 = 0;
              while (uVar13 = uVar13 + 1 & 0xff, uVar13 < uVar12)
              {
                iVar8 = iVar9 + 3;
                iVar9 = iVar9 + 1;
                if ((&uStack_76)[iVar8] == uVar18)
                  goto LAB_0002589c;
              }
              bVar21 = bVar21 + 1;
            } while (bVar21 < paVar2->app_in_cluster_count);
          }
        }
        if (uVar15 != 0)
        {
          puVar7 = paVar2->app_out_cluster_lst;
          if (paVar2->app_out_cluster_count != 0)
          {
            bVar21 = 0;
            do
            {
              uVar17 = (ushort) * (byte *)((int)puVar7 + 1) * 0x100 + (ushort) * (byte *)puVar7;
              puVar7 = puVar7 + 1;
              if (uVar17 == (&uStack_76)[uVar12 + 2])
                goto LAB_0002589c;
              uVar13 = 0;
              uVar18 = uVar12;
              while (true)
              {
                uVar13 = uVar13 + 1 & 0xff;
                if (uVar15 <= uVar13)
                  break;
                iVar9 = uVar18 + 3;
                uVar18 = uVar18 + 1;
                if (uVar17 == (&uStack_76)[iVar9])
                  goto LAB_0002589c;
              }
              bVar21 = bVar21 + 1;
            } while (bVar21 < paVar2->app_out_cluster_count);
          }
        }
      }
      goto LAB_0002576c;
    }
    local_a8 = 0;
  }
LAB_0002590e:
  if (iStack_84 != 0)
  {
  LAB_00025708:
    zb_buf_free((zb_buf_t *)buf);
    return;
  }
LAB_0002591a:
  uVar16 = (char)local_a8 + '\x05';
LAB_000256c0:
  puStack_98 = &uStack_34;
  // WARNING: Ignoring partial resolution of indirect
  local_40._0_3_ = CONCAT12(uVar16, (u16)local_40);
  local_40 = local_40 & 0xff000000 | (uint)(uint3)local_40;
  auStack_50._0_4_ = (u8 *)tl_bufInitalloc((zb_buf_t *)buf, uVar16);
  memcpy(auStack_50._0_4_, puStack_98, local_40 >> 0x10 & 0xff);
  local_40._0_3_ = (uint3)local_40 & 0xff0000 | 0x8006;
  p_Stack_3c = ll_reset;
  local_40 = (uint)(uint3)local_40;
  auStack_50._4_4_ = (zb_buf_t *)buf;
  zdo_send_req((zdo_zdp_req_t *)auStack_50);
  zb_buf_free(auStack_50._4_4_);
  return;
LAB_0002589c:
  if (7 < uVar14)
  {
    // WARNING: Ignoring partial resolution of indirect
    uStack_30._0_1_ = (undefined)local_a8;
    local_a8 = uVar14;
    goto LAB_0002591a;
  }
  if (uVar14 == 0)
  {
    uVar16 = paVar2->endpoint;
  }
  else
  {
    uVar16 = paVar2->endpoint;
    puVar11 = (u8 *)((int)&uStack_30 + 1);
    uVar18 = 0;
    do
    {
      if (*puVar11 == uVar16)
        break;
      uVar18 = uVar18 + 1 & 0xff;
      puVar11 = puVar11 + 1;
    } while (uVar18 < uVar14);
    if (uVar18 != uVar14)
      goto LAB_0002576c;
  }
  *(u8 *)((int)&uStack_30 + uVar14 + 1) = uVar16;
  local_a8 = uVar14 + 1 & 0xff;
LAB_0002576c:
  bVar20 = bVar20 + 1;
  paVar6 = paVar6 + 1;
  uVar14 = local_a8;
  uVar17 = uStack_76;
  if (bVar4 <= bVar20)
    goto LAB_0002593e;
  goto LAB_00025788;
LAB_0002593e:
  // WARNING: Ignoring partial resolution of indirect
  uStack_30._0_1_ = (undefined)local_a8;
  if (local_a8 == 0)
    goto LAB_0002590e;
  goto LAB_0002591a;
}
// WARNING: Could not reconcile some variable overlaps
void zdo_mgmNwkUpdateIndicate(void *buf)

{
  u8 uVar1;
  byte bVar2;
  u8 *puVar3;
  u32 chp;
  short sVar4;
  byte bVar5;
  u8 uVar6;
  int iVar7;
  undefined local_34[12];
  undefined4 uStack_28;
  undefined4 uStack_24;
  zdo_callback p_Stack_20;
  u8 local_1c;
  void *arg;

  puVar3 = *(u8 **)((int)buf + 0xc);
  uVar1 = *puVar3;
  chp = *(u32 *)(puVar3 + 1);
  bVar5 = puVar3[5];
  bVar2 = puVar3[6];
  sVar4 = *(short *)(puVar3 + 7);
  if (bVar5 == 0xfe)
  {
    bVar5 = zdo_channel_page2num(chp);
    arg = (void *)(uint)bVar5;
    uVar6 = zdo_af_get_accept_nwk_update_channel();
    if (((uVar6 != '\0') && (uVar6 = zdo_af_get_accept_nwk_update_channel(), uVar6 != 0xff)) &&
        (bVar5 = zdo_af_get_accept_nwk_update_channel(), (void *)(uint)bVar5 != arg))
      goto LAB_00026212;
    uVar6 = 0x80;
    if ((int)arg - 0xbU < 0x10)
    {
      g_zbInfo.nwkNib.updateId = bVar2;
      ev_timer_taskPost(zdo_change_channel_cb, arg, 0x2e);
      zb_buf_free((zb_buf_t *)buf);
      return;
    }
  }
  else
  {
    if (bVar5 == 0xff)
    {
      aps_ib.aps_channel_mask._0_1_ = (undefined)chp;
      aps_ib.aps_channel_mask._1_1_ = (undefined)(chp >> 8);
      aps_ib.aps_channel_mask._2_1_ = (undefined)(chp >> 0x10);
      aps_ib.aps_channel_mask._3_1_ = (undefined)(chp >> 0x18);
      iVar7 = memcmp(ss_ib.trust_center_address, &g_invalid_addr, 8);
      if ((iVar7 == 0) || (sVar4 == 0))
      {
        g_zbInfo.nwkNib.managerAddr._0_1_ = (undefined)sVar4;
        g_zbInfo.nwkNib.managerAddr._1_1_ = (undefined)((ushort)sVar4 >> 8);
      }
      goto LAB_00026212;
    }
    uVar6 = 0x80;
    if ((bVar5 < 6) && (bVar2 < 6))
    {
      zdo_nur._6_2_ = *(undefined2 *)((int)buf + 0x14);
      zdo_nur._0_4_ = chp;
      zdo_nur[4] = bVar5;
      zdo_nur[5] = bVar2;
      zdo_nur[8] = uVar1;
      iVar7 = (*(code *)&zdo_nlmeEdScanReq)(chp, bVar5, bVar2);
      uVar6 = 0x84;
      if (iVar7 == 0)
      {
        zdo_mgmt_nwk_flag = zdo_mgmt_nwk_flag | 1;
        goto LAB_00026212;
      }
    }
  }
  if ((*(ushort *)((int)buf + 2) & 0xfff8) != 0xfff8)
  {
    local_34._0_4_ = (u8 *)0x0;
    local_34._4_4_ = (u8 *)0x0;
    local_34._8_4_ = 0;
    uStack_28 = 0;
    p_Stack_20 = ll_reset;
    local_1c = '\0';
    uStack_24 = 0x20000;
    local_34._0_4_ = (u8 *)tl_bufInitalloc((zb_buf_t *)buf, '\x02');
    *local_34._0_4_ = uVar1;
    local_34._0_4_[1] = uVar6;
    local_34._8_4_ = local_34._8_4_ & 0xffff0000 | (uint) * (ushort *)((int)buf + 0x14);
    uStack_24 = CONCAT22((ushort)((uint)uStack_24 >> 0x10) & 0xff, 0x8038);
    local_34._4_4_ = (u8 *)buf;
    zdo_send_req((zdo_zdp_req_t *)local_34);
  }
LAB_00026212:
  zb_buf_free((zb_buf_t *)buf);
  return;
}
// WARNING: Could not reconcile some variable overlaps
void zdo_mgmtBindIndicate(void *buf)

{
  u8 uVar1;
  byte bVar2;
  uint uVar3;
  u8 *puVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  u8 *out;
  uint uVar8;
  uint local_44;
  undefined auStack_40[12];
  undefined4 uStack_34;
  uint uStack_30;
  zdo_callback p_Stack_2c;
  u8 local_28;

  uVar1 = **(u8 **)((int)buf + 0xc);
  bVar2 = (*(u8 **)((int)buf + 0xc))[1];
  uVar5 = (uint)bVar2;
  if ((*(ushort *)((int)buf + 2) & 0xfff8) != 0xfff8)
  {
    auStack_40._0_4_ = (u8 *)0x0;
    auStack_40._4_4_ = (zb_buf_t *)0x0;
    auStack_40._8_4_ = 0;
    uStack_34 = 0;
    uStack_30 = 0;
    p_Stack_2c = ll_reset;
    local_28 = '\0';
    uVar3 = aps_bindingTblEntryNum();
    puVar4 = (u8 *)aps_bindingTblEntryGet();
    local_44 = 0;
    if (uVar5 < uVar3)
    {
      local_44 = 2;
      if ((int)(uVar3 - uVar5) < 2)
      {
        local_44 = uVar3 - uVar5 & 0xff;
      }
    }
    auStack_40._0_4_ = (u8 *)tl_bufInitalloc((zb_buf_t *)buf, '/');
    *auStack_40._0_4_ = uVar1;
    auStack_40._0_4_[1] = '\0';
    auStack_40._0_4_[2] = (u8)uVar3;
    auStack_40._0_4_[3] = bVar2;
    auStack_40._0_4_[4] = (u8)local_44;
    out = auStack_40._0_4_ + 5;
    if (APS_BINDING_TABLE_SIZE != '\0')
    {
      iVar7 = 0;
      uVar8 = 0;
      uVar3 = 0;
      do
      {
        uVar6 = uVar3;
        if ((puVar4[0xd] != '\0') && (uVar6 = uVar3 + 1 & 0xff, uVar5 <= uVar3))
        {
          memcpy(out, g_zbInfo.macPib.extAddress, 8);
          out[8] = puVar4[2];
          out[9] = *puVar4;
          out[10] = puVar4[1];
          out[0xb] = puVar4[3];
          if (puVar4[3] == '\x03')
          {
            memcpy(out + 0xc, puVar4 + 4, 8);
            out[0x14] = puVar4[0xc];
            out = out + 0x15;
          }
          else
          {
            out[0xc] = puVar4[4];
            out[0xd] = puVar4[5];
            out = out + 0xe;
          }
          uVar8 = uVar8 + 1 & 0xff;
          if (local_44 <= uVar8)
            break;
        }
        iVar7 = iVar7 + 1;
        if ((int)(uint)APS_BINDING_TABLE_SIZE <= iVar7)
          break;
        puVar4 = puVar4 + 0xe;
        uVar3 = uVar6;
      } while (true);
    }
    uStack_30 = (uint)CONCAT12((char)out - (char)auStack_40._0_4_, 0x8033);
    auStack_40._8_4_ = auStack_40._8_4_ & 0xffff0000 | (uint) * (ushort *)((int)buf + 0x14);
    auStack_40._4_4_ = (zb_buf_t *)buf;
    zdo_send_req((zdo_zdp_req_t *)auStack_40);
    buf = auStack_40._4_4_;
  }
  zb_buf_free((zb_buf_t *)buf);
  return;
}
void zdo_mgmtLeaveIndicate(void *buf)

{
  undefined uVar1;
  ushort uVar2;
  bool bVar3;
  int iVar4;
  undefined *puVar5;
  void *out;
  tl_zb_normal_neighbor_entry_t *ptVar6;
  char cVar7;
  u8 *in_stack_ffffffb8;
  u8 *in_stack_ffffffbc;
  undefined auStack_2c[8];
  byte bStack_24;

  uVar1 = **(undefined **)((int)buf + 0xc);
  memcpy(auStack_2c, *(undefined **)((int)buf + 0xc) + 1, 9);
  uVar2 = *(ushort *)((int)buf + 2);
  iVar4 = memcmp(auStack_2c, &g_zero_addr, 8);
  cVar7 = -0x7c;
  if ((iVar4 != 0) && (iVar4 = memcmp(auStack_2c, g_zbInfo.macPib.extAddress, 8), iVar4 != 0))
  {
    ptVar6 = nwk_neTblGetByExtAddr((addrExt_t)CONCAT44(in_stack_ffffffbc, in_stack_ffffffb8));
    cVar7 = -0x38;
    if (ptVar6 != (tl_zb_normal_neighbor_entry_t *)0x0)
    {
      cVar7 = -0x38;
    }
  }
  bVar3 = zdo_af_get_mgmtLeave_use_aps_sec();
  if ((bVar3 != false) && (-1 < (int)((uint) * (byte *)((int)buf + 0x1f) << 0x1f)))
  {
    cVar7 = -0x73;
  }
  if ((uVar2 & 0xfff8) == 0xfff8)
  {
    zb_buf_free((zb_buf_t *)buf);
  }
  else
  {
    puVar5 = (undefined *)tl_bufInitalloc((zb_buf_t *)buf, '\x02');
    *puVar5 = uVar1;
    puVar5[1] = cVar7;
    zdo_send_req((zdo_zdp_req_t *)&stack0xffffffb8);
    zb_buf_free((zb_buf_t *)buf);
  }
  if ((cVar7 == '\0') && (out = (void *)c1(), out != (void *)0x0))
  {
    memcpy(out, auStack_2c, 8);
    *(byte *)((int)out + 8) = (byte)(((uint)bStack_24 << 0x19) >> 0x1f);
    *(byte *)((int)out + 9) = bStack_24 >> 7;
    ev_timer_taskPost(zdoMgmtLeaveCmdProcessCb, out, 100);
  }
  return;
}
// WARNING: Could not reconcile some variable overlaps
void zdo_mgmtLqiIndictate(void *buf)

{
  u8 uVar1;
  byte bVar2;
  u16 uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  u8 *puStack_64;
  uint uStack_60;
  undefined auStack_58[12];
  undefined4 uStack_4c;
  undefined4 uStack_48;
  zdo_callback p_Stack_44;
  u8 local_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined2 local_28;
  uint extraout_r0;

  uVar1 = **(u8 **)((int)buf + 0xc);
  uVar5 = (uint)(*(u8 **)((int)buf + 0xc))[1];
  if ((*(ushort *)((int)buf + 2) & 0xfff8) != 0xfff8)
  {
    auStack_58._0_4_ = (u8 *)0x0;
    auStack_58._4_4_ = (zb_buf_t *)0x0;
    auStack_58._8_4_ = 0;
    uStack_4c = 0;
    uStack_48 = 0;
    p_Stack_44 = ll_reset;
    local_40 = '\0';
    uStack_3c = 0;
    uStack_38 = 0;
    uStack_34 = 0;
    uStack_30 = 0;
    uStack_2c = 0;
    local_28 = 0;
    puStack_64 = (u8 *)tl_bufInitalloc((zb_buf_t *)buf, '1');
    *puStack_64 = uVar1;
    puStack_64[1] = '\0';
    auStack_58._0_4_ = puStack_64;
    bVar2 = tl_zbNeighborTableNumGet();
    extraout_r0 = (uint)bVar2;
    puStack_64[2] = bVar2;
    puStack_64[3] = (u8)uVar5;
    if ((extraout_r0 < uVar5) || (extraout_r0 == 0))
    {
      puStack_64[4] = '\0';
      puStack_64 = puStack_64 + 5;
      memcpy(&uStack_3c, g_zbInfo.nwkNib.extPANId, 8);
    }
    else
    {
      uVar4 = extraout_r0 - uVar5;
      if (2 < (int)uVar4)
      {
        uVar4 = 2;
      }
      puStack_64[4] = (u8)uVar4;
      puStack_64 = puStack_64 + 5;
      memcpy(&uStack_3c, g_zbInfo.nwkNib.extPANId, 8);
      if (((uVar4 & 0xff) != 0) && (TL_ZB_NEIGHBOR_TABLE_SIZE != '\0'))
      {
        uStack_60 = 0;
        uVar7 = 0;
        uVar6 = 0;
        do
        {
          if ((char)g_zb_neighborTbl.neighborTbl[uVar6].field_0x1e < '\0')
          {
            if (uVar5 <= uVar7)
            {
              uVar3 = g_zb_neighborTbl.neighborTbl[uVar6].addrmapIdx;
              tl_zbExtAddrByIdx(uVar3, (addrExt_t)CONCAT44(buf, uVar5));
              uVar3 = tl_zbshortAddrByIdx(uVar3);
              uStack_2c = CONCAT13(2, CONCAT12((byte)(((byte)g_zb_neighborTbl.neighborTbl[uVar6].field_0x1e & 1) << 2) |
                                                   (byte)g_zb_neighborTbl.neighborTbl[uVar6].field_0x1e >> 1 & 3 |
                                                   (byte)(((byte)g_zb_neighborTbl.neighborTbl[uVar6].field_0x1e >> 4 & 7) << 4),
                                               uVar3));
              local_28 = CONCAT11(g_zb_neighborTbl.neighborTbl[uVar6].lqi,
                                  g_zb_neighborTbl.neighborTbl[uVar6].depth);
              memcpy(puStack_64, &uStack_3c, 0x16);
              puStack_64 = puStack_64 + 0x16;
              uStack_60 = uStack_60 + 1 & 0xff;
              if ((uVar4 & 0xff) <= uStack_60)
                break;
            }
            uVar7 = uVar7 + 1 & 0xff;
          }
          uVar6 = uVar6 + 1 & 0xff;
        } while (uVar6 < TL_ZB_NEIGHBOR_TABLE_SIZE);
      }
    }
    uStack_48 = CONCAT22((ushort)(byte)((char)puStack_64 - (char)auStack_58._0_4_), 0x8031);
    auStack_58._8_4_ = auStack_58._8_4_ & 0xffff0000 | (uint) * (ushort *)((u8 *)buf + 0x14);
    auStack_58._4_4_ = (zb_buf_t *)buf;
    zdo_send_req((zdo_zdp_req_t *)auStack_58);
    buf = auStack_58._4_4_;
  }
  zb_buf_free((zb_buf_t *)buf);
  return;
}
// WARNING: Could not reconcile some variable overlaps
void zdo_mgmtPermitJoinIndicate(void *buf)

{
  u8 uVar1;
  zb_buf_t *p;
  undefined local_38[12];
  undefined4 uStack_2c;
  uint uStack_28;
  zdo_callback p_Stack_24;
  u8 local_20;
  u8 local_1c[4];

  uVar1 = **(u8 **)((int)buf + 0xc);
  local_1c[0] = (*(u8 **)((int)buf + 0xc))[1];
  if ((*(ushort *)((int)buf + 2) & 0xfff8) != 0xfff8)
  {
    local_38._0_4_ = (u8 *)0x0;
    local_38._4_4_ = (zb_buf_t *)0x0;
    local_38._8_4_ = 0;
    uStack_2c = 0;
    p_Stack_24 = ll_reset;
    local_20 = '\0';
    uStack_28 = 0x20000;
    p = (zb_buf_t *)c1();
    if (p == (zb_buf_t *)0x0)
    {
      zb_buf_free((zb_buf_t *)buf);
      return;
    }
    local_38._4_4_ = p;
    local_38._0_4_ = (u8 *)tl_bufInitalloc(p, '\x02');
    *local_38._0_4_ = uVar1;
    local_38._0_4_[1] = '\0';
    uStack_28 = (uint)((uint3)uStack_28 & 0xff0000 | 0x8036);
    local_38._8_4_ = local_38._8_4_ & 0xffff0000 | (uint) * (ushort *)((int)buf + 0x14);
    zdo_send_req((zdo_zdp_req_t *)local_38);
    zb_buf_free(local_38._4_4_);
  }
  *(u8 *)buf = local_1c[0];
  tl_zbPrimitivePost('\x03', 'w', buf);
  if ((zdoAppIndCbLst != 0) && (*(int *)(zdoAppIndCbLst + 0x18) != 0))
  {
    zdo_nwkUpdateNotifyRespSend(local_1c);
  }
  return;
}
void zdo_nwkAddrIndicate(void *buf)

{
  ev_timer_taskPost(zdo_nwkAddrReqDelayCb, buf, 200);
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
undefined4 zdo_nwkAddrReqDelayCb(void)

{
  device_type_t dVar1;
  byte bVar2;
  u16 uVar3;
  zb_buf_t *in_r0;
  tl_zb_normal_neighbor_entry_t *ptVar4;
  int iVar5;
  undefined *puVar6;
  u8 size;
  uint uVar7;
  undefined *puVar8;
  char cVar9;
  undefined uVar10;
  uint in_stack_ffffffa4;
  uint uVar11;
  u8 *puVar12;
  undefined4 local_3c;
  undefined4 uStack_38;
  byte bStack_34;
  byte bStack_33;
  undefined4 local_30;
  undefined4 uStack_2c;
  u16 local_26;
  uint extraout_r0;

  uVar10 = **(undefined **)(in_r0->buf + 0xc);
  memcpy(&local_3c, *(undefined **)(in_r0->buf + 0xc) + 1, 10);
  puVar12 = (u8 *)0x0;
  local_26 = 0xfffe;
  ptVar4 = nwk_neTblGetByExtAddr((addrExt_t)(ulonglong)in_stack_ffffffa4);
  iVar5 = memcmp(&local_3c, g_zbInfo.macPib.extAddress, 8);
  if ((iVar5 == 0) ||
      ((ptVar4 != (tl_zb_normal_neighbor_entry_t *)0x0 && ((ptVar4->field_0x1e & 0xe) == 4))))
  {
    if (bStack_34 < 2)
    {
      cVar9 = '\0';
      goto LAB_000248f0;
    }
    if ((*(ushort *)(in_r0->buf + 2) & 0xfff8) == 0xfff8)
      goto LAB_00024ad4;
    cVar9 = -0x80;
  }
  else
  {
    if ((*(ushort *)(in_r0->buf + 2) & 0xfff8) == 0xfff8)
    {
    LAB_00024ad4:
      zb_buf_free(in_r0);
      return 0xfffffffe;
    }
    cVar9 = -0x7f;
  LAB_000248f0:
    local_30 = uStack_38;
    uStack_2c = local_3c;
    if (bStack_34 == 0)
    {
      if (cVar9 == '\0')
      {
        tl_zbShortAddrByExtAddr(&local_26, (addrExt_t)CONCAT44(puVar12, in_stack_ffffffa4), (u16 *)&local_3c);
        size = '\x1a';
        uVar7 = 0;
        uVar11 = 0;
      }
      else
      {
        size = '\x1a';
        uVar7 = 0;
        uVar11 = 0;
      }
      goto LAB_00024910;
    }
  }
  uStack_2c = local_3c;
  local_30 = uStack_38;
  if (bStack_34 == 1)
  {
    if (cVar9 == '\0')
    {
      memcpy(&local_30, g_zbInfo.macPib.extAddress, 8);
      local_26 = g_zbInfo.macPib.shortAddress;
      dVar1 = af_nodeDevTypeGet();
      if ((dVar1 == DEVICE_TYPE_COORDINATOR) ||
          (dVar1 = af_nodeDevTypeGet(), dVar1 == DEVICE_TYPE_ROUTER))
      {
        bVar2 = tl_zbNeighborTableChildEDNumGet();
        extraout_r0 = (uint)bVar2;
        uVar11 = extraout_r0;
        if (extraout_r0 == 0)
        {
          size = '\x1a';
          uVar7 = 0;
        }
        else if (bStack_33 < extraout_r0)
        {
          uVar7 = extraout_r0 - bStack_33 & 0xff;
          if (uVar7 * 2 < 0x1f)
          {
            size = (char)(uVar7 * 2) + '\x1a';
          }
          else
          {
            size = '9';
            uVar7 = 0xf;
          }
        }
        else
        {
          size = '\x1a';
          uVar7 = 0;
        }
      }
      else
      {
        size = '\x1a';
        uVar7 = 0;
        uVar11 = 0;
      }
    }
    else
    {
      size = '\x1a';
      uVar7 = 0;
      uVar11 = 0;
    }
  }
  else
  {
    tl_zbShortAddrByExtAddr(&local_26, (addrExt_t)CONCAT44(puVar12, in_stack_ffffffa4), (u16 *)&local_3c);
    size = '\x1a';
    uVar7 = 0;
    uVar11 = 0;
  }
LAB_00024910:
  puVar6 = (undefined *)tl_bufInitalloc(in_r0, size);
  *puVar6 = uVar10;
  puVar6[1] = cVar9;
  memcpy(puVar6 + 2, &local_30, 8);
  puVar6[10] = (char)local_26;
  puVar6[0xb] = (char)(local_26 >> 8);
  dVar1 = af_nodeDevTypeGet();
  if ((((dVar1 == DEVICE_TYPE_COORDINATOR) ||
        (dVar1 = af_nodeDevTypeGet(), dVar1 == DEVICE_TYPE_ROUTER)) &&
       (cVar9 == '\0')) &&
      (bStack_34 == 1))
  {
    if (uVar11 == 0)
    {
      puVar6[0xc] = 0;
    }
    else
    {
      puVar6[0xd] = bStack_33;
      puVar8 = puVar6 + 0xe;
      iVar5 = tl_zbNeighborTabSearchForChildEndDev();
      uVar11 = 0;
      uVar10 = 0;
      if (iVar5 != 0)
      {
        bVar2 = 0;
        do
        {
          bVar2 = bVar2 + 1;
          if (bStack_33 <= bVar2)
          {
            uVar3 = tl_zbshortAddrByIdx(*(u16 *)(iVar5 + 0x16));
            *puVar8 = (char)uVar3;
            uVar3 = tl_zbshortAddrByIdx(*(u16 *)(iVar5 + 0x16));
            puVar8[1] = (char)((uint)uVar3 >> 8);
            puVar8 = puVar8 + 2;
            uVar11 = uVar11 + 1 & 0xff;
          }
          uVar10 = (undefined)uVar11;
        } while ((uVar11 < uVar7) && (iVar5 = tl_zbNeighborTabSearchForChildEndDev(), iVar5 != 0));
      }
      puVar6[0xc] = uVar10;
    }
  }
  zdo_send_req((zdo_zdp_req_t *)&stack0xffffffa8);
  zb_buf_free(in_r0);
  return 0xfffffffe;
}
// WARNING: Could not reconcile some variable overlaps
void zdo_nwkUpdateNotifyRespSend(void *buf)

{
  undefined4 uVar1;
  zb_buf_t *p;
  u8 *puVar2;
  code *in_r3;
  uint uVar3;
  u8 local_114[3];
  byte bStack_111;
  u8 auStack_10c[216];
  undefined auStack_34[12];
  undefined4 uStack_28;
  uint uStack_24;
  zdo_callback p_Stack_20;
  u8 local_1c;

  p = (zb_buf_t *)(*in_r3)();
  memcpy(local_114, p, 0xe0);
  auStack_34._0_4_ = (u8 *)0x0;
  auStack_34._4_4_ = (zb_buf_t *)0x0;
  auStack_34._8_4_ = 0;
  uStack_28 = 0;
  uStack_24 = 0;
  p_Stack_20 = ll_reset;
  local_1c = '\0';
  auStack_34._0_4_ = (u8 *)tl_bufInitalloc(p, bStack_111 + 0xb);
  *auStack_34._0_4_ = zdo_nur[8];
  auStack_34._0_4_[1] = local_114[0];
  uVar1 = zdo_nur._0_4_;
  auStack_34._0_4_[2] = (u8)zdo_nur._0_4_;
  auStack_34._0_4_[3] = (u8)((uint)uVar1 >> 8);
  auStack_34._0_4_[4] = (u8)((uint)uVar1 >> 0x10);
  auStack_34._0_4_[5] = (u8)((uint)uVar1 >> 0x18);
  auStack_34._0_4_[6] = (u8)g_zbInfo.nwkNib.txTotal;
  auStack_34._0_4_[7] = g_zbInfo.nwkNib.txTotal._1_1_;
  auStack_34._0_4_[8] = (u8)g_zbInfo.nwkNib.txFail;
  auStack_34._0_4_[9] = g_zbInfo.nwkNib.txFail._1_1_;
  auStack_34._0_4_[10] = bStack_111;
  puVar2 = auStack_34._0_4_ + 0xb;
  uVar3 = 0;
  do
  {
    *puVar2 = auStack_10c[uVar3];
    puVar2 = puVar2 + 1;
    uVar3 = uVar3 + 1 & 0xff;
  } while (uVar3 <= bStack_111);
  uStack_24 = (uint)CONCAT12((char)puVar2 - (char)auStack_34._0_4_, 0x8038);
  auStack_34._8_4_ = auStack_34._8_4_ & 0xffff0000 | (uint)zdo_nur._6_2_;
  auStack_34._4_4_ = p;
  zdo_send_req((zdo_zdp_req_t *)auStack_34);
  zb_buf_free(auStack_34._4_4_);
  return;
}
void zdo_parentAnnounceIndicate(void *buf)

{
  u32 uVar1;

  uVar1 = drv_u32Rand();
  ev_timer_taskPost(zdo_parentAnnounceIndicateDelay, buf, (uVar1 & 0x1f) * 0x32 + 1000);
  return;
}
// WARNING: Could not reconcile some variable overlaps
// WARNING: Unknown calling convention -- yet parameter storage is locked
undefined4 zdo_parentAnnounceIndicateDelay(void)

{
  byte bVar1;
  zb_buf_t *in_r0;
  u8 *pBuf;
  zb_buf_t *p;
  u8 *puVar2;
  u8 *puVar3;
  u8 *out;
  int iVar4;
  u8 *m2;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  u8 *puVar9;
  undefined local_50[12];
  undefined4 uStack_44;
  uint uStack_40;
  zdo_callback p_Stack_3c;
  u8 local_38;
  undefined auStack_34[8];
  uint local_2c;
  undefined uStack_28;

  puVar9 = *(u8 **)(in_r0->buf + 0xc);
  uStack_28 = 0;
  puVar3 = puVar9 + 1;
  bVar1 = puVar9[1];
  uVar5 = (uint)bVar1;
  local_2c = (uint)bVar1;
  iVar4 = (int)(char)bVar1;
  if (10 < iVar4)
    goto LAB_00024cc6;
  local_50._0_4_ = (u8 *)0x0;
  local_50._4_4_ = (zb_buf_t *)0x0;
  local_50._8_4_ = 0;
  uStack_44 = 0;
  uStack_40 = 0;
  p_Stack_3c = ll_reset;
  local_38 = '\0';
  pBuf = ev_buf_allocate((u16)((uint)(iVar4 << 0x13) >> 0x10));
  if (pBuf == (u8 *)0x0)
    goto LAB_00024ca8;
  memcpy(pBuf, puVar9 + 2, iVar4 << 3);
  p = (zb_buf_t *)c1();
  if (p == (zb_buf_t *)0x0)
  {
    ev_buf_free(pBuf);
    zb_buf_free(in_r0);
    return 0xfffffffe;
  }
  puVar2 = (u8 *)tl_bufInitalloc(p, 'K');
  *puVar2 = *puVar9;
  puVar2[1] = '\0';
  local_50._0_4_ = puVar2;
  if (0 < iVar4)
  {
    out = puVar2 + 3;
    uVar8 = 0;
    uVar7 = 0;
    m2 = pBuf;
    do
    {
      iVar4 = tl_zbNeighborTabSearchForChildEndDev();
      while (iVar4 != 0)
      {
        tl_zbExtAddrByIdx(*(u16 *)(iVar4 + 0x16), (addrExt_t)CONCAT44(out, puVar9));
        iVar4 = memcmp(auStack_34, m2, 8);
        if (iVar4 == 0)
        {
          uVar8 = uVar8 + 1 & 0xff;
          if (uVar7 < 9)
          {
            uVar7 = uVar7 + 1 & 0xff;
            memcpy(out, auStack_34, 8);
            out = out + 8;
          }
          if (uVar7 < uVar8)
          {
            *puVar3 = (u8)(uVar8 - uVar7);
            memcpy(puVar9 + (uVar8 - uVar7) * 8 + 2, auStack_34, 8);
          }
          break;
        }
        iVar4 = tl_zbNeighborTabSearchForChildEndDev();
      }
      uVar6 = uVar5 - 1;
      uVar5 = uVar6 & 0xff;
      if ((int)(uVar6 * 0x1000000) < 1)
        goto LAB_00024c50;
      m2 = m2 + 8;
    } while (true);
  }
  puVar2[2] = '\0';
  ev_buf_free(pBuf);
  goto LAB_00024cbe;
LAB_00024c50:
  puVar2[2] = (u8)uVar7;
  ev_buf_free(pBuf);
  if (uVar7 != 0)
  {
    p_Stack_3c = ll_reset;
    uStack_40 = (uint)CONCAT12((u8)uVar7 * '\b' + '\x03', 0x801f);
    local_50._8_4_ = local_50._8_4_ & 0xffff0000 | (uint) * (ushort *)(in_r0->buf + 0x14);
    local_50._4_4_ = p;
    zdo_send_req((zdo_zdp_req_t *)local_50);
    zb_buf_free(local_50._4_4_);
    if (uVar7 < uVar8)
    {
      return 0;
    }
  LAB_00024ca8:
    zb_buf_free(in_r0);
    return 0xfffffffe;
  }
LAB_00024cbe:
  zb_buf_free(in_r0);
  in_r0 = p;
LAB_00024cc6:
  zb_buf_free(in_r0);
  return 0xfffffffe;
}
void zdo_parentAnnounceNotify(void *buf)

{
  byte bVar1;
  u16 uVar2;
  tl_zb_normal_neighbor_entry_t *entry;
  byte bVar3;
  undefined in_stack_ffffffd0;
  undefined in_stack_ffffffd1;
  undefined6 in_stack_ffffffd2;

  bVar1 = *(byte *)(*(int *)((int)buf + 0xc) + 2);
  if ((*(char *)(*(int *)((int)buf + 0xc) + 1) == '\0') && (bVar1 != 0))
  {
    bVar3 = 0;
    do
    {
      entry = nwk_neTblGetByExtAddr((addrExt_t)
                                        CONCAT62(in_stack_ffffffd2, CONCAT11(in_stack_ffffffd1, in_stack_ffffffd0)));
      if (entry != (tl_zb_normal_neighbor_entry_t *)0x0)
      {
        uVar2 = tl_zbshortAddrByIdx(entry->addrmapIdx);
        in_stack_ffffffd0 = (undefined)uVar2;
        in_stack_ffffffd1 = (undefined)(uVar2 >> 8);
        tl_zbExtAddrByIdx(entry->addrmapIdx, (addrExt_t)CONCAT62(in_stack_ffffffd2, uVar2));
        nwk_nodeAddrInfoDelete();
        tl_zbNeighborTableDelete(entry);
      }
      bVar3 = bVar3 + 1;
    } while (bVar3 < bVar1);
  }
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void zdo_parent_announce_send(void)

{
  byte bVar1;
  zb_buf_t *p;
  u8 *puVar2;
  u8 uVar3;
  uint uVar4;
  uint uVar5;
  u8 *puVar6;

  uVar5 = (uint)remainChildListNum_8696;
  if (uVar5 == 0)
  {
    bVar1 = tl_zbNeighborTableChildEDNumGet();
    uVar5 = (uint)bVar1;
  }
  if (uVar5 < 10)
  {
    remainChildListNum_8696 = '\0';
    if (uVar5 == 0)
    {
      remainChildListNum_8696 = 0;
      return;
    }
  }
  else
  {
    remainChildListNum_8696 = (char)uVar5 + -10;
    uVar5 = 10;
  }
  p = (zb_buf_t *)c1();
  if (p != (zb_buf_t *)0x0)
  {
    puVar2 = (u8 *)tl_bufInitalloc(p, (u8)(uVar5 * 0x8000000 + 0x2000000 >> 0x18));
    uVar3 = zdp_txSeqNo + '\x01';
    *puVar2 = zdp_txSeqNo;
    zdp_txSeqNo = uVar3;
    puVar2[1] = (u8)uVar5;
    uVar4 = 0;
    puVar6 = puVar2;
    do
    {
      uVar3 = (u8)uVar4;
      ent_8695 = tl_zbNeighborTabSearchForChildEndDev();
      if (ent_8695 == 0)
      {
        remainChildListNum_8696 = '\0';
        break;
      }
      tl_zbExtAddrByIdx(*(u16 *)(ent_8695 + 0x16), (addrExt_t)CONCAT44(p, puVar6));
      uVar4 = uVar4 + 1 & 0xff;
      uVar3 = (u8)uVar4;
    } while (uVar4 < uVar5);
    puVar2[1] = uVar3;
    zdo_send_req((zdo_zdp_req_t *)&stack0xffffffc4);
    zb_buf_free(p);
    if (remainChildListNum_8696 != '\0')
    {
      zdo_apsParentAnnceTimerStart();
    }
  }
  return;
}
void zdo_remoteAddrNotify(void *buf)

{
  int iVar1;
  undefined in_stack_ffffffd0;
  char cVar2;
  undefined6 in_stack_ffffffd2;
  u16 auStack_26[8];
  undefined2 local_16;

  iVar1 = *(int *)((int)buf + 0xc);
  cVar2 = *(char *)(iVar1 + 1);
  if (cVar2 == '\0')
  {
    memcpy(&stack0xffffffd2, (void *)(iVar1 + 2), 8);
    memcpy(auStack_26, (void *)(iVar1 + 10), 2);
    local_16 = 0;
    tl_zbNwkAddrMapAdd(auStack_26[0],
                       (addrExt_t)CONCAT62(in_stack_ffffffd2, CONCAT11(cVar2, in_stack_ffffffd0)),
                       (u16 *)&stack0xffffffd2);
  }
  return;
}
// WARNING: Could not reconcile some variable overlaps
void zdo_send_req(zdo_zdp_req_t *req)

{
  u16 clusterId;
  zdo_callback p_Var1;
  ushort uVar2;
  uint uVar3;
  u8 *cmdPld;
  int iVar4;
  uint local_2c;
  undefined4 uStack_28;
  uint uStack_24;
  undefined4 uStack_20;
  undefined2 local_1c;
  u8 local_19;

  local_19 = '\0';
  clusterId = req->cluster_id;
  local_2c = 0;
  uStack_28 = 0;
  uStack_24 = 0;
  uStack_20 = 0;
  local_1c = 4;
  if (req->dst_addr_mode == SHORT_ADDR_MODE)
  {
    uStack_20 = 0x20000;
    local_2c = (uint)(req->field_2).dst_nwk_addr;
  }
  else if (req->dst_addr_mode == EXT_ADDR_MODE)
  {
    uStack_20 = 0x20000;
    memcpy((epInfo_t *)&local_2c, &req->field_2, 8);
  }
  if (clusterId == 0x13)
  {
    cmdPld = req->zdu;
    uVar2 = (ushort)cmdPld[2] * 0x100 + (ushort)cmdPld[1];
    if (g_zbInfo.nwkNib.nwkAddr != uVar2)
    {
      uStack_24 = uStack_24 & 0xffff | (uint)uVar2 << 0x10;
      uStack_20 = CONCAT22((short)((uint)uStack_20 >> 0x10), 1);
    }
  }
  else
  {
    cmdPld = req->zdu;
  }
  af_dataSend('\0', (epInfo_t *)&local_2c, clusterId, (ushort)req->zduLen, cmdPld, &local_19);
  p_Var1 = req->zdoRspReceivedIndCb;
  if (p_Var1 != ll_reset)
  {
    uVar3 = (uint)zdpCblWptr;
    zdpCblWptr = zdpCblWptr + 1;
    iVar4 = (uVar3 & 3) * 8;
    *(ushort *)(zdp_cbl + iVar4 + 4) = (ushort)req->zdpSeqNum;
    *(zdo_callback *)(zdp_cbl + iVar4) = p_Var1;
    zdp_cbl[iVar4 + 6] = 1;
    zdp_cbl[iVar4 + 7] = 1;
  }
  return;
}
void zdp_cb_process(u16 tsn, void *buf)

{
  char *pcVar1;
  int iVar2;
  int iVar3;

  pcVar1 = zdp_cbl + 7;
  iVar2 = 0;
  while ((*pcVar1 == '\0' || (iVar3 = iVar2 * 8, *(u16 *)(zdp_cbl + iVar3 + 4) != tsn)))
  {
    iVar2 = iVar2 + 1;
    pcVar1 = pcVar1 + 8;
    if (iVar2 == 4)
    {
      return;
    }
  }
  if (*(int *)(zdp_cbl + iVar3) != 0)
  {
    _zdo_send_req();
  }
  zdp_cbl[iVar3 + 7] = 0;
  return;
}
undefined4 zdp_data_send(u32 *param_1, byte param_2, zdo_zdp_req_t *param_3)

{
  u8 uVar1;
  u8 uVar2;
  byte bVar3;
  u8 *pBuf;
  undefined4 uVar4;
  u8 *out;

  pBuf = ev_buf_allocate((ushort)param_2);
  uVar1 = zdp_txSeqNo;
  uVar4 = 0x8a;
  if (pBuf != (u8 *)0x0)
  {
    uVar2 = zdp_txSeqNo + '\x01';
    param_3->zdpSeqNum = zdp_txSeqNo;
    zdp_txSeqNo = uVar2;
    *(char *)&param_3->zdu = (char)pBuf;
    *(char *)((int)&param_3->zdu + 1) = (char)((uint)pBuf >> 8);
    *(char *)((int)&param_3->zdu + 2) = (char)((uint)pBuf >> 0x10);
    *(char *)((int)&param_3->zdu + 3) = (char)((uint)pBuf >> 0x18);
    param_3->zduLen = param_2;
    *pBuf = uVar1;
    if (param_3->cluster_id == 6)
    {
      memcpy(pBuf + 1, param_1, 4);
      pBuf[5] = *(u8 *)(param_1 + 1);
      out = pBuf + 6;
      memcpy(out, (void *)((int)param_1 + 6), (uint) * (byte *)(param_1 + 1) << 1);
      bVar3 = *(byte *)(param_1 + 1);
      out[(uint)bVar3 * 2] = *(u8 *)((int)param_1 + 5);
      memcpy(out + (uint)bVar3 * 2 + 1,
             (void *)((uint) * (byte *)(param_1 + 1) * 2 + (int)(void *)((int)param_1 + 6)),
             (uint) * (byte *)((int)param_1 + 5) << 1);
    }
    else if (param_3->cluster_id == 0x38)
    {
      memcpy(pBuf + 1, param_1, 5);
      bVar3 = *(byte *)(param_1 + 1);
      if (bVar3 < 6)
      {
        pBuf[6] = *(u8 *)((int)param_1 + 5);
      }
      else if (bVar3 == 0xff)
      {
        g_zbInfo.nwkNib.updateId = g_zbInfo.nwkNib.updateId + '\x01';
        pBuf[6] = g_zbInfo.nwkNib.updateId;
        pBuf[7] = *(u8 *)((int)param_1 + 6);
        pBuf[8] = *(u8 *)((int)param_1 + 7);
      }
      else if (bVar3 == 0xfe)
      {
        bVar3 = zdo_channel_page2num(*param_1);
        g_zbInfo.nwkNib.updateId = g_zbInfo.nwkNib.updateId + '\x01';
        pBuf[6] = g_zbInfo.nwkNib.updateId;
        ev_timer_taskPost(zdo_change_channel_cb, (void *)(uint)bVar3, 0x1cc);
      }
    }
    else
    {
      memcpy(pBuf + 1, param_1, param_2 - 1);
    }
    zdo_send_req(param_3);
    ev_buf_free(pBuf);
    uVar4 = 0;
  }
  return uVar4;
}
