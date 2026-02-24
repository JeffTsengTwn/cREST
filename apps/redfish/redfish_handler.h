#ifndef REDFISH_HANDLER_H__
#define REDFISH_HANDLER_H__

#include "cREST.h"

/* Redfish version */
void redfishGetVersion(int argc, char *argv[], char *envp[], Response *response);

/* Service Root: /redfish/v1 */
void redfishGetServiceRoot(int argc, char *argv[], char *envp[], Response *response);

/* Systems Collection: /redfish/v1/Systems */
void redfishGetSystems(int argc, char *argv[], char *envp[], Response *response);

/* System Instance: /redfish/v1/Systems/1 */
void redfishGetSystem(int argc, char *argv[], char *envp[], Response *response);

/* Chassis Collection: /redfish/v1/Chassis */
void redfishGetChassisCollection(int argc, char *argv[], char *envp[], Response *response);

/* Chassis Instance: /redfish/v1/Chassis/1 */
void redfishGetChassis(int argc, char *argv[], char *envp[], Response *response);

/* Managers Collection: /redfish/v1/Managers */
void redfishGetManagers(int argc, char *argv[], char *envp[], Response *response);

/* Manager Instance: /redfish/v1/Managers/1 */
void redfishGetManager(int argc, char *argv[], char *envp[], Response *response);

/* AccountService: /redfish/v1/AccountService */
void redfishGetAccountService(int argc, char *argv[], char *envp[], Response *response);

/* SessionService: /redfish/v1/SessionService */
void redfishGetSessionService(int argc, char *argv[], char *envp[], Response *response);

/* Redfish error response helper */
void redfishErrorNotFound(Response *response);
void redfishErrorMethodNotAllowed(Response *response);

#endif
