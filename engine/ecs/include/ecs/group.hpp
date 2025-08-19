#pragma once
#include <iterator>
#include <vector>
#include "ecs/common.hpp"
#include <unordered_set>
#include "../src/projections.hpp"

namespace ecs {
template <typename each_iterator>
class EachRange;
}; // namespace ecs

namespace ecs::internal {
class ISparseSet;
};

// NOTE: Lifetime of ordering is tied to the group
namespace ecs {
class IGroup {
public:
    template <typename projection>
    class Iterator;

public:
    using entity_iterator = Iterator<internal::entity_projection>;

public:
    virtual ~IGroup() = default;

    IGroup(std::vector<internal::ISparseSet *> &sets);

    // Callback on entity update watching in each sparse set
    void add_update(Entity entity);

    // Callback on entity update watching in each sparse set
    void remove_update(Entity entity);

    // Begin iterator
    entity_iterator begin() const;

    // End iterator
    entity_iterator end() const;

private:
    // swap entity into the last of [0, size]
    void swap_last(Entity entity);

    bool should_add(Entity entity) const;
    bool should_remove(Entity entity) const;
    bool contains(Entity entity) const;
    bool has_all(Entity entity) const;

protected:
    std::vector<internal::ISparseSet *> m_sets;
    std::unordered_set<Entity> m_entities;
};

template <typename... Components>
class Group : public IGroup {
public:
    using each_iterator = Iterator<internal::each_projection<Components...>>;

public:
    // copy not allowed
    Group(const Group &o) = delete;
    Group &operator=(const Group &o) = delete;

    // move allowed
    Group(const Group &&o) = default;
    Group &operator=(const Group &&o) = default;

    Group(std::vector<internal::ISparseSet *> &sets);
    EachRange<each_iterator> each() const;
};
}; // namespace ecs

#include "../src/group.inl"
