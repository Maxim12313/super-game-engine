#pragma once
#include "common.hpp"
#include "packed_array_manager.hpp"

class Coordinator {
private:
    EntityManager entity_manager;
    PackedArrayManager<MAX_COMPONENTS> components;
    PackedArrayManager<MAX_COMPONENTS> systems;

public:
    Coordinator() {
    }

    // -------------ENTITY-------------
    Entity get_entity() {
        return entity_manager.get_entity();
    }

    void return_entity(Entity entity) {
        entity_manager.return_entity(entity);
    }

    // -------------COMPONENT----------
    template <typename T>
    void register_component_type() {
        components.register_type<T>();
    }

    template <typename T>
    void set_component(Entity entity, T data) {
        components.set(entity, data);
    }

    // -------------SYSTEM------------
};
