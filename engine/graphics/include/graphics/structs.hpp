#pragma once

#include <cstdint>
namespace graphics {

struct Color {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    uint8_t alpha;
};

struct Rect {
    double x;
    double y;
    double w;
    double h;
    Color color;
};

} // namespace graphics
