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
* @file test_wifi_hal_extender.c
* @page WIFIHAL_Extender WiFi HAL Level 1 Tests - Extender
*
* ## Module's Role
* This module includes Level 1 functional tests (success and failure scenarios).
* This is to ensure that the wifi_getRadioChannelStats() API meets the operational requirements across all vendors.
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
#include "test_utils.h"

#include <ut.h>
#include <ut_log.h>

/**
* @brief This function checks if wifi_getRadioChannelStats() works as expected
*
* Calls the header function wifi_getRadioChannelStats() with correct and incorrect params
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
* |01|call wifi_getRadioChannelStats() with channel in pool as 1 and check if channelStats get populated for radio 0 | radioIndex=0, channelStatsArrayPtr[0].ch_number=1, channelStatsArrayPtr[0].ch_in_pool=1, channelStatsArrayPtr[1].ch_number=6, channelStatsArrayPtr[1].ch_in_pool=1, sizeOfchannelStatsArray=2 | WIFI_HAL_SUCCESS| Should Pass |
* |02|call wifi_getRadioChannelStats() with channel in pool as 1 and check if channelStats get populated for radio 1 | radioIndex=1, channelStatsArrayPtr[0].ch_number=36, channelStatsArrayPtr[0].ch_in_pool=1, channelStatsArrayPtr[1].ch_number=48, channelStatsArrayPtr[1].ch_in_pool=1, sizeOfchannelStatsArray=2 | WIFI_HAL_SUCCESS| Should Pass |
* |03|call wifi_getRadioChannelStats() with channel in pool as 0 and  check if channelStats are zeroes for radio 0 | radioIndex=0, channelStatsArrayPtr[0].ch_number=1, channelStatsArrayPtr[0].ch_in_pool=0, sizeOfchannelStatsArray=1 | WIFI_HAL_SUCCESS| Should Pass |
* |04|call wifi_getRadioChannelStats() with channel in pool as 0 and  check if channelStats are zeroes for radio 1 | radioIndex=1, channelStatsArrayPtr[0].ch_number=36, channelStatsArrayPtr[0].ch_in_pool=0, sizeOfchannelStatsArray=1 | WIFI_HAL_SUCCESS| Should Pass |
* |05|call wifi_getRadioChannelStats() with radioIndex as 0, sizeOfchannelStatsArray as 0 and check if ON channelStats are retrieved | radioIndex=0, channelStatsArrayPtr=0, sizeOfchannelStatsArray=1 | WIFI_HAL_SUCCESS | Should Pass |
* |06|call wifi_getRadioChannelStats() with radioIndex as 1, sizeOfchannelStatsArray as 0 and check if ON channelStats are retrieved | radioIndex=1, channelStatsArrayPtr=0, sizeOfchannelStatsArray=1 | WIFI_HAL_SUCCESS | Should Pass |
* |07|call wifi_getRadioChannelStats() with radioIndex as 0, one instance of channel in pool as 1, check if channelStats get populated and another instance of channel in pool as 0, check if channelStats are zeroes | radioIndex=0, channelStatsArrayPtr[0].ch_number=1, channelStatsArrayPtr[0].ch_in_pool=1, channelStatsArrayPtr[1].ch_number=6, channelStatsArrayPtr[1].ch_in_pool=0, sizeOfchannelStatsArray=2 | WIFI_HAL_SUCCESS| Should Pass |
* |08|call wifi_getRadioChannelStats() with radioIndex as 1, one instance of channel in pool as 1, check if channelStats get populated and another instance of channel in pool as 0, check if channelStats are zeroes | radioIndex=1, channelStatsArrayPtr[0].ch_number=36, channelStatsArrayPtr[0].ch_in_pool=1, channelStatsArrayPtr[1].ch_number=48, channelStatsArrayPtr[1].ch_in_pool=0, sizeOfchannelStatsArray=2 | WIFI_HAL_SUCCESS| Should Pass |
* |09|call wifi_getRadioChannelStats() with NULL buffer as channelStatsArrayPtr for radio 0 | radioIndex=0, channelStatsArrayPtr=NULL, sizeOfchannelStatsArray=1 | WIFI_HAL_INVALID_ARGUMENTS| Should Fail |
* |10|call wifi_getRadioChannelStats() with NULL buffer as channelStatsArrayPtr for radio 1 | radioIndex=1, channelStatsArrayPtr=NULL, sizeOfchannelStatsArray=1 | WIFI_HAL_INVALID_ARGUMENTS| Should Fail |
* |11|call wifi_getRadioChannelStats() with invalid positive channel number for radio 0 | radioIndex=0, channelStatsArrayPtr.ch_number=999, channelStatsArrayPtr.in_pool=1, sizeOfchannelStatsArray=1 | WIFI_HAL_INVALID_ARGUMENTS| Should Fail |
* |12|call wifi_getRadioChannelStats() with invalid positive channel number for radio 1 | radioIndex=1, channelStatsArrayPtr.ch_number=999, channelStatsArrayPtr.in_pool=1, sizeOfchannelStatsArray=1 | WIFI_HAL_INVALID_ARGUMENTS| Should Fail |
* |13|call wifi_getRadioChannelStats() with invalid negative channel number for radio 0 | radioIndex=0, channelStatsArrayPtr.ch_number=-1, channelStatsArrayPtr.in_pool=1, sizeOfchannelStatsArray=1 | WIFI_HAL_INVALID_ARGUMENTS| Should Fail |
* |14|call wifi_getRadioChannelStats() with invalid negative channel number for radio 0 | radioIndex=1, channelStatsArrayPtr.ch_number=-36, channelStatsArrayPtr.in_pool=1, sizeOfchannelStatsArray=1 | WIFI_HAL_INVALID_ARGUMENTS| Should Fail |
* |15|call wifi_getRadioChannelStats() with negative radioIndex | radioIndex=-1, channelStatsArrayPtr.ch_number=1, channelStatsArrayPtr.ch_in_pool=1, sizeOfchannelStatsArray=1 | WIFI_HAL_INVALID_ARGUMENTS| Should Fail |
* |16|call wifi_getRadioChannelStats() with out of range positive radioIndex | radioIndex=99, channelStatsArrayPtr.ch_number=1, channelStatsArrayPtr.ch_in_pool=1, sizeOfchannelStatsArray=1 | WIFI_HAL_INVALID_ARGUMENTS| Should Fail |
*/
void test_extender_wifi_getRadioChannelStats(void)
{

    UT_LOG("Entering getRadioChannelStats...");

    int result = 0;
    int radioIndex = 0;
    int returnStatus = 0;
    int row = 0;
    int column = 0;
    int radioIndex_negative = -1;
    int radioIndex_outOfRange = 99;
    int channel_invalid = 999;
    int sizeOfchannelStatsArray = 1;
    unsigned int numRadios = 0;
    wifi_channelStats_t channelStatsArray;
    wifi_channelStats_t * channelStatsArrayPtr = NULL;
    const int ch_numbers[][2] = {{1, 6}, {36, 48}, {1, 33}};
    const int ch_numbers_negative[3] = {-1, -36, -1};
    int org_ch[2] = {0};

    /* Get the number of radios applicable */
    returnStatus = test_utils_getMaxNumberOfRadio(&numRadios);

    /* TODO : From wifi_getHalCapability() all possible channels for each of the radios can be retrieved.
    For future test enhancements (L2), can loop through all possible channels and get the stats of each */

    if (returnStatus == 0)
    {
        UT_LOG("Number of Radios : %u", numRadios);

        /* Positive Test WIFI_HAL_SUCCESS */
        /* Passing valid radioIndex, valid channelStatsArrayPtr buffer (with valid channel number and channel in pool as 1) and sizeOfchannelStatsArray as 2 and expecting the API to return success */
        UT_LOG("Test Case 1");

        /* Allocate the memory size for channelStatsArrayPtr */
        sizeOfchannelStatsArray = 2;
        channelStatsArrayPtr = (wifi_channelStats_t *)malloc( sizeof(wifi_channelStats_t) * sizeOfchannelStatsArray );

        if (channelStatsArrayPtr != NULL)
        {
            memset(channelStatsArrayPtr, 0, sizeof(wifi_channelStats_t) * sizeOfchannelStatsArray);
            for (radioIndex = 0 ; radioIndex < numRadios; radioIndex ++)
            {
                row = radioIndex;
                for (column = 0; column < 2; column ++)
                {
                    channelStatsArrayPtr[column].ch_number = ch_numbers[row][column];
                    channelStatsArrayPtr[column].ch_in_pool = 1;
                }

                UT_LOG("For Radio %d, Channel Number[0] : %d and Channel in Pool[0] : %d, Channel Number[1] : %d and Channel in Pool[1]: %d", radioIndex, channelStatsArrayPtr[0].ch_number, channelStatsArrayPtr[0].ch_in_pool, channelStatsArrayPtr[1].ch_number, channelStatsArrayPtr[1].ch_in_pool);

                /* Invoke the API */
                result = wifi_getRadioChannelStats(radioIndex, channelStatsArrayPtr, sizeOfchannelStatsArray);
                UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );

                UT_LOG("Passing radioIndex as %d, valid channelStatsArrayPtr buffer (with valid channel numbers and channel in pool as 1) and sizeOfchannelStatsArray as %d returns : %d", radioIndex, sizeOfchannelStatsArray, result);

                if (result == WIFI_HAL_SUCCESS)
                {
                    for (column = 0; column < 2; column ++)
                    {
                        UT_LOG("Channel Stats : ch_number=%d, ch_in_pool=%d, ch_noise=%d, ch_radar_noise=%d, ch_max_80211_rssi=%d, ch_non_80211_noise=%d, ch_utilization=%d, ch_utilization_total=%llu, ch_utilization_busy=%llu, ch_utilization_busy_tx=%llu, ch_utilization_busy_rx=%llu, ch_utilization_busy_self=%llu, ch_utilization_busy_ext=%llu", channelStatsArrayPtr[column].ch_number, channelStatsArrayPtr[column].ch_in_pool, channelStatsArrayPtr[column].ch_noise, channelStatsArrayPtr[column].ch_radar_noise, channelStatsArrayPtr[column].ch_max_80211_rssi, channelStatsArrayPtr[column].ch_non_80211_noise, channelStatsArrayPtr[column].ch_utilization, channelStatsArrayPtr[column].ch_utilization_total, channelStatsArrayPtr[column].ch_utilization_busy, channelStatsArrayPtr[column].ch_utilization_busy_tx, channelStatsArrayPtr[column].ch_utilization_busy_rx, channelStatsArrayPtr[column].ch_utilization_busy_self, channelStatsArrayPtr[column].ch_utilization_busy_ext);

                        /* Check if Stats are properly received by checking if all Stats are NOT zero */
                        if ((channelStatsArrayPtr[column].ch_noise != 0) || (channelStatsArrayPtr[column].ch_radar_noise != 0) || (channelStatsArrayPtr[column].ch_max_80211_rssi != 0)|| (channelStatsArrayPtr[column].ch_non_80211_noise != 0) || (channelStatsArrayPtr[column].ch_utilization != 0) || (channelStatsArrayPtr[column].ch_utilization_total != 0)|| (channelStatsArrayPtr[column].ch_utilization_busy != 0) || (channelStatsArrayPtr[column].ch_utilization_busy_tx != 0)|| (channelStatsArrayPtr[column].ch_utilization_busy_rx != 0) || (channelStatsArrayPtr[column].ch_utilization_busy_self != 0)|| (channelStatsArrayPtr[column].ch_utilization_busy_ext != 0))
                        {
                            UT_PASS("Stats values retrieved are valid");
                            UT_LOG("Stats values retrieved are valid");
                        }
                        else
                        {
                            UT_FAIL("Stats values retrieved are NOT valid");
                            UT_LOG("Stats values retrieved are NOT valid");
                        }
                    }
                }
            }
            free(channelStatsArrayPtr);
        }
        else
        {
            /* TBD : Should the App exit when malloc fails? */
            UT_LOG("Malloc operation failed for Test Case 1");
        }

        /* Positive Test WIFI_HAL_SUCCESS */
        /* Passing valid radioIndex, valid channelStatsArrayPtr buffer (with valid channel number and channel in pool as 0) and sizeOfchannelStatsArray as 1 and expecting the API to return success while also skipping population of stats values for that particular channel */

        UT_LOG("Test Case 2");

        /* Allocate the memory size for channelStatsArrayPtr */
        sizeOfchannelStatsArray = 1;
        channelStatsArrayPtr = (wifi_channelStats_t *)malloc( sizeof(wifi_channelStats_t) * sizeOfchannelStatsArray );

        if (channelStatsArrayPtr != NULL)
        {
            memset(channelStatsArrayPtr, 0, sizeof(wifi_channelStats_t) * sizeOfchannelStatsArray);
            for (radioIndex = 0 ; radioIndex < numRadios; radioIndex ++)
            {
                row = radioIndex;
                channelStatsArrayPtr[0].ch_number = ch_numbers[row][0];
                channelStatsArrayPtr[0].ch_in_pool = 0;

                UT_LOG("For Radio %d, Channel Number : %d and Channel in Pool : %d", radioIndex, channelStatsArrayPtr[0].ch_number, channelStatsArrayPtr[0].ch_in_pool);

                /* Invoke the API */
                result = wifi_getRadioChannelStats(radioIndex, channelStatsArrayPtr, sizeOfchannelStatsArray);
                UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );

                UT_LOG("Passing radioIndex as %d, valid channelStatsArrayPtr buffer (with valid channel number and channel in pool as 0) and sizeOfchannelStatsArray as %d returns : %d", radioIndex, sizeOfchannelStatsArray, result);

                if (result == WIFI_HAL_SUCCESS)
                {
                    UT_LOG("Channel Stats : ch_number=%d, ch_in_pool=%d, ch_noise=%d, ch_radar_noise=%d, ch_max_80211_rssi=%d, ch_non_80211_noise=%d, ch_utilization=%d, ch_utilization_total=%llu, ch_utilization_busy=%llu, ch_utilization_busy_tx=%llu, ch_utilization_busy_rx=%llu, ch_utilization_busy_self=%llu, ch_utilization_busy_ext=%llu", channelStatsArrayPtr[0].ch_number, channelStatsArrayPtr[0].ch_in_pool, channelStatsArrayPtr[0].ch_noise, channelStatsArrayPtr[0].ch_radar_noise, channelStatsArrayPtr[0].ch_max_80211_rssi, channelStatsArrayPtr[0].ch_non_80211_noise, channelStatsArrayPtr[0].ch_utilization, channelStatsArrayPtr[0].ch_utilization_total, channelStatsArrayPtr[0].ch_utilization_busy, channelStatsArrayPtr[0].ch_utilization_busy_tx, channelStatsArrayPtr[0].ch_utilization_busy_rx, channelStatsArrayPtr[0].ch_utilization_busy_self, channelStatsArrayPtr[0].ch_utilization_busy_ext);

                    /* Check if the Stats values retrieved are 0 */
                    if ((channelStatsArrayPtr[0].ch_noise == 0) && (channelStatsArrayPtr[0].ch_radar_noise == 0) && (channelStatsArrayPtr[0].ch_max_80211_rssi == 0)&& (channelStatsArrayPtr[0].ch_non_80211_noise == 0) && (channelStatsArrayPtr[0].ch_utilization == 0) && (channelStatsArrayPtr[0].ch_utilization_total == 0)&& (channelStatsArrayPtr[0].ch_utilization_busy == 0) && (channelStatsArrayPtr[0].ch_utilization_busy_tx == 0)&& (channelStatsArrayPtr[0].ch_utilization_busy_rx == 0) && (channelStatsArrayPtr[0].ch_utilization_busy_self == 0)&& (channelStatsArrayPtr[0].ch_utilization_busy_ext == 0))
                    {
                        UT_PASS("Stats values retrieved are 0 as the channel is not in pool");
                        UT_LOG("Stats values retrieved are 0 as the channel is not in pool");
                    }
                    else
                    {
                        UT_FAIL("Stats values are retrieved when the channel is not in pool");
                        UT_LOG("Stats values are retrieved when the channel is not in pool");
                    }
                }
            }

            free(channelStatsArrayPtr);
        }
        else
        {
            UT_LOG("Malloc operation failed for Test Case 2");
        }

        /* Positive Test WIFI_HAL_SUCCESS */
        /* Passing valid radioIndex, valid channelStatsArray buffer and sizeOfchannelStatsArray as 0 and expecting the API to return success with ON CHAN stats */
        sizeOfchannelStatsArray = 0;
        UT_LOG("Test Case 3");

        for (radioIndex = 0 ; radioIndex < numRadios; radioIndex ++)
        {
            memset(&channelStatsArray, 0, sizeof(wifi_channelStats_t));

            /* Invoke the API */
            result = wifi_getRadioChannelStats(radioIndex, &channelStatsArray, sizeOfchannelStatsArray);
            UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );

            UT_LOG("Passing radioIndex as %d, valid channelStatsArray buffer and sizeOfchannelStatsArray as %d returns : %d", radioIndex, sizeOfchannelStatsArray, result);

            if (result == WIFI_HAL_SUCCESS)
            {
                UT_LOG("ON CHAN Stats : ch_number=%d, ch_in_pool=%d, ch_noise=%d, ch_radar_noise=%d, ch_max_80211_rssi=%d, ch_non_80211_noise=%d, ch_utilization=%d, ch_utilization_total=%llu, ch_utilization_busy=%llu, ch_utilization_busy_tx=%llu, ch_utilization_busy_rx=%llu, ch_utilization_busy_self=%llu, ch_utilization_busy_ext=%llu", channelStatsArray.ch_number, channelStatsArray.ch_in_pool, channelStatsArray.ch_noise, channelStatsArray.ch_radar_noise, channelStatsArray.ch_max_80211_rssi, channelStatsArray.ch_non_80211_noise, channelStatsArray.ch_utilization, channelStatsArray.ch_utilization_total, channelStatsArray.ch_utilization_busy, channelStatsArray.ch_utilization_busy_tx, channelStatsArray.ch_utilization_busy_rx, channelStatsArray.ch_utilization_busy_self, channelStatsArray.ch_utilization_busy_ext);

                /* Check if ON CHAN stats retrieved are valid */
                if ((channelStatsArray.ch_number > 0) && (channelStatsArray.ch_number < 166))
                {
                    UT_PASS("ON CHAN stats retrieved are valid");
                    UT_LOG("ON CHAN stats retrieved are valid");
                }
                else
                {
                    UT_FAIL("ON CHAN stats retrieved are NOT valid");
                    UT_LOG("ON CHAN stats retrieved are NOT valid");
                }
            }
        }

        /* Positive Test WIFI_HAL_SUCCESS */
        /* Passing valid radioIndex, valid channelStatsArrayPtr buffer (with valid channel number and channel in pool as 1 and another instance with valid channel number and channel in pool as 0) and sizeOfchannelStatsArray as 2 and expecting the API to return success */
        UT_LOG("Test Case 4");

        /* Allocate the memory size for channelStatsArrayPtr */
        sizeOfchannelStatsArray = 2;
        channelStatsArrayPtr = (wifi_channelStats_t *)malloc( sizeof(wifi_channelStats_t) * sizeOfchannelStatsArray );

        if (channelStatsArrayPtr != NULL)
        {
            memset(channelStatsArrayPtr, 0, sizeof(wifi_channelStats_t) * sizeOfchannelStatsArray);
            for (radioIndex = 0 ; radioIndex < numRadios; radioIndex ++)
            {
                row = radioIndex;
                for (column = 0; column < 2; column ++)
                {
                    channelStatsArrayPtr[column].ch_number = ch_numbers[row][column];
                }

                /* Instance 1 is in pool and Instance 2 is not in pool */
                channelStatsArrayPtr[0].ch_in_pool = 1;
                channelStatsArrayPtr[1].ch_in_pool = 0;

		/* Copy the channel numbers to org_ch array before the API call */
		org_ch[0] = channelStatsArrayPtr[0].ch_number;
                org_ch[1] = channelStatsArrayPtr[1].ch_number;

                UT_LOG("For Radio %d, Channel Number[0] : %d and Channel in Pool[0] : %d, Channel Number[1] : %d and Channel in Pool[1] : %d", radioIndex, channelStatsArrayPtr[0].ch_number, channelStatsArrayPtr[0].ch_in_pool, channelStatsArrayPtr[1].ch_number, channelStatsArrayPtr[1].ch_in_pool);

                /* Invoke the API */
                result = wifi_getRadioChannelStats(radioIndex, channelStatsArrayPtr, sizeOfchannelStatsArray);
                UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );

                UT_LOG("Passing radioIndex as %d, valid channelStatsArrayPtr buffer (with valid channel number %d and channel in pool as 1 and another instance with valid channel number %d and channel in pool as 0) and sizeOfchannelStatsArray as %d returns : %d", radioIndex, channelStatsArrayPtr[0].ch_number, channelStatsArrayPtr[1].ch_number, sizeOfchannelStatsArray, result);

                if (result == WIFI_HAL_SUCCESS)
                {
                    for (column = 0; column < 2; column ++)
                    {
                        UT_LOG("Channel Stats : ch_number=%d, ch_in_pool=%d, ch_noise=%d, ch_radar_noise=%d, ch_max_80211_rssi=%d, ch_non_80211_noise=%d, ch_utilization=%d, ch_utilization_total=%llu, ch_utilization_busy=%llu, ch_utilization_busy_tx=%llu, ch_utilization_busy_rx=%llu, ch_utilization_busy_self=%llu, ch_utilization_busy_ext=%llu", channelStatsArrayPtr[column].ch_number, channelStatsArrayPtr[column].ch_in_pool, channelStatsArrayPtr[column].ch_noise, channelStatsArrayPtr[column].ch_radar_noise, channelStatsArrayPtr[column].ch_max_80211_rssi, channelStatsArrayPtr[column].ch_non_80211_noise, channelStatsArrayPtr[column].ch_utilization, channelStatsArrayPtr[column].ch_utilization_total, channelStatsArrayPtr[column].ch_utilization_busy, channelStatsArrayPtr[column].ch_utilization_busy_tx, channelStatsArrayPtr[column].ch_utilization_busy_rx, channelStatsArrayPtr[column].ch_utilization_busy_self, channelStatsArrayPtr[column].ch_utilization_busy_ext);
                    }

		    /* Check if instance 1 channel number is not corrupted */
		    if (channelStatsArrayPtr[0].ch_number != org_ch[0])
	            {
			UT_FAIL("The channel number for instance 1 got corrupted after wifi_getRadioChannelStats() call");
	                UT_LOG("The channel number : %d for instance 1 got corrupted after wifi_getRadioChannelStats() call", channelStatsArrayPtr[0].ch_number);
		    }

                    /* Check if Stats receieved for instance 1 are valid by checking if any of the values are non-zero*/
                    if((channelStatsArrayPtr[0].ch_noise != 0) || (channelStatsArrayPtr[0].ch_radar_noise != 0) || (channelStatsArrayPtr[0].ch_max_80211_rssi != 0)|| (channelStatsArrayPtr[0].ch_non_80211_noise != 0) || (channelStatsArrayPtr[0].ch_utilization != 0) || (channelStatsArrayPtr[0].ch_utilization_total != 0)|| (channelStatsArrayPtr[0].ch_utilization_busy != 0) || (channelStatsArrayPtr[0].ch_utilization_busy_tx != 0)|| (channelStatsArrayPtr[0].ch_utilization_busy_rx != 0) || (channelStatsArrayPtr[0].ch_utilization_busy_self != 0)|| (channelStatsArrayPtr[0].ch_utilization_busy_ext != 0))
                    {
                        UT_PASS("Stats Values retrieved are valid when channel in pool");
                        UT_LOG("Stats Values retrieved are valid for channel %d in pool", channelStatsArrayPtr[0].ch_number);
                    }
                    else
                    {
                        UT_FAIL("Stats Values retrieved are NOT valid when chanel in pool");
                        UT_LOG("Stats Values retrieved are NOT valid for channel %d in pool", channelStatsArrayPtr[0].ch_number);
                    }

		    /* Check if instance 2 channel number is not corrupted */
                    if (channelStatsArrayPtr[1].ch_number != org_ch[1])
                    {
                        UT_FAIL("The channel number for instance 2 got corrupted after wifi_getRadioChannelStats() call");
                        UT_LOG("The channel number : %d for instance 2 got corrupted after wifi_getRadioChannelStats() call", channelStatsArrayPtr[1].ch_number);
                    }

                    /* Check if Stats receieved for instance 2 are valid by checking if population of stats is skipped */
                    if((channelStatsArrayPtr[1].ch_noise == 0) && (channelStatsArrayPtr[1].ch_radar_noise == 0) && (channelStatsArrayPtr[1].ch_max_80211_rssi == 0)&& (channelStatsArrayPtr[1].ch_non_80211_noise == 0) && (channelStatsArrayPtr[1].ch_utilization == 0) && (channelStatsArrayPtr[1].ch_utilization_total == 0)&& (channelStatsArrayPtr[1].ch_utilization_busy == 0) && (channelStatsArrayPtr[1].ch_utilization_busy_tx == 0)&& (channelStatsArrayPtr[1].ch_utilization_busy_rx == 0) && (channelStatsArrayPtr[1].ch_utilization_busy_self == 0)&& (channelStatsArrayPtr[1].ch_utilization_busy_ext == 0))
                    {
                        UT_PASS("Stats Values retrieved are valid when channel not in pool");
                        UT_LOG("Stats Values retrieved are valid for channel %d not in pool", channelStatsArrayPtr[1].ch_number);
                    }
                    else
                    {
                        UT_FAIL("Stats Values are retrieved when channel not in pool");
                        UT_LOG("Stats Values are retrieved when channel %d not in pool", channelStatsArrayPtr[1].ch_number);
                    }
                }
            }

            free(channelStatsArrayPtr);
        }
        else
        {
            UT_LOG("Malloc operation failed for Test Case 4");
        }

        /* Negative Test WIFI_HAL_INVALID_ARGUMENTS */
        /* Passing valid radioIndex, NULL buffer as channelStatsArrayPtr and sizeOfchannelStatsArray as 1 and expecting the API to return failure */
        UT_LOG("Test Case 5");
        sizeOfchannelStatsArray = 1;

        for (radioIndex = 0 ; radioIndex < numRadios; radioIndex ++)
        {
            /* Invoke the API */
            result = wifi_getRadioChannelStats(radioIndex, NULL, sizeOfchannelStatsArray);
            UT_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS );

            UT_LOG("Passing radioIndex as %d, NULL buffer as channelStatsArrayPtr and sizeOfchannelStatsArray as %d returns : %d", radioIndex, sizeOfchannelStatsArray, result);
        }

        /* Negative Test WIFI_HAL_INVALID_ARGUMENTS */
        /* Passing valid radioIndex, invalid channelStatsArrayPtr buffer (with invalid positive channel number and channel in pool as 1) and sizeOfchannelStatsArray as 1 and expecting the API to return failure */
        UT_LOG("Test Case 6");
        sizeOfchannelStatsArray = 1;

        for (radioIndex = 0 ; radioIndex < numRadios; radioIndex ++)
        {
            channelStatsArray.ch_number = channel_invalid;
            channelStatsArray.ch_in_pool = 1;
            UT_LOG("For Radio %d, Invalid Channel Number : %d and Channel in Pool : %d", radioIndex, channelStatsArray.ch_number, channelStatsArray.ch_in_pool);

            /* Invoke the API */
            result = wifi_getRadioChannelStats(radioIndex, &channelStatsArray, sizeOfchannelStatsArray);
            UT_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS );

            UT_LOG("Passing radioIndex as %d, invalid channelStatsArrayPtr buffer (with invalid positive channel number and channel in pool as 1) and sizeOfchannelStatsArray as %d returns : %d", radioIndex, sizeOfchannelStatsArray, result);
        }

        /* Negative Test WIFI_HAL_INVALID_ARGUMENTS */
        /* Passing valid radioIndex, invalid channelStatsArrayPtr buffer (with invalid negative channel number and channel in pool as 1) and sizeOfchannelStatsArray as 1 and expecting the API to return failure */
        UT_LOG("Test Case 7");
        sizeOfchannelStatsArray = 1;

        for (radioIndex = 0 ; radioIndex < numRadios; radioIndex ++)
        {
            row = radioIndex;
            channelStatsArray.ch_number = ch_numbers_negative[row];
            channelStatsArray.ch_in_pool = 1;

            UT_LOG("For Radio %d, Invalid Channel Number : %d and Channel in Pool : %d", radioIndex, channelStatsArray.ch_number, channelStatsArray.ch_in_pool);

            /* Invoke the API */
            result = wifi_getRadioChannelStats(radioIndex, &channelStatsArray, sizeOfchannelStatsArray);
            UT_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS );
            UT_LOG("Passing radioIndex as %d, invalid channelStatsArrayPtr buffer (with invalid negative channel number and channel in pool as 1) and sizeOfchannelStatsArray as %d returns : %d", radioIndex_negative, sizeOfchannelStatsArray, result);
        }

        /* Negative Test WIFI_HAL_INVALID_ARGUMENTS */
        /* Passing negative radioIndex, valid channelStatsArrayPtr buffer (with valid channel number and channel in pool as 1) and sizeOfchannelStatsArray as 1 and expecting the API to return failure */
        sizeOfchannelStatsArray = 1;
        UT_LOG("Test Case 8");

        channelStatsArray.ch_number = ch_numbers[0][0];
        channelStatsArray.ch_in_pool = 1;
        UT_LOG("For Radio %d, Channel Number : %d and Channel in Pool : %d", radioIndex_negative, channelStatsArray.ch_number, channelStatsArray.ch_in_pool);

        /* Invoke the API */
        result = wifi_getRadioChannelStats(radioIndex_negative, &channelStatsArray, sizeOfchannelStatsArray);
        UT_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS );

        UT_LOG("Passing radioIndex as %d, valid channelStatsArrayPtr buffer and sizeOfchannelStatsArray as %d returns : %d", radioIndex_negative, sizeOfchannelStatsArray, result);

        /* Negative Test WIFI_HAL_INVALID_ARGUMENTS */
        /* Passing out of range positive radioIndex, valid channelStatsArrayPtr buffer (with valid channel number and channel in pool as 1) and sizeOfchannelStatsArray as 1 and expecting the API to return failure */
        UT_LOG("Test Case 9");

        channelStatsArray.ch_number = ch_numbers[0][0];
        channelStatsArray.ch_in_pool = 1;
        UT_LOG("For Radio %d, Channel Number : %d and Channel in Pool : %d", radioIndex_outOfRange, channelStatsArray.ch_number, channelStatsArray.ch_in_pool);

        /* Invoke the API */
        result = wifi_getRadioChannelStats(radioIndex_outOfRange, &channelStatsArray, sizeOfchannelStatsArray);
        UT_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS );

        UT_LOG("Passing radioIndex as %d, valid channelStatsArrayPtr buffer and sizeOfchannelStatsArray as %d returns : %d", radioIndex_outOfRange, sizeOfchannelStatsArray, result);
    }
    else
    {
        UT_LOG("Unable to retrieve the number of radios from HalCapability");
    }

    UT_LOG("Exiting getRadioChannelStats...");
    return;

}

static UT_test_suite_t *pSuite = NULL;

/**
 * @brief Register the main tests for this module
 *
 * @return int - 0 on success, otherwise failure
 */
int test_wifi_extender_register( void )
{
    pSuite = UT_add_suite("[L1 wifi-extender]", NULL, NULL);

    if (NULL == pSuite)
    {
        return -1;
    }

    UT_add_test( pSuite, "wifi_getRadioChannelStats", test_extender_wifi_getRadioChannelStats);

    return 0;
}
