#ifndef HTTP_SERVER_PARSER_H
#define HTTP_SERVER_PARSER_H

#include <utility>
#include <sstream>
#include "request.h"

enum Status {
    Ready,
    InProgress,
    Error
};

struct Parser {
    static Status parse(Request &request, const std::string& req);
};

#endif //HTTP_SERVER_PARSER_H
