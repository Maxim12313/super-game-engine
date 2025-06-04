#pragma once
#include "packed_array.hpp"
#include "signature_utils.hpp"

/**
 * @class SignatureManager
 * @brief Wrapper over packed array specific for maintaing and setting signatures
 *  default init for set
 *  not default init for get (should avoid, mostly for debugging)
 */
class SignatureManager {
private:
    PackedArray<Signature, MAX_ENTITIES> signatures;

public:
    SignatureManager() {
    }

    /**
     * @brief Init entity signature with signature value
     *
     * @param entity
     * @param signature
     */
    void set(Entity entity, Signature signature) {
        signatures[entity] = signature;
    }

    /**
     * @brief Default init entity signature to 0 empty
     *
     * @param entity
     */
    void set(Entity entity) {
        signatures[entity];
    }

    /**
     * @brief Erase the entity signature if it exists
     *
     * @param entity
     */
    void erase(Entity entity) {
        signatures.erase(entity);
    }

    /**
     * @param entity
     * @return Reference to the signature of entity
     */
    Signature &operator[](Entity entity) {
        return signatures[entity];
    }

    /**
     * @tparam T
     * @param entity
     * @return True if the bit corresponding to the T type is set in
     * entity's signature
     */
    template <typename T>
    bool has_bit(Entity entity) {
        Signature curr = signatures[entity];
        return signature_utils::has_bit<T>(curr);
    }

    /**
     * @param entity
     * @return True if a signature is set for entity
     */
    bool contains(Entity entity) {
        return signatures.contains(entity);
    }

    /**
     * @brief Sets the T type bit in entity's signature
     *
     * @tparam T
     * @param entity
     */
    template <typename T>
    void set_bit(Entity entity) {
        Signature &curr = signatures[entity];
        curr = signature_utils::set_bit<T>(curr);
    }

    /**
     * @brief Resets the T type bit in entity's signature
     *
     * @tparam T
     * @param entity
     */
    template <typename T>
    void reset_bit(Entity entity) {
        Signature &curr = signatures[entity];
        curr = signature_utils::reset_bit<T>(curr);
    }
};
