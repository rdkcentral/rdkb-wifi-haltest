#ifdef TEST

#include <stddef.h>
#include "wifi_hal_generic.h"
#include "wifi_hal_telemetry.h"
#include "wifi_hal_ap.h"
#include "wifi_hal_extender.h"

#include <CUnit.h>

void test_extender_wifi_steerTriggered_callback_register(void)
{
	CU_FAIL("Need to implement"); 
}

void test_wifi_hal_extender_NeedToImplement(void)
{
    CU_FAIL("Need to Implement wifi_hal_extender");
}

void test_extender_wifi_getRadioChannelStats(void)
{
	CU_FAIL("Need to implement"); 
}

void test_extender_wifi_getApAssociatedDeviceRxStatsResult(void)
{
	CU_FAIL("Need to implement"); 
}

void test_extender_wifi_getApAssociatedDeviceTxStatsResult(void)
{
	CU_FAIL("Need to implement"); 
}

void test_extender_wifi_getApAssociatedDeviceTidStatsResult(void)
{
	CU_FAIL("Need to implement"); 
}

void test_extender_wifi_getApAssociatedDeviceStats(void)
{
	CU_FAIL("Need to implement"); 
}

void test_extender_wifi_getSSIDRadioIndex(void)
{
	CU_FAIL("Need to implement"); 
}

void test_extender_wifi_applySSIDSettings(void)
{
	CU_FAIL("Need to implement"); 
}

void test_extender_wifi_startNeighborScan(void)
{
	CU_FAIL("Need to implement"); 
}

void test_extender_wifi_setApCsaDeauth(void)
{
	CU_FAIL("Need to implement"); 
}

void test_extender_wifi_setApScanFilter(void)
{
	CU_FAIL("Need to implement"); 
}

void test_extender_wifi_steering_setGroup(void)
{
	CU_FAIL("Need to implement"); 
}

void test_extender_wifi_steering_eventRegister(void)
{
	CU_FAIL("Need to implement"); 
}

void test_extender_wifi_steering_eventUnregister(void)
{
	CU_FAIL("Need to implement"); 
}

void test_extender_wifi_steering_clientSet(void)
{
	CU_FAIL("Need to implement"); 
}

void test_extender_wifi_steering_clientRemove(void)
{
	CU_FAIL("Need to implement"); 
}

void test_extender_wifi_steering_clientMeasure(void)
{
	CU_FAIL("Need to implement"); 
}

void test_extender_wifi_steering_clientDisconnect(void)
{
	CU_FAIL("Need to implement"); 
}

void test_extender_wifi_BTMQueryRequest_callback_register(void)
{
	CU_FAIL("Need to implement"); 
}

void test_extender_wifi_setBTMRequest(void)
{
	CU_FAIL("Need to implement"); 
}

void test_extender_wifi_RMBeaconRequestCallbackRegister(void)
{
	CU_FAIL("Need to implement"); 
}

void test_extender_wifi_RMBeaconRequestCallbackUnregister(void)
{
	CU_FAIL("Need to implement"); 
}

void test_extender_wifi_cancelRMBeaconRequest(void)
{
	CU_FAIL("Need to implement"); 
}

void test_extender_wifi_setRMBeaconRequest(void)
{
	CU_FAIL("Need to implement"); 
}

void test_extender_wifi_getRMCapabilities(void)
{
	CU_FAIL("Need to implement"); 
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
    pSuite = CU_add_suite("[L1 test_wifi_extender]", &test_wifi_hal_extender_init, &test_wifi_hal_extender_clean);
    if (NULL == pSuite) 
    {
        return -1;
    }
    //COMMENTED FOR NOW
   /* CU_ADD_TEST( pSuite, test_extender_wifi_steerTriggered_callback_register);
	CU_ADD_TEST( pSuite, test_extender_wifi_getRadioChannelStats);
	CU_ADD_TEST( pSuite, test_extender_wifi_getApAssociatedDeviceRxStatsResult);
	CU_ADD_TEST( pSuite, test_extender_wifi_getApAssociatedDeviceTxStatsResult);
	CU_ADD_TEST( pSuite, test_extender_wifi_getApAssociatedDeviceTidStatsResult);
	CU_ADD_TEST( pSuite, test_extender_wifi_getApAssociatedDeviceStats);
	CU_ADD_TEST( pSuite, test_extender_wifi_getSSIDRadioIndex);
	CU_ADD_TEST( pSuite, test_extender_wifi_applySSIDSettings);
	CU_ADD_TEST( pSuite, test_extender_wifi_startNeighborScan);
	CU_ADD_TEST( pSuite, test_extender_wifi_setApCsaDeauth);
	CU_ADD_TEST( pSuite, test_extender_wifi_setApScanFilter);
	CU_ADD_TEST( pSuite, test_extender_wifi_steering_setGroup);
	CU_ADD_TEST( pSuite, test_extender_wifi_steering_eventRegister);
	CU_ADD_TEST( pSuite, test_extender_wifi_steering_eventUnregister);
	CU_ADD_TEST( pSuite, test_extender_wifi_steering_clientSet);
	CU_ADD_TEST( pSuite, test_extender_wifi_steering_clientRemove);
	CU_ADD_TEST( pSuite, test_extender_wifi_steering_clientMeasure);
	CU_ADD_TEST( pSuite, test_extender_wifi_steering_clientDisconnect);
	CU_ADD_TEST( pSuite, test_extender_wifi_BTMQueryRequest_callback_register);
	CU_ADD_TEST( pSuite, test_extender_wifi_setBTMRequest);
	CU_ADD_TEST( pSuite, test_extender_wifi_RMBeaconRequestCallbackRegister);
	CU_ADD_TEST( pSuite, test_extender_wifi_RMBeaconRequestCallbackUnregister);
	CU_ADD_TEST( pSuite, test_extender_wifi_cancelRMBeaconRequest);
	CU_ADD_TEST( pSuite, test_extender_wifi_setRMBeaconRequest);
	CU_ADD_TEST( pSuite, test_extender_wifi_getRMCapabilities);
*/
    return 0;
}

#endif // TEST
