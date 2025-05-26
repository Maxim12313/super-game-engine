#include "../ecs/packed_array.hpp"
#include "../include/test_utils.hpp"

constexpr int n = 30; // MUST BE n >= 10

void test2() {
    PackedArray<int, n> array;
    for (int i = 0; i < n; i++)
        array.set(i, i);

    array.erase(0);
    array.erase(1);
    array.set(n, n);
    array.set(n + 1, n + 1);
    vector<bool> seen(n, false);

    for (int val : array)
        seen[val - 2] = true;

    for (bool has : seen)
        ASSERT(has);
}

void test1() {
    PackedArray<int, n> array;
    for (int i = 0; i < n; i++)
        array.set(i, i);

    for (int i = 0; i < n; i++)
        ASSERT_EQUAL(array.get(i), i);

    int count = 0;
    for (int val : array)
        ASSERT_EQUAL(val, count++);

    for (int i = 0; i < n; i++)
        array.get(i) = i * 2;

    for (int i = 0; i < n; i++)
        ASSERT_EQUAL(array.get(i), 2 * i);
}

int main() {
    test1();
    test2();
}
