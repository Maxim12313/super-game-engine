#pragma once
#include "common.hpp"
#include "ecs/packed_array.hpp"
#include "id_utils.hpp"
#include "utils/test_utils.hpp"
#include <spdlog/spdlog.h>
#include <stack>
#include <vector>

/**
 * @class EntityManager
 * @brief Ensures unique entity ids are provisioned and
 * tracks entities for subscribed to each component
 */
class EntityManager {
private:
    stack<Entity> available;
    vector<PackedArray<Entity>> subscribed;

    /// protected get_id
    template <typename Component>
    Component_ID get_id() {
        Component_ID id = id_utils::get_component_id<Component>();
        ASSERT(id >= subscribed.size() && "Already registered");
        return id;
    }

public:
    /// Initialize with [0, MAX_ENTITIES) available ids
    EntityManager();

    template <typename Component>
    void register_component() {
        // just check not registered
        get_id<Component>();
        subscribed.emplace_back();
    }

    /// The unique entity identifier free for use.
    Entity create_entity();

    /// Destroy this entity and reclaim the id
    void destroy_entity(Entity entity);

    /// Removes entity's compoennt if it exists otherwise does nothing
    template <typename Component>
    void erase_component(Entity entity) {
        Component_ID id = get_id<Component>();
        auto &array = subscribed[id];
        array.erase(entity);
    }

    /// Adds component to tracking for this component
    template <typename Component>
    void add_component(Entity entity) {
        Component_ID id = get_id<Component>();
        auto &array = subscribed[id];
        array[entity] = entity;
    }
};
