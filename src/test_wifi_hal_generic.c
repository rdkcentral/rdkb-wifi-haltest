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

/**
* @file test_wifi_hal_generic.c
* @page WIFIHAL_Generic WiFi HAL Level 1 Tests - Generic
*
* ## Module's Role
* This module includes Level 1 functional tests (success and failure scenarios).
* This is to ensure that the wifi_init() and wifi_getHalCapability() APIs meet the operational requirements across all vendors.
*
* **Pre-Conditions:**  None@n
* **Dependencies:** None@n
*
* Ref to API Definition specification documentation : [halSpec.md](../../../docs/pages/)
*/

#include <string.h>
#include <stdlib.h>
#include <setjmp.h>

#include "wifi_hal.h"
#include "api_translator.h"

#include <ut.h>
#include <ut_log.h>

/**
* @brief This function checks if wifi_init() works as expected
*
* Calls the header function wifi_init() with no params
*
* **Test Group ID:** Basic: 01@n
* **Test Case ID:** 001@n
* **Priority:** Medium@n
*
* **Pre-Conditions:** None@n    
* **Dependencies:** None@n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console@n
*
* **Test Procedure:**@n
*
* |Variation / Step|Description|Test Data|Expected Result|Notes|
* |:--:|---------|----------|--------------|-----|
* |01| invoke wifi_init()| Not Applicable| WIFI_HAL_SUCCESS | Should Pass |
*/
void test_generic_wifi_init( void )
{

    UT_LOG("Entering init...");

    int result = 0;

    /* Positive Test WIFI_HAL_SUCCESS */
    UT_LOG("Test Case 1");
    result = wifi_init();
    UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );

    UT_LOG("Init API returns : %d", result);

    /* TODO : Need to get confirmation whether invoking wifi_init() back to back returns success/failure */
    /*
    UT_LOG("Test Case 2");
    result = wifi_init();
    UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );

    UT_LOG("Second invocation of Init API returns : %d", result); */

    UT_LOG("Exiting init...");

}

/**
* @brief This function checks if wifi_getHalCapability() works as expected
*
* Calls the header function wifi_getHalCapability() with correct and incorrect params
*
* **Test Group ID:** Basic: 01@n
* **Test Case ID:** 002@n
* **Priority:** Medium@n
*
* **Pre-Conditions:** None@n 
* **Dependencies:** None@n
* **User Interaction:** If user chose to run the test in interactive mode, then the test case has to be selected via console@n
*
* **Test Procedure:**@n
*
* |Variation / Step|Description|Test Data|Expected Result|Notes|
* |:--:|---------|----------|--------------|-----|
* |01|call wifi_getHalCapability() with a valid empty buffer | *cap=valid buffer of type wifi_hal_capability_t | WIFI_HAL_SUCCESS| Should Pass |
* |02|call wifi_getHalCapability() with NULL buffer | *cap=NULL | WIFI_HAL_INVALID_ARGUMENTS | Should Fail |
*/
void test_generic_wifi_getHalCapability(void)
{
    UT_LOG("Entering getHalCapability...");

    wifi_hal_capability_t cap;
    int result = 0;

    /* Positive Test WIFI_HAL_SUCCESS */
    /* Passing a valid buffer to retrieve the HAL capability and expecting the API to return success*/
    UT_LOG("Test Case 1");
    result = wifi_getHalCapability(&cap);
    UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS  );

    UT_LOG("Passing valid buffer to the API returns : %d", result);

    /* Negative Test WIFI_HAL_INVALID_ARGUMENTS */
    /* Passing a NULL buffer input to retrieve the HAL capability and expecting the API to return failure */
    UT_LOG("Test Case 2");
    result = wifi_getHalCapability(NULL);
    UT_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS  );

    UT_LOG("Passing NULL buffer to the API returns : %d", result);

    UT_LOG("Exiting getHalCapability...");
}

static UT_test_suite_t * pSuite = NULL;

/**
 * @brief Register the main tests for this module
 *
 * @return int - 0 on success, otherwise failure
 */
int test_wifi_generic_register( void )
{
    /* add a suite to the registry */
    pSuite = UT_add_suite("[L1 wifi-generic]", NULL, NULL);
    if (NULL == pSuite)
    {
        return -1;
    }

    UT_add_test( pSuite, "wifi_init", test_generic_wifi_init);
    UT_add_test( pSuite, "wifi_getHalCapability" , test_generic_wifi_getHalCapability);

    return 0;
}
