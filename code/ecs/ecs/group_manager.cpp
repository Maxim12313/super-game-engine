#include "group_manager.hpp"

void GroupManager::update(Entity entity, Signature signature) {
    for (int i = 0; i < groups.size(); i++) {
        Group &group_ents = groups[i];
        Signature group_sig = signatures[i];

        bool is_contained = group_ents.contains(entity);
        bool is_eligible = (group_sig & signature) == group_sig;

        if (is_contained && !is_eligible) {
            // remove it
            group_ents.erase(entity);
        } else if (!is_contained && is_eligible) {
            // add it
            group_ents[entity] = entity;
        }
    }
}
