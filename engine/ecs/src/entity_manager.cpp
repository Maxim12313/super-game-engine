#include "entity_manager.hpp"
#include "ecs/common.hpp"
#include "utils/macros.hpp"

namespace ecs::internal {

EntityManager::EntityManager() : m_top(0) {
}

Entity EntityManager::create_entity() {
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

void EntityManager::destroy_entity(Entity entity) {
    m_destroyed.push(entity);
}
} // namespace ecs::internal
