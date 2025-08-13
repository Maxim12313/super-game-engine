#include "filter.hpp"
#include "ecs/common.hpp"
#include "component_manager.hpp"
#include "sparse_set.hpp"

namespace ecs::internal {

void filter_intersection(std::vector<Entity> &entities, ISparseSet *array) {
    for (int i = 0; i < entities.size(); i++) {
        // continually shrink and iterate only when i is oik
        while (i < entities.size() && !array->contains(entities[i])) {
            // swap self dies sometimes
            if (i != entities.size() - 1)
                std::swap(entities[i], entities.back());

            entities.pop_back();
        }
    }
}

std::vector<Entity> get_view_helper(ComponentManager &manager,
                                    std::vector<ISparseSet *> &packed_arrays) {
    // get smallest
    ISparseSet *small = packed_arrays[0];
    for (auto *curr : packed_arrays) {
        if (small->size() > curr->size())
            small = curr;
    }

    // create copy and filter
    std::vector<Entity> entities = small->entities();
    for (auto *curr : packed_arrays) {
        filter_intersection(entities, curr);
    }

    return entities;
}
} // namespace ecs::internal
