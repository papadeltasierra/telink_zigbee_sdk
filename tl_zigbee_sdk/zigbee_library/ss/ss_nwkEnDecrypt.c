// WARNING: Could not reconcile some variable overlaps
// WARNING: Unknown calling convention -- yet parameter storage is locked
undefined4 ss_nwkDecryptFrame(void)

{
  byte bVar1;
  ushort uVar2;
  u8 uVar3;
  zb_buf_t *in_r0;
  tl_zb_normal_neighbor_entry_t *ptVar4;
  int iVar5;
  int in_r1;
  byte *in;
  uint in_r2;
  uint uVar6;
  int in_r3;
  uint uVar7;
  uint uVar8;
  int iVar9;
  uint in_stack_00000004;
  undefined4 in_stack_ffffffa4;
  undefined4 in_stack_ffffffa8;
  uint local_48;
  byte bStack_44;
  u16 auStack_43[4];
  byte bStack_3b;
  undefined auStack_38[8];
  uint uStack_30;
  undefined local_2c;
  ushort local_28[2];

  uVar8 = in_r1 * 0x1000000 + 0xf2000000U >> 0x18;
  in = (byte *)(in_r3 + uVar8);
  *in = *in & 0xf8 | 5;
  memcpy(&local_48, in, 0xe);
  uVar7 = ((in_r2 & 0xff) - 0xf) - uVar8;
  uVar2 = *(ushort *)(in_r0->buf + 0x14);
  uVar6 = uVar7 & 0xff;
  if ((int)(uVar7 * 0x1000000) >> 0x18 < 4)
  {
  LAB_0001f7ee:
    g_sysDiags.nwkDecryptFailures = g_sysDiags.nwkDecryptFailures + 1;
    zb_buf_free(in_r0);
  }
  else
  {
    ptVar4 = nwk_neTblGetByExtAddr((addrExt_t)CONCAT44(in_stack_ffffffa8, in_stack_ffffffa4));
    if (((ptVar4 == (tl_zb_normal_neighbor_entry_t *)0x0) || (ss_ib.activeKeySeqNum != bStack_3b)) || ((ptVar4->incomingFrameCnt <= ((uint)bStack_44 << 0x18 | local_48 >> 8) &&
                                                                                                        (ptVar4->incomingFrameCnt != 0xffffffff))))
    {
      iVar5 = ss_zdoGetNwkKeyBySeqNum();
      if ((iVar5 != 0) && (ss_ib.activeKeySeqNum <= bStack_3b))
      {
        memcpy(auStack_38, auStack_43, 8);
        uStack_30 = (uint)bStack_44 << 0x18 | local_48 >> 8;
        local_2c = (undefined)local_48;
        iVar9 = in_r3 + uVar8 + 0xe;
        iVar5 = ss_ccmDecryption();
        if (iVar5 == 0)
        {
          uVar3 = tl_zbShortAddrByExtAddr(local_28, (addrExt_t)CONCAT44(iVar9, uVar6), auStack_43);
          if (((uVar3 == '\0') && (uVar2 != local_28[0])) && (local_28[0] < 0xfff7))
          {
            T_DBG_decFrameCnt = T_DBG_decFrameCnt + '\x01';
            zb_buf_free(in_r0);
            return 1;
          }
          if ((((int)((uint)g_zbNwkCtx._45_1_ << 0x1b) < 0) &&
               (0x80000000 < ((uint)bStack_44 << 0x18 | local_48 >> 8))) &&
              ((zdoAppIndCbLst != 0 &&
                ((*(int *)(zdoAppIndCbLst + 0x24) != 0 &&
                  (-1 < (int)((uint)zdo_mgmt_nwk_flag << 0x1e)))))))
          {
            tl_cryHashFunction();
          }
          if (ptVar4 != (tl_zb_normal_neighbor_entry_t *)0x0)
          {
            ptVar4->age = '\0';
            *(char *)&ptVar4->incomingFrameCnt = (char)(local_48 >> 8);
            *(char *)((int)&ptVar4->incomingFrameCnt + 1) = (char)(local_48 >> 0x10);
            *(char *)((int)&ptVar4->incomingFrameCnt + 2) = (char)(local_48 >> 0x18);
            *(byte *)((int)&ptVar4->incomingFrameCnt + 3) = bStack_44;
            ptVar4->lqi = (u8)((int)((uint)ptVar4->lqi + (in_stack_00000004 & 0xff)) >> 1);
            bVar1 = ptVar4->field_0x1e;
            if ((bVar1 & 0x70) == 0x50)
            {
              if ((bVar1 & 0xe) == 2)
              {
                ptVar4->field_0x1e = bVar1 & 0x8f | 0x20;
              }
              else if ((bVar1 & 0xe) == 4)
              {
                ptVar4->field_0x1e = bVar1 & 0x8f | 0x10;
                ss_zdoChildTableStore();
              }
            }
          }
          if (ss_ib.activeKeySeqNum == bStack_3b)
          {
            return 0;
          }
          if ((int)((uint)zdo_mgmt_nwk_flag << 0x1d) < 0)
          {
            return 0;
          }
          ss_zdoNwkKeySwitch();
          return 0;
        }
        goto LAB_0001f7ee;
      }
      uVar3 = '\x12';
    }
    else
    {
      g_sysDiags.nwkFCFailure = g_sysDiags.nwkFCFailure + 1;
      uVar3 = '\x11';
    }
    in_r0->buf[2] = uVar3;
    in_r0->buf[0] = (u8)uVar2;
    in_r0->buf[1] = (u8)(uVar2 >> 8);
    tl_zbTaskPost(zdo_nlme_status_indication, in_r0);
  }
  return 1;
}
// WARNING: Could not reconcile some variable overlaps
// WARNING: Unknown calling convention -- yet parameter storage is locked
undefined4 ss_nwkSecureFrame(void)

{
  int in_r0;
  int iVar1;
  byte in_r1;
  uint uVar2;
  byte *pbVar3;
  undefined4 uStack_4c;
  uint local_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  short local_38;
  undefined auStack_34[8];
  u32 uStack_2c;
  undefined uStack_28;

  uStack_3c = 0;
  uStack_2c = ss_ib.outgoingFrameCounter;
  local_44 = CONCAT31((undefined3)ss_ib.outgoingFrameCounter, 0x28);
  uStack_40 = ss_ib.outgoingFrameCounter >> 0x18;
  ss_ib.outgoingFrameCounter = ss_ib.outgoingFrameCounter + 1;
  local_38 = (ushort)ss_ib.activeKeySeqNum << 8;
  memcpy((void *)((int)&uStack_40 + 1), g_zbInfo.macPib.extAddress, 8);
  local_44 = local_44 & 0xfffffff8 | 5;
  uVar2 = in_r1 - 0xe & 0xff;
  memcpy((void *)(*(int *)(in_r0 + 0x15) + uVar2), &local_44, 0xe);
  iVar1 = ss_zdoGetNwkKeyBySeqNum();
  uStack_4c = 1;
  if (iVar1 != 0)
  {
    uStack_28 = (undefined)local_44;
    memcpy(auStack_34, (void *)((int)&uStack_40 + 1), 8);
    iVar1 = ss_ccmEncryption();
    if (iVar1 != 0)
    {
      *(byte *)(in_r0 + 0x14) = (char)iVar1 + in_r1;
      pbVar3 = (byte *)(*(int *)(in_r0 + 0x15) + uVar2);
      *pbVar3 = *pbVar3 & 0xf8;
      uStack_4c = 0;
      if (((((int)((uint)g_zbNwkCtx._45_1_ << 0x1b) < 0) &&
            (0x80000000 < ss_ib.outgoingFrameCounter)) &&
           (zdoAppIndCbLst != 0)) &&
          ((*(int *)(zdoAppIndCbLst + 0x24) != 0 && (-1 < (int)((uint)zdo_mgmt_nwk_flag << 0x1e)))))
      {
        FUNEEEEA();
      }
    }
  }
  return uStack_4c;
}
