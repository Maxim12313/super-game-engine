#pragma once
#include <vector>
#include "ecs/common.hpp"

namespace ecs::internal {
class ISparseSet;
};

// NOTE: Lifetime of ordering is tied to the group
namespace ecs {

class Group {
public:
    virtual ~Group() = default;

    Group(std::vector<internal::ISparseSet *> &sets);

    // Callback on entity update watching in each sparse set
    void update(Entity entity);

private:
    std::vector<internal::ISparseSet *> m_sets;
};

}; // namespace ecs
