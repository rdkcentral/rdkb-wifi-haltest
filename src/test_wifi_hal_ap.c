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
* @file test_wifi_hal_ap.c
* @page WIFIHAL_Ap WiFi HAL Level 1 Tests - AP
*
* ## Module's Role
* This module includes Level 1 functional tests (success and failure scenarios).
* This is to ensure that the wifi_getApAssociatedDevice(), wifi_enableCSIEngine(), wifi_getRadioVapInfoMap(), wifi_kickAssociatedDevice() and wifi_createVAP() APIs meet the operational requirements across all vendors.
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
#include "config_parser.h"
#include "test_utils.h"
#include "api_translator.h"

#include <ut.h>
#include <ut_log.h>

/* Values here should be read from a configuration file, that supports the test */
#define TBC_NEGATIVE_INDEX_OUT_OF_RANGE (-1)
#define TBC_POSITIVE_INDEX_OUT_OF_RANGE (99)

/**
* @brief This function checks if wifi_getApAssociatedDevice() works as expected
*
* Calls the header function wifi_getApAssociatedDevice() with correct and incorrect params
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
* |01|call wifi_getApAssociatedDevice() with apIndex 0 and NULL buffer to opNumOfDevices | apIndex=0, *opDeviceMacAddArray=valid buffer of type mac_address_t , maxNumDevices=32, opNumOfDevices=NULL  | WIFI_HAL_INVALID_ARGUMENTS| Should Fail |
* |02|call wifi_getApAssociatedDevice() with apIndex 1 and NULL buffer to opNumOfDevices | apIndex=1, *opDeviceMacAddArray=valid buffer of type mac_address_t, maxNumDevices=32, opNumOfDevices=NULL  | WIFI_HAL_INVALID_ARGUMENTS| Should Fail |
* |03|call wifi_getApAssociatedDevice() with maxNumDevices as 0 for apIndex 0 | apIndex=0, *opDeviceMacAddArray=valid buffer of type mac_address_t, maxNumDevices=0, opNumOfDevices=valid buffer of type unsigned int | WIFI_HAL_INVALID_ARGUMENTS| Should Fail |
* |04|call wifi_getApAssociatedDevice() with maxNumDevices as 0 for apIndex 1 | apIndex=1, *opDeviceMacAddArray=valid buffer of type mac_address_t, maxNumDevices=0, opNumOfDevices=valid buffer of type unsigned int  | WIFI_HAL_INVALID_ARGUMENTS| Should Fail |
* |05|call wifi_getApAssociatedDevice() with opDeviceMacAddArray as NULL for apIndex 0 | apIndex=0, *opDeviceMacAddArray=NULL, maxNumDevices=0, opNumOfDevices=valid buffer of type unsigned int  | WIFI_HAL_INVALID_ARGUMENTS| Should Fail |
* |06|call wifi_getApAssociatedDevice() with opDeviceMacAddArray as NULL for apIndex 1 | apIndex=1, *opDeviceMacAddArray=NULL, maxNumDevices=0, opNumOfDevices=valid buffer of type unsigned int  | WIFI_HAL_INVALID_ARGUMENTS| Should Fail |
* |07|call wifi_getApAssociatedDevice() with invalid negative apIndex | apIndex=-1, *opDeviceMacAddArray=valid buffer of type mac_address_t, maxNumDevices=0, opNumOfDevices=valid buffer of type unsigned int  | WIFI_HAL_INVALID_ARGUMENTS| Should Fail |
* |08|call wifi_getApAssociatedDevice() with invalid positive outofRange apIndex | apIndex=99, *opDeviceMacAddArray=valid buffer of type mac_address_t, maxNumDevices=0, opNumOfDevices=valid buffer of type unsigned int  | WIFI_HAL_INVALID_ARGUMENTS| Should Fail |
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
* @brief This function checks if wifi_enableCSIEngine() works as expected
*
* Calls the header function wifi_enableCSIEngine() with correct and incorrect params
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
* |01|call wifi_enableCSIEngine() with apIndex as 0, NULL mac address and enable parameter as false | apIndex=0, sta=NULL , enable=FALSE | WIFI_HAL_SUCCESS | Should Pass |
* |02|call wifi_enableCSIEngine() with apIndex as 1, NULL mac address and enable parameter as false | apIndex=1, sta=NULL , enable=FALSE | WIFI_HAL_SUCCESS | Should Pass |
* |03|call wifi_enableCSIEngine() with apIndex as 0, NULL mac address and enable parameter as true | apIndex=0, sta=NULL , enable=TRUE | WIFI_HAL_SUCCESS | Should Pass |
* |04|call wifi_enableCSIEngine() with apIndex as 1, NULL mac address and enable parameter as true | apIndex=1, sta=NULL , enable=TRUE | WIFI_HAL_SUCCESS | Should Pass |
* |05|call wifi_enableCSIEngine() with apIndex as 0, NULL mac address and enable parameter as an invalid value | apIndex=0, sta=NULL, enable=2 | WIFI_HAL_INVALID_ARGUMENTS| Should Fail |
* |06|call wifi_enableCSIEngine() with apIndex as 1, NULL mac address and enable parameter as an invalid value | apIndex=1, sta=NULL, enable=2 | WIFI_HAL_INVALID_ARGUMENTS| Should Fail |
* |07|call wifi_enableCSIEngine() with negative apIndex, NULL mac address and enable parameter as FALSE | apIndex=-1, sta=NULL , enable=FALSE | WIFI_HAL_INVALID_ARGUMENTS| Should Fail |
* |08|call wifi_enableCSIEngine() with out of range apIndex, NULL mac address and enable parameter as FALSE | apIndex=99, sta=NULL , enable=FALSE | WIFI_HAL_INVALID_ARGUMENTS| Should Fail |
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
* @brief This function checks if wifi_createVAP() works as expected
*
* Calls the header function wifi_createVAP() with correct and incorrect params
*
* **Test Group ID:** Basic: 01@n
* **Test Case ID:** 003@n
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
* |01|call wifi_createVAP() with valid arguments | radioIndex=0, map.num_vaps=1, map=valid buffer of type wifi_vap_info_map_t | WIFI_HAL_SUCCESS | Should Pass |
* |02|call wifi_createVAP() with valid arguments | radioIndex=1, map.num_vaps=1, map=valid buffer of type wifi_vap_info_map_t | WIFI_HAL_SUCCESS | Should Pass |
* |03|call wifi_createVAP() with vap info map as NULL for radio 0 | radioIndex=0, map=NULL | WIFI_HAL_INVALID_ARGUMENTS| Should Fail |
* |04|call wifi_createVAP() with vap info map as NULL for radio 1 | radioIndex=1, map=NULL | WIFI_HAL_INVALID_ARGUMENTS| Should Fail |
* |05|call wifi_createVAP() with invalid radioIndex and valid vap info map | radioIndex=99, map=valid buffer of type wifi_vap_info_map_t | WIFI_HAL_INVALID_ARGUMENTS| Should Fail |
* |06|call wifi_createVAP() with invalid radioIndex and vap info map as NULL | radioIndex=99, map=NULL | WIFI_HAL_INVALID_ARGUMENTS| Should Fail |
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
* @brief This function checks if wifi_getRadioVapInfoMap() works as expected
*
* Calls the header function wifi_getRadioVapInfoMap() with correct and incorrect params
*
* **Test Group ID:** Basic: 01@n
* **Test Case ID:** 004@n
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
* |01|call wifi_getRadioVapInfoMap() with radioIndex 0 and valid VAP info map buffer | radioIndex=0, map=valid buffer of type wifi_vap_info_map_t | WIFI_HAL_SUCCESS | Should Pass |
* |02|call wifi_getRadioVapInfoMap() with radioIndex 1 and valid VAP info map buffer | radioIndex=1, map=valid buffer of type wifi_vap_info_map_t | WIFI_HAL_SUCCESS | Should Pass |
* |03|call wifi_getRadioVapInfoMap() with radioIndex 0 and NULL Buffer as input to VAP info map | radioIndex=0, map=NULL | WIFI_HAL_INVALID_ARGUMENTS| Should Fail |
* |04|call wifi_getRadioVapInfoMap() with radioIndex 1 and NULL Buffer as input to VAP info map | radioIndex=1, map=NULL | WIFI_HAL_INVALID_ARGUMENTS| Should Fail |
* |05|call wifi_getRadioVapInfoMap() with positive out of range radio index, valid VAP info map buffer | radioIndex=99, map=valid buffer of type wifi_vap_info_map_t | WIFI_HAL_INVALID_ARGUMENTS| Should Fail |
* |06|call wifi_getRadioVapInfoMap() with invalid radio index, VAP info map as NULL buffer | radioIndex=99, map=NULL | WIFI_HAL_INVALID_ARGUMENTS| Should Fail |
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
* @brief This function checks if wifi_kickAssociatedDevice() works as expected
*
* Calls the header function wifi_kickAssociatedDevice() with correct and incorrect params
*
* **Test Group ID:** Basic: 01@n
* **Test Case ID:** 005@n
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
* |01|call wifi_kickAssociatedDevice() with positive out of range apIndex | apIndex=99, device=pass valid buffer of type wifi_device_t | WIFI_HAL_INVALID_ARGUMENTS| Should Fail |
* |02|call wifi_kickAssociatedDevice() with negative out of range apIndex | apIndex=-1, device=pass valid buffer of type wifi_device_t | WIFI_HAL_INVALID_ARGUMENTS| Should Fail |
* |03|call wifi_kickAssociatedDevice() with apIndex as 0 and invalid device mac | apIndex=0, device="AA:BB:CC:DD:EE:FF" | WIFI_HAL_INVALID_ARGUMENTS| Should Fail |
* |04|call wifi_kickAssociatedDevice() with apIndex as 1 and invalid device mac | apIndex=1, device="AA:BB:CC:DD:EE:FF" | WIFI_HAL_INVALID_ARGUMENTS| Should Fail |
* |05|call wifi_kickAssociatedDevice() with apIndex as 0 and device mac as NULL | apIndex=0, device=NULL | WIFI_HAL_INVALID_ARGUMENTS| Should Fail |
* |06|call wifi_kickAssociatedDevice() with apIndex as 1 and device mac as NULL | apIndex=1, device=NULL | WIFI_HAL_INVALID_ARGUMENTS| Should Fail |
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

/**
* @brief This function checks if wifi_createVAP() works as expected on setting WPA3-PERSONAL as security mode for private vaps
*
* Calls the header function wifi_createVAP() with correct params
*
* **Test Group ID:** Basic: 01@n
* **Test Case ID:** 006@n
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
* |01|call wifi_createVAP() with valid arguments for apIndex 0 | apIndex=0, map=valid buffer of type wifi_vap_info_map_t with map.num_vaps=1, map.vap_array[0].u.bss_info.security.mode=wifi_security_mode_wpa3_personal, map.vap_array[0].u.bss_info.isolation=FALSE | WIFI_HAL_SUCCESS | Should Pass |
* |02|call wifi_createVAP() with valid arguments for apIndex 1 | apIndex=1, map=valid buffer of type wifi_vap_info_map_t with map.num_vaps=1, map.vap_array.u.bss_info.security.mode=wifi_security_mode_wpa3_personal, map.vap_array.u.bss_info.isolation=FALSE with vap_array index as 0 | WIFI_HAL_SUCCESS | Should Pass |
*/
void test_createVAP_private_valid_tc1(void)
{
    UT_LOG("Entering test_createVAP_private_valid_tc1...");

    int * apIndices = NULL;
    int index = 0;
    int result = 0;
    int radioIndex = 0;
    int returnStatus = 0;
    wifi_vap_info_map_t  tmp_map, org_map;
    unsigned int numRadios = 0;

    /* Get the number of radios applicable */
    returnStatus = test_utils_getMaxNumberOfRadio(&numRadios);

    if (returnStatus == 0)
    {
        UT_LOG("Number of Radios : %u", numRadios);

	/* Postive Test WIFI_HAL_SUCCESS */
        /* Setting security mode as wpa3-personal, Isolation Enabled as FALSE and expecting the API to return success */
        UT_LOG("Test Case 1");

        /* Allocate memory to store the apIndices */
        apIndices = (int *)malloc( sizeof(int) * numRadios );

        if (apIndices != NULL)
        {
            /* Get the list of private access points corresponding to each of the supported radios */
	    returnStatus = test_utils_getApIndices(numRadios, apIndices, PRIVATE);

            if (returnStatus == 0)
            {
                for (radioIndex = 0; radioIndex < numRadios; radioIndex++, index++)
                {
		    /* Get the vap configuration */
                    returnStatus = get_private_vap_config(apIndices[index], &org_map.vap_array[0]);
                    if (returnStatus == 0)
                    {
                        UT_LOG("get_private_vap_config for vap %d returns : %d", apIndices[index], returnStatus);

                        /* Initialize the values to be set */
			tmp_map = org_map;
                        tmp_map.num_vaps = 1;
                        /* Set security mode as WPA3-PERSONAL and disable isolation  */
                        tmp_map.vap_array[0].u.bss_info.security.mode = wifi_security_mode_wpa3_personal;
                        tmp_map.vap_array[0].u.bss_info.isolation = FALSE;

			UT_LOG("Setting the security mode to wpa3-personal and Isolation Enabled as FALSE");
                        result = wifi_createVAP(radioIndex, &tmp_map);
                        UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );
                        UT_LOG("Setting security mode as wpa3-personal, Isolation Enabled as FALSE using wifi_createVAP for private ap_index %d of radio %d returns : %d", apIndices[index], radioIndex, result);

			/* Setting the config back to default values */
			result = wifi_createVAP(radioIndex, &org_map);
                        UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );
                        UT_LOG("Setting the config back to default values for private ap_index %d of radio %d returns : %d", apIndices[index], radioIndex, result);
                    }
                    else
                    {
                        UT_LOG("Unable to parse the vap config file");
                    }
                }
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

    UT_LOG("Exiting test_createVAP_private_valid_tc1...");
    return;
}

/**
* @brief This function checks if wifi_createVAP() works as expected on setting WPA3-TRANSITION as security mode for private vaps
*
* Calls the header function wifi_createVAP() with correct params
*
* **Test Group ID:** Basic: 01@n
* **Test Case ID:** 007@n
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
* |01|call wifi_createVAP() with valid arguments for apIndex 0 | apIndex=0, map=valid buffer of type wifi_vap_info_map_t with map.num_vaps=1, map.vap_array[0].u.bss_info.security.mode=wifi_security_mode_wpa3_transition, map.vap_array[0].u.bss_info.isolation=FALSE | WIFI_HAL_SUCCESS | Should Pass |
* |02|call wifi_createVAP() with valid arguments for apIndex 1 | apIndex=1, map=valid buffer of type wifi_vap_info_map_t with map.num_vaps=1, map.vap_array[0].u.bss_info.security.mode=wifi_security_mode_wpa3_transition, map.vap_array[0].u.bss_info.isolation=FALSE | WIFI_HAL_SUCCESS | Should Pass |
*/
void test_createVAP_private_valid_tc2(void)
{
    UT_LOG("Entering test_createVAP_private_valid_tc2...");

    int * apIndices = NULL;
    int index = 0;
    int result = 0;
    int radioIndex = 0;
    int returnStatus = 0;
    wifi_vap_info_map_t tmp_map, org_map;
    unsigned int numRadios = 0;

    /* Get the number of radios applicable */
    returnStatus = test_utils_getMaxNumberOfRadio(&numRadios);

    if (returnStatus == 0)
    {
        UT_LOG("Number of Radios : %u", numRadios);

        /* Postive Test WIFI_HAL_SUCCESS */
        /* Setting security mode as wpa3-transition, Isolation Enabled as FALSE and expecting the API to return success */
        UT_LOG("Test Case 1");

        /* Allocate memory to store the apIndices */
        apIndices = (int *)malloc( sizeof(int) * numRadios );

        if (apIndices != NULL)
        {
            /* Get the list of private access points corresponding to each of the supported radios */
	    returnStatus = test_utils_getApIndices(numRadios, apIndices, PRIVATE);

            if (returnStatus == 0)
            {
                for (radioIndex = 0; radioIndex < numRadios; radioIndex++, index++)
                {
                    /* Get the vap configuration */
                    returnStatus = get_private_vap_config(apIndices[index], &org_map.vap_array[0]);
                    if (returnStatus == 0)
                    {
                        UT_LOG("get_private_vap_config for vap %d returns : %d", apIndices[index], returnStatus);

                        /* Initialize the values to be set */
                        tmp_map = org_map;
                        tmp_map.num_vaps = 1;
                        /* Set security mode as WPA3-TRANSITION and disable isolation  */
                        tmp_map.vap_array[0].u.bss_info.security.mode = wifi_security_mode_wpa3_transition;
                        tmp_map.vap_array[0].u.bss_info.isolation = FALSE;

                        UT_LOG("Setting the security mode to wpa3-transition and Isolation Enabled as FALSE");
                        result = wifi_createVAP(radioIndex, &tmp_map);
                        UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );
                        UT_LOG("Setting security mode as wpa3-transition, Isolation Enabled as FALSE using wifi_createVAP for private ap_index %d of radio %d returns : %d", apIndices[index], radioIndex, result);

                        /* Setting the config back to default values */
                        result = wifi_createVAP(radioIndex, &org_map);
                        UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );
                        UT_LOG("Setting the config back to default values for private ap_index %d of radio %d returns : %d", apIndices[index], radioIndex, result);
                    }
                    else
                    {
                        UT_LOG("Unable to parse the vap config file");
                    }
                }
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

    UT_LOG("Exiting test_createVAP_private_valid_tc2...");
    return;
}

/**
* @brief This function checks if wifi_createVAP() works as expected on setting invalid security mode for private vaps
*
* Calls the header function wifi_createVAP() with incorrect params
*
* **Test Group ID:** Basic: 01@n
* **Test Case ID:** 008@n
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
* |01|call wifi_createVAP() with invalid security mode for apIndex 0 | apIndex=0, map=buffer of type wifi_vap_info_map_t with map.num_vaps=1, map.vap_array[0].u.bss_info.security.mode=wifi_security_mode_wpa2_enterprise | WIFI_HAL_INVALID_ARGUMENTS| Should Fail |
* |02|call wifi_createVAP() with invalid security mode for apIndex 1 | apIndex=1, map=buffer of type wifi_vap_info_map_t with map.num_vaps=1, map.vap_array[0].u.bss_info.security.mode=wifi_security_mode_wpa2_enterprise | WIFI_HAL_INVALID_ARGUMENTS| Should Fail |
*/
void test_createVAP_private_invalid(void)
{
    UT_LOG("Entering test_createVAP_private_invalid...");

    int * apIndices = NULL;
    int index = 0;
    int result = 0;
    int radioIndex = 0;
    int returnStatus = 0;
    wifi_vap_info_map_t tmp_map, org_map;
    unsigned int numRadios = 0;

    /* Get the number of radios applicable */
    returnStatus = test_utils_getMaxNumberOfRadio(&numRadios);

    if (returnStatus == 0)
    {
        UT_LOG("Number of Radios : %u", numRadios);

        /* Negative Test WIFI_HAL_INVALID_ARGUMENTS */
        /* Setting invalid security mode and verify if API return failure */
        UT_LOG("Test Case 1");

        /* Allocate memory to store the apIndices */
        apIndices = (int *)malloc( sizeof(int) * numRadios );

        if (apIndices != NULL)
        {
            /* Get the list of private access points corresponding to each of the supported radios */
	    returnStatus = test_utils_getApIndices(numRadios, apIndices, PRIVATE);

            if (returnStatus == 0)
            {
                for (radioIndex = 0; radioIndex < numRadios; radioIndex++, index++)
                {
                    /* Get the vap configuration */
                    returnStatus = get_private_vap_config(apIndices[index], &org_map.vap_array[0]);
                    if (returnStatus == 0)
                    {
                        UT_LOG("get_private_vap_config for vap %d returns : %d", apIndices[index], returnStatus);

                        /* Initialize the values to be set */
			tmp_map = org_map;
                        tmp_map.num_vaps = 1;
			/* Set invalid security mode */
                        tmp_map.vap_array[0].u.bss_info.security.mode = wifi_security_mode_wpa2_enterprise;

                        UT_LOG("Setting the invalid security mode wpa2-enterprise");
                        result = wifi_createVAP(radioIndex, &tmp_map);
                        UT_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS );
                        UT_LOG("Setting invalid security mode using wifi_createVAP for private ap_index %d of radio %d returns : %d", apIndices[index], radioIndex, result);

			if(result == WIFI_HAL_SUCCESS)
		        {
			    /* Setting the config back to default values */
			    result = wifi_createVAP(radioIndex, &org_map);
			    UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );
			    UT_LOG("Setting the config back to default values for private ap_index %d of radio %d returns : %d", apIndices[index], radioIndex, result);
			}
                    }
                    else
                    {
                        UT_LOG("Unable to parse the vap config file");
                    }
                }
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

    UT_LOG("Exiting test_createVAP_private_invalid...");
    return;
}

/**
* @brief This function checks if wifi_createVAP() works as expected on setting WPA2-PERSONAL as security mode for sta vaps
*
* Calls the header function wifi_createVAP() with correct params
*
* **Test Group ID:** Basic: 01@n
* **Test Case ID:** 009@n
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
* |01|call wifi_createVAP() with valid arguments for apIndex 14 | apIndex=14, map=valid buffer of type wifi_vap_info_map_t with map.num_vaps=1, map.vap_array[0].u.bss_info.security.mode=wifi_security_mode_wpa2_personal | WIFI_HAL_SUCCESS | Should Pass |
* |02|call wifi_createVAP() with valid arguments for apIndex 15 | apIndex=15, map=valid buffer of type wifi_vap_info_map_t with map.num_vaps=1, map.vap_array[0].u.bss_info.security.mode=wifi_security_mode_wpa2_personal | WIFI_HAL_SUCCESS | Should Pass |
*/
void test_createVAP_meshsta_valid_tc1(void)
{
    UT_LOG("Entering test_createVAP_meshsta_valid_tc1...");

    int * apIndices = NULL;
    int index = 0;
    int result = 0;
    int radioIndex = 0;
    int returnStatus = 0;
    wifi_vap_info_map_t tmp_map, org_map;
    unsigned int numRadios = 0;

    /* Get the number of radios applicable */
    returnStatus = test_utils_getMaxNumberOfRadio(&numRadios);

    if (returnStatus == 0)
    {
        UT_LOG("Number of Radios : %u", numRadios);

        /* Postive Test WIFI_HAL_SUCCESS */
        /* Setting security mode as wpa2-personal and expecting the API to return success */
        UT_LOG("Test Case 1");

        /* Allocate memory to store the apIndices */
        apIndices = (int *)malloc( sizeof(int) * numRadios );

        if (apIndices != NULL)
        {
            /* Get the list of STA access points corresponding to each of the supported radios */
	    returnStatus = test_utils_getApIndices(numRadios, apIndices, STA);

            if (returnStatus == 0)
            {
                for (radioIndex = 0; radioIndex < numRadios; radioIndex++, index++)
		{
		     /* Get the vap configuration */
                    returnStatus = get_mesh_sta_vap_config(apIndices[index], &org_map.vap_array[0]);
                    if (returnStatus == 0)
                    {
                        /* Initialize the values to be set */
		        tmp_map = org_map;
                        tmp_map.num_vaps = 1;
			/* Set security mode as WPA2-PERSONAL */
                        tmp_map.vap_array[0].u.bss_info.security.mode = wifi_security_mode_wpa2_personal;

                        UT_LOG("Setting the security mode to wpa2-personal");
                        result = wifi_createVAP(radioIndex, &tmp_map);
                        UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );
                        UT_LOG("Setting security mode as wpa2-personal using wifi_createVAP for sta ap_index %d of radio %d returns : %d", apIndices[index], radioIndex, result);

                        /* Setting the config back to default values */
                        result = wifi_createVAP(radioIndex, &org_map);
                        UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );
                        UT_LOG("Setting the config back to default values for sta ap_index %d of radio %d returns : %d", apIndices[index], radioIndex, result); 
                    }
                    else
                    {
                        UT_LOG("Unable to parse the vap config file");
                    }
                }
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

    UT_LOG("Exiting test_createVAP_meshsta_valid_tc1...");
    return;
}

/**
* @brief This function checks if wifi_createVAP() works as expected on setting WPA3-TRANSITION as security mode for sta vaps
*
* Calls the header function wifi_createVAP() with correct params
*
* **Test Group ID:** Basic: 01@n
* **Test Case ID:** 010@n
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
* |01|call wifi_createVAP() with valid arguments for apIndex 14 | apIndex=14, map=valid buffer of type wifi_vap_info_map_t with map.num_vaps=1, map.vap_array[0].u.bss_info.security.mode=wifi_security_mode_wpa3_transition | WIFI_HAL_SUCCESS | Should Pass |
* |02|call wifi_createVAP() with valid arguments for apIndex 15 | apIndex=15, map=valid buffer of type wifi_vap_info_map_t with map.num_vaps=1, map.vap_array[0].u.bss_info.security.mode=wifi_security_mode_wpa3_transition | WIFI_HAL_SUCCESS | Should Pass |
*/
void test_createVAP_meshsta_valid_tc2(void)
{
    UT_LOG("Entering test_createVAP_meshsta_valid_tc2...");

    int * apIndices = NULL;
    int index = 0;
    int result = 0;
    int radioIndex = 0;
    int returnStatus = 0;
    wifi_vap_info_map_t tmp_map, org_map;
    unsigned int numRadios = 0;

    /* Get the number of radios applicable */
    returnStatus = test_utils_getMaxNumberOfRadio(&numRadios);

    if (returnStatus == 0)
    {
        UT_LOG("Number of Radios : %u", numRadios);

        /* Postive Test WIFI_HAL_SUCCESS */
        /* Setting security mode as wpa3-transition and expecting the API to return success */
        UT_LOG("Test Case 1");

        /* Allocate memory to store the apIndices */
        apIndices = (int *)malloc( sizeof(int) * numRadios );

        if (apIndices != NULL)
        {
            /* Get the list of STA access points corresponding to each of the supported radios */
            returnStatus = test_utils_getApIndices(numRadios, apIndices, STA);

            if (returnStatus == 0)
            {
               for (radioIndex = 0; radioIndex < numRadios; radioIndex++, index++)
                {
                    /* Get the vap configuration */
                    returnStatus = get_mesh_sta_vap_config(apIndices[index], &org_map.vap_array[0]);
                    if (returnStatus == 0)
                    {
                        /* Initialize the values to be set */
			tmp_map = org_map;
			tmp_map.num_vaps = 1;
                        /* Set security mode as WPA3-TRANSITION  */
                        tmp_map.vap_array[0].u.bss_info.security.mode = wifi_security_mode_wpa3_transition;

                        UT_LOG("Setting the security mode to wpa3-transition");
                        result = wifi_createVAP(radioIndex, &tmp_map);
                        UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );
                        UT_LOG("Setting security mode as wpa3-transition using wifi_createVAP for sta ap_index %d of radio %d returns : %d", apIndices[index], radioIndex, result);

                        /* Setting the config back to default values */
                        result = wifi_createVAP(radioIndex, &org_map);
                        UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );
                        UT_LOG("Setting the config back to default values for sta ap_index %d of radio %d returns : %d", apIndices[index], radioIndex, result); 
                    }
                    else
                    {
                        UT_LOG("Unable to parse the vap config file");
                    }
                }
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

    UT_LOG("Exiting test_createVAP_meshsta_valid_tc2...");
    return;
}

/**
* @brief This function checks if wifi_createVAP() works as expected on setting WPA3-PERSONAL as security mode for sta vaps
*
* Calls the header function wifi_createVAP() with correct params
*
* **Test Group ID:** Basic: 01@n
* **Test Case ID:** 011@n
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
* |01|call wifi_createVAP() with valid arguments for apIndex 14 | apIndex=14, map=valid buffer of type wifi_vap_info_map_t with map.num_vaps=1, map.vap_array[0].u.bss_info.security.mode=wifi_security_mode_wpa3_personal | WIFI_HAL_SUCCESS | Should Pass |
* |02|call wifi_createVAP() with valid arguments for apIndex 15 | apIndex=15, map=valid buffer of type wifi_vap_info_map_t with map.num_vaps=1, map.vap_array[0].u.bss_info.security.mode=wifi_security_mode_wpa3_personal | WIFI_HAL_SUCCESS | Should Pass |
*/
void test_createVAP_meshsta_valid_tc3(void)
{
    UT_LOG("Entering test_createVAP_meshsta_valid_tc3...");

    int * apIndices = NULL;
    int index = 0;
    int result = 0;
    int radioIndex = 0;
    int returnStatus = 0;
    wifi_vap_info_map_t tmp_map, org_map;
    unsigned int numRadios = 0;

    /* Get the number of radios applicable */
    returnStatus = test_utils_getMaxNumberOfRadio(&numRadios);

    if (returnStatus == 0)
    {
        UT_LOG("Number of Radios : %u", numRadios);

        /* Postive Test WIFI_HAL_SUCCESS */
        /* Setting security mode as wpa3-personal and expecting the API to return success */
        UT_LOG("Test Case 1");

        /* Allocate memory to store the apIndices */
        apIndices = (int *)malloc( sizeof(int) * numRadios );

        if (apIndices != NULL)
        {
            /* Get the list of STA access points corresponding to each of the supported radios */
            returnStatus = test_utils_getApIndices(numRadios, apIndices, STA);

            if (returnStatus == 0)
            {
                for (radioIndex = 0; radioIndex < numRadios; radioIndex++, index++)
                {
                    /* Get the vap configuration */
                    returnStatus = get_mesh_sta_vap_config(apIndices[index], &org_map.vap_array[0]);
                    if (returnStatus == 0)
                    {
                        /* Initialize the values to be set */
                        tmp_map = org_map;
                        tmp_map.num_vaps = 1;
                        /* Set security mode as WPA3-PERSONAL  */
                        tmp_map.vap_array[0].u.bss_info.security.mode = wifi_security_mode_wpa3_personal;

                        UT_LOG("Setting the security mode to wpa3-personal");
                        result = wifi_createVAP(radioIndex, &tmp_map);
                        UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );
                        UT_LOG("Setting security mode as wpa3-personal using wifi_createVAP for sta ap_index %d of radio %d returns : %d", apIndices[index], radioIndex, result);

                        /* Setting the config back to default values */
                        result = wifi_createVAP(radioIndex, &org_map);
		        UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );
                        UT_LOG("Setting the config back to default values for sta ap_index %d of radio %d returns : %d", apIndices[index], radioIndex, result);
                    }
                    else
                    {
                        UT_LOG("Unable to parse the vap config file");
                    }
                }
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

    UT_LOG("Exiting test_createVAP_meshsta_valid_tc3...");
    return;
}

/**
* @brief This function checks if wifi_createVAP() works as expected on setting invalid security mode for sta vaps
*
* Calls the header function wifi_createVAP() with incorrect params
*
* **Test Group ID:** Basic: 01@n
* **Test Case ID:** 012@n
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
* |01|call wifi_createVAP() with invalid security mode for apIndex 14 | apIndex=14, map=buffer of type wifi_vap_info_map_t with map.num_vaps=1, map.vap_array[0].u.bss_info.security.mode=wifi_security_mode_wpa_enterprise | WIFI_HAL_INVALID_ARGUMENTS| Should Fail |
* |02|call wifi_createVAP() with invalid security mode for apIndex 15 | apIndex=15, map=buffer of type wifi_vap_info_map_t with map.num_vaps=1, map.vap_array[0].u.bss_info.security.mode=wifi_security_mode_wpa_enterprise | WIFI_HAL_INVALID_ARGUMENTS| Should Fail |
*/
void test_createVAP_meshsta_invalid(void)
{
    UT_LOG("Entering test_createVAP_meshsta_invalid...");

    int * apIndices = NULL;
    int index = 0;
    int result = 0;
    int radioIndex = 0;
    int returnStatus = 0;
    wifi_vap_info_map_t tmp_map, org_map;
    unsigned int numRadios = 0;

    /* Get the number of radios applicable */
    returnStatus = test_utils_getMaxNumberOfRadio(&numRadios);

    if (returnStatus == 0)
    {
        UT_LOG("Number of Radios : %u", numRadios);

        /* Negative Test WIFI_HAL_INVALID_ARGUMENTS */
        /* Setting invalid security mode and verify if API return failure */
        UT_LOG("Test Case 1");

        /* Allocate memory to store the apIndices */
        apIndices = (int *)malloc( sizeof(int) * numRadios );

        if (apIndices != NULL)
        {
            /* Get the list of STA access points corresponding to each of the supported radios */
            returnStatus = test_utils_getApIndices(numRadios, apIndices, STA);

            if (returnStatus == 0)
            {
                for (radioIndex = 0; radioIndex < numRadios; radioIndex++, index++)
                {
                    /* Get the vap configuration */
                    returnStatus = get_mesh_sta_vap_config(apIndices[index], &org_map.vap_array[0]);
                    if (returnStatus == 0)
                    {
                        /* Initialize the values to be set */
                        tmp_map = org_map;
                        tmp_map.num_vaps = 1;
                        /* Set invalid security mode */
                        tmp_map.vap_array[0].u.bss_info.security.mode = wifi_security_mode_wpa_enterprise;

                        UT_LOG("Setting the invalid security mode wpa-enterprise");
                        result = wifi_createVAP(radioIndex, &tmp_map);
                        UT_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS );
                        UT_LOG("Setting invalid security mode using wifi_createVAP for sta ap_index %d of radio %d returns : %d", radioIndex, apIndices[index], result);

                        if(result == WIFI_HAL_SUCCESS)
                        {
                            /* Setting the config back to default values */
                            result = wifi_createVAP(radioIndex, &org_map);
                            UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );
                            UT_LOG("Setting the config back to default values for private ap_index %d of radio %d returns : %d", apIndices[index], radioIndex, result);
                        }
                    }
                    else
                    {
                        UT_LOG("Unable to parse the vap config file");
                    }
                }
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

    UT_LOG("Exiting test_createVAP_meshsta_invalid...");
    return;
}

/**
* @brief This function checks if wifi_createVAP() works as expected on setting WPA2-PERSONAL as security mode for iot vaps
*
* Calls the header function wifi_createVAP() with correct params
*
* **Test Group ID:** Basic: 01@n
* **Test Case ID:** 013@n
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
* |01|call wifi_createVAP() with valid arguments for apIndex 2 | apIndex=2, map=valid buffer of type wifi_vap_info_map_t with map.num_vaps=1, map.vap_array[0].u.bss_info.security.mode=wifi_security_mode_wpa2_personal, map.vap_array[0].u.bss_info.isolation=FALSE | WIFI_HAL_SUCCESS | Should Pass |
* |02|call wifi_createVAP() with valid arguments for apIndex 3 | apIndex=3, map=valid buffer of type wifi_vap_info_map_t with map.num_vaps=1, map.vap_array[0].u.bss_info.security.mode=wifi_security_mode_wpa2_personal, map.vap_array[0].u.bss_info.isolation=FALSE | WIFI_HAL_SUCCESS | Should Pass |
*/
void test_createVAP_iot_valid_tc1(void)
{
    UT_LOG("Entering test_createVAP_iot_valid_tc1...");

    int * apIndices = NULL;
    int index = 0;
    int result = 0;
    int radioIndex = 0;
    int returnStatus = 0;
    wifi_vap_info_map_t  tmp_map, org_map;
    unsigned int numRadios = 0;

    /* Get the number of radios applicable */
    returnStatus = test_utils_getMaxNumberOfRadio(&numRadios);

    if (returnStatus == 0)
    {
        UT_LOG("Number of Radios : %u", numRadios);

        /* Postive Test WIFI_HAL_SUCCESS */
        /* Setting security mode as wpa2-personal, Isolation Enabled as FALSE and expecting the API to return success */
        UT_LOG("Test Case 1");

        /* Allocate memory to store the apIndices */
        apIndices = (int *)malloc( sizeof(int) * numRadios );

        if (apIndices != NULL)
        {
            /* Get the list of IOT access points corresponding to each of the supported radios */
            returnStatus = test_utils_getApIndices(numRadios, apIndices, IOT);

            if (returnStatus == 0)
            {
                for (radioIndex = 0; radioIndex < numRadios; radioIndex++, index++)
                {
                    /* Get the vap configuration */
                    returnStatus = get_iot_vap_config(apIndices[index], &org_map.vap_array[0]);
                    if (returnStatus == 0)
                    {
                        /* Initialize the values to be set */
                        tmp_map = org_map;
                        tmp_map.num_vaps = 1;
                        /* Set security mode as WPA2-PERSONAL and disable isolation  */
                        tmp_map.vap_array[0].u.bss_info.security.mode = wifi_security_mode_wpa2_personal;
                        tmp_map.vap_array[0].u.bss_info.isolation = FALSE;

                        UT_LOG("Setting the security mode as wpa2-personal and Isolation Enabled as FALSE");
                        result = wifi_createVAP(radioIndex, &tmp_map);
                        UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );
                        UT_LOG("Setting security mode as wpa2-personal, Isolation Enabled as FALSE using wifi_createVAP for iot ap_index %d of radio %d returns : %d", apIndices[index], radioIndex, result);

                        /* Setting the config back to default values */
                        result = wifi_createVAP(radioIndex, &org_map);
                        UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );
                        UT_LOG("Setting the config back to default values for iot ap_index %d of radio %d returns : %d", apIndices[index], radioIndex, result);
                    }
                    else
                    {
                        UT_LOG("Unable to parse the vap config file");
                    }
                }
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

    UT_LOG("Exiting test_createVAP_iot_valid_tc1...");
    return;
}

/**
* @brief This function checks if wifi_createVAP() works as expected on setting WPA3-TRANSITION as security mode for iot vaps
*
* Calls the header function wifi_createVAP() with correct params
*
* **Test Group ID:** Basic: 01@n
* **Test Case ID:** 014@n
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
* |01|call wifi_createVAP() with valid arguments for apIndex 2 | apIndex=2, map=valid buffer of type wifi_vap_info_map_t with map.num_vaps=1, map.vap_array[0].u.bss_info.security.mode=wifi_security_mode_wpa3_transition, map.vap_array[0].u.bss_info.isolation=FALSE | WIFI_HAL_SUCCESS | Should Pass |
* |02|call wifi_createVAP() with valid arguments for apIndex 3 | apIndex=3, map=valid buffer of type wifi_vap_info_map_t with map.num_vaps=1, map.vap_array[0].u.bss_info.security.mode=wifi_security_mode_wpa3_transition, map.vap_array[0].u.bss_info.isolation=FALSE | WIFI_HAL_SUCCESS | Should Pass |
*/
void test_createVAP_iot_valid_tc2(void)
{
    UT_LOG("Entering test_createVAP_iot_valid_tc2...");

    int * apIndices = NULL;
    int index = 0;
    int result = 0;
    int radioIndex = 0;
    int returnStatus = 0;
    wifi_vap_info_map_t  tmp_map, org_map;
    unsigned int numRadios = 0;

    /* Get the number of radios applicable */
    returnStatus = test_utils_getMaxNumberOfRadio(&numRadios);

    if (returnStatus == 0)
    {
        UT_LOG("Number of Radios : %u", numRadios);

        /* Postive Test WIFI_HAL_SUCCESS */
        /* Setting security mode as wpa3-transition, Isolation Enabled as FALSE and expecting the API to return success */
        UT_LOG("Test Case 1");

        /* Allocate memory to store the apIndices */
        apIndices = (int *)malloc( sizeof(int) * numRadios );

        if (apIndices != NULL)
        {
            /* Get the list of IOT access points corresponding to each of the supported radios */
	    returnStatus = test_utils_getApIndices(numRadios, apIndices, IOT);

            if (returnStatus == 0)
            {
                for (radioIndex = 0; radioIndex < numRadios; radioIndex++, index++)
                {
                    /* Get the vap configuration */
                    returnStatus = get_iot_vap_config(apIndices[index], &org_map.vap_array[0]);
                    if (returnStatus == 0)
                    {
                        /* Initialize the values to be set */
			tmp_map = org_map;
			tmp_map.num_vaps = 1;
                        /* Set security mode as WPA3-TRANSITION and disable isolation  */
                        tmp_map.vap_array[0].u.bss_info.security.mode = wifi_security_mode_wpa3_transition;
                        tmp_map.vap_array[0].u.bss_info.isolation = FALSE;

                        UT_LOG("Setting the security mode as wpa3-transition and Isolation Enabled as FALSE");
                        result = wifi_createVAP(radioIndex, &tmp_map);
                        UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );
                        UT_LOG("Setting security mode as wpa3-transition, Isolation Enabled as FALSE using wifi_createVAP for iot ap_index %d of radio %d returns : %d", apIndices[index], radioIndex, result);

                        /* Setting the config back to default values */
                        result = wifi_createVAP(radioIndex, &org_map);
                        UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );
                        UT_LOG("Setting the config back to default values for iot ap_index %d of radio %d returns : %d", apIndices[index], radioIndex, result);
                    }
                    else
                    {
                        UT_LOG("Unable to parse the vap config file");
                    }
                }
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

    UT_LOG("Exiting test_createVAP_iot_valid_tc2...");
    return;
}

/**
* @brief This function checks if wifi_createVAP() works as expected on setting WPA3-PERSONAL as security mode for iot vaps
*
* Calls the header function wifi_createVAP() with correct params
*
* **Test Group ID:** Basic: 01@n
* **Test Case ID:** 015@n
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
* |01|call wifi_createVAP() with valid arguments for apIndex 2 | apIndex=2, map=valid buffer of type wifi_vap_info_map_t with map.num_vaps=1, map.vap_array[0].u.bss_info.security.mode=wifi_security_mode_wpa3_personal, map.vap_array[0].u.bss_info.isolation=FALSE | WIFI_HAL_SUCCESS | Should Pass |
* |02|call wifi_createVAP() with valid arguments for apIndex 3 | apIndex=3, map=valid buffer of type wifi_vap_info_map_t with map.num_vaps=1, map.vap_array[0].u.bss_info.security.mode=wifi_security_mode_wpa3_personal, map.vap_array[0].u.bss_info.isolation=FALSE | WIFI_HAL_SUCCESS | Should Pass |
*/
void test_createVAP_iot_valid_tc3(void)
{
    UT_LOG("Entering test_createVAP_iot_valid_tc3...");

    int * apIndices = NULL;
    int index = 0;
    int result = 0;
    int radioIndex = 0;
    int returnStatus = 0;
    wifi_vap_info_map_t  tmp_map, org_map;
    unsigned int numRadios = 0;

    /* Get the number of radios applicable */
    returnStatus = test_utils_getMaxNumberOfRadio(&numRadios);

    if (returnStatus == 0)
    {
        UT_LOG("Number of Radios : %u", numRadios);

        /* Postive Test WIFI_HAL_SUCCESS */
        /* Setting security mode as wpa3-personal, Isolation Enabled as FALSE and expecting the API to return success */
        UT_LOG("Test Case 1");

        /* Allocate memory to store the apIndices */
        apIndices = (int *)malloc( sizeof(int) * numRadios );

        if (apIndices != NULL)
        {
            /* Get the list of IOT access points corresponding to each of the supported radios */
            returnStatus = test_utils_getApIndices(numRadios, apIndices, IOT);

            if (returnStatus == 0)
            {
                for (radioIndex = 0; radioIndex < numRadios; radioIndex++, index++)
                {
                    /* Get the vap configuration */
                    returnStatus = get_iot_vap_config(apIndices[index], &org_map.vap_array[0]);
                    if (returnStatus == 0)
                    {
                        /* Initialize the values to be set */
                        tmp_map = org_map;
                        tmp_map.num_vaps = 1;
                        /* Set security mode as WPA3-PERSONAL and disable isolation  */
                        tmp_map.vap_array[0].u.bss_info.security.mode = wifi_security_mode_wpa3_personal;
                        tmp_map.vap_array[0].u.bss_info.isolation = FALSE;

                        UT_LOG("Setting the security mode as wpa3-personal and Isolation Enabled as FALSE");
                        result = wifi_createVAP(radioIndex, &tmp_map);
                        UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );
                        UT_LOG("Setting security mode as wpa3-personal, Isolation Enabled as FALSE using wifi_createVAP for iot ap_index %d of radio %d returns : %d", apIndices[index], radioIndex, result);

                        /* Setting the config back to default values */
                        result = wifi_createVAP(radioIndex, &org_map);
                        UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );
                        UT_LOG("Setting the config back to default values for iot ap_index %d of radio %d returns : %d", apIndices[index], radioIndex, result);
                    }
                    else
                    {
                        UT_LOG("Unable to parse the vap config file");
                    }
                }
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

    UT_LOG("Exiting test_createVAP_iot_valid_tc3...");
    return;
}

/**
* @brief This function checks if wifi_createVAP() works as expected on setting invalid security mode for iot vaps
*
* Calls the header function wifi_createVAP() with incorrect params
*
* **Test Group ID:** Basic: 01@n
* **Test Case ID:** 016@n
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
* |01|call wifi_createVAP() with invalid security mode for apIndex 2 | apIndex=2, map=buffer of type wifi_vap_info_map_t with map.num_vaps=1, map.vap_array[0].u.bss_info.security.mode=wifi_security_mode_wpa3_enterprise | WIFI_HAL_INVALID_ARGUMENTS| Should Fail |
* |02|call wifi_createVAP() with invalid security mode for apIndex 3 | apIndex=3, map=buffer of type wifi_vap_info_map_t with map.num_vaps=1, map.vap_array[0].u.bss_info.security.mode=wifi_security_mode_wpa3_enterprise | WIFI_HAL_INVALID_ARGUMENTS| Should Fail |
*/
void test_createVAP_iot_invalid(void)
{
    UT_LOG("Entering test_createVAP_iot_invalid...");

    int * apIndices = NULL;
    int index = 0;
    int result = 0;
    int radioIndex = 0;
    int returnStatus = 0;
    wifi_vap_info_map_t  tmp_map, org_map;
    unsigned int numRadios = 0;

    /* Get the number of radios applicable */
    returnStatus = test_utils_getMaxNumberOfRadio(&numRadios);

    if (returnStatus == 0)
    {
        UT_LOG("Number of Radios : %u", numRadios);

        /* Negative Test WIFI_HAL_INVALID_ARGUMENTS */
        /* Setting invalid security mode and expecting the API to return failure */
        UT_LOG("Test Case 1");

        /* Allocate memory to store the apIndices */
        apIndices = (int *)malloc( sizeof(int) * numRadios );

        if (apIndices != NULL)
        {
            /* Get the list of IOT access points corresponding to each of the supported radios */
            returnStatus = test_utils_getApIndices(numRadios, apIndices, IOT);

            if (returnStatus == 0)
            {
                for (radioIndex = 0; radioIndex < numRadios; radioIndex++, index++)
                {
                    /* Get the vap configuration */
                    returnStatus = get_iot_vap_config(apIndices[index], &org_map.vap_array[0]);
                    if (returnStatus == 0)
                    {
                        /* Initialize the values to be set */
                        tmp_map = org_map;
                        tmp_map.num_vaps = 1;
			/* Set invalid security mode */
                        tmp_map.vap_array[0].u.bss_info.security.mode = wifi_security_mode_wpa3_enterprise;

                        UT_LOG("Setting the invalid security mode wpa3-enterprise");
                        result = wifi_createVAP(radioIndex, &tmp_map);
                        UT_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS );
                        UT_LOG("Setting invalid security mode using wifi_createVAP for iot ap_index %d of radio %d returns : %d", apIndices[index], radioIndex, result);

			if(result == WIFI_HAL_SUCCESS)
                        {
                            /* Setting the config back to default values */
                            result = wifi_createVAP(radioIndex, &org_map);
                            UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );
                            UT_LOG("Setting the config back to default values for private ap_index %d of radio %d returns : %d", apIndices[index], radioIndex, result);
                        }
                    }
                    else
                    {
                        UT_LOG("Unable to parse the vap config file");
                    }
                }
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

    UT_LOG("Exiting test_createVAP_iot_invalid...");
    return;
}

/**
* @brief This function checks if wifi_createVAP() works as expected on setting WPA2-PERSONAL as security mode for backhaul vaps
*
* Calls the header function wifi_createVAP() with correct params
*
* **Test Group ID:** Basic: 01@n
* **Test Case ID:** 017@n
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
* |01|call wifi_createVAP() with valid arguments for apIndex 12 | apIndex=12, map=valid buffer of type wifi_vap_info_map_t with map.num_vaps=1, map.vap_array[0].u.bss_info.security.mode=wifi_security_mode_wpa2_personal, map.vap_array[0].u.bss_info.isolation=TRUE | WIFI_HAL_SUCCESS | Should Pass |
* |02|call wifi_createVAP() with valid arguments for apIndex 13 | apIndex=13, map=valid buffer of type wifi_vap_info_map_t with map.num_vaps=1, map.vap_array[0].u.bss_info.security.mode=wifi_security_mode_wpa2_personal, map.vap_array[0].u.bss_info.isolation=TRUE | WIFI_HAL_SUCCESS | Should Pass |
*/
void test_createVAP_backhaul_valid_tc1(void)
{
    UT_LOG("Entering test_createVAP_backhaul_valid_tc1...");

    int * apIndices = NULL;
    int index = 0;
    int result = 0;
    int radioIndex = 0;
    int returnStatus = 0;
    wifi_vap_info_map_t  tmp_map, org_map;
    unsigned int numRadios = 0;

    /* Get the number of radios applicable */
    returnStatus = test_utils_getMaxNumberOfRadio(&numRadios);

    if (returnStatus == 0)
    {
        UT_LOG("Number of Radios : %u", numRadios);

        /* Postive Test WIFI_HAL_SUCCESS */
        /* Setting security mode as wpa2-personal, Isolation Enabled as TRUE and expecting the API to return success */
        UT_LOG("Test Case 1");

        /* Allocate memory to store the apIndices */
        apIndices = (int *)malloc( sizeof(int) * numRadios );

        if (apIndices != NULL)
        {
            /* Get the list of backhaul access points corresponding to each of the supported radios */
            returnStatus = test_utils_getApIndices(numRadios, apIndices, BACKHAUL);

            if (returnStatus == 0)
            {
                for (radioIndex = 0; radioIndex < numRadios; radioIndex++, index++)
                {
                    /* Get the vap configuration */
                    returnStatus = get_mesh_backhaul_vap_config(apIndices[index], &org_map.vap_array[0]);
                    if (returnStatus == 0)
                    {
                        /* Initialize the values to be set */
			tmp_map = org_map;
			tmp_map.num_vaps = 1;
                        /* Set security mode as WPA2-PERSONAL and enable isolation  */
                        tmp_map.vap_array[0].u.bss_info.security.mode = wifi_security_mode_wpa2_personal;
                        tmp_map.vap_array[0].u.bss_info.isolation = TRUE;

                        UT_LOG("Setting the security mode as wpa2-personal and Isolation Enabled as TRUE");
                        result = wifi_createVAP(radioIndex, &tmp_map);
                        UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );
                        UT_LOG("Setting security mode as wpa2-personal, Isolation Enabled as TRUE using wifi_createVAP for backhaul ap_index %d of radio %d returns : %d", apIndices[index], radioIndex, result);

			/* Setting the config back to default values */
			result = wifi_createVAP(radioIndex, &org_map);
			UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );
			UT_LOG("Setting the config back to default values for backhaul ap_index %d of radio %d returns : %d", apIndices[index], radioIndex, result);
                    }
                    else
                    {
                        UT_LOG("Unable to parse the vap config file");
                    }
                }
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

    UT_LOG("Exiting test_createVAP_backhaul_valid_tc1...");
    return;
}

/**
* @brief This function checks if wifi_createVAP() works as expected on setting WPA3-TRANSITION as security mode for backhaul vaps
*
* Calls the header function wifi_createVAP() with correct params
*
* **Test Group ID:** Basic: 01@n
* **Test Case ID:** 018@n
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
* |01|call wifi_createVAP() with valid arguments for apIndex 12 | apIndex=12, map=valid buffer of type wifi_vap_info_map_t with map.num_vaps=1, map.vap_array[0].u.bss_info.security.mode=wifi_security_mode_wpa3_transition, map.vap_array[0].u.bss_info.isolation=TRUE | WIFI_HAL_SUCCESS | Should Pass |
* |02|call wifi_createVAP() with valid arguments for apIndex 13 | apIndex=13, map=valid buffer of type wifi_vap_info_map_t with map.num_vaps=1, map.vap_array[0].u.bss_info.security.mode=wifi_security_mode_wpa3_transition, map.vap_array[0].u.bss_info.isolation=TRUE | WIFI_HAL_SUCCESS | Should Pass |
*/
void test_createVAP_backhaul_valid_tc2(void)
{
    UT_LOG("Entering test_createVAP_backhaul_valid_tc2...");

    int * apIndices = NULL;
    int index = 0;
    int result = 0;
    int radioIndex = 0;
    int returnStatus = 0;
    wifi_vap_info_map_t  tmp_map, org_map;
    unsigned int numRadios = 0;

    /* Get the number of radios applicable */
    returnStatus = test_utils_getMaxNumberOfRadio(&numRadios);

    if (returnStatus == 0)
    {
        UT_LOG("Number of Radios : %u", numRadios);

        /* Postive Test WIFI_HAL_SUCCESS */
        /* Setting security mode as wpa3-transition, Isolation Enabled as TRUE and expecting the API to return success */
        UT_LOG("Test Case 1");

        /* Allocate memory to store the apIndices */
        apIndices = (int *)malloc( sizeof(int) * numRadios );

        if (apIndices != NULL)
        {
            /* Get the list of backhaul access points corresponding to each of the supported radios */
	    returnStatus = test_utils_getApIndices(numRadios, apIndices, BACKHAUL);

	    if (returnStatus == 0)
            {
                for (radioIndex = 0; radioIndex < numRadios; radioIndex++, index++)
                {
                    /* Get the vap configuration */
                    returnStatus = get_mesh_backhaul_vap_config(apIndices[index], &org_map.vap_array[0]);
                    if (returnStatus == 0)
                    {
                        /* Initialize the values to be set */
	                tmp_map = org_map;
                        tmp_map.num_vaps = 1;
                        /* Set security mode as WPA3-TRANSITION and enable isolation  */
                        tmp_map.vap_array[0].u.bss_info.security.mode = wifi_security_mode_wpa3_transition;
                        tmp_map.vap_array[0].u.bss_info.isolation = TRUE;

                        UT_LOG("Setting the security mode as wpa3-transition and Isolation Enabled as TRUE");
                        result = wifi_createVAP(radioIndex, &tmp_map);
                        UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );
                        UT_LOG("Setting security mode as wpa3-transition, Isolation Enabled as TRUE using wifi_createVAP for backhaul ap_index %d of radio %d returns : %d", apIndices[index], radioIndex, result);

                        /* Setting the config back to default values */
                        result = wifi_createVAP(radioIndex, &org_map);
                        UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );
                        UT_LOG("Setting the config back to default values for backhaul ap_index %d of radio %d returns : %d", apIndices[index], radioIndex, result);
                    }
                    else
                    {
                        UT_LOG("Unable to parse the vap config file");
                    }
                }
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

    UT_LOG("Exiting test_createVAP_backhaul_valid_tc2...");
    return;
}

/**
* @brief This function checks if wifi_createVAP() works as expected on setting WPA3-PERSONAL as security mode for backhaul vaps
*
* Calls the header function wifi_createVAP() with correct params
*
* **Test Group ID:** Basic: 01@n
* **Test Case ID:** 019@n
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
* |01|call wifi_createVAP() with valid arguments for apIndex 12 | apIndex=12, map=valid buffer of type wifi_vap_info_map_t with map.num_vaps=1, map.vap_array[0].u.bss_info.security.mode=wifi_security_mode_wpa3_personal, map.vap_array[0].u.bss_info.isolation=TRUE | WIFI_HAL_SUCCESS | Should Pass |
* |02|call wifi_createVAP() with valid arguments for apIndex 13 | apIndex=13, map=valid buffer of type wifi_vap_info_map_t with map.num_vaps=1, map.vap_array[0].u.bss_info.security.mode=wifi_security_mode_wpa3_personal, map.vap_array[0].u.bss_info.isolation=TRUE | WIFI_HAL_SUCCESS | Should Pass |
*/
void test_createVAP_backhaul_valid_tc3(void)
{
    UT_LOG("Entering test_createVAP_backhaul_valid_tc3...");

    int * apIndices = NULL;
    int index = 0;
    int result = 0;
    int radioIndex = 0;
    int returnStatus = 0;
    wifi_vap_info_map_t  tmp_map, org_map;
    unsigned int numRadios = 0;

    /* Get the number of radios applicable */
    returnStatus = test_utils_getMaxNumberOfRadio(&numRadios);

    if (returnStatus == 0)
    {
        UT_LOG("Number of Radios : %u", numRadios);

        /* Postive Test WIFI_HAL_SUCCESS */
        /* Setting security mode as wpa3-personal, Isolation Enabled as TRUE and expecting the API to return success */
        UT_LOG("Test Case 1");

        /* Allocate memory to store the apIndices */
        apIndices = (int *)malloc( sizeof(int) * numRadios );

        if (apIndices != NULL)
        {
            /* Get the list of backhaul access points corresponding to each of the supported radios */
	    returnStatus = test_utils_getApIndices(numRadios, apIndices, BACKHAUL);

	    if (returnStatus == 0)
            {
               for (radioIndex = 0; radioIndex < numRadios; radioIndex++, index++)
                {
                    /* Get the vap configuration */
                    returnStatus = get_mesh_backhaul_vap_config(apIndices[index], &org_map.vap_array[0]);
                    if (returnStatus == 0)
                    {
                        /* Initialize the values to be set */
			tmp_map = org_map;
			tmp_map.num_vaps = 1;
			/* Set security mode as WPA3-PERSONAL and enable isolation  */
			tmp_map.vap_array[0].u.bss_info.security.mode = wifi_security_mode_wpa3_personal;
                        tmp_map.vap_array[0].u.bss_info.isolation = TRUE;

                        UT_LOG("Setting the security mode as wpa3-personal and Isolation Enabled as TRUE");
                        result = wifi_createVAP(radioIndex, &tmp_map);
                        UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );
                        UT_LOG("Setting security mode as wpa3-personal, Isolation Enabled as TRUE using wifi_createVAP for backhaul ap_index %d of radio %d returns : %d", apIndices[index], radioIndex, result);

                        /* Setting the config back to default values */
                        result = wifi_createVAP(radioIndex, &org_map);
                        UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );
                        UT_LOG("Setting the config back to default values for backhaul ap_index %d of radio %d returns : %d", apIndices[index], radioIndex, result);
                    }
                    else
                    {
                        UT_LOG("Unable to parse the vap config file");
                    }
                }
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

    UT_LOG("Exiting test_createVAP_backhaul_valid_tc3...");
    return;
}	

/**
* @brief This function checks if wifi_createVAP() works as expected on setting invalid security mode for backhaul vaps
*
* Calls the header function wifi_createVAP() with incorrect params
*
* **Test Group ID:** Basic: 01@n
* **Test Case ID:** 020@n
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
* |01|call wifi_createVAP() with invalid security mode for apIndex 12 | apIndex=12, map=buffer of type wifi_vap_info_map_t with map.num_vaps=1, map.vap_array[0].u.bss_info.security.mode=wifi_security_mode_wpa_wpa2_enterprise | WIFI_HAL_INVALID_ARGUMENTS| Should Fail |
* |02|call wifi_createVAP() with invalid security mode for apIndex 13 | apIndex=13, map=buffer of type wifi_vap_info_map_t with map.num_vaps=1, map.vap_array[0].u.bss_info.security.mode=wifi_security_mode_wpa_wpa2_enterprise | WIFI_HAL_INVALID_ARGUMENTS| Should Fail |
*/
void test_createVAP_backhaul_invalid(void)
{
    UT_LOG("Entering test_createVAP_backhaul_invalid...");

    int * apIndices = NULL;
    int index = 0;
    int result = 0;
    int radioIndex = 0;
    int returnStatus = 0;
    wifi_vap_info_map_t  tmp_map, org_map;
    unsigned int numRadios = 0;

    /* Get the number of radios applicable */
    returnStatus = test_utils_getMaxNumberOfRadio(&numRadios);

    if (returnStatus == 0)
    {
        UT_LOG("Number of Radios : %u", numRadios);

        /* Negative Test WIFI_HAL_INVALID_ARGUMENTS */
        /* Setting invalid security mode and expecting the API to return failure */
        UT_LOG("Test Case 1");

        /* Allocate memory to store the apIndices */
        apIndices = (int *)malloc( sizeof(int) * numRadios );

        if (apIndices != NULL)
        {
            /* Get the list of backhaul access points corresponding to each of the supported radios */
	    returnStatus = test_utils_getApIndices(numRadios, apIndices, BACKHAUL);

	    if (returnStatus == 0)
            {
               for (radioIndex = 0; radioIndex < numRadios; radioIndex++, index++)
                {
                    /* Get the vap configuration */
                    returnStatus = get_mesh_backhaul_vap_config(apIndices[index], &org_map.vap_array[0]);
                    if (returnStatus == 0)
                    {
                        /* Initialize the values to be set */
                        tmp_map = org_map;
                        tmp_map.num_vaps = 1;
                        /* Set invalid security mode */
                        tmp_map.vap_array[0].u.bss_info.security.mode = wifi_security_mode_wpa_wpa2_enterprise;

                        UT_LOG("Setting the invalid security mode wpa-wpa2-enterprise");
                        result = wifi_createVAP(radioIndex, &tmp_map);
                        UT_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS );
                        UT_LOG("Setting invalid security mode using wifi_createVAP for backhaul ap_index %d of radio %d returns : %d", apIndices[index], radioIndex, result);

			if(result == WIFI_HAL_SUCCESS)
                        {
                            /* Setting the config back to default values */
                            result = wifi_createVAP(radioIndex, &org_map);
                            UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );
                            UT_LOG("Setting the config back to default values for private ap_index %d of radio %d returns : %d", apIndices[index], radioIndex, result);
                        }
                    }
                    else
                    {
                        UT_LOG("Unable to parse the vap config file");
                    }
                }
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

    UT_LOG("Exiting test_createVAP_backhaul_invalid...");
    return;
}

/**
* @brief This function checks if wifi_createVAP() works as expected on setting WPA2-PERSONAL as security mode for lnf-psk vaps
*
* Calls the header function wifi_createVAP() with correct params
*
* **Test Group ID:** Basic: 01@n
* **Test Case ID:** 021@n
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
* |01|call wifi_createVAP() with valid arguments for apIndex 6 | apIndex=6, map=valid buffer of type wifi_vap_info_map_t with map.num_vaps=1, map.vap_array[0].u.bss_info.security.mode=wifi_security_mode_wpa2_personal, map.vap_array[0].u.bss_info.isolation=TRUE | WIFI_HAL_SUCCESS | Should Pass |
* |02|call wifi_createVAP() with valid arguments for apIndex 7 | apIndex=7, map=valid buffer of type wifi_vap_info_map_t with map.num_vaps=1, map.vap_array[0].u.bss_info.security.mode=wifi_security_mode_wpa2_personal, map.vap_array[0].u.bss_info.isolation=TRUE | WIFI_HAL_SUCCESS | Should Pass |
*/
void test_createVAP_lnfpsk_valid_tc1(void)
{
    UT_LOG("Entering test_createVAP_lnfpsk_valid_tc1...");

    int * apIndices = NULL;
    int index = 0;
    int result = 0;
    int radioIndex = 0;
    int returnStatus = 0;
    wifi_vap_info_map_t  tmp_map, org_map;
    unsigned int numRadios = 0;

    /* Get the number of radios applicable */
    returnStatus = test_utils_getMaxNumberOfRadio(&numRadios);

    if (returnStatus == 0)
    {
        UT_LOG("Number of Radios : %u", numRadios);

        /* Postive Test WIFI_HAL_SUCCESS */
        /* Setting security mode as wpa2-personal, Isolation Enabled as TRUE and expecting the API to return success */
        UT_LOG("Test Case 1");

        /* Allocate memory to store the apIndices */
        apIndices = (int *)malloc( sizeof(int) * numRadios );

        if (apIndices != NULL)
        {
            /* Get the list of LNF-PSK access points corresponding to each of the supported radios */
            returnStatus = test_utils_getApIndices(numRadios, apIndices, LNF_PSK);

            if (returnStatus == 0)
            {
                for (radioIndex = 0; radioIndex < numRadios; radioIndex++, index++)
                {
                    /* Get the vap configuration */
                    returnStatus = get_lnf_psk_vap_config(apIndices[index], &org_map.vap_array[0]);
                    if (returnStatus == 0)
                    {
                        /* Initialize the values to be set */
                        tmp_map = org_map;
                        tmp_map.num_vaps = 1;
                        /* Set security mode as WPA2-PERSONAL and disable isolation  */
                        tmp_map.vap_array[0].u.bss_info.security.mode = wifi_security_mode_wpa2_personal;
                        tmp_map.vap_array[0].u.bss_info.isolation = TRUE;

                        UT_LOG("Setting the security mode as wpa2-personal and Isolation Enabled as TRUE");
                        result = wifi_createVAP(radioIndex, &tmp_map);
                        UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );
                        UT_LOG("Setting security mode as wpa2-personal, Isolation Enabled as TRUE using wifi_createVAP for lnf_psk ap_index %d of radio %d returns : %d", apIndices[index], radioIndex, result);

                        /* Setting the config back to default values */
                        result = wifi_createVAP(radioIndex, &org_map);
                        UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );
                        UT_LOG("Setting the config back to default values for lnf_psk ap_index %d of radio %d returns : %d", apIndices[index], radioIndex, result);
                    }
                    else
                    {
                        UT_LOG("Unable to parse the vap config file");
                    }
                }
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

    UT_LOG("Exiting test_createVAP_lnfpsk_valid_tc1...");
    return;
}

/**
* @brief This function checks if wifi_createVAP() works as expected on setting invalid security mode for lnf-psk vaps
*
* Calls the header function wifi_createVAP() with incorrect params
*
* **Test Group ID:** Basic: 01@n
* **Test Case ID:** 022@n
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
* |01|call wifi_createVAP() with invalid security mode for apIndex 6 | apIndex=6, map=buffer of type wifi_vap_info_map_t with map.num_vaps=1, map.vap_array[0].u.bss_info.security.mode=wifi_security_mode_wpa_enterprise | WIFI_HAL_INVALID_ARGUMENTS| Should Fail |
* |02|call wifi_createVAP() with invalid security mode for apIndex 7 | apIndex=7, map=buffer of type wifi_vap_info_map_t with map.num_vaps=1, map.vap_array[0].u.bss_info.security.mode=wifi_security_mode_wpa_enterprise | WIFI_HAL_INVALID_ARGUMENTS| Should Fail |
*/
void test_createVAP_lnfpsk_invalid(void)
{
    UT_LOG("Entering test_createVAP_lnfpsk_invalid...");

    int * apIndices = NULL;
    int index = 0;
    int result = 0;
    int radioIndex = 0;
    int returnStatus = 0;
    wifi_vap_info_map_t  tmp_map, org_map;
    unsigned int numRadios = 0;

    /* Get the number of radios applicable */
    returnStatus = test_utils_getMaxNumberOfRadio(&numRadios);

    if (returnStatus == 0)
    {
        UT_LOG("Number of Radios : %u", numRadios);

        /* Negative Test WIFI_HAL_INVALID_ARGUMENTS */
        /* Setting invalid security mode and expecting the API to return failure */
        UT_LOG("Test Case 1");

        /* Allocate memory to store the apIndices */
        apIndices = (int *)malloc( sizeof(int) * numRadios );

        if (apIndices != NULL)
        {
            /* Get the list of LNF-PSK access points corresponding to each of the supported radios */
            returnStatus = test_utils_getApIndices(numRadios, apIndices, LNF_PSK);

            if (returnStatus == 0)
            {
                for (radioIndex = 0; radioIndex < numRadios; radioIndex++, index++)
                {
                    /* Get the vap configuration */
                    returnStatus = get_lnf_psk_vap_config(apIndices[index], &org_map.vap_array[0]);
                    if (returnStatus == 0)
                    {
                        /* Initialize the values to be set */
                        tmp_map = org_map;
                        tmp_map.num_vaps = 1;
                        /* Set invalid security mode */
                        tmp_map.vap_array[0].u.bss_info.security.mode = wifi_security_mode_wpa_enterprise;

                        UT_LOG("Setting the invalid security mode wpa-enterprise");
                        result = wifi_createVAP(radioIndex, &tmp_map);
                        UT_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS );
                        UT_LOG("Setting invalid security mode using wifi_createVAP for lnf_psk ap_index %d of radio %d returns : %d", apIndices[index], radioIndex, result);

                        if(result == WIFI_HAL_SUCCESS)
                        {
                            /* Setting the config back to default values */
                            result = wifi_createVAP(radioIndex, &org_map);
                            UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );
                            UT_LOG("Setting the config back to default values for lnf_psk ap_index %d of radio %d returns : %d", apIndices[index], radioIndex, result);
                        }
                    }
                    else
                    {
                        UT_LOG("Unable to parse the vap config file");
                    }
                }
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

    UT_LOG("Exiting test_createVAP_lnfpsk_invalid...");
    return;
}

/**
* @brief This function checks if wifi_createVAP() works as expected on setting wpa2-enterprise as security mode for lnf radius vaps
*
* Calls the header function wifi_createVAP() with correct params
*
* **Test Group ID:** Basic: 01@n
* **Test Case ID:** 023@n
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
* |01|call wifi_createVAP() with valid arguments for apIndex 10 | apIndex=10, map=valid buffer of type wifi_vap_info_map_t with map.num_vaps=1, map.vap_array[0].u.bss_info.security.mode=wifi_security_mode_wpa2_enterprise, map.vap_array[0].u.bss_info.isolation=TRUE | WIFI_HAL_SUCCESS | Should Pass |
* |02|call wifi_createVAP() with valid arguments for apIndex 11 | apIndex=11, map=valid buffer of type wifi_vap_info_map_t with map.num_vaps=1, map.vap_array[0].u.bss_info.security.mode=wifi_security_mode_wpa2_enterprise, map.vap_array[0].u.bss_info.isolation=TRUE | WIFI_HAL_SUCCESS | Should Pass |
*/
void test_createVAP_lnfradius_valid_tc1(void)
{
    UT_LOG("Entering test_createVAP_lnfradius_valid_tc1...");

    int * apIndices = NULL;
    int index = 0;
    int result = 0;
    int radioIndex = 0;
    int returnStatus = 0;
    wifi_vap_info_map_t  tmp_map, org_map;
    unsigned int numRadios = 0;

    /* Get the number of radios applicable */
    returnStatus = test_utils_getMaxNumberOfRadio(&numRadios);

    if (returnStatus == 0)
    {
        UT_LOG("Number of Radios : %u", numRadios);

        /* Postive Test WIFI_HAL_SUCCESS */
        /* Setting security mode as wpa2-enterprise, Isolation Enabled as TRUE and expecting the API to return success */
        UT_LOG("Test Case 1");

        /* Allocate memory to store the apIndices */
        apIndices = (int *)malloc( sizeof(int) * numRadios );

        if (apIndices != NULL)
        {
            /* Get the list of LNF-RADIUS access points corresponding to each of the supported radios */
            returnStatus = test_utils_getApIndices(numRadios, apIndices, LNF_RADIUS);

            if (returnStatus == 0)
            {
                for (radioIndex = 0; radioIndex < numRadios; radioIndex++, index++)
                {
                    /* Get the vap configuration */
                    returnStatus = get_lnf_radius_vap_config(apIndices[index], &org_map.vap_array[0]);
                    if (returnStatus == 0)
                    {
                        /* Initialize the values to be set */
                        tmp_map = org_map;
                        tmp_map.num_vaps = 1;
                        /* Set security mode as WPA2-ENTERPRISE and enable isolation  */
                        tmp_map.vap_array[0].u.bss_info.security.mode = wifi_security_mode_wpa2_enterprise;
                        tmp_map.vap_array[0].u.bss_info.isolation = TRUE;

                        UT_LOG("Setting the security mode as wpa2-enterprise and Isolation Enabled as TRUE");
                        result = wifi_createVAP(radioIndex, &tmp_map);
                        UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );
                        UT_LOG("Setting security mode as wpa2-enterprise, Isolation Enabled as TRUE using wifi_createVAP for lnf_radius ap_index %d of radio %d returns : %d", apIndices[index], radioIndex, result);

                        /* Setting the config back to default values */
                        result = wifi_createVAP(radioIndex, &org_map);
                        UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );
                        UT_LOG("Setting the config back to default values for lnf_radius ap_index %d of radio %d returns : %d", apIndices[index], radioIndex, result);
                    }
                    else
                    {
                        UT_LOG("Unable to parse the vap config file");
                    }
                }
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

    UT_LOG("Exiting test_createVAP_lnfradius_valid_tc1...");
    return;
}

/**
* @brief This function checks if wifi_createVAP() works as expected on setting invalid security mode for lnf-radius vaps
*
* Calls the header function wifi_createVAP() with incorrect params
*
* **Test Group ID:** Basic: 01@n
* **Test Case ID:** 024@n
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
* |01|call wifi_createVAP() with invalid security mode for apIndex 10 | apIndex=10, map=buffer of type wifi_vap_info_map_t with map.num_vaps=1, map.vap_array[0].u.bss_info.security.mode=wifi_security_mode_wpa_personal | WIFI_HAL_INVALID_ARGUMENTS| Should Fail |
* |02|call wifi_createVAP() with invalid security mode for apIndex 11 | apIndex=11, map=buffer of type wifi_vap_info_map_t with map.num_vaps=1, map.vap_array[0].u.bss_info.security.mode=wifi_security_mode_wpa_personal | WIFI_HAL_INVALID_ARGUMENTS| Should Fail |
*/
void test_createVAP_lnfradius_invalid(void)
{
    UT_LOG("Entering test_createVAP_lnfradius_invalid...");

    int * apIndices = NULL;
    int index = 0;
    int result = 0;
    int radioIndex = 0;
    int returnStatus = 0;
    wifi_vap_info_map_t  tmp_map, org_map;
    unsigned int numRadios = 0;

    /* Get the number of radios applicable */
    returnStatus = test_utils_getMaxNumberOfRadio(&numRadios);

    if (returnStatus == 0)
    {
        UT_LOG("Number of Radios : %u", numRadios);

        /* Negative Test WIFI_HAL_INVALID_ARGUMENTS */
        /* Setting invalid security mode and expecting the API to return failure */
        UT_LOG("Test Case 1");

        /* Allocate memory to store the apIndices */
        apIndices = (int *)malloc( sizeof(int) * numRadios );

        if (apIndices != NULL)
        {
            /* Get the list of LNF-RADIUS access points corresponding to each of the supported radios */
            returnStatus = test_utils_getApIndices(numRadios, apIndices, LNF_RADIUS);

            if (returnStatus == 0)
            {
                for (radioIndex = 0; radioIndex < numRadios; radioIndex++, index++)
                {
                    /* Get the vap configuration */
                    returnStatus = get_lnf_radius_vap_config(apIndices[index], &org_map.vap_array[0]);
                    if (returnStatus == 0)
                    {
                        /* Initialize the values to be set */
                        tmp_map = org_map;
                        tmp_map.num_vaps = 1;
                        /* Set invalid security mode */
                        tmp_map.vap_array[0].u.bss_info.security.mode = wifi_security_mode_wpa_personal;

                        UT_LOG("Setting the invalid security mode wpa-personal");
                        result = wifi_createVAP(radioIndex, &tmp_map);
                        UT_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS );
                        UT_LOG("Setting invalid security mode using wifi_createVAP for lnf_radius ap_index %d of radio %d returns : %d", apIndices[index], radioIndex, result);

                        if(result == WIFI_HAL_SUCCESS)
                        {
                            /* Setting the config back to default values */
                            result = wifi_createVAP(radioIndex, &org_map);
                            UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );
                            UT_LOG("Setting the config back to default values for lnf_radius ap_index %d of radio %d returns : %d", apIndices[index], radioIndex, result);
                        }
                    }
                    else
                    {
                        UT_LOG("Unable to parse the vap config file");
                    }
                }
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

    UT_LOG("Exiting test_createVAP_lnfradius_invalid...");
    return;
}

/**
* @brief This function checks if wifi_createVAP() works as expected on setting none as security mode for hotspot open vaps
*
* Calls the header function wifi_createVAP() with correct params
*
* **Test Group ID:** Basic: 01@n
* **Test Case ID:** 025@n
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
* |01|call wifi_createVAP() with valid arguments for apIndex 4 | apIndex=4, map=valid buffer of type wifi_vap_info_map_t with map.num_vaps=1, map.vap_array[0].u.bss_info.security.mode=wifi_security_mode_none, map.vap_array[0].u.bss_info.isolation=TRUE | WIFI_HAL_SUCCESS | Should Pass |
* |02|call wifi_createVAP() with valid arguments for apIndex 5 | apIndex=5, map=valid buffer of type wifi_vap_info_map_t with map.num_vaps=1, map.vap_array[0].u.bss_info.security.mode=wifi_security_mode_none, map.vap_array[0].u.bss_info.isolation=TRUE | WIFI_HAL_SUCCESS | Should Pass |
*/
void test_createVAP_hotspotopen_valid_tc1(void)
{
    UT_LOG("Entering test_createVAP_hotspotopen_valid_tc1...");

    int * apIndices = NULL;
    int index = 0;
    int result = 0;
    int radioIndex = 0;
    int returnStatus = 0;
    wifi_vap_info_map_t  tmp_map, org_map;
    unsigned int numRadios = 0;

    /* Get the number of radios applicable */
    returnStatus = test_utils_getMaxNumberOfRadio(&numRadios);

    if (returnStatus == 0)
    {
        UT_LOG("Number of Radios : %u", numRadios);

        /* Postive Test WIFI_HAL_SUCCESS */
        /* Setting security mode as none, Isolation Enabled as TRUE and expecting the API to return success */
        UT_LOG("Test Case 1");

        /* Allocate memory to store the apIndices */
        apIndices = (int *)malloc( sizeof(int) * numRadios );

        if (apIndices != NULL)
        {
            /* Get the list of HOTSPOT-OPEN access points corresponding to each of the supported radios */
            returnStatus = test_utils_getApIndices(numRadios, apIndices, HOTSPOT_OPEN);

            if (returnStatus == 0)
            {
                for (radioIndex = 0; radioIndex < numRadios; radioIndex++, index++)
                {
                    /* Get the vap configuration */
                    returnStatus = get_hotspot_open_vap_config(apIndices[index], &org_map.vap_array[0]);
                    if (returnStatus == 0)
                    {
                        /* Initialize the values to be set */
                        tmp_map = org_map;
                        tmp_map.num_vaps = 1;
                        /* Set security mode as NONE and enable isolation  */
                        tmp_map.vap_array[0].u.bss_info.security.mode = wifi_security_mode_none;
                        tmp_map.vap_array[0].u.bss_info.isolation = TRUE;

                        UT_LOG("Setting security mode as none and Isolation Enabled as TRUE");
                        result = wifi_createVAP(radioIndex, &tmp_map);
                        UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );
                        UT_LOG("Setting security mode as none, Isolation Enabled as TRUE using wifi_createVAP for hotspot_open ap_index %d of radio %d returns : %d", apIndices[index], radioIndex, result);

                        /* Setting the config back to default values */
                        result = wifi_createVAP(radioIndex, &org_map);
                        UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );
                        UT_LOG("Setting the config back to default values for hotspot_open ap_index %d of radio %d returns : %d", apIndices[index], radioIndex, result);
                    }
                    else
                    {
                        UT_LOG("Unable to parse the vap config file");
                    }
                }
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

    UT_LOG("Exiting test_createVAP_hotspotopen_valid_tc1...");
    return;
}

/**
* @brief This function checks if wifi_createVAP() works as expected on setting invalid security mode for hotspot open vaps
*
* Calls the header function wifi_createVAP() with incorrect params
*
* **Test Group ID:** Basic: 01@n
* **Test Case ID:** 026@n
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
* |01|call wifi_createVAP() with invalid security mode for apIndex 4 | apIndex=4, map=buffer of type wifi_vap_info_map_t with map.num_vaps=1, map.vap_array[0].u.bss_info.security.mode=wifi_security_mode_wpa3_personal | WIFI_HAL_INVALID_ARGUMENTS| Should Fail |
* |02|call wifi_createVAP() with invalid security mode for apIndex 5 | apIndex=5, map=buffer of type wifi_vap_info_map_t with map.num_vaps=1, map.vap_array[0].u.bss_info.security.mode=wifi_security_mode_wpa3_personal | WIFI_HAL_INVALID_ARGUMENTS| Should Fail |
*/
void test_createVAP_hotspotopen_invalid(void)
{
    UT_LOG("Entering test_createVAP_hotspotopen_invalid...");

    int * apIndices = NULL;
    int index = 0;
    int result = 0;
    int radioIndex = 0;
    int returnStatus = 0;
    wifi_vap_info_map_t  tmp_map, org_map;
    unsigned int numRadios = 0;

    /* Get the number of radios applicable */
    returnStatus = test_utils_getMaxNumberOfRadio(&numRadios);

    if (returnStatus == 0)
    {
        UT_LOG("Number of Radios : %u", numRadios);

        /* Negative Test WIFI_HAL_INVALID_ARGUMENTS */
        /* Setting invalid security mode and expecting the API to return failure */
        UT_LOG("Test Case 1");

        /* Allocate memory to store the apIndices */
        apIndices = (int *)malloc( sizeof(int) * numRadios );

        if (apIndices != NULL)
        {
            /* Get the list of HOTSPOT-OPEN access points corresponding to each of the supported radios */
            returnStatus = test_utils_getApIndices(numRadios, apIndices, HOTSPOT_OPEN);

            if (returnStatus == 0)
            {
                for (radioIndex = 0; radioIndex < numRadios; radioIndex++, index++)
                {
                    /* Get the vap configuration */
                    returnStatus = get_hotspot_open_vap_config(apIndices[index], &org_map.vap_array[0]);
                    if (returnStatus == 0)
                    {
                        /* Initialize the values to be set */
                        tmp_map = org_map;
                        tmp_map.num_vaps = 1;
                        /* Set invalid security mode */
                        tmp_map.vap_array[0].u.bss_info.security.mode = wifi_security_mode_wpa3_personal;

                        UT_LOG("Setting the invalid security mode wpa3-personal");
                        result = wifi_createVAP(radioIndex, &tmp_map);
                        UT_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS );
                        UT_LOG("Setting invalid security mode using wifi_createVAP for hotspot_open ap_index %d of radio %d returns : %d", apIndices[index], radioIndex, result);

                        if(result == WIFI_HAL_SUCCESS)
                        {
                            /* Setting the config back to default values */
                            result = wifi_createVAP(radioIndex, &org_map);
                            UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );
                            UT_LOG("Setting the config back to default values for hotspot_open ap_index %d of radio %d returns : %d", apIndices[index], radioIndex, result);
                        }
                    }
                    else
                    {
                        UT_LOG("Unable to parse the vap config file");
                    }
                }
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

    UT_LOG("Exiting test_createVAP_hotspotopen_invalid...");
    return;
}

/**
* @brief This function checks if wifi_createVAP() works as expected on setting wpa2-enterprise as security mode for hotspot secure vaps
*
* Calls the header function wifi_createVAP() with correct params
*
* **Test Group ID:** Basic: 01@n
* **Test Case ID:** 027@n
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
* |01|call wifi_createVAP() with valid arguments for apIndex 8 | apIndex=8, map=valid buffer of type wifi_vap_info_map_t with map.num_vaps=1, map.vap_array[0].u.bss_info.security.mode=wifi_security_mode_wpa2_enterprise, map.vap_array[0].u.bss_info.isolation=TRUE | WIFI_HAL_SUCCESS | Should Pass |
* |02|call wifi_createVAP() with valid arguments for apIndex 9 | apIndex=9, map=valid buffer of type wifi_vap_info_map_t with map.num_vaps=1, map.vap_array[0].u.bss_info.security.mode=wifi_security_mode_wpa2_enterprise, map.vap_array[0].u.bss_info.isolation=TRUE | WIFI_HAL_SUCCESS | Should Pass |
*/
void test_createVAP_hotspotsecure_valid_tc1(void)
{
    UT_LOG("Entering test_createVAP_hotspotsecure_valid_tc1...");

    int * apIndices = NULL;
    int index = 0;
    int result = 0;
    int radioIndex = 0;
    int returnStatus = 0;
    wifi_vap_info_map_t  tmp_map, org_map;
    unsigned int numRadios = 0;

    /* Get the number of radios applicable */
    returnStatus = test_utils_getMaxNumberOfRadio(&numRadios);

    if (returnStatus == 0)
    {
        UT_LOG("Number of Radios : %u", numRadios);

        /* Postive Test WIFI_HAL_SUCCESS */
        /* Setting security mode as wpa2-enterprise, Isolation Enabled as TRUE and expecting the API to return success */
        UT_LOG("Test Case 1");

        /* Allocate memory to store the apIndices */
        apIndices = (int *)malloc( sizeof(int) * numRadios );

        if (apIndices != NULL)
        {
            /* Get the list of HOTSPOT-SECURE access points corresponding to each of the supported radios */
            returnStatus = test_utils_getApIndices(numRadios, apIndices, HOTSPOT_SECURE);

            if (returnStatus == 0)
            {
                for (radioIndex = 0; radioIndex < numRadios; radioIndex++, index++)
                {
                    /* Get the vap configuration */
                    returnStatus = get_hotspot_secure_vap_config(apIndices[index], &org_map.vap_array[0]);
                    if (returnStatus == 0)
                    {
                        /* Initialize the values to be set */
                        tmp_map = org_map;
                        tmp_map.num_vaps = 1;
                        /* Set security mode as WPA2-ENTERPRISE and enable isolation  */
                        tmp_map.vap_array[0].u.bss_info.security.mode = wifi_security_mode_wpa2_enterprise;
                        tmp_map.vap_array[0].u.bss_info.isolation = TRUE;

                        UT_LOG("Setting the security mode as wpa2-enterprise and Isolation Enabled as TRUE");
                        result = wifi_createVAP(radioIndex, &tmp_map);
                        UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );
                        UT_LOG("Setting security mode as wpa2-enterprise, Isolation Enabled as TRUE using wifi_createVAP for hotspot_secure ap_index %d of radio %d returns : %d", apIndices[index], radioIndex, result);

                        /* Setting the config back to default values */
                        result = wifi_createVAP(radioIndex, &org_map);
                        UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );
                        UT_LOG("Setting the config back to default values for hotspot_secure ap_index %d of radio %d returns : %d", apIndices[index], radioIndex, result);
                    }
                    else
                    {
                        UT_LOG("Unable to parse the vap config file");
                    }
                }
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

    UT_LOG("Exiting test_createVAP_hotspotsecure_valid_tc1...");
    return;
}

/**
* @brief This function checks if wifi_createVAP() works as expected on setting invalid security mode for hotspot secure vaps
*
* Calls the header function wifi_createVAP() with incorrect params
*
* **Test Group ID:** Basic: 01@n
* **Test Case ID:** 028@n
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
* |01|call wifi_createVAP() with invalid security mode for apIndex 8 | apIndex=8, map=buffer of type wifi_vap_info_map_t with map.num_vaps=1, map.vap_array[0].u.bss_info.security.mode=wifi_security_mode_wpa3_personal | WIFI_HAL_INVALID_ARGUMENTS| Should Fail |
* |02|call wifi_createVAP() with invalid security mode for apIndex 9 | apIndex=9, map=buffer of type wifi_vap_info_map_t with map.num_vaps=1, map.vap_array[0].u.bss_info.security.mode=wifi_security_mode_wpa3_personal | WIFI_HAL_INVALID_ARGUMENTS| Should Fail |
*/
void test_createVAP_hotspotsecure_invalid(void)
{
    UT_LOG("Entering test_createVAP_hotspotsecure_invalid...");

    int * apIndices = NULL;
    int index = 0;
    int result = 0;
    int radioIndex = 0;
    int returnStatus = 0;
    wifi_vap_info_map_t  tmp_map, org_map;
    unsigned int numRadios = 0;

    /* Get the number of radios applicable */
    returnStatus = test_utils_getMaxNumberOfRadio(&numRadios);

    if (returnStatus == 0)
    {
        UT_LOG("Number of Radios : %u", numRadios);

        /* Negative Test WIFI_HAL_INVALID_ARGUMENTS */
        /* Setting invalid security mode and expecting the API to return failure */
        UT_LOG("Test Case 1");

        /* Allocate memory to store the apIndices */
        apIndices = (int *)malloc( sizeof(int) * numRadios );

        if (apIndices != NULL)
        {
            /* Get the list of HOTSPOT-SECURE access points corresponding to each of the supported radios */
            returnStatus = test_utils_getApIndices(numRadios, apIndices, HOTSPOT_SECURE);

            if (returnStatus == 0)
            {
                for (radioIndex = 0; radioIndex < numRadios; radioIndex++, index++)
                {
                    /* Get the vap configuration */
                    returnStatus = get_hotspot_secure_vap_config(apIndices[index], &org_map.vap_array[0]);
                    if (returnStatus == 0)
                    {
                        /* Initialize the values to be set */
                        tmp_map = org_map;
                        tmp_map.num_vaps = 1;
                        /* Set invalid security mode */
                        tmp_map.vap_array[0].u.bss_info.security.mode = wifi_security_mode_wpa3_personal;

                        UT_LOG("Setting the invalid security mode wpa3-personal");
                        result = wifi_createVAP(radioIndex, &tmp_map);
                        UT_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS );
                        UT_LOG("Setting invalid security mode using wifi_createVAP for hotspot_secure ap_index %d of radio %d returns : %d", apIndices[index], radioIndex, result);

                        if(result == WIFI_HAL_SUCCESS)
                        {
                            /* Setting the config back to default values */
                            result = wifi_createVAP(radioIndex, &org_map);
                            UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );
                            UT_LOG("Setting the config back to default values for hotspot_secure ap_index %d of radio %d returns : %d", apIndices[index], radioIndex, result);
                        }
                    }
                    else
                    {
                        UT_LOG("Unable to parse the vap config file");
                    }
                }
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

    UT_LOG("Exiting test_createVAP_hotspotsecure_invalid...");
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
    UT_add_test( pSuite, "private_valid_tc1", test_createVAP_private_valid_tc1);
    UT_add_test( pSuite, "private_valid_tc2", test_createVAP_private_valid_tc2);
    UT_add_test( pSuite, "private_invalid", test_createVAP_private_invalid);
    UT_add_test( pSuite, "meshsta_valid_tc1", test_createVAP_meshsta_valid_tc1);
    UT_add_test( pSuite, "meshsta_valid_tc2", test_createVAP_meshsta_valid_tc2);
    UT_add_test( pSuite, "meshsta_valid_tc3", test_createVAP_meshsta_valid_tc3);
    UT_add_test( pSuite, "meshsta_invalid", test_createVAP_meshsta_invalid);
    UT_add_test( pSuite, "iot_valid_tc1", test_createVAP_iot_valid_tc1);
    UT_add_test( pSuite, "iot_valid_tc2", test_createVAP_iot_valid_tc2);
    UT_add_test( pSuite, "iot_valid_tc3", test_createVAP_iot_valid_tc3);
    UT_add_test( pSuite, "iot_invalid", test_createVAP_iot_invalid);
    UT_add_test( pSuite, "backhaul_valid_tc1", test_createVAP_backhaul_valid_tc1);
    UT_add_test( pSuite, "backhaul_valid_tc2", test_createVAP_backhaul_valid_tc2);
    UT_add_test( pSuite, "backhaul_valid_tc3", test_createVAP_backhaul_valid_tc3);
    UT_add_test( pSuite, "backhaul_invalid", test_createVAP_backhaul_invalid);
    UT_add_test( pSuite, "lnfpsk_valid_tc1", test_createVAP_lnfpsk_valid_tc1);
    UT_add_test( pSuite, "lnfpsk_invalid", test_createVAP_lnfpsk_invalid);
    UT_add_test( pSuite, "lnfradius_valid_tc1", test_createVAP_lnfradius_valid_tc1);
    UT_add_test( pSuite, "lnfradius_invalid", test_createVAP_lnfradius_invalid);
    UT_add_test( pSuite, "hotspotopen_valid_tc1", test_createVAP_hotspotopen_valid_tc1);
    UT_add_test( pSuite, "hotspotopen_invalid", test_createVAP_hotspotopen_invalid);
    UT_add_test( pSuite, "hotspotsecure_valid_tc1", test_createVAP_hotspotsecure_valid_tc1);
    UT_add_test( pSuite, "hotspotsecure_invalid", test_createVAP_hotspotsecure_invalid);

    return 0;
}
