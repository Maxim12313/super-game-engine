#pragma once
#include "common.hpp"
#include "sparse_set.hpp"
#include "utils/macros.hpp"
#include <stack>
#include <vector>

/**
 * @class EntityManager
 * @brief Ensures unique entity ids are provisioned and
 * tracks entities for subscribed to each component
 */
class EntityManager {
private:
    std::stack<Entity> available;

public:
    /// Initialize with [0, MAX_ENTITIES) available ids
    EntityManager();

    /// The unique entity identifier free for use.
    Entity create_entity();

    /// Destroy this entity and reclaim the id
    void destroy_entity(Entity entity);
};
