#include "../include/components/components.hpp"
#include "../include/ecs/coordinator.hpp"
#include "../include/graphics/graphics.hpp"
#include "../include/systems/draw_system.hpp"
#include "config.hpp"
#include "game_objects/player.hpp"
#include <raylib.h>
#include <spdlog/spdlog.h>

// #define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_DEBUG

Coordinator coordinator_init();
void logger_init();

int main() {
    logger_init();

    Graphics::init("dodge master");

    Coordinator coordinator = coordinator_init();

    Entity player = coordinator.create_entity();
    player_init(player, coordinator, Position{100, 100}, Radius{100}, ORANGE,
                MoveSpeed{10});

    while (!Graphics::should_close()) {
        float delta_time = 1.0 / GetFPS();

        Graphics::begin_drawing();
        Graphics::clear_background(RAYWHITE);
        coordinator.run_system<DrawSystem>();
        Graphics::end_drawing();
    }
    Graphics::close_window();
}

void logger_init() {
    spdlog::set_level(spdlog::level::debug);
    spdlog::set_pattern("[%^%l%$] [%s %!:%#]  %v");
}

Coordinator coordinator_init() {
    Coordinator coordinator;

    // components
    coordinator.register_component<Shape, Position, Color, WidthHeight, Radius,
                                   MoveSpeed>();

    // systems
    coordinator.register_system(DrawSystem{});

    return coordinator;
}
