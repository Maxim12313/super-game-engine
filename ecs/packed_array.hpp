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
class PackedArray : public IPackedArray {
private:
    int count = 0;
    array<T, MAX> data;

    unordered_map<Entity, int> entity_to_idx;
    unordered_map<int, Entity> idx_to_entity;

    void add(Entity entity) {
        assert(entity_to_idx.count(entity) == 0 && "already registered");
        entity_to_idx[entity] = count;
        idx_to_entity[count] = entity;
        count++;
    }

public:
    PackedArray() {
    }

    void clear() {
        count = 0;
        entity_to_idx.clear();
        idx_to_entity.clear();
    }

    array<T, MAX> &get_data() {
        return data;
    }
    void set(Entity entity, T val) {
        if (!entity_to_idx.count(entity))
            add(entity);
        get(entity) = val;
    }
    T &get(Entity entity) {
        assert(entity_to_idx.count(entity) != 0 && "not registered");
        return data[entity_to_idx[entity]];
    }
    void erase(Entity entity) {
        if (!entity_to_idx.count(entity))
            return;
        int left = entity_to_idx[entity];
        int right = count - 1;
        swap(data[left], data[right]);

        int right_entity = idx_to_entity[right];
        entity_to_idx[right_entity] = left;
        idx_to_entity[left] = right_entity;
        entity_to_idx.erase(entity);
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
