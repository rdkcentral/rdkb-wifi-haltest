# Unit Testing Suite

The following documents should be references to provide specific information on the tests required for this module.

[Documentation can be found under "docs/pages" in this repository](docs/pages)

### Populate Configurations

As per oneWiFi architecture, we cannot run 3PE tests when oneWiFi process is up and running. oneWiFi service needs to be stopped before 3PE tests are run. Hence, it becomes 3PE test suite's responsibility to bring-up/initialize the WiFi subsystem. The "vap_config" file under /config folder is required in the initializing process to create every WiFi Accesspoint. This config file is aligned with the opensourced OneWiFi schema available in [https://code.rdkcentral.com/r/plugins/gitiles/rdkb/components/opensource/ccsp/OneWifi/+/refs/heads/rdk-next/config/subdoc_schemas_1_4/dml_subdoc_schema](https://code.rdkcentral.com/r/plugins/gitiles/rdkb/components/opensource/ccsp/OneWifi/+/refs/heads/rdk-next/config/subdoc_schemas_1_4/dml_subdoc_schema "https://code.rdkcentral.com/r/plugins/gitiles/rdkb/components/opensource/ccsp/onewifi/+/refs/heads/rdk-next/config/subdoc_schemas_1_4/dml_subdoc_schema"). In line with the schema, certain sensitive data is not populated in the config file such as passphrases and radius configuration parameters. The users of the 3PE test suite can populate appropriate platform specific values for the below parameters in the configuration file "vap_config" before executing the test binary.

1. For WifiVapConfig VapIndex : 0, populate
    * "Passphrase": ""

2. For WifiVapConfig VapIndex : 1, populate
    * "Passphrase": ""

3. For WifiVapConfig VapIndex : 2, populate
    * "Passphrase": ""

4. For WifiVapConfig VapIndex : 3, populate
    * "Passphrase": ""

5. For WifiVapConfig VapIndex : 4, populate
    * "RadiusServerIPAddr": "",
    * "RadiusServerPort": ,
    * "SecondaryRadiusServerIPAddr": "",
    * "SecondaryRadiusServerPort": ,

6. For WifiVapConfig VapIndex : 5, populate
    * "RadiusServerIPAddr": "",
    * "RadiusServerPort": ,
    * "SecondaryRadiusServerIPAddr": "",
    * "SecondaryRadiusServerPort": ,

7. For WifiVapConfig VapIndex : 6, populate
    * "Passphrase": ""

8. For WifiVapConfig VapIndex : 7, populate
    * "Passphrase": ""

9. For WifiVapConfig VapIndex : 8, populate
    * "RadiusServerIPAddr": "",
    * "RadiusServerPort": ,
    * "SecondaryRadiusServerIPAddr": "",
    * "SecondaryRadiusServerPort": ,

10. For WifiVapConfig VapIndex : 9, populate
    * "RadiusServerIPAddr": "",
    * "RadiusServerPort": ,
    * "SecondaryRadiusServerIPAddr": "",
    * "SecondaryRadiusServerPort": ,

11. For WifiVapConfig VapIndex : 12, populate
    * "Passphrase": ""

12. For WifiVapConfig VapIndex : 13, populate
    * "Passphrase": ""

13. For WifiVapConfig VapIndex : 14, populate
    * "Passphrase": ""

14. For WifiVapConfig VapIndex : 15, populate
    * "Passphrase": ""
