/**
 * @brief Register test functionality
 * 
 */

/* L1 Testing Functions */
extern int test_wifi_hal_ap_register( void );
extern int test_wifi_hal_client_mgt_register( void );
extern int test_wifi_hal_extender_register( void );
extern int test_wifi_hal_radio_register( void );
extern int test_wifi_hal_sta_register( void );
extern int test_wifi_hal_telemetry_register( void );
extern int test_wifi_hal_ap_register( void );
extern int test_generic_register( void );

/* L2 Testing Functions */
extern int test_wifi_hal_l2_register( void );

int register_hal_tests( void )
{
    int registerFailed=0;

    registerFailed |= test_generic_register();
    registerFailed |= test_wifi_hal_client_mgt_register();
    registerFailed |= test_wifi_hal_extender_register();
    registerFailed |= test_wifi_hal_radio_register();
    registerFailed |= test_wifi_hal_sta_register();
    registerFailed |= test_wifi_hal_telemetry_register();
    registerFailed |= test_wifi_hal_ap_register();
    registerFailed |= test_wifi_hal_l2_register();

    return registerFailed;
}

