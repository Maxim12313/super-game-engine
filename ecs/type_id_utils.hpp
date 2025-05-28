#pragma once
#include "common.hpp"
#include <cstdint>

namespace type_id_utils {
static Type_ID curr = 0;
template <typename T>
Type_ID get_type_id() {
    // static id init exactly once for each type, otherwise just ret existing
    static Type_ID id = curr++;
    return id;
}

}; // namespace type_id_utils
