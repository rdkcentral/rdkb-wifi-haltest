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


#include <stdio.h>
#include <string.h>

#include <test_utils.h>
#include <wifi_hal.h>

INT test_utils_setValidSSID(INT radioIndex, INT ap_index, INT ap_pointing_index)
{
    char *ssid_Name = "test@1234";
    int result;
    wifi_vap_info_map_t  map;

    result = wifi_getRadioVapInfoMap(radioIndex, &map);
    if (result != WIFI_HAL_SUCCESS)
    {
        return result;
    }

    map.vap_array[ap_pointing_index].vap_index = ap_index;
    snprintf(map.vap_array[ap_pointing_index].u.bss_info.ssid, strlen(ssid_Name)+1,"%s", ssid_Name);

    result = wifi_createVAP(radioIndex,&map);
     
     /* check value using get for functional verification */
    result = wifi_getRadioVapInfoMap(radioIndex, &map);

    if (result != WIFI_HAL_SUCCESS)
    {
        return result;
    }
    if (0 != strcmp(map.vap_array[ap_pointing_index].u.bss_info.ssid, ssid_Name))
    {
        return WIFI_HAL_ERROR;
    }
    return result;
}

INT test_utils_setInValidIndexSSID(INT radioIndex, INT ap_index, INT ap_pointing_index)
{
    char *ssid_Name = TEST_WIFI_HAL_VALID_SSID;
    int result;
    wifi_vap_info_map_t  map;

    /* negative */
    /* try to set SSID for invalid index */
    result = wifi_getRadioVapInfoMap(radioIndex, &map);
    if (result != WIFI_HAL_SUCCESS)
    {
        return result;
    }

    map.vap_array[ap_pointing_index].vap_index = ap_index;
    snprintf(map.vap_array[ap_pointing_index].u.bss_info.ssid, strlen(ssid_Name)+1, "%s", ssid_Name);

    result = wifi_createVAP(radioIndex,&map);
    return result;
}

INT test_utils_setNULLSSID(INT radioIndex, INT ap_index,INT ap_pointing_index)
{

    wifi_vap_info_map_t  map;
    int result;

    /* Negative */

    /* set SSID Name to NULL */
    result = wifi_getRadioVapInfoMap(radioIndex, &map);
    if (result != WIFI_HAL_SUCCESS)
    {
        return result;
    }

    map.vap_array[ap_pointing_index].vap_index = ap_index;
    map.vap_array[ap_pointing_index].u.bss_info.ssid[0] ='\0';

    result = wifi_createVAP(radioIndex,&map);
    /* Done */
    return result;
}

/**function to retrieve the number of radios applicable
*IN/OUT : maxRadio
*RETURN : returns non-zero or zero value depending on whether 
*         number of radios is successfully retrieved or not
*         respectively
**/
INT test_utils_getMaxNumberOfRadio(UINT *maxRadio)
{
    int result = 0;
    wifi_hal_capability_t cap;

    result = wifi_getHalCapability(&cap);

    if(result == WIFI_HAL_SUCCESS)
        *maxRadio = cap.wifi_prop.numRadios;
    else
        *maxRadio = 0;

   return result;
}

#if 0
INT test_utils_setBandwidth(INT radioIndex, UINT bandwidth)
{
    INT result = WIFI_HAL_FAILURE;
    wifi_radio_operationParam_t operationParam;
    /* disable auto channel first if it is enabled */

    result = wifi_getRadioOperatingParameters(radioIndex, &operationParam);
    if (result != WIFI_HAL_SUCCESS)
    {
        return result;
    }

    if (operationParam.autoChannelEnabled != FALSE )
    {
        operationParam.autoChannelEnabled = FALSE;
        result = wifi_setRadioOperatingParameters(radioIndex, &operationParam);
    }

    operationParam.channelWidth = bandwidth;
    result = wifi_setRadioOperatingParameters(radioIndex, &operationParam);

    if (result != WIFI_HAL_SUCCESS)
        return result;

    result = wifi_getRadioOperatingParameters(radioIndex, &operationParam);
    if (result != WIFI_HAL_SUCCESS )
    {
        return WIFI_HAL_ERROR;
    }

    if (operationParam.channelWidth != bandwidth)
    {
        return WIFI_HAL_ERROR;
    }

    return WIFI_HAL_ERROR;
}

INT test_utils_setApEnable (BOOL enable, INT ap_index)
{
    int result = WIFI_HAL_SUCCESS;
    BOOL get_ap_enable = FALSE;

    result = wifi_setApEnable(ap_index, enable);
    if (result != WIFI_HAL_SUCCESS)
    {
        return result;
    }
    result = wifi_applySSIDSettings(ap_index);
    if (result != WIFI_HAL_SUCCESS)
    {
        return result;
    }
    
    result = wifi_getApEnable(ap_index, &get_ap_enable);

    if (result != WIFI_HAL_SUCCESS)
    {
        return result;
    }
     
    if( get_ap_enable != enable ) 
    {
        return WIFI_HAL_ERROR;
    }

    return result;

    return WIFI_HAL_ERROR;
}

INT test_utils_channelPush(INT radioIndex, ULONG channel)
{
    INT result;
    wifi_radio_operationParam_t operationParam;

    /* disable auto channel first if it is enabled */
    result = wifi_getRadioOperatingParameters(radioIndex, &operationParam);
    if (result != WIFI_HAL_SUCCESS)
    {
        return result;
    }

    if (operationParam.autoChannelEnabled != FALSE )
    {
	    operationParam.autoChannelEnabled = FALSE;
        result = wifi_setRadioOperatingParameters(radioIndex, &operationParam);
    }

    if (result != WIFI_HAL_SUCCESS)
    {
        return result;
    }

    operationParam.channel = channel;
    result =  wifi_setRadioOperatingParameters(radioIndex, &operationParam);
    
    if (result != WIFI_HAL_SUCCESS)
    {
        return result;
    }

    memset(&operationParam, 0, sizeof operationParam);
    result = wifi_getRadioOperatingParameters(radioIndex, &operationParam);

    if (result != WIFI_HAL_SUCCESS || (operationParam.channel != channel ))
    {
         return WIFI_HAL_ERROR;
    }

    return WIFI_HAL_ERROR;
}
#endif
