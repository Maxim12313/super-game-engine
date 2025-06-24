#pragma once
#include "common.hpp"
#include "components/components.hpp"

inline void rectangle_draw(Entity entity, Coordinator &coordinator) {
    Position position = coordinator.get<Position>(entity);
    Color color = coordinator.get<Color>(entity);
    WidthHeight wh = coordinator.get<WidthHeight>(entity);
    Graphics::draw_rectangle(position.pos.x, position.pos.y, wh.wh.x, wh.wh.y,
                             color);
}

inline void rectangle_init(Entity entity, Coordinator &coordinator,
                           Position position, WidthHeight width_height,
                           Color color) {
    components_init(entity, coordinator, position, width_height, color,
                    Shape::rectangle);
}
