#pragma once
#include "ecs/registry.hpp"
#include "ecs/view.hpp"
#include "ecs/group.hpp"
#include <utility>
#include "utils.hpp"
#include "utils/macros.hpp"
#include "../src/sparse_set.hpp"
#include "../src/entity_manager.hpp"

namespace ecs {
// class public ********
Registry::Registry() : m_entities(std::make_unique<internal::EntityManager>()) {
}

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
    arr->remove(entity);
}

inline Entity Registry::create() {
    return m_entities->create_entity();
}

inline void Registry::destroy(Entity entity) {
    for (auto &array : m_components)
        array->remove(entity);

    m_entities->destroy_entity(entity);
}

template <typename... Components>
View<Components...> Registry::view() {
    auto sets = get_sets<Components...>();
    return View<Components...>(sets);
}

template <typename... Components>
const Group<Components...> &Registry::group() {
    auto sets = get_sets<Components...>();

    auto ptr = std::make_unique<Group<Components...>>(sets);
    const auto &group_ref = *ptr;
    m_groups.emplace_back(std::move(ptr));
    return group_ref;
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
