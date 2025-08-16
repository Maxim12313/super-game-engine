#pragma once
#include "../src/utils.hpp"
#include "utils/macros.hpp"
#include "../src/sparse_set.hpp"
#include "../src/entity_manager.hpp"
#include <memory>
#include <utility>
#include <vector>
#include <memory>
#include "view.hpp"
#include "group.hpp"

namespace ecs {

/**
 * @class Registry
 * @brief Manages ECS Data
 */
class Registry {
public:
    Registry() = default;

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
    const Group &group();

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
    std::vector<std::unique_ptr<Group>> m_groups;
    internal::EntityManager m_entities;
};
} // namespace ecs

namespace ecs {
// class public ********

template <typename... Components>
void Registry::register_components() {
    // ensure left to right order
    int a[]{register_component<Components>()...};
    (void)sizeof(a);
}

template <typename Component>
Component &Registry::get(Entity entity) {
    internal::SparseSet<Component> *arr = get_array<Component>();
    return (*arr)[entity];
}

template <typename Component>
void Registry::push_back(Entity entity, const Component &val) {
    internal::SparseSet<Component> *arr = get_array<Component>();
    arr->push_back(entity, val);
}

template <typename Component, typename... Args>
void Registry::emplace_back(Entity entity, Args &&...args) {
    internal::SparseSet<Component> *arr = get_array<Component>();
    arr->emplace_back(entity, std::forward<Args>(args)...);
}

template <typename Component>
bool Registry::contains(Entity entity) const {
    internal::SparseSet<Component> *arr = get_array<Component>();
    return arr->contains(entity);
}

template <typename Component>
void Registry::remove(Entity entity) {
    internal::SparseSet<Component> *arr = get_array<Component>();
    arr->erase(entity);
}

inline Entity Registry::create() {
    return m_entities.create_entity();
}

inline void Registry::destroy(Entity entity) {
    for (auto &array : m_components)
        array->remove(entity);

    m_entities.destroy_entity(entity);
}

template <typename... Components>
View<Components...> Registry::view() {
    auto sets = get_sets<Components...>();
    return View<Components...>(sets);
}

template <typename... Components>
const Group &Registry::group() {
    auto sets = get_sets<Components...>();
    m_groups.emplace_back(std::make_unique<Group>(sets));
    return *m_groups.back();
}

// class private ********
template <typename Component>
internal::SparseSet<Component> *Registry::get_array() {
    Component_ID id = internal::utils::get_component_id<Component>();
    ASSERT_MSG(id < m_components.size(), "Unregistered type {} for {}", id,
               typeid(Component).name());
    auto unique = m_components[int(id)].get();
    auto arr = static_cast<internal::SparseSet<Component> *>(unique);
    return arr;
}

// return 0 for init list ordering
template <typename Component>
int Registry::add_set(std::vector<internal::ISparseSet *> &sets) {
    auto set = get_array<Component>();
    sets.push_back(set);
    return 0;
}

// return 0 for init list ordering
template <typename Component>
int Registry::register_component() {
    Component_ID id = internal::utils::get_component_id<Component>();
    ASSERT_MSG(id >= m_components.size(), "Already registered {} for {}", id,
               typeid(Component).name());
    m_components.emplace_back(
        std::make_unique<internal::SparseSet<Component>>());
    return 0;
}

template <typename... Components>
std::vector<internal::ISparseSet *> Registry::get_sets() {
    std::vector<internal::ISparseSet *> sets;

    // ensure left to right order
    int a[]{add_set<Components>(sets)...};
    (void)sizeof(a);

    return sets;
}

}; // namespace ecs
