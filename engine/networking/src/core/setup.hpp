#pragma once
#include <sys/socket.h>

int setup(const char *port, int ai_socktype, int ai_family = AF_UNSPEC);
