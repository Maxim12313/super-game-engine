#pragma once
#include "../objects/game.hpp"

class CollisionHandler {
private:
    Game &g;

public:
    CollisionHandler(Game &_g) : g(_g) {
    }

    void run() {
    }
};
