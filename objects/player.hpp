#pragma once
#include "../handlers/draw_backend.hpp"
#include "game.hpp"

class Player {
private:
    static float &get_radius(Game &g) {
        return g.get_radius(g.player);
    }

    static Vector2 &get_position(Game &g) {
        return g.get_position(g.player);
    }

    static Color &get_color(Game &g) {
        return g.get_color(g.player);
    }

    static float &get_speed(Game &g) {
        return g.get_speed(g.player);
    }

public:
    static void create(Game &g, float radius, float speed, Vector2 pos, Color color) {
        Entity player = g.entity_manager.get_entity();
        g.radii.set(player, radius);
        g.speeds.set(player, speed);
        g.positions.set(player, pos);
        g.directions.set(player, Vector2{0, 0});
        g.colors.set(player, color);
        g.player = player;
    }

    static void draw(Game &g) {
        Vector2 pos = get_position(g);
        float radius = get_radius(g);
        Color color = get_color(g);
        Draw::draw_circle(pos.x, pos.y, radius, color);
    }

    static void input(Game &g) {
        Vector2 dir(0, 0);
        if (IsKeyDown(KEY_A))
            dir.x--;
        if (IsKeyDown(KEY_D))
            dir.x++;
        if (IsKeyDown(KEY_W))
            dir.y--;
        if (IsKeyDown(KEY_S))
            dir.y++;

        if (Vector2Length(dir) == 0)
            return;

        Vector2 &pos = get_position(g);
        float speed = get_speed(g);
        dir = Vector2Scale(Vector2Normalize(dir), speed);
        pos = Vector2Add(dir, pos);
    }
};
