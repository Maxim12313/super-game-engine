#pragma once
#include "../components/components.hpp"
#include "packed_array.hpp"

class SignatureManager {
private:
    PackedArray<Signature, MAX_ENTITIES> signatures;

public:
    SignatureManager() {
    }

    void set(Entity entity, Signature signature) {
        signatures.set(entity, signature);
    }

    void erase(Entity entity) {
        signatures.erase(entity);
    }

    Signature &get(Entity entity) {
        return signatures.get(entity);
    }

    template <typename T>
    void set_bit(Entity entity) {
        Type_ID id = get_type_id<T>();
        Signature &curr = signatures.get(entity);
        curr |= (1u << id);
    }

    template <typename T>
    void reset_bit(Entity entity) {
        Type_ID id = get_type_id<T>();
        Signature &curr = signatures.get(entity);
        if (curr & (1u << id))
            curr -= (1u << id);
    }
};
