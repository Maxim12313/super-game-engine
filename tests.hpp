// #pragma once
// #include "handlers/draw_handler.hpp"
// #include "objects/game.hpp"
// #include <iostream>
// #include <raylib.h>
//
// namespace TEST {
// void clocks() {
//     InitWindow(WIDTH * SCALE, HEIGHT * SCALE, "wassup");
//
//     SetTargetFPS(FPS);
//     Vector2 pos2(100, 100);
//     while (!WindowShouldClose()) {
//         float dt = GetFrameTime();
//         if (IsKeyDown(KEY_A))
//             pos2.x -= 10;
//         if (IsKeyDown(KEY_D))
//             pos2.x += 10;
//         if (IsKeyDown(KEY_S))
//             pos2.y += 10;
//         if (IsKeyDown(KEY_W))
//             pos2.y -= 10;
//
//         BeginDrawing();
//         ClearBackground(RAYWHITE);
//         DrawCircle(pos2.x, pos2.y, 10, RED);
//         EndDrawing();
//     }
//
//     CloseWindow();
// }
//
// void lines() {
//     InitWindow(WIDTH * SCALE, HEIGHT * SCALE, "wassup");
//
//     SetTargetFPS(FPS);
//     Vector2 pos1(100, 100);
//     Vector2 pos2(0, 0);
//     while (!WindowShouldClose()) {
//         float dt = GetFrameTime();
//         if (IsKeyDown(KEY_A))
//             pos2.x--;
//         if (IsKeyDown(KEY_D))
//             pos2.x++;
//         if (IsKeyDown(KEY_S))
//             pos2.y++;
//         if (IsKeyDown(KEY_W))
//             pos2.y--;
//
//         BeginDrawing();
//         ClearBackground(RAYWHITE);
//         DrawLineV(pos1, pos2, ORANGE);
//         EndDrawing();
//     }
//
//     CloseWindow();
// }
//
// void rotation() {
//     InitWindow(WIDTH * SCALE, HEIGHT * SCALE, "wassup");
//
//     SetTargetFPS(FPS);
//     Rectangle rect(100, 100, 100, 100);
//     Vector2 origin(rect.width / 2, rect.height / 2);
//     float rotation = 0;
//     while (!WindowShouldClose()) {
//         float dt = GetFrameTime();
//         if (IsKeyDown(KEY_A))
//             rotation--;
//         if (IsKeyDown(KEY_D))
//             rotation++;
//
//         BeginDrawing();
//         ClearBackground(RAYWHITE);
//         DrawRectanglePro(rect, origin, rotation, ORANGE);
//         EndDrawing();
//     }
//
//     CloseWindow();
// }
// }; // namespace TEST
