#include "../include/ecs/view.hpp"
#include "ecs/common.hpp"
#include "ecs/component_manager.hpp"
#include "ecs/sparse_set.hpp"

void internal::filter_intersection(vector<Entity> &entities,
                                   ISparseSet *array) {
    for (int i = 0; i < entities.size(); i++) {
        // continually shrink and iterate only when i is oik
        while (i < entities.size() && !array->contains(entities[i])) {
            // swap self dies sometimes
            if (i != entities.size() - 1)
                swap(entities[i], entities.back());

            entities.pop_back();
        }
    }
}

vector<Entity> internal::get_view_helper(ComponentManager &manager,
                                         vector<ISparseSet *> &packed_arrays) {
    // get smallest
    ISparseSet *small = packed_arrays[0];
    for (auto *curr : packed_arrays) {
        if (small->size() > curr->size())
            small = curr;
    }

    // create copy and filter
    vector<Entity> entities = small->entities();
    for (auto *curr : packed_arrays) {
        filter_intersection(entities, curr);
    }

    return entities;
}
