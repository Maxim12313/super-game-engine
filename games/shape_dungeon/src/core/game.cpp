#include "../components/index.hpp"
#include "components/health_point.hpp"
#include "components/weapon_cooldown.hpp"
#include "graphics/camera2d.hpp"
#include "graphics/color.hpp"
#include "graphics/window.hpp"
#include <optional>
#include "game.hpp"

Game::Game(const char *title, const int w, const int h) : m_drawer(w, h) {

    /// Demo:
    ///
    ///      display player, weapon, bullet, and immoblie mob
    ///      system: player movement, basic combat
    ///

    m_registry.register_components<Ammo, Damage, Faction, HealthPoint,
                                   IsShooting, Position, Sprite, Velocity2D,
                                   WeaponCooldown, WeaponHolder>();

    const auto player = m_registry.create();
    const auto weapon = m_registry.create();
    const auto mob = m_registry.create();

    ///
    /// Assign component data to entitys
    ///

    m_registry.emplace_back<Sprite>(player, 24, graphics::CYAN);
    m_registry.emplace_back<Velocity2D>(player, glm::vec2(0, 1), 16);
    m_registry.emplace_back<Position>(player, 0, 0);
    m_registry.emplace_back<Faction>(player, Faction::Human);
    m_registry.emplace_back<WeaponHolder>(player, weapon, std::nullopt);
    m_registry.emplace_back<IsShooting>(player, false);
    m_registry.emplace_back<Ammo>(player, 200);
    m_registry.emplace_back<HealthPoint>(player, 10);

    m_registry.emplace_back<Sprite>(weapon, 16, 32, graphics::GRAY);
    m_registry.emplace_back<Position>(weapon, 20, 0);
    m_registry.emplace_back<WeaponCooldown>(weapon, 0.4);

    m_registry.emplace_back<Sprite>(mob, 48, 48, graphics::RED);
    m_registry.emplace_back<Position>(mob, 0, 128);
    m_registry.emplace_back<Faction>(mob, Faction::Mob);
    m_registry.emplace_back<HealthPoint>(mob, 5);

    // // Assign events to systems.
    // m_dispatcher.sink<KeyDown>().connect<&MoveSystem::on_key_down>(
    //     m_move_system);
    // m_dispatcher.sink<KeyUp>().connect<&MoveSystem::on_key_up>(m_move_system);
    //
    // // Assign events to window.
    // m_dispatcher.sink<KeyDown>().connect<&Window::on_key_down>(m_window);

    // Set up collideables
    // m_collideables.ai = ai_paddle;
    // m_collideables.player = player_paddle;
    // m_collideables.ball = ball;
    // m_collideables.registery = &m_registry;
}

const int Game::run() {
    graphics::Camera2D camera2D = graphics::Camera2D();
    m_drawer.begin_camera(camera2D);
    m_drawer.set_background_color(graphics::GRAY);
    while (!m_window.should_close()) {
        m_window.begin_update();
        m_drawer.clear();

        // events();
        // render();

        auto view = m_registry.view<Sprite, Position>();
        for (auto [entity, spr, pos] : view.each()) {
            if (spr.m_radius != 0) {
                // noob has no function to draw circle still
                // drawer.queue_circle(pos.m_x, pos.m_y, spr.radius,
                // spr.m_color);
            } else {
                m_drawer.queue_rectangle(pos.m_x, pos.m_y, spr.m_width,
                                         spr.m_height, spr.m_color);
            }
        }
        m_drawer.execute_draw();

        m_window.end_update();
    }

    return EXIT_SUCCESS;
}

void Game::events() {
    // Process all user and system events.
    // while (SDL_PollEvent(&m_window.m_event) != 0) {
    //     switch (m_window.m_event.type) {
    //         case SDL_QUIT:
    //             m_window.close();
    //             break;
    //
    //         case SDL_KEYDOWN:
    //             m_dispatcher.trigger<KeyDown>(m_window.m_event.key.keysym.sym);
    //             break;
    //
    //         case SDL_KEYUP:
    //             m_dispatcher.trigger<KeyUp>(m_window.m_event.key.keysym.sym);
    //             break;
    //     }
    // }
}

void Game::update(const double time) {
    // m_move_system.update(time, m_registry);
    // m_ai_system.update(time, m_registry);
    // m_collision_system.update(time, m_collideables);
}

void Game::render() {
    m_renderSystem.render(m_drawer, m_registry);

    // Draw everything.
    m_drawer.execute_draw();
}
