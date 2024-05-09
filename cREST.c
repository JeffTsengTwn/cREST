#include "cREST.h"

static int hex_value(char c) {
    if (c >= '0' && c <= '9') {
        return c - '0';
    }
    if (c >= 'a' && c <= 'f') {
        return c - 'a' + 10;
    }
    if (c >= 'A' && c <= 'F') {
        return c - 'A' + 10;
    }
    return -1;
}

static void url_decode(const char *src, char *dst, size_t dst_size) {
    size_t di = 0;

    if (NULL == dst || 0 == dst_size) {
        return;
    }

    if (NULL == src) {
        dst[0] = '\0';
        return;
    }

    while (*src && di + 1 < dst_size) {
        if ('%' == *src && src[1] && src[2] && hex_value(src[1]) >= 0 && hex_value(src[2]) >= 0) {
            dst[di++] = (char)((hex_value(src[1]) << 4) | hex_value(src[2]));
            src += 3;
        } else if ('+' == *src) {
            dst[di++] = ' ';
            src++;
        } else {
            dst[di++] = *src++;
        }
    }
    dst[di] = '\0';
}

/* Parses "a=1&b=2" (query string or x-www-form-urlencoded body) into
 * request->params, appending to whatever is already there. */
static void parse_params(const char *raw, Request *request) {
    char buffer[BODY_SIZE];
    char *pair = NULL;
    char *saveptr = NULL;

    if (NULL == raw || '\0' == raw[0] || NULL == request) {
        return;
    }

    strncpy(buffer, raw, sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';

    for (pair = strtok_r(buffer, "&", &saveptr);
         NULL != pair && request->param_count < MAX_PARAMS;
         pair = strtok_r(NULL, "&", &saveptr)) {
        Param *param = &request->params[request->param_count];
        char *eq = strchr(pair, '=');

        if (eq) {
            *eq = '\0';
            url_decode(pair, param->key, sizeof(param->key));
            url_decode(eq + 1, param->value, sizeof(param->value));
        } else {
            url_decode(pair, param->key, sizeof(param->key));
            param->value[0] = '\0';
        }
        request->param_count++;
    }
}

static void read_body(FCGX_Stream *in, const char *content_length_str, const char *content_type, Request *request) {
    int content_length = 0;
    int read_bytes = 0;

    if (NULL == in || NULL == content_length_str) {
        return;
    }

    content_length = atoi(content_length_str);
    if (content_length <= 0) {
        return;
    }
    if (content_length > BODY_SIZE - 1) {
        content_length = BODY_SIZE - 1;
    }

    read_bytes = FCGX_GetStr(request->body, content_length, in);
    if (read_bytes < 0) {
        read_bytes = 0;
    }
    request->body[read_bytes] = '\0';
    request->content_length = read_bytes;

    if (0 == read_bytes) {
        return;
    }

    if (content_type && NULL != strstr(content_type, "application/json")) {
        request->json = cJSON_Parse(request->body);
    } else {
        parse_params(request->body, request);
    }
}

Controller *cREST_dispatch(FCGX_Stream *in, FCGX_ParamArray envp, Controller *controllers[]) {
    DEBUG_PRINT("Enter function.");
    int idx = 0;
    Controller *matched = NULL;
    Response *response = NULL;
    Request request;

    const char *path_info = FCGX_GetParam("PATH_INFO", envp);
    const char *request_method = FCGX_GetParam("REQUEST_METHOD", envp);
    const char *query_string = FCGX_GetParam("QUERY_STRING", envp);
    const char *content_length_str = FCGX_GetParam("CONTENT_LENGTH", envp);
    const char *content_type = FCGX_GetParam("CONTENT_TYPE", envp);

    if (NULL == path_info || NULL == request_method) {
        DEBUG_PRINT("PATH_INFO or REQUEST_METHOD is NULL");
        return NULL;
    }

    memset(&request, 0x00, sizeof(Request));
    strncpy(request.method, request_method, sizeof(request.method) - 1);
    strncpy(request.path, path_info, sizeof(request.path) - 1);

    if (content_type) {
        strncpy(request.content_type, content_type, sizeof(request.content_type) - 1);
    }

    if (query_string) {
        strncpy(request.query, query_string, sizeof(request.query) - 1);
        parse_params(query_string, &request);
    }

    read_body(in, content_length_str, content_type, &request);

    for (idx = 0; controllers[idx] != NULL; idx++) {
        DEBUG_PRINT("Dispatch loop idx = %d", idx);
        Controller *controller = controllers[idx];
        DEBUG_PRINT("PATH_INFO = %s", path_info);

        if (0 == strcmp(path_info, controller->path)) {
            response = &controller->response;
            memset(response, 0x00, sizeof(Response));

            if (controller->doGet && 0 == strcmp(request_method, "GET")) {
                DEBUG_PRINT("Case GET");
                controller->doGet(&request, response);
                matched = controller;
            } else if (controller->doPost && 0 == strcmp(request_method, "POST")) {
                DEBUG_PRINT("Case POST");
                controller->doPost(&request, response);
                matched = controller;
            } else if (controller->doPut && 0 == strcmp(request_method, "PUT")) {
                DEBUG_PRINT("Case PUT");
                controller->doPut(&request, response);
                matched = controller;
            } else if (controller->doDelete && 0 == strcmp(request_method, "DELETE")) {
                DEBUG_PRINT("Case DELETE");
                controller->doDelete(&request, response);
                matched = controller;
            } else if (controller->doPatch && 0 == strcmp(request_method, "PATCH")) {
                DEBUG_PRINT("Case PATCH");
                controller->doPatch(&request, response);
                matched = controller;
            }
            break;
        }
    }

    if (request.json) {
        cJSON_Delete(request.json);
        request.json = NULL;
    }

    return matched;
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

const char *cREST_get_param(Request *request, const char *key) {
    int i = 0;

    if (NULL == request || NULL == key) {
        return NULL;
    }

    for (i = 0; i < request->param_count; i++) {
        if (0 == strcmp(request->params[i].key, key)) {
            return request->params[i].value;
        }
    }
    return NULL;
}

cJSON *cREST_get_json_param(Request *request, const char *key) {
    if (NULL == request || NULL == request->json || NULL == key) {
        return NULL;
    }
    return cJSON_GetObjectItemCaseSensitive(request->json, key);
}

void cREST_set_response(Response *response, int code, const char *type, const char *content) {
    if (NULL == response) {
        return;
    }

    response->code = code;

    if (type) {
        strncpy(response->type, type, sizeof(response->type) - 1);
        response->type[sizeof(response->type) - 1] = '\0';
    }

    if (content) {
        strncpy(response->content, content, sizeof(response->content) - 1);
        response->content[sizeof(response->content) - 1] = '\0';
    } else {
        response->content[0] = '\0';
    }
}

void cREST_set_json_response(Response *response, int code, cJSON *json) {
    char *printed = NULL;

    if (NULL == response) {
        if (json) {
            cJSON_Delete(json);
        }
        return;
    }

    if (NULL == json) {
        cREST_set_response(response, code, "application/json", "{}");
        return;
    }

    printed = cJSON_PrintUnformatted(json);

    response->code = code;
    strncpy(response->type, "application/json", sizeof(response->type) - 1);
    response->type[sizeof(response->type) - 1] = '\0';

    if (printed) {
        strncpy(response->content, printed, sizeof(response->content) - 1);
        response->content[sizeof(response->content) - 1] = '\0';
        cJSON_free(printed);
    } else {
        response->content[0] = '\0';
    }

    cJSON_Delete(json);
}

void cREST_set_error_response(Response *response, int code, const char *message) {
    cJSON *error = cJSON_CreateObject();
    cJSON_AddStringToObject(error, "error", message ? message : "unknown error");
    cREST_set_json_response(response, code, error);
}
