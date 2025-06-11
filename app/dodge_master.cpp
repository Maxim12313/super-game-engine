#include "../include/components/components.hpp"
#include "../include/ecs/coordinator.hpp"
#include "../include/graphics/graphics.hpp"
#include "../include/systems/draw_system.hpp"

Coordinator init_coordinator();

int main() {
    Graphics::init("dodge master");

    Coordinator coordinator = init_coordinator();

    while (!Graphics::should_close()) {

        Graphics::begin_drawing();
        Graphics::clear_background(RAYWHITE);

        Graphics::end_drawing();
    }
    Graphics::close_window();
}

Coordinator init_coordinator() {
    Coordinator coordinator;

    // components
    coordinator.register_component<Shape>();
    coordinator.register_component<Position>();
    coordinator.register_component<Color>();
    coordinator.register_component<WidthHeight>();
    coordinator.register_component<Radius>();

    // systems
    coordinator.register_system(DrawSystem{});

    return coordinator;
}
