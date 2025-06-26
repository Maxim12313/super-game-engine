#include "../include/ecs/coordinator.hpp"

Coordinator::Coordinator() {
}

Entity Coordinator::create_entity() {
    Entity entity = entity_manager.create_entity();
    entity_signatures.assign(entity, 0);
    return entity;
}

void Coordinator::erase_entity(Entity entity) {
    component_manager.erase_entity(entity);
    entity_signatures.erase(entity);
    entity_manager.destroy_entity(entity);
}
