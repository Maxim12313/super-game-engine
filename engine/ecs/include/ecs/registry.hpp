#pragma once
#include "../src/core/utils.hpp"
#include "utils/macros.hpp"
#include "../src/core/sparse_set.hpp"
#include "../src/core/entity_manager.hpp"
#include <memory>
#include <tuple>
#include <utility>
#include <vector>
#include <memory>

namespace ecs {

/**
 * @class Registry
 * @brief Manages ECS Data
 */
class Registry {
public:
    Registry() = default;

    // register the components
    template <typename Components>
    void register_component();

    // Get data
    template <typename T>
    T &get(Entity entity);

    // Copy init entity with val component
    template <typename T>
    void push_back(Entity entity, const T &val);

    // In place init entity for component T with args
    template <typename T, typename... Args>
    void emplace_back(Entity entity, Args &&...args);

    // True if a T data type for entity is set
    template <typename T>
    bool contains(Entity entity) const;

    // Erase the T data entry for entity if it exists, else does nothing
    template <typename T>
    void remove(Entity entity);

    // Returns a new entity to use
    Entity create();

    // Erase all data for the entity and destroy it
    void destroy(Entity entity);

private:
    // Requires that the type be registered already
    template <typename T>
    internal::SparseSet<T> *get_array();

private:
    std::vector<std::unique_ptr<internal::ISparseSet>> m_components;
    internal::EntityManager m_entities;
};
} // namespace ecs

namespace ecs {
// class public ********
template <typename Component>
void Registry::register_component() {
    Component_ID id = internal::utils::get_component_id<Component>();
    ASSERT_MSG(id >= m_components.size(), "Already registered {} for {}", id,
               typeid(Component).name());
    m_components.emplace_back(
        std::make_unique<internal::SparseSet<Component>>());
}

template <typename T>
T &Registry::get(Entity entity) {
    internal::SparseSet<T> *arr = get_array<T>();
    return (*arr)[entity];
}

template <typename T>
void Registry::push_back(Entity entity, const T &val) {
    internal::SparseSet<T> *arr = get_array<T>();
    arr->push_back(entity, val);
}

template <typename T, typename... Args>
void Registry::emplace_back(Entity entity, Args &&...args) {
    internal::SparseSet<T> *arr = get_array<T>();
    arr->emplace_back(entity, std::forward<Args>(args)...);
}

template <typename T>
bool Registry::contains(Entity entity) const {
    internal::SparseSet<T> *arr = get_array<T>();
    return arr->contains(entity);
}

template <typename T>
void Registry::remove(Entity entity) {
    internal::SparseSet<T> *arr = get_array<T>();
    arr->erase(entity);
}

inline Entity Registry::create() {
    return m_entities.create_entity();
}

inline void Registry::destroy(Entity entity) {
    for (auto &array : m_components) {
        array->erase(entity);
    }
    m_entities.destroy_entity(entity);
}

// class private ********
template <typename T>
internal::SparseSet<T> *Registry::get_array() {
    Component_ID id = internal::utils::get_component_id<T>();
    ASSERT_MSG(id < m_components.size(), "Unregistered type {} for {}", id,
               typeid(T).name());
    auto unique = m_components[int(id)].get();
    auto arr = static_cast<internal::SparseSet<T> *>(unique);
    return arr;
}

}; // namespace ecs
