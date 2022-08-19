/* ******************************************************************************
* Copyright (C) 2022 Sky group of companies, All Rights Reserved
* * --------------------------------------------------------------------------
* * THIS SOFTWARE CONTRIBUTION IS PROVIDED ON BEHALF OF SKY PLC. 
* * BY THE CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING,
* * BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
* * A PARTICULAR PURPOSE ARE DISCLAIMED
* ******************************************************************************
*
*   ** Project      : wifi
*   ** @addtogroup  : ut_wifi
*   ** @author      : gerald.weatherup@sky.uk
*   ** @date        : 19/08/22
*   **
*   ** @brief : Unit testing level 1
*   **
*
* ******************************************************************************/
 /** Core framework needs the following capabilties
 * 
 * @version 0.1 supporting (3.0) HAL
 * @date 2022-05-19
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <stddef.h>
#include <stdio.h>
#include "wifi_hal_generic.h"

#include <ut.h>

/**
 * @brief Init the test system
 * 
 * @return int - 0 on success, otherwise failure
 */
int test_generic_init(void)
{
    /* Check the requirements to start testing, and init any modules required */
    /* Check if the radio's are in the correct state etc. */
   
    return 0;
}

/**
 * @brief Clean the test system
 * 
 * @return int - 0 on success, otherwise failure
 */
int test_generic_clean(void)
{
    return 0;
}

/**
 * @brief Tests requirements for L1 testing wifi_getHalCapabilty()
 * 
 * Test Coverage:
 * 
 * @retval WIFI_HAL_SUCCESS             -> tested
 * @retval WIFI_HAL_ERROR               -> unclear requirement
 * @retval WIFI_HAL_INTERNAL_ERROR      -> unclear requirement
 * @retval WIFI_HAL_UNSUPPORTED         -> unclear requirement
 * @retval WIFI_HAL_INVALID_ARGUMENTS   -> tested
 * @retval WIFI_HAL_INVALID_VALUE       -> unclear requirement
 * 
 * @Note hal api is Synchronous
 */
void test_generic_wifi_getHalCapability(void)
{
    wifi_hal_capability_t cap;
    INT result;

    /* L1 Test */

    /* Check the testing profile see if this function is present on this platform */
    //TEST_RETURN_IF_UNSUPPORTED_FUNCTION( "wifi_getHalCapability" );
    
    /* Negative Test cause */
    result = wifi_getHalCapability(NULL);
    UT_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS  );

    /* Positive Test WIFI_HAL_SUCCESS */
    //wifi_getHalCapability_ExpectAndReturn(WIFI_HAL_SUCCESS);
    result = wifi_getHalCapability(&cap);
    UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS  );

    /* Check each element of the profile */
    UT_ASSERT_EQUAL( cap.version.major , 3 );
    UT_ASSERT_EQUAL( cap.version.minor, 0 );

    /* Check the expected capabilties are the same as the capabilites returned */
    //TEST_ASSERT_PROFILE_CHECK( "wifi_getHalCapability", caps );
}


/**
 * @brief Tests requirements for L1 testing for wifi_init()
 * 
 * @todo documentation unclear when WIFI_HAL_ERROR - would be expected, and why it would fail?
 * #################################################
 * BRCM specific ERROR codes
 * WIFI_HAL_ERROR would be returned only in case of internal errors,like WLDM_INIT failures or thread creation failures
 *##################################################
 */
void test_generic_wifi_init( void )
{
    int result;

    /* Positive result */
    result = wifi_init();
    UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );

    /*calling wifi_init should succeed, As it will return with Already intialized message */
    result = wifi_init();
    UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS);

    /* @todo: Unclear how the function will fail, not enough information in the documentation */
}

void test_generic_wifi_getHalCapabilityPositive( void )
{
    wifi_hal_capability_t caps;
    int result;

    /* WIFI_HAL_SUCCESS */

    result = wifi_getHalCapability( &caps );
    UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );

    /* @TODO: Check the capabilities against the expected profile for this platform */
}

void test_generic_wifi_getHalCapabilityNegative( void )
{
    int result;

    result = wifi_getHalCapability( NULL );
    UT_ASSERT_EQUAL( result, WIFI_HAL_ERROR );
}

static UT_test_suite_t *pSuite = NULL;

/**
 * @brief Register the main tests for this module
 * 
 * @return int - 0 on success, otherwise failure
 */
int test_generic_register( void )
{
    /* add a suite to the registry */
    pSuite = UT_add_suite("[L1 wifi_hal_generic]", &test_generic_init, &test_generic_clean);
    if (NULL == pSuite) 
    {
        return -1;
    }

    UT_add_test( pSuite, "wifi_init", test_generic_wifi_init);
    UT_add_test( pSuite, "wifi_getHalCapability - Positive", test_generic_wifi_getHalCapabilityPositive);
    UT_add_test( pSuite, "wifi_getHalCapability - Negative", test_generic_wifi_getHalCapabilityNegative);

    return 0;
}
