/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2016 RDK Management
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
*/
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

