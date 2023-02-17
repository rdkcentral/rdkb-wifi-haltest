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


#include <stddef.h>
#include "test_utils.h"

#include <wifi_hal_generic.h>
#include <wifi_hal.h>
#include <wifi_hal_extender.h>
#include <wifi_hal_sta.h>
#include <stdlib.h>
#include <ut.h>
#include <ut_log.h>
#include <config_parser.h>
#include <api_translator.h>

extern wifi_radio_operationParam_t g_operationParam[3];
extern wifi_vap_info_map_t g_org_map[3];

void test_wifi_hal_L2_setValidSSID_2Ghz(void)
{
    INT ap_index = 0; 
    INT radioIndex = 0;
    INT ap_pointing_index = 0;
    int result;

    result = test_utils_setValidSSID(radioIndex, ap_index, ap_pointing_index);
    UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );
    return;
}

void test_wifi_hal_L2_setInValidIndexSSID_2Ghz(void)
{
    INT ap_index = 25; /* Invalid Index */
    INT radioIndex = 0;
    INT ap_pointing_index = 0;
    int result;
    result = test_utils_setInValidIndexSSID(radioIndex, ap_index, ap_pointing_index);
    UT_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS);
    return;
}

void test_wifi_hal_L2_setNULLSSID_2Ghz(void)
{

    INT ap_index = 0;
    INT radioIndex = 0;
    INT ap_pointing_index = 0;
    int result;

    result = test_utils_setNULLSSID(radioIndex, ap_index, ap_pointing_index);
    UT_ASSERT_EQUAL( result, WIFI_HAL_ERROR);
}

void test_wifi_hal_L2_setValidSSID_5Ghz(void)
{
    INT ap_index = 1;
    INT radioIndex = 1;
    INT ap_pointing_index = 0;
    int result;

    result = test_utils_setValidSSID(radioIndex, ap_index, ap_pointing_index);
    UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );
    return;
}

void test_wifi_hal_L2_setInValidIndexSSID_5Ghz(void)
{
    INT ap_index = 25; /* Invalid Index */
    INT radioIndex = 1;
    INT ap_pointing_index = 0;
    int result;
    result = test_utils_setInValidIndexSSID(radioIndex, ap_index, ap_pointing_index);
    UT_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS);
    return;
}

void test_wifi_hal_L2_setNULLSSID_5Ghz(void)
{

    INT ap_index = 1;
    INT radioIndex = 1;
    INT ap_pointing_index = 0;
    int result;

    result = test_utils_setNULLSSID(radioIndex, ap_index, ap_pointing_index);
    UT_ASSERT_EQUAL( result, WIFI_HAL_ERROR);
}

void test_wifi_hal_L2_setValidSSID_6Ghz(void)
{
    INT ap_index = 16;
    INT radioIndex = 2;
    INT ap_pointing_index = 0;
    int result;

    result = test_utils_setValidSSID(radioIndex, ap_index, ap_pointing_index);
    UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );
    return;
}

void test_wifi_hal_L2_setInValidIndexSSID_6Ghz(void)
{
    INT ap_index = 25; /* Invalid Index */
    INT radioIndex = 2;
    INT ap_pointing_index = 0;
    int result;
    result = test_utils_setInValidIndexSSID(radioIndex, ap_index, ap_pointing_index);
    UT_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS);
    return;
}

void test_wifi_hal_L2_setNULLSSID_6Ghz(void)
{

    INT ap_index = 16;
    INT radioIndex = 2;
    INT ap_pointing_index = 0;
    int result;

    result = test_utils_setNULLSSID(radioIndex, ap_index, ap_pointing_index);
    UT_ASSERT_EQUAL( result, WIFI_HAL_ERROR);
}

/* This will test AP Enable/Disable functionality*
* positive case * maps to WIFI_HAL_SUCCESS *
* set main interface AP to disable first and check it through get *
* now set it to enable and check it through get *
* virtaul/guest Enable/Disable set check is not added yet
*
* Negative case * WIFI_HAL_ERROR *
* Try to Enable AP  with wrong AP indexes * Here 25,26,27 are taken as wrong indeces */

#if 0
void test_wifi_hal_L2_setApDisable_2GHz(void)
{
    int result;
    int ap_index = 0;
    BOOL enable;

    /* Positive case */
    /* Disable the APs */
    enable = FALSE;
    result = test_utils_setApEnable (enable, ap_index);
    UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS);
    return;
}

void test_wifi_hal_L2_setApDisable_5GHz(void)
{
    int result;
    int ap_index = 1;
    BOOL enable;

    /* Positive case */
    /* Disable the APs */
    enable = FALSE;
    result = test_utils_setApEnable (enable, ap_index);
    UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS);
    return;
}

void test_wifi_hal_L2_setApDisable_6GHz(void)
{
    int result;
    int ap_index = 16;
    BOOL enable;

    /* Positive case */
    /* Disable the APs */
    enable = FALSE;
    result = test_utils_setApEnable (enable, ap_index);
    UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS);
    return;
}

void test_wifi_hal_L2_setApEnable_2GHz(void)
{
    /* Positive case */
    /* Enable the APs */
    int result;
    int ap_index = 0;
    BOOL enable = TRUE;
    result = test_utils_setApEnable (enable, ap_index);
    UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS);
    return;
}

void test_wifi_hal_L2_setApEnable_5GHz(void)
{
    /* Positive case */
    /* Enable the APs */
    int result;
    int ap_index = 1;
    BOOL enable = TRUE;
    result = test_utils_setApEnable (enable, ap_index);
    UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS);
    return;
}

void test_wifi_hal_L2_setApEnable_6GHz(void)
{
    /* Positive case */
    /* Enable the APs */
    int result;
    int ap_index = 16;
    BOOL enable = TRUE;
    result = test_utils_setApEnable (enable, ap_index);
    UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS);
    return;
}

void test_wifi_hal_L2_setInvalidIndexApDisable(void)
{
    /* Negative case */
    /* Enable  the APs  with wrong index */
    int ap_index=25;
    BOOL enable = FALSE;
    int result;

    result = test_utils_setApEnable (enable, ap_index);
    UT_ASSERT_EQUAL( result, WIFI_HAL_ERROR);

    /* Done */
    return;
}

void test_wifi_hal_L2_setInvalidIndexApEnable(void)
{
    /* Negative case */
    /* Enable  the APs  with wrong index */
    int ap_index=25;
    BOOL enable = TRUE;
    int result;

    result = test_utils_setApEnable (enable, ap_index);
    UT_ASSERT_EQUAL( result, WIFI_HAL_ERROR);

    /* Done */
    return;
}

/* This will test Radio Channel push functionality*
* positive case * maps to WIFI_HAL_SUCCESS *
* set Radios to valid channel and check the value through get*
*
* Negative case * WIFI_HAL_SUCCESS, WIFI_HAL_INVALID_ARGUMENTS *
* Set Radios Invalid Channel *
* Set the channel with wrong radio index *
*/
void test_wifi_L2_Validchannel_push_2GHz(void)
{
    /* set 2.4 GHz channel first */

    /* Positive */
    /* Set it for a valid channel e.g 13 */
    /* Available Channels in 2.4GHz 1,2,3,4,5,6,7,8,9,10,11,12,13 */
    INT radioIndex = 0;
    ULONG channel = 13;
    INT result;

    result = test_utils_channelPush(radioIndex, channel);
    UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS);
    return;
}

void test_wifi_L2_InValidchannel_push_2GHz(void)
{

    /* Negative */
    /* Set it for Invalid Channel */
    INT radioIndex = 0;
    ULONG channel = 25;
    INT result;

    result = test_utils_channelPush(radioIndex, channel);
    UT_ASSERT_EQUAL( result, WIFI_HAL_ERROR);
    return;
}

void test_wifi_L2_InValidIndex_channel_push_2GHz(void)
{
    /* Negative */
    /* set it with wrong radio index */
    INT radioIndex = 0;
    ULONG channel = 25;
    INT result;

    radioIndex = 5;
    channel = 13;
    result = test_utils_channelPush(radioIndex, channel);
    UT_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS);
    return;
}


void test_wifi_L2_Validchannel_push_5GHz(void)
{
    /* set 5 Ghz channel */
    /* Positive */
    /* Set it for a valid channel e.g 149 */ /* selected channel with all bandwidth capable 20/40/80/160 */
    /* Available Channels in 5 GHz NON DFS 36,40,44,48,149,153,157,161,165 */
    INT radioIndex = 1;
    ULONG channel = 149;
    INT result;

    result = test_utils_channelPush(radioIndex, channel);
    UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS);
    return;
}

void test_wifi_L2_InValidchannel_push_5GHz(void)
{
    /* Negative */
    /* Set it for Invalid Channel */
    ULONG channel = 178;
    INT radioIndex = 1;
    INT result;

    result = test_utils_channelPush(radioIndex, channel);
    UT_ASSERT_EQUAL( result, WIFI_HAL_ERROR);
    return;
}

void test_wifi_L2_InValidIndex_channel_push_5GHz(void)
{
    /* Negative */
    INT radioIndex = 5;
    ULONG channel = 149;
    INT result;

    result = test_utils_channelPush(radioIndex, channel);
    UT_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS);
    return;
}

void test_wifi_L2_Validchannel_push_6GHz(void)
{
    /* set 6 Ghz channel */
    /* Positive */
    /* Set it for a valid channel e.g 1 */
    /* Available Channels in 6 GHz  1,5,9,13,17,21,25,29,33,37,41,45,49,53,57,61,65,69,73,77,81,85,89,93  */
    INT radioIndex = 2;
    ULONG channel = 1;
    INT result;

    result = test_utils_channelPush(radioIndex, channel);
    UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS);
    return;
}

void test_wifi_L2_InValidchannel_push_6GHz(void)
{
    /* Negative */
    /* Set it for Invalid Channel */
    ULONG channel = 178;
    INT radioIndex =2;
    INT result;
    result = test_utils_channelPush(radioIndex, channel);
    UT_ASSERT_EQUAL( result, WIFI_HAL_ERROR);
    return;
}

void test_wifi_L2_InValidIndex_channel_push_6GHz(void)
{
    /* Negative */
    INT radioIndex = 5;
    ULONG channel = 1;
    INT result;

    result = test_utils_channelPush(radioIndex, channel);
    UT_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS);
    return;
}

/* This will test Radio bandwidth set functionality*
* positive case * maps to WIFI_HAL_SUCCESS*
* set Radios to valid bandwidth and check the value through get*
*
* Negative case * WIFI_HAL_ERROR, WIFI_HAL_INVALID_ARGUMENTS *
* Set Radios Invalid bandwidth *
* Set the bandwidth with wrong radio index *
* Set the bandwidth to NULL *
*/
void test_wifi_L2_set_valid_bandwidth_2Ghz_40MHz(void)
{
    /* set 2.4 GHz bandwidth first */

    /* Positive */
    /* Set it for a valid bandwidth */
    /* Available Channels in 2.4GHz is 20 Mhz, 40 Mhz */
    INT radioIndex = 0;
    UINT bandwidth;
    INT result;

    bandwidth = WIFI_CHANNELBANDWIDTH_40MHZ;
    result = test_utils_setBandwidth(radioIndex, bandwidth);
    UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS);
    return;
}

void test_wifi_L2_set_valid_bandwidth_2Ghz_20MHz(void)
{
    /* set 2.4 GHz bandwidth first */

    /* Positive */
    /* Set it for a valid bandwidth */
    /* Available Channels in 2.4GHz is 20 Mhz, 40 Mhz */
    INT radioIndex = 0;
    UINT bandwidth;
    INT result;

    bandwidth = WIFI_CHANNELBANDWIDTH_20MHZ;
    result = test_utils_setBandwidth(radioIndex, bandwidth);
    UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS);
    return;
}


void test_wifi_L2_set_Invalid_bandwidth_2Ghz(void)
{
    /* Negative */
    /* Set it for Invalid bandwidth */
    INT radioIndex = 0;
    UINT bandwidth = 0x12;
    INT result;

    result = test_utils_setBandwidth(radioIndex, bandwidth);
    UT_ASSERT_EQUAL( result, WIFI_HAL_ERROR);
    return;
}

void test_wifi_L2_set_Invalid_bandwidth_5Ghz(void)
{
    /* Negative */
    /* Set it for Invalid bandwidth */
    INT radioIndex = 1;
    UINT bandwidth = 0x12;
    INT result;

    result = test_utils_setBandwidth(radioIndex, bandwidth);
    UT_ASSERT_EQUAL( result, WIFI_HAL_ERROR);
    return;
}

void test_wifi_L2_set_Invalid_bandwidth_6Ghz(void)
{
    /* Negative */
    /* Set it for Invalid bandwidth */
    INT radioIndex = 2;
    UINT bandwidth = 0x12;
    INT result;

    result = test_utils_setBandwidth(radioIndex, bandwidth);
    UT_ASSERT_EQUAL( result, WIFI_HAL_ERROR);
    return;
}


void test_wifi_L2_set_InvalidIndex_bandwidth_2Ghz(void)
{
    /* Negative */
    /* Invalid radio index */
    INT radioIndex = 5;
    UINT bandwidth = WIFI_CHANNELBANDWIDTH_40MHZ;
    INT result;

    result = test_utils_setBandwidth(radioIndex, bandwidth);
    UT_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS);
    return;
}

void test_wifi_L2_set_InvalidIndex_bandwidth_5Ghz(void)
{
    /* Negative */
    /* Invalid radio index */
    INT radioIndex = 5;
    UINT bandwidth = WIFI_CHANNELBANDWIDTH_80MHZ;
    INT result;

    result = test_utils_setBandwidth(radioIndex, bandwidth);
    UT_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS);
    return;
}

void test_wifi_L2_set_InvalidIndex_bandwidth_6Ghz(void)
{
    /* Negative */
    /* Invalid radio index */
    INT radioIndex = 5;
    UINT bandwidth = WIFI_CHANNELBANDWIDTH_80MHZ;
    INT result;

    result = test_utils_setBandwidth(radioIndex, bandwidth);
    UT_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS);
    return;
}

void test_wifi_L2_set_valid_bandwidth_5Ghz_80MHz(void)
{
    /* set 5 GHz bandwidth */

    /* Positive */
    /* Set it for a valid bandwidth */
    /* Available Channels in 5 GHz is 20 Mhz, 40 Mhz, 80 Mhz, 160 Mhz*/
    INT radioIndex = 1;
    UINT bandwidth = WIFI_CHANNELBANDWIDTH_80MHZ;
    INT result;

    result = test_utils_setBandwidth(radioIndex, bandwidth);
    UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS);
    return ;
}

void test_wifi_L2_set_valid_bandwidth_6Ghz_80MHz(void)
{
    /* set 6 GHz bandwidth */

    /* Positive */
    /* Set it for a valid bandwidth */
    /* Available Channels in 5 GHz is 20 Mhz, 40 Mhz, 80 Mhz, 160 Mhz*/
    INT radioIndex = 2;
    UINT bandwidth = WIFI_CHANNELBANDWIDTH_80MHZ;
    INT result;

    result = test_utils_setBandwidth(radioIndex, bandwidth);
    UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS);
    return;
}


void test_wifi_L2_set_valid_bandwidth_5Ghz_20MHz(void)
{
    /* set 5 GHz bandwidth */

    /* Positive */
    /* Set it for a valid bandwidth */
    /* Available Channels in 5 GHz is 20 Mhz, 40 Mhz, 80 Mhz, 160 Mhz*/
    INT radioIndex = 1;
    UINT bandwidth = WIFI_CHANNELBANDWIDTH_20MHZ;
    INT result;

    result = test_utils_setBandwidth(radioIndex, bandwidth);
    UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS);
    return;
}

void test_wifi_L2_set_valid_bandwidth_6Ghz_20MHz(void)
{
    /* set 6 GHz bandwidth */

    /* Positive */
    /* Set it for a valid bandwidth */
    /* Available Channels in 5 GHz is 20 Mhz, 40 Mhz, 80 Mhz, 160 Mhz*/
    INT radioIndex = 2;
    UINT bandwidth = WIFI_CHANNELBANDWIDTH_20MHZ;
    INT result;

    result = test_utils_setBandwidth(radioIndex, bandwidth);
    UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS);
    return;
}


void test_wifi_L2_set_valid_bandwidth_5Ghz_40MHz(void)
{
    /* set 5 GHz bandwidth */

    /* Positive */
    /* Set it for a valid bandwidth */
    /* Available Channels in 5 GHz is 20 Mhz, 40 Mhz, 80 Mhz, 160 Mhz*/
    INT radioIndex = 1;
    UINT bandwidth = WIFI_CHANNELBANDWIDTH_40MHZ;
    INT result;

    result = test_utils_setBandwidth(radioIndex, bandwidth);
    UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS);
    return;
}

void test_wifi_L2_set_valid_bandwidth_6Ghz_40MHz(void)
{
    /* set 6 GHz bandwidth */

    /* Positive */
    /* Set it for a valid bandwidth */
    /* Available Channels in 5 GHz is 20 Mhz, 40 Mhz, 80 Mhz, 160 Mhz*/
    INT radioIndex = 2;
    UINT bandwidth = WIFI_CHANNELBANDWIDTH_40MHZ;
    INT result;

    result = test_utils_setBandwidth(radioIndex, bandwidth);
    UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS);
    return;
}


void test_wifi_L2_set_valid_bandwidth_5Ghz_160MHz(void)
{
    /* set 5 GHz bandwidth */

    /* Positive */
    /* Set it for a valid bandwidth */
    /* Available Channels in 5 GHz is 20 Mhz, 40 Mhz, 80 Mhz, 160 Mhz*/
    INT radioIndex = 1;
    UINT bandwidth = WIFI_CHANNELBANDWIDTH_160MHZ;
    INT result;

    result = test_utils_setBandwidth(radioIndex, bandwidth);
    UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS);
    return;
}

void test_wifi_L2_set_valid_bandwidth_6Ghz_160MHz(void)
{
    /* set 6 GHz bandwidth */

    /* Positive */
    /* Set it for a valid bandwidth */
    /* Available Channels in 5 GHz is 20 Mhz, 40 Mhz, 80 Mhz, 160 Mhz*/
    INT radioIndex = 2;
    UINT bandwidth = WIFI_CHANNELBANDWIDTH_160MHZ;
    INT result;

    result = test_utils_setBandwidth(radioIndex, bandwidth);
    UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS);
    return;
}

void test_wifi_L2_set_valid_bandwidth_5Ghz_80_80MHz(void)
{
    /* set 5 GHz bandwidth */

    /* Positive */
    /* Set it for a valid bandwidth */
    /* Available Channels in 5 GHz is 20 Mhz, 40 Mhz, 80 Mhz, 160 Mhz*/
    INT radioIndex = 1;
    UINT bandwidth = WIFI_CHANNELBANDWIDTH_80_80MHZ;
    INT result;

    result = test_utils_setBandwidth(radioIndex, bandwidth);
    UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS);
    return;
}

void test_wifi_L2_set_valid_bandwidth_6Ghz_80_80MHz(void)
{
    /* set 6 GHz bandwidth */

    /* Positive */
    /* Set it for a valid bandwidth */
    /* Available Channels in 5 GHz is 20 Mhz, 40 Mhz, 80 Mhz, 160 Mhz*/
    INT radioIndex = 2;
    UINT bandwidth = WIFI_CHANNELBANDWIDTH_80_80MHZ;
    INT result;

    result = test_utils_setBandwidth(radioIndex, bandwidth);
    UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS);
    return;
}
#endif

int convert_channelwidth_to_enum(char channelwidth[10], wifi_channelBandwidth_t *chbw)
{
    if( strcmp(channelwidth, "20MHz") == 0 )
    {
        *chbw = WIFI_CHANNELBANDWIDTH_20MHZ;
    }
    else if( strcmp(channelwidth, "40MHz") == 0 )
    {
	*chbw = WIFI_CHANNELBANDWIDTH_40MHZ;
    }
    else if( strcmp(channelwidth, "80MHz") == 0 )
    {
	*chbw = WIFI_CHANNELBANDWIDTH_80MHZ;
    }
    else if( strcmp(channelwidth, "160MHz") == 0 )
    {
        *chbw = WIFI_CHANNELBANDWIDTH_160MHZ;
    }
    else
    {
        return -1;
    }
    return 0;
}

/**
 * @brief Tests requirements for L2 testing: get the supported channelwidths from wifi_getHalCapability(), set using wifi_setRadioOperatingParameters() and verify using wifi_getRadioOperatingChannelBandwidth()
 *
 * Test Coverage: Positive Scenario
 *
 * @retval WIFI_HAL_SUCCESS   -> tested
 *
 * @Note hal api is Synchronous
 */

void test_getRadioOperatingChannelBandwidth_valid()
{
    UT_LOG("Entering test_getRadioOperatingChannelBandwidth_valid...");
    wifi_channelBandwidth_t channelWidth_list[5] = {0};
    wifi_channelBandwidth_t set_channelwidth_enum = 0;
    char initial_channelwidth[10] = {'\0'};
    char set_channelwidth[10] = {'\0'};
    unsigned int numRadios = 0;
    int radioIndex = 0, i = 0, result = 0, returnStatus = 0, count = 0;
    wifi_radio_operationParam_t tmp_radio;

    /* Get the number of radios applicable */
    returnStatus = test_utils_getMaxNumberOfRadio(&numRadios);

    if (returnStatus == 0)
    {
        UT_LOG("Number of Radios : %u", numRadios);

        /* Postive Test WIFI_HAL_SUCCESS */
        /* Setting valid radio operating parameters and expecting the API to return success */
        UT_LOG("Test Case 1");

        for (radioIndex = 0; radioIndex < numRadios; radioIndex++)
        {
	    if(get_channel_bandwidth(radioIndex, &count, channelWidth_list) == -1) {
		UT_LOG("Unable to retrieve channel bandwidth");
                UT_FAIL("Unable to retrieve channel bandwidth");
		return;
            }

            for (i=1; i<count; i++)
            {
                result = wifi_getRadioOperatingChannelBandwidth(radioIndex, initial_channelwidth);
                UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS);
		UT_LOG("wifi_getRadioOperatingChannelBandwidth for radio %d is %s returns result %d\n", radioIndex, initial_channelwidth, result);

                if (NULL != strstr(initial_channelwidth, "MHz"))
                {
                    UT_LOG("Initial Channelwidth of radio %d is %s which is a valid bandwidth", radioIndex, initial_channelwidth);
                    UT_PASS("Initial Channel Bandwidth validation success");
                }

                tmp_radio = g_operationParam[radioIndex];
                tmp_radio.channelWidth = channelWidth_list[i];

                UT_LOG("Setting channelWidth to %d using setRadioOperatingParameters", tmp_radio.channelWidth);
                result = wifi_setRadioOperatingParameters(radioIndex, &tmp_radio);
                UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );
                UT_LOG("wifi_setRadioOperatingParameters for radio %d returns : %d", radioIndex, result);

                result = wifi_getRadioOperatingChannelBandwidth(radioIndex, set_channelwidth);
                UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS);
                UT_LOG("wifi_setRadioOperatingParameters for radioIndex %d returns result %d\n", radioIndex, result);

                if (NULL != strstr(set_channelwidth, "MHz"))
                {
                    UT_LOG("Set Channelwidth of radio %d is %s which is a valid bandwidth", radioIndex, set_channelwidth);
                    UT_PASS("Set ChannelWidth validation success");
                }

                if (convert_channelwidth_to_enum(set_channelwidth, &set_channelwidth_enum) == 0)
		{
		    if(set_channelwidth_enum == tmp_radio.channelWidth)
	            {
	                UT_LOG("The channelwidth set using wifi_setRadioOperatingParameters is reflected successfully in wifi_getRadioOperatingChannelBandwidth for Radio %d", radioIndex);
			UT_PASS("The channelwidth set using wifi_setRadioOperatingParameters is reflected successfully in wifi_getRadioOperatingChannelBandwidth");
			result = wifi_setRadioOperatingParameters(radioIndex, &g_operationParam[radioIndex]);
			UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );
			UT_LOG("wifi_setRadioOperatingParameters after setting back to rado_config file values for radio %d returns : %d", radioIndex, result);
	            }
	            else
                    {
			UT_LOG("The channelwidth set using wifi_setRadioOperatingParameters is NOT reflected in wifi_getRadioOperatingChannelBandwidth for Radio %d", radioIndex);
                        UT_FAIL("The channelwidth set using wifi_setRadioOperatingParameters is NOT reflected in wifi_getRadioOperatingChannelBandwidth");
                    }
		}
	        else
	        {
		    UT_LOG("convert_channelwidth_to_enum failed");
                    UT_FAIL("convert_channelwidth_to_enum failed");
		    return;
	        }
	    }
        }
    }
    else
    {
        UT_LOG("Unable to retrieve the number of radios from HalCapability");
    }

    UT_LOG("Exiting test_getRadioOperatingChannelBandwidth_valid");
    return;
}

/**
 * @brief Tests requirements for L2 testing for setting invalid channelwidth values using wifi_getRadioOperatingChannelBandwidth() and verify with wifi_setRadioOperatingParameters()
 *
 * Test Coverage: Negative Scenario
 *
 * @retval WIFI_HAL_INVALID_ARGUMENTS   -> tested
 *
 * @Note hal api is Synchronous
 */

void test_getRadioOperatingChannelBandwidth_invalid_channelwidth()
{
    UT_LOG("Entering test_getRadioOperatingChannelBandwidth_invalid_channelwidth...");

    wifi_channelBandwidth_t positive_width = 200;
    wifi_channelBandwidth_t negative_width = -250;
    char initial_channelwidth[10] = {'\0'};
    char set_channelwidth[10] = {'\0'};
    int result = 0, returnStatus = 0, radioIndex = 0;
    unsigned int numRadios = 0;
    wifi_radio_operationParam_t tmp_radio;

    /* Get the number of radios applicable */
    returnStatus = test_utils_getMaxNumberOfRadio(&numRadios);

    if (returnStatus == 0)
    {
        UT_LOG("Number of Radios : %u", numRadios);

        /* Negative Test WIFI_HAL_INVALID_ARGUMENTS */
        /* Setting invalid channel bandwidth and expecting the API to return failure */
        UT_LOG("Test Case 2");

        for (radioIndex = 0; radioIndex < numRadios; radioIndex++)
        {
            result = wifi_getRadioOperatingChannelBandwidth(radioIndex, initial_channelwidth);
            UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS);

            if (NULL != strstr(initial_channelwidth, "MHz"))
            {
                UT_LOG("Initial ChannelBandwidth of radio %d is %s which is a valid bandwidth", radioIndex, initial_channelwidth);
                UT_PASS("Initial Channel Bandwidth validation success");
            }

            /* Negative Test WIFI_HAL_INVALID_ARGUMENTS */
            /* Setting invalid positive channel bandwidth 200 and expecting the API to return failure */
            UT_LOG("Test case 2.1");
            tmp_radio = g_operationParam[radioIndex];
            tmp_radio.channelWidth = positive_width;

            UT_LOG("Setting channelWidth to %d using setRadioOperatingParameters", tmp_radio.channelWidth);
            result = wifi_setRadioOperatingParameters(radioIndex, &tmp_radio);
	    UT_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS );
            UT_LOG("wifi_setRadioOperatingParameters for radio %d returns : %d", radioIndex, result);

             /* Negative Test WIFI_HAL_INVALID_ARGUMENTS */
             /* Setting invalid negative channel bandwidth -250 and expecting the API to return failure */
	     UT_LOG("Test case 2.2");
             tmp_radio = g_operationParam[radioIndex];
             tmp_radio.channelWidth = negative_width;

             UT_LOG("Setting channelWidth to %d using setRadioOperatingParameters", tmp_radio.channelWidth);
	     result = wifi_setRadioOperatingParameters(radioIndex, &tmp_radio);
	     UT_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS );
	     UT_LOG("wifi_setRadioOperatingParameters for radio %d returns : %d", radioIndex, result);

             result = wifi_getRadioOperatingChannelBandwidth(radioIndex, set_channelwidth);
             UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS);

             if (NULL != strstr(set_channelwidth, "MHz"))
             {
                 UT_LOG("Final ChannelBandwidth of radio %d is %s which is a valid bandwidth", radioIndex, set_channelwidth);
                 UT_PASS("Final Channel Bandwidth validation success");
	     }

             if(strcmp(initial_channelwidth, set_channelwidth) == 0)
             {
                 UT_LOG("Channel Width remains uncorrupted after setting invalid values");
                 UT_PASS("Channel Bandwidth validation success");
             }
             else
             {
                 UT_LOG("Channel Width got corrupted after setting invalid values");
                 UT_FAIL("Channel Bandwidth validation failure");
		 /* Set the values back same as the radio_config file */
		 result = wifi_setRadioOperatingParameters(radioIndex, &g_operationParam[radioIndex]);
		 UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );
		 UT_LOG("wifi_setRadioOperatingParameters after setting back to rado_config file values for radio %d returns : %d", radioIndex, result);
             }
	}
    }
    else
    {
        UT_LOG("Unable to retrieve the number of radios from HalCapability");
    }

    UT_LOG("Exiting test_getRadioOperatingChannelBandwidth_invalid_channelwidth");
    return;
}

/**
 * @brief Tests requirements for L2 testing wifi_setRadioOperatingParameters() with invalid radioIndex values and verify with wifi_getRadioOperatingChannelBandwidth()
 *
 * Test Coverage: Negative Scenario
 *
 * @retval WIFI_HAL_INVALID_ARGUMENTS   -> tested
 *
 * @Note hal api is Synchronous
 */

void test_getRadioOperatingChannelBandwidth_invalid_radioIndex()
{
    UT_LOG("Entering test_getRadioOperatingChannelBandwidth_invalid_radioIndex...");

    int radioIndex_outOfRange = 99;
    int radioIndex_negative = -1;
    wifi_channelBandwidth_t width = 40;
    char initial_channelwidth[10] = {'\0'};
    char set_channelwidth[10] = {'\0'};
    int result = 0, returnStatus = 0, radioIndex = 0;
    unsigned int numRadios = 0;
    wifi_radio_operationParam_t tmp_radio;

    /* Get the number of radios applicable */
    returnStatus = test_utils_getMaxNumberOfRadio(&numRadios);

    if (returnStatus == 0)
    {
        UT_LOG("Number of Radios : %u", numRadios);

        /* Negative Test WIFI_HAL_INVALID_ARGUMENTS */
        /* Setting invalid outofRange positive and negative radioIndex and expecting the API to return failure */
        UT_LOG("Test Case 3");

        for (radioIndex = 0; radioIndex < numRadios; radioIndex++)
        {
            result = wifi_getRadioOperatingChannelBandwidth(radioIndex, initial_channelwidth);
            UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS);

            if (NULL != strstr(initial_channelwidth, "MHz"))
            {
                UT_LOG("Initial ChannelBandwidth of radio %d is %s which is a valid bandwidth", radioIndex, initial_channelwidth);
                UT_PASS("Initial ChannelBandwidth validation success");
            }

	    tmp_radio = g_operationParam[radioIndex];
	    tmp_radio.channelWidth = width;

	    /* Negative Test WIFI_HAL_INVALID_ARGUMENTS */
	    /* Setting invalid positive outofRange radioIndex and expecting the API to return failure */
	    UT_LOG("Test case 3.1");

	    UT_LOG("Setting channelWidth to %d using setRadioOperatingParameters with radioIndex %d", tmp_radio.channelWidth, radioIndex_outOfRange);
	    result = wifi_setRadioOperatingParameters(radioIndex_outOfRange, &tmp_radio);
	    UT_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS );
            UT_LOG("wifi_setRadioOperatingParameters for radio %d returns : %d", radioIndex_outOfRange, result);

            /* Negative Test WIFI_HAL_INVALID_ARGUMENTS */
	    /* Setting invalid negative radioIndex and expecting the API to return failure */
	    UT_LOG("Test case 3.2");

	    UT_LOG("Setting channelWidth to %d using setRadioOperatingParameters with radioIndex %d", tmp_radio.channelWidth, radioIndex_negative);
            result = wifi_setRadioOperatingParameters(radioIndex_negative, &tmp_radio);
            UT_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS );
            UT_LOG("wifi_setRadioOperatingParameters for radio %d returns : %d", radioIndex_negative, result);

	    result = wifi_getRadioOperatingChannelBandwidth(radioIndex, set_channelwidth);
	    UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS);
            UT_LOG("wifi_getRadioOperatingChannelBandwidth2 for radioIndex %d returns result %d\n", radioIndex, result);

            if (NULL != strstr(set_channelwidth, "MHz"))
            {
                UT_LOG("Final ChannelBandwidth of radio %d is %s which is a valid bandwidth", radioIndex, set_channelwidth);
                UT_PASS("Final ChannelBandwidth validation success");
            }

            if(strcmp(initial_channelwidth, set_channelwidth) == 0)
            {
                UT_LOG("Channel Width value remains uncorrupted after setting invalid radioIndex");
	        UT_PASS("Channel Bandwidth validation success");
            }
            else
            {
                UT_LOG("Channel Width value got corrupted after setting invalid radioIndex");
                UT_FAIL("Channel Bandwidth validation failure");
		/* Set the values back same as the radio_config file */
		result = wifi_setRadioOperatingParameters(radioIndex, &g_operationParam[radioIndex]);
		UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );
		UT_LOG("wifi_setRadioOperatingParameters after setting back to rado_config file values for radio %d returns : %d", radioIndex, result);
            }
        }
    }
    else
    {
        UT_LOG("Unable to retrieve the number of radios from HalCapability");
    }

    UT_LOG("Exiting test_getRadioOperatingChannelBandwidth_invalid_radioIndex");
    return;
}

/**
 * @brief Tests requirements for L2 testing wifi_setRadioOperatingParameters() with operationParam as NULL and verify using wifi_getRadioOperatingChannelBandwidth()
 *
 * Test Coverage: Negative Scenario
 *
 * @retval WIFI_HAL_INVALID_ARGUMENTS   -> tested
 *
 * @Note hal api is Synchronous
 */

void test_getRadioOperatingChannelBandwidth_operationParamNULL()
{
    UT_LOG("Entering test_getRadioOperatingChannelBandwidth_operationParamNULL...");

    char initial_channelwidth[10] = {'\0'};
    char set_channelwidth[10] = {'\0'};
    int result = 0, returnStatus = 0, radioIndex = 0;
    unsigned int numRadios = 0;

    /* Get the number of radios applicable */
    returnStatus = test_utils_getMaxNumberOfRadio(&numRadios);

    if (returnStatus == 0)
    {
        UT_LOG("Number of Radios : %u", numRadios);

        /* Negative Test WIFI_HAL_INVALID_ARGUMENTS */
        /* Setting operationParam to NULL and expecting the API to return failure */
        UT_LOG("Test Case 4");

        for (radioIndex = 0; radioIndex < numRadios; radioIndex++)
        {
            result = wifi_getRadioOperatingChannelBandwidth(radioIndex, initial_channelwidth);
            UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS);

            if (NULL != strstr(initial_channelwidth, "MHz"))
            {
                UT_LOG("Initial ChannelBandwidth of radio %d is %s which is a valid bandwidth", radioIndex, initial_channelwidth);
                UT_PASS("Initial ChannelBandwidth validation success");
            }

            UT_LOG("Setting operationParam as NULL and expecting the API to return failure");
            result = wifi_setRadioOperatingParameters(radioIndex, NULL);
	    UT_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS );
            UT_LOG("wifi_setRadioOperatingParameters for radio %d returns : %d", radioIndex, result);

            result = wifi_getRadioOperatingChannelBandwidth(radioIndex, set_channelwidth);
            UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS);

            if (NULL != strstr(set_channelwidth, "MHz"))
            {
                UT_LOG("Final ChannelBandwidth of radio %d is %s which is a valid bandwidth", radioIndex, set_channelwidth);
                UT_PASS("Final ChannelBandwidth validation success");
            }

            if(strcmp(initial_channelwidth, set_channelwidth) == 0)
            {
                UT_LOG("ChannelWidth value remains uncorrupted after setting operationParam value as NULL");
                UT_PASS("Channel Bandwidth validation success");
            }
            else
            {
                UT_LOG("ChannelWidth value got corrupted after setting operationParam value as NULL");
                UT_FAIL("Channel Bandwidth validation failure");
		/* Set the values back same as the radio_config file */
		result = wifi_setRadioOperatingParameters(radioIndex, &g_operationParam[radioIndex]);
		UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );
		UT_LOG("Setting the radio operating parameters back to the values in radio_config file for radio %d returns : %d", radioIndex, result);
            }
        }
    }
    else
    {
        UT_LOG("Unable to retrieve the number of radios from HalCapability");
    }

    UT_LOG("Exiting test_getRadioOperatingChannelBandwidth_operationParamNULL");
    return;
}

/**
 * @brief Tests requirements for L2 testing wifi_createVAP() with valid vapinfo parameters value(enable as false) and verify the set values using wifi_getRadioVapInfoMap()
 *
 * Test Coverage: Positive Scenario
 *
 * @retval WIFI_HAL_SUCCESS   -> tested
 *
 * @Note hal api is Synchronous
 */

void test_createVAP_vapinfo_valid_tc1(void)
{
    UT_LOG("Entering test_createVAP_vapinfoValid_tc1...");

    int * apIndices = NULL;
    int i = 0, index = 0, result = 0, radioIndex = 0, returnStatus = 0;
    wifi_vap_info_map_t  map, map1, tmp_map;
    unsigned int numRadios = 0;

    /* Get the number of radios applicable */
    returnStatus = test_utils_getMaxNumberOfRadio(&numRadios);

    if (returnStatus == 0)
    {
        UT_LOG("Number of Radios : %u", numRadios);

        /* Postive Test WIFI_HAL_SUCCESS */
        /* Setting valid VAP info map and expecting the API to return success */
        UT_LOG("Test Case 5");

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
		    result = wifi_getRadioVapInfoMap(radioIndex, &map1);
		    UT_ASSERT_EQUAL(result, WIFI_HAL_SUCCESS);

		    for(i=0; i<map1.num_vaps; i++)
		    {
	                if ((strstr(map1.vap_array[i].vap_name, "private_ssid") != NULL))
			{
			    UT_LOG("The initial values are map1.vap_array[i].vap_name is %s, map1.vap_array[i].vap_index is %d, map1.vap_array[i].u.bss_info.enabled is %d, map1.vap_array[i].u.bss_info.showSsid is %d and map1.vap_array[i].u.bss_info.ssid is %s", map1.vap_array[i].vap_name, map1.vap_array[i].vap_index, map1.vap_array[i].u.bss_info.enabled, map1.vap_array[i].u.bss_info.showSsid, map1.vap_array[i].u.bss_info.ssid);
			}
		    }

                    /* Initialize the values to be set */
                    tmp_map = g_org_map[radioIndex];
                    tmp_map.num_vaps = 1;
                    /* disable the SSID and set showSsid as false */
                    tmp_map.vap_array[0].u.bss_info.enabled = 0;
                    tmp_map.vap_array[0].u.bss_info.showSsid = 0;
                    strcpy(tmp_map.vap_array[0].u.bss_info.ssid, "tdkteam321");

		    UT_LOG("Setting the vapinfo values: tmp_map.vap_array[0].u.bss_info.enabled is %d, tmp_map.vap_array[0].u.bss_info.showSsid is %d and tmp_map.vap_array[0].u.bss_info.ssid is %s", tmp_map.vap_array[0].u.bss_info.enabled, tmp_map.vap_array[0].u.bss_info.showSsid, tmp_map.vap_array[0].u.bss_info.ssid);
		    result = wifi_createVAP(radioIndex, &tmp_map);
		    UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );
		    UT_LOG("Setting valid VAP info map using wifi_createVAP for radio %d returns : %d", radioIndex, result);

		    result = wifi_getRadioVapInfoMap(radioIndex, &map1);
		    UT_ASSERT_EQUAL(result, WIFI_HAL_SUCCESS);

		    for(i=0; i<map1.num_vaps; i++)
		    {
		        if ((strstr(map1.vap_array[i].vap_name, "private_ssid") != NULL))
			{
			    UT_LOG("The values post wifi_createVAP are map1.vap_array[i].vap_name is %s, map1.vap_array[i].vap_index is %d, map1.vap_array[i].u.bss_info.enabled is %d, map1.vap_array[i].u.bss_info.showSsid is %d and map1.vap_array[i].u.bss_info.ssid is %s", map1.vap_array[i].vap_name, map1.vap_array[i].vap_index, map1.vap_array[i].u.bss_info.enabled, map1.vap_array[i].u.bss_info.showSsid, map1.vap_array[i].u.bss_info.ssid);

			    if ((tmp_map.vap_array[0].u.bss_info.enabled == map1.vap_array[i].u.bss_info.enabled) && (tmp_map.vap_array[0].u.bss_info.showSsid == map1.vap_array[i].u.bss_info.showSsid) && (strcmp(tmp_map.vap_array[0].u.bss_info.ssid, map1.vap_array[i].u.bss_info.ssid) == 0))
			    {
		                UT_LOG("The set vapinfo values using wifi_createVAP are reflected successfully for Radio %d in wifi_getRadioVapInfoMap", radioIndex);
				UT_PASS("The set vapinfo values using wifi_createVAP are reflected successfully in wifi_getRadioVapInfoMap");
	                    }
			    else
			    {
				UT_LOG("The set vapinfo values using wifi_createVAP are NOT reflected for Radio %d in wifi_getRadioVapInfoMap", radioIndex);
				UT_FAIL("The set vapinfo values using wifi_createVAP are NOT reflected in wifi_getRadioVapInfoMap");
			    }
                        }
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

    UT_LOG("Exiting test_createVAP_vapinfoValid_tc1...");
    return;
}

/**
 * @brief Tests requirements for L2 testing wifi_createVAP() with valid vapinfo parameters value(enable as true) and verify the set values using wifi_getRadioVapInfoMap()
 *
 * Test Coverage: Positive Scenario
 *
 * @retval WIFI_HAL_SUCCESS   -> tested
 *
 * @Note hal api is Synchronous
 */

void test_createVAP_vapinfo_valid_tc2(void)
{
    UT_LOG("Entering test_createVAP_vapinfoValid_tc2...");

    int result = 0, index = 0, i = 0, radioIndex = 0, returnStatus = 0;
    int * apIndices = NULL;
    wifi_vap_info_map_t  map, map1, tmp_map;
    unsigned int numRadios = 0;

    /* Get the number of radios applicable */
    returnStatus = test_utils_getMaxNumberOfRadio(&numRadios);

    if (returnStatus == 0)
    {
        UT_LOG("Number of Radios : %u", numRadios);

        /* Postive Test WIFI_HAL_SUCCESS */
        /* Setting valid VAP info map and expecting the API to return success */
        UT_LOG("Test Case 6");

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
		    result = wifi_getRadioVapInfoMap(radioIndex, &map1);
		    UT_ASSERT_EQUAL(result, WIFI_HAL_SUCCESS);

		    for(i=0; i<map1.num_vaps; i++)
	            {
	                if ((strstr(map1.vap_array[i].vap_name, "private_ssid") != NULL))
			{
			    UT_LOG("The initial values are map1.vap_array[i].vap_name is %s, map1.vap_array[i].vap_index is %d, map1.vap_array[i].u.bss_info.enabled is %d, map1.vap_array[i].u.bss_info.showSsid is %d and map1.vap_array[i].u.bss_info.ssid is %s", map1.vap_array[i].vap_name, map1.vap_array[i].vap_index, map1.vap_array[i].u.bss_info.enabled, map1.vap_array[i].u.bss_info.showSsid, map1.vap_array[i].u.bss_info.ssid);
			}
		    }

                    /* Initialize the values to be set */
                    tmp_map = g_org_map[radioIndex];
                    tmp_map.num_vaps = 1;
                    /* enable the SSID and set showSsid as true */
                    tmp_map.vap_array[0].u.bss_info.enabled = 1;
                    tmp_map.vap_array[0].u.bss_info.showSsid = 1;
                    strcpy(tmp_map.vap_array[0].u.bss_info.ssid, g_org_map[radioIndex].vap_array[0].u.bss_info.ssid);

		    UT_LOG("Setting the vapinfo values: tmp_map.vap_array[0].u.bss_info.enabled is %d, tmp_map.vap_array[0].u.bss_info.showSsid is %d and tmp_map.vap_array[0].u.bss_info.ssid is %s", tmp_map.vap_array[0].u.bss_info.enabled, tmp_map.vap_array[0].u.bss_info.showSsid, tmp_map.vap_array[0].u.bss_info.ssid);
		    result = wifi_createVAP(radioIndex, &tmp_map);
		    UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );
		    UT_LOG("Setting valid VAP info map using wifi_createVAP for radio %d returns : %d", radioIndex, result);

		    result = wifi_getRadioVapInfoMap(radioIndex, &map1);
		    UT_ASSERT_EQUAL(result, WIFI_HAL_SUCCESS);

                    for(i=0; i<map1.num_vaps; i++)
                    {
                        if ((strstr(map1.vap_array[i].vap_name, "private_ssid") != NULL))
			{
                            UT_LOG("The values post wifi_createVAP are map1.vap_array[i].vap_name is %s, map1.vap_array[i].vap_index is %d, map1.vap_array[i].u.bss_info.enabled is %d, map1.vap_array[i].u.bss_info.showSsid is %d and map1.vap_array[i].u.bss_info.ssid is %s", map1.vap_array[i].vap_name, map1.vap_array[i].vap_index, map1.vap_array[i].u.bss_info.enabled, map1.vap_array[i].u.bss_info.showSsid, map1.vap_array[i].u.bss_info.ssid);

                            if ((tmp_map.vap_array[0].u.bss_info.enabled == map1.vap_array[i].u.bss_info.enabled) && (tmp_map.vap_array[0].u.bss_info.showSsid == map1.vap_array[i].u.bss_info.showSsid) && (strcmp(tmp_map.vap_array[0].u.bss_info.ssid, map1.vap_array[i].u.bss_info.ssid) == 0))
                            {
                                UT_LOG("The set vapinfo values using wifi_createVAP are reflected successfully for Radio %d in wifi_getRadioVapInfoMap", radioIndex);
				UT_PASS("The set vapinfo values using wifi_createVAP are reflected successfully in wifi_getRadioVapInfoMap");
                            }
                            else
                            {
                                UT_LOG("The set vapinfo values using wifi_createVAP are NOT reflected for Radio %d in wifi_getRadioVapInfoMap", radioIndex);
				UT_FAIL("The set vapinfo values using wifi_createVAP are NOT reflected in wifi_getRadioVapInfoMap");
                            }
			}
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

    UT_LOG("Exiting test_createVAP_vapinfoValid_tc2...");
    return;
}

/**
 * @brief Tests requirements for L2 testing wifi_createVAP() with invalid vapinfo parameters value and verify if values remain uncorrupted using wifi_getRadioVapInfoMap()
 *
 * Test Coverage: Negative Scenario
 *
 * @retval WIFI_HAL_INVALID_ARGUMENTS   -> tested
 *
 * @Note hal api is Synchronous
 */

void test_createVAP_vapinfoInvalid()
{
    UT_LOG("Entering test_createVAP_vapinfoInvalid...");
    int result = 0, index = 0, i = 0, radioIndex = 0, returnStatus = 0;
    int * apIndices = NULL;
    wifi_vap_info_map_t  map, map1, tmp_map;
    unsigned int numRadios = 0;

    /* Get the number of radios applicable */
    returnStatus = test_utils_getMaxNumberOfRadio(&numRadios);

    if (returnStatus == 0)
    {
        UT_LOG("Number of Radios : %u", numRadios);

        /* Negative Test WIFI_HAL_INVALID_ARGUMENTS */
        /* Setting invalid VAP info values and expecting the API to return failure */
        UT_LOG("Test Case 7");

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
		    result = wifi_getRadioVapInfoMap(radioIndex, &map);
		    UT_ASSERT_EQUAL(result, WIFI_HAL_SUCCESS);

		    for(i=0; i<map.num_vaps; i++)
		    {
	                if ((strstr(map.vap_array[i].vap_name, "private_ssid") != NULL))
			{
		            UT_LOG("The initial values are map.vap_array[i].vap_name is %s, map.vap_array[i].vap_index is %d, map.vap_array[i].u.bss_info.enabled is %d, map.vap_array[i].u.bss_info.showSsid is %d and map.vap_array[i].u.bss_info.ssid is %s", map.vap_array[i].vap_name, map.vap_array[i].vap_index, map.vap_array[i].u.bss_info.enabled, map.vap_array[i].u.bss_info.showSsid, map.vap_array[i].u.bss_info.ssid);
			}
		    }

                    /* Initialize the values to be set */
		    tmp_map = g_org_map[radioIndex];
		    tmp_map.num_vaps = 1;
                    /* Set invalid vapinfo parameter values */
                    tmp_map.vap_array[0].u.bss_info.enabled = 2;
                    tmp_map.vap_array[0].u.bss_info.showSsid = 2;
                    strcpy(tmp_map.vap_array[0].u.bss_info.ssid, "");

		    UT_LOG("Setting the vapinfo values: tmp_map.vap_array[0].u.bss_info.enabled is %d, tmp_map.vap_array[0].u.bss_info.showSsid is %d and tmp_map.vap_array[0].u.bss_info.ssid is %s", tmp_map.vap_array[0].u.bss_info.enabled, tmp_map.vap_array[0].u.bss_info.showSsid, tmp_map.vap_array[0].u.bss_info.ssid);
		    result = wifi_createVAP(radioIndex, &tmp_map);
		    UT_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS );
		    UT_LOG("Setting invalid VAP info map using wifi_createVAP for radio %d returns : %d", radioIndex, result);

		    result = wifi_getRadioVapInfoMap(radioIndex, &map1);
		    UT_ASSERT_EQUAL(result, WIFI_HAL_SUCCESS);
                    for(i=0; i<map1.num_vaps; i++)
                    {
	                if ((strstr(map1.vap_array[i].vap_name, "private_ssid") != NULL))
			{
			    UT_LOG("The values post createVAP are map1.vap_array[i].vap_name is %s, map1.vap_array[i].vap_index is %d, map1.vap_array[i].u.bss_info.enabled is %d, map1.vap_array[i].u.bss_info.showSsid is %d and map1.vap_array[i].u.bss_info.ssid is %s", map1.vap_array[i].vap_name, map1.vap_array[i].vap_index, map1.vap_array[i].u.bss_info.enabled, map1.vap_array[i].u.bss_info.showSsid, map1.vap_array[i].u.bss_info.ssid);

                            if ((map.vap_array[i].u.bss_info.enabled == map1.vap_array[i].u.bss_info.enabled) && (map.vap_array[i].u.bss_info.showSsid == map1.vap_array[i].u.bss_info.showSsid) && (strcmp(map.vap_array[i].u.bss_info.ssid, map1.vap_array[i].u.bss_info.ssid) == 0))
                            {
                                UT_LOG("The vapinfo values remain uncorrupted for Radio %d after setting valid radioIndex and vapinfomap with invalid values to wifi_createVAP", radioIndex);
				UT_PASS("The vapinfo values remain uncorrupted after setting valid radioIndex and vapinfomap with invalid values to wifi_createVAP");
                            }
                            else
                            {
                                UT_LOG("The vapinfo values got corrupted for Radio %d after setting valid radioIndex and vapinfomap with invalid values to wifi_createVAP", radioIndex);
				UT_FAIL("The vapinfo values got corrupted after setting valid radioIndex and vapinfomap with invalid values to wifi_createVAP");
				/* Set the map values back to those in vap_config file */
				g_org_map[radioIndex].num_vaps = 1;
				result = wifi_createVAP(radioIndex, &g_org_map[radioIndex]);
				UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );
				UT_LOG("Setting config values same as vap_config file returns %d", result);
			    }	
			}
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

     UT_LOG("Exiting test_createVAP_vapinfoInvalid...");
     return;
}

/**
 * @brief Tests requirements for L2 testing wifi_createVAP() with map as NULL and verify if values remain uncorrupted using wifi_getRadioVapInfoMap()
 *
 * Test Coverage: Negative Scenario
 *
 * @retval WIFI_HAL_INVALID_ARGUMENTS   -> tested
 *
 * @Note hal api is Synchronous
 */

void test_createVAP_mapNULL(void)
{
    UT_LOG("Entering test_createVAP_mapNULL...");

    int * apIndices = NULL;
    int index = 0, i = 0, result = 0, radioIndex = 0, returnStatus = 0;
    wifi_vap_info_map_t map, map1;
    unsigned int numRadios = 0;

    /* Get the number of radios applicable */
    returnStatus = test_utils_getMaxNumberOfRadio(&numRadios);

    if (returnStatus == 0)
    {
        UT_LOG("Number of Radios : %u", numRadios);

        /* Negative Test WIFI_HAL_INVALID_ARGUMENTS */
        /* Setting map as NULL and expecting the API to return FAILURE */
        UT_LOG("Test Case 8");

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
		    result = wifi_getRadioVapInfoMap(radioIndex, &map);
		    UT_ASSERT_EQUAL(result, WIFI_HAL_SUCCESS);

		    for(i=0; i<map.num_vaps; i++)
		    {
			if ((strstr(map.vap_array[i].vap_name, "private_ssid") != NULL))
			{
			    UT_LOG("The initial values are map.vap_array[i].vap_name is %s, map.vap_array[i].vap_index is %d, map.vap_array[i].u.bss_info.enabled is %d, map.vap_array[i].u.bss_info.showSsid is %d and map.vap_array[i].u.bss_info.ssid is %s", map.vap_array[i].vap_name, map.vap_array[i].vap_index, map.vap_array[i].u.bss_info.enabled, map.vap_array[i].u.bss_info.showSsid, map.vap_array[i].u.bss_info.ssid);
			}
		    }

		    result = wifi_createVAP(radioIndex, NULL);
		    UT_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS );
		    UT_LOG("Setting map as NULL using wifi_createVAP for radio %d returns : %d", radioIndex, result);

		    result = wifi_getRadioVapInfoMap(radioIndex, &map1);
		    UT_ASSERT_EQUAL(result, WIFI_HAL_SUCCESS);
                    for(i=0; i<map1.num_vaps; i++)
                    {
		        if ((strstr(map1.vap_array[i].vap_name, "private_ssid") != NULL))
			{
			    UT_LOG("The values post createVAP are map1.vap_array[i].u.bss_info.enabled is %d, map1.vap_array[i].u.bss_info.showSsid is %d and map1.vap_array[i].u.bss_info.ssid is %s", map1.vap_array[i].u.bss_info.enabled, map1.vap_array[i].u.bss_info.showSsid, map1.vap_array[i].u.bss_info.ssid);

			    if ((map.vap_array[i].u.bss_info.enabled == map1.vap_array[i].u.bss_info.enabled) && (map.vap_array[i].u.bss_info.showSsid == map1.vap_array[i].u.bss_info.showSsid) && (strcmp(map.vap_array[i].u.bss_info.ssid, map1.vap_array[i].u.bss_info.ssid) == 0))
                            {
                                UT_LOG("The vapinfo values remain uncorrupted for Radio %d after setting valid radioIndex and NULL map to wifi_createVAP", radioIndex);
				UT_PASS("The vapinfo values remain uncorrupted after setting valid radioIndex and NULL vapinfomap to wifi_createVAP");
                            }
                            else
                            {
                                UT_LOG("The vapinfo values got corrupted for Radio %d after setting valid radioIndex and NULL map to wifi_createVAP", radioIndex);
				UT_FAIL("The vapinfo values got corrupted after setting valid radioIndex and NULL vapinfomap to wifi_createVAP");
				/* Set the map values back to those in vap_config file */
				g_org_map[radioIndex].num_vaps = 1;
				result = wifi_createVAP(radioIndex, &g_org_map[radioIndex]);
				UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );
                                UT_LOG("Setting config values same as vap_config file returns %d", result);
                            }
			}
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

    UT_LOG("Exiting test_createVAP_mapNULL...");
    return;
}

/**
 * @brief Tests requirements for L2 testing wifi_createVAP() with valid map, invalid radioIndex and verify if the values remain uncorrupted using wifi_getRadioVapInfoMap()
 *
 * Test Coverage: Negative Scenario
 *
 * @retval WIFI_HAL_INVALID_ARGUMENTS   -> tested
 *
 * @Note hal api is Synchronous
 */

void test_createVAP_invalidradio(void)
{
    UT_LOG("Entering test_createVAP_invalidradio...");

    int * apIndices = NULL;
    int index = 0, i = 0, result = 0, radioIndex = 0, returnStatus = 0;
    wifi_vap_info_map_t  map, map1;
    unsigned int numRadios = 0;
    int radioIndex_outOfRange = 99;
    int radioIndex_negative = -1;

    /* Get the number of radios applicable */
    returnStatus = test_utils_getMaxNumberOfRadio(&numRadios);

    if (returnStatus == 0)
    {
        UT_LOG("Number of Radios : %u", numRadios);

        /* Negative Test WIFI_HAL_INVALID_ARGUMENTS */
        /* Setting valid map, invalid radioIndex and expecting the API to return FAILURE */
        UT_LOG("Test Case 9");

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
		    result = wifi_getRadioVapInfoMap(radioIndex, &map);
		    UT_ASSERT_EQUAL(result, WIFI_HAL_SUCCESS);

		    for(i=0; i<map.num_vaps; i++)
		    {
	                if ((strstr(map1.vap_array[i].vap_name, "private_ssid") != NULL))
			{
			    UT_LOG("The initial values are map.vap_array[i].vap_name is %s, map.vap_array[i].vap_index is %d, map.vap_array[i].u.bss_info.enabled is %d, map.vap_array[i].u.bss_info.showSsid is %d and map.vap_array[i].u.bss_info.ssid is %s", map.vap_array[i].vap_name, map.vap_array[i].vap_index, map.vap_array[i].u.bss_info.enabled, map.vap_array[i].u.bss_info.showSsid, map.vap_array[i].u.bss_info.ssid);
			}
		    }

                    /* Negative Test WIFI_HAL_INVALID_ARGUMENTS */
	            /* Setting valid map, invalid radioIndex_outOfRange and expecting the API to return FAILURE */
		    UT_LOG("Test Case 9.1");
		    result = wifi_createVAP(radioIndex_outOfRange, &g_org_map[radioIndex]);
		    UT_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS );
                    UT_LOG("Setting valid map and invalid radioIndex_outOfRange using wifi_createVAP for radio %d returns : %d", radioIndex_outOfRange, result);

		    /* Negative Test WIFI_HAL_INVALID_ARGUMENTS */
		    /* Setting valid map, invalid radioIndex_negative and expecting the API to return FAILURE */
	            UT_LOG("Test Case 9.2");
		    result = wifi_createVAP(radioIndex_negative, &g_org_map[radioIndex]);
		    UT_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS );
		    UT_LOG("Setting valid map and invalid radioIndex_negative using wifi_createVAP for radio %d returns : %d", radioIndex_outOfRange, result);

		    result = wifi_getRadioVapInfoMap(radioIndex, &map1);
		    UT_ASSERT_EQUAL(result, WIFI_HAL_SUCCESS);

                    for(i=0; i<map1.num_vaps; i++)
                    {
                        if ((strstr(map1.vap_array[i].vap_name, "private_ssid") != NULL))
			{
			    UT_LOG("The values post createVAP are map1.vap_array[i].vap_name is %s, map1.vap_array[i].vap_index is %d, map1.vap_array[i].u.bss_info.enabled is %d, map1.vap_array[i].u.bss_info.showSsid is %d and map1.vap_array[i].u.bss_info.ssid is %s", map1.vap_array[i].vap_name, map1.vap_array[i].vap_index, map1.vap_array[i].u.bss_info.enabled, map1.vap_array[i].u.bss_info.showSsid, map1.vap_array[i].u.bss_info.ssid);

			    if ((map.vap_array[i].u.bss_info.enabled == map1.vap_array[i].u.bss_info.enabled) && (map.vap_array[i].u.bss_info.showSsid == map1.vap_array[i].u.bss_info.showSsid) && (strcmp(map.vap_array[i].u.bss_info.ssid, map1.vap_array[i].u.bss_info.ssid) == 0))
                            {
                                UT_LOG("The vapinfo values remain uncorrupted for Radio %d after setting invalid radioIndex and valid map to wifi_createVAP", radioIndex);
				UT_PASS("The vapinfo values remain uncorrupted after setting invalid radioIndex and valid map to wifi_createVAP");
                            }
                            else
                            {
                                UT_LOG("The vapinfo values got corrupted for Radio %d after setting invalid radioIndex and valid map to wifi_createVAP", radioIndex);
				UT_FAIL("The vapinfo values got corrupted after setting invalid radioIndex and valid map to wifi_createVAP");
				/* Set the map values back to those in vap_config file */
				g_org_map[radioIndex].num_vaps = 1;
				result = wifi_createVAP(radioIndex, &g_org_map[radioIndex]);
				UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );
				UT_LOG("Setting config values same as vap_config file returns %d", result);
                            }
                        }
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

    UT_LOG("Exiting test_createVAP_invalidradio...");
    return;
}

/**
 * @brief Tests requirements for L2 testing wifi_createVAP() with valid security parameters value and verify the set values using wifi_getRadioVapInfoMap()
 *
 * Test Coverage: Positive Scenario
 *
 * @retval WIFI_HAL_SUCCESS   -> tested
 *
 * @Note hal api is Synchronous
 */

void test_createVAP_security_valid_tc1(void)
{
    UT_LOG("Entering test_createVAP_securityValid_tc1...");

    int result = 0, index = 0, i = 0, radioIndex = 0, returnStatus = 0;
    int * apIndices = NULL;
    wifi_vap_info_map_t  map, map1, tmp_map;
    unsigned int numRadios = 0;

    /* Get the number of radios applicable */
    returnStatus = test_utils_getMaxNumberOfRadio(&numRadios);

    if (returnStatus == 0)
    {
        UT_LOG("Number of Radios : %u", numRadios);

        /* Postive Test WIFI_HAL_SUCCESS */
        /* Setting valid security info map and expecting the API to return success */
        UT_LOG("Test Case 10");

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
		    result = wifi_getRadioVapInfoMap(radioIndex, &map);
		    UT_ASSERT_EQUAL(result, WIFI_HAL_SUCCESS);

		    for(i=0; i<map.num_vaps; i++)
		    {
	                if ((strstr(map.vap_array[i].vap_name, "private_ssid") != NULL))
			{
			    UT_LOG("The initial values are map.vap_array[i].vap_name is %s, map.vap_array[i].vap_index is %d, map.vap_array[i].u.bss_info.security.mfp is %d, map.vap_array[i].u.bss_info.security.encr is %d map.vap_array[i].u.bss_info.security.mode is %d and map.vap_array[i].u.bss_info.security.u.key.key is %s", map.vap_array[i].vap_name, map.vap_array[i].vap_index, map.vap_array[i].u.bss_info.security.mfp, map.vap_array[i].u.bss_info.security.encr, map.vap_array[i].u.bss_info.security.mode, map.vap_array[i].u.bss_info.security.u.key.key);
			}
		    }

                    /* Initialize the values to be set */
                    tmp_map = g_org_map[radioIndex];
		    tmp_map.num_vaps = 1;
		    /* set valid values for mfp, encryption method, security mode and keypassphrase */
		    tmp_map.vap_array[0].u.bss_info.security.mfp = wifi_mfp_cfg_optional;
		    tmp_map.vap_array[0].u.bss_info.security.encr = wifi_encryption_aes_tkip;
		    tmp_map.vap_array[0].u.bss_info.security.mode = wifi_security_mode_wpa3_transition;
		    strcpy(tmp_map.vap_array[0].u.bss_info.security.u.key.key, "tdk@2023");

		    UT_LOG("Setting the security parameter values tmp_map.vap_array[0].u.bss_info.security.mfp is %d, tmp_map.vap_array[0].u.bss_info.security.encr is %d tmp_map.vap_array[0].u.bss_info.security.mode is %d and tmp_map.vap_array[0].u.bss_info.security.u.key.key is %s", tmp_map.vap_array[0].u.bss_info.security.mfp, tmp_map.vap_array[0].u.bss_info.security.encr, tmp_map.vap_array[0].u.bss_info.security.mode, tmp_map.vap_array[0].u.bss_info.security.u.key.key);
		    result = wifi_createVAP(radioIndex, &tmp_map);
		    UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );
		    UT_LOG("Setting valid security parameter values using wifi_createVAP for radio %d returns : %d", radioIndex, result);

		    result = wifi_getRadioVapInfoMap(radioIndex, &map1);
		    UT_ASSERT_EQUAL(result, WIFI_HAL_SUCCESS);

                    for(i=0; i<map1.num_vaps; i++)
                    {
	                if ((strstr(map1.vap_array[i].vap_name, "private_ssid") != NULL))
			{
			    UT_LOG("The values post createVAP are map1.vap_array[i].vap_name is %s, map1.vap_array[i].vap_index is %d, map1.vap_array[i].u.bss_info.security.mfp is %d, map1.vap_array[i].u.bss_info.security.encr is %d map1.vap_array[i].u.bss_info.security.mode is %d and map1.vap_array[i].u.bss_info.security.u.key.key is %s", map1.vap_array[i].vap_name, map1.vap_array[i].vap_index, map1.vap_array[i].u.bss_info.security.mfp, map1.vap_array[i].u.bss_info.security.encr, map1.vap_array[i].u.bss_info.security.mode, map1.vap_array[i].u.bss_info.security.u.key.key);

			    if((tmp_map.vap_array[0].u.bss_info.security.mfp == map1.vap_array[i].u.bss_info.security.mfp) && (tmp_map.vap_array[0].u.bss_info.security.encr == map1.vap_array[i].u.bss_info.security.encr) && (tmp_map.vap_array[0].u.bss_info.security.mode == map1.vap_array[i].u.bss_info.security.mode) && (strcmp(tmp_map.vap_array[0].u.bss_info.security.u.key.key, map1.vap_array[i].u.bss_info.security.u.key.key) == 0))
			    {
		                UT_LOG("The set security values using wifi_createVAP are reflected successfully for Radio %d in wifi_getRadioVapInfoMap", radioIndex);
				UT_PASS("The set security values using wifi_createVAP are reflected successfully in wifi_getRadioVapInfoMap");
			    }
			    else
			    {
				UT_LOG("The set security values using wifi_createVAP are NOT reflected for Radio %d in wifi_getRadioVapInfoMap", radioIndex);
				UT_FAIL("The set security values using wifi_createVAP are NOT reflected in wifi_getRadioVapInfoMap");
			    }
			}
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

    UT_LOG("Exiting test_createVAP_securityValid_tc1...");
    return;
}

/**
 * @brief Tests requirements for L2 testing wifi_createVAP() with valid security parameters value and verify the set values using wifi_getRadioVapInfoMap()
 *
 * Test Coverage: Positive Scenario
 *
 * @retval WIFI_HAL_SUCCESS   -> tested
 *
 * @Note hal api is Synchronous
 */

void test_createVAP_security_valid_tc2(void)
{
    UT_LOG("Entering test_createVAP_securityValid_tc2...");

    int result = 0, index = 0, i = 0, radioIndex = 0, returnStatus = 0;
    int * apIndices = NULL;
    wifi_vap_info_map_t  map, map1, tmp_map;
    unsigned int numRadios = 0;

    /* Get the number of radios applicable */
    returnStatus = test_utils_getMaxNumberOfRadio(&numRadios);

    if (returnStatus == 0)
    {
        UT_LOG("Number of Radios : %u", numRadios);

        /* Postive Test WIFI_HAL_SUCCESS */
        /* Setting valid security info map and expecting the API to return success */
        UT_LOG("Test Case 11");

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
		    result = wifi_getRadioVapInfoMap(radioIndex, &map);
		    UT_ASSERT_EQUAL(result, WIFI_HAL_SUCCESS);

		    for(i=0; i<map.num_vaps; i++)
		    {
		        if ((strstr(map.vap_array[i].vap_name, "private_ssid") != NULL))
			{
			    UT_LOG("The initial values are map.vap_array[i].vap_name is %s, map.vap_array[i].vap_index is %d, map.vap_array[i].u.bss_info.security.mfp is %d, map.vap_array[i].u.bss_info.security.encr is %d map.vap_array[i].u.bss_info.security.mode is %d and map.vap_array[i].u.bss_info.security.u.key.key is %s", map.vap_array[i].vap_name, map.vap_array[i].vap_index, map.vap_array[i].u.bss_info.security.mfp, map.vap_array[i].u.bss_info.security.encr, map.vap_array[i].u.bss_info.security.mode, map.vap_array[i].u.bss_info.security.u.key.key);
			}
		    }

                    /* Initialize the values to be set */
                    tmp_map = g_org_map[radioIndex];
                    tmp_map.num_vaps = 1;
                    /* set valid values for mfp, encryption method, security mode and keypassphrase */
                    tmp_map.vap_array[0].u.bss_info.security.mfp = wifi_mfp_cfg_disabled;
                    tmp_map.vap_array[0].u.bss_info.security.encr = wifi_encryption_aes;
                    tmp_map.vap_array[0].u.bss_info.security.mode = wifi_security_mode_wpa2_personal;
                    strcpy(tmp_map.vap_array[0].u.bss_info.security.u.key.key, "folded9656angle");

		    UT_LOG("Setting the security parameter values tmp_map.vap_array[0].u.bss_info.security.mfp is %d, tmp_map.vap_array[0].u.bss_info.security.encr is %d tmp_map.vap_array[0].u.bss_info.security.mode is %d and tmp_map.vap_array[0].u.bss_info.security.u.key.key is %s", tmp_map.vap_array[0].u.bss_info.security.mfp, tmp_map.vap_array[0].u.bss_info.security.encr, tmp_map.vap_array[0].u.bss_info.security.mode, tmp_map.vap_array[0].u.bss_info.security.u.key.key);
		    result = wifi_createVAP(radioIndex, &tmp_map);
		    UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );
                    UT_LOG("Setting valid security parameter values using wifi_createVAP for radio %d returns : %d", radioIndex, result);

		    result = wifi_getRadioVapInfoMap(radioIndex, &map1);
		    UT_ASSERT_EQUAL(result, WIFI_HAL_SUCCESS);

                    for(i=0; i<map1.num_vaps; i++)
                    {
	                if ((strstr(map1.vap_array[i].vap_name, "private_ssid") != NULL))
			{
	                    UT_LOG("The values post createVAP are map1.vap_array[i].vap_name is %s, map1.vap_array[i].vap_index is %d, map1.vap_array[i].u.bss_info.security.mfp is %d, map1.vap_array[i].u.bss_info.security.encr is %d map1.vap_array[i].u.bss_info.security.mode is %d and map1.vap_array[i].u.bss_info.security.u.key.key is %s", map1.vap_array[i].vap_name, map1.vap_array[i].vap_index, map1.vap_array[i].u.bss_info.security.mfp, map1.vap_array[i].u.bss_info.security.encr, map1.vap_array[i].u.bss_info.security.mode, map1.vap_array[i].u.bss_info.security.u.key.key);

                            if((tmp_map.vap_array[0].u.bss_info.security.mfp == map1.vap_array[i].u.bss_info.security.mfp) && (tmp_map.vap_array[0].u.bss_info.security.encr == map1.vap_array[i].u.bss_info.security.encr) && (tmp_map.vap_array[0].u.bss_info.security.mode == map1.vap_array[i].u.bss_info.security.mode) && (strcmp(tmp_map.vap_array[0].u.bss_info.security.u.key.key, map1.vap_array[i].u.bss_info.security.u.key.key) == 0))
                            {
                                UT_LOG("The set security values using wifi_createVAP are reflected successfully for Radio %d in wifi_getRadioVapInfoMap", radioIndex);
				UT_PASS("The set security values using wifi_createVAP are reflected successfully in wifi_getRadioVapInfoMap");
                            }
                            else
                            {
                                UT_LOG("The set security values using wifi_createVAP are NOT reflected for Radio %d in wifi_getRadioVapInfoMap", radioIndex);
				UT_FAIL("The set security values using wifi_createVAP are NOT reflected in wifi_getRadioVapInfoMap");
                            }
			}
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

    UT_LOG("Exiting test_createVAP_securityValid_tc2...");
    return;
}

/**
 * @brief Tests requirements for L2 testing wifi_createVAP() with invalid security parameters value and verify if values remain uncorrupted using wifi_getRadioVapInfoMap()
 *
 * Test Coverage: Negative Scenario
 *
 * @retval WIFI_HAL_INVALID_ARGUMENTS   -> tested
 *
 * @Note hal api is Synchronous
 */

void test_createVAP_security_Invalid(void)
{
    UT_LOG("Entering test_createVAP_security_Invalid...");

    int result = 0, index = 0, i = 0, radioIndex = 0, returnStatus = 0;
    int * apIndices = NULL;
    wifi_vap_info_map_t  map, map1, tmp_map;
    unsigned int numRadios = 0;

    /* Get the number of radios applicable */
    returnStatus = test_utils_getMaxNumberOfRadio(&numRadios);

    if (returnStatus == 0)
    {
        UT_LOG("Number of Radios : %u", numRadios);

        /* Negative Test WIFI_HAL_INVALID_ARGUMENTS */
        /* Setting invalid security info map and expecting the API to return failure */
        UT_LOG("Test Case 12");

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
		    result = wifi_getRadioVapInfoMap(radioIndex, &map);
		    UT_ASSERT_EQUAL(result, WIFI_HAL_SUCCESS);

		    for(i=0; i<map.num_vaps; i++)
		    {
	                if ((strstr(map.vap_array[i].vap_name, "private_ssid") != NULL))
			{
			    UT_LOG("The initial values are map.vap_array[i].vap_name is %s, map.vap_array[i].vap_index is %d, map.vap_array[i].u.bss_info.security.mfp is %d, map.vap_array[i].u.bss_info.security.encr is %d map.vap_array[i].u.bss_info.security.mode %d and map.vap_array[i].u.bss_info.security.u.key.key is %s", map.vap_array[i].vap_name, map.vap_array[i].vap_index, map.vap_array[i].u.bss_info.security.mfp, map.vap_array[i].u.bss_info.security.encr, map.vap_array[i].u.bss_info.security.mode, map.vap_array[i].u.bss_info.security.u.key.key);
			}
		    }

                    /* Initialize the values to be set */
		    tmp_map = g_org_map[radioIndex];
		    tmp_map.num_vaps = 1;
		    /* set invalid values for mfp, encryption method, security mode and keypassphrase */
		    tmp_map.vap_array[0].u.bss_info.security.mfp = 4;
                    tmp_map.vap_array[0].u.bss_info.security.encr = 7;
                    tmp_map.vap_array[0].u.bss_info.security.mode = 0x00000100;
                    strcpy(tmp_map.vap_array[0].u.bss_info.security.u.key.key, "");

		    UT_LOG("Setting the security parameter values tmp_map.vap_array[0].u.bss_info.security.mfp is %d, tmp_map.vap_array[0].u.bss_info.security.encr is %d tmp_map.vap_array[0].u.bss_info.security.mode is %d and tmp_map.vap_array[0].u.bss_info.security.u.key.key is %s", tmp_map.vap_array[0].u.bss_info.security.mfp, tmp_map.vap_array[0].u.bss_info.security.encr, tmp_map.vap_array[0].u.bss_info.security.mode, tmp_map.vap_array[0].u.bss_info.security.u.key.key);						result = wifi_createVAP(radioIndex, &tmp_map);
	            UT_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS );
		    UT_LOG("Setting invalid security parameters using wifi_createVAP for radio %d returns : %d", radioIndex, result);

		    result = wifi_getRadioVapInfoMap(radioIndex, &map1);
		    UT_ASSERT_EQUAL(result, WIFI_HAL_SUCCESS);

                    for(i=0; i<map1.num_vaps; i++)
                    {
	                if ((strstr(map1.vap_array[i].vap_name, "private_ssid") != NULL))
			{
			    UT_LOG("The values post wifi_createVAP are map1.vap_array[i].vap_name is %s, map1.vap_array[i].vap_index is %d, map1.vap_array[i].u.bss_info.security.mfp is %d, map1.vap_array[i].u.bss_info.security.encr is %d map1.vap_array[i].u.bss_info.security.mode %d and map1.vap_array[i].u.bss_info.security.u.key.key is %s", map1.vap_array[i].vap_name, map1.vap_array[i].vap_index, map1.vap_array[i].u.bss_info.security.mfp, map1.vap_array[i].u.bss_info.security.encr, map1.vap_array[i].u.bss_info.security.mode, map1.vap_array[i].u.bss_info.security.u.key.key);

			    if((map.vap_array[i].u.bss_info.security.mfp == map1.vap_array[i].u.bss_info.security.mfp) && (map.vap_array[i].u.bss_info.security.encr == map1.vap_array[i].u.bss_info.security.encr) && (map.vap_array[i].u.bss_info.security.mode == map1.vap_array[i].u.bss_info.security.mode) && (strcmp(map.vap_array[i].u.bss_info.security.u.key.key, map1.vap_array[i].u.bss_info.security.u.key.key) == 0))
                            {
                                UT_LOG("The security values remain uncorrupted for Radio %d after setting valid radioIndex and vapinfomap with invalid values to wifi_createVAP", radioIndex);
				UT_PASS("The security values remain uncorrupted after setting valid radioIndex and vapinfomap with invalid values to wifi_createVAP");
			    }
                            else
                            {
                                UT_LOG("The security values got corrupted for Radio %d after setting valid radioIndex and vapinfomap with invalid values to wifi_createVAP", radioIndex);
				UT_FAIL("The security values got corrupted after setting valid radioIndex and vapinfomap with invalid values to wifi_createVAP");
				/* Set the map values back to those in vap_config file */
				g_org_map[radioIndex].num_vaps = 1;
				result = wifi_createVAP(radioIndex, &g_org_map[radioIndex]);
				UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );
				UT_LOG("Setting config values same as vap_config file returns %d", result);
                            }
			}
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

    UT_LOG("Exiting test_createVAP_security_Invalid...");
    return;
}

/**
 * @brief Tests requirements for L2 testing wifi_createVAP() with valid interworking parameters value and verify the set values using wifi_getRadioVapInfoMap()
 *
 * Test Coverage: Positive Scenario
 *
 * @retval WIFI_HAL_SUCCESS   -> tested
 *
 * @Note hal api is Synchronous
 */

void test_createVAP_interworking_valid_tc1(void)
{
    UT_LOG("Entering test_createVAP_interworking_valid_tc1...");

    int result = 0, index = 0, i = 0, radioIndex = 0, returnStatus = 0;
    int * apIndices = NULL;
    wifi_vap_info_map_t  map, map1, tmp_map;
    unsigned int numRadios = 0;

    /* Get the number of radios applicable */
    returnStatus = test_utils_getMaxNumberOfRadio(&numRadios);

    if (returnStatus == 0)
    {
        UT_LOG("Number of Radios : %u", numRadios);

        /* Postive Test WIFI_HAL_SUCCESS */
        /* Setting valid interworking info map and expecting the API to return success */
        UT_LOG("Test Case 13");

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
		    result = wifi_getRadioVapInfoMap(radioIndex, &map);
		    UT_ASSERT_EQUAL(result, WIFI_HAL_SUCCESS);

		    for(i=0; i<map.num_vaps; i++)
		    {
	                if ((strstr(map.vap_array[i].vap_name, "private_ssid") != NULL))
			{
		            UT_LOG("The initial values are map.vap_array[i].vap_name is %s, map.vap_array[i].vap_index is %d, map.vap_array[i].u.bss_info.interworking.interworking.interworkingEnabled is %d, map.vap_array[i].u.bss_info.interworking.interworking.accessNetworkType is %d and map.vap_array[i].u.bss_info.interworking.interworking.internetAvailable is %d",map.vap_array[i].vap_name, map.vap_array[i].vap_index, map.vap_array[i].u.bss_info.interworking.interworking.interworkingEnabled, map.vap_array[i].u.bss_info.interworking.interworking.accessNetworkType, map.vap_array[i].u.bss_info.interworking.interworking.internetAvailable);
                        }
		    }

                    /* Initialize the values to be set */
		    tmp_map = g_org_map[radioIndex];
		    tmp_map.num_vaps = 1;
                    /* set valid values for interworkingEnabled(set to true), accessNetworkType and internetAvailable */
                    tmp_map.vap_array[0].u.bss_info.interworking.interworking.interworkingEnabled = 1;
                    tmp_map.vap_array[0].u.bss_info.interworking.interworking.accessNetworkType = 1;
                    tmp_map.vap_array[0].u.bss_info.interworking.interworking.internetAvailable = 1;

		    UT_LOG("Setting the interworking parameter values tmp_map.vap_array[0].u.bss_info.interworking.interworking.interworkingEnabled is %d, tmp_map.vap_array[0].u.bss_info.interworking.interworking.accessNetworkType is %d and tmp_map.vap_array[0].u.bss_info.interworking.interworking.internetAvailable is %d", tmp_map.vap_array[0].u.bss_info.interworking.interworking.interworkingEnabled, tmp_map.vap_array[0].u.bss_info.interworking.interworking.accessNetworkType, tmp_map.vap_array[0].u.bss_info.interworking.interworking.internetAvailable);
		    result = wifi_createVAP(radioIndex, &tmp_map);
		    UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );
		    UT_LOG("Setting valid interworking parameters using wifi_createVAP for radio %d returns : %d", radioIndex, result);

		    result = wifi_getRadioVapInfoMap(radioIndex, &map1);
                    UT_ASSERT_EQUAL(result, WIFI_HAL_SUCCESS);
                    for(i=0; i<map1.num_vaps; i++)
                    {
	                if ((strstr(map1.vap_array[i].vap_name, "private_ssid") != NULL))
			{
			    UT_LOG("The values post createVAP are map1.vap_array[i].vap_name is %s, map1.vap_array[i].vap_index is %d, map1.vap_array[i].u.bss_info.interworking.interworking.interworkingEnabled is %d, map1.vap_array[i].u.bss_info.interworking.interworking.accessNetworkType is %d and map1.vap_array[i].u.bss_info.interworking.interworking.internetAvailable is %d",map1.vap_array[i].vap_name, map1.vap_array[i].vap_index, map1.vap_array[i].u.bss_info.interworking.interworking.interworkingEnabled, map1.vap_array[i].u.bss_info.interworking.interworking.accessNetworkType, map1.vap_array[i].u.bss_info.interworking.interworking.internetAvailable);

			    if((tmp_map.vap_array[0].u.bss_info.interworking.interworking.interworkingEnabled == map1.vap_array[i].u.bss_info.interworking.interworking.interworkingEnabled) && (tmp_map.vap_array[0].u.bss_info.interworking.interworking.accessNetworkType == map1.vap_array[i].u.bss_info.interworking.interworking.accessNetworkType) && (tmp_map.vap_array[0].u.bss_info.interworking.interworking.internetAvailable == map1.vap_array[i].u.bss_info.interworking.interworking.internetAvailable))
			    {
		                UT_LOG("The set interworking values using wifi_createVAP are reflected successfully for Radio %d in wifi_getRadioVapInfoMap", radioIndex);
				UT_PASS("The set interworking values using wifi_createVAP are reflected successfully in wifi_getRadioVapInfoMap");
			    }
			    else
			    {
				UT_LOG("The set interworking values using wifi_createVAP are NOT reflected for Radio %d in wifi_getRadioVapInfoMap", radioIndex);
				UT_FAIL("The set interworking values using wifi_createVAP are NOT reflected in wifi_getRadioVapInfoMap");
			    }
                        }
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

    UT_LOG("Exiting test_createVAP_interworking_valid_tc1...");
    return;
}

/**
 * @brief Tests requirements for L2 testing wifi_createVAP() with valid interworking parameters value and verify the set values using wifi_getRadioVapInfoMap()
 *
 * Test Coverage: Positive Scenario
 *
 * @retval WIFI_HAL_SUCCESS   -> tested
 *
 * @Note hal api is Synchronous
 */

void test_createVAP_interworking_valid_tc2(void)
{
    UT_LOG("Entering test_createVAP_interworking_valid_tc2...");

    int result = 0, index = 0, i = 0, radioIndex = 0, returnStatus = 0;
    int * apIndices = NULL;
    wifi_vap_info_map_t  map, map1, tmp_map;
    unsigned int numRadios = 0;

    /* Get the number of radios applicable */
    returnStatus = test_utils_getMaxNumberOfRadio(&numRadios);

    if (returnStatus == 0)
    {
        UT_LOG("Number of Radios : %u", numRadios);

        /* Postive Test WIFI_HAL_SUCCESS */
        /* Setting valid interworking info map and expecting the API to return success */
        UT_LOG("Test Case 14");

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
		    result = wifi_getRadioVapInfoMap(radioIndex, &map);
		    UT_ASSERT_EQUAL(result, WIFI_HAL_SUCCESS);

		    for(i=0; i<map.num_vaps; i++)
		    {
	                if ((strstr(map.vap_array[i].vap_name, "private_ssid") != NULL))
			{
			    UT_LOG("The initial values are map.vap_array[i].vap_name is %s, map.vap_array[i].vap_index is %d, map.vap_array[i].u.bss_info.interworking.interworking.interworkingEnabled is %d, map.vap_array[i].u.bss_info.interworking.interworking.accessNetworkType is %d and map.vap_array[i].u.bss_info.interworking.interworking.internetAvailable is %d", map.vap_array[i].vap_name, map.vap_array[i].vap_index, map.vap_array[i].u.bss_info.interworking.interworking.interworkingEnabled, map.vap_array[i].u.bss_info.interworking.interworking.accessNetworkType, map.vap_array[i].u.bss_info.interworking.interworking.internetAvailable);
                        }
		    }

                    /* Initialize the values to be set */
		    tmp_map = g_org_map[radioIndex];
		    tmp_map.num_vaps = 1;
                    /* set valid values for interworkingEnabled(set to true), accessNetworkType and internetAvailable */
                    tmp_map.vap_array[0].u.bss_info.interworking.interworking.interworkingEnabled = 0;
                    tmp_map.vap_array[0].u.bss_info.interworking.interworking.accessNetworkType = 0;
                    tmp_map.vap_array[0].u.bss_info.interworking.interworking.internetAvailable = 0;

		    UT_LOG("Setting the interworking parameter values tmp_map.vap_array[0].u.bss_info.interworking.interworking.interworkingEnabled is %d, tmp_map.vap_array[0].u.bss_info.interworking.interworking.accessNetworkType is %d and tmp_map.vap_array[0].u.bss_info.interworking.interworking.internetAvailable is %d", tmp_map.vap_array[0].u.bss_info.interworking.interworking.interworkingEnabled, tmp_map.vap_array[0].u.bss_info.interworking.interworking.accessNetworkType, tmp_map.vap_array[0].u.bss_info.interworking.interworking.internetAvailable);
		    result = wifi_createVAP(radioIndex, &tmp_map);
                    UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );
                    UT_LOG("Setting valid interworking parameters using wifi_createVAP for radio %d returns : %d", radioIndex, result);

		    result = wifi_getRadioVapInfoMap(radioIndex, &map1);
                    UT_ASSERT_EQUAL(result, WIFI_HAL_SUCCESS);

                    for(i=0; i<map1.num_vaps; i++)
                    {
	                if ((strstr(map1.vap_array[i].vap_name, "private_ssid") != NULL))
			{
			    UT_LOG("The values post createVAP are map1.vap_array[i].vap_name is %s, map1.vap_array[i].vap_index is %d, map1.vap_array[i].u.bss_info.interworking.interworking.interworkingEnabled is %d, map1.vap_array[i].u.bss_info.interworking.interworking.accessNetworkType is %d and map1.vap_array[i].u.bss_info.interworking.interworking.internetAvailable is %d", map1.vap_array[i].vap_name, map1.vap_array[i].vap_index, map1.vap_array[i].u.bss_info.interworking.interworking.interworkingEnabled, map1.vap_array[i].u.bss_info.interworking.interworking.accessNetworkType, map1.vap_array[i].u.bss_info.interworking.interworking.internetAvailable);

			    if((tmp_map.vap_array[0].u.bss_info.interworking.interworking.interworkingEnabled == map1.vap_array[i].u.bss_info.interworking.interworking.interworkingEnabled) && (tmp_map.vap_array[0].u.bss_info.interworking.interworking.accessNetworkType == map1.vap_array[i].u.bss_info.interworking.interworking.accessNetworkType) && (tmp_map.vap_array[0].u.bss_info.interworking.interworking.internetAvailable == map1.vap_array[i].u.bss_info.interworking.interworking.internetAvailable))
                            {
                                UT_LOG("The set interworking values using wifi_createVAP are reflected successfully for Radio %d in wifi_getRadioVapInfoMap", radioIndex);
                                UT_PASS("The set interworking values using wifi_createVAP are reflected successfully in wifi_getRadioVapInfoMap");
                            }
                            else
                            {
                                UT_LOG("The set interworking values using wifi_createVAP are NOT reflected for Radio %d in wifi_getRadioVapInfoMap", radioIndex);
                                UT_FAIL("The set interworking values using wifi_createVAP are NOT reflected in wifi_getRadioVapInfoMap");
                            }
                        }
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

    UT_LOG("Exiting test_createVAP_interworking_valid_tc2...");
    return;
}

/**
 * @brief Tests requirements for L2 testing wifi_createVAP() with invalid interworking vapinfo parameters value and verify if values remain uncorrupted using wifi_getRadioVapInfoMap()
 *
 * Test Coverage: Negative Scenario
 *
 * @retval WIFI_HAL_INVALID_ARGUMENTS   -> tested
 *
 * @Note hal api is Synchronous
 */

void test_createVAP_interworking_Invalid(void)
{
    UT_LOG("Entering test_createVAP_interworking_Invalid...");

    int result = 0, index = 0, i = 0, radioIndex = 0, returnStatus = 0;
    int * apIndices = NULL;
    wifi_vap_info_map_t  map, map1, tmp_map;
    unsigned int numRadios = 0;

    /* Get the number of radios applicable */
    returnStatus = test_utils_getMaxNumberOfRadio(&numRadios);

    if (returnStatus == 0)
    {
        UT_LOG("Number of Radios : %u", numRadios);

        /* Negative Test WIFI_HAL_INVALID_ARGUMENTS */
        /* Setting invalid interworking info map and expecting the API to return failure */
        UT_LOG("Test Case 15");

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
		    result = wifi_getRadioVapInfoMap(radioIndex, &map);
		    UT_ASSERT_EQUAL(result, WIFI_HAL_SUCCESS);

		    for(i=0; i<map.num_vaps; i++)
		    {
	                if ((strstr(map.vap_array[i].vap_name, "private_ssid") != NULL))
			{
			    UT_LOG("Initial values are map.vap_array[i].vap_name is %s, map.vap_array[i].vap_index is %d, map.vap_array[i].u.bss_info.interworking.interworking.interworkingEnabled is %d, map.vap_array[i].u.bss_info.interworking.interworking.accessNetworkType is %d and map.vap_array[i].u.bss_info.interworking.interworking.internetAvailable is %d", map.vap_array[i].vap_name, map.vap_array[i].vap_index, map.vap_array[i].u.bss_info.interworking.interworking.interworkingEnabled, map.vap_array[i].u.bss_info.interworking.interworking.accessNetworkType, map.vap_array[i].u.bss_info.interworking.interworking.internetAvailable);
			}
		    }

                    /* Initialize the values to be set */
                    tmp_map = g_org_map[radioIndex];
                    tmp_map.num_vaps = 1;
                    /* set invalid values for interworkingEnabled, accessNetworkType and internetAvailable */
                    tmp_map.vap_array[0].u.bss_info.interworking.interworking.interworkingEnabled = 16;
                    tmp_map.vap_array[0].u.bss_info.interworking.interworking.accessNetworkType = 2000;
                    tmp_map.vap_array[0].u.bss_info.interworking.interworking.internetAvailable = 71;

		    UT_LOG("Setting the interworking parameter values tmp_map.vap_array[0].u.bss_info.interworking.interworking.interworkingEnabled is %d, tmp_map.vap_array[0].u.bss_info.interworking.interworking.accessNetworkType is %d and tmp_map.vap_array[0].u.bss_info.interworking.interworking.internetAvailable is %d", tmp_map.vap_array[0].u.bss_info.interworking.interworking.interworkingEnabled, tmp_map.vap_array[0].u.bss_info.interworking.interworking.accessNetworkType, tmp_map.vap_array[0].u.bss_info.interworking.interworking.internetAvailable);
		    result = wifi_createVAP(radioIndex, &tmp_map);
		    UT_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS );
		    UT_LOG("Setting invalid interworking parameters using wifi_createVAP for radio %d returns : %d", radioIndex, result);

		    result = wifi_getRadioVapInfoMap(radioIndex, &map1);
		    UT_ASSERT_EQUAL(result, WIFI_HAL_SUCCESS);
                    for(i=0; i<map1.num_vaps; i++)
                    {
	                if ((strstr(map1.vap_array[i].vap_name, "private_ssid") != NULL))
			{
			    UT_LOG("The values post createVAP are map1.vap_array[i].vap_name is %s, map1.vap_array[i].vap_index is %d, map1.vap_array[i].u.bss_info.interworking.interworking.interworkingEnabled is %d, map1.vap_array[i].u.bss_info.interworking.interworking.accessNetworkType is %d and map1.vap_array[i].u.bss_info.interworking.interworking.internetAvailable is %d", map1.vap_array[i].vap_name, map1.vap_array[i].vap_index, map1.vap_array[i].u.bss_info.interworking.interworking.interworkingEnabled, map1.vap_array[i].u.bss_info.interworking.interworking.accessNetworkType, map1.vap_array[i].u.bss_info.interworking.interworking.internetAvailable);

			    if((map.vap_array[i].u.bss_info.interworking.interworking.interworkingEnabled == map1.vap_array[i].u.bss_info.interworking.interworking.interworkingEnabled) && (map.vap_array[i].u.bss_info.interworking.interworking.accessNetworkType == map1.vap_array[i].u.bss_info.interworking.interworking.accessNetworkType) && (map.vap_array[i].u.bss_info.interworking.interworking.internetAvailable == map1.vap_array[i].u.bss_info.interworking.interworking.internetAvailable))
                            {
                                UT_LOG("The interworking values remain uncorrupted for Radio %d after setting valid radioIndex and vapinfomap with invalid values to wifi_createVAP", radioIndex);
				UT_PASS("The interworking values remain uncorrupted after setting valid radioIndex and vapinfomap with invalid values to wifi_createVAP");
                            }
                            else
                            {
                                UT_LOG("The interworking values got corrupted for Radio %d after setting valid radioIndex and vapinfomap with invalid values to wifi_createVAP", radioIndex);
			        UT_FAIL("The interworking values got corrupted after setting valid radioIndex and vapinfomap with invalid values to wifi_createVAP");
				/* Set the map values back to those in vap_config file */
				g_org_map[radioIndex].num_vaps = 1;
				result = wifi_createVAP(radioIndex, &g_org_map[radioIndex]);
				UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );
				UT_LOG("Setting config values same as vap_config file returns %d", result);
                            }
			}
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

    UT_LOG("Exiting test_createVAP_interworking_Invalid...");
    return;
}

/**
 * @brief Tests requirements for L2 testing wifi_createVAP() with valid wps parameters value and verify the set values using wifi_getRadioVapInfoMap()
 *
 * Test Coverage: Positive Scenario
 *
 * @retval WIFI_HAL_SUCCESS   -> tested
 *
 * @Note hal api is Synchronous
 */

void test_createVAP_wps_valid_tc1(void)
{
    UT_LOG("Entering test_createVAP_wps_valid_tc1...");

    int result = 0, index = 0, i = 0, radioIndex = 0, returnStatus = 0;
    int * apIndices = NULL;
    wifi_vap_info_map_t  map, map1, tmp_map;
    unsigned int numRadios = 0;

    /* Get the number of radios applicable */
    returnStatus = test_utils_getMaxNumberOfRadio(&numRadios);

    if (returnStatus == 0)
    {
        UT_LOG("Number of Radios : %u", numRadios);

        /* Postive Test WIFI_HAL_SUCCESS */
        /* Setting valid wps info map and expecting the API to return success */
        UT_LOG("Test Case 16");

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
		    result = wifi_getRadioVapInfoMap(radioIndex, &map);
		    UT_ASSERT_EQUAL(result, WIFI_HAL_SUCCESS);

		    for(i=0; i<map.num_vaps; i++)
	            {
                        if ((strstr(map.vap_array[i].vap_name, "private_ssid") != NULL))
			{
			    UT_LOG("The initial values are map.vap_array[i].vap_name is %s, map.vap_array[i].vap_index is %d, map.vap_array[i].u.bss_info.wps.enable is %d, map.vap_array[i].u.bss_info.wps.methods is %d and map.vap_array[i].u.bss_info.wps.pin is %s", map.vap_array[i].vap_name, map.vap_array[i].vap_index, map.vap_array[i].u.bss_info.wps.enable, map.vap_array[i].u.bss_info.wps.methods, map.vap_array[i].u.bss_info.wps.pin);
                        }
	            }

                    /* Initialize the values to be set */
                    tmp_map = g_org_map[radioIndex];
                    tmp_map.num_vaps = 1;
                    /* set valid values for wps enable(set to false), methods and wps-pin */
                    tmp_map.vap_array[0].u.bss_info.wps.enable = 0;
                    tmp_map.vap_array[0].u.bss_info.wps.methods = WIFI_ONBOARDINGMETHODS_PIN;
                    strcpy(tmp_map.vap_array[0].u.bss_info.wps.pin, "98765432");

		    UT_LOG("Setting the wps parameter values tmp_map.vap_array[0].u.bss_info.wps.enable is %d, tmp_map.vap_array[0].u.bss_info.wps.methods is %d and tmp_map.vap_array[0].u.bss_info.wps.pin is %s", tmp_map.vap_array[0].u.bss_info.wps.enable, tmp_map.vap_array[0].u.bss_info.wps.methods, tmp_map.vap_array[0].u.bss_info.wps.pin);
		    result = wifi_createVAP(radioIndex, &tmp_map);
		    UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );
		    UT_LOG("Setting valid VAP info map using wifi_createVAP for radio %d returns : %d", radioIndex, result);

		    result = wifi_getRadioVapInfoMap(radioIndex, &map1);
	            UT_ASSERT_EQUAL(result, WIFI_HAL_SUCCESS);

                    for(i=0; i<map1.num_vaps; i++)
                    {
	                if ((strstr(map1.vap_array[i].vap_name, "private_ssid") != NULL))
			{
			    UT_LOG("The values post createVAP are map1.vap_array[i].vap_name is %s, map1.vap_array[i].vap_index is %d, map1.vap_array[i].u.bss_info.wps.enable is %d, map1.vap_array[i].u.bss_info.wps.methods is %d and map1.vap_array[i].u.bss_info.wps.pin is %s", map1.vap_array[i].vap_name, map1.vap_array[i].vap_index, map1.vap_array[i].u.bss_info.wps.enable, map1.vap_array[i].u.bss_info.wps.methods, map1.vap_array[i].u.bss_info.wps.pin);

			    if((tmp_map.vap_array[0].u.bss_info.wps.enable == map1.vap_array[i].u.bss_info.wps.enable) && (tmp_map.vap_array[0].u.bss_info.wps.methods == map1.vap_array[i].u.bss_info.wps.methods) && (strcmp(tmp_map.vap_array[0].u.bss_info.wps.pin, map1.vap_array[i].u.bss_info.wps.pin) == 0))
			    {
		                UT_LOG("The set wps values using wifi_createVAP are reflected successfully for Radio %d in wifi_getRadioVapInfoMap", radioIndex);
				UT_PASS("The set wps values using wifi_createVAP are reflected successfully in wifi_getRadioVapInfoMap");
		            }
			    else
			    {
				UT_LOG("The set wps values using wifi_createVAP are NOT reflected for Radio %d in wifi_getRadioVapInfoMap", radioIndex);
				UT_FAIL("The set wps values using wifi_createVAP are NOT reflected in wifi_getRadioVapInfoMap");
			    }
			}
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

    UT_LOG("Exiting test_createVAP_wps_valid_tc1...");
    return;
}

/**
 * @brief Tests requirements for L2 testing wifi_createVAP() with valid wps parameters value and verify the set values using wifi_getRadioVapInfoMap()
 *
 * Test Coverage: Positive Scenario
 *
 * @retval WIFI_HAL_SUCCESS   -> tested
 *
 * @Note hal api is Synchronous
 */

void test_createVAP_wps_valid_tc2(void)
{
    UT_LOG("Entering test_createVAP_wps_valid_tc2...");

    int result = 0, index = 0, i = 0, radioIndex = 0, returnStatus = 0;
    int * apIndices = NULL;
    wifi_vap_info_map_t  map, map1, tmp_map;
    unsigned int numRadios = 0;

    /* Get the number of radios applicable */
    returnStatus = test_utils_getMaxNumberOfRadio(&numRadios);

    if (returnStatus == 0)
    {
        UT_LOG("Number of Radios : %u", numRadios);

        /* Postive Test WIFI_HAL_SUCCESS */
        /* Setting valid wps info map and expecting the API to return success */
        UT_LOG("Test Case 17");

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
		    result = wifi_getRadioVapInfoMap(radioIndex, &map);
		    UT_ASSERT_EQUAL(result, WIFI_HAL_SUCCESS);
		    for(i=0; i<map.num_vaps; i++)
		    {
	                if ((strstr(map.vap_array[i].vap_name, "private_ssid") != NULL))
			{
			    UT_LOG("The initial values are map.vap_array[i].vap_name is %s, map.vap_array[i].vap_index is %d, map.vap_array[i].u.bss_info.wps.enable is %d, map.vap_array[i].u.bss_info.wps.methods is %d and map.vap_array[i].u.bss_info.wps.pin is %s", map.vap_array[i].vap_name, map.vap_array[i].vap_index, map.vap_array[i].u.bss_info.wps.enable, map.vap_array[i].u.bss_info.wps.methods, map.vap_array[i].u.bss_info.wps.pin);
                        }
		    }


                    /* Initialize the values to be set */
                    tmp_map = g_org_map[radioIndex];
		    tmp_map.num_vaps = 1;
		    /* set valid values for wps enable(set to true), methods and wps-pin */
		    tmp_map.vap_array[0].u.bss_info.wps.enable = 1;
		    tmp_map.vap_array[0].u.bss_info.wps.methods = WIFI_ONBOARDINGMETHODS_PUSHBUTTON;
                    strcpy(tmp_map.vap_array[0].u.bss_info.wps.pin, "69468780");

		    UT_LOG("Setting the wps parameter values tmp_map.vap_array[0].u.bss_info.wps.enable is %d, tmp_map.vap_array[0].u.bss_info.wps.methods is %d and tmp_map.vap_array[0].u.bss_info.wps.pin is %s", tmp_map.vap_array[0].u.bss_info.wps.enable, tmp_map.vap_array[0].u.bss_info.wps.methods, tmp_map.vap_array[0].u.bss_info.wps.pin);
		    result = wifi_createVAP(radioIndex, &tmp_map);
		    UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );
		    UT_LOG("Setting valid VAP info map using wifi_createVAP for radio %d returns : %d", radioIndex, result);

		    result = wifi_getRadioVapInfoMap(radioIndex, &map1);
		    UT_ASSERT_EQUAL(result, WIFI_HAL_SUCCESS);

                    for(i=0; i<map1.num_vaps; i++)
                    {
                        if ((strstr(map1.vap_array[i].vap_name, "private_ssid") != NULL))
			{
			    UT_LOG("The values post createVAP are map1.vap_array[i].vap_name is %s, map1.vap_array[i].vap_index is %d, map1.vap_array[i].u.bss_info.wps.enable is %d, map1.vap_array[i].u.bss_info.wps.methods is %d and map1.vap_array[i].u.bss_info.wps.pin is %s", map1.vap_array[i].vap_name, map1.vap_array[i].vap_index, map1.vap_array[i].u.bss_info.wps.enable, map1.vap_array[i].u.bss_info.wps.methods, map1.vap_array[i].u.bss_info.wps.pin);

			    if((tmp_map.vap_array[0].u.bss_info.wps.enable == map1.vap_array[i].u.bss_info.wps.enable) && (tmp_map.vap_array[0].u.bss_info.wps.methods == map1.vap_array[i].u.bss_info.wps.methods) && (strcmp(tmp_map.vap_array[0].u.bss_info.wps.pin, map1.vap_array[i].u.bss_info.wps.pin) == 0))
                            {
                                UT_LOG("The set wps values using wifi_createVAP are reflected successfully for Radio %d in wifi_getRadioVapInfoMap", radioIndex);
                                UT_PASS("The set wps values using wifi_createVAP are reflected successfully in wifi_getRadioVapInfoMap");
                            }
                            else
                            {
                                UT_LOG("The set wps values using wifi_createVAP are NOT reflected for Radio %d in wifi_getRadioVapInfoMap", radioIndex);
                                UT_FAIL("The set wps values using wifi_createVAP are NOT reflected in wifi_getRadioVapInfoMap");
                            }
                        }
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

    UT_LOG("Exiting test_createVAP_wps_valid_tc2...");
    return;
}

/**
 * @brief Tests requirements for L2 testing wifi_createVAP() with invalid wps parameters value and verify if values remain uncorrupted using wifi_getRadioVapInfoMap()
 *
 * Test Coverage: Negative Scenario
 *
 * @retval WIFI_HAL_INVALID_ARGUMENTS   -> tested
 *
 * @Note hal api is Synchronous
 */

void test_createVAP_wps_Invalid(void)
{
    UT_LOG("Entering test_createVAP_wps_Invalid...");

    int result = 0, index = 0, i = 0, radioIndex = 0, returnStatus = 0;
    int * apIndices = NULL;
    wifi_vap_info_map_t  map, map1, tmp_map;
    unsigned int numRadios = 0;

    /* Get the number of radios applicable */
    returnStatus = test_utils_getMaxNumberOfRadio(&numRadios);

    if (returnStatus == 0)
    {
        UT_LOG("Number of Radios : %u", numRadios);

        /* Negative Test WIFI_HAL_INVALID_ARGUMENTS*/
        /* Setting invalid wps info map and expecting the API to return failure */
        UT_LOG("Test Case 18");

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
		    result = wifi_getRadioVapInfoMap(radioIndex, &map);
		    UT_ASSERT_EQUAL(result, WIFI_HAL_SUCCESS);

		    for(i=0; i<map.num_vaps; i++)
		    {
	                if ((strstr(map.vap_array[i].vap_name, "private_ssid") != NULL))
			{
			    UT_LOG("Initial values are map.vap_array[i].vap_name is %s, map.vap_array[i].vap_index is %d, map.vap_array[i].u.bss_info.wps.enable is %d, map.vap_array[i].u.bss_info.wps.methods is %d and map.vap_array[i].u.bss_info.wps.pin is %s", map.vap_array[i].vap_name, map.vap_array[i].vap_index, map.vap_array[i].u.bss_info.wps.enable, map.vap_array[i].u.bss_info.wps.methods, map.vap_array[i].u.bss_info.wps.pin);
			}
		    }

                    /* Initialize the avlues to be set */
		    tmp_map = g_org_map[radioIndex];
		    tmp_map.num_vaps = 1;
                    /* set invalid values for wps enable(set to true), methods and wps-pin */
                    tmp_map.vap_array[0].u.bss_info.wps.enable = 22;
                    tmp_map.vap_array[0].u.bss_info.wps.methods = 2000;
                    strcpy(tmp_map.vap_array[0].u.bss_info.wps.pin, "");

		    UT_LOG("Setting the wps parameter values tmp_map.vap_array[0].u.bss_info.wps.enable is %d, tmp_map.vap_array[0].u.bss_info.wps.methods is %d and tmp_map.vap_array[0].u.bss_info.wps.pin is %s", tmp_map.vap_array[0].u.bss_info.wps.enable, tmp_map.vap_array[0].u.bss_info.wps.methods, tmp_map.vap_array[0].u.bss_info.wps.pin);
		    result = wifi_createVAP(radioIndex, &tmp_map);
		    UT_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS );
                    UT_LOG("Setting invalid VAP info map for wps parameters using wifi_createVAP for radio %d returns : %d", radioIndex, result);

		    result = wifi_getRadioVapInfoMap(radioIndex, &map1);
		    UT_ASSERT_EQUAL(result, WIFI_HAL_SUCCESS);

                    for(i=0; i<map1.num_vaps; i++)
                    {
                        if ((strstr(map1.vap_array[i].vap_name, "private_ssid") != NULL))
		        {
			    UT_LOG("The values post wifi_createVAP are map1.vap_array[i].vap_name is %s, map1.vap_array[i].vap_index is %d, map1.vap_array[i].u.bss_info.wps.enable is %d, map1.vap_array[i].u.bss_info.wps.methods is %d and map1.vap_array[i].u.bss_info.wps.pin is %s", map1.vap_array[i].vap_name, map1.vap_array[i].vap_index, map1.vap_array[i].u.bss_info.wps.enable, map1.vap_array[i].u.bss_info.wps.methods, map1.vap_array[i].u.bss_info.wps.pin);

			    if((map.vap_array[i].u.bss_info.wps.enable == map1.vap_array[i].u.bss_info.wps.enable) && (map.vap_array[i].u.bss_info.wps.methods == map1.vap_array[i].u.bss_info.wps.methods) && (strcmp(map.vap_array[i].u.bss_info.wps.pin, map1.vap_array[i].u.bss_info.wps.pin) == 0))
                             {
                                 UT_LOG("The wps values remain uncorrupted for Radio %d after setting valid radioIndex and vapinfomap with invalid values to wifi_createVAP", radioIndex);
				 UT_PASS("The wps values remain uncorrupted after setting valid radioIndex and vapinfomap with invalid values to wifi_createVAP");
                             }
                             else
                             {
                                 UT_LOG("The wps values got corrupted for Radio %d after setting invailid radioIndex and valid vapinfomap to wifi_createVAP", radioIndex);
				 UT_FAIL("The wps values got corrupted after setting invalid radioIndex and valid vapinfomap to wifi_createVAP");
				 /* Set the map values back to those in vap_config file */
				 g_org_map[radioIndex].num_vaps = 1;
				 result = wifi_createVAP(radioIndex, &g_org_map[radioIndex]);
				 UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );
                                 UT_LOG("Setting config values same as vap_config file returns %d", result);
                             }
			}
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

    UT_LOG("Exiting test_createVAP_wps_Invalid...");
    return;
}

/**
 * @brief Tests requirements for L2 testing: get the channel list from wifi_getHalCapability() and fetch wifi_getRadioChannelStats() with in_pool as true 
 *
 * Test Coverage: Positive Scenario
 *
 * @retval WIFI_HAL_SUCCESS   -> tested
 *
 * @Note hal api is Synchronous
 */

void test_wifi_getRadioChannelStats_inpool_true(void)
{
    UT_LOG("Entering test_wifi_getRadioChannelStats_inpool_true...");

    int result = 0, returnStatus = 0, radioIndex = 0, column = 0, sizeOfchannelStatsArray = 0;
    int ch_numbers[25] = {0};
    unsigned int numRadios = 0;
    wifi_channelStats_t * channelStatsArrayPtr = NULL;

    /* Positive Test WIFI_HAL_SUCCESS */
    /* Passing valid radioIndex, valid channelStatsArrayPtr buffer (with valid channel number and channel in pool as 1), valid sizeOfchannelStatsArray and expecting the    API to return success */
    UT_LOG("Test Case 19");

    /* Get the number of radios applicable */
    returnStatus = test_utils_getMaxNumberOfRadio(&numRadios);

    if (returnStatus == 0)
    {
        UT_LOG("Number of Radios : %u", numRadios);
        for (radioIndex = 0 ; radioIndex < 2; radioIndex ++)
        {
            if(get_channel_list(radioIndex, &sizeOfchannelStatsArray, ch_numbers) == -1) {
                UT_LOG("Unable to retrieve channel list");
                UT_FAIL("Unable to retrieve channel list");
                return;
            }
            channelStatsArrayPtr = (wifi_channelStats_t *)malloc( sizeof(wifi_channelStats_t) * sizeOfchannelStatsArray );

            if (channelStatsArrayPtr != NULL)
            {
                memset(channelStatsArrayPtr, 0, sizeof(wifi_channelStats_t) * (sizeOfchannelStatsArray));
                for (column = 0; column < sizeOfchannelStatsArray; column++)
                {
                    channelStatsArrayPtr[column].ch_number = ch_numbers[column];
                    /* pass in_pool value as true */
                    channelStatsArrayPtr[column].ch_in_pool = 1;
                }

                result = wifi_getRadioChannelStats(radioIndex, channelStatsArrayPtr, sizeOfchannelStatsArray);
                UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );
                UT_LOG("Passing radioindex %d, valid channelStatsArrayPtr buffer (with valid channel numbers and channel in pool as 1) and sizeOfchannelStatsArray as %d returns : %d", radioIndex, sizeOfchannelStatsArray, result);

                for (column = 0; column < sizeOfchannelStatsArray; column++)
                {
                    if (result == WIFI_HAL_SUCCESS)
                    {
                        UT_LOG("Channel Stats for Radio:%d : ch_number=%d, ch_in_pool=%d, ch_noise=%d, ch_radar_noise=%d, ch_max_80211_rssi=%d, ch_non_80211_noise=%d, ch_utilization=%d, ch_utilization_total=%llu, ch_utilization_busy=%llu, ch_utilization_busy_tx=%llu, ch_utilization_busy_rx=%llu, ch_utilization_busy_self=%llu, ch_utilization_busy_ext=%llu", radioIndex, channelStatsArrayPtr[column].ch_number, channelStatsArrayPtr[column].ch_in_pool, channelStatsArrayPtr[column].ch_noise, channelStatsArrayPtr[column].ch_radar_noise, channelStatsArrayPtr[column].ch_max_80211_rssi, channelStatsArrayPtr[column].ch_non_80211_noise, channelStatsArrayPtr[column].ch_utilization, channelStatsArrayPtr[column].ch_utilization_total, channelStatsArrayPtr[column].ch_utilization_busy, channelStatsArrayPtr[column].ch_utilization_busy_tx, channelStatsArrayPtr[column].ch_utilization_busy_rx, channelStatsArrayPtr[column].ch_utilization_busy_self, channelStatsArrayPtr[column].ch_utilization_busy_ext);

                        /* Skip the DFS channels and check if Stats are properly received by checking if all Stats are NOT zero */
                       if ( (channelStatsArrayPtr[column].ch_number < 52) || (channelStatsArrayPtr[column].ch_number > 144) )
		       {
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
		       else
		       {
		           UT_LOG("Skip checking channelstats values for DFS channels");
		       }
                   }
               }
	       free(channelStatsArrayPtr);
            }
            else
            {
                UT_LOG("Malloc operation failed for Radio:%d", radioIndex);
            }
        }
    }
    else
    {
        UT_LOG("Unable to retrieve the number of radios from HalCapability");
    }

    UT_LOG("Exiting test_wifi_getRadioChannelStats_inpool_true");
    return;
}

/**
 * @brief Tests requirements for L2 testing: get the channel list from wifi_getHalCapability() and fetch wifi_getRadioChannelStats() with in_pool as false
 *
 * Test Coverage: Positive Scenario
 *
 * @retval WIFI_HAL_SUCCESS   -> tested
 *
 * @Note hal api is Synchronous
 */

void test_wifi_getRadioChannelStats_inpool_false(void)
{
    UT_LOG("Entering test_wifi_getRadioChannelStats_inpool_false...");

    int result = 0, returnStatus = 0, radioIndex = 0, column = 0, sizeOfchannelStatsArray = 0;
    int ch_numbers[25] = {0};
    unsigned int numRadios = 0;
    wifi_channelStats_t * channelStatsArrayPtr = NULL;

    /* Positive Test WIFI_HAL_SUCCESS */
    /* Passing valid radioIndex, valid channelStatsArrayPtr buffer (with valid channel number and channel in pool as 0), valid sizeOfchannelStatsArray and expecting the    API to return success */
    /* while also skipping population of stats values for that particular channel */
    UT_LOG("Test Case 20");

    /* Get the number of radios applicable */
    returnStatus = test_utils_getMaxNumberOfRadio(&numRadios);

    if (returnStatus == 0)
    {
        UT_LOG("Number of Radios : %u", numRadios);
	for (radioIndex = 0 ; radioIndex < 2; radioIndex ++)
	{
            if(get_channel_list(radioIndex, &sizeOfchannelStatsArray, ch_numbers) == -1) {
                UT_LOG("Unable to retrieve channel list");
                UT_FAIL("Unable to retrieve channel list");
                return;
            }
	    channelStatsArrayPtr = (wifi_channelStats_t *)malloc( sizeof(wifi_channelStats_t) * sizeOfchannelStatsArray );

	    if (channelStatsArrayPtr != NULL)
	    {
		memset(channelStatsArrayPtr, 0, sizeof(wifi_channelStats_t) * sizeOfchannelStatsArray );
		for (column = 0; column < sizeOfchannelStatsArray; column++)
		{
	            channelStatsArrayPtr[column].ch_number = ch_numbers[column];
		    /* pass in_pool value as false */
	            channelStatsArrayPtr[column].ch_in_pool = 0;
                }
		    result = wifi_getRadioChannelStats(radioIndex, channelStatsArrayPtr, sizeOfchannelStatsArray);
		    UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );
		    UT_LOG("Passing radioindex %d, valid channelStatsArrayPtr buffer (with valid channel numbers and channel in pool as 0) and sizeOfchannelStatsArray as %d returns : %d", radioIndex, sizeOfchannelStatsArray, result);

                for (column = 0; column < sizeOfchannelStatsArray; column++)
                {
                    if (result == WIFI_HAL_SUCCESS)
                    {
                        UT_LOG("Channel Stats for Radio %d: ch_number=%d, ch_in_pool=%d, ch_noise=%d, ch_radar_noise=%d, ch_max_80211_rssi=%d, ch_non_80211_noise=%d, ch_utilization=%d, ch_utilization_total=%llu, ch_utilization_busy=%llu, ch_utilization_busy_tx=%llu, ch_utilization_busy_rx=%llu, ch_utilization_busy_self=%llu, ch_utilization_busy_ext=%llu", radioIndex, channelStatsArrayPtr[column].ch_number, channelStatsArrayPtr[column].ch_in_pool, channelStatsArrayPtr[column].ch_noise, channelStatsArrayPtr[column].ch_radar_noise, channelStatsArrayPtr[column].ch_max_80211_rssi, channelStatsArrayPtr[column].ch_non_80211_noise, channelStatsArrayPtr[column].ch_utilization, channelStatsArrayPtr[column].ch_utilization_total, channelStatsArrayPtr[column].ch_utilization_busy, channelStatsArrayPtr[column].ch_utilization_busy_tx, channelStatsArrayPtr[column].ch_utilization_busy_rx, channelStatsArrayPtr[column].ch_utilization_busy_self, channelStatsArrayPtr[column].ch_utilization_busy_ext);

                        /* Check if the Stats values retrieved are 0 */
                        if ((channelStatsArrayPtr[column].ch_noise == 0) && (channelStatsArrayPtr[column].ch_radar_noise == 0) && (channelStatsArrayPtr[column].ch_max_80211_rssi == 0) && (channelStatsArrayPtr[column].ch_non_80211_noise == 0) && (channelStatsArrayPtr[column].ch_utilization == 0) && (channelStatsArrayPtr[column].ch_utilization_total == 0) && (channelStatsArrayPtr[column].ch_utilization_busy == 0) && (channelStatsArrayPtr[column].ch_utilization_busy_tx == 0) && (channelStatsArrayPtr[column].ch_utilization_busy_rx == 0) && (channelStatsArrayPtr[column].ch_utilization_busy_self == 0) && (channelStatsArrayPtr[column].ch_utilization_busy_ext == 0))
                        {
                            UT_PASS("Stats values retrieved are 0 as the channel is not in pool");
                            UT_LOG("Stats values retrieved are 0 as the channel is not in pool for Radio %d", radioIndex);
                        }
                        else
                        {
                            UT_FAIL("Stats values are retrieved when the channel is not in pool");
                            UT_LOG("Stats values are retrieved when the channel is not in pool for Radio %d", radioIndex);
                        }
                    }
                }
                free(channelStatsArrayPtr);
            }
            else
            {
                UT_LOG("Malloc operation failed for Radio:%d", radioIndex);
            }
        }
    }
    else
    {
        UT_LOG("Unable to retrieve the number of radios from HalCapability");
    }

    UT_LOG("Exiting test_wifi_getRadioChannelStats_inpool_false");
    return;
}

/**
 * @brief Tests requirements for L2 testing: get the channel list from wifi_getHalCapability() and fetch wifi_getRadioChannelStats() with invalid radioIndex and in_pool as true
 *
 * Test Coverage: Negative Scenario
 *
 * @retval WIFI_HAL_INVALID_ARGUMENTS   -> tested
 *
 * @Note hal api is Synchronous
 */

void test_wifi_getRadiochannelstats_invalidradio(void)
{
    UT_LOG("Entering test_getRadiochannelstats_invalidradio...");

    int result = 0, returnStatus = 0, radioIndex = 0, column = 0, sizeOfchannelStatsArray = 0;
    unsigned int numRadios = 0;
    wifi_channelStats_t * channelStatsArrayPtr = NULL;
    int ch_numbers[25] = {0};
    int radioIndex_outOfRange = 99;
    int radioIndex_negative = -1;

    /* Negative Test WIFI_HAL_INVALID_ARGUMENTS */
    /* Passing invalid radioIndex(positive and negative outofrange), valid channelStatsArrayPtr buffer (with valid channel number and channel in pool as 0), valid size of channelStatsArray and expecting the API to return failure */
    UT_LOG("Test Case 21");

    /* Get the number of radios applicable */
    returnStatus = test_utils_getMaxNumberOfRadio(&numRadios);

    if (returnStatus == 0)
    {
        UT_LOG("Number of Radios : %u", numRadios);
        for (radioIndex = 0 ; radioIndex < numRadios; radioIndex ++)
	{
            if(get_channel_list(radioIndex, &sizeOfchannelStatsArray, ch_numbers) == -1) {
                UT_LOG("Unable to retrieve channel list");
                UT_FAIL("Unable to retrieve channel list");
                return;
            }
	    channelStatsArrayPtr = (wifi_channelStats_t *)malloc( sizeof(wifi_channelStats_t) * sizeOfchannelStatsArray );
	    if (channelStatsArrayPtr != NULL)
	    {
		memset(channelStatsArrayPtr, 0, sizeof(wifi_channelStats_t) * sizeOfchannelStatsArray );
		for (column = 0; column < sizeOfchannelStatsArray; column ++)
		{
		    channelStatsArrayPtr[column].ch_number = ch_numbers[column];
		    /* pass in_pool value as true */
		    channelStatsArrayPtr[column].ch_in_pool = 1;
                }

                /* Negative Test WIFI_HAL_INVALID_ARGUMENTS */
                /* Passing invalid positive radioIndex and expecting the API to return failure */
                UT_LOG("Test Case 21.1");
	        UT_LOG("Passing invalid radioindex %d, valid channelStatsArrayPtr buffer (with valid channel numbers and channel in pool as 1) and sizeOfchannelStatsArray as %d", radioIndex_outOfRange, sizeOfchannelStatsArray);
		result = wifi_getRadioChannelStats(radioIndex_outOfRange, channelStatsArrayPtr, sizeOfchannelStatsArray);
		UT_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS );
                UT_LOG("Post setting radioIndex_outOfRange wifi_getRadioChannelStats returns : %d", result);

                /* Negative Test WIFI_HAL_INVALID_ARGUMENTS */
                /* Passing invalid negative radioIndex and expecting the API to return failure */
		UT_LOG("Test Case 21.2");
		UT_LOG("Passing invalid radioindex %d, valid channelStatsArrayPtr buffer (with valid channel numbers and channel in pool as 1) and sizeOfchannelStatsArray as %d", radioIndex_negative, sizeOfchannelStatsArray);
		result = wifi_getRadioChannelStats(radioIndex_negative, channelStatsArrayPtr, sizeOfchannelStatsArray);
		UT_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS );
		UT_LOG("Post setting radioIndex_outOfRange wifi_getRadioChannelStats returns : %d", result);
		free(channelStatsArrayPtr);
	    }
	    else
	    {
	        UT_LOG("Malloc operation failed for Radio:%d", radioIndex);
	    }
	}
    }
    else
    {
	UT_LOG("Unable to retrieve the number of radios from HalCapability");
    }

    UT_LOG("Exiting test_wifi_getRadiochannelstats_invalidradio");
    return;
}

static UT_test_suite_t *pSuite = NULL;

/**
 * @brief Init the test system
 * 
 * @return int - 0 on success, otherwise failure
 */
int test_wifi_hal_init(void)
{
    return 0;
}

/**
 * @brief Clean the test system
 * 
 * @return int - 0 on success, otherwise failure
 */
int test_wifi_hal_clean(void)
{
    return 0;
}

/**
 * @brief Register the main tests for this module
 * 
 * @return int - 0 on success, otherwise failure
 */
int test_wifi_hal_l2_register( void )
{
    /* add a suite to the registry */
    pSuite = UT_add_suite("[L2 test_wifi_hal]", &test_wifi_hal_init, &test_wifi_hal_clean);
    if (NULL == pSuite) 
    {
        return -1;
    }

    UT_add_test( pSuite, "set_valid_channelbandwidth", test_getRadioOperatingChannelBandwidth_valid);
    UT_add_test( pSuite, "set_invalid_channelbandwidth", test_getRadioOperatingChannelBandwidth_invalid_channelwidth);
    UT_add_test( pSuite, "set_invalidradioIndex_channelbandwidth", test_getRadioOperatingChannelBandwidth_invalid_radioIndex);
    UT_add_test( pSuite, "set_operationParam_NULL_channelbandwidth", test_getRadioOperatingChannelBandwidth_operationParamNULL);
    UT_add_test( pSuite, "createVAP_vapinfo_tc1", test_createVAP_vapinfo_valid_tc1);
    UT_add_test( pSuite, "createVAP_vapinfo_tc2", test_createVAP_vapinfo_valid_tc2);
    UT_add_test( pSuite, "createVAP_vapinfo_Invalid", test_createVAP_vapinfoInvalid);
    UT_add_test( pSuite, "createVAP_map_NULL",  test_createVAP_mapNULL);
    UT_add_test( pSuite, "createVAP_vapinfo_Invalidradio",  test_createVAP_invalidradio);
    UT_add_test( pSuite, "createVAP_security_tc1",  test_createVAP_security_valid_tc1);
    UT_add_test( pSuite, "createVAP_security_tc2",  test_createVAP_security_valid_tc2);
    UT_add_test( pSuite, "createVAP_security_Invalid",  test_createVAP_security_Invalid);
    UT_add_test( pSuite, "createVAP_interworking_tc1",  test_createVAP_interworking_valid_tc1);
    UT_add_test( pSuite, "createVAP_interworking_tc2",  test_createVAP_interworking_valid_tc2);
    UT_add_test( pSuite, "createVAP_interworking_Invalid",  test_createVAP_interworking_Invalid);
    UT_add_test( pSuite, "createVAP_wps_tc1",  test_createVAP_wps_valid_tc1);
    UT_add_test( pSuite, "createVAP_wps_tc2",  test_createVAP_wps_valid_tc2);
    UT_add_test( pSuite, "createVAP_wps_Invalid",  test_createVAP_wps_Invalid);
    UT_add_test( pSuite, "get_ChannelStats_inpool_true",  test_wifi_getRadioChannelStats_inpool_true);
    UT_add_test( pSuite, "get_ChannelStats_inpool_false",  test_wifi_getRadioChannelStats_inpool_false);
    UT_add_test( pSuite, "get_ChannelStats_Invalidradio",  test_wifi_getRadiochannelstats_invalidradio);

#if 0
    UT_add_test( pSuite, "set_Valid_SSID_2GHz (test@1234)", test_wifi_hal_L2_setValidSSID_2Ghz);
    UT_add_test( pSuite, "set_InValidIndex_SSID_2GHz", test_wifi_hal_L2_setInValidIndexSSID_2Ghz);
    UT_add_test( pSuite, "set_NULL_SSID_2GHz", test_wifi_hal_L2_setNULLSSID_2Ghz);
    UT_add_test( pSuite, "set_Valid_SSID_5GHz", test_wifi_hal_L2_setValidSSID_5Ghz);
    UT_add_test( pSuite, "set_InValidIndex_SSID_5GHz", test_wifi_hal_L2_setInValidIndexSSID_5Ghz);
    UT_add_test( pSuite, "set_NULL_SSID_5GHz", test_wifi_hal_L2_setNULLSSID_5Ghz);
    UT_add_test( pSuite, "set_Valid_SSID_6GHz", test_wifi_hal_L2_setValidSSID_6Ghz);
    UT_add_test( pSuite, "set_InValidIndex_SSID_6GHz", test_wifi_hal_L2_setInValidIndexSSID_6Ghz);
    UT_add_test( pSuite, "set_NULL_SSID_6GHz", test_wifi_hal_L2_setNULLSSID_6Ghz);

    UT_add_test( pSuite, "set_ap_Disable_2GHz", test_wifi_hal_L2_setApDisable_2GHz);
    UT_add_test( pSuite, "set_ap_Disable_5GHz", test_wifi_hal_L2_setApDisable_5GHz);
    UT_add_test( pSuite, "set_ap_Disable_6GHz", test_wifi_hal_L2_setApDisable_6GHz);
    UT_add_test( pSuite, "set_ap_Enable_2GHz", test_wifi_hal_L2_setApEnable_2GHz);
    UT_add_test( pSuite, "set_ap_Enable_5GHz", test_wifi_hal_L2_setApEnable_5GHz);
    UT_add_test( pSuite, "set_ap_Enable_6GHz", test_wifi_hal_L2_setApEnable_6GHz);
    UT_add_test( pSuite, "set_ap_InValidIndex_Disable",test_wifi_hal_L2_setInvalidIndexApDisable);
    UT_add_test( pSuite, "set_ap_InValidIndex_Enable",test_wifi_hal_L2_setInvalidIndexApEnable);
    UT_add_test( pSuite, "valid_channel_push_2GHz", test_wifi_L2_Validchannel_push_2GHz);
    UT_add_test( pSuite, "Invalid_channel_push_2GHz", test_wifi_L2_InValidchannel_push_2GHz);
    UT_add_test( pSuite, "Invalid_Index_channel_push_2GHz", test_wifi_L2_InValidIndex_channel_push_2GHz);
    UT_add_test( pSuite, "valid_channel_push_5GHz", test_wifi_L2_Validchannel_push_5GHz);
    UT_add_test( pSuite, "Invalid_channel_push_5GHz", test_wifi_L2_InValidchannel_push_5GHz);
    UT_add_test( pSuite, "Invalid_Index_channel_push_5GHz", test_wifi_L2_InValidIndex_channel_push_5GHz);
    UT_add_test( pSuite, "valid_channel_push_6GHz", test_wifi_L2_Validchannel_push_6GHz);
    UT_add_test( pSuite, "Invalid_channel_push_6GHz", test_wifi_L2_InValidchannel_push_6GHz);
    UT_add_test( pSuite, "Invalid_Index_channel_push_6GHz", test_wifi_L2_InValidIndex_channel_push_6GHz);
    UT_add_test( pSuite, "set_Valid_bandwidth_2GHz_40MHz",test_wifi_L2_set_valid_bandwidth_2Ghz_40MHz);
    UT_add_test( pSuite, "set_Valid_bandwidth_2GHz_20MHz",test_wifi_L2_set_valid_bandwidth_2Ghz_20MHz);
    UT_add_test( pSuite, "set_InValid_bandwidth_2GHz",test_wifi_L2_set_Invalid_bandwidth_2Ghz);
    UT_add_test( pSuite, "set_InValidIndex_bandwidth_2GHz",test_wifi_L2_set_InvalidIndex_bandwidth_2Ghz);
    UT_add_test( pSuite, "set_Valid_bandwidth_5GHz_20MHz",test_wifi_L2_set_valid_bandwidth_5Ghz_20MHz);
    UT_add_test( pSuite, "set_Valid_bandwidth_5GHz_40MHz",test_wifi_L2_set_valid_bandwidth_5Ghz_40MHz);
    UT_add_test( pSuite, "set_Valid_bandwidth_5GHz_80MHz",test_wifi_L2_set_valid_bandwidth_5Ghz_80MHz);
    UT_add_test( pSuite, "set_Valid_bandwidth_5GHz_160MHz",test_wifi_L2_set_valid_bandwidth_5Ghz_160MHz);
    UT_add_test( pSuite, "set_Valid_bandwidth_5GHz_80_80MHz",test_wifi_L2_set_valid_bandwidth_5Ghz_80_80MHz);
    UT_add_test( pSuite, "set_InValid_bandwidth_5GHz",test_wifi_L2_set_Invalid_bandwidth_5Ghz);
    UT_add_test( pSuite, "set_InValidIndex_bandwidth_5GHz",test_wifi_L2_set_InvalidIndex_bandwidth_5Ghz);
    UT_add_test( pSuite, "set_Valid_bandwidth_6GHz_20MHz",test_wifi_L2_set_valid_bandwidth_6Ghz_20MHz);
    UT_add_test( pSuite, "set_Valid_bandwidth_6GHz_20MHz",test_wifi_L2_set_valid_bandwidth_6Ghz_40MHz);
    UT_add_test( pSuite, "set_Valid_bandwidth_6GHz_160MHz",test_wifi_L2_set_valid_bandwidth_6Ghz_160MHz);
    UT_add_test( pSuite, "set_Valid_bandwidth_6GHz_80MHz",test_wifi_L2_set_valid_bandwidth_6Ghz_80MHz);
    UT_add_test( pSuite, "set_Valid_bandwidth_6GHz_80_80MHz",test_wifi_L2_set_valid_bandwidth_6Ghz_80_80MHz);
    UT_add_test( pSuite, "set_InValid_bandwidth_6GHz",test_wifi_L2_set_Invalid_bandwidth_6Ghz);
    UT_add_test( pSuite, "set_InValidIndex_bandwidth_6GHz",test_wifi_L2_set_InvalidIndex_bandwidth_6Ghz);
#endif

    return 0;
}

