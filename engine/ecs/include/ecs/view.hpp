#pragma once
#include <memory>
#include <tuple>
#include <unordered_map>
#include <vector>
#include "common.hpp"
#include "../src/sparse_set.hpp"
#include "../src/projections.hpp"

namespace ecs {
class Registry;

// WARNING: for any pools that are pushed or removed from, related iterators
// will be invalidated
// WARNING: Views depend on the lifetime of the registry and will store dangling
// pointers otherwise
template <typename... Components>
class View {
public:
public:
    // NOTE: lazy min_idx check on construction
    View(std::vector<internal::ISparseSet *> &sets) : m_sets(std::move(sets)) {
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

    template <typename projection>
    class Iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using iterator_type = std::vector<Entity>::const_iterator;

    public:
        Iterator(iterator_type curr_it, iterator_type end_it,
                 std::vector<internal::ISparseSet *> &sets)
            : m_curr_it(curr_it), m_end_it(end_it), m_sets(sets) {

            if (m_curr_it != m_end_it && !is_valid())
                search_next();
        }

        Iterator operator++() {
            search_next();
            return *this;
        }
        projection::value_type operator*() const {
            return m_proj(*m_curr_it, m_sets);
        }

        bool operator==(const Iterator &o) const {
            return m_curr_it == o.m_curr_it;
        }
        bool operator!=(const Iterator &o) const {
            return m_curr_it != o.m_curr_it;
        }

    private:
        bool is_valid() const {
            for (const auto &set : m_sets) {
                if (!set->contains(*m_curr_it))
                    return false;
            }
            return true;
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

public:
    using each_iterator = Iterator<internal::each_projection<Components...>>;
    using entity_iterator = Iterator<internal::entity_projection>;

    class EachRange {
    public:
        EachRange(each_iterator &begin_it, each_iterator &end_it)
            : m_begin(std::move(begin_it)), m_end(std::move(end_it)) {
        }

        each_iterator begin() {
            return m_begin;
        }
        each_iterator end() {
            return m_end;
        }

    private:
        each_iterator m_begin;
        each_iterator m_end;
    };

public:
    EachRange each() {
        const auto &min_set = m_sets[m_min_idx];
        each_iterator begin_it(min_set->begin(), min_set->end(), m_sets);

        each_iterator end_it(min_set->end(), min_set->end(), m_sets);
        return EachRange{begin_it, end_it};
    }

    // use lazy smallest
    entity_iterator begin() {
        const auto &min_set = m_sets[m_min_idx];
        return entity_iterator(min_set->begin(), min_set->end(), m_sets);
    }

    entity_iterator end() {
        const auto &min_set = m_sets[m_min_idx];
        return entity_iterator(min_set->end(), min_set->end(), m_sets);
    }

private:
    // lazy smallest set idx
    int m_min_idx;
    std::vector<internal::ISparseSet *> m_sets;
};

}; // namespace ecs
