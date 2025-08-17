#include "../src/sparse_set.hpp"
#include "utils/macros.hpp"
using namespace std;

constexpr int n = 30; // MUST BE n >= 10

void test2() {
    ecs::internal::SparseSet<int> array;
    for (int i = 0; i < n; i++)
        array.push_back(i, i);

    array.remove(0);
    array.remove(1);

    array.push_back(n, n);
    array.push_back(n + 1, n + 1);
    vector<bool> seen(n, false);

    for (int val : array)
        seen[val - 2] = true;

    for (bool has : seen)
        ASSERT(has);
}

void test1() {
    ecs::internal::SparseSet<int> array;
    for (int i = 0; i < n; i++)
        array.push_back(i, i);

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
