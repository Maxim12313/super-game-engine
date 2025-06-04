#pragma once
#include "../include/utils/test_utils.hpp"
#include "common.hpp"
#include <stack>

/**
 * @class EntityManager
 * @brief Ensures unique entity ids are provisioned
 *
 */
class EntityManager {
private:
    stack<Entity> available_entities;

public:
    EntityManager() {
        for (int id = 0; id < MAX_ENTITIES; id++) {
            available_entities.push(Entity(id));
        }
    }
    Entity create_entity() {
        // NOTE: consider whether deny or just flag full when full
        ASSERT(!available_entities.empty() && "full");
        Entity res = available_entities.top();
        available_entities.pop();
        return res;
    }
    void erase_entity(Entity entity) {
        available_entities.push(Entity(entity));
    }
};
