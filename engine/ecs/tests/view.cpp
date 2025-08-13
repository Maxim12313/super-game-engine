#include "../src/core/view.hpp"
#include "utils/macros.hpp"
using namespace std;

void test_filter_intersection() {
    ecs::internal::SparseSet<int> arr;
    for (int i = 0; i < 20; i += 2) {
        arr.push_back(i, -i);
    }
    vector<ecs::Entity> entities;
    for (int i = 0; i < 20; i += 2) {
        entities.push_back(i + 1);
    }

    // none are the same
    filter_intersection(entities, &arr);
    ASSERT(entities.empty());

    entities.clear();
    for (int i = 0; i < 5; i++) {
        entities.push_back(i);
    }

    // 0, 2, 4
    filter_intersection(entities, &arr);
    ASSERT(entities.size() == 3);

    entities.clear();
    entities.push_back(4);
    entities.push_back(2);
    entities.push_back(8);

    // 4, 2, 8
    filter_intersection(entities, &arr);
    ASSERT(entities.size() == 3);
}

int main() {
    test_filter_intersection();
}
