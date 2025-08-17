#include <iostream>

#include "core/game.hpp"

int main(int argc, char *argv[]) {

    try {
        Game square_dungeon("Square Dungeon", 1280, 720);
        return square_dungeon.run();
    } catch (const std::exception &e) {
        // Error message printed to console, dont need to reprint exception,
        // just wait for player input.

        std::cin.get();
        return EXIT_FAILURE;
    } catch (...) {
        // Error message printed to console, dont need to reprint exception,
        // just wait for player input.

        std::cin.get();
        return EXIT_FAILURE;
    }
}
