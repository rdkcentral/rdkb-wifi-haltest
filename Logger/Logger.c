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

/* System Includes */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* Application Includes */
#include "Logger.h"

void LOG (const char *message, const char *function, int line)
{
    char details[MAX_BUFFER_SIZE] = { '\0' };
    char logMessage[MAX_BUFFER_SIZE] = { '\0' };
    char time_now[20] = { '\0' };
    FILE *fp = NULL;
    time_t now ;
    time(&now);
    struct tm *tmp ;
    tmp = localtime(&now);
    strftime(time_now, sizeof(time_now), "%Y-%m-%d-%X", tmp);

    fp = fopen (LOG_PATH, "a");
    if (fp)
    {
        sprintf (details, "3PE [%s] [%s] [%d] : ", time_now, function, line);
        strcat (logMessage, details);
        strcat (logMessage, message);
        fprintf (fp, "%s\n", logMessage);
    }

    fclose (fp);
    fp = NULL;
}
