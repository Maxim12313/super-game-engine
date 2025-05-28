#pragma once
#include "packed_array.hpp"
#include "packed_array_manager.hpp"

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
    virtual void run(PackedArrayManager<MAX_ENTITIES> &component_manager) = 0;

    // mean just 1 call on registration
    virtual Signature get_signature() = 0;
};
