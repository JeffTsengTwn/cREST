// helloworld
#include "cREST.h"
#include <fcgi_stdio.h>

// 405 頁面的 HTML 內容
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

void handleGet(int argc, char *argv[], char *envp[], Response *response) {
    response->code = 200;
    sprintf(response->type, "application/json");
    sprintf(response->content, "{\"message\" : \"Hello world!\"}");
}

void main(void) {
    // 初始化控制器
    Controller helloController;
    cREST_init_controller(&helloController, "/hello", handleGet, NULL, NULL, NULL);

    // 註冊控制器
    Controller *controllers[] = {&helloController};
    Controller *controller = NULL;
    Response *response = NULL;
    // FastCGI 初始化
    FCGX_Init();
    FCGX_Request request;

    // 處理 FastCGI 請求
    while (FCGX_Accept_r(&request) == 0) {
        // 處理請求
        controller =  cREST_dispatch(0, NULL, NULL, controllers);
            
        if(controller) {
            // 將回應寫回 FastCGI
            response = &(controller->response);
            FCGX_FPrintF(request.out, "Status: %d OK\r\n", response->code);
            FCGX_FPrintF(request.out, "Content-type: %s\r\n\r\n", response->type);
            FCGX_FPrintF(request.out, "%s\r\n", response->content);
        } else {
            // Handle other HTTP methods if needed
            FCGX_FPrintF(request.out, "Status: %d Method Not Allowed\r\n", 405);
            FCGX_FPrintF(request.out, "Content-type: %s\r\n\r\n", "text/html" );
            FCGX_FPrintF(request.out, "%s\r\n", methodNotAllowedPage);
        }

        // 結束請求
        FCGX_Finish_r(&request);
    }

}