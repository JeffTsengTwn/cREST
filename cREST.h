#ifndef cREST_h__
#define cREST_h__

#include <fcgi_stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cjson/cJSON.h>

#define PATH_SIZE 256
#define TYPE_SIZE 256
#define CONTENT_SIZE 8192
#define QUERY_SIZE 2048
#define BODY_SIZE 8192
#define METHOD_SIZE 8
#define PARAM_KEY_SIZE 128
#define PARAM_VALUE_SIZE 512
#define MAX_PARAMS 32

typedef struct _Param {
    char key[PARAM_KEY_SIZE];
    char value[PARAM_VALUE_SIZE];
} Param;

/* Holds everything cREST_dispatch() was able to parse out of the current
 * FastCGI request: the query string (as key/value Params), the raw body,
 * and - when Content-Type is application/json - the parsed cJSON body. */
typedef struct _Request {
    char method[METHOD_SIZE];
    char path[PATH_SIZE];
    char query[QUERY_SIZE];
    char content_type[TYPE_SIZE];
    char body[BODY_SIZE];
    int content_length;
    Param params[MAX_PARAMS];
    int param_count;
    cJSON *json;
} Request;

typedef struct _Response {
    int code;
    char type[TYPE_SIZE];
    char content[CONTENT_SIZE];
} Response;

typedef void (*Method)(Request *, Response *);

typedef struct _Controller {
    char path[PATH_SIZE];
    Method doGet;
    Method doPost;
    Method doPut;
    Method doDelete;
    Method doPatch;
    Response response;
} Controller;

extern Controller *cREST_dispatch(FCGX_Stream *in, FCGX_ParamArray envp, Controller *controllers[]);
extern void cREST_init_controller(Controller *, char *, Method, Method, Method, Method, Method);

/* Request helpers */
extern const char *cREST_get_param(Request *request, const char *key);
extern cJSON *cREST_get_json_param(Request *request, const char *key);

/* Response helpers */
extern void cREST_set_response(Response *response, int code, const char *type, const char *content);
extern void cREST_set_json_response(Response *response, int code, cJSON *json);
extern void cREST_set_error_response(Response *response, int code, const char *message);

#ifdef DEBUG
#define DEBUG_PRINT(fmt, ...) \
    do { \
        FILE *pFile = NULL; \
        pFile = fopen("/tmp/crest.log", "a+"); \
        if (NULL != pFile) { \
            fprintf(pFile, "[DEBUG] %s:%d: " fmt "\n", __FUNCTION__, __LINE__, ##__VA_ARGS__); \
            fclose(pFile); \
        } \
    } while (0)

#else
#define DEBUG_PRINT(fmt, ...)
#endif

#endif
