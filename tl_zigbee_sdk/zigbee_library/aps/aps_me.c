// WARNING: Unknown calling convention -- yet parameter storage is locked
void aps_bindingTabInit(void)

{
  aps_binding_entry_t *dest;

  dest = bindTblEntryGet();
  memset(dest, 0, (uint)APS_BINDING_TABLE_SIZE * 0xe);
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
// WARNING: Unknown calling convention -- yet parameter storage is locked
undefined4 aps_bindingTblEntryAdd(void)

{
  aps_binding_entry_t *paVar1;
  undefined4 in_r0;
  aps_binding_entry_t *paVar2;
  undefined4 uVar3;
  u8 in_r1;
  u8 in_r2;
  u8 *in_r3;
  int iVar4;
  aps_binding_entry_t *paVar5;

  paVar2 = bindTblEntryGet();
  uVar3 = 0;
  if (APS_BINDING_TABLE_SIZE != 0)
  {
    if (paVar2->used != '\0')
    {
      iVar4 = 0;
      paVar5 = paVar2;
      do
      {
        iVar4 = iVar4 + 1;
        if ((int)(uint)APS_BINDING_TABLE_SIZE <= iVar4)
        {
          return 0;
        }
        paVar2 = paVar5 + 1;
        paVar1 = paVar5 + 1;
        paVar5 = paVar2;
      } while (paVar1->used != '\0');
    }
    paVar2->used = '\x01';
    *(char *)&paVar2->clusterId = (char)in_r0;
    *(char *)((int)&paVar2->clusterId + 1) = (char)((uint)in_r0 >> 8);
    paVar2->srcEp = in_r1;
    paVar2->dstAddrMode = in_r2;
    if (in_r2 == '\x03')
    {
      memcpy(&paVar2->field_3, in_r3, 8);
      (paVar2->field_3).dstExtAddrInfo.dstEp = in_r3[8];
      uVar3 = 1;
    }
    else
    {
      uVar3 = 0;
      if (in_r2 == '\x01')
      {
        (paVar2->field_3).dstExtAddrInfo.extAddr[0] = *in_r3;
        (paVar2->field_3).dstExtAddrInfo.extAddr[1] = in_r3[1];
        uVar3 = 1;
      }
    }
  }
  return uVar3;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void aps_bindingTblEntryDel(void)

{
  void *in_r0;
  int iVar1;
  aps_binding_entry_t *paVar2;
  uint uVar3;

  iVar1 = aps_bindingTblEntryNum();
  paVar2 = bindTblEntryGet();
  if (in_r0 != (void *)0x0)
  {
    *(undefined *)((int)in_r0 + 0xd) = 0;
    uVar3 = ((int)in_r0 - (int)paVar2 >> 1) * -0x49249249 & 0xff;
    iVar1 = iVar1 + -1;
    if ((int)uVar3 < iVar1)
    {
      memcpy(in_r0, (void *)((int)in_r0 + 0xe), (iVar1 - uVar3) * 0xe);
    }
    paVar2[iVar1].used = '\0';
  }
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void aps_bindingTblEntryGet(void)

{
  bindTblEntryGet();
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
char aps_bindingTblEntryNum(void)

{
  char cVar1;
  aps_binding_entry_t *paVar2;
  int iVar3;

  paVar2 = bindTblEntryGet();
  cVar1 = '\0';
  if (APS_BINDING_TABLE_SIZE != 0)
  {
    iVar3 = 0;
    while (true)
    {
      if (paVar2->used == '\x01')
      {
        cVar1 = cVar1 + '\x01';
      }
      if ((int)(uint)APS_BINDING_TABLE_SIZE <= iVar3 + 1)
        break;
      iVar3 = iVar3 + 1;
      paVar2 = paVar2 + 1;
    }
  }
  return cVar1;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void aps_bindingTblNvInit(void)

{
  nv_sts_t nVar1;
  aps_binding_entry_t *buf;

  buf = bindTblEntryGet();
  nv_itemLengthCheckAdd(0x80, (ushort)APS_BINDING_TABLE_SIZE * 0xe);
  nVar1 = nv_flashReadNew('\x01', '\x02', 0x80, 0xe, (u8 *)buf);
  if (nVar1 != NV_SUCC)
  {
    aps_oldBindingTblRecover();
  }
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
undefined4 aps_me_bind_req(void)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;

  uVar1 = aps_bindingTblEntryNum();
  uVar3 = 0xae;
  if (APS_BINDING_TABLE_SIZE != uVar1)
  {
    iVar2 = aps_bindingTblMatch();
    uVar3 = 0;
    if (iVar2 == 0)
    {
      iVar2 = aps_bindingTblEntryAdd();
      uVar3 = 0xa6;
      if (iVar2 != 0)
      {
        tl_zbTaskPost(aps_bindingTblSave2Flash, (void *)0x0);
        uVar3 = 0;
      }
    }
  }
  return uVar3;
}
void aps_me_init(void)

{
  u8 uVar1;
  int iVar2;

  uVar1 = aps_groupTblNvInit();
  if (uVar1 == '\0')
  {
    aps_init_group_num_set();
    iVar2 = aps_bindingTblNvInit();
  }
  else
  {
    aps_groupTblReset();
    iVar2 = aps_bindingTblNvInit();
  }
  if (iVar2 != 0)
  {
    aps_bindingTabInit();
  }
  aps_ib.aps_designated_coordinator = '\0';
  aps_ib.aps_channel_mask = 0x7fff800;
  aps_ib.aps_use_ext_panid._0_4_ = 0;
  aps_ib.aps_use_ext_panid._4_4_ = 0;
  aps_ib.aps_nonmember_radius = '\x02';
  aps_ib.aps_interframe_delay = APS_INTERFRAME_DELAY;
  aps_ib.aps_max_window_size = APS_MAX_WINDOW_SIZE;
  if (APS_MAX_WINDOW_SIZE == '\0')
  {
    aps_ib.aps_max_window_size = '\x01';
  }
  aps_ib.aps_fragment_payload_size = APS_FRAGMEMT_PAYLOAD_SIZE;
  aps_ib._18_1_ = aps_ib._18_1_ & 0xf5 | 1;
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
undefined4 aps_me_unbind_req(void)

{
  int iVar1;
  undefined4 uVar2;

  iVar1 = aps_bindingTblMatch();
  uVar2 = 0xa4;
  if (iVar1 != 0)
  {
    aps_bindingTblEntryDel();
    tl_zbTaskPost(aps_bindingTblSave2Flash, (void *)0x0);
    uVar2 = 0;
  }
  return uVar2;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
nv_sts_t aps_oldBindingTblRecover(void)

{
  byte bVar1;
  byte bVar2;
  nv_sts_t nVar3;
  nv_sts_t nVar4;
  aps_binding_entry_t *buf;
  byte *buf_00;
  int iVar5;
  aps_binding_entry_t *paVar6;
  uint uVar7;
  byte *pbVar8;
  ushort uVar9;
  ushort uVar10;
  uint uVar11;
  int iVar12;
  undefined uVar13;
  undefined uVar14;
  undefined2 uVar15;
  ushort *in_stack_ffffffb4;
  ushort uStack_38;
  u16 auStack_36[5];
  ushort local_2c;
  u8 uStack_2a;
  ushort uStack_28;
  ushort local_26;

  buf = bindTblEntryGet();
  local_26 = 0;
  nVar3 = nv_flashSingleItemSizeGet('\x02', '\x06', &local_26);
  if (nVar3 != NV_SUCC)
  {
    return nVar3;
  }
  if ((uint)APS_OLD_BINDING_TBL_SIZE_MAX < (uint)local_26)
  {
    return NV_SUCC;
  }
  uVar7 = local_26 - 4;
  if (uVar7 < 0x16)
  {
    return NV_SUCC;
  }
  iVar12 = 1;
  if (uVar7 == 0x16)
  {
    APS_BINDING_TABLE_SIZE_V1 = 1;
  }
  else
  {
    do
    {
      iVar5 = iVar12 + 1;
      uVar11 = (iVar12 + 0xb) * iVar5 * 2;
      if (uVar7 < uVar11)
      {
        return NV_SUCC;
      }
      iVar12 = iVar5;
    } while (uVar11 - uVar7 != 0);
    APS_BINDING_TABLE_SIZE_V1 = (byte)iVar5;
  }
  buf_00 = ev_buf_allocate(local_26);
  if (buf_00 == (byte *)0x0)
  {
    return NV_SUCC;
  }
  nVar3 = nv_flashReadNew('\x01', '\x02', '\x06', local_26, buf_00);
  if (nVar3 != NV_SUCC)
    goto LAB_00023008;
  local_2c = 0;
  uStack_2a = '\0';
  uVar13 = SUB41(&local_2c, 0);
  uVar14 = (undefined)((uint)&local_2c >> 8);
  uVar15 = (undefined2)((uint)&local_2c >> 0x10);
  uStack_28 = local_2c;
  nVar4 = nv_flashReadNew('\0', '\x01', 0xff, 10, (u8 *)&local_2c);
  if (nVar4 == NV_SUCC)
  {
    iVar12 = 0;
    do
    {
      uVar13 = 10;
      uVar14 = 0;
      uVar15 = 0;
      in_stack_ffffffb4 = &uStack_38;
      nVar4 = nv_flashReadByIndex('\x01', '\x03', uStack_2a, (u16)iVar12, 10, (u8 *)in_stack_ffffffb4);
      if (nVar4 != NV_ITEM_NOT_FOUND)
      {
        iVar5 = tl_idxByExtAddr();
        if (iVar5 != 0)
        {
          tl_zbNwkAddrMapAdd(0xffff, (addrExt_t)CONCAT44(in_stack_ffffffb4, CONCAT22(uVar15, CONCAT11(uVar14, uVar13))), auStack_36);
          tl_addrMappingForBind('\x01', uStack_28);
        }
        uVar7 = (uint)APS_BINDING_TABLE_SIZE_V1;
        if (uVar7 != 0)
        {
          iVar5 = 0;
          pbVar8 = buf_00;
          do
          {
            if (((int)(uint)uStack_38 >> iVar5 & 1U) != 0)
            {
              *(ushort *)(pbVar8 + 0x14) = uStack_28;
            }
            iVar5 = iVar5 + 1;
            pbVar8 = pbVar8 + 0x14;
          } while (iVar5 < (int)uVar7);
        }
      }
      iVar12 = iVar12 + 1;
    } while (iVar12 <= (int)(uint)local_2c);
  }
  if (buf_00[2] == 0)
  {
    bindTblEntryGet();
  LAB_000230be:
    uVar9 = (ushort)APS_BINDING_TABLE_SIZE;
  }
  else
  {
    iVar12 = tl_idxByExtAddr();
    if (iVar12 != 0)
    {
      tl_zbNwkAddrMapAdd(g_zbInfo.nwkNib.nwkAddr,
                         (addrExt_t)
                             CONCAT44(in_stack_ffffffb4, CONCAT22(uVar15, CONCAT11(uVar14, uVar13))),
                         (u16 *)g_zbInfo.nwkNib.ieeeAddr);
      tl_addrMappingForBind('\x01', uStack_28);
    }
    uVar7 = (uint)APS_BINDING_TABLE_SIZE_V1;
    if ((uVar7 != 0) && (bVar1 = *buf_00, bVar1 != 0))
    {
      iVar5 = 0;
      iVar12 = 0;
      pbVar8 = buf_00;
      do
      {
        if (pbVar8[0xd] == 1)
        {
          *(ushort *)(pbVar8 + 10) = uStack_28;
          iVar12 = iVar12 + 1;
        }
        iVar5 = iVar5 + 1;
      } while ((iVar5 < (int)uVar7) && (pbVar8 = pbVar8 + 0x14, iVar12 < (int)(uint)bVar1));
    }
    bVar1 = buf_00[2];
    paVar6 = bindTblEntryGet();
    if (bVar1 == 0)
      goto LAB_000230be;
    pbVar8 = buf_00 + 0xa4;
    iVar12 = 0;
    uVar10 = 0;
    do
    {
      uVar11 = (uint)*pbVar8;
      uVar7 = (uint)pbVar8[1];
      if ((uVar11 < APS_BINDING_TABLE_SIZE_V1) && (uVar7 < APS_BINDING_TABLE_SIZE_V1))
      {
        paVar6->used = '\x01';
        paVar6->srcEp = buf_00[uVar11 * 0x14 + 0xc];
        bVar2 = (byte)((ushort) * (undefined2 *)(buf_00 + uVar11 * 0x14 + 8) >> 8);
        *(byte *)&paVar6->clusterId = (byte) * (undefined2 *)(buf_00 + uVar11 * 0x14 + 8) | bVar2;
        *(byte *)((int)&paVar6->clusterId + 1) = bVar2;
        if (buf_00[uVar7 * 0x14 + 0x10] == 1)
        {
          paVar6->dstAddrMode = '\x03';
          iVar5 = (uVar7 + 1) * 0x14;
          tl_zbExtAddrByIdx(*(u16 *)(buf_00 + iVar5),
                            (addrExt_t)
                                CONCAT44(in_stack_ffffffb4, CONCAT22(uVar15, CONCAT11(uVar14, uVar13))));
          (paVar6->field_3).dstExtAddrInfo.dstEp = buf_00[iVar5 + 2];
        }
        else
        {
          paVar6->dstAddrMode = '\x01';
          iVar5 = (uVar7 + 1) * 0x14;
          (paVar6->field_3).dstExtAddrInfo.extAddr[0] = buf_00[iVar5];
          (paVar6->field_3).dstExtAddrInfo.extAddr[1] = buf_00[iVar5 + 1];
        }
        uVar10 = uVar10 + 1 & 0xff;
        uVar9 = (ushort)APS_BINDING_TABLE_SIZE;
        if (uVar9 <= uVar10)
          goto LAB_000230c2;
        paVar6 = paVar6 + 1;
      }
      iVar12 = iVar12 + 1;
      pbVar8 = pbVar8 + 2;
    } while (iVar12 < (int)(uint)bVar1);
    uVar9 = (ushort)APS_BINDING_TABLE_SIZE;
  }
LAB_000230c2:
  nv_flashWriteNew('\x01', 2, 0x80, uVar9 * 0xe, (u8 *)buf);
  nv_flashSingleItemRemove('\x02', '\x06', local_26);
  nVar4 = nv_flashReadNew('\0', '\x01', 0xff, 10, (u8 *)&local_2c);
  if (nVar4 == NV_SUCC)
  {
    iVar12 = 0;
    do
    {
      nVar4 = nv_flashReadByIndex('\x01', '\x03', uStack_2a, (u16)iVar12, 10, (u8 *)&uStack_38);
      if (nVar4 != NV_ITEM_NOT_FOUND)
      {
        nv_itemDeleteByIndex('\x01', '\x03', uStack_2a, (u16)iVar12);
      }
      iVar12 = iVar12 + 1;
    } while (iVar12 <= (int)(uint)local_2c);
  }
LAB_00023008:
  ev_buf_free(buf_00);
  return nVar3;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
// WARNING: Unknown calling convention -- yet parameter storage is locked
undefined4 aps_search_dst_from_bind_tbl(void)

{
  u16 uVar1;
  int in_r0;
  aps_binding_entry_t *paVar2;
  undefined4 uVar3;
  int in_r1;
  char cVar4;
  int iVar5;
  undefined *out;

  paVar2 = bindTblEntryGet();
  uVar3 = 0xa8;
  if (APS_BINDING_TABLE_SIZE == '\0')
  {
    return 0xa8;
  }
  out = (undefined *)(in_r1 + 8);
  iVar5 = 0;
  cVar4 = '\0';
  do
  {
    if (((paVar2->used == '\x01') && (paVar2->srcEp == *(u8 *)(in_r0 + 8))) &&
        (paVar2->clusterId == *(u16 *)(in_r0 + 6)))
    {
      out[9] = paVar2->dstAddrMode;
      if (paVar2->dstAddrMode == '\x03')
      {
        out[8] = (paVar2->field_3).dstExtAddrInfo.dstEp;
        memcpy(out, &paVar2->field_3, 8);
      }
      else
      {
        uVar1 = (paVar2->field_3).groupAddr;
        *out = (char)uVar1;
        out[1] = (char)(uVar1 >> 8);
      }
      out = out + 10;
      cVar4 = cVar4 + '\x01';
      *(undefined *)(in_r1 + 4) = 0;
      *(char *)(in_r1 + 5) = cVar4;
      uVar3 = 0;
      if ((int)(uint)APS_BINDING_TABLE_SIZE <= iVar5 + 1)
      {
        return 0;
      }
    }
    else if ((int)(uint)APS_BINDING_TABLE_SIZE <= iVar5 + 1)
    {
      return uVar3;
    }
    iVar5 = iVar5 + 1;
    paVar2 = paVar2 + 1;
  } while (true);
}
