#pragma once
#include "../include/globals.hpp"
#include <stack>

class EntityManager {
private:
    stack<Entity> available_entities;

public:
    EntityManager() {
        for (int id = 0; id < MAX_ENTITIES; id++) {
            available_entities.push(Entity(id));
        }
    }
    // return -1 if fail
    Entity get_entity() {
        if (available_entities.empty())
            return -1;
        Entity res = available_entities.top();
        available_entities.pop();
        return res;
    }
    void return_entity(Entity entity) {
        available_entities.push(Entity(entity));
    }
};
