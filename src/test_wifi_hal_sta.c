#ifdef TEST

#include <stddef.h>
#include "wifi_hal_generic.h"
#include "wifi_hal_sta.h"

#include <CUnit.h>


void test_wifi_hal_sta_NeedToImplement(void)
{
    CU_FAIL("Need to Implement wifi_hal_sta");
}

void test_sta_wifi_staConnectionStatus_callback_register(void)
{
	CU_FAIL("Need to implement"); 
}

void test_sta_wifi_connect(void)
{
	CU_FAIL("Need to implement"); 
}

void test_sta_wifi_disconnect(void)
{
	CU_FAIL("Need to implement"); 
}

void test_sta_wifi_getStationCapability(void)
{
	CU_FAIL("Need to implement"); 
}

void test_sta_wifi_findNetworks(void)
{
	CU_FAIL("Need to implement"); 
}

void test_sta_wifi_getStationStats(void)
{
	CU_FAIL("Need to implement"); 
}

static CU_pSuite pSuite = NULL;

/**
 * @brief Init the test system
 * 
 * @return int - 0 on success, otherwise failure
 */
int test_wifi_hal_sta_init(void)
{
    return 0;
}

/**
 * @brief Clean the test system
 * 
 * @return int - 0 on success, otherwise failure
 */
int test_wifi_hal_sta_clean(void)
{
    return 0;
}

/**
 * @brief Register the main tests for this module
 * 
 * @return int - 0 on success, otherwise failure
 */
int test_wifi_hal_sta_register( void )
{
    /* add a suite to the registry */
    pSuite = CU_add_suite("[L1 test_wifi_sta]", &test_wifi_hal_sta_init, &test_wifi_hal_sta_clean);
    if (NULL == pSuite) 
    {
        return -1;
    }
// COMMENTED FOR NOW
/*
    CU_ADD_TEST( pSuite, test_wifi_hal_sta_NeedToImplement);
	CU_ADD_TEST( pSuite, test_sta_wifi_connect);
	CU_ADD_TEST( pSuite, test_sta_wifi_disconnect);
	CU_ADD_TEST( pSuite, test_sta_wifi_getStationCapability);
	CU_ADD_TEST( pSuite, test_sta_wifi_findNetworks);
	CU_ADD_TEST( pSuite, test_sta_wifi_getStationStats);
    CU_ADD_TEST( pSuite, test_sta_wifi_staConnectionStatus_callback_register);
*/

    return 0;
}

#endif // TEST
