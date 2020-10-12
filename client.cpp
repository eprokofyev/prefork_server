#include "client.h"
#include <string>
#include <cerrno>
#include <cstring>
#include <sys/socket.h>
#include <sys/sendfile.h>
#include <iostream>
#include "parser.h"
#include "handler.h"
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

Client::Client(int s, std::string doc_root, std::unordered_map<std::string, Mapping>& map) : socket(s), doc_root_(doc_root), map_(map) {}

Client::~Client() {
    if (socket > 0)
        ::close(socket);
}

void Client::serve() {
    try {
        std::string req = read();
        auto status = Parser::parse(request, req);
        if (status == Status::Ready) {
            std::string path;
            int size = Handler::handler(response, request, doc_root_, path);
            write(path, size);
        } else if (status == Status::Error) {
            Handler::error_handler(response, request);
            write("", 0);
        }
    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}

std::string Client::read() const{
    std::string result;
    int bytes = 8000;
    char *buf = new char[bytes];
    size_t r = 0;
    while (r != bytes) {
        ssize_t rc = ::recv(socket, buf + r, bytes - r, 0);
        if (rc == -1 || rc == 0) {
            delete [] buf;
            throw std::runtime_error("read failed: " + std::string(std::strerror(errno)));
        }

        r += rc;
        result.append(buf, rc);
        if (result.find("\r\n\r\n") != std::string::npos) {
            break;
        }
    }

    delete [] buf;
    return result;
}

void Client::write(const std::string& path, int size_file) {
    send(response.data(), response.size());

    if (request.method == "GET" && !path.empty()) {
        int fd = open(path.c_str(), 0);
        sendfile(socket, fd, 0, size_file);
        close(fd);
    }

}

void Client::send(const char* start, int size) const {
    size_t left = size;
    ssize_t sent = 0;
    int flags = 0;

    while (left > 0) {
        sent = ::send(socket, start + sent, size - sent, flags);
        if (-1 == sent)
            throw std::runtime_error("write failed: " + std::string(strerror(errno)));
        left -= sent;
    }
}