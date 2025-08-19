#pragma once
#include "isparse_set.hpp"
#include "ecs/common.hpp"
#include <array>
#include <utility>
#include <vector>
#include <unordered_map>

// Forwarding ********
namespace ecs {
class IGroup;
};

// Declaration ********
namespace ecs::internal {

/**
 * @class SparseSet
 * @brief Data container supporting cache fast iteration and key value indexing
 */
template <typename T>
class SparseSet : public ISparseSet {

public:
    SparseSet() = default;

    // Access entity's val. Requires that val exists
    T &operator[](Entity entity);

    // Registeres val for entity, requires that entity not yet registered
    // anything
    void push_back(Entity entity, const T &val);

    // Creates val in place for entity
    template <typename... Args>
    void emplace_back(Entity entity, Args &&...args);

    // Will erase the entity from the array if it exists and otherwise do
    // nothing
    void remove(Entity entity) override;

    // Swap entire positions between obj id'd by entity and obj id'd by idx
    // Returns if succeeded (only doesnt if both refer same obj)
    bool swap_ent_idx(Entity entity, int idx) override;

private:
    // Access entity's val. Requires that val exists
    T &get(Entity entity);

    // Swap positions of a, b in m_data, also updating to_idx and to_entity
    // Returns true if a != b and swapped
    bool swap_ent_ent(Entity a, Entity b);

private:
    std::vector<T> m_data;
};
} // namespace ecs::internal

#include "sparse_set.inl"
