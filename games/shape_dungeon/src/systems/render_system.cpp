#include "../components/position.hpp"
#include "../components/sprite.hpp"

#include "render_system.hpp"
#include "ecs/registry.hpp"
#include "graphics/drawer.hpp"

void RenderSystem::render(graphics::Drawer &drawer, ecs::Registry &registry) {
    // First we retrieve a view of the entitys we want to process, specifying
    // which components. Then we iterate over each one and utilize the
    // components.

    auto view = registry.view<Sprite, Position>();
    for (auto [entity, spr, pos] : view.each()) {
        if (spr.m_radius != 0) {
            // noob has no function to draw circle still
            // drawer.queue_circle(pos.m_x, pos.m_y, spr.radius, spr.m_color);
        } else {
            drawer.queue_rectangle(pos.m_x, pos.m_y, spr.m_width, spr.m_height,
                                   spr.m_color);
        }
    }
}
