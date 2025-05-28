#pragma once
#include "packed_array.hpp"
#include "type_id_utils.hpp"
#include <cassert>
#include <memory>
#include <vector>

template <size_t MAX>
class PackedArrayManager {
private:
    vector<unique_ptr<IPackedArray>> arrays;

public:
    PackedArrayManager() {
    }

    template <typename T>
    void register_type() {
        Type_ID id = type_id_utils::get_type_id<T>();
        assert(id >= arrays.size() && "already registered");
        arrays.emplace_back(make_unique<PackedArray<T, MAX>>());
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
    void erase(Entity entity) {
        PackedArray<T, MAX> *arr = get_array<T>();
        arr->erase(entity);
    }

    template <typename T>
    PackedArray<T, MAX> *get_array() {
        Type_ID id = type_id_utils::get_type_id<T>();
        assert(id < arrays.size() && "unregistered type");
        auto unique = arrays[int(id)].get();
        auto arr = static_cast<PackedArray<T, MAX> *>(unique);
        return arr;
    }
};
