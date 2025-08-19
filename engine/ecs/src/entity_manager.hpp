#pragma once
#include "ecs/common.hpp"
#include "sparse_set.hpp"
#include "utils/macros.hpp"
#include <stack>
#include <stack>

namespace ecs::internal {

/**
 * @class internal::EntityManager
 * @brief Ensures unique entity ids are provisioned and
 * tracks entities for subscribed to each component
 */
class EntityManager {

public:
    // Initialize with [0, MAX_ENTITIES) available ids
    EntityManager();

    // The unique entity identifier free for use.
    Entity create_entity();

    // Destroy this entity and reclaim the id
    void destroy_entity(Entity entity);

private:
    std::stack<Entity> m_destroyed;
    Entity m_top;
};
}; // namespace ecs::internal

namespace ecs::internal {
// class public ********
inline EntityManager::EntityManager() : m_top(0) {
}

inline Entity EntityManager::create_entity() {
    Entity res;
    if (m_top < MAX_ENTITIES) {
        res = m_top++;
    } else if (m_destroyed.size() > 0) {
        res = m_destroyed.top();
        m_destroyed.pop();
    } else {
        ASSERT_MSG(m_top < MAX_ENTITIES || m_destroyed.size() > 0,
                   "no more entity space");
        res = MAX_ENTITIES;
    }
    return res;
}

inline void EntityManager::destroy_entity(Entity entity) {
    m_destroyed.push(entity);
}

} // namespace ecs::internal
