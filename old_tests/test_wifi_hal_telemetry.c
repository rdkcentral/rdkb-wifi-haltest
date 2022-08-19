#ifdef TEST

#include <stddef.h>
#include "wifi_hal_generic.h"
#include "wifi_hal_telemetry.h"

#include <csunit.h>


void test_telemetry_NeedToImplement(void)
{
    TEST_FAIL"Need to Implement wifi_hal_telemetry");
}

void test_telemetry_wifi_getRadioTrafficStats2( void )
{
    TEST_FAIL"Need to Implement");
}

void test_telemetry_wifi_getSSIDTrafficStats2( void )
{
    TEST_FAIL"Need to Implement");
}

void test_telemetry_wifi_getNeighboringWiFiStatus( void )
{
    TEST_FAIL"Need to Implement");
}

void test_telemetry_wifi_getRadioBandUtilization( void )
{
    TEST_FAIL"Need to Implement");
}

void test_telemetry_wifi_getApAssociatedDeviceDiagnosticResult3( void )
{
    TEST_FAIL"Need to Implement");
}

void test_telemetry_wifi_getApAssociatedClientDiagnosticResult( void )
{
    TEST_FAIL"Need to Implement");
}

void test_telemetry_wifi_setClientDetailedStatisticsEnable( void )
{
    TEST_FAIL"Need to Implement");
}

void test_telemetry_wifi_getRadioStatsEnable( void )
{
    TEST_FAIL"Need to Implement");
}

void test_telemetry_wifi_setRadioStatsEnable( void )
{
    TEST_FAIL"Need to Implement");
}

void test_telemetry_wifi_getVAPTelemetry( void )
{
    TEST_FAIL"Need to Implement");
}


static CU_pSuite pSuite = NULL;

/**
 * @brief Init the test system
 * 
 * @return int - 0 on success, otherwise failure
 */
int test_wifi_hal_telemetry_init(void)
{
    return 0;
}

/**
 * @brief Clean the test system
 * 
 * @return int - 0 on success, otherwise failure
 */
int test_wifi_hal_telemetry_clean(void)
{
    return 0;
}

/**
 * @brief Register the main tests for this module
 * 
 * @return int - 0 on success, otherwise failure
 */
int test_wifi_hal_telemetry_register( void )
{
    /* add a suite to the registry */
    pSuite = CS_TEST_ADD_SUITE("[L1 test_wifi_hal_telemetry]", &test_wifi_hal_telemetry_init, &test_wifi_hal_telemetry_clean);
    if (NULL == pSuite) 
    {
        return -1;
    }

    //COMMENTED for now
    /*
    CS_TEST_ADD( pSuite, test_telemetry_wifi_getRadioTrafficStats2);
    CS_TEST_ADD( pSuite, test_telemetry_wifi_getSSIDTrafficStats2);
    CS_TEST_ADD( pSuite, test_telemetry_wifi_getNeighboringWiFiStatus);
    CS_TEST_ADD( pSuite, test_telemetry_wifi_getRadioBandUtilization);
    CS_TEST_ADD( pSuite, test_telemetry_wifi_getApAssociatedDeviceDiagnosticResult3);
    CS_TEST_ADD( pSuite, test_telemetry_wifi_getApAssociatedClientDiagnosticResult);
    CS_TEST_ADD( pSuite, test_telemetry_wifi_setClientDetailedStatisticsEnable);
    CS_TEST_ADD( pSuite, test_telemetry_wifi_getRadioStatsEnable);
    CS_TEST_ADD( pSuite, test_telemetry_wifi_setRadioStatsEnable);
    CS_TEST_ADD( pSuite, test_telemetry_wifi_getVAPTelemetry);
*/
    return 0;
}
#endif // TEST
