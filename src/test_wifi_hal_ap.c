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

#include <string.h>
#include <stdlib.h>
#include <setjmp.h>

#include "wifi_hal.h"
#include "wifi_hal_ap.h"

#include <ut.h>

void test_wifi_getApAssociatedDevice(void)
{
	UT_FAIL("Need to implement"); 
}

void test_wifi_enableCSIEngine(void)
{
	UT_FAIL("Need to implement"); 
}

void test_wifi_createVAP(void)
{
	UT_FAIL("Need to implement"); 
}

void test_wifi_getRadioVapInfoMap(void)
{
	UT_FAIL("Need to implement"); 
}

void test_wifi_mgmt_frame_callbacks_register(void)
{
	UT_FAIL("Need to implement"); 
}

void test_wifi_newApAssociatedDevice_callback_register(void)
{
	UT_FAIL("Need to implement"); 
}

void test_wifi_apDeAuthEvent_callback_register(void)
{
	UT_FAIL("Need to implement"); 
}

void test_wifi_apDisassociatedDevice_callback_register(void)
{
	UT_FAIL("Need to implement"); 
}

static UT_test_suite_t * pSuite = NULL;

/**
 * @brief Register the main tests for this module
 * 
 * @return int - 0 on success, otherwise failure
 */
INT test_wifi_ap_register( void )
{
    /* add a suite to the registry */
    pSuite = UT_add_suite("[L1 wifi-ap]", NULL, NULL);
    if (NULL == pSuite) 
    {
        return -1;
    }

    UT_add_test( pSuite, "wifi_getApAssociatedDevice", test_wifi_getApAssociatedDevice);
    UT_add_test( pSuite, "wifi_enableCSIEngine", test_wifi_enableCSIEngine);
    UT_add_test( pSuite, "wifi_createVAP", test_wifi_createVAP);
    UT_add_test( pSuite, "wifi_getRadioVapInfoMap", test_wifi_getRadioVapInfoMap);
    UT_add_test( pSuite, "wifi_mgmt_frame_callbacks_register", test_wifi_mgmt_frame_callbacks_register);
    UT_add_test( pSuite, "wifi_newApAssociatedDevice_callback_register", test_wifi_newApAssociatedDevice_callback_register);
    UT_add_test( pSuite, "wifi_apDeAuthEvent_callback_register", test_wifi_apDeAuthEvent_callback_register);
    UT_add_test( pSuite, "wifi_apDisassociatedDevice_callback_register", test_wifi_apDisassociatedDevice_callback_register);

    return 0;
}