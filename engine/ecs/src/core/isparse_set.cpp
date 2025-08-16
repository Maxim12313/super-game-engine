#include "isparse_set.hpp"

namespace ecs::internal {

void ISparseSet::clear() {
    m_to_idx.clear();
    m_to_entity.clear();
}

// Returns if entity is registered with this packed array
bool ISparseSet::contains(Entity entity) const {
    return m_to_idx.count(entity);
}

size_t ISparseSet::size() const {
    return m_to_entity.size();
}

std::vector<Entity>::const_iterator ISparseSet::begin() const {
    return m_to_entity.begin();
}

std::vector<Entity>::const_iterator ISparseSet::end() const {
    return m_to_entity.end();
}
} // namespace ecs::internal
