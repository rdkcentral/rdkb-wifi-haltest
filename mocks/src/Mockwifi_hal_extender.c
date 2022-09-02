/* AUTOGENERATED FILE. DO NOT EDIT. */
#include <string.h>
#include <stdlib.h>
#include <setjmp.h>
#include "cmock.h"
#include "Mockwifi_hal_extender.h"

static const char* CMockString_array_size = "array_size";
static const char* CMockString_input_output_channelStats_array = "input_output_channelStats_array";
static const char* CMockString_radioIndex = "radioIndex";
static const char* CMockString_wifi_getRadioChannelStats = "wifi_getRadioChannelStats";

typedef struct _CMOCK_wifi_getRadioChannelStats_CALL_INSTANCE
{
  UNITY_LINE_TYPE LineNumber;
  INT ReturnVal;
  INT Expected_radioIndex;
  wifi_channelStats_t* Expected_input_output_channelStats_array;
  INT Expected_array_size;

} CMOCK_wifi_getRadioChannelStats_CALL_INSTANCE;

static struct Mockwifi_hal_extenderInstance
{
  CMOCK_MEM_INDEX_TYPE wifi_getRadioChannelStats_CallInstance;
} Mock;

extern jmp_buf AbortFrame;

void Mockwifi_hal_extender_Verify(void)
{
  UNITY_LINE_TYPE cmock_line = TEST_LINE_NUM;
  CMOCK_MEM_INDEX_TYPE call_instance;
  call_instance = Mock.wifi_getRadioChannelStats_CallInstance;
  if (CMOCK_GUTS_NONE != call_instance)
  {
    UNITY_SET_DETAIL(CMockString_wifi_getRadioChannelStats);
    UNITY_TEST_FAIL(cmock_line, CMockStringCalledLess);
  }
}

void Mockwifi_hal_extender_Init(void)
{
  Mockwifi_hal_extender_Destroy();
}

void Mockwifi_hal_extender_Destroy(void)
{
  CMock_Guts_MemFreeAll();
  memset(&Mock, 0, sizeof(Mock));
}

INT wifi_getRadioChannelStats(INT radioIndex, wifi_channelStats_t* input_output_channelStats_array, INT array_size)
{
  UNITY_LINE_TYPE cmock_line = TEST_LINE_NUM;
  CMOCK_wifi_getRadioChannelStats_CALL_INSTANCE* cmock_call_instance;
  UNITY_SET_DETAIL(CMockString_wifi_getRadioChannelStats);
  cmock_call_instance = (CMOCK_wifi_getRadioChannelStats_CALL_INSTANCE*)CMock_Guts_GetAddressFor(Mock.wifi_getRadioChannelStats_CallInstance);
  Mock.wifi_getRadioChannelStats_CallInstance = CMock_Guts_MemNext(Mock.wifi_getRadioChannelStats_CallInstance);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringCalledMore);
  cmock_line = cmock_call_instance->LineNumber;
  {
    UNITY_SET_DETAILS(CMockString_wifi_getRadioChannelStats,CMockString_radioIndex);
    UNITY_TEST_ASSERT_EQUAL_MEMORY((void*)(&cmock_call_instance->Expected_radioIndex), (void*)(&radioIndex), sizeof(INT), cmock_line, CMockStringMismatch);
  }
  {
    UNITY_SET_DETAILS(CMockString_wifi_getRadioChannelStats,CMockString_input_output_channelStats_array);
    UNITY_TEST_ASSERT_EQUAL_MEMORY((void*)(cmock_call_instance->Expected_input_output_channelStats_array), (void*)(input_output_channelStats_array), sizeof(wifi_channelStats_t), cmock_line, CMockStringMismatch);
  }
  {
    UNITY_SET_DETAILS(CMockString_wifi_getRadioChannelStats,CMockString_array_size);
    UNITY_TEST_ASSERT_EQUAL_MEMORY((void*)(&cmock_call_instance->Expected_array_size), (void*)(&array_size), sizeof(INT), cmock_line, CMockStringMismatch);
  }
  UNITY_CLR_DETAILS();
  return cmock_call_instance->ReturnVal;
}

void CMockExpectParameters_wifi_getRadioChannelStats(CMOCK_wifi_getRadioChannelStats_CALL_INSTANCE* cmock_call_instance, INT radioIndex, wifi_channelStats_t* input_output_channelStats_array, INT array_size);
void CMockExpectParameters_wifi_getRadioChannelStats(CMOCK_wifi_getRadioChannelStats_CALL_INSTANCE* cmock_call_instance, INT radioIndex, wifi_channelStats_t* input_output_channelStats_array, INT array_size)
{
  memcpy((void*)(&cmock_call_instance->Expected_radioIndex), (void*)(&radioIndex),
         sizeof(INT[sizeof(radioIndex) == sizeof(INT) ? 1 : -1])); /* add INT to :treat_as_array if this causes an error */
  cmock_call_instance->Expected_input_output_channelStats_array = input_output_channelStats_array;
  memcpy((void*)(&cmock_call_instance->Expected_array_size), (void*)(&array_size),
         sizeof(INT[sizeof(array_size) == sizeof(INT) ? 1 : -1])); /* add INT to :treat_as_array if this causes an error */
}

void wifi_getRadioChannelStats_CMockExpectAndReturn(UNITY_LINE_TYPE cmock_line, INT radioIndex, wifi_channelStats_t* input_output_channelStats_array, INT array_size, INT cmock_to_return)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_wifi_getRadioChannelStats_CALL_INSTANCE));
  CMOCK_wifi_getRadioChannelStats_CALL_INSTANCE* cmock_call_instance = (CMOCK_wifi_getRadioChannelStats_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, CMockStringOutOfMemory);
  memset(cmock_call_instance, 0, sizeof(*cmock_call_instance));
  Mock.wifi_getRadioChannelStats_CallInstance = CMock_Guts_MemChain(Mock.wifi_getRadioChannelStats_CallInstance, cmock_guts_index);
  cmock_call_instance->LineNumber = cmock_line;
  CMockExpectParameters_wifi_getRadioChannelStats(cmock_call_instance, radioIndex, input_output_channelStats_array, array_size);
  memcpy((void*)(&cmock_call_instance->ReturnVal), (void*)(&cmock_to_return),
         sizeof(INT[sizeof(cmock_to_return) == sizeof(INT) ? 1 : -1])); /* add INT to :treat_as_array if this causes an error */
}

