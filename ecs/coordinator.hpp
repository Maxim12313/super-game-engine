#pragma once
#include "common.hpp"
#include "component_manager.hpp"
#include "entity_manager.hpp"
#include "signature_manager.hpp"
#include "system_manager.hpp"
#include "../include/test_utils.hpp"

class System;
class SystemManager;

class Coordinator {
private:
    SignatureManager entity_signature_manager;
    EntityManager entity_manager;
    ComponentManager component_manager;
    unique_ptr<SystemManager> system_manager;

public:
    Coordinator() : system_manager(make_unique<SystemManager>()) {
    }

    // -----------------ENTITY
    Entity create_entity() {
        Entity entity = entity_manager.create_entity();
        entity_signature_manager.set(entity, 0);
        return entity;
    }

    void erase_entity(Entity entity) {
        Signature &signature = entity_signature_manager.get(entity);

        entity_manager.erase_entity(entity);
        entity_signature_manager.erase(entity);
        component_manager.erase_entity(entity, signature);
        system_manager->erase(entity, signature);
    }

    // -----------------REGISTER
    template <typename T>
    void register_system(T system) {
        system_manager->register_system<T>(system);
    }

    template <typename T>
    void register_component() {
        component_manager.register_type<T>();
    }

    // -----------------COMPONENTS
    template <typename T>
    T &get_component(Entity entity) {
        return component_manager.get<T>(entity);
    }

    template <typename T>
    void set_component(Entity entity, T data) {
        // must be ref to reflect changes throughout bottom
        component_manager.set<T>(entity, data);
        entity_signature_manager.set_bit<T>(entity);

        Signature signature = entity_signature_manager.get(entity);
        system_manager->add_entity(entity, signature);
    }

    // -----------------SYSTEMS
    template <typename T>
    T *get_system() {
        return system_manager->get_system<T>();
    }
};
