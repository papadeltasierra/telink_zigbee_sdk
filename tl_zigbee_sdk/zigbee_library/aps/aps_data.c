// WARNING: Unknown calling convention -- yet parameter storage is locked
void apsAckPeriodic(void)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  s8 *psVar4;

  if (APS_TX_CACHE_TABLE_SIZE != '\0')
  {
    psVar4 = &aps_txCache_tbl[0].apsAddrWaitTimeout;
    iVar3 = 0;
    do
    {
      while (((int)((uint)(byte)aps_txCache_tbl[iVar3].field_0x12 << 0x1f) >> 0x1f) * -0x1000000 !=
             0)
      {
        bVar1 = (byte)aps_txCache_tbl[iVar3].field_0x12 >> 4;
        if (bVar1 != 3)
        {
          if ((bVar1 == 1) &&
              (iVar2 = ((byte)*psVar4 - 1) * 0x1000000, *psVar4 = (byte)((uint)iVar2 >> 0x18),
               iVar2 < 1))
          {
            apsTxEventPost();
          }
          break;
        }
        iVar2 = ((byte)psVar4[-1] - 1) * 0x1000000;
        psVar4[-1] = (byte)((uint)iVar2 >> 0x18);
        if (0 < iVar2)
          break;
        apsTxEventPost();
        iVar3 = iVar3 + 1;
        psVar4 = psVar4 + 0x1c;
        if ((int)(uint)APS_TX_CACHE_TABLE_SIZE <= iVar3)
        {
          return;
        }
      }
      iVar3 = iVar3 + 1;
      psVar4 = psVar4 + 0x1c;
    } while (iVar3 < (int)(uint)APS_TX_CACHE_TABLE_SIZE);
  }
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void apsDataFragmentRcvWinClear(void)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  byte *pbVar4;
  int iVar5;

  if (g_apsDataFragmentRcvWin[89] != '\0')
  {
    if (g_apsDataFragmentRcvWin._0_4_ != 0)
    {
      ev_timer_taskCancel((ev_timer_event_t **)g_apsDataFragmentRcvWin);
    }
    g_apsDataFragmentRcvWin._4_4_ = 0;
    pbVar4 = g_apsDataFragmentRcvWin + 0x28;
    iVar5 = 0;
    do
    {
      if (((g_apsDataFragmentRcvWin[iVar5 * 0x24 + 0x2b] & 0x7f) != 0) &&
          (uVar1 = (uint)*pbVar4, uVar1 != 0))
      {
        uVar2 = 0;
        do
        {
          iVar3 = (uVar2 + iVar5 * 9 + 2) * 4;
          if (*(zb_buf_t **)(g_apsDataFragmentRcvWin + iVar3) != (zb_buf_t *)0x0)
          {
            zb_buf_free(*(zb_buf_t **)(g_apsDataFragmentRcvWin + iVar3));
            *(undefined4 *)(g_apsDataFragmentRcvWin + iVar3) = 0;
            uVar1 = (uint)*pbVar4;
          }
          uVar2 = uVar2 + 1 & 0xff;
        } while (uVar2 < uVar1);
      }
      iVar5 = iVar5 + 1;
      pbVar4 = pbVar4 + 0x24;
    } while (iVar5 != 2);
    memset(g_apsDataFragmentRcvWin, 0, 0x5a);
  }
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void apsDataFragmentReSend(void)

{
  int iVar1;
  uint uVar2;

  if ((g_apsDataFragmentTransWin[47] != '\0') &&
      (iVar1 = 0x2e, g_apsDataFragmentTransWin[46] != '\0'))
  {
    uVar2 = 0;
    if (g_apsDataFragmentTransWin[45] == 0xff)
    {
    LAB_00021d38:
      g_apsDataFragmentTransWin[iVar1] = (char)uVar2;
    }
    else
    {
      do
      {
        if (((int)(uint)g_apsDataFragmentTransWin[45] >> uVar2 & 1U) == 0)
        {
          iVar1 = *(int *)(g_apsDataFragmentTransWin + uVar2 * 4);
          *(byte *)(iVar1 + 0x12) = *(byte *)(iVar1 + 0x12) & 0xf;
          *(u8 *)(iVar1 + 0x14) = APS_ACK_EXPIRY;
          *(u8 *)(iVar1 + 0x13) = APS_MAX_FRAME_RETRIES;
          apsTxEventPost();
          iVar1 = 0x2d;
          uVar2 = 1 << uVar2 | (uint)g_apsDataFragmentTransWin[45];
          goto LAB_00021d38;
        }
        uVar2 = uVar2 + 1;
      } while (uVar2 != 8);
    }
  }
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
undefined4 apsDataFragmentRequest(void)

{
  u8 uVar1;
  char cVar2;
  void *in_r0;
  u8 *dest;
  int iVar3;
  undefined4 in_r1;
  undefined2 in_r2;
  undefined4 uVar4;

  uVar4 = 0x39;
  if (((g_apsDataFragmentTransWin[47] == '\0') && (g_apsDataFragmentTransWin._32_4_ == (u8 *)0x0)) && (dest = ev_buf_allocate(0x1f), dest != (u8 *)0x0))
  {
    memset(dest, 0, 0x1f);
    memcpy(dest, in_r0, 0x1f);
    uVar1 = aps_ib.aps_fragment_payload_size;
    g_apsDataFragmentTransWin[47] = '\x01';
    g_apsDataFragmentTransWin[46] = 0;
    g_apsDataFragmentTransWin[45] = 0xff;
    g_apsDataFragmentTransWin._32_4_ = dest;
    g_apsDataFragmentTransWin._36_4_ = in_r1;
    g_apsDataFragmentTransWin._40_2_ = in_r2;
    iVar3 = FUNAAAAB();
    cVar2 = FUN_00001624(in_r2, uVar1);
    g_apsDataFragmentTransWin[42] = ('\x01' - (iVar3 == 0)) + cVar2;
    g_apsDataFragmentTransWin[43] = 0;
    tl_zbTaskPost(aps_data_fragment, (void *)0x0);
    uVar4 = 0;
  }
  return uVar4;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
undefined4 apsDataRequest(void)

{
  undefined uVar1;
  void *in_r0;
  zb_buf_t *p;
  undefined4 uVar2;
  void *out;
  int iVar3;
  void *in_r1;
  byte in_r2;

  p = (zb_buf_t *)c1();
  uVar2 = 0x39;
  if (p != (zb_buf_t *)0x0)
  {
    memset(p, 0, 0x1f);
    out = tl_bufInitalloc(p, in_r2);
    if ((uint)((int)out - (int)p) < 0x27)
    {
      zb_buf_free(p);
      sys_exceptionPost(0x6fc, 'P');
      uVar2 = 6;
    }
    else
    {
      if ((*(short *)((int)in_r0 + 4) == 0) && (*(short *)((int)in_r0 + 6) == 0x13))
      {
        *(undefined *)((int)in_r0 + 0xe) = 0x49;
      }
      else
      {
        do
        {
          uVar1 = aps_get_handle();
          iVar3 = apsHandleIsExit();
        } while (iVar3 != 0);
        *(undefined *)((int)in_r0 + 0xe) = uVar1;
      }
      memcpy(out, in_r1, (uint)in_r2);
      memcpy(p, in_r0, 0x1f);
      p->buf[0] = (u8)out;
      p->buf[1] = (u8)((uint)out >> 8);
      p->buf[2] = (u8)((uint)out >> 0x10);
      p->buf[3] = (u8)((uint)out >> 0x18);
      p->buf[9] = in_r2;
      tl_zbTaskPost(aps_data_request, p);
      uVar2 = 0;
    }
  }
  return uVar2;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
undefined4 apsHandleIsExit(void)

{
  u8 in_r0;
  int iVar1;
  aps_tx_cache_list_t *paVar2;

  if (APS_TX_CACHE_TABLE_SIZE != 0)
  {
    iVar1 = 0;
    paVar2 = aps_txCache_tbl;
    while (true)
    {
      if (((paVar2->field_0x12 & 1) != 0) && (paVar2->handler == in_r0))
      {
        return 1;
      }
      iVar1 = iVar1 + 1;
      if ((int)(uint)APS_TX_CACHE_TABLE_SIZE <= iVar1)
        break;
      paVar2 = paVar2 + 1;
    }
  }
  return 0;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void apsRcvingWindowHandling(void)

{
  void *out;
  void *in_r0;
  uint uVar1;
  int iVar2;
  void *in;
  int iVar3;
  uint uVar4;

  out = g_apsDataFragmentRcvWin._4_4_;
  if ((*(byte *)((int)in_r0 + 0x23) & 0x7f) == 2)
  {
    if (g_apsDataFragmentRcvWin._4_4_ == (void *)0x0)
    {
      sys_exceptionPost(0x1bd, 'R');
    }
    else
    {
      uVar4 = 0;
      if (*(char *)((int)in_r0 + 0x20) != '\0')
      {
        do
        {
          iVar3 = uVar4 * 4;
          if (CONCAT13(*(undefined *)((int)in_r0 + iVar3 + 3),
                       CONCAT12(*(undefined *)((int)in_r0 + iVar3 + 2),
                                CONCAT11(*(undefined *)((int)in_r0 + iVar3 + 1),
                                         *(undefined *)((int)in_r0 + iVar3)))) != 0)
          {
            aps_indPrimBuild();
            in = (void *)CONCAT13(*(undefined *)((int)in_r0 + iVar3 + 3),
                                  CONCAT12(*(undefined *)((int)in_r0 + iVar3 + 2),
                                           CONCAT11(*(undefined *)((int)in_r0 + iVar3 + 1),
                                                    *(undefined *)((int)in_r0 + iVar3))));
            uVar1 = (uint) * (byte *)((int)in_r0 + 0x21);
            if (uVar1 == 0)
            {
              g_apsDataFragmentRcvWin._80_2_ = *(ushort *)((int)in + 10);
              memcpy(out, in, 0x23);
              uVar1 = (uint) * (byte *)((int)in_r0 + 0x21);
            }
            memcpy((void *)((int)out + (uVar1 + uVar4) * (uint)g_apsDataFragmentRcvWin._80_2_ + 0x25), *(void **)((int)in + 0xc), (uint) * (ushort *)((int)in + 10));
            iVar2 = (uint) * (ushort *)((int)in + 10) + (uint) * (ushort *)((int)out + 0x23);
            *(char *)((int)out + 0x23) = (char)iVar2;
            *(char *)((int)out + 0x24) = (char)((uint)iVar2 >> 8);
            zb_buf_free((zb_buf_t *)
                            CONCAT13(*(undefined *)((int)in_r0 + iVar3 + 3),
                                     CONCAT12(*(undefined *)((int)in_r0 + iVar3 + 2),
                                              CONCAT11(*(undefined *)((int)in_r0 + iVar3 + 1),
                                                       *(undefined *)((int)in_r0 + iVar3)))));
            *(undefined *)((int)in_r0 + iVar3) = 0;
            *(undefined *)((int)in_r0 + iVar3 + 1) = 0;
            *(undefined *)((int)in_r0 + iVar3 + 2) = 0;
            *(undefined *)((int)in_r0 + iVar3 + 3) = 0;
            g_apsDataFragmentRcvWin[86] = g_apsDataFragmentRcvWin[86] + 1;
          }
          uVar4 = uVar4 + 1 & 0xff;
        } while (uVar4 < *(byte *)((int)in_r0 + 0x20));
      }
      memset(in_r0, 0, 0x24);
      if (g_apsDataFragmentRcvWin[85] < g_apsDataFragmentRcvWin[86])
      {
        sys_exceptionPost(0x1dc, 'R');
      }
      if (g_apsDataFragmentRcvWin[86] == g_apsDataFragmentRcvWin[85])
      {
        tl_zbTaskPost(af_aps_data_fragment_entry, out);
        apsDataFragmentRcvWinClear();
      }
    }
  }
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
undefined4 apsTxDataSendStart(void)

{
  void *in;
  int in_r0;
  void *out;
  undefined4 uVar1;
  int iVar2;

  in = *(void **)(in_r0 + 8);
  out = (void *)c1();
  if (out == (void *)0x0)
  {
    aps_txCacheConfirm();
    uVar1 = 1;
  }
  else
  {
    memcpy(out, in, 0xc3);
    iVar2 = (int)out + ((uint) * (byte *)((int)in + 0x10) - (int)in & 0xff);
    *(char *)((int)out + 0x10) = (char)iVar2;
    *(char *)((int)out + 0x11) = (char)((uint)iVar2 >> 8);
    *(char *)((int)out + 0x12) = (char)((uint)iVar2 >> 0x10);
    *(char *)((int)out + 0x13) = (char)((uint)iVar2 >> 0x18);
    if ((int)((uint) * (byte *)(in_r0 + 0x12) << 0x1c) < 0)
    {
      tl_zbNwkInterPanDataReq();
      uVar1 = 0;
    }
    else
    {
      tl_zbPrimitivePost('\x03', 'p', out);
      uVar1 = 0;
    }
  }
  return uVar1;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void apsTxEventPost(void)

{
  byte bVar1;
  char cVar2;
  int in_r0;
  int iVar3;
  char in_r1;

  bVar1 = *(byte *)(in_r0 + 0x12);
  switch (bVar1 >> 4)
  {
  case 0:
    if ((int)((uint)bVar1 << 0x1e) < 0)
    {
      *(byte *)(in_r0 + 0x12) = bVar1 & 0xf | 0x10;
      return;
    }
  LAB_00021ca0:
    iVar3 = apsTxDataSendStart();
    if (iVar3 == 0)
    {
      *(byte *)(in_r0 + 0x12) = *(byte *)(in_r0 + 0x12) & 0xf | 0x20;
    }
    return;
  case 1:
    if (in_r1 == '\0')
      goto LAB_00021ca0;
    break;
  case 2:
  case 3:
  case 4:
    if (in_r1 == '\x01')
    {
      if (((int)((uint)bVar1 << 0x1d) < 0) &&
          (cVar2 = *(char *)(in_r0 + 0x13), *(char *)(in_r0 + 0x13) = cVar2 + -1, cVar2 != '\0'))
      {
        iVar3 = apsTxDataSendStart();
        if (iVar3 == 0)
        {
          *(u8 *)(in_r0 + 0x14) = APS_ACK_EXPIRY;
          *(byte *)(in_r0 + 0x12) = *(byte *)(in_r0 + 0x12) & 0xf | 0x40;
          return;
        }
        return;
      }
      goto switchD_00021c5a_caseD_5;
    }
    if (in_r1 == '\x02')
    {
      *(byte *)(in_r0 + 0x12) = bVar1 & 0xf | 0x30;
      return;
    }
    break;
  case 5:
    goto switchD_00021c5a_caseD_5;
  default:
    return;
  }
  if (in_r1 != '\x03')
  {
    return;
  }
switchD_00021c5a_caseD_5:
  aps_txCacheConfirm();
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
undefined4 aps_ack_send(void)

{
  byte bVar1;
  undefined2 uVar2;
  u8 uVar3;
  int in_r0;
  zb_buf_t *p;
  int iVar4;
  byte *pbVar5;
  byte *out;
  byte in_r1;
  byte bVar6;
  uint length;
  u8 uVar7;
  byte *pbVar9;
  u8 uVar10;
  char cVar11;
  byte bVar12;
  undefined4 uVar13;
  undefined4 uVar14;
  u8 uVar8;

  p = (zb_buf_t *)c1();
  if (p == (zb_buf_t *)0x0)
  {
    return 0xb9;
  }
  uVar13 = 0;
  uVar14 = 0;
  bVar1 = *(byte *)(in_r0 + 0x15);
  if ((bVar1 & 3) == 1)
  {
    pbVar5 = (byte *)tl_bufInitalloc(p, '\x02');
    *pbVar5 = 0x12;
    pbVar9 = pbVar5 + 1;
    uVar3 = '\x02';
    length = 0;
    *pbVar9 = *(byte *)(in_r0 + 0x16);
    out = pbVar5 + 2;
    cVar11 = *(char *)(in_r0 + 0x15);
  }
  else
  {
    if ((int)((uint)bVar1 * 0x1000000) < 0)
    {
      bVar6 = 0x82;
      bVar12 = 0x82;
      cVar11 = '\v';
      uVar3 = '\v';
    }
    else
    {
      bVar12 = 2;
      bVar6 = 2;
      cVar11 = '\b';
      uVar3 = '\b';
    }
    length = 0;
    if ((bVar1 & 0x20) != 0)
    {
      bVar6 = bVar12 | 0x20;
      length = ss_apsEnAuxHdrFill();
      uVar3 = cVar11 + (char)length;
    }
    pbVar5 = (byte *)tl_bufInitalloc(p, uVar3);
    *pbVar5 = bVar6;
    pbVar5[1] = *(byte *)(in_r0 + 0x17);
    pbVar5[2] = *(byte *)(in_r0 + 0x1c);
    pbVar5[3] = *(byte *)(in_r0 + 0x1d);
    pbVar5[4] = *(byte *)(in_r0 + 0x1e);
    pbVar5[5] = *(byte *)(in_r0 + 0x1f);
    pbVar5[6] = *(byte *)(in_r0 + 0x1a);
    pbVar9 = pbVar5 + 7;
    *pbVar9 = *(byte *)(in_r0 + 0x16);
    out = pbVar5 + 8;
    cVar11 = *(char *)(in_r0 + 0x15);
  }
  if (cVar11 < '\0')
  {
    pbVar9[1] = 2;
    out[1] = *(byte *)(in_r0 + 0x21);
    out[2] = in_r1;
    out = out + 3;
  }
  uVar7 = (u8)((uint)pbVar5 >> 8);
  uVar8 = (u8)((uint)pbVar5 >> 0x10);
  uVar10 = (u8)((uint)pbVar5 >> 0x18);
  if (length == 0)
  {
    memset(p, 0, 0x1a);
    p->buf[10] = '\0';
    p->buf[0xb] = '\x02';
    p->buf[0xd] = '\x01';
    uVar2 = *(undefined2 *)(in_r0 + 0x18);
    p->buf[8] = (u8)uVar2;
    p->buf[9] = (u8)((ushort)uVar2 >> 8);
    p->buf[0xe] = '\x01';
    p->buf[0xf] = 'K';
    p->buf[0x14] = uVar3;
    p->buf[0x10] = (u8)pbVar5;
    p->buf[0x11] = uVar7;
    p->buf[0x12] = uVar8;
    p->buf[0x13] = uVar10;
  }
  else
  {
    memcpy(out, &stack0xffffffc4, length);
    memset(p, 0, 0x1a);
    p->buf[0xb] = '\x02';
    p->buf[0xd] = '\x01';
    uVar2 = *(undefined2 *)(in_r0 + 0x18);
    p->buf[8] = (u8)uVar2;
    p->buf[9] = (u8)((ushort)uVar2 >> 8);
    p->buf[0xe] = '\x01';
    p->buf[0xf] = 'K';
    p->buf[0x14] = uVar3;
    p->buf[0x10] = (u8)pbVar5;
    p->buf[0x11] = uVar7;
    p->buf[0x12] = uVar8;
    p->buf[0x13] = uVar10;
    uVar3 = zb_address_ieee_by_short(*(u16 *)(in_r0 + 0x18), (addrExt_t)CONCAT44(uVar14, uVar13));
    if (uVar3 != '\0')
    {
      zb_buf_free(p);
      return 0xad;
    }
    iVar4 = ss_apsSecureFrame();
    if (iVar4 != 0)
    {
      return 0xad;
    }
  }
  tl_zbPrimitivePost('\x03', 'p', p);
  return 0;
}
// WARNING: Could not reconcile some variable overlaps
// WARNING: Unknown calling convention -- yet parameter storage is locked
void aps_cmd_send(void)

{
  byte bVar1;
  char cVar2;
  zb_buf_t *buf;
  zb_buf_t *pzVar3;
  undefined2 uVar4;
  undefined uVar5;
  u8 uVar6;
  bool bVar7;
  zb_buf_t **in_r0;
  uint uVar8;
  int iVar9;
  addrExt_t *pauVar10;
  int iVar11;
  byte in_r1;
  uint uVar12;
  uint uVar13;
  byte bVar14;
  undefined *puVar15;
  uint uVar16;
  uint uVar17;
  void *out;
  undefined4 in_stack_ffffffa0;
  uint uStack_58;
  byte bStack_54;
  u8 uStack_50;
  uint local_4c;
  undefined4 uStack_48;
  uint uStack_44;
  undefined4 uStack_40;
  uint uStack_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined2 local_2c;
  undefined local_28;
  undefined uStack_27;

  buf = *in_r0;
  uVar5 = aps_get_counter_value();
  local_4c = 0;
  uStack_48 = 0;
  uStack_40 = 0;
  uStack_3c = (uint)CONCAT11(uVar5, in_r1);
  bVar1 = *(byte *)(in_r0 + 4);
  uStack_44 = (uint)bVar1;
  if (bVar1 == 2)
  {
    local_4c = (uint) * (ushort *)(in_r0 + 2);
  LAB_00022a1a:
    bStack_54 = (byte)(((uint)g_zbNwkCtx._46_1_ << 0x1b) >> 0x1f);
    uVar12 = (uint) * (byte *)(in_r0 + 1);
    uVar8 = (uint) * (byte *)((int)in_r0 + 5);
    uVar13 = (uint) * (byte *)((int)in_r0 + 6);
    pzVar3 = in_r0[1];
    uVar16 = (uint) * (byte *)((int)in_r0 + 7);
    uVar6 = '\0';
    uStack_50 = '\0';
    if ((pzVar3->buf[0] == '\x05') && (pzVar3->buf[1] == '\x01'))
    {
      bVar7 = ss_securityModeIsDistributed();
      uStack_50 = uVar6;
      if (((bVar7 == false) && (in_r1 != 0x48)) &&
          ((*(char *)(in_r0 + 4) != '\x02' || ((*(ushort *)(in_r0 + 2) & 0xfff8) != 0xfff8))))
      {
        uStack_50 = '\x01';
      }
      bStack_54 = 0;
      uVar12 = (uint) * (byte *)(in_r0 + 1);
      uVar8 = (uint) * (byte *)((int)in_r0 + 5);
      uVar13 = (uint) * (byte *)((int)in_r0 + 6);
      uVar16 = (uint) * (byte *)((int)in_r0 + 7);
    }
    local_28 = 1;
    if (*(char *)(in_r0 + 5) != '\0')
    {
      local_28 = 0x41;
    }
    uStack_38 = 0;
    uStack_34 = 0;
    uStack_30 = 0;
    local_2c = 0;
    uVar17 = in_r1 - 0x49;
    iVar9 = ~uVar17 + uVar17;
    uStack_27 = uVar5;
    if ((iVar9 == 0) && (*(char *)((int)in_r0 + 0x12) == '\0'))
    {
      uVar17 = 0xfffffffd;
      uStack_58 = 2;
    }
    else
    {
      iVar11 = ss_apsEnAuxHdrFill();
      uStack_58 = iVar11 + 2U & 0xff;
      uVar17 = ~uStack_58;
      uVar12 = (uint) * (byte *)(in_r0 + 1);
      uVar8 = (uint) * (byte *)((int)in_r0 + 5);
      uVar13 = (uint) * (byte *)((int)in_r0 + 6);
      uVar16 = (uint) * (byte *)((int)in_r0 + 7);
    }
    out = (void *)((uVar8 << 8 | uVar12 | uVar13 << 0x10 | uVar16 << 0x18) + uVar17);
    memcpy(out, &local_28, 2);
    memset(buf, 0, 0x1a);
    buf->buf[10] = uStack_50;
    buf->buf[0xd] = bStack_54;
    buf->buf[0xe] = *(u8 *)((int)in_r0 + 0x13);
    buf->buf[0xf] = in_r1;
    buf->buf[0x14] = *(char *)((int)in_r0 + 0x11) + (char)uStack_58;
    buf->buf[0x10] = (u8)out;
    buf->buf[0x11] = (u8)((uint)out >> 8);
    buf->buf[0x12] = (u8)((uint)out >> 0x10);
    buf->buf[0x13] = (u8)((uint)out >> 0x18);
    if ((iVar9 == 0) && (*(char *)((int)in_r0 + 0x12) == '\0'))
    {
    LAB_00022af8:
      buf->buf[0xb] = '\x02';
      cVar2 = *(char *)(in_r0 + 4);
    }
    else
    {
      if (2 < uStack_58)
      {
        memcpy((void *)((int)out + 2), &uStack_38, uStack_58 - 2);
      }
      if (((iVar9 == 0) && (*(char *)(in_r0 + 4) != '\x03')) &&
          (pauVar10 = tl_zbExtAddrPtrByShortAddr(*(u16 *)(in_r0 + 2)), pauVar10 == (addrExt_t *)0x0))
      {
        bVar14 = 0xad;
        goto LAB_000229f4;
      }
      iVar11 = ss_apsSecureFrame();
      if (iVar11 == 1)
      {
        uStack_44 = CONCAT13(0xad, (undefined3)uStack_44);
        aps_conf();
        return;
      }
      if (iVar9 == 0)
        goto LAB_00022af8;
      iVar9 = *(int *)(buf->buf + 0x10);
      puVar15 = (undefined *)(iVar9 + -0xb);
      buf->buf[0x10] = (u8)puVar15;
      buf->buf[0x11] = (u8)((uint)puVar15 >> 8);
      buf->buf[0x12] = (u8)((uint)puVar15 >> 0x10);
      buf->buf[0x13] = (u8)((uint)puVar15 >> 0x18);
      buf->buf[0x14] = buf->buf[0x14] + '\v';
      *puVar15 = local_28;
      *(undefined *)(iVar9 + -10) = uStack_27;
      *(undefined *)(iVar9 + -9) = 0xe;
      buf->buf[0xb] = '\x02';
      cVar2 = *(char *)(in_r0 + 4);
    }
    if (cVar2 == '\x02')
    {
      uVar4 = *(undefined2 *)(in_r0 + 2);
      buf->buf[8] = (u8)uVar4;
      buf->buf[9] = (u8)((ushort)uVar4 >> 8);
      bVar7 = false;
    }
    else
    {
      uVar6 = tl_zbShortAddrByExtAddr((u16 *)(buf->buf + 8), (addrExt_t)CONCAT44(uVar16, in_stack_ffffffa0),
                                      (u16 *)(in_r0 + 2));
      if (uVar6 == 0xff)
      {
        memcpy(buf, in_r0 + 2, 8);
        bVar7 = true;
      }
      else
      {
        bVar7 = false;
      }
    }
    iVar9 = apsTxDataPost();
    if (iVar9 != 0)
    {
      apsTxEventPost();
      if (!bVar7)
      {
        return;
      }
      aps_txCacheAsNoShortAddr();
      return;
    }
  }
  else
  {
    memcpy(&local_4c, in_r0 + 2, 8);
    bVar14 = 0xa6;
    if ((byte)(bVar1 - 2) < 2)
      goto LAB_00022a1a;
  LAB_000229f4:
    uStack_44 = uStack_44 & 0xffffff | (uint)bVar14 << 0x18;
  }
  aps_conf();
  zb_buf_free(buf);
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void aps_conf(void)

{
  u8 uVar1;
  byte bVar2;
  ushort *in_r0;
  u8 *dest;
  undefined4 in_lr;
  char cVar3;
  undefined uVar4;
  u16 in_stack_ffffffea;

  bVar2 = *(byte *)(in_r0 + 8);
  if (bVar2 < 0x40)
  {
    dest = ev_buf_allocate(0x14);
    if (dest != (u8 *)0x0)
    {
      memset(dest, 0, 0x14);
      memcpy(dest, in_r0, 0x14);
      tl_zbTaskPost(af_dataCnfHandler, dest);
    }
  }
  else
  {
    cVar3 = *(char *)((int)in_r0 + 0xb);
    if (cVar3 == '\0')
    {
      if (bVar2 == 0x49)
      {
        uVar4 = 0;
        uVar1 = tl_zbShortAddrByExtAddr((u16 *)&stack0xffffffea,
                                        (addrExt_t)((ulonglong)CONCAT42(in_lr, in_stack_ffffffea) << 0x10),
                                        (u16 *)g_zbInfo.macPib.extAddress);
        if ((uVar1 == '\0') && (in_stack_ffffffea != g_zbInfo.macPib.shortAddress))
        {
          tl_zbNwkAddrMapAdd(g_zbInfo.macPib.shortAddress,
                             (addrExt_t)
                                 CONCAT44(in_lr, CONCAT22(in_stack_ffffffea, CONCAT11(uVar4, cVar3))),
                             (u16 *)g_zbInfo.macPib.extAddress);
          zb_info_save((void *)0x0);
        }
        bVar2 = af_nodeDescStackRevisionGet();
        if (bVar2 < 0x15)
        {
          bVar2 = *(byte *)(in_r0 + 8);
        }
        else
        {
          tl_zbTaskPost(endDevTimeoutReq, (void *)0x0);
          bVar2 = *(byte *)(in_r0 + 8);
        }
      }
      else if (((bVar2 == 0x41) || (bVar2 == 0x4a)) && (*(char *)(in_r0 + 4) == '\x02'))
      {
        if ((*in_r0 & 0xfff8) == 0xfff8)
        {
          (*(code *)&ss_tcSwitchKeyTimerStart)();
          bVar2 = *(byte *)(in_r0 + 8);
        }
      }
      if (bVar2 == 0x45)
      {
        ss_tcSwitchKey();
      }
    }
  }
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
// WARNING: Removing unreachable block (RAM,0x00022594)
// WARNING: Removing unreachable block (RAM,0x00022612)
// WARNING: Could not reconcile some variable overlaps
// WARNING: Unknown calling convention -- yet parameter storage is locked
void aps_data_request(void)

{
  u8 uVar1;
  u8 uVar2;
  byte bVar3;
  byte bVar4;
  bool bVar5;
  u8 uVar6;
  zb_buf_t *in_r0;
  addrExt_t *pauVar7;
  uint length;
  uint uVar8;
  uint uVar9;
  int iVar10;
  undefined *puVar11;
  u8 *puVar12;
  uint uVar13;
  undefined4 in_stack_ffffff80;
  undefined4 in_stack_ffffff84;
  undefined4 uStack_64;
  undefined4 uStack_60;
  uint uStack_5c;
  uint uStack_58;
  int iStack_54;
  uint uStack_50;
  u8 uStack_4c;
  byte bStack_4b;
  uint local_48;
  undefined4 uStack_44;
  uint uStack_40;
  undefined4 uStack_3c;
  u8 uStack_38;
  u8 uStack_37;
  undefined2 uStack_36;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined2 local_28;

  uVar1 = in_r0->buf[0x1d];
  uVar2 = in_r0->buf[0x1e];
  local_48 = 0;
  uStack_44 = 0;
  uStack_3c = 0;
  uStack_38 = in_r0->buf[0xe];
  uStack_37 = in_r0->buf[0xf];
  bVar3 = in_r0->buf[8];
  uStack_40 = (uint)bVar3 << 0x10;
  bVar4 = in_r0->buf[0xc];
  uStack_40 = uStack_40 | bVar4;
  uStack_36 = *(undefined2 *)(in_r0->buf + 6);
  if (bVar4 == 1)
  {
  LAB_00022338:
    local_48 = (uint) * (ushort *)(in_r0->buf + 0x10);
  LAB_00022342:
    bVar3 = in_r0->buf[10];
    uVar9 = (uint)bVar3;
    uStack_64 = 0;
    uStack_60 = 0;
    iStack_54 = 0;
    uStack_50 = (uint) * (uint3 *)(in_r0->buf + 0x19) << 8;
    uStack_4c = in_r0->buf[0x1c];
    uStack_5c = CONCAT13(2, (uint3)in_r0->buf[0xb] << 0x10);
    uStack_58 = (((uint)g_zbNwkCtx._46_1_ << 0x1b) >> 0x1f) << 8;
    bStack_4b = (byte)((uVar9 << 0x1a) >> 0x1f);
    if (bVar4 == 1)
    {
      if ((int)((uint)g_zbInfo.nwkNib._45_1_ << 0x1c) < 0)
      {
        uStack_5c = CONCAT22(CONCAT11(1, in_r0->buf[0xb]), *(undefined2 *)(in_r0->buf + 0x10));
        in_r0->buf[0x18] = 0xff;
        uStack_58 = uStack_58 | aps_ib.aps_nonmember_radius;
        uVar13 = 8;
      }
      else
      {
        uStack_5c = uStack_5c | GROUP_MESSAGE_SEND_ADDRESS;
        uVar9 = uVar9 & 0xfffffffb;
        uVar13 = 0xc;
      }
      bVar4 = (byte)uVar9;
      uVar9 = uVar9 & 0xfe;
      in_r0->buf[10] = bVar4 & 0xfe;
    LAB_0002239c:
      if ((char)bVar3 < '\0')
      {
        uVar13 = uVar13 | 3;
        uVar8 = uVar9 & 0xfb;
        in_r0->buf[10] = (byte)uVar9 & 0xfb;
        bVar5 = false;
        if (in_r0->buf[0xc] == '\x03')
        {
          uStack_5c = uStack_5c & 0xffffff | 0x3000000;
          memcpy(&uStack_64, in_r0->buf + 0x10, 8);
        }
      }
      else
      {
        uVar8 = (uint)in_r0->buf[10];
        bVar5 = false;
      }
    }
    else
    {
      if (bVar4 == 2)
      {
        uVar13 = 0;
        if ((*(ushort *)(in_r0->buf + 0x10) & 0xfff8) == 0xfff8)
        {
          in_r0->buf[10] = bVar3 & 0xfa;
          uVar13 = 8;
          uVar9 = (uint)in_r0->buf[10];
        }
        uStack_5c = uStack_5c | *(ushort *)(in_r0->buf + 0x10);
        goto LAB_0002239c;
      }
      if (((char)bVar3 < '\0') || (bVar4 != 3))
      {
        uVar13 = 0;
        goto LAB_0002239c;
      }
      uVar6 = tl_zbShortAddrByExtAddr((u16 *)&uStack_5c, (addrExt_t)CONCAT44(in_stack_ffffff84, in_stack_ffffff80),
                                      (u16 *)(in_r0->buf + 0x10));
      if ((uVar6 == 0xff) || (bVar5 = false, (uStack_5c & 0xfff8) == 0xfff8))
      {
        memcpy(&uStack_64, in_r0->buf + 0x10, 8);
        (in_r0->hdr).handle = in_r0->buf[0xe];
        (in_r0->hdr).id = in_r0->buf[8];
        bVar5 = true;
      }
      uVar8 = (uint)in_r0->buf[10];
      uVar13 = 0;
    }
    if ((int)(uVar8 << 0x1d) < 0)
    {
      uVar13 = uVar13 | 0x40;
    }
    if ((int)(uVar8 << 0x1c) < 0)
    {
      uVar13 = 0x7f;
    }
    if ((char)bVar3 < '\0')
    {
      iVar10 = *(int *)in_r0->buf;
      *(char *)(iVar10 + -5) = (char)uVar13;
      *(u8 *)(iVar10 + -4) = in_r0->buf[6];
      *(u8 *)(iVar10 + -3) = in_r0->buf[7];
      *(u8 *)(iVar10 + -2) = in_r0->buf[4];
      *(u8 *)(iVar10 + -1) = in_r0->buf[5];
      uVar8 = 0xfffffffa;
      uVar9 = 5;
    }
    else
    {
      uVar9 = (uVar13 & 0xc) - 0xc;
      iVar10 = ~uVar9 + uVar9 + (uint)(0xb < (uVar13 & 0xc));
      uVar9 = iVar10 + 8;
      if ((int)(uVar8 << 0x1f) < 0)
      {
        uVar13 = uVar13 & 0xdf | 0x20;
        uStack_34 = 0;
        uStack_30 = 0;
        uStack_2c = 0;
        local_28 = 0;
        length = ss_apsEnAuxHdrFill();
        uVar9 = uVar9 + length & 0xff;
      }
      else
      {
        length = 0;
      }
      uVar8 = ~uVar9;
      puVar11 = (undefined *)(*(int *)in_r0->buf + uVar8);
      *puVar11 = (char)uVar13;
      if (iVar10 == 0)
      {
        puVar11[1] = in_r0->buf[0x18];
        puVar12 = puVar11 + 2;
      }
      else
      {
        puVar11[1] = in_r0->buf[0x10];
        puVar11[2] = in_r0->buf[0x11];
        puVar12 = puVar11 + 3;
      }
      *puVar12 = in_r0->buf[6];
      puVar12[1] = in_r0->buf[7];
      puVar12[2] = in_r0->buf[4];
      puVar12[3] = in_r0->buf[5];
      puVar12[4] = in_r0->buf[8];
      if (in_r0->buf[0x19] == '\0')
      {
        uVar6 = in_r0->buf[0xf];
      }
      else
      {
        uVar6 = in_r0->buf[0x1c];
      }
      puVar12[5] = uVar6;
      if (length != 0)
      {
        memcpy(puVar12 + 6, &uStack_34, length);
      }
    }
    uStack_58 = CONCAT13(in_r0->buf[0xe], CONCAT12(in_r0->buf[0xd], (undefined2)uStack_58));
    uStack_50 = uStack_50 & 0xffffff00 | (uint)(byte)(in_r0->buf[9] + (char)uVar9);
    iStack_54 = *(int *)in_r0->buf + uVar8;
    (in_r0->hdr).handle = in_r0->buf[0xe];
    memcpy(in_r0, &uStack_64, 0x1a);
    if ((int)(uVar13 << 0x1a) < 0)
    {
      if ((uVar13 & 0xc) == 0)
      {
        if (!bVar5)
        {
          pauVar7 = tl_zbExtAddrPtrByShortAddr((u16)uStack_5c);
          if (pauVar7 == (addrExt_t *)0x0)
            goto LAB_000224d4;
        }
        iVar10 = ss_apsSecureFrame();
        if (iVar10 != 1)
          goto LAB_0002248a;
      }
    LAB_000224d4:
      if (uVar1 == '\0')
      {
        uStack_40 = CONCAT13(0xad, (undefined3)uStack_40);
        aps_conf();
        return;
      }
    }
    else
    {
    LAB_0002248a:
      iVar10 = apsTxDataPost();
      if (iVar10 != 0)
      {
        if (uVar1 != '\0')
        {
          *(u8 *)(iVar10 + 0x16) = uVar1;
          *(u8 *)(iVar10 + 0x17) = uVar2;
          *(int *)(g_apsDataFragmentTransWin + (uint)g_apsDataFragmentTransWin[44] * 4) = iVar10;
          g_apsDataFragmentTransWin[44] = g_apsDataFragmentTransWin[44] + 1;
        }
        apsTxEventPost();
        if (!bVar5)
        {
          return;
        }
        aps_txCacheAsNoShortAddr();
        return;
      }
      if (uVar1 == '\0')
        goto LAB_00022326;
    }
    tl_zbTaskPost(aps_data_fragment, (void *)0x0);
  }
  else
  {
    if (bVar4 == 2)
    {
      uStack_40._0_2_ = CONCAT11(in_r0->buf[0x18], 2);
      uStack_40 = (uint)CONCAT12(bVar3, (undefined2)uStack_40);
      goto LAB_00022338;
    }
    if (bVar4 == 3)
    {
      uStack_40._0_2_ = CONCAT11(in_r0->buf[0x18], 3);
      uStack_40 = (uint)CONCAT12(bVar3, (undefined2)uStack_40);
      memcpy(&local_48, in_r0->buf + 0x10, 8);
      goto LAB_00022342;
    }
    if (uVar1 != '\0')
    {
      sys_exceptionPost(0x591, 'P');
    }
    puVar12 = ev_buf_allocate((u16)((uint)APS_BINDING_TABLE_SIZE * 0xa0000 + 0x80000 >> 0x10));
    if (puVar12 == (u8 *)0x0)
    {
      uStack_40 = CONCAT13(0xb9, (undefined3)uStack_40);
    }
    else
    {
      iVar10 = aps_search_dst_from_bind_tbl();
      uStack_40 = uStack_40 & 0xffffff | iVar10 << 0x18;
      if (iVar10 == 0)
      {
        *puVar12 = (u8)in_r0;
        puVar12[1] = (u8)((uint)in_r0 >> 8);
        puVar12[2] = (u8)((uint)in_r0 >> 0x10);
        puVar12[3] = (u8)((uint)in_r0 >> 0x18);
        ev_timer_taskPost(bindingTxBack, puVar12, 1);
        return;
      }
      ev_buf_free(puVar12);
    }
  LAB_00022326:
    aps_conf();
    zb_buf_free(in_r0);
  }
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
int aps_duplicate_check(void)

{
  int iVar1;
  byte in_r1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  ushort local_16;

  iVar1 = tl_addrByShort();
  iVar2 = 0;
  if (iVar1 == 0)
  {
    uVar5 = (uint)local_16;
    if ((g_nwkAddrMap.addrMap[uVar5].field_0x13 & 0xe) != 0)
    {
      uVar3 = (uint)g_nwkAddrMap.addrMap[uVar5].aps_dup_cnt;
      uVar4 = uVar3 - in_r1;
      iVar2 = uVar4 + ~uVar4 + (uint)(in_r1 <= uVar3);
    }
    g_nwkAddrMap.addrMap[uVar5].aps_dup_cnt = in_r1;
    g_nwkAddrMap.addrMap[uVar5].field_0x13 =
        g_nwkAddrMap.addrMap[uVar5].field_0x13 & 0xf1 |
        (byte)(((uint)APS_ACK_EXPIRY * (uint)APS_MAX_FRAME_RETRIES + 1 & 7) << 1);
    apsDupliateCheckFlag = 1;
  }
  return iVar2;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void aps_indPrimBuild(void)

{
  byte bVar1;
  byte bVar2;
  undefined uVar3;
  undefined uVar4;
  ushort uVar5;
  ushort uVar6;
  ushort uVar7;
  undefined *in_r0;
  int iVar8;
  undefined uStack_54;
  undefined uStack_50;
  undefined uStack_4c;
  int iStack_48;
  byte bStack_44;
  char cStack_42;
  undefined uStack_41;
  undefined uStack_40;
  undefined uStack_3f;
  undefined uStack_38;
  undefined uStack_37;
  undefined auStack_34[6];
  undefined uStack_2e;
  undefined uStack_2d;

  memcpy(&iStack_48, in_r0, 0x12);
  memcpy(auStack_34, in_r0 + 0x14, 0xf);
  bVar1 = in_r0[0x14];
  bVar2 = in_r0[0x15];
  uVar3 = in_r0[0x16];
  uVar4 = in_r0[0x17];
  uVar5 = *(ushort *)(in_r0 + 0x18);
  uVar6 = *(ushort *)(in_r0 + 0x1c);
  uVar7 = *(ushort *)(in_r0 + 0x1e);
  memset(in_r0, 0, 0x23);
  uStack_50 = (undefined)uVar6;
  in_r0[8] = uStack_50;
  in_r0[9] = (char)((uint)uVar6 >> 8);
  uStack_4c = (undefined)uVar7;
  in_r0[6] = uStack_4c;
  in_r0[7] = (char)((uint)uVar7 >> 8);
  in_r0[5] = uVar4;
  in_r0[1] = uStack_2e;
  uStack_54 = (undefined)uVar5;
  in_r0[0x14] = uStack_54;
  in_r0[0x15] = (char)((uint)uVar5 >> 8);
  in_r0[4] = 2;
  in_r0[0x1c] = uStack_38;
  in_r0[0x1d] = uStack_37;
  in_r0[0x22] = uVar3;
  in_r0[0x20] = uStack_41;
  in_r0[0x21] = in_r0[0xc2];
  if ((bVar2 & 0xc) == 0xc)
  {
    in_r0[2] = uStack_2e;
    in_r0[3] = uStack_2d;
    *in_r0 = 1;
  }
  else
  {
    in_r0[2] = uStack_40;
    in_r0[3] = uStack_3f;
    *in_r0 = 2;
  }
  iStack_48 = iStack_48 + (uint)bVar1;
  in_r0[0xc] = (char)iStack_48;
  in_r0[0xd] = (char)((uint)iStack_48 >> 8);
  in_r0[0xe] = (char)((uint)iStack_48 >> 0x10);
  in_r0[0xf] = (char)((uint)iStack_48 >> 0x18);
  iVar8 = (uint)bStack_44 - (uint)bVar1;
  in_r0[10] = (char)iVar8;
  in_r0[0xb] = (char)((uint)iVar8 >> 8);
  if ((int)((uint)bVar2 << 0x1a) < 0)
  {
    in_r0[0x1f] = in_r0[0x1f] | 1;
  }
  if (cStack_42 != '\0')
  {
    in_r0[0x1f] = in_r0[0x1f] | 2;
  }
  return;
}
// WARNING: Could not reconcile some variable overlaps
// WARNING: Unknown calling convention -- yet parameter storage is locked
void aps_interPanDataIndCb(void)

{
  int iVar1;
  u16 clusterID;
  byte bVar2;
  u8 uVar3;
  zb_buf_t *buf;
  int iVar4;
  af_endpoint_descriptor_t *paVar5;
  code *in_r3;
  byte bVar6;
  uint local_40;
  uint uStack_3c;
  undefined4 uStack_38;
  int iStack_34;
  undefined4 uStack_30;
  uint uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  ushort local_20;
  undefined local_1e;

  buf = (zb_buf_t *)(*in_r3)();
  iVar1 = *(int *)(buf->buf + 4);
  bVar2 = buf->buf[0x1d];
  dstPanID = *(undefined2 *)(buf->buf + 0x10);
  local_40 = 0;
  uStack_38 = 0;
  iStack_34 = 0;
  uStack_30 = 0;
  uStack_2c = 0;
  uStack_28 = 0;
  uStack_24 = 0;
  local_1e = 0;
  local_20 = (ushort)buf->buf[0x27];
  uStack_3c = (uint)buf->buf[0x1c];
  if (buf->buf[0x1c] == 3)
  {
    memcpy(&uStack_2c, buf->buf + 0x14, 8);
  }
  else
  {
    uStack_2c = (uint) * (ushort *)(buf->buf + 0x14);
  }
  if (buf->buf[0x26] == '\x02')
  {
    local_40 = local_40 & 0xffff | (uint) * (ushort *)(buf->buf + 0x1e) << 0x10;
  }
  iVar4 = aps_hdr_parse();
  buf->buf[0x14] = (u8)iVar4;
  clusterID = *(u16 *)(buf->buf + 0x1c);
  uStack_3c = uStack_3c & 0xffff | (uint) * (ushort *)(buf->buf + 0x1e) << 0x10;
  iStack_34 = iVar1 + 2 + iVar4;
  uStack_38 = CONCAT22((bVar2 - 2 & 0xff) - (short)iVar4, clusterID);
  paVar5 = af_epDescriptorGet();
  bVar2 = af_availableEpNumGet();
  if (bVar2 != 0)
  {
    bVar6 = 0;
    do
    {
      uVar3 = af_clsuterIdMatched(clusterID, paVar5->correspond_simple_desc);
      if (uVar3 != '\0')
      {
        local_40._0_2_ = CONCAT11(paVar5->ep, (undefined)local_40);
        local_40 = local_40 & 0xffff0000 | (uint)(ushort)local_40;
        if (bVar6 < bVar2)
        {
          memcpy(buf, &local_40, 0x23);
          tl_zbTaskPost(af_aps_data_entry, buf);
          return;
        }
        break;
      }
      bVar6 = bVar6 + 1;
      paVar5 = paVar5 + 1;
    } while (bVar6 < bVar2);
  }
  zb_buf_free(buf);
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void aps_txCacheAsNoShortAddr(void)

{
  void *in_r0;
  u8 *in_r1;
  zdo_nwk_addr_req_t zStack_18;

  memcpy(&zStack_18, in_r0, 8);
  zStack_18.req_type = ZDO_ADDR_REQ_SINGLE_REQ;
  zStack_18.start_index = '\0';
  zb_zdoNwkAddrReq(0xfffc, &zStack_18, in_r1, aps_nwk_addr_req_cb);
  return;
}
// WARNING: Could not reconcile some variable overlaps
// WARNING: Unknown calling convention -- yet parameter storage is locked
void aps_txCacheConfirm(void)

{
  zb_buf_t *buf;
  u8 *puVar1;
  void *in_r0;
  int in_r1;
  u32 t_ms;
  byte bVar2;
  void *pvVar3;
  uint uVar4;
  undefined4 local_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  uint uStack_28;

  puVar1 = g_apsDataFragmentTransWin._32_4_;
  local_38 = 0;
  uStack_34 = 0;
  uStack_30 = 0;
  uStack_2c = 0;
  uStack_28 = 0;
  if (*(char *)((int)in_r0 + 0x16) == '\0')
  {
    uStack_28 = (uint) * (ushort *)((int)in_r0 + 0xf);
    uStack_30._0_3_ = (uint3) * (byte *)((int)in_r0 + 0xe) << 0x10;
    uStack_30._1_3_ = (uint3)((uint)(in_r1 << 0x18) >> 8) | (uint3)uStack_30 >> 8;
    uStack_30 = CONCAT31(uStack_30._1_3_, *(undefined *)((int)in_r0 + 0xc));
    memcpy(&local_38, in_r0, 8);
    uStack_30._0_2_ = CONCAT11(*(undefined *)((int)in_r0 + 0xd), (undefined)uStack_30);
    uStack_30 = uStack_30 & 0xffff0000 | (uint)(ushort)uStack_30;
    uStack_28 = uStack_28 & 0xffff | (uint) * (ushort *)((int)in_r0 + 0x18) << 0x10;
    aps_conf();
    if (*(zb_buf_t **)((int)in_r0 + 8) != (zb_buf_t *)0x0)
    {
      zb_buf_free(*(zb_buf_t **)((int)in_r0 + 8));
    }
    memset(in_r0, 0, 0x1c);
    g_apsTxCacheNum = g_apsTxCacheNum + -1;
  }
  else
  {
    T_DBG_fgmtCnf._0_1_ = (char)T_DBG_fgmtCnf + '\x01';
    bVar2 = *(byte *)((int)in_r0 + 0x12) & 0xf0;
    if ((((bVar2 == 0x30) || (bVar2 == 0x40)) || (bVar2 == 0x10)) || (bVar2 == 0x20))
    {
      T_DBG_fgmtCnf._1_1_ = T_DBG_fgmtCnf._1_1_ + '\x01';
      if ((in_r1 != 0) ||
          ((int)((g_apsDataFragmentTransWin._40_4_ >> 0x10 & 0xff) - 1) <=
           (int)(g_apsDataFragmentTransWin._40_4_ >> 0x18)))
      {
        uStack_28 = (uint) * (ushort *)(g_apsDataFragmentTransWin._32_4_ + 0xe);
        uStack_30._0_3_ = (uint3)g_apsDataFragmentTransWin._32_4_[8] << 0x10;
        uStack_30._1_3_ = (uint3)((uint)(in_r1 << 0x18) >> 8) | (uint3)uStack_30 >> 8;
        uStack_30 = CONCAT31(uStack_30._1_3_, g_apsDataFragmentTransWin._32_4_[0xc]);
        memcpy(&local_38, g_apsDataFragmentTransWin._32_4_ + 0x10, 8);
        uStack_30._0_2_ = CONCAT11(puVar1[0x18], (undefined)uStack_30);
        uStack_30 = uStack_30 & 0xffff0000 | (uint)(ushort)uStack_30;
        uStack_28 = uStack_28 & 0xffff | (uint) * (ushort *)(puVar1 + 6) << 0x10;
        aps_conf();
        if (g_apsDataFragmentTransWin[47] != '\0')
        {
          if (g_apsDataFragmentTransWin._32_4_ != (u8 *)0x0)
          {
            ev_buf_free(g_apsDataFragmentTransWin._32_4_);
          }
          if (g_apsDataFragmentTransWin[44] != '\0')
          {
            uVar4 = 0;
            do
            {
              pvVar3 = *(void **)(g_apsDataFragmentTransWin + uVar4 * 4);
              if (pvVar3 != (void *)0x0)
              {
                if (*(zb_buf_t **)((int)pvVar3 + 8) != (zb_buf_t *)0x0)
                {
                  zb_buf_free(*(zb_buf_t **)((int)pvVar3 + 8));
                }
                memset(pvVar3, 0, 0x1c);
                g_apsTxCacheNum = g_apsTxCacheNum + -1;
              }
              uVar4 = uVar4 + 1 & 0xff;
            } while (uVar4 < (g_apsDataFragmentTransWin._44_4_ & 0xff));
          }
          g_apsDataFragmentTransWin._0_4_ = 0;
          g_apsDataFragmentTransWin._4_4_ = 0;
          g_apsDataFragmentTransWin._8_4_ = 0;
          g_apsDataFragmentTransWin._12_4_ = 0;
          g_apsDataFragmentTransWin._16_4_ = 0;
          g_apsDataFragmentTransWin._20_4_ = 0;
          g_apsDataFragmentTransWin._24_4_ = 0;
          g_apsDataFragmentTransWin._28_4_ = 0;
          g_apsDataFragmentTransWin._32_4_ = (u8 *)0x0;
          g_apsDataFragmentTransWin._36_4_ = 0;
          g_apsDataFragmentTransWin._40_4_ = 0;
          g_apsDataFragmentTransWin._44_4_ = 0;
        }
        T_DBG_fgmtCnf._2_1_ = T_DBG_fgmtCnf._2_1_ + '\x01';
        return;
      }
      if (aps_ib.aps_max_window_size <= g_apsDataFragmentTransWin[44])
      {
        if (g_apsDataFragmentTransWin[44] != 0)
        {
          uVar4 = 0;
          do
          {
            pvVar3 = *(void **)(g_apsDataFragmentTransWin + uVar4 * 4);
            buf = *(zb_buf_t **)((int)pvVar3 + 8);
            if (buf != (zb_buf_t *)0x0)
            {
              zb_buf_free(buf);
            }
            memset(pvVar3, 0, 0x1c);
            g_apsTxCacheNum = g_apsTxCacheNum + -1;
            *(undefined4 *)(g_apsDataFragmentTransWin + uVar4 * 4) = 0;
            uVar4 = uVar4 + 1 & 0xff;
          } while (uVar4 < (g_apsDataFragmentTransWin._44_4_ & 0xff));
        }
        g_apsDataFragmentTransWin._44_4_ = g_apsDataFragmentTransWin._44_4_ & 0xff000000 | 0xff00;
        g_apsDataFragmentTransWin[46] = '\0';
      }
      T_DBG_fgmtCnf._3_1_ = T_DBG_fgmtCnf._3_1_ + '\x01';
    }
    if (g_apsDataFragmentTransWin[46] == '\0')
    {
      g_apsDataFragmentTransWin._40_4_ =
          g_apsDataFragmentTransWin._40_4_ & 0xffffff |
          (uint)(byte)(g_apsDataFragmentTransWin[43] + 1) << 0x18;
    }
    t_ms = 100;
    if (aps_ib.aps_interframe_delay != 0)
    {
      t_ms = (uint)aps_ib.aps_interframe_delay;
    }
    ev_timer_taskPost(aps_data_fragment_delay, (void *)0x0, t_ms);
  }
  return;
}
// WARNING: Could not reconcile some variable overlaps
// WARNING: Unknown calling convention -- yet parameter storage is locked
undefined4 bindingTxBack(void)

{
  byte bVar1;
  char cVar2;
  undefined2 uVar3;
  undefined uVar4;
  zb_buf_t **in_r0;
  undefined4 *out;
  undefined4 uVar5;
  int iVar6;
  ushort uVar7;
  int iVar8;
  uint local_3c;
  undefined4 uStack_38;
  uint uStack_34;
  undefined4 uStack_30;
  int iStack_2c;
  uint uStack_28;
  int iStack_24;
  int iStack_20;
  undefined2 local_1c;
  undefined local_1a;

  out = (undefined4 *)c1();
  if (out != (undefined4 *)0x0)
  {
    memcpy(out, *in_r0, 0xc3);
    iVar8 = (int)out + (*(int *)(*in_r0)->buf - (int)*in_r0);
    *(char *)out = (char)iVar8;
    *(char *)((int)out + 1) = (char)((uint)iVar8 >> 8);
    *(char *)((int)out + 2) = (char)((uint)iVar8 >> 0x10);
    *(char *)((int)out + 3) = (char)((uint)iVar8 >> 0x18);
    bVar1 = *(byte *)(in_r0 + 1);
    iVar8 = (uint)bVar1 * 10;
    cVar2 = *(char *)((int)in_r0 + iVar8 + 0x11);
    *(char *)(out + 3) = cVar2;
    if (cVar2 == '\x03')
    {
      *(undefined *)(out + 6) = *(undefined *)((int)in_r0 + iVar8 + 0x10);
      memcpy(out + 4, (void *)((int)in_r0 + iVar8 + 8), 8);
    }
    else if (cVar2 == '\x01')
    {
      uVar3 = *(undefined2 *)((int)in_r0 + iVar8 + 8);
      *(char *)(out + 4) = (char)uVar3;
      *(char *)((int)out + 0x11) = (char)((ushort)uVar3 >> 8);
    }
    cVar2 = *(char *)(in_r0 + 1);
    *(byte *)(in_r0 + 1) = cVar2 + 1U;
    if (1 < (byte)(cVar2 + 1U))
    {
      uVar4 = aps_get_counter_value();
      *(undefined *)((int)out + 0xf) = uVar4;
      do
      {
        uVar4 = aps_get_handle();
        iVar8 = apsHandleIsExit();
      } while (iVar8 != 0);
      *(undefined *)((int)out + 0xe) = uVar4;
    }
    iVar8 = (uint)bVar1 * 10;
    if ((*(char *)((int)in_r0 + iVar8 + 0x11) == '\x03') &&
        (iVar6 = memcmp((void *)((int)in_r0 + iVar8 + 8), g_zbInfo.macPib.extAddress, 8), iVar6 == 0))
    {
      local_1c = 0;
      local_3c = (uint)CONCAT21(g_zbInfo.nwkNib.nwkAddr, *(undefined *)((int)in_r0 + iVar8 + 0x10))
                     << 8 |
                 2;
      uVar7 = g_zbInfo.nwkNib.nwkAddr;
      if (*(char *)((int)out + 0x19) != '\0')
      {
        uVar7 = *(ushort *)((int)out + 0x1a);
      }
      uStack_28 = (uint)uVar7;
      uStack_38 = CONCAT22(*(undefined2 *)(out + 1), CONCAT11(*(undefined *)(out + 2), 2));
      uStack_34 = (uint)CONCAT12(*(undefined *)((int)out + 9), *(undefined2 *)((int)out + 6));
      uStack_30 = *out;
      local_1a = *(undefined *)((int)out + 0xf);
      iStack_2c = iVar6;
      iStack_24 = iVar6;
      iStack_20 = iVar6;
      memcpy(out, &local_3c, 0x23);
      tl_zbTaskPost(af_aps_data_entry, out);
    }
    else
    {
      aps_data_request();
    }
    uVar5 = 100;
    if (*(byte *)((int)in_r0 + 5) <= *(byte *)(in_r0 + 1))
    {
      zb_buf_free(*in_r0);
      ev_buf_free((u8 *)in_r0);
      uVar5 = 0xfffffffe;
    }
    return uVar5;
  }
  return 100;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void endDevTimeoutReq(void)

{
  return;
}
