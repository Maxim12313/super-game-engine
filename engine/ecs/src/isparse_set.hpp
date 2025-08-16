#pragma once
#include "ecs/common.hpp"
#include "ecs/group.hpp"
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

    ISparseSet();

    // Erases the data entry for the given entity
    virtual void remove(Entity entity) = 0;

    // Clear the array, resetting size to 0
    void clear();

    // Returns if entity is registered with this packed array
    bool contains(Entity entity) const;

    // Size
    size_t size() const;

    // Begin iterator to entity list
    std::vector<Entity>::const_iterator begin() const;

    // End iterator to entity list
    std::vector<Entity>::const_iterator end() const;

    // Set group observer
    void set_group(Group *m_group);

protected:
    std::unordered_map<Entity, int> m_to_idx;
    std::vector<Entity> m_to_entity;
    Group *m_group;
};

} // namespace ecs::internal
