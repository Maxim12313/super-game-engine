#include "ecs/group.hpp"
#include "isparse_set.hpp"

namespace ecs::internal {
// class public ********
ISparseSet::ISparseSet() : m_group(nullptr) {
}

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

void ISparseSet::set_group(Group *group) {
    ASSERT_MSG(!m_group, "Replacing an existing group is not allowed");
    m_group = group;
}

} // namespace ecs::internal
