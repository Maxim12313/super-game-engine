#pragma once
#include "packed_array.hpp"
#include "signature_utils.hpp"

// default init for set
// not default init for get, (should avoid, mostly for debugging)
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
        assert(contains(entity) && "not registered");
        return signatures.get(entity);
    }

    bool contains(Entity entity) {
        return signatures.contains(entity);
    }

    template <typename T>
    void set_bit(Entity entity) {
        if (!contains(entity)) {
            set(entity, 0);
        }
        Signature &curr = signatures.get(entity);
        curr = signature_utils::set_bit<T>(curr);
    }

    template <typename T>
    void reset_bit(Entity entity) {
        Signature &curr = signatures.get(entity);
        curr = signature_utils::reset_bit<T>(curr);
    }
};
