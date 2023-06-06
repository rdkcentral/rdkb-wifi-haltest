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
#include "wifi_hal_telemetry.h"

INT wifi_getRadioBandUtilization(INT radioIndex, INT* output_percentage)
{
  /*TODO: Implement Me!*/
  (void)radioIndex;
  (void)output_percentage;
  return (INT)0;
}

INT wifi_getApAssociatedDeviceDiagnosticResult3(INT apIndex, wifi_associated_dev3_t** associated_dev_array, UINT* output_array_size)
{
  /*TODO: Implement Me!*/
  (void)apIndex;
  (void)associated_dev_array;
  (void)output_array_size;
  return (INT)0;
}

INT wifi_getApAssociatedClientDiagnosticResult(INT apIndex, mac_address_t mac_addr, wifi_associated_dev3_t* dev_conn)
{
  /*TODO: Implement Me!*/
  (void)apIndex;
  (void)mac_addr;
  (void)dev_conn;
  return (INT)0;
}

INT wifi_getRadioTrafficStats2(INT radioIndex, wifi_radioTrafficStats2_t* output_struct)
{
  /*TODO: Implement Me!*/
  (void)radioIndex;
  (void)output_struct;
  return (INT)0;
}

