#include <iostream>
#include "parser.h"

Status Parser::parse(Request &request, const std::string& req) {
    std::stringstream ss(req);
    ss >> request.method;
    ss >> request.uri;

    std::string input;
    while (ss >> input)
    if (request.method == "GET" || request.method == "HEAD" || request.method == "OPTIONS" || request.method == "PUT"
    || request.method == "DELETE" || request.method == "POST") {
        return Status::Ready;
    } else {
        return Status::Error;
    }
}

