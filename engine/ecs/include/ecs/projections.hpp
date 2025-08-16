#pragma once
#include <iterator>
#include "ecs/common.hpp"
#include <vector>
#include "../src/sparse_set.hpp"

namespace ecs::internal {

template <typename... Components>
class each_projection {
public:
    using value_type = std::tuple<Entity, Components...>;

    value_type operator()(Entity entity, std::vector<ISparseSet *> &sets) {
        int idx = 0;
        return std::tuple<Entity, Components &...>(
            {entity, fetch_val<Components>(entity, idx)...});
    }

private:
    template <typename T>
    T &fetch_val(Entity entity, int &idx,
                 std::vector<ISparseSet *> &sets) const {
        auto *concrete = static_cast<SparseSet<T> *>(sets[idx]);
        idx++;
        return (*concrete)[entity];
    }
};
}; // namespace ecs::internal
