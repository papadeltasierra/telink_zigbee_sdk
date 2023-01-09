bool ss_keyPreconfigured(void)

{
  char cVar1;
  ss_material_set_t *psVar2;

  psVar2 = ss_ib.nwkSecurMaterialSet + (((uint)ss_ib._62_1_ << 0x1a) >> 0x1e);
  cVar1 = '\0';
  do
  {
    if (psVar2->key[0] != '\0')
      break;
    cVar1 = cVar1 + '\x01';
    psVar2 = (ss_material_set_t *)(psVar2->key + 1);
  } while (cVar1 != '\x10');
  return (bool)('\x01' - (cVar1 == '\x10'));
}
bool ss_securityModeIsDistributed(void)

{
  int iVar1;
  char in_tmpCY;

  iVar1 = memcmp(ss_ib.trust_center_address, &g_invalid_addr, 8);
  return (bool)((byte)iVar1 + ~(byte)iVar1 + in_tmpCY);
}
void ss_securityModeSet(ss_securityMode_e m)

{
  int iVar1;

  if ((int)((uint)aps_ib._18_1_ << 0x1e) < 0)
  {
    iVar1 = memcmp(ss_ib.trust_center_address, &g_zero_addr, 8);
    if ((iVar1 != 0) && (iVar1 = memcmp(ss_ib.trust_center_address, &g_invalid_addr, 8), iVar1 != 0))
    {
      sys_exceptionPost(0x268, '3');
    }
  }
  if (m == SS_SEMODE_CENTRALIZED)
  {
    ss_ib.tcPolicy.updateTCLKrequired = '\x01';
    ss_ib.trust_center_address[0] = '\0';
    ss_ib.trust_center_address[1] = '\0';
    ss_ib.trust_center_address[2] = '\0';
    ss_ib.trust_center_address[3] = '\0';
    ss_ib.trust_center_address[4] = '\0';
    ss_ib.trust_center_address[5] = '\0';
    ss_ib.trust_center_address[6] = '\0';
    ss_ib.trust_center_address[7] = '\0';
  }
  else if (m == 1)
  {
    ss_ib.tcPolicy.updateTCLKrequired = '\0';
    memcpy(ss_ib.trust_center_address, &g_invalid_addr, 8);
  }
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void ss_tcSwitchKey(void)

{
  ss_zdoNwkKeySwitch();
  if ((zdo_mgmt_nwk_flag & 2) != 0)
  {
    zdo_mgmt_nwk_flag = zdo_mgmt_nwk_flag & 0xfd;
  }
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void ss_tcSwitchKeyTimerStart(void)

{
  code *unaff_r8;

  (*unaff_r8)();
  if ((int)((uint)zdo_mgmt_nwk_flag << 0x1e) < 0)
  {
    ev_timer_taskPost(tcSwitchKeyTimerCb, (void *)0x0, 3000);
  }
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void ss_tcTransportKeyTimerStart(void)

{
  void *in_r0;
  uint uVar1;

  zdo_mgmt_nwk_flag = zdo_mgmt_nwk_flag | 2;
  uVar1 = (((uint)ss_ib._62_1_ << 0x1a) >> 0x1e) + 1 & 1;
  memcpy(ss_ib.nwkSecurMaterialSet + uVar1, (void *)((int)in_r0 + 9), 0x10);
  ss_ib.nwkSecurMaterialSet[uVar1].keySeqNum = *(u8 *)((int)in_r0 + 0x1a);
  ss_ib.nwkSecurMaterialSet[uVar1].keyType = *(u8 *)((int)in_r0 + 8);
  ev_timer_taskPost(zb_tcTransportKeyTimerCb, in_r0, 1000);
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void ss_zdoChildAuthStart(void)

{
  byte bVar1;
  u8 uVar2;
  zb_buf_t *in_r0;
  tl_zb_normal_neighbor_entry_t *ptVar3;
  int iVar4;
  uint uVar5;
  undefined in_stack_ffffff94;
  undefined7 in_stack_ffffff95;
  char cStack_54;
  char cStack_53;
  undefined4 local_48;
  undefined4 uStack_44;
  undefined local_40[34];
  u8 uStack_1e;

  memcpy(&local_48, in_r0, 0x15);
  uVar5 = 1;
  local_40[12] = local_40[12] | (local_40[11] != '\0') * '\x02';
  if (((local_40[12] != 0) && (uVar5 = 0, local_40[12] != 3)) && (uVar5 = 0xff, local_40[12] == 2))
  {
    uVar5 = 3;
  }
  ptVar3 = nwk_neTblGetByExtAddr((addrExt_t)CONCAT71(in_stack_ffffff95, in_stack_ffffff94));
  if ((ss_ib._62_1_ & 7) == 0)
  {
    if ((ptVar3 != (tl_zb_normal_neighbor_entry_t *)0x0) &&
        (bVar1 = ptVar3->field_0x1e, (bVar1 & 0x70) == 0x50))
    {
      if ((bVar1 & 0xe) == 4)
      {
        ptVar3->field_0x1e = bVar1 & 0x8f | 0x10;
        ss_zdoChildTableStore();
      }
      else
      {
        ptVar3->field_0x1e = bVar1 & 0x8f | 0x20;
      }
    }
  }
  else
  {
    if (((uVar5 == 0) && (ptVar3 != (tl_zb_normal_neighbor_entry_t *)0x0)) &&
        ((ptVar3->field_0x1e & 0x70) == 0x10))
    {
      ss_zdoChildTableStore();
    }
    if ((int)((uint)g_zbNwkCtx._45_1_ << 0x1b) < 0)
    {
      if (uVar5 != 0)
      {
        uVar2 = ss_devKeyPairFind((addrExt_t)CONCAT71(in_stack_ffffff95, in_stack_ffffff94),
                                  (ss_dev_pair_set_t *)local_40);
        if (uVar5 == 3)
        {
          if ((ss_ib.tcPolicy.allowRejoins == '\0') &&
              ((uVar2 != '\0' ||
                ((cStack_53 == '\x01' &&
                  (iVar4 = memcmp(tcLinkKeyCentralDefault, ss_ib.tcLinkKey, 0x10), iVar4 == 0))))))
            goto LAB_0002007c;
        }
        else if ((((uVar2 == '\0') && (uVar5 == 1)) && (cStack_53 == '\0')) && (cStack_54 == '\x02'))
        {
          ss_devKeyPairDelete((addrExt_t)CONCAT71(in_stack_ffffff95, in_stack_ffffff94));
        }
        memcpy(in_r0, (ss_dev_pair_set_t *)local_40, 8);
        in_r0->buf[8] = '\x01';
        if ((int)((uint)ss_ib.preConfiguredKeyType << 0x1d) < 0)
        {
          memset(in_r0->buf + 9, 0, 0x10);
          in_r0->buf[0x1a] = '\0';
        }
        else
        {
          memcpy(in_r0->buf + 9, ss_ib.nwkSecurMaterialSet + (((uint)ss_ib._62_1_ << 0x1a) >> 0x1e),
                 0x10);
          in_r0->buf[0x1a] = ss_ib.activeKeySeqNum;
        }
        in_r0->buf[0x19] = local_40[10];
        if (local_40[10] != '\0')
        {
          memcpy(in_r0->buf + 0x1b, &local_48, 8);
        }
        in_r0->buf[0x24] = '\0';
        if ((zdoAppIndCbLst != 0) && (*(int *)(zdoAppIndCbLst + 0x20) != 0))
        {
          local_40._16_4_ = uStack_44;
          local_40._20_4_ = local_48;
          local_40._24_4_ = local_40._4_4_;
          local_40._28_4_ = local_40._0_4_;
          local_40._32_2_ = local_40._8_2_;
          uStack_1e = (u8)uVar5;
          iVar4 = ss_tcSwitchKeyTimerStart();
          if (iVar4 == 0)
            goto LAB_0002007c;
        }
      LAB_000201d8:
        tl_zbTaskPost(ss_apsmeTransportKeyReq, in_r0);
        return;
      }
    }
    else
    {
      iVar4 = memcmp(ss_ib.trust_center_address, &g_invalid_addr, 8);
      if (iVar4 != 0)
      {
        in_r0->buf[0x12] = (u8)uVar5;
        memcpy(in_r0, ss_ib.trust_center_address, 8);
        in_r0->buf[0x10] = local_40[8];
        in_r0->buf[0x11] = local_40[9];
        memcpy(in_r0->buf + 8, (ss_dev_pair_set_t *)local_40, 8);
        tl_zbTaskPost(ss_apsmeUpdateDevReq, in_r0);
        return;
      }
      if ((uVar5 != 0) && ((uVar5 - 3) + ~(uVar5 - 3) + (uint)(2 < uVar5) == 0))
      {
        memcpy(in_r0, (ss_dev_pair_set_t *)local_40, 8);
        in_r0->buf[8] = '\x01';
        if ((int)((uint)ss_ib.preConfiguredKeyType << 0x1d) < 0)
        {
          memset(in_r0->buf + 9, 0, 0x10);
          in_r0->buf[0x1a] = '\0';
        }
        else
        {
          memcpy(in_r0->buf + 9, ss_ib.nwkSecurMaterialSet + (((uint)ss_ib._62_1_ << 0x1a) >> 0x1e),
                 0x10);
          in_r0->buf[0x1a] = ss_ib.activeKeySeqNum;
        }
        in_r0->buf[0x19] = '\0';
        in_r0->buf[0x24] = '\0';
        goto LAB_000201d8;
      }
    }
  }
LAB_0002007c:
  zb_buf_free(in_r0);
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void ss_zdoChildTableStore(void)

{
  u16 uVar1;
  int in_r0;
  u8 *arg;
  undefined4 unaff_r4;
  undefined4 in_lr;

  arg = ev_buf_allocate(0xc);
  if (arg != (u8 *)0x0)
  {
    uVar1 = tl_zbshortAddrByIdx(*(u16 *)(in_r0 + 0x16));
    *arg = (u8)uVar1;
    arg[1] = (u8)((uint)uVar1 >> 8);
    tl_zbExtAddrByIdx(*(u16 *)(in_r0 + 0x16), (addrExt_t)CONCAT44(unaff_r4, in_lr));
    arg[0xb] = arg[0xb] & 0x8f | (byte)((*(byte *)(in_r0 + 0x1e) >> 4 & 7) << 4);
    arg[0xb] = arg[0xb] & 0xfe | *(byte *)(in_r0 + 0x1e) & 1;
    arg[0xb] = arg[0xb] & 0xf1 | (byte)((*(byte *)(in_r0 + 0x1e) >> 1 & 7) << 1);
    arg[10] = *(u8 *)(in_r0 + 0x20);
    tl_zbTaskPost(nwk_nodeAddrInfoStore, arg);
  }
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
int ss_zdoGetNwkKeyBySeqNum(void)

{
  u8 in_r0;
  int iVar1;
  uint uVar2;

  uVar2 = ((uint)ss_ib._62_1_ << 0x1a) >> 0x1e;
  if ((ss_ib.nwkSecurMaterialSet[uVar2].keySeqNum == in_r0) ||
      (uVar2 = uVar2 + 1 & 1, ss_ib.nwkSecurMaterialSet[uVar2].keySeqNum == in_r0))
  {
    iVar1 = uVar2 * 0x12 + 0x842170;
  }
  else
  {
    iVar1 = 0;
  }
  return iVar1;
}
void ss_zdoInit(bool enSecurity)

{
  byte bVar1;
  nv_sts_t nVar2;
  u8 uVar3;
  int iVar4;
  undefined in_stack_ffffffe8;
  undefined uVar5;
  undefined in_stack_ffffffe9;
  undefined uVar6;
  undefined in_stack_ffffffea;
  undefined uVar7;
  undefined in_stack_ffffffeb;
  undefined uVar8;
  undefined4 in_stack_ffffffec;

  if (((int)((uint)g_zbNwkCtx._45_1_ << 0x1f) < 0) || (uVar3 = zdo_ssInfoInit(), uVar3 != '\0'))
  {
    if (enSecurity)
    {
      ss_ib._62_1_ = ss_ib._62_1_ & 0xf8 | 0xd;
      ss_ib.preConfiguredKeyType = SS_PRECONFIGURED_NOKEY;
      ss_ib.devKeyPairNum._0_1_ = 0;
      ss_ib.devKeyPairNum._1_1_ = 0;
    }
    else
    {
      ss_ib._62_1_ = ss_ib._62_1_ & 0xf8;
    }
  }
  else
  {
    aps_ib._18_1_ = aps_ib._18_1_ | 2;
    tl_neighborFrameCntReset();
    ss_devKeyPairInfoGet();
    iVar4 = memcmp(ss_ib.trust_center_address, &g_zero_addr, 8);
    if ((iVar4 != 0) && (iVar4 = memcmp(ss_ib.trust_center_address, &g_invalid_addr, 8), iVar4 != 0))
    {
      tl_zbNwkAddrMapAdd(0, (addrExt_t)CONCAT44(in_stack_ffffffec, CONCAT13(in_stack_ffffffeb, CONCAT12(in_stack_ffffffea, CONCAT11(in_stack_ffffffe9, in_stack_ffffffe8)))), (u16 *)ss_ib.trust_center_address);
    }
  }
  ss_ib.ssTimeoutPeriod._0_1_ = 0x87;
  ss_ib.ssTimeoutPeriod._1_1_ = 0x13;
  ss_ib.ssTimeoutPeriod._2_1_ = 0;
  ss_ib.ssTimeoutPeriod._3_1_ = 0;
  bVar1 = af_nodeDescStackRevisionGet();
  ss_ib.tcPolicy.allowRejoins = bVar1 < 0x15;
  ss_ib.tcPolicy.allowJoins = '\x01';
  uVar5 = 0;
  uVar6 = 0;
  uVar7 = 0;
  uVar8 = 0;
  nVar2 = nv_nwkFrameCountFromFlash((u32 *)&stack0xffffffe8);
  ss_ib.outgoingFrameCounter._0_1_ = uVar5;
  ss_ib.outgoingFrameCounter._1_1_ = uVar6;
  ss_ib.outgoingFrameCounter._2_1_ = uVar7;
  ss_ib.outgoingFrameCounter._3_1_ = uVar8;
  if (nVar2 != NV_SUCC)
  {
    ss_ib.outgoingFrameCounter._0_1_ = 0;
    ss_ib.outgoingFrameCounter._1_1_ = 0;
    ss_ib.outgoingFrameCounter._2_1_ = 0;
    ss_ib.outgoingFrameCounter._3_1_ = 0;
  }
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void ss_zdoNwkKeyConfigure(void)

{
  void *in;
  uint extraout_r1;
  u8 extraout_r2;
  code *in_r3;
  uint uVar1;

  in = (void *)(*in_r3)();
  uVar1 = extraout_r1 & 0xff;
  if (uVar1 < 2)
  {
    memcpy(ss_ib.nwkSecurMaterialSet + uVar1, in, 0x10);
    ss_ib.nwkSecurMaterialSet[uVar1].keySeqNum = (u8)extraout_r1;
    ss_ib.nwkSecurMaterialSet[uVar1].keyType = extraout_r2;
  }
  else
  {
    sys_exceptionPost(0x1e9, '@');
  }
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void ss_zdoNwkKeySwitch(void)

{
  u8 in_r0;
  int iVar1;

  if (ss_ib.nwkSecurMaterialSet[0].keySeqNum == in_r0)
  {
    iVar1 = 0;
  }
  else
  {
    iVar1 = 1;
    if (ss_ib.nwkSecurMaterialSet[1].keySeqNum != in_r0)
    {
      return;
    }
  }
  if (ss_ib.activeKeySeqNum != in_r0)
  {
    ss_ib._62_1_ = ss_ib._62_1_ & 0xcf | (byte)(iVar1 << 4);
    if (0x80000000 < ss_ib.outgoingFrameCounter)
    {
      ss_ib.outgoingFrameCounter = 0;
    }
    ss_ib.activeKeySeqNum = in_r0;
    tl_neighborFrameCntReset();
    nv_nwkFrameCountSaveToFlash(ss_ib.outgoingFrameCounter);
    zdo_ssInfoSaveToFlash();
  }
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void ss_zdoTcInit(void)

{
  g_zbNwkCtx._45_1_ = g_zbNwkCtx._45_1_ | 0x10;
  memcpy(ss_ib.trust_center_address, g_zbInfo.macPib.extAddress, 8);
  aps_ib._18_1_ = aps_ib._18_1_ | 2;
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void ss_zdoUpdateDeviceIndHandle(void)

{
  u8 uVar1;
  bool bVar2;
  zb_buf_t *in_r0;
  int iVar3;
  undefined in_stack_ffffffd8;
  undefined7 in_stack_ffffffd9;
  u16 local_12;

  uVar1 = in_r0->buf[0x12];
  if (uVar1 == '\x02')
  {
    iVar3 = tl_idxByExtAddr();
    if ((iVar3 != 0xff) || (iVar3 = FUNBBBBK(), iVar3 != 0xff))
    {
      tl_zbExtAddrByIdx(local_12, (addrExt_t)CONCAT71(in_stack_ffffffd9, in_stack_ffffffd8));
      if ((zdoAppIndCbLst != 0) && (*(int *)(zdoAppIndCbLst + 0xc) != 0))
      {
        ss_zdoNwkKeyConfigure();
      }
      tl_zbshortAddrByIdx(local_12);
      nwkRoutingTabEntryDstDel();
      tl_zbExtAddrByIdx(local_12, (addrExt_t)CONCAT71(in_stack_ffffffd9, in_stack_ffffffd8));
      tl_zbshortAddrByIdx(local_12);
      nwkRouteRecTabEntryDstDel();
      ss_devKeyPairDelete((addrExt_t)CONCAT71(in_stack_ffffffd9, in_stack_ffffffd8));
      aps_bindingTblEntryDelByDstExtAddr();
      tl_nwkNeighborDeleteByAddrmapIdx(local_12);
      tl_zbNwkAddrMapDelete(local_12);
    }
  }
  else if (uVar1 != '\0')
  {
    if (uVar1 == '\x03')
    {
      bVar2 = ss_securityModeIsDistributed();
      if (bVar2 == false)
        goto LAB_000204a8;
    }
    else if ((uVar1 == '\x01') && (ss_ib.tcPolicy.allowJoins != '\0'))
    {
    LAB_000204a8:
      tl_zbNwkAddrMapAdd(*(u16 *)(in_r0->buf + 0x10),
                         (addrExt_t)CONCAT71(in_stack_ffffffd9, in_stack_ffffffd8),
                         (u16 *)(in_r0->buf + 8));
      in_r0->buf[0x12] = '\x01';
      in_r0->buf[0x13] = '\0';
      in_r0->buf[0x14] = '\0';
      ss_zdoChildAuthStart();
      return;
    }
  }
  zb_buf_free(in_r0);
  return;
}
void ss_zdoUseKey(byte param_1)

{
  if (param_1 < 2)
  {
    ss_ib._62_1_ = ss_ib._62_1_ & 0xcf | (byte)((param_1 & 3) << 4);
    ss_ib.activeKeySeqNum = param_1;
  }
  else
  {
    sys_exceptionPost(0x201, '@');
  }
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
int tcSwitchKeyTimerCb(void)

{
  u8 uVar1;
  ss_apsmeSwitchKeyReq_t sStack_14;

  memcpy(&sStack_14, &g_invalid_addr, 8);
  sStack_14.keySeqNum = ss_ib.activeKeySeqNum + '\x01';
  uVar1 = zb_apsmeSwitchKeyReq(&sStack_14);
  return -(uint)(uVar1 == '\0');
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
undefined4 zb_tcTransportKeyTimerCb(void)

{
  void *in_r0;

  tl_zbTaskPost(ss_apsmeTransportKeyReq, in_r0);
  return 0xfffffffe;
}
void zdo_ssInfoUpdate(void)

{
  if ((((ss_ib.outgoingFrameCounter & 0x3ff) == 0) && (g_zbInfo.bdbAttr.nodeIsOnANetwork != '\0')) && (g_bdbCtx.state == '\0'))
  {
    ss_ib.outgoingFrameCounter = ss_ib.outgoingFrameCounter + 1;
    nv_nwkFrameCountSaveToFlash(ss_ib.outgoingFrameCounter);
  }
  return;
}
