#include "../ecs/component_manager.hpp"
#include "../ecs/entity_manager.hpp"
#include "../include/test_utils.hpp"

// duplicate of packed_array_manager
// is just wrapper so should work the same

constexpr int m = 200;

struct Type1 {
    int val;
};

struct Type2 {
    int val;
};

void test1() {
    ComponentManager arrays;
    EntityManager entities;

    arrays.register_component<Type1>();
    arrays.register_component<Type2>();

    Entity first = entities.get_entity();
    arrays.set_component(first, Type1{1});

    Entity second = entities.get_entity();
    arrays.set_component(second, Type1{2});

    auto arr = arrays.get_components<Type1>();
    for (auto val : *arr) {
        ASSERT((val.val == 1) || (val.val == 2));
    }

    arrays.erase_component<Type1>(first);
    for (auto val : *arr) {
        ASSERT(val.val == 2);
    }

    arrays.set_component(first, Type1{30});

    arrays.set_component(first, Type2{60});
    arrays.set_component(second, Type2{120});

    for (auto val : *arr) {
        ASSERT((val.val == 30) || (val.val == 2));
    }

    for (auto val : *arrays.get_components<Type2>()) {
        ASSERT((val.val == 60) || (val.val == 120));
    }
}

int main() {
    test1();
}
