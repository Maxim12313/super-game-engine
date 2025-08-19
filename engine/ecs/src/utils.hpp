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

// set the bit for each component
template <typename... Components>
Signature get_signature() {
    Signature sig;
    (sig.set(get_component_id<Components>()), ...);
    return sig;
}

}; // namespace ecs::internal::utils
