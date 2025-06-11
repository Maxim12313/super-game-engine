#pragma once
#include "coordinator.hpp"
#include "id_utils.hpp"
#include "system.hpp"
#include <memory>
#include <vector>

class Coordinator;

/**
 * @class SystemManager
 * @brief Manages registered systems with adding entities and keeping required
 * signature for each system
 *
 */
class SystemManager {
private:
    vector<unique_ptr<System>> systems;
    vector<Signature> signatures;

public:
    SystemManager() {
    }

    /**
     * @brief Register T system as an available to manage
     */
    template <typename T>
    void register_system(T system) {
        System_ID id = id_utils::get_system_id<T>();
        ASSERT(id >= systems.size() && "already registered");
        systems.emplace_back(make_unique<T>(system));
        signatures.push_back(system.get_signature());
    }

    /**
     * @brief Run the system T
     */
    template <typename T>
    void run_system(Coordinator &coordinator) {
        T *system = get_system<T>();
        system->run(coordinator);
    }

    /**
     * @brief Requires that T system be registered
     * @return A pointer to the T system
     */
    template <typename T>
    T *get_system() {
        System_ID id = id_utils::get_system_id<T>();
        ASSERT(id < systems.size() && "unregistered system");
        System *system = systems[int(id)].get();
        return static_cast<T *>(system);
    }

    /**
     * @brief Register fresh entity with all registered systems that
     * accept its signature
     */
    void register_updated_entity(Entity entity, Signature signature) {
        for (int i = 0; i < systems.size(); i++) {
            Signature required = signatures[i];

            // if signature contains required bits
            if ((required & signature) == required) {
                System *system = systems[i].get();
                system->register_entity(entity);
            }
        }
    }
    /**
     * @brief  Erase fresh entity from all registered systems that
     * used to accept entity signature but no longer accept the updated
     * signature
     */
    void erase_updated_entity(Entity entity, Signature signature) {
        for (int i = 0; i < systems.size(); i++) {
            Signature required = signatures[i];
            System *system = systems[i].get();
            if ((required & signature) != required) {
                system->erase(entity);
            }
        }
    }

    /**
     * @brief Erase this entity from all registered systems
     */
    void erase_entity(Entity entity) {
        for (auto &system : systems) {
            system->erase(entity);
        }
    }
};
