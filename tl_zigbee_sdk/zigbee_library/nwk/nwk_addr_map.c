// WARNING: Unknown calling convention -- yet parameter storage is locked
undefined4 nwk_nodeAddrInfoDelete(void)

{
  nv_sts_t nVar1;
  int in_r0;
  int iVar2;
  int iVar3;
  u8 auStack_40[2];
  undefined auStack_3e[9];
  byte bStack_35;
  u8 auStack_34[4];
  undefined auStack_30[8];
  ushort local_28;
  u8 uStack_26;

  if ((*(byte *)(in_r0 + 0xb) & 0xe) == 4)
  {
    local_28 = 0;
    uStack_26 = '\0';
    nVar1 = nv_flashReadNew('\0', '\x01', 0xff, 0xc, (u8 *)&local_28);
    if (nVar1 == NV_SUCC)
    {
      iVar3 = 0;
      do
      {
        nVar1 = nv_flashReadByIndex('\x01', '\v', uStack_26, (u16)iVar3, 0xc, auStack_34);
        if ((nVar1 == NV_SUCC) && (iVar2 = memcmp((void *)(in_r0 + 2), auStack_30, 8), iVar2 == 0))
        {
          nv_itemDeleteByIndex('\x01', '\v', uStack_26, (u16)iVar3);
        }
        iVar3 = iVar3 + 1;
      } while (iVar3 <= (int)(uint)local_28);
    }
  }
  local_28 = 0;
  uStack_26 = '\0';
  nVar1 = nv_flashReadNew('\0', '\x01', 0xff, 0xc, (u8 *)&local_28);
  if (nVar1 == NV_SUCC)
  {
    iVar3 = 0;
    do
    {
      nVar1 = nv_flashReadByIndex('\x01', '\x02', uStack_26, (u16)iVar3, 0xc, auStack_40);
      if (((nVar1 == NV_SUCC) && (iVar2 = memcmp((void *)(in_r0 + 2), auStack_3e, 8), iVar2 == 0)) &&
          (((bStack_35 ^ *(byte *)(in_r0 + 0xb)) & 0x70) == 0))
      {
        nv_itemDeleteByIndex('\x01', '\x02', uStack_26, (u16)iVar3);
        return 0;
      }
      iVar3 = iVar3 + 1;
    } while (iVar3 <= (int)(uint)local_28);
  }
  return 3;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
buf_sts_t nwk_nodeAddrInfoStore(void)

{
  nv_sts_t nVar1;
  buf_sts_t bVar2;
  short *in_r0;
  int iVar3;
  int iVar4;
  short local_34;
  undefined auStack_32[10];
  ushort local_28;
  u8 uStack_26;

  local_28 = 0;
  uStack_26 = '\0';
  nVar1 = nv_flashReadNew('\0', '\x01', 0xff, 0xc, (u8 *)&local_28);
  if (nVar1 == NV_SUCC)
  {
    iVar4 = 0;
  LAB_0001631c:
    do
    {
      nVar1 = nv_flashReadByIndex('\x01', '\x02', uStack_26, (u16)iVar4, 0xc, (u8 *)&local_34);
      if (nVar1 == NV_SUCC)
      {
        iVar3 = memcmp(in_r0 + 1, auStack_32, 8);
        if (iVar3 == 0)
        {
          if (local_34 == *in_r0)
            goto LAB_0001636c;
        }
        else if (local_34 != *in_r0)
        {
          iVar4 = iVar4 + 1;
          if ((int)(uint)local_28 < iVar4)
            break;
          goto LAB_0001631c;
        }
        nv_itemDeleteByIndex('\x01', '\x02', uStack_26, (u16)iVar4);
      }
      iVar4 = iVar4 + 1;
    } while (iVar4 <= (int)(uint)local_28);
  }
  nv_flashWriteNew('\0', 1, '\x02', 0xc, (u8 *)in_r0);
LAB_0001636c:
  bVar2 = ev_buf_free((u8 *)in_r0);
  return bVar2;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
undefined4 nwk_parentNodeInfoStore(void)

{
  nv_sts_t nVar1;
  tl_zb_normal_neighbor_entry_t *ptVar2;
  int iVar3;
  u16 local_3c;
  undefined auStack_3a[8];
  u8 uStack_32;
  byte bStack_31;
  u8 auStack_30[11];
  byte bStack_25;
  ushort local_24;
  u8 uStack_22;

  ptVar2 = tl_zbNeighborTableSearchForParent();
  local_24 = 0;
  uStack_22 = '\0';
  nVar1 = nv_flashReadNew('\0', '\x01', 0xff, 0xc, (u8 *)&local_24);
  if (nVar1 == NV_SUCC)
  {
    iVar3 = 0;
    do
    {
      while (true)
      {
        nVar1 = nv_flashReadByIndex('\x01', '\x02', uStack_22, (u16)iVar3, 0xc, auStack_30);
        if ((nVar1 != NV_SUCC) || ((bStack_25 & 0x70) != 0))
          break;
        nv_itemDeleteByIndex('\x01', '\x02', uStack_22, (u16)iVar3);
        iVar3 = iVar3 + 1;
        if ((int)(uint)local_24 < iVar3)
          goto LAB_000163f8;
      }
      iVar3 = iVar3 + 1;
    } while (iVar3 <= (int)(uint)local_24);
  }
LAB_000163f8:
  if (ptVar2 != (tl_zb_normal_neighbor_entry_t *)0x0)
  {
    local_3c = g_nwkAddrMap.addrMap[ptVar2->addrmapIdx].shortAddr;
    memcpy(auStack_3a, g_nwkAddrMap.addrMap[ptVar2->addrmapIdx].extAddr, 8);
    uStack_32 = ptVar2->depth;
    bStack_31 = bStack_31 & 0x80 | ptVar2->field_0x1e & 0xe | ptVar2->field_0x1e & 1;
    nv_flashWriteNew('\0', 1, '\x02', 0xc, (u8 *)&local_3c);
  }
  return 0xfffffffe;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
zb_nwk_status_t tl_addrByShort(void)

{
  zb_nwk_status_t zVar1;
  u16 in_r0;
  int iVar2;
  char in_r1;
  int in_r3;
  undefined4 unaff_r4;
  undefined4 in_lr;

  if (in_r3 == 0)
  {
    sys_exceptionPost(0x140, '0');
    zVar1 = ~NWK_STATUS_SUCCESS;
  }
  else
  {
    iVar2 = FUNBBBBK();
    zVar1 = NWK_STATUS_SUCCESS;
    if ((iVar2 != 0) && (zVar1 = ~NWK_STATUS_SUCCESS, in_r1 != '\0'))
    {
      zVar1 = tl_zbNwkAddrMapAdd(in_r0, (addrExt_t)CONCAT44(unaff_r4, in_lr), (u16 *)&g_zero_addr);
    }
  }
  return zVar1;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void tl_addrMapListDelete(void)

{
  addrMapping_t *paVar1;
  tl_zb_addr_map_entry_t *ptVar2;
  char in_r0;
  tl_zb_addr_map_entry_t *in_r1;
  tl_zb_addr_map_entry_t *ptVar3;

  if (in_r0 == '\0')
  {
    ptVar2 = g_nwkAddrMap.activeHead;
    if (in_r1 == g_nwkAddrMap.activeHead)
    {
      g_nwkAddrMap.activeHead = in_r1->activeNext;
    }
    else
    {
      do
      {
        ptVar3 = ptVar2;
        ptVar2 = ptVar3->activeNext;
        if (ptVar2 == (tl_zb_addr_map_entry_t *)0x0)
        {
          return;
        }
      } while (in_r1 != ptVar2);
      paVar1 = in_r1->activeNext;
      *(char *)&ptVar3->activeNext = (char)paVar1;
      *(char *)((int)&ptVar3->activeNext + 1) = (char)((uint)paVar1 >> 8);
      *(char *)((int)&ptVar3->activeNext + 2) = (char)((uint)paVar1 >> 0x10);
      *(char *)((int)&ptVar3->activeNext + 3) = (char)((uint)paVar1 >> 0x18);
    }
  }
  else
  {
    ptVar2 = g_nwkAddrMap.freeHead;
    if (g_nwkAddrMap.freeHead == in_r1)
    {
      g_nwkAddrMap.freeHead = (g_nwkAddrMap.freeHead)->freeNext;
    }
    else
    {
      do
      {
        ptVar3 = ptVar2;
        ptVar2 = ptVar3->freeNext;
        if (ptVar2 == (tl_zb_addr_map_entry_t *)0x0)
        {
          return;
        }
      } while (in_r1 != ptVar2);
      paVar1 = in_r1->freeNext;
      *(char *)&ptVar3->freeNext = (char)paVar1;
      *(char *)((int)&ptVar3->freeNext + 1) = (char)((uint)paVar1 >> 8);
      *(char *)((int)&ptVar3->freeNext + 2) = (char)((uint)paVar1 >> 0x10);
      *(char *)((int)&ptVar3->freeNext + 3) = (char)((uint)paVar1 >> 0x18);
    }
  }
  return;
}
void tl_addrMappingForBind(u8 bind, u16 idx)

{
  uint uVar1;

  uVar1 = (uint)idx;
  if ((uVar1 < TL_ZB_NWK_ADDR_MAP_SIZE) && ((g_nwkAddrMap.addrMap[uVar1].field_0x13 & 1) != 0))
  {
    g_nwkAddrMap.addrMap[uVar1].field_0x13 =
        g_nwkAddrMap.addrMap[uVar1].field_0x13 & 0xef | (byte)((bind & 1) << 4);
  }
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
undefined4 tl_idxByExtAddr(void)

{
  undefined2 uVar1;
  undefined2 *in_r0;
  int iVar2;
  void *in_r1;
  addrMapping_t *paVar3;

  if ((g_nwkAddrMap.activeHead != (tl_zb_addr_map_entry_t *)0x0) &&
      (paVar3 = g_nwkAddrMap.activeHead,
       (int)((uint)(byte)(g_nwkAddrMap.activeHead)->field_0x13 << 0x1f) < 0))
  {
    do
    {
      iVar2 = memcmp(paVar3->extAddr, in_r1, 8);
      if (iVar2 == 0)
      {
        uVar1 = FUN_0000162c(paVar3 + -0x69e53, 0x14);
        *in_r0 = uVar1;
        return 0;
      }
      paVar3 = paVar3->activeNext;
    } while ((paVar3 != (addrMapping_t *)0x0) && ((paVar3->field_0x13 & 1) != 0));
  }
  return 0xff;
}
void tl_zbExtAddrByIdx(u16 idx, addrExt_t extAddr)

{
  void *in_r1;

  memcpy(in_r1, g_nwkAddrMap.addrMap[idx].extAddr, 8);
  return;
}
u8 tl_zbExtAddrByShortAddr(u16 shortAddr, addrExt_t extAddr, u16 *idx)

{
  u16 uVar1;
  addrMapping_t *paVar2;
  u8 uVar3;
  undefined2 uVar4;
  undefined2 *in_r2;

  uVar3 = 0xff;
  if ((g_nwkAddrMap.activeHead != (tl_zb_addr_map_entry_t *)0x0) &&
      ((int)((uint)(byte)(g_nwkAddrMap.activeHead)->field_0x13 << 0x1f) < 0))
  {
    uVar1 = (g_nwkAddrMap.activeHead)->shortAddr;
    paVar2 = g_nwkAddrMap.activeHead;
    while (uVar1 != shortAddr)
    {
      paVar2 = paVar2->activeNext;
      if ((paVar2 == (addrMapping_t *)0x0) || ((paVar2->field_0x13 & 1) == 0))
      {
        return 0xff;
      }
      uVar1 = paVar2->shortAddr;
    }
    memcpy(idx, paVar2->extAddr, 8);
    uVar4 = FUN_0000162c(paVar2 + -0x69e53, 0x14);
    *in_r2 = uVar4;
    uVar3 = '\0';
  }
  return uVar3;
}
// WARNING: Removing unreachable block (RAM,0x000160cc)
zb_nwk_status_t tl_zbNwkAddrMapAdd(u16 shortAddr, addrExt_t extAddr, u16 *ref)

{
  tl_zb_addr_map_entry_t *ptVar1;
  undefined2 uVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  undefined2 *in_r2;
  undefined uVar6;

  uVar3 = FUNBBBBK();
  uVar4 = tl_idxByExtAddr();
  *in_r2 = 0;
  uVar6 = (undefined)((uint)shortAddr >> 8);
  if (((uVar4 | uVar3) & 0xff) == 0)
  {
  LAB_000160d8:
    iVar5 = memcmp(g_nwkAddrMap.addrMap[0].extAddr, &g_zero_addr, 8);
    ptVar1 = g_nwkAddrMap.freeHead;
    if (iVar5 == 0)
      goto LAB_000161b2;
  }
  else
  {
    if (uVar4 == 0)
    {
      *in_r2 = 0;
    }
    ptVar1 = g_nwkAddrMap.freeHead;
    if (uVar3 == 0)
      goto LAB_000160d8;
  }
  g_nwkAddrMap.freeHead = ptVar1;
  if (uVar4 != 0)
  {
    if (ptVar1 == (tl_zb_addr_map_entry_t *)0x0)
    {
      return 199;
    }
    if ((int)((uint)(byte)ptVar1->field_0x13 << 0x1f) < 0)
    {
      return 199;
    }
    g_nwkAddrMap.validNum = g_nwkAddrMap.validNum + 1;
    ptVar1->field_0x13 = ptVar1->field_0x13 | 1;
    *(char *)&ptVar1->shortAddr = (char)shortAddr;
    *(undefined *)((int)&ptVar1->shortAddr + 1) = uVar6;
    if (ref == (u16 *)0x0)
    {
      ptVar1->extAddr[0] = '\0';
      ptVar1->extAddr[1] = '\0';
      ptVar1->extAddr[2] = '\0';
      ptVar1->extAddr[3] = '\0';
      ptVar1->extAddr[4] = '\0';
      ptVar1->extAddr[5] = '\0';
      ptVar1->extAddr[6] = '\0';
      ptVar1->extAddr[7] = '\0';
    }
    else
    {
      memcpy(ptVar1->extAddr, ref, 8);
    }
    ptVar1->aps_dup_cnt = '\0';
    ptVar1->field_0x13 = ptVar1->field_0x13 & 0xf1;
    uVar2 = FUN_0000162c(ptVar1 + -0x69e53, 0x14);
    *in_r2 = uVar2;
    tl_addrMapListDelete();
    *(char *)&ptVar1->activeNext = (char)g_nwkAddrMap.activeHead;
    *(char *)((int)&ptVar1->activeNext + 1) = (char)((uint)g_nwkAddrMap.activeHead >> 8);
    *(char *)((int)&ptVar1->activeNext + 2) = (char)((uint)g_nwkAddrMap.activeHead >> 0x10);
    *(char *)((int)&ptVar1->activeNext + 3) = (char)((uint)g_nwkAddrMap.activeHead >> 0x18);
    g_nwkAddrMap.activeHead = ptVar1;
    return NWK_STATUS_SUCCESS;
  }
LAB_000161b2:
  memcpy(g_nwkAddrMap.addrMap[0].extAddr, ref, 8);
  g_nwkAddrMap.addrMap[0].shortAddr._1_1_ = uVar6;
  g_nwkAddrMap.addrMap[0].shortAddr._0_1_ = (char)shortAddr;
  return NWK_STATUS_SUCCESS;
}
void tl_zbNwkAddrMapDelete(u16 idx)

{
  if ((g_nwkAddrMap.addrMap[idx].field_0x13 & 1) != 0)
  {
    g_nwkAddrMap.addrMap[idx].field_0x13 = g_nwkAddrMap.addrMap[idx].field_0x13 & 0xfe;
    g_nwkAddrMap.addrMap[idx].field_0x13 = g_nwkAddrMap.addrMap[idx].field_0x13 & 0xef;
    tl_addrMapListDelete();
    *(char *)&g_nwkAddrMap.addrMap[idx].freeNext = (char)g_nwkAddrMap.freeHead;
    *(char *)((int)&g_nwkAddrMap.addrMap[idx].freeNext + 1) =
        (char)((uint)g_nwkAddrMap.freeHead >> 8);
    *(char *)((int)&g_nwkAddrMap.addrMap[idx].freeNext + 2) =
        (char)((uint)g_nwkAddrMap.freeHead >> 0x10);
    *(char *)((int)&g_nwkAddrMap.addrMap[idx].freeNext + 3) =
        (char)((uint)g_nwkAddrMap.freeHead >> 0x18);
    g_nwkAddrMap.validNum = g_nwkAddrMap.validNum - 1;
    g_nwkAddrMap.freeHead = g_nwkAddrMap.addrMap + idx;
  }
  return;
}
void tl_zbNwkAddrMapInit(void)

{
  tl_zbNwkAddrMapRst();
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void tl_zbNwkAddrMapRst(void)

{
  u32 len;
  uint uVar1;
  tl_zb_addr_map_entry_t *ptVar2;
  tl_zb_addr_map_entry_t *ptVar3;
  uint uVar4;

  len = addrMapTblSizeGet();
  memset(&g_nwkAddrMap, 0, len);
  g_nwkAddrMap.activeHead._0_1_ = 0;
  g_nwkAddrMap.activeHead._1_1_ = 0;
  g_nwkAddrMap.activeHead._2_1_ = 0;
  g_nwkAddrMap.activeHead._3_1_ = 0;
  ptVar2 = g_nwkAddrMap.addrMap;
  g_nwkAddrMap.freeHead._0_1_ = 0x7c;
  g_nwkAddrMap.freeHead._1_1_ = 0x5e;
  g_nwkAddrMap.freeHead._2_1_ = 0x84;
  g_nwkAddrMap.freeHead._3_1_ = 0;
  uVar4 = (uint)TL_ZB_NWK_ADDR_MAP_SIZE;
  if (1 < uVar4)
  {
    uVar1 = 0;
    ptVar3 = ptVar2;
    do
    {
      ptVar3->field_0x13 = ptVar3->field_0x13 & 0xfe;
      *(undefined *)&ptVar3->activeNext = 0;
      *(undefined *)((int)&ptVar3->activeNext + 1) = 0;
      *(undefined *)((int)&ptVar3->activeNext + 2) = 0;
      *(undefined *)((int)&ptVar3->activeNext + 3) = 0;
      ptVar2 = ptVar3 + 1;
      *(char *)&ptVar3->freeNext = (char)ptVar2;
      *(char *)((int)&ptVar3->freeNext + 1) = (char)((uint)ptVar2 >> 8);
      *(char *)((int)&ptVar3->freeNext + 2) = (char)((uint)ptVar2 >> 0x10);
      *(char *)((int)&ptVar3->freeNext + 3) = (char)((uint)ptVar2 >> 0x18);
      uVar1 = uVar1 + 1 & 0xffff;
      ptVar3 = ptVar2;
    } while ((int)uVar1 < (int)(uVar4 - 1));
  }
  ptVar2->field_0x13 = ptVar2->field_0x13 & 0xfe;
  *(undefined *)&ptVar2->freeNext = 0;
  *(undefined *)((int)&ptVar2->freeNext + 1) = 0;
  *(undefined *)((int)&ptVar2->freeNext + 2) = 0;
  *(undefined *)((int)&ptVar2->freeNext + 3) = 0;
  *(undefined *)&ptVar2->activeNext = 0;
  *(undefined *)((int)&ptVar2->activeNext + 1) = 0;
  *(undefined *)((int)&ptVar2->activeNext + 2) = 0;
  *(undefined *)((int)&ptVar2->activeNext + 3) = 0;
  g_nwkAddrMap.validNum._0_1_ = 0;
  g_nwkAddrMap.validNum._1_1_ = 0;
  g_nwkAddrMap.validNum._2_1_ = 0;
  g_nwkAddrMap.validNum._3_1_ = 0;
  return;
}
u8 tl_zbShortAddrByExtAddr(u16 *shortAddr, addrExt_t extAddr, u16 *idx)

{
  undefined2 uVar1;
  int iVar2;
  undefined2 *in_r2;
  addrMapping_t *paVar3;

  paVar3 = g_nwkAddrMap.activeHead;
  if (g_nwkAddrMap.activeHead != (tl_zb_addr_map_entry_t *)0x0)
  {
    do
    {
      iVar2 = memcmp(idx, paVar3->extAddr, 8);
      if (iVar2 == 0)
      {
        *shortAddr = paVar3->shortAddr;
        uVar1 = FUN_0000162c(paVar3 + -0x69e53, 0x14);
        *in_r2 = uVar1;
        return '\0';
      }
      paVar3 = paVar3->activeNext;
    } while (paVar3 != (addrMapping_t *)0x0);
  }
  return 0xff;
}
u16 tl_zbshortAddrByIdx(u16 idx)

{
  return g_nwkAddrMap.addrMap[idx].shortAddr;
}
u8 zb_address_ieee_by_short(u16 short_addr, addrExt_t ieee_address)

{
  u8 uVar1;
  u16 *in_r1;
  undefined4 in_lr;
  undefined4 in_stack_fffffff8;

  uVar1 = tl_zbExtAddrByShortAddr(short_addr, (addrExt_t)CONCAT44(in_lr, in_stack_fffffff8), in_r1);
  return uVar1;
}
