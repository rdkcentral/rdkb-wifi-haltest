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

#include <stdio.h>

#include "wifi_hal_generic.h"

#include <ut.h>
#include "Logger.h"
#include "PreReqUtility.h"

int WiFiPreReq()
{
    LOG("Inside the WiFi initialization pre-reqsuite function...", __func__, __LINE__);
    int ret = 0;
	
    /* Invoke wifi_init() */
    ret = wifi_init();
    if (ret == 0)
    {
        LOG("WiFi initialization pre-reqsuite success", __func__, __LINE__);
    }
    else
    {
        LOG("WiFi initialization pre-reqsuite failed", __func__, __LINE__);
    }	

    LOG("Exited the the WiFi initialization pre-reqsuite function...", __func__, __LINE__);    
    return ret;
}
