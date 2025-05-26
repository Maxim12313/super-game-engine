#include "../ecs/entity_manager.hpp"
#include "../include/test_utils.hpp"
#include <unordered_set>

// MUST BE LESS THAN THE MAX NUM ENTITIES
constexpr int n = 100;

void test1() {
    EntityManager manager;
    unordered_set<Entity> seen;
    for (int i = 0; i < n; i++) {
        if (!seen.empty() && rand() > RAND_MAX / 2) {
            Entity lose = *begin(seen);
            manager.return_entity(lose);
            seen.erase(lose);
        } else {
            Entity adding = manager.get_entity();
            ASSERT(!seen.count(adding));
            seen.insert(adding);
        }
    }
}

int main() {
    test1();
}
