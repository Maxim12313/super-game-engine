#include "ecs/group.hpp"
#include "isparse_set.hpp"
#include "utils/macros.hpp"

namespace ecs {

// class public ********
Group::Group(std::vector<internal::ISparseSet *> &sets)
    : m_sets(std::move(sets)) {
}

// TODO: finish implementing
void Group::add_update(Entity entity) {
    // detect if changes need to be made
    if (!should_add(entity))
        return;

    int idx = m_entities.size();
    // swap entity into the first [0, idx]
    for (auto &set : m_sets)
        set->swap_ent_idx(entity, idx);

    // include entity
    m_entities.insert(entity);
}

void Group::remove_update(Entity entity) {
    // detect if changes need to be made
    if (!should_remove(entity))
        return;

    int idx = m_entities.size() - 1;
    // swap entity into last position of [0, idx]
    for (auto &set : m_sets) {
        set->swap_ent_idx(entity, idx);
    }

    // kickout entity
    m_entities.erase(entity);
}
// class private ********

bool Group::should_add(Entity entity) const {
    ASSERT_MSG(!contains(entity),
               "if part of group, then push/emplace double register")
    return has_all(entity);
}

bool Group::should_remove(Entity entity) const {
    // we are part of the group but no longer have every component
    return contains(entity) && !has_all(entity);
}

bool Group::contains(Entity entity) const {
    return m_entities.count(entity);
}

bool Group::has_all(Entity entity) const {
    for (auto &set : m_sets) {
        if (!set->contains(entity))
            return false;
    }
    return true;
}

} // namespace ecs
