#include "../src/core/component_manager.hpp"
#include "../src/core/entity_manager.hpp"
#include <utils/macros.hpp>

using namespace std;
#include <iostream>

void test1();

int main() {
    test1();
}

struct Type1 {
    int val;
};

struct Type2 {
    int val;
};

void test1() {
    ecs::internal::ComponentManager arrays;
    ecs::internal::EntityManager entities;

    arrays.register_type<Type1>();
    arrays.register_type<Type2>();

    ecs::Entity first = 0;
    arrays.assign(first, Type1{1});

    ecs::Entity second = 1;
    arrays.assign(second, Type2{2});

    auto arr = arrays.get_array<Type1>();
    for (auto val : *arr) {
        ASSERT((val.val == 1) || (val.val == 2));
    }

    arrays.erase_data<Type1>(first);
    for (auto val : *arr) {
        ASSERT(val.val == 2);
    }

    arrays.assign(first, Type1{30});

    arrays.assign(first, Type2{60});
    arrays.assign(second, Type2{120});

    for (auto val : *arr) {
        ASSERT((val.val == 30) || (val.val == 2));
    }

    for (auto val : *arrays.get_array<Type2>()) {
        ASSERT((val.val == 60) || (val.val == 120));
    }
}
