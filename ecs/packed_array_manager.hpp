#pragma once
#include "../components/components.hpp"
#include "packed_array.hpp"
#include <memory>

using Type_ID = uint32_t;

static Type_ID curr = 0;
template <typename T>
Type_ID get_type_id() {
    static Type_ID id = curr++;
    return id;
}

template <size_t MAX>
class PackedArrayManager {
private:
    vector<shared_ptr<IPackedArray>> arrays;

public:
    PackedArrayManager() {
    }

    template <typename T>
    void register_type() {
        Type_ID id = get_type_id<T>();
        PackedArray<T, MAX> arr;
        arrays.emplace_back(make_shared<IPackedArray>(arr));
    }

    template <typename T>
    void add(Entity ent, T data) {
        PackedArray<T, MAX> *arr = get_array<T>();
        arr->set(ent, data);
    }

    template <typename T>
    void remove(Entity ent) {
        PackedArray<T, MAX> *arr = get_array<T>();
        arr->erase(ent);
    }

    template <typename T>
    PackedArray<T, MAX> *get_array() {
        Type_ID id = get_type_id<T>();
        assert(id < arrays.size() && "unregistered type");
        PackedArray<T, MAX> *arr = arrays[int(id)].get();
        return arr;
    }
};
