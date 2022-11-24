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
#include "config_parser.h"
#include "test_utils.h"
#include "api_translator.h"

#include <ut.h>
#include <ut_log.h>

/* Values here should be read from a configuration file, that supports the test */
#define TBC_CONFIG_MAX_APS (1)
#define TBC_CONFIG_MAX_RADIOS (2)
#define TBC_NEGATIVE_INDEX_OUT_OF_RANGE (-1)
#define TBC_POSITIVE_INDEX_OUT_OF_RANGE (99)

/**
 * @brief Tests requirements for L1 testing wifi_getApAssociatedDevice()
 *
 * Test Coverage: Negative Scenarios
 *
 * @retval WIFI_HAL_INVALID_ARGUMENTS   -> tested
 *
 * @Note hal api is Synchronous
 */
void test_wifi_getApAssociatedDevice(void)
{
    UT_LOG("Entering getApAssociatedDevice...");

    int result = 0;
    int iteration = 0;
    int * apIndices = NULL;
    int apIndex_negative = -1;
    int apIndex_OutOfRange = 99;
    int returnStatus = 0;
    mac_address_t opDeviceMacAddArray[32];
    unsigned int maxNumDevices = sizeof(opDeviceMacAddArray)/sizeof(mac_address_t);
    unsigned int maxNumDevices_invalid = 0;
    unsigned int returnedOpNumOfDevices = 0;
    unsigned int numRadios = 0;

    /* Get the number of radios applicable */
    returnStatus = test_utils_getMaxNumberOfRadio(&numRadios);

    if (returnStatus == 0)
    {
        UT_LOG("Number of Radios : %u", numRadios);

        /* Allocate memory to store the apIndices */
        apIndices = (int *)malloc( sizeof(int) * numRadios );

        if (apIndices != NULL)
        {
            /* Get the list of private access points corresponding to each of the supported radios */
            returnStatus = test_utils_getApIndices(numRadios, apIndices, PRIVATE);

            if (returnStatus == 0)
            {
                UT_LOG("Private AP Indices for the supported radios retrieved");

                /* Negative Test WIFI_HAL_INVALID_ARGUMENTS */
                /* Passing valid apIndex, valid buffer to opDeviceMacAddArray, valid maxNumDevices and NULL buffer to opNumOfDevices and expecting the API to return failure*/
                UT_LOG("Test Case 1");

                for (iteration = 0; iteration < numRadios; iteration ++)
                {
                    result = wifi_getApAssociatedDevice(apIndices[iteration], &opDeviceMacAddArray[0], maxNumDevices, NULL);
                    UT_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS );

                    UT_LOG("Setting valid buffer to opDeviceMacAddArray, maxNumDevices as %d, NULL buffer to opNumOfDevices for apIndex %d returns : %d", maxNumDevices, apIndices[iteration], result);
                }

                /* Negative Test WIFI_HAL_INVALID_ARGUMENTS */
                /* Passing valid apIndex, valid buffer to opDeviceMacAddArray, maxNumDevices as 0 and valid buffer to opNumOfDevices and expecting the API to return failure*/
                UT_LOG("Test Case 2");

                for (iteration = 0; iteration < numRadios; iteration ++)
                {
                    result = wifi_getApAssociatedDevice(apIndices[iteration], &opDeviceMacAddArray[0], maxNumDevices_invalid, &returnedOpNumOfDevices);
                    UT_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS );

                    UT_LOG("Setting valid buffer to opDeviceMacAddArray, maxNumDevices as %d, valid buffer to opNumOfDevices for apIndex %d returns : %d", maxNumDevices_invalid, apIndices[iteration], result);
                }

                /* Negative Test WIFI_HAL_INVALID_ARGUMENTS */
                /* Passing valid apIndex, NULL buffer to opDeviceMacAddArray, maxNumDevices as valid value and valid buffer to opNumOfDevices and expecting the API to return failure*/
                UT_LOG("Test Case 3");

                for (iteration = 0; iteration < numRadios; iteration ++)
                {
                    result = wifi_getApAssociatedDevice(apIndices[iteration], NULL, maxNumDevices, &returnedOpNumOfDevices);
                    UT_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS );

                    UT_LOG("Setting NULL buffer to opDeviceMacAddArray, maxNumDevices as %d, valid buffer to opNumOfDevices for apIndex %d returns : %d", maxNumDevices, apIndices[iteration], result);
                }

                /* Negative Test WIFI_HAL_INVALID_ARGUMENTS */
                /* Passing negative apIndex, valid buffer to opDeviceMacAddArray, maxNumDevices as valid value and valid buffer to opNumOfDevices and expecting the API to return failure*/
                UT_LOG("Test Case 4");

                result = wifi_getApAssociatedDevice(apIndex_negative, &opDeviceMacAddArray[0], maxNumDevices, &returnedOpNumOfDevices);
                UT_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS );

                UT_LOG("Setting valid buffer to opDeviceMacAddArray, maxNumDevices as %d, valid buffer to opNumOfDevices for apIndex %d returns : %d", maxNumDevices, apIndex_negative, result);

                /* Negative Test WIFI_HAL_INVALID_ARGUMENTS */
                /* Passing positive out of range apIndex, valid buffer to opDeviceMacAddArray, maxNumDevices as valid value and valid buffer to opNumOfDevices and expecting the API to return failure*/
                UT_LOG("Test Case 5");

                result = wifi_getApAssociatedDevice(apIndex_OutOfRange, &opDeviceMacAddArray[0], maxNumDevices, &returnedOpNumOfDevices);
                UT_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS );

                UT_LOG("Setting valid buffer to opDeviceMacAddArray, maxNumDevices as %d, valid buffer to opNumOfDevices for apIndex %d returns : %d", maxNumDevices, apIndex_OutOfRange, result);
            }
            else
            {
                UT_LOG("Unable to retrieve the access point indices");
            }

            free(apIndices);
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

    UT_LOG("Exiting getApAssociatedDevice...");
    return;
}

/**
 * @brief Tests requirements for L1 testing wifi_enableCSIEngine()

 * Test Coverage: Positive and Negative Scenarios
 *
 * @retval WIFI_HAL_SUCCESS             -> tested
 * @retval WIFI_HAL_ERROR               -> tested
 * @retval WIFI_HAL_INVALID_ARGUMENTS   -> tested
 *
 * @Note hal api is Synchronous
 */
void test_wifi_enableCSIEngine(void)
{

    UT_LOG("Entering enableCSIEngine...");

    int result = 0;
    int iteration = 0;
    int * apIndices = NULL;
    int apIndex_negative = -1;
    int apIndex_OutOfRange = 99;
    int returnStatus = 0;
    unsigned int numRadios = 0;
    BOOL enable = FALSE;
    BOOL enable_invalid = 2;

    /* Get the number of radios applicable */
    returnStatus = test_utils_getMaxNumberOfRadio(&numRadios);

    if (returnStatus == 0)
    {
        UT_LOG("Number of Radios : %u", numRadios);

        /* Allocate memory to store the apIndices */
        apIndices = (int *)malloc( sizeof(int) * numRadios );

        if (apIndices != NULL)
        {
            /* Get the list of private access points corresponding to each of the supported radios */
            returnStatus = test_utils_getApIndices(numRadios, apIndices, PRIVATE);

            if (returnStatus == 0)
            {
                UT_LOG("Private AP Indices for the supported radios retrieved");

                /* Positive Test WIFI_HAL_SUCCESS */
                /* Passing valid apIndex, NULL mac address and enable parameter as false and expecting the API to return success */
                UT_LOG("Test Case 1");

                for (iteration = 0; iteration < numRadios; iteration ++)
                {
                    result = wifi_enableCSIEngine(apIndices[iteration], NULL, enable);
                    UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );

                    UT_LOG("Setting NULL mac address and enable as %d for apIndex %d returns : %d", enable, apIndices[iteration], result);
                }

                /* Negative Test WIFI_HAL_ERROR */
                /* Passing valid apIndex, NULL mac address and enable parameter as true and expecting the API to return failure */
                enable = TRUE;
                UT_LOG("Test Case 2");

                for (iteration = 0; iteration < numRadios; iteration ++)
                {
                    result = wifi_enableCSIEngine(apIndices[iteration], NULL, enable);
                    UT_ASSERT_EQUAL( result, WIFI_HAL_ERROR );

                    UT_LOG("Setting NULL mac address and enable as %d for apIndex %d returns : %d", enable, apIndices[iteration], result);
                }

                /* Negative Test WIFI_HAL_INVALID_ARGUMENTS */
                /* Passing valid apIndex, NULL mac address and enable parameter as an invalid value and expecting the API to return failure */
                UT_LOG("Test Case 3");

                for (iteration = 0; iteration < numRadios; iteration ++)
                {
                    result = wifi_enableCSIEngine(apIndices[iteration], NULL, enable_invalid);
                    UT_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS );

                    UT_LOG("Setting NULL mac address and enable as %d for apIndex %d returns : %d", enable_invalid, apIndices[iteration], result);
                }

                /* Negative Test WIFI_HAL_INVALID_ARGUMENTS */
                /* Passing negative apIndex, NULL mac address and enable parameter as FALSE and expecting the API to return failure */
                enable = FALSE;
                UT_LOG("Test Case 4");

                result = wifi_enableCSIEngine(apIndex_negative, NULL, enable);
                UT_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS );

                UT_LOG("Setting NULL mac address and enable as %d for apIndex %d returns : %d", enable, apIndex_negative, result);

                /* Negative Test WIFI_HAL_INVALID_ARGUMENTS */
                /* Passing out of range apIndex, NULL mac address and enable parameter as FALSE and expecting the API to return failure */
                UT_LOG("Test Case 5");

                result = wifi_enableCSIEngine(apIndex_OutOfRange, NULL, enable);
                UT_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS );

                UT_LOG("Setting NULL mac address and enable as %d for apIndex %d returns : %d", enable, apIndex_OutOfRange, result);
            }
            else
            {
                UT_LOG("Unable to retrieve the access point indices");
            }

            free(apIndices);
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

    UT_LOG("Exiting enableCSIEngine...");
    return;

}

/**
 * @brief Tests requirements for L1 testing wifi_createVAP()
 *
 * Test Coverage: Positive and Negative Scenarios
 *
 * @retval WIFI_HAL_SUCCESS             -> tested
 * @retval WIFI_HAL_INVALID_ARGUMENTS   -> tested
 *
 * @Note hal api is Synchronous
 */
void test_wifi_createVAP(void)
{

    UT_LOG("Entering createVAP...");

    int result = 0;
    int * apIndices = NULL;
    int index = 0;
    wifi_vap_info_map_t  map;
    int radioIndex = 0;
    unsigned int numRadios = 0;
    int returnStatus = 0;
    int radioIndex_outOfRange = 99;

    /* Get the number of radios applicable */
    returnStatus = test_utils_getMaxNumberOfRadio(&numRadios);

    if (returnStatus == 0)
    {
        UT_LOG("Number of Radios : %u", numRadios);

        /* Postive Test WIFI_HAL_SUCCESS */
        /* Setting valid VAP info map and expecting the API to return success */
        UT_LOG("Test Case 1");

        /* Allocate memory to store the apIndices */
        apIndices = (int *)malloc( sizeof(int) * numRadios );

        if (apIndices != NULL)
        {
            /* Get the list of private access points corresponding to each of the supported radios */
            returnStatus = test_utils_getApIndices(numRadios, apIndices, PRIVATE);

            if (returnStatus == 0)
            {
                UT_LOG("Private AP Indices for the supported radios retrieved");

                for (radioIndex = 0; radioIndex < numRadios; radioIndex++, index++)
                {
                    /* Get the vap configuration */
                    returnStatus = get_private_vap_config(apIndices[index], &map.vap_array[0]);
                    if (returnStatus == 0)
                    {
                        UT_LOG("get_private_vap_config for vap %d returns : %d", apIndices[index], returnStatus);

                        map.num_vaps = 1;
                        result = wifi_createVAP(radioIndex, &map);
                        UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );

                        UT_LOG("Setting valid VAP info map for radio %d returns : %d", radioIndex, result);
                    }
                    else
                    {
                        UT_LOG("Unable to parse the vap config file");
                    }
                }

                /* Negative Test WIFI_HAL_INVALID_ARGUMENTS */
                /* Passing NULL Buffer as input to VAP info map structure and expecting the API to return failure */
                UT_LOG("Test Case 2");

                for (radioIndex = 0; radioIndex < numRadios; radioIndex++)
                {
                    result = wifi_createVAP(radioIndex, NULL);
                    UT_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS );

                    UT_LOG("Setting NULL buffer as VAP info map structure for radio %d returns : %d", radioIndex, result);
                }

                /* Negative Test WIFI_HAL_INVALID_ARGUMENTS */
                /* Passing out of range value as radio index and valid VAP info map buffer and expecting the API to return failure */
                UT_LOG("Test Case 3");

                result = wifi_createVAP(radioIndex_outOfRange, &map);
                UT_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS );

                UT_LOG("Setting valid VAP info map structure for radio %d returns : %d", radioIndex_outOfRange, result);

                /* Negative Test WIFI_HAL_INVALID_ARGUMENTS */
                /* Passing out of range value as radio index and VAP info map as NULL buffer and expecting the API to return failure */
                UT_LOG("Test Case 4");

                result = wifi_createVAP(radioIndex_outOfRange, NULL);
                UT_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS );

                UT_LOG("Setting VAP info map structure as NULL for radio %d returns : %d", radioIndex_outOfRange, result);
            }
            else
            {
                UT_LOG("Unable to retrieve the access point indices");
            }

            free(apIndices);
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

    UT_LOG("Exiting createVAP...");
    return;

}

/**
 * @brief Tests requirements for L1 testing wifi_getRadioVapInfoMap()
 *
 * Test Coverage: Positive and Negative Scenarios
 *
 * @retval WIFI_HAL_SUCCESS             -> tested
 * @retval WIFI_HAL_INVALID_ARGUMENTS   -> tested
 *
 * @Note hal api is Synchronous
 */
void test_wifi_getRadioVapInfoMap(void)
{

    UT_LOG("Entering getRadioVapInfoMap...");

    int result = 0;
    wifi_vap_info_map_t map;
    int radioIndex = 0;
    unsigned int numRadios = 0;
    int returnStatus = 0;
    int radioIndex_outOfRange = 99;

    /* Get the number of radios applicable */
    returnStatus = test_utils_getMaxNumberOfRadio(&numRadios);

    if (returnStatus == 0)
    {
        UT_LOG("Number of Radios : %u", numRadios);

        /* Postive Test WIFI_HAL_SUCCESS */
        /* Passing valid VAP info map buffer and expecting the API to return success */
        UT_LOG("Test Case 1");

        for (radioIndex = 0; radioIndex < numRadios; radioIndex++)
        {
            result = wifi_getRadioVapInfoMap(radioIndex, &map);
            UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );

            UT_LOG("Passing valid buffer to VAP info map for radio %d returns : %d", radioIndex, result);
        }

        /* Negative Test WIFI_HAL_INVALID_ARGUMENTS */
        /* Passing NULL Buffer as input to VAP info map and expecting the API to return failure */
        UT_LOG("Test Case 2");

        for (radioIndex = 0; radioIndex < numRadios; radioIndex++)
        {
            result = wifi_getRadioVapInfoMap(radioIndex, NULL);
            UT_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS );

            UT_LOG("Passing NULL buffer as VAP info map for radio %d returns : %d", radioIndex, result);
        }

        /* Negative Test WIFI_HAL_INVALID_ARGUMENTS */
        /* Passing a positive out of range radio index, valid VAP info map buffer and expecting the API to return failure */
        UT_LOG("Test Case 3");

        result = wifi_getRadioVapInfoMap(radioIndex_outOfRange, &map);
        UT_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS );

        UT_LOG("Passing an out of range positive radio index %d and valid buffer as VAP info map returns : %d", radioIndex_outOfRange, result);

        /* Negative Test WIFI_HAL_INVALID_ARGUMENTS */
        /* Passing an invalid radio index, VAP info map as NULL buffer and expecting the API to return failure */
        UT_LOG("Test Case 4");

        result = wifi_getRadioVapInfoMap(radioIndex_outOfRange, NULL);
        UT_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS );

        UT_LOG("Passing invalid radio index %d and NULL buffer as VAP info map returns : %d", radioIndex_outOfRange, result);
    }
    else
    {
        UT_LOG("Unable to retrieve the number of radios from HalCapability");
    }

    UT_LOG("Exiting getRadioVapInfoMap...");
    return;

}

/**
 * @brief Tests requirements for L1 testing wifi_kickAssociatedDevice
 *
 * Test Coverage: Negative Scenarios
 *
 * @retval WIFI_HAL_INVALID_ARGUMENTS   -> tested
 *
 * @Note hal api is Synchronous
 */

void test_wifi_kickAssociatedDevice(void)
{
   UT_LOG("Entering kickAssociatedDevice..." );

   int result = 0;
   int index = 0;
   unsigned int numRadios = 0;
   int returnStatus = 0;
   wifi_device_t device;
   int * apIndex = NULL;
   char *mac = "AA:BB:CC:DD:EE:FF";

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
	       		/* Negative Test WIFI_HAL_INVALID_ARGUMENTS */
	       		/* Passing an invalid positive out of range apIndex, valid device and expecting the API to return failure */
	       		UT_LOG("Test Case 1");
	       		memset(&device,0,sizeof(wifi_device_t));
	       		result = wifi_kickAssociatedDevice(TBC_POSITIVE_INDEX_OUT_OF_RANGE, &device);
			UT_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS );
	       		UT_LOG("Passing an invalid positive out of range apIndex %d with valid device returns %d", TBC_POSITIVE_INDEX_OUT_OF_RANGE, result);

			/* Negative Test WIFI_HAL_INVALID_ARGUMENTS */
	       		/* Passing an invalid negative apIndex, valid device and expecting the API to return failure */
	       		UT_LOG("Test Case 2");
	       		memset(&device,0,sizeof(wifi_device_t));
	       		result = wifi_kickAssociatedDevice(TBC_NEGATIVE_INDEX_OUT_OF_RANGE, &device);
	                UT_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS );
			UT_LOG("Passing an invalid negative out of range apIndex %d with valid device returns %d", TBC_NEGATIVE_INDEX_OUT_OF_RANGE, result);

			/* Negative Test WIFI_HAL_INVALID_ARGUMENTS */
	       		/* Passing valid apIndex, invalid device mac  and expecting the API to return failure */
	       		UT_LOG("Test Case 3");
	       		for (index = 0; index < numRadios; index++)
	       		{
	       			memset(&device,0,sizeof(wifi_device_t));
	       			sscanf(mac, "%02hhX:%02hhX:%02hhX:%02hhX:%02hhX:%02hhX", &device.wifi_devMacAddress[0], &device.wifi_devMacAddress[1], &device.wifi_devMacAddress[2], &device.wifi_devMacAddress[3], &device.wifi_devMacAddress[4], &device.wifi_devMacAddress[5]);
	       			result = wifi_kickAssociatedDevice(apIndex[index], &device);
	                        UT_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS );
				UT_LOG("Passing valid apIndex  %d with invalid %02hhX:%02hhX:%02hhX:%02hhX:%02hhX:%02hhX device mac returns %d", apIndex[index], device.wifi_devMacAddress[0], device.wifi_devMacAddress[1], device.wifi_devMacAddress[2], device.wifi_devMacAddress[3], device.wifi_devMacAddress[4], device.wifi_devMacAddress[5], result);
	       		}

			/* Negative Test WIFI_HAL_INVALID_ARGUMENTS */
	       		/* Passing valid apIndex, NULL device and expecting the API to return failure */
	       		UT_LOG("Test Case 4");
	       		for (index = 0; index < numRadios; index++)
	       		{
	       			memset(&device,0,sizeof(wifi_device_t));
	       			result = wifi_kickAssociatedDevice(apIndex[index], NULL);
	                        UT_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS );
				UT_LOG("Passing valid apIndex %d with NULL device returns %d", apIndex[index], result);
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

   UT_LOG("Exiting kickAssociatedDevice..." );
   return;

}


#if 0 /* Requires review, this is not defined in the wifi_hal, but maybe in later revisions */

static INT test_wifi_receivedMgmtFrame_callback(INT apIndex, UCHAR *sta_mac, UCHAR *frame, UINT len, wifi_mgmtFrameType_t type, wifi_direction_t dir)
{
    (void)apIndex;
    (void)sta_mac;
    (void)frame;
    (void)len;
    (void)type;
    (void)dir;
    /* During level2 testing all these fields should be validated */
    /* Should not be triggered during this test */
    UT_FAIL( "This function isn't expected to be triggered" );
    return (INT)0;

}

void test_wifi_mgmt_frame_callbacks_register(void)
{
    INT result;

    /* Positive */
    result = wifi_mgmt_frame_callbacks_register(&test_wifi_receivedMgmtFrame_callback);
    UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );
    result = wifi_mgmt_frame_callbacks_register(NULL);
    UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );

    /* TOOD: Believe this interface is incorrectly defined */

    /* Negative */
    /* TODO: Negative case ? How can this be triggered, I expect this function to be void and not INT result */
}
#endif

static INT test_wifi_newApAssociatedDevice_callback(INT apIndex, wifi_associated_dev_t *associated_dev)
{
    (void)apIndex;
    (void)associated_dev;
    /* Should not be triggered during this test */
    UT_FAIL( "This function isn't expected to be triggered" );
    return (INT)0;
}

void test_wifi_newApAssociatedDevice_callback_register(void)
{
    /* Positive */
    wifi_newApAssociatedDevice_callback_register(&test_wifi_newApAssociatedDevice_callback);
    wifi_newApAssociatedDevice_callback_register(NULL);

    /* Negative - N/A */
}

static INT test_wifi_apDeAuthEvent_callback(int apIndex, char *mac, int reason)
{
    (void)apIndex;
    (void)mac;
    (void)reason;
    /* Should not be triggered during this test */
    UT_FAIL( "This function isn't expected to be triggered" );
    return (INT)0;
}

void test_wifi_apDeAuthEvent_callback_register(void)
{
    /* Positive */
    wifi_apDeAuthEvent_callback_register(&test_wifi_apDeAuthEvent_callback);
    wifi_apDeAuthEvent_callback_register(NULL);

    /* Negative - N/A */
}

static INT test_wifi_apDisassociatedDevice_callback(INT apIndex, char *MAC, INT event_type)
{
    (void)apIndex;
    (void)MAC;
    (void)event_type;
    UT_FAIL( "This function isn't expected to be triggered" );
    return (INT)0;
}

void test_wifi_apDisassociatedDevice_callback_register(void)
{
    /* Positive */
    wifi_apDisassociatedDevice_callback_register(&test_wifi_apDisassociatedDevice_callback);
    wifi_apDisassociatedDevice_callback_register(NULL);

    /* Negative - N/A */
}

static UT_test_suite_t * pSuite = NULL;

/**
 * @brief Register the main tests for this module
 *
 * @return int - 0 on success, otherwise failure
 */
INT test_wifi_ap_register( void )
{
    /* add a suite to the registry */
    pSuite = UT_add_suite("[L1 wifi-ap]", NULL, NULL);
    if (NULL == pSuite)
    {
        return -1;
    }

    UT_add_test( pSuite, "wifi_getApAssociatedDevice", test_wifi_getApAssociatedDevice);
    UT_add_test( pSuite, "wifi_enableCSIEngine", test_wifi_enableCSIEngine);
    UT_add_test( pSuite, "wifi_getRadioVapInfoMap", test_wifi_getRadioVapInfoMap);
    UT_add_test( pSuite, "wifi_createVAP", test_wifi_createVAP);
    //UT_add_test( pSuite, "wifi_mgmt_frame_callbacks_register", test_wifi_mgmt_frame_callbacks_register);  /* Needs review */
    //UT_add_test( pSuite, "wifi_newApAssociatedDevice_callback_register", test_wifi_newApAssociatedDevice_callback_register);
    //UT_add_test( pSuite, "wifi_apDeAuthEvent_callback_register", test_wifi_apDeAuthEvent_callback_register);
    //UT_add_test( pSuite, "wifi_apDisassociatedDevice_callback_register", test_wifi_apDisassociatedDevice_callback_register);
    UT_add_test( pSuite, "wifi_kickAssociatedDevice", test_wifi_kickAssociatedDevice);
    return 0;
}
