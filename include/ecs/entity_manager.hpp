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
    EntityManager();
    Entity create_entity();
    void erase_entity(Entity entity);
};
