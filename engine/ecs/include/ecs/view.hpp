#pragma once
#include <memory>
#include <tuple>
#include <unordered_map>
#include <vector>
#include "common.hpp"
#include "../src/core/sparse_set.hpp"

namespace ecs {
class Registry;

// WARNING: for any pools that are pushed or removed from, related iterators
// will be invalidated
// WARNING: Views depend on the lifetime of the registry and will store dangling
// pointers otherwise
template <typename... Components>
class View {
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

    class Iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = Entity;
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
        value_type operator*() const {
            return *m_curr_it;
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

    protected:
        iterator_type m_curr_it;
        const iterator_type m_end_it;
        const std::vector<internal::ISparseSet *> &m_sets;
    };

    template <typename... Ts>
    class EachIterator : public Iterator {
    public:
        using iterator_category = Iterator::iterator_category;
        using value_type = std::tuple<Entity, Ts &...>;
        using iterator_type = std::vector<Entity>::const_iterator;

    public:
        EachIterator(iterator_type curr_it, iterator_type end_it,
                     std::vector<internal::ISparseSet *> &sets)
            : Iterator(curr_it, end_it, sets) {
        }

        value_type operator*() const {
            int idx = 0;
            Entity entity = *this->m_curr_it;
            return std::tuple<Entity, Ts &...>(
                {entity, fetch_val<Ts>(entity, idx)...});
        }

    private:
        template <typename T>
        T &fetch_val(Entity entity, int &idx) const {
            auto &sets = this->m_sets;
            auto *concrete = static_cast<internal::SparseSet<T> *>(sets[idx]);
            idx++;
            return (*concrete)[entity];
        }
    };

    template <typename... Ts>
    class EachRange {
    public:
        EachRange(EachIterator<Ts...> &begin_it, EachIterator<Ts...> &end_it)
            : m_begin(std::move(begin_it)), m_end(std::move(end_it)) {
        }

        EachIterator<Ts...> begin() const {
            return m_begin;
        }
        EachIterator<Ts...> end() const {
            return m_end;
        }

    private:
        EachIterator<Ts...> m_begin;
        EachIterator<Ts...> m_end;
    };

    EachRange<Components...> each() {
        const auto &min_set = m_sets[m_min_idx];
        EachIterator<Components...> begin_it(min_set->begin(), min_set->end(),
                                             m_sets);
        EachIterator<Components...> end_it(min_set->end(), min_set->end(),
                                           m_sets);
        return EachRange<Components...>(begin_it, end_it);
    }

    // use lazy smallest
    Iterator begin() {
        const auto &min_set = m_sets[m_min_idx];
        return Iterator(min_set->begin(), min_set->end(), m_sets);
    }

    Iterator end() {
        const auto &min_set = m_sets[m_min_idx];
        return Iterator(min_set->end(), min_set->end(), m_sets);
    }

private:
    // lazy smallest set idx
    int m_min_idx;
    std::vector<internal::ISparseSet *> m_sets;
};

}; // namespace ecs
