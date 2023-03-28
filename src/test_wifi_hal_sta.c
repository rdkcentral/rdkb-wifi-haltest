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
#include <time.h>

#include "wifi_hal.h"

#include "PreReqUtility.h"
#include "test_utils.h"
#include "api_translator.h"

#include <ut.h>
#include <ut_log.h>

/* Static function prototypes */
static void timeDelay (unsigned int seconds);
static int sta_init_function();

/**
 * @brief Tests requirements for L1 testing wifi_connect()
 * Test Coverage: Negative Scenarios
 *
 * @retval WIFI_HAL_ERROR               -> tested
 * @retval WIFI_HAL_INVALID_ARGUMENTS   -> tested
 *
 * @Note hal api is Synchronous
 */
void test_sta_wifi_connect(void)
{

    UT_LOG("Entering wifi_connect...");

    int result = 0;
    int returnStatus = 0;
    unsigned int numRadios = 0;
    int * apIndices = NULL;
    int iteration = 0;
    int apIndex_negative = -1;
    int apIndex_outOfRange = 99;
    wifi_bss_info_t bss;

    /* Get the number of radios applicable */
    returnStatus = test_utils_getMaxNumberOfRadio(&numRadios);

    if (returnStatus == 0)
    {
        UT_LOG("Number of Radios : %u", numRadios);

        /* Get the list of sta access points corresponding to each of the supported radios */
        apIndices = (int *)malloc( sizeof(int) * numRadios );

        if(apIndices != NULL)
        {
            returnStatus = test_utils_getApIndices(numRadios, apIndices, STA);
            if (returnStatus == 0)
            {
                UT_LOG("STA AP Indices for the supported radios retrieved");

                /* Negative Test WIFI_HAL_ERROR */
                /* Passing valid sta apIndex, invalid bss info and expecting the API to return failure */
                UT_LOG("Test Case 1");

                for(iteration = 0; iteration < numRadios; iteration ++)
                {
                    result = wifi_connect(apIndices[iteration], &bss);
                    UT_ASSERT_EQUAL( result, WIFI_HAL_ERROR );

                    UT_LOG("Setting invalid bss info for STA AP %d returns : %d", apIndices[iteration], result);
                }

                /* Negative Test WIFI_HAL_INVALID_ARGUMENTS */
                /* Passing valid sta apIndex, NULL bss info and expecting the API to return failure */
                UT_LOG("Test Case 2");

                for(iteration = 0; iteration < numRadios; iteration ++)
                {
                    result = wifi_connect(apIndices[iteration], NULL);
                    UT_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS );

                    UT_LOG("Setting NULL buffer as bss info for STA AP %d returns : %d", apIndices[iteration], result);
                }
            }
            else
            {
                UT_LOG("Unable to retrieve the STA access point indices");
            }
            free(apIndices);
        }
        else
        {
            UT_LOG("Malloc operation failed");
        }

        /* Get the list of private access points corresponding to each of the supported radios */
        apIndices = (int *)malloc( sizeof(int) * numRadios );

        if(apIndices != NULL)
        {
            returnStatus = test_utils_getApIndices(numRadios, apIndices, PRIVATE);
            if (returnStatus == 0)
            {
                UT_LOG("Private AP Indices for the supported radios retrieved");

                /* Negative Test WIFI_HAL_INVALID_ARGUMENTS */
                /* Passing private apIndex, invalid bss info and expecting the API to return failure */
                UT_LOG("Test Case 3");

                for(iteration = 0; iteration < numRadios; iteration ++)
                {
                    result = wifi_connect(apIndices[iteration], &bss);
                    UT_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS );

                    UT_LOG("Setting invalid bss info for Private AP %d returns : %d", apIndices[iteration], result);
                }
            }
            else
            {
                UT_LOG("Unable to retrieve the Private access point indices");
            }
            free(apIndices);
        }
        else
        {
            UT_LOG("Malloc operation failed");
        }

        /* Negative Test WIFI_HAL_INVALID_ARGUMENTS */
        /* Passing negative apIndex, invalid bss info and expecting the API to return failure */
        UT_LOG("Test Case 4");

        result = wifi_connect(apIndex_negative, &bss);
        UT_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS );

        UT_LOG("Setting invalid bss info for AP %d returns : %d", apIndex_negative, result);

        /* Negative Test WIFI_HAL_INVALID_ARGUMENTS */
        /* Passing out of range positive apIndex, invalid bss info and expecting the API to return failure */
        UT_LOG("Test Case 5");

        result = wifi_connect(apIndex_outOfRange, &bss);
        UT_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS );

        UT_LOG("Setting invalid bss info for AP %d returns : %d", apIndex_outOfRange, result);
    }
    else
    {
        UT_LOG("Unable to retrieve the number of radios from HalCapability");
    }

    UT_LOG("Exiting wifi_connect...");
    return;
}

/**
 * @brief Tests requirements for L1 testing wifi_disconnect()
 * Test Coverage: Negative Scenarios
 *
 * @retval WIFI_HAL_ERROR                      -> tested
 * @retval WIFI_HAL_INVALID_ARGUMENTS          -> tested
 *
 * @Note hal api is Synchronous
 */
void test_sta_wifi_disconnect(void)
{

    UT_LOG("Entering wifi_disconnect...");

    int result = 0;
    int returnStatus = 0;
    unsigned int numRadios = 0;
    int * apIndices = NULL;
    int iteration = 0;
    int apIndex_negative = -1;
    int apIndex_outOfRange = 99;

    /* Get the number of radios applicable */
    returnStatus = test_utils_getMaxNumberOfRadio(&numRadios);

    if (returnStatus == 0)
    {
        UT_LOG("Number of Radios : %u", numRadios);

        /* Get the list of sta access points corresponding to each of the supported radios */
        apIndices = (int *)malloc( sizeof(int) * numRadios );

        if(apIndices != NULL)
        {
            returnStatus = test_utils_getApIndices(numRadios, apIndices, STA);
            if (returnStatus == 0)
            {
                UT_LOG("STA AP Indices for the supported radios retrieved");

                /* Negative Test WIFI_HAL_ERROR */
                /* Passing STA apIndex but with no STA connection and expecting the API to return failure */
                UT_LOG("Test Case 1");

                for(iteration = 0; iteration < numRadios; iteration ++)
                {
                    result = wifi_disconnect(apIndices[iteration]);
                    UT_ASSERT_EQUAL( result, WIFI_HAL_ERROR );

                    UT_LOG("Disconnecting for STA AP %d when there is no STA connection returns : %d", apIndices[iteration], result);
                }
            }
            else
            {
                UT_LOG("Unable to retrieve the STA access point indices");
            }
            free(apIndices);
        }
        else
        {
            UT_LOG("Malloc operation failed");
        }

        /* Get the list of private access points corresponding to each of the supported radios */
        apIndices = (int *)malloc( sizeof(int) * numRadios );

        if(apIndices != NULL)
        {
            returnStatus = test_utils_getApIndices(numRadios, apIndices, PRIVATE);
            if (returnStatus == 0)
            {
                UT_LOG("Private AP Indices for the supported radios retrieved");

                /* Negative Test WIFI_HAL_INVALID_ARGUMENTS */
                /* Passing private apIndex with no STA connection and expecting the API to return failure */
                UT_LOG("Test Case 2");

                for(iteration = 0; iteration < numRadios; iteration ++)
                {
                    result = wifi_disconnect(apIndices[iteration]);
                    UT_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS );

                    UT_LOG("Disconnecting for Private AP %d when there is no STA connection returns : %d", apIndices[iteration], result);
                }
            }
            else
            {
                UT_LOG("Unable to retrieve the Private access point indices");
            }
            free(apIndices);
        }
        else
        {
            UT_LOG("Malloc operation failed");
        }

        /* Negative Test WIFI_HAL_INVALID_ARGUMENTS */
        /* Passing negative apIndex and expecting the API to return failure */
        UT_LOG("Test Case 3");

        result = wifi_disconnect(apIndex_negative);
        UT_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS );

        UT_LOG("Disconnecting for AP %d returns : %d", apIndex_negative, result);

        /* Negative Test WIFI_HAL_INVALID_ARGUMENTS */
        /* Passing out of range positive apIndex and expecting the API to return failure */
        UT_LOG("Test Case 4");

        result = wifi_disconnect(apIndex_outOfRange);
        UT_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS );

        UT_LOG("Disconnecting for AP %d returns : %d", apIndex_outOfRange, result);
    }
    else
    {
        UT_LOG("Unable to retrieve the number of radios from HalCapability");
    }

    UT_LOG("Exiting wifi_disconnect...");
    return;

}

/* TODO: This function is commented as it will be invoked only by test_sta_wifi_staConnectionStatus_callback_register */
#if 0
INT test_sta_wifi_staConnectionStatus_callback(INT apIndex, wifi_bss_info_t *bss_dev, wifi_station_stats_t *sta)
{
    (void) apIndex;
    (void) bss_dev;
    (void) sta;
    /* Should not be triggered during this test */
    UT_FAIL( "This function isn't expected to be triggered" );
    return (INT)0;

}
#endif

void test_sta_wifi_staConnectionStatus_callback_register(void)
{
    /* FIXME: Added if 0 to avoid build error. Getting error as this function is present in only in
    OneWifi. Need OneWifi Build to avoid this error*/
#if 0
	/* Positive */
    wifi_staConnectionStatus_callback_register(&test_sta_wifi_staConnectionStatus_callback);
    wifi_staConnectionStatus_callback_register(NULL);
    /* Negative */
#endif
}

/**
 * @brief Tests requirements for L1 testing wifi_startScan()

 * Test Coverage: Positive and Negative Scenarios
 *
 * @retval WIFI_HAL_SUCCESS             -> tested
 * @retval WIFI_HAL_ERROR               -> tested
 * @retval WIFI_HAL_INVALID_ARGUMENTS   -> tested
 *
 * @Note hal api is Synchronous
 */
void test_sta_wifi_startScan(void)
{

    UT_LOG("Entering startScan...");

    int result = 0;
    int returnStatus = 0;
    unsigned int numRadios = 0;
    int radioIndex = 0;
    int dwell_time = 0;
    int row = 0;
    int column = 0;
    int radioIndex_outOfRange = 99;
    unsigned int seconds = 30;
    unsigned int numOfFreq = 0;
    unsigned int * chan_list = NULL;
    const int ch_numbers[][3] = {{1, 6}, {36, 48}, {1, 33}};
    wifi_neighborScanMode_t scan_mode = 0;

    /* Get the number of radios applicable */
    returnStatus = test_utils_getMaxNumberOfRadio(&numRadios);

    if (returnStatus == 0)
    {
        UT_LOG("Number of Radios : %u", numRadios);

        /* Positive Test WIFI_HAL_SUCCESS */
        /* Passing valid radioIndex with scanMode 2, dwell_time 0, numOfFreq 0, chan_list NULL and expecting the API to return success */
        UT_LOG("Test Case 1");
        scan_mode = WIFI_RADIO_SCAN_MODE_ONCHAN;

        for (radioIndex = 0; radioIndex < numRadios; radioIndex ++)
        {
            result = wifi_startScan(radioIndex, scan_mode, dwell_time, numOfFreq, chan_list);
            UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );

            UT_LOG("Setting scanMode %d, dwell_time %d, num_of_frequencies %d, chan_list NULL for radio %d returns : %d", scan_mode, dwell_time, numOfFreq, radioIndex, result);
            printf("\nWaiting for scanning to be over for radio %d...", radioIndex);
	    timeDelay(seconds);
        }

        /* Positive Test WIFI_HAL_SUCCESS */
        /* Passing valid radioIndex with scanMode 3, dwell_time 0, numOfFreq 2, chan_list array with 2 valid channel frequency and expecting the API to return success */
        UT_LOG("Test Case 2");
        scan_mode = WIFI_RADIO_SCAN_MODE_OFFCHAN;
        numOfFreq = 2;

        /* Allocate memory to store the apIndices */
        chan_list = (unsigned int *)malloc( sizeof(unsigned int) * numOfFreq );

        if (chan_list != NULL)
        {
            for (radioIndex = 0; radioIndex < numRadios; radioIndex ++)
            {
                row = radioIndex;
                for (column = 0; column < 2; column ++)
                {
                    chan_list[column] = ch_numbers[row][column];
                }

                result = wifi_startScan(radioIndex, scan_mode, dwell_time, numOfFreq, chan_list);
                UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );

                UT_LOG("Setting scanMode %d, dwell_time %d, num_of_frequencies %d, chan_list[0] %d, chan_list[1] %d for radio %d returns : %d", scan_mode, dwell_time, numOfFreq, chan_list[0], chan_list[1], radioIndex, result);
                printf("\nWaiting for scanning to be over for radio %d...", radioIndex);
                timeDelay(seconds);
            }
            free(chan_list);
        }
        else
        {
            UT_LOG("Malloc operation failed");
        }

        /* Negative Test WIFI_HAL_INVALID_ARGUMENTS */
        /* Passing valid radioIndex with scanMode 2, invalid dwell_time -1, numOfFreq 0, chan_list NULL and expecting the API to return failure */
        UT_LOG("Test Case 3");
        scan_mode = WIFI_RADIO_SCAN_MODE_ONCHAN;
        dwell_time = -1;
        numOfFreq = 0;
        chan_list = NULL;

        for (radioIndex = 0; radioIndex < numRadios; radioIndex ++)
        {
            result = wifi_startScan(radioIndex, scan_mode, dwell_time, numOfFreq, chan_list);
            UT_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS );

            UT_LOG("Setting scanMode %d, dwell_time %d, num_of_frequencies %d, chan_list NULL for radio %d returns : %d", scan_mode, dwell_time, numOfFreq, radioIndex, result);
        }

        /* Negative Test WIFI_HAL_ERROR */
        /* Passing valid radioIndex with scanMode 3, dwell_time 0, numOfFreq 2, chan_list NULL and expecting the API to return failure */
        UT_LOG("Test Case 4");
        scan_mode = WIFI_RADIO_SCAN_MODE_OFFCHAN;
        dwell_time = 0;
        numOfFreq = 2;
        chan_list = NULL;

        for (radioIndex = 0; radioIndex < numRadios; radioIndex ++)
        {
            result = wifi_startScan(radioIndex, scan_mode, dwell_time, numOfFreq, chan_list);
            UT_ASSERT_EQUAL( result, WIFI_HAL_ERROR );

            UT_LOG("Setting scanMode %d, dwell_time %d, num_of_frequencies %d, chan_list NULL for radio %d returns : %d", scan_mode, dwell_time, numOfFreq, radioIndex, result);
        }

        /* Negative Test WIFI_HAL_INVALID_ARGUMENTS */
        /* Passing invalid radioIndex with scanMode 2, dwell_time 0, numOfFreq 0, chan_list NULL and expecting the API to return failure */
        UT_LOG("Test Case 5");
        scan_mode = WIFI_RADIO_SCAN_MODE_ONCHAN;
        dwell_time = 0;
        numOfFreq = 0;
        chan_list = NULL;

        result = wifi_startScan(radioIndex_outOfRange, scan_mode, dwell_time, numOfFreq, chan_list);
        UT_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS );

        UT_LOG("Setting scanMode %d, dwell_time %d, num_of_frequencies %d, chan_list NULL for radio %d returns : %d", scan_mode, dwell_time, numOfFreq, radioIndex_outOfRange, result);
    }
    else
    {
        UT_LOG("Unable to retrieve the number of radios from HalCapability");
    }

    UT_LOG("Exiting startscan...");
    return;

}

/** Function for invoking time delay
 * Description : This function will introduce
 *               a time delay according to the
 *               seconds parameter passed
 **/
static void timeDelay (unsigned int seconds)
{
    unsigned int retTime = time(0) + seconds;
    while (time(0) < retTime);
}

/** Suite Initialization function
* Description : This function is to initialize the wifi-sta suite
*               by creating the required STA configuration for the
*               supported access points.
**/
static int sta_init_function()
{
    static int STA_INIT = FALSE;
    int ret = 0;
    int * apIndices = NULL;
    unsigned int numRadios = 0;
    unsigned int index = 0;

    if (STA_INIT == FALSE)
    {
        UT_LOG("STA Uninitialized; doing init");
        /* Get the number of radios applicable */
        ret = test_utils_getMaxNumberOfRadio(&numRadios);
        if (ret == 0)
        {
            UT_LOG("Number of Radios : %u", numRadios);
            /* Get the list of private access points corresponding to each of the supported radios */
            apIndices = (int *)malloc( sizeof(int) * numRadios );

            if(!apIndices)
            {
                UT_LOG("malloc failed");
                return -1;
            }

            ret = test_utils_getApIndices(numRadios, apIndices, STA);
            if (ret == 0)
	    {
                UT_LOG("STA AP Indices for the supported radios retrieved");

                for (index = 0; index < numRadios; index++)
                {
                    UT_LOG("Calling createVAP");
                    ret = createVAP(index, apIndices[index], STA);

                    if(ret == 0)
                    {
                        UT_LOG("createVAP success for STA Index %d", apIndices[index]);
                    }
                    else
                    {
                        UT_LOG("createVAP failed for STA Index %d",apIndices[index]);
                        free(apIndices);
                        return ret;
                    }
                }
            }
            else
            {
                UT_LOG("STA AP Indices for the supported radios not retrieved");
                free(apIndices);
                return ret;
            }
            free(apIndices);
            STA_INIT = TRUE;
        }
        else
        {
            UT_LOG("Unable to retrieve the number of radios supported from HalCapability");
	    return ret;
        }
    }
    else
    {
        UT_LOG("STA is already initialized");
    }
    return 0;

}

static UT_test_suite_t * pSuite = NULL;

/**
 * @brief Register the main tests for this module
 *
 * @return int - 0 on success, otherwise failure
 */
INT test_wifi_sta_register( void )
{
    /* add a suite to the registry */
    pSuite = UT_add_suite("[L1 wifi-sta]", sta_init_function, NULL);

    if (NULL == pSuite)
    {
        return -1;
    }

    //UT_add_test( pSuite, "wifi_staConnectionStatus_callback_register", test_sta_wifi_staConnectionStatus_callback_register);
    UT_add_test( pSuite, "wifi_startScan", test_sta_wifi_startScan);
    UT_add_test( pSuite, "wifi_connect", test_sta_wifi_connect);
    UT_add_test( pSuite, "wifi_disconnect", test_sta_wifi_disconnect);

    return 0;
}
