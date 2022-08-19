/**
 * @file test_wifi_hal_generic.c
 * @author gerald weatherup (gerald.weatherup@sky.uk)
 * @brief Testing the wifi_hal_generic.h interface
 * @addtogroup wifi_hal_tests
 * 
 * Core framework needs the following capabilties
 *
 * @remarks: Profile / Capability defination for each platform, this will allow one set of tests to adapt to the requirements based on platform caps
 *
 * - Supported functions capability checking also required
 * - @todo SYSTEM_RETURN_IF_UNSUPPORTED_FUNCTION - would be required
 * - @todo SYSTEM_ASSERT_PROFILE_CHECK - would be required
 * - @todo SYSTEM_GET_INT_FROM_PROFILE - would be required
 * - @todo SYSTEM_GET_STRING_FROM_PROFILE - would be required
 * - @todo verification from 'wl' commands to validate the functions needs to be looked at
 * 
 * @version 0.1 supporting (3.0) HAL
 * @date 2022-05-19
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifdef TEST

#include <stddef.h>
#include <stdio.h>
#include "wifi_hal_generic.h"

#include <csunit.h>

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
    CU_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS  );

    /* Positive Test WIFI_HAL_SUCCESS */
    //wifi_getHalCapability_ExpectAndReturn(WIFI_HAL_SUCCESS);
    result = wifi_getHalCapability(&cap);
    CU_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS  );

    /* Check each element of the profile */
    CU_ASSERT_EQUAL( cap.version.major , 3 );
    CU_ASSERT_EQUAL( cap.version.minor, 0 );

    /* Check the expected capabilties are the same as the capabilites returned */
    //TEST_ASSERT_PROFILE_CHECK( "wifi_getHalCapability", caps );
}

/**
 * @brief Tests requirements for L1 testing for wifi_factoryReset()
 * 
 * Test Coverage:
 * 
 * @retval RETURN_OK    -   Call the function it should return
 * @retval RETURN_ERR   -   Unclear requirement, what is an error?
 * 
 * @todo RETURN_XXX is inconsistant in this interface, since WIFI_HAL_XXX is also used
 * @todo the API should be returning enums, which are unique to the WIFI_HAL, and therefore fixed usage.
 * @todo Altough the function under test is specified as synchronous, here is also a note that contradicts this.
 *          - This function must not suspend and must not invoke any blocking system calls. It should probably just send a message to a driver event handler task.
 * @todo RETURN_ERR - unclear requirement from documentation
 * 
 * @todo: Negative test, not clear how this is possible, can it be called twice?
 * 
 * @Note hal api is Synchronous
 */
void test_generic_wifi_factoryReset( void )
{
    int result;

    /* Positive test */
    result = wifi_factoryReset();
    CU_ASSERT_EQUAL( result, RETURN_OK );

    /* Validate via other means that the reset has occurred, more detail information on wifi required */
    /* Negative Test */

    /* @todo: Can this be called twice? Back to Back, Documentation */

    /* Diabled for testing */
    // result = wifi_factoryReset();
    // CU_ASSERT_EQUAL( RETURN_ERR, result );

    /* @todo: Unclear how the function will fail, not enough information in the documentation */
}

/**
 * @brief Tests requirements for L1 testing for wifi_setLED()
 * 
 * @todo: Requires capabilties & SYSTEM_GET_INT_FROM_PROFILE 
 */

void test_generic_wifi_setLED( void )
{
    int result;
    int leds_present_on_this_platform=1;
    int index;

    /* Notes: Function needs to adapt based on the number of LED's capable for the system */
    //leds_present_on_this_platform = SYSTEM_GET_INT_FROM_PROFILE( "number_of_wifi_leds");

    /* Positive Test */
    for ( index=0; index< leds_present_on_this_platform; index++ )
    {
        /* Radio Index 0 should always exist */
        result = wifi_setLED( index, TRUE );
        CU_ASSERT_EQUAL( result, RETURN_OK  );

        /* Requirement here to prove the functionality of the LED, how can this be achieved? */
        wifi_setLED( index, FALSE );
        CU_ASSERT_EQUAL( result, RETURN_OK  );
    }

    /* Negative Test */
    /* This LED will be out of range on all platforms */
    result = wifi_setLED( 9999, TRUE );
    CU_ASSERT_EQUAL( result, RETURN_ERR  );

    /* This LED will be out of range on all platforms */
    result = wifi_setLED( 9999, FALSE );
    CU_ASSERT_EQUAL( result, RETURN_ERR );
}

/**
 * @brief Tests requirements for L1 testing for wifi_init()
 * 
 * @todo documentation unclear when RETURN_ERR - would be expected, and why it would fail?
 * #################################################
 * BRCM specific ERROR codes
 * RETURN_ERR would be returned only in case of internal errors,like WLDM_INIT failures or thread creation failures
 *##################################################
 */
void test_generic_wifi_init( void )
{
    int result;

    /* Positive result */
    result = wifi_init();
    CU_ASSERT_EQUAL( result, RETURN_OK );

    /*calling wifi_init should succeed, As it will return with Already intialized message */
    result = wifi_init();
    CU_ASSERT_EQUAL( result, RETURN_OK);

    /* @todo: Unclear how the function will fail, not enough information in the documentation */
}

/**
 * @brief Tests requirements for L1 testing for wifi_reset()
 * 
 * Function is stated as Synchronous, and should not block
 * 
 * @todo documentation unclear why the RETURN_ERR condition would occur
 * 
 *BRCM specific ERROR codes
 *RETURN_ERR would be returned only in case of internal errors
 *
 */
void test_generic_wifi_reset( void )
{
    int result;

    /* Positive */
    result = wifi_reset();
    CU_ASSERT_EQUAL( result, RETURN_OK );

    /* Reset twice back to back should therefore be possible */
    result = wifi_reset();
    CU_ASSERT_EQUAL( result, RETURN_OK );

    /* Negative */

    /* Unclear documentation requirement */
}

/**
 * @brief Tests requirements for L1 testing for wifi_down()
 * 
 * @todo documentation unclear why the wifi would RETURN_ERR, is it possible to call twice? 
 *
 *BRCM specific ERROR codes
 *RETURN_ERR would be returned only in case of internal errors
 */
void test_generic_wifi_down( void )
{
    int result;

    /* Positive */
    result = wifi_down();
    CU_ASSERT_EQUAL( result, RETURN_OK );

    /* calling it twice should succeed,As it will only call wifi_setRadioEnable with 0 */
    result = wifi_down();
    CU_ASSERT_EQUAL(  result, RETURN_OK );

    /* Negative */

    /* Unclear documentation requirement */
}

/**
 * @brief Tests requirements for L1 testing for wifi_createInitialConfigFiles
 * 
 * @todo documentation unclear why the wifi would RETURN_ERR, is it possible to call twice?
 * @todo calling twice what is the expected result of the functionality?
 */
void test_generic_wifi_createInitialConfigFiles( void )
{
    int result;
    
    /* Positive */
    result = wifi_createInitialConfigFiles();
    CU_ASSERT_EQUAL( result, RETURN_OK );

    /* Negative */
    result = wifi_createInitialConfigFiles();
    CU_ASSERT_EQUAL( result, RETURN_ERR );
}

/**
 * @brief Tests requirements for L1 testing for wifi_createHostApdConfig
 * 
 * @todo documentation unclear why the wifi would RETURN_ERR, is it possible to call twice?
 * @todo calling twice what is the expected result of the functionality?
 */
void test_generic_wifi_createHostApdConfig( void )
{
    INT result;
    int loopCount=1;
    int index;

    /* Notes: Function needs to adapt based on the number of LED's capable for the system */
    // loopCount = SYSTEM_GET_INT_FROM_PROFILE( "number_of_ap");

    /* Positive Test */
    for ( index=0; index< loopCount; index++ )
    {    
        /* Positive */
        result = wifi_createHostApdConfig(index, TRUE );
        CU_ASSERT_EQUAL( result, RETURN_OK  );

        result = wifi_createHostApdConfig(index, FALSE );
        CU_ASSERT_EQUAL( result, RETURN_OK );

        /* Negative, unclear requirement to generated, from the documentation*/
        /* Call TRUE Twice */
        result = wifi_createHostApdConfig(index, TRUE );
        CU_ASSERT_EQUAL( result, RETURN_ERR );

        result = wifi_createHostApdConfig(index, TRUE );
        CU_ASSERT_EQUAL( result, RETURN_ERR );

        /* Call FALSE Twice */
        result = wifi_createHostApdConfig(index, FALSE );
        CU_ASSERT_EQUAL( result, RETURN_OK );

        result = wifi_createHostApdConfig(index, FALSE );
        CU_ASSERT_EQUAL( result, RETURN_OK );

    }
}

/**
 * @brief Tests requirements for L1 testing for wifi_startHostApd
 * 
 * @todo documentation unclear why the wifi would RETURN_ERR, is it possible to call twice?
 * @todo calling twice what is the expected result of the functionality?
 */
void test_generic_wifi_startHostApd( void )
{
    int result;
    
    /* Positive */
    result = wifi_startHostApd();
    CU_ASSERT_EQUAL( result, RETURN_OK );

    /* Second successive call should also work fine without any errors */
    result = wifi_startHostApd();
    CU_ASSERT_EQUAL( result, RETURN_OK );

    /* Negative, unclear requirement to generated */
}

/**
 * @brief Tests requirements for L1 testing for wifi_stopHostApd
 * 
 * @todo documentation unclear why the wifi would RETURN_ERR, is it possible to call twice?
 * @todo calling twice what is the expected result of the functionality?
 * 
 */
void test_generic_wifi_stopHostApd( void )
{
    int result;
    
    /* Positive */
    result = wifi_stopHostApd();
    CU_ASSERT_EQUAL( result, RETURN_OK );

    /* Second successive call should also work fine without any errors */
    result = wifi_stopHostApd();
    CU_ASSERT_EQUAL( result, RETURN_ERR );

    /* Negative */
}

static CU_pSuite pSuite = NULL;

/**
 * @brief Register the main tests for this module
 * 
 * @return int - 0 on success, otherwise failure
 */
int test_generic_register( void )
{
    /* add a suite to the registry */
    pSuite = CS_TEST_ADD_SUITE("[L1 test_wifi_hal_generic]", &test_generic_init, &test_generic_clean);
    if (NULL == pSuite) 
    {
        return -1;
    }

    CS_TEST_ADD( pSuite, test_generic_wifi_init);
    CS_TEST_ADD( pSuite, test_generic_wifi_reset);
    CS_TEST_ADD( pSuite, test_generic_wifi_setLED);
    CS_TEST_ADD( pSuite, test_generic_wifi_down );
    CS_TEST_ADD( pSuite, test_generic_wifi_factoryReset);
    CS_TEST_ADD( pSuite, test_generic_wifi_createInitialConfigFiles);
    CS_TEST_ADD( pSuite, test_generic_wifi_createHostApdConfig);
    CS_TEST_ADD( pSuite, test_generic_wifi_startHostApd);
    CS_TEST_ADD( pSuite, test_generic_wifi_stopHostApd);

    return 0;
}
#endif // TEST
