#include <string.h>
#include <stdlib.h>
#include <setjmp.h>

#include "wifi_hal.h"
#include "wifi_hal_sta.h"


INT wifi_connect(INT apIndex, wifi_bss_info_t* bss)
{
  /*TODO: Implement Me!*/
  (void)apIndex;
  (void)bss;
  return (INT)0;
}

INT wifi_disconnect(INT apIndex)
{
  /*TODO: Implement Me!*/
  (void)apIndex;
  return (INT)0;
}

void wifi_staConnectionStatus_callback_register(wifi_staConnectionStatus_callback callback_proc)
{
  /*TODO: Implement Me!*/
  (void)callback_proc;
}

