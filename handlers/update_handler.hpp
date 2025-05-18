#pragma once
#include "../objects/game.hpp"
#include "../objects/player.hpp"

class UpdateHandler {
private:
    Game &g;

public:
    UpdateHandler(Game &_g) : g(_g) {
    }

    void run() {
        Player::input(g);
    }
};
