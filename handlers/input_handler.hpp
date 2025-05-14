#pragma once
#include "../objects/game.hpp"
#include <raymath.h>

class InputHandler {
private:
    Game &g;

    void move_player() {
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
        Vector2 &pos = g.player_pos();
        dir = Vector2Scale(Vector2Normalize(dir), g.player_speed());
        pos = Vector2Add(dir, pos);
    }

public:
    InputHandler(Game &g_in) : g(g_in) {}

    void run() { move_player(); }
};
