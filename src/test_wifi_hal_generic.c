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
#include "wifi_hal_generic.h"

#include <ut.h>
#include <Logger.h>

/**
 * @brief Tests requirements for L1 testing wifi_int()
 *
 * Test Coverage: Positive Scenario
 *
 * @retval WIFI_HAL_SUCCESS             -> tested
 *
 * @Note hal api is Synchronous
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

    UT_LOG("Exiting init...");

}

/**
 * @brief Tests requirements for L1 testing wifi_getHalCapability()
 * 
 * Test Coverage: Positive and Negative Scenarios
 * 
 * @retval WIFI_HAL_SUCCESS             -> tested
 * @retval WIFI_HAL_INVALID_ARGUMENTS   -> tested
 * 
 * @Note hal api is Synchronous
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
