#ifdef TEST

#include <stddef.h>
#include "wifi_hal_generic.h"
#include "wifi_hal_client_mgt.h"

#include <CUnit.h>

void test_wifi_hal_client_mgt_NeedToImplement(void)
{
    CU_FAIL("Need to Implement wifi_hal_client_mgt");
}

void test_client_mgt_wifi_getBandSteeringEnable(void)
{
	CU_FAIL("Need to implement"); 
}

void test_client_mgt_wifi_setBandSteeringEnable(void)
{
	CU_FAIL("Need to implement"); 
}

void test_client_mgt_wifi_getBandSteeringApGroup(void)
{
	CU_FAIL("Need to implement"); 
}

void test_client_mgt_wifi_setBandSteeringApGroup(void)
{
	CU_FAIL("Need to implement"); 
}

void test_client_mgt_wifi_getBandSteeringBandUtilizationThreshold(void)
{
	CU_FAIL("Need to implement"); 
}

void test_client_mgt_wifi_setBandSteeringBandUtilizationThreshold(void)
{
	CU_FAIL("Need to implement"); 
}

void test_client_mgt_wifi_getBandSteeringRSSIThreshold(void)
{
	CU_FAIL("Need to implement"); 
}

void test_client_mgt_wifi_setBandSteeringRSSIThreshold(void)
{
	CU_FAIL("Need to implement"); 
}

void test_client_mgt_wifi_getBandSteeringPhyRateThreshold(void)
{
	CU_FAIL("Need to implement"); 
}

void test_client_mgt_wifi_setBandSteeringPhyRateThreshold(void)
{
	CU_FAIL("Need to implement"); 
}

void test_client_mgt_wifi_getBandSteeringOverloadInactiveTime(void)
{
	CU_FAIL("Need to implement"); 
}

void test_client_mgt_wifi_setBandSteeringOverloadInactiveTime(void)
{
	CU_FAIL("Need to implement"); 
}

void test_client_mgt_wifi_getBandSteeringIdleInactiveTime(void)
{
	CU_FAIL("Need to implement"); 
}

void test_client_mgt_wifi_setBandSteeringIdleInactiveTime(void)
{
	CU_FAIL("Need to implement"); 
}

void test_client_mgt_wifi_getBandSteeringLog(void)
{
	CU_FAIL("Need to implement"); 
}

void test_client_mgt_wifi_getApAssociatedDevicesHighWatermarkThreshold(void)
{
	CU_FAIL("Need to implement"); 
}

void test_client_mgt_wifi_setApAssociatedDevicesHighWatermarkThreshold(void)
{
	CU_FAIL("Need to implement"); 
}

void test_client_mgt_wifi_getApAssociatedDevicesHighWatermarkThresholdReached(void)
{
	CU_FAIL("Need to implement"); 
}

void test_client_mgt_wifi_getApAssociatedDevicesHighWatermark(void)
{
	CU_FAIL("Need to implement"); 
}

void test_client_mgt_wifi_getApAssociatedDevicesHighWatermarkDate(void)
{
	CU_FAIL("Need to implement"); 
}

void test_client_mgt_wifi_setFastBSSTransitionActivated(void)
{
	CU_FAIL("Need to implement"); 
}

void test_client_mgt_wifi_getBSSTransitionActivated(void)
{
	CU_FAIL("Need to implement"); 
}

void test_client_mgt_wifi_setEAP_Param(void)
{
	CU_FAIL("Need to implement"); 
}

void test_client_mgt_wifi_getEAP_Param(void)
{
	CU_FAIL("Need to implement"); 
}

void test_client_mgt_wifi_getFTOverDSActivated(void)
{
	CU_FAIL("Need to implement"); 
}

void test_client_mgt_wifi_setFTOverDSActivated(void)
{
	CU_FAIL("Need to implement"); 
}

void test_client_mgt_wifi_getFTMobilityDomainID(void)
{
	CU_FAIL("Need to implement"); 
}

void test_client_mgt_wifi_setFTMobilityDomainID(void)
{
	CU_FAIL("Need to implement"); 
}

void test_client_mgt_wifi_getFTResourceRequestSupported(void)
{
	CU_FAIL("Need to implement"); 
}

void test_client_mgt_wifi_setFTResourceRequestSupported(void)
{
	CU_FAIL("Need to implement"); 
}

void test_client_mgt_wifi_getFTR0KeyLifetime(void)
{
	CU_FAIL("Need to implement"); 
}

void test_client_mgt_wifi_setFTR0KeyLifetime(void)
{
	CU_FAIL("Need to implement"); 
}

void test_client_mgt_wifi_getFTR0KeyHolderID(void)
{
	CU_FAIL("Need to implement"); 
}

void test_client_mgt_wifi_setFTR0KeyHolderID(void)
{
	CU_FAIL("Need to implement"); 
}

void test_client_mgt_wifi_getFTR1KeyHolderID(void)
{
	CU_FAIL("Need to implement"); 
}

void test_client_mgt_wifi_setFTR1KeyHolderID(void)
{
	CU_FAIL("Need to implement"); 
}

void test_client_mgt_wifi_pushApFastTransitionConfig(void)
{
	CU_FAIL("Need to implement"); 
}

void test_client_mgt_wifi_setBSSTransitionActivation(void)
{
	CU_FAIL("Need to implement"); 
}

void test_client_mgt_wifi_getBSSTransitionActivation(void)
{
	CU_FAIL("Need to implement"); 
}

void test_client_mgt_wifi_setNeighborReportActivation(void)
{
	CU_FAIL("Need to implement"); 
}

void test_client_mgt_wifi_getNeighborReportActivation(void)
{
	CU_FAIL("Need to implement"); 
}

static CU_pSuite pSuite = NULL;

/**
 * @brief Init the test system
 * 
 * @return int - 0 on success, otherwise failure
 */
int test_wifi_hal_client_mgt_init(void)
{
    return 0;
}

/**
 * @brief Clean the test system
 * 
 * @return int - 0 on success, otherwise failure
 */
int test_wifi_hal_client_mgt_clean(void)
{
    return 0;
}

/**
 * @brief Register the main tests for this module
 * 
 * @return int - 0 on success, otherwise failure
 */
int test_wifi_hal_client_mgt_register( void )
{
    /* add a suite to the registry */
    pSuite = CU_add_suite("[L1 test_wifi_client_mgt]", &test_wifi_hal_client_mgt_init, &test_wifi_hal_client_mgt_clean);
    if (NULL == pSuite) 
    {
        return -1;
    }

    // COMMENTED FOR NOW
    /* CU_ADD_TEST( pSuite, test_wifi_hal_client_mgt_NeedToImplement);
	CU_ADD_TEST( pSuite, test_client_mgt_wifi_getBandSteeringEnable);
	CU_ADD_TEST( pSuite, test_client_mgt_wifi_setBandSteeringEnable);
	CU_ADD_TEST( pSuite, test_client_mgt_wifi_getBandSteeringApGroup);
	CU_ADD_TEST( pSuite, test_client_mgt_wifi_setBandSteeringApGroup);
	CU_ADD_TEST( pSuite, test_client_mgt_wifi_getBandSteeringBandUtilizationThreshold);
	CU_ADD_TEST( pSuite, test_client_mgt_wifi_setBandSteeringBandUtilizationThreshold);
	CU_ADD_TEST( pSuite, test_client_mgt_wifi_getBandSteeringRSSIThreshold);
	CU_ADD_TEST( pSuite, test_client_mgt_wifi_setBandSteeringRSSIThreshold);
	CU_ADD_TEST( pSuite, test_client_mgt_wifi_getBandSteeringPhyRateThreshold);
	CU_ADD_TEST( pSuite, test_client_mgt_wifi_setBandSteeringPhyRateThreshold);
	CU_ADD_TEST( pSuite, test_client_mgt_wifi_getBandSteeringOverloadInactiveTime);
	CU_ADD_TEST( pSuite, test_client_mgt_wifi_setBandSteeringOverloadInactiveTime);
	CU_ADD_TEST( pSuite, test_client_mgt_wifi_getBandSteeringIdleInactiveTime);
	CU_ADD_TEST( pSuite, test_client_mgt_wifi_setBandSteeringIdleInactiveTime);
	CU_ADD_TEST( pSuite, test_client_mgt_wifi_getBandSteeringLog);
	CU_ADD_TEST( pSuite, test_client_mgt_wifi_getApAssociatedDevicesHighWatermarkThreshold);
	CU_ADD_TEST( pSuite, test_client_mgt_wifi_setApAssociatedDevicesHighWatermarkThreshold);
	CU_ADD_TEST( pSuite, test_client_mgt_wifi_getApAssociatedDevicesHighWatermarkThresholdReached);
	CU_ADD_TEST( pSuite, test_client_mgt_wifi_getApAssociatedDevicesHighWatermark);
	CU_ADD_TEST( pSuite, test_client_mgt_wifi_getApAssociatedDevicesHighWatermarkDate);
	CU_ADD_TEST( pSuite, test_client_mgt_wifi_setFastBSSTransitionActivated);
	CU_ADD_TEST( pSuite, test_client_mgt_wifi_getBSSTransitionActivated);
	CU_ADD_TEST( pSuite, test_client_mgt_wifi_setEAP_Param);
	CU_ADD_TEST( pSuite, test_client_mgt_wifi_getEAP_Param);
	CU_ADD_TEST( pSuite, test_client_mgt_wifi_getFTOverDSActivated);
	CU_ADD_TEST( pSuite, test_client_mgt_wifi_setFTOverDSActivated);
	CU_ADD_TEST( pSuite, test_client_mgt_wifi_getFTMobilityDomainID);
	CU_ADD_TEST( pSuite, test_client_mgt_wifi_setFTMobilityDomainID);
	CU_ADD_TEST( pSuite, test_client_mgt_wifi_getFTResourceRequestSupported);
	CU_ADD_TEST( pSuite, test_client_mgt_wifi_setFTResourceRequestSupported);
	CU_ADD_TEST( pSuite, test_client_mgt_wifi_getFTR0KeyLifetime);
	CU_ADD_TEST( pSuite, test_client_mgt_wifi_setFTR0KeyLifetime);
	CU_ADD_TEST( pSuite, test_client_mgt_wifi_getFTR0KeyHolderID);
	CU_ADD_TEST( pSuite, test_client_mgt_wifi_setFTR0KeyHolderID);
	CU_ADD_TEST( pSuite, test_client_mgt_wifi_getFTR1KeyHolderID);
	CU_ADD_TEST( pSuite, test_client_mgt_wifi_setFTR1KeyHolderID);
	CU_ADD_TEST( pSuite, test_client_mgt_wifi_pushApFastTransitionConfig);
	CU_ADD_TEST( pSuite, test_client_mgt_wifi_setBSSTransitionActivation);
	CU_ADD_TEST( pSuite, test_client_mgt_wifi_getBSSTransitionActivation);
	CU_ADD_TEST( pSuite, test_client_mgt_wifi_setNeighborReportActivation);
	CU_ADD_TEST( pSuite, test_client_mgt_wifi_getNeighborReportActivation);
*/
    return 0;
}

#endif // TEST
