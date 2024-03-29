/* AUTOGENERATED FILE. DO NOT EDIT. */
#include <string.h>
#include <stdlib.h>
#include <setjmp.h>
#include "cmock.h"
#include "Mockwifi_hal_telemetry.h"

static const char* CMockString_apIndex = "apIndex";
static const char* CMockString_associated_dev_array = "associated_dev_array";
static const char* CMockString_dev_conn = "dev_conn";
static const char* CMockString_mac_addr = "mac_addr";
static const char* CMockString_output_array_size = "output_array_size";
static const char* CMockString_output_percentage = "output_percentage";
static const char* CMockString_output_struct = "output_struct";
static const char* CMockString_radioIndex = "radioIndex";
static const char* CMockString_wifi_getApAssociatedClientDiagnosticResult = "wifi_getApAssociatedClientDiagnosticResult";
static const char* CMockString_wifi_getApAssociatedDeviceDiagnosticResult3 = "wifi_getApAssociatedDeviceDiagnosticResult3";
static const char* CMockString_wifi_getRadioBandUtilization = "wifi_getRadioBandUtilization";
static const char* CMockString_wifi_getRadioTrafficStats2 = "wifi_getRadioTrafficStats2";

typedef struct _CMOCK_wifi_getRadioBandUtilization_CALL_INSTANCE
{
  UNITY_LINE_TYPE LineNumber;
  INT ReturnVal;
  INT Expected_radioIndex;
  INT* Expected_output_percentage;

} CMOCK_wifi_getRadioBandUtilization_CALL_INSTANCE;

typedef struct _CMOCK_wifi_getApAssociatedDeviceDiagnosticResult3_CALL_INSTANCE
{
  UNITY_LINE_TYPE LineNumber;
  INT ReturnVal;
  INT Expected_apIndex;
  wifi_associated_dev3_t** Expected_associated_dev_array;
  UINT* Expected_output_array_size;

} CMOCK_wifi_getApAssociatedDeviceDiagnosticResult3_CALL_INSTANCE;

typedef struct _CMOCK_wifi_getApAssociatedClientDiagnosticResult_CALL_INSTANCE
{
  UNITY_LINE_TYPE LineNumber;
  INT ReturnVal;
  INT Expected_apIndex;
  mac_address_t Expected_mac_addr;
  wifi_associated_dev3_t* Expected_dev_conn;

} CMOCK_wifi_getApAssociatedClientDiagnosticResult_CALL_INSTANCE;

typedef struct _CMOCK_wifi_getRadioTrafficStats2_CALL_INSTANCE
{
  UNITY_LINE_TYPE LineNumber;
  INT ReturnVal;
  INT Expected_radioIndex;
  wifi_radioTrafficStats2_t* Expected_output_struct;

} CMOCK_wifi_getRadioTrafficStats2_CALL_INSTANCE;

static struct Mockwifi_hal_telemetryInstance
{
  CMOCK_MEM_INDEX_TYPE wifi_getRadioBandUtilization_CallInstance;
  CMOCK_MEM_INDEX_TYPE wifi_getApAssociatedDeviceDiagnosticResult3_CallInstance;
  CMOCK_MEM_INDEX_TYPE wifi_getApAssociatedClientDiagnosticResult_CallInstance;
  CMOCK_MEM_INDEX_TYPE wifi_getRadioTrafficStats2_CallInstance;
} Mock;

extern jmp_buf AbortFrame;

void Mockwifi_hal_telemetry_Verify(void)
{
  UNITY_LINE_TYPE cmock_line = TEST_LINE_NUM;
  CMOCK_MEM_INDEX_TYPE call_instance;
  call_instance = Mock.wifi_getRadioBandUtilization_CallInstance;
  if (CMOCK_GUTS_NONE != call_instance)
  {
    UNITY_SET_DETAIL(CMockString_wifi_getRadioBandUtilization);
    UNITY_TEST_FAIL(cmock_line, CMockStringCalledLess);
  }
  call_instance = Mock.wifi_getApAssociatedDeviceDiagnosticResult3_CallInstance;
  if (CMOCK_GUTS_NONE != call_instance)
  {
    UNITY_SET_DETAIL(CMockString_wifi_getApAssociatedDeviceDiagnosticResult3);
    UNITY_TEST_FAIL(cmock_line, CMockStringCalledLess);
  }
  call_instance = Mock.wifi_getApAssociatedClientDiagnosticResult_CallInstance;
  if (CMOCK_GUTS_NONE != call_instance)
  {
    UNITY_SET_DETAIL(CMockString_wifi_getApAssociatedClientDiagnosticResult);
    UNITY_TEST_FAIL(cmock_line, CMockStringCalledLess);
  }
  call_instance = Mock.wifi_getRadioTrafficStats2_CallInstance;
  if (CMOCK_GUTS_NONE != call_instance)
  {
    UNITY_SET_DETAIL(CMockString_wifi_getRadioTrafficStats2);
    UNITY_TEST_FAIL(cmock_line, CMockStringCalledLess);
  }
}

void Mockwifi_hal_telemetry_Init(void)
{
  Mockwifi_hal_telemetry_Destroy();
}

void Mockwifi_hal_telemetry_Destroy(void)
{
  CMock_Guts_MemFreeAll();
  memset(&Mock, 0, sizeof(Mock));
}

INT wifi_getRadioBandUtilization(INT radioIndex, INT* output_percentage)
{
  UNITY_LINE_TYPE cmock_line = TEST_LINE_NUM;
  CMOCK_wifi_getRadioBandUtilization_CALL_INSTANCE* cmock_call_instance;
  UNITY_SET_DETAIL(CMockString_wifi_getRadioBandUtilization);
  cmock_call_instance = (CMOCK_wifi_getRadioBandUtilization_CALL_INSTANCE*)CMock_Guts_GetAddressFor(Mock.wifi_getRadioBandUtilization_CallInstance);
  Mock.wifi_getRadioBandUtilization_CallInstance = CMock_Guts_MemNext(Mock.wifi_getRadioBandUtilization_CallInstance);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringCalledMore);
  cmock_line = cmock_call_instance->LineNumber;
  {
    UNITY_SET_DETAILS(CMockString_wifi_getRadioBandUtilization,CMockString_radioIndex);
    UNITY_TEST_ASSERT_EQUAL_MEMORY((void*)(&cmock_call_instance->Expected_radioIndex), (void*)(&radioIndex), sizeof(INT), cmock_line, CMockStringMismatch);
  }
  {
    UNITY_SET_DETAILS(CMockString_wifi_getRadioBandUtilization,CMockString_output_percentage);
    UNITY_TEST_ASSERT_EQUAL_MEMORY((void*)(cmock_call_instance->Expected_output_percentage), (void*)(output_percentage), sizeof(INT), cmock_line, CMockStringMismatch);
  }
  UNITY_CLR_DETAILS();
  return cmock_call_instance->ReturnVal;
}

void CMockExpectParameters_wifi_getRadioBandUtilization(CMOCK_wifi_getRadioBandUtilization_CALL_INSTANCE* cmock_call_instance, INT radioIndex, INT* output_percentage);
void CMockExpectParameters_wifi_getRadioBandUtilization(CMOCK_wifi_getRadioBandUtilization_CALL_INSTANCE* cmock_call_instance, INT radioIndex, INT* output_percentage)
{
  memcpy((void*)(&cmock_call_instance->Expected_radioIndex), (void*)(&radioIndex),
         sizeof(INT[sizeof(radioIndex) == sizeof(INT) ? 1 : -1])); /* add INT to :treat_as_array if this causes an error */
  cmock_call_instance->Expected_output_percentage = output_percentage;
}

void wifi_getRadioBandUtilization_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, INT radioIndex, INT* output_percentage, INT cmock_to_return)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_wifi_getRadioBandUtilization_CALL_INSTANCE));
  CMOCK_wifi_getRadioBandUtilization_CALL_INSTANCE* cmock_call_instance = (CMOCK_wifi_getRadioBandUtilization_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.wifi_getRadioBandUtilization_CallInstance = CMock_Guts_MemChain(Mock.wifi_getRadioBandUtilization_CallInstance, cmock_guts_index);
  cmock_call_instance->LineNumber = cmock_line;
  CMockExpectParameters_wifi_getRadioBandUtilization(cmock_call_instance, radioIndex, output_percentage);
  memcpy((void*)(&cmock_call_instance->ReturnVal), (void*)(&cmock_to_return),
         sizeof(INT[sizeof(cmock_to_return) == sizeof(INT) ? 1 : -1])); /* add INT to :treat_as_array if this causes an error */
}

INT wifi_getApAssociatedDeviceDiagnosticResult3(INT apIndex, wifi_associated_dev3_t** associated_dev_array, UINT* output_array_size)
{
  UNITY_LINE_TYPE cmock_line = TEST_LINE_NUM;
  CMOCK_wifi_getApAssociatedDeviceDiagnosticResult3_CALL_INSTANCE* cmock_call_instance;
  UNITY_SET_DETAIL(CMockString_wifi_getApAssociatedDeviceDiagnosticResult3);
  cmock_call_instance = (CMOCK_wifi_getApAssociatedDeviceDiagnosticResult3_CALL_INSTANCE*)CMock_Guts_GetAddressFor(Mock.wifi_getApAssociatedDeviceDiagnosticResult3_CallInstance);
  Mock.wifi_getApAssociatedDeviceDiagnosticResult3_CallInstance = CMock_Guts_MemNext(Mock.wifi_getApAssociatedDeviceDiagnosticResult3_CallInstance);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringCalledMore);
  cmock_line = cmock_call_instance->LineNumber;
  {
    UNITY_SET_DETAILS(CMockString_wifi_getApAssociatedDeviceDiagnosticResult3,CMockString_apIndex);
    UNITY_TEST_ASSERT_EQUAL_MEMORY((void*)(&cmock_call_instance->Expected_apIndex), (void*)(&apIndex), sizeof(INT), cmock_line, CMockStringMismatch);
  }
  {
    UNITY_SET_DETAILS(CMockString_wifi_getApAssociatedDeviceDiagnosticResult3,CMockString_associated_dev_array);
    UNITY_TEST_ASSERT_EQUAL_PTR(cmock_call_instance->Expected_associated_dev_array, associated_dev_array, cmock_line, CMockStringMismatch);
  }
  {
    UNITY_SET_DETAILS(CMockString_wifi_getApAssociatedDeviceDiagnosticResult3,CMockString_output_array_size);
    UNITY_TEST_ASSERT_EQUAL_MEMORY((void*)(cmock_call_instance->Expected_output_array_size), (void*)(output_array_size), sizeof(UINT), cmock_line, CMockStringMismatch);
  }
  UNITY_CLR_DETAILS();
  return cmock_call_instance->ReturnVal;
}

void CMockExpectParameters_wifi_getApAssociatedDeviceDiagnosticResult3(CMOCK_wifi_getApAssociatedDeviceDiagnosticResult3_CALL_INSTANCE* cmock_call_instance, INT apIndex, wifi_associated_dev3_t** associated_dev_array, UINT* output_array_size);
void CMockExpectParameters_wifi_getApAssociatedDeviceDiagnosticResult3(CMOCK_wifi_getApAssociatedDeviceDiagnosticResult3_CALL_INSTANCE* cmock_call_instance, INT apIndex, wifi_associated_dev3_t** associated_dev_array, UINT* output_array_size)
{
  memcpy((void*)(&cmock_call_instance->Expected_apIndex), (void*)(&apIndex),
         sizeof(INT[sizeof(apIndex) == sizeof(INT) ? 1 : -1])); /* add INT to :treat_as_array if this causes an error */
  cmock_call_instance->Expected_associated_dev_array = associated_dev_array;
  cmock_call_instance->Expected_output_array_size = output_array_size;
}

void wifi_getApAssociatedDeviceDiagnosticResult3_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, INT apIndex, wifi_associated_dev3_t** associated_dev_array, UINT* output_array_size, INT cmock_to_return)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_wifi_getApAssociatedDeviceDiagnosticResult3_CALL_INSTANCE));
  CMOCK_wifi_getApAssociatedDeviceDiagnosticResult3_CALL_INSTANCE* cmock_call_instance = (CMOCK_wifi_getApAssociatedDeviceDiagnosticResult3_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.wifi_getApAssociatedDeviceDiagnosticResult3_CallInstance = CMock_Guts_MemChain(Mock.wifi_getApAssociatedDeviceDiagnosticResult3_CallInstance, cmock_guts_index);
  cmock_call_instance->LineNumber = cmock_line;
  CMockExpectParameters_wifi_getApAssociatedDeviceDiagnosticResult3(cmock_call_instance, apIndex, associated_dev_array, output_array_size);
  memcpy((void*)(&cmock_call_instance->ReturnVal), (void*)(&cmock_to_return),
         sizeof(INT[sizeof(cmock_to_return) == sizeof(INT) ? 1 : -1])); /* add INT to :treat_as_array if this causes an error */
}

INT wifi_getApAssociatedClientDiagnosticResult(INT apIndex, mac_address_t mac_addr, wifi_associated_dev3_t* dev_conn)
{
  UNITY_LINE_TYPE cmock_line = TEST_LINE_NUM;
  CMOCK_wifi_getApAssociatedClientDiagnosticResult_CALL_INSTANCE* cmock_call_instance;
  UNITY_SET_DETAIL(CMockString_wifi_getApAssociatedClientDiagnosticResult);
  cmock_call_instance = (CMOCK_wifi_getApAssociatedClientDiagnosticResult_CALL_INSTANCE*)CMock_Guts_GetAddressFor(Mock.wifi_getApAssociatedClientDiagnosticResult_CallInstance);
  Mock.wifi_getApAssociatedClientDiagnosticResult_CallInstance = CMock_Guts_MemNext(Mock.wifi_getApAssociatedClientDiagnosticResult_CallInstance);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringCalledMore);
  cmock_line = cmock_call_instance->LineNumber;
  {
    UNITY_SET_DETAILS(CMockString_wifi_getApAssociatedClientDiagnosticResult,CMockString_apIndex);
    UNITY_TEST_ASSERT_EQUAL_MEMORY((void*)(&cmock_call_instance->Expected_apIndex), (void*)(&apIndex), sizeof(INT), cmock_line, CMockStringMismatch);
  }
  {
    UNITY_SET_DETAILS(CMockString_wifi_getApAssociatedClientDiagnosticResult,CMockString_mac_addr);
    UNITY_TEST_ASSERT_EQUAL_MEMORY((void*)(&cmock_call_instance->Expected_mac_addr), (void*)(&mac_addr), sizeof(mac_address_t), cmock_line, CMockStringMismatch);
  }
  {
    UNITY_SET_DETAILS(CMockString_wifi_getApAssociatedClientDiagnosticResult,CMockString_dev_conn);
    UNITY_TEST_ASSERT_EQUAL_MEMORY((void*)(cmock_call_instance->Expected_dev_conn), (void*)(dev_conn), sizeof(wifi_associated_dev3_t), cmock_line, CMockStringMismatch);
  }
  UNITY_CLR_DETAILS();
  return cmock_call_instance->ReturnVal;
}

void CMockExpectParameters_wifi_getApAssociatedClientDiagnosticResult(CMOCK_wifi_getApAssociatedClientDiagnosticResult_CALL_INSTANCE* cmock_call_instance, INT apIndex, mac_address_t mac_addr, wifi_associated_dev3_t* dev_conn);
void CMockExpectParameters_wifi_getApAssociatedClientDiagnosticResult(CMOCK_wifi_getApAssociatedClientDiagnosticResult_CALL_INSTANCE* cmock_call_instance, INT apIndex, mac_address_t mac_addr, wifi_associated_dev3_t* dev_conn)
{
  memcpy((void*)(&cmock_call_instance->Expected_apIndex), (void*)(&apIndex),
         sizeof(INT[sizeof(apIndex) == sizeof(INT) ? 1 : -1])); /* add INT to :treat_as_array if this causes an error */
  memcpy((void*)(&cmock_call_instance->Expected_mac_addr), (void*)(&mac_addr),
         sizeof(mac_address_t[sizeof(mac_addr) == sizeof(mac_address_t) ? 1 : -1])); /* add mac_address_t to :treat_as_array if this causes an error */
  cmock_call_instance->Expected_dev_conn = dev_conn;
}

void wifi_getApAssociatedClientDiagnosticResult_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, INT apIndex, mac_address_t mac_addr, wifi_associated_dev3_t* dev_conn, INT cmock_to_return)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_wifi_getApAssociatedClientDiagnosticResult_CALL_INSTANCE));
  CMOCK_wifi_getApAssociatedClientDiagnosticResult_CALL_INSTANCE* cmock_call_instance = (CMOCK_wifi_getApAssociatedClientDiagnosticResult_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.wifi_getApAssociatedClientDiagnosticResult_CallInstance = CMock_Guts_MemChain(Mock.wifi_getApAssociatedClientDiagnosticResult_CallInstance, cmock_guts_index);
  cmock_call_instance->LineNumber = cmock_line;
  CMockExpectParameters_wifi_getApAssociatedClientDiagnosticResult(cmock_call_instance, apIndex, mac_addr, dev_conn);
  memcpy((void*)(&cmock_call_instance->ReturnVal), (void*)(&cmock_to_return),
         sizeof(INT[sizeof(cmock_to_return) == sizeof(INT) ? 1 : -1])); /* add INT to :treat_as_array if this causes an error */
}

INT wifi_getRadioTrafficStats2(INT radioIndex, wifi_radioTrafficStats2_t* output_struct)
{
  UNITY_LINE_TYPE cmock_line = TEST_LINE_NUM;
  CMOCK_wifi_getRadioTrafficStats2_CALL_INSTANCE* cmock_call_instance;
  UNITY_SET_DETAIL(CMockString_wifi_getRadioTrafficStats2);
  cmock_call_instance = (CMOCK_wifi_getRadioTrafficStats2_CALL_INSTANCE*)CMock_Guts_GetAddressFor(Mock.wifi_getRadioTrafficStats2_CallInstance);
  Mock.wifi_getRadioTrafficStats2_CallInstance = CMock_Guts_MemNext(Mock.wifi_getRadioTrafficStats2_CallInstance);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringCalledMore);
  cmock_line = cmock_call_instance->LineNumber;
  {
    UNITY_SET_DETAILS(CMockString_wifi_getRadioTrafficStats2,CMockString_radioIndex);
    UNITY_TEST_ASSERT_EQUAL_MEMORY((void*)(&cmock_call_instance->Expected_radioIndex), (void*)(&radioIndex), sizeof(INT), cmock_line, CMockStringMismatch);
  }
  {
    UNITY_SET_DETAILS(CMockString_wifi_getRadioTrafficStats2,CMockString_output_struct);
    UNITY_TEST_ASSERT_EQUAL_MEMORY((void*)(cmock_call_instance->Expected_output_struct), (void*)(output_struct), sizeof(wifi_radioTrafficStats2_t), cmock_line, CMockStringMismatch);
  }
  UNITY_CLR_DETAILS();
  return cmock_call_instance->ReturnVal;
}

void CMockExpectParameters_wifi_getRadioTrafficStats2(CMOCK_wifi_getRadioTrafficStats2_CALL_INSTANCE* cmock_call_instance, INT radioIndex, wifi_radioTrafficStats2_t* output_struct);
void CMockExpectParameters_wifi_getRadioTrafficStats2(CMOCK_wifi_getRadioTrafficStats2_CALL_INSTANCE* cmock_call_instance, INT radioIndex, wifi_radioTrafficStats2_t* output_struct)
{
  memcpy((void*)(&cmock_call_instance->Expected_radioIndex), (void*)(&radioIndex),
         sizeof(INT[sizeof(radioIndex) == sizeof(INT) ? 1 : -1])); /* add INT to :treat_as_array if this causes an error */
  cmock_call_instance->Expected_output_struct = output_struct;
}

void wifi_getRadioTrafficStats2_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, INT radioIndex, wifi_radioTrafficStats2_t* output_struct, INT cmock_to_return)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_wifi_getRadioTrafficStats2_CALL_INSTANCE));
  CMOCK_wifi_getRadioTrafficStats2_CALL_INSTANCE* cmock_call_instance = (CMOCK_wifi_getRadioTrafficStats2_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.wifi_getRadioTrafficStats2_CallInstance = CMock_Guts_MemChain(Mock.wifi_getRadioTrafficStats2_CallInstance, cmock_guts_index);
  cmock_call_instance->LineNumber = cmock_line;
  CMockExpectParameters_wifi_getRadioTrafficStats2(cmock_call_instance, radioIndex, output_struct);
  memcpy((void*)(&cmock_call_instance->ReturnVal), (void*)(&cmock_to_return),
         sizeof(INT[sizeof(cmock_to_return) == sizeof(INT) ? 1 : -1])); /* add INT to :treat_as_array if this causes an error */
}

