/* ******************************************************************************
* Copyright (C) 2022 Sky group of companies, All Rights Reserved
* * --------------------------------------------------------------------------
* * THIS SOFTWARE CONTRIBUTION IS PROVIDED ON BEHALF OF SKY PLC. 
* * BY THE CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING,
* * BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
* * A PARTICULAR PURPOSE ARE DISCLAIMED
* ******************************************************************************
*
*   ** Project      : ut_wifi
*   ** @addtogroup  : ut_wifi
*   ** @author      : gerald.weatherup@sky.uk
*   ** @date        : 19/08/22
*   **
*   ** @brief : UT test registration function
*   **
*
* ******************************************************************************/
/**
 * @brief Register test functionality
 * 
 */

/* L1 Testing Functions */
//extern int test_wifi_hal_ap_register( void );
//extern int test_wifi_hal_client_mgt_register( void );
//extern int test_wifi_hal_extender_register( void );
//extern int test_wifi_hal_radio_register( void );
//extern int test_wifi_hal_sta_register( void );
//extern int test_wifi_hal_telemetry_register( void );
//extern int test_wifi_hal_ap_register( void );
extern int test_generic_register( void );

/* L2 Testing Functions */
extern int test_wifi_hal_l2_register( void );

int register_hal_l1_tests( void )
{
    int registerFailed=0;

    registerFailed |= test_generic_register();
    //registerFailed |= test_wifi_hal_client_mgt_register();
    //registerFailed |= test_wifi_hal_extender_register();
    //registerFailed |= test_wifi_hal_radio_register();
    //registerFailed |= test_wifi_hal_sta_register();
    //registerFailed |= test_wifi_hal_telemetry_register();
    //registerFailed |= test_wifi_hal_ap_register();

    return registerFailed;
}

int register_hal_l2_tests( void )
{
    int registerFailed=0;

    registerFailed |= test_wifi_hal_l2_register();

    return registerFailed;
}
