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

#include "wifi_hal.h"
#include "api_translator.h"

/*Work around to test generic hal apis
Enable below block while building for Linux target. This provides dummy definition for generic hal apis*/
#if BUILD_LINUX
INT wifi_hal_init(){return 0;}
INT wifi_hal_getHalCapability(wifi_hal_capability_t *hal)
{
    /* To ensure that number of radios not returned as a junk value */
    if(hal != NULL)
        hal->wifi_prop.numRadios = 0;
    return 0;
}
INT wifi_hal_connect(INT ap_index, wifi_bss_info_t *bss){return 0;}
INT wifi_hal_setRadioOperatingParameters(wifi_radio_index_t index, wifi_radio_operationParam_t *operationParam){return 0;}
INT wifi_hal_createVAP(wifi_radio_index_t index, wifi_vap_info_map_t *map){return 0;}
INT wifi_hal_getRadioVapInfoMap(wifi_radio_index_t index, wifi_vap_info_map_t *map){return 0;}
INT wifi_hal_startScan(wifi_radio_index_t index, wifi_neighborScanMode_t scan_mode, INT dwell_time, UINT num, UINT *chan_list){return 0;}
INT wifi_hal_disconnect(INT apIndex){return 0;}
#endif
