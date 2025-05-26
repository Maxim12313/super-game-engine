#include "../ecs/packed_array_manager.hpp"
#include "../include/test_utils.hpp"

constexpr int n = 300;
constexpr int m = 200;

struct Type1 {
    int val;
};

struct Type2 {
    int val;
};

void test1() {
    PackedArrayManager<n> arrays;
    EntityManager entities;

    arrays.register_type<Type1>();
    arrays.register_type<Type2>();

    Entity first = entities.get_entity();
    arrays.set(first, Type1{1});

    Entity second = entities.get_entity();
    arrays.set(second, Type1{2});

    auto arr = arrays.get_array<Type1>();
    for (auto val : *arr) {
        ASSERT((val.val == 1) || (val.val == 2));
    }

    arrays.erase<Type1>(first);
    for (auto val : *arr) {
        ASSERT(val.val == 2);
    }

    arrays.set(first, Type1{30});

    arrays.set(first, Type2{60});
    arrays.set(second, Type2{120});

    for (auto val : *arr) {
        ASSERT((val.val == 30) || (val.val == 2));
    }

    for (auto val : *arrays.get_array<Type2>()) {
        ASSERT((val.val == 60) || (val.val == 120));
    }
}

int main() {
    test1();
}
