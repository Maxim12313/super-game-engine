#pragma once
#include "common.hpp"

inline void draw_circle(Entity entity, Coordinator &coordinator) {
    Position position = coordinator.strict_get_component<Position>(entity);
    Radius radius = coordinator.strict_get_component<Radius>(entity);
    Color color = coordinator.strict_get_component<Color>(entity);
    Graphics::draw_circle(position.pos.x, position.pos.y, radius.radius, color);
}
