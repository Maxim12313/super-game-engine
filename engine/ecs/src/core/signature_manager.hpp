#pragma once
#include "utils.hpp"
#include "sparse_set.hpp"

namespace ecs::internal {

/**
 * @class SignatureManager
 * @brief Wrapper over packed array specific for maintaing and setting
 * signatures default init for set not default init for get (should avoid,
 * mostly for debugging)
 */
class SignatureManager {
public:
    SignatureManager() = default;

    // Init signature for entity
    void push_back(Entity entity, Signature signature = 0) {
        m_signatures.push_back(entity, signature);
    }

    // Erase the entity signature if it exists
    void erase(Entity entity) {
        m_signatures.remove(entity);
    }

    // return Reference to the signature of entity
    Signature &operator[](Entity entity) {
        return m_signatures[entity];
    }

    // of course must exist
    // returns True if the bit corresponding to the T type is set in
    template <typename T>
    bool has_bit(Entity entity) {
        Signature curr = m_signatures[entity];
        return has_bit<T>(curr);
    }

    bool contains(Entity entity) {
        return m_signatures.contains(entity);
    }

    // Default inits entity signature
    // Sets the T type bit in entity's signature, requires that
    template <typename T>
    void set_bit(Entity entity) {
        if (!contains(entity))
            push_back(entity);
        Signature &curr = m_signatures[entity];
        curr = utils::set_bit<T>(curr);
    }

    // Resets the T type bit in entity's signature
    template <typename T>
    void reset_bit(Entity entity) {
        Signature &curr = m_signatures[entity];
        curr = utils::reset_bit<T>(curr);
    }

private:
    SparseSet<Signature> m_signatures;
};
} // namespace ecs::internal
