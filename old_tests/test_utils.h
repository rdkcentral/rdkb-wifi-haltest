
#include <stdint.h>

// In order to get INT, BOOL Types
#include <wifi_hal_generic.h>

#define TEST_WIFI_HAL_VALID_SSID ("test@1234")

/* TODO -> Doxygen comments required */

/* Local Functions */
extern INT test_utils_setApEnable (BOOL enable, INT ap_index);
extern INT test_utils_channelPush(INT radioIndex, ULONG channel);
extern INT test_utils_setBandwidth(INT radioIndex, UINT bandwidth);

/* This will test SSID set functionality *
* positive case * maps to WIFI_HAL_SUCCESS *
* set main interface SSIDs to "test@1234" and check if the value is set with corresponding get
* virtaul/guest SSID set check is not added yet
*
* Negative case * maps to WIFI_HAL_ERROR, WIFI_HAL_INTERNAL_ERROR, WIFI_HAL_UNSUPPORTED, WIFI_HAL_INVALID_ARGUMENTS, WIFI_HAL_INVALID_VALUE *
* Try to set SSID to NULL Value *
* Try to set SSID with wrong AP indexes * Here 25,26,27 are taken as wrong indeces */

/* SSID SET UTILITY FUNCTIONS */
extern INT test_utils_setValidSSID(INT radioIndex, INT ap_index, INT ap_pointing_index);
extern INT test_utils_setInValidIndexSSID(INT radioIndex, INT ap_index, INT ap_pointing_index);
extern INT test_utils_setNULLSSID(INT radioIndex, INT ap_index,INT ap_pointing_index);
/* UTILITY FUNCTIONS END */