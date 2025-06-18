#pragma once
#include "../include/components/components.hpp"
#include "../include/ecs/coordinator.hpp"
#include "../include/graphics/graphics.hpp"

// TODO: consider perfect forwarding to optimize
template <typename... T>
void components_init(Entity entity, Coordinator &coordinator, T... components) {
    (coordinator.assign_component(entity, components), ...);
}
