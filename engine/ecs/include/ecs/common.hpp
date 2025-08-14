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

constexpr int MAX_ENTITIES = int(1e9);

} // namespace ecs
