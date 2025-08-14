#include "ecs/common.hpp"
#include <ecs/registry.hpp>
#include "utils/timing.hpp"
#include <chrono>
#include <iostream>

using namespace std::chrono;

int main() {
    ecs::Registry registry;
    registry.register_components<int, char, double>();

    get_micro_since();
    int n = int(1e4);
    int m = 6;

    // for (int j = 0; j < m; j++) {
    //     for (int i = 0; i < n; i++) {
    //         int k = j + i;
    //     }
    // }

    for (int entity = 0; entity < n; entity++) {
        registry.emplace_back<int>(entity, entity);
    }
    for (int entity = 0; entity < n; entity += 3) {
        registry.emplace_back<double>(entity, entity + 0.5);
    }
    for (int entity = 0; entity < n; entity += 5) {
        registry.emplace_back<char>(entity, entity + 0.5);
    }

    for (auto entity : registry.view<int, char, double>()) {
        int a = registry.get<int>(entity);
        char b = registry.get<char>(entity);
        double c = registry.get<double>(entity);
    }

    for (auto entity : registry.view<int, double>()) {
        int a = registry.get<int>(entity);
        double c = registry.get<double>(entity);
    }

    for (auto entity : registry.view<char, double>()) {
        char b = registry.get<char>(entity);
        double c = registry.get<double>(entity);
    }

    std::cout << get_ms_since() << "\n";
}
