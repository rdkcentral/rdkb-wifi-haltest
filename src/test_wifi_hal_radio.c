#ifdef TEST

#include <stddef.h>
#include "wifi_hal_generic.h"
#include "wifi_hal_radio.h"

#include <CUnit.h>

void test_wifi_hal_radio_NeedToImplement(void)
{
    CU_FAIL("Need to Implement wifi_hal_radio");
}

void test_radio_wifi_getRadioResetCount(void)
{
	CU_FAIL("Need to implement"); 
}

void test_radio_wifi_factoryResetRadios(void)
{
	CU_FAIL("Need to implement"); 
}

void test_radio_wifi_factoryResetRadio(void)
{
	CU_FAIL("Need to implement"); 
}

void test_radio_wifi_getRadioEnable(void)
{
	CU_FAIL("Need to implement"); 
}

void test_radio_wifi_setRadioEnable(void)
{
	CU_FAIL("Need to implement"); 
}

void test_radio_wifi_getRadioStatus(void)
{
	CU_FAIL("Need to implement"); 
}

void test_radio_wifi_getRadioIfName(void)
{
	CU_FAIL("Need to implement"); 
}

void test_radio_wifi_getRadioChannelsInUse(void)
{
	CU_FAIL("Need to implement"); 
}

void test_radio_wifi_getRadioDfsEnable(void)
{
	CU_FAIL("Need to implement"); 
}

void test_radio_wifi_setRadioDfsEnable(void)
{
	CU_FAIL("Need to implement"); 
}

void test_radio_wifi_getRadioMCS(void)
{
	CU_FAIL("Need to implement"); 
}

void test_radio_wifi_setRadioMCS(void)
{
	CU_FAIL("Need to implement"); 
}

void test_radio_wifi_getRadioTransmitPower(void)
{
	CU_FAIL("Need to implement"); 
}

void test_radio_wifi_getRadioPercentageTransmitPower(void)
{
	CU_FAIL("Need to implement"); 
}

void test_radio_wifi_setRadioTransmitPower(void)
{
	CU_FAIL("Need to implement"); 
}

void test_radio_wifi_getRadioCarrierSenseThresholdRange(void)
{
	CU_FAIL("Need to implement"); 
}

void test_radio_wifi_getRadioCarrierSenseThresholdInUse(void)
{
	CU_FAIL("Need to implement"); 
}

void test_radio_wifi_setRadioCarrierSenseThresholdInUse(void)
{
	CU_FAIL("Need to implement"); 
}

void test_radio_wifi_applyRadioSettings(void)
{
	CU_FAIL("Need to implement"); 
}

void test_radio_wifi_setRadioCtsProtectionEnable(void)
{
	CU_FAIL("Need to implement"); 
}

void test_radio_wifi_setRadioObssCoexistenceEnable(void)
{
	CU_FAIL("Need to implement"); 
}

void test_radio_wifi_setRadioFragmentationThreshold(void)
{
	CU_FAIL("Need to implement"); 
}

void test_radio_wifi_setRadioSTBCEnable(void)
{
	CU_FAIL("Need to implement"); 
}

void test_radio_wifi_getRadioAMSDUEnable(void)
{
	CU_FAIL("Need to implement"); 
}

void test_radio_wifi_setRadioAMSDUEnable(void)
{
	CU_FAIL("Need to implement"); 
}

void test_radio_wifi_getRadioUpTime(void)
{
	CU_FAIL("Need to implement"); 
}

void test_radio_wifi_getRadioReverseDirectionGrantSupported(void)
{
	CU_FAIL("Need to implement"); 
}

void test_radio_wifi_getRadioAutoBlockAckEnable(void)
{
	CU_FAIL("Need to implement"); 
}

void test_radio_wifi_setRadioAutoBlockAckEnable(void)
{
	CU_FAIL("Need to implement"); 
}

void test_radio_wifi_getRadioIGMPSnoopingEnable(void)
{
	CU_FAIL("Need to implement"); 
}

void test_radio_wifi_setRadioIGMPSnoopingEnable(void)
{
	CU_FAIL("Need to implement"); 
}

void test_radio_wifi_setZeroDFSState(void)
{
	CU_FAIL("Need to implement"); 
}

void test_radio_wifi_getZeroDFSState(void)
{
	CU_FAIL("Need to implement"); 
}

void test_radio_wifi_setDownlinkMuType(void)
{
	CU_FAIL("Need to implement"); 
}

void test_radio_wifi_getDownlinkMuType(void)
{
	CU_FAIL("Need to implement"); 
}

void test_radio_wifi_setUplinkMuType(void)
{
	CU_FAIL("Need to implement"); 
}

void test_radio_wifi_getUplinkMuType(void)
{
	CU_FAIL("Need to implement"); 
}

void test_radio_wifi_setGuardInterval(void)
{
	CU_FAIL("Need to implement"); 
}

void test_radio_wifi_getGuardInterval(void)
{
	CU_FAIL("Need to implement"); 
}

void test_radio_wifi_setBSSColor(void)
{
	CU_FAIL("Need to implement"); 
}

void test_radio_wifi_getBSSColor(void)
{
	CU_FAIL("Need to implement"); 
}

void test_radio_wifi_getAvailableBSSColor(void)
{
	CU_FAIL("Need to implement"); 
}

void test_radio_wifi_getMuEdca(void)
{
	CU_FAIL("Need to implement"); 
}

void test_radio_wifi_setDownlinkDataAckType(void)
{
	CU_FAIL("Need to implement"); 
}

void test_radio_wifi_get80211axDefaultParameters(void)
{
	CU_FAIL("Need to implement"); 
}

void test_radio_wifi_setRadioOperatingParameters(void)
{
	CU_FAIL("Need to implement"); 
}

void test_radio_wifi_getRadioOperatingParameters(void)
{
	CU_FAIL("Need to implement"); 
}

void test_radio_wifi_getScanResults(void)
{
	CU_FAIL("Need to implement"); 
}

void test_radio_wifi_scanResults_callback_register(void)
{
	CU_FAIL("Need to implement"); 
}

static CU_pSuite pSuite = NULL;

/**
 * @brief Init the test system
 * 
 * @return int - 0 on success, otherwise failure
 */
int test_wifi_hal_radio_init(void)
{
    return 0;
}

/**
 * @brief Clean the test system
 * 
 * @return int - 0 on success, otherwise failure
 */
int test_wifi_hal_radio_clean(void)
{
    return 0;
}

/**
 * @brief Register the main tests for this module
 * 
 * @return int - 0 on success, otherwise failure
 */
int test_wifi_hal_radio_register( void )
{
    /* add a suite to the registry */
    pSuite = CU_add_suite("[L1 test_wifi_radio]", &test_wifi_hal_radio_init, &test_wifi_hal_radio_clean);
    if (NULL == pSuite) 
    {
        return -1;
    }

    // COMMENTED for now
   /* CU_ADD_TEST( pSuite, test_wifi_hal_radio_NeedToImplement);
	CU_ADD_TEST( pSuite, test_radio_wifi_getRadioResetCount);
	CU_ADD_TEST( pSuite, test_radio_wifi_factoryResetRadios);
	CU_ADD_TEST( pSuite, test_radio_wifi_factoryResetRadio);
	CU_ADD_TEST( pSuite, test_radio_wifi_getRadioEnable);
	CU_ADD_TEST( pSuite, test_radio_wifi_setRadioEnable);
	CU_ADD_TEST( pSuite, test_radio_wifi_getRadioStatus);
	CU_ADD_TEST( pSuite, test_radio_wifi_getRadioIfName);
	CU_ADD_TEST( pSuite, test_radio_wifi_getRadioChannelsInUse);
	CU_ADD_TEST( pSuite, test_radio_wifi_getRadioDfsEnable);
	CU_ADD_TEST( pSuite, test_radio_wifi_setRadioDfsEnable);
	CU_ADD_TEST( pSuite, test_radio_wifi_getRadioMCS);
	CU_ADD_TEST( pSuite, test_radio_wifi_setRadioMCS);
	CU_ADD_TEST( pSuite, test_radio_wifi_getRadioTransmitPower);
	CU_ADD_TEST( pSuite, test_radio_wifi_getRadioPercentageTransmitPower);
	CU_ADD_TEST( pSuite, test_radio_wifi_setRadioTransmitPower);
	CU_ADD_TEST( pSuite, test_radio_wifi_getRadioCarrierSenseThresholdRange);
	CU_ADD_TEST( pSuite, test_radio_wifi_getRadioCarrierSenseThresholdInUse);
	CU_ADD_TEST( pSuite, test_radio_wifi_setRadioCarrierSenseThresholdInUse);
	CU_ADD_TEST( pSuite, test_radio_wifi_applyRadioSettings);
	CU_ADD_TEST( pSuite, test_radio_wifi_setRadioCtsProtectionEnable);
	CU_ADD_TEST( pSuite, test_radio_wifi_setRadioObssCoexistenceEnable);
	CU_ADD_TEST( pSuite, test_radio_wifi_setRadioFragmentationThreshold);
	CU_ADD_TEST( pSuite, test_radio_wifi_setRadioSTBCEnable);
	CU_ADD_TEST( pSuite, test_radio_wifi_getRadioAMSDUEnable);
	CU_ADD_TEST( pSuite, test_radio_wifi_setRadioAMSDUEnable);
	CU_ADD_TEST( pSuite, test_radio_wifi_getRadioUpTime);
	CU_ADD_TEST( pSuite, test_radio_wifi_getRadioReverseDirectionGrantSupported);
	CU_ADD_TEST( pSuite, test_radio_wifi_getRadioAutoBlockAckEnable);
	CU_ADD_TEST( pSuite, test_radio_wifi_setRadioAutoBlockAckEnable);
	CU_ADD_TEST( pSuite, test_radio_wifi_getRadioIGMPSnoopingEnable);
	CU_ADD_TEST( pSuite, test_radio_wifi_setRadioIGMPSnoopingEnable);
	CU_ADD_TEST( pSuite, test_radio_wifi_setZeroDFSState);
	CU_ADD_TEST( pSuite, test_radio_wifi_getZeroDFSState);
	CU_ADD_TEST( pSuite, test_radio_wifi_setDownlinkMuType);
	CU_ADD_TEST( pSuite, test_radio_wifi_getDownlinkMuType);
	CU_ADD_TEST( pSuite, test_radio_wifi_setUplinkMuType);
	CU_ADD_TEST( pSuite, test_radio_wifi_getUplinkMuType);
	CU_ADD_TEST( pSuite, test_radio_wifi_setGuardInterval);
	CU_ADD_TEST( pSuite, test_radio_wifi_getGuardInterval);
	CU_ADD_TEST( pSuite, test_radio_wifi_setBSSColor);
	CU_ADD_TEST( pSuite, test_radio_wifi_getBSSColor);
	CU_ADD_TEST( pSuite, test_radio_wifi_getAvailableBSSColor);
	CU_ADD_TEST( pSuite, test_radio_wifi_getMuEdca);
	CU_ADD_TEST( pSuite, test_radio_wifi_setDownlinkDataAckType);
	CU_ADD_TEST( pSuite, test_radio_wifi_get80211axDefaultParameters);
	CU_ADD_TEST( pSuite, test_radio_wifi_setRadioOperatingParameters);
	CU_ADD_TEST( pSuite, test_radio_wifi_getRadioOperatingParameters);
	CU_ADD_TEST( pSuite, test_radio_wifi_getScanResults);
    CU_ADD_TEST( pSuite, test_radio_wifi_scanResults_callback_register);
    */

    return 0;
}
#endif // TEST
