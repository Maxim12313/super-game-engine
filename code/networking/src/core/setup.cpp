#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include "wrappers.hpp"
#include "setup.hpp"

// returns -1 on failure
// otherwise returns sockfd on success
int setup(const char *port, int ai_socktype, int ai_family) {
    addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    addrinfo *raw_list;
    int status = getaddrinfo(nullptr, port, &hints, &raw_list);
    if (status != 0) {
        std::cerr << "erorr getting addr info: " << gai_strerror(status)
                  << "\n";
        return -1;
    }

    AddrInfoPtr addr_list(raw_list);
    addrinfo *info = addr_list.get();
    while (info) {
        int fd = socket(info->ai_family, info->ai_socktype, info->ai_protocol);
        if (fd != -1) {
            int stat = bind(fd, info->ai_addr, info->ai_addrlen);
            if (stat != -1) {
                return fd;
            }
        }
        info = info->ai_next;
    }
    std::cerr << "failed to find suitable address\n";
    return -1;
}
