#pragma once
#include "ecs/common.hpp"
#include <raylib.h>

struct Position {
    Vector2 pos;
};

struct Radius {
    float radius;
};

enum class Shape {
    rectangle = 0,
    circle,
};

struct Velocity {
    Vector2 velocity;
};

struct MoveSpeed {
    float speed;
};

struct WidthHeight {
    Vector2 wh;
};

struct PlayerMovable {};

struct Collided {
    Entity other;
};
