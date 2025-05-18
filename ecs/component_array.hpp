#pragma once
#include "../include/globals.hpp"
#include "entity_manager.hpp"
#include <cassert>
#include <unordered_map>

template <typename T, size_t MAX>
class ComponentArray {
private:
    int count = 0;
    array<T, MAX> components;

    unordered_map<int, int> entity_to_idx;
    unordered_map<int, int> idx_to_entity;

    void add(int entity) {
        assert(entity_to_idx.count(entity) == 0 && "already registered");
        entity_to_idx[entity] = count;
        idx_to_entity[count] = entity;
        count++;
    }

public:
    ComponentArray() {
    }

    array<T, MAX_ENTITIES> &get_components() {
        return components;
    }
    void set(int entity, T val) {
        add(entity);
        get(entity) = val;
    }
    T &get(int entity) {
        assert(entity_to_idx.count(entity) != 0 && "not registered");
        return components[entity_to_idx[entity]];
    }
    void erase(int entity) {
        if (!entity_to_idx.count(entity))
            return;
        int left = entity_to_idx[entity];
        int right = count - 1;
        swap(components[left], components[right]);

        int right_entity = idx_to_entity[right];
        entity_to_idx[right_entity] = left;
        idx_to_entity[left] = right_entity;
        entity_to_idx.erase(entity);
        count--;
    }
    size_t size() const {
        return count;
    }
};
