#pragma once
#include <utility>
#include <vector>

namespace ecs::internal {
class ISparseSet;
};

namespace ecs {

// Declaration ********
template <typename each_iterator>
class EachRange {
public:
    EachRange(int idx, const std::vector<internal::ISparseSet *> &sets);

    each_iterator begin() const;
    each_iterator end() const;

private:
    int m_idx;
    const std::vector<internal::ISparseSet *> &m_sets;
};

}; // namespace ecs

#include "../src/isparse_set.hpp"
namespace ecs {
// Class public ********
template <typename each_iterator>
EachRange<each_iterator>::EachRange(
    int idx, const std::vector<internal::ISparseSet *> &sets)
    : m_idx(idx), m_sets(sets) {
}

template <typename each_iterator>
each_iterator EachRange<each_iterator>::begin() const {
    auto set = m_sets[m_idx];
    return each_iterator(set->begin(), set->end(), m_sets);
}

template <typename each_iterator>
each_iterator EachRange<each_iterator>::end() const {
    auto set = m_sets[m_idx];
    return each_iterator(set->end(), set->end(), m_sets);
}
}; // namespace ecs
