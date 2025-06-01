#pragma once
#include "common.hpp"
#include "packed_array.hpp"

// NOTE: templating for systems expects the following class functions to be implemented
// void run(Coordinator &)
// don't want to deal with cyclic dependencies

class System {
protected:
    PackedArray<Entity, MAX_ENTITIES> subscribed_entities;

public:
    System() {
    }
    virtual ~System() {
    }
    void add(Entity entity) {
        subscribed_entities.set(entity, entity);
    }
    void erase(Entity entity) {
        subscribed_entities.erase(entity);
    }
    virtual Signature get_signature() = 0;
};
