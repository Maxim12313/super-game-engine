#pragma once
#include "ecs/common.hpp"
#include "ecs/component_manager.hpp"
#include "ecs/sparse_set.hpp"
#include <vector>

namespace internal {
vector<Entity> get_view_helper(ComponentManager &manager,
                               vector<ISparseSet *> &packed_arrays);

void filter_intersection(vector<Entity> &entities, ISparseSet *array);

}; // namespace internal

template <typename... Components>
vector<Entity> get_view(ComponentManager &manager) {
    vector<ISparseSet *> packed_arrays = {manager.get_array<Components>()...};
    return internal::get_view_helper(manager, packed_arrays);
}

/* Notes:
 * Start with smallest and make unions
 * It better to do nlogn sort for O(n) compares for intersections or better to
 * do less signature checks
 *
 */
