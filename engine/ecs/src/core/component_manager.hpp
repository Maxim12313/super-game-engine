#pragma once
#include "utils.hpp"
#include "utils/macros.hpp"
#include "sparse_set.hpp"
#include <memory>
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

    template <typename T>
    void register_type();

    /**
     * @brief Will default init T data for entity if not set
     * @return Reference to the T data set for entity
     */
    template <typename T>
    T &get(Entity entity);

    /**
     * @brief Assign entity T value to val
     */
    template <typename T>
    void assign(Entity entity, T val);

    /**
     * @return True if a T data type for entity is set
     */
    template <typename T>
    bool contains(Entity entity);

    /**
     * @brief Erase the T data entry for entity if it exists, else does nothing
     */
    template <typename T>
    void erase_data(Entity entity);

    /**
     * @brief Erase all data for the entity and unset
     */
    void erase_entity(Entity entity);

    /**
     * @brief Requires that the type be registered already
     * @return The packed array associeted with type T
     */
    template <typename T>
    SparseSet<T> *get_array();

private:
    std::vector<std::unique_ptr<ISparseSet>> m_arrays;
};
} // namespace ecs::internal

namespace ecs::internal {

// component_manager public ********
template <typename T>
void ComponentManager::register_type() {
    Component_ID id = utils::get_component_id<T>();
    LOG_TRACE("{}", typeid(T).name());
    ASSERT(id >= m_arrays.size() && "Already registered");
    m_arrays.emplace_back(std::make_unique<SparseSet<T>>());
}

template <typename T>
T &ComponentManager::get(Entity entity) {
    SparseSet<T> *arr = get_array<T>();
    return (*arr)[entity];
}

template <typename T>
void ComponentManager::assign(Entity entity, T val) {
    get<T>(entity) = val;
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
    LOG_TRACE("{}", typeid(T).name());
    ASSERT(id < m_arrays.size() && "unregistered type");
    auto unique = m_arrays[int(id)].get();
    auto arr = static_cast<SparseSet<T> *>(unique);
    return arr;
}

}; // namespace ecs::internal
