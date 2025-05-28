#pragma once
#include "system.hpp"
#include "type_id_utils.hpp"
#include <memory>
#include <vector>

class SystemManager {
private:
    vector<unique_ptr<System>> systems;
    vector<Signature> signatures;

    template <typename T>
    System *get_system() {
        Type_ID id = get_type_id<T>();
        assert(id < systems.size() && "unregistered type");
        return systems[int(id)].get();
    }

public:
    SystemManager() {
    }

    template <typename T>
    void register_system(Signature signature) {
        Type_ID id = get_type_id<T>();
        assert(id >= systems.size() && "already registered");
        systems.emplace_back(make_unique(T{}));
        signatures.push_back(signature);
    }

    template <typename T>
    void run_system(PackedArrayManager<MAX_ENTITIES> &component_manager) {
        System *system = get_system<T>();
        system->run(component_manager);
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
};
