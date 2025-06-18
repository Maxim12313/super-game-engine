#include "../include/components/components.hpp"
#include "../include/ecs/coordinator.hpp"
#include "../include/graphics/graphics.hpp"
#include "../include/systems/draw_system.hpp"
#include "config.hpp"
#include <raylib.h>

Coordinator init_coordinator();

int main() {
    Graphics::init("dodge master");

    Coordinator coordinator = init_coordinator();

    while (!Graphics::should_close()) {
        float delta_time = 1.0 / GetFPS();

        Graphics::begin_drawing();
        Graphics::clear_background(RAYWHITE);
        coordinator.run_system<DrawSystem>();

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
