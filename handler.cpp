#include "handler.h"
#include <sstream>
#include <iostream>
#include <fstream>
#include "mime_types.h"
#include <filesystem>

std::string url_decode(std::string& file_name) {
    std::string tmp;
    int i = 0, j = 0;
    char ch;
    for (i=0; i < file_name.size(); ++i) {
        if (int(file_name[i]) == 37) {
            sscanf(file_name.substr(i + 1, 2).c_str(), "%x", &j);
            ch = static_cast<char>(j);
            tmp += ch;
            i = i + 2;
        } else {
            tmp += file_name[i];
        }
    }

    return tmp;
}

int Handler::handler(std::string &response, Request &req, std::string& doc_root, std::string &path) {
   if (req.method != "GET" && req.method != "HEAD") {
        response = "HTTP/1.1 405 Method Not Allowed\r\nServer: server on c++\r\nConnection: close\r\n\r\n";
        return 0;
    }

    if (req.uri.find("../") != std::string::npos) {
        response = "HTTP/1.1 403 Forbidden\r\nServer: server on c++\r\nConnection: close\r\n\r\n";
        return 0;
    }

    auto pos = req.uri.find('?');
    if (pos != std::string::npos) {
        req.uri = req.uri.substr(0, pos);
    }

    req.uri = url_decode(req.uri);
    if (req.uri.rfind('/') == req.uri.size() - 1) {
        req.uri += "index.html";
    }

    pos = req.uri.rfind('.');
    if (pos == std::string::npos) {
        response = "HTTP/1.0 400 Bad Request\r\nServer: server on c++\r\nConnection: close\r\n\r\n";
        return 0;
    }

    bool bad_path = false;
    path = doc_root + req.uri;
    int size = 0;
    try {
        size = std::filesystem::file_size(path);
    } catch(std::filesystem::filesystem_error& e) {
        bad_path = true;
        std::cout << e.what() << '\n';
        if (req.uri.rfind("index.html") != std::string::npos) {
            response = "HTTP/1.0 403 Forbidden\r\nServer: server on c++\r\nConnection: close\r\n\r\n";
        } else {
            response = "HTTP/1.0 404 Not Found\r\nServer: server on c++\r\nConnection: close\r\n\r\n";
        }
    }
    if (bad_path) {
        return 0;
    }

    std::string mime_type = get_mime_type(req.uri.substr(pos));
    std::stringstream resp;
    resp << "HTTP/1.1 200 OK\r\n" << "Content-Type: " << mime_type << "\r\n"
    << "Server: server on c++\r\n" << "Content-Length: " << size
    << "\r\nConnection: close"
    << "\r\n\r\n";

    response = std::move(resp.str());

    return size;
}

void Handler::error_handler(std::string &response, Request &req) {
    response = "HTTP/1.0 400 Bad Request\r\nServer: server on c++\r\nConnection: close\r\n\r\n";
}
