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
* @file test_wifi_hal_radio.c
* @page WIFIHAL_Radio WiFi HAL Level 1 Tests - Radio
*
* ## Module's Role
* This module includes Level 1 functional tests (success and failure scenarios).
* This is to ensure that the APIs: wifi_getRadioTransmitPower(), wifi_getRadioOperatingChannelBandwidth() and wifi_setRadioOperatingParameters()  meets the operational requirements of the RADIO HAL across all vendors.
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

#include <ut.h>
#include <ut_log.h>

#include "config_parser.h"
#include "test_utils.h"
#include "api_translator.h"

/**
* @brief This function checks that wifi_getRadioTransmitPower() operates correctly
*
* Calls the header function wifi_getRadioTransmitPower() with correct and incorrect params
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
* |01|invoke wifi_getRadioTransmitPower() with valid opRadioTxPower buffer for 2.4G radio | radioIndex=0, opRadioTxPower=Valid Buffer of type unsigned long | WIFI_HAL_SUCCESS| Should Pass |
* |02|invoke wifi_getRadioTransmitPower() with valid opRadioTxPower buffer for 5G radio | radioIndex=1, opRadioTxPower=Valid Buffer of type unsigned long | WIFI_HAL_SUCCESS| Should Pass |
* |03|invoke wifi_getRadioTransmitPower() with NULL opRadioTxPower buffer for 2.4G radio | radioIndex=0, opRadioTxPower=NULL | WIFI_HAL_INVALID_ARGUMENTS | Should Fail |
* |04|invoke wifi_getRadioTransmitPower() with NULL opRadioTxPower buffer for 5G radio | radioIndex=1, opRadioTxPower=NULL | WIFI_HAL_INVALID_ARGUMENTS | Should Fail |
* |05|invoke wifi_getRadioTransmitPower() with valid opRadioTxPower buffer for out of range radioIndex | radioIndex=99, opRadioTxPower=Valid Buffer of type unsigned long | WIFI_HAL_INVALID_ARGUMENTS | Should Fail |
* |06|invoke wifi_getRadioTransmitPower() with valid opRadioTxPower buffer for negative radioIndex | radioIndex=-1, opRadioTxPower=Valid Buffer of type unsigned long | WIFI_HAL_INVALID_ARGUMENTS | Should Fail |
* |05|invoke wifi_getRadioTransmitPower() with NULL opRadioTxPower buffer for out of range radioIndex | radioIndex=99, opRadioTxPower=NULL | WIFI_HAL_INVALID_ARGUMENTS | Should Fail |
*/
void test_radio_wifi_getRadioTransmitPower(void)
{
   UT_LOG("Entering getRadioTransmitPower... ");

   int result = 0;
   ulong transmit_power = 0;
   int radioIndex = 0;
   unsigned int numRadios = 0;
   int returnStatus = 0;
   int radioIndex_outOfRange = 99;
   int radioIndex_negative = -1;

    /* Get the number of radios applicable */
    returnStatus = test_utils_getMaxNumberOfRadio(&numRadios);

    if (returnStatus == 0)
    {
        UT_LOG("Number of Radios : %u", numRadios);

        /* Postive Test WIFI_HAL_SUCCESS */
        /* Passing valid radio index, valid transmit power and expecting the API to return success */
        UT_LOG("Test Case 1");

        for (radioIndex = 0; radioIndex < numRadios; radioIndex++)
        {
            result = wifi_getRadioTransmitPower(radioIndex, &transmit_power);
            UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS);
            UT_LOG("Passing valid transmit power for radio index %d returns : %d", radioIndex, result);

            if (transmit_power == 0)
            {
               UT_LOG("Transmit power is %ld for radio %d which is not a valid transmit power", transmit_power, radioIndex);
               UT_FAIL("Transmit power validation fail");
            }
            else
            {
               UT_LOG("Transmit power is %ld for radio %d which is a valid transmit power", transmit_power, radioIndex);
               UT_PASS("Transmit power validation success");
            }

        }

        /* Negative Test WIFI_HAL_INVALID_ARGUMENTS */
        /* Passing NULL to transmit power and expecting the API to return failure */
        UT_LOG("Test Case 2");

        for (radioIndex = 0; radioIndex < numRadios; radioIndex++)
        {
            result = wifi_getRadioTransmitPower(radioIndex, NULL);
            UT_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS);
            UT_LOG("Passing NULL as transmit power for radio %d returns : %d", radioIndex, result);
        }

        /* Negative Test WIFI_HAL_INVALID_ARGUMENTS */
        /* Passing invalid positive radio index, valid transmit power and expecting the API to return failure */
        UT_LOG("Test Case 3");

        result = wifi_getRadioTransmitPower(radioIndex_outOfRange, &transmit_power);
        UT_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS);
        UT_LOG("Passing an out of range positive radio index %d and valid transmit power returns : %d", radioIndex_outOfRange, result);

        /* Negative Test WIFI_HAL_INVALID_ARGUMENTS */
        /* Passing a negative radio index, valid transmit power and expecting the API to return failure */
        UT_LOG("Test Case 4");

        result = wifi_getRadioTransmitPower(radioIndex_negative, &transmit_power);
        UT_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS);
        UT_LOG("Passing an out of range negative radio index %d and valid transmit power returns : %d", radioIndex_negative, result);

        /* Negative Test WIFI_HAL_INVALID_ARGUMENTS */
        /* Passing an invalid radio index, NULL transmit power buffer and expecting the API to return failure */
        UT_LOG("Test Case 5");

        result = wifi_getRadioTransmitPower(radioIndex_outOfRange, NULL);
        UT_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS);
        UT_LOG("Passing an invalid radio index %d and NULL transmit power buffer returns : %d", radioIndex_outOfRange, result);

    }
    else
    {
        UT_LOG("Unable to retrieve the number of radios from HalCapability");
    }

    UT_LOG("Exiting getRadioTransmitPower... ");
    return;

}

/**
* @brief This function checks that wifi_getRadioOperatingChannelBandwidth() operates correctly
*
* Calls the header function wifi_getRadioOperatingChannelBandwidth() with correct and incorrect params
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
* |01|invoke wifi_getRadioOperatingChannelBandwidth() with valid opRadioOpChnBw buffer for 2.4G radio and check if the channel bandwidth is valid | radioIndex=0, opRadioOpChnBw=Valid Buffer of unsigned long type | WIFI_HAL_SUCCESS| Should Pass |
* |02|invoke wifi_getRadioOperatingChannelBandwidth() with valid opRadioOpChnBw buffer for 5G radio and check if the channel bandwidth is valid | radioIndex=1, opRadioOpChnBw=Valid Buffer of unsigned long type | WIFI_HAL_SUCCESS| Should Pass |
* |03|invoke wifi_getRadioOperatingChannelBandwidth() with NULL opRadioOpChnBw buffer for 2.4G radio | radioIndex=0, opRadioOpChnBw=NULL | WIFI_HAL_INVALID_ARGUMENTS | Should Fail |
* |04|invoke wifi_getRadioOperatingChannelBandwidth() with NULL opRadioOpChnBw buffer for 5G radio | radioIndex=1, opRadioOpChnBw=NULL | WIFI_HAL_INVALID_ARGUMENTS | Should Fail |
* |05|invoke wifi_getRadioOperatingChannelBandwidth() with valid opRadioOpChnBw buffer for out of range radioIndex | radioIndex=99, opRadioOpChnBw=Valid Buffer of unsigned long type | WIFI_HAL_INVALID_ARGUMENTS | Should Fail |
* |06|invoke wifi_getRadioOperatingChannelBandwidth() with valid opRadioOpChnBw buffer for negative radioIndex | radioIndex=-1, opRadioOpChnBw=Valid Buffer of unsigned long type | WIFI_HAL_INVALID_ARGUMENTS | Should Fail |
* |07|invoke wifi_getRadioOperatingChannelBandwidth() with NULL opRadioOpChnBw buffer for out of range radioIndex | radioIndex=99, opRadioOpChnBw=NULL | WIFI_HAL_INVALID_ARGUMENTS | Should Fail |
*/
void test_radio_wifi_getRadioOperatingChannelBandwidth(void)
{

    UT_LOG("Entering getRadioOperatingChannelBandwidth...");

    int result = 0;
    char channel_bandwidth[10] = {'\0'};
    int radioIndex = 0;
    unsigned int numRadios = 0;
    int returnStatus = 0;
    int radioIndex_outOfRange = 99;
    int radioIndex_negative = -1;

    /* Get the number of radios applicable */
    returnStatus = test_utils_getMaxNumberOfRadio(&numRadios);

    if (returnStatus == 0)
    {
        UT_LOG("Number of Radios : %u", numRadios);

        /* Postive Test WIFI_HAL_SUCCESS */
        /* Passing valid channel bandwidth buffer and expecting the API to return success */
        UT_LOG("Test Case 1");

        for (radioIndex = 0; radioIndex < numRadios; radioIndex++)
        {
            result = wifi_getRadioOperatingChannelBandwidth(radioIndex, channel_bandwidth);
            UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS);

            UT_LOG("Passing valid buffer as channel bandwidth for radio %d returns : %d", radioIndex, result);

            if (NULL != strstr(channel_bandwidth, "MHz"))
            {
                UT_LOG("Channel Bandwidth of radio %d is %s which is a valid bandwidth", radioIndex, channel_bandwidth); 
                UT_PASS("Channel Bandwidth validation success");				
            }
            else
            {
                UT_LOG("Channel Bandwidth of radio %d is %s which is NOT a valid bandwidth", radioIndex, channel_bandwidth); 
                UT_FAIL("Channel Bandwidth validation fail");
            }
        }

        /* Negative Test WIFI_HAL_INVALID_ARGUMENTS */
        /* Passing NULL Buffer as input to channel bandwidth and expecting the API to return failure */
        UT_LOG("Test Case 2");

        for (radioIndex = 0; radioIndex < numRadios; radioIndex++)
        {
            result = wifi_getRadioOperatingChannelBandwidth(radioIndex, NULL);
            UT_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS);

            UT_LOG("Passing NULL buffer as channel bandwidth for radio %d returns : %d", radioIndex, result);
        }

        /* Negative Test WIFI_HAL_INVALID_ARGUMENTS */
        /* Passing a positive out of range radio index, valid channel bandwidth buffer and expecting the API to return failure */
        UT_LOG("Test Case 3");

        result = wifi_getRadioOperatingChannelBandwidth(radioIndex_outOfRange, channel_bandwidth);
        UT_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS);

        UT_LOG("Passing an out of range positive radio index %d and valid buffer as channel bandwidth returns : %d", radioIndex_outOfRange, result);

        /* Negative Test WIFI_HAL_INVALID_ARGUMENTS */
        /* Passing a negative radio index, valid channel bandwidth buffer and expecting the API to return failure */
        UT_LOG("Test Case 4");

        result = wifi_getRadioOperatingChannelBandwidth(radioIndex_negative, channel_bandwidth);
        UT_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS);

        UT_LOG("Passing negative radio index %d and valid buffer as channel bandwidth returns : %d", radioIndex_negative, result);

        /* Negative Test WIFI_HAL_INVALID_ARGUMENTS */
        /* Passing an invalid radio index, channel bandwidth as NULL buffer and expecting the API to return failure */
        UT_LOG("Test Case 5");

        result = wifi_getRadioOperatingChannelBandwidth(radioIndex_outOfRange, NULL);
        UT_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS);

        UT_LOG("Passing invalid radio index %d and NULL buffer as channel bandwidth returns : %d", radioIndex_outOfRange, result);
    }
    else
    {
        UT_LOG("Unable to retrieve the number of radios from HalCapability");
    }

    UT_LOG("Exiting getRadioOperatingChannelBandwidth...");
    return;

}


/**
* @brief This function checks that wifi_setRadioOperatingParameters() operates correctly
*
* Calls the header function wifi_setRadioOperatingParameters() with correct and incorrect params
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
* |01|invoke wifi_setRadioOperatingParameters() with valid operationParam structure configuration for 2.4G radio | radioIndex=0, operationParam=Valid configuration buffer of type wifi_radio_operationParam_t | WIFI_HAL_SUCCESS| Should Pass |
* |02|invoke wifi_setRadioOperatingParameters() with valid operationParam structure configuration for 5G radio | radioIndex=1, operationParam=Valid configuration buffer of type wifi_radio_operationParam_t | WIFI_HAL_SUCCESS| Should Pass |
* |03|invoke wifi_setRadioOperatingParameters() with NULL operationParam structure for 2.4G radio | radioIndex=0, operationParam=NULL | WIFI_HAL_INVALID_ARGUMENTS | Should Fail |
* |04|invoke wifi_setRadioOperatingParameters() with NULL operationParam structure for 5G radio | radioIndex=1, operationParam=NULL | WIFI_HAL_INVALID_ARGUMENTS | Should Fail |
*/
void test_radio_wifi_setRadioOperatingParameters(void)
{
    UT_LOG("Entering setRadioOperatingParameters...");

    int result = 0;
    unsigned int numRadios = 0;
    int returnStatus = 0;
    int radioIndex = 0;
    wifi_radio_operationParam_t operationParam;

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
            /* Get the radio configuration */
            returnStatus = get_radio_config(radioIndex, &operationParam); 
            if (returnStatus == 0)
            {
                UT_LOG("get_radio_config for radio %d returns : %d", radioIndex, returnStatus);

                result = wifi_setRadioOperatingParameters(radioIndex, &operationParam);
                UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );

                UT_LOG("Setting valid operating parameters for radio %d returns : %d", radioIndex, result);
            }
            else
            {
                UT_LOG("Unable to parse the radio config file");
            }	
        }			

        /* Negative Test WIFI_HAL_INVALID_ARGUMENTS */
        /* Passing NULL Buffer as input to operating parameter structure and expecting the API to return failure */
        UT_LOG("Test Case 2");

        for (radioIndex = 0; radioIndex < numRadios; radioIndex++)
        {
            result = wifi_setRadioOperatingParameters(radioIndex, NULL);
            UT_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS );

            UT_LOG("Setting NULL buffer as operating parameter structure for radio %d returns : %d", radioIndex, result);
        }
    }
    else
    {
        UT_LOG("Unable to retrieve the number of radios from HalCapability");
    }

    UT_LOG("Exiting setRadioOperatingParameters...");
    return;

}

/**
* @brief This function checks that wifi_setRadioOperatingParameters() operates correctly
*
* Calls the header function wifi_setRadioOperatingParameters() with correct params
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
* |01|invoke wifi_setRadioOperatingParameters() with valid channel values set to operationParam structure for 2.4G radio | radioIndex=0, operationParam.channel={3, 6, 9, 11} | WIFI_HAL_SUCCESS| Should Pass |
* |02|invoke wifi_setRadioOperatingParameters() with valid channel values set to operationParam structure for 5G radio | radioIndex=1, operationParam.channel={44, 116, 144, 157} | WIFI_HAL_SUCCESS| Should Pass |
*/
void test_setRadioOperatingParameters_valid_channel(void)
{
    UT_LOG("Entering test_setRadioOperatingParameters_valid_channel...");

    int result = 0, returnStatus = 0, radioIndex = 0, column = 0, row = 0;
    unsigned int numRadios = 0;
    unsigned int ch_numbers[4][2] = {{3, 44}, {6, 116}, {9, 144}, {11, 157}};
    wifi_radio_operationParam_t operationParam, tmp_radio;

    /* Get the number of radios applicable */
    returnStatus = test_utils_getMaxNumberOfRadio(&numRadios);

    if (returnStatus == 0)
    {
        UT_LOG("Number of Radios : %u", numRadios);

        /* Postive Test WIFI_HAL_SUCCESS */
        /* Setting valid channel number and expecting the API to return success */
        UT_LOG("Test Case 1");

        for (radioIndex = 0; radioIndex < numRadios; radioIndex++)
        {
            /* Get the radio configuration */
            returnStatus = get_radio_config(radioIndex, &operationParam);
            if (returnStatus == 0)
            {
                for(row = 0; row < 4; row++)
                {
                    column = radioIndex;
                    tmp_radio = operationParam;
                    tmp_radio.channel = ch_numbers[row][column];
                    UT_LOG("Setting valid channel number %d", tmp_radio.channel);
                    result = wifi_setRadioOperatingParameters(radioIndex, &tmp_radio);
                    UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );
                    UT_LOG("Setting valid channel numbers for radio %d returns : %d", radioIndex, result);
                }

                /* Setting the config back to default values */
                result = wifi_setRadioOperatingParameters(radioIndex, &operationParam);
                UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );
                UT_LOG("wifi_setRadioOperatingParameters after setting back to default values for radio %d returns : %d", radioIndex, result);
            }
            else
            {
                UT_LOG("Unable to parse the radio config file");
            }
        }
    }
    else
    {
        UT_LOG("Unable to retrieve the number of radios from HalCapability");
    }

    UT_LOG("Exiting test_setRadioOperatingParameters_valid_channel...");
    return;
}

static int convert_channelwidth_to_string(wifi_channelBandwidth_t width, char *chWidth)
{
    if( width == WIFI_CHANNELBANDWIDTH_20MHZ )
    {
        strcpy(chWidth, "20");
    }
    else if( width == WIFI_CHANNELBANDWIDTH_40MHZ )
    {
        strcpy(chWidth, "40");
    }
    else if( width == WIFI_CHANNELBANDWIDTH_80MHZ )
    {
        strcpy(chWidth, "80");
    }
    else
    {
        return -1;
    }
    return 0;
}

/**
* @brief This function checks that wifi_setRadioOperatingParameters() operates correctly
*
* Calls the header function wifi_setRadioOperatingParameters() with correct params
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
* |01|invoke wifi_setRadioOperatingParameters() with valid channelwidth set to operationParam structure for 2.4G radio | radioIndex=0, operationParam.channelWidth=WIFI_CHANNELBANDWIDTH_20MHZ | WIFI_HAL_SUCCESS| Should Pass |
* |02|invoke wifi_setRadioOperatingParameters() with valid channelwidth set to operationParam structure for 5G radio | radioIndex=1, operationParam.channelWidth=WIFI_CHANNELBANDWIDTH_40MHZ | WIFI_HAL_SUCCESS| Should Pass |
*/
void test_setRadioOperatingParameters_valid_channelwidth(void)
{
    UT_LOG("Entering test_setRadioOperatingParameters_valid_channelwidth...");

    int result = 0;
    int returnStatus = 0;
    int radioIndex = 0;
    int i = 0;
    unsigned int numRadios = 0;
    char chWidth[10] = {'\0'};
    wifi_radio_operationParam_t operationParam, tmp_radio;
    wifi_channelBandwidth_t width[3] = {WIFI_CHANNELBANDWIDTH_20MHZ, WIFI_CHANNELBANDWIDTH_40MHZ, WIFI_CHANNELBANDWIDTH_80MHZ};

    /* Get the number of radios applicable */
    returnStatus = test_utils_getMaxNumberOfRadio(&numRadios);

    if (returnStatus == 0)
    {
        UT_LOG("Number of Radios : %u", numRadios);

        /* Positive Test WIFI_HAL_SUCCESS */
        /* Setting valid channel width and expecting the API to return success */
        UT_LOG("Test Case 1");

        for (radioIndex = 0; radioIndex < numRadios; radioIndex++)
        {
            /* Get the radio configuration */
            returnStatus = get_radio_config(radioIndex, &operationParam);
            if (returnStatus == 0)
            {
                for(i = 0; i < 3; i++)
                {
                    /* Skip setting WIFI_CHANNELBANDWIDTH_80MHZ for radio 0 since its not a supported value */
                    if( (radioIndex == 0) && (i == 2))
                        break;
                    /* Positive Test WIFI_HAL_SUCCESS */
                    /* Setting valid channel bandwidth 40MHz and expecting the API to return success */
                    tmp_radio = operationParam;
                    tmp_radio.channelWidth = width[i];

		    convert_channelwidth_to_string(tmp_radio.channelWidth, chWidth);
                    UT_LOG("Setting channelWidth to %sMHz using setRadioOperatingParameters", chWidth);

                    result = wifi_setRadioOperatingParameters(radioIndex, &tmp_radio);
                    UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );
                    UT_LOG("wifi_setRadioOperatingParameters for radio %d returns : %d", radioIndex, result);
		}

                /* Setting the config back to default values */
                result = wifi_setRadioOperatingParameters(radioIndex, &operationParam);
                UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );
                UT_LOG("wifi_setRadioOperatingParameters after setting back to default values for radio %d returns : %d", radioIndex, result);
            }
            else
            {
                UT_LOG("Unable to parse the radio config file");
            }
        }
    }
    else
    {
        UT_LOG("Unable to retrieve the number of radios from HalCapability");
    }

    UT_LOG("Exiting test_setRadioOperatingParameters_valid_channelwidth...");
    return;
}

/**
* @brief This function checks that wifi_setRadioOperatingParameters() operates correctly
*
* Calls the header function wifi_setRadioOperatingParameters() with incorrect params
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
* |01|invoke wifi_setRadioOperatingParameters() with invalid operationParam structure consisting of invalid channelwidth which is a positive out of range value for 2.4G radio | radioIndex=0, operationParam.channelWidth=400 | WIFI_HAL_INVALID_ARGUMENTS| Should Fail |
* |02|invoke wifi_setRadioOperatingParameters() with invalid operationParam structure consisting of invalid channelwidth which is a positive out of range value for 5G radio | radioIndex=1, operationParam.channelWidth=400 | WIFI_HAL_INVALID_ARGUMENTS| Should Fail |
* |03|invoke wifi_setRadioOperatingParameters() with invalid operationParam structure consisting of invalid channelwidth which is a negative value for 2.4G radio | radioIndex=0, operationParam.channelWidth=-20 | WIFI_HAL_INVALID_ARGUMENTS| Should Fail |
* |04|invoke wifi_setRadioOperatingParameters() with invalid operationParam structure consisting of invalid channelwidth which is a negative value for 5G radio | radioIndex=1, operationParam.channelWidth=-20 | WIFI_HAL_INVALID_ARGUMENTS| Should Fail |
*/
void test_setRadioOperatingParameters_invalid_channelwidth(void)
{
    UT_LOG("Entering test_setRadioOperatingParameters_invalid_channelwidth...");

    int result = 0;
    int returnStatus = 0;
    int radioIndex = 0;
    unsigned int numRadios = 0;
    wifi_radio_operationParam_t operationParam, tmp_radio;
    wifi_channelBandwidth_t positive_width = 400;
    wifi_channelBandwidth_t negative_width = -20;

    /* Get the number of radios applicable */
    returnStatus = test_utils_getMaxNumberOfRadio(&numRadios);

    if (returnStatus == 0)
    {
        UT_LOG("Number of Radios : %u", numRadios);

        /* Negative Test WIFI_HAL_INVALID_ARGUMENTS */
        /* Setting invalid channel width and expecting the API to return failure */
        UT_LOG("Test Case 1");

        for (radioIndex = 0; radioIndex < numRadios; radioIndex++)
        {
            /* Get the radio configuration */
            returnStatus = get_radio_config(radioIndex, &operationParam);
            if (returnStatus == 0)
            {
	        /* Negative Test WIFI_HAL_INVALID_ARGUMENTS */
	        /* Setting invalid positive channel bandwidth 400 and expecting the API to return failure */
	        UT_LOG("Test case 1");
                tmp_radio = operationParam;
                tmp_radio.channelWidth = positive_width;
                UT_LOG("Setting channelWidth to %d using setRadioOperatingParameters", tmp_radio.channelWidth);

		result = wifi_setRadioOperatingParameters(radioIndex, &tmp_radio);
		UT_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS );
		UT_LOG("wifi_setRadioOperatingParameters for radio %d returns : %d", radioIndex, result);

                if(result == WIFI_HAL_SUCCESS)
                {
                    /* Setting the config back to default values */
                    result = wifi_setRadioOperatingParameters(radioIndex, &operationParam);
                    UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );
                    UT_LOG("wifi_setRadioOperatingParameters after setting back to default values for radio %d returns : %d", radioIndex, result);
                }

                /* Negative Test WIFI_HAL_INVALID_ARGUMENTS */
                /* Setting invalid negative channel bandwidth -20 and expecting the API to return failure */
                UT_LOG("Test case 2");
                tmp_radio = operationParam;
                tmp_radio.channelWidth = negative_width;
                UT_LOG("Setting channelWidth to %d using setRadioOperatingParameters", tmp_radio.channelWidth);

                result = wifi_setRadioOperatingParameters(radioIndex, &tmp_radio);
                UT_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS );
                UT_LOG("wifi_setRadioOperatingParameters for radio %d returns : %d", radioIndex, result);

                if(result == WIFI_HAL_SUCCESS)
                {
                    /* Setting the config back to default values  */
                    result = wifi_setRadioOperatingParameters(radioIndex, &operationParam);
                    UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );
                    UT_LOG("wifi_setRadioOperatingParameters after setting back to default values for radio %d returns : %d", radioIndex, result);
                }		
            }
            else
            {
                UT_LOG("Unable to parse the radio config file");
            }
        }
    }
    else
    {
        UT_LOG("Unable to retrieve the number of radios from HalCapability");
    }

    UT_LOG("Exiting test_setRadioOperatingParameters_invalid_channelwidth...");
    return;
}

/**
* @brief This function checks that wifi_setRadioOperatingParameters() operates correctly
*
* Calls the header function wifi_setRadioOperatingParameters() with incorrect params
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
* |01|invoke wifi_setRadioOperatingParameters() with invalid operationParam structure consisting of invalid channel which is a positive out of range value for 2.4G radio | radioIndex=0, operationParam.channelWidth=250 | WIFI_HAL_INVALID_ARGUMENTS| Should Fail |
* |02|invoke wifi_setRadioOperatingParameters() with invalid operationParam structure consisting of invalid channel which is a positive out of range value for 5G radio | radioIndex=1, operationParam.channelWidth=250 | WIFI_HAL_INVALID_ARGUMENTS| Should Fail |
* |03|invoke wifi_setRadioOperatingParameters() with invalid operationParam structure consisting of invalid channel which is a negative value for 2.4G radio | radioIndex=0, operationParam.channelWidth=-36 | WIFI_HAL_INVALID_ARGUMENTS| Should Fail |
* |04|invoke wifi_setRadioOperatingParameters() with invalid operationParam structure consisting of invalid channel which is a negative value for 5G radio | radioIndex=1, operationParam.channelWidth=-36 | WIFI_HAL_INVALID_ARGUMENTS| Should Fail |
*/
void test_setRadioOperatingParameters_invalid_channel(void)
{
    UT_LOG("Entering test_setRadioOperatingParameters_invalid_channel...");

    int result = 0;
    int returnStatus = 0;
    int radioIndex = 0;
    unsigned int numRadios = 0;
    wifi_radio_operationParam_t operationParam, tmp_radio;
    unsigned int positive_channel = 250;
    unsigned int negative_channel = -36;

    /* Get the number of radios applicable */
    returnStatus = test_utils_getMaxNumberOfRadio(&numRadios);

    if (returnStatus == 0)
    {
        UT_LOG("Number of Radios : %u", numRadios);

        /* Negative Test WIFI_HAL_INVALID_ARGUMENTS */
        /* Setting invalid channel and expecting the API to return failure */
        UT_LOG("Test Case 1");

        for (radioIndex = 0; radioIndex < numRadios; radioIndex++)
        {
            /* Get the radio configuration */
            returnStatus = get_radio_config(radioIndex, &operationParam);
            if (returnStatus == 0)
            {
	        /* Negative Test WIFI_HAL_INVALID_ARGUMENTS */
	        /* Setting invalid positive channel 250 and expecting the API to return failure */
	        UT_LOG("Test case 1");
                tmp_radio = operationParam;
                tmp_radio.channel = positive_channel;
                UT_LOG("Setting channel to %d using setRadioOperatingParameters", tmp_radio.channel);

                result = wifi_setRadioOperatingParameters(radioIndex, &tmp_radio);
                UT_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS );
                UT_LOG("wifi_setRadioOperatingParameters for radio %d returns : %d", radioIndex, result);

                if(result == WIFI_HAL_SUCCESS)
                {
                    /* Setting the config back to default values */
                    result = wifi_setRadioOperatingParameters(radioIndex, &operationParam);
                    UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );
                    UT_LOG("wifi_setRadioOperatingParameters after setting back to default values for radio %d returns : %d", radioIndex, result);
                }

                UT_LOG("Test case 2");
                tmp_radio = operationParam;
                tmp_radio.channel = negative_channel;
                UT_LOG("Setting channel to %d using setRadioOperatingParameters", tmp_radio.channel);

                result = wifi_setRadioOperatingParameters(radioIndex, &tmp_radio);
                UT_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS );
                UT_LOG("wifi_setRadioOperatingParameters for radio %d returns : %d", radioIndex, result);

		if(result == WIFI_HAL_SUCCESS)
		{
		    /* Setting the config back to default values */
		    result = wifi_setRadioOperatingParameters(radioIndex, &operationParam);
                    UT_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );
                    UT_LOG("wifi_setRadioOperatingParameters after setting back to default values for radio %d returns : %d", radioIndex, result);
		}
            }
            else
            {
                UT_LOG("Unable to parse the radio config file");
            }
        }
    }
    else
    {
        UT_LOG("Unable to retrieve the number of radios from HalCapability");
    }

    UT_LOG("Exiting test_setRadioOperatingParameters_invalid_channel...");
    return;
}

#if 0 /* #FIXME: Requires review, this is not defined in the wifi_hal, but maybe in later revisions */
static INT test_wifi_scanResults_callback(INT radioIndex)
{
   (void)radioIndex;
   /* Should not be triggered during the test*/
   UT_FAIL("This function isn't expected to be triggered");
   return (INT)0;
}

void test_radio_wifi_scanResults_callback_register(void)
{

   /* Positive */
   wifi_scanResults_callback_register(&test_wifi_scanResults_callback);
   wifi_scanResults_callback_register(NULL);

   /* Negative - N/A*/
}
#endif

static UT_test_suite_t *pSuite = NULL;

/**
 * @brief Register the main tests for this module
 * 
 * @return int - 0 on success, otherwise failure
 */
INT test_wifi_radio_register( void )
{
   /* add a suite to the registry */
   pSuite = UT_add_suite("[L1 wifi-radio]", NULL, NULL);
   if (NULL == pSuite) 
   {
      return -1;
   }

   UT_add_test( pSuite, "wifi_getRadioTransmitPower", test_radio_wifi_getRadioTransmitPower);
   UT_add_test( pSuite, "wifi_getRadioOperatingChannelBandwidth)", test_radio_wifi_getRadioOperatingChannelBandwidth);
   /* #FIXME: Added this function as it was present in wifi_hal_radio.h but not in test_wifi_hal_radio.c */
   UT_add_test( pSuite, "wifi_setRadioOperatingParameters", test_radio_wifi_setRadioOperatingParameters);
   /* FIXME: Commented UT for wifi_scanResults_callback_register as the function is not present in wifi_hal.c in any of the platforms*/
   //UT_add_test( pSuite, "wifi_scanResults_callback_register)", test_radio_wifi_scanResults_callback_register);
   UT_add_test( pSuite, "setRadioParameters_valid_channel", test_setRadioOperatingParameters_valid_channel);
   UT_add_test( pSuite, "setRadioParameters_valid_chwidth", test_setRadioOperatingParameters_valid_channelwidth);
   UT_add_test( pSuite, "setRadioParameters_invalidchwidth", test_setRadioOperatingParameters_invalid_channelwidth);
   UT_add_test( pSuite, "setRadioParameters_invalidchannel", test_setRadioOperatingParameters_invalid_channel);

  return 0;
}
