#pragma once
#include "../objects/game.hpp"
#include <raymath.h>

class DrawHandler {
private:
    Game &g;
    char buffer[1024];

    void draw() {

        ClearBackground(RAYWHITE);

        for (int i = 0; i < g.positions.size(); i++) {
            Vector2 &pos = g.positions[i];
            DrawCircle(pos.x, pos.y, g.radii[i] * SCALE, g.colors[i]);
        }

        int fps = g.dt == 0 ? 0 : 1 / g.dt;
        snprintf(buffer, sizeof(buffer), "FPS: %d", fps);
        DrawText(buffer, (WIDTH - 100) * SCALE, 20 * SCALE, 20 * SCALE, GREEN);
    }

public:
    DrawHandler(Game &g_in) : g(g_in) {}

    void run() {
        //
        draw();
    }
};
