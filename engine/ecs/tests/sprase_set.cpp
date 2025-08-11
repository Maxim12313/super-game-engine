#include "../src/core/sparse_set.hpp"
#include "utils/macros.hpp"
using namespace std;

constexpr int n = 30; // MUST BE n >= 10

void test2() {
    ecs::internal::SparseSet<int> array;
    for (int i = 0; i < n; i++)
        array[i] = i;

    array.erase(0);
    array.erase(1);
    array[n] = n;
    array[n + 1] = n + 1;
    vector<bool> seen(n, false);

    for (int val : array)
        seen[val - 2] = true;

    for (bool has : seen)
        ASSERT(has);
}

void test1() {
    ecs::internal::SparseSet<int> array;
    for (int i = 0; i < n; i++)
        array[i] = i;

    for (int i = 0; i < n; i++)
        ASSERT_EQUAL(array[i], i);

    int count = 0;
    for (int val : array)
        ASSERT_EQUAL(val, count++);

    for (int i = 0; i < n; i++)
        array[i] = i * 2;

    for (int i = 0; i < n; i++)
        ASSERT_EQUAL(array[i], 2 * i);
}

int main() {
    test1();
    test2();
}
