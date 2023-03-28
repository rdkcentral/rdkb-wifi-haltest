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

#include <ut.h>
#include <ut_log.h>
#include "test_utils.h"

/* Values here should be read from a configuration file, that supports the test */
#define TBC_NEGATIVE_INDEX_OUT_OF_RANGE (-1)
#define TBC_POSITIVE_INDEX_OUT_OF_RANGE (99)


/**
 * @brief Tests requirements for L1 testing wifi_getRadioBandUtilization
 *
 * Test Coverage: Positive and Negative Scenarios
 *
 * @retval WIFI_HAL_SUCCESS             -> tested
 * @retval WIFI_HAL_INVALID_ARGUMENTS   -> tested
 *
 * @Note hal api is Synchronous
 */
void test_telemetry_wifi_getRadioBandUtilization(void)
{
   UT_LOG("Entering getRadioBandUtilization... ");

   int result = 0;
   int radioIndex = 0;
   unsigned int numRadios = 0;
   int returnStatus = 0;
   int output_percentage = 0;

    /* Get the number of radios applicable */
    returnStatus = test_utils_getMaxNumberOfRadio(&numRadios);

    if (returnStatus == 0)
    {
        UT_LOG("Number of Radios : %u", numRadios);

        /* Postive Test WIFI_HAL_SUCCESS */
        /* Passing valid radio index, valid Band Utilization and expecting the API to return success */
        UT_LOG("Test Case 1");

        for (radioIndex = 0; radioIndex < numRadios; radioIndex++)
        {
            result = wifi_getRadioBandUtilization(radioIndex, &output_percentage);
            UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );
            UT_LOG("Passing valid Band Utilization for radio index %d returns : %d", radioIndex, result);

            if (output_percentage >= 0 && output_percentage <= 100)
            {
               UT_LOG("Band Utilization is %d for radio %d which is a valid Band Utilization percentage", output_percentage, radioIndex);
               UT_PASS("Band Utilization validation success");
            }
            else
            {
               UT_LOG("Band Utilization is %d for radio %d which is not a valid Band Utilization percentage", output_percentage, radioIndex);
               UT_FAIL("Band Utilization validation fail");
            }
        }

        /* Negative Test WIFI_HAL_INVALID_ARGUMENTS */
        /* Passing invalid radio index, valid Band Utilization and expecting the API to return failure */
        UT_LOG("Test Case 2");
        result = wifi_getRadioBandUtilization(TBC_POSITIVE_INDEX_OUT_OF_RANGE, &output_percentage);
        UT_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS);
        UT_LOG("Passing an out of range positive radio index %d and valid Band Utilization percentage returns : %d", TBC_POSITIVE_INDEX_OUT_OF_RANGE, result);

        /* Negative Test WIFI_HAL_INVALID_ARGUMENTS */
        /* Passing invalid radio index, valid Band Utilization and expecting the API to return failure */
        UT_LOG("Test Case 3");
        result = wifi_getRadioBandUtilization(TBC_NEGATIVE_INDEX_OUT_OF_RANGE, &output_percentage);
        UT_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS);
        UT_LOG("Passing an out of range negative radio index %d and valid Band Utilization percentage returns : %d", TBC_NEGATIVE_INDEX_OUT_OF_RANGE, result);

        /* Negative Test WIFI_HAL_INVALID_ARGUMENTS */
        /* Passing NULL to Band Utilization and expecting the API to return failure */
        UT_LOG("Test Case 4");
        for (radioIndex = 0; radioIndex < numRadios; radioIndex++)
        {
            result = wifi_getRadioBandUtilization(radioIndex, NULL);
            UT_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS);
            UT_LOG("Passing NULL as Band Utilization for radio %d returns : %d", radioIndex, result);
        }

    }
    else
    {
        UT_LOG("Unable to retrieve the number of radios from HalCapability");
    }

    UT_LOG("Exiting getRadioBandUtilization... ");
    return;

}

/**
 * @brief Tests requirements for L1 testing wifi_getApAssociatedDeviceDiagnosticResult3
 *
 * Test Coverage: Positive and Negative Scenarios
 *
 * @retval WIFI_HAL_SUCCESS             -> tested
 * @retval WIFI_HAL_INVALID_ARGUMENTS   -> tested
 *
 * @Note hal api is Synchronous
 */
void test_telemetry_wifi_getApAssociatedDeviceDiagnosticResult3(void)
{
   UT_LOG("Entering getApAssociatedDeviceDiagnosticResult3... ");

   int result = 0;
   int index = 0;
   unsigned int numRadios = 0;
   int returnStatus = 0;
   wifi_associated_dev3_t *associated_dev_array = NULL;
   uint output_array_size = 0;
   char *macstr = "000000000000";
   wifi_associated_dev3_t dev;
   int * apIndex = NULL;

   /* To get number of supported radios*/
   returnStatus = test_utils_getMaxNumberOfRadio(&numRadios);

   if (returnStatus == 0)
   {
       UT_LOG("Number of Radios : %u", numRadios);

       /* To get apIndex for supported number of radios */
       apIndex = (int *)malloc( sizeof(int) * numRadios );
       if (apIndex != NULL)
       {
          returnStatus = test_utils_getApIndices(numRadios, apIndex, PRIVATE);
          if(returnStatus == 0)
          {
            /* Postive Test WIFI_HAL_SUCCESS */
            /* Passing valid apIndex , valid client mac buffer and valid array size and expecting the API to return success */
            UT_LOG("Test Case 1");
            for (index = 0; index < numRadios; index++)
            {
              result = wifi_getApAssociatedDeviceDiagnosticResult3(apIndex[index], &associated_dev_array, &output_array_size);
              UT_ASSERT_EQUAL(result, WIFI_HAL_SUCCESS);
              UT_LOG("Passing valid apIndex %d with valid client mac buffer and array size for radio %d returns %d", apIndex[index], index, result);
              if (result == 0)
              {
                /* Checking with client mac buffer as NULL and array size as 0 */
                if((associated_dev_array == NULL) && (output_array_size == 0))
                {
                 UT_LOG("Output Array size is %d " , output_array_size);
                 UT_PASS("Device Diagnostic Result validation is success");
                }
                else
                {
                 UT_LOG("Output Array size %d ", output_array_size);
                 UT_FAIL("Device Diagnostic Result validation fail");
                }
              }
            }

           /* Negative Test WIFI_HAL_INVALID_ARGUMENTS */
           /* Passing an invalid positive out of range apIndex, valid client mac buffer and valid array size and expecting the API to return failure */
          UT_LOG("Test Case 2");
          result = wifi_getApAssociatedDeviceDiagnosticResult3(TBC_POSITIVE_INDEX_OUT_OF_RANGE, &associated_dev_array, &output_array_size);
          UT_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS);
          UT_LOG("Passing an invalid positive out of range apIndex %d with valid client mac buffer and valid size returns %d", TBC_POSITIVE_INDEX_OUT_OF_RANGE, result);

          /* Negative Test WIFI_HAL_INVALID_ARGUMENTS */
          /* Passing an invalid negative out of range apIndex, valid client mac buffer and valid array size and expecting the API to return failure */
          UT_LOG("Test Case 3");
          result = wifi_getApAssociatedDeviceDiagnosticResult3(TBC_NEGATIVE_INDEX_OUT_OF_RANGE, &associated_dev_array, &output_array_size);
          UT_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS);
          UT_LOG("Passing an invalid negative out of range apIndex %d with valid client mac buffer and valid size returns %d", TBC_NEGATIVE_INDEX_OUT_OF_RANGE, result);

          /* Negative Test WIFI_HAL_INVALID_ARGUMENTS */
          /* Passing valid apIndex, invalid client mac buffer and array size as 1 and expecting the API to return failure */
          UT_LOG("Test Case 4");
          for (index = 0; index < numRadios; index++)
          {
              output_array_size = 1;
              sscanf(macstr, "%02hhx:%02hhx:%02hhx:%02hhx:%02hhx:%02hhx", &dev.cli_MACAddress[0], &dev.cli_MACAddress[1], &dev.cli_MACAddress[2], &dev.cli_MACAddress[3], &dev.cli_MACAddress[4], &dev.cli_MACAddress[5]);
              associated_dev_array = &dev;
              result = wifi_getApAssociatedDeviceDiagnosticResult3(apIndex[index], &associated_dev_array, &output_array_size);
              UT_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS);
              UT_LOG("Passing an valid apIndex %d with invalid client mac buffer and array size as 1 returns  %d", apIndex[index], result);
          }

          /* Negative Test WIFI_HAL_INVALID_ARGUMENTS */
          /* Passing an valid apIndex, valid client mac buffer and NULL array size and expecting the API to return failure */
          UT_LOG("Test Case 5");
          for (index = 0; index < numRadios; index++)
          {
              result = wifi_getApAssociatedDeviceDiagnosticResult3(apIndex[index], &associated_dev_array, NULL);
              UT_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS);
              UT_LOG("Passing an valid apIndex %d with valid client buffer and NULL size returns %d", apIndex[index], result);
          }

        }
        else
        {

              UT_LOG("Unable to retrieve the access point indices");
        }
	free(apIndex);
    }
    else
    {
	    UT_LOG("Malloc operation failed");
    }
   }
   else
   {
        UT_LOG("Unable to retrieve the number of radios from HalCapability");
   }

   UT_LOG("Exiting getApAssociatedDeviceDiagnosticResult3... ");
   return;

}

/* FIXME: This function wifi_getApAssociatedClientDiagnosticResult is defined for WIFI_HAL_VERSION_3_PHASE2 and WIFI_HAL_VERSION_GE_2_17
*  BUG: Function not implemented in CMXB7 Platform
*/

/* TODO This function will return success only when a MAC of a client connected to this device is sent as a parameter.
*  Note: MAC Address should be in this format: aabbccddeeff; Alphabets in MAC can be in upper or lower case.
*/
/**
 * @brief Tests requirements for L1 testing wifi_getApAssociatedClientDiagnosticResult
 *
 * Test Coverage: Positive and Negative Scenarios
 *
 * @retval WIFI_HAL_INVALID_ARGUMENTS   -> tested
 *
 * @Note hal api is Synchronous
 */
void test_telemetry_wifi_getApAssociatedClientDiagnosticResult(void)
{
     UT_LOG("Entering getApAssociatedClientDiagnosticResult... ");

     int returnStatus = 0;
     unsigned int numRadios = 0;
     int * apIndex = NULL;
     int index = 0;
     wifi_associated_dev3_t associated_dev_array;
     int result = 0;
     mac_address_t client_mac = {'\0'};
     char macstr[] = "000000000000";


     /* Get the number of radios applicable */
     returnStatus = test_utils_getMaxNumberOfRadio(&numRadios);
     if (returnStatus == 0)
     {
           UT_LOG("Number of Radios : %u", numRadios);
           /* To get apIndex for supported number of radios */
           apIndex = (int *)malloc( sizeof(int) * numRadios );
           if (apIndex != NULL)
	   {
             returnStatus = test_utils_getApIndices(numRadios, apIndex, PRIVATE);
             if(returnStatus == 0)
             {

                     /* Postive Test WIFI_HAL_SUCCESS */
                     /* Passing valid apIndex , valid client mac and valid device array buffer and expecting the API to return success */
                     /* To-Do : To be implemented Later
                     UT_LOG("Test Case 1");
                     for (index = 0; index < numRadios; index++)
                     {
                             result = wifi_getApAssociatedClientDiagnosticResult(apIndex[index], client_mac, &associated_dev_array);
                             UT_ASSERT_EQUAL(result, WIFI_HAL_SUCCESS);
                             UT_LOG("Passing valid apIndex %d with valid client mac and array buffer returns %d", apIndex[index], result);
                             if (result == 0)
                             {
                                     UT_LOG("Mac address of client is %02X:%02X:%02X:%02X:%02X:%02X with valid apIndex  returns %d", client_mac[0],client_mac[1],client_mac[2],client_mac[3],client_mac[4],client_mac[5], result);
                                     UT_PASS("Client mac validation is success");
                             }
                     }
                     */

		     /* Negative Test WIFI_HAL_INVALID_ARGUMENTS */
                     /* Passing an invalid positive out of range apIndex, valid client mac and valid device array buffer and expecting the API to return failure */
                     UT_LOG("Test Case 2");
                     memset(&associated_dev_array, 0, sizeof(wifi_associated_dev3_t));
                     result = wifi_getApAssociatedClientDiagnosticResult(TBC_POSITIVE_INDEX_OUT_OF_RANGE, client_mac, &associated_dev_array);
		     UT_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS );
                     UT_LOG("Passing an invalid apIndex %d with valid client mac and valid device array buffer returns %d", TBC_POSITIVE_INDEX_OUT_OF_RANGE, result);

                     /* Negative Test WIFI_HAL_INVALID_ARGUMENTS */
                     /* Passing an invalid negative out of range apIndex, valid client mac and valid device array buffer and expecting the API to return failure */
                     UT_LOG("Test Case 3");
                     memset(&associated_dev_array, 0, sizeof(wifi_associated_dev3_t));
                     result = wifi_getApAssociatedClientDiagnosticResult(TBC_NEGATIVE_INDEX_OUT_OF_RANGE, client_mac, &associated_dev_array);
		     UT_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS );
                     UT_LOG("Passing an invalid apIndex %d with valid client mac and valid device array buffer returns %d", TBC_NEGATIVE_INDEX_OUT_OF_RANGE, result);

                     /* Negative Test WIFI_HAL_INVALID_ARGUMENTS */
                     /* Passing apIndex as 1 , NULL client mac and valid device array buffer and expecting the API to return failure */
                     UT_LOG("Test Case 4");
                     index=1;
                     memset(&associated_dev_array, 0, sizeof(wifi_associated_dev3_t));
                     result = wifi_getApAssociatedClientDiagnosticResult(apIndex[index], NULL, &associated_dev_array);
		     UT_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS );
                     UT_LOG("Passing valid apIndex %d with NULL client mac with valid array buffer  returns %d", apIndex[index], result);

                     /* Negative Test WIFI_HAL_INVALID_ARGUMENTS */
                     /* Passing apIndex as 1 , valid client mac and NULL array buffer and expecting the API to return failure */
                     UT_LOG("Test Case 5");
                     index=1;
                     memset(&associated_dev_array, 0, sizeof(wifi_associated_dev3_t));
                     result = wifi_getApAssociatedClientDiagnosticResult(apIndex[index], client_mac, NULL);
		     UT_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS );
                     UT_LOG("Passing valid apIndex %d with valid client mac and NULL array buffer returns %d", apIndex[index], result);

                     /* Negative Test WIFI_HAL_INVALID_ARGUMENTS */
                     /* Passing valid apIndex, invalid client mac and NULL array buffer and expecting the API to return failure */
                     UT_LOG("Test Case 6");
                     for (index = 0; index < numRadios; index++)
                     {
                             memset(&associated_dev_array, 0, sizeof(wifi_associated_dev3_t));
                             sscanf(macstr, "%02hhx:%02hhx:%02hhx:%02hhx:%02hhx:%02hhx", &client_mac[0], &client_mac[1], &client_mac[2], &client_mac[3], &client_mac[4], &client_mac[5]);
                             result = wifi_getApAssociatedClientDiagnosticResult(apIndex[index], client_mac, NULL);
			     UT_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS );
                             UT_LOG("Passing valid apIndex %d with invalid client mac %02hhx:%02hhx:%02hhx:%02hhx:%02hhx:%02hhx with NULL array buffer returns %d", apIndex[index], client_mac[0],client_mac[1],client_mac[2],client_mac[3],client_mac[4],client_mac[5], result);
                     }
             }
             else
             {
                     UT_LOG("Unable to retrieve the access point indices");
             }
	     free(apIndex);
       }
       else
       {
	     UT_LOG("Malloc operation failed");
       }
     }
     else
     {
             UT_LOG("Unable to retrieve the number of radios from HalCapability");
     }

     UT_LOG("Exiting getApAssociatedClientDiagnosticResult...");
     return;
}


/**
 * @brief Tests requirements for L1 testing wifi_getRadioTrafficStats2
 *
 * Test Coverage: Positive and Negative Scenarios
 *
 * @retval WIFI_HAL_SUCCESS             -> tested
 * @retval WIFI_HAL_INVALID_ARGUMENTS   -> tested
 *
 * @Note hal api is Synchronous
 */
void test_telemetry_wifi_getRadioTrafficStats2(void)
{
   UT_LOG("Entering getRadioTrafficStats2... ");

   int result = 0;
   int radioIndex = 0;
   unsigned int numRadios = 0;
   int returnStatus = 0;
   wifi_radioTrafficStats2_t output_struct;

   /* Get the number of radios applicable */
   returnStatus = test_utils_getMaxNumberOfRadio(&numRadios);

   if (returnStatus == 0)
   {
       UT_LOG("Number of Radios : %u", numRadios);

       /* Postive Test WIFI_HAL_SUCCESS */
       /* Passing valid radio index, valid traffic stats and expecting the API to return success */
        UT_LOG("Test Case 1");

        for (radioIndex = 0; radioIndex < numRadios; radioIndex++)
        {
            result = wifi_getRadioTrafficStats2(radioIndex, &output_struct);
            UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );
            UT_LOG("Passing valid traffic stats for radio index %d returns : %d", radioIndex, result);

            if ( result == 0)
            {
               UT_LOG("Traffic stats for radio %d are BytesSent = %ld, BytesReceived = %ld, PacketsSent = %ld, PacketsReceived = %ld, ErrorsSent = %ld, ErrorsReceived = %ld, DiscardPacketsSent = %ld, DiscardPacketsReceived = %ld, PLCPErrorCount = %ld, FCSErrorCount = %ld, InvalidMACCount = %ld, PacketsOtherReceived = %ld, NoiseFloor = %d, ChannelUtilization = %ld, ActivityFactor = %d, CarrierSenseThreshold_Exceeded = %d, RetransmissionMetirc = %d, MaximumNoiseFloorOnChannel = %d, MinimumNoiseFloorOnChannel = %d, MedianNoiseFloorOnChannel = %d, radio_StatisticsStartTime = %ld", radioIndex, output_struct.radio_BytesSent, output_struct.radio_BytesReceived, output_struct.radio_PacketsSent, output_struct.radio_PacketsReceived, output_struct.radio_ErrorsSent, output_struct.radio_ErrorsReceived, output_struct.radio_DiscardPacketsSent, output_struct.radio_DiscardPacketsReceived, output_struct.radio_PLCPErrorCount, output_struct.radio_FCSErrorCount, output_struct.radio_InvalidMACCount, output_struct.radio_PacketsOtherReceived, output_struct.radio_NoiseFloor, output_struct.radio_ChannelUtilization, output_struct.radio_ActivityFactor, output_struct.radio_CarrierSenseThreshold_Exceeded, output_struct.radio_RetransmissionMetirc, output_struct.radio_MaximumNoiseFloorOnChannel, output_struct.radio_MinimumNoiseFloorOnChannel, output_struct.radio_MedianNoiseFloorOnChannel, output_struct.radio_StatisticsStartTime);
               UT_PASS("Radio Traffic stats validation success");
            }
            else
            {
               UT_LOG("Traffic stats for radio %d are BytesSent = %ld, BytesReceived = %ld, PacketsSent = %ld, PacketsReceived = %ld, ErrorsSent = %ld, ErrorsReceived = %ld, DiscardPacketsSent = %ld, DiscardPacketsReceived = %ld, PLCPErrorCount = %ld, FCSErrorCount = %ld, InvalidMACCount = %ld, PacketsOtherReceived = %ld, NoiseFloor = %d, ChannelUtilization = %ld, ActivityFactor = %d, CarrierSenseThreshold_Exceeded = %d, RetransmissionMetirc = %d, MaximumNoiseFloorOnChannel = %d, MinimumNoiseFloorOnChannel = %d, MedianNoiseFloorOnChannel = %d, radio_StatisticsStartTime = %ld", radioIndex, output_struct.radio_BytesSent, output_struct.radio_BytesReceived, output_struct.radio_PacketsSent, output_struct.radio_PacketsReceived, output_struct.radio_ErrorsSent, output_struct.radio_ErrorsReceived, output_struct.radio_DiscardPacketsSent, output_struct.radio_DiscardPacketsReceived, output_struct.radio_PLCPErrorCount, output_struct.radio_FCSErrorCount, output_struct.radio_InvalidMACCount, output_struct.radio_PacketsOtherReceived, output_struct.radio_NoiseFloor, output_struct.radio_ChannelUtilization, output_struct.radio_ActivityFactor, output_struct.radio_CarrierSenseThreshold_Exceeded, output_struct.radio_RetransmissionMetirc, output_struct.radio_MaximumNoiseFloorOnChannel, output_struct.radio_MinimumNoiseFloorOnChannel, output_struct.radio_MedianNoiseFloorOnChannel, output_struct.radio_StatisticsStartTime);
               UT_FAIL("Radio Traffic stats validation fail");
            }

        }

        /* Negative Test WIFI_HAL_INVALID_ARGUMENTS */
        /* Passing invalid radio index, valid traffic stats and expecting the API to return failure */
        UT_LOG("Test Case 2");
        result = wifi_getRadioTrafficStats2(TBC_POSITIVE_INDEX_OUT_OF_RANGE, &output_struct);
        UT_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS);
        UT_LOG("Passing an out of range positive radio index %d and valid traffic stats returns : %d", TBC_POSITIVE_INDEX_OUT_OF_RANGE, result);

        /* Negative Test WIFI_HAL_INVALID_ARGUMENTS */
        /* Passing invalid radio index, valid traffic stats and expecting the API to return failure */
        UT_LOG("Test Case 3");
        result = wifi_getRadioTrafficStats2(TBC_NEGATIVE_INDEX_OUT_OF_RANGE, &output_struct);
        UT_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS);
        UT_LOG("Passing an out of range negative radio index %d and valid traffic stats returns : %d", TBC_NEGATIVE_INDEX_OUT_OF_RANGE, result);

        /* Negative Test WIFI_HAL_INVALID_ARGUMENTS */
        /* Passing NULL to traffic stats, valid radio index and expecting the API to return failure */
        UT_LOG("Test Case 4");
        for (radioIndex = 0; radioIndex < numRadios; radioIndex++)
        {
            result = wifi_getRadioTrafficStats2(radioIndex, NULL);
            UT_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS);
            UT_LOG("Passing NULL as traffic stats for radio %d returns : %d", radioIndex, result);
        }

    }
    else
    {
        UT_LOG("Unable to retrieve the number of radios from HalCapability");
    }

    UT_LOG("Exiting getRadioTrafficStats2... ");
    return;

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
