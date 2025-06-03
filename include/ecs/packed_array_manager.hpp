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

    template <typename T>
    T &get(Entity entity) {
        PackedArray<T, MAX> *arr = get_array<T>();
        return arr->get(entity);
    }

    template <typename T>
    void set(Entity entity, T data) {
        PackedArray<T, MAX> *arr = get_array<T>();
        arr->set(entity, data);
    }

    template <typename T>
    bool contains(Entity entity) {
        PackedArray<T, MAX> *arr = get_array<T>();
        return arr->contains(entity);
    }

    template <typename T>
    void erase_data(Entity entity) {
        PackedArray<T, MAX> *arr = get_array<T>();
        arr->erase(entity);
    }

    void erase_entity(Entity entity, Signature signature) {
        uint32_t bits = sizeof(entity) * 8;
        for (uint32_t k = 0; k < bits; k++) {
            // if contains k_th data type
            if (signature & (1u << k)) {
                arrays[k].get()->erase(entity);
            }
        }
    }

    template <typename T>
    PackedArray<T, MAX> *get_array() {
        Component_ID id = id_utils::get_component_id<T>();
        ASSERT(id < arrays.size() && "unregistered type");
        auto unique = arrays[int(id)].get();
        auto arr = static_cast<PackedArray<T, MAX> *>(unique);
        return arr;
    }

    IPackedArray *get_array(int id) {
        return arrays[id].get();
    }
};
