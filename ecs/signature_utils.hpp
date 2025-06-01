/**
 * @brief Short set of utils for bit operations on signatures
 */

#pragma once
#include "common.hpp"
#include "id_utils.hpp"

// NOTE: SIGNATURES ALL BASED ON COMPONENTS
namespace signature_utils {
template <typename T>
Signature set_bit(Signature signature) {
    Component_ID id = id_utils::get_component_id<T>();
    return signature | (1u << id);
}
template <typename T>
Signature reset_bit(Signature signature) {
    Component_ID id = id_utils::get_component_id<T>();
    return signature & ~(1u << id);
}
}; // namespace signature_utils
