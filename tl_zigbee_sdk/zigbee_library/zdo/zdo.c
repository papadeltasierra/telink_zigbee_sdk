u8 zdo_af_get_accept_nwk_update_channel(void)

{
  return zdo_cfg_attributes.config_accept_nwk_update_channel;
}
u16 zdo_af_get_accept_nwk_update_pan_id(void)

{
  return zdo_cfg_attributes.config_accept_nwk_update_pan_id;
}
bool zdo_af_get_mgmtLeave_use_aps_sec(void)

{
  return (bool)zdo_cfg_attributes.config_mgmt_leave_use_aps_sec;
}
u16 zdo_af_get_nwk_time_btwn_scans(void)

{
  return zdo_cfg_attributes.config_nwk_time_btwn_scans;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
u8 zdo_af_get_scan_attempts(void)

{
  return zdo_cfg_attributes.config_nwk_scan_attempts;
}
u8 zdo_channel_page2num(u32 chp)

{
  u8 uVar1;
  int iVar2;

  iVar2 = 0;
  uVar1 = '\v';
  do
  {
    if ((chp >> iVar2 + 0xb & 1) != 0)
    {
      return uVar1;
    }
    uVar1 = uVar1 + '\x01';
    iVar2 = iVar2 + 1;
  } while (uVar1 != '\x1b');
  return '\x1b';
}
void zdo_init(void)

{
  zdp_init();
  memcpy(&zdo_cfg_attributes, &zdoCfgAttrDefault, 0x18);
  return;
}
void zdo_zdpCbTblRegister(zdo_appIndCb_t *cbTbl)

{
  zdoAppIndCbLst = cbTbl;
  return;
}
