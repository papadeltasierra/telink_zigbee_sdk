// WARNING: Unknown calling convention -- yet parameter storage is locked
void nwkNebManagePeriodic(void)

{
  byte bVar1;
  int iVar2;
  u32 *puVar3;
  u32 uVar4;
  int iVar5;
  uint uVar6;

  if (TL_ZB_NEIGHBOR_TABLE_SIZE != '\0')
  {
    uVar6 = 0;
    do
    {
      while (bVar1 = g_zb_neighborTbl.neighborTbl[uVar6].field_0x1e, (bVar1 & 0x80) != 0)
      {
        if ((bVar1 & 0x70) == 0x50)
        {
          puVar3 = &g_zb_neighborTbl.neighborTbl[uVar6].authTimeout;
          uVar4 = *puVar3;
        }
        else
        {
          if (((bVar1 & 0x7e) != 0x14) || (g_zb_neighborTbl.neighborTbl[uVar6].devTimeout == 0))
            break;
          puVar3 = &g_zb_neighborTbl.neighborTbl[uVar6].timeoutCnt;
          uVar4 = *puVar3;
        }
        if ((uVar4 != 0) && (*puVar3 = uVar4 - 1, uVar4 - 1 != 0))
          break;
        iVar2 = uVar6 * 0x24;
        iVar5 = iVar2 + 0x84305c;
        tl_zbshortAddrByIdx(g_zb_neighborTbl.neighborTbl[uVar6].addrmapIdx);
        tl_zbExtAddrByIdx(*(u16 *)(iVar5 + 2), (addrExt_t)CONCAT44(iVar5, iVar2));
        nwk_nodeAddrInfoDelete();
        tl_zbNeighborTableDelete((tl_zb_normal_neighbor_entry_t *)((int)&g_zb_neighborTbl.neighborTbl[0].freeNext + iVar2));
        uVar6 = uVar6 + 1 & 0xff;
        if (TL_ZB_NEIGHBOR_TABLE_SIZE <= uVar6)
        {
          return;
        }
      }
      uVar6 = uVar6 + 1 & 0xff;
    } while (uVar6 < TL_ZB_NEIGHBOR_TABLE_SIZE);
  }
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void tl_nebListDelete(void)

{
  nebTbl_t *pnVar1;
  tl_zb_normal_neighbor_entry_t *ptVar2;
  char in_r0;
  tl_zb_normal_neighbor_entry_t *in_r1;
  tl_zb_normal_neighbor_entry_t *ptVar3;

  if (in_r0 == '\0')
  {
    ptVar2 = g_zb_neighborTbl.activeHead;
    if (in_r1 == g_zb_neighborTbl.activeHead)
    {
      g_zb_neighborTbl.activeHead = in_r1->activeNext;
    }
    else
    {
      do
      {
        ptVar3 = ptVar2;
        ptVar2 = ptVar3->activeNext;
        if (ptVar2 == (tl_zb_normal_neighbor_entry_t *)0x0)
        {
          return;
        }
      } while (in_r1 != ptVar2);
      pnVar1 = in_r1->activeNext;
      *(char *)&ptVar3->activeNext = (char)pnVar1;
      *(char *)((int)&ptVar3->activeNext + 1) = (char)((uint)pnVar1 >> 8);
      *(char *)((int)&ptVar3->activeNext + 2) = (char)((uint)pnVar1 >> 0x10);
      *(char *)((int)&ptVar3->activeNext + 3) = (char)((uint)pnVar1 >> 0x18);
    }
  }
  else
  {
    ptVar2 = g_zb_neighborTbl.freeHead;
    if (g_zb_neighborTbl.freeHead == in_r1)
    {
      g_zb_neighborTbl.freeHead = (g_zb_neighborTbl.freeHead)->freeNext;
    }
    else
    {
      do
      {
        ptVar3 = ptVar2;
        ptVar2 = ptVar3->freeNext;
        if (ptVar2 == (tl_zb_normal_neighbor_entry_t *)0x0)
        {
          return;
        }
      } while (in_r1 != ptVar2);
      pnVar1 = in_r1->freeNext;
      *(char *)&ptVar3->freeNext = (char)pnVar1;
      *(char *)((int)&ptVar3->freeNext + 1) = (char)((uint)pnVar1 >> 8);
      *(char *)((int)&ptVar3->freeNext + 2) = (char)((uint)pnVar1 >> 0x10);
      *(char *)((int)&ptVar3->freeNext + 3) = (char)((uint)pnVar1 >> 0x18);
    }
  }
  return;
}
u8 tl_neighborFrameCntReset(void)

{
  byte bVar1;
  u32 *puVar2;
  u32 *puVar3;

  if (TL_ZB_NEIGHBOR_TABLE_SIZE != '\0')
  {
    bVar1 = TL_ZB_NEIGHBOR_TABLE_SIZE - 1;
    puVar2 = &g_zb_neighborTbl.neighborTbl[0].incomingFrameCnt;
    for (puVar3 = &g_zb_neighborTbl.neighborTbl[1].incomingFrameCnt; *puVar2 = 0,
        puVar3 != &g_zb_neighborTbl.neighborTbl[bVar1 + 1].incomingFrameCnt;
         puVar3 = puVar3 + 9)
    {
      puVar2 = puVar3;
    }
  }
  return '\0';
}
u8 tl_nwkNeighborDeleteByAddrmapIdx(u16 idx)

{
  u16 uVar1;
  nebTbl_t *entry;

  if ((g_zb_neighborTbl.activeHead != (tl_zb_normal_neighbor_entry_t *)0x0) &&
      (((g_zb_neighborTbl.activeHead)->field_0x1e & 0x80) != 0))
  {
    uVar1 = (g_zb_neighborTbl.activeHead)->addrmapIdx;
    entry = g_zb_neighborTbl.activeHead;
    while (idx != uVar1)
    {
      entry = entry->activeNext;
      if (entry == (nebTbl_t *)0x0)
      {
        return '\0';
      }
      if ((entry->field_0x1e & 0x80) == 0)
      {
        return '\0';
      }
      uVar1 = entry->addrmapIdx;
    }
    tl_zbNeighborTableDelete(entry);
  }
  return '\0';
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void tl_zbAdditionNeighborReset(void)

{
  int iVar1;
  u16 *puVar2;

  puVar2 = &g_zb_neighborTbl.additionNeighborTbl[0].shortAddr;
  iVar1 = 0;
  do
  {
    *puVar2 = 0xfffe;
    memset(g_zb_neighborTbl.additionNeighborTbl[iVar1].extAddr, 0xff, 8);
    iVar1 = iVar1 + 1;
    puVar2 = puVar2 + 0xe;
  } while (iVar1 != 6);
  g_zb_neighborTbl.additionNeighborNum = '\0';
  return;
}
u8 tl_zbAdditionNeighborTableNumGet(void)

{
  return g_zb_neighborTbl.additionNeighborNum;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
// WARNING: Unknown calling convention -- yet parameter storage is locked
u8 tl_zbAdditionNeighborTableUpdate(tl_zb_addition_neighbor_entry_t *entry)

{
  tl_zb_addition_neighbor_entry_t *out;
  uint uVar1;
  int iVar2;

  if (entry->addrMode == '\x02')
  {
    out = (tl_zb_addition_neighbor_entry_t *)AdditionNeighborEntryGetFromShortAddr();
  LAB_0001aca8:
    if (out != (tl_zb_addition_neighbor_entry_t *)0x0)
      goto LAB_0001acac;
  }
  else if (entry->addrMode == '\x03')
  {
    out = (tl_zb_addition_neighbor_entry_t *)AdditionNeighborEntryGetFromExtAddr();
    goto LAB_0001aca8;
  }
  uVar1 = (uint)g_zb_neighborTbl.additionNeighborNum;
  if (uVar1 < 6)
  {
    g_zb_neighborTbl.additionNeighborNum = g_zb_neighborTbl.additionNeighborNum + '\x01';
    out = g_zb_neighborTbl.additionNeighborTbl + uVar1;
  }
  else
  {
    iVar2 = 0;
    while (out = g_zb_neighborTbl.additionNeighborTbl + iVar2,
           (g_zb_neighborTbl.additionNeighborTbl[iVar2].field_0x16 & 0xf) <=
               (entry->field_0x16 & 0xf))
    {
      iVar2 = iVar2 + 1;
      if (iVar2 == 6)
      {
        return 199;
      }
    }
  }
LAB_0001acac:
  memcpy(out, entry, 0x1c);
  return '\0';
}
u8 tl_zbNeighborTableChildEDNumGet(void)

{
  byte bVar1;
  nebTbl_t *pnVar2;

  g_zb_neighborTbl.childrenNum = '\0';
  if (g_zb_neighborTbl.activeHead != (tl_zb_normal_neighbor_entry_t *)0x0)
  {
    bVar1 = (g_zb_neighborTbl.activeHead)->field_0x1e;
    pnVar2 = g_zb_neighborTbl.activeHead;
    while ((bVar1 & 0x80) != 0)
    {
      if (((bVar1 & 0xe) == 4) && (((bVar1 & 0x70) == 0x50 || ((bVar1 & 0x70) == 0x10))))
      {
        g_zb_neighborTbl.childrenNum = g_zb_neighborTbl.childrenNum + '\x01';
      }
      pnVar2 = pnVar2->activeNext;
      if (pnVar2 == (nebTbl_t *)0x0)
      {
        return g_zb_neighborTbl.childrenNum;
      }
      bVar1 = pnVar2->field_0x1e;
    }
  }
  return g_zb_neighborTbl.childrenNum;
}
// WARNING: Type propagation algorithm not settling
// WARNING: Unknown calling convention -- yet parameter storage is locked
// WARNING: Type propagation algorithm not settling
// WARNING: Unknown calling convention -- yet parameter storage is locked
// WARNING: Unknown calling convention -- yet parameter storage is locked
void tl_zbNeighborTableDelete(tl_zb_normal_neighbor_entry_t *entry)

{
  nebTbl_t *pnVar1;
  int iVar2;
  byte bVar3;
  undefined in_stack_ffffffe8;
  undefined7 in_stack_ffffffe9;

  bVar3 = entry->field_0x1e & 0x70;
  if ((bVar3 == 0x50) || (bVar3 == 0x10))
  {
    g_sysDiags.childMoved = g_sysDiags.childMoved + 1;
  }
  if (g_zb_neighborTbl.normalNeighborNum == '\0')
  {
    sys_exceptionPost(0x124, '3');
  }
  g_sysDiags.neighborRemoved = g_sysDiags.neighborRemoved + 1;
  tl_zbExtAddrByIdx(entry->addrmapIdx, (addrExt_t)CONCAT71(in_stack_ffffffe9, in_stack_ffffffe8));
  iVar2 = aps_bindingTblExis();
  if (iVar2 == 0)
  {
    tl_zbNwkAddrMapDelete(entry->addrmapIdx);
  }
  entry->field_0x1e = entry->field_0x1e & 0x8f | 0x30;
  entry->field_0x1e = entry->field_0x1e & 0x7f;
  entry->transFailure = '\0';
  tl_nebListDelete();
  *(undefined *)&entry->freeNext = g_zb_neighborTbl.freeHead._0_1_;
  *(undefined *)((int)&entry->freeNext + 1) = g_zb_neighborTbl.freeHead._1_1_;
  *(undefined *)((int)&entry->freeNext + 2) = g_zb_neighborTbl.freeHead._2_1_;
  *(undefined *)((int)&entry->freeNext + 3) = g_zb_neighborTbl.freeHead._3_1_;
  g_zb_neighborTbl.normalNeighborNum = '\0';
  if (g_zb_neighborTbl.activeHead != (tl_zb_normal_neighbor_entry_t *)0x0)
  {
    bVar3 = (g_zb_neighborTbl.activeHead)->field_0x1e;
    pnVar1 = g_zb_neighborTbl.activeHead;
    while ((bVar3 & 0x80) != 0)
    {
      g_zb_neighborTbl.normalNeighborNum = g_zb_neighborTbl.normalNeighborNum + '\x01';
      pnVar1 = pnVar1->activeNext;
      if (pnVar1 == (nebTbl_t *)0x0)
        break;
      bVar3 = pnVar1->field_0x1e;
    }
  }
  g_zb_neighborTbl.freeHead = entry;
  tl_zbNeighborTableChildEDNumGet();
  return;
}
// WARNING: Could not reconcile some variable overlaps
void tl_zbNeighborTableInit(void)

{
  nv_sts_t nVar1;
  tl_zb_normal_neighbor_entry_t *ptVar2;
  int iVar3;
  undefined uVar4;
  undefined uVar5;
  undefined2 uVar6;
  u16 *puVar7;
  u32 *puVar8;
  undefined auStack_68[32];
  uint uStack_48;
  u32 local_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  u16 local_38;
  u16 auStack_36[4];
  byte bStack_2e;
  byte bStack_2d;
  ushort local_2c;
  u8 uStack_2a;
  ushort local_26;

  tl_zbNeighborTableRst();
  auStack_68._0_4_ = (nebTbl_t *)0x0;
  auStack_68._4_4_ = (nebTbl_t *)0x0;
  auStack_68._8_4_ = 0;
  auStack_68._12_4_ = 0;
  auStack_68._16_4_ = 0;
  auStack_68._20_4_ = 0;
  auStack_68._24_4_ = 0;
  auStack_68._28_4_ = 0;
  uStack_48 = 0;
  local_2c = 0;
  uStack_2a = '\0';
  nVar1 = nv_flashReadNew('\0', '\x01', 0xff, 0xc, (u8 *)&local_2c);
  if (nVar1 == NV_SUCC)
  {
    iVar3 = 0;
    do
    {
      while (true)
      {
        uVar4 = 0xc;
        uVar5 = 0;
        uVar6 = 0;
        puVar7 = &local_38;
        nVar1 = nv_flashReadByIndex('\x01', '\x02', uStack_2a, (u16)iVar3, 0xc, (u8 *)&local_38);
        if (nVar1 == 0)
          break;
      LAB_0001ad7a:
        iVar3 = iVar3 + 1;
        if ((int)(uint)local_2c < iVar3)
          goto LAB_0001ae2e;
      }
      tl_zbNwkAddrMapAdd(local_38, (addrExt_t)CONCAT44(puVar7, CONCAT22(uVar6, CONCAT11(uVar5, uVar4))),
                         auStack_36);
      auStack_68._20_4_ = auStack_68._20_4_ & 0xffff | (uint)local_26 << 0x10;
      auStack_68._28_3_ =
          CONCAT12(auStack_68[30] & 0x80 | bStack_2d & 1 | (byte)((bStack_2d >> 4 & 7) << 4) |
                       (byte)((bStack_2d >> 1 & 7) << 1),
                   auStack_68._28_2_);
      auStack_68._28_4_ = auStack_68._28_4_ & 0xff000000 | (uint)auStack_68._28_3_;
      auStack_68[30] = (byte)((uint)auStack_68._28_3_ >> 0x10);
      if ((auStack_68[30] & 0xe) == 4)
      {
        auStack_68._12_4_ = 10;
        auStack_68._16_4_ = auStack_68._12_4_;
        if (g_zbInfo.nwkNib.endDevTimeoutDefault != 0)
        {
          auStack_68._12_4_ = 0x3c << (uint)g_zbInfo.nwkNib.endDevTimeoutDefault;
          auStack_68._16_4_ = auStack_68._12_4_;
        }
      }
      uStack_48 = (uint)CONCAT12(NWK_NEIGHBORTBL_ADD_LQITHRESHOLD + '\x01',
                                 (ushort)uStack_48 & 0xff00 | (ushort)bStack_2e);
      auStack_68._28_4_ = auStack_68._28_4_ | 0x7f0000;
      auStack_68._24_4_ = (uint)nVar1;
      ptVar2 = tl_zbNeighborTableUpdate((tl_zb_normal_neighbor_entry_t *)auStack_68, '\0');
      if (ptVar2 == (tl_zb_normal_neighbor_entry_t *)0x0)
        goto LAB_0001ad7a;
      ptVar2->lqi = '\0';
      iVar3 = iVar3 + 1;
    } while (iVar3 <= (int)(uint)local_2c);
  }
LAB_0001ae2e:
  local_44 = 0;
  uStack_40 = 0;
  uStack_3c = 0;
  local_2c = 0;
  uStack_2a = '\0';
  nVar1 = nv_flashReadNew('\0', '\x01', 0xff, 0xc, (u8 *)&local_2c);
  if (nVar1 == NV_SUCC)
  {
    iVar3 = 0;
    do
    {
      while (true)
      {
        uVar4 = 0xc;
        uVar5 = 0;
        uVar6 = 0;
        puVar8 = &local_44;
        nVar1 = nv_flashReadByIndex('\x01', '\v', uStack_2a, (u16)iVar3, 0xc, (u8 *)&local_44);
        if (((nVar1 != NV_SUCC) ||
             (ptVar2 = nwk_neTblGetByExtAddr((addrExt_t)CONCAT44(puVar8, CONCAT22(uVar6, CONCAT11(uVar5, uVar4)))),
              ptVar2 == (tl_zb_normal_neighbor_entry_t *)0x0)) ||
            ((ptVar2->field_0x1e & 0xe) != 4))
          break;
        auStack_68._12_4_ = local_44;
        iVar3 = iVar3 + 1;
        auStack_68._16_4_ = auStack_68._12_4_;
        if ((int)(uint)local_2c < iVar3)
        {
          return;
        }
      }
      iVar3 = iVar3 + 1;
    } while (iVar3 <= (int)(uint)local_2c);
  }
  return;
}
u8 tl_zbNeighborTableNumGet(void)

{
  byte bVar1;
  nebTbl_t *pnVar2;

  g_zb_neighborTbl.normalNeighborNum = '\0';
  if (g_zb_neighborTbl.activeHead != (tl_zb_normal_neighbor_entry_t *)0x0)
  {
    bVar1 = (g_zb_neighborTbl.activeHead)->field_0x1e;
    pnVar2 = g_zb_neighborTbl.activeHead;
    while ((bVar1 & 0x80) != 0)
    {
      g_zb_neighborTbl.normalNeighborNum = g_zb_neighborTbl.normalNeighborNum + '\x01';
      pnVar2 = pnVar2->activeNext;
      if (pnVar2 == (nebTbl_t *)0x0)
      {
        return g_zb_neighborTbl.normalNeighborNum;
      }
      bVar1 = pnVar2->field_0x1e;
    }
  }
  return g_zb_neighborTbl.normalNeighborNum;
}
u8 tl_zbNeighborTableRouterValidNumGet(void)

{
  byte bVar1;
  nebTbl_t *pnVar2;
  u8 uVar3;

  uVar3 = '\0';
  if (g_zb_neighborTbl.activeHead != (tl_zb_normal_neighbor_entry_t *)0x0)
  {
    bVar1 = (g_zb_neighborTbl.activeHead)->field_0x1e;
    pnVar2 = g_zb_neighborTbl.activeHead;
    while ((bVar1 & 0x80) != 0)
    {
      if ((((bVar1 & 0xe) == 0) || ((bVar1 & 0xe) == 2)) && (pnVar2->lqi != '\0'))
      {
        uVar3 = uVar3 + '\x01';
      }
      pnVar2 = pnVar2->activeNext;
      if (pnVar2 == (nebTbl_t *)0x0)
      {
        return uVar3;
      }
      bVar1 = pnVar2->field_0x1e;
    }
  }
  return uVar3;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void tl_zbNeighborTableRst(void)

{
  u32 len;
  uint uVar1;
  tl_zb_normal_neighbor_entry_t *ptVar2;
  tl_zb_normal_neighbor_entry_t *ptVar3;
  int iVar4;
  u16 *puVar5;

  len = neighborTblSizeGet();
  memset(&g_zb_neighborTbl, 0, len);
  g_zb_neighborTbl.activeHead = (tl_zb_normal_neighbor_entry_t *)0x0;
  ptVar2 = g_zb_neighborTbl.neighborTbl;
  g_zb_neighborTbl.freeHead = g_zb_neighborTbl.neighborTbl;
  if (TL_ZB_NEIGHBOR_TABLE_SIZE != '\x01')
  {
    uVar1 = 0;
    ptVar3 = ptVar2;
    do
    {
      ptVar3->field_0x1e = ptVar3->field_0x1e & 0x8f | 0x30;
      ptVar3->field_0x1e = ptVar3->field_0x1e & 0x7f;
      *(undefined *)&ptVar3->activeNext = 0;
      *(undefined *)((int)&ptVar3->activeNext + 1) = 0;
      *(undefined *)((int)&ptVar3->activeNext + 2) = 0;
      *(undefined *)((int)&ptVar3->activeNext + 3) = 0;
      ptVar2 = ptVar3 + 1;
      *(char *)&ptVar3->freeNext = (char)ptVar2;
      *(char *)((int)&ptVar3->freeNext + 1) = (char)((uint)ptVar2 >> 8);
      *(char *)((int)&ptVar3->freeNext + 2) = (char)((uint)ptVar2 >> 0x10);
      *(char *)((int)&ptVar3->freeNext + 3) = (char)((uint)ptVar2 >> 0x18);
      uVar1 = uVar1 + 1;
      ptVar3 = ptVar2;
    } while (uVar1 < TL_ZB_NEIGHBOR_TABLE_SIZE - 1);
  }
  *(undefined *)&ptVar2->freeNext = 0;
  *(undefined *)((int)&ptVar2->freeNext + 1) = 0;
  *(undefined *)((int)&ptVar2->freeNext + 2) = 0;
  *(undefined *)((int)&ptVar2->freeNext + 3) = 0;
  ptVar2->field_0x1e = ptVar2->field_0x1e & 0x7f;
  *(undefined *)&ptVar2->activeNext = 0;
  *(undefined *)((int)&ptVar2->activeNext + 1) = 0;
  *(undefined *)((int)&ptVar2->activeNext + 2) = 0;
  *(undefined *)((int)&ptVar2->activeNext + 3) = 0;
  puVar5 = &g_zb_neighborTbl.additionNeighborTbl[0].shortAddr;
  iVar4 = 0;
  do
  {
    *puVar5 = 0xfffe;
    memset(g_zb_neighborTbl.additionNeighborTbl[iVar4].extAddr, 0xff, 8);
    iVar4 = iVar4 + 1;
    puVar5 = puVar5 + 0xe;
  } while (iVar4 != 6);
  return;
}
