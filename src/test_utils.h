/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2023 RDK Management
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

#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include <stdint.h>

// In order to get INT, BOOL Types
#include <wifi_hal_generic.h>
#include <wifi_hal_radio.h>
#include <wifi_hal_ap.h>
#define TEST_WIFI_HAL_VALID_SSID ("test@1234")

/* #TODO -> Doxygen comments required */

/* Local Functions */

/*
extern INT test_utils_setApEnable (BOOL enable, INT ap_index);
extern INT test_utils_channelPush(INT radioIndex, ULONG channel);
extern INT test_utils_setBandwidth(INT radioIndex, UINT bandwidth);
*/

/* This will test SSID set functionality *
* positive case * maps to WIFI_HAL_SUCCESS *
* set main interface SSIDs to "test@1234" and check if the value is set with corresponding get
* virtual/guest SSID set check is not added yet
*
* Negative case * maps to WIFI_HAL_ERROR, WIFI_HAL_INTERNAL_ERROR, WIFI_HAL_UNSUPPORTED, WIFI_HAL_INVALID_ARGUMENTS, WIFI_HAL_INVALID_VALUE *
* Try to set SSID to NULL Value *
* Try to set SSID with wrong AP indexes * Here 25,26,27 are taken as wrong indices */

/* SSID SET UTILITY FUNCTIONS */
extern INT test_utils_setValidSSID(INT radioIndex, INT ap_index, INT ap_pointing_index);
extern INT test_utils_setInValidIndexSSID(INT radioIndex, INT ap_index, INT ap_pointing_index);
extern INT test_utils_setNULLSSID(INT radioIndex, INT ap_index,INT ap_pointing_index);

/* GET NUMBER OF RADIOS */
extern INT test_utils_getMaxNumberOfRadio(UINT *maxRadio);

/* GET ACCESS POINT INDICES */
typedef enum {
    PRIVATE,
    STA,
    IOT,
    BACKHAUL,
    LNF_PSK,
    LNF_RADIUS,
    HOTSPOT_OPEN,
    HOTSPOT_SECURE
} APTYPE;

extern INT test_utils_getApIndices(UINT maxRadio, INT apIndices[], APTYPE type);
extern INT l2_test_prerequisite();
extern INT get_channel_list(int radioIndex, int *count, int channels[25]);
extern INT get_channel_bandwidth(int radioIndex, int *count, wifi_channelBandwidth_t Width[5]);
/* UTILITY FUNCTIONS END */

#endif /* TEST_UTILS_H */
