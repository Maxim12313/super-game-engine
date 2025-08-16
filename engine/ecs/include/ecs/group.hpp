#pragma once

namespace ecs::internal {
class IGroup {
    virtual ~IGroup() = default;
};

}; // namespace ecs::internal

namespace ecs {
template <typename... Components>
class Group {};

}; // namespace ecs
