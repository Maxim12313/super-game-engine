#pragma once
#include "../components/components.hpp"
#include "packed_array.hpp"
#include <cassert>
#include <memory>

template <size_t MAX>
class PackedArrayManager {
private:
    vector<unique_ptr<IPackedArray>> arrays;

public:
    PackedArrayManager() {
    }

    template <typename T>
    void register_type() {
        Type_ID id = get_type_id<T>();
        assert(id >= arrays.size() && "already registered");
        arrays.emplace_back(make_unique<PackedArray<T, MAX>>());
    }

    template <typename T>
    void set(Entity ent, T data) {
        PackedArray<T, MAX> *arr = get_array<T>();
        arr->set(ent, data);
    }

    template <typename T>
    void erase(Entity ent) {
        PackedArray<T, MAX> *arr = get_array<T>();
        arr->erase(ent);
    }

    template <typename T>
    PackedArray<T, MAX> *get_array() {
        Type_ID id = get_type_id<T>();
        assert(id < arrays.size() && "unregistered type");
        auto unique = arrays[int(id)].get();
        auto arr = static_cast<PackedArray<T, MAX> *>(unique);
        return arr;
    }
};
