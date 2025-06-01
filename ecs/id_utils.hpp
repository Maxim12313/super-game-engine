#pragma once
#include "common.hpp"

namespace id_utils {

static Component_ID curr_component = 0;
template <typename T>
Component_ID get_component_id() {
    // static id init exactly once for each type, otherwise just ret existing
    static Component_ID id = curr_component++;
    return id;
}

static System_ID curr_system = 0;
template <typename T>
System_ID get_system_id() {
    // static id init exactly once for each type, otherwise just ret existing
    static System_ID id = curr_system++;
    return id;
}

}; // namespace id_utils
