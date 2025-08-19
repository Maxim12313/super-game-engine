/**
 * @file
 * @brief Set of ECS common definitions
 */

#pragma once
#include <bitset>
#include <cstdint>

namespace ecs {

constexpr int MAX_ENTITIES = int(1e9);
constexpr int MAX_COMPONENTS = 64;

using Entity = uint32_t;
using Component_ID = uint32_t;
using Signature = std::bitset<MAX_COMPONENTS>;

} // namespace ecs
