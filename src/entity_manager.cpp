#include "../include/ecs/entity_manager.hpp"

EntityManager::EntityManager() {
    for (int id = 0; id < MAX_ENTITIES; id++) {
        available_entities.push(Entity(id));
    }
}

Entity EntityManager::create_entity() {
    // NOTE: consider whether deny or just flag full when full
    ASSERT(!available_entities.empty() && "full");
    Entity res = available_entities.top();
    available_entities.pop();
    return res;
}

void EntityManager::erase_entity(Entity entity) {
    available_entities.push(Entity(entity));
}
