#include "../src/core/entity_manager.hpp"
#include "utils/macros.hpp"
#include "unordered_set"

using namespace std;

constexpr int n = 100;

void test_destroy_create() {
    ecs::internal::EntityManager manager;
    unordered_set<ecs::Entity> seen;
    for (int i = 0; i < n; i++) {
        if (!seen.empty() && rand() > RAND_MAX / 2) {
            ecs::Entity lose = *begin(seen);
            manager.destroy_entity(lose);
            seen.erase(lose);
        } else {
            ecs::Entity adding = manager.create_entity();
            ASSERT(!seen.count(adding));
            seen.insert(adding);
        }
    }
}

void test_component_entity_tracking() {
    ecs::internal::EntityManager manager;
}

int main() {
    test_destroy_create();
    test_component_entity_tracking();
}
