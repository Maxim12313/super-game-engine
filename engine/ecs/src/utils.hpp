#pragma once
#include "ecs/common.hpp"

namespace ecs::internal::utils {

static Component_ID curr_component = 0;
template <typename T>
Component_ID get_component_id() {
    // static id init exactly once for each type, otherwise just ret existing
    static Component_ID id = curr_component++;
    return id;
}

}; // namespace ecs::internal::utils
