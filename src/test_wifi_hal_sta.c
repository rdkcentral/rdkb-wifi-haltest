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
#include "wifi_hal_sta.h"

#include <ut.h>

/* Values here should be read from a configuration file, that supports the test */
#define TBC_CONFIG_MAX_RADIOS (2)
#define TBC_RADIO_INDEX_OUT_OF_RANGE (99)

#define TBC_RADIO_MAX_BW (4)
#define TBC_CONFIG_MAX_BW (7)

void test_sta_wifi_connect(void)
{
    /* FIXME: Added if 0 to avoid build error. Getting error as this function is present in only in
    OneWifi. Need OneWifi Build to avoid this error*/
#if 0
    INT result;
    INT ap_index = 0;
    wifi_bss_info_t *bss;

    /* Positive */
    result = wifi_connect(ap_index,bss);
    UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );

    /* Negative */
    result = wifi_connect(-1, bss);
    UT_ASSERT_EQUAL( result, WIFI_HAL_ERROR );

    result = wifi_connect(1, NULL);
    UT_ASSERT_EQUAL( result, WIFI_HAL_ERROR );

    result = wifi_connect(2, bss);
    UT_ASSERT_EQUAL( result, WIFI_HAL_ERROR );
#endif
}

void test_sta_wifi_disconnect(void)
{
    /* FIXME: Added if 0 to avoid build error. Getting error as this function is present in only in
    OneWifi. Need OneWifi Build to avoid this error*/
#if 0
    INT result;
    INT ap_index = 0;
    wifi_bss_info_t *bss;

    /* Positive */
    //TODO: A client should be connected when this function is called
    result = wifi_disconnect(ap_index);
    UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );

    /* Negative */
    result = wifi_disconnect(-1);
    UT_ASSERT_EQUAL( result, WIFI_HAL_ERROR );

    result = wifi_disconnect(1);
    UT_ASSERT_EQUAL( result, WIFI_HAL_ERROR );

    result = wifi_disconnect(2);
    UT_ASSERT_EQUAL( result, WIFI_HAL_ERROR );
#endif
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

void test_sta_wifi_startScan(void)
{
    /* FIXME: Added if 0 to avoid build error. Getting error as this function is present in only in
    OneWifi. Need OneWifi Build to avoid this error*/
#if 0
    INT result;
    INT i;
    wifi_neighborScanMode_t scan_mode;
    INT dwell_time;
    UINT num;
    UINT chan_list[2];

    /* Positive */
    for(i = 0; i < TBC_CONFIG_MAX_RADIOS; i++)
    {
        if( i == 0 )
        {
            for(int j = 0 ; j < 2; j++)
            {
                chan_list[j] = 1 + (5 * j);
            }
            result = wifi_startScan(i, 1, 0, 2, chan_list);
            UT_ASSERT_EQUAL(result, WIFI_HAL_SUCCESS );
        }
        else
        {
            for(int j = 0 ; j < 2; j++)
            {
                chan_list[j] = 36 + (4 * j);
            }
            result = wifi_startScan(i, 1, 0, 2, chan_list);
            UT_ASSERT_EQUAL(result, WIFI_HAL_SUCCESS );
        }
    }

    /* Negative */
    /* This scan function will throw error when it is called successively without any delay */
    i = 0;
    for(int j = 0 ; j < 2; j++)
    {
        chan_list[j] = 1 + (5 * j);
    }
    result = wifi_startScan(i, 1, 0, 2, chan_list);
    result = wifi_startScan(i, 1, 0, 2, chan_list);
    UT_ASSERT_EQUAL(result, WIFI_HAL_ERROR );

#endif
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
    pSuite = UT_add_suite("[L1 wifi-sta]", NULL, NULL);
    if (NULL == pSuite) 
    {
        return -1;
    }

    UT_add_test( pSuite, "wifi_staConnectionStatus_callback_register", test_sta_wifi_staConnectionStatus_callback_register);
    UT_add_test( pSuite, "wifi_startScan", test_sta_wifi_startScan);
    UT_add_test( pSuite, "wifi_connect", test_sta_wifi_connect);
    UT_add_test( pSuite, "wifi_disconnect", test_sta_wifi_disconnect);

    return 0;
}