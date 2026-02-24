#include "redfish_handler.h"
#include <stdio.h>

#define REDFISH_CONTENT_TYPE "application/json;odata.metadata=minimal;charset=utf-8"

/* --------------------------------------------------------------------------
 * GET /redfish  -  Redfish Version
 * -------------------------------------------------------------------------- */
void redfishGetVersion(int argc, char *argv[], char *envp[], Response *response) {
    response->code = 200;
    snprintf(response->type, TYPE_SIZE, REDFISH_CONTENT_TYPE);
    snprintf(response->content, CONTENT_SIZE,
        "{\n"
        "    \"v1\": \"/redfish/v1/\"\n"
        "}"
    );
}

/* --------------------------------------------------------------------------
 * GET /redfish/v1  -  Service Root
 * -------------------------------------------------------------------------- */
void redfishGetServiceRoot(int argc, char *argv[], char *envp[], Response *response) {
    response->code = 200;
    snprintf(response->type, TYPE_SIZE, REDFISH_CONTENT_TYPE);
    snprintf(response->content, CONTENT_SIZE,
        "{\n"
        "    \"@odata.type\": \"#ServiceRoot.v1_16_0.ServiceRoot\",\n"
        "    \"@odata.id\": \"/redfish/v1/\",\n"
        "    \"Id\": \"RootService\",\n"
        "    \"Name\": \"Root Service\",\n"
        "    \"RedfishVersion\": \"1.17.0\",\n"
        "    \"UUID\": \"00000000-0000-0000-0000-000000000001\",\n"
        "    \"Systems\": {\n"
        "        \"@odata.id\": \"/redfish/v1/Systems\"\n"
        "    },\n"
        "    \"Chassis\": {\n"
        "        \"@odata.id\": \"/redfish/v1/Chassis\"\n"
        "    },\n"
        "    \"Managers\": {\n"
        "        \"@odata.id\": \"/redfish/v1/Managers\"\n"
        "    },\n"
        "    \"AccountService\": {\n"
        "        \"@odata.id\": \"/redfish/v1/AccountService\"\n"
        "    },\n"
        "    \"SessionService\": {\n"
        "        \"@odata.id\": \"/redfish/v1/SessionService\"\n"
        "    }\n"
        "}"
    );
}

/* --------------------------------------------------------------------------
 * GET /redfish/v1/Systems  -  Computer System Collection
 * -------------------------------------------------------------------------- */
void redfishGetSystems(int argc, char *argv[], char *envp[], Response *response) {
    response->code = 200;
    snprintf(response->type, TYPE_SIZE, REDFISH_CONTENT_TYPE);
    snprintf(response->content, CONTENT_SIZE,
        "{\n"
        "    \"@odata.type\": \"#ComputerSystemCollection.ComputerSystemCollection\",\n"
        "    \"@odata.id\": \"/redfish/v1/Systems\",\n"
        "    \"Name\": \"Computer System Collection\",\n"
        "    \"Members@odata.count\": 1,\n"
        "    \"Members\": [\n"
        "        {\n"
        "            \"@odata.id\": \"/redfish/v1/Systems/1\"\n"
        "        }\n"
        "    ]\n"
        "}"
    );
}

/* --------------------------------------------------------------------------
 * GET /redfish/v1/Systems/1  -  Computer System Instance
 * -------------------------------------------------------------------------- */
void redfishGetSystem(int argc, char *argv[], char *envp[], Response *response) {
    response->code = 200;
    snprintf(response->type, TYPE_SIZE, REDFISH_CONTENT_TYPE);
    snprintf(response->content, CONTENT_SIZE,
        "{\n"
        "    \"@odata.type\": \"#ComputerSystem.v1_20_0.ComputerSystem\",\n"
        "    \"@odata.id\": \"/redfish/v1/Systems/1\",\n"
        "    \"Id\": \"1\",\n"
        "    \"Name\": \"Computer System\",\n"
        "    \"Description\": \"Computer System\",\n"
        "    \"SystemType\": \"Physical\",\n"
        "    \"Manufacturer\": \"Manufacturer\",\n"
        "    \"Model\": \"Server Model\",\n"
        "    \"SerialNumber\": \"SN-12345678\",\n"
        "    \"PartNumber\": \"PN-001\",\n"
        "    \"UUID\": \"00000000-0000-0000-0000-000000000010\",\n"
        "    \"BiosVersion\": \"1.0.0\",\n"
        "    \"PowerState\": \"On\",\n"
        "    \"Status\": {\n"
        "        \"State\": \"Enabled\",\n"
        "        \"Health\": \"OK\"\n"
        "    },\n"
        "    \"IndicatorLED\": \"Off\",\n"
        "    \"Boot\": {\n"
        "        \"BootSourceOverrideEnabled\": \"Disabled\",\n"
        "        \"BootSourceOverrideTarget\": \"None\",\n"
        "        \"BootSourceOverrideTarget@Redfish.AllowableValues\": [\n"
        "            \"None\", \"Pxe\", \"Hdd\", \"Cd\", \"BiosSetup\"\n"
        "        ]\n"
        "    },\n"
        "    \"ProcessorSummary\": {\n"
        "        \"Count\": 2,\n"
        "        \"Model\": \"Multi-Core CPU\",\n"
        "        \"Status\": {\n"
        "            \"State\": \"Enabled\",\n"
        "            \"Health\": \"OK\"\n"
        "        }\n"
        "    },\n"
        "    \"MemorySummary\": {\n"
        "        \"TotalSystemMemoryGiB\": 64,\n"
        "        \"Status\": {\n"
        "            \"State\": \"Enabled\",\n"
        "            \"Health\": \"OK\"\n"
        "        }\n"
        "    },\n"
        "    \"Actions\": {\n"
        "        \"#ComputerSystem.Reset\": {\n"
        "            \"target\": \"/redfish/v1/Systems/1/Actions/ComputerSystem.Reset\",\n"
        "            \"ResetType@Redfish.AllowableValues\": [\n"
        "                \"On\", \"ForceOff\", \"GracefulShutdown\", \"GracefulRestart\", \"ForceRestart\"\n"
        "            ]\n"
        "        }\n"
        "    },\n"
        "    \"Links\": {\n"
        "        \"Chassis\": [\n"
        "            {\n"
        "                \"@odata.id\": \"/redfish/v1/Chassis/1\"\n"
        "            }\n"
        "        ],\n"
        "        \"ManagedBy\": [\n"
        "            {\n"
        "                \"@odata.id\": \"/redfish/v1/Managers/1\"\n"
        "            }\n"
        "        ]\n"
        "    }\n"
        "}"
    );
}

/* --------------------------------------------------------------------------
 * GET /redfish/v1/Chassis  -  Chassis Collection
 * -------------------------------------------------------------------------- */
void redfishGetChassisCollection(int argc, char *argv[], char *envp[], Response *response) {
    response->code = 200;
    snprintf(response->type, TYPE_SIZE, REDFISH_CONTENT_TYPE);
    snprintf(response->content, CONTENT_SIZE,
        "{\n"
        "    \"@odata.type\": \"#ChassisCollection.ChassisCollection\",\n"
        "    \"@odata.id\": \"/redfish/v1/Chassis\",\n"
        "    \"Name\": \"Chassis Collection\",\n"
        "    \"Members@odata.count\": 1,\n"
        "    \"Members\": [\n"
        "        {\n"
        "            \"@odata.id\": \"/redfish/v1/Chassis/1\"\n"
        "        }\n"
        "    ]\n"
        "}"
    );
}

/* --------------------------------------------------------------------------
 * GET /redfish/v1/Chassis/1  -  Chassis Instance
 * -------------------------------------------------------------------------- */
void redfishGetChassis(int argc, char *argv[], char *envp[], Response *response) {
    response->code = 200;
    snprintf(response->type, TYPE_SIZE, REDFISH_CONTENT_TYPE);
    snprintf(response->content, CONTENT_SIZE,
        "{\n"
        "    \"@odata.type\": \"#Chassis.v1_23_0.Chassis\",\n"
        "    \"@odata.id\": \"/redfish/v1/Chassis/1\",\n"
        "    \"Id\": \"1\",\n"
        "    \"Name\": \"Computer System Chassis\",\n"
        "    \"Description\": \"System Chassis\",\n"
        "    \"ChassisType\": \"RackMount\",\n"
        "    \"Manufacturer\": \"Manufacturer\",\n"
        "    \"Model\": \"Rack Server\",\n"
        "    \"SerialNumber\": \"CS-12345678\",\n"
        "    \"PartNumber\": \"CP-001\",\n"
        "    \"SKU\": \"SKU-001\",\n"
        "    \"IndicatorLED\": \"Off\",\n"
        "    \"PowerState\": \"On\",\n"
        "    \"Status\": {\n"
        "        \"State\": \"Enabled\",\n"
        "        \"Health\": \"OK\"\n"
        "    },\n"
        "    \"Thermal\": {\n"
        "        \"@odata.id\": \"/redfish/v1/Chassis/1/Thermal\"\n"
        "    },\n"
        "    \"Power\": {\n"
        "        \"@odata.id\": \"/redfish/v1/Chassis/1/Power\"\n"
        "    },\n"
        "    \"Links\": {\n"
        "        \"ComputerSystems\": [\n"
        "            {\n"
        "                \"@odata.id\": \"/redfish/v1/Systems/1\"\n"
        "            }\n"
        "        ],\n"
        "        \"ManagedBy\": [\n"
        "            {\n"
        "                \"@odata.id\": \"/redfish/v1/Managers/1\"\n"
        "            }\n"
        "        ]\n"
        "    }\n"
        "}"
    );
}

/* --------------------------------------------------------------------------
 * GET /redfish/v1/Managers  -  Manager Collection
 * -------------------------------------------------------------------------- */
void redfishGetManagers(int argc, char *argv[], char *envp[], Response *response) {
    response->code = 200;
    snprintf(response->type, TYPE_SIZE, REDFISH_CONTENT_TYPE);
    snprintf(response->content, CONTENT_SIZE,
        "{\n"
        "    \"@odata.type\": \"#ManagerCollection.ManagerCollection\",\n"
        "    \"@odata.id\": \"/redfish/v1/Managers\",\n"
        "    \"Name\": \"Manager Collection\",\n"
        "    \"Members@odata.count\": 1,\n"
        "    \"Members\": [\n"
        "        {\n"
        "            \"@odata.id\": \"/redfish/v1/Managers/1\"\n"
        "        }\n"
        "    ]\n"
        "}"
    );
}

/* --------------------------------------------------------------------------
 * GET /redfish/v1/Managers/1  -  Manager Instance (BMC)
 * -------------------------------------------------------------------------- */
void redfishGetManager(int argc, char *argv[], char *envp[], Response *response) {
    response->code = 200;
    snprintf(response->type, TYPE_SIZE, REDFISH_CONTENT_TYPE);
    snprintf(response->content, CONTENT_SIZE,
        "{\n"
        "    \"@odata.type\": \"#Manager.v1_17_0.Manager\",\n"
        "    \"@odata.id\": \"/redfish/v1/Managers/1\",\n"
        "    \"Id\": \"1\",\n"
        "    \"Name\": \"Manager\",\n"
        "    \"Description\": \"Baseboard Management Controller\",\n"
        "    \"ManagerType\": \"BMC\",\n"
        "    \"FirmwareVersion\": \"1.0.0\",\n"
        "    \"Status\": {\n"
        "        \"State\": \"Enabled\",\n"
        "        \"Health\": \"OK\"\n"
        "    },\n"
        "    \"UUID\": \"00000000-0000-0000-0000-000000000100\",\n"
        "    \"Model\": \"BMC Controller\",\n"
        "    \"DateTime\": \"2025-01-01T00:00:00+00:00\",\n"
        "    \"DateTimeLocalOffset\": \"+00:00\",\n"
        "    \"NetworkProtocol\": {\n"
        "        \"@odata.id\": \"/redfish/v1/Managers/1/NetworkProtocol\"\n"
        "    },\n"
        "    \"EthernetInterfaces\": {\n"
        "        \"@odata.id\": \"/redfish/v1/Managers/1/EthernetInterfaces\"\n"
        "    },\n"
        "    \"LogServices\": {\n"
        "        \"@odata.id\": \"/redfish/v1/Managers/1/LogServices\"\n"
        "    },\n"
        "    \"Actions\": {\n"
        "        \"#Manager.Reset\": {\n"
        "            \"target\": \"/redfish/v1/Managers/1/Actions/Manager.Reset\",\n"
        "            \"ResetType@Redfish.AllowableValues\": [\n"
        "                \"GracefulRestart\", \"ForceRestart\"\n"
        "            ]\n"
        "        }\n"
        "    },\n"
        "    \"Links\": {\n"
        "        \"ManagerForServers\": [\n"
        "            {\n"
        "                \"@odata.id\": \"/redfish/v1/Systems/1\"\n"
        "            }\n"
        "        ],\n"
        "        \"ManagerForChassis\": [\n"
        "            {\n"
        "                \"@odata.id\": \"/redfish/v1/Chassis/1\"\n"
        "            }\n"
        "        ]\n"
        "    }\n"
        "}"
    );
}

/* --------------------------------------------------------------------------
 * GET /redfish/v1/AccountService  -  Account Service
 * -------------------------------------------------------------------------- */
void redfishGetAccountService(int argc, char *argv[], char *envp[], Response *response) {
    response->code = 200;
    snprintf(response->type, TYPE_SIZE, REDFISH_CONTENT_TYPE);
    snprintf(response->content, CONTENT_SIZE,
        "{\n"
        "    \"@odata.type\": \"#AccountService.v1_12_0.AccountService\",\n"
        "    \"@odata.id\": \"/redfish/v1/AccountService\",\n"
        "    \"Id\": \"AccountService\",\n"
        "    \"Name\": \"Account Service\",\n"
        "    \"Description\": \"Account Service\",\n"
        "    \"Status\": {\n"
        "        \"State\": \"Enabled\",\n"
        "        \"Health\": \"OK\"\n"
        "    },\n"
        "    \"ServiceEnabled\": true,\n"
        "    \"AuthFailureLoggingThreshold\": 3,\n"
        "    \"MinPasswordLength\": 8,\n"
        "    \"MaxPasswordLength\": 64,\n"
        "    \"AccountLockoutThreshold\": 5,\n"
        "    \"AccountLockoutDuration\": 30,\n"
        "    \"AccountLockoutCounterResetAfter\": 30,\n"
        "    \"Accounts\": {\n"
        "        \"@odata.id\": \"/redfish/v1/AccountService/Accounts\"\n"
        "    },\n"
        "    \"Roles\": {\n"
        "        \"@odata.id\": \"/redfish/v1/AccountService/Roles\"\n"
        "    }\n"
        "}"
    );
}

/* --------------------------------------------------------------------------
 * GET /redfish/v1/SessionService  -  Session Service
 * -------------------------------------------------------------------------- */
void redfishGetSessionService(int argc, char *argv[], char *envp[], Response *response) {
    response->code = 200;
    snprintf(response->type, TYPE_SIZE, REDFISH_CONTENT_TYPE);
    snprintf(response->content, CONTENT_SIZE,
        "{\n"
        "    \"@odata.type\": \"#SessionService.v1_1_9.SessionService\",\n"
        "    \"@odata.id\": \"/redfish/v1/SessionService\",\n"
        "    \"Id\": \"SessionService\",\n"
        "    \"Name\": \"Session Service\",\n"
        "    \"Description\": \"Session Service\",\n"
        "    \"Status\": {\n"
        "        \"State\": \"Enabled\",\n"
        "        \"Health\": \"OK\"\n"
        "    },\n"
        "    \"ServiceEnabled\": true,\n"
        "    \"SessionTimeout\": 1800,\n"
        "    \"Sessions\": {\n"
        "        \"@odata.id\": \"/redfish/v1/SessionService/Sessions\"\n"
        "    }\n"
        "}"
    );
}

/* --------------------------------------------------------------------------
 * Error Helpers
 * -------------------------------------------------------------------------- */
void redfishErrorNotFound(Response *response) {
    response->code = 404;
    snprintf(response->type, TYPE_SIZE, REDFISH_CONTENT_TYPE);
    snprintf(response->content, CONTENT_SIZE,
        "{\n"
        "    \"error\": {\n"
        "        \"code\": \"Base.1.0.GeneralError\",\n"
        "        \"message\": \"The requested resource was not found.\",\n"
        "        \"@Message.ExtendedInfo\": [\n"
        "            {\n"
        "                \"@odata.type\": \"#Message.v1_0_0.Message\",\n"
        "                \"MessageId\": \"Base.1.0.ResourceMissingAtURI\",\n"
        "                \"Message\": \"The resource at the URI was not found.\",\n"
        "                \"Severity\": \"Critical\",\n"
        "                \"Resolution\": \"Check the URI and try again.\"\n"
        "            }\n"
        "        ]\n"
        "    }\n"
        "}"
    );
}

void redfishErrorMethodNotAllowed(Response *response) {
    response->code = 405;
    snprintf(response->type, TYPE_SIZE, REDFISH_CONTENT_TYPE);
    snprintf(response->content, CONTENT_SIZE,
        "{\n"
        "    \"error\": {\n"
        "        \"code\": \"Base.1.0.GeneralError\",\n"
        "        \"message\": \"The request method is not allowed on this resource.\",\n"
        "        \"@Message.ExtendedInfo\": [\n"
        "            {\n"
        "                \"@odata.type\": \"#Message.v1_0_0.Message\",\n"
        "                \"MessageId\": \"Base.1.0.ActionNotSupported\",\n"
        "                \"Message\": \"The requested HTTP method is not allowed for this resource.\",\n"
        "                \"Severity\": \"Critical\",\n"
        "                \"Resolution\": \"Use a supported HTTP method for this resource.\"\n"
        "            }\n"
        "        ]\n"
        "    }\n"
        "}"
    );
}
