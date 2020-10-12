#ifndef PREFORK_SERVER_REQUEST_H
#define PREFORK_SERVER_REQUEST_H

#include <string>

struct Request {
    std::string method;
    std::string uri;
};

#endif //PREFORK_SERVER_REQUEST_H
