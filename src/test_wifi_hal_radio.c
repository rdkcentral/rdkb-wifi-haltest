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
#include <Logger.h>

#include "config_parser.h"
#include "test_utils.h"

/* Values here should be read from a configuration file, that supports the test */
#define TBC_CONFIG_MAX_RADIOS (2)
#define TBC_RADIO_INDEX_OUT_OF_RANGE (99)

#define TBC_RADIO_MAX_BW (4)
#define TBC_CONFIG_MAX_BW (7)

void test_radio_wifi_getRadioTransmitPower(void)
{
   INT result;
   ULONG output_ulong = 0;
   INT radioIndex = 0;

   /* Positive */
   for (radioIndex=0;radioIndex< TBC_CONFIG_MAX_RADIOS;radioIndex++)
   {
      /* TODO: Need to check the value returned by this function */
      result = wifi_getRadioTransmitPower(radioIndex, &output_ulong);
      UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS);
   }

   /* Negative */
   result = wifi_getRadioTransmitPower(TBC_RADIO_INDEX_OUT_OF_RANGE, &output_ulong);
   UT_ASSERT_EQUAL( result, WIFI_HAL_ERROR );

   result = wifi_getRadioTransmitPower(-1, &output_ulong);
   UT_ASSERT_EQUAL( result, WIFI_HAL_ERROR );

   result = wifi_getRadioTransmitPower(2, &output_ulong);
   UT_ASSERT_EQUAL( result, WIFI_HAL_ERROR );

   result = wifi_getRadioTransmitPower(0, NULL);
   UT_ASSERT_EQUAL( result, WIFI_HAL_ERROR );
}

/**
 * @brief Tests requirements for L1 testing wifi_getRadioOperatingChannelBandwidth()
 *
 * Test Coverage: Positive and Negative Scenarios
 *
 * @retval WIFI_HAL_SUCCESS             -> tested
 * @retval WIFI_HAL_INVALID_ARGUMENTS   -> tested
 *
 * @Note hal api is Synchronous
 */
void test_radio_wifi_getRadioOperatingChannelBandwidth(void)
{

    UT_LOG("Entering getRadioOperatingChannelBandwidth...");

    int result = 0;
    char channel_bandwidth[10] = {'\0'};
    int radioIndex = 0;
    unsigned int numRadios = 0;
    int returnStatus = 0;
    int radioIndex_outOfRange = 99;
    int radioIndex_negative = -1;

    /* Get the number of radios applicable */
    returnStatus = test_utils_getMaxNumberOfRadio(&numRadios);

    if (returnStatus == 0)
    {
        UT_LOG("Number of Radios : %u", numRadios);

        /* Postive Test WIFI_HAL_SUCCESS */
        /* Passing valid channel bandwidth buffer and expecting the API to return success */
        UT_LOG("Test Case 1");

        for (radioIndex = 0; radioIndex < numRadios; radioIndex++)
        {
            result = wifi_getRadioOperatingChannelBandwidth(radioIndex, channel_bandwidth);
            UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS);

            UT_LOG("Passing valid buffer as channel bandwidth for radio %d returns : %d", radioIndex, result);

            if (NULL != strstr(channel_bandwidth, "MHz"))
            {
                UT_LOG("Channel Bandwidth of radio %d is %s which is a valid bandwidth", radioIndex, channel_bandwidth); 
                UT_PASS("Channel Bandwidth validation success");				
            }
            else
            {
                UT_LOG("Channel Bandwidth of radio %d is %s which is NOT a valid bandwidth", radioIndex, channel_bandwidth); 
                UT_FAIL("Channel Bandwidth validation fail");
            }
        }

        /* Negative Test WIFI_HAL_INVALID_ARGUMENTS */
        /* Passing NULL Buffer as input to channel bandwidth and expecting the API to return failure */
        UT_LOG("Test Case 2");

        for (radioIndex = 0; radioIndex < numRadios; radioIndex++)
        {
            result = wifi_getRadioOperatingChannelBandwidth(radioIndex, NULL);
            UT_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS);

            UT_LOG("Passing NULL buffer as channel bandwidth for radio %d returns : %d", radioIndex, result);
        }

        /* Negative Test WIFI_HAL_INVALID_ARGUMENTS */
        /* Passing a positive out of range radio index, valid channel bandwidth buffer and expecting the API to return failure */
        UT_LOG("Test Case 3");

        result = wifi_getRadioOperatingChannelBandwidth(radioIndex_outOfRange, channel_bandwidth);
        UT_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS);

        UT_LOG("Passing an out of range positive radio index %d and valid buffer as channel bandwidth returns : %d", radioIndex_outOfRange, result);

        /* Negative Test WIFI_HAL_INVALID_ARGUMENTS */
        /* Passing a negative radio index, valid channel bandwidth buffer and expecting the API to return failure */
        UT_LOG("Test Case 4");

        result = wifi_getRadioOperatingChannelBandwidth(radioIndex_negative, channel_bandwidth);
        UT_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS);

        UT_LOG("Passing negative radio index %d and valid buffer as channel bandwidth returns : %d", radioIndex_negative, result);

        /* Negative Test WIFI_HAL_INVALID_ARGUMENTS */
        /* Passing an invalid radio index, channel bandwidth as NULL buffer and expecting the API to return failure */
        UT_LOG("Test Case 5");

        result = wifi_getRadioOperatingChannelBandwidth(radioIndex_outOfRange, NULL);
        UT_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS);

        UT_LOG("Passing invalid radio index %d and NULL buffer as channel bandwidth returns : %d", radioIndex_outOfRange, result);
    }
    else
    {
        UT_LOG("Unable to retrieve the number of radios from HalCapability");
    }

    UT_LOG("Exiting getRadioOperatingChannelBandwidth...");
    return;

}

/* TODO: Need to add other instances for this function like stubs*/
void test_radio_wifi_getRadioOperatingParameters(void)
{
   INT result;
   INT radioIndex = 0;
   wifi_radio_operationParam_t operationParam;

   /* Positive */
   for (radioIndex=0; radioIndex < TBC_CONFIG_MAX_RADIOS; radioIndex++)
   {
      /* TODO: Need to check the value returned by this function */
      result = wifi_getRadioOperatingParameters(radioIndex, &operationParam);
      UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS);
   }

   /* Negative */
   result = wifi_getRadioOperatingParameters(-1, &operationParam);
   UT_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS );

   result = wifi_getRadioOperatingParameters(2, &operationParam);
   UT_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS );

   /* FIXME: Need to check whether it will return WIFI_HAL_INVALID_ARGUMENTS */
   result = wifi_getRadioOperatingParameters(0, NULL);
   UT_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS );
}

/**
 * @brief Tests requirements for L1 testing wifi_setRadioOperatingParameters()
 *
 * Test Coverage: Positive and Negative Scenarios
 *
 * @retval WIFI_HAL_SUCCESS             -> tested
 * @retval WIFI_HAL_INVALID_ARGUMENTS   -> tested
 *
 * @Note hal api is Synchronous
 */
void test_radio_wifi_setRadioOperatingParameters(void)
{
    UT_LOG("Entering setRadioOperatingParameters...");

    int result = 0;
    unsigned int numRadios = 0;
    int returnStatus = 0;
    int radioIndex = 0;
    wifi_radio_operationParam_t operationParam;

    /* Get the number of radios applicable */
    returnStatus = test_utils_getMaxNumberOfRadio(&numRadios);

    if (returnStatus == 0)
    {
        UT_LOG("Number of Radios : %u", numRadios);

        /* Postive Test WIFI_HAL_SUCCESS */
        /* Setting valid radio operating parameters and expecting the API to return success */
        UT_LOG("Test Case 1");

        for (radioIndex = 0; radioIndex < numRadios; radioIndex++)
        {
            /* Get the radio configuration */
            returnStatus = get_radio_config(radioIndex, &operationParam); 
            if (returnStatus == 0)
            {
                UT_LOG("get_radio_config for radio %d returns : %d", radioIndex, returnStatus);

                result = wifi_setRadioOperatingParameters(radioIndex, &operationParam);
                UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );

                UT_LOG("Setting valid operating parameters for radio %d returns : %d", radioIndex, result);
            }
            else
            {
                UT_LOG("Unable to parse the radio config file");
            }	
        }			

        /* Negative Test WIFI_HAL_INVALID_ARGUMENTS */
        /* Passing NULL Buffer as input to operating parameter structure and expecting the API to return failure */
        UT_LOG("Test Case 2");

        for (radioIndex = 0; radioIndex < numRadios; radioIndex++)
        {
            result = wifi_setRadioOperatingParameters(radioIndex, NULL);
            UT_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS );

            UT_LOG("Setting NULL buffer as operating parameter structure for radio %d returns : %d", radioIndex, result);
        }
    }
    else
    {
        UT_LOG("Unable to retrieve the number of radios from HalCapability");
    }

    UT_LOG("Exiting setRadioOperatingParameters...");
    return;

}

#if 0 /* #FIXME: Requires review, this is not defined in the wifi_hal, but maybe in later revisions */
static INT test_wifi_scanResults_callback(INT radioIndex)
{
   (void)radioIndex;
   /* Should not be triggered during the test*/
   UT_FAIL("This function isn't expected to be triggered");
   return (INT)0;
}

void test_radio_wifi_scanResults_callback_register(void)
{

   /* Positive */
   wifi_scanResults_callback_register(&test_wifi_scanResults_callback);
   wifi_scanResults_callback_register(NULL);

   /* Negative - N/A*/
}
#endif

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
   /* #FIXME: Added this function as it was present in wifi_hal_radio.h but not in test_wifi_hal_radio.c */
   UT_add_test( pSuite, "wifi_getRadioOperatingParameters", test_radio_wifi_getRadioOperatingParameters);
   UT_add_test( pSuite, "wifi_setRadioOperatingParameters", test_radio_wifi_setRadioOperatingParameters);
   /* FIXME: Commented UT for wifi_scanResults_callback_register as the function is not present in wifi_hal.c in any of the platforms*/
   //UT_add_test( pSuite, "wifi_scanResults_callback_register)", test_radio_wifi_scanResults_callback_register);

  return 0;
}
