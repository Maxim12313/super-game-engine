#pragma once
#include "common.hpp"

inline void draw_handler(Entity entity, Coordinator &coordinator) {
    auto shape = coordinator.get<Shape>(entity);
    switch (shape) {
        case Shape::rectangle:
            rectangle_draw(entity, coordinator);
            break;
        case Shape::circle:
            circle_draw(entity, coordinator);
            break;
    }
}

// class DrawSystem : public System {
// public:
//     void run(Coordinator &coordinator) override {
//         for (Entity entity : entities) {
//             draw_handler(entity, coordinator);
//         }
//     }
//
//     Signature get_signature() override {
//         return internal::set_signature<Shape, Position, Color>();
//     }
// };
