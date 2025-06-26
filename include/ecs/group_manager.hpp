#pragma once
#include "ecs/common.hpp"
#include "ecs/signature_manager.hpp"
#include "ecs/signature_utils.hpp"
#include "ecs/sparse_set.hpp"
#include <unordered_map>

using Group = SparseSet<Entity>;

// NOTE: does not support group deletion
class GroupManager {
private:
    vector<Group> groups;
    vector<Signature> signatures;
    unordered_map<int, int> sig_to_idx;

    // reuse view code for creating group and make group in
    // coordinator
    void create_group(Signature signature) {
        Group group;
    }

public:
    // creates the group if it doesn't exist
    template <typename... Component>
    const Group &get_group() {
        Signature signature = internal::set_signature<Component...>();
        if (!sig_to_idx.count(signature))
            create_group(signature);
        return groups[sig_to_idx[signature]];
    }

    void update(Entity entity, Signature signature);
};
