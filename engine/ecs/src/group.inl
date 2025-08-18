#pragma once
#include "ecs/group.hpp"
#include "utils/macros.hpp"
#include "../src/isparse_set.hpp"
#include "utils/macros.hpp"
#include "ecs/each_range.hpp"
#include "view.inl"
namespace ecs {

// class Iterator ********
template <typename projection>
class IGroup::Iterator {
public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = projection::value_type;

    using iterator_type = std::vector<Entity>::const_iterator;

public:
    // end_it for keeping same api as view iterator
    Iterator(iterator_type begin_it, iterator_type end_it,
             const std::vector<internal::ISparseSet *> &sets)
        : m_curr(begin_it), m_end(end_it), m_sets(sets) {
    }
    Iterator &operator++() {
        m_curr++;
        return *this;
    }
    bool operator!=(IGroup::Iterator<projection> &o) {
        return m_curr != o.m_curr;
    }
    value_type operator*() {
        return m_proj(*m_curr, m_sets);
    }

private:
    projection m_proj;
    iterator_type m_curr;
    iterator_type m_end;
    const std::vector<internal::ISparseSet *> &m_sets;
};

// IGroup public ********
inline IGroup::IGroup(std::vector<internal::ISparseSet *> &sets)
    : m_sets(std::move(sets)) {

    ASSERT_MSG(m_sets.size() > 0, "Group size {} should be > 0 ",
               m_sets.size());

    // get min sset
    auto min_set = m_sets[0];
    for (auto set : m_sets) {
        if (min_set->size() > set->size())
            min_set = set;
    }

    // rearrange the memory of sets to form the group
    for (auto it = min_set->begin(); it != min_set->end(); it++) {
        // swap into the front
        if (all_sets_have_entity(m_sets, *it)) {
            swap_last(*it);
            m_entities.insert(*it);
        }
    }
}

inline void IGroup::add_update(Entity entity) {
    // detect if changes need to be made
    if (!should_add(entity))
        return;

    // put it just into the range and include it
    swap_last(entity);
    m_entities.insert(entity);
}

inline void IGroup::remove_update(Entity entity) {
    // detect if changes need to be made
    if (!should_remove(entity))
        return;

    // put it to the end of the range then exclude it
    m_entities.erase(entity);
    swap_last(entity);
}

inline IGroup::entity_iterator IGroup::begin() const {
    auto set = m_sets[0];
    return entity_iterator(set->begin(), set->end(), m_sets);
}
inline IGroup::entity_iterator IGroup::end() const {
    auto set = m_sets[0];
    return entity_iterator(set->end(), set->end(), m_sets);
}

// IGroup private ********
inline void IGroup::swap_last(Entity entity) {
    int idx = m_entities.size();
    for (auto &set : m_sets) {
        set->swap_ent_idx(entity, idx);
    }
}

inline bool IGroup::should_add(Entity entity) const {
    ASSERT_MSG(!contains(entity),
               "if part of group, then push/emplace double register")
    return has_all(entity);
}
inline bool IGroup::should_remove(Entity entity) const {
    // we are part of the group but no longer have every component
    return contains(entity) && !has_all(entity);
}
inline bool IGroup::contains(Entity entity) const {
    return m_entities.count(entity);
}
inline bool IGroup::has_all(Entity entity) const {
    for (auto &set : m_sets) {
        if (!set->contains(entity))
            return false;
    }
    return true;
}

// Group public ********
template <typename... Ts>
Group<Ts...>::Group(std::vector<internal::ISparseSet *> &sets) : IGroup(sets) {

    // set observers
    for (auto set : sets) {
        set->set_group(this);
    }
}

template <typename... Ts>
EachRange<typename Group<Ts...>::each_iterator> Group<Ts...>::each() const {
    return EachRange<each_iterator>(/*min_idx=*/0, m_sets);
}
}; // namespace ecs
