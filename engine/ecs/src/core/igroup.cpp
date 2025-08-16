#include "igroup.hpp"
#include "isparse_set.hpp"

namespace ecs::internal {

IGroup::IGroup(std::vector<ISparseSet *> &sets) : m_sets(std::move(sets)) {
}

// TODO: finish implementing
void IGroup::update(Entity entity) {
    // detect if changes need to be made
    for (auto &set : m_sets) {
    }

    // make changes if necessary
    for (auto &set : m_sets) {
    }
}

} // namespace ecs::internal
