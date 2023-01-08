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


