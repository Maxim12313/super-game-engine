#pragma once
#include "common.hpp"
#include "packed_array.hpp"

/**
 * @class System
 * @brief Abstract class for a system which can register entities and operate on them
 * NOTE: templating for systems expects the following class functions to be implemented
 * void run(Coordinator &)
 * don't want to deal with cyclic dependencies
 */
class System {
protected:
    PackedArray<Entity, MAX_ENTITIES> subscribed_entities;

public:
    System() {
    }
    virtual ~System() {
    }
    void add(Entity entity) {
        if (!subscribed_entities.contains(entity))
            subscribed_entities.set(entity, entity);
    }
    void erase(Entity entity) {
        if (subscribed_entities.contains(entity))
            subscribed_entities.erase(entity);
    }

    bool contains(Entity entity) {
        return subscribed_entities.contains(entity);
    }
    virtual Signature get_signature() = 0;
};
