#pragma once
#include "../include/utils/test_utils.hpp"
#include "common.hpp"
#include <stack>

/**
 * @class EntityManager
 * @brief Ensures unique entity ids are provisioned
 */
class EntityManager {
private:
    stack<Entity> available_entities;

public:
    /**
     * @brief Initialize with [0, MAX_ENTITIES) available ids
     */
    EntityManager() {
        for (int id = 0; id < MAX_ENTITIES; id++) {
            available_entities.push(Entity(id));
        }
    }
    /**
     * @return The unique entity identifier free for use.
     * NOTE: this does not return a random id
     */
    Entity create_entity() {
        // NOTE: consider whether deny or just flag full when full
        ASSERT(!available_entities.empty() && "full");
        Entity res = available_entities.top();
        available_entities.pop();
        return res;
    }
    /**
     * @brief Erase this entity and reclaim the id
     */
    void erase_entity(Entity entity) {
        available_entities.push(Entity(entity));
    }
};
