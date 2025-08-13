#include "entity_manager.hpp"
#include "utils/macros.hpp"

namespace ecs::internal {

EntityManager::EntityManager() {
    for (int id = 0; id < MAX_ENTITIES; id++) {
        m_available.push(Entity(id));
    }
}

Entity EntityManager::create_entity() {
    ASSERT(!m_available.empty() && "full");
    Entity res = m_available.top();
    m_available.pop();
    return res;
}

void EntityManager::destroy_entity(Entity entity) {
    m_available.push(Entity(entity));
}
} // namespace ecs::internal
