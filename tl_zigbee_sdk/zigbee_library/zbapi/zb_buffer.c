bool is_zb_buf(void *p)

{
  byte bVar1;

  bVar1 = 0;
  if ((void *)((int)&g_mPool.usedNum + 3) < p)
  {
    bVar1 = ~-(p < &g_mPool.pool[ZB_BUF_POOL_SIZE - 1].hdr);
  }
  return (bool)bVar1;
}

void tl_zbBufferInit(void)

{
  u32 len;
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;

  len = zbBufferSizeGet();
  memset(&g_mPool, 0, len);
  iVar3 = 0x844130;
  g_mPool.head._0_1_ = 0x30;
  g_mPool.head._1_1_ = 0x41;
  g_mPool.head._2_1_ = 0x84;
  g_mPool.head._3_1_ = 0;
  uVar1 = (uint)ZB_BUF_POOL_SIZE;
  if (1 < uVar1)
  {
    iVar2 = 0;
    iVar4 = iVar3;
    do
    {
      iVar3 = iVar4 + 0xd0;
      *(char *)(iVar4 + 0xc4) = (char)iVar3;
      *(char *)(iVar4 + 0xc5) = (char)((uint)iVar3 >> 8);
      *(char *)(iVar4 + 0xc6) = (char)((uint)iVar3 >> 0x10);
      *(char *)(iVar4 + 199) = (char)((uint)iVar3 >> 0x18);
      iVar2 = iVar2 + 1;
      iVar4 = iVar3;
    } while (iVar2 < (int)(uVar1 - 1));
  }
  *(undefined *)(iVar3 + 0xc4) = 0;
  *(undefined *)(iVar3 + 0xc5) = 0;
  *(undefined *)(iVar3 + 0xc6) = 0;
  *(undefined *)(iVar3 + 199) = 0;
  return;
}
void zb_buf_clear(zb_buf_t *p)

{
  byte bVar1;
  u32 en;

  bVar1 = (p->hdr).field_0x3;
  en = drv_disable_irq();
  (p->hdr).id = '\0';
  (p->hdr).handle = '\0';
  (p->hdr).rssi = '\0';
  (p->hdr).field_0x3 = 0;
  (p->hdr).field_0x3 = bVar1 & 1 | (p->hdr).field_0x3 & 0xfe;
  drv_restore_irq(en);
  return;
}

u8 zb_buf_free(zb_buf_t *buf)

{
  u32 en;
  uint uVar1;
  uint uVar2;

  en = drv_disable_irq();
  if (buf == (zb_buf_t *)g_zbMacCtx.txRawDataBuf)
  {
    if (buf == (zb_buf_t *)0x0)
    {
      sys_exceptionPost(0xa6, '\x11');
    }
    goto LAB_00011a76;
  }
  if ((buf < g_mPool.pool) || (&g_mPool.pool[ZB_BUF_POOL_SIZE - 1].hdr <= buf))
  {
    sys_exceptionPost(0xb2, '\x11');
  }
  uVar2 = buf->freeCnt + 1;
  *(char *)&buf->freeCnt = (char)uVar2;
  *(char *)((int)&buf->freeCnt + 1) = (char)(uVar2 >> 8);
  *(char *)((int)&buf->freeCnt + 2) = (char)(uVar2 >> 0x10);
  *(char *)((int)&buf->freeCnt + 3) = (char)(uVar2 >> 0x18);
  uVar1 = (uint)(byte)(buf->hdr).field_0x3;
  if ((int)(uVar1 << 0x1e) < 0)
  {
    uVar1 = ((uVar1 << 0x1e) >> 0x1f) << 0x18;
    if (buf->allocCnt < uVar2)
    {
      uVar2 = 0x10000;
    }
    else
    {
    LAB_000119a0:
      uVar2 = 0;
    }
  LAB_000119a2:
    T_zbBufFreeDbg = uVar2 | uVar1 | (byte)(buf->hdr).field_0x3 & 1;
    T_zbBufDbg = buf;
    sys_exceptionPost(0xc5, '\x12');
  }
  else
  {
    if (buf->allocCnt < uVar2)
    {
      uVar1 = ((uVar1 << 0x1e) >> 0x1f) << 0x18;
      uVar2 = 0x10000;
      goto LAB_000119a2;
    }
    if (-1 < (int)(uVar1 << 0x1f))
    {
      uVar1 = ((uVar1 << 0x1e) >> 0x1f) << 0x18;
      goto LAB_000119a0;
    }
  }
  if (((g_mPool.head < g_mPool.pool) && (g_mPool.head != (zb_buf_t *)0x0)) ||
      ((zb_buf_t *)((int)&g_mPool + (ZB_BUF_POOL_SIZE - 1) * 0xd0 + 8) < g_mPool.head))
  {
    sys_exceptionPost(0xca, '\x13');
  }
  g_mPool.usedNum = g_mPool.usedNum - 1;
  *(char *)&buf->next = (char)g_mPool.head;
  *(char *)((int)&buf->next + 1) = (char)((uint)g_mPool.head >> 8);
  *(char *)((int)&buf->next + 2) = (char)((uint)g_mPool.head >> 0x10);
  *(char *)((int)&buf->next + 3) = (char)((uint)g_mPool.head >> 0x18);
  g_mPool.head = buf;
  if ((buf < g_mPool.pool) ||
      ((zb_buf_t *)((int)&g_mPool + (ZB_BUF_POOL_SIZE - 1) * 0xd0 + 8) < buf))
  {
    sys_exceptionPost(0xd3, '\x13');
  }
  (buf->hdr).field_0x3 = (buf->hdr).field_0x3 & 0xfe;
  (buf->hdr).handle = 0xff;
LAB_00011a76:
  drv_restore_irq(en);
  return '\0';
}
