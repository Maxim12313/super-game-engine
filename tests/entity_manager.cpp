#include "../include/ecs/entity_manager.hpp"
#include "../include/utils/test_utils.hpp"
#include <unordered_set>

constexpr int n = 100;

void test_destroy_create() {
    EntityManager manager;
    unordered_set<Entity> seen;
    for (int i = 0; i < n; i++) {
        if (!seen.empty() && rand() > RAND_MAX / 2) {
            Entity lose = *begin(seen);
            manager.destroy_entity(lose);
            seen.erase(lose);
        } else {
            Entity adding = manager.create_entity();
            ASSERT(!seen.count(adding));
            seen.insert(adding);
        }
    }
}

void test_component_entity_tracking() {
    EntityManager manager;
}

int main() {
    test_destroy_create();
    test_component_entity_tracking();
}
