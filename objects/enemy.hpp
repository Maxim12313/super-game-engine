#pragma once
#include "../handlers/draw_backend.hpp"
#include "game.hpp"

// static and behavior mostly
class Enemy {
public:
    static void create(Game &g, float radius, float speed, Vector2 pos, Color color) {
        Entity id = g.entity_manager.get_entity();
        g.enemy_ids.set(id, id);
        g.radii.set(id, radius);
        g.speeds.set(id, speed);
        g.positions.set(id, pos);
        g.directions.set(id, Vector2{0, 0});
        g.colors.set(id, color);
    }
    static void destroy(Game &g, Entity id) {
        g.enemy_ids.erase(id);
        g.radii.erase(id);
        g.speeds.erase(id);
        g.positions.erase(id);
        g.directions.erase(id);
    }

    static void draw(Game &g) {
        auto array = g.enemy_ids;
        auto data = array.get_components();
        for (int i = 0; i < array.size(); i++) {
            Entity id = data[i];
            float radius = g.radii.get(id);
            Color color = g.colors.get(id);
            Vector2 pos = g.positions.get(id);
            Draw::draw_circle(pos.x, pos.y, radius, color);
        }
    }
};
