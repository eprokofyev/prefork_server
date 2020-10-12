#ifndef PREFORK_SERVER_SERVER_H
#define PREFORK_SERVER_SERVER_H

#include "client.h"
#include "memory"
#include "Mapping.h"
#include <unistd.h>
#include <string>
#include <unordered_map>


class Server {

public:

    Server(int port, int limit, std::string doc_root);

    ~Server();

    std::shared_ptr<Client> accept();

private:

    int socket;

    std::string doc_root_;

    std::unordered_map<std::string, Mapping> map;

};

#endif //PREFORK_SERVER_SERVER_H
