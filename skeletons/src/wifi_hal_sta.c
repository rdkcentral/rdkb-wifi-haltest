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

