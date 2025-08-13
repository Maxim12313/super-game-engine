#pragma once
#include "ecs/common.hpp"
#include "component_manager.hpp"
#include "sparse_set.hpp"
#include <vector>

namespace ecs::internal {

std::vector<Entity> get_view_helper(ComponentManager &manager,
                                    std::vector<ISparseSet *> &packed_arrays);

void filter_intersection(std::vector<Entity> &entities, ISparseSet *array);

template <typename... Components>
std::vector<Entity> get_view(ComponentManager &manager) {
    std::vector<ISparseSet *> packed_arrays = {
        manager.get_array<Components>()...};
    return get_view_helper(manager, packed_arrays);
}

} // namespace ecs::internal
