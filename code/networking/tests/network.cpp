#include <cstring>
#include <iostream>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "missing host\n";
        return 1;
    }

    std::cout << "ip addressses for host: " << argv[1] << "\n";

    struct addrinfo hints;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    struct addrinfo *res;
    int status = getaddrinfo(argv[1], nullptr, &hints, &res);
    if (status != 0) {
        std::cerr << "erorr getting addr info: " << gai_strerror(status)
                  << "\n";
        return 1;
    }

    std::cout << "showing the addresses\n";

    char ipstr[INET6_ADDRSTRLEN];
    struct addrinfo *curr = res;
    while (curr) {
        struct sockaddr_in *ipv4;
        struct sockaddr_in6 *ipv6;
        void *addr;
        int family = curr->ai_family;
        std::string ipver;

        if (family == AF_INET) {
            ipv4 = (struct sockaddr_in *)curr->ai_addr;
            addr = &(ipv4->sin_addr);
            ipver = "ipv4";
        } else {
            ipv6 = (struct sockaddr_in6 *)curr->ai_addr;
            addr = &(ipv6->sin6_addr);
            ipver = "ipv6";
        }
        inet_ntop(family, addr, ipstr, sizeof(ipstr));
        std::cout << ipver << " " << ipstr << "\n";
        curr = curr->ai_next;
    }
}
