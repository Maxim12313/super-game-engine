#pragma once
#include "../handlers/draw_backend.hpp"
#include "../objects/enemy.hpp"
#include "../objects/game.hpp"
#include "../objects/player.hpp"
#include <raymath.h>

class DrawHandler {
private:
    Game &g;
    char buffer[1024];

public:
    DrawHandler(Game &_g) : g(_g) {
    }

    void run() {
        int fps = g.dt == 0 ? 0 : 1 / g.dt;
        snprintf(buffer, sizeof(buffer), "FPS: %d", fps);

        BeginDrawing();

        Draw::clear_background(RAYWHITE);
        Player::draw(g);
        Enemy::draw(g);
        Draw::draw_text(buffer, WIDTH - 100, 20, 20, GREEN);

        EndDrawing();
    }
};
