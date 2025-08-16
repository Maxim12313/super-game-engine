#pragma once
#include <vector>
#include "ecs/common.hpp"
#include <unordered_set>

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
    void add_update(Entity entity);

    // Callback on entity update watching in each sparse set
    void remove_update(Entity entity);

private:
    bool should_add(Entity entity) const;
    bool should_remove(Entity entity) const;
    bool has_all(Entity entity) const;
    bool contains(Entity entity) const;

private:
    std::vector<internal::ISparseSet *> m_sets;
    std::unordered_set<Entity> m_entities;
};

}; // namespace ecs
