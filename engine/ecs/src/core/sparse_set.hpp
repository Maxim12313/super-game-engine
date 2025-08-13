#pragma once
#include "utils/macros.hpp"
#include "ecs/common.hpp"
#include <array>
#include <utility>
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
     * @brief Access entity's val. Requires that val exists
     * @return Returns a reference to the T data entry for entity
     */
    T &operator[](Entity entity);

    /**
     * @brief Registeres val for entity, requires that entity not yet registered
     * anything
     * @param val
     */
    void push_back(Entity entity, const T &val);

    /**
     * @brief Creates val in place for entity
     * @tparam Args
     * @param args
     */
    template <typename... Args>
    void emplace_back(Entity entity, Args &&...args);

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
    void register_entity(Entity entity);

private:
    std::vector<T> m_data;
};
} // namespace ecs::internal

namespace ecs::internal {

// TODO: make api unfiorm, change this to get<T>
template <typename T>
T &SparseSet<T>::operator[](Entity entity) {
    ASSERT_MSG(contains(entity), "entity {} is not registered for type {}",
               entity, typeid(T).name());
    return m_data[to_idx[entity]];
}

// TODO: operator notation looks terrible too
template <typename T>
void SparseSet<T>::push_back(Entity entity, const T &val) {
    register_entity(entity);
    operator[](entity) = val;
}

template <typename T>
template <typename... Args>
void SparseSet<T>::emplace_back(Entity entity, Args &&...args) {
    register_entity(entity);
    operator[](entity) = T(std::forward<Args>(args)...);
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
        std::swap(m_data[left_idx], m_data[right_idx]);

        // remap right ent to left
        to_idx[right_entity] = left_idx;
    }

    // cleanup all left side info
    to_idx.erase(left_entity);
    to_entity.pop_back();
    m_data.pop_back();
}

template <typename T>
std::vector<T>::iterator SparseSet<T>::begin() {
    return std::begin(m_data);
}

template <typename T>
std::vector<T>::iterator SparseSet<T>::end() {
    return std::end(m_data);
}

template <typename T>
void SparseSet<T>::register_entity(Entity entity) {
    ASSERT_MSG(to_idx.count(entity) == 0, "already registered {} for type {}",
               entity, typeid(T).name());
    to_idx[entity] = to_entity.size();

    // default init
    m_data.emplace_back();
    to_entity.push_back(entity);
}

}; // namespace ecs::internal
