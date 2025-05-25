#include <iostream>
#include <raylib.h>

int main() {
    std::cout << "hello world\n";
}

// void run() {
//     InitWindow(WIDTH * SCALE, HEIGHT * SCALE, "dummy");
//     printf("%f\n", SCALE);
//
//     Game g;
//     Player::create(g, 100, 10, Vector2{WIDTH / 2, HEIGHT / 2}, RED);
//     Enemy::create(g, 100, 10, Vector2{WIDTH / 10, HEIGHT / 2}, GREEN);
//
//     DrawHandler drawer(g);
//     UpdateHandler updater(g);
//
//     SetTargetFPS(FPS);
//     while (!WindowShouldClose()) {
//         g.dt = GetFrameTime();
//         drawer.run();
//         updater.run();
//     }
//
//     CloseWindow();
// }
//
// int main() {
//     run();
// }
