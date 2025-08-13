#include "funcs.hpp"
#include <iostream>
#include "utils/macros.hpp"
#include "ecs/registry.hpp"

void thing() {
    ecs::Registry registry;
    registry.register_components<int, char, float>();

    ecs::Entity a = registry.create();
    registry.emplace_back<int>(a, 1);
    registry.emplace_back<char>(a, '9');
    registry.emplace_back<float>(a, 1.5);

    char res = registry.get<char>(a);
    LOG_INFO("{}", res);
}
