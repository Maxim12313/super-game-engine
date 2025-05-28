#pragma once
#include "common.hpp"
#include "component_manager.hpp"
#include "entity_manager.hpp"
#include "packed_array_manager.hpp"
#include "signature_manager.hpp"

// class Coordinator {
// private:
//     EntityManager entity_manager;
//
//     ComponentManager component_manager;
//
//     SystemManager system_manager;
//
// public:
//     Coordinator() {
//     }
//
//     // -----------------ENTITY------------------
//     Entity get_entity() {
//         return entity_manager.get_entity();
//     }
//
//     void return_entity(Entity entity) {
//         entity_manager.return_entity(entity);
//     }
//
//     // -------------COMPONENT/SYSTEM-----------
//     template <typename T>
//     void register_componen() {
//         component_manager.register_component<T>();
//     }
//
//     template <typename T>
//     void set_component(Entity entity, T data) {
//         component_manager.set_component(entity, data);
//         entity_signatures.set_bit<T>(entity);
//     }
//
//     template <typename T>
//     void erase_component(Entity entity) {
//         component_manager.erase_component<T>(entity);
//         entity_signatures.erase(entity);
//     }
// };
