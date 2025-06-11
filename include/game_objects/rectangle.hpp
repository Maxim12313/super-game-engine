#pragma once
#include "common.hpp"

inline void draw_rectangle(Entity entity, Coordinator &coordinator) {
    Position position = coordinator.strict_get_component<Position>(entity);
    Color color = coordinator.strict_get_component<Color>(entity);
    WidthHeight lh = coordinator.strict_get_component<WidthHeight>(entity);
    Graphics::draw_rectangle(position.pos.x, position.pos.y, lh.width,
                             lh.height, color);
}
