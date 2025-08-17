#pragma once
#include <iterator>
#include "ecs/common.hpp"
#include <vector>

// forwarding
namespace ecs::internal {
class ISparseSet;

template <typename T>
class SparseSet;
} // namespace ecs::internal

namespace ecs::internal {

class entity_projection {
public:
    using value_type = Entity;
    value_type operator()(Entity entity,
                          const std::vector<ISparseSet *> &sets) const {
        return entity;
    }
};

template <typename... Components>
class each_projection {
public:
    using value_type = std::tuple<Entity, Components &...>;

    value_type operator()(Entity entity,
                          const std::vector<ISparseSet *> &sets) const {
        int idx = 0;
        return std::tuple<Entity, Components &...>(
            {entity, fetch_val<Components>(entity, idx, sets)...});
    }

private:
    template <typename T>
    T &fetch_val(Entity entity, int &idx,
                 const std::vector<ISparseSet *> &sets) const {
        auto *concrete = static_cast<SparseSet<T> *>(sets[idx]);
        idx++;
        return (*concrete)[entity];
    }
};

}; // namespace ecs::internal
