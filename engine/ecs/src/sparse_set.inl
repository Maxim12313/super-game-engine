#pragma once
#include "sparse_set.hpp"
#include "utils/macros.hpp"
#include "ecs/group.hpp"

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

    // group observer
    if (m_group)
        m_group->add_update(entity);
}

template <typename T>
template <typename... Args>
void SparseSet<T>::emplace_back(Entity entity, Args &&...args) {
    ASSERT_MSG(m_to_idx.count(entity) == 0, "already registered {} for type {}",
               entity, typeid(T).name());
    m_to_idx[entity] = m_to_entity.size();
    m_data.emplace_back(args...);
    m_to_entity.push_back(entity);

    // group observer
    if (m_group)
        m_group->add_update(entity);
}

template <typename T>
void SparseSet<T>::remove(Entity entity) {
    if (!contains(entity))
        return;

    Entity a = entity;
    Entity b = m_to_entity.back();

    // swap with the end
    swap_ent_ent(a, b);

    // pop off the end
    m_to_entity.pop_back();
    m_data.pop_back();
    m_to_idx.erase(a);

    // group observer
    if (m_group)
        m_group->remove_update(entity);
}

template <typename T>
bool SparseSet<T>::swap_ent_idx(Entity entity, int idx) {
    Entity a = entity;
    Entity b = m_to_entity[idx];
    return swap_ent_ent(a, b);
}

// private methods ********
template <typename T>
T &SparseSet<T>::get(Entity entity) {
    ASSERT_MSG(contains(entity), "entity {} is not registered for type {}",
               entity, typeid(T).name());
    return m_data[m_to_idx[entity]];
}

template <typename T>
bool SparseSet<T>::swap_ent_ent(Entity a, Entity b) {
    // do nothing
    if (a == b)
        return false;

    int a_idx = m_to_idx[a];
    int b_idx = m_to_idx[b];

    // swap everything
    std::swap(m_data[a_idx], m_data[b_idx]);
    std::swap(m_to_entity[a_idx], m_to_entity[b_idx]);
    std::swap(m_to_idx[a], m_to_idx[b]);

    return true;
}

}; // namespace ecs::internal
