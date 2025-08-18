#include "ecs/registry.hpp"
#include "utils/macros.hpp"
#include "utils/str_converter.hpp"
#include <set>

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

    auto group = registry.group<char, int>();
    std::set<ecs::Entity> expected = {a, c, d};
    std::set<ecs::Entity> have;
    for (auto [entity, char_val, int_val] : group.each()) {
        LOG_INFO("{} {} {}", entity, char_val, int_val);
        have.insert(entity);
    }
    ASSERT_EQUAL(str_list(expected), str_list(have));
}
