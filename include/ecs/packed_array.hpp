#pragma once
#include "../utils/test_utils.hpp"
#include "common.hpp"
#include <array>
#include <unordered_map>

/**
 * @class IPackedArray
 * @brief Interface placeholder for type erasing in packed array manager
 *
 */
class IPackedArray {
public:
    virtual ~IPackedArray() {
    }
    /**
     * @brief Erases the data entry for the given entity
     *
     * @param entity The entity whos data will be erased for this type
     */
    virtual void erase(Entity entity) = 0;
};

/**
 * @class PackedArray
 * @brief Data container supporting cache fast iteration and key value indexing
 */
template <typename T, size_t MAX>
class PackedArray : public IPackedArray {
private:
    int count = 0;
    array<T, MAX> data;

    unordered_map<Entity, int> entity_to_idx;
    unordered_map<int, Entity> idx_to_entity;

    /**
     * @brief If not already registered, default init T datatype for entity
     *
     * @param entity
     */
    void register_entity(Entity entity) {
        ASSERT(entity_to_idx.count(entity) == 0 && "already registered");
        entity_to_idx[entity] = count;
        idx_to_entity[count] = entity;
        data[count] = T(); // default init
        count++;
    }

public:
    PackedArray() {
    }

    /**
     * @brief Clear the array, resetting size to 0
     */
    void clear() {
        count = 0;
        entity_to_idx.clear();
        idx_to_entity.clear();
    }

    /**
     * @param entity
     * @return Returns if entity is registered with this packed array
     */
    bool contains(Entity entity) {
        return entity_to_idx.count(entity);
    }

    /**
     * @brief Will default init if entity not contained in the array
     *
     * @param entity
     * @return Returns a reference to the T data entry for entity
     */
    T &operator[](Entity entity) {
        if (!contains(entity))
            register_entity(entity);
        return data[entity_to_idx[entity]];
    }

    /**
     * @brief Will erase the entity from the array if it exists and
     * otherwise do nothing
     *
     * @param entity
     */
    void erase(Entity entity) override {
        if (!contains(entity))
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

    /**
     * @return Number of valid entries
     */
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
