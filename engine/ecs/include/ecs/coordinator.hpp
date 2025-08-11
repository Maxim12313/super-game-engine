#pragma once
#include "utils/macros.hpp"
#include "common.hpp"
#include "../src/core/component_manager.hpp"
#include "../src/core/group_manager.hpp"
#include "../src/core/entity_manager.hpp"
#include "../src/core/signature_manager.hpp"

namespace ecs {

/**
 * @class Coordinator
 * @brief All ECS data and behavior maangement should be through the
 * coordinaator
 */
class Coordinator {
private:
    internal::SignatureManager entity_signatures;
    internal::EntityManager entity_manager;
    internal::ComponentManager component_manager;
    internal::GroupManager group_manager;

public:
    Coordinator() = default;

    /**
     * @brief Create a new entity
     */
    Entity create_entity() {
        Entity entity = entity_manager.create_entity();
        entity_signatures.assign(entity, 0);
        return entity;
    }

    /**
     * @brief Erase entity or do nothing if it does not exist
     */
    void erase_entity(Entity entity) {
        component_manager.erase_entity(entity);
        entity_signatures.erase(entity);
        entity_manager.destroy_entity(entity);
    }

    /**
     * @brief Register T component [requires not already registered]
     */
    template <typename... T>
    void register_component() {
        (component_manager.register_type<T>(), ...);
    }

    /**
     * @brief Requires that the compoennt be already registered for this
     * entity
     * @return Returns the associated T data for entity
     */
    template <typename T>
    T &get(Entity entity) {
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
        entity_signatures.set_bit<T>(entity);
        group_manager.update(entity, entity_signatures[entity]);
    }

    /**
     * @brief Erase entity's T component if exist, otherwise do nothing
     */
    template <typename T>
    void erase_component(Entity entity) {
        component_manager.erase_data<T>(entity);
        entity_signatures.reset_bit<T>(entity);
    }
};
} // namespace ecs
