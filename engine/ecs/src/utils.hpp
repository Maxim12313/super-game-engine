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

/**
 * @brief Set T component bit or do nothing if already set
 */
template <typename Component>
Signature set_bit(Signature signature) {
    Component_ID id = get_component_id<Component>();
    return signature | (1u << id);
}

/**
 * @brief Reset T component bit or do nothing if already set
 */
template <typename T>
Signature reset_bit(Signature signature) {
    Component_ID id = get_component_id<T>();
    return signature & ~(1u << id);
}

/**
 * @return True if T component bit is set
 */
template <typename T>
bool has_bit(Signature signature) {
    Component_ID id = get_component_id<T>();
    return signature & (1 << id);
}

template <typename... Component>
Signature set_signature() {
    Signature signature = 0;
    ((signature |= set_bit<Component>(signature)), ...);
    return signature;
}

}; // namespace ecs::internal::utils
