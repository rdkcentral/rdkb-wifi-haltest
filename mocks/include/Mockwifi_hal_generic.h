/* AUTOGENERATED FILE. DO NOT EDIT. */
#ifndef _MOCKWIFI_HAL_GENERIC_H
#define _MOCKWIFI_HAL_GENERIC_H

#include "unity.h"
#include "wifi_hal_generic.h"

/* Ignore the following warnings, since we are copying code */
#if defined(__GNUC__) && !defined(__ICC) && !defined(__TMS470__)
#if __GNUC__ > 4 || (__GNUC__ == 4 && (__GNUC_MINOR__ > 6 || (__GNUC_MINOR__ == 6 && __GNUC_PATCHLEVEL__ > 0)))
#pragma GCC diagnostic push
#endif
#if !defined(__clang__)
#pragma GCC diagnostic ignored "-Wpragmas"
#endif
#pragma GCC diagnostic ignored "-Wunknown-pragmas"
#pragma GCC diagnostic ignored "-Wduplicate-decl-specifier"
#endif

void Mockwifi_hal_generic_Init(void);
void Mockwifi_hal_generic_Destroy(void);
void Mockwifi_hal_generic_Verify(void);




#define wifi_init_ExpectAndReturn(cmock_retval) wifi_init_CMockExpectAndReturn(__LINE__, cmock_retval)
void wifi_init_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, INT cmock_to_return);
#define wifi_getHalCapability_ExpectAndReturn(cap, cmock_retval) wifi_getHalCapability_CMockExpectAndReturn(__LINE__, cap, cmock_retval)
void wifi_getHalCapability_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, wifi_hal_capability_t* cap, INT cmock_to_return);

#if defined(__GNUC__) && !defined(__ICC) && !defined(__TMS470__)
#if __GNUC__ > 4 || (__GNUC__ == 4 && (__GNUC_MINOR__ > 6 || (__GNUC_MINOR__ == 6 && __GNUC_PATCHLEVEL__ > 0)))
#pragma GCC diagnostic pop
#endif
#endif

#endif