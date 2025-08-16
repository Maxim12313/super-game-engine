#pragma once
#include "ecs/common.hpp"
#include <vector>
#include <unordered_map>

namespace ecs::internal {

/**
 * ISparseSet
 * Interface placeholder for type erasing in packed array manager
 */
class ISparseSet {
public:
    virtual ~ISparseSet() = default;

    // Erases the data entry for the given entity
    virtual void remove(Entity entity) = 0;

    // Clear the array, resetting size to 0
    void clear();

    // Returns if entity is registered with this packed array
    bool contains(Entity entity) const;

    size_t size() const;

    std::vector<Entity>::const_iterator begin() const;

    std::vector<Entity>::const_iterator end() const;

protected:
    std::unordered_map<Entity, int> m_to_idx;
    std::vector<Entity> m_to_entity;
};

} // namespace ecs::internal
