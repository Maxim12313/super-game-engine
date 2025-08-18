#pragma once
#include <memory>
#include "common.hpp"
#include <vector>
#include <memory>
#include <unordered_map>

// forwarding ********
namespace ecs::internal {
class EntityManager;

template <typename Component>
class SparseSet;

class ISparseSet;
}; // namespace ecs::internal

namespace ecs {
template <typename... Components>
class View;
template <typename... Components>
class Group;
class IGroup;
}; // namespace ecs

// declarations ********
namespace ecs {

/**
 * @class Registry
 * @brief Manages ECS Data
 */
class Registry {
public:
    Registry();

    // register the components
    template <typename... Components>
    void register_components();

    // Get data
    template <typename Component>
    Component &get(Entity entity);

    // Copy init entity with val component
    template <typename Component>
    void push_back(Entity entity, const Component &val);

    // In place init entity for component T with args
    template <typename Component, typename... Args>
    void emplace_back(Entity entity, Args &&...args);

    // True if a T data type for entity is set
    template <typename Component>
    bool contains(Entity entity) const;

    // Erase the T data entry for entity if it exists, else does nothing
    template <typename Component>
    void remove(Entity entity);

    // Returns a new entity to use
    Entity create();

    // Erase all data for the entity and destroy it
    void destroy(Entity entity);

    // Returns a view to iterate over entities with the specified components
    template <typename... Components>
    View<Components...> view();

    // Returns a group that manages the ordering of the specified components
    template <typename... Components>
    const Group<Components...> &group();

private:
    // Requires that the type be registered already
    template <typename Components>
    internal::SparseSet<Components> *get_array();

    template <typename Component>
    int add_set(std::vector<internal::ISparseSet *> &sets);

    template <typename Component>
    int register_component();

    template <typename... Components>
    std::vector<internal::ISparseSet *> get_sets();

private:
    std::vector<std::unique_ptr<internal::ISparseSet>> m_components;
    std::unique_ptr<internal::EntityManager> m_entities;
    std::unordered_map<Signature, std::unique_ptr<IGroup>> m_groups;
};
} // namespace ecs

#include "../src/registry.inl"
