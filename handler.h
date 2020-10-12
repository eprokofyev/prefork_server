#ifndef HTTP_SERVER_HANDLER_H
#define HTTP_SERVER_HANDLER_H

#include <string>
#include "request.h"

struct Handler {
    static int handler(std::string &response, Request &req, std::string& doc_root, std::string& path);

    static void error_handler(std::string &response, Request &req);
};

#endif //HTTP_SERVER_HANDLER_H
