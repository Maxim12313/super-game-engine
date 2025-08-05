#include <array>
#pragma once

// clang-format off
namespace internal {
constexpr std::array<float, 18> SQUARE_VERTICES = {
    -0.5, 0.5,  0,
    0.5,  0.5,  0,
    0.5, -0.5, 0,
    0.5, 0.5, 0,
    0.5, -0.5, 0,
    -0.5, -0.5, 0
    };
}
// clang-format on
