/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2023 RDK Management
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
*/

#include <ut.h>
#include "PreReqUtility.h"
#include "test_utils.h"

extern int register_hal_l1_tests( void );
extern int register_hal_l2_tests( void );
wifi_radio_operationParam_t g_operationParam[3];
wifi_vap_info_map_t g_org_map[3];

int main(int argc, char** argv) 
{
    int registerReturn = 0;
    int preReqReturn = 0;

    /* Register tests as required, then call the UT-main to support switches and triggering */
    UT_init( argc, argv );

    /* Check if tests are registered successfully */
    registerReturn = register_hal_l1_tests();
    if (registerReturn == 0)
    {
        printf("\nregister_hal_l1_tests() returned success");
    }
    else
    {
        printf("\nregister_hal_l1_tests() returned failure");
        return 1;
    }

    /* TODO : Can explore the possibility of doing initialization using CU_InitializeFunc and CU_add_suite */
    /* WiFi Initialization */
    preReqReturn = WiFiPreReq();
    printf("\nWiFi Pre-Requisite routine returns : %d", preReqReturn);
    if (preReqReturn == 0)
    {
        printf("\nWiFi Pre-Requisite set successfully");
    }
    else
    {
        printf("\nWiFi Pre-Requisite not set successfully");
    }

    registerReturn = register_hal_l2_tests();
    if (registerReturn == 0)
    {
        printf("\nregister_hal_l2_tests() returned success");
    }
    else
    {
        printf("\nregister_hal_l2_tests() returned failure");
        return 1;
    }

    preReqReturn = l2_test_prerequisite();
    printf("\nL2 Pre-Requisite returns : %d", preReqReturn);
    if (preReqReturn == 0)
    {
        printf("\nL2 Pre-Requisite set successfully");
    }
    else
    {
        printf("\nL2 Pre-Requisite not set successfully");
    }    
    /* Begin test executions */
    UT_run_tests();

    return 0;

}
