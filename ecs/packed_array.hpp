#pragma once
#include "../include/globals.hpp"
#include "entity_manager.hpp"
#include <cassert>
#include <unordered_map>

class IPackedArray {
public:
    virtual ~IPackedArray() {
    }
};

template <typename T, size_t MAX>
class PackedArray : IPackedArray {
private:
    int count = 0;
    array<T, MAX> data;

    unordered_map<int, int> data_to_idx;
    unordered_map<int, int> idx_to_data;

    void add(int entity) {
        assert(data_to_idx.count(entity) == 0 && "already registered");
        data_to_idx[entity] = count;
        idx_to_data[count] = entity;
        count++;
    }

public:
    PackedArray() {
    }

    array<T, MAX> &get_data() {
        return data;
    }
    void set(int entity, T val) {
        add(entity);
        get(entity) = val;
    }
    T &get(int entity) {
        assert(data_to_idx.count(entity) != 0 && "not registered");
        return data[data_to_idx[entity]];
    }
    void erase(int entity) {
        if (!data_to_idx.count(entity))
            return;
        int left = data_to_idx[entity];
        int right = count - 1;
        swap(data[left], data[right]);

        int right_entity = idx_to_data[right];
        data_to_idx[right_entity] = left;
        idx_to_data[left] = right_entity;
        data_to_idx.erase(entity);
        count--;
    }
    size_t size() const {
        return count;
    }

    array<T, MAX>::iterator begin() {
        return data.begin();
    }
    array<T, MAX>::iterator end() {
        return data.begin() + count;
    }
};
