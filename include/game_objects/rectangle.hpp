#pragma once
#include "common.hpp"

inline void rectangle_draw(Entity entity, Coordinator &coordinator) {
    Position position = coordinator.get_component<Position>(entity);
    Color color = coordinator.get_component<Color>(entity);
    WidthHeight lh = coordinator.get_component<WidthHeight>(entity);
    Graphics::draw_rectangle(position.pos.x, position.pos.y, lh.width,
                             lh.height, color);
}

inline void rectangle_init(Entity entity, Coordinator &coordinator,
                           Position position, Radius radius, Color color) {
    components_init(entity, coordinator, position, radius, color);
}
