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
#include "wifi_hal_ap.h"

#include <ut.h>

/* Values here should be read from a configuration file, that supports the test */
#define TBC_CONFIG_MAX_APS (1)
#define TBC_CONFIG_MAX_RADIOS (2)
#define TBC_CONFIG_AP_INDEX_OUT_OF_RANGE (-1)
#define TBC_RADIO_INDEX_OUT_OF_RANGE (99)

void test_wifi_getApAssociatedDevice(void)
{
    INT result;
    mac_address_t opDeviceMacAddArray[32];
    UINT maxNumDevices = sizeof(opDeviceMacAddArray)/sizeof(mac_address_t);
    UINT returnedOpNumOfDevices = 0;

    // #TODO: Get the number of apIndex's out of the interface?

/*
* @brief Gets the Ap Associated Device list for client MAC addresses
*
* @param[in]  apIndex                Access Point index
* @param[out] opDeviceMacAddArray    List of devices MAC, to be returned
* @param[in]  maxNumDevices          Max number of devices that can be returned
* @param[out] opNumOfDevices         Number of entries returned in the array
INT wifi_getApAssociatedDevice(INT apIndex, mac_address_t *opDeviceMacAddArray, UINT maxNumDevices, UINT *opNumOfDevices);
*/

    // #TODO: maxNumDevices, specified the number of interfaces devices that you can return, but how do you get them all, spec doesn't say.

    // #TODO: Likely need to perform other functions before this one.
    for (int apIndex=0; apIndex< TBC_CONFIG_MAX_APS; apIndex++ )
    {
        /* Positive */
        result = wifi_getApAssociatedDevice(apIndex, &opDeviceMacAddArray[0], maxNumDevices, &returnedOpNumOfDevices);
        UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );

        /* FIXME: Check returnedOpNumOfDevices, against database */
        /* FIXME: Check opDeviceMacAddArray, is there a good way to check expectations against an array */
    }

    /* Negative 0 */
    result = wifi_getApAssociatedDevice(TBC_CONFIG_AP_INDEX_OUT_OF_RANGE, &opDeviceMacAddArray[0], maxNumDevices, &returnedOpNumOfDevices );
    UT_ASSERT_EQUAL( result, WIFI_HAL_ERROR );

    /* Negative 1 */
    result = wifi_getApAssociatedDevice(0, NULL, maxNumDevices, &returnedOpNumOfDevices );
    UT_ASSERT_EQUAL( result, WIFI_HAL_ERROR );

    /* Negative 2 */
    result = wifi_getApAssociatedDevice(0, &opDeviceMacAddArray[0], 0, &returnedOpNumOfDevices );
    UT_ASSERT_EQUAL( result, WIFI_HAL_ERROR );

    /* Negative 3 */
    result = wifi_getApAssociatedDevice(0, &opDeviceMacAddArray[0], maxNumDevices, NULL );
    UT_ASSERT_EQUAL( result, WIFI_HAL_ERROR );
}

#if 0 /* Requires review, this is not defined in the wifi_hal, but maybe in later revisions */

void test_wifi_enableCSIEngine(void)
{
    INT result;
    mac_address_t sta={0};
    BOOL enable;
    INT apIndex;
/*
 * @brief This function enables or disables CSI engine data for a specific STA on a VAP
 * @param[in] apIndex  Index of VAP
 * @param[in] sta      MAC address of the station associated in this VAP for which engine is being enabled/disabled
 * @param[in] enable   Enable or disable
 *
 * @return The status of the operation
 * @retval WIFI_HAL_SUCCESS if successful
 * @retval WIFI_HAL_ERROR if error
 * INT wifi_enableCSIEngine(INT apIndex, mac_address_t sta, BOOL enable);
 */ 
    /* Positive */
    enable = TRUE;
    apIndex = 0;

    result=wifi_enableCSIEngine( apIndex, sta, enable );
    UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );

    enable = FALSE;
    result=wifi_enableCSIEngine( apIndex, sta, enable );
    UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );

    /* Negative */
    result=wifi_enableCSIEngine( TBC_CONFIG_AP_INDEX_OUT_OF_RANGE, sta, enable );
    UT_ASSERT_EQUAL( result, WIFI_HAL_ERROR );

    result=wifi_enableCSIEngine( apIndex, sta, 2 );
    UT_ASSERT_EQUAL( result, WIFI_HAL_ERROR );

}
#endif

void test_wifi_createVAP(void)
{
    INT result;
    wifi_vap_info_map_t  map;
    INT ap_index = 0;
    INT radioIndex = 0;
    INT ap_pointing_index = 0;

    /* Note: wifi_getRadioVapInfoMap() should be tested before this function is ran */

    /* #FIXME: Is there a destroyVAP function? */

    /* #TODO: More testing required of this interface */
    /* Positive */
    for (radioIndex=0;radioIndex< TBC_CONFIG_MAX_RADIOS;radioIndex++ )
    {
        result = wifi_getRadioVapInfoMap(radioIndex, &map);
        UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );

        map.vap_array[ap_pointing_index].vap_index = ap_index;
        //map.vap_array[ap_pointing_index].u.bss_info.ssid[0] ='\0';

        result = wifi_createVAP(radioIndex,&map);
        UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );

        /* #TODO: Check &map params for all configuration values being correct */
    }

    /* Negative */
    for (radioIndex=0;radioIndex< TBC_CONFIG_MAX_RADIOS;radioIndex++ )
    {
        result = wifi_getRadioVapInfoMap(radioIndex, &map);
        UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );

        map.vap_array[ap_pointing_index].vap_index = ap_index;
        map.vap_array[ap_pointing_index].u.bss_info.ssid[0] ='\0';

        result = wifi_createVAP(radioIndex,&map);
        UT_ASSERT_EQUAL( result, WIFI_HAL_ERROR );
    }
}

void test_wifi_getRadioVapInfoMap(void)
{
    INT result;
    wifi_vap_info_map_t  map;
    INT radioIndex = 0;

    /* Positive */
    for (radioIndex=0;radioIndex< TBC_CONFIG_MAX_RADIOS;radioIndex++ )
    {
        result = wifi_getRadioVapInfoMap(radioIndex, &map);
        UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );
    }

    /* Negative */
    result = wifi_getRadioVapInfoMap(TBC_RADIO_INDEX_OUT_OF_RANGE, &map);
    UT_ASSERT_EQUAL( result, WIFI_HAL_ERROR );

    result = wifi_getRadioVapInfoMap(0, NULL);
    UT_ASSERT_EQUAL( result, WIFI_HAL_ERROR );
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
    //UT_add_test( pSuite, "wifi_enableCSIEngine", test_wifi_enableCSIEngine);  /* Needs review */
    UT_add_test( pSuite, "wifi_getRadioVapInfoMap", test_wifi_getRadioVapInfoMap);
    UT_add_test( pSuite, "wifi_createVAP", test_wifi_createVAP);
    //UT_add_test( pSuite, "wifi_mgmt_frame_callbacks_register", test_wifi_mgmt_frame_callbacks_register);  /* Needs review */
    UT_add_test( pSuite, "wifi_newApAssociatedDevice_callback_register", test_wifi_newApAssociatedDevice_callback_register);
    UT_add_test( pSuite, "wifi_apDeAuthEvent_callback_register", test_wifi_apDeAuthEvent_callback_register);
    UT_add_test( pSuite, "wifi_apDisassociatedDevice_callback_register", test_wifi_apDisassociatedDevice_callback_register);

    return 0;
}