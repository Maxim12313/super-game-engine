#include "../include/ecs/view.hpp"
#include "../include/utils/test_utils.hpp"

void test_filter_intersection() {
    SparseSet<int> arr;
    for (int i = 0; i < 20; i += 2) {
        arr[i] = -i;
    }
    vector<Entity> entities;
    for (int i = 0; i < 20; i += 2) {
        entities.push_back(i + 1);
    }

    // none are the same
    internal::filter_intersection(entities, &arr);
    ASSERT(entities.empty());

    entities.clear();
    for (int i = 0; i < 5; i++) {
        entities.push_back(i);
    }

    // 0, 2, 4
    internal::filter_intersection(entities, &arr);
    ASSERT(entities.size() == 3);

    entities.clear();
    entities.push_back(4);
    entities.push_back(2);
    entities.push_back(8);

    // 4, 2, 8
    internal::filter_intersection(entities, &arr);
    ASSERT(entities.size() == 3);
}

int main() {
    test_filter_intersection();
}
