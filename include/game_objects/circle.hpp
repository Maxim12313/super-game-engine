#pragma once
#include "common.hpp"
#include "components/components.hpp"

inline void circle_draw(Entity entity, Coordinator &coordinator) {
    Position position = coordinator.get_component<Position>(entity);
    Radius radius = coordinator.get_component<Radius>(entity);
    Color color = coordinator.get_component<Color>(entity);
    Graphics::draw_circle(position.pos.x, position.pos.y, radius.radius, color);
}

inline void circle_init(Entity entity, Coordinator &coordinator,
                        Position position, Radius radius, Color color) {
    components_init(entity, coordinator, position, radius, color,
                    Shape::circle);
    cout << "hello world\n";
}
