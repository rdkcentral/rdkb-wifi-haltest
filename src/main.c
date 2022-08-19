/* ******************************************************************************
* Copyright (C) 2022 Sky group of companies, All Rights Reserved
* * --------------------------------------------------------------------------
* * THIS SOFTWARE CONTRIBUTION IS PROVIDED ON BEHALF OF SKY PLC. 
* * BY THE CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING,
* * BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
* * A PARTICULAR PURPOSE ARE DISCLAIMED
* ******************************************************************************
*
*   ** Project      : wifi
*   ** @addtogroup  : ut_wifi
*   ** @author      : gerald.weatherup@sky.uk
*   ** @date        : 19/08/22
*   **
*   ** @brief : test main registration function
*   **
*
* ******************************************************************************/
#include <ut.h>

extern int register_hal_l1_tests( void );
extern int register_hal_l2_tests( void );

int main(int argc, char** argv) 
{
    /* Register tests as required, then call the UT-main to support switches and triggering */
    UT_init( argc, argv );

    register_hal_l1_tests();
    register_hal_l2_tests();

    UT_run_tests();
}
