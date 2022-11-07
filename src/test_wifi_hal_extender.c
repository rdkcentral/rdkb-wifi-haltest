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
#include "wifi_hal_extender.h"

#include <ut.h>

#define TBC_CONFIG_MAX_RADIOS (2)
#define TBC_RADIO_INDEX_OUT_OF_RANGE (99)
void test_extender_wifi_getRadioChannelStats(void)
{
/*
 * #FIXME Should we use wifi_getRadioChannelStats to get the stats of current channel alone? Or
 * Should we use it to get all the channels?
 *
 * #BUG If wifi_getRadioChannelStats is used to collect stats of all channels, wifi_getRadioPossibleChannels should be called, which is not present in the list of function
*/

    INT result = -1;
    INT radioIndex = 0;
    INT i = 0;
    wifi_channelStats_t input_output_channelStats_array;

    /* Positive */
    for ( radioIndex = 0; radioIndex < TBC_CONFIG_MAX_RADIOS; radioIndex++)
    {
        if(radioIndex == 0)
        {
            input_output_channelStats_array.ch_number = 11;
        }
        else
        {
            input_output_channelStats_array.ch_number = 36;
        }

        input_output_channelStats_array.ch_in_pool = 1;

        /* BUG: There is a similar function wifi_getRadioChannelStats2. Should we implement this function  */
        /* TODO: Need to check the value returned by this function */

        result = wifi_getRadioChannelStats(radioIndex, &input_output_channelStats_array, 1);
        UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );
    }

    /* Negative */
    result = wifi_getRadioChannelStats(-1, &input_output_channelStats_array, i);
    UT_ASSERT_EQUAL( result, WIFI_HAL_ERROR );

    result = wifi_getRadioChannelStats(2, &input_output_channelStats_array, i);
    UT_ASSERT_EQUAL( result, WIFI_HAL_ERROR );

    result = wifi_getRadioChannelStats(0, NULL, i);
    UT_ASSERT_EQUAL( result, WIFI_HAL_ERROR );

    input_output_channelStats_array.ch_number = 206;

    result = wifi_getRadioChannelStats(0, &input_output_channelStats_array, i);
    UT_ASSERT_EQUAL( result, WIFI_HAL_ERROR );

    result = wifi_getRadioChannelStats(0, &input_output_channelStats_array, -1);
    UT_ASSERT_EQUAL( result, WIFI_HAL_ERROR );

}

static UT_test_suite_t *pSuite = NULL;

/**
 * @brief Register the main tests for this module
 *
 * @return int - 0 on success, otherwise failure
 */
int test_wifi_extender_register( void )
{
    /* add a suite to the registry */
    pSuite = UT_add_suite("[L1 wifi-extender]", NULL, NULL);
    if (NULL == pSuite)
    {
        return -1;
    }

    UT_add_test( pSuite, "wifi_getRadioChannelStats", test_extender_wifi_getRadioChannelStats);

    return 0;
}
