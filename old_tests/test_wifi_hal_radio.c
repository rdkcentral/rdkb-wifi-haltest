#ifdef TEST

#include <stddef.h>
#include "wifi_hal_generic.h"
#include "wifi_hal_radio.h"

#include <csunit.h>

void test_wifi_hal_radio_NeedToImplement(void)
{
    TEST_FAIL"Need to Implement wifi_hal_radio");
}

void test_radio_wifi_getRadioResetCount(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_radio_wifi_factoryResetRadios(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_radio_wifi_factoryResetRadio(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_radio_wifi_getRadioEnable(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_radio_wifi_setRadioEnable(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_radio_wifi_getRadioStatus(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_radio_wifi_getRadioIfName(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_radio_wifi_getRadioChannelsInUse(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_radio_wifi_getRadioDfsEnable(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_radio_wifi_setRadioDfsEnable(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_radio_wifi_getRadioMCS(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_radio_wifi_setRadioMCS(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_radio_wifi_getRadioTransmitPower(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_radio_wifi_getRadioPercentageTransmitPower(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_radio_wifi_setRadioTransmitPower(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_radio_wifi_getRadioCarrierSenseThresholdRange(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_radio_wifi_getRadioCarrierSenseThresholdInUse(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_radio_wifi_setRadioCarrierSenseThresholdInUse(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_radio_wifi_applyRadioSettings(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_radio_wifi_setRadioCtsProtectionEnable(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_radio_wifi_setRadioObssCoexistenceEnable(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_radio_wifi_setRadioFragmentationThreshold(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_radio_wifi_setRadioSTBCEnable(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_radio_wifi_getRadioAMSDUEnable(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_radio_wifi_setRadioAMSDUEnable(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_radio_wifi_getRadioUpTime(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_radio_wifi_getRadioReverseDirectionGrantSupported(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_radio_wifi_getRadioAutoBlockAckEnable(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_radio_wifi_setRadioAutoBlockAckEnable(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_radio_wifi_getRadioIGMPSnoopingEnable(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_radio_wifi_setRadioIGMPSnoopingEnable(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_radio_wifi_setZeroDFSState(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_radio_wifi_getZeroDFSState(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_radio_wifi_setDownlinkMuType(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_radio_wifi_getDownlinkMuType(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_radio_wifi_setUplinkMuType(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_radio_wifi_getUplinkMuType(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_radio_wifi_setGuardInterval(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_radio_wifi_getGuardInterval(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_radio_wifi_setBSSColor(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_radio_wifi_getBSSColor(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_radio_wifi_getAvailableBSSColor(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_radio_wifi_getMuEdca(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_radio_wifi_setDownlinkDataAckType(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_radio_wifi_get80211axDefaultParameters(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_radio_wifi_setRadioOperatingParameters(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_radio_wifi_getRadioOperatingParameters(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_radio_wifi_getScanResults(void)
{
	TEST_FAIL"Need to implement"); 
}

void test_radio_wifi_scanResults_callback_register(void)
{
	TEST_FAIL"Need to implement"); 
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
    pSuite = CS_TEST_ADD_SUITE("[L1 test_wifi_radio]", &test_wifi_hal_radio_init, &test_wifi_hal_radio_clean);
    if (NULL == pSuite) 
    {
        return -1;
    }

    // COMMENTED for now
   /* CS_TEST_ADD( pSuite, test_wifi_hal_radio_NeedToImplement);
	CS_TEST_ADD( pSuite, test_radio_wifi_getRadioResetCount);
	CS_TEST_ADD( pSuite, test_radio_wifi_factoryResetRadios);
	CS_TEST_ADD( pSuite, test_radio_wifi_factoryResetRadio);
	CS_TEST_ADD( pSuite, test_radio_wifi_getRadioEnable);
	CS_TEST_ADD( pSuite, test_radio_wifi_setRadioEnable);
	CS_TEST_ADD( pSuite, test_radio_wifi_getRadioStatus);
	CS_TEST_ADD( pSuite, test_radio_wifi_getRadioIfName);
	CS_TEST_ADD( pSuite, test_radio_wifi_getRadioChannelsInUse);
	CS_TEST_ADD( pSuite, test_radio_wifi_getRadioDfsEnable);
	CS_TEST_ADD( pSuite, test_radio_wifi_setRadioDfsEnable);
	CS_TEST_ADD( pSuite, test_radio_wifi_getRadioMCS);
	CS_TEST_ADD( pSuite, test_radio_wifi_setRadioMCS);
	CS_TEST_ADD( pSuite, test_radio_wifi_getRadioTransmitPower);
	CS_TEST_ADD( pSuite, test_radio_wifi_getRadioPercentageTransmitPower);
	CS_TEST_ADD( pSuite, test_radio_wifi_setRadioTransmitPower);
	CS_TEST_ADD( pSuite, test_radio_wifi_getRadioCarrierSenseThresholdRange);
	CS_TEST_ADD( pSuite, test_radio_wifi_getRadioCarrierSenseThresholdInUse);
	CS_TEST_ADD( pSuite, test_radio_wifi_setRadioCarrierSenseThresholdInUse);
	CS_TEST_ADD( pSuite, test_radio_wifi_applyRadioSettings);
	CS_TEST_ADD( pSuite, test_radio_wifi_setRadioCtsProtectionEnable);
	CS_TEST_ADD( pSuite, test_radio_wifi_setRadioObssCoexistenceEnable);
	CS_TEST_ADD( pSuite, test_radio_wifi_setRadioFragmentationThreshold);
	CS_TEST_ADD( pSuite, test_radio_wifi_setRadioSTBCEnable);
	CS_TEST_ADD( pSuite, test_radio_wifi_getRadioAMSDUEnable);
	CS_TEST_ADD( pSuite, test_radio_wifi_setRadioAMSDUEnable);
	CS_TEST_ADD( pSuite, test_radio_wifi_getRadioUpTime);
	CS_TEST_ADD( pSuite, test_radio_wifi_getRadioReverseDirectionGrantSupported);
	CS_TEST_ADD( pSuite, test_radio_wifi_getRadioAutoBlockAckEnable);
	CS_TEST_ADD( pSuite, test_radio_wifi_setRadioAutoBlockAckEnable);
	CS_TEST_ADD( pSuite, test_radio_wifi_getRadioIGMPSnoopingEnable);
	CS_TEST_ADD( pSuite, test_radio_wifi_setRadioIGMPSnoopingEnable);
	CS_TEST_ADD( pSuite, test_radio_wifi_setZeroDFSState);
	CS_TEST_ADD( pSuite, test_radio_wifi_getZeroDFSState);
	CS_TEST_ADD( pSuite, test_radio_wifi_setDownlinkMuType);
	CS_TEST_ADD( pSuite, test_radio_wifi_getDownlinkMuType);
	CS_TEST_ADD( pSuite, test_radio_wifi_setUplinkMuType);
	CS_TEST_ADD( pSuite, test_radio_wifi_getUplinkMuType);
	CS_TEST_ADD( pSuite, test_radio_wifi_setGuardInterval);
	CS_TEST_ADD( pSuite, test_radio_wifi_getGuardInterval);
	CS_TEST_ADD( pSuite, test_radio_wifi_setBSSColor);
	CS_TEST_ADD( pSuite, test_radio_wifi_getBSSColor);
	CS_TEST_ADD( pSuite, test_radio_wifi_getAvailableBSSColor);
	CS_TEST_ADD( pSuite, test_radio_wifi_getMuEdca);
	CS_TEST_ADD( pSuite, test_radio_wifi_setDownlinkDataAckType);
	CS_TEST_ADD( pSuite, test_radio_wifi_get80211axDefaultParameters);
	CS_TEST_ADD( pSuite, test_radio_wifi_setRadioOperatingParameters);
	CS_TEST_ADD( pSuite, test_radio_wifi_getRadioOperatingParameters);
	CS_TEST_ADD( pSuite, test_radio_wifi_getScanResults);
    CS_TEST_ADD( pSuite, test_radio_wifi_scanResults_callback_register);
    */

    return 0;
}
#endif // TEST
