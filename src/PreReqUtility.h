/*
##########################################################################
# If not stated otherwise in this file or this component's Licenses.txt
# file the following copyright and licenses apply:
#
# Copyright 2022 RDK Management
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
##########################################################################
*/

#ifndef PRE_REQ_UTILITY_H
#define PRE_REQ_UTILITY_H

#include <stdio.h>
#include "test_utils.h"

/**function to perform WiFi initialization
*IN : None
*OUT : returns success or failure status of WiFi initialization
**/
int WiFiPreReq( void);

/**function to create private access points
* IN  : radioIndex for which private AP index needs to be created
* IN  : AP index
* IN  : Type of AP index (eg : Private, Sta)
* OUT : returns success or failure status of AP creation
**/
int createVAP(int radioIndex, int apIndex, APTYPE type);

#endif /* PRE_REQ_UTILITY_H */
