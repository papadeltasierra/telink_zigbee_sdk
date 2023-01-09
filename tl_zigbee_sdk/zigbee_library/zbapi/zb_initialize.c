void os_init(u8 isRetention)

{
  os_reset(isRetention);
  return;
}
void os_reset(u8 isRetention)

{
  if (isRetention == '\0')
  {
    ev_buf_init();
    ev_timer_init();
    zb_sched_init();
    tl_zbBufferInit();
  }
  secondClockRun();
  return;
}
u8 zb_info_load(void)

{
  nv_sts_t nVar1;

  nVar1 = nv_flashReadNew('\x01', '\0', '\x01', 0xc0, (u8 *)&g_zbInfo);
  return nVar1;
}
void zb_info_save(void *arg)

{
  nv_flashWriteNew('\x01', 0, '\x01', 0xc0, (u8 *)&g_zbInfo);
  return;
}
void zb_init(void)

{
  u8 uVar1;

  uVar1 = nv_facrotyNewRstFlagCheck();
  if (uVar1 != '\0')
  {
    nv_resetToFactoryNew();
  }
  uVar1 = zb_info_load();
  if (uVar1 == '\0')
  {
    tl_zbMacInit('\0');
    tl_zbNwkInit('\0');
    aps_init();
  }
  else
  {
    tl_zbMacInit('\x01');
    tl_zbNwkInit('\x01');
    aps_init();
    zb_nwkKeySet();
    ss_zdoUseKey(0);
    tl_bdbAttrInit();
  }
  af_init();
  zdo_init();
  return;
}
void zb_nwkKeySet(void)

{
  u32 uVar1;
  undefined4 *puVar2;
  u8 *puVar3;
  undefined4 *puVar4;
  undefined4 local_20;
  undefined4 uStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  undefined2 auStack_10[2];

  puVar4 = &local_20;
  local_20 = 0;
  uStack_1c = 0;
  uStack_18 = 0;
  uStack_14 = 0;
  puVar3 = "";
  do
  {
    puVar2 = (undefined4 *)"";
    if (*puVar3 != '\0')
      goto LAB_00011c00;
    puVar3 = puVar3 + 1;
  } while (puVar3 != linkKeyDistributedCertification);
  do
  {
    uVar1 = drv_u32Rand();
    *(short *)puVar4 = (short)uVar1;
    puVar4 = (undefined4 *)((int)puVar4 + 2);
    puVar2 = &local_20;
  } while (puVar4 != (undefined4 *)auStack_10);
LAB_00011c00:
  (*(code *)&ss_zdoNwkKeyConfigure)(puVar2, 0, 1);
  return;
}
void zb_reset(void)

{
  tl_zbMacReset();
  tl_zbNwkInit('\x01');
  aps_init();
  zb_nwkKeySet();
  ss_zdoUseKey(0);
  tl_bdbAttrInit();
  return;
}
