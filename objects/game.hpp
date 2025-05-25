#pragma once
// #include "../ecs/component_array.hpp"
// #include "../ecs/entity_manager.hpp"
// #include "../include/globals.hpp"
//

struct Game {};

// struct Game {
//     float dt;
//     EntityManager entity_manager;
//
//     // Entities
//     Entity player;
//     ComponentArray<Entity, MAX_ENTITIES> enemy_ids;
//
//     // properties
//     ComponentArray<float, MAX_ENTITIES> radii;
//     ComponentArray<Vector2, MAX_ENTITIES> positions;
//     ComponentArray<Vector2, MAX_ENTITIES> directions;
//     ComponentArray<float, MAX_ENTITIES> speeds;
//     ComponentArray<Color, MAX_ENTITIES> colors;
//
//     float &get_radius(Entity id) {
//         return radii.get(id);
//     }
//     Vector2 &get_position(Entity id) {
//         return positions.get(id);
//     }
//     Vector2 &get_directions(Entity id) {
//         return directions.get(id);
//     }
//     Color &get_color(Entity id) {
//         return colors.get(id);
//     }
//     float &get_speed(Entity id) {
//         return speeds.get(id);
//     }
// };
