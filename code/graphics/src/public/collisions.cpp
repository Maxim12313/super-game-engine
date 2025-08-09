#include "graphics/collisions.hpp"
#include <iostream>
#include <utility>

bool rect_colliding(int x1, int y1, int w1, int h1, int x2, int y2, int w2,
                    int h2) {

    bool aligned_x = (x1 < x2 && x1 + w1 >= x2) || (x2 < x1 && x2 + w2 >= x1);
    bool aligned_y = (y1 < y2 && y1 + h1 >= y2) || (y2 < y1 && y2 + h2 >= y1);
    return aligned_x && aligned_y;
}
