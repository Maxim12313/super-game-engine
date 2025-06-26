#pragma once
#include "common.hpp"
#include <raylib.h>
#include <raymath.h>

inline void wasd_move(Entity entity, Coordinator &coordinator) {
    auto movable = coordinator.get<PlayerMovable>(entity);
    auto &position = coordinator.get<Position>(entity);
    auto speed = coordinator.get<MoveSpeed>(entity);

    Vector2 change(0, 0);
    if (IsKeyDown(KEY_D))
        change.x++;
    if (IsKeyDown(KEY_A))
        change.x--;
    if (IsKeyDown(KEY_W))
        change.y--;
    if (IsKeyDown(KEY_S))
        change.y++;

    if (Vector2Length(change) == 0)
        return;

    float delta_time = coordinator.get_delta_time();

    change = Vector2Normalize(change);
    change = Vector2Scale(change, speed.speed * delta_time);
    position.pos = Vector2Add(position.pos, change);
}

// /**
//  * @class DrawSystem
//  * @brief Takes Shape, Position, Color
//  *
//  */
// class MoveSystem : public System {
// public:
//     /**
//      * @brief Player controllable
//      */
//     void run(Coordinator &coordinator) {
//         for (Entity entity : entities) {
//             wasd_move(entity, coordinator);
//         }
//     }
//
//     Signature get_signature() override {
//         return internal::set_signature<Color, Position,
//         PlayerMovable>();
//     }
// };
