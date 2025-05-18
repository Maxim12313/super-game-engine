#pragma once
#include "../ecs/component_array.hpp"
#include "../ecs/entity_manager.hpp"
#include "../include/globals.hpp"

struct Game {
    float dt;
    EntityManager entity_manager;

    Entity player;

    ComponentArray<float, MAX_ENTITIES> radii;
    ComponentArray<Vector2, MAX_ENTITIES> positions;
    ComponentArray<Vector2, MAX_ENTITIES> directions;
    ComponentArray<float, MAX_ENTITIES> speeds;
    ComponentArray<Entity, MAX_ENTITIES> enemy_ids;
    ComponentArray<Color, MAX_ENTITIES> colors;
};
