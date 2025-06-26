/**
 * @file
 * @brief Short set of utils for bit operations on signatures.
 * Note that all signatures are based on components
 */

#pragma once
#include "common.hpp"
#include "id_utils.hpp"

namespace internal {

/**
 * @brief Set T component bit or do nothing if already set
 */
template <typename Component>
Signature set_bit(Signature signature) {
    Component_ID id = internal::get_component_id<Component>();
    return signature | (1u << id);
}

/**
 * @brief Reset T component bit or do nothing if already set
 */
template <typename T>
Signature reset_bit(Signature signature) {
    Component_ID id = internal::get_component_id<T>();
    return signature & ~(1u << id);
}

/**
 * @return True if T component bit is set
 */
template <typename T>
bool has_bit(Signature signature) {
    Component_ID id = internal::get_component_id<T>();
    return signature & (1 << id);
}

template <typename... Component>
Signature set_signature() {
    Signature signature = 0;
    ((signature |= set_bit<Component>(signature)), ...);
    return signature;
}

}; // namespace internal
