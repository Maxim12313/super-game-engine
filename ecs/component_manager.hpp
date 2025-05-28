#pragma once
#include "common.hpp"
#include "packed_array_manager.hpp"
#include "signature_manager.hpp"

class ComponentManager {
private:
    PackedArrayManager<MAX_ENTITIES> components;
    SignatureManager entity_signatures;

public:
    ComponentManager() {
    }

    template <typename T>
    void register_component() {
        components.register_type<T>();
    }

    template <typename T>
    void set_component(Entity entity, T data) {
        components.set(entity, data);
        entity_signatures.set_bit<T>(entity);
    }

    template <typename T>
    void erase_component(Entity entity) {
        components.erase<T>(entity);
    }

    template <typename T>
    PackedArray<T, MAX_ENTITIES> *get_components() {
        return components.get_array<T>();
    }
};
