#ifndef PREFORK_SERVER_CLIENT_H
#define PREFORK_SERVER_CLIENT_H

#include <string>
#include <unordered_map>
#include "request.h"
#include "Mapping.h"

class Client {

public:

    Client(int s, std::string doc_root, std::unordered_map<std::string, Mapping>& map);

    ~Client();

    void serve();

private:

    std::string read() const;

    void write(const std::string& path, int size_file);

    void send(const char* start, int size) const;

    int socket;

    std::string doc_root_;

    Request request;

    std::string response;

    std::unordered_map<std::string, Mapping>& map_;

};

#endif //PREFORK_SERVER_CLIENT_H
