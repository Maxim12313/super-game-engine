#include "entity_manager.hpp"
#include "utils/macros.hpp"

namespace ecs::internal {

EntityManager::EntityManager() {
    for (int id = 0; id < MAX_ENTITIES; id++) {
        available.push(Entity(id));
    }
}

Entity EntityManager::create_entity() {
    ASSERT(!available.empty() && "full");
    Entity res = available.top();
    available.pop();
    return res;
}

void EntityManager::destroy_entity(Entity entity) {
    available.push(Entity(entity));
}
} // namespace ecs::internal
