#pragma once
#include "common.hpp"
#include <vector>
#include "../src/core/igroup.hpp"

namespace ecs {
template <typename... Components>
class Group : public internal::IGroup {};

}; // namespace ecs
