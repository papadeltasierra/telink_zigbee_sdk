// WARNING: Unknown calling convention -- yet parameter storage is locked
undefined4 nwk_permitJoinTimeout(void)

{
  g_zbInfo.macPib.associationPermit = '\0';
  g_zbNwkCtx._45_1_ = g_zbNwkCtx._45_1_ & 0xfd;
  permitJoinTimerEvt = 0;
  return 0xfffffffe;
}
void tl_zbNwkNlmePermitJoiningRequestHandler(void *arg)

{
  if (((int)((uint)(byte)g_zbInfo.nwkNib.capabilityInfo << 0x1e) < 0) &&
      ((g_zbNwkCtx._45_1_ & 0x84) == 0x84))
  {
    if (permitJoinTimerEvt != (ev_timer_event_t *)0x0)
    {
      ev_timer_taskCancel(&permitJoinTimerEvt);
    }
    // WARNING: Load size is inaccurate
    g_zbNwkCtx._45_1_ = g_zbNwkCtx._45_1_ & 0xfd | ('\x01' - (*arg == '\0')) * '\x02';
    // WARNING: Load size is inaccurate
    g_zbInfo.macPib.associationPermit = *arg;
    if (g_zbInfo.macPib.associationPermit != '\0')
    {
      if (g_zbInfo.macPib.associationPermit == 0xff)
      {
        g_zbInfo.macPib.associationPermit = '\x01';
      }
      else
      {
        g_zbInfo.macPib.associationPermit = '\x01';
        // WARNING: Load size is inaccurate
        permitJoinTimerEvt = ev_timer_taskPost(nwk_permitJoinTimeout, (void *)0x0, (uint)*arg * 1000);
      }
    }
    tl_zbNwkBeaconPayloadUpdate();
    *(undefined *)arg = 0;
    tl_zbTaskPost(zdo_nlmePermitJoinCnf, arg);
  }
  else
  {
    *(undefined *)arg = 0xc2;
    tl_zbTaskPost(zdo_nlmePermitJoinCnf, arg);
  }
  return;
}
