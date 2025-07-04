#include "sparse_set.hpp"

void ISparseSet::clear() {
    to_idx.clear();
    to_entity.clear();
}

bool ISparseSet::contains(Entity entity) {
    return to_idx.count(entity);
}

size_t ISparseSet::size() {
    return to_entity.size();
}

const std::vector<Entity> &ISparseSet::entities() {
    return to_entity;
}
