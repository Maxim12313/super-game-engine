/**
 * @file
 * @brief Set of ECS common definitions
 */

#pragma once
#include <cstdint>

namespace ecs {

using Entity = uint32_t;
using Signature = uint32_t;

using Component_ID = uint32_t;
using System_ID = uint32_t;

constexpr int MAX_ENTITIES = 30;
constexpr int MAX_COMPONENTS = 30;
constexpr int MAX_SYSTEMS = 30;

} // namespace ecs
