int buf_type_get(void *param_1)

{
  bool bVar1;
  u8 uVar2;
  int iVar3;

  bVar1 = is_zb_buf(param_1);
  iVar3 = 0;
  if (bVar1 == false)
  {
    uVar2 = is_ev_buf(param_1);
    iVar3 = 2 - (uint)(uVar2 != '\0');
  }
  return iVar3;
}
u8 tl_zbPrimitivePost(u8 layerQ, u8 primitive, void *arg)

{
  u8 uVar1;
  tl_zb_task_t local_1c;

  T_exceptTaskPost._0_1_ = layerQ;
  T_exceptTaskPost._1_1_ = primitive;
  if (arg == (void *)0x0)
  {
    sys_exceptionPost(0xd8, '\x10');
  }
  *(u8 *)((int)arg + 0xc0) = primitive;
  local_1c.tlCb = (tl_zb_callback_t)0x0;
  local_1c.data = arg;
  uVar1 = tl_zbTaskQPush(layerQ, &local_1c);
  if (uVar1 != '\0')
  {
    if ((layerQ == '\x01') && ((primitive == 'L' || (primitive == 'B'))))
    {
      zb_buf_free((zb_buf_t *)arg);
    }
    else
    {
      sys_exceptionPost(0xe6, '\x15');
    }
  }
  return uVar1;
}
u8 tl_zbTaskPost(tl_zb_callback_t func, void *arg)

{
  u8 uVar1;
  int iVar2;
  tl_zb_task_t local_14;

  local_14.tlCb = func;
  local_14.data = arg;
  uVar1 = tl_zbTaskQPush('\0', &local_14);
  if (uVar1 != '\0')
  {
    iVar2 = buf_type_get(arg);
    if (iVar2 == 0)
    {
      sys_exceptionPost(0xc1, '\x15');
      zb_buf_free((zb_buf_t *)arg);
    }
    else if (iVar2 == 1)
    {
      sys_exceptionPost(0xc5, 's');
      ev_buf_free((u8 *)arg);
    }
    else
    {
      sys_exceptionPost(0xc9, '\x05');
    }
  }
  return uVar1;
}
void tl_zbTaskProcedure(void)

{
  tl_zb_task_t *ptVar1;
  tl_zb_task_t local_10;

  tl_zbMacTaskProc();
  tl_zbNwkTaskProc();
  ptVar1 = tl_zbTaskQPop('\0', &local_10);
  if (ptVar1 != (tl_zb_task_t *)0x0)
  {
    FUN_00011e70(local_10.data);
  }
  zdo_ssInfoUpdate();
  return;
}
u8 tl_zbTaskQPush(tl_zb_taskList_e idx, tl_zb_task_t *task)

{
  byte bVar1;
  tl_zb_callback_t pvVar2;
  void *pvVar3;
  u32 en;
  int iVar4;
  tl_zb_task_t *ptVar5;

  en = drv_disable_irq();
  if (idx == 0)
  {
    if (0x1f < (int)((uint)taskQ_user.wptr - (uint)taskQ_user.rptr))
    {
    LAB_00000fe6:
      drv_restore_irq(en);
      return '\x01';
    }
    ptVar5 = taskQ_user.evt + (taskQ_user.wptr & 0x1f);
    taskQ_user.wptr = taskQ_user.wptr + '\x01';
  }
  else
  {
    iVar4 = (idx - 1) * 0x84;
    bVar1 = g_zbTaskQ[iVar4 + 0x80];
    if (0xf < (int)((uint)bVar1 - (uint)(byte)g_zbTaskQ[iVar4 + 0x81]))
      goto LAB_00000fe6;
    ptVar5 = (tl_zb_task_t *)(g_zbTaskQ + (bVar1 & 0xf) * 8 + iVar4);
    g_zbTaskQ[iVar4 + 0x80] = bVar1 + 1;
  }
  /*
  pvVar2 = task->tlCb;
  *(char *)&ptVar5->tlCb = (char)pvVar2;
  *(char *)((int)&ptVar5->tlCb + 1) = (char)((uint)pvVar2 >> 8);
  *(char *)((int)&ptVar5->tlCb + 2) = (char)((uint)pvVar2 >> 0x10);
  *(char *)((int)&ptVar5->tlCb + 3) = (char)((uint)pvVar2 >> 0x18);
  pvVar3 = task->data;
  *(char *)&ptVar5->data = (char)pvVar3;
  *(char *)((int)&ptVar5->data + 1) = (char)((uint)pvVar3 >> 8);
  *(char *)((int)&ptVar5->data + 2) = (char)((uint)pvVar3 >> 0x10);
  *(char *)((int)&ptVar5->data + 3) = (char)((uint)pvVar3 >> 0x18);
  */
  // Copy the task onto the queue.
  ptVar5->tlCb = pvVar2->tlCb;
  ptVar5->data = pvVar2->data;

  iVar4 = buf_type_get(task->data);
  if ((iVar4 == 0) && (-1 < (int)((uint) * (byte *)((int)task->data + 0xc3) << 0x1f)))
  {
    T_DBG_taskQPush_cb = task->tlCb;
    T_DBG_taskQPush_idx = idx;
    T_DBG_taskQPush_data = task->data;
    sys_exceptionPost(0x80, '\x13');
  }
  drv_restore_irq(en);
  return '\0';
}

u8 tl_zbUserTaskQNum(void)

{
  return taskQ_user[256] - taskQ_user[257];
}
void zb_sched_init(void)

{
  memset(taskQ_user, 0, 0x102);
  memset(g_zbTaskQ, 0, 0x294);
  return;
}
