#pragma once
#include "common.hpp"

inline void draw_handler(Entity entity, Coordinator &coordinator) {
    Shape &shape = coordinator.get_component<Shape>(entity);
    switch (shape.shape_id) {
        case Shape::rectangle:
            draw_rectangle(entity, coordinator);
        case Shape::circle:
            draw_circle(entity, coordinator);
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
     */
    void run(Coordinator &coordinator) {
        Graphics::begin_drawing();
        for (Entity entity : subscribed_entities) {
            draw_handler(entity, coordinator);
        }
        Graphics::end_drawing();
    }

    Signature get_signature() override {
        Signature signature = 0;
        signature = signature_utils::set_bit<Shape>(signature);
        signature = signature_utils::set_bit<Position>(signature);
        signature = signature_utils::set_bit<Color>(signature);
        return signature;
    }
};
