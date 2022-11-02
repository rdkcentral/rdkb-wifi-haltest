/*
 * If not stated otherwise in this file or this component's LICENSE file the
 * following copyright and licenses apply:
 *
 * Copyright 2016 RDK Management
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

#include <stdio.h>
#include <string.h>
#include "config_parser.h"

#define RADIO_CONFIG "radio_config"
#define VAP_CONFIG "vap_config"
//#define TEST_DIR_PATH "../config/"
#define TEST_DIR_PATH "./"
#define MIN_NUM_RADIOS 1
#define RET_OK 0
#define RET_ERR -1

//macros to check the validity of cjon objects
#define DECODE_CHECKS
#define decode_param_string(json, key, value) \
{   \
    value = cJSON_GetObjectItem(json, key);     \
    if ((value == NULL) || (cJSON_IsString(value) == FALSE) ||  \
            (value->valuestring == NULL) || (strcmp(value->valuestring, "") == 0)) {    \
        printf("%s:%d: Validation failed for key:%s\n", __func__, __LINE__, key);   \
        goto cleanup;  \
    }   \
}   
#define decode_param_integer(json, key, value) \
{   \
    value = cJSON_GetObjectItem(json, key);     \
    if ((value == NULL) || (cJSON_IsNumber(value) == FALSE)) {  \
        printf("%s:%d: Validation failed for key:%s\n", __func__, __LINE__, key);   \
        goto cleanup;  \
    }   \
}  

#define decode_param_bool(json, key, value) \
{   \
    value = cJSON_GetObjectItem(json, key);     \
    if ((value == NULL) || (cJSON_IsBool(value) == FALSE)) {    \
        printf("%s:%d: Validation failed for key:%s\n", __func__, __LINE__, key);   \
        goto cleanup;  \
    }   \
} 

#define decode_param_object(json, key, value) \
{   \
    value = cJSON_GetObjectItem(json, key);     \
    if ((value == NULL) || (cJSON_IsObject(value) == FALSE)) {  \
        printf("%s:%d: Validation failed for key:%s\n", __func__, __LINE__, key);   \
        goto cleanup;  \
    }   \
}

/**function to read the json config file and return its content as a string
*IN : json file name
*OUT : content of json file as string
**/
char* read_file(const char *filename) {
    FILE *file = NULL;
    long length = 0;
    char *content = NULL;
    size_t read_chars = 0;

    /* open in read binary mode */
    file = fopen(filename, "rb");
    if (file == NULL)
    {
        goto cleanup;
    }

    /* get the length */
    if (fseek(file, 0, SEEK_END) != 0)
    {
        goto cleanup;
    }
    length = ftell(file);
    if (length < 0)
    {
        goto cleanup;
    }
    if (fseek(file, 0, SEEK_SET) != 0)
    {
        goto cleanup;
    }

    /* allocate content buffer */
    content = (char*)malloc((size_t)length + sizeof(""));
    if (content == NULL)
    {
        goto cleanup;
    }

    /* read the file into memory */
    read_chars = fread(content, sizeof(char), (size_t)length, file);
    if ((long)read_chars != length)
    {
        free(content);
        content = NULL;
        goto cleanup;
    }
    content[read_chars] = '\0';


cleanup:
    if (file != NULL)
    {
        fclose(file);
    }

    return content;
}

/**function to read the json config file and return its content as a json object
*IN : json file name
*OUT : content of json file as a json object
**/
static cJSON *parse_file(const char *filename)
{
    cJSON *parsed = NULL;
    char *content = read_file(filename);

    parsed = cJSON_Parse(content);

    if (content != NULL)
    {
        free(content);
    }

    return parsed;
}

/**function to read the json config file and return its content as a json object
*IN : json file name
*OUT : content of json file as a json object
**/
cJSON * config_to_json(const char *test_name)
{
    char *actual = NULL;
    cJSON *tree = NULL;

    size_t test_name_length = 0;
    char *test_path = NULL;

    test_name_length = strlen(test_name);

    test_path = (char*)malloc(sizeof(TEST_DIR_PATH) + test_name_length);
    sprintf(test_path, TEST_DIR_PATH"%s", test_name);

    tree = parse_file(test_path);

    if (actual != NULL)
    {
        free(actual);
    }
    if (test_path != NULL)
    {
        free(test_path);
    }
    return tree;
}

/**function to read the radio configuration from json config file
*IN : radio index
*IN : radio_info - the buffer to hold radio config
*OUT : returns success or failure status of the operation
**/
int get_radio_config(int index, wifi_radio_operationParam_t *radio_info)
{
    cJSON *obj_radios = NULL;
    cJSON *json = NULL;
    cJSON *obj_radio = NULL;
    cJSON  *param = NULL;
    char *ptr, *tmp;
    unsigned int num_of_channel = 0;
    int ret = RET_ERR;

    //convert json config file to json object
    json = config_to_json(RADIO_CONFIG);
    if (json==NULL)
    {
        printf("Failed to parse config\n");
        return RET_ERR;
    }
    obj_radios = cJSON_GetObjectItem(json, "WifiRadioConfig");
    if (!cJSON_IsArray(obj_radios) || cJSON_GetArraySize(obj_radios) < MIN_NUM_RADIOS || cJSON_GetArraySize(obj_radios) > MAX_NUM_RADIOS)
    {
        printf("Radio object not present or incorrect number of radio objects\n");
        cJSON_Delete(json);
        return RET_ERR;
    }
    cJSON_ArrayForEach(obj_radio, obj_radios)
    {
        param = cJSON_GetObjectItem(obj_radio, "RadioIndex");
        if(param && (cJSON_IsNumber(param)) && param->valueint == index)
        {
            // Enabled
            decode_param_bool(obj_radio, "Enabled", param);
            radio_info->enable = (param->type & cJSON_True) ?TRUE:FALSE;
            // AutoChannelEnabled
            decode_param_bool(obj_radio, "AutoChannelEnabled", param);
            radio_info->autoChannelEnabled = (param->type & cJSON_True) ? TRUE:FALSE;
            // FreqBand
            decode_param_integer(obj_radio, "FreqBand", param);
            radio_info->band = param->valuedouble;
            // Channel
            decode_param_integer(obj_radio, "Channel", param);
            radio_info->channel = param->valuedouble;
            // NumSecondaryChannels
            decode_param_integer(obj_radio, "NumSecondaryChannels", param);
            radio_info->numSecondaryChannels = param->valuedouble;
            if  (radio_info->numSecondaryChannels > 0) {
                //SecondaryChannelsList
                decode_param_string(obj_radio, "SecondaryChannelsList",param);
                ptr = param->valuestring;
                tmp = param->valuestring;
                while ((ptr = strchr(tmp, ',')) != NULL) {
                    ptr++;
                    radio_info->channelSecondary[num_of_channel] = atoi(tmp);
                    tmp = ptr;
                    num_of_channel++;
                }
                // Last channel
                radio_info->channelSecondary[num_of_channel++] = atoi(tmp);
            }

            // ChannelWidth
            decode_param_integer(obj_radio, "ChannelWidth", param);
            radio_info->channelWidth = param->valuedouble;

            // HwMode
            decode_param_integer(obj_radio, "HwMode", param);
            radio_info->variant = param->valuedouble;

            // CsaBeaconCount
            decode_param_integer(obj_radio, "CsaBeaconCount", param);
            radio_info->csa_beacon_count = param->valuedouble;

            // Country
            decode_param_string(obj_radio, "Country", param);
            radio_info->countryCode = wifi_countrycode_US; //need enhancement, can pass enum no: from config

            // DcsEnabled
            decode_param_bool(obj_radio, "DcsEnabled", param);
            radio_info->DCSEnabled = (param->type & cJSON_True) ?TRUE:FALSE;

            // DtimPeriod
            decode_param_integer(obj_radio, "DtimPeriod", param);
            radio_info->dtimPeriod = param->valuedouble;
            // BeaconInterval
            decode_param_integer(obj_radio, "BeaconInterval", param);
            radio_info->beaconInterval = param->valuedouble;
            // OperatingClass
            decode_param_integer(obj_radio, "OperatingClass", param);
            radio_info->operatingClass = param->valuedouble;
            // BasicDataTransmitRates
            decode_param_integer(obj_radio, "BasicDataTransmitRates", param);
            radio_info->basicDataTransmitRates = param->valuedouble;
            // OperationalDataTransmitRates
            decode_param_integer(obj_radio, "OperationalDataTransmitRates", param);
            radio_info->operationalDataTransmitRates = param->valuedouble;
            // FragmentationThreshold
            decode_param_integer(obj_radio, "FragmentationThreshold", param);
            radio_info->fragmentationThreshold = param->valuedouble;
            // GuardInterval
            decode_param_integer(obj_radio, "GuardInterval", param);
            radio_info->guardInterval = param->valuedouble;
            // TransmitPower
            decode_param_integer(obj_radio, "TransmitPower", param);
            radio_info->transmitPower = param->valuedouble;
            // RtsThreshold
            decode_param_integer(obj_radio, "RtsThreshold", param);
            radio_info->rtsThreshold = param->valuedouble;
            // FactoryResetSsid
            decode_param_bool(obj_radio, "FactoryResetSsid", param);
            radio_info->factoryResetSsid = (param->type & cJSON_True) ?TRUE:FALSE;
            // RadioStatsMeasuringRate
            decode_param_integer(obj_radio, "RadioStatsMeasuringRate", param);
            radio_info->radioStatsMeasuringRate = param->valuedouble;
            // RadioStatsMeasuringInterval
            decode_param_integer(obj_radio, "RadioStatsMeasuringInterval", param);
            radio_info->radioStatsMeasuringInterval = param->valuedouble;
            // CtsProtection
            decode_param_bool(obj_radio, "CtsProtection", param);
            radio_info->ctsProtection = (param->type & cJSON_True) ?TRUE:FALSE;
            // ObssCoex
            decode_param_bool(obj_radio, "ObssCoex", param);
            radio_info->obssCoex = (param->type & cJSON_True) ?TRUE:FALSE;
            // StbcEnable
            decode_param_bool(obj_radio, "StbcEnable", param);
            radio_info->stbcEnable = (param->type & cJSON_True) ?TRUE:FALSE;
            // GreenFieldEnable
            decode_param_bool(obj_radio, "GreenFieldEnable", param);
            radio_info->greenFieldEnable = (param->type & cJSON_True) ?TRUE:FALSE;
            // UserControl
            decode_param_integer(obj_radio, "UserControl", param);
            radio_info->userControl = param->valuedouble;
            // AdminControl
            decode_param_integer(obj_radio, "AdminControl", param);
            radio_info->adminControl = param->valuedouble;
            // ChanUtilThreshold
            decode_param_integer(obj_radio, "ChanUtilThreshold", param);
            radio_info->chanUtilThreshold = param->valuedouble;
            // ChanUtilSelfHealEnable
            decode_param_bool(obj_radio, "ChanUtilSelfHealEnable", param);
            radio_info->chanUtilSelfHealEnable = (param->type & cJSON_True) ?TRUE:FALSE;

            ret = RET_OK;
            break;
        }
    }

    cleanup:        
        cJSON_Delete(json);
    return ret;
}
