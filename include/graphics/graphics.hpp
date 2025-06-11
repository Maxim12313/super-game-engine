/**
 * @file
 * @brief Interface for graphic stubs if I decide to go back and
 * implement this myself. For now leave it to raylib
 */

#pragma once
#include "../config.hpp"
#include <raylib.h>

class Graphics {
public:
    static void init(const char *title) {
        InitWindow(WIDTH * SCALE, WIDTH * SCALE, title);
        SetTargetFPS(FPS);
    }

    static bool should_close() {
        return WindowShouldClose();
    }

    static void begin_drawing() {
        BeginDrawing();
    }
    static void end_drawing() {
        EndDrawing();
    }

    static void close_window() {
        CloseWindow();
    }

    static void clear_background(Color color) {
        ClearBackground(color);
    }

    static void draw_text(const char *text, int x, int y, int fontsize,
                          Color fontcolor) {
        DrawText(text, x * SCALE, y * SCALE, fontsize * SCALE, fontcolor);
    }

    static void draw_circle(int centerX, int centerY, float radius,
                            Color color) {
        DrawCircle(centerX, centerY, radius, color);
    }

    static void draw_rectangle(int posX, int posY, int width, int height,
                               Color color) {
        DrawRectangle(posX, posY, width, height, color);
    }
};
