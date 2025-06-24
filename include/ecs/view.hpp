#pragma once
#include "ecs/common.hpp"
#include "ecs/component_manager.hpp"
#include "ecs/packed_array.hpp"
#include <tuple>
#include <vector>

template <typename... Components>
vector<Entity> get_view(ComponentManager &manager) {
    vector<IPackedArray *> packed_arrays = {manager.get_array<Components>()...};
    IPackedArray *small = packed_arrays[0];
    for (int i = 1; i < packed_arrays.size(); i++) {
        if (small->size() > packed_arrays[i]->size())
            small = packed_arrays[i];
    }
    // vector<Entity> entities =
    // for (int i = 0; i < packed_arrays.size(); i++) {
    //
    // }
}

/* Notes:
 * Start with smallest and make unions
 * It better to do nlogn sort for O(n) compares for intersections or better to
 * do less signature checks
 *
 */
