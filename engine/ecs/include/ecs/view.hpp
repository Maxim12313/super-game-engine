#pragma once
#include "../src/core/component_manager.hpp"

namespace ecs {

template <typename... Components>
class View {
public:
    View(const internal::ComponentManager &components);

private:
    std::tuple<Components...> m_components;
};

}; // namespace ecs

namespace ecs {

template <typename... Components>
View<Components...>::View(const internal::ComponentManager &components) {
}

}; // namespace ecs
