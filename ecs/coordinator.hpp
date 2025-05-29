#pragma once
#include "common.hpp"
#include "component_manager.hpp"
#include "entity_manager.hpp"
#include "packed_array_manager.hpp"
#include "signature_manager.hpp"

class Coordinator {
private:
    EntityManager entity_manager;

    ComponentManager component_manager;

    SystemManager system_manager;

public:
    Coordinator() {
    }

    // -----------------ENTITY------------------
    Entity get_entity() {
        return entity_manager.get_entity();
    }

    void return_entity(Entity entity) {
        entity_manager.return_entity(entity);
    }
};
