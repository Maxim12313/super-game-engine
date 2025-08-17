#pragma once

#include "ecs/registry.hpp"
#include "graphics/drawer.hpp"

///
/// This class will take data from the appropriate components
/// and render them to the screen.
///
class RenderSystem final {
public:
    ///
    /// Default constructor.
    ///
    RenderSystem() = default;

    ///
    /// Default destructor.
    ///
    ~RenderSystem() = default;

    ///
    /// Renders all entities.
    ///
    /// \param window The Window to render to.
    /// \param registry The registry to retrieve entities from.
    ///
    void render(graphics::Drawer &drawer, ecs::Registry &registry);
};
