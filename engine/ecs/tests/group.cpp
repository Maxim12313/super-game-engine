#include "ecs/registry.hpp"

int main() {
    ecs::Registry reg;
    reg.register_components<int, float, char>();

    ecs::Entity a = 0;
    reg.emplace_back<char>(a, 'a');
    reg.emplace_back<int>(a, 1);
    reg.emplace_back<float>(a, 10.5);

    auto group = reg.group<int, float>();
}
