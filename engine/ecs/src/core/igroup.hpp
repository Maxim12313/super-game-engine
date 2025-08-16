#pragma once
#include <vector>
#include "ecs/common.hpp"

namespace ecs::internal {
class ISparseSet;

class IGroup {
public:
    virtual ~IGroup() = default;

    IGroup(std::vector<ISparseSet *> &sets);

    // Callback on entity update watching in each sparse set
    void update(Entity entity);

private:
    std::vector<ISparseSet *> m_sets;
};

}; // namespace ecs::internal
