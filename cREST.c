#include "cREST.h"

Controller *cREST_dispatch(int argc, char *argv[], char *envp[], Controller *controllers[]) {
    int idx = 0;
    Controller *controller = NULL;
    Response *response = &controller->response;
    
    memset(response, 0x00, sizeof(Response));
    for (idx = 0; idx < sizeof(controllers) / sizeof(Controller *); idx++) {
        controller = controllers[idx];
        if (0 == strcmp(getenv("REQUEST_URI"), controller->path)) {
            if (controller->doGet && 0 == strcmp(getenv("REQUEST_METHOD"), "GET")) {
                controller->doGet(argc, argv, envp, response);
                return controller;
            } else if (controller->doPost && 0 == strcmp(getenv("REQUEST_METHOD"), "POST")) {
                controller->doPost(argc, argv, envp, response);
                return controller;
            } else if (controller->doPut && 0 == strcmp(getenv("REQUEST_METHOD"), "PUT")) {
                controller->doPut(argc, argv, envp, response);
                return controller;
            } else if (controller->doDelete && 0 == strcmp(getenv("REQUEST_METHOD"), "DELETE")) {
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
