
/* ******************************************************************************
* Copyright (C) 2022 Sky group of companies, All Rights Reserved
* * --------------------------------------------------------------------------
* * THIS SOFTWARE CONTRIBUTION IS PROVIDED ON BEHALF OF SKY PLC. 
* * BY THE CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING,
* * BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
* * A PARTICULAR PURPOSE ARE DISCLAIMED
* ******************************************************************************
*
*   ** Project      : wifi
*   ** @addtogroup  : ut_wifi
*   ** @author      : Palaksha Gowda
*   ** @date        : 19/08/22
*   **
*   ** @brief : Unit testing
*   **
*
* ******************************************************************************/

#include <stdio.h>
#include <string.h>

#include <test_utils.h>
#include <wifi_hal.h>

INT test_utils_setBandwidth(INT radioIndex, UINT bandwidth)
{
    #if 0
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
    #endif

    return WIFI_HAL_ERROR;
}


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

    /* Negative */ /* set SSID Name to NULL */
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

INT test_utils_setApEnable (BOOL enable, INT ap_index)
{
#if 0
    int result = RETURN_OK;
    BOOL get_ap_enable = FALSE;

    result = wifi_setApEnable(ap_index, enable);
    if (result != RETURN_OK)
    {
        return result;
    }
    result = wifi_applySSIDSettings(ap_index);
    if (result != RETURN_OK)
    {
        return result;
    }
    
    result = wifi_getApEnable(ap_index, &get_ap_enable);

    if (result != RETURN_OK)
    {
        return result;
    }
     
    if( get_ap_enable != enable ) 
    {
        return RETURN_ERR;
    }

    return result;
#endif
    return WIFI_HAL_ERROR;
}

INT test_utils_channelPush(INT radioIndex, ULONG channel)
{
#if 0
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

#endif
    return WIFI_HAL_ERROR;
}
