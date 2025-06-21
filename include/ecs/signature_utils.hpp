/**
 * @file
 * @brief Short set of utils for bit operations on signatures.
 * Note that all signatures are based on components
 */

#pragma once
#include "common.hpp"
#include "id_utils.hpp"

namespace signature_utils {

/**
 * @brief Set T component bit or do nothing if already set
 */
template <typename T>
void set_bit(Signature &signature) {
    Component_ID id = id_utils::get_component_id<T>();
    signature = signature | (1u << id);
}

/**
 * @brief Reset T component bit or do nothing if already set
 */
template <typename T>
void reset_bit(Signature &signature) {
    Component_ID id = id_utils::get_component_id<T>();
    signature = signature & ~(1u << id);
}

/**
 * @return True if T component bit is set
 */
template <typename T>
bool has_bit(Signature signature) {
    Component_ID id = id_utils::get_component_id<T>();
    return signature & (1 << id);
}

template <typename... T>
Signature set_signature() {
    Signature signature = 0;
    (set_bit<T>(signature), ...);
    return signature;
}

}; // namespace signature_utils
