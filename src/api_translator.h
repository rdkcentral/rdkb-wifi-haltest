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

//Generic hal api declaration, to avoid compilation error
INT wifi_hal_init();
INT wifi_hal_getHalCapability(wifi_hal_capability_t *hal);
INT wifi_hal_connect(INT ap_index, wifi_bss_info_t *bss);
INT wifi_hal_setRadioOperatingParameters(wifi_radio_index_t index, wifi_radio_operationParam_t *operationParam);
INT wifi_hal_createVAP(wifi_radio_index_t index, wifi_vap_info_map_t *map);
INT wifi_hal_kickAssociatedDevice(INT ap_index, mac_address_t mac);
INT wifi_hal_startScan(wifi_radio_index_t index, wifi_neighborScanMode_t scan_mode, INT dwell_time, UINT num, UINT *chan_list);
INT wifi_hal_disconnect(INT ap_index);
INT wifi_hal_getRadioVapInfoMap(wifi_radio_index_t index, wifi_vap_info_map_t *map);

/*Work around to test generic hal apis*/
#define wifi_init() wifi_hal_init()

#define wifi_getHalCapability(cap) wifi_hal_getHalCapability(cap)

#define wifi_setRadioOperatingParameters(index, param) wifi_hal_setRadioOperatingParameters(index, param)

#define wifi_createVAP(index, map) wifi_hal_createVAP(index, map)

#define wifi_getRadioVapInfoMap(index, map) wifi_hal_getRadioVapInfoMap(index, map)
