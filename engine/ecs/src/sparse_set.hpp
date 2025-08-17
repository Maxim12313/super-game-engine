#pragma once
#include "isparse_set.hpp"
#include "utils/macros.hpp"
#include "ecs/common.hpp"
#include <array>
#include <utility>
#include <vector>
#include <unordered_map>
#include "ecs/group.hpp"

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

    // Swap entire positions between obj id'd by entity and obj id'd by idx
    // Returns if succeeded (only doesnt if both refer same obj)
    bool swap_ent_idx(Entity entity, int idx) override;

private:
    // Access entity's val. Requires that val exists
    T &get(Entity entity);

    // Swap positions of a, b in m_data, also updating to_idx and to_entity
    // Returns true if a != b and swapped
    bool swap_ent_ent(Entity a, Entity b);

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
    bool swapped = swap_ent_ent(a, b);
    if (swapped) {
        // pop off the back entry
        m_to_idx.erase(a);
        m_to_entity.pop_back();
        m_data.pop_back();
    }

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
