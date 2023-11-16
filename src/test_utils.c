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


#include <stdio.h>
#include <string.h>

#include <test_utils.h>
#include <wifi_hal.h>

#include "api_translator.h"
#include <wifi_hal_generic.h>
#include <ut.h>
#include <ut_log.h>
#include <stdlib.h>
#include "config_parser.h"

extern wifi_radio_operationParam_t g_operationParam[3];
extern wifi_vap_info_map_t g_org_map[3];

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

/**function to retrieve the number of radios applicable
* IN     : maxRadio - number of radios supported
* IN     : type - describes the type of access point (eg : Private, Sta)
* OUT    : returns an array of access point indices
*          depending on the number of radios supported
**/
INT test_utils_getApIndices(UINT maxRadio, INT apIndices[], APTYPE type)
{
    int result = 0;

    switch(type)
    {
        case PRIVATE :
            if (maxRadio == 3)
            {
                apIndices [0] = 0;
                apIndices [1] = 1;
                apIndices [2] = 16;
            }
            else if (maxRadio == 2)
            {
                apIndices [0] = 0;
                apIndices [1] = 1;
            }
            else
            {
                result = -1;
            }
            break;

        case STA :
            if (maxRadio == 3)
            {
                apIndices [0] = 14;
                apIndices [1] = 15;
                /* TODO : Add STA index for 6G  */
                /* apIndices [2] = 24; */
            }
            else if (maxRadio == 2)
            {
                apIndices [0] = 14;
                apIndices [1] = 15;
            }
            else
            {
                result = -1;
            }
            break;

        case IOT :
            if (maxRadio == 3)
            {
		/* TODO : Add IOT index for 6G  */
                apIndices [0] = 2;
                apIndices [1] = 3;
            }
            else if (maxRadio == 2)
            {
                apIndices [0] = 2;
                apIndices [1] = 3;
            }
            else
            {
                result = -1;
            }
            break;

        case BACKHAUL :
            if (maxRadio == 3)
            {
		/* TODO : Add BACKHAUL index for 6G  */
                apIndices [0] = 12;
                apIndices [1] = 13;
            }
            else if (maxRadio == 2)
            {
                apIndices [0] = 12;
                apIndices [1] = 13;
            }
            else
            {
                result = -1;
            }
            break;

        case LNF_PSK :
            if (maxRadio == 3)
            {
                apIndices [0] = 6;
                apIndices [1] = 7;
                /* TODO : Add LNF_PSK index for 6G  */
            }
            else if (maxRadio == 2)
            {
                apIndices [0] = 6;
                apIndices [1] = 7;
            }
            else
            {
                result = -1;
            }
            break;

        case LNF_RADIUS :
            if (maxRadio == 3)
            {
                apIndices [0] = 10;
                apIndices [1] = 11;
                /* TODO : Add LNF_RADIUS index for 6G  */
            }
            else if (maxRadio == 2)
            {
                apIndices [0] = 10;
                apIndices [1] = 11;
            }
            else
            {
                result = -1;
            }
            break;

        case HOTSPOT_OPEN :
            if (maxRadio == 3)
            {
                apIndices [0] = 4;
                apIndices [1] = 5;
                /* TODO : Add HOTSPOT_OPEN index for 6G  */
            }
            else if (maxRadio == 2)
            {
                apIndices [0] = 4;
                apIndices [1] = 5;
            }
            else
            {
                result = -1;
            }
            break;

        case HOTSPOT_SECURE :
            if (maxRadio == 3)
            {
                apIndices [0] = 8;
                apIndices [1] = 9;
                /* TODO : Add HOTSPOT_SECURE index for 6G  */
            }
            else if (maxRadio == 2)
            {
                apIndices [0] = 8;
                apIndices [1] = 9;
            }
            else
            {
                result = -1;
            }
            break;

        default :
            result = -1;
    }
    return result;
}

/** function to set prerequisite for l2 tests **/
INT l2_test_prerequisite()
{
    int * apIndices = NULL;
    int radioIndex = 0, index = 0, returnStatus = 0;
    unsigned int numRadios = 0;

    UT_LOG("Entered l2_test_prerequisite");
    returnStatus = test_utils_getMaxNumberOfRadio(&numRadios);

    if( returnStatus == 0)
    {
        apIndices = (int *)malloc( sizeof(int) * numRadios );
	if( apIndices != NULL)
	{
            returnStatus = test_utils_getApIndices(numRadios, apIndices, PRIVATE);
            if( returnStatus == 0)
	    {	
	        for(radioIndex = 0; radioIndex < numRadios ; radioIndex++, index++)
                {
                    returnStatus = get_radio_config(radioIndex, &g_operationParam[radioIndex]);
                    if( returnStatus != 0)
                    {
                        UT_LOG("Failed to parse radio_config file returnStatus is %d", returnStatus);
                        return -1;
                    }
                    returnStatus = get_private_vap_config(apIndices[index], &g_org_map[radioIndex].vap_array[0]);
                    if (returnStatus != 0)
                    {
                        UT_LOG("Failed to parse vap_config file returnStatus is %d", returnStatus);
                        return -1;
	            }
                }
		free(apIndices);
	    }
            else
	    {
                UT_LOG("Failed to retrieve apIndices");
                return -1;
            }
        }
        else
        {
	    UT_LOG("Malloc opeartion failed");
            return -1;
        }
     }
     else
     {
	 UT_LOG("Failed to fetch the number of radios");
         return -1;
     }
	
     UT_LOG("Exiting l2_test_prerequisite");
     return 0;
}

/**function to get channel list based on radioIndex
* IN     :  radioIndex - to identify specific radio
* IN     :  count - to store the number of channels
* IN     :  channels - array to store the list of channels supported for particular radio
**/
INT get_channel_list(int radioIndex, int *count, int channels[25])
{
    int j, k, ret = 0;
    UT_LOG("Entered get_channel_list");
    wifi_hal_capability_t cap;
    wifi_radio_capabilities_t *rcap;
    wifi_channels_list_t *chList;

    ret = wifi_getHalCapability(&cap);
    UT_ASSERT_EQUAL(ret, WIFI_HAL_SUCCESS);

    if(ret == WIFI_HAL_SUCCESS)
    {
        rcap = &(cap.wifi_prop.radiocap[radioIndex]);
        for (j = 0; j < rcap->numSupportedFreqBand; j++) {
            chList = &(rcap->channel_list[j]);
	    *count = chList->num_channels;
            for (k = 0; k < chList->num_channels; k++) {
                UT_LOG(" %d", chList->channels_list[k]);
                channels[k] = chList->channels_list[k];
            }
        }
    }
    else
    {
        UT_LOG("wifi_getHalCapability failed ret is %d", ret);
        return -1;
    }

    UT_LOG("Exiting get_channel_list");
    return 0;
}

/**function to get channel list based on radioIndex
* IN     :  radioIndex - to identify specific radio
* IN     :  count - to store the number of channels
* IN     :  Width - array to store the list of supported channel widths for particular radio
**/
INT get_channel_bandwidth(int radioIndex, int *count, wifi_channelBandwidth_t Width[5])
{
    int j = 0, ret = 0;
    wifi_hal_capability_t cap;
    wifi_radio_capabilities_t *rcap;
    ret = wifi_getHalCapability(&cap);
    UT_ASSERT_EQUAL(ret, WIFI_HAL_SUCCESS);

    if(ret == WIFI_HAL_SUCCESS)
    {
        rcap = &(cap.wifi_prop.radiocap[radioIndex]);
        for (j = 0; j < rcap->numSupportedFreqBand; j++)
        {
            wifi_channelBandwidth_t chbw = rcap->channelWidth[j];
            UT_LOG("channelWidth: 0x%04x", rcap->channelWidth[j]);

            if (chbw & WIFI_CHANNELBANDWIDTH_20MHZ)
            {
                UT_LOG(" 20");
                Width[*count] = WIFI_CHANNELBANDWIDTH_20MHZ;
                (*count)++;
            }
            if (chbw & WIFI_CHANNELBANDWIDTH_40MHZ)
            {
                UT_LOG(" 40");
                Width[*count] = WIFI_CHANNELBANDWIDTH_40MHZ;
                (*count)++;
            }
            if (chbw & WIFI_CHANNELBANDWIDTH_80MHZ)
            {
                UT_LOG(" 80");
                Width[*count] = WIFI_CHANNELBANDWIDTH_80MHZ;
		(*count)++;
            }
            if (chbw & WIFI_CHANNELBANDWIDTH_160MHZ)
            {
                UT_LOG(" 160");
                Width[*count] = WIFI_CHANNELBANDWIDTH_160MHZ;
                (*count)++;
            }
            UT_LOG(" MHz");

            if(chbw == 0x0000)
            {
                UT_LOG("channelWidth is 0");
                UT_FAIL("channelWidth is 0");
		return -1;
            }
        }
     }
     else
     {
         UT_LOG("wifi_getHalCapability failed ret is %d", ret);
         return -1;
     }
     return 0;
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
