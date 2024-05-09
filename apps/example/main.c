// helloworld
#include "cREST.h"
#include <fcgi_stdio.h>

static void PrintEnv(char **envp)
{

    for( ; *envp != NULL; envp++) {
        DEBUG_PRINT("%s\n", *envp);
    }

}

// HTML content for the 405 page
const char *methodNotAllowedPage =
    "<!DOCTYPE html>\n"
    "<html lang=\"en\">\n"
    "<head>\n"
    "    <meta charset=\"UTF-8\">\n"
    "    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n"
    "    <title>Method Not Allowed</title>\n"
    "    <style>\n"
    "        body {\n"
    "            font-family: Arial, sans-serif;\n"
    "            text-align: center;\n"
    "            padding: 50px;\n"
    "        }\n"
    "        h1 {\n"
    "            color: #dc3545;\n"
    "        }\n"
    "        p {\n"
    "            color: #343a40;\n"
    "        }\n"
    "    </style>\n"
    "</head>\n"
    "<body>\n"
    "    <h1>405 - Method Not Allowed</h1>\n"
    "    <p>The requested method is not supported for this resource.</p>\n"
    "</body>\n"
    "</html>\n";

void handleGet(Request *request, Response *response) {
    cJSON *body = cJSON_CreateObject();
    const char *name = cREST_get_param(request, "name");

    cJSON_AddStringToObject(body, "message", "Hello world!");
    if (name) {
        cJSON_AddStringToObject(body, "name", name);
    }

    cREST_set_json_response(response, 200, body);
}

void handlePost(Request *request, Response *response) {
    if (NULL == request->json) {
        cREST_set_error_response(response, 400, "Request body must be JSON.");
        return;
    }

    /* Echo the JSON body straight back to demonstrate PATCH/POST + JSON support. */
    cREST_set_json_response(response, 201, cJSON_Duplicate(request->json, 1));
}

void main(int argc, char *argv[], char *env[]) {

    FCGX_Stream *in, *out, *err;
    FCGX_ParamArray envp;

    // Initialize the controller
    Controller helloController;
    cREST_init_controller(&helloController, "/hello", handleGet, NULL, handlePost, NULL, handlePost);

    // Register controllers (NULL-terminated)
    Controller *controllers[] = {&helloController, NULL};
    Controller *controller = NULL;
    Response *response = NULL;
    // Initialize FastCGI
    FCGX_Init();

    DEBUG_PRINT("After FCGX_Init()");
    // Handle FastCGI requests
    while (FCGX_Accept(&in, &out, &err, &envp) >= 0) {
        DEBUG_PRINT("Enter FCGX_Accept loop");

        PrintEnv(envp);

        // Handle the request
        controller = cREST_dispatch(in, envp, controllers);

        if(controller) {
            // Write the response back to FastCGI
            response = &(controller->response);
            FCGX_FPrintF(out, "Status: %d OK\r\n", response->code);
            FCGX_FPrintF(out, "Content-type: %s\r\n\r\n", response->type);
            FCGX_FPrintF(out, "%s\r\n", response->content);
        } else {
            // Handle other HTTP methods if needed
            FCGX_FPrintF(out, "Status: %d Method Not Allowed\r\n", 405);
            FCGX_FPrintF(out, "Content-type: %s\r\n\r\n", "text/html" );
            FCGX_FPrintF(out, "%s\r\n", methodNotAllowedPage);
        }
    }

}
