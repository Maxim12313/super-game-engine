#pragma once
#include "components/components.hpp"
#include "ecs/coordinator.hpp"
#include "ecs/system.hpp"
#include <raylib.h>
#include <raymath.h>

bool is_colliding_rect_rect(Entity a, Entity b, Coordinator &c) {
    auto a_pos = c.get<Position>(a).pos;
    auto a_vel = c.get<Velocity>(a).velocity;
    auto a_wh = c.get<WidthHeight>(a);

    auto b_pos = c.get<Position>(a).pos;
    auto b_vel = c.get<Velocity>(a).velocity;
    auto b_wh = c.get<WidthHeight>(a);

    // for now we give a priority and have it determine the new positions
    auto a1 = a_pos;
    auto a2 = Vector2Add(a1, a_wh.wh);

    auto b1 = b_pos;
    auto b2 = Vector2Add(b1, b_wh.wh);
}

// class CollisionSystem : public System {
// public:
//     Signature get_signature() override {
//         return internal::set_signature<Position, Velocity, Shape,
//                                               Collided>();
//     }
//
//     void run(Coordinator &c) override {
//         // for now assume all rectangles
//         // TOOD: optimize this
//         for (auto i = begin(entities); i != end(entities); i++) {
//             for (auto j = i + 1; j != end(entities); j++) {
//             }
//         }
//     }
// };
