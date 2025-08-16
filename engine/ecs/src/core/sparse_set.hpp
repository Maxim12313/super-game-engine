#pragma once
#include "isparse_set.hpp"
#include "utils/macros.hpp"
#include "ecs/common.hpp"
#include <array>
#include <utility>
#include <vector>
#include <unordered_map>

namespace ecs::internal {

/**
 * @class SparseSet
 * @brief Data container supporting cache fast iteration and key value indexing
 */
template <typename T>
class SparseSet : public ISparseSet {

public:
    SparseSet() = default;

    // Access entity's val. Requires that val exists
    T &operator[](Entity entity);

    // Registeres val for entity, requires that entity not yet registered
    // anything
    void push_back(Entity entity, const T &val);

    // Creates val in place for entity
    template <typename... Args>
    void emplace_back(Entity entity, Args &&...args);

    // Will erase the entity from the array if it exists and otherwise do
    // nothing
    void remove(Entity entity) override;

private:
    // Access entity's val. Requires that val exists
    T &get(Entity entity);

private:
    std::vector<T> m_data;
};
} // namespace ecs::internal

namespace ecs::internal {

// public methods ********
template <typename T>
T &SparseSet<T>::operator[](Entity entity) {
    return get(entity);
}

template <typename T>
void SparseSet<T>::push_back(Entity entity, const T &val) {
    ASSERT_MSG(m_to_idx.count(entity) == 0, "already registered {} for type {}",
               entity, typeid(T).name());
    m_to_idx[entity] = m_to_entity.size();
    m_data.push_back(val);
    m_to_entity.push_back(entity);
}

template <typename T>
template <typename... Args>
void SparseSet<T>::emplace_back(Entity entity, Args &&...args) {
    ASSERT_MSG(m_to_idx.count(entity) == 0, "already registered {} for type {}",
               entity, typeid(T).name());
    m_to_idx[entity] = m_to_entity.size();
    m_data.emplace_back(args...);
    m_to_entity.push_back(entity);
}

template <typename T>
void SparseSet<T>::remove(Entity entity) {
    if (!contains(entity))
        return;

    Entity &left_entity = entity;

    int left_idx = m_to_idx[left_entity];
    int right_idx = m_to_entity.size() - 1;

    Entity right_entity = m_to_entity[right_idx];

    if (left_entity != right_entity) {
        // move left data to right side to pop
        std::swap(m_to_entity[left_entity], m_to_entity[right_entity]);
        std::swap(m_data[left_idx], m_data[right_idx]);

        // remap right ent to left
        m_to_idx[right_entity] = left_idx;
    }

    // cleanup all left side info
    m_to_idx.erase(left_entity);
    m_to_entity.pop_back();
    m_data.pop_back();
}

// private methods ********
template <typename T>
T &SparseSet<T>::get(Entity entity) {
    ASSERT_MSG(contains(entity), "entity {} is not registered for type {}",
               entity, typeid(T).name());
    return m_data[m_to_idx[entity]];
}

}; // namespace ecs::internal
