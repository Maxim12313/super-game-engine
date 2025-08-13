#pragma once
#include "utils/macros.hpp"
#include "common.hpp"
#include "../src/core/component_manager.hpp"
#include "../src/core/group_manager.hpp"
#include "../src/core/entity_manager.hpp"
#include "../src/core/signature_manager.hpp"
#include <utility>

namespace ecs {

/**
 * @class Coordinator
 * @brief All ECS data and behavior maangement should be through the
 * coordinaator
 */
class Coordinator {

public:
    Coordinator() = default;

    // Create a new entity
    Entity create_entity();

    // Erase entity or do nothing if it does not exist
    // Clears from component arrays
    void erase_entity(Entity entity);

    // Create component array for this type
    // Requires not already registered]
    template <typename... Components>
    void register_component();

    // Get reference to this entity's component
    // Requires that the component be already registered for this
    template <typename Component>
    Component &get(Entity entity);

    // Copy this component in for entity
    // Requires componnent not already registered for entity
    template <typename Component>
    void push_back(Entity entity, const Component &component);

    // Init this component in place for entity
    // Requires component not already registered for entity
    template <typename Component, typename... Args>
    void emplace_back(Entity entity, Args &&...args);

    // Erase entity's component if exist, otherwise do nothing
    template <typename Component>
    void erase_component(Entity entity);

private:
    internal::SignatureManager m_entity_signature;
    internal::EntityManager m_entity_manager;
    internal::ComponentManager m_component_manager;
    internal::GroupManager m_group_manager;
};

}; // namespace ecs

namespace ecs {

// inline definitions ********
inline Entity Coordinator::create_entity() {
    Entity entity = m_entity_manager.create_entity();
    m_entity_signature.push_back(entity);
    return entity;
}

inline void Coordinator::erase_entity(Entity entity) {
    m_component_manager.erase_entity(entity);
    m_entity_signature.erase(entity);
    m_entity_manager.destroy_entity(entity);
}

// templated definitions ********
template <typename... Components>
void Coordinator::register_component() {
    (m_component_manager.register_type<Components>(), ...);
}

template <typename Component>
Component &Coordinator::get(Entity entity) {
    ASSERT(m_component_manager.contains<Component>(entity) &&
           "entity does not have this component");
    return m_component_manager.get<Component>(entity);
}

template <typename Component>
void Coordinator::push_back(Entity entity, const Component &component) {
}

template <typename Component, typename... Args>
void Coordinator::emplace_back(Entity entity, Args &&...args) {
    m_component_manager.emplace_back(entity, std::forward<Args>(args)...);
}

template <typename Component>
void Coordinator::erase_component(Entity entity) {
    m_component_manager.erase_data<Component>(entity);
    m_entity_signature.reset_bit<Component>(entity);
}

} // namespace ecs
