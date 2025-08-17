#pragma once

#include "ecs/registry.hpp"
#include "graphics/drawer.hpp"
#include "graphics/window.hpp"
#include "systems/index.hpp"

// #include "../systems/AISystem.hpp"
// #include "../systems/CollisionSystem.hpp"
// #include "../systems/MoveSystem.hpp"
// #include "../systems/RenderSystem.hpp"

// #include "Window.hpp"

///
/// This class will manage our game data and game loop.
/// Along with the application instance.
///
class Game final {
public:
    ///
    /// Main constructor.
    ///
    /// \param title Title of the window.
    /// \param w Width of the window.
    /// \param h Height of the window.
    /// \param fps Target fps for game.
    ///
    Game(const char *title, const int w, const int h);

    ///
    /// Run the game loop.
    ///
    /// \return Returns game exit code.
    ///
    [[maybe_unused]] const int run();

private:
    ///
    /// Deleted default constructor.
    ///
    Game() = delete;

    ///
    /// Recieve and process game events.
    ///
    void events();

    ///
    /// Process game data.
    ///
    /// \param time The DeltaTime or similar from fixed-timestep loop.
    ///
    void update(const double time);

    ///
    /// Render everything to the window.
    ///
    void render();

    ///
    /// Our main window
    ///
    graphics::Window m_window;

    ///
    /// Processes events
    ///
    graphics::Event m_event;

    ///
    /// OpenGL abstraction for drawing on screen
    ///
    graphics::Drawer m_drawer;

    ///
    /// The default entt registry to hold and manage our entities.
    ///
    ecs::Registry m_registry;

    ///
    /// The AI system.
    ///
    // AISystem m_ai_system;

    ///
    /// The collision system.
    ///
    // CollisionSystem m_collision_system;

    ///
    /// The movement system.
    ///
    // MoveSystem m_move_system;

    ///
    /// The Render system.
    ///
    RenderSystem m_renderSystem;
};
