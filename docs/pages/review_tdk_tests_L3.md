# Review of TDK-B Tests                                                                                             Version -V1.0

## Purpose of this document :
In order to design 3PE-HAL-Test-Suite we can refer this documnet.

## Requirements :<br />
1. APIs avaialble for testing :- [https://github.com/comcast-sky/rdk-components-hal-wifi-rdkb/tree/develop/include]<br />
2. Refer to link for ticket :- [https://ccp.sys.comcast.net/browse/RDKB-44011]
3. Source code for test scripts :-
https://gerrit.teamccp.com/plugins/gitiles/rdk/rdkb/components/generic/tdkb/generic/+/stable2/testscripts/RDKB/component/WIFIHAL/

## Original spreadsheet Link :
https://wiki.rdkcentral.com/download/attachments/213600196/WIFIHAL_Component_TestCases.xls?version=1&modificationDate=1660196147000&api=v2

## Tests Specification Identifiers :
- <u>**ID :**</u> Test case ID is serial number of test case from the original spreadsheet.
- <u>**Test Case Objectives :**</u> Purpose of the test
- <u>**Test Items :**</u> Items (e.g., requirement specifications, design specifications, code, etc.) required to run a particular test case. This should be provided in “Notes” or “Attachment” feature. It describes the features and conditions required for testing.
- <u>**Input Specifications :**</u> Description of what is required (step-by-step) to execute the test case (e.g., input files, values that must be entered into a field, etc.). This should be provided in “Action” field.
- <u>**Output Specifications :**</u> Description of what the system should look like after the test case is run. This should be provided in the “Expected Results” field.
- <u>**Environmental Needs :**</u> Description of any special environmental needs. This includes system architectures, Hardware & Software tools, records or files, interfaces, etc
- <u>**Test script :** </u> Test script name for HAL API testing.
- <u>**Test case ID :** </u> Test case identifier which is unique for every test case, in order to clearly find the test.
- <u>**Test objective :** </u> Purpose or outcomes of the tests.
- <u>**Review :**</u> This includes info regarding whether API being tested is available anymore or not and also test case is Required/Not required or Unclear.Also it includes additional API requirement for Level 2 API testing.


 ## Abbreviations :
|Acronym| Full form|
|-----------|----------|
|CCSP |Coommon Client Software Platform|
|TDK   |Test Development Kit|
|TDK-B |Test Development Kit - Broadband|
|HAL |Hardware Abstraction Layer|
|Rpi | Raspberry Pi|
|AP |Access Point|
|API |Application Programming Interface|
|MAC |Media Access Control|
|EAPOL |Extensible Authentication Protocol over LAN|
|EAP |Extensible Authentication Protocol|
|RSSI |Relative Received Signal Strength|
|FT |Fast Transition|
|DS |Distribution System|
|FTR |Fast Transition R0/R1 |
|BSS |Basic Service Set|

## TDK Testing Table
### Level 3 Testing - External testing
|ID|Objectives|Requirements | Input| Output | Environement | Test Script |Test Case ID |Test Objective|Review |
|----|--------|-------------|------|--------|--------------|-------------|-------------|--------------|-------|
|[#739](#original-spreadsheet-link)|wifi_setNeighborReportActivation() - Invoke the HAL API wifi_setNeighborReports() to set the neighbor reports for the connected client when Neighbor Reports Activation is enabled for 2.4GHz private radio AP.|1.Ccsp Components  should be in a running state else invoke [cosa_start.sh](https://rdkopengrok.stb.r53.xcal.tv/source/xref/txb7_stable2/generic/CcspCommonLibrary/scripts/cosa?r=818de962) manually that includes all the ccsp components and TDK Component.<br /> 2.TDK Agent should be in running state or invoke it through [StartTDK.sh](https://gerrit.teamccp.com/plugins/gitiles/rdk/rdkb/components/generic/tdkb/devices/tch/tch_cbr/+/stable2/agent/scripts/StartTDK.sh) script.<br /> 3. Connect a client to 2.4GHz radio private AP|UINT apIndex,<br />BOOL activate|INT<br />The HAL API wifi_setNeighborReports() to set the neighbor reports for the connected client when Neighbor Reports Activation is enabled for 2.4GHz private radio AP should be invoked successfully.|Hardware,Broadband|TS_WIFIHAL_2.4GHzSetNeighborReports|TC_WIFIHAL_717|Invoke the HAL API wifi_setNeighborReports() to set the neighbor reports for the connected client when Neighbor Reports Activation is enabled for 2.4GHz private radio AP.|V3:Required since same function wifi_setNeighborReportActivation() available in the TDK test suite|
|[#743](#original-spreadsheet-link)|wifi_setNeighborReportActivation() - Invoke the HAL API wifi_setNeighborReports() to set the neighbor reports for the connected client when Neighbor Reports Activation is enabled for 5GHz private radio AP.|1.Ccsp Components  should be in a running state else invoke [cosa_start.sh](https://rdkopengrok.stb.r53.xcal.tv/source/xref/txb7_stable2/generic/CcspCommonLibrary/scripts/cosa?r=818de962) manually that includes all the ccsp components and TDK Component.<br /> 2.TDK Agent should be in running state or invoke it through [StartTDK.sh](https://gerrit.teamccp.com/plugins/gitiles/rdk/rdkb/components/generic/tdkb/devices/tch/tch_cbr/+/stable2/agent/scripts/StartTDK.sh) script.<br /> 3. Connect a client to 5GHz radio private AP|UINT apIndex,<br />BOOL activate|INT<br />The HAL API wifi_setNeighborReports() to set the neighbor reports for the connected client when Neighbor Reports Activation is enabled for 5GHz private radio AP should be invoked successfully.|Hardware,Broadband|TS_WIFIHAL_5GHzSetNeighborReports|TC_WIFIHAL_718|Invoke the HAL API wifi_setNeighborReports() to set the neighbor reports for the connected client when Neighbor Reports Activation is enabled for 5GHz private radio AP.|V3:Required since same function wifi_setNeighborReportActivation() available in the TDK test suite|
|[#739](#original-spreadsheet-link)|wifi_getNeighborReportActivation() - Invoke the HAL API wifi_setNeighborReports() to set the neighbor reports for the connected client when Neighbor Reports Activation is enabled for 2.4GHz private radio AP.|1.Ccsp Components  should be in a running state else invoke [cosa_start.sh](https://rdkopengrok.stb.r53.xcal.tv/source/xref/txb7_stable2/generic/CcspCommonLibrary/scripts/cosa?r=818de962) manually that includes all the ccsp components and TDK Component.<br /> 2.TDK Agent should be in running state or invoke it through [StartTDK.sh](https://gerrit.teamccp.com/plugins/gitiles/rdk/rdkb/components/generic/tdkb/devices/tch/tch_cbr/+/stable2/agent/scripts/StartTDK.sh) script.<br /> 3. Connect a client to 2.4GHz radio private AP|UINT apIndex,<br />BOOL *activate|INT<br />The HAL API wifi_setNeighborReports() to set the neighbor reports for the connected client when Neighbor Reports Activation is enabled for 2.4GHz private radio AP should be invoked successfully.|Hardware,Broadband|TS_WIFIHAL_2.4GHzSetNeighborReports|TC_WIFIHAL_717|Invoke the HAL API wifi_setNeighborReports() to set the neighbor reports for the connected client when Neighbor Reports Activation is enabled for 2.4GHz private radio AP.|V3:Required since same function wifi_getNeighborReportActivation() available in the TDK test suite|
|[#743](#original-spreadsheet-link)|wifi_getNeighborReportActivation() - Invoke the HAL API wifi_setNeighborReports() to set the neighbor reports for the connected client when Neighbor Reports Activation is enabled for 5GHz private radio AP.|1.Ccsp Components  should be in a running state else invoke [cosa_start.sh](https://rdkopengrok.stb.r53.xcal.tv/source/xref/txb7_stable2/generic/CcspCommonLibrary/scripts/cosa?r=818de962) manually that includes all the ccsp components and TDK Component.<br />2.TDK Agent should be in running state or invoke it through [StartTDK.sh](https://gerrit.teamccp.com/plugins/gitiles/rdk/rdkb/components/generic/tdkb/devices/tch/tch_cbr/+/stable2/agent/scripts/StartTDK.sh) script.<br /> 3. Connect a client to 5GHz radio private AP|UINT apIndex,<br />BOOL *activate|INT<br />The HAL API wifi_setNeighborReports() to set the neighbor reports for the connected client when Neighbor Reports Activation is enabled for 5GHz private radio AP should be invoked successfully.|Hardware,Broadband|TS_WIFIHAL_5GHzSetNeighborReports|TC_WIFIHAL_718|Invoke the HAL API wifi_setNeighborReports() to set the neighbor reports for the connected client when Neighbor Reports Activation is enabled for 5GHz private radio AP.|V3:Required since same function wifi_getNeighborReportActivation() available in the TDK test suite|
|[#324](#original-spreadsheet-link)|wifi_getApAssociatedDevice() - Get the List of associated devices mac adresses for 2.4GHz.|1.Ccsp Components  should be in a running state else invoke [cosa_start.sh](https://rdkopengrok.stb.r53.xcal.tv/source/xref/txb7_stable2/generic/CcspCommonLibrary/scripts/cosa?r=818de962) manually that includes all the ccsp components and TDK Component.<br />2.TDK Agent should be in running state or invoke it through [StartTDK.sh](https://gerrit.teamccp.com/plugins/gitiles/rdk/rdkb/components/generic/tdkb/devices/tch/tch_cbr/+/stable2/agent/scripts/StartTDK.sh) script.<br /> 3.A wifi client should be connected to the GW while testing.|INT apIndex,<br />mac_address_t *opDeviceMacAddArray,<br />UINT maxNumDevices,<br />UINT *opNumOfDevices|INT<br />Should get the list of associated devices for 2.4GHz|Hardware,Broadband|TS_WIFIHAL_2.4GHzGet_ApAssociatedDevice|TS_WIFIHAL_337|Get the List of associated devices mac adresses.|V3:Required, since wifi_getApAssociatedDevice() available in TDK test suite.|
|[#335](#original-spreadsheet-link)|wifi_getApAssociatedDevice() - Get the List of associated devices mac adresses for 5GHz.|1.Ccsp Components  should be in a running state else invoke [cosa_start.sh](https://rdkopengrok.stb.r53.xcal.tv/source/xref/txb7_stable2/generic/CcspCommonLibrary/scripts/cosa?r=818de962) manually that includes all the ccsp components and TDK Component.<br />2.TDK Agent should be in running state or invoke it through [StartTDK.sh](https://gerrit.teamccp.com/plugins/gitiles/rdk/rdkb/components/generic/tdkb/devices/tch/tch_cbr/+/stable2/agent/scripts/StartTDK.sh) script|INT apIndex,<br />mac_address_t *opDeviceMacAddArray,<br />UINT maxNumDevices,<br />UINT *opNumOfDevices|INT<br />Should get the list of associated devices for 5GHz|Hardware,Broadband|TS_WIFIHAL_5GHzGet_ApAssociatedDevice|TS_WIFIHAL_351|Get the List of associated devices mac adresses.|V3:Required, since wifi_getApAssociatedDevice() available in TDK test suite.|
|[#739](#original-spreadsheet-link)|wifi_getApAssociatedDeviceDiagnosticResult3() - Invoke the HAL API wifi_setNeighborReports() to set the neighbor reports for the connected client when Neighbor Reports Activation is enabled for 2.4GHz private radio AP.|1.Ccsp Components  should be in a running state else invoke [cosa_start.sh](https://rdkopengrok.stb.r53.xcal.tv/source/xref/txb7_stable2/generic/CcspCommonLibrary/scripts/cosa?r=818de962) manually that includes all the ccsp components and TDK Component.<br />2.TDK Agent should be in running state or invoke it through [StartTDK.sh](https://gerrit.teamccp.com/plugins/gitiles/rdk/rdkb/components/generic/tdkb/devices/tch/tch_cbr/+/stable2/agent/scripts/StartTDK.sh) script.<br /> 3. Connect a client to 2.4GHz radio private AP|INT 2apIndex,<br />wifi_associated_dev3_t **associated_dev_array,<br />UINT *output_array_size|INT<br />The HAL API wifi_setNeighborReports() to set the neighbor reports for the connected client when Neighbor Reports Activation is enabled for 2.4GHz private radio AP should be invoked successfully.|Hardware,Broadband|TS_WIFIHAL_2.4GHzSetNeighborReports|TC_WIFIHAL_717|Invoke the HAL API wifi_setNeighborReports() to set the neighbor reports for the connected client when Neighbor Reports Activation is enabled for 2.4GHz private radio AP.|V3:Required since same function wifi_getApAssociatedDeviceDiagnosticResult3() available in the TDK test suite|
|[#743](#original-spreadsheet-link)|wifi_getApAssociatedDeviceDiagnosticResult3() - Invoke the HAL API wifi_setNeighborReports() to set the neighbor reports for the connected client when Neighbor Reports Activation is enabled for 5GHz private radio AP.|1.Ccsp Components  should be in a running state else invoke [cosa_start.sh](https://rdkopengrok.stb.r53.xcal.tv/source/xref/txb7_stable2/generic/CcspCommonLibrary/scripts/cosa?r=818de962) manually that includes all the ccsp components and TDK Component.<br /> 2.TDK Agent should be in running state or invoke it through [StartTDK.sh](https://gerrit.teamccp.com/plugins/gitiles/rdk/rdkb/components/generic/tdkb/devices/tch/tch_cbr/+/stable2/agent/scripts/StartTDK.sh) script.<br /> 3. Connect a client to 5GHz radio private AP|INT apIndex,<br />wifi_associated_dev3_t **associated_dev_array,<br />UINT *output_array_size|INT<br />The HAL API wifi_setNeighborReports() to set the neighbor reports for the connected client when Neighbor Reports Activation is enabled for 5GHz private radio AP should be invoked successfully.|Hardware,Broadband|TS_WIFIHAL_5GHzSetNeighborReports|TC_WIFIHAL_718|Invoke the HAL API wifi_setNeighborReports() to set the neighbor reports for the connected client when Neighbor Reports Activation is enabled for 5GHz private radio AP.|V3:Required since same function wifi_getApAssociatedDeviceDiagnosticResult3() available in the TDK test suite|
|[#770](#original-spreadsheet-link)|wifi_getApAssociatedDeviceDiagnosticResult3() - Invoke the HAL API wifi_getRMCapabilities() with 2.4GHz connected client MAC address and check if the RM Capabilities values retrieved are valid and non-empty.|1.Ccsp Components  should be in a running state else invoke [cosa_start.sh](https://rdkopengrok.stb.r53.xcal.tv/source/xref/txb7_stable2/generic/CcspCommonLibrary/scripts/cosa?r=818de962) manually that includes all the ccsp components and TDK Component.<br /> 2.TDK Agent should be in running state or invoke it through [StartTDK.sh](https://gerrit.teamccp.com/plugins/gitiles/rdk/rdkb/components/generic/tdkb/devices/tch/tch_cbr/+/stable2/agent/scripts/StartTDK.sh) script.<br /> 3. Connect a wifi client to 2.4GHz private AP|INT apIndex,<br /> wifi_associated_dev3_t **associated_dev_array,<br />UINT *output_array_size|INT<br />The HAL API wifi_getRMCapabilities() with 2.4GHz connected client MAC address should be invoked successfully and the RM Capabilities values retrieved should be valid and non-empty.|Hardware,Broadband|TS_WIFIHAL_2.4GHzGetRMCapabilities|TC_WIFIHAL_759|Invoke the HAL API wifi_getRMCapabilities() with 2.4GHz connected client MAC address and check if the RM Capabilities values retrieved are valid and non-empty.|V3:Required since same function wifi_getApAssociatedDeviceDiagnosticResult3() available in the TDK test suite|
|[#336](#original-spreadsheet-link)|wifi_getApAssociatedDeviceDiagnosticResult3() - This test script is to find the AP associated device details of 5GHz using wifi_getApAssociatedDeviceDiagnosticResult3()|1.Ccsp Components  should be in a running state else invoke [cosa_start.sh](https://rdkopengrok.stb.r53.xcal.tv/source/xref/txb7_stable2/generic/CcspCommonLibrary/scripts/cosa?r=818de962) manually that includes all the ccsp components and TDK Component.<br />2.TDK Agent should be in running state or invoke it Through [StartTDK.sh](https://gerrit.teamccp.com/plugins/gitiles/rdk/rdkb/components/generic/tdkb/devices/tch/tch_cbr/+/stable2/agent/scripts/StartTDK.sh) script|INT apIndex,<br /> wifi_associated_dev3_t **associated_dev_array,<br />UINT *output_array_size|INT<br />It should return output_array_size, which will give the no associated device.|Hardware,Broadband|TS_WIFIHAL_5GHzGetApAssociatedDeviceDiagnosticResult3|TC_WIFIHAL_352|This test script is to find the AP associated device details of 5GHz using wifi_getApAssociatedDeviceDiagnosticResult3()|V3:Required, since wifi_getApAssociatedDeviceDiagnosticResult3() available in TDK test suite.|
|[#748](#original-spreadsheet-link)|Invoke the HAL API wifi_getApAssociatedClientDiagnosticResult() with the connected client MAC address and check if the client diagnostic results are retrieved successfully for 2.4GHz Private AP.|1.Ccsp Components  should be in a running state else invoke [cosa_start.sh](https://rdkopengrok.stb.r53.xcal.tv/source/xref/txb7_stable2/generic/CcspCommonLibrary/scripts/cosa?r=818de962) manually that includes all the ccsp components and TDK Component. <br />2.TDK Agent should be in running state or invoke it Through [StartTDK.sh](https://gerrit.teamccp.com/plugins/gitiles/rdk/rdkb/components/generic/tdkb/devices/tch/tch_cbr/+/stable2/agent/scripts/StartTDK.sh) script. <br />3.Connect a wifi client to 2.4GHz private AP.|INT apIndex, mac_address_t mac_addr, wifi_associated_dev3_t *dev_conn|INT<br />The HAL API wifi_getApAssociatedClientDiagnosticResult() with the connected client MAC address should be invoked successfully and the client diagnostic results should be retrieved for 2.4GHz Private AP.|Hardware,Broadband|TS_WIFIHAL_2.4GHzGetApAssociatedClientDiagnosticResult|TC_WIFIHAL_737|Invoke the HAL API wifi_getApAssociatedClientDiagnosticResult() with the connected client MAC address and check if the client diagnostic results are retrieved successfully for 2.4GHz Private AP.|V3:Required since same function wifi_getApAssociatedClientDiagnosticResult() available in the TDK test suite|
|[#749](#original-spreadsheet-link)|Invoke the HAL API wifi_getApAssociatedClientDiagnosticResult() with the connected client MAC address and check if the client diagnostic results are retrieved successfully for 5GHz Private AP.|1.Ccsp Components  should be in a running state else invoke [cosa_start.sh](https://rdkopengrok.stb.r53.xcal.tv/source/xref/txb7_stable2/generic/CcspCommonLibrary/scripts/cosa?r=818de962) manually that includes all the ccsp components and TDK Component. <br />2.TDK Agent should be in running state or invoke it Through [StartTDK.sh](https://gerrit.teamccp.com/plugins/gitiles/rdk/rdkb/components/generic/tdkb/devices/tch/tch_cbr/+/stable2/agent/scripts/StartTDK.sh) script. <br />3.Connect a wifi client to 5GHz private AP.|INT apIndex,<br />mac_address_t mac_addr,<br />wifi_associated_dev3_t *dev_conn|INT<br /> The HAL API wifi_getApAssociatedClientDiagnosticResult() with the connected client MAC address should be invoked successfully and the client diagnostic results should be retrieved for 5GHz Private AP.|Hardware,Broadband|TS_WIFIHAL_5GHzGetApAssociatedClientDiagnosticResult|TC_WIFIHAL_738|Invoke the HAL API wifi_getApAssociatedClientDiagnosticResult() with the connected client MAC address and check if the client diagnostic results are retrieved successfully for 5GHz Private AP.|V3:Required since same function wifi_getApAssociatedClientDiagnosticResult() available in the TDK test suite|
|[#276](#original-spreadsheet-link)|wifi_getApAssociatedDeviceDiagnosticResult() - To get the Ap Associated Device Diagnostic Result for 2.4GHz|1.Ccsp Components  should be in a running state else invoke [cosa_start.sh]((https://rdkopengrok.stb.r53.xcal.tv/source/xref/txb7_stable2/generic/CcspCommonLibrary/scripts/cosa?r=818de962)) manually that includes all the ccsp components and TDK Component.<br /> 2.TDK Agent should be in running state or invoke it through [StartTDK.sh](https://gerrit.teamccp.com/plugins/gitiles/rdk/rdkb/components/generic/tdkb/devices/tch/tch_cbr/+/stable2/agent/scripts/StartTDK.sh) script.<br /> 3.Connect a 2.4GHz wifi client|INT apIndex,<br />wifi_associated_dev3_t **associated_dev_array,<br />UINT *output_array_size|INT<br />Should detect and return the neighboring access points and the diagnostic results|Hardware, Broadband, Emulator, RPI|TS_WIFIHAL_2.4GHzGetApAssociatedDeviceDiagnosticResult|TC_WIFIHAL_295|To get the Ap Associated Device Diagnostic Result for 2.4GHz|V3:Required,wifi_getApAssociatedDeviceDiagnosticResult() available in TDKB test suite|
|[#277](#original-spreadsheet-link)|wifi_getApAssociatedDeviceDiagnosticResult() - To get the Ap Associated Device Diagnostic Result for 5GHz|1.Ccsp Components  should be in a running state else invoke [cosa_start.sh](https://rdkopengrok.stb.r53.xcal.tv/source/xref/txb7_stable2/generic/CcspCommonLibrary/scripts/cosa?r=818de962) manually that includes all the ccsp components and TDK Component.<br /> 2.TDK Agent should be in running state or invoke it through [StartTDK.sh](https://gerrit.teamccp.com/plugins/gitiles/rdk/rdkb/components/generic/tdkb/devices/tch/tch_cbr/+/stable2/agent/scripts/StartTDK.sh) script.<br /> 3. Connect a 5GHz client to the DUT|INT apIndex,<br />wifi_associated_dev3_t **associated_dev_array,<br />UINT *output_array_size|INT<br />Should detect and return the neighboring access points and the diagnostic results|Hardware, Broadband, Emulator, RPI|TS_WIFIHAL_5GHzGetApAssociatedDeviceDiagnosticResult|TC_WIFIHAL_296|To get the Ap Associated Device Diagnostic Result for 5GHz|V3:Required,wifi_getApAssociatedDeviceDiagnosticResult() available in TDKB test suite|
|[#513](#original-spreadsheet-link)|wifi_getNeighboringWiFiDiagnosticResult2() - To validate the filter  mode WIFI_SCANFILTER_MODE_ENABLED using WiFi HAL API wifi_setApScanFilter for 2.4GHz AccessPoint|1.DUT should have some neighboring APs with valid SSID names.<br /> 2. Ccsp Components  should be in a running state else invoke [cosa_start.sh](https://rdkopengrok.stb.r53.xcal.tv/source/xref/txb7_stable2/generic/CcspCommonLibrary/scripts/cosa?r=818de962) manually that includes all the ccsp components and TDK Component.<br /> 3.TDK Agent should be in running state or invoke it through [StartTDK.sh](https://gerrit.teamccp.com/plugins/gitiles/rdk/rdkb/components/generic/tdkb/devices/tch/tch_cbr/+/stable2/agent/scripts/StartTDK.sh) script|INT radioIndex,<br />wifi_neighbor_ap2_t **neighbor_ap_array,<br />UINT *output_array_size|INT<br />On setting filter  mode as WIFI_SCANFILTER_MODE_ENABLED, only the SSID name set in filter should come up in further neighbor Ap scan result|Hardware,Broadcast|TS_WIFIHAL_2.4GHz_SetApScanFiltermode_Enabled|TC_WIFIHAL_411|To validate the filter  mode WIFI_SCANFILTER_MODE_ENABLED using WiFi HAL API wifi_setApScanFilter for 2.4GHz AccessPoint|V3:Unclear, we need to review this if we can use this TEST for wifi_startScan() API.Currently it is for wifi_getNeighboringWiFiDiagnosticResult2()|
|[#519](#original-spreadsheet-link)|wifi_getNeighboringWiFiDiagnosticResult2() - To validate the filter  mode WIFI_SCANFILTER_MODE_ENABLED using WiFi HAL API wifi_setApScanFilter for 5GHz AccessPoint|1.DUT should have some neighboring APs with valid SSID names.<br /> 2. Ccsp Components  should be in a running state else invoke [cosa_start.sh](https://rdkopengrok.stb.r53.xcal.tv/source/xref/txb7_stable2/generic/CcspCommonLibrary/scripts/cosa?r=818de962) manually that includes all the ccsp components and TDK Component.<br /> 3.TDK Agent should be in running state or invoke it through [StartTDK.sh](https://gerrit.teamccp.com/plugins/gitiles/rdk/rdkb/components/generic/tdkb/devices/tch/tch_cbr/+/stable2/agent/scripts/StartTDK.sh) script|INT radioIndex,<br />wifi_neighbor_ap2_t **neighbor_ap_array,<br />UINT *output_array_size|INT<br />On setting filter  mode as WIFI_SCANFILTER_MODE_ENABLED, only the SSID name set in filter should come up in further neighbor Ap scan result|Hardware,Broacast|TS_WIFIHAL_5GHz_SetApScanFiltermode_Enabled|TC_WIFIHAL_413|To validate the filter  mode WIFI_SCANFILTER_MODE_ENABLED using WiFi HAL API wifi_setApScanFilter for 5GHz AccessPoint|V3:Unclear, we need to review this if we can use this TEST for wifi_startScan() API.Currently it is for wifi_getNeighboringWiFiDiagnosticResult2()|
|[#836](#original-spreadsheet-link)|Verify the kick functionality using wifi_kickAssociatedDevice() for 2.4GHz|1.DUT should be connected with a WiFi client. <br />2. Ccsp Components  should be in a running state else invoke [cosa_start.sh](https://rdkopengrok.stb.r53.xcal.tv/source/xref/txb7_stable2/generic/CcspCommonLibrary/scripts/cosa?r=818de962) manually that includes all the ccsp components and TDK Component.<br /> 3.TDK Agent should be in running state or invoke it through [StartTDK.sh](https://gerrit.teamccp.com/plugins/gitiles/rdk/rdkb/components/generic/tdkb/devices/tch/tch_cbr/+/stable2/agent/scripts/StartTDK.sh) scrip|INT apIndex,<br />wifi_device_t *device|INT<br />wifi_kickAssociatedDevice() should successfully disconnect WiFi connection to the specified MAC |Hardware,Broadband|TS_WIFIHAL_2.4GHzKickAssociatedDevice|TC_WIFIHAL_287|Verify the kick functionality using wifi_kickAssociatedDevice()|V3:Required, since wifi_kickAssociatedDevice() available in TDK test suite.|
|[#394](#original-spreadsheet-link)|Verify the kick functionality using wifi_kickAssociatedDevice() for 5GHz|1.DUT should be connected with a WiFi client.<br /> 2. Ccsp Components  should be in a running state else invoke [cosa_start.sh](https://rdkopengrok.stb.r53.xcal.tv/source/xref/txb7_stable2/generic/CcspCommonLibrary/scripts/cosa?r=818de962) manually that includes all the ccsp components and TDK Component.<br /> 3.TDK Agent should be in running state or invoke it through [StartTDK.sh](https://gerrit.teamccp.com/plugins/gitiles/rdk/rdkb/components/generic/tdkb/devices/tch/tch_cbr/+/stable2/agent/scripts/StartTDK.sh) scrip.|INT apIndex,<br />wifi_device_t *device|INT<br />wifi_kickAssociatedDevice() should successfully disconnect WiFi connection to the specified MAC |Hardware,Broadband|TS_WIFIHAL_5GHzKickAssociatedDevice|TC_WIFIHAL_288|Verify the kick functionality using wifi_kickAssociatedDevice()|V3:Required, since wifi_kickAssociatedDevice() available in TDK test suite.|
|[#589](#original-spreadsheet-link)|Invoke the HAL API wifi_enableCSIEngine() to enable the CSI monitoring for the connected client and then disable CSI monitoring. In both cases check if the frame info is retrieved as expected for 2.4GHz|1.Ccsp Components  should be in a running state else invoke [cosa_start.sh](https://rdkopengrok.stb.r53.xcal.tv/source/xref/txb7_stable2/generic/CcspCommonLibrary/scripts/cosa?r=818de962) manually that includes all the ccsp components and TDK Component.<br /> 2.TDK Agent should be in running state or invoke it through [StartTDK.sh](https://gerrit.teamccp.com/plugins/gitiles/rdk/rdkb/components/generic/tdkb/devices/tch/tch_cbr/+/stable2/agent/scripts/StartTDK.sh) script.<br /> 3.Connect a wifi client to 2.4GHz radio|INT apIndex,<br /> mac_address_t sta,<br />BOOL enable|INT<br />Invocation of the HAP API wifi_enableCSIEngine() to enable the CSI monitoring for the connected client and then to disable CSI monitoring should be success. In both cases the frame info should be retrieved as expected.|Hardware,  Broadband|TS_WIFIHAL_2.4GHzEnableCSIEngine_DisableWithClientMAC|TC_WIFIHAL_583|Invoke the HAL API wifi_enableCSIEngine() to enable the CSI monitoring for the connected client and then disable CSI monitoring. In both cases check if the frame info is retrieved as expected|V3:Unclear, we need to review this if we can use this TEST for wifi_enableCSIEngine() API.|
|[#590](#original-spreadsheet-link)|Invoke the HAL API wifi_enableCSIEngine() to enable the CSI monitoring for the connected client and then disable CSI monitoring. In both cases check if the frame info is retrieved as expected for 5GHz|1.Ccsp Components  should be in a running state else invoke [cosa_start.sh](https://rdkopengrok.stb.r53.xcal.tv/source/xref/txb7_stable2/generic/CcspCommonLibrary/scripts/cosa?r=818de962) manually that includes all the ccsp components and TDK Component.<br /> 2.TDK Agent should be in running state or invoke it through [StartTDK.sh](https://gerrit.teamccp.com/plugins/gitiles/rdk/rdkb/components/generic/tdkb/devices/tch/tch_cbr/+/stable2/agent/scripts/StartTDK.sh) script.<br /> 3.Connect a wifi client to 5GHz radio|INT apIndex,<br />mac_address_t sta,<br />BOOL enable|INT<br />Invocation of the HAP API wifi_enableCSIEngine() to enable the CSI monitoring for the connected client and then to disable CSI monitoring should be success. In both cases the frame info should be retrieved as expected.|Harware, Broadband|TS_WIFIHAL_5GHzEnableCSIEngine_DisableWithClientMAC|TC_WIFIHAL_584|Invoke the HAL API wifi_enableCSIEngine() to enable the CSI monitoring for the connected client and then disable CSI monitoring. In both cases check if the frame info is retrieved as expected|V3:Unclear, we need to review this if we can use this TEST for wifi_enableCSIEngine() API.|
|[#591](#original-spreadsheet-link)|Invoke the HAL API wifi_enableCSIEngine() to enable the CSI monitoring for the connected client and then disable CSI monitoring for all using the MAC "00:00:00:00:00:00". In both cases check if the frame info is retrieved as expected for 2.4GHz|1.Ccsp Components  should be in a running state else invoke [cosa_start.sh](https://rdkopengrok.stb.r53.xcal.tv/source/xref/txb7_stable2/generic/CcspCommonLibrary/scripts/cosa?r=818de962) manually that includes all the ccsp components and TDK Component.<br /> 2.TDK Agent should be in running state or invoke it through [StartTDK.sh](https://gerrit.teamccp.com/plugins/gitiles/rdk/rdkb/components/generic/tdkb/devices/tch/tch_cbr/+/stable2/agent/scripts/StartTDK.sh) script.<br /> 3.Connect a wifi client to 2.4GHz radio.|INT apIndex,<br />mac_address_t sta,<br />BOOL enable|INT<br />Invocation of the HAP API wifi_enableCSIEngine() to enable the CSI monitoring for the connected client and then to disable CSI monitoring by passing the MAC : "00:00:00:00:00:00" should be success. In both cases the frame info should be retrieved as expected.|Hardware, Broadband|TS_WIFIHAL_2.4GHzEnableCSIEngine_DisableAll|TC_WIFIHAL_585|Invoke the HAL API wifi_enableCSIEngine() to enable the CSI monitoring for the connected client and then disable CSI monitoring for all using the MAC "00:00:00:00:00:00". In both cases check if the frame info is retrieved as expected|V3:Unclear, we need to review this if we can use this TEST for wifi_enableCSIEngine() API.|
|[#592](#original-spreadsheet-link)|Enable CSI monitoring for an invalid MAC address(no connected client) by invoking wifi_enableCSIEngine() and check if the CSI frame info is not retrieved for the invalid MAC for 5GHz.|1.Ccsp Components  should be in a running state else invoke [cosa_start.sh](https://rdkopengrok.stb.r53.xcal.tv/source/xref/txb7_stable2/generic/CcspCommonLibrary/scripts/cosa?r=818de962) manually that includes all the ccsp components and TDK Component.<br /> 2.TDK Agent should be in running state or invoke it through [StartTDK.sh](https://gerrit.teamccp.com/plugins/gitiles/rdk/rdkb/components/generic/tdkb/devices/tch/tch_cbr/+/stable2/agent/scripts/StartTDK.sh) script|INT apIndex,<br />mac_address_t sta,<br />BOOL enable|INT<br />Invocation of the HAP API wifi_enableCSIEngine() to enable the CSI monitoring for the connected client and then to disable CSI monitoring by passing the MAC : "00:00:00:00:00:00" should be success. In both cases the frame info should be retrieved as expected.|Hardware,Broadband|TS_WIFIHAL_5GHzEnableCSIEngine_DisableAll|TC_WIFIHAL_586|Invoke the HAL API wifi_enableCSIEngine() to enable the CSI monitoring for the connected client and then disable CSI monitoring for all using the MAC "00:00:00:00:00:00". In both cases check if the frame info is retrieved as expected|V3:Unclear, we need to review this if we can use this TEST for wifi_enableCSIEngine() API.|