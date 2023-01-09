// WARNING: Unknown calling convention -- yet parameter storage is locked
int ss_apsDecryptFrame(void)

{
  undefined uVar1;
  bool bVar2;
  u8 uVar3;
  byte bVar4;
  bool bVar5;
  int *in_r0;
  int iVar6;
  tl_zb_normal_neighbor_entry_t *ptVar7;
  int iVar8;
  int iVar9;
  uint uVar10;
  ss_preconfiguredKey_e sVar11;
  byte bVar12;
  uint uVar13;
  byte *in;
  u8 *m1;
  byte bVar14;
  undefined4 in_stack_ffffff60;
  undefined4 in_stack_ffffff64;
  u8 *puStack_98;
  byte *pbStack_94;
  u8 *puStack_90;
  uint uStack_8c;
  undefined auStack_7c[52];
  undefined auStack_48[35];
  undefined local_25;

  bVar12 = g_zbDefaultLinkKeyEn;
  in = (byte *)(*in_r0 + (uint) * (byte *)(in_r0 + 5));
  memcpy(auStack_48 + 0x18, in, 5);
  bVar4 = *in;
  if (((uint)auStack_48[28] << 0x18 | auStack_48._24_4_ >> 8) == 0xffffffff)
  {
    return 1;
  }
  uVar10 = auStack_48._24_4_ & 0x18;
  if (uVar10 == 8)
  {
    return 1;
  }
  uVar3 = tl_zbExtAddrByShortAddr(*(u16 *)(in_r0 + 6), (addrExt_t)CONCAT44(in_stack_ffffff64, in_stack_ffffff60),
                                  (u16 *)(ss_dev_pair_set_t *)auStack_48);
  if ((uVar3 == 0xff) && ((int)((uint)aps_ib._18_1_ << 0x1e) < 0))
  {
    return 1;
  }
  pbStack_94 = in + 5;
  if ((int)((uint)bVar4 << 0x1a) < 0)
  {
    memcpy((ss_dev_pair_set_t *)auStack_48, pbStack_94, 8);
    pbStack_94 = in + 0xd;
  }
  bVar14 = 0;
  bVar4 = ss_devKeyPairFind((addrExt_t)CONCAT44(in_stack_ffffff64, in_stack_ffffff60),
                            (ss_dev_pair_set_t *)auStack_48);
  uVar13 = (uint)auStack_7c & ~(~(uint)bVar4 + (uint)bVar4 + (uint)bVar14);
  if (((ss_ib.tcLinkKeyType == '\0') && ((int)((uint)g_zbNwkCtx._45_1_ << 0x1b) < 0)) &&
      ((uVar13 == 0 || (*(char *)(uVar13 + 0x19) != '\0'))))
  {
    iVar6 = 0x44;
    iVar8 = 0x45;
    uVar1 = (undefined)g_sysDiags.apsUnauthorizedKey;
  LAB_0001e8d6:
    iVar9 = CONCAT11(*(undefined *)((int)&g_sysDiags.numberOfResets + iVar8), uVar1) + 1;
    *(char *)((int)&g_sysDiags.numberOfResets + iVar6) = (char)iVar9;
    *(char *)((int)&g_sysDiags.numberOfResets + iVar8) = (char)((uint)iVar9 >> 8);
    iVar6 = 1;
  }
  else
  {
    puStack_98 = ss_ib.tcLinkKey;
    bVar2 = false;
    if (uVar10 == 0x10)
    {
      ptVar7 = tl_zbNeighborTableSearchFromShortAddr(*(u16 *)(in_r0 + 6),
                                                     (addrExt_t)CONCAT44(in_stack_ffffff64, in_stack_ffffff60),
                                                     (u16 *)(auStack_48 + 0x10));
      if (((ptVar7 != (tl_zb_normal_neighbor_entry_t *)0x0) && ((ptVar7->field_0x1e & 0xe) != 0)) &&
          (iVar6 = memcmp(auStack_48 + 0x10, (ss_dev_pair_set_t *)auStack_48, 8), iVar6 == 0))
      {
        puStack_98 = ss_ib.distibuteLinkKey;
        bVar2 = true;
      }
    }
    if (uVar13 != 0)
    {
      puStack_98 = (u8 *)(uVar13 + 8);
    }
    uVar10 = ((uint) * (byte *)in_r0 + (uint) * (byte *)(in_r0 + 1)) - ((uint)pbStack_94 & 0xff) & 0xff;
    *in = *in & 0xf8 | 5;
    bVar5 = zb_isDeviceFactoryNew();
    puStack_90 = (u8 *)0x0;
    if (((bVar5 != false) && ((auStack_48._24_4_ & 0x18) == 0x10)) &&
        (puStack_90 = ev_buf_allocate((u16)uVar10), puStack_90 != (u8 *)0x0))
    {
      memcpy(puStack_90, pbStack_94, uVar10);
    }
    if (uVar13 == 0)
    {
      uStack_8c = (uint)auStack_48[28] << 0x18 | auStack_48._24_4_ >> 8;
    }
    else if (*(char *)(uVar13 + 0x19) == '\0')
    {
      uStack_8c = (uint)auStack_48[28] << 0x18 | auStack_48._24_4_ >> 8;
      if (uStack_8c < *(uint *)(uVar13 + 0x20))
      {
        iVar6 = 0x42;
        iVar8 = 0x43;
        uVar1 = (undefined)g_sysDiags.apsFCFailure;
        goto LAB_0001e8d6;
      }
      iVar6 = uStack_8c + 1;
      *(char *)(uVar13 + 0x20) = (char)iVar6;
      *(char *)(uVar13 + 0x21) = (char)((uint)iVar6 >> 8);
      *(char *)(uVar13 + 0x22) = (char)((uint)iVar6 >> 0x10);
      *(char *)(uVar13 + 0x23) = (char)((uint)iVar6 >> 0x18);
    }
    else
    {
      uStack_8c = (uint)auStack_48[28] << 0x18 | auStack_48._24_4_ >> 8;
    }
    local_25 = 0;
    if ((auStack_48._24_4_ & 0x18) != 0)
    {
      if ((auStack_48._24_4_ & 0x18) == 0x18)
      {
        local_25 = 2;
      }
      ss_keyHash();
    }
    auStack_48._8_4_ = uStack_8c;
    auStack_48._24_4_ = auStack_48._24_4_ & 0xfffffff8 | 5;
    auStack_48[12] = auStack_48[24];
    iVar6 = ss_ccmDecryption();
    bVar5 = zb_isDeviceFactoryNew();
    if ((bVar5 != false) && ((auStack_48._24_4_ & 0x18) == 0x10))
    {
      if (iVar6 == 0)
      {
      LAB_0001ea64:
        if (bVar2)
        {
          iVar6 = 0;
          ss_ib.distibuteLinkKey = puStack_98;
        }
        else
        {
          bVar4 = 0;
          uVar10 = memcmp(puStack_98, tcLinkKeyCentralDefault, 0x10);
          iVar6 = ~uVar10 + uVar10 + (uint)bVar4;
          ss_ib.tcLinkKeyType = (u8)iVar6;
          if (iVar6 == 0)
          {
            sVar11 = SS_PRECONFIGURED_UNIQUELLINKKEY;
            ss_ib.tcLinkKey = puStack_98;
          }
          else
          {
            ss_ib.tcLinkKey = tcLinkKeyCentralDefault;
            sVar11 = SS_PRECONFIGURED_GLOBALLINKKEY;
          }
          ss_ib.preConfiguredKeyType = sVar11 | ss_ib.preConfiguredKeyType;
          iVar6 = 0;
        }
      }
      else if ((puStack_90 != (u8 *)0x0) && (m1 = puStack_98, bVar12 != 0))
      {
        do
        {
          if ((bVar12 & 1) == 0)
          {
            if (((bVar12 & 2) == 0) || (!bVar2))
              break;
            puStack_98 = linkKeyDistributedCertification;
            bVar12 = 0;
          LAB_0001e9f0:
            local_25 = 0;
            ss_keyHash();
            memcpy(pbStack_94, puStack_90, uVar10);
            iVar6 = ss_ccmDecryption();
            m1 = puStack_98;
            if (iVar6 == 0)
              goto LAB_0001ea64;
          }
          else
          {
            if (bVar2)
            {
              bVar12 = bVar12 & 0xfe;
              puStack_98 = linkKeyDistributedMaster;
            }
            else
            {
              bVar12 = 0;
              puStack_98 = tcLinkKeyCentralDefault;
            }
            iVar8 = memcmp(m1, puStack_98, 0x10);
            if (iVar8 != 0)
              goto LAB_0001e9f0;
          }
        } while (bVar12 != 0);
      }
    }
    if (puStack_90 != (u8 *)0x0)
    {
      ev_buf_free(puStack_90);
    }
    if (iVar6 == 0)
    {
      *(byte *)(in_r0 + 1) =
          ((*(byte *)(in_r0 + 1) - 4) + (char)in) - (char)((uint)pbStack_94 & 0xff);
      pbStack_94 = pbStack_94 + (*in_r0 - (int)in);
      *(byte *)in_r0 = (byte)pbStack_94;
      *(byte *)((int)in_r0 + 1) = (byte)((uint)pbStack_94 >> 8);
      *(byte *)((int)in_r0 + 2) = (byte)((uint)pbStack_94 >> 0x10);
      *(byte *)((int)in_r0 + 3) = (byte)((uint)pbStack_94 >> 0x18);
    }
    else
    {
      g_sysDiags.apsDecryptFailures = g_sysDiags.apsDecryptFailures + 1;
    }
  }
  return iVar6;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
uint ss_apsEnAuxHdrFill(void)

{
  byte *in_r0;
  byte *out;
  char *in_r1;
  int in_r2;

  out = in_r0 + 5;
  in_r0[1] = (byte)ss_ib.outgoingFrameCounter;
  in_r0[2] = (byte)(ss_ib.outgoingFrameCounter >> 8);
  in_r0[3] = (byte)(ss_ib.outgoingFrameCounter >> 0x10);
  in_r0[4] = (byte)(ss_ib.outgoingFrameCounter >> 0x18);
  ss_ib.outgoingFrameCounter = ss_ib.outgoingFrameCounter + 1;
  *in_r0 = *in_r0 & 0xf8 | 5;
  if (in_r1 == (char *)0x0)
  {
    if (in_r2 << 0x1b < 0)
    {
      *in_r0 = *in_r0 | 0x20;
      memcpy(out, g_zbInfo.macPib.extAddress, 8);
      out = in_r0 + 0xd;
    }
  }
  else
  {
    *in_r0 = *in_r0 | 0x20;
    memcpy(out, g_zbInfo.macPib.extAddress, 8);
    out = in_r0 + 0xd;
    if (*in_r1 == '\x05')
    {
      if (in_r1[1] == '\x01')
      {
        *in_r0 = *in_r0 & 0xe7 | 0x10;
      }
      else
      {
        *in_r0 = *in_r0 | 0x18;
      }
      goto LAB_0001e438;
    }
  }
  *in_r0 = *in_r0 & 0xe7;
LAB_0001e438:
  return (int)out - (int)in_r0 & 0xff;
}
// WARNING: Could not reconcile some variable overlaps
// WARNING: Unknown calling convention -- yet parameter storage is locked
undefined4 ss_apsSecureFrame(void)

{
  uint uVar1;
  byte bVar2;
  undefined *in_r0;
  int iVar3;
  byte in_r1;
  byte *pbVar4;
  uint in_r2;
  ss_dev_pair_set_t *in_r3;
  uint uVar5;
  uint uVar6;
  byte bVar7;
  undefined4 in_stack_ffffff80;
  undefined4 in_stack_ffffff84;
  undefined auStack_78[36];
  undefined4 uStack_54;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  undefined4 uStack_48;
  uint local_44;
  int iStack_40;
  undefined4 uStack_3c;
  undefined2 local_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  uint uStack_2c;
  undefined uStack_28;
  undefined local_25;

  local_44 = 0;
  iStack_40 = 0;
  uStack_3c = 0;
  local_38 = 0;
  uStack_54 = 0;
  uStack_50 = 0;
  uStack_4c = 0;
  uStack_48 = 0;
  pbVar4 = *(byte **)(in_r0 + 0x10);
  *pbVar4 = *pbVar4 & 0xdf | 0x20;
  pbVar4 = pbVar4 + (in_r2 & 0xff);
  memcpy(&local_44, pbVar4, (uint)in_r1 - (in_r2 & 0xff));
  uVar1 = local_44 & 0x18;
  uVar6 = local_44 & 0x18;
  bVar7 = 7 < uVar6;
  if (uVar6 != 8)
  {
    bVar2 = ss_devKeyPairFind((addrExt_t)CONCAT44(in_stack_ffffff84, in_stack_ffffff80), in_r3);
    uVar5 = ~(~(uint)bVar2 + (uint)bVar2 + (uint)bVar7) & (uint)auStack_78;
    if ((ss_ib.tcLinkKeyType == '\0') && ((int)((uint)g_zbNwkCtx._45_1_ << 0x1b) < 0))
    {
      if ((uVar5 == 0) || (*(char *)(uVar5 + 0x19) != '\0'))
        goto LAB_0001e5bc;
    }
    else if (uVar5 == 0)
    {
      ss_securityModeIsDistributed();
    }
    if (uVar1 != 0)
    {
      local_25 = 0;
      if (uVar6 == 0x18)
      {
        local_25 = 2;
      }
      ss_keyHash();
    }
  }
  uStack_34 = 0;
  uStack_30 = 0;
  uStack_2c = iStack_40 << 0x18 | local_44 >> 8;
  local_44 = local_44 & 0xfffffff8 | 5;
  uStack_28 = (undefined)local_44;
  memcpy(&uStack_34, g_zbInfo.macPib.extAddress, 8);
  iVar3 = ss_ccmEncryption();
  if (iVar3 != 0)
  {
    in_r0[0x14] = (char)iVar3 + in_r1;
    *pbVar4 = *pbVar4 & 0xf8;
    return 0;
  }
LAB_0001e5bc:
  in_r0[2] = 0xad;
  *in_r0 = (char)*(undefined2 *)(in_r0 + 8);
  in_r0[1] = (char)((ushort) * (undefined2 *)(in_r0 + 8) >> 8);
  tl_zbTaskPost(zdo_nlme_status_indication, in_r0);
  return 1;
}
