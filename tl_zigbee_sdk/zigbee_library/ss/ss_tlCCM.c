u8 aes_ccmAuthTran(u8 M, u8 *key, u8 *iv, u8 *mStr, u16 mStrLen, u8 *aStr, u8 aStrLen, u8 *result)

{
  u8 uVar1;
  u8 *pBuf;
  uint uVar2;
  uint length;
  uint uVar3;
  uint length_00;
  int iVar4;
  uint uVar5;
  int iVar6;
  u16 uVar7;
  uint uStack_54;
  undefined4 local_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  byte local_34[16];

  length_00 = (uint)mStrLen;
  uVar5 = ((M - 2) * 0x10000000 >> 0x1d) << 3 | 1 | (uint)(aStrLen != '\0') * 0x40;
  local_34[0] = (byte)uVar5;
  memcpy(local_34 + 1, iv, 0xd);
  uVar2 = aStrLen + 2;
  uVar7 = mStrLen;
  pBuf = ev_buf_allocate((u16)uVar2);
  uVar7._1_1_ = (byte)(uVar7 >> 8);
  uVar7._0_1_ = (byte)uVar7;
  uVar1 = 0xff;
  if (pBuf != (u8 *)0x0)
  {
    *pBuf = '\0';
    pBuf[1] = aStrLen;
    memcpy(pBuf + 2, aStr, (uint)aStrLen);
    uVar7._1_1_ = (byte)(uVar7 >> 8);
    uVar7._0_1_ = (byte)uVar7;
    length = uVar2 & 0xff;
    local_44 = 0;
    uStack_40 = 0;
    uStack_3c = 0;
    uStack_38 = 0;
    uVar3 = length;
    if ((uVar2 & 0xf) != 0)
    {
      uVar3 = (uVar2 & 0xf0) + 0x10 & 0xff;
    }
    uVar3 = uVar3 + (mStrLen & 0xff);
    if ((mStrLen & 0xf) != 0)
    {
      uVar3 = (uVar3 & 0xf0) + 0x10;
    }
    local_44._0_1_ = 0;
    uStack_54 = 0;
    iVar6 = 0;
    while (true)
    {
      iVar4 = 0;
      while (true)
      {
        *(byte *)((int)&local_44 + iVar4) = (byte)local_44 ^ (byte)uVar5;
        iVar4 = iVar4 + 1;
        if (iVar4 == 0x10)
          break;
        local_44._0_1_ = *(byte *)((int)&local_44 + iVar4);
        uVar5 = (uint)local_34[iVar4];
      }
      aes_encrypt(key, (uchar *)&local_44, (uchar *)&local_44);
      uVar7._1_1_ = (byte)(uVar7 >> 8);
      uVar7._0_1_ = (byte)uVar7;
      if (length < 0x10)
      {
        if ((length - 2 & 0xff) < 0xf)
        {
          memcpy(local_34, pBuf + iVar6, length);
          uVar7._1_1_ = (byte)(uVar7 >> 8);
          uVar7._0_1_ = (byte)uVar7;
          memset(local_34 + length, 0, 0x10 - length);
          uVar7._1_1_ = (byte)(uVar7 >> 8);
          uVar7._0_1_ = (byte)uVar7;
          uStack_54 = 0;
          length = 0;
        }
        else if (length_00 < 0x10)
        {
          memcpy(local_34, mStr + uStack_54 * 0x10, length_00);
          uVar7._1_1_ = (byte)(uVar7 >> 8);
          uVar7._0_1_ = (byte)uVar7;
          memset(local_34 + length_00, 0, 0x10 - length_00);
          uVar7._1_1_ = (byte)(uVar7 >> 8);
          uVar7._0_1_ = (byte)uVar7;
          length = 0;
        }
        else
        {
          memcpy(local_34, mStr + uStack_54 * 0x10, 0x10);
          uVar7._1_1_ = (byte)(uVar7 >> 8);
          uVar7._0_1_ = (byte)uVar7;
          uStack_54 = uStack_54 + 1 & 0xff;
          length_00 = length_00 - 0x11 & 0xffff;
          length = 0;
        }
      }
      else
      {
        memcpy(local_34, pBuf + iVar6, 0x10);
        uVar7._1_1_ = (byte)(uVar7 >> 8);
        uVar7._0_1_ = (byte)uVar7;
        length = length - 0x11 & 0xff;
      }
      if ((uVar3 & 0xff) + 0x10 <= iVar6 + 0x10U)
        break;
      iVar6 = iVar6 + 0x10;
      uVar5 = (uint)local_34[0];
    }
    memcpy(result, &local_44, (uint)M);
    uVar7._1_1_ = (byte)(uVar7 >> 8);
    uVar7._0_1_ = (byte)uVar7;
    ev_buf_free(pBuf);
    uVar7._1_1_ = (byte)(uVar7 >> 8);
    uVar7._0_1_ = (byte)uVar7;
    uVar1 = '\0';
  }
  return uVar1;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
undefined4 aes_ccmBaseTran(void)

{
  uint in_r0;
  uchar *in_r1;
  void *in_r2;
  byte *pbVar1;
  int in_r3;
  uint uVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  uint in_stack_00000000;
  int in_stack_0000000c;
  char in_stack_00000010;
  byte local_48[16];
  byte local_38;
  undefined auStack_37[13];
  undefined uStack_2a;
  undefined uStack_29;
  undefined local_28;

  uVar5 = in_stack_00000000 & 0xffff;
  local_28 = 1;
  local_38 = 1;
  memcpy(auStack_37, in_r2, 0xd);
  uStack_29 = 0;
  uStack_2a = 0;
  aes_encrypt(in_r1, &local_38, local_48);
  if ((in_r0 & 0xff) != 0)
  {
    uVar2 = 0;
    do
    {
      *(byte *)(in_stack_0000000c + uVar2) = *(byte *)(in_stack_0000000c + uVar2) ^ local_48[uVar2];
      uVar2 = uVar2 + 1;
    } while ((uVar2 & 0xffff) < (in_r0 & 0xff));
  }
  uStack_2a = 0;
  uStack_29 = 1;
  if ((in_stack_00000010 != '\x01') || (uVar5 != 0))
  {
    if ((in_stack_00000000 & 0xf) != 0)
    {
      in_stack_00000000 = (in_stack_00000000 & 0xf0) + 0x10;
    }
    if ((in_stack_00000000 & 0xff) != 0)
    {
      uVar2 = 1;
      uVar6 = 0;
      do
      {
        aes_encrypt(in_r1, &local_38, local_48);
        pbVar1 = local_48;
        uVar3 = uVar6;
        do
        {
          if ((int)uVar5 <= (int)uVar3)
            break;
          *(byte *)(in_r3 + uVar3) = *(byte *)(in_r3 + uVar3) ^ *pbVar1;
          uVar3 = uVar3 + 1;
          pbVar1 = pbVar1 + 1;
        } while (&local_38 != pbVar1);
        iVar4 = (uVar2 + 1) * 0x10000;
        uVar2 = uVar2 + 1 & 0xffff;
        uStack_2a = (undefined)((uint)iVar4 >> 0x18);
        uStack_29 = (undefined)((uint)iVar4 >> 0x10);
        uVar6 = uVar6 + 0x10 & 0xffff;
      } while (uVar6 < (in_stack_00000000 & 0xff));
    }
  }
  return 0;
}
u8 aes_ccmDecAuthTran(u8 micLen, u8 *key, u8 *iv, u8 *mStr, u16 mStrLen, u8 *aStr, u8 aStrLen, u8 *mic)

{
  u8 *puVar1;
  int iVar2;
  u8 uVar3;
  byte bVar4;
  u8 uVar5;
  int iVar6;
  u8 local_20;
  u8 auStack_1f[19];

  uVar3 = aes_ccmAuthTran(micLen, key, iv, mStr, mStrLen, aStr, aStrLen, &local_20);
  uVar5 = 0xff;
  if (((uVar3 == '\0') && (uVar5 = '\0', micLen != '\0')) && (uVar5 = 0xff, *mic == local_20))
  {
    iVar6 = 0;
    bVar4 = 0;
    do
    {
      bVar4 = bVar4 + 1;
      if (micLen <= bVar4)
      {
        return '\0';
      }
      iVar2 = iVar6 + 1;
      puVar1 = auStack_1f + iVar6;
      iVar6 = iVar6 + 1;
    } while (mic[iVar2] == *puVar1);
    uVar5 = 0xff;
  }
  return uVar5;
}
u8 aes_ccmDecTran(u8 micLen, u8 *key, u8 *iv, u8 *mStr, u16 mStrLen, u8 *aStr, u8 aStrLen, u8 *mic)

{
  u8 uVar1;

  uVar1 = aes_ccmBaseTran();
  return uVar1;
}
u8 aes_ccmEncTran(u8 M, u8 *key, u8 *iv, u8 *mStr, u16 mStrLen, u8 *aStr, u8 aStrLen, u8 *result)

{
  u8 uVar1;

  uVar1 = aes_ccmBaseTran();
  return uVar1;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
u8 ss_ccmDecryption(void)

{
  u8 uVar1;
  u8 *in_r0;
  u8 *in_r1;
  u8 in_r2;
  u8 *in_r3;
  int iVar2;
  uint in_stack_00000000;
  u8 *in_stack_00000004;
  ushort mStrLen;

  iVar2 = (in_stack_00000000 & 0xff) - 4;
  mStrLen = (ushort)iVar2 & 0xff;
  aes_ccmDecTran('\x04', in_r0, in_r1, in_stack_00000004, mStrLen, in_r3, in_r2, in_stack_00000004 + iVar2);
  uVar1 = aes_ccmDecAuthTran('\x04', in_r0, in_r1, in_stack_00000004, mStrLen, in_r3, in_r2,
                             in_stack_00000004 + iVar2);
  return uVar1;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
uint ss_ccmEncryption(void)

{
  u8 uVar1;
  u8 *in_r0;
  u8 *in_r1;
  u8 in_r2;
  u8 *in_r3;
  uint uVar2;
  uint uVar3;
  uint in_stack_00000000;
  u8 *in_stack_00000004;
  u8 auStack_24[4];

  uVar3 = in_stack_00000000 & 0xff;
  uVar1 = aes_ccmAuthTran('\x04', in_r0, in_r1, in_stack_00000004, (u16)uVar3, in_r3, in_r2, auStack_24);
  uVar2 = 0;
  if (uVar1 == '\0')
  {
    aes_ccmEncTran('\x04', in_r0, in_r1, in_stack_00000004, (u16)uVar3, in_r3, in_r2, auStack_24);
    memcpy(in_stack_00000004 + uVar3, auStack_24, 4);
    uVar2 = uVar3 + 4 & 0xff;
  }
  return uVar2;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
undefined4 ss_keyHash(void)

{
  ss_ttlMAC();
  return 0;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void ss_ttlMAC(void)

{
  uint in_r0;
  u8 *pBuf;
  int in_r1;
  int in_r2;
  int iVar1;
  uint uVar2;
  byte local_3c[16];
  undefined auStack_2c[16];

  uVar2 = in_r0 & 0xff;
  if (uVar2 < 0x71)
  {
    pBuf = ev_buf_allocate(0x80);
    if (pBuf == (u8 *)0x0)
    {
      sys_exceptionPost(0x9e, '\x02');
    }
    else
    {
      iVar1 = 0;
      do
      {
        local_3c[iVar1] = *(byte *)(in_r2 + iVar1) ^ 0x5c;
        iVar1 = iVar1 + 1;
      } while (iVar1 != 0x10);
      iVar1 = 0;
      do
      {
        pBuf[iVar1] = *(byte *)(in_r2 + iVar1) ^ 0x36;
        iVar1 = iVar1 + 1;
      } while (iVar1 != 0x10);
      if (uVar2 != 0)
      {
        iVar1 = 0;
        do
        {
          pBuf[iVar1 + 0x10] = *(u8 *)(in_r1 + iVar1);
          iVar1 = iVar1 + 1;
        } while (iVar1 < (int)uVar2);
      }
      (*(code *)&tl_cryHashFunction)(pBuf, uVar2 + 0x10 & 0xff, auStack_2c);
      (*(code *)&tl_cryHashFunction)(local_3c, 0x20);
      ev_buf_free(pBuf);
    }
  }
  else
  {
    sys_exceptionPost(0x8c, '\x04');
  }
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
undefined4 tl_cryHashFunction(void)

{
  int iVar1;
  uint extraout_r1;
  uchar *Key;
  code *in_r3;
  uint uVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  byte abStack_28[16];

  iVar1 = (*in_r3)();
  uVar5 = extraout_r1 & 0xff;
  memset(Key, 0, 0x10);
  uVar2 = 0;
  uVar4 = 0;
  while (uVar4 < uVar5)
  {
    while (true)
    {
      abStack_28[uVar2] = *(byte *)(iVar1 + uVar4);
      uVar2 = uVar2 + 1;
      uVar4 = uVar4 + 1;
      if (uVar2 < 0x10)
        break;
      aes_encrypt(Key, abStack_28, Key);
      iVar3 = 0;
      do
      {
        Key[iVar3] = Key[iVar3] ^ abStack_28[iVar3];
        iVar3 = iVar3 + 1;
      } while (iVar3 != 0x10);
      uVar2 = 0;
      if (uVar5 <= uVar4)
        goto LAB_0001f9a2;
    }
  }
LAB_0001f9a2:
  abStack_28[uVar2] = 0x80;
  while (uVar2 = uVar2 + 1, uVar2 != 0xe)
  {
    if (0xf < uVar2)
    {
      aes_encrypt(Key, abStack_28, Key);
      iVar1 = 0;
      do
      {
        Key[iVar1] = Key[iVar1] ^ abStack_28[iVar1];
        iVar1 = iVar1 + 1;
      } while (iVar1 != 0x10);
      abStack_28[0] = 0;
      uVar2 = 1;
    }
    abStack_28[uVar2] = 0;
  }
  abStack_28[14] = (byte)((uVar5 << 3) >> 8);
  abStack_28[15] = (byte)(uVar5 << 3);
  aes_encrypt(Key, abStack_28, Key);
  iVar1 = 0;
  do
  {
    Key[iVar1] = Key[iVar1] ^ abStack_28[iVar1];
    iVar1 = iVar1 + 1;
  } while (iVar1 != 0x10);
  return 0;
}
