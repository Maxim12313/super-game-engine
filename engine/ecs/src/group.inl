#pragma once
#include "ecs/group.hpp"
#include "utils/macros.hpp"
#include "../src/isparse_set.hpp"
#include "utils/macros.hpp"
namespace ecs {

// class Iterator ********
template <typename projection>
class Group::Iterator {
public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = projection::value_type;

    using iterator_type = std::vector<Entity>::const_iterator;

public:
    Iterator(iterator_type it, const std::vector<internal::ISparseSet *> &sets)
        : m_it(it), m_sets(sets) {
    }
    Iterator &operator++() {
        m_it++;
        return *this;
    }
    bool operator!=(Group::Iterator<projection> &o) {
        return m_it != o.m_it;
    }
    value_type operator*() {
        return m_proj(*m_it, m_sets);
    }

private:
    projection m_proj;
    iterator_type m_it;
    const std::vector<internal::ISparseSet *> &m_sets;
};

// class public ********
inline Group::Group(std::vector<internal::ISparseSet *> &sets)
    : m_sets(std::move(sets)) {
}

inline void Group::add_update(Entity entity) {
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

inline void Group::remove_update(Entity entity) {
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

inline Group::entity_iterator Group::begin() const {
    ASSERT_MSG(m_sets.size() > 0, "Group size {} should be > 0 ",
               m_sets.size());
    auto it = m_sets[0]->begin();
    return entity_iterator(it, m_sets);
}
inline Group::entity_iterator Group::end() const {
    ASSERT_MSG(m_sets.size() > 0, "Group size {} should be > 0 ",
               m_sets.size());
    auto it = m_sets[0]->end();
    return entity_iterator(it, m_sets);
}

// class private ********
inline bool Group::should_add(Entity entity) const {
    ASSERT_MSG(!contains(entity),
               "if part of group, then push/emplace double register")
    return has_all(entity);
}
inline bool Group::should_remove(Entity entity) const {
    // we are part of the group but no longer have every component
    return contains(entity) && !has_all(entity);
}
inline bool Group::contains(Entity entity) const {
    return m_entities.count(entity);
}
inline bool Group::has_all(Entity entity) const {
    for (auto &set : m_sets) {
        if (!set->contains(entity))
            return false;
    }
    return true;
}
}; // namespace ecs
