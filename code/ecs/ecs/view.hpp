#pragma once
#include "common.hpp"
#include "component_manager.hpp"
#include "sparse_set.hpp"
#include <vector>

std::vector<Entity> get_view_helper(ComponentManager &manager,
                                    std::vector<ISparseSet *> &packed_arrays);

void filter_intersection(std::vector<Entity> &entities, ISparseSet *array);

template <typename... Components>
std::vector<Entity> get_view(ComponentManager &manager) {
    std::vector<ISparseSet *> packed_arrays = {
        manager.get_array<Components>()...};
    return get_view_helper(manager, packed_arrays);
}

/* Notes:
 * Start with smallest and make unions
 * It better to do nlogn sort for O(n) compares for intersections or better to
 * do less signature checks
 *
 */
