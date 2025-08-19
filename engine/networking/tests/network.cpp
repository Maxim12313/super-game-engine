#include "../src/setup.hpp"
#include <iostream>
#include <sys/socket.h>

int main() {
    const char *port = "5000";
    int socket = setup(port, SOCK_STREAM);
    std::cout << socket << "\n";
}
