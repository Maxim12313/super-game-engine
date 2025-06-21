#pragma once
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
    float width;
    float height;
};

struct PlayerMovable {};
