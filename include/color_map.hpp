#pragma once
#include "globals.hpp"

enum class Color_ID {
    red = 0,
    orange,
    yellow,
    green,
    blue,
    black,
    white,
};

namespace ColorMap {
constexpr Color values[] = {
    RED, ORANGE, YELLOW, GREEN, BLUE, BLACK, WHITE,
};

constexpr Color get(Color_ID id) {
    return values[int(id)];
}

}; // namespace ColorMap
