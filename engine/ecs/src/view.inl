#pragma once
#include "ecs/each_range.hpp"
#include "ecs/view.hpp"
#include "isparse_set.hpp"
#include "utils/macros.hpp"

namespace ecs {
// Helpers ********

bool all_sets_have_entity(const std::vector<internal::ISparseSet *> &sets,
                          Entity entity) {
    for (const auto &set : sets) {
        if (!set->contains(entity))
            return false;
    }
    return true;
}

// Iterator ********
template <typename... Components>
template <typename projection>
class View<Components...>::Iterator {
public:
    using iterator_category = std::forward_iterator_tag;
    using iterator_type = std::vector<Entity>::const_iterator;
    using value_type = projection::value_type;

public:
    Iterator(iterator_type curr_it, iterator_type end_it,
             const std::vector<internal::ISparseSet *> &sets)
        : m_curr_it(curr_it), m_end_it(end_it), m_sets(sets) {

        if (m_curr_it != m_end_it && !is_valid())
            search_next();
    }

    Iterator &operator++() {
        search_next();
        return *this;
    }
    value_type operator*() const {
        return m_proj(*m_curr_it, m_sets);
    }
    bool operator!=(const Iterator &o) const {
        return m_curr_it != o.m_curr_it;
    }

private:
    bool is_valid() const {
        return all_sets_have_entity(m_sets, *m_curr_it);
    }

    void search_next() {
        do {
            m_curr_it++;
        } while (m_curr_it != m_end_it && !is_valid());
    }

private:
    projection m_proj;
    iterator_type m_curr_it;
    const iterator_type m_end_it;
    const std::vector<internal::ISparseSet *> &m_sets;
};

// View public ********
template <typename... Components>
View<Components...>::View(std::vector<internal::ISparseSet *> &sets)
    : m_sets(std::move(sets)) {
    ASSERT_MSG(m_sets.size() > 0, "view has no sets");

    // setup min_idx
    int min_idx = 0;
    for (int i = 0; i < m_sets.size(); i++) {
        if (m_sets[min_idx]->size() > m_sets[i]->size()) {
            min_idx = i;
        }
    }
    m_min_idx = min_idx;
}

template <typename... Ts>
EachRange<typename View<Ts...>::each_iterator> View<Ts...>::each() {
    return EachRange<each_iterator>(m_min_idx, m_sets);
}

template <typename... Ts>
View<Ts...>::entity_iterator View<Ts...>::begin() {
    const auto &min_set = m_sets[m_min_idx];
    return entity_iterator(min_set->begin(), min_set->end(), m_sets);
}

template <typename... Ts>
View<Ts...>::entity_iterator View<Ts...>::end() {
    const auto &min_set = m_sets[m_min_idx];
    return entity_iterator(min_set->end(), min_set->end(), m_sets);
}

}; // namespace ecs
