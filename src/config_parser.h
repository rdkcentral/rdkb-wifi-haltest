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

#include <stdlib.h>
#include <wifi_hal.h>

/**function to read the radio configuration from json config file
*IN : radio index
*IN : radio_info - the buffer to hold radio config
*OUT : returns success or failure status of the operation
**/
int get_radio_config(int index, wifi_radio_operationParam_t *radio_info);

/**function to read the private VAP configuration from json config file
*IN : index - VAP index
*IN : vap_info - the buffer to hold private VAP config
*OUT : returns success or failure status of the operation
**/
int get_private_vap_config(int index, wifi_vap_info_t *vap_info);

/**function to read the mesh_sta VAP configuration from json config file
*IN : index - VAP index
*IN : vap_info - the buffer to hold mesh_sta VAP config
*OUT : returns success or failure status of the operation
**/
int get_mesh_sta_vap_config(int index, wifi_vap_info_t *vap_info);
