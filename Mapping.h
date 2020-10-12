#ifndef PREFORK_SERVER_MAPPING_H
#define PREFORK_SERVER_MAPPING_H

struct Mapping {
    int fd;
    int fsize;
    char* dataPtr;
};

#endif //PREFORK_SERVER_MAPPING_H
