#pragma once
#include <raylib.h>

struct Position {
    Vector2 pos;
};

struct Radius {
    float radius;
};

struct Shape {
    enum ShapeID {
        rectangle = 0,
        circle,
    };
    ShapeID shape_id;
};

struct Velocity {
    Vector2 velocity;
};

struct WidthHeight {
    float width;
    float height;
};
