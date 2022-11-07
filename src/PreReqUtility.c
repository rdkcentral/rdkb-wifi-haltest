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

/**function to perform WiFi initialization
*IN : None
*OUT : returns success or failure status of WiFi initialization
**/
int WiFiPreReq()
{

    UT_LOG("Inside the WiFi initialization pre-reqsuite function...");

    int ret = 0;
    int numOfRadios = 0;
    int radioIndex = 0;
    wifi_hal_capability_t cap;
    wifi_radio_operationParam_t operationParam;
    int radioSuccess = 0;

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

            /* Invoke wifi_setRadioOperatingParameters for all applicable radios */
            for (radioIndex = 0; radioIndex < numOfRadios; radioIndex++)
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
                    UT_LOG("WiFi initialization pre-reqsuite failed");
                    break;
                }
            }

            /* Check if radio set operating pararmeters is success for all applicable radios */
            if (radioSuccess == numOfRadios)
            {
                UT_LOG("WiFi initialization pre-reqsuite success");
            }
            else
            {
                UT_LOG("WiFi initialization pre-reqsuite failed");
            }
        }
        else
        {                        
            UT_LOG("WiFi getHalCapability returned failure");
            UT_LOG("WiFi initialization pre-reqsuite failed");
        }
    }
    else
    {
        UT_LOG("WiFi init returned failure");
        UT_LOG("WiFi initialization pre-reqsuite failed");
    }	

    UT_LOG("Exited the the WiFi initialization pre-reqsuite function...");    
    return ret;

}
