#pragma once
#include "common.hpp"

inline void draw_handler(Entity entity, Coordinator &coordinator) {
    Shape &shape = coordinator.get_component<Shape>(entity);
    switch (shape) {
        case Shape::rectangle:
            rectangle_draw(entity, coordinator);
        case Shape::circle:
            circle_draw(entity, coordinator);
    }
}

// NOTE: may make sense to separate this by shape later on
/**
 * @class DrawSystem
 * @brief Takes Shape, Position, Color
 *
 */
class DrawSystem : public System {
public:
    /**
     * @brief Draw everything
     * NOTE: Does not call begin_drawing or end_drawing
     */
    void run(Coordinator &coordinator) {
        for (Entity entity : subscribed_entities) {
            draw_handler(entity, coordinator);
        }
    }

    Signature get_signature() override {
        Signature signature = 0;
        signature = signature_utils::set_bit<Shape>(signature);
        signature = signature_utils::set_bit<Position>(signature);
        signature = signature_utils::set_bit<Color>(signature);
        return signature;
    }
};
