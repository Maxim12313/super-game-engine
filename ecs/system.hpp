#pragma once
#include "common.hpp"

class System {
public:
    virtual ~System() {
    }

    virtual void check_add(Entity entity) = 0;
    virtual void run() = 0;
};
