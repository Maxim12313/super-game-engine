#pragma once
#include "../utils/test_utils.hpp"
#include "id_utils.hpp"
#include "sparse_set.hpp"
#include <memory>
#include <spdlog/spdlog.h>
#include <vector>

/**
 * @class PackedArrayManager
 * @brief Manages registered packed arrays which can hold different types
 */
class ComponentManager {
private:
    vector<unique_ptr<ISparseSet>> arrays;

public:
    ComponentManager() {
    }

    template <typename T>
    void register_type() {
        Component_ID id = id_utils::get_component_id<T>();
        SPDLOG_TRACE(typeid(T).name());
        ASSERT(id >= arrays.size() && "Already registered");
        arrays.emplace_back(make_unique<SparseSet<T>>());
    }

    /**
     * @brief Will default init T data for entity if not set
     * @return Reference to the T data set for entity
     */
    template <typename T>
    T &get(Entity entity) {
        SparseSet<T> *arr = get_array<T>();
        return (*arr)[entity];
    }

    /**
     * @brief Assign entity T value to val
     */
    template <typename T>
    void assign(Entity entity, T val) {
        get<T>(entity) = val;
    }

    /**
     * @return True if a T data type for entity is set
     */
    template <typename T>
    bool contains(Entity entity) {
        SparseSet<T> *arr = get_array<T>();
        return arr->contains(entity);
    }

    /**
     * @brief Erase the T data entry for entity if it exists, else does nothing
     */
    template <typename T>
    void erase_data(Entity entity) {
        SparseSet<T> *arr = get_array<T>();
        arr->erase(entity);
    }

    /**
     * @brief Erase all data for the entity and unset
     */
    void erase_entity(Entity entity) {
        for (auto &array : arrays) {
            array->erase(entity);
        }
    }

    /**
     * @brief Requires that the type be registered already
     * @return The packed array associeted with type T
     */
    template <typename T>
    SparseSet<T> *get_array() {
        Component_ID id = id_utils::get_component_id<T>();
        SPDLOG_TRACE(typeid(T).name());
        ASSERT(id < arrays.size() && "unregistered type");
        auto unique = arrays[int(id)].get();
        auto arr = static_cast<SparseSet<T> *>(unique);
        return arr;
    }
};
