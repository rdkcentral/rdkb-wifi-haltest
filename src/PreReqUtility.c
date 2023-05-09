/*
##########################################################################
# If not stated otherwise in this file or this component's Licenses.txt
# file the following copyright and licenses apply:
#
# Copyright 2022 RDK Management
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
##########################################################################
*/

#include <stdlib.h>
#include <ut.h>
#include <ut_log.h>

#include "wifi_hal.h"

#include "PreReqUtility.h"
#include "config_parser.h"
#include "api_translator.h"

/**function to perform WiFi initialization
* IN : None
* OUT : returns success or failure status of WiFi initialization
**/
int WiFiPreReq()
{

    UT_LOG("Inside the WiFi initialization pre-requisite function...");

    int ret = 0;
    int numOfRadios = 0;
    int radioIndex = 0;
    wifi_hal_capability_t cap;
    wifi_radio_operationParam_t operationParam;
    int radioSuccess = 0;
    int vapSuccess = 0;
    int * apIndices = NULL;
    int index = 0;

    /* Invoke wifi_init() */
    ret = wifi_init();
    if (ret == 0)
    {
        UT_LOG("WiFi init returned success");

        /* Invoke wifi_getHalCapability() */
        ret = wifi_getHalCapability(&cap);
        if (ret == 0)
        {
            UT_LOG("WiFi getHalCapability returned success");

            /* Get the number of radios applicable */
            numOfRadios = cap.wifi_prop.numRadios;

            UT_LOG("Number of Radios : %u", numOfRadios);

            /* Get the list of private access points corresponding to each of the supported radios */
            apIndices = (int *)malloc( sizeof(int) * numOfRadios );

            if (apIndices != NULL)
            {
                ret = test_utils_getApIndices(numOfRadios, apIndices, PRIVATE);

                if (ret == 0)
                {
                    UT_LOG("Private AP Indices for the supported radios retrieved");

                    /* Invoke wifi_setRadioOperatingParameters for all applicable radios */
                    for (radioIndex = 0; radioIndex < numOfRadios; radioIndex++, index++)
                    {
                        /* Get the radio configuration */
                        ret = get_radio_config(radioIndex, &operationParam);

                        if (ret == 0)
                        {
                            UT_LOG("get_radio_config for radio %d returns : %d", radioIndex, ret);

                            ret = wifi_setRadioOperatingParameters(radioIndex, &operationParam);
                            if (ret == 0)
                            {
                                UT_LOG("WiFi setRadioOperatingParameters returned success");
                                radioSuccess++;

                                /* Create VAP */
                                ret = createVAP(radioIndex, apIndices[index], PRIVATE);
                                if (ret == 0)
                                {
                                    vapSuccess++;
                                }
                                else
                                {
                                    break;
                                }
                            }
                            else
                            {
                                UT_LOG("WiFi setRadioOperatingParameters returned failure");
                                break;
                            }
                        }
                        else
                        {
                            UT_LOG("Unable to parse the radio config file");
                            UT_LOG("WiFi initialization pre-requisite failed");
                            break;
                        }
                    }

                    /* Check if radio set operating parameters and vap create is success for all applicable radios */
                    if (radioSuccess == numOfRadios && vapSuccess == numOfRadios)
                    {
                        UT_LOG("WiFi initialization pre-requisite success");
                    }
                    else
                    {
                        UT_LOG("WiFi initialization pre-requisite failed");
                    }
                }
                else
                {
                    UT_LOG("Unable to retrieve the access point indices");
                }
                free(apIndices);
            }
            else
            {
                UT_LOG("Malloc operation failed");
                UT_LOG("WiFi initialization pre-requisite failed");
            }
        }
        else
        {
            UT_LOG("WiFi getHalCapability returned failure");
            UT_LOG("WiFi initialization pre-requisite failed");
        }
    }
    else
    {
        UT_LOG("WiFi init returned failure");
        UT_LOG("WiFi initialization pre-requisite failed");
    }

    UT_LOG("Exited the the WiFi initialization pre-requisite function...");
    return ret;

}

/**function to create private access points
* IN  : radioIndex for which private AP index needs to be created
* IN  : AP index
* IN  : Type of AP index (eg : Private, Sta)
* OUT : returns success or failure status of AP creation
**/
int createVAP(int radioIndex, int apIndex, APTYPE type)
{
    int ret;
    wifi_vap_info_map_t map;

    /* Get the vap configuration */
    switch(type)
    {
        case PRIVATE :
            ret = get_private_vap_config(apIndex, &map.vap_array[0]);
            break;
        case STA :
            ret = get_mesh_sta_vap_config(apIndex, &map.vap_array[0]);
            break;
        default:
            UT_LOG("Unable to parse the vap config file");
            return WIFI_HAL_ERROR;
    }

    UT_LOG("get_private_vap_config for vap %d returns : %d", apIndex, ret);

    map.num_vaps = 1;
    ret = wifi_createVAP(radioIndex, &map);
    if (ret != 0)
    {
        UT_LOG("WiFi create VAP returned failure");
        return WIFI_HAL_ERROR;
    }

    UT_LOG("WiFi create VAP returned success");

    return WIFI_HAL_SUCCESS;
}
