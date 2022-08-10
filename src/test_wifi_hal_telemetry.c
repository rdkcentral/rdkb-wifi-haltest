#ifdef TEST

#include <stddef.h>
#include "wifi_hal_generic.h"
#include "wifi_hal_telemetry.h"

#include <CUnit.h>


void test_telemetry_NeedToImplement(void)
{
    CU_FAIL("Need to Implement wifi_hal_telemetry");
}

void test_telemetry_wifi_getRadioTrafficStats2( void )
{
    CU_FAIL("Need to Implement");
}

void test_telemetry_wifi_getSSIDTrafficStats2( void )
{
    CU_FAIL("Need to Implement");
}

void test_telemetry_wifi_getNeighboringWiFiStatus( void )
{
    CU_FAIL("Need to Implement");
}

void test_telemetry_wifi_getRadioBandUtilization( void )
{
    CU_FAIL("Need to Implement");
}

void test_telemetry_wifi_getApAssociatedDeviceDiagnosticResult3( void )
{
    CU_FAIL("Need to Implement");
}

void test_telemetry_wifi_getApAssociatedClientDiagnosticResult( void )
{
    CU_FAIL("Need to Implement");
}

void test_telemetry_wifi_setClientDetailedStatisticsEnable( void )
{
    CU_FAIL("Need to Implement");
}

void test_telemetry_wifi_getRadioStatsEnable( void )
{
    CU_FAIL("Need to Implement");
}

void test_telemetry_wifi_setRadioStatsEnable( void )
{
    CU_FAIL("Need to Implement");
}

void test_telemetry_wifi_getVAPTelemetry( void )
{
    CU_FAIL("Need to Implement");
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
    pSuite = CU_add_suite("[L1 test_wifi_hal_telemetry]", &test_wifi_hal_telemetry_init, &test_wifi_hal_telemetry_clean);
    if (NULL == pSuite) 
    {
        return -1;
    }

    //COMMENTED for now
    /*
    CU_ADD_TEST( pSuite, test_telemetry_wifi_getRadioTrafficStats2);
    CU_ADD_TEST( pSuite, test_telemetry_wifi_getSSIDTrafficStats2);
    CU_ADD_TEST( pSuite, test_telemetry_wifi_getNeighboringWiFiStatus);
    CU_ADD_TEST( pSuite, test_telemetry_wifi_getRadioBandUtilization);
    CU_ADD_TEST( pSuite, test_telemetry_wifi_getApAssociatedDeviceDiagnosticResult3);
    CU_ADD_TEST( pSuite, test_telemetry_wifi_getApAssociatedClientDiagnosticResult);
    CU_ADD_TEST( pSuite, test_telemetry_wifi_setClientDetailedStatisticsEnable);
    CU_ADD_TEST( pSuite, test_telemetry_wifi_getRadioStatsEnable);
    CU_ADD_TEST( pSuite, test_telemetry_wifi_setRadioStatsEnable);
    CU_ADD_TEST( pSuite, test_telemetry_wifi_getVAPTelemetry);
*/
    return 0;
}
#endif // TEST
