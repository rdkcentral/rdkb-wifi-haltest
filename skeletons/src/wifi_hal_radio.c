#include <string.h>
#include <stdlib.h>
#include <setjmp.h>

#include "wifi_hal.h"
#include "wifi_hal_radio.h"


INT wifi_getRadioTransmitPower(INT radioIndex, ULONG* output_ulong)
{
  /*TODO: Implement Me!*/
  (void)radioIndex;
  (void)output_ulong;
  return (INT)0;
}

INT wifi_getRadioOperatingChannelBandwidth(INT radioIndex, CHAR* output_string)
{
  /*TODO: Implement Me!*/
  (void)radioIndex;
  (void)output_string;
  return (INT)0;
}

INT wifi_setRadioOperatingParameters(wifi_radio_index_t index, wifi_radio_operationParam_t* operationParam)
{
  /*TODO: Implement Me!*/
  (void)index;
  (void)operationParam;
  return (INT)0;
}

void wifi_scanResults_callback_register(wifi_scanResults_callback callback_proc)
{
  /*TODO: Implement Me!*/
  (void)callback_proc;
}

