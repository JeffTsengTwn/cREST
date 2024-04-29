#include "cREST.h"

Controller *cREST_dispatch(int argc, char *argv[], char *envp[], Controller *controllers[]) {
    DEBUG_PRINT("Enter function.");
    int idx = 0;
    Controller *controller = NULL;
    Response *response = NULL;
    for (idx = 0; idx < sizeof(controllers) / sizeof(Controller *); idx++) {
        DEBUG_PRINT("Dispatch loop idx = %d", idx);
        controller = controllers[idx];
        response = &controller->response;
        memset(response, 0x00, sizeof(Response));
        DEBUG_PRINT("PATH_INFO = %s", getenv("PATH_INFO"));
        if (0 == strcmp(getenv("PATH_INFO"), controller->path)) {
            if (controller->doGet && 0 == strcmp(getenv("REQUEST_METHOD"), "GET")) {
                DEBUG_PRINT("Case GET");
                controller->doGet(argc, argv, envp, response);
                return controller;
            } else if (controller->doPost && 0 == strcmp(getenv("REQUEST_METHOD"), "POST")) {
                DEBUG_PRINT("Case POST");
                controller->doPost(argc, argv, envp, response);
                return controller;
            } else if (controller->doPut && 0 == strcmp(getenv("REQUEST_METHOD"), "PUT")) {
                DEBUG_PRINT("Case PUT");
                controller->doPut(argc, argv, envp, response);
                return controller;
            } else if (controller->doDelete && 0 == strcmp(getenv("REQUEST_METHOD"), "DELETE")) {
                DEBUG_PRINT("Case DELETE");
                controller->doDelete(argc, argv, envp, response);
                return controller;
            } 
        }
    }
    return NULL;
}

void cREST_init_controller(Controller *controller, char *path, Method get, Method put, Method post, Method del) {
    strncpy(controller->path, path, sizeof(controller->path) - 1);
    controller->path[sizeof(controller->path) - 1] = '\0';
    controller->doGet = get;
    controller->doPut = put;
    controller->doPost = post;
    controller->doDelete = del;
}
