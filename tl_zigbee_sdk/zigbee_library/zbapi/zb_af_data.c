void af_aps_data_entry(void *arg)

{
  ushort uVar1;
  byte bVar2;
  byte bVar3;
  u8 uVar4;
  zb_buf_t *buf;
  af_endpoint_descriptor_t *paVar5;
  u8 *pBuf;
  u8 *out;
  u16 uVar6;
  code *in_r3;
  uint uVar7;
  byte bVar8;

  buf = (zb_buf_t *)(*in_r3)();
  if (buf->buf[1] == '\0')
  {
    if (*(short *)(buf->buf + 6) == 0)
    {
      af_zdoSimpleDescriptorGet();
      af_aps_data_fragment_entry(buf);
      return;
    }
  }
  else
  {
    paVar5 = af_epDescriptorGet();
    bVar3 = af_availableEpNumGet();
    if (bVar3 != 0)
    {
      uVar7 = (uint)buf->buf[10] * 0x1000000 + 0x25000000;
      bVar2 = (byte)(uVar7 >> 0x18);
      pBuf = ev_buf_allocate((ushort)bVar2);
      if (pBuf != (u8 *)0x0)
      {
        memcpy(pBuf, buf, 0x23);
        uVar1 = *(ushort *)(buf->buf + 10);
        pBuf[0x23] = (u8)uVar1;
        pBuf[0x24] = (u8)((uint)uVar1 >> 8);
        memcpy(pBuf + 0x25, *(void **)(buf->buf + 0xc), (uint)uVar1);
        bVar8 = 0;
        do
        {
          uVar4 = buf->buf[1];
          if (paVar5->ep == uVar4)
          {
            uVar4 = af_profileIdMatched(*(u16 *)(buf->buf + 6), paVar5->correspond_simple_desc);
            if ((uVar4 != '\0') || (*(short *)(buf->buf + 6) == -0x3fa2))
            {
              if (paVar5->cb_rx != ll_reset)
              {
                uVar6 = *(u16 *)(buf->buf + 6);
                if (uVar6 == 0xffff)
                {
                  uVar6 = paVar5->correspond_simple_desc->app_profile_id;
                }
                pBuf[6] = (u8)uVar6;
                pBuf[7] = (u8)(uVar6 >> 8);
                af_aps_data_fragment_entry(pBuf);
                goto LAB_0002693a;
              }
              break;
            }
            uVar4 = buf->buf[1];
          }
          if ((uVar4 == 0xff) &&
              (((uVar4 = af_profileIdMatched(*(u16 *)(buf->buf + 6), paVar5->correspond_simple_desc),
                 uVar4 != '\0' || (*(short *)(buf->buf + 6) == -0x3fa2)) &&
                (paVar5->cb_rx != ll_reset))))
          {
            uVar6 = *(u16 *)(buf->buf + 6);
            if (uVar6 == 0xffff)
            {
              uVar6 = paVar5->correspond_simple_desc->app_profile_id;
            }
            pBuf[6] = (u8)uVar6;
            pBuf[7] = (u8)(uVar6 >> 8);
            pBuf[1] = paVar5->ep;
            out = ev_buf_allocate((ushort)bVar2);
            if (out == (u8 *)0x0)
              break;
            memcpy(out, pBuf, uVar7 >> 0x18);
            af_aps_data_fragment_entry(out);
          }
          bVar8 = bVar8 + 1;
          paVar5 = paVar5 + 1;
        } while (bVar8 < bVar3);
        ev_buf_free(pBuf);
      }
    }
  }
LAB_0002693a:
  zb_buf_free(buf);
  return;
}
void af_aps_data_fragment_entry(void *arg)

{
  byte bVar1;
  u8 uVar2;
  u8 *pBuf;
  af_endpoint_descriptor_t *paVar3;
  u16 uVar4;
  code *in_r3;
  byte bVar5;

  pBuf = (u8 *)(*in_r3)();
  paVar3 = af_epDescriptorGet();
  bVar1 = af_availableEpNumGet();
  if (bVar1 != 0)
  {
    bVar5 = 0;
    do
    {
      if (((pBuf[1] == paVar3->ep) &&
           (uVar2 = af_clsuterIdMatched(*(u16 *)(pBuf + 8), paVar3->correspond_simple_desc),
            uVar2 != '\0')) &&
          ((uVar2 = af_profileIdMatched(*(u16 *)(pBuf + 6), paVar3->correspond_simple_desc),
            uVar2 != '\0' || (*(short *)(pBuf + 6) == -0x3fa2))))
      {
        if (paVar3->cb_rx != ll_reset)
        {
          uVar4 = *(u16 *)(pBuf + 6);
          if (uVar4 == 0xffff)
          {
            uVar4 = paVar3->correspond_simple_desc->app_profile_id;
          }
          pBuf[6] = (u8)uVar4;
          pBuf[7] = (u8)(uVar4 >> 8);
          _cgp_mcpsDataIndFilter();
          return;
        }
        break;
      }
      bVar5 = bVar5 + 1;
      paVar3 = paVar3 + 1;
    } while (bVar5 < bVar1);
  }
  ev_buf_free(pBuf);
  return;
}
void af_dataCnfHandler(void *arg)

{
  byte bVar1;
  af_endpoint_descriptor_t *paVar2;
  af_endpoint_descriptor_t *paVar3;
  byte bVar4;

  paVar2 = af_zdoSimpleDescriptorGet();
  paVar3 = af_epDescriptorGet();
  bVar1 = af_availableEpNumGet();
  if ((paVar2->cb_cnf == ll_reset) || (*(char *)((int)arg + 10) != '\0'))
  {
    if (bVar1 != 0)
    {
      bVar4 = 0;
      do
      {
        if ((paVar3->cb_cnf != ll_reset) && (paVar3->ep == *(u8 *)((int)arg + 10)))
          goto LAB_00026910;
        bVar4 = bVar4 + 1;
        paVar3 = paVar3 + 1;
      } while (bVar4 < bVar1);
    }
  }
  else
  {
  LAB_00026910:
    af_aps_data_entry(arg);
  }
  ev_buf_free((u8 *)arg);
  return;
}
// WARNING: Could not reconcile some variable overlaps
u8 af_dataSend(u8 srcEp, epInfo_t *pDstEpInfo, u16 clusterId, u16 cmdPldLen, u8 *cmdPld, u8 *apsCnt)

{
  u8 uVar1;
  u8 uVar2;
  aps_tx_options aVar3;
  uint uVar4;
  uint uStack_24;
  undefined4 uStack_20;
  uint uStack_1c;
  ushort local_18;
  undefined local_16;

  uStack_24 = 0;
  uStack_20 = 0;
  uStack_1c = 0;
  local_18 = 0;
  local_16 = 0;
  uVar2 = pDstEpInfo->dstAddrMode;
  if ((byte)(uVar2 - 2) < 2)
  {
    uStack_1c = (uint)pDstEpInfo->dstEp;
    if (uVar2 != '\x02')
    {
      memcpy(&uStack_24, pDstEpInfo, 8);
      aVar3 = pDstEpInfo->txOptions;
      goto LAB_000267e8;
    }
  }
  else if (uVar2 != '\x01')
  {
    aVar3 = pDstEpInfo->txOptions;
    if ((int)((uint)aVar3 << 0x1c) < 0)
    {
      return '\x01';
    }
    goto LAB_000267e8;
  }
  uStack_24 = (uint)(pDstEpInfo->dstAddr).shortAddr;
  aVar3 = pDstEpInfo->txOptions;
LAB_000267e8:
  uStack_1c = CONCAT22(pDstEpInfo->aliasSrcAddr, CONCAT11(pDstEpInfo->useAlias, (undefined)uStack_1c));
  local_18 = local_18 & 0xff00 | (ushort)pDstEpInfo->aliasSeqNum;
  uVar1 = aps_get_counter_value();
  *apsCnt = uVar1;
  uVar4 = (uint)aVar3;
  if ((int)(uVar4 << 0x1c) < 0)
  {
    if (aps_ib.aps_fragment_payload_size == 0)
    {
      return '\x01';
    }
    if (uVar2 == '\x01')
    {
      return '\x01';
    }
    if ((uVar2 == '\x02') && ((uStack_24 & 0xfff8) == 0xfff8))
    {
      return '\x01';
    }
    if (aps_ib.aps_fragment_payload_size < cmdPldLen)
    {
      uVar4 = uVar4 | 4;
    }
    else
    {
      uVar4 = uVar4 & 0xfffffff7;
    }
    if ((int)(uVar4 << 0x1c) < 0)
    {
      uVar2 = apsDataFragmentRequest();
      return uVar2;
    }
  }
  uVar2 = apsDataRequest();
  return uVar2;
}
