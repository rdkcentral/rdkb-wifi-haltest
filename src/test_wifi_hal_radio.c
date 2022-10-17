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

void test_radio_wifi_getRadioOperatingChannelBandwidth(void)
{
   INT result;
   char channel_bandwidth[10] = {'\0'};
   INT radioIndex = 0;

   /* Positive */
   for (radioIndex=0; radioIndex < TBC_CONFIG_MAX_RADIOS; radioIndex++)
   {
      /* TODO: Need to check the value returned by this function */
      result = wifi_getRadioOperatingChannelBandwidth(radioIndex, channel_bandwidth);
      UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS);
   }

   /* Negative */
   /* FIXME: Need to check when this function will return WIFI_HAL_INVALID_ARGUMENTS */
   result = wifi_getRadioOperatingChannelBandwidth(TBC_RADIO_INDEX_OUT_OF_RANGE, channel_bandwidth);
   UT_ASSERT_EQUAL( result, WIFI_HAL_ERROR );

   result = wifi_getRadioOperatingChannelBandwidth(-1, channel_bandwidth);
   UT_ASSERT_EQUAL( result, WIFI_HAL_ERROR );

   result = wifi_getRadioOperatingChannelBandwidth(2, channel_bandwidth);
   UT_ASSERT_EQUAL( result, WIFI_HAL_ERROR );

   result = wifi_getRadioOperatingChannelBandwidth(0, NULL);
   UT_ASSERT_EQUAL( result, WIFI_HAL_ERROR );
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

void test_radio_wifi_setRadioOperatingParameters(void)
{
   INT result;
   INT radioIndex = 0;
   wifi_radio_operationParam_t operationParam;

   /* Positive */
   for (radioIndex = 0; radioIndex < TBC_CONFIG_MAX_RADIOS; radioIndex++)
   {
      result = wifi_getRadioOperatingParameters(radioIndex, &operationParam);
      UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );

      operationParam.channelWidth = 2;

      result = wifi_setRadioOperatingParameters(radioIndex, &operationParam);
      UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );
   }

   /* Negative */
   for (radioIndex = 0; radioIndex < TBC_CONFIG_MAX_RADIOS; radioIndex++)
   {
      result = wifi_getRadioOperatingParameters(radioIndex, &operationParam);
      UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );

      operationParam.channelWidth = 32;

      result = wifi_setRadioOperatingParameters(radioIndex, &operationParam);
      UT_ASSERT_EQUAL( result, WIFI_HAL_ERROR );
   }
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
