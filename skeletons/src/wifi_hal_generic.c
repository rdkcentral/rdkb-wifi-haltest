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
#include "wifi_hal_generic.h"


INT wifi_init(void)
{
  /*TODO: Implement Me!*/
  return (INT)0;
}

INT wifi_getHalCapability(wifi_hal_capability_t* cap)
{
    /* To ensure that number of radios not returned as a junk value */
    if(cap != NULL)
        cap->wifi_prop.numRadios = 0;

    return (INT)0;
}
