#pragma once
#include "utils/macros.hpp"
#include "ecs/common.hpp"
#include <array>
#include <vector>
#include <unordered_map>

namespace ecs::internal {

/**
 * @class ISparseSet
 * @brief Interface placeholder for type erasing in packed array manager
 *
 */
class ISparseSet {
protected:
    std::unordered_map<Entity, int> to_idx;
    std::vector<Entity> to_entity;

public:
    virtual ~ISparseSet() = default;
    /**
     * @brief Erases the data entry for the given entity
     *
     * @param entity The entity whos data will be erased for this type
     */
    virtual void erase(Entity entity) = 0;

    /**
     * @brief Clear the array, resetting size to 0
     */
    void clear() {
        to_idx.clear();
        to_entity.clear();
    }

    /**
     * @return Returns if entity is registered with this packed array
     */
    bool contains(Entity entity) {

        return to_idx.count(entity);
    }

    size_t size() {
        return to_entity.size();
    }

    const std::vector<Entity> &entities() {
        return to_entity;
    }
};

/**
 * @class SparseSet
 * @brief Data container supporting cache fast iteration and key value indexing
 */
template <typename T>
class SparseSet : public ISparseSet {

public:
    SparseSet() = default;

    /**
     * @brief Will default init if entity not contained in the array
     * @return Returns a reference to the T data entry for entity
     */
    T &operator[](Entity entity);

    /**
     * @brief Will erase the entity from the array if it exists and
     * otherwise do nothing
     */
    void erase(Entity entity) override;

    /**
     * @brief Iterator to first element
     */
    std::vector<T>::iterator begin();
    /**
     * @brief Iterator to 1 beyond the last valid element
     */
    std::vector<T>::iterator end();

private:
    // @brief If not already registered, default init T datatype for entity
    void register_entity(Entity entity) {
        ASSERT(to_idx.count(entity) == 0 && "already registered");
        to_idx[entity] = to_entity.size();

        // default init
        data.emplace_back();
        to_entity.push_back(entity);
    }

private:
    std::vector<T> data;
};
} // namespace ecs::internal

namespace ecs::internal {

template <typename T>
T &SparseSet<T>::operator[](Entity entity) {
    if (!contains(entity))
        register_entity(entity);
    return data[to_idx[entity]];
}

template <typename T>
void SparseSet<T>::erase(Entity entity) {
    if (!contains(entity))
        return;

    Entity &left_entity = entity;

    int left_idx = to_idx[left_entity];
    int right_idx = to_entity.size() - 1;

    Entity right_entity = to_entity[right_idx];

    if (left_entity != right_entity) {
        // move left data to right side to pop
        std::swap(to_entity[left_entity], to_entity[right_entity]);
        std::swap(data[left_idx], data[right_idx]);

        // remap right ent to left
        to_idx[right_entity] = left_idx;
    }

    // cleanup all left side info
    to_idx.erase(left_entity);
    to_entity.pop_back();
    data.pop_back();
}

template <typename T>
std::vector<T>::iterator SparseSet<T>::begin() {
    return std::begin(data);
}

template <typename T>
std::vector<T>::iterator SparseSet<T>::end() {
    return std::end(data);
}

}; // namespace ecs::internal
