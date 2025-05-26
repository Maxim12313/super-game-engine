#pragma once
#include "my_color.hpp"
#include "position.hpp"
#include "radius.hpp"
#include "speed.hpp"
#include "velocity.hpp"
#include "wasd_movable.hpp"

using Type_ID = uint32_t;
static Type_ID curr = 0;
template <typename T>
Type_ID get_type_id() {
    // static id init exactly once for each type, otherwise just ret existing
    static Type_ID id = curr++;
    return id;
}
