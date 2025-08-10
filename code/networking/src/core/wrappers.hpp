#pragma once

#include <memory>
#include <netdb.h>
struct AddrInfoDeleter {
    void operator()(addrinfo *info) {
        freeaddrinfo(info);
    }
};

using AddrInfoPtr = std::unique_ptr<addrinfo, AddrInfoDeleter>;
