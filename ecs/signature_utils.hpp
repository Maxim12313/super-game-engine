#pragma once
#include "common.hpp"
#include "type_id_utils.hpp"

namespace signature_utils {
template <typename T>
Signature set_bit(Signature signature) {
    Type_ID id = type_id_utils::get_type_id<T>();
    return signature | (1u << id);
}
template <typename T>
Signature reset_bit(Signature signature) {
    Type_ID id = type_id_utils::get_type_id<T>();
    return signature & ~(1u << id);
}
}; // namespace signature_utils
