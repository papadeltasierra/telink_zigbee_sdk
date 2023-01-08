// WARNING: Unknown calling convention -- yet parameter storage is locked
void ss_apsRequestKeyCmdHandle(void)

{
  u8 uVar1;
  zb_buf_t *in_r0;
  undefined1 *out;
  undefined4 uVar2;
  undefined *puVar3;
  char *pcVar4;
  int iVar5;
  undefined4 in_stack_ffffffb8;
  undefined4 in_stack_ffffffbc;
  u16 auStack_30[6];

  if (((int)((uint)g_zbNwkCtx._45_1_ << 0x1b) < 0) &&
      (*(char *)(*(int *)(in_r0->buf + 0xc) + 1) == '\x04'))
  {
    uVar1 = tl_zbExtAddrByShortAddr(*(u16 *)(in_r0->buf + 0x14),
                                    (addrExt_t)CONCAT44(in_stack_ffffffbc, in_stack_ffffffb8), auStack_30);
    if ((uVar1 == '\0') &&
        ((ss_ib.tcPolicy.allowTCLKrequest == '\x01' &&
          ((int)(uint)ss_ib.devKeyPairNum < (int)(TL_ZB_NWK_ADDR_MAP_SIZE - 1)))))
    {
      out = (undefined1 *)ss_tcKeyPairFind();
      if (out != (undefined1 *)0x0)
      {
      LAB_0001f3f6:
        memcpy(out, auStack_30, 8);
        drv_generateRandomData(out + 8, '\x10');
        out[0x19] = 0;
        out[0x18] = 1;
        out[0x20] = 0;
        out[0x21] = 0;
        out[0x22] = 0;
        out[0x23] = 0;
        out[0x1c] = 0;
        out[0x1d] = 0;
        out[0x1e] = 0;
        out[0x1f] = 0;
        uVar2 = FUN_0000162c(ss_ib.ssTimeoutPeriod, 1000);
        out[0x24] = (char)uVar2;
        out[0x25] = (char)((uint)uVar2 >> 8);
        out[0x26] = (char)((uint)uVar2 >> 0x10);
        out[0x27] = (char)((uint)uVar2 >> 0x18);
        puVar3 = (undefined *)tl_bufInitalloc(in_r0, '\'');
        *puVar3 = 5;
        puVar3[1] = 4;
        memcpy(puVar3 + 2, out + 8, 0x10);
        memcpy(puVar3 + 0x12, auStack_30, 8);
        memcpy(puVar3 + 0x1a, g_zbInfo.macPib.extAddress, 8);
        aps_cmd_send();
        return;
      }
      pcVar4 = g_ssTcKeyPair + 0x1a;
      iVar5 = 0;
      do
      {
        out = g_ssTcKeyPair + iVar5 * 0x28;
        if (*pcVar4 == '\0')
        {
          g_ssTcKeyPair[iVar5 * 0x28 + 0x1a] = 1;
          goto LAB_0001f3f6;
        }
        iVar5 = iVar5 + 1;
        pcVar4 = pcVar4 + 0x28;
      } while (iVar5 != 10);
    }
  }
  zb_buf_free(in_r0);
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void ss_apsUpdateDeviceCmdHandle(void)

{
  byte bVar1;
  u16 shortAddr;
  u8 uVar2;
  zb_buf_t *in_r0;
  int iVar3;
  undefined in_stack_ffffffb4;
  undefined7 in_stack_ffffffb5;
  char cStack_33;
  undefined uStack_28;
  undefined auStack_27[8];
  byte bStack_1f;
  byte bStack_1e;
  u8 uStack_1d;

  shortAddr = *(u16 *)(in_r0->buf + 0x14);
  bVar1 = in_r0->buf[0x1f];
  memcpy(&uStack_28, *(void **)(in_r0->buf + 0xc), 0xc);
  iVar3 = (uint)bStack_1e * 0x100 + (uint)bStack_1f;
  in_r0->buf[0x10] = (u8)iVar3;
  in_r0->buf[0x11] = (u8)((uint)iVar3 >> 8);
  memcpy(in_r0->buf + 8, auStack_27, 8);
  in_r0->buf[0x12] = uStack_1d;
  uVar2 = tl_zbExtAddrByShortAddr(shortAddr, (addrExt_t)CONCAT71(in_stack_ffffffb5, in_stack_ffffffb4), (u16 *)in_r0);
  if (uVar2 == 0xff)
  {
  LAB_0001f1f6:
    zb_buf_free(in_r0);
  }
  else
  {
    uVar2 = ss_devKeyPairFind((addrExt_t)CONCAT71(in_stack_ffffffb5, in_stack_ffffffb4),
                              (ss_dev_pair_set_t *)in_r0);
    if (uVar2 == '\0')
    {
      if ((bVar1 == 0) && (cStack_33 == '\0'))
        goto LAB_0001f1f6;
    }
    else if ((ss_ib.tcLinkKeyType == '\0') && ((bVar1 & 1) == 0))
      goto LAB_0001f1f6;
    tl_zbTaskPost(ss_zdoUpdateDeviceIndHandle, in_r0);
    if (g_gpDeviceAnnounceCheckCb != ll_reset)
    {
      FUNDDDDA();
    }
  }
  return;
}
// WARNING: Could not reconcile some variable overlaps
// WARNING: Unknown calling convention -- yet parameter storage is locked
void ss_apsVerifyKeyCmdHandle(void)

{
  zb_buf_t *in_r0;
  ss_dev_pair_set_t *keyPair;
  int iVar1;
  undefined *puVar2;
  int iVar3;
  undefined in_stack_ffffff9c;
  undefined in_stack_ffffff9d;
  undefined6 in_stack_ffffff9e;
  undefined auStack_5a[18];
  undefined4 uStack_48;
  undefined *puStack_44;
  uint uStack_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  undefined local_34;
  undefined auStack_30[19];
  undefined local_1d;

  if ((*(ushort *)(in_r0->buf + 2) & 0xfff8) != 0xfff8)
  {
    memcpy(&stack0xffffff9c, *(void **)(in_r0->buf + 0xc), 0x1a);
    keyPair = (ss_dev_pair_set_t *)ss_tcKeyPairFind();
    if (keyPair != (ss_dev_pair_set_t *)0x0)
    {
      iVar1 = ss_apsVerifyKeyCmdValid();
      if (iVar1 == 0)
      {
        local_1d = 3;
        ss_keyHash();
        iVar3 = memcmp(auStack_30, auStack_5a, 0x10);
        if (iVar3 == 0)
        {
          keyPair->keyAttr = SS_VERIFIED_KEY;
          ss_devKeyPairDelete((addrExt_t)
                                  CONCAT62(in_stack_ffffff9e,
                                           CONCAT11(in_stack_ffffff9d, in_stack_ffffff9c)));
          ss_devKeyPairSave(keyPair);
        }
        else
        {
          iVar1 = 0xad;
        }
      }
      ss_tcKeyPairClear();
      uStack_48 = 0;
      puStack_44 = (undefined *)0x0;
      uStack_40 = 0;
      uStack_3c = 0;
      local_34 = 0;
      uStack_38 = 0xb00;
      puVar2 = (undefined *)tl_bufInitalloc(in_r0, '\v');
      *puVar2 = 0x10;
      puVar2[1] = (char)iVar1;
      puVar2[2] = in_stack_ffffff9d;
      memcpy(puVar2 + 3, &stack0xffffff9e, 8);
      uStack_38 = CONCAT31(uStack_38._1_3_, 2);
      if (iVar1 == 0)
      {
        uStack_38._0_3_ = CONCAT12(1, (undefined2)uStack_38);
      }
      uStack_38 = CONCAT13(1, (undefined3)uStack_38);
      uStack_40 = uStack_40 & 0xffff0000 | (uint) * (ushort *)(in_r0->buf + 0x14);
      local_34 = 1;
      puStack_44 = puVar2;
      aps_cmd_send();
      return;
    }
  }
  zb_buf_free(in_r0);
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
undefined4 ss_apsVerifyKeyCmdValid(void)

{
  bool bVar1;
  int in_r0;
  char in_r1;
  undefined4 uVar2;

  uVar2 = 0xa3;
  if (((((int)((uint)g_zbNwkCtx._45_1_ << 0x1b) < 0) && (uVar2 = 0xaa, in_r1 == '\x04')) &&
       (bVar1 = ss_securityModeIsDistributed(), bVar1 == false)) &&
      ((uVar2 = 0xad, in_r0 != 0 && (uVar2 = 0, *(char *)(in_r0 + 0x18) == '\0'))))
  {
    uVar2 = 0xad;
  }
  return uVar2;
}
// WARNING: Could not reconcile some variable overlaps
// WARNING: Unknown calling convention -- yet parameter storage is locked
void ss_apsmeRequestKeyReq(void)

{
  zb_buf_t *in_r0;
  undefined *puVar1;
  u8 uVar2;
  undefined uVar3;
  uint uStack_24;
  undefined4 uStack_20;
  uint uStack_1c;
  undefined local_18;

  if ((ss_ib.tcPolicy.updateTCLKrequired == '\0') || (1 < (byte)(in_r0->buf[0x10] - 2)))
  {
    zb_buf_free(in_r0);
  }
  else
  {
    if (in_r0->buf[0x11] == '\x02')
    {
      uVar2 = '\n';
      uVar3 = 10;
    }
    else
    {
      uVar2 = '\x02';
      uVar3 = 2;
    }
    puVar1 = (undefined *)tl_bufInitalloc(in_r0, uVar2);
    *puVar1 = 8;
    puVar1[1] = in_r0->buf[0x11];
    if (in_r0->buf[0x11] == '\x02')
    {
      memcpy(puVar1 + 2, in_r0->buf + 8, 8);
    }
    uStack_24 = 0;
    uStack_20 = 0;
    local_18 = 0;
    uVar2 = in_r0->buf[0x10];
    uStack_1c = (uint)CONCAT11(uVar3, uVar2);
    if (uVar2 == '\x02')
    {
      uStack_24 = (uint) * (ushort *)in_r0->buf;
    }
    else if (uVar2 == '\x03')
    {
      memcpy(&uStack_24, in_r0, 8);
    }
    uStack_1c = CONCAT13(1, CONCAT12(1, (undefined2)uStack_1c));
    aps_cmd_send();
  }
  return;
}
// WARNING: Could not reconcile some variable overlaps
// WARNING: Unknown calling convention -- yet parameter storage is locked
void ss_apsmeSwitchKeyReq(void)

{
  zb_buf_t *in_r0;
  undefined *puVar1;
  int iVar2;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined local_14;

  puVar1 = (undefined *)tl_bufInitalloc(in_r0, '\x02');
  *puVar1 = 9;
  puVar1[1] = in_r0->buf[8];
  uStack_20 = 0;
  uStack_1c = 0;
  local_14 = 0;
  uStack_18 = 0x200;
  iVar2 = memcmp(in_r0, &g_invalid_addr, 8);
  if (iVar2 == 0)
  {
    uStack_18 = CONCAT31(uStack_18._1_3_, 2);
    uStack_20 = CONCAT22(uStack_20._2_2_, 0xfffe);
  }
  else
  {
    uStack_18 = CONCAT31(uStack_18._1_3_, 3);
    memcpy(&uStack_20, in_r0, 8);
  }
  uStack_18 = CONCAT13(1, CONCAT12('\x01' - ((uStack_20 & 0xfff8) == 0xfff8), (undefined2)uStack_18));
  aps_cmd_send();
  return;
}
// WARNING: Type propagation algorithm not settling
// WARNING: Could not reconcile some variable overlaps
// WARNING: Unknown calling convention -- yet parameter storage is locked
void ss_apsmeTransportKeyReq(void)

{
  u8 uVar1;
  char cVar2;
  bool bVar3;
  zb_buf_t *in_r0;
  int iVar4;
  undefined *puVar5;
  undefined *out;
  char cVar6;
  undefined uVar7;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined local_24;

  iVar4 = memcmp(in_r0, &g_zero_addr, 8);
  if ((iVar4 == 0) && (in_r0->buf[8] != '\x01'))
  {
    zb_buf_free(in_r0);
    return;
  }
  uStack_30 = 0;
  uStack_2c = 0;
  uStack_28 = 0;
  local_24 = 0;
  puVar5 = (undefined *)tl_bufInitalloc(in_r0, '\'');
  *puVar5 = 5;
  puVar5[1] = in_r0->buf[8];
  memcpy(puVar5 + 2, in_r0->buf + 9, 0x10);
  out = puVar5 + 0x12;
  uStack_28 = CONCAT13(1, (uint3)uStack_28);
  iVar4 = memcmp(in_r0, &g_zero_addr, 8);
  cVar2 = (char)puVar5;
  if (iVar4 == 0)
  {
    uStack_28 = CONCAT31(uStack_28._1_3_, 2);
    uStack_30 = CONCAT22(uStack_30._2_2_, 0xfffe);
    iVar4 = memcmp(in_r0, &g_zero_addr, 8);
  }
  else
  {
    uStack_28 = CONCAT31(uStack_28._1_3_, 3);
    if (in_r0->buf[0x19] == '\0')
    {
      memcpy(&uStack_30, in_r0, 8);
    }
    else
    {
      memcpy(puVar5 + -0x17, in_r0, 8);
      memcpy(&uStack_30, in_r0->buf + 0x1b, 8);
    }
    iVar4 = memcmp(in_r0, &g_zero_addr, 8);
  }
  if ((iVar4 == 0) || (in_r0->buf[0x19] != '\0'))
  {
    uVar7 = 0;
    uVar1 = in_r0->buf[0x24];
  }
  else
  {
    uVar7 = 1;
    uVar1 = in_r0->buf[0x24];
  }
  if ((uVar1 == '\0') && (in_r0->buf[0x19] == '\0'))
  {
    uStack_28 = uStack_28 & 0xffffff;
    uVar1 = in_r0->buf[8];
  }
  else
  {
    uVar1 = in_r0->buf[8];
  }
  if (uVar1 == '\x01')
  {
    puVar5[0x12] = in_r0->buf[0x1a];
    memcpy(puVar5 + 0x13, in_r0, 8);
    bVar3 = ss_securityModeIsDistributed();
    if (bVar3 == false)
    {
      memcpy(puVar5 + 0x1b, g_zbInfo.macPib.extAddress, 8);
    }
    else
    {
      memcpy(puVar5 + 0x1b, ss_ib.trust_center_address, 8);
    }
    cVar6 = cVar2 + '#';
  }
  else if (uVar1 == '\x04')
  {
    memcpy(out, in_r0, 8);
    memcpy(puVar5 + 0x1a, g_zbInfo.macPib.extAddress, 8);
    cVar6 = cVar2 + '\"';
  }
  else
  {
    if (uVar1 == '\x03')
    {
      memcpy(out, in_r0->buf + 0x1b, 8);
      puVar5[0x1a] = in_r0->buf[0x23];
      out = puVar5 + 0x1b;
    }
    cVar6 = (char)out;
  }
  uStack_28._0_3_ = CONCAT12(uVar7, CONCAT11(cVar6 - cVar2, (undefined)uStack_28));
  uStack_28 = uStack_28 & 0xff000000 | (uint)(uint3)uStack_28;
  aps_cmd_send();
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void ss_apsmeUpdateDevReq(void)

{
  zb_buf_t *in_r0;
  void *out;

  if (ss_ib.tcLinkKeyType == '\0')
  {
    ss_apsmeUpdateDevReqSend();
  }
  else if (ss_ib.tcLinkKeyType == '\x01')
  {
    if ((-1 < (int)((uint)aps_ib._18_1_ << 0x1d)) && (out = (void *)c1(), out != (void *)0x0))
    {
      memcpy(out, in_r0, 0x13);
      ev_timer_taskPost(updateDeviceSendAgain, out, 0x14);
    }
    ss_apsmeUpdateDevReqSend();
  }
  else
  {
    zb_buf_free(in_r0);
  }
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void ss_apsmeUpdateDevReqSend(void)

{
  zb_buf_t *in_r0;
  undefined *puVar1;

  puVar1 = (undefined *)tl_bufInitalloc(in_r0, '\f');
  *puVar1 = 6;
  memcpy(puVar1 + 1, in_r0->buf + 8, 8);
  puVar1[9] = in_r0->buf[0x10];
  puVar1[10] = in_r0->buf[0x11];
  puVar1[0xb] = in_r0->buf[0x12];
  aps_cmd_send();
  return;
}
u8 ss_devKeyPairDelete(addrExt_t extAddr)

{
  nv_sts_t nVar1;
  void *in_r0;
  int iVar2;
  int iVar3;
  u8 auStack_48[36];
  ushort local_24;
  u8 uStack_22;

  local_24 = 0;
  uStack_22 = '\0';
  nVar1 = nv_flashReadNew('\0', '\a', 0xff, 0x24, (u8 *)&local_24);
  if (nVar1 == NV_SUCC)
  {
    iVar3 = 0;
    do
    {
      nVar1 = nv_flashReadByIndex('\a', '\b', uStack_22, (u16)iVar3, 0x24, auStack_48);
      if ((nVar1 == NV_SUCC) && (iVar2 = memcmp(in_r0, auStack_48, 8), iVar2 == 0))
      {
        nv_itemDeleteByIndex('\a', '\b', uStack_22, (u16)iVar3);
        ss_ib.devKeyPairNum = ss_ib.devKeyPairNum - 1;
        return '\0';
      }
      iVar3 = iVar3 + 1;
    } while (iVar3 <= (int)(uint)local_24);
    nVar1 = NV_ITEM_NOT_FOUND;
  }
  return nVar1;
}
u8 ss_devKeyPairFind(addrExt_t extAddr, ss_dev_pair_set_t *keyPair)

{
  nv_sts_t nVar1;
  nv_sts_t nVar2;
  int iVar3;
  u8 *in_r1;
  u8 uVar4;
  int iVar5;
  u8 *puVar6;
  undefined auStack_4c[36];
  ushort local_28;
  u8 uStack_26;

  local_28 = 0;
  uStack_26 = '\0';
  nVar1 = nv_flashReadNew('\0', '\a', 0xff, 0x24, (u8 *)&local_28);
  if (nVar1 == NV_SUCC)
  {
    iVar5 = 0;
    puVar6 = (u8 *)0x0;
    nVar1 = NV_ITEM_NOT_FOUND;
    do
    {
      nVar2 = nv_flashReadByIndex('\a', '\b', uStack_26, (u16)iVar5, 0x24, in_r1);
      if (nVar2 != NV_ITEM_NOT_FOUND)
      {
        if ((puVar6 == (u8 *)0x0) && (in_r1[0x19] == '\x01'))
        {
          memcpy(auStack_4c, in_r1, 0x24);
          nVar1 = NV_SUCC;
          puVar6 = in_r1;
        }
        else if (in_r1[0x19] == '\0')
        {
          uVar4 = in_r1[0x18];
          if (uVar4 == '\x01')
          {
            iVar3 = memcmp(keyPair, in_r1, 8);
            if (iVar3 != 0)
              goto LAB_0001ec72;
            memcpy(auStack_4c, in_r1, 0x24);
            uVar4 = in_r1[0x18];
            nVar1 = NV_SUCC;
          }
          if ((uVar4 == '\x02') && (iVar3 = memcmp(keyPair, in_r1, 8), iVar3 == 0))
          {
            return '\0';
          }
        }
      }
    LAB_0001ec72:
      iVar5 = iVar5 + 1;
    } while (iVar5 <= (int)(uint)local_28);
    memcpy(in_r1, auStack_4c, 0x24);
  }
  return nVar1;
}
u16 ss_devKeyPairInfoGet(void)

{
  nv_sts_t nVar1;
  int iVar2;
  u8 auStack_40[36];
  ushort local_1c;
  u8 uStack_1a;

  local_1c = 0;
  uStack_1a = '\0';
  ss_ib.devKeyPairNum = 0;
  nVar1 = nv_flashReadNew('\0', '\a', 0xff, 0x24, (u8 *)&local_1c);
  if (nVar1 == NV_SUCC)
  {
    iVar2 = 0;
    do
    {
      nVar1 = nv_flashReadByIndex('\a', '\b', uStack_1a, (u16)iVar2, 0x24, auStack_40);
      if (nVar1 == NV_SUCC)
      {
        ss_ib.devKeyPairNum = ss_ib.devKeyPairNum + 1;
      }
      iVar2 = iVar2 + 1;
    } while (iVar2 <= (int)(uint)local_1c);
  }
  return ss_ib.devKeyPairNum;
}
void ss_devKeyPairSave(ss_dev_pair_set_t *keyPair)

{
  nv_sts_t nVar1;

  nVar1 = nv_flashWriteNew('\0', 7, '\b', 0x24, keyPair->device_address);
  if (nVar1 == NV_SUCC)
  {
    ss_ib.devKeyPairNum = ss_ib.devKeyPairNum + 1;
  }
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
// WARNING: Unknown calling convention -- yet parameter storage is locked
void ss_tcKeyPairClear(void)

{
  void *in_r0;

  memset(in_r0, 0, 0x28);
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
undefined4 updateDeviceSendAgain(void)

{
  ss_apsmeUpdateDevReqSend();
  return 0xfffffffe;
}
