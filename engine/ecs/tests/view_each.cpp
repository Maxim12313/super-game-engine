#include "ecs/view.hpp"
#include "ecs/registry.hpp"

int main() {
    ecs::Registry registry;
    registry.register_components<int, float, char>();

    ecs::Entity a = 0;
    registry.emplace_back<char>(a, 'a');
    registry.emplace_back<int>(a, 1);
    registry.emplace_back<float>(a, 10.5);

    ecs::Entity b = 1;
    registry.emplace_back<char>(b, 'b');

    ecs::Entity c = 2;
    registry.emplace_back<char>(c, 'c');
    registry.emplace_back<int>(c, 3);

    ecs::Entity d = 3;
    registry.emplace_back<char>(d, 'd');
    registry.emplace_back<int>(d, 4);
    registry.emplace_back<float>(d, 11.5);

    auto view = registry.view<char, int, float>();
    for (auto [entity, x, y, z] : view.each()) {
        LOG_INFO("{} {} {} {}", entity, x, y, z);
    }
}
