#include <string.h>
#include <stdlib.h>
#include <setjmp.h>
#include "cmock.h"
#include "Mockwifi_hal.h"


static struct Mockwifi_halInstance
{
  unsigned char placeHolder;
} Mock;

extern jmp_buf AbortFrame;

void Mockwifi_hal_Verify(void)
{
}

void Mockwifi_hal_Init(void)
{
  Mockwifi_hal_Destroy();
}

void Mockwifi_hal_Destroy(void)
{
  CMock_Guts_MemFreeAll();
  memset(&Mock, 0, sizeof(Mock));
}

