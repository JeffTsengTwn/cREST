#include "cREST.h"
#include "redfish_handler.h"
#include <fcgi_stdio.h>

static void PrintEnv(char **envp)
{
    for ( ; *envp != NULL; envp++) {
        DEBUG_PRINT("%s\n", *envp);
    }
}

void main(int argc, char *argv[], char *env[]) {

    FCGX_Stream *in, *out, *err;
    FCGX_ParamArray envp;

    /* ----------------------------------------------------------------
     * 初始化控制器 - 每個 Redfish 端點註冊一個 Controller
     * PATH_INFO 由 lighttpd 去掉 /redfish 前綴後傳入
     * 例如: 請求 /redfish/v1/Systems → PATH_INFO = /v1/Systems
     * ---------------------------------------------------------------- */

    /* /redfish → PATH_INFO = "" 或 "/" */
    Controller versionCtrl;
    cREST_init_controller(&versionCtrl, "/", redfishGetVersion, NULL, NULL, NULL, NULL);

    Controller versionCtrl2;
    cREST_init_controller(&versionCtrl2, "", redfishGetVersion, NULL, NULL, NULL, NULL);

    /* Service Root: /redfish/v1 */
    Controller serviceRootCtrl;
    cREST_init_controller(&serviceRootCtrl, "/v1", redfishGetServiceRoot, NULL, NULL, NULL, NULL);

    Controller serviceRootCtrl2;
    cREST_init_controller(&serviceRootCtrl2, "/v1/", redfishGetServiceRoot, NULL, NULL, NULL, NULL);

    /* Systems Collection: /redfish/v1/Systems */
    Controller systemsCtrl;
    cREST_init_controller(&systemsCtrl, "/v1/Systems", redfishGetSystems, NULL, NULL, NULL, NULL);

    /* System Instance: /redfish/v1/Systems/1 */
    Controller systemCtrl;
    cREST_init_controller(&systemCtrl, "/v1/Systems/1", redfishGetSystem, NULL, NULL, NULL, NULL);

    /* Chassis Collection: /redfish/v1/Chassis */
    Controller chassisCollCtrl;
    cREST_init_controller(&chassisCollCtrl, "/v1/Chassis", redfishGetChassisCollection, NULL, NULL, NULL, NULL);

    /* Chassis Instance: /redfish/v1/Chassis/1 */
    Controller chassisCtrl;
    cREST_init_controller(&chassisCtrl, "/v1/Chassis/1", redfishGetChassis, NULL, NULL, NULL, NULL);

    /* Managers Collection: /redfish/v1/Managers */
    Controller managersCtrl;
    cREST_init_controller(&managersCtrl, "/v1/Managers", redfishGetManagers, NULL, NULL, NULL, NULL);

    /* Manager Instance: /redfish/v1/Managers/1 */
    Controller managerCtrl;
    cREST_init_controller(&managerCtrl, "/v1/Managers/1", redfishGetManager, NULL, NULL, NULL, NULL);

    /* AccountService: /redfish/v1/AccountService */
    Controller accountServiceCtrl;
    cREST_init_controller(&accountServiceCtrl, "/v1/AccountService", redfishGetAccountService, NULL, NULL, NULL, NULL);

    /* SessionService: /redfish/v1/SessionService */
    Controller sessionServiceCtrl;
    cREST_init_controller(&sessionServiceCtrl, "/v1/SessionService", redfishGetSessionService, NULL, NULL, NULL, NULL);

    /* 註冊控制器 (NULL 結尾) */
    Controller *controllers[] = {
        &versionCtrl,
        &versionCtrl2,
        &serviceRootCtrl,
        &serviceRootCtrl2,
        &systemsCtrl,
        &systemCtrl,
        &chassisCollCtrl,
        &chassisCtrl,
        &managersCtrl,
        &managerCtrl,
        &accountServiceCtrl,
        &sessionServiceCtrl,
        NULL
    };

    Controller *controller = NULL;
    Response *response = NULL;
    Response errorResponse;

    /* FastCGI 初始化 */
    FCGX_Init();

    DEBUG_PRINT("After FCGX_Init()");

    /* 處理 FastCGI 請求 */
    while (FCGX_Accept(&in, &out, &err, &envp) >= 0) {
        DEBUG_PRINT("Enter FCGX_Accept loop");

        PrintEnv(envp);

        const char *path_info = FCGX_GetParam("PATH_INFO", envp);
        const char *request_method = FCGX_GetParam("REQUEST_METHOD", envp);

        /* 設定環境變數供 cREST_dispatch 使用 */
        setenv("PATH_INFO", path_info ? path_info : "", 1);
        setenv("REQUEST_METHOD", request_method ? request_method : "GET", 1);

        /* 分派請求 */
        controller = cREST_dispatch(0, NULL, NULL, controllers);

        if (controller) {
            /* 成功匹配 - 回傳 Redfish 回應 */
            response = &(controller->response);
            FCGX_FPrintF(out, "Status: %d\r\n", response->code);
            FCGX_FPrintF(out, "Content-Type: %s\r\n", response->type);
            FCGX_FPrintF(out, "OData-Version: 4.0\r\n");
            FCGX_FPrintF(out, "\r\n");
            FCGX_FPrintF(out, "%s", response->content);
        } else {
            /* 未匹配 - 回傳 Redfish 404 錯誤 */
            memset(&errorResponse, 0x00, sizeof(Response));
            redfishErrorNotFound(&errorResponse);
            FCGX_FPrintF(out, "Status: %d\r\n", errorResponse.code);
            FCGX_FPrintF(out, "Content-Type: %s\r\n", errorResponse.type);
            FCGX_FPrintF(out, "OData-Version: 4.0\r\n");
            FCGX_FPrintF(out, "\r\n");
            FCGX_FPrintF(out, "%s", errorResponse.content);
        }
    }
}
