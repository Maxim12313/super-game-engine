#pragma once
#include "../utils/test_utils.hpp"
#include "id_utils.hpp"
#include "packed_array.hpp"
#include <memory>
#include <vector>

/**
 * @class PackedArrayManager
 * @brief Manages registered packed arrays which can hold different types
 */
template <size_t MAX>
class PackedArrayManager {
private:
    vector<unique_ptr<IPackedArray>> arrays;

public:
    PackedArrayManager() {
    }

    template <typename T>
    void register_type() {
        Component_ID id = id_utils::get_component_id<T>();
        ASSERT(id >= arrays.size() && "already registered");
        arrays.emplace_back(make_unique<PackedArray<T, MAX>>());
    }

    /**
     * @brief Will default init T data for entity if not set
     * @return Reference to the T data set for entity
     */
    template <typename T>
    T &get(Entity entity) {
        PackedArray<T, MAX> *arr = get_array<T>();
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
        PackedArray<T, MAX> *arr = get_array<T>();
        return arr->contains(entity);
    }

    /**
     * @brief Erase the T data entry for entity if it exists, else does nothing
     */
    template <typename T>
    void erase_data(Entity entity) {
        PackedArray<T, MAX> *arr = get_array<T>();
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
    PackedArray<T, MAX> *get_array() {
        Component_ID id = id_utils::get_component_id<T>();
        ASSERT(id < arrays.size() && "unregistered type");
        auto unique = arrays[int(id)].get();
        auto arr = static_cast<PackedArray<T, MAX> *>(unique);
        return arr;
    }

    // IPackedArray *get_array(int id) {
    //     return arrays[id].get();
    // }
};
