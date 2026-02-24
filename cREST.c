#include "cREST.h"

Controller *cREST_dispatch(int argc, char *argv[], char *envp[], Controller *controllers[]) {
    DEBUG_PRINT("Enter function.");
    int idx = 0;
    Controller *controller = NULL;
    Response *response = NULL;
    const char *path_info = getenv("PATH_INFO");
    const char *request_method = getenv("REQUEST_METHOD");

    if (NULL == path_info || NULL == request_method) {
        DEBUG_PRINT("PATH_INFO or REQUEST_METHOD is NULL");
        return NULL;
    }

    for (idx = 0; controllers[idx] != NULL; idx++) {
        DEBUG_PRINT("Dispatch loop idx = %d", idx);
        controller = controllers[idx];
        response = &controller->response;
        memset(response, 0x00, sizeof(Response));
        DEBUG_PRINT("PATH_INFO = %s", path_info);
        if (0 == strcmp(path_info, controller->path)) {
            if (controller->doGet && 0 == strcmp(request_method, "GET")) {
                DEBUG_PRINT("Case GET");
                controller->doGet(argc, argv, envp, response);
                return controller;
            } else if (controller->doPost && 0 == strcmp(request_method, "POST")) {
                DEBUG_PRINT("Case POST");
                controller->doPost(argc, argv, envp, response);
                return controller;
            } else if (controller->doPut && 0 == strcmp(request_method, "PUT")) {
                DEBUG_PRINT("Case PUT");
                controller->doPut(argc, argv, envp, response);
                return controller;
            } else if (controller->doDelete && 0 == strcmp(request_method, "DELETE")) {
                DEBUG_PRINT("Case DELETE");
                controller->doDelete(argc, argv, envp, response);
                return controller;
            } else if (controller->doPatch && 0 == strcmp(request_method, "PATCH")) {
                DEBUG_PRINT("Case PATCH");
                controller->doPatch(argc, argv, envp, response);
                return controller;
            }
        }
    }
    return NULL;
}

void cREST_init_controller(Controller *controller, char *path, Method get, Method put, Method post, Method del, Method patch) {
    strncpy(controller->path, path, sizeof(controller->path) - 1);
    controller->path[sizeof(controller->path) - 1] = '\0';
    controller->doGet = get;
    controller->doPut = put;
    controller->doPost = post;
    controller->doDelete = del;
    controller->doPatch = patch;
}
