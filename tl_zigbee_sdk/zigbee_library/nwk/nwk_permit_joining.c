// WARNING: Unknown calling convention -- yet parameter storage is locked
undefined4 nwk_permitJoinTimeout(void)

{
  g_zbInfo.macPib.associationPermit = 0;

  /*
  union {
    structure {
	    u8  is_factory_new:1;	  !< Device is factory new
	    u8  permit_join:1; 		  !< True if permit join is in progress
	    u8  joined:1;      		  !< Non-zero if we are joined into the network
	    u8  router_started:1; 	!< not used
	    u8  is_tc:1;            !< True if we are Trust Center
    	u8  joined_pro:1;
	    u8	panIdConflict:1;	  !< if we find panID conflict
	    u8	joinAccept:1;
    },
    u8 _45_1_;
  }
  */
  // 0xfd == 0b11111101
  // g_zbNwkCtx._45_1_ = g_zbNwkCtx._45_1_ & 0xfd;
  g_zbNwkCtx.permit_join = 0;
  permitJoinTimerEvt = 0;
  return 0xfffffffe;
}


// QUESTION: Is arg actually a task buffer with the value in the first data byte?
void tl_zbNwkNlmePermitJoiningRequestHandler(void *arg)
{
  /*
   * This explains the g_zbNwkCtx change.
   * union {
   *   structure {
 	 *     u8  is_factory_new:1;	!< Device is factory new
	 *     u8  permit_join:1; 		!< True if permit join is in progress
	 *     u8  joined:1;      		!< Non-zero if we are joined into the network
	 *     u8  router_started:1; 	!< not used
	 *     u8  is_tc:1;           !< True if we are Trust Center
	 *     u8  joined_pro:1;
	 *     u8	panIdConflict:1;    !< if we find panID conflict
	 *     u8	joinAccept:1;
   *   },
   *   u8 _45_1;
   */
  // if (((int)((uint)(byte)g_zbInfo.nwkNib.capabilityInfo << 0x1e) < 0) &&
  if ((g_zbInfo.nwkNib.capabilityInfo.allocAddr) &&
       g_zbNwkCtx.joinAccept &&
       g_zbNwkCtx.routerS_started)
  // ((g_zbNwkCtx._45_1_ & 0x84) == 0x84))
  {
    if (permitJoinTimerEvt != (ev_timer_event_t *)0x0)
    {
      // Cancel the PermitJoin event timer.
      ev_timer_taskCancel(&permitJoinTimerEvt);
    }
    // WARNING: Load size is inaccurate
    // g_zbNwkCtx._45_1_ = g_zbNwkCtx._45_1_ & 0xfd | ('\x01' - (*arg == '\0')) * '\x02';
    // Join permitted if the argment is non-zero.
    g_zbNwkCtx.permit_join = (*arg);

    // WARNING: Load size is inaccurate
    // Permission period.
    g_zbInfo.macPib.associationPermit = (u8)(*arg);
    if (g_zbInfo.macPib.associationPermit != 0x00)
    {
      if (g_zbInfo.macPib.associationPermit == 0xff)
      {
        // 0xff means "allow forever"
        g_zbInfo.macPib.associationPermit = 1;
      }
      else
      {
        // 0x01-0xfe means "allow for this number of seconds."
        g_zbInfo.macPib.associationPermit = 1;
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
    // QUESTION: What is special about 0xc2?
    *(undefined *)arg = 0xc2;
    tl_zbTaskPost(zdo_nlmePermitJoinCnf, arg);
  }
  return;
}
