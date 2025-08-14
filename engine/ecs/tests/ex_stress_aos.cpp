#include "ecs/common.hpp"
#include "utils/timing.hpp"
#include <ecs/registry.hpp>
#include <chrono>
#include <iostream>

using namespace std::chrono;

int main() {
    ecs::Registry registry;
    registry.register_components<int, char, double>();
    get_micro_since();

    std::cout << get_micro_since() << "\n";
}
