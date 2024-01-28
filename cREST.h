#ifndef cREST_h__
#define cREST_h__

#include <fcgi_stdio.h>
#include <stdlib.h>
#include <string.h>

#define PATH_SIZE 256
#define TYPE_SIZE 256
#define CONTENT_SIZE 1024

typedef struct _Response {
    int code;
    char type[TYPE_SIZE];
    char content[CONTENT_SIZE];
} Response;

typedef void (*Method)(int, char *[], char *[], Response *);

typedef struct _Controller {
    char path[PATH_SIZE];
    Method doGet;
    Method doPost;
    Method doPut;
    Method doDelete;
    Method doUnsupport;
    Response response;
} Controller;

extern Controller *cREST_dispatch(int, char *[], char *[], Controller *[]);
extern void cREST_init_controller(Controller *, char *, Method, Method, Method, Method);

#endif
