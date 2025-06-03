#pragma once
#include "coordinator.hpp"
#include "id_utils.hpp"
#include "system.hpp"
#include <memory>
#include <vector>

class Coordinator;

/**
 * @class SystemManager
 * @brief Manages registered systems with adding entities and keeping required signature for each system
 *
 */
class SystemManager {
private:
    vector<unique_ptr<System>> systems;
    vector<Signature> signatures;

public:
    SystemManager() {
    }

    template <typename T>
    void register_system(T system) {
        System_ID id = id_utils::get_system_id<T>();
        ASSERT(id >= systems.size() && "already registered");
        systems.emplace_back(make_unique<T>(system));
        signatures.push_back(system.get_signature());
    }

    template <typename T>
    T *get_system() {
        System_ID id = id_utils::get_system_id<T>();
        ASSERT(id < systems.size() && "unregistered system");
        System *system = systems[int(id)].get();
        return static_cast<T *>(system);
    }

    void add_entity(Entity entity, Signature signature) {
        for (int i = 0; i < systems.size(); i++) {
            Signature required = signatures[i];
            // if signature contains required
            if ((required & signature) == required) {
                System *system = systems[i].get();
                system->add(entity);
            }
        }
    }

    void erase(Entity entity) {
        for (int i = 0; i < systems.size(); i++) {
            System *system = systems[i].get();
            if (system->contains(entity))
                system->erase(entity);
        }
    }
};
