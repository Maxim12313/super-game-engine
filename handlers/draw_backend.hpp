#pragma once
#include "../include/globals.hpp"
#include <raylib.h>
// dont call raylib, instead call this
// leave interface if decide to implement graphics on own

namespace Draw {
void draw_text(char *buffer, int x, int y, int font_size, Color color) {
    DrawText(buffer, x * SCALE, y * SCALE, font_size * SCALE, color);
}

void draw_circle(int x, int y, float r, Color color) {
    DrawCircle(x * SCALE, y * SCALE, r * SCALE, color);
}

void clear_background(Color color) {
    ClearBackground(color);
}

}; // namespace Draw
