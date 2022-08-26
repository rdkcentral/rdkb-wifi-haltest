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
#include "wifi_hal_client_mgt.h"

#include <ut.h>

void test_client_mgt_wifi_getBandSteeringEnable(void)
{
	UT_FAIL("Need to implement"); 
}

void test_client_mgt_wifi_setBandSteeringEnable(void)
{
	UT_FAIL("Need to implement"); 
}

void test_client_mgt_wifi_getBandSteeringApGroup(void)
{
	UT_FAIL("Need to implement"); 
}

void test_client_mgt_wifi_setBandSteeringApGroup(void)
{
	UT_FAIL("Need to implement"); 
}

void test_client_mgt_wifi_getBandSteeringBandUtilizationThreshold(void)
{
	UT_FAIL("Need to implement"); 
}

void test_client_mgt_wifi_setBandSteeringBandUtilizationThreshold(void)
{
	UT_FAIL("Need to implement"); 
}

void test_client_mgt_wifi_getBandSteeringRSSIThreshold(void)
{
	UT_FAIL("Need to implement"); 
}

void test_client_mgt_wifi_setBandSteeringRSSIThreshold(void)
{
	UT_FAIL("Need to implement"); 
}

void test_client_mgt_wifi_getBandSteeringPhyRateThreshold(void)
{
	UT_FAIL("Need to implement"); 
}

void test_client_mgt_wifi_setBandSteeringPhyRateThreshold(void)
{
	UT_FAIL("Need to implement"); 
}

void test_client_mgt_wifi_getBandSteeringOverloadInactiveTime(void)
{
	UT_FAIL("Need to implement"); 
}

void test_client_mgt_wifi_setBandSteeringOverloadInactiveTime(void)
{
	UT_FAIL("Need to implement"); 
}

void test_client_mgt_wifi_getBandSteeringIdleInactiveTime(void)
{
	UT_FAIL("Need to implement"); 
}

void test_client_mgt_wifi_setBandSteeringIdleInactiveTime(void)
{
	UT_FAIL("Need to implement"); 
}

void test_client_mgt_wifi_getBandSteeringLog(void)
{
	UT_FAIL("Need to implement"); 
}

void test_client_mgt_wifi_getApAssociatedDevicesHighWatermarkThreshold(void)
{
	UT_FAIL("Need to implement"); 
}

void test_client_mgt_wifi_setApAssociatedDevicesHighWatermarkThreshold(void)
{
	UT_FAIL("Need to implement"); 
}

void test_client_mgt_wifi_getApAssociatedDevicesHighWatermarkThresholdReached(void)
{
	UT_FAIL("Need to implement"); 
}

void test_client_mgt_wifi_getApAssociatedDevicesHighWatermark(void)
{
	UT_FAIL("Need to implement"); 
}

void test_client_mgt_wifi_getApAssociatedDevicesHighWatermarkDate(void)
{
	UT_FAIL("Need to implement"); 
}

void test_client_mgt_wifi_setFastBSSTransitionActivated(void)
{
	UT_FAIL("Need to implement"); 
}

void test_client_mgt_wifi_getBSSTransitionActivated(void)
{
	UT_FAIL("Need to implement"); 
}

void test_client_mgt_wifi_setEAP_Param(void)
{
	UT_FAIL("Need to implement"); 
}

void test_client_mgt_wifi_getEAP_Param(void)
{
	UT_FAIL("Need to implement"); 
}

void test_client_mgt_wifi_getFTOverDSActivated(void)
{
	UT_FAIL("Need to implement"); 
}

void test_client_mgt_wifi_setFTOverDSActivated(void)
{
	UT_FAIL("Need to implement"); 
}

void test_client_mgt_wifi_getFTMobilityDomainID(void)
{
	UT_FAIL("Need to implement"); 
}

void test_client_mgt_wifi_setFTMobilityDomainID(void)
{
	UT_FAIL("Need to implement"); 
}

void test_client_mgt_wifi_getFTResourceRequestSupported(void)
{
	UT_FAIL("Need to implement"); 
}

void test_client_mgt_wifi_setFTResourceRequestSupported(void)
{
	UT_FAIL("Need to implement"); 
}

void test_client_mgt_wifi_getFTR0KeyLifetime(void)
{
	UT_FAIL("Need to implement"); 
}

void test_client_mgt_wifi_setFTR0KeyLifetime(void)
{
	UT_FAIL("Need to implement"); 
}

void test_client_mgt_wifi_getFTR0KeyHolderID(void)
{
	UT_FAIL("Need to implement"); 
}

void test_client_mgt_wifi_setFTR0KeyHolderID(void)
{
	UT_FAIL("Need to implement"); 
}

void test_client_mgt_wifi_getFTR1KeyHolderID(void)
{
	UT_FAIL("Need to implement"); 
}

void test_client_mgt_wifi_setFTR1KeyHolderID(void)
{
	UT_FAIL("Need to implement"); 
}

void test_client_mgt_wifi_pushApFastTransitionConfig(void)
{
	UT_FAIL("Need to implement"); 
}

void test_client_mgt_wifi_setBSSTransitionActivation(void)
{
	UT_FAIL("Need to implement"); 
}

void test_client_mgt_wifi_getBSSTransitionActivation(void)
{
	UT_FAIL("Need to implement"); 
}

void test_client_mgt_wifi_setNeighborReportActivation(void)
{
	UT_FAIL("Need to implement"); 
}

void test_client_mgt_wifi_getNeighborReportActivation(void)
{
	UT_FAIL("Need to implement"); 
}

static UT_test_suite_t * pSuite = NULL;

/**
 * @brief Register the main tests for this module
 * 
 * @return int - 0 on success, otherwise failure
 */
INT test_wifi_client_mgr_register( void )
{
    /* add a suite to the registry */
    pSuite = UT_add_suite("[L1 wifi-client_mgt]", NULL, NULL);
    if (NULL == pSuite) 
    {
        return -1;
    }

		UT_add_test( pSuite, "wifi_getBandSteeringEnable",  test_client_mgt_wifi_getBandSteeringEnable);
		UT_add_test( pSuite, "wifi_setBandSteeringEnable",  test_client_mgt_wifi_setBandSteeringEnable);
		UT_add_test( pSuite, "wifi_getBandSteeringApGroup",  test_client_mgt_wifi_getBandSteeringApGroup);
		UT_add_test( pSuite, "wifi_setBandSteeringApGroup",  test_client_mgt_wifi_setBandSteeringApGroup);
		UT_add_test( pSuite, "wifi_getBandSteeringBandUtilizationThreshold",  test_client_mgt_wifi_getBandSteeringBandUtilizationThreshold);
		UT_add_test( pSuite, "wifi_setBandSteeringBandUtilizationThreshold",  test_client_mgt_wifi_setBandSteeringBandUtilizationThreshold);
		UT_add_test( pSuite, "wifi_getBandSteeringRSSIThreshold",  test_client_mgt_wifi_getBandSteeringRSSIThreshold);
		UT_add_test( pSuite, "wifi_setBandSteeringRSSIThreshold",  test_client_mgt_wifi_setBandSteeringRSSIThreshold);
		UT_add_test( pSuite, "wifi_getBandSteeringPhyRateThreshold",  test_client_mgt_wifi_getBandSteeringPhyRateThreshold);
		UT_add_test( pSuite, "wifi_setBandSteeringPhyRateThreshold",  test_client_mgt_wifi_setBandSteeringPhyRateThreshold);
		UT_add_test( pSuite, "wifi_getBandSteeringOverloadInactiveTime",  test_client_mgt_wifi_getBandSteeringOverloadInactiveTime);
		UT_add_test( pSuite, "wifi_setBandSteeringOverloadInactiveTime",  test_client_mgt_wifi_setBandSteeringOverloadInactiveTime);
		UT_add_test( pSuite, "wifi_getBandSteeringIdleInactiveTime",  test_client_mgt_wifi_getBandSteeringIdleInactiveTime);
		UT_add_test( pSuite, "wifi_setBandSteeringIdleInactiveTime",  test_client_mgt_wifi_setBandSteeringIdleInactiveTime);
		UT_add_test( pSuite, "wifi_getBandSteeringLog",  test_client_mgt_wifi_getBandSteeringLog);
		UT_add_test( pSuite, "wifi_getApAssociatedDevicesHighWatermarkThreshold",  test_client_mgt_wifi_getApAssociatedDevicesHighWatermarkThreshold);
		UT_add_test( pSuite, "wifi_setApAssociatedDevicesHighWatermarkThreshold",  test_client_mgt_wifi_setApAssociatedDevicesHighWatermarkThreshold);
		UT_add_test( pSuite, "wifi_getApAssociatedDevicesHighWatermarkThresholdReached",  test_client_mgt_wifi_getApAssociatedDevicesHighWatermarkThresholdReached);
		UT_add_test( pSuite, "wifi_getApAssociatedDevicesHighWatermark",  test_client_mgt_wifi_getApAssociatedDevicesHighWatermark);
		UT_add_test( pSuite, "wifi_getApAssociatedDevicesHighWatermarkDate",  test_client_mgt_wifi_getApAssociatedDevicesHighWatermarkDate);
		UT_add_test( pSuite, "wifi_setFastBSSTransitionActivated",  test_client_mgt_wifi_setFastBSSTransitionActivated);
		UT_add_test( pSuite, "wifi_getBSSTransitionActivated",  test_client_mgt_wifi_getBSSTransitionActivated);
		UT_add_test( pSuite, "wifi_setEAP_Param",  test_client_mgt_wifi_setEAP_Param);
		UT_add_test( pSuite, "wifi_getEAP_Param",  test_client_mgt_wifi_getEAP_Param);
		UT_add_test( pSuite, "wifi_getFTOverDSActivated",  test_client_mgt_wifi_getFTOverDSActivated);
		UT_add_test( pSuite, "wifi_setFTOverDSActivated",  test_client_mgt_wifi_setFTOverDSActivated);
		UT_add_test( pSuite, "wifi_getFTMobilityDomainID",  test_client_mgt_wifi_getFTMobilityDomainID);
		UT_add_test( pSuite, "wifi_setFTMobilityDomainID",  test_client_mgt_wifi_setFTMobilityDomainID);
		UT_add_test( pSuite, "wifi_getFTResourceRequestSupported",  test_client_mgt_wifi_getFTResourceRequestSupported);
		UT_add_test( pSuite, "wifi_setFTResourceRequestSupported",  test_client_mgt_wifi_setFTResourceRequestSupported);
		UT_add_test( pSuite, "wifi_getFTR0KeyLifetime",  test_client_mgt_wifi_getFTR0KeyLifetime);
		UT_add_test( pSuite, "wifi_setFTR0KeyLifetime",  test_client_mgt_wifi_setFTR0KeyLifetime);
		UT_add_test( pSuite, "wifi_getFTR0KeyHolderID",  test_client_mgt_wifi_getFTR0KeyHolderID);
		UT_add_test( pSuite, "wifi_setFTR0KeyHolderID",  test_client_mgt_wifi_setFTR0KeyHolderID);
		UT_add_test( pSuite, "wifi_getFTR1KeyHolderID",  test_client_mgt_wifi_getFTR1KeyHolderID);
		UT_add_test( pSuite, "wifi_setFTR1KeyHolderID",  test_client_mgt_wifi_setFTR1KeyHolderID);
		UT_add_test( pSuite, "wifi_pushApFastTransitionConfig",  test_client_mgt_wifi_pushApFastTransitionConfig);
		UT_add_test( pSuite, "wifi_setBSSTransitionActivation",  test_client_mgt_wifi_setBSSTransitionActivation);
		UT_add_test( pSuite, "wifi_getBSSTransitionActivation",  test_client_mgt_wifi_getBSSTransitionActivation);
		UT_add_test( pSuite, "wifi_setNeighborReportActivation",  test_client_mgt_wifi_setNeighborReportActivation);
		UT_add_test( pSuite, "wifi_getNeighborReportActivation",  test_client_mgt_wifi_getNeighborReportActivation);


    return 0;
}