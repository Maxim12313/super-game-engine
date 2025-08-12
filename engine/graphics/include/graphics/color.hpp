#pragma once

namespace graphics {

// ranging [0, 1] for all
struct Color {
    float red;
    float green;
    float blue;
};

constexpr Color CYAN = {0.2f, 0.3f, 0.3f};
constexpr Color PURPLE = {0.5, 1, 0};

constexpr Color RED = {1, 0, 0};
constexpr Color GREEN = {0, 1, 0};
constexpr Color BLUE = {0, 0, 1};
constexpr Color GRAY = {0.5, 0.5, 0.5};

} // namespace graphics
