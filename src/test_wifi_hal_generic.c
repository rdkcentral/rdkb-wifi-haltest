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

void test_generic_wifi_init( void )
{
    int result;

    /* Positive result */
    result = wifi_init();
    UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );

    /*calling wifi_init should succeed, As it will return with Already initalized message */
    result = wifi_init();
    UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS);

    /* #TODO: Unclear how the function will fail, maybe this function should be void? */
}

/**
 * @brief Tests requirements for L1 testing wifi_getHalCapability()
 * 
 * Test Coverage:
 * 
 * @retval WIFI_HAL_SUCCESS             -> tested
 * @retval WIFI_HAL_INVALID_ARGUMENTS   -> tested
 * 
 * @Note hal api is Synchronous
 */
void test_generic_wifi_getHalCapability(void)
{
    wifi_hal_capability_t cap;
    INT result;

    /* L1 Test */

    /* Negative Test cause */
    result = wifi_getHalCapability(NULL);
    UT_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS  );

    /* Positive Test WIFI_HAL_SUCCESS */
    result = wifi_getHalCapability(&cap);
    UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS  );

    /* Check each element of the profile */
    UT_ASSERT_EQUAL( cap.version.major , 3 );
    UT_ASSERT_EQUAL( cap.version.minor, 0 );

    /* #TODO: Check the testing profile see if this function is present on this platform */
    //TEST_RETURN_IF_UNSUPPORTED_FUNCTION( "wifi_getHalCapability" );

    /* #TODO: Check the expected capabilites are the same as the capabilites returned */
    //TEST_ASSERT_PROFILE_CHECK( "wifi_getHalCapability", caps );
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