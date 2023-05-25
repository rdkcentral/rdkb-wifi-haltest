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
#include "wifi_hal_ap.h"


INT wifi_getApAssociatedDevice(INT apIndex, mac_address_t* output_deviceMacAddressArray, UINT maxNumDevices, UINT* output_numDevices)
{
  /*TODO: Implement Me!*/
  (void)apIndex;
  (void)output_deviceMacAddressArray;
  (void)maxNumDevices;
  (void)output_numDevices;
  return (INT)0;
}

INT wifi_enableCSIEngine(INT apIndex, mac_address_t sta, BOOL enable)
{
  /*TODO: Implement Me!*/
  (void)apIndex;
  (void)sta;
  (void)enable;
  return (INT)0;
}

INT wifi_createVAP(wifi_radio_index_t index, wifi_vap_info_map_t* map)
{
  /*TODO: Implement Me!*/
  (void)index;
  (void)map;
  return (INT)0;
}

INT wifi_getRadioVapInfoMap(wifi_radio_index_t index, wifi_vap_info_map_t* map)
{
  /*TODO: Implement Me!*/
  (void)index;
  (void)map;
  return (INT)0;
}

INT wifi_mgmt_frame_callbacks_register(wifi_receivedMgmtFrame_callback mgmtRxCallback)
{
  /*TODO: Implement Me!*/
  (void)mgmtRxCallback;
  return (INT)0;
}

void wifi_newApAssociatedDevice_callback_register(wifi_newApAssociatedDevice_callback callback_proc)
{
  /*TODO: Implement Me!*/
  (void)callback_proc;
}

void wifi_apDeAuthEvent_callback_register(wifi_apDeAuthEvent_callback callback_proc)
{
  /*TODO: Implement Me!*/
  (void)callback_proc;
}

void wifi_apDisassociatedDevice_callback_register(wifi_apDisassociatedDevice_callback callback_proc)
{
  /*TODO: Implement Me!*/
  (void)callback_proc;
}
