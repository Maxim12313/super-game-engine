#pragma once
#include "common.hpp"
#include "game_objects/circle.hpp"
#include "game_objects/rectangle.hpp"

inline void player_init(Entity entity, Coordinator &coordinator,
                        Position position, WidthHeight width_height,
                        Color color, MoveSpeed move_speed) {

    rectangle_init(entity, coordinator, position, width_height, color);
    coordinator.assign_component(entity, move_speed);
    coordinator.assign_component(entity, PlayerMovable{});
}
