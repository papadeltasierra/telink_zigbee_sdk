u8 tl_zbMacHdrSize(u16 frameCtrl)

{
  u8 uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;

  uVar2 = (uint)frameCtrl;
  uVar3 = (uVar2 << 0x14) >> 0x1e;
  uVar4 = (uVar2 << 0x10) >> 0x1e;
  uVar1 = '\x03';
  if ((uVar3 != 0) && (uVar1 = '\a', uVar3 == 3))
  {
    uVar1 = '\r';
  }
  if (uVar4 != 0)
  {
    if (uVar4 == 3)
    {
      uVar1 = uVar1 + '\b';
    }
    else
    {
      uVar1 = uVar1 + '\x02';
    }
    if (-1 < (int)(uVar2 << 0x19))
    {
      uVar1 = uVar1 + '\x02';
    }
  }
  return uVar1;
}

// WARNING: Unknown calling convention -- yet parameter storage is locked

undefined *tl_zbMacHdrBuilder(void)

{
  undefined *in_r0;
  uint uVar1;
  ushort *in_r1;
  uint uVar2;
  uint uVar3;
  undefined *out;

  uVar3 = (uint)*in_r1;
  uVar1 = (uVar3 << 0x14) >> 0x1e;
  uVar2 = (uVar3 << 0x10) >> 0x1e;
  *in_r0 = (char)*in_r1;
  in_r0[1] = (char)(uVar3 >> 8);
  in_r0[2] = g_zbInfo.macPib.seqNum;
  out = in_r0 + 3;
  g_zbInfo.macPib.seqNum = g_zbInfo.macPib.seqNum + '\x01';
  if (uVar1 != 0)
  {
    in_r0[3] = *(undefined *)(in_r1 + 3);
    in_r0[4] = *(undefined *)((int)in_r1 + 7);
    if (uVar1 == 3)
    {
      memcpy(in_r0 + 5, in_r1 + 4, 8);
      out = in_r0 + 0xd;
    }
    else
    {
      in_r0[5] = *(undefined *)(in_r1 + 4);
      in_r0[6] = *(undefined *)((int)in_r1 + 9);
      out = in_r0 + 7;
    }
  }
  if (uVar2 != 0)
  {
    if (-1 < (int)(uVar3 << 0x19))
    {
      *out = *(undefined *)(in_r1 + 8);
      out[1] = *(undefined *)((int)in_r1 + 0x11);
      out = out + 2;
    }
    if (uVar2 == 3)
    {
      memcpy(out, in_r1 + 9, 8);
      out = out + 8;
    }
    else
    {
      *out = *(undefined *)(in_r1 + 9);
      out[1] = *(undefined *)((int)in_r1 + 0x13);
      out = out + 2;
    }
  }
  return out;
}

uint tl_zbMacHdrParse(tl_mac_hdr_t *macHdr,u8 *rxBuf)

{
  tl_mac_hdr_fc_t tVar1;
  uint uVar2;
  uint uVar3;
  u8 *in;

  tVar1 = *(tl_mac_hdr_fc_t *)rxBuf;
  uVar2 = (uint)(ushort)tVar1;
  memset(macHdr,0,0x1a);
  macHdr->frameCtrl = tVar1;
  macHdr->seqNum = rxBuf[2];
  in = rxBuf + 3;
  macHdr->infElPresent = (byte)((uVar2 << 0x14) >> 0x1e);
  uVar3 = (uVar2 << 0x10) >> 0x1e;
  macHdr->srcIeeeAddrMode = (byte)(uVar2 >> 8) >> 6;
  macHdr->framePending = (byte)((uVar2 << 0x19) >> 0x1f);
  if ((uVar2 << 0x14) >> 0x1e != 0) {
    memcpy(&macHdr->destPAN,in,2);
    if (macHdr->infElPresent == '\x02') {
      memcpy(macHdr->destAddrr,rxBuf + 5,2);
      in = rxBuf + 7;
      uVar3 = (uint)macHdr->srcIeeeAddrMode;
    }
    else {
      memcpy(macHdr->destAddrr,rxBuf + 5,8);
      in = rxBuf + 0xd;
      uVar3 = (uint)macHdr->srcIeeeAddrMode;
    }
  }
  if (uVar3 == 0) goto LAB_000129d6;
  if (macHdr->framePending == '\0') {
    memcpy(&macHdr->destPanIdAgain?,in,2);
    in = in + 2;
    if (macHdr->srcIeeeAddrMode == '\x02') goto LAB_00012a1a;
  }
  else if (uVar3 == 2) {
LAB_00012a1a:
    memcpy(macHdr->srcAddr,in,2);
    in = in + 2;
    goto LAB_000129d6;
  }
  memcpy(macHdr->srcAddr,in,8);
  in = in + 8;
LAB_000129d6:
  // Returning ZigBee payload length.
  return (int)in - (int)rxBuf & 0xff;
}


