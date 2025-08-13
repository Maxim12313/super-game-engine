#pragma once
#include "utils.hpp"
#include "utils/macros.hpp"
#include "sparse_set.hpp"
#include <memory>
#include <tuple>
#include <utility>
#include <vector>
#include <memory>

namespace ecs::internal {

/**
 * @class PackedArrayManager
 * @brief Manages registered packed arrays which can hold different types
 */
class ComponentManager {
public:
    ComponentManager() = default;

    // register the commponents
    template <typename T>
    void register_type();

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
    bool contains(Entity entity);

    // Erase the T data entry for entity if it exists, else does nothing
    template <typename T>
    void erase_data(Entity entity);

    // Erase all data for the entity and unset
    void erase_entity(Entity entity);

    // Requires that the type be registered already
    template <typename T>
    SparseSet<T> *get_array();

    template <typename... Components>
    std::tuple<Components...> get_view() {
    }

private:
    std::vector<std::unique_ptr<ISparseSet>> m_arrays;
};
} // namespace ecs::internal

namespace ecs::internal {

// component_manager public ********
template <typename T>
void ComponentManager::register_type() {
    Component_ID id = utils::get_component_id<T>();
    ASSERT_MSG(id >= m_arrays.size(), "Already registered {} for {}", id,
               typeid(T).name());
    m_arrays.emplace_back(std::make_unique<SparseSet<T>>());
}

template <typename T>
T &ComponentManager::get(Entity entity) {
    SparseSet<T> *arr = get_array<T>();
    return (*arr)[entity];
}

template <typename T>
void ComponentManager::push_back(Entity entity, const T &val) {
    SparseSet<T> *arr = get_array<T>();
    arr->push_back(entity, val);
}

template <typename T, typename... Args>
void ComponentManager::emplace_back(Entity entity, Args &&...args) {
    SparseSet<T> *arr = get_array<T>();
    arr->emplace_back(entity, std::forward<Args>(args)...);
}

template <typename T>
bool ComponentManager::contains(Entity entity) {
    SparseSet<T> *arr = get_array<T>();
    return arr->contains(entity);
}

template <typename T>
void ComponentManager::erase_data(Entity entity) {
    SparseSet<T> *arr = get_array<T>();
    arr->erase(entity);
}

inline void ComponentManager::erase_entity(Entity entity) {
    for (auto &array : m_arrays) {
        array->erase(entity);
    }
}

template <typename T>
SparseSet<T> *ComponentManager::get_array() {
    Component_ID id = utils::get_component_id<T>();
    ASSERT_MSG(id < m_arrays.size(), "Unregistered type {} for {}", id,
               typeid(T).name());
    auto unique = m_arrays[int(id)].get();
    auto arr = static_cast<SparseSet<T> *>(unique);
    return arr;
}

}; // namespace ecs::internal
