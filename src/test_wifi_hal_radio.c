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
#include "wifi_hal_radio.h"

#include <ut.h>

void test_radio_wifi_getRadioTransmitPower(void)
{
	UT_FAIL("Need to implement"); 
}

void test_radio_wifi_getRadioOperatingChannelBandwidth(void)
{
	UT_FAIL("Need to implement"); 
}

void test_radio_wifi_setRadioOperatingParameters(void)
{
	UT_FAIL("Need to implement"); 
}

void test_radio_wifi_scanResults_callback_register(void)
{
	UT_FAIL("Need to implement"); 
}


static UT_test_suite_t *pSuite = NULL;

/**
 * @brief Register the main tests for this module
 * 
 * @return int - 0 on success, otherwise failure
 */
INT test_wifi_radio_register( void )
{
    /* add a suite to the registry */
    pSuite = UT_add_suite("[L1 wifi-radio]", NULL, NULL);
    if (NULL == pSuite) 
    {
        return -1;
    }

    UT_add_test( pSuite, "wifi_getRadioTransmitPower", test_radio_wifi_getRadioTransmitPower);
		UT_add_test( pSuite, "wifi_getRadioOperatingChannelBandwidth)", test_radio_wifi_getRadioOperatingChannelBandwidth);
		UT_add_test( pSuite, "wifi_setRadioOperatingParameters", test_radio_wifi_setRadioOperatingParameters);
		UT_add_test( pSuite, "wifi_scanResults_callback_register)", test_radio_wifi_scanResults_callback_register);

  return 0;
}