#pragma once
#include "../ecs/packed_array_manager.hpp"
#include "../ecs/signature_utils.hpp"
#include "../ecs/system.hpp"

#include "../components/position.hpp"
#include "../components/speed.hpp"
#include "../components/velocity.hpp"

class WASD_Input : public System {
public:
    WASD_Input() {
    }
    void run(PackedArrayManager<MAX_COMPONENTS> &component_manager) override {
        for (Entity entity : subscribed_entities) {
        }
    }
    Signature get_signature() override {
        Signature signature = 0;
        signature = signature_utils::set_bit<Position>(signature);
        signature = signature_utils::set_bit<Velocity>(signature);
        signature = signature_utils::set_bit<Speed>(signature);
        return signature;
    }
};
