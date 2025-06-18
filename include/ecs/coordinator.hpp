#pragma once
#include "../utils/test_utils.hpp"
#include "common.hpp"
#include "component_manager.hpp"
#include "entity_manager.hpp"
#include "signature_manager.hpp"
#include "system_manager.hpp"

class System;
class SystemManager;

/**
 * @class Coordinator
 * @brief All ECS data and behavior maangement should be through the
 * coordinaator
 */
class Coordinator {
private:
    SignatureManager entity_signature_manager;
    EntityManager entity_manager;
    ComponentManager component_manager;
    unique_ptr<SystemManager> system_manager;

public:
    Coordinator() : system_manager(make_unique<SystemManager>()) {
    }

    /**
     * @brief Create a new entity
     */
    Entity create_entity() {
        Entity entity = entity_manager.create_entity();
        entity_signature_manager.set(entity, 0);
        return entity;
    }

    /**
     * @brief Erase entity or do nothing if it does not exist
     */
    void erase_entity(Entity entity) {
        component_manager.erase_entity(entity);
        system_manager->erase_entity(entity);
        entity_signature_manager.erase(entity);
        entity_manager.erase_entity(entity);
    }

    /**
     * @brief Register T system [requires not already registered]
     */
    template <typename T>
    void register_system(T system) {
        system_manager->register_system<T>(system);
    }

    /**
     * @brief Register T component [requires not already registered]
     */
    template <typename T>
    void register_component() {
        component_manager.register_type<T>();
    }

    /**
     * @brief Requires that the compoennt be already registered for this
     * entity
     * @return Returns the associated T data for entity
     */
    template <typename T>
    T &get_component(Entity entity) {
        ASSERT(component_manager.contains<T>(entity) &&
               "entity does not have this component");
        return component_manager.get<T>(entity);
    }

    /**
     * @return True if this entity has this component type registered
     */
    template <typename T>
    bool has_component(Entity entity) {
        return component_manager.contains<T>(entity);
    }

    /**
     * @brief Assign entity T component data to val
     */
    template <typename T>
    void assign_component(Entity entity, T val) {
        component_manager.assign(entity, val);
        entity_signature_manager.set_bit<T>(entity);

        Signature signature = entity_signature_manager[entity];
        system_manager->register_updated_entity(entity, signature);
    }

    /**
     * @brief Erase entity's T component if exist, otherwise do nothing
     */
    template <typename T>
    void erase_component(Entity entity) {
        component_manager.erase_data<T>(entity);
        entity_signature_manager.reset_bit<T>(entity);
        Signature updated_signature = entity_signature_manager[entity];
        system_manager->erase_updated_entity(entity, updated_signature);
    }

    /**
     * @brief Requires that T system is registered
     */
    template <typename T>
    T *get_system() {
        return system_manager->get_system<T>();
    }

    template <typename T>
    void run_system() {
        T *system = get_system<T>();
        system->run(*this);
    }
};
