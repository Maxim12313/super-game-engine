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
 * @class Registry
 * @brief All ECS data maangement
 */
class Registry {

public:
    Registry() = default;

    // Create a new entity
    Entity create();

    // Erase entity or do nothing if it does not exist
    // Clears from component arrays
    void destroy(Entity entity);

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
    template <typename... Components>
    void remove(Entity entity);

private:
    internal::SignatureManager m_signatures;
    internal::EntityManager m_entities;
    internal::ComponentManager m_components;
    internal::GroupManager m_groups;
};

}; // namespace ecs

namespace ecs {

// inline definitions ********
inline Entity Registry::create() {
    Entity entity = m_entities.create_entity();
    m_signatures.push_back(entity);
    return entity;
}

inline void Registry::destroy(Entity entity) {
    m_components.erase_entity(entity);
    m_signatures.erase(entity);
    m_entities.destroy_entity(entity);
}

// templated definitions ********
template <typename... Components>
void Registry::register_component() {
    (m_components.register_type<Components>(), ...);
}

template <typename Component>
Component &Registry::get(Entity entity) {
    ASSERT(m_components.contains<Component>(entity) &&
           "entity does not have this component");
    return m_components.get<Component>(entity);
}

template <typename Component>
void Registry::push_back(Entity entity, const Component &component) {
}

template <typename Component, typename... Args>
void Registry::emplace_back(Entity entity, Args &&...args) {
    m_components.emplace_back(entity, std::forward<Args>(args)...);
}

template <typename... Components>
void Registry::remove(Entity entity) {
    (m_components.erase_data<Components>(entity), ...);
}

} // namespace ecs
