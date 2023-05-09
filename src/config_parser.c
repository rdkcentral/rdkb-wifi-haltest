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

#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include "config_parser.h"
#include "cJSON.h"

#define RADIO_CONFIG "radio_config"
#define VAP_CONFIG "vap_config"
//#define TEST_DIR_PATH "../config/"
#define TEST_DIR_PATH "./"
#define MIN_NUM_RADIOS 1
#define RET_OK 0
#define RET_ERR -1

//utils to check the validity of cjon objects
static int decode_param_string(cJSON  *json, char *key, cJSON  **value)
{   
    *value = cJSON_GetObjectItem(json, key);     
    if ((*value == NULL) || (cJSON_IsString(*value) == FALSE) ||  
            ((*value)->valuestring == NULL) || (strcmp((*value)->valuestring, "") == 0)) {    
        printf("%s:%d: Validation failed for key:%s\n", __func__, __LINE__, key);   
        return RET_ERR;
    }
    return RET_OK;
}   
static int decode_param_integer(cJSON  *json, char *key, cJSON  **value)
{
    *value = cJSON_GetObjectItem(json, key);
    if ((*value == NULL) || (cJSON_IsNumber(*value) == FALSE)) {
        printf("%s:%d: Validation failed for key:%s\n", __func__, __LINE__, key);
        return RET_ERR;
    }
    return RET_OK;
}

static int decode_param_bool(cJSON  *json, char *key, cJSON  **value)
{
    *value = cJSON_GetObjectItem(json, key);
    if ((*value == NULL) || (cJSON_IsBool(*value) == FALSE)) {
        printf("%s:%d: Validation failed for key:%s\n", __func__, __LINE__, key);
        return RET_ERR;
    }
    return RET_OK;
}

static int decode_param_object(cJSON  *json, char *key, cJSON  **value)
{
    *value = cJSON_GetObjectItem(json, key);
    if ((*value == NULL) || (cJSON_IsObject(*value) == FALSE)) {
        printf("%s:%d: Validation failed for key:%s\n", __func__, __LINE__, key);
        return RET_ERR;
    }
    return RET_OK;
}

/**function to read the json config file and return its content as a string
*IN : json file name
*OUT : content of json file as string
**/
static char* read_file(const char *filename) {
    FILE *file = NULL;
    long length = 0;
    char *content = NULL;
    size_t read_chars = 0;

    /* open in read binary mode */
    file = fopen(filename, "rb");
    if (file != NULL)
    {
        /* get the length */
        if (fseek(file, 0, SEEK_END) == 0)
        {
            length = ftell(file);
            if (length > 0)
            {
                if (fseek(file, 0, SEEK_SET) == 0)
                {
                    /* allocate content buffer */
                    content = (char*)malloc((size_t)length + sizeof(""));
                    if (content != NULL)
                    {
                        /* read the file into memory */
                        read_chars = fread(content, sizeof(char), (size_t)length, file);
                        if ((long)read_chars != length)
                        {
                            free(content);
                            content = NULL;
                        }
                        else
                            content[read_chars] = '\0';
                    }
                }
            }
        }
    }

    fclose(file);

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
static cJSON * config_to_json(const char *test_name)
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
            if(decode_param_bool(obj_radio, "Enabled", &param))
                break;
            radio_info->enable = (param->type & cJSON_True) ?TRUE:FALSE;

            // AutoChannelEnabled
            if(decode_param_bool(obj_radio, "AutoChannelEnabled", &param))
                break;
            radio_info->autoChannelEnabled = (param->type & cJSON_True) ? TRUE:FALSE;

            // FreqBand
            if(decode_param_integer(obj_radio, "FreqBand", &param))
                break;
            radio_info->band = param->valuedouble;

            // Channel
            if(decode_param_integer(obj_radio, "Channel", &param))
                break;
            radio_info->channel = param->valuedouble;

            // NumSecondaryChannels
            if(decode_param_integer(obj_radio, "NumSecondaryChannels", &param))
                break;
            radio_info->numSecondaryChannels = param->valuedouble;
            if  (radio_info->numSecondaryChannels > 0) {
                //SecondaryChannelsList
                if(decode_param_string(obj_radio, "SecondaryChannelsList",&param))
                    break;
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
            if(decode_param_integer(obj_radio, "ChannelWidth", &param))
                break;
            radio_info->channelWidth = param->valuedouble;

            // HwMode
            if(decode_param_integer(obj_radio, "HwMode", &param))
                break;
            radio_info->variant = param->valuedouble;

            // CsaBeaconCount
            if(decode_param_integer(obj_radio, "CsaBeaconCount", &param))
                break;
            radio_info->csa_beacon_count = param->valuedouble;

            // Country
            if(decode_param_string(obj_radio, "Country", &param))
                break;
            radio_info->countryCode = wifi_countrycode_US; //need enhancement, can pass enum no: from config

            // DcsEnabled
            if(decode_param_bool(obj_radio, "DcsEnabled", &param))
                break;
            radio_info->DCSEnabled = (param->type & cJSON_True) ?TRUE:FALSE;

            // DtimPeriod
            if(decode_param_integer(obj_radio, "DtimPeriod", &param))
                break;
            radio_info->dtimPeriod = param->valuedouble;

            // BeaconInterval
            if(decode_param_integer(obj_radio, "BeaconInterval", &param))
                break;
            radio_info->beaconInterval = param->valuedouble;

            // OperatingClass
            if(decode_param_integer(obj_radio, "OperatingClass", &param))
                break;
            radio_info->operatingClass = param->valuedouble;

            // BasicDataTransmitRates
            if(decode_param_integer(obj_radio, "BasicDataTransmitRates", &param))
                break;
            radio_info->basicDataTransmitRates = param->valuedouble;

            // OperationalDataTransmitRates
            if(decode_param_integer(obj_radio, "OperationalDataTransmitRates", &param))
                break;
            radio_info->operationalDataTransmitRates = param->valuedouble;

            // FragmentationThreshold
            if(decode_param_integer(obj_radio, "FragmentationThreshold", &param))
                break;
            radio_info->fragmentationThreshold = param->valuedouble;

            // GuardInterval
            if(decode_param_integer(obj_radio, "GuardInterval", &param))
                break;
            radio_info->guardInterval = param->valuedouble;

            // TransmitPower
            if(decode_param_integer(obj_radio, "TransmitPower", &param))
                break;
            radio_info->transmitPower = param->valuedouble;

            // RtsThreshold
            if(decode_param_integer(obj_radio, "RtsThreshold", &param))
                break;
            radio_info->rtsThreshold = param->valuedouble;

            // FactoryResetSsid
            if(decode_param_bool(obj_radio, "FactoryResetSsid", &param))
                break;
            radio_info->factoryResetSsid = (param->type & cJSON_True) ?TRUE:FALSE;

            // RadioStatsMeasuringRate
            if(decode_param_integer(obj_radio, "RadioStatsMeasuringRate", &param))
                break;
            radio_info->radioStatsMeasuringRate = param->valuedouble;

            // RadioStatsMeasuringInterval
            if(decode_param_integer(obj_radio, "RadioStatsMeasuringInterval", &param))
                break;
            radio_info->radioStatsMeasuringInterval = param->valuedouble;

            // CtsProtection
            if(decode_param_bool(obj_radio, "CtsProtection", &param))
                break;
            radio_info->ctsProtection = (param->type & cJSON_True) ?TRUE:FALSE;

            // ObssCoex
            if(decode_param_bool(obj_radio, "ObssCoex", &param))
                break;
            radio_info->obssCoex = (param->type & cJSON_True) ?TRUE:FALSE;

            // StbcEnable
            if(decode_param_bool(obj_radio, "StbcEnable", &param))
                break;
            radio_info->stbcEnable = (param->type & cJSON_True) ?TRUE:FALSE;

            // GreenFieldEnable
            if(decode_param_bool(obj_radio, "GreenFieldEnable", &param))
                break;
            radio_info->greenFieldEnable = (param->type & cJSON_True) ?TRUE:FALSE;

            // UserControl
            if(decode_param_integer(obj_radio, "UserControl", &param))
                break;
            radio_info->userControl = param->valuedouble;

            // AdminControl
            if(decode_param_integer(obj_radio, "AdminControl", &param))
                break;
            radio_info->adminControl = param->valuedouble;

            // ChanUtilThreshold
            if(decode_param_integer(obj_radio, "ChanUtilThreshold", &param))
                break;
            radio_info->chanUtilThreshold = param->valuedouble;

            // ChanUtilSelfHealEnable
            if(decode_param_bool(obj_radio, "ChanUtilSelfHealEnable", &param))
                break;
            radio_info->chanUtilSelfHealEnable = (param->type & cJSON_True) ?TRUE:FALSE;

            printf("\nRadio config parsed successfully\n");
            cJSON_Delete(json);
            return RET_OK;
        }
    }

    cJSON_Delete(json);
    printf("Failed to parse radio config\n");
    return ret;
}

static int string_mac_to_uint8_mac(unsigned char *mac, char *s_mac)
{

    if((mac == NULL) || (s_mac == NULL))
    {
        printf("%s:%d:parameters is NULL\n", __func__, __LINE__);
        return RET_ERR;
    }
    sscanf(s_mac, "%02hhx:%02hhx:%02hhx:%02hhx:%02hhx:%02hhx", &mac[0], &mac[1], &mac[2],&mac[3], &mac[4], &mac[5]);
    return RET_OK;
}

static int decode_vap_common_object(cJSON *vap, wifi_vap_info_t *vap_info)
{
    cJSON  *param = NULL;

    //VAP Name
    if(decode_param_string(vap, "VapName", &param))
        return RET_ERR;
    strcpy(vap_info->vap_name, param->valuestring);

    // VAP Index
    if(decode_param_integer(vap, "VapIndex", &param))
        return RET_ERR;
    vap_info->vap_index = param->valuedouble;

    // Radio Index
    if(decode_param_integer(vap, "RadioIndex", &param))
        return RET_ERR;
    vap_info->radio_index = param->valuedouble;

    // VAP Mode
    if(decode_param_integer(vap, "VapMode", &param))
        return RET_ERR;
    vap_info->vap_mode = param->valuedouble;

    //Bridge Name
    if(decode_param_string(vap, "BridgeName", &param))
        return RET_ERR;
    strncpy(vap_info->bridge_name, param->valuestring,WIFI_BRIDGE_NAME_LEN-1);

    // SSID
    if(decode_param_string(vap, "SSID", &param))
        return RET_ERR;
    strcpy(vap_info->u.bss_info.ssid, param->valuestring);

    // BSSID : TBD whether to use in set
    /*if(decode_param_string(vap, "BSSID", &param))
    if((ret = string_mac_to_uint8_mac(vap_info->u.bss_info.bssid, param->valuestring)) == RET_ERR){
        printf("string_mac_to_uint8_mac FAILED\n");
        goto cleanup;}*/

    // Enabled
    if(decode_param_bool(vap, "Enabled", &param))
        return RET_ERR;
    vap_info->u.bss_info.enabled = (param->type & cJSON_True) ? TRUE:FALSE;

    // Broadcast SSID
    if(decode_param_bool(vap, "SSIDAdvertisementEnabled", &param))
        return RET_ERR;
    vap_info->u.bss_info.showSsid = (param->type & cJSON_True) ? TRUE:FALSE;

    // Isolation
    if(decode_param_bool(vap, "IsolationEnable", &param))
        return RET_ERR;
    vap_info->u.bss_info.isolation = (param->type & cJSON_True) ? TRUE:FALSE;

    // ManagementFramePowerControl
    if(decode_param_integer(vap, "ManagementFramePowerControl", &param))
        return RET_ERR;
    vap_info->u.bss_info.mgmtPowerControl = param->valuedouble;

    // BssMaxNumSta
    if(decode_param_integer(vap, "BssMaxNumSta", &param))
        return RET_ERR;
    vap_info->u.bss_info.bssMaxSta = param->valuedouble;

    // BSSTransitionActivated
    if(decode_param_bool(vap, "BSSTransitionActivated", &param))
        return RET_ERR;
    vap_info->u.bss_info.bssTransitionActivated = (param->type & cJSON_True) ? TRUE:FALSE;

    // NeighborReportActivated
    if(decode_param_bool(vap, "NeighborReportActivated", &param))
        return RET_ERR;
    vap_info->u.bss_info.nbrReportActivated = (param->type & cJSON_True) ? TRUE:FALSE;

    // NetworkGreyList --> to be confirmed, available in onewifi, but not in github
//    if(decode_param_bool(vap, "NetworkGreyList", &param))
//        return RET_ERR;
//    vap_info->u.bss_info.network_initiated_greylist = (param->type & cJSON_True) ? TRUE:FALSE;

    // RapidReconnCountEnable
/*    if(decode_param_bool(vap, "RapidReconnCountEnable", &param))
          return RET_ERR;
    vap_info->u.bss_info.rapidReconnectEnable = (param->type & cJSON_True) ? TRUE:FALSE;

    // RapidReconnThreshold
    if(decode_param_integer(vap, "RapidReconnThreshold", &param))
        return RET_ERR;
    vap_info->u.bss_info.rapidReconnThreshold = param->valuedouble;

    // VapStatsEnable
    if(decode_param_bool(vap, "VapStatsEnable", &param))
        return RET_ERR;
    vap_info->u.bss_info.vapStatsEnable = (param->type & cJSON_True) ? TRUE:FALSE;*/

    // MacFilterEnable
    if(decode_param_bool(vap, "MacFilterEnable", &param))
        return RET_ERR;
    vap_info->u.bss_info.mac_filter_enable = (param->type & cJSON_True) ? TRUE:FALSE;

    // MacFilterMode
    if(decode_param_integer(vap, "MacFilterMode", &param))
        return RET_ERR;
    vap_info->u.bss_info.mac_filter_mode = param->valuedouble;

    // WmmEnabled
    if(decode_param_bool(vap, "WmmEnabled", &param))
        return RET_ERR;
    vap_info->u.bss_info.wmm_enabled = (param->type & cJSON_True) ? TRUE:FALSE;

    //UapsdEnabled
    if(decode_param_bool(vap, "UapsdEnabled", &param))
        return RET_ERR;
    vap_info->u.bss_info.UAPSDEnabled = (param->type & cJSON_True) ? TRUE:FALSE;

    //BeaconRate
    if(decode_param_integer(vap, "BeaconRate", &param))
        return RET_ERR;
    vap_info->u.bss_info.beaconRate = param->valuedouble;

    // WmmNoAck
    if(decode_param_integer(vap, "WmmNoAck", &param))
        return RET_ERR;
    vap_info->u.bss_info.wmmNoAck = param->valuedouble;

    // WepKeyLength
    if(decode_param_integer(vap, "WepKeyLength", &param))
        return RET_ERR;
    vap_info->u.bss_info.wepKeyLength = param->valuedouble;

    // BssHotspot
    if(decode_param_bool(vap, "BssHotspot", &param))
        return RET_ERR;
    vap_info->u.bss_info.bssHotspot = (param->type & cJSON_True) ? TRUE:FALSE;

    // wpsPushButton
    if(decode_param_integer(vap, "WpsPushButton", &param))
        return RET_ERR;
    vap_info->u.bss_info.wpsPushButton = param->valuedouble;

    //wpsEnable
    if(decode_param_bool(vap, "WpsEnable", &param))
        return RET_ERR;
    vap_info->u.bss_info.wps.enable  = (param->type & cJSON_True) ? TRUE:FALSE;

    //wpsConfigMethodsEnabled
    if(strstr(vap_info->vap_name, "private") != NULL) {
        if(decode_param_integer(vap, "WpsConfigMethodsEnabled", &param))
            return RET_ERR;
        vap_info->u.bss_info.wps.methods = param->valuedouble;
    //wpsPin
    if(decode_param_string(vap, "WpsPin", &param))
        return RET_ERR;
    strncpy(vap_info->u.bss_info.wps.pin, param->valuestring, WIFI_AP_MAX_WPSPIN_LEN-1);
    }

    // BeaconRateCtl
    if(decode_param_string(vap, "BeaconRateCtl", &param))
        return RET_ERR;
    strcpy(vap_info->u.bss_info.beaconRateCtl, param->valuestring);

    return RET_OK;
}

static int decode_personal_security_object(cJSON *security, wifi_vap_security_t *security_info)
{
    cJSON *param = NULL;

    // MFPConfig
    if(decode_param_string(security, "MFPConfig", &param))
        return RET_ERR;
    if (strstr(param->valuestring, "Disabled")) {
        security_info->mfp = wifi_mfp_cfg_disabled;
    } else if (strstr(param->valuestring, "Required")) {
        security_info->mfp = wifi_mfp_cfg_required;
    } else if (strstr(param->valuestring, "Optional")) {
        security_info->mfp = wifi_mfp_cfg_optional;
    }
    else
        return RET_ERR;

    if(decode_param_string(security, "Mode", &param))
        return RET_ERR;
    if (strcmp(param->valuestring, "None") == 0) {
        security_info->mode = wifi_security_mode_none;
    } else if (strcmp(param->valuestring, "WPA-Personal") == 0) {
        security_info->mode = wifi_security_mode_wpa_personal;
    } else if (strcmp(param->valuestring, "WPA2-Personal") == 0) {
        security_info->mode = wifi_security_mode_wpa2_personal;
    } else if (strcmp(param->valuestring, "WPA-WPA2-Personal") == 0) {
        security_info->mode = wifi_security_mode_wpa_wpa2_personal;
    } else if (strcmp(param->valuestring, "WPA3-Personal") == 0) {
        security_info->mode = wifi_security_mode_wpa3_personal;
        security_info->u.key.type = wifi_security_key_type_sae;
    } else if (strcmp(param->valuestring, "WPA3-Personal-Transition") == 0) {
        security_info->mode = wifi_security_mode_wpa3_transition;
        security_info->u.key.type = wifi_security_key_type_psk_sae;
    } else
        return RET_ERR;

    if(decode_param_string(security, "EncryptionMethod", &param))
        return RET_ERR;
    if (strcmp(param->valuestring, "TKIP") == 0) {
        security_info->encr = wifi_encryption_tkip;
    } else if(strcmp(param->valuestring, "AES") == 0) {
        security_info->encr = wifi_encryption_aes;
    } else if(strcmp(param->valuestring, "AES+TKIP") == 0) {
        security_info->encr = wifi_encryption_aes_tkip;
    } else if(strcmp(param->valuestring, "None") == 0) {
        security_info->encr = wifi_encryption_none;
    } else
        return RET_ERR;

    if(decode_param_string(security, "Passphrase", &param))
        return RET_ERR;
    strncpy(security_info->u.key.key, param->valuestring,sizeof(security_info->u.key.key) - 1);

    return RET_OK;
}

static int decode_interworking_common_object(cJSON *interworking, wifi_interworking_t *interworking_info)
{
    cJSON *param, *venue = NULL;

    if(decode_param_bool(interworking, "InterworkingEnable", &param))
        return RET_ERR;
    interworking_info->interworking.interworkingEnabled = (param->type & cJSON_True) ? TRUE:FALSE;

    if(decode_param_integer(interworking, "AccessNetworkType", &param))
        return RET_ERR;
    interworking_info->interworking.accessNetworkType = param->valuedouble;

    if(decode_param_bool(interworking, "Internet", &param))
        return RET_ERR;
    interworking_info->interworking.internetAvailable = (param->type & cJSON_True) ? TRUE:FALSE;

    if(decode_param_bool(interworking, "ASRA", &param))
        return RET_ERR;
    interworking_info->interworking.asra = (param->type & cJSON_True) ? TRUE:FALSE;

    if(decode_param_bool(interworking, "ESR", &param))
        return RET_ERR;
    interworking_info->interworking.esr = (param->type & cJSON_True) ? TRUE:FALSE;

    if(decode_param_bool(interworking, "UESA", &param))
        return RET_ERR;
    interworking_info->interworking.uesa = (param->type & cJSON_True) ? TRUE:FALSE;

    if(decode_param_bool(interworking, "HESSOptionPresent", &param))
        return RET_ERR;
    interworking_info->interworking.hessOptionPresent = (param->type & cJSON_True) ? TRUE:FALSE;

    if(decode_param_string(interworking, "HESSID", &param))
        return RET_ERR;
    strcpy(interworking_info->interworking.hessid, param->valuestring);

    if(decode_param_object(interworking, "Venue", &venue))
        return RET_ERR;

    if(decode_param_integer(venue, "VenueType", &param))
        return RET_ERR;
    interworking_info->interworking.venueType = param->valuedouble;

    if(decode_param_integer(venue, "VenueGroup", &param))
        return RET_ERR;
    interworking_info->interworking.venueGroup = param->valuedouble;

    return RET_OK;
}

/**function to read the private VAP configuration from json config file
*IN : index - VAP index
*IN : vap_info - the buffer to hold private VAP config
*OUT : returns success or failure status of the operation
**/
int get_private_vap_config(int index, wifi_vap_info_t *vap_info)
{
    cJSON *obj_vaps = NULL;
    cJSON *json = NULL;
    cJSON *obj_vap = NULL;
    cJSON *param = NULL;
    cJSON *security = NULL;
    cJSON *interworking = NULL;
    int ret = RET_OK;

    json = config_to_json(VAP_CONFIG);
    if (json == NULL)
    {
        printf("Failed to parse config\n");
        return RET_ERR;
    }
    obj_vaps = cJSON_GetObjectItem(json, "WifiVapConfig");
    if (!cJSON_IsArray(obj_vaps))
    {
        printf("VAP object not present or incorrect number of VAP objects\n");
        cJSON_Delete(json);
        return RET_ERR;
    }

    cJSON_ArrayForEach(obj_vap, obj_vaps)
    {
        param = cJSON_GetObjectItem(obj_vap, "VapIndex");
        if(param && (cJSON_IsNumber(param)) && param->valueint == index)
        {
            ret = decode_vap_common_object(obj_vap, vap_info);
            if(ret == RET_ERR){
                printf("\ndecode_vap_common_object failed");
                break;}

            if(decode_param_object(obj_vap, "Security", &security))
                break;
            ret = decode_personal_security_object(security, &vap_info->u.bss_info.security);
            if(ret == RET_ERR){
                printf("\ndecode_personal_security_object failed");
                break;}

            if(decode_param_object(obj_vap, "Interworking", &interworking))
                break;
            ret = decode_interworking_common_object(interworking, &vap_info->u.bss_info.interworking);
            if(ret == RET_ERR){
                printf("\ndecode_interworking_common_object failed");
                break;}

            printf("\nReading VAP config SUCCESS for VAP index %d\n",index);
         }
    }

    cJSON_Delete(json);
    printf("\nExiting get vap config for VapName: %s \n", vap_info->vap_name);
    return ret;
}


int decode_scan_params_object(cJSON *scan_obj, wifi_scan_params_t *scan_info)
{
    cJSON  *param = NULL;

    // period
    if(decode_param_integer(scan_obj, "Period", &param))
        return RET_ERR;
    scan_info->period = param->valuedouble;

    // channel
    if(decode_param_integer(scan_obj, "Channel", &param))
        return RET_ERR;
    scan_info->channel.channel = param->valuedouble;

    return RET_OK;
}


/**function to read the mesh_sta VAP configuration from json config file
*IN : index - VAP index
*IN : vap_info - the buffer to hold mesh_sta VAP config
*OUT : returns success or failure status of the operation
**/
int get_mesh_sta_vap_config(int index, wifi_vap_info_t *vap_info)
{
    cJSON *obj_vaps = NULL;
    cJSON *json = NULL;
    cJSON *vap = NULL;
    cJSON *param = NULL;
    cJSON *security = NULL;
    cJSON *scan = NULL;
    int ret = RET_ERR;

    json = config_to_json(VAP_CONFIG);
    if (json == NULL)
    {
        printf("Failed to parse config\n");
        return RET_ERR;
    }
    obj_vaps = cJSON_GetObjectItem(json, "WifiVapConfig");
    if (!cJSON_IsArray(obj_vaps))
    {
        printf("VAP object not present\n");
        cJSON_Delete(json);
        return RET_ERR;
    }

    cJSON_ArrayForEach(vap, obj_vaps)
    {
        param = cJSON_GetObjectItem(vap, "VapIndex");
        if(param && (cJSON_IsNumber(param)) && param->valueint == index)
        {
            vap_info->vap_index = param->valuedouble;
            //VAP Name
            if(decode_param_string(vap, "VapName", &param))
                break;
            strcpy(vap_info->vap_name, param->valuestring);

            // Radio Index
            if(decode_param_integer(vap, "RadioIndex", &param))
                break;
            vap_info->radio_index = param->valuedouble;

            // VAP Mode
            if(decode_param_integer(vap, "VapMode", &param))
                break;
            vap_info->vap_mode = param->valuedouble;

            //Bridge Name
            if(decode_param_string(vap, "BridgeName", &param))
                break;
            strncpy(vap_info->bridge_name, param->valuestring,WIFI_BRIDGE_NAME_LEN-1);

            // SSID
            if(decode_param_string(vap, "SSID", &param))
                break;
            strcpy(vap_info->u.sta_info.ssid, param->valuestring);

            // BSSID : TBD whether to use in set
            /*if(decode_param_string(vap, "BSSID", &param))
                break;
            if((ret = string_mac_to_uint8_mac(vap_info->u.sta_info.bssid, param->valuestring)) == RET_ERR){
                printf("string_mac_to_uint8_mac FAILED\n");
                break;}*/

            //MAC
            if(decode_param_string(vap, "MAC", &param))
                break;
            if((ret = string_mac_to_uint8_mac(vap_info->u.sta_info.mac, param->valuestring)) == RET_ERR){
                printf("string_mac_to_uint8_mac FAILED\n");
                break;}

            // Enabled
            if(decode_param_bool(vap, "Enabled", &param))
                break;
            vap_info->u.bss_info.enabled = (param->type & cJSON_True) ? TRUE:FALSE;

            // ConnectStatus
            if(decode_param_bool(vap, "ConnectStatus", &param))
                break;
            vap_info->u.sta_info.conn_status = (param->type & cJSON_True) ? wifi_connection_status_connected:wifi_connection_status_disconnected;

            if(decode_param_object(vap, "Security", &security))
                break;
            ret = decode_personal_security_object(security, &vap_info->u.sta_info.security);
            if(ret == RET_ERR){
                printf("\ndecode_personal_security_object failed");
                break;}

            if(decode_param_object(vap, "ScanParameters", &scan))
                break;
            ret = decode_scan_params_object(scan, &vap_info->u.sta_info.scan_params);
            if(ret == RET_ERR){
                printf("\ndecode_scan_params_object failed");
                break;}
            ret = RET_OK;
         }
    }

    cJSON_Delete(json);
    printf("\n get_mesh_sta_vap_config() VapName: %s \n", vap_info->vap_name);
    return ret;
}


/**function to read the IOT VAP configuration from json config file
*IN : index - VAP index
*IN : vap_info - the buffer to hold IOT VAP config
*OUT : returns success or failure status of the operation
**/
int get_iot_vap_config(int index, wifi_vap_info_t *vap_info)
{
    return get_private_vap_config(index, vap_info);
}


/**function to read the mesh_backhaul VAP configuration from json config file
*IN : index - VAP index
*IN : vap_info - the buffer to hold mesh_backhaul VAP config
*OUT : returns success or failure status of the operation
**/
int get_mesh_backhaul_vap_config(int index, wifi_vap_info_t *vap_info)
{
    return get_private_vap_config(index, vap_info);
}


/**function to check if an ipAddress is valid or not
*IN : ip - ip to be decoded
*OUT : returns success or failure status of the operation
**/
static int decode_ipv4_address(char *ip) {
    struct sockaddr_in sa;
    if (inet_pton(AF_INET,ip, &(sa.sin_addr)) != 1 ) {
	return RET_ERR;
    }
    return RET_OK;
}

/**function to read the radius settings 
*IN : radius - json radius object
*IN : radius_info - wifi_radius_settings_t buffer to retreive radius info
*OUT : returns success or failure status of the operation
**/
static int decode_radius_object(cJSON *radius, wifi_radius_settings_t *radius_info)
{
    cJSON *param = NULL;

    //ip
    if(decode_param_string(radius, "RadiusServerIPAddr", &param))
	return RET_ERR;
    if (decode_ipv4_address(param->valuestring) == RET_ERR) {
            printf("%s:%d: Validation failed for RadiusServerIPAddr\n", __func__, __LINE__);
            return RET_ERR;
    }
    #ifndef WIFI_HAL_VERSION_3_PHASE2
    strcpy((char *)radius_info->ip,param->valuestring);
    #else
    /* check the INET family and update the radius ip address */
    if(inet_pton(AF_INET, param->valuestring, &(radius_info->ip.u.IPv4addr)) > 0) {
         radius_info->ip.family = wifi_ip_family_ipv4;
    } else if(inet_pton(AF_INET6, param->valuestring, &(radius_info->ip.u.IPv6addr)) > 0) {
        radius_info->ip.family = wifi_ip_family_ipv6;
    } else {
        printf("inet_pton() address conversion failed for RadiusServerIPAddr\n");
        return RET_ERR;
    }
    #endif

    //port
    if(decode_param_integer(radius, "RadiusServerPort", &param))
        return RET_ERR;
    radius_info->port = param->valuedouble;

    //key
    if(decode_param_string(radius, "RadiusSecret", &param))
        return RET_ERR;
    strcpy(radius_info->key, param->valuestring);

    //s_ip
    if(decode_param_string(radius, "SecondaryRadiusServerIPAddr", &param))
        return RET_ERR;
    if (decode_ipv4_address(param->valuestring) == RET_ERR) {
            printf("%s:%d: Validation failed for SecondaryRadiusServerIPAddr\n", __func__, __LINE__);
	     return RET_ERR;
    }
    #ifndef WIFI_HAL_VERSION_3_PHASE2
    strcpy((char *)radius_info->s_ip,param->valuestring);
    #else
    /* check the INET family and update the radius ip address */
    if (inet_pton(AF_INET, param->valuestring, &(radius_info->s_ip.u.IPv4addr)) > 0) {
        radius_info->s_ip.family = wifi_ip_family_ipv4;
    } else if(inet_pton(AF_INET6, param->valuestring, &(radius_info->s_ip.u.IPv6addr)) > 0) {
        radius_info->s_ip.family = wifi_ip_family_ipv6;
    } else {
        return RET_ERR;
    }
    #endif

    //s_port
    if(decode_param_integer(radius, "SecondaryRadiusServerPort", &param))
        return RET_ERR;
    radius_info->s_port = param->valuedouble;

    //s_key
    if(decode_param_string(radius, "SecondaryRadiusSecret", &param))
        return RET_ERR;
    strcpy(radius_info->s_key, param->valuestring);

    //dasip
    decode_param_string(radius, "DasServerIPAddr", &param);
    if (decode_ipv4_address(param->valuestring) == RET_ERR) {
            printf("%s:%d: Validation failed for DasServerIPAddr\n", __func__, __LINE__);
            return RET_ERR;
    }
    if (inet_pton(AF_INET, param->valuestring, &(radius_info->dasip.u.IPv4addr)) > 0) {
        radius_info->dasip.family = wifi_ip_family_ipv4;
    } else if (inet_pton(AF_INET6, param->valuestring, &(radius_info->dasip.u.IPv6addr)) > 0) {
        radius_info->dasip.family = wifi_ip_family_ipv6;
    } else {
        return RET_ERR;
    }

    //dasport
    if(decode_param_integer(radius, "DasServerPort", &param))
        return RET_ERR;
    radius_info->dasport = param->valuedouble;

    //daskey
    if(decode_param_string(radius, "DasSecret", &param))
        return RET_ERR;
    strcpy(radius_info->daskey, param->valuestring);

    //max_auth_attempts
    if(decode_param_integer(radius, "MaxAuthAttempts", &param))
        return RET_ERR;
    radius_info->max_auth_attempts = param->valuedouble;

    //blacklist_table_timeout
    if(decode_param_integer(radius, "BlacklistTableTimeout", &param))
        return RET_ERR;
    radius_info->blacklist_table_timeout = param->valuedouble;

    //identity_req_retry_interval
    if(decode_param_integer(radius, "IdentityReqRetryInterval", &param))
        return RET_ERR;
    radius_info->identity_req_retry_interval = param->valuedouble;

    //server_retries
    if(decode_param_integer(radius, "ServerRetries", &param))
        return RET_ERR;
    radius_info->server_retries = param->valuedouble;

    return RET_OK;
}


/**function to read the enterprise security object
*IN : security - json enterprise-security object
*IN : security_info - wifi_vap_security_t buffer to retreive security nfo
*OUT : returns success or failure status of the operation
**/
static int decode_enterprise_security_object(cJSON *security, wifi_vap_security_t *security_info)
{
    cJSON *param = NULL;

    //Mode
    if(decode_param_string(security, "Mode", &param))
        return RET_ERR;
    if ((strcmp(param->valuestring, "WPA2-Enterprise") != 0) && (strcmp(param->valuestring, "WPA-WPA2-Enterprise") != 0)) {
        printf("%s:%d: WiFi VAP security is not WPA2 Eneterprise, value:%s\n",
            __func__, __LINE__, param->valuestring);
        return RET_ERR;
    }
    if (strcmp(param->valuestring, "WPA2-Enterprise") == 0) {
        security_info->mode = wifi_security_mode_wpa2_enterprise;
    } else {
        security_info->mode = wifi_security_mode_wpa_wpa2_enterprise;
    }

    //encr
    if(decode_param_string(security, "EncryptionMethod", &param))
        return RET_ERR;
    if ((strcmp(param->valuestring, "AES") != 0) && (strcmp(param->valuestring, "AES+TKIP") != 0)) {
        printf("%s:%d: WiFi VAP Encrytpion mode is Invalid:%s\n",
                    __func__, __LINE__, param->valuestring);
        return RET_ERR;
    }
    if (strcmp(param->valuestring, "AES") == 0) {
        security_info->encr = wifi_encryption_aes;
    } else {
        security_info->encr = wifi_encryption_aes_tkip;
    }

    // MFPConfig
    if(decode_param_string(security, "MFPConfig", &param))
        return RET_ERR;
    if ((strcmp(param->valuestring, "Disabled") != 0)
        && (strcmp(param->valuestring, "Required") != 0)
        && (strcmp(param->valuestring, "Optional") != 0)) {
        printf("%s:%d: MFPConfig not valid, value:%s\n",
                        __func__, __LINE__, param->valuestring);
        return RET_ERR;
    }
    if (strstr(param->valuestring, "Disabled")) {
        security_info->mfp = wifi_mfp_cfg_disabled;
    } else if (strstr(param->valuestring, "Required")) {
        security_info->mfp = wifi_mfp_cfg_required;
    } else if (strstr(param->valuestring, "Optional")) {
        security_info->mfp = wifi_mfp_cfg_optional;
    }

    //Wpa3_transition_disable
    if(decode_param_bool(security, "Wpa3_transition_disable", &param))
        return RET_ERR;
    security_info->wpa3_transition_disable =  (param->type & cJSON_True) ? TRUE:FALSE;

    //rekey_interval
    if(decode_param_integer(security, "RekeyInterval", &param))
        return RET_ERR;
    security_info->rekey_interval = param->valuedouble;

    //strict_rekey
    if(decode_param_bool(security, "StrictRekey", &param))
        return RET_ERR;
    security_info->strict_rekey =  (param->type & cJSON_True) ? TRUE:FALSE;

    //eapol_key_timeout
    if(decode_param_integer(security, "EapolKeyTimeout", &param))
        return RET_ERR;
    security_info->eapol_key_timeout = param->valuedouble;

    //eapol_key_retries
    if(decode_param_integer(security, "EapolKeyRetries", &param))
        return RET_ERR;
    security_info->eapol_key_retries = param->valuedouble;

    //eap_identity_req_timeout
    if(decode_param_integer(security, "EapIdentityReqTimeout", &param))
        return RET_ERR;
    security_info->eap_identity_req_timeout = param->valuedouble;

    //eap_identity_req_retries
    if(decode_param_integer(security, "EapIdentityReqRetries", &param))
        return RET_ERR;
    security_info->eap_identity_req_retries = param->valuedouble;

    //eap_req_timeout
    if(decode_param_integer(security, "EapReqTimeout", &param))
        return RET_ERR;
    security_info->eap_req_timeout = param->valuedouble;

    //eap_req_retries
    if(decode_param_integer(security, "EapReqRetries", &param))
        return RET_ERR;
    security_info->eap_req_retries = param->valuedouble;

     //disable_pmksa_caching
    if(decode_param_bool(security, "DisablePmksaCaching", &param))
        return RET_ERR;
    security_info->disable_pmksa_caching = (param->type & cJSON_True) ? TRUE:FALSE;

    //radius
    if(decode_param_object(security, "RadiusSettings", &param))
        return RET_ERR;
    if (decode_radius_object(param, &security_info->u.radius) != 0) {
        printf("%s:%d: Validation failed\n", __func__, __LINE__);
        return RET_ERR;
    }
    return RET_OK;
}


/**function to read open-security object
*IN : security - json open-security object
*IN : security_info - wifi_vap_security_t buffer to retreive security nfo
*OUT : returns success or failure status of the operation
**/
static int decode_no_security_object(cJSON *security, wifi_vap_security_t *security_info)
{
    cJSON *param = NULL;

    //mode
    if(decode_param_string(security, "Mode", &param))
	return RET_ERR;
    if (strcmp(param->valuestring, "None") != 0) {
        printf("%s:%d: Decode error for open security object\n", __func__, __LINE__);
	return RET_ERR;
    }
    security_info->mode = wifi_security_mode_none;

    //radius
    if(decode_param_object(security, "RadiusSettings", &param))
	return RET_ERR;
    if (decode_radius_object(param, &security_info->u.radius) != 0) {
        printf("%s:%d: Validation failed for open_radius_object\n", __func__, __LINE__);
	return RET_ERR;
    }
    return RET_OK;
}

/**function to read the hotspot_open VAP configuration from json config file
*IN : index - VAP index
*IN : vap_info - the buffer to hold hotspot_open VAP config
*OUT : returns success or failure status of the operation
**/
int get_hotspot_open_vap_config(int index, wifi_vap_info_t *vap_info)
{
    cJSON *obj_vaps = NULL;
    cJSON *json = NULL;
    cJSON *obj_vap = NULL;
    cJSON *param = NULL;
    cJSON *security = NULL;
    cJSON *interworking = NULL;
    int ret = RET_OK;

    json = config_to_json(VAP_CONFIG);
    if (json == NULL)
    {
        printf("Failed to parse config\n");
        return RET_ERR;
    }
    obj_vaps = cJSON_GetObjectItem(json, "WifiVapConfig");
    if (!cJSON_IsArray(obj_vaps))
    {
        printf("VAP object not present or incorrect number of VAP objects\n");
        cJSON_Delete(json);
        return RET_ERR;
    }

    cJSON_ArrayForEach(obj_vap, obj_vaps)
    {
        param = cJSON_GetObjectItem(obj_vap, "VapIndex");
        if(param && (cJSON_IsNumber(param)) && param->valueint == index)
        {
            ret = decode_vap_common_object(obj_vap, vap_info);
            if(ret == RET_ERR){
                printf("\ndecode_vap_common_object failed");
                break;}

            if(decode_param_object(obj_vap, "Security", &security))
                break;
            ret = decode_no_security_object(security, &vap_info->u.bss_info.security);
            if(ret == RET_ERR){
                printf("\ndecode_no_security_object failed");
                break;}

            if(decode_param_object(obj_vap, "Interworking", &interworking))
                break;
            ret = decode_interworking_common_object(interworking, &vap_info->u.bss_info.interworking);
            if(ret == RET_ERR){
                printf("\ndecode_interworking_common_object failed");
                break;}

            printf("\nget_hotspot_open_vap_config() SUCCESS \n");
         }
    }

    cJSON_Delete(json);
    printf("\n get_hotspot_open_vap_config() VAPName: %s \n", vap_info->vap_name);
    return ret;
}

/**function to read the hotspot_secure VAP configuration from json config file
*IN : index - VAP index
*IN : vap_info - the buffer to hold hotspot_secure VAP config
*OUT : returns success or failure status of the operation
**/
int get_hotspot_secure_vap_config(int index, wifi_vap_info_t *vap_info)
{
    cJSON *obj_vaps = NULL;
    cJSON *json = NULL;
    cJSON *obj_vap = NULL;
    cJSON *param = NULL;
    cJSON *security = NULL;
    cJSON *interworking = NULL;
    int ret = RET_OK;

    json = config_to_json(VAP_CONFIG);
    if (json == NULL)
    {
        printf("Failed to parse config\n");
        return RET_ERR;
    }
    obj_vaps = cJSON_GetObjectItem(json, "WifiVapConfig");
    if (!cJSON_IsArray(obj_vaps))
    {
        printf("VAP object not present or incorrect number of VAP objects\n");
        cJSON_Delete(json);
        return RET_ERR;
    }

    cJSON_ArrayForEach(obj_vap, obj_vaps)
    {
        param = cJSON_GetObjectItem(obj_vap, "VapIndex");
        if(param && (cJSON_IsNumber(param)) && param->valueint == index)
        {
            ret = decode_vap_common_object(obj_vap, vap_info);
            if(ret == RET_ERR){
                printf("\ndecode_vap_common_object failed");
                break;}

            if(decode_param_object(obj_vap, "Security", &security))
                break;
            ret = decode_enterprise_security_object(security, &vap_info->u.bss_info.security);
            if(ret == RET_ERR){
                printf("\ndecode_enterprise_security_object failed");
                break;}

            if(decode_param_object(obj_vap, "Interworking", &interworking))
                break;
            /*for MVP, skipping passpoint/anqp object parsing as per Dev i/p */
            //ret = decode_interworking_object(interworking, &vap_info->u.bss_info.interworking);
            ret = decode_interworking_common_object(interworking, &vap_info->u.bss_info.interworking);
            if(ret == RET_ERR){
                printf("\ndecode_interworking_object failed");
                break;}

            printf("\nget_hotspot_secure_vap_config() SUCCESS \n");
         }
    }

    cJSON_Delete(json);
    printf("\n get_hotspot_secure_vap_config() VAPName: %s \n", vap_info->vap_name);
    return ret;
}


/**function to read the lnf_psk VAP configuration from json config file
*IN : index - VAP index
*IN : vap_info - the buffer to hold lnf_psk VAP config
*OUT : returns success or failure status of the operation
**/
int get_lnf_psk_vap_config(int index, wifi_vap_info_t *vap_info)
{
    return get_private_vap_config(index, vap_info);
}


/**function to read the lnf_radius VAP configuration from json config file
*IN : index - VAP index
*IN : vap_info - the buffer to hold lnf_radius VAP config
*OUT : returns success or failure status of the operation
**/
int get_lnf_radius_vap_config(int index, wifi_vap_info_t *vap_info)
{
    cJSON *obj_vaps = NULL;
    cJSON *json = NULL;
    cJSON *obj_vap = NULL;
    cJSON *param = NULL;
    cJSON *security = NULL;
    cJSON *interworking = NULL;
    int ret = RET_OK;

    json = config_to_json(VAP_CONFIG);
    if (json == NULL)
    {
        printf("Failed to parse config\n");
        return RET_ERR;
    }
    obj_vaps = cJSON_GetObjectItem(json, "WifiVapConfig");
    if (!cJSON_IsArray(obj_vaps))
    {
        printf("VAP object not present or incorrect number of VAP objects\n");
        cJSON_Delete(json);
        return RET_ERR;
    }

    cJSON_ArrayForEach(obj_vap, obj_vaps)
    {
        param = cJSON_GetObjectItem(obj_vap, "VapIndex");
        if(param && (cJSON_IsNumber(param)) && param->valueint == index)
        {
            ret = decode_vap_common_object(obj_vap, vap_info);
            if(ret == RET_ERR){
                printf("\ndecode_vap_common_object failed");
                break;}

            if(decode_param_object(obj_vap, "Security", &security))
                break;
            ret = decode_enterprise_security_object(security, &vap_info->u.bss_info.security);
            if(ret == RET_ERR){
                printf("\ndecode_enterprise_security_object failed");
                break;}

            if(decode_param_object(obj_vap, "Interworking", &interworking))
                break;
            ret = decode_interworking_common_object(interworking, &vap_info->u.bss_info.interworking);
            if(ret == RET_ERR){
                printf("\ndecode_interworking_common_object failed");
                break;}

            printf("\nget_lnf_radius_vap_config() SUCCESS \n");
         }
    }

    cJSON_Delete(json);
    printf("\n get_lnf_radius_vap_config() VAPName: %s \n", vap_info->vap_name);
    return ret;
}
