#pragma once
#include "../include/color_map.hpp"
#include "../include/globals.hpp"
#include "../include/shape_map.hpp"
#include "room.hpp"
#include <array>

class RoomManager {
private:
public:
    // let this be created externally
    vector<Room> rooms;

    array<Color_ID, MAX_ENTITIES> color_ids;
    array<bool, MAX_ENTITIES> is_valid;

    array<Vector2, MAX_ENTITIES> positions;
    array<Vector2, MAX_ENTITIES> vectors;

    array<Shape_ID, MAX_ENTITIES> shape_ids;
    array<Rectangle, MAX_ENTITIES> rects;
    array<Rectangle, MAX_ENTITIES> elipses;

    // 0 init some
    RoomManager(vector<Room> &rooms_in) : is_valid({}), elipses({}), rooms(std::move(rooms_in)) {}
};
