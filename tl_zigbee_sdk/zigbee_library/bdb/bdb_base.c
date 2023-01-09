void bdb_coordinatorStart(void)

{
  aps_ib.aps_designated_coordinator = '\x01';
  ss_ib.tcPolicy.allowTCLKrequest = '\x01';
  zb_routerStart();
  return;
}
void bdb_factoryNewDevCfg(u8 touchLinkEn, u8 chan)

{
  aps_ib.aps_use_ext_panid[0] = '\0';
  aps_ib.aps_use_ext_panid[1] = '\0';
  aps_ib.aps_use_ext_panid[2] = '\0';
  aps_ib.aps_use_ext_panid[3] = '\0';
  aps_ib.aps_use_ext_panid[4] = '\0';
  aps_ib.aps_use_ext_panid[5] = '\0';
  aps_ib.aps_use_ext_panid[6] = '\0';
  aps_ib.aps_use_ext_panid[7] = '\0';
  aps_ib.aps_designated_coordinator = '\x01';
  ss_ib.tcPolicy.allowTCLKrequest = '\x01';
  g_zbInfo.nwkNib.panId = g_zbInfo.macPib.panId;
  if (touchLinkEn != '\0')
  {
    tl_zbMacChannelSet(chan);
    rf_setTrxState('\x01');
  }
  g_zbInfo.nwkNib.panId._1_1_ = (undefined)(g_zbInfo.nwkNib.panId >> 8);
  return;
}
void bdb_linkKeyCfg(bdb_commissionSetting_t *setting, u8 isFactoryNew)

{
  u8 *puVar1;

  if (isFactoryNew == '\0')
  {
    if (-1 < (int)((uint)ss_ib.preConfiguredKeyType << 0x1e))
    {
      ss_ib.tcLinkKeyType = '\x01';
      puVar1 = tcLinkKeyCentralDefault;
      goto LAB_00028660;
    }
  }
  else
  {
    isFactoryNew = (setting->linkKey).tcLinkKey.keyType;
  }
  puVar1 = (setting->linkKey).tcLinkKey.key;
  ss_ib.tcLinkKeyType = isFactoryNew;
LAB_00028660:
  ss_ib.tcLinkKey._0_1_ = (char)puVar1;
  ss_ib.tcLinkKey._1_1_ = (char)((uint)puVar1 >> 8);
  ss_ib.tcLinkKey._2_1_ = (char)((uint)puVar1 >> 0x10);
  ss_ib.tcLinkKey._3_1_ = (char)((uint)puVar1 >> 0x18);
  puVar1 = (setting->linkKey).distributeLinkKey.key;
  ss_ib.distibuteLinkKey._0_1_ = (char)puVar1;
  ss_ib.distibuteLinkKey._1_1_ = (char)((uint)puVar1 >> 8);
  ss_ib.distibuteLinkKey._2_1_ = (char)((uint)puVar1 >> 0x10);
  ss_ib.distibuteLinkKey._3_1_ = (char)((uint)puVar1 >> 0x18);
  return;
}
void bdb_outgoingFrameCountUpdate(u8 repower)

{
  if (repower == '\0')
  {
    ss_ib.outgoingFrameCounter = drv_pm_deepSleep_frameCnt_get();
  }
  else
  {
    ss_ib.outgoingFrameCounter = ss_ib.outgoingFrameCounter + 0x400;
    nv_nwkFrameCountSaveToFlash(ss_ib.outgoingFrameCounter);
  }
  return;
}
void bdb_scanCfg(u32 chanMask, u8 duration)

{
  aps_ib.aps_channel_mask._0_1_ = (char)chanMask;
  aps_ib.aps_channel_mask._1_1_ = (char)(chanMask >> 8);
  aps_ib.aps_channel_mask._2_1_ = (char)(chanMask >> 0x10);
  aps_ib.aps_channel_mask._3_1_ = (char)(chanMask >> 0x18);
  zdo_cfg_attributes.config_nwk_scan_duration = duration;
  return;
}
