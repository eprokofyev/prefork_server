#include <iostream>
#include <tuple>
#include <zconf.h>
#include "config.h"
#include "server.h"

int main() {
    Config config;
    bool status;
    std::tie(config, status) = Config::read_config("/home/evgeny/httpd.conf");
    if (!status) {
        std::cout << "bad config" <<std::endl;
    }

    try
    {
        Server s(8085, 50, config.doc_root);
        for (int i = 0; i < 4; i++) {
            pid_t pid = fork();
            if (pid == fork()) {
                break;
            } else if (pid < 0) {
                std::cout << "bad fork " << std::endl;
            }
        }

        while(true) {
            std::shared_ptr<Client> client = s.accept();
            client->serve();
        }
    }
    catch (std::exception& e)
    {
        std::cerr << "exception: " << e.what() << "\n";
    }


    std::cout << "Hello, World!" << std::endl;
    return 0;
}
