#include "handlers/draw_handler.hpp"
#include "handlers/input_handler.hpp"
#include "objects/game.hpp"
#include <iostream>
#include <raylib.h>

int main() {
    InitWindow(WIDTH * SCALE, HEIGHT * SCALE, "dummy");
    printf("%f\n", SCALE);

    Game g;

    InputHandler inputer(g);
    DrawHandler drawer(g);

    SetTargetFPS(FPS);
    while (!WindowShouldClose()) {
        g.dt = GetFrameTime();
        inputer.run();

        BeginDrawing();
        drawer.run();
        EndDrawing();
    }

    CloseWindow();
}
