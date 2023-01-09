void secondClockInit(void)

{
  secondTimer._4_4_ = secondClockPeriodic;
  ev_on_timer((ev_timer_event_t *)secondTimer, 1000);
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
undefined4 secondClockPeriodic(void)

{
  uint uVar1;

  if (g_secondCnt != -1)
  {
    g_secondCnt = g_secondCnt + 1;
  }
  uVar1 = 0;
  do
  {
    secondClockStop();
    uVar1 = uVar1 + 1 & 0xff;
  } while (*(int *)(timeoutsCb + uVar1 * 4) != 0);
  return 0;
}
void secondClockRun(void)

{
  u8 uVar1;

  uVar1 = ev_timer_exist((ev_timer_event_t *)secondTimer);
  if (uVar1 == '\0')
  {
    secondClockInit();
  }
  return;
}
// WARNING: Unknown calling convention -- yet parameter storage is locked
void secondClockStop(void)

{
  code *in_r3;

  (*in_r3)();
  secondTimer._4_4_ = secondClockPeriodic;
  ev_on_timer((ev_timer_event_t *)secondTimer, 1000);
  return;
}
