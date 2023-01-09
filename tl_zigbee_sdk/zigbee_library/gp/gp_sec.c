u8 gpCcmStar(u8 appId, gpdId_t gpdId, u8 gpdfSecKey, u8 gpdfSecLevel, u8 endpoint, u32 secFrameCounter,
             u8 gpdAsduLen, u8 *gpdAsdu, bool autoComm, bool rxAfterTx, u32 mic, u8 *pKey)

{
  ushort size;
  uint length;
  u8 uVar1;
  u8 *aStr;
  u8 *puVar2;
  int iVar3;
  u8 aStrLen;
  u8 uStack_58;
  uint uStack_54;
  uint local_44;
  uint uStack_40;
  u32 uStack_3c;
  undefined uStack_38;
  uint local_34;
  uint uStack_30;
  u8 local_2c;
  u8 local_28;

  local_34 = (uint)gpdfSecLevel;
  uStack_30 = (uint)gpdfSecKey;
  iVar3 = (int)((ulonglong)gpdId & 0xff000000ff);
  length = (uint)gpdAsduLen;
  uVar1 = '\0';
  if (((ulonglong)gpdId & 0xff) != 0)
  {
    uStack_38 = 5;
    if (appId == '\0')
    {
      uStack_40 = (uint)gpdfSecKey;
      uStack_54 = 10;
      local_28 = appId;
    }
    else
    {
      if (appId != '\x02')
      {
        return '\x01';
      }
      local_28 = '\0';
      uStack_54 = 7;
      uStack_40 = local_34;
    }
    local_44 = (uint)gpdfSecKey;
    uStack_3c = secFrameCounter;
    local_2c = local_28;
    local_28 = gpNwkHdrFrameCtrlBuild();
    if (iVar3 == 3)
    {
      aStr = ev_buf_allocate((u16)uStack_54);
    }
    else
    {
      if (iVar3 != 2)
      {
        return '\x01';
      }
      uStack_54 = uStack_54 + length & 0xff;
      aStr = ev_buf_allocate((u16)uStack_54);
    }
    uVar1 = '\x01';
    if (aStr != (u8 *)0x0)
    {
      *aStr = local_28;
      aStr[1] = local_2c;
      puVar2 = aStr + 2;
      if (appId == '\0')
      {
        aStr[2] = gpdfSecKey;
        aStr[3] = '\0';
        aStr[4] = '\0';
        aStr[5] = '\0';
        puVar2 = aStr + 6;
      }
      else if (appId == '\x02')
      {
        uStack_58 = (u8)(((ulonglong)gpdId & 0xff000000ff) >> 0x20);
        aStr[2] = uStack_58;
        puVar2 = aStr + 3;
      }
      *puVar2 = (u8)secFrameCounter;
      puVar2[1] = (u8)(secFrameCounter >> 8);
      puVar2[2] = (u8)(secFrameCounter >> 0x10);
      puVar2[3] = (u8)(secFrameCounter >> 0x18);
      aStrLen = (u8)uStack_54;
      if (iVar3 == 2)
      {
        memcpy(puVar2 + 4, gpdAsdu, length);
        aes_ccmDecTran('\x04', pKey, (u8 *)&local_44, (u8 *)0x0, 0, aStr, aStrLen, (u8 *)&mic);
        uVar1 = aes_ccmDecAuthTran('\x04', pKey, (u8 *)&local_44, (u8 *)0x0, 0, aStr, aStrLen, (u8 *)&mic);
        uVar1 = '\x01' - (uVar1 == '\0');
      }
      else
      {
        uVar1 = '\x01';
        if (iVar3 == 3)
        {
          size = (ushort)gpdAsduLen;
          puVar2 = ev_buf_allocate(size);
          if ((puVar2 == (u8 *)0x0) && (gpdAsduLen != '\0'))
          {
            ev_buf_free(aStr);
            return '\x01';
          }
          memcpy(puVar2, gpdAsdu, length);
          aes_ccmDecTran('\x04', pKey, (u8 *)&local_44, gpdAsdu, size, aStr, aStrLen, (u8 *)&mic);
          uVar1 = aes_ccmDecAuthTran('\x04', pKey, (u8 *)&local_44, gpdAsdu, size, aStr, aStrLen,
                                     (u8 *)&mic);
          uVar1 = uVar1 != '\0';
          if ((bool)uVar1)
          {
            memcpy(gpdAsdu, puVar2, length);
          }
          if (puVar2 != (u8 *)0x0)
          {
            ev_buf_free(puVar2);
          }
        }
      }
      ev_buf_free(aStr);
    }
  }
  return uVar1;
}
