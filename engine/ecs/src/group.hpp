#pragma once
#include <vector>
#include "ecs/common.hpp"

// NOTE: Lifetime of ordering is tied to the group
namespace ecs::internal {
class ISparseSet;

class Group {
public:
    Group(std::vector<ISparseSet *> &sets);

    // Callback on entity update watching in each sparse set
    void update(Entity entity);

private:
    std::vector<ISparseSet *> m_sets;
};

}; // namespace ecs::internal
