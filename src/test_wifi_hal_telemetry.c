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
#include "wifi_hal_telemetry.h"

#include <ut.h>

void test_telemetry_wifi_getRadioBandUtilization(void)
{
	UT_FAIL("Need to implement");
    /* Positive */
    /* Negative */
}

void test_telemetry_wifi_getApAssociatedDeviceDiagnosticResult3(void)
{
	UT_FAIL("Need to implement");
    /* Positive */
    /* Negative */
}

void test_telemetry_wifi_getApAssociatedClientDiagnosticResult(void)
{
  UT_FAIL("Need to implement"); 
}

void test_telemetry_wifi_getRadioTrafficStats2(void)
{
  UT_FAIL("Need to implement"); 
}

static UT_test_suite_t * pSuite = NULL;

/**
 * @brief Register the main tests for this module
 * 
 * @return int - 0 on success, otherwise failure
 */
int test_wifi_telemetry_register( void )
{
    /* add a suite to the registry */
    pSuite = UT_add_suite("[L1 wifi-telemetry]", NULL, NULL);
    if (NULL == pSuite) 
    {
        return -1;
    }

    UT_add_test( pSuite, "wifi_getRadioBandUtilization", test_telemetry_wifi_getRadioBandUtilization);
		UT_add_test( pSuite, "wifi_getApAssociatedDeviceDiagnosticResult3", test_telemetry_wifi_getApAssociatedDeviceDiagnosticResult3);
		UT_add_test( pSuite, "wifi_getApAssociatedClientDiagnosticResult", test_telemetry_wifi_getApAssociatedClientDiagnosticResult);
		UT_add_test( pSuite, "wifi_getRadioTrafficStats2", test_telemetry_wifi_getRadioTrafficStats2);

    return 0;
}