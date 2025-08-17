#pragma once
#include <memory>
#include <tuple>
#include <unordered_map>
#include <vector>
#include "common.hpp"
#include "each_range.hpp"
#include "../src/projections.hpp"

// Forwarding ********
namespace ecs::internal {
template <typename Components>
class SparseSet;
class ISparseSet;
}; // namespace ecs::internal

// Declaration ********
namespace ecs {
class Registry;

// WARNING: for any pools that are pushed or removed from, related iterators
// will be invalidated
// Views also depends on the lifetime of the registry and will store dangling
// pointers otherwise
template <typename... Components>
class View {
public:
    template <typename projection>
    class Iterator;

    using each_iterator = Iterator<internal::each_projection<Components...>>;
    using entity_iterator = Iterator<internal::entity_projection>;

public:
    // NOTE: lazy min_idx check on construction
    View(std::vector<internal::ISparseSet *> &sets);

    EachRange<each_iterator> each();

    // NOTE: use lazy smallest
    entity_iterator begin();

    entity_iterator end();

private:
    int m_min_idx;
    std::vector<internal::ISparseSet *> m_sets;
};

}; // namespace ecs

#include "../src/view.inl"
