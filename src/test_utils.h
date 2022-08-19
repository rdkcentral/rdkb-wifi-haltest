
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
*   ** @author      : Palaksha Gowda
*   ** @date        : 19/08/22
*   **
*   ** @brief : Unit testing
*   **
*
* ******************************************************************************/

#include <stdint.h>

// In order to get INT, BOOL Types
#include <wifi_hal_generic.h>

#define TEST_WIFI_HAL_VALID_SSID ("test@1234")

/* #TODO -> Doxygen comments required */

/* Local Functions */
extern INT test_utils_setApEnable (BOOL enable, INT ap_index);
extern INT test_utils_channelPush(INT radioIndex, ULONG channel);
extern INT test_utils_setBandwidth(INT radioIndex, UINT bandwidth);

/* This will test SSID set functionality *
* positive case * maps to WIFI_HAL_SUCCESS *
* set main interface SSIDs to "test@1234" and check if the value is set with corresponding get
* virtual/guest SSID set check is not added yet
*
* Negative case * maps to WIFI_HAL_ERROR, WIFI_HAL_INTERNAL_ERROR, WIFI_HAL_UNSUPPORTED, WIFI_HAL_INVALID_ARGUMENTS, WIFI_HAL_INVALID_VALUE *
* Try to set SSID to NULL Value *
* Try to set SSID with wrong AP indexes * Here 25,26,27 are taken as wrong indices */

/* SSID SET UTILITY FUNCTIONS */
extern INT test_utils_setValidSSID(INT radioIndex, INT ap_index, INT ap_pointing_index);
extern INT test_utils_setInValidIndexSSID(INT radioIndex, INT ap_index, INT ap_pointing_index);
extern INT test_utils_setNULLSSID(INT radioIndex, INT ap_index,INT ap_pointing_index);
/* UTILITY FUNCTIONS END */