#ifdef TEST

#include <stddef.h>
#include "wifi_hal_generic.h"
#include "wifi_hal_client_mgt.h"

#include <csinit.h>

void test_wifi_hal_client_mgt_NeedToImplement(void)
{
    TEST_FAIL"Need to Implement wifi_hal_client_mgt");
}

void test_client_mgt_wifi_getBandSteeringEnable(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_client_mgt_wifi_setBandSteeringEnable(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_client_mgt_wifi_getBandSteeringApGroup(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_client_mgt_wifi_setBandSteeringApGroup(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_client_mgt_wifi_getBandSteeringBandUtilizationThreshold(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_client_mgt_wifi_setBandSteeringBandUtilizationThreshold(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_client_mgt_wifi_getBandSteeringRSSIThreshold(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_client_mgt_wifi_setBandSteeringRSSIThreshold(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_client_mgt_wifi_getBandSteeringPhyRateThreshold(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_client_mgt_wifi_setBandSteeringPhyRateThreshold(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_client_mgt_wifi_getBandSteeringOverloadInactiveTime(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_client_mgt_wifi_setBandSteeringOverloadInactiveTime(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_client_mgt_wifi_getBandSteeringIdleInactiveTime(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_client_mgt_wifi_setBandSteeringIdleInactiveTime(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_client_mgt_wifi_getBandSteeringLog(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_client_mgt_wifi_getApAssociatedDevicesHighWatermarkThreshold(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_client_mgt_wifi_setApAssociatedDevicesHighWatermarkThreshold(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_client_mgt_wifi_getApAssociatedDevicesHighWatermarkThresholdReached(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_client_mgt_wifi_getApAssociatedDevicesHighWatermark(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_client_mgt_wifi_getApAssociatedDevicesHighWatermarkDate(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_client_mgt_wifi_setFastBSSTransitionActivated(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_client_mgt_wifi_getBSSTransitionActivated(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_client_mgt_wifi_setEAP_Param(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_client_mgt_wifi_getEAP_Param(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_client_mgt_wifi_getFTOverDSActivated(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_client_mgt_wifi_setFTOverDSActivated(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_client_mgt_wifi_getFTMobilityDomainID(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_client_mgt_wifi_setFTMobilityDomainID(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_client_mgt_wifi_getFTResourceRequestSupported(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_client_mgt_wifi_setFTResourceRequestSupported(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_client_mgt_wifi_getFTR0KeyLifetime(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_client_mgt_wifi_setFTR0KeyLifetime(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_client_mgt_wifi_getFTR0KeyHolderID(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_client_mgt_wifi_setFTR0KeyHolderID(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_client_mgt_wifi_getFTR1KeyHolderID(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_client_mgt_wifi_setFTR1KeyHolderID(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_client_mgt_wifi_pushApFastTransitionConfig(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_client_mgt_wifi_setBSSTransitionActivation(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_client_mgt_wifi_getBSSTransitionActivation(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_client_mgt_wifi_setNeighborReportActivation(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_client_mgt_wifi_getNeighborReportActivation(void)
{
	TEST_FAIL"Need to implement"); 
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
    pSuite = CS_TEST_ADD_SUITE("[L1 test_wifi_client_mgt]", &test_wifi_hal_client_mgt_init, &test_wifi_hal_client_mgt_clean);
    if (NULL == pSuite) 
    {
        return -1;
    }

    // COMMENTED FOR NOW
    /* CS_TEST_ADD( pSuite, test_wifi_hal_client_mgt_NeedToImplement);
	CS_TEST_ADD( pSuite, test_client_mgt_wifi_getBandSteeringEnable);
	CS_TEST_ADD( pSuite, test_client_mgt_wifi_setBandSteeringEnable);
	CS_TEST_ADD( pSuite, test_client_mgt_wifi_getBandSteeringApGroup);
	CS_TEST_ADD( pSuite, test_client_mgt_wifi_setBandSteeringApGroup);
	CS_TEST_ADD( pSuite, test_client_mgt_wifi_getBandSteeringBandUtilizationThreshold);
	CS_TEST_ADD( pSuite, test_client_mgt_wifi_setBandSteeringBandUtilizationThreshold);
	CS_TEST_ADD( pSuite, test_client_mgt_wifi_getBandSteeringRSSIThreshold);
	CS_TEST_ADD( pSuite, test_client_mgt_wifi_setBandSteeringRSSIThreshold);
	CS_TEST_ADD( pSuite, test_client_mgt_wifi_getBandSteeringPhyRateThreshold);
	CS_TEST_ADD( pSuite, test_client_mgt_wifi_setBandSteeringPhyRateThreshold);
	CS_TEST_ADD( pSuite, test_client_mgt_wifi_getBandSteeringOverloadInactiveTime);
	CS_TEST_ADD( pSuite, test_client_mgt_wifi_setBandSteeringOverloadInactiveTime);
	CS_TEST_ADD( pSuite, test_client_mgt_wifi_getBandSteeringIdleInactiveTime);
	CS_TEST_ADD( pSuite, test_client_mgt_wifi_setBandSteeringIdleInactiveTime);
	CS_TEST_ADD( pSuite, test_client_mgt_wifi_getBandSteeringLog);
	CS_TEST_ADD( pSuite, test_client_mgt_wifi_getApAssociatedDevicesHighWatermarkThreshold);
	CS_TEST_ADD( pSuite, test_client_mgt_wifi_setApAssociatedDevicesHighWatermarkThreshold);
	CS_TEST_ADD( pSuite, test_client_mgt_wifi_getApAssociatedDevicesHighWatermarkThresholdReached);
	CS_TEST_ADD( pSuite, test_client_mgt_wifi_getApAssociatedDevicesHighWatermark);
	CS_TEST_ADD( pSuite, test_client_mgt_wifi_getApAssociatedDevicesHighWatermarkDate);
	CS_TEST_ADD( pSuite, test_client_mgt_wifi_setFastBSSTransitionActivated);
	CS_TEST_ADD( pSuite, test_client_mgt_wifi_getBSSTransitionActivated);
	CS_TEST_ADD( pSuite, test_client_mgt_wifi_setEAP_Param);
	CS_TEST_ADD( pSuite, test_client_mgt_wifi_getEAP_Param);
	CS_TEST_ADD( pSuite, test_client_mgt_wifi_getFTOverDSActivated);
	CS_TEST_ADD( pSuite, test_client_mgt_wifi_setFTOverDSActivated);
	CS_TEST_ADD( pSuite, test_client_mgt_wifi_getFTMobilityDomainID);
	CS_TEST_ADD( pSuite, test_client_mgt_wifi_setFTMobilityDomainID);
	CS_TEST_ADD( pSuite, test_client_mgt_wifi_getFTResourceRequestSupported);
	CS_TEST_ADD( pSuite, test_client_mgt_wifi_setFTResourceRequestSupported);
	CS_TEST_ADD( pSuite, test_client_mgt_wifi_getFTR0KeyLifetime);
	CS_TEST_ADD( pSuite, test_client_mgt_wifi_setFTR0KeyLifetime);
	CS_TEST_ADD( pSuite, test_client_mgt_wifi_getFTR0KeyHolderID);
	CS_TEST_ADD( pSuite, test_client_mgt_wifi_setFTR0KeyHolderID);
	CS_TEST_ADD( pSuite, test_client_mgt_wifi_getFTR1KeyHolderID);
	CS_TEST_ADD( pSuite, test_client_mgt_wifi_setFTR1KeyHolderID);
	CS_TEST_ADD( pSuite, test_client_mgt_wifi_pushApFastTransitionConfig);
	CS_TEST_ADD( pSuite, test_client_mgt_wifi_setBSSTransitionActivation);
	CS_TEST_ADD( pSuite, test_client_mgt_wifi_getBSSTransitionActivation);
	CS_TEST_ADD( pSuite, test_client_mgt_wifi_setNeighborReportActivation);
	CS_TEST_ADD( pSuite, test_client_mgt_wifi_getNeighborReportActivation);
*/
    return 0;
}

#endif // TEST
