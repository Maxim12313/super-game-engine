#pragma once
#include "common.hpp"
#include "game_objects/circle.hpp"

inline void player_init(Entity entity, Coordinator &coordinator,
                        Position position, Radius radius, Color color,
                        MoveSpeed move_speed) {
    circle_init(entity, coordinator, position, radius, color);
    coordinator.assign_component(entity, move_speed);
}

inline void wasd_move(Entity entity, Coordinator &coordinator) {
    Position &position = coordinator.get_component<Position>(entity);
}
