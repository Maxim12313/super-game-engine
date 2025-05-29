#include "../ecs/system_manager.hpp"
#include "../ecs/system.hpp"

class DoubleSystem : public System {
public:
    DoubleSystem() {
    }
    void run(const ComponentManager &component_manager) override {
    }
    Signature get_signature() override {
    }
};

int main() {
}
