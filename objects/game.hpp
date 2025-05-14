#pragma once
#include "../include/globals.hpp"
#include <raylib.h>

struct Game {
    // let player be at pos 0 always
    float dt;
    vector<bool> is_invalid;
    vector<Vector2> positions;
    vector<float> speeds;
    vector<float> radii;
    vector<Color> colors;

    Vector2 &player_pos() { return positions[0]; }
    float &player_speed() { return speeds[0]; }

    Game() {
        is_invalid.push_back(true);
        radii.push_back(20);
        speeds.push_back(10);
        colors.push_back(RED);
        positions.emplace_back(WIDTH / 2, HEIGHT / 2);

        is_invalid.resize(MAX_ENTITIES + 1);
        positions.resize(MAX_ENTITIES + 1);
        speeds.resize(MAX_ENTITIES + 1);
        radii.resize(MAX_ENTITIES + 1);
        colors.resize(MAX_ENTITIES + 1);
    }
};
