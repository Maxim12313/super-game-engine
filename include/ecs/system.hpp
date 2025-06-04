#pragma once
#include "common.hpp"
#include "packed_array.hpp"

/**
 * @class System
 * @brief Abstract class for a system which can register entities and
 * operate on them
 */
class System {
protected:
    PackedArray<Entity, MAX_ENTITIES> subscribed_entities;

public:
    System() {
    }
    virtual ~System() {
    }
    /**
     * @brief Registers entity to be read/modified by this system and
     * nothing if already registered
     */
    void register_entity(Entity entity) {
        subscribed_entities[entity] = entity;
    }
    /**
     * @brief Erases the entity from this system's tracking and nothing
     * if already not contained
     */
    void erase(Entity entity) {
        subscribed_entities.erase(entity);
    }

    /**
     * @return True if entity is tracked by the system
     */
    bool contains(Entity entity) {
        return subscribed_entities.contains(entity);
    }

    /**
     * @return The systems's signature, corresponding to the components
     * that an entity must have to be tracked by this system
     */
    virtual Signature get_signature() = 0;
};
