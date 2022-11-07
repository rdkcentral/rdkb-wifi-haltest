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

/* Values here should be read from a configuration file, that supports the test */
#define TBC_CONFIG_MAX_APS (1)
#define TBC_CONFIG_MAX_RADIOS (2)
#define TBC_CONFIG_AP_INDEX_OUT_OF_RANGE (-1)
#define TBC_RADIO_INDEX_OUT_OF_RANGE (99)

typedef unsigned char mac_addr_t[6];

void test_telemetry_wifi_getRadioBandUtilization(void)
{
   INT result;
   INT radioIndex = 0;
   INT output_percentage;

   /* Positive */
   for(radioIndex = 0; radioIndex < TBC_CONFIG_MAX_RADIOS; radioIndex++)
   {
      /* TODO: Need to check the value returned by this function */
         result = wifi_getRadioBandUtilization(radioIndex, &output_percentage);
         UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );
   }

   /* Negative */
   result = wifi_getRadioBandUtilization(TBC_RADIO_INDEX_OUT_OF_RANGE, &output_percentage);
   UT_ASSERT_EQUAL( result, WIFI_HAL_ERROR );

   result = wifi_getRadioBandUtilization(0, NULL);
   UT_ASSERT_EQUAL( result, WIFI_HAL_ERROR );
}

void test_telemetry_wifi_getApAssociatedDeviceDiagnosticResult3(void)
{
   INT result;
   INT apIndex = 0;
   wifi_associated_dev3_t *associated_dev_array = NULL;
   UINT output_array_size;

   /* Positive */
   /* TODO: Need to check the value returned by this function */
   result = wifi_getApAssociatedDeviceDiagnosticResult3(apIndex, &associated_dev_array, &output_array_size);
   UT_ASSERT_EQUAL(result, WIFI_HAL_SUCCESS);

   apIndex = 5;

   /* TODO: Need to check the value returned by this function */
   result = wifi_getApAssociatedDeviceDiagnosticResult3(apIndex, &associated_dev_array, &output_array_size);
   UT_ASSERT_EQUAL(result, WIFI_HAL_SUCCESS);

   /* Negative */
   result = wifi_getApAssociatedDeviceDiagnosticResult3(-1, &associated_dev_array, &output_array_size);
   UT_ASSERT_EQUAL( result, WIFI_HAL_ERROR );

   result = wifi_getApAssociatedDeviceDiagnosticResult3(1, &associated_dev_array, NULL);
   UT_ASSERT_EQUAL( result, WIFI_HAL_ERROR );

   result = wifi_getApAssociatedDeviceDiagnosticResult3(0, NULL, &output_array_size);
   UT_ASSERT_EQUAL( result, WIFI_HAL_ERROR );

   free(associated_dev_array);
   associated_dev_array = NULL;
}

/* FIXME: This function wifi_getApAssociatedClientDiagnosticResult is defined for WIFI_HAL_VERSION_3_PHASE2 and WIFI_HAL_VERSION_GE_2_17
*  BUG: Function not implemented in CMXB7 Platform
*/

/* TODO This function will return success only when a MAC of a client connected to this device is sent as a parameter.
*  Note: MAC Address should be in this format: aabbccddeeff; Alphabets in MAC can be in upper or lower case. 
*/
void test_telemetry_wifi_getApAssociatedClientDiagnosticResult(void)
{
   INT result;
   INT apIndex = 0;
   wifi_associated_dev3_t *associated_dev_array = NULL;
   mac_addr_t client_mac;
   //char macAddr[12];

   UINT output_array_size = 0;

   /* TODO: Need to check the value returned by this function */
   result = wifi_getApAssociatedDeviceDiagnosticResult3(apIndex, &associated_dev_array, &output_array_size);
   UT_ASSERT_EQUAL(result, WIFI_HAL_SUCCESS);

   if(associated_dev_array && output_array_size > 0 && result == WIFI_HAL_SUCCESS)
   {
      memcpy(&client_mac, associated_dev_array[0].cli_MACAddress,sizeof(client_mac));
   }
   free(associated_dev_array);
   associated_dev_array = NULL;

   /* Positive */

   /* TODO: Need to check the value returned by this function */
   result = wifi_getApAssociatedClientDiagnosticResult(apIndex, client_mac, associated_dev_array);
   UT_ASSERT_EQUAL(result, WIFI_HAL_SUCCESS);

   /* Negative */
   result = wifi_getApAssociatedClientDiagnosticResult(-1, client_mac, associated_dev_array);
   UT_ASSERT_EQUAL( result, WIFI_HAL_ERROR );

   result = wifi_getApAssociatedClientDiagnosticResult(1, NULL, associated_dev_array);
   UT_ASSERT_EQUAL( result, WIFI_HAL_ERROR );

   result = wifi_getApAssociatedClientDiagnosticResult(0, client_mac, NULL);
   UT_ASSERT_EQUAL( result, WIFI_HAL_ERROR );

   free(associated_dev_array);
   associated_dev_array = NULL;
}

void test_telemetry_wifi_getRadioTrafficStats2(void)
{
   INT result;
   INT radioIndex = 0;
   wifi_radioTrafficStats2_t output_struct;

   /* Positive */
   for(radioIndex = 0; radioIndex < TBC_CONFIG_MAX_RADIOS; radioIndex++)
   {
      /* TODO: Need to check the value returned by this function */
      result = wifi_getRadioTrafficStats2(radioIndex, &output_struct);
      UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );
   }

   /* Negative */
   result = wifi_getRadioTrafficStats2(TBC_RADIO_INDEX_OUT_OF_RANGE, &output_struct);
   UT_ASSERT_EQUAL( result, WIFI_HAL_ERROR );

   result = wifi_getRadioTrafficStats2(radioIndex, NULL);
   UT_ASSERT_EQUAL( result, WIFI_HAL_ERROR );
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