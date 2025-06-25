#pragma once
#include "sparse_set.hpp"
#include "signature_utils.hpp"

/**
 * @class SignatureManager
 * @brief Wrapper over packed array specific for maintaing and setting
 * signatures default init for set not default init for get (should avoid,
 * mostly for debugging)
 */
class SignatureManager {
private:
    SparseSet<Signature> signatures;

public:
    SignatureManager() {
    }

    /**
     * @brief Init entity signature with signature value
     */
    void set(Entity entity, Signature signature) {
        signatures[entity] = signature;
    }

    /**
     * @brief Default init entity signature to 0 empty
     */
    void set(Entity entity) {
        signatures[entity];
    }

    /**
     * @brief Erase the entity signature if it exists
     */
    void erase(Entity entity) {
        signatures.erase(entity);
    }

    /**
     * @return Reference to the signature of entity
     */
    Signature &operator[](Entity entity) {
        return signatures[entity];
    }

    /**
     * @return True if the bit corresponding to the T type is set in
     * entity's signature
     */
    template <typename T>
    bool has_bit(Entity entity) {
        Signature curr = signatures[entity];
        return signature_utils::has_bit<T>(curr);
    }

    /**
     * @return True if a signature is set for entity
     */
    bool contains(Entity entity) {
        return signatures.contains(entity);
    }

    /**
     * @brief Sets the T type bit in entity's signature
     */
    template <typename T>
    void set_bit(Entity entity) {
        Signature &curr = signatures[entity];
        signature_utils::set_bit<T>(curr);
    }

    /**
     * @brief Resets the T type bit in entity's signature
     */
    template <typename T>
    void reset_bit(Entity entity) {
        Signature &curr = signatures[entity];
        signature_utils::reset_bit<T>(curr);
    }
};
