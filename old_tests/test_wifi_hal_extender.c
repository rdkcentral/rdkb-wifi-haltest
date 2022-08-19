#ifdef TEST

#include <stddef.h>
#include "wifi_hal_generic.h"
#include "wifi_hal_telemetry.h"
#include "wifi_hal_ap.h"
#include "wifi_hal_extender.h"

#include <csunit.h>

void test_extender_wifi_steerTriggered_callback_register(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_wifi_hal_extender_NeedToImplement(void)
{
    TEST_FAIL"Need to Implement wifi_hal_extender");
}

void test_extender_wifi_getRadioChannelStats(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_extender_wifi_getApAssociatedDeviceRxStatsResult(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_extender_wifi_getApAssociatedDeviceTxStatsResult(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_extender_wifi_getApAssociatedDeviceTidStatsResult(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_extender_wifi_getApAssociatedDeviceStats(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_extender_wifi_getSSIDRadioIndex(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_extender_wifi_applySSIDSettings(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_extender_wifi_startNeighborScan(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_extender_wifi_setApCsaDeauth(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_extender_wifi_setApScanFilter(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_extender_wifi_steering_setGroup(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_extender_wifi_steering_eventRegister(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_extender_wifi_steering_eventUnregister(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_extender_wifi_steering_clientSet(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_extender_wifi_steering_clientRemove(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_extender_wifi_steering_clientMeasure(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_extender_wifi_steering_clientDisconnect(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_extender_wifi_BTMQueryRequest_callback_register(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_extender_wifi_setBTMRequest(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_extender_wifi_RMBeaconRequestCallbackRegister(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_extender_wifi_RMBeaconRequestCallbackUnregister(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_extender_wifi_cancelRMBeaconRequest(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_extender_wifi_setRMBeaconRequest(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_extender_wifi_getRMCapabilities(void)
{
	TEST_FAIL"Need to implement"); 
}


static CU_pSuite pSuite = NULL;

/**
 * @brief Init the test system
 * 
 * @return int - 0 on success, otherwise failure
 */
int test_wifi_hal_extender_init(void)
{
    return 0;
}

/**
 * @brief Clean the test system
 * 
 * @return int - 0 on success, otherwise failure
 */
int test_wifi_hal_extender_clean(void)
{
    return 0;
}

/**
 * @brief Register the main tests for this module
 * 
 * @return int - 0 on success, otherwise failure
 */
int test_wifi_hal_extender_register( void )
{
    /* add a suite to the registry */
    pSuite = CS_TEST_ADD_SUITE("[L1 test_wifi_extender]", &test_wifi_hal_extender_init, &test_wifi_hal_extender_clean);
    if (NULL == pSuite) 
    {
        return -1;
    }
    //COMMENTED FOR NOW
   /* CS_TEST_ADD( pSuite, test_extender_wifi_steerTriggered_callback_register);
	CS_TEST_ADD( pSuite, test_extender_wifi_getRadioChannelStats);
	CS_TEST_ADD( pSuite, test_extender_wifi_getApAssociatedDeviceRxStatsResult);
	CS_TEST_ADD( pSuite, test_extender_wifi_getApAssociatedDeviceTxStatsResult);
	CS_TEST_ADD( pSuite, test_extender_wifi_getApAssociatedDeviceTidStatsResult);
	CS_TEST_ADD( pSuite, test_extender_wifi_getApAssociatedDeviceStats);
	CS_TEST_ADD( pSuite, test_extender_wifi_getSSIDRadioIndex);
	CS_TEST_ADD( pSuite, test_extender_wifi_applySSIDSettings);
	CS_TEST_ADD( pSuite, test_extender_wifi_startNeighborScan);
	CS_TEST_ADD( pSuite, test_extender_wifi_setApCsaDeauth);
	CS_TEST_ADD( pSuite, test_extender_wifi_setApScanFilter);
	CS_TEST_ADD( pSuite, test_extender_wifi_steering_setGroup);
	CS_TEST_ADD( pSuite, test_extender_wifi_steering_eventRegister);
	CS_TEST_ADD( pSuite, test_extender_wifi_steering_eventUnregister);
	CS_TEST_ADD( pSuite, test_extender_wifi_steering_clientSet);
	CS_TEST_ADD( pSuite, test_extender_wifi_steering_clientRemove);
	CS_TEST_ADD( pSuite, test_extender_wifi_steering_clientMeasure);
	CS_TEST_ADD( pSuite, test_extender_wifi_steering_clientDisconnect);
	CS_TEST_ADD( pSuite, test_extender_wifi_BTMQueryRequest_callback_register);
	CS_TEST_ADD( pSuite, test_extender_wifi_setBTMRequest);
	CS_TEST_ADD( pSuite, test_extender_wifi_RMBeaconRequestCallbackRegister);
	CS_TEST_ADD( pSuite, test_extender_wifi_RMBeaconRequestCallbackUnregister);
	CS_TEST_ADD( pSuite, test_extender_wifi_cancelRMBeaconRequest);
	CS_TEST_ADD( pSuite, test_extender_wifi_setRMBeaconRequest);
	CS_TEST_ADD( pSuite, test_extender_wifi_getRMCapabilities);
*/
    return 0;
}

#endif // TEST
