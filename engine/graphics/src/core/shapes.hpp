#include <array>
#pragma once

namespace graphics {
// clang-format off
namespace internal {
constexpr std::array<float, 18> SQUARE_VERTICES = {
    0, 0, 0,
    1, 0, 0,
    1, 1, 0,

    1, 1, 0,
    0, 1, 0,
    0, 0, 0
    };
}
// clang-format on
} // namespace graphics
