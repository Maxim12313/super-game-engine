#include "utils/str_converter.hpp"
#include "ecs/view.hpp"
#include "ecs/registry.hpp"
#include <iostream>
#include <set>
#include <tuple>

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

    {
        std::set<std::tuple<ecs::Entity, char, int, float>> expected = {
            std::make_tuple(a, 'a', 1, 10.5), {d, 'd', 4, 11.5}};

        std::set<std::tuple<ecs::Entity, char, int, float>> actual;
        auto view = registry.view<char, int, float>();
        for (auto [entity, x, y, z] : view.each()) {
            actual.emplace(entity, x, y, z);
        }
        auto t = std::make_tuple<int, char, float>(1, 'a', 3.5);
        std::cout << t << "\n";

        // ASSERT_EQUAL(str_list(expected), (actual));
    }
}
