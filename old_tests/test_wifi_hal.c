
#ifdef TEST

#include <stddef.h>
#include "test_utils.h"

#include <wifi_hal_generic.h>
#include <wifi_hal.h>
#include <wifi_hal_extender.h>
#include <csunit.h>

void test_wifi_hal_L2_setValidSSID_2Ghz(void)
{
    INT ap_index = 0; 
    INT radioIndex = 0;
    INT ap_pointing_index = 0;
    int result;

    result = test_utils_setValidSSID(radioIndex, ap_index, ap_pointing_index);
    CU_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );
    return;
}

void test_wifi_hal_L2_setInValidIndexSSID_2Ghz(void)
{
    INT ap_index = 25; /* Invalid Index */
    INT radioIndex = 0;
    INT ap_pointing_index = 0;
    int result;
    result = test_utils_setInValidIndexSSID(radioIndex, ap_index, ap_pointing_index);
    CU_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS);
    return;
}

void test_wifi_hal_L2_setNULLSSID_2Ghz(void)
{

    INT ap_index = 0;
    INT radioIndex = 0;
    INT ap_pointing_index = 0;
    int result;

    result = test_utils_setNULLSSID(radioIndex, ap_index, ap_pointing_index);
    CU_ASSERT_EQUAL( result, WIFI_HAL_ERROR);
}

void test_wifi_hal_L2_setValidSSID_5Ghz(void)
{
    INT ap_index = 1;
    INT radioIndex = 1;
    INT ap_pointing_index = 0;
    int result;

    result = test_utils_setValidSSID(radioIndex, ap_index, ap_pointing_index);
    CU_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );
    return;
}

void test_wifi_hal_L2_setInValidIndexSSID_5Ghz(void)
{
    INT ap_index = 25; /* Invalid Index */
    INT radioIndex = 1;
    INT ap_pointing_index = 0;
    int result;
    result = test_utils_setInValidIndexSSID(radioIndex, ap_index, ap_pointing_index);
    CU_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS);
    return;
}

void test_wifi_hal_L2_setNULLSSID_5Ghz(void)
{

    INT ap_index = 1;
    INT radioIndex = 1;
    INT ap_pointing_index = 0;
    int result;

    result = test_utils_setNULLSSID(radioIndex, ap_index, ap_pointing_index);
    CU_ASSERT_EQUAL( result, WIFI_HAL_ERROR);
}

void test_wifi_hal_L2_setValidSSID_6Ghz(void)
{
    INT ap_index = 16;
    INT radioIndex = 2;
    INT ap_pointing_index = 0;
    int result;

    result = test_utils_setValidSSID(radioIndex, ap_index, ap_pointing_index);
    CU_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS );
    return;
}

void test_wifi_hal_L2_setInValidIndexSSID_6Ghz(void)
{
    INT ap_index = 25; /* Invalid Index */
    INT radioIndex = 2;
    INT ap_pointing_index = 0;
    int result;
    result = test_utils_setInValidIndexSSID(radioIndex, ap_index, ap_pointing_index);
    CU_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS);
    return;
}

void test_wifi_hal_L2_setNULLSSID_6Ghz(void)
{

    INT ap_index = 16;
    INT radioIndex = 2;
    INT ap_pointing_index = 0;
    int result;

    result = test_utils_setNULLSSID(radioIndex, ap_index, ap_pointing_index);
    CU_ASSERT_EQUAL( result, WIFI_HAL_ERROR);
}

/* This will test AP Enable/Disable functionality*
* positive case * maps to RETURN_OK *
* set main interface AP to disable first and check it through get *
* now set it to enable and check it through get *
* virtaul/guest Enable/Disable set check is not added yet
*
* Negative case * RETURN_ERR *
* Try to Enable AP  with wrong AP indexes * Here 25,26,27 are taken as wrong indeces */

void test_wifi_hal_L2_setApDisable_2GHz(void)
{
    int result;
    int ap_index = 0;
    BOOL enable;

    /* Positive case */
    /* Disable the APs */
    enable = FALSE;
    result = test_utils_setApEnable (enable, ap_index);
    CU_ASSERT_EQUAL( result, RETURN_OK);
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
    CU_ASSERT_EQUAL( result, RETURN_OK);
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
    CU_ASSERT_EQUAL( result, RETURN_OK);
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
    CU_ASSERT_EQUAL( result, RETURN_OK);
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
    CU_ASSERT_EQUAL( result, RETURN_OK);
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
    CU_ASSERT_EQUAL( result, RETURN_OK);
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
    CU_ASSERT_EQUAL( result, RETURN_ERR);

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
    CU_ASSERT_EQUAL( result, RETURN_ERR);

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
    CU_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS);
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
    CU_ASSERT_EQUAL( result, WIFI_HAL_ERROR);
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
    CU_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS);
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
    CU_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS);
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
    CU_ASSERT_EQUAL( result, WIFI_HAL_ERROR);
    return;
}

void test_wifi_L2_InValidIndex_channel_push_5GHz(void)
{
    /* Negative */
    INT radioIndex = 5;
    ULONG channel = 149;
    INT result;

    result = test_utils_channelPush(radioIndex, channel);
    CU_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS);
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
    CU_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS);
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
    CU_ASSERT_EQUAL( result, WIFI_HAL_ERROR);
    return;
}

void test_wifi_L2_InValidIndex_channel_push_6GHz(void)
{
    /* Negative */
    INT radioIndex = 5;
    ULONG channel = 1;
    INT result;

    result = test_utils_channelPush(radioIndex, channel);
    CU_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS);
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
    CU_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS);
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
    CU_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS);
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
    CU_ASSERT_EQUAL( result, WIFI_HAL_ERROR);
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
    CU_ASSERT_EQUAL( result, WIFI_HAL_ERROR);
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
    CU_ASSERT_EQUAL( result, WIFI_HAL_ERROR);
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
    CU_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS);
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
    CU_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS);
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
    CU_ASSERT_EQUAL( result, WIFI_HAL_INVALID_ARGUMENTS);
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
    CU_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS);
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
    CU_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS);
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
    CU_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS);
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
    CU_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS);
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
    CU_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS);
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
    CU_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS);
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
    CU_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS);
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
    CU_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS);
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
    CU_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS);
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
    CU_ASSERT_EQUAL( result, WIFI_HAL_SUCCESS);
    return;
}


static CU_pSuite pSuite = NULL;

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
    pSuite = CS_ADD_SUITE("[L2 test_wifi_hal]", &test_wifi_hal_init, &test_wifi_hal_clean);
    if (NULL == pSuite) 
    {
        return -1;
    }
    CS_TEST_ADD( pSuite, "L2_set_Valid_SSID_2GHz (test@1234)", test_wifi_hal_L2_setValidSSID_2Ghz);
    CS_TEST_ADD( pSuite, "L2_set_InValidIndex_SSID_2GHz", test_wifi_hal_L2_setInValidIndexSSID_2Ghz);
    CS_TEST_ADD( pSuite, "L2_set_NULL_SSID_2GHz", test_wifi_hal_L2_setNULLSSID_2Ghz);
    CS_TEST_ADD( pSuite, "L2_set_Valid_SSID_5GHz", test_wifi_hal_L2_setValidSSID_5Ghz);
    CS_TEST_ADD( pSuite, "L2_set_InValidIndex_SSID_5GHz", test_wifi_hal_L2_setInValidIndexSSID_5Ghz);
    CS_TEST_ADD( pSuite, "L2_set_NULL_SSID_5GHz", test_wifi_hal_L2_setNULLSSID_5Ghz);
    CS_TEST_ADD( pSuite, "L2_set_Valid_SSID_6GHz", test_wifi_hal_L2_setValidSSID_6Ghz);
    CS_TEST_ADD( pSuite, "L2_set_InValidIndex_SSID_6GHz", test_wifi_hal_L2_setInValidIndexSSID_6Ghz);
    CS_TEST_ADD( pSuite, "L2_set_NULL_SSID_6GHz", test_wifi_hal_L2_setNULLSSID_6Ghz);
    CS_TEST_ADD( pSuite, "L2_set_ap_Disable_2GHz", test_wifi_hal_L2_setApDisable_2GHz);
    CS_TEST_ADD( pSuite, "L2_set_ap_Disable_5GHz", test_wifi_hal_L2_setApDisable_5GHz);
    CS_TEST_ADD( pSuite, "L2_set_ap_Disable_6GHz", test_wifi_hal_L2_setApDisable_6GHz);
    CS_TEST_ADD( pSuite, "L2_set_ap_Enable_2GHz", test_wifi_hal_L2_setApEnable_2GHz);
    CS_TEST_ADD( pSuite, "L2_set_ap_Enable_5GHz", test_wifi_hal_L2_setApEnable_5GHz);
    CS_TEST_ADD( pSuite, "L2_set_ap_Enable_6GHz", test_wifi_hal_L2_setApEnable_6GHz);
    CS_TEST_ADD( pSuite, "L2_set_ap_InValidIndex_Disable",test_wifi_hal_L2_setInvalidIndexApDisable);
    CS_TEST_ADD( pSuite, "L2_set_ap_InValidIndex_Enable",test_wifi_hal_L2_setInvalidIndexApEnable);
    CS_TEST_ADD( pSuite, "L2_valid_channel_push_2GHz", test_wifi_L2_Validchannel_push_2GHz);
    CS_TEST_ADD( pSuite, "L2_Invalid_channel_push_2GHz", test_wifi_L2_InValidchannel_push_2GHz);
    CS_TEST_ADD( pSuite, "L2_Invalid_Index_channel_push_2GHz", test_wifi_L2_InValidIndex_channel_push_2GHz);
    CS_TEST_ADD( pSuite, "L2_valid_channel_push_5GHz", test_wifi_L2_Validchannel_push_5GHz);
    CS_TEST_ADD( pSuite, "L2_Invalid_channel_push_5GHz", test_wifi_L2_InValidchannel_push_5GHz);
    CS_TEST_ADD( pSuite, "L2_Invalid_Index_channel_push_5GHz", test_wifi_L2_InValidIndex_channel_push_5GHz);
    CS_TEST_ADD( pSuite, "L2_valid_channel_push_6GHz", test_wifi_L2_Validchannel_push_6GHz);
    CS_TEST_ADD( pSuite, "L2_Invalid_channel_push_6GHz", test_wifi_L2_InValidchannel_push_6GHz);
    CS_TEST_ADD( pSuite, "L2_Invalid_Index_channel_push_6GHz", test_wifi_L2_InValidIndex_channel_push_6GHz);
    CS_TEST_ADD( pSuite, "L2_set_Valid_bandwidth_2GHz_40MHz",test_wifi_L2_set_valid_bandwidth_2Ghz_40MHz);
    CS_TEST_ADD( pSuite, "L2_set_Valid_bandwidth_2GHz_20MHz",test_wifi_L2_set_valid_bandwidth_2Ghz_20MHz);
    CS_TEST_ADD( pSuite, "L2_set_InValid_bandwidth_2GHz",test_wifi_L2_set_Invalid_bandwidth_2Ghz);
    CS_TEST_ADD( pSuite, "L2_set_InValidIndex_bandwidth_2GHz",test_wifi_L2_set_InvalidIndex_bandwidth_2Ghz);
    CS_TEST_ADD( pSuite, "L2_set_Valid_bandwidth_5GHz_20MHz",test_wifi_L2_set_valid_bandwidth_5Ghz_20MHz);
    CS_TEST_ADD( pSuite, "L2_set_Valid_bandwidth_5GHz_40MHz",test_wifi_L2_set_valid_bandwidth_5Ghz_40MHz);
    CS_TEST_ADD( pSuite, "L2_set_Valid_bandwidth_5GHz_80MHz",test_wifi_L2_set_valid_bandwidth_5Ghz_80MHz);
    CS_TEST_ADD( pSuite, "L2_set_Valid_bandwidth_5GHz_160MHz",test_wifi_L2_set_valid_bandwidth_5Ghz_160MHz);
    CS_TEST_ADD( pSuite, "L2_set_Valid_bandwidth_5GHz_80_80MHz",test_wifi_L2_set_valid_bandwidth_5Ghz_80_80MHz);
    CS_TEST_ADD( pSuite, "L2_set_InValid_bandwidth_5GHz",test_wifi_L2_set_Invalid_bandwidth_5Ghz);
    CS_TEST_ADD( pSuite, "L2_set_InValidIndex_bandwidth_5GHz",test_wifi_L2_set_InvalidIndex_bandwidth_5Ghz);
    CS_TEST_ADD( pSuite, "L2_set_Valid_bandwidth_6GHz_20MHz",test_wifi_L2_set_valid_bandwidth_6Ghz_20MHz);
    CS_TEST_ADD( pSuite, "L2_set_Valid_bandwidth_6GHz_20MHz",test_wifi_L2_set_valid_bandwidth_6Ghz_40MHz);
    CS_TEST_ADD( pSuite, "L2_set_Valid_bandwidth_6GHz_160MHz",test_wifi_L2_set_valid_bandwidth_6Ghz_160MHz);
    CS_TEST_ADD( pSuite, "L2_set_Valid_bandwidth_6GHz_80MHz",test_wifi_L2_set_valid_bandwidth_6Ghz_80MHz);
    CS_TEST_ADD( pSuite, "L2_set_Valid_bandwidth_6GHz_80_80MHz",test_wifi_L2_set_valid_bandwidth_6Ghz_80_80MHz);
    CS_TEST_ADD( pSuite, "L2_set_InValid_bandwidth_6GHz",test_wifi_L2_set_Invalid_bandwidth_6Ghz);
    CS_TEST_ADD( pSuite, "L2_set_InValidIndex_bandwidth_6GHz",test_wifi_L2_set_InvalidIndex_bandwidth_6Ghz);

    return 0;
}

#endif // TEST
