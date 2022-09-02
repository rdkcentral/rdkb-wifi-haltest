#include <string.h>
#include <stdlib.h>
#include <setjmp.h>

#include "wifi_hal.h"
#include "wifi_hal_telemetry.h"

INT wifi_getRadioBandUtilization(INT radioIndex, INT* output_percentage)
{
  /*TODO: Implement Me!*/
  (void)radioIndex;
  (void)output_percentage;
  return (INT)0;
}

INT wifi_getApAssociatedDeviceDiagnosticResult3(INT apIndex, wifi_associated_dev3_t** associated_dev_array, UINT* output_array_size)
{
  /*TODO: Implement Me!*/
  (void)apIndex;
  (void)associated_dev_array;
  (void)output_array_size;
  return (INT)0;
}

INT wifi_getApAssociatedClientDiagnosticResult(INT apIndex, mac_address_t mac_addr, wifi_associated_dev3_t* dev_conn)
{
  /*TODO: Implement Me!*/
  (void)apIndex;
  (void)mac_addr;
  (void)dev_conn;
  return (INT)0;
}

INT wifi_getRadioTrafficStats2(INT radioIndex, wifi_radioTrafficStats2_t* output_struct)
{
  /*TODO: Implement Me!*/
  (void)radioIndex;
  (void)output_struct;
  return (INT)0;
}

