u16 tl_zbNwkStochasticAddrCal(void)

{
  u8 uVar1;
  u32 uVar2;
  uint uVar3;
  undefined in_stack_ffffffdc;
  undefined7 in_stack_ffffffdd;

  do
  {
    do
    {
      uVar2 = drv_u32Rand();
      uVar3 = uVar2 & 0xffff;
    } while (0xfff7 < uVar3);
  } while (((g_zbInfo.macPib.shortAddress == uVar3) || (uVar3 == 0)) ||
           (uVar1 = tl_zbExtAddrByShortAddr((u16)uVar3, (addrExt_t)CONCAT71(in_stack_ffffffdd, in_stack_ffffffdc),
                                            (u16 *)&stack0xffffffdc),
            uVar1 == '\0'));
  return (u16)uVar2;
}
